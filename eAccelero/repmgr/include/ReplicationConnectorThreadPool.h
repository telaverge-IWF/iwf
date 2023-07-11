/*********************************-*-H-*-************************************
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

#ifndef _CONNECTOR_THREAD_POOL_H
#define _CONNECTOR_THREAD_POOL_H
#include <map>

#include "ThreadQueue.h"
#include "Thread.h"
#include "ReplicationConnector.h"

#include "Hash.h"
#include "ReplicationClient.h"

#define COUCHBASE_ENTRY_TTL 1800

//Replication Statistics macro
#define REPL_INC_INSERT_FAILURE(replica) \
    { \
        ReplStatsMap::iterator it=m_replStatMapRef->find(replica); \
        if((it != m_replStatMapRef->end())) \
        { \
            it->second->insertFailure[StatsIndex].Increment(); \
        } \
    }

#define REPL_INC_INSERT_SUCCESS(replica) \
    { \
        ReplStatsMap::iterator it=m_replStatMapRef->find(replica); \
        if((it != m_replStatMapRef->end())) \
        { \
            it->second->insertSuccess[StatsIndex].Increment(); \
        } \
    }


#define REPL_INC_UPDATE_SUCCESS(replica) \
    { \
        ReplStatsMap::iterator it=m_replStatMapRef->find(replica); \
        if((it != m_replStatMapRef->end())) \
        { \
            it->second->updateSuccess[StatsIndex].Increment(); \
        } \
    }

#define REPL_INC_UPDATE_FAILURE(replica) \
    { \
        ReplStatsMap::iterator it=m_replStatMapRef->find(replica); \
        if((it != m_replStatMapRef->end())) \
        { \
            it->second->updateFailure[StatsIndex].Increment(); \
        } \
    }

#define REPL_INC_DELETE_SUCCESS(replica) \
    { \
        ReplStatsMap::iterator it=m_replStatMapRef->find(replica); \
        if((it != m_replStatMapRef->end())) \
        { \
            it->second->deleteSuccess[StatsIndex].Increment(); \
        } \
    }

#define REPL_INC_DELETE_FAILURE(replica) \
    { \
        ReplStatsMap::iterator it=m_replStatMapRef->find(replica); \
        if((it != m_replStatMapRef->end())) \
        { \
            it->second->deleteFailure[StatsIndex].Increment(); \
        } \
    }


typedef struct ReplStat
{
    eAccelero::GenericStatsCounter insertSuccess[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter insertFailure[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter updateSuccess[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter updateFailure[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter deleteSuccess[EACC_MAX_THREADS];
    eAccelero::GenericStatsCounter deleteFailure[EACC_MAX_THREADS];

}ReplStats;


typedef std::map<std::string,ReplStats *> ReplStatsMap;

class ReplicaBean;
class CouchbaseConnectorBean;
class ReplicationSyncConnectorPool;
//class ReplicationConnector;

enum OperationId
{
    INSERT=1,
    UPDATE,
    READ,
    REMOVE,
    /*This is to terminate the threads*/
    TERMINATE

};

using namespace eAccelero;
class ReplicationEvent
{
    public:
        OperationId operationId;
        std::string bucketName;

        std::string key;
        //Serialize serializeObj;
        uint32_t length;
        char data[MAX_DATA_LEN];

        uint32_t expiryTime; // Time to live for an entry in the Couchbase

        ReplicationEvent(OperationId operId,std::string bucket,std::string keyArg,uint32_t len
                ,void *dat):operationId(operId),bucketName(bucket),key(keyArg),length(len),
                 expiryTime(COUCHBASE_ENTRY_TTL)
        {
            memset(data,0,MAX_DATA_LEN);
            if( dat != NULL)
            {
                if(len <= MAX_DATA_LEN)
                {
                    memcpy(data,dat,len);
                }
                else
                {
                    CLOG_WARNING("Length passed=%d which is greater than MAX_DATA_LEN,so truncating to MAX_DATA_LEN",len);
                    memcpy(data,dat,MAX_DATA_LEN);
                }
            }
        }

        ReplicationEvent():operationId((OperationId)0),length(0), expiryTime(COUCHBASE_ENTRY_TTL)
        {
            data[0]='\0';
        }


        ~ReplicationEvent()
        {

        }

};


typedef std::map<std::string,ReplicationConnector*> connectionMap;

class ReplicationClientConnectRetryThread: public Runnable
{

    private:
        uint32_t retryMax;
    public:
        void Run(void *arg);
        int32_t Terminate();

	void SetRetryMax(uint32_t retryMaxCount)
	{
	    retryMax=retryMaxCount;
	}
	ReplicationClientConnectRetryThread():retryMax(10)
	{
	}



};

class OperationTimeoutHandleThread: public Runnable
{

    private:
        bool disableOperations;
        bool running;
        std::string key;
    public:

        void Run(void *arg);
        OperationTimeoutHandleThread():disableOperations(false)
        {
        }

        void SetKey(std::string keyStr)
        {
            CLOG_DEBUG("Setting key=%s",key.c_str());
            key=keyStr;
        }

        void DisableOperations()
        {
            //CLOG_DEBUG("Disabling couchbase operations!");
            disableOperations=true;
        }

        void EnableOperations()
        {
            CLOG_DEBUG("Enabling couchbase operations!");
            disableOperations=false;
        }

        bool IsOperationsDisabled()
        {
            return disableOperations;
        }

        void SetRunning(bool state)
        {
            CLOG_DEBUG("Setting running=%d",state);
            running=state;
        }

        bool IsActive()
        {
            return running;
        }

};


class ReplicationThread: public Runnable
{

    private:
        connectionMap connMap;
    public:
        ThreadQueue<ReplicationEvent*> threadQ;
        int32_t Initialize(std::vector<ReplicaBean> &replicas,CouchbaseConnectorBean &connectionInfo);
        void Run(void *arg);
        int32_t Terminate();
        int32_t Reconnect(bool allConnections);
        bool CheckForBulkOperations();
        static ReplStatsMap *m_replStatMapRef;
        int32_t m_lcbWaitCounter;
        uint32_t m_opCounter;
        bool m_lcbWait;
        uint32_t m_curQSize;
        uint32_t m_maxBulkOpSize;

};

class ReplicationThreadPool
{
    private:
        static std::vector<ReplicationThread *> repThreads;
        static std::vector<eAccelero::Thread *>threads;
        static uint32_t poolSize;
        uint32_t threadTimeOut;
        /*rrCounter used to distribute messages in round robin manner to the threads*/
        uint32_t rrCounter;
        eAccelero::Mutex rrCounterLock;
        static eAccelero::Mutex instanceLock;
        static ReplicationThreadPool *instance;
        ReplStatsMap m_ReplStatsMap;

        unsigned int HashUniversal(const char* key, unsigned int len);
        ReplicationThreadPool():threadTimeOut(0),rrCounter(0)
    {
    }


    public:
        /*Initializes the ReplicationThread pool */
        int32_t Initialize(uint32_t poolSize,std::vector<ReplicaBean> &replicas,CouchbaseConnectorBean &connectionInfo);
        /*Terminates the ReplicationThread pool*/
        int32_t Terminate();
        /*Posts an event to a Replication Thread based on round robin algorithm*/
        int32_t PostToThreadQ(ReplicationEvent *event);


        /*GetInstance should be called only after Initialize is called*/
        static ReplicationThreadPool *GetInstance();

        uint32_t GetReplicationThreadPoolSize();

        uint32_t GetReplicationThreadQSize(uint32_t threadIndex);

        int32_t InitializeReplicationStats(uint32_t poolSize, std::vector<ReplicaBean> &replicas);

        void ResetReplicationStats();
        void GetReplStatsInsertSuccess(ReplicaBean &replica,std::vector<uint32_t> &threadWiseStats);
        void GetReplStatsInsertFailure(ReplicaBean &replica,std::vector<uint32_t> &threadWiseStats);
        void GetReplStatsUpdateSuccess(ReplicaBean &replica,std::vector<uint32_t> &threadWiseStats);
        void GetReplStatsUpdateFailure(ReplicaBean &replica,std::vector<uint32_t> &threadWiseStats);
        void GetReplStatsDeleteSuccess(ReplicaBean &replica,std::vector<uint32_t> &threadWiseStats);
        void GetReplStatsDeleteFailure(ReplicaBean &replica,std::vector<uint32_t> &threadWiseStats);

        int32_t Reconnect(bool all);
        static Hash hash;

};



#endif




