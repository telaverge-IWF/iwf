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

#ifndef _REPLICATION_CONNECTOR_H
#define _REPLICATION_CONNECTOR_H

#include <stdio.h>
#include <libcouchbase/couchbase.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include<iostream>
#include "ThreadSpec.h"
#include "Atomic.h"
#include "Thread.h"
#include "Statistics.h"
#include "GenericStatsCounter.h"
#define MAX_BULK_FETCH_SIZE 25000

#define MAX_DATA_LEN 2600 

#if 0
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

#endif

enum ConnectionState
{
    DISCONNECTED=0,
    CONNECTED
};

//typedef std::map<std::string,ReplStats *> ReplStatsMap;

class ReplicationConnector
{

    public:
        virtual int32_t Connect()=0;
        virtual int32_t Disconnect()=0;
        virtual int32_t CreateEntry(std::string key, void *entry, uint32_t entryLen,bool lcbWait, uint32_t expiryTime = 0)=0;
        virtual int32_t UpdateEntry(std::string key, void *entry, uint32_t entryLen,bool lcbWait, uint32_t expiryTime = 0)=0;
        virtual int32_t DeleteEntry(std::string key,bool lcbWait)=0;
        virtual int32_t GetEntry( std::string key, void *outEntry,uint32_t *outEntryLen )=0;
        virtual int32_t GetEntry( std::string key, std::string &outEntry,uint32_t *outEntryLen )=0;
        virtual int32_t GetBulkEntries(std::vector<std::string> &keys, std::vector<std::string> &outData,bool appendReplicaName=false)=0;
        virtual int32_t GetServerList(std::string &serverList){return 0;}
        virtual  void SetConnectionState(ConnectionState connectState)=0;
        virtual void SetServerAddress(std::string &serverAddr)=0;
        virtual bool IsConnected()=0;
	virtual bool IsConnectorInUse()=0;
	virtual void SetConnectorInUse(bool inUse)=0;

        virtual int32_t SetOperationTimeout(int32_t uSecTimeout)=0;

};


class CouchbaseBuffer
{
    public:

        char dataBuffer[MAX_DATA_LEN];


};

class CouchbaseConnector:public ReplicationConnector
{
    private:
        std::string serverAddress;
        int32_t serverPort;
        std::string userName;
        std::string password;
        std::string bucketName;
        lcb_t instance;
        bool syncMode; //determines the syncMode of couchbase operations
        ConnectionState connState;
    public:
        //	static void *data;  //to get the data on read operation
        static eAccelero::ThreadSpec<uint32_t> dataLen;

        static eAccelero::ThreadSpec<int32_t> m_ResultCode; //result code set during errors
        static eAccelero::ThreadSpec<int32_t> m_BulkFetchStatus; //result code set during errors
        static eAccelero::ThreadSpec<int32_t> m_atleastOneErrorOccurred; //result code set during errors
        static eAccelero::ThreadSpec<CouchbaseBuffer> cbBuffer;
        //static eAccelero::ThreadSpec<std::vector<std::string>> bulkData;
        static std::vector<std::string> bulkData;
        //static ReplStatsMap *m_replStatMapRef;

        eAccelero::Atomic<bool> m_ConnectorInUse;
        //static ReplStatsMap *m_replStatMapRef;
        CouchbaseConnector(std::string serverAddr,int32_t port,std::string name, std::string pass
                ,std::string bucket,bool syncMode ):serverAddress(serverAddr),
        serverPort(port),userName(name),
        password(pass),bucketName(bucket),syncMode(syncMode),connState(DISCONNECTED)
        {
            CLOG_DEBUG("Conn=%p,server=%s, ConnectionState=%d",this,serverAddr.c_str(),connState);

           // *data=(char*)malloc(MAX_DATA_LEN);
           //cbBuffer->data=(char*)malloc(MAX_DATA_LEN);
	   m_ConnectorInUse=false;

        }

        ~CouchbaseConnector()
        {
            CLOG_DEBUG("Destroy Conn=%p",this);
        }

        int32_t Connect() ;
        int32_t Disconnect() ;
        int32_t CreateEntry(std::string key, void *entry, uint32_t entryLen,
                            bool lcbWait, uint32_t expiryTime = 0);
        int32_t UpdateEntry(std::string key, void *entry, uint32_t entryLen,
                            bool lcbWait, uint32_t expiryTime = 0);
        int32_t DeleteEntry(std::string key,bool lcbWait);
        int32_t GetEntry( std::string key, void *outEntry,uint32_t *outEntryLen );
        int32_t GetEntry( std::string key, std::string &outEntry, uint32_t *outEntryLen );
        int32_t GetServerList(std::string &serverList);

        int32_t GetBulkEntries(std::vector<std::string> &keys, std::vector<std::string> &outData,bool appendReplicaName=false);
        int32_t SetOperationTimeout(int32_t uSecTimeout);
	bool IsConnectorInUse()
	{
	    return m_ConnectorInUse;	
	}
		
	void SetConnectorInUse(bool inUse)
	{
	    m_ConnectorInUse=inUse;
	}
        static void SetTsErrorCode(int32_t resCode)
        {
            *m_ResultCode=resCode;
        }

        static void SetBulkFetchStatus(int32_t status)
        {
            *m_BulkFetchStatus=status;
        }
        void SetConnectionState(ConnectionState connectState)
        {
            CLOG_DEBUG("This=%p, ConnectionState=%d",this,connectState);
            connState=connectState;
        }
        void SetServerAddress(std::string &serverAddr)
        {
            serverAddress=serverAddr;
        }
        bool IsConnected()
        {
            if(connState == CONNECTED)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        static void SetTsDataLen(uint32_t len)
        {
            *dataLen=len;
        }

};






#endif

