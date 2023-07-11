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

#include "ReplicationSyncConnectorPool.h"
#define OP_TIMEOUT_CONNECTOR_TIMEOUT 50000


/*Sync connector thread pool functions*/

int32_t ReplicationSyncConnectorPool::Initialize(uint32_t poolSize,std::vector<ReplicaBean> &replicas,
        CouchbaseConnectorBean &connectionInfo)
{
    DLOG_DEBUG(">>>> ReplicationSyncConnectorPool::Initialize >>>>");
    int32_t ret=SUCCESS;
    int32_t initRet=SUCCESS;

    /*Create the ReplicationConnectors to all the replicas/buckets */
    DLOG_INFO("Initializing ReplicationSyncConnectorPool with %u connections",poolSize);
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
    /*Get the list of server nodes in the cluster so that we can pass the list to the
     * actual connect*/
    if((ret=dummy->GetServerList(serverList))!=SUCCESS)
    {
        DLOG_ERROR("Failed to connecto to cluster and obtain server list");
	delete dummy;
        initRet=ret;
    }
    else
    {
        DLOG_DEBUG("ServerList=%s",serverList.c_str());
        delete dummy;
    }


    DLOG_DEBUG("Initializing connection instance for %s",DEF_REPLICA_NAME);
    //std::vector<SyncConnectorInfo> connections;
    for( uint32_t j=0; j <=  poolSize; j++)
    {
        SyncConnectorInfo connectorInfo;
        ReplicationConnector *connector=new CouchbaseConnector(serverList,
                connectionInfo.serverPort,
                connectionInfo.userName,
                connectionInfo.password,
                DEF_REPLICA_NAME,
                true);
        /*Connect to the target replica*/
        if(initRet == SUCCESS)
        {
            if((ret=connector->Connect()) != SUCCESS)
            {
                DLOG_ERROR("Connection Failure!");
                DLOG_ERROR("Server Address=%s Port=%u Username=%s Password=%s Replica Name=%s",
                        serverList.c_str(),connectionInfo.serverPort,
                        connectionInfo.userName.c_str(),
                        connectionInfo.password.c_str(), DEF_REPLICA_NAME);
                //return ret;
                initRet=ret;
                connector->SetConnectionState(DISCONNECTED);
            }
            else
            {
                connector->SetConnectionState(CONNECTED);
                DLOG_INFO("Successfully connected to server:<%s> and replica:<%s>",serverList.c_str(),DEF_REPLICA_NAME);

            }
        }
        if(j==poolSize)
        {
            DLOG_DEBUG("Created opTimeoutConnector");
            opTimeoutConnector=connector;
            opTimeoutConnector->SetOperationTimeout(OP_TIMEOUT_CONNECTOR_TIMEOUT);
        }
        else
        {
            connectorInfo.syncConnection=connector;
            /*Insert the ReplicationConnector to the connections vector*/
            connections.push_back(connectorInfo);
        }

    }

    /*Insert the connections vector to the map, using replicaName as the key*/
        syncConnMap.insert(std::make_pair(DEF_REPLICA_NAME,connections));

    DLOG_DEBUG("<<<< ReplicationSyncConnectorPool::Initialize <<<<");
    return initRet;
}

/*Gets a free ReplicationConnector from the sync pool*/
ReplicationConnector *ReplicationSyncConnectorPool::GetConnector(std::string replicaName)
{
    /*Get the vector from the SyncConnMap*/
    SyncConnMap::iterator it=syncConnMap.find(replicaName);
    if(it == syncConnMap.end())
    {
        CLOG_ERROR("Connections not found for %s",replicaName.c_str());
        return NULL;
    }

    /*Iterate through all the entries in the vector*/
    syncConnectorsLock.lock();
    for(uint32_t i=0;i< it->second.size();i++)
    {
        /*If the sync connector is available mark it unavailable
          and return the sync connection instance*/
        if(it->second[i].available)
        {
            it->second[i].available=false;
            syncConnectorsLock.unlock();
            return it->second[i].syncConnection;
        }
    }

    syncConnectorsLock.unlock();
    /*return false*/
    return NULL;


}

int32_t ReplicationSyncConnectorPool::ReleaseConnection(std::string replicaName,
        ReplicationConnector *connection)
{
    /*Get the vector from the SyncConnMap*/
    SyncConnMap::iterator it=syncConnMap.find(replicaName);
    if(it == syncConnMap.end())
    {
        CLOG_ERROR("Connections not found for %s",replicaName.c_str());
        return !SUCCESS;
    }

    /*Iterate through all the entries in the vector*/
    syncConnectorsLock.lock();
    for(uint32_t i=0;i< it->second.size();i++)
    {
        /*If the connection is found in the vector set its status to available*/
        if(it->second[i].syncConnection == connection)
        {
            it->second[i].available=true;
            syncConnectorsLock.unlock();
            return SUCCESS;
        }
    }

    syncConnectorsLock.unlock();
    /*If its not found return error*/
    return !SUCCESS;

}

int32_t ReplicationSyncConnectorPool::Reconnect(bool all,bool connectToLocal)
{
    CLOG_DEBUG(">>>> ReplicationSyncConnectorPool::Reconnect >>>>");
    int32_t ret=SUCCESS;
    int32_t initRet=SUCCESS;
    std::string serverAddr="";
    CouchbaseConnectorBean connectionInfo=ReplicationClient::GetConnDetails();
    if(connectToLocal)
    {
        DLOG_DEBUG("Connecting to localhost");
        connectionInfo.serverAddress="localhost";
    }
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

            delete dummy;
            DLOG_ERROR("Failed to connect to Cluster and get serverList!");
            return ret;
        }
        else
        {
            delete dummy;

            DLOG_DEBUG("ServerList=%s",serverAddr.c_str());
        }

        //check for conenctions in DISCONNECT state and attempt connection
        SyncConnMap::iterator it=syncConnMap.begin();
        for( ; it!=syncConnMap.end(); it++)
        {
            std::vector<SyncConnectorInfo> connections;
            for(uint32_t i=0;i < it->second.size(); i++)
            {
                if(!(it->second[i].syncConnection->IsConnected()))
                {
                    it->second[i].syncConnection->SetServerAddress(serverAddr);
                    if((ret=it->second[i].syncConnection->Connect()) != SUCCESS)
                    {
                        CLOG_ERROR("Connect Failed!");
                        initRet=ret;
                    }
                    else
                    {

                        it->second[i].syncConnection->SetConnectionState(CONNECTED);
                    }

                }
            }
        }
        //reconnect the opTimeoutConnector
        opTimeoutConnector->SetServerAddress(serverAddr);
        if((ret=opTimeoutConnector->Connect())!= SUCCESS)
        {
            CLOG_ERROR("OpTimeoutConnector connect failed!");
            initRet=ret;
        }
        else
        {
            opTimeoutConnector->SetConnectionState(CONNECTED);
            opTimeoutConnector->SetOperationTimeout(50000);
        }
    }
    else
    {
        //TODO Disconnect and reconnect all connections
        DLOG_DEBUG("Disconnect and reconnect all connections");
        if((ret=dummy->GetServerList(serverAddr))!=SUCCESS)
        {

            delete dummy;
            DLOG_ERROR("Failed to connect to Cluster and get serverList!");
            return ret;
        }
        else
        {
            delete dummy;

            DLOG_DEBUG("ServerList=%s",serverAddr.c_str());
        }

        SyncConnMap::iterator it=syncConnMap.begin();
        for( ; it!=syncConnMap.end(); it++)
        {
            std::vector<SyncConnectorInfo> connections;
            for(uint32_t i=0;i < it->second.size(); i++)
            {
                it->second[i].syncConnection->Disconnect();
                it->second[i].syncConnection->SetServerAddress(serverAddr);
                if((ret=it->second[i].syncConnection->Connect()) != SUCCESS)
                {
                    CLOG_ERROR("Connect Failed!");
                    initRet=ret;
                }
                else
                {

                    it->second[i].syncConnection->SetConnectionState(CONNECTED);
                }

            }
        }
        //reconnect the opTimeoutConnector
        opTimeoutConnector->Disconnect();
        opTimeoutConnector->SetServerAddress(serverAddr);
        if((ret=opTimeoutConnector->Connect())!= SUCCESS)
        {
            CLOG_ERROR("OpTimeoutConnector connect failed!");
            initRet=ret;
        }
        else
        {
            opTimeoutConnector->SetConnectionState(CONNECTED);
            opTimeoutConnector->SetOperationTimeout(50000);
        }


    }
    CLOG_DEBUG("<<<< ReplicationSyncConnectorPool::Reconnect <<<<");
    return initRet;
}

int32_t ReplicationSyncConnectorPool::Terminate()
{
    int32_t ret=SUCCESS;

    SyncConnMap::iterator it ;
    syncConnectorsLock.lock();
    /*Terminate all the connections*/
    for(it=syncConnMap.begin(); it != syncConnMap.end();it++)
    {
        for( uint32_t i=0; i < it->second.size(); i++)
        {
            if(it->second[i].syncConnection->IsConnected())
            {
                it->second[i].syncConnection->Disconnect();
            }
        }
    }
    syncConnectorsLock.unlock();
    return ret;


}


