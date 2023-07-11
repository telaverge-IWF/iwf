/*********************************-*-CPP-*-************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/

#include "ReplicationClient.h"
#include "Logger.h"
ReplicationClient * ReplicationClient::instance=NULL;
CouchbaseConnectorBean ReplicationClient::connDetails;
std::vector<ReplicaBean> ReplicationClient::replicas;
ReplicationSyncConnectorPool * ReplicationClient::syncConnPool=NULL;
eAccelero::Mutex ReplicationClient::instanceLock;
ReplicationStatusCbk ReplicationClient::replStatusCbk=NULL;
ReplicationClientConnectRetryThread ReplicationClient::retryConnectionThread;
OperationTimeoutHandleThread ReplicationClient::OpTimeoutHandleThread;

eAccelero::Atomic<int32_t> ReplicationClient::cbTimeoutStatus;

#define BUCKET "dreBucket"
#define MAX_STATS_BUF_SIZE 10000

#define OP_TIMEOUT_THRED_SLEEP_TIME 100000 //in microseconds
#define MAX_LINE_SIZE 200

int32_t ReplicationClient::StartRetryConnectionThread()
{

    retryConnectionThread.SetRetryMax(ReplicationClient::connDetails.retryConnMax);
    Thread *thread=new Thread("RetryConnectionThread");
    DLOG_DEBUG("Starting RetryConnectionThread...");
    thread->Start(&retryConnectionThread);
    return SUCCESS;
}

int32_t ReplicationClient::StartOpTimeoutHandleThread()
{

    CLOG_DEBUG("Starting OpTimeoutHandleThread");
    Thread *thread= new Thread("OpTimeoutHandleThread");
    OpTimeoutHandleThread.SetKey("TimeoutTest");
    thread->Start(&OpTimeoutHandleThread);
    OpTimeoutHandleThread.SetRunning(true);
    return SUCCESS;
}
//Run method for OpTimeoutRetryThread
void OperationTimeoutHandleThread::Run(void *arg)
{
    bool running=true;
    eAccelero::ScopedLogger scopedLogger(ReplicationClient::GetInstance()->GetLogger());
    DLOG_DEBUG(">>>> OperationTimeoutHandleTherad::Run >>>>");
    char tempBuf[10];
    uint32_t len=0;
    int32_t ret=LCB_SUCCESS;
    int32_t initRet=LCB_SUCCESS;
    int32_t syncConnRet=!LCB_SUCCESS;
    int32_t asyncConnRet=!LCB_SUCCESS;
    DisableOperations();
    ReplicationConnector *opTimeoutConnector=ReplicationClient::GetInstance()->GetOpTimeoutConnector();

    while(running)
    {
        ret=LCB_SUCCESS;
        initRet=LCB_SUCCESS;
        usleep(OP_TIMEOUT_THRED_SLEEP_TIME);
        if((ReplicationClient::GetInstance()->cbTimeoutStatus) == LCB_ETIMEDOUT )
        {
            DLOG_DEBUG("Trying for key=%s",key.c_str());
            //trying for range of 10 keys,just to make sure we try from all the couchbase nodes in the cluster
            for(int32_t i =0; i< 10; i++)
            {

                std::stringstream tmp;
                tmp.str(std::string());
                tmp << key << i;
                std::string tmpStr=tmp.str();
                initRet=opTimeoutConnector->GetEntry(tmpStr,tempBuf,&len);
                if((initRet == LCB_NETWORK_ERROR) || (initRet == LCB_ETIMEDOUT) ||
                        (initRet == LCB_CONNECT_ERROR))
                {
                    ret=LCB_ETIMEDOUT;
                }

                if(syncConnRet != LCB_SUCCESS ||  asyncConnRet != LCB_SUCCESS)
                {
                    DLOG_ERROR("Waiting to re-establish sync/async connections!");
                    ret=LCB_ETIMEDOUT;
                }
            }
            if(ret == LCB_ETIMEDOUT)
            {

                DLOG_ERROR("Still Getting operation timeout! Retrying...");
                (ReplicationClient::GetInstance()->cbTimeoutStatus)=LCB_ETIMEDOUT;
                if(syncConnRet!=LCB_SUCCESS && (syncConnRet=ReplicationClient::GetInstance()->GetSyncConnPool()->Reconnect(true))!= LCB_SUCCESS)
                {
                    DLOG_ERROR("Reconnect all Sync connections!");
                    if(syncConnRet == REPL_BUCKET_ENOENT)
                    {
                        DLOG_ERROR("Retry reconnect with localhost!");

                        if((syncConnRet=ReplicationClient::GetInstance()->GetSyncConnPool()->Reconnect(true,true))!= LCB_SUCCESS)
                        {
                            DLOG_ERROR("Reconnect with localhost also failed!");
                        }
                        else
                        {
                            DLOG_ERROR("Sync connection retry with local host is success!");
                        }
                    }
                    //return ret;
                }
                else
                {
                    DLOG_ERROR("Sync Connector reconnect success!");
                }

                /*Initialize the ReplicationThreadPool*/

                DLOG_ERROR("Reconnect all ASync connections!");
                if(asyncConnRet != LCB_SUCCESS && (asyncConnRet=ReplicationThreadPool::GetInstance()->Reconnect(true))!= LCB_SUCCESS)
                {

                    DLOG_ERROR("Replication Thread Pool Retry connect failed!");
                    //return ret;
                }
                else
                {
                    DLOG_ERROR("Replication Thread pool Retry finally Success!");
                }



            }
            else
            {
                DLOG_ERROR("Restored connection to all couchbase nodes!");
                syncConnRet=!LCB_SUCCESS;
                asyncConnRet=!LCB_SUCCESS;

                (ReplicationClient::GetInstance()->cbTimeoutStatus)=LCB_SUCCESS;
            }


        }
    }
    EnableOperations();
    SetRunning(false);

    DLOG_DEBUG("<<<< ReplicationClientConnectRetryThread::Run <<<<");
}


//Run method for RetryConnectionThread
void ReplicationClientConnectRetryThread::Run(void *arg)
{

    eAccelero::ScopedLogger scopedLogger(ReplicationClient::GetInstance()->GetLogger());
    DLOG_DEBUG(">>>> ReplicationClientConnectRetryThread::Run >>>>");
    int32_t syncConnRet=SUCCESS;
    int32_t asyncConnRet=SUCCESS;

    ReplicationClient * instance=ReplicationClient::GetInstance();

    ReplicationStatusCbk replStatusCbk=instance->GetReplStatusCbk();
    DLOG_DEBUG("replStatsusCbk got=%p",replStatusCbk);
    if(retryMax==0)
    {
 	    //if retryMax is set to 0 , retry indefinately until connection succeeds
	    retryMax=-1;
    }
    syncConnRet=!SUCCESS;
    asyncConnRet=!SUCCESS;

    while( retryMax != 0)
    {
        //for all connections marked as DISCONNECTED in AsyncThreadPool and SyncPool try to connect again.

       if(syncConnRet!=SUCCESS && (syncConnRet=instance->GetSyncConnPool()->Reconnect(false))!= SUCCESS)
        {
            DLOG_ERROR("Sync connection pool Retry connect failed!");
            if(syncConnRet == REPL_BUCKET_ENOENT)
            {
                DLOG_DEBUG("Retry reconnect with localhost!");

                if((syncConnRet=instance->GetSyncConnPool()->Reconnect(false,true))!= SUCCESS)
                {
                    DLOG_DEBUG("Reconnect with localhost also failed!");
                }
            }
            //return ret;
        }

        /*Retry Async pool connections */

        if((asyncConnRet=ReplicationThreadPool::GetInstance()->Reconnect(false))!= SUCCESS)
        {

            DLOG_ERROR("Replication Thread Pool Retry connect failed!");
            //return ret;
        }


        if( syncConnRet == SUCCESS && asyncConnRet == SUCCESS)
        {
            if(replStatusCbk)
            {
                DLOG_DEBUG("Call the replicationStatus Callback!");
                replStatusCbk(true);
                DLOG_DEBUG("Starting the timeout monitor thread");
                ReplicationClient::GetInstance()->StartOpTimeoutHandleThread();
            }
            break;
        }
        else
        {
            if(!replStatusCbk)
            {
         //       replStatusCbk(false);
            }
        }
	    retryMax--;

    }
    CLOG_DEBUG("<<<< ReplicationClientConnectRetryThread::Run <<<<");
}

int32_t ReplicationClient::Initialize(uint32_t syncPoolSize,uint32_t asyncPoolSize,
        CouchbaseConnectorBean &connDetails,
        std::vector<ReplicaBean> &replicaInfo,
        eAccelero::Logger &logger)
{
    int32_t ret=SUCCESS;
    int32_t initRet=SUCCESS;
    if(!instance)
    {
        instance=new ReplicationClient(logger);
        ReplicationClient::connDetails=connDetails;

        ReplicaBean rBean;
        rBean.replicaName="DiameterSession";
        rBean.replicaSize=512;
        rBean.replicaTTL=1;

        std::vector<ReplicaBean> replicas;
        replicas.push_back(rBean);
        /*Initialize the SyncConnectorPool*/
        instance->syncConnPool= new ReplicationSyncConnectorPool();
        eAccelero::ScopedLogger scopedLogger(instance->GetLogger());
        if((ret=instance->syncConnPool->Initialize(syncPoolSize,replicas,connDetails))!= SUCCESS)
        {
            if(ret == REPL_BUCKET_ENOENT)
            {
                CouchbaseConnectorBean retryBean=connDetails;
                retryBean.serverAddress="localhost";

                if((ret=instance->syncConnPool->Reconnect(false,true))!= SUCCESS)
                {

                    DLOG_ERROR("Second try!Sync connection pool initialization failed!");
                    initRet=ret;

                }

            }
            else
            {
                DLOG_ERROR("Sync connection pool initialization failed!");
                initRet=ret;
            }
        }

        /*Initialize the ReplicationThreadPool*/

        if((ret=ReplicationThreadPool::GetInstance()->Initialize(asyncPoolSize,replicas,connDetails))!= SUCCESS)
        {
            if(ret == REPL_BUCKET_ENOENT)
            {
                CouchbaseConnectorBean retryBean=connDetails;
                retryBean.serverAddress="localhost";
                if((ret=ReplicationThreadPool::GetInstance()->Initialize(asyncPoolSize,replicas,retryBean))!= SUCCESS)
                {
                    DLOG_ERROR("Second try! Replication Thread Pool Initialization failed!");
                    initRet=ret;

                }

            }
            else
            {
                DLOG_ERROR("Replication Thread Pool Initialization failed!");
                initRet=ret;
            }
        }
        if( initRet != SUCCESS )
        {
            DLOG_ERROR("Replication Client Initialization failed!");
            DLOG_DEBUG("Start Retry connection thread...");
            StartRetryConnectionThread();

        }
        else
        {
            DLOG_DEBUG("Starting the couchbase timeout monitor thread");
            StartOpTimeoutHandleThread();
        }

      //  replicas=replicaInfo;

        ReplicationThreadPool::GetInstance()->InitializeReplicationStats(asyncPoolSize,
                    replicas);
    }
    else
    {
        DLOG_DEBUG("ReplicationClient already Initialized\n");
    }
    return initRet;
}

int32_t ReplicationClient::Terminate()
{

    /*Terminate the ReplicationThreadPool*/
    ReplicationThreadPool::GetInstance()->Terminate();

    /*Terminate the ReplicationSyncConnectorPool*/
    syncConnPool->Terminate();

    return SUCCESS;
}


int32_t ReplicationClient::ReplicateNewEntry(std::string replicaName,std::string key,void *data, uint32_t dataLen, uint32_t expiryTime)
{
    eAccelero::ScopedLogger scopedLogger(this->GetLogger());
    int32_t ret=SUCCESS;
    if(ReplicationClient::GetInstance()->cbTimeoutStatus == LCB_ETIMEDOUT )
    {
        DLOG_WARNING("Insert Operations are disabled temporarily");
        return LCB_ETIMEDOUT;
    }


    /*form an event with operation INSERT from the data*/
    ReplicationEvent *event=new ReplicationEvent(INSERT,replicaName,key,dataLen,data);
    if (expiryTime)
    {
        event->expiryTime = expiryTime;
    }
    /*Post the event to the ReplicationThreadPool*/
    ReplicationThreadPool::GetInstance()->PostToThreadQ(event);


    return ret;
}


int32_t ReplicationClient::ReplicateUpdatedEntry(std::string replicaName,std::string key, void *data, uint32_t dataLen, uint32_t expiryTime)
{

    eAccelero::ScopedLogger scopedLogger(this->GetLogger());
    int32_t ret=SUCCESS;
    if(ReplicationClient::GetInstance()->cbTimeoutStatus == LCB_ETIMEDOUT )
    {
        DLOG_WARNING("Update Operations are disabled temporarily");
        return LCB_ETIMEDOUT;
    }


  /*form an event with operation UPDATE from the data*/
    //ReplicationEvent event(UPDATE,replicaName,key,dataLen,data);
    ReplicationEvent *event=new ReplicationEvent(UPDATE,replicaName,key,dataLen,data);
    if (expiryTime)
    {
        event->expiryTime = expiryTime;
    }
    /*Post the event to the ReplicationThreadPool*/
    ReplicationThreadPool::GetInstance()->PostToThreadQ(event);

    return ret;

}

int32_t ReplicationClient::ReplicateDeletedEntry(std::string replicaName,std::string key)
{
    eAccelero::ScopedLogger scopedLogger(this->GetLogger());
    int32_t ret=SUCCESS;
    if(ReplicationClient::GetInstance()->cbTimeoutStatus == LCB_ETIMEDOUT )
    {
        DLOG_WARNING("Delete Operations are disabled temporarily");
        return LCB_ETIMEDOUT;
    }


    /*form an event with operation REMOVE from the data*/
    //ReplicationEvent event(REMOVE,replicaName,key,0,NULL);
    ReplicationEvent *event=new ReplicationEvent(REMOVE,replicaName,key,0,NULL);
    /*Post the event to the ReplicationThreadPool*/
    ReplicationThreadPool::GetInstance()->PostToThreadQ(event);

    return ret;

}

/*if all raplication connectors are in use REPL_ALL_CONNECTORS_INUSE will be returned*/
int32_t ReplicationClient::GetReplicatedEntry(std::string replicaName,std::string key, void *data,
        uint32_t *dataLen)
{

    int ret=SUCCESS;
    /*Get the free instance from the sync connector pool*/

    std::string newKey=replicaName;
    newKey.append(key);
    ReplicationConnector * syncConn=syncConnPool->GetConnector(DEF_REPLICA_NAME);
    if ( syncConn == NULL)
    {
        CLOG_ERROR("All ReplicationConnectors are in use for %s",replicaName.c_str());
        return REPL_ALL_CONNECTORS_INUSE;
    }

    if((ReplicationClient::GetInstance()->cbTimeoutStatus)!= LCB_ETIMEDOUT && (ret=syncConn->GetEntry(newKey,data,dataLen)) != SUCCESS )
    {
        //if we get an operation timeout/network error/connect error set the atomic variable to timeout state
        if((ret == LCB_NETWORK_ERROR) || (ret == LCB_ETIMEDOUT) ||
                (ret == LCB_CONNECT_ERROR)|| (ret == REPL_CLIENT_ETMPFAIL))
        {
            CLOG_WARNING("Timeout/Network error , setting cbTimeoutStatus");
            (ReplicationClient::GetInstance()->cbTimeoutStatus)=LCB_ETIMEDOUT;
        }


        /*Release the aquired connection back to the sync connector pool*/
        syncConnPool->ReleaseConnection(DEF_REPLICA_NAME,syncConn);
        return ret;
    }
    else
    if((ReplicationClient::GetInstance()->cbTimeoutStatus) == LCB_ETIMEDOUT)
    {
        CLOG_WARNING("Fetch Operations are disabled temporarily");
        ret=LCB_ETIMEDOUT;
    }



    /*Use the connector and release it back to the sync connector pool*/

    syncConnPool->ReleaseConnection(DEF_REPLICA_NAME,syncConn);
    return ret;
}


/*if all raplication connectors are in use REPL_ALL_CONNECTORS_INUSE will be returned*/
int32_t ReplicationClient::GetReplicatedEntry(std::string replicaName,std::string key, std::string &data,
        uint32_t *dataLen)
{
    int ret=SUCCESS;
    std::string newKey=replicaName;
    newKey.append(key);
    /*Get the free instance from the sync connector pool*/
    ReplicationConnector * syncConn=syncConnPool->GetConnector(DEF_REPLICA_NAME);
    if ( syncConn == NULL)
    {
        CLOG_ERROR("All ReplicationConnectors are in use for %s",replicaName.c_str());
        return REPL_ALL_CONNECTORS_INUSE;
    }

    if((ReplicationClient::GetInstance()->cbTimeoutStatus) != LCB_ETIMEDOUT && (ret=syncConn->GetEntry(newKey,data,dataLen)) != SUCCESS )
    {

        //if we get an operation timeout/network error/connect error set the atomic variable to timeout state
        if((ret == LCB_NETWORK_ERROR) || (ret == LCB_ETIMEDOUT) ||
                (ret == LCB_CONNECT_ERROR))
        {
            CLOG_WARNING("Timeout/Network error , setting cbTimeoutStatus");
            (ReplicationClient::GetInstance()->cbTimeoutStatus)=LCB_ETIMEDOUT;
        }



        /*Release the aquired connection back to the sync connector pool*/
        syncConnPool->ReleaseConnection(DEF_REPLICA_NAME,syncConn);
        return ret;
    } else if((ReplicationClient::GetInstance()->cbTimeoutStatus) == LCB_ETIMEDOUT)
    {
        CLOG_DEBUG("Fetch Operations are disabled temporarily");
        ret=LCB_ETIMEDOUT;
    }

   /*Use the connector and release it back to the sync connector pool*/
    syncConnPool->ReleaseConnection(DEF_REPLICA_NAME,syncConn);
    return ret;
}

//Initialize should be called before invoking GetInstance
ReplicationClient * ReplicationClient::GetInstance()
{
    eAccelero::Mutex::ScopedMutex sMutex(instanceLock);
    if(instance)
    {
        return instance;
    }
    else
    {
        return NULL;
    }

}

Logger& ReplicationClient::GetLogger()
{
    return m_logger;
}


uint32_t ReplicationClient::GetReplicationPoolSize()
{
    return ReplicationThreadPool::GetInstance()->GetReplicationThreadPoolSize();
}

uint32_t ReplicationClient::GetReplicationThreadQSize(uint32_t threadIndex)
{
    return ReplicationThreadPool::GetInstance()->GetReplicationThreadQSize(threadIndex);
}

ReplicationConnector * ReplicationClient::GetOpTimeoutConnector()
{

    return syncConnPool->GetOpTimeoutConnector();

}

void ReplicationClient::FormStatsString( std::string bucketName,uint32_t index,uint32_t insertSuccess, uint32_t insertFailure,
                                          uint32_t updateSuccess, uint32_t updateFailure, uint32_t deleteSuccess,
                                          uint32_t deleteFailure,char *formatStringLine)
{
    formatStringLine[0]='\0';
    sprintf(formatStringLine,"%-27s[%d] |%-15u|%-15u|%-15u|%-15u|%-15u|%-15u\n",bucketName.c_str(),index,
            insertSuccess,insertFailure,updateSuccess,updateFailure,deleteSuccess,deleteFailure);

}

void ReplicationClient::ResetReplicationStats()
{
    ReplicationThreadPool::GetInstance()->ResetReplicationStats();
}

void ReplicationClient::GenerateReplicationStats(std::string &replStats)
{
    char formatString[MAX_STATS_BUF_SIZE];
    char formatStringLine[MAX_LINE_SIZE];
    snprintf(formatString,MAX_STATS_BUF_SIZE,"%-30s |%-15s|%-15s|%-15s|%-15s|%-15s|%-15s","Replica","Insert-Success","Insert-Failure","Update-Success","Update-Failure","Delete-Success","Delete-Failure\n");
    std::vector<uint32_t> insertSuccessStats;
    std::vector<uint32_t> insertFailureStats;
    std::vector<uint32_t> updateSuccessStats;
    std::vector<uint32_t> updateFailureStats;
    std::vector<uint32_t> deleteSuccessStats;
    std::vector<uint32_t> deleteFailureStats;
    CLOG_DEBUG(">>> ReplicationClient::GenerateReplicationStats >>> %s",replStats.c_str());
    for( uint32_t i=0; i< replicas.size();i++)
    {

        CLOG_DEBUG("---Replica[%d]---",i);
        ReplicationThreadPool::GetInstance()->GetReplStatsInsertSuccess(replicas[i],insertSuccessStats);

        ReplicationThreadPool::GetInstance()->GetReplStatsInsertFailure(replicas[i],insertFailureStats);
        ReplicationThreadPool::GetInstance()->GetReplStatsUpdateSuccess(replicas[i],updateSuccessStats);
        ReplicationThreadPool::GetInstance()->GetReplStatsUpdateFailure(replicas[i],updateFailureStats);
        ReplicationThreadPool::GetInstance()->GetReplStatsDeleteSuccess(replicas[i],deleteSuccessStats);
        ReplicationThreadPool::GetInstance()->GetReplStatsDeleteFailure(replicas[i],deleteFailureStats);
        for( uint32_t j=0; j < insertSuccessStats.size();j++)
        {
            CLOG_DEBUG("----j=%d---",j);
            FormStatsString(replicas[i].replicaName,j,insertSuccessStats[j],insertFailureStats[j],
                            updateSuccessStats[j],updateFailureStats[j],deleteSuccessStats[j],
                            deleteFailureStats[j],formatStringLine);
            strncat(formatString,formatStringLine,MAX_STATS_BUF_SIZE);

        }

        /**/
    }
    replStats=formatString;
}


int32_t ReplicationClient::RegisterReplicationStatusCbk(ReplicationStatusCbk replStatusCbk)
{
    //register the replicationStatus callback
    CLOG_DEBUG("Callback Addr %p",replStatusCbk);
    ReplicationClient::replStatusCbk=replStatusCbk;
    return SUCCESS;
}

int32_t ReplicationClient::GetBulkReplicatedEntries(std::string replicaName,int32_t start, int32_t end, std::vector<std::string> &outData)
{
    CLOG_DEBUG(">>>>GetBulkReplicatedEntries>>>>");
    std::vector<std::string> range;
    std::vector<std::string> keys;
   
    for(int32_t i=start;i<end; i++)
    {

        //printf("i=%d\n",i);
        std::stringstream tmp;
        tmp.str(std::string());
        tmp << replicaName << i;
        std::string tmpStr=tmp.str();    
        range.push_back(tmpStr);
        //CLOG_DEBUG("i=%d key=%s keysLen=%d",i,range[i].c_str());
        
        //printf("i=%d key=%s\n keyLen=%d",i,range[i-1].c_str(),range[i].length());
        
    }

    int32_t ret=SUCCESS;
    //std::string newKey=replicaName;
    //newKey.append(key);
    /*Get the free instance from the sync connector pool*/
    ReplicationConnector * syncConn=syncConnPool->GetConnector(DEF_REPLICA_NAME);
    if ( syncConn == NULL)
    {
        CLOG_ERROR("All ReplicationConnectors are in use for %s",replicaName.c_str());
        return REPL_ALL_CONNECTORS_INUSE;
    }

    CLOG_DEBUG("SyncConn obj=%p",syncConn);
    if ((ReplicationClient::GetInstance()->cbTimeoutStatus) != LCB_ETIMEDOUT )
    {
        if((ret=syncConn->GetBulkEntries(range,keys,true)) != SUCCESS )
        {
            /*Release the aquired connection back to the sync connector pool*/
            syncConnPool->ReleaseConnection(DEF_REPLICA_NAME,syncConn);
            if((ret == LCB_NETWORK_ERROR) || (ret == LCB_ETIMEDOUT) ||
                    (ret == LCB_CONNECT_ERROR))
            {
                CLOG_WARNING("Timeout/Network error , setting cbTimeoutStatus");
                (ReplicationClient::GetInstance()->cbTimeoutStatus)=LCB_ETIMEDOUT;
            }
            else if(ret == LCB_KEY_ENOENT)
            {
                CLOG_DEBUG("None of the Range keys are present");
            }

            return ret; //REPL_NO_KEYS_FOR_BULK_FETCH;
        }
    }
    //Get the actual data with fetched keys
    if((ReplicationClient::GetInstance()->cbTimeoutStatus) != LCB_ETIMEDOUT )
    {
        if((ret=syncConn->GetBulkEntries(keys,outData) != SUCCESS))
        {
            /*Release the aquired connection back to the sync connector pool*/
            syncConnPool->ReleaseConnection(DEF_REPLICA_NAME,syncConn);
            if((ret == LCB_NETWORK_ERROR) || (ret == LCB_ETIMEDOUT) ||
                    (ret == LCB_CONNECT_ERROR))
            {
                CLOG_WARNING("Timeout/Network error , setting cbTimeoutStatus");
                (ReplicationClient::GetInstance()->cbTimeoutStatus)=LCB_ETIMEDOUT;
            }
            else if(ret == LCB_KEY_ENOENT)
            {
                CLOG_DEBUG("Range keys are not present");
            }

            return ret;
        }
    }
    else
    {
        ret = LCB_ETIMEDOUT;
    }


    /*Use the connector and release it back to the sync connector pool*/
    syncConnPool->ReleaseConnection(DEF_REPLICA_NAME,syncConn);
    CLOG_DEBUG("<<<<GetBulkReplicatedEntries<<<<");
    return ret;


}
