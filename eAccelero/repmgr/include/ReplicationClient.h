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

#ifndef _REPLICATION_CLIENT_H
#define _REPLICATION_CLIENT_H
#include <iostream>
#include <vector>
#include <map>
#include<sstream>
#include "ReplicationSyncConnectorPool.h"
#include "ReplicationConnectorThreadPool.h"
#define DEF_REPLICA_SIZE 1000
#define DEF_REPLICA_NAME "DiameterSession"
#include "ReplicationErrors.h"
#include "Logger.h"

class ReplicationSyncConnectorPool;
class ReplicationThreadPool;
class ReplicationClientConnectRetryThread;
class OperationTimeoutHandleThread;
//function pointer to enable replication ( called by replication client library)
typedef int (*ReplicationStatusCbk)(bool status);

//using namespace eAccelero;
class CouchbaseConnectorBean
{
    public:
        std::string serverAddress;//couchbase-server node address
        int32_t    serverPort;   //port
        std::string userName;   //username associated with the bucket
        std::string password;   // password associated with the bucket
        uint32_t retryConnMax;
        uint32_t bulkOperationMax;
        CouchbaseConnectorBean(): serverPort(0),bulkOperationMax(100)
    {
    }

        CouchbaseConnectorBean(std::string serverAddr , int32_t serverPortNo,std::string user
                , std::string pass): serverAddress(serverAddr), serverPort(serverPortNo),
        userName(user), password(pass)
    {
    }


};


class ReplicaBean
{

    public:
        std::string replicaName;
        uint32_t replicaSize; //size to be alocated to this replica/bucket
        int32_t replicaTTL;


        ReplicaBean(): replicaSize(DEF_REPLICA_SIZE),replicaTTL(0)
    {
    }

        ReplicaBean(std::string name,uint32_t size,uint32_t TTL)
            : replicaName(name),replicaSize(size),replicaTTL(TTL)
        {
        }

        ~ReplicaBean()
        {
        }


};


/*Singleton class*/
class ReplicationClient
{
    private:
        static ReplicationClient * instance;
        static std::vector<ReplicaBean> replicas;
        //ReplicationThreadPool *tPool;
        static CouchbaseConnectorBean	connDetails;

        static ReplicationSyncConnectorPool *syncConnPool;
        eAccelero::Logger &m_logger;
        eAccelero::Mutex testLock;
        static eAccelero::Mutex instanceLock;
        static ReplicationStatusCbk replStatusCbk;
        static ReplicationClientConnectRetryThread retryConnectionThread;
        static OperationTimeoutHandleThread OpTimeoutHandleThread;


        ReplicationClient(eAccelero::Logger &logger):m_logger(logger)
    {
    }

    public:

        static eAccelero::Atomic<int32_t> cbTimeoutStatus;
        static CouchbaseConnectorBean GetConnDetails()
        {
             return connDetails;
        }

        static std::vector<ReplicaBean> GetReplicaInfo()
        {
            return replicas;
        }
        static ReplicationStatusCbk GetReplStatusCbk()
        {
            return replStatusCbk;
        }

        static ReplicationSyncConnectorPool * GetSyncConnPool()
        {
            return syncConnPool;
        }

        static ReplicationConnector *GetOpTimeoutConnector();

        static ReplicationClient * GetInstance();



        static void Destroy()
        {
            if(instance != NULL)
            {
                delete instance;
                instance=NULL;
            }
        }

        /*syncPoolSize is the number of syncronous connection instances
         * to be created, to be used by the application for read operation
         * asyncPoolSize is the number of ReplicationThreads to be created.
         * connDetails will have the couchbase server connection details
         * replicas is the vector having all the replica information
         * logger is the initialized logger       */
        static int32_t Initialize(uint32_t syncPoolSize,uint32_t asyncPoolSize,
                CouchbaseConnectorBean &connDetails,
                std::vector<ReplicaBean> &replicas,
                eAccelero::Logger &logger);

        /*Terminates the ReplicationClient*/
        static int32_t  Terminate();

        /*non-POD types have to be serialized before invoking below 2 api */
        /*Replicate a new entry*/
        int32_t ReplicateNewEntry(std::string replicaName,std::string key,void *data,uint32_t dataLen, uint32_t expiryTime = 0);

        /*Replicate an updation of existing entry*/
        int32_t ReplicateUpdatedEntry(std::string replicaName,std::string key, void *data,
                uint32_t dataLen, uint32_t expiryTime = 0);

        /*Replication Deletion of an entry*/
        int32_t ReplicateDeletedEntry(std::string replicaName,std::string key);

        /*Get an entry from the Replica*/
        int32_t GetReplicatedEntry(std::string replicaName,std::string key, void *data, uint32_t *dataLen);


        /*Get entry overloaded for Non-POD types*/
        int32_t GetReplicatedEntry(std::string replicaName,std::string key, std::string &data, uint32_t *dataLen);

        /*Bulk Fetch Entries*/
        int32_t GetBulkReplicatedEntries(std::string replicaName,int32_t start, int32_t end, std::vector<std::string> &outData);

        eAccelero::Logger & GetLogger();

        uint32_t GetReplicationPoolSize();

        uint32_t GetReplicationThreadQSize(uint32_t threadIndex);

        void GenerateReplicationStats(std::string &replStats);

        void FormStatsString( std::string bucketName,uint32_t index,
                uint32_t insertSuccess, uint32_t insertFailure,
                uint32_t updateSuccess, uint32_t updateFailure,
                uint32_t deleteSuccess,uint32_t deleteFailure,
                char *formatStringLine);
        void ResetReplicationStats();

        static int32_t RegisterReplicationStatusCbk(ReplicationStatusCbk replicationStatusCbk);

        static int32_t StartRetryConnectionThread();

        static int32_t StartOpTimeoutHandleThread();

};

#endif
