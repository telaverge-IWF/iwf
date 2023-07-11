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


#include "ReplicationConnectorThreadPool.h"
#include <iostream>
#include "ReplicationErrors.h"
#include "Statistics.h"
#define MAX_BULK_OP_SIZE 2

ReplicationThreadPool *ReplicationThreadPool::instance=NULL;
std::vector<ReplicationThread*> ReplicationThreadPool::repThreads;
std::vector<Thread*> ReplicationThreadPool::threads;
uint32_t ReplicationThreadPool::poolSize=0;
eAccelero::Mutex ReplicationThreadPool::instanceLock;
ReplStatsMap *ReplicationThread::m_replStatMapRef=NULL;

Hash ReplicationThreadPool::hash;

int32_t ReplicationThread::Initialize(std::vector<ReplicaBean> &replicas,
        CouchbaseConnectorBean &connectionInfo)
{
    DLOG_DEBUG(">>>> ReplicationThread::Initialize >>>>");
    int32_t ret=SUCCESS;
    int32_t initRet=SUCCESS;

    /*Create the ReplicationConnectors to all the replicas/buckets */
    DLOG_INFO("Initializing ReplicationThread");
    DLOG_INFO("Server Address=%s Port=%u Username=%s Password=%s",
            connectionInfo.serverAddress.c_str(),connectionInfo.serverPort,
            connectionInfo.userName.c_str(),
            connectionInfo.password.c_str());
    /*temp connection to get the server list from the cluster*/
    ReplicationConnector *dummy=new CouchbaseConnector(connectionInfo.serverAddress,
            connectionInfo.serverPort,
            connectionInfo.userName,
            connectionInfo.password,
            DEF_REPLICA_NAME,
            false);
    std::string serverList;
    if( (ret=dummy->GetServerList(serverList))!= SUCCESS)
    {
        DLOG_ERROR("Failed to connect to cluster and obtain server list");
        if( ret != REPL_BUCKET_ENOENT )
        {
            initRet=ret;
        }
        else
        {
            serverList="localhost";
            DLOG_DEBUG("Retry connection to cluster..");
        }

    }
    else
    {
        DLOG_DEBUG("ServerList=%s",serverList.c_str());
    }
    delete dummy;

    //need to create only one connector to the default bucket
    DLOG_DEBUG("Creating ReplicationConnector to server %s for replica %s",serverList.c_str(),DEF_REPLICA_NAME);
    ReplicationConnector *connector=new CouchbaseConnector(serverList,
            connectionInfo.serverPort,
            connectionInfo.userName,
            connectionInfo.password,
            DEF_REPLICA_NAME,
            false);
    /*Connect to the target replica*/
        if(initRet == SUCCESS)
        {
            if((ret=connector->Connect()) != SUCCESS)
            {
                DLOG_ERROR("Connection Failure! ");
                DLOG_ERROR("Server Address=%s Port=%u Username=%s Password=%s Replica Name=%s",
                        connectionInfo.serverAddress.c_str(),connectionInfo.serverPort,
                        connectionInfo.userName.c_str(),
                        connectionInfo.password.c_str(), DEF_REPLICA_NAME);

                initRet=ret;
                if( ret == REPL_BUCKET_ENOENT )
                {
                    DLOG_DEBUG("Setting Connection state= CONNECTED before retrying..");
                    connector->SetConnectionState(CONNECTED);
                }
                else
                {
                    DLOG_DEBUG("Setting Connection state= DISCONNECTED");
                    connector->SetConnectionState(DISCONNECTED);
                }
                //return ret;
            }
            else
            {
                DLOG_INFO("Successfully connected to server:<%s> and replica:<%s>",serverList.c_str(),DEF_REPLICA_NAME);
                connector->SetConnectionState(CONNECTED);
            }
        }
        /*Populate the connMap*/
        connMap[DEF_REPLICA_NAME]=connector;


    DLOG_DEBUG("<<<< ReplicationThread::Initialize <<<");
    return initRet;
}

bool ReplicationThread::CheckForBulkOperations()
{
    DLOG_DEBUG(">>>>ReplicationThread::CheckForBulkOperations:Thread %p >>>>",this);
    //Get the Q size
    //currentQSize set to Qsize+1 as a pop happened just before this function call
    m_curQSize=threadQ.Size()+1;
    DLOG_DEBUG("Thread %p : Current Q Size: %d, m_lcbWaitCounter %d, m_opCounter %d, m_lcbWait",this,m_curQSize,m_lcbWaitCounter,m_opCounter,m_lcbWait);

    if(m_lcbWaitCounter == 0)
    {

        //if Q size is more than our max window size ,
        //set the lcbWaitCounter to m_maxBulkOpSize
        if(m_curQSize > m_maxBulkOpSize)
        {
            m_lcbWaitCounter = m_maxBulkOpSize;

            DLOG_DEBUG("m_curQSize > m_maxBulkOpSize Thread %p : Current Q Size: %d, m_lcbWaitCounter %d, m_opCounter %d, m_lcbWait",this,m_curQSize,m_lcbWaitCounter,m_opCounter,m_lcbWait);
        }
        else
        {
            m_lcbWaitCounter = m_curQSize;

            DLOG_DEBUG(" m_lcbWaitCounter = m_curQSize; Thread %p : Current Q Size: %d, m_lcbWaitCounter %d, m_opCounter %d, m_lcbWait",this,m_curQSize,m_lcbWaitCounter,m_opCounter,m_lcbWait);
        }
    }


    if(m_lcbWaitCounter >1)
    {
        DLOG_DEBUG("Decrement lcbWaitCounter");
        m_lcbWaitCounter--;
        m_opCounter++;
        m_lcbWait=false;
        DLOG_DEBUG("m_lcbWaitCounter >1: Thread %p : Current Q Size: %d, m_lcbWaitCounter %d, m_opCounter %d, m_lcbWait",this,m_curQSize,m_lcbWaitCounter,m_opCounter,m_lcbWait);
    }
    else
    {
        DLOG_DEBUG("lcbWaitCounter to true");
        //check the Q size again
/*        m_curQSize = threadQ.Size();
        DLOG_DEBUG("m_curQSize = threadQ.Size();: Thread %p : Current Q Size: %d, m_lcbWaitCounter %d, m_opCounter %d, m_lcbWait",this,m_curQSize,m_lcbWaitCounter,m_opCounter,m_lcbWait);
        if(m_curQSize != 0)//TEST
        {
            if(m_opCounter < m_maxBulkOpSize)
            {
                //we can further delay calling lcb_wait
                m_lcbWaitCounter++;
                m_opCounter++;
                m_lcbWait=false;

                DLOG_DEBUG("m_opCounter < m_maxBulkOpSize )_curQSize = threadQ.Size();: Thread %p : Current Q Size: %d, m_lcbWaitCounter %d, m_opCounter %d, m_lcbWait",this,m_curQSize,m_lcbWaitCounter,m_opCounter,m_lcbWait);
            }
            else
            {
                m_lcbWait=true;
                //reset the counters
                m_lcbWaitCounter=0;
                m_opCounter=0;

                DLOG_DEBUG("1:ResetCounters _curQSize = threadQ.Size();: Thread %p : Current Q Size: %d, m_lcbWaitCounter %d, m_opCounter %d, m_lcbWait",this,m_curQSize,m_lcbWaitCounter,m_opCounter,m_lcbWait);
            }
        }
        else
        */
        {
            m_lcbWait=true;
            //reset the counters
            m_lcbWaitCounter=0;
            m_opCounter=0;
            DLOG_DEBUG("2:ResetCounters _curQSize = threadQ.Size();: Thread %p : Current Q Size: %d, m_lcbWaitCounter %d, m_opCounter %d, m_lcbWait",this,m_curQSize,m_lcbWaitCounter,m_opCounter,m_lcbWait);
        }
    }
    DLOG_DEBUG("<<<<ReplicationThread::CheckForBulkOperations:Thread %p<<<<",this);
    return SUCCESS;
}

/*Run method for replication thread*/
void ReplicationThread::Run(void *arg)
{

    m_maxBulkOpSize=ReplicationClient::GetInstance()->GetConnDetails().bulkOperationMax;
    //counters for deciding when to call lcb_wait(couchbase function)
    m_lcbWaitCounter=0;
    m_opCounter=0;
    //flag which is passed into couchbase connector function to
    //take decision whether to call lcb_wait
    m_lcbWait=true;

    m_curQSize=0;

    bool active=true;
    static uint32_t stIndx=0;
    ReplicationEvent *event=NULL;
    eAccelero::ScopedLogger scopedLogger(ReplicationClient::GetInstance()->GetLogger());
    DLOG_DEBUG("Starting ReplicationThread %p",this);
    StatsIndex = stIndx;
    stIndx++;
    DLOG_DEBUG("StatsIndex=%u , Addr=%p",StatsIndex,&StatsIndex);

    DLOG_DEBUG("NewStatsIndex=%u",stIndx);
    while(active)
    {

        threadQ.WaitAndPop(event);
        CheckForBulkOperations();
        DLOG_DEBUG("Got event for ReplicationThread %p",this);
        DLOG_DEBUG("AFTER DECISION Thread %p : Current Q Size: %d, m_lcbWaitCounter %d, m_opCounter %d, lcbWait=%d",this,m_curQSize,m_lcbWaitCounter,m_opCounter,m_lcbWait);
        connectionMap::iterator it;
        if(event->operationId == TERMINATE)
        {
            DLOG_INFO("Got TERMINATE event from the ReplicationThreadPool");
            active=false;
            //Disconnect all the connections
            delete event;
            event=NULL;
            Terminate();
            return;
        }

        /*Find out the bucket/replica name from the ReplicationEvent received*/
        /*Using the bucket/replica name as the key get the ReplicationConnector from the connMap*/
        it=connMap.find(DEF_REPLICA_NAME);
        if(it==connMap.end())
        {
            DLOG_ERROR("Could not find connection for replica %s!",DEF_REPLICA_NAME);
            continue;
        }


        /*Get the operationId from ReplicationEvent to determine the type of operation to be performed*/
        std::string key=event->bucketName;
        key.append(event->key);
        int32_t ret=SUCCESS;
        switch(event->operationId)
        {
            case INSERT:
                {
		    if(it->second->IsConnectorInUse())
                    {
                        DLOG_DEBUG("connector %p is in use!",it->second);
                        break;
                    }
                    else
                    {
                        it->second->SetConnectorInUse(true);
                    }

                    if((ret=it->second->CreateEntry(key,event->data,event->length,m_lcbWait, event->expiryTime)) != SUCCESS)
                    {
                        DLOG_ERROR("Insertion Failed for key %s",event->key.c_str());
                        if((ret == LCB_NETWORK_ERROR) || (ret == LCB_ETIMEDOUT) ||
                                (ret == LCB_CONNECT_ERROR)|| (ret == REPL_CLIENT_ETMPFAIL))
                        {
                            CLOG_WARNING("Timeout/Network error/temp failure on client , setting cbTimeoutStatus");
                            (ReplicationClient::GetInstance()->cbTimeoutStatus)=LCB_ETIMEDOUT;
                        }

                        REPL_INC_INSERT_FAILURE(event->bucketName)
                    }
                    else
                    {

                        REPL_INC_INSERT_SUCCESS(event->bucketName)
                    }

                    it->second->SetConnectorInUse(false);
                    break;
                }
            case UPDATE:
                {
		    if(it->second->IsConnectorInUse())
                    {
                        DLOG_DEBUG("connector %p is in use!",it->second);
                        break;
                    }
                    else
                    {
                        it->second->SetConnectorInUse(true);
                    }

                    if((ret=it->second->UpdateEntry(key,event->data,event->length,m_lcbWait, event->expiryTime)) != SUCCESS)
                    {
                        DLOG_ERROR("Updation Failed for key %s",event->key.c_str());
                        if((ret == LCB_NETWORK_ERROR) || (ret == LCB_ETIMEDOUT) ||
                                (ret == LCB_CONNECT_ERROR)|| (ret == REPL_CLIENT_ETMPFAIL))
                        {
                            CLOG_WARNING("Timeout/Network error/temp failure on client , setting cbTimeoutStatus");
                            (ReplicationClient::GetInstance()->cbTimeoutStatus)=LCB_ETIMEDOUT;
                        }

                        REPL_INC_UPDATE_FAILURE(event->bucketName)
                    }
                    else
                    {
                        REPL_INC_UPDATE_SUCCESS(event->bucketName)
                    }

                    it->second->SetConnectorInUse(false);
                    break;
                }
            case REMOVE:
                {
                    if(it->second->IsConnectorInUse())
                    {
                        DLOG_DEBUG("connector %p is in use!",it->second);
                        break;
                    }
                    else
                    {
                        it->second->SetConnectorInUse(true);
                    }

                    if((ret=it->second->DeleteEntry(key,m_lcbWait)) != SUCCESS)
                    {
                        DLOG_ERROR("Deletion Failed for key %s",event->key.c_str());
                        if((ret == LCB_NETWORK_ERROR) || (ret == LCB_ETIMEDOUT) ||
                                (ret == LCB_CONNECT_ERROR)|| (ret == REPL_CLIENT_ETMPFAIL))
                        {
                            CLOG_WARNING("Timeout/Network error/temp failure on client , setting cbTimeoutStatus");
                            (ReplicationClient::GetInstance()->cbTimeoutStatus)=LCB_ETIMEDOUT;
                        }
                        REPL_INC_DELETE_FAILURE(event->bucketName)
                    }
                    else
                    {
                        REPL_INC_DELETE_SUCCESS(event->bucketName)
                    }
                    it->second->SetConnectorInUse(false);
                    break;
                }
            default:
                {
                    DLOG_ERROR("No such operation supported");
                    break;
                }


        }
        delete event;
        event=NULL;
    }
}


int32_t ReplicationThread::Terminate()
{
    /*Terminate all the ReplicationConnectors*/
    connectionMap::iterator it;
    for(it = connMap.begin(); it != connMap.end(); it++)
    {
        it->second->Disconnect();
    }

    connMap.clear();
    return SUCCESS;
}


uint32_t ReplicationThreadPool::GetReplicationThreadPoolSize()
{
    return poolSize;
}

uint32_t ReplicationThreadPool::GetReplicationThreadQSize(uint32_t threadIndex)
{
    if(threadIndex < poolSize)
    {
        return repThreads[threadIndex]->threadQ.Size();
    }
    return 0;
}

int32_t ReplicationThreadPool::Initialize(uint32_t threadPoolSize, std::vector<ReplicaBean> &replicas,
        CouchbaseConnectorBean &connectionInfo)
{

    int32_t ret=SUCCESS;
    int32_t initRet=SUCCESS;
    if(!instance)
    {
        instance=new ReplicationThreadPool();
    }
    else
    {
        DLOG_DEBUG("ReplicationThreadPool already initialized!");
        return ret;
    }
    poolSize=threadPoolSize;
    DLOG_INFO("Initializing ReplicationThreadPool with pool size %u",poolSize);
    /*Create ReplicationThreads */
    for(uint32_t i=0;i<poolSize; i++)
    {
        DLOG_DEBUG("Creating ReplicationThread:%d",i+1);
        ReplicationThread *repThread = new ReplicationThread();
        Thread *thread=new Thread("ReplicaThread");
        /*Initialize the thread passing replica info and connection information*/
        if((ret=repThread->Initialize(replicas,connectionInfo)) != SUCCESS)
        {
            if(ret == REPL_BUCKET_ENOENT)
            {
                CouchbaseConnectorBean retryBean=connectionInfo;
                retryBean.serverAddress="localhost";

                if((ret=repThread->Initialize(replicas,retryBean)) != SUCCESS)
                {

                    DLOG_ERROR("Second try!Replication thread initialization failed!");
                    initRet=ret;

                }
                else
                {
                    DLOG_DEBUG("Repl Thread initialized after retry!");
                }

            }
            else
            {

                DLOG_ERROR("ReplicationThread initialization failure");
                //return ret;
                initRet=ret;
            }
        }

        /*store the thread in the vector*/
        threads.push_back(thread);
        repThreads.push_back(repThread);


        /*Start the thread*/
        DLOG_DEBUG("Starting thread %d",i+1);
        thread->Start(repThread,&i);



    }
    //Initialize Hash
    hash.Initialize(1,0);

    return initRet;
}

int32_t ReplicationThreadPool::InitializeReplicationStats(uint32_t poolSize,std::vector<ReplicaBean> &replicas)
{
    for ( uint32_t i=0; i<replicas.size(); i++)
    {
        DLOG_DEBUG("Initializing Replication Stats for %s",replicas[i].replicaName.c_str());
        ReplStats *replStat= new ReplStats;
        m_ReplStatsMap[replicas[i].replicaName]=replStat;

    }
   //update the replStatsMap pointer in ReplicationThread
    ReplicationThread::m_replStatMapRef=&m_ReplStatsMap;
    return 0;
}

void ReplicationThreadPool::GetReplStatsInsertFailure(ReplicaBean &replica,std::vector<uint32_t> &threadWiseStats)
{

    threadWiseStats.clear();
    ReplStatsMap::iterator it=m_ReplStatsMap.find(replica.replicaName);
    if( it != m_ReplStatsMap.end())
    {
        for(uint32_t i=0 ; i < poolSize; i++)
        {
            threadWiseStats.push_back(it->second->insertFailure[i].GetCount());
        }
    }



}



void ReplicationThreadPool::GetReplStatsInsertSuccess(ReplicaBean &replica,std::vector<uint32_t> &threadWiseStats)
{
    CLOG_DEBUG(">>>> ReplicationThreadPool::GetReplStatsInsertSuccess >>>>");
    threadWiseStats.clear();
    ReplStatsMap::iterator it=m_ReplStatsMap.find(replica.replicaName);
    if( it != m_ReplStatsMap.end())
    {
        for(uint32_t i=0 ; i < poolSize; i++)
        {
            threadWiseStats.push_back(it->second->insertSuccess[i].GetCount());
        }
    }

}

void ReplicationThreadPool::GetReplStatsUpdateFailure(ReplicaBean &replica,std::vector<uint32_t> &threadWiseStats)
{

    threadWiseStats.clear();
    ReplStatsMap::iterator it=m_ReplStatsMap.find(replica.replicaName);
    if( it != m_ReplStatsMap.end())
    {
        for(uint32_t i=0 ; i < poolSize; i++)
        {
            threadWiseStats.push_back(it->second->updateFailure[i].GetCount());
        }
    }



}



void ReplicationThreadPool::GetReplStatsUpdateSuccess(ReplicaBean &replica,std::vector<uint32_t> &threadWiseStats)
{
    threadWiseStats.clear();
    ReplStatsMap::iterator it=m_ReplStatsMap.find(replica.replicaName);
    if( it != m_ReplStatsMap.end())
    {
        for(uint32_t i=0 ; i < poolSize; i++)
        {
            threadWiseStats.push_back(it->second->updateSuccess[i].GetCount());
        }
    }

}

void ReplicationThreadPool::GetReplStatsDeleteFailure(ReplicaBean &replica,std::vector<uint32_t> &threadWiseStats)
{

    threadWiseStats.clear();
    ReplStatsMap::iterator it=m_ReplStatsMap.find(replica.replicaName);
    if( it != m_ReplStatsMap.end())
    {
        for(uint32_t i=0 ; i < poolSize; i++)
        {
            threadWiseStats.push_back(it->second->deleteFailure[i].GetCount());
        }
    }



}



void ReplicationThreadPool::GetReplStatsDeleteSuccess(ReplicaBean &replica,std::vector<uint32_t> &threadWiseStats)
{
    threadWiseStats.clear();
    ReplStatsMap::iterator it=m_ReplStatsMap.find(replica.replicaName);
    if( it != m_ReplStatsMap.end())
    {
        for(uint32_t i=0 ; i < poolSize; i++)
        {
            threadWiseStats.push_back(it->second->deleteSuccess[i].GetCount());
        }
    }

}

#if 0
~ReplicationThreadPool::ReplicationThreadPool()
{
    for(int i=0;i<threads.size();i++)
    {
        delete threads[i];
        delete repThreads[i];
    }
}
#endif

unsigned int ReplicationThreadPool::HashUniversal(const char* key, unsigned int len) {
    unsigned int hash = 0, a = 31415, b = 27183;
    for(unsigned int i = 0; i < len; ++i) {
        hash = a * hash + key[i];
        a *= b;
    }
    return hash;
}


int32_t ReplicationThreadPool::PostToThreadQ(ReplicationEvent *event)
{

    /*Post the event to a Replication Thread based on round robin algorithm*/
    //ReplicationEvent *dyEvent=new ReplicationEvent(event);
    //rrCounterLock.lock();
    //CLOG_DEBUG("Before threadQ.Push Key in ReplicationThreadPool::POSTTOQ: %s",event.key.c_str());
    //unsigned int threadIndex = HashUniversal(event->key.c_str(),event->key.length());
    unsigned int threadIndex = hash.Hash32(event->key.c_str(),event->key.length(),1);
    repThreads[threadIndex%poolSize]->threadQ.Push(event);
    //CLOG_DEBUG("Posted to %p repThread",repThreads[rrCounter%poolSize]);
    //CLOG_DEBUG("After threadQ.Push Key in ReplicationThreadPool::POSTTOQ: %s",event.key.c_str());
    //rrCounter++;
    //rrCounterLock.unlock();

    return SUCCESS;
}


int32_t ReplicationThreadPool::Terminate()
{
    /*Terminate all ReplicationThreads by passing an event set with TERMINATE as operation*/
    ReplicationEvent *event=new ReplicationEvent();
    event->operationId=TERMINATE;
    for(uint32_t i=0; i< poolSize; i++)
    {
        DLOG_INFO("Terminate ReplicationThread %d",i+1);
        repThreads[i]->threadQ.Push(event);
    }
    return SUCCESS;
}


ReplicationThreadPool * ReplicationThreadPool::GetInstance()
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


void ReplicationThreadPool::ResetReplicationStats()
{
    ReplStatsMap::iterator it = m_ReplStatsMap.begin();
    for( ; it != m_ReplStatsMap.end(); it++)
    {
        CLOG_DEBUG("Resetting stats for %s",it->first.c_str());
        for( uint32_t i=0;i < poolSize; i++)
        {
            it->second->insertSuccess[i].Reset();
            it->second->insertFailure[i].Reset();
            it->second->updateSuccess[i].Reset();
            it->second->updateFailure[i].Reset();
            it->second->deleteSuccess[i].Reset();
            it->second->deleteFailure[i].Reset();
        }
    }
}

int32_t ReplicationThreadPool::Reconnect(bool all)
{
    int32_t ret=SUCCESS;
    int32_t initRet=SUCCESS;
    CLOG_DEBUG(">>>> ReplicationThreadPool::Reconnect >>>>");

    for(uint32_t i=0; i< repThreads.size(); i++)
    {
        if((ret=repThreads[i]->Reconnect(all)) != SUCCESS)
        {
            CLOG_ERROR("Reconnect Failed!");
            initRet=ret;
        }
        else
        {

            CLOG_DEBUG("Reconnect Success!");
        }
    }

    CLOG_DEBUG("<<<< ReplicationThreadPool::Reconnect <<<<");
    return initRet;
}

int32_t ReplicationThread::Reconnect(bool all)
{
    CLOG_DEBUG(">>>> ReplicationThread::Reconnect >>>>");
    int32_t ret=SUCCESS;
    int32_t initRet=SUCCESS;
    std::string serverAddr="";
    CouchbaseConnectorBean connectionInfo=ReplicationClient::GetConnDetails();
    std::vector<ReplicaBean> replicas=ReplicationClient::GetReplicaInfo();
    DLOG_INFO("Server Address=%s Port=%u Username=%s Password=%s",
            connectionInfo.serverAddress.c_str(),connectionInfo.serverPort,
            connectionInfo.userName.c_str(),
            connectionInfo.password.c_str());
    /*temp connection to get the server list from the cluster*/
    ReplicationConnector *dummy=new CouchbaseConnector(connectionInfo.serverAddress,
            connectionInfo.serverPort,
            connectionInfo.userName,
            connectionInfo.password,
            DEF_REPLICA_NAME,
            false);

    if(!all)
    {
        if((ret=dummy->GetServerList(serverAddr))!=SUCCESS)
        {
            DLOG_ERROR("Failed to connect to cluster and obtain server list");
            if( ret != REPL_BUCKET_ENOENT )
            {
                initRet=ret;
            }
            else
            {
                connectionInfo.serverAddress="localhost";
                dummy->SetServerAddress(connectionInfo.serverAddress);
                DLOG_DEBUG("Retry connection to cluster..");
                if((ret=dummy->GetServerList(serverAddr)) !=SUCCESS)
                {
                    delete dummy;
                    DLOG_ERROR("Failed to connect to Cluster and get serverList!");
                    return ret;
                }
            }

        }
        else
        {
            delete dummy;

            DLOG_DEBUG("ServerList=%s",serverAddr.c_str());
        }

        //check for  connections which are in DISCONNECT state and attempt connection
        connectionMap::iterator it;
        for( it=connMap.begin(); it != connMap.end();it++)
        {
            if(!it->second->IsConnected())
            {
                it->second->SetServerAddress(serverAddr);
                if((ret=it->second->Connect()) != SUCCESS)
                {
                    CLOG_ERROR("Connection Failure!");
                    initRet=ret;
                }
                else
                {
                    CLOG_DEBUG("Successfully connected to server: connObj=%p",it->second);
                    it->second->SetConnectionState(CONNECTED);
                }
            }
        }
    }
    else
    {
        CLOG_DEBUG("Disconnect and Reconnect all Connections");
        if((ret=dummy->GetServerList(serverAddr))!=SUCCESS)
        {
            DLOG_ERROR("Failed to connect to cluster and obtain server list");
            if( ret != REPL_BUCKET_ENOENT && ret != REPL_CONNECT_ERROR)
            {
                initRet=ret;
            }
            else
            {
                connectionInfo.serverAddress="localhost";
                dummy->SetServerAddress(connectionInfo.serverAddress);
                DLOG_DEBUG("Retry connection to cluster..");
                if((ret=dummy->GetServerList(serverAddr)) !=SUCCESS)
                {
                    delete dummy;
                    DLOG_ERROR("Failed to connect to Cluster and get serverList!");
                    return ret;
                }
            }

        }
        else
        {
            delete dummy;

            DLOG_DEBUG("ServerList=%s",serverAddr.c_str());
        }

        //check for  connections which are in DISCONNECT state and attempt connection
        connectionMap::iterator it;
        for( it=connMap.begin(); it != connMap.end();it++)
        {
	    while(it->second->IsConnectorInUse())
	    {
		usleep(50000);
		CLOG_INFO("connection %p is in use!",it->second);
	    }
	    it->second->SetConnectorInUse(true);
            it->second->Disconnect();
            it->second->SetServerAddress(serverAddr);
            if((ret=it->second->Connect()) != SUCCESS)
            {
                CLOG_ERROR("Connection Failure!");
                initRet=ret;
            }
            else
            {
                CLOG_DEBUG("Successfully connected to server: connObj=%p",it->second);
                it->second->SetConnectionState(CONNECTED);
            }
	    it->second->SetConnectorInUse(false);
        }

        //TODO:if all=true disconnect and reconnect all connections
    }
    CLOG_DEBUG("<<<< ReplicationThread::Reconnect <<<<");
    return initRet;
}
