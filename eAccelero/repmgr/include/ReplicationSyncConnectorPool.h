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

#ifndef _REP_SYNC_THREAD_POOL_H_
#define _REP_SYNC_THREAD_POOL_H_

#include "Thread.h"
#include "ThreadQueue.h"

#include "ReplicationClient.h"
#include "ReplicationConnector.h"

class ReplicaBean;
class CouchbaseConnectorBean;

class SyncConnectorInfo
{
    public:
        ReplicationConnector *syncConnection;
        bool available;
        SyncConnectorInfo():syncConnection(NULL),available(true)
    {
    }

};

/*Syncrounous Connections for Read operations*/

typedef std::map<std::string,std::vector< SyncConnectorInfo> >SyncConnMap;
class ReplicationSyncConnectorPool
{

    private:
        std::vector<SyncConnectorInfo> connections;
        std::vector<ReplicationConnector *> connPool;
        /*For each bucket/replicaName there will be poolSize connections maintained */
        SyncConnMap syncConnMap;
        uint32_t poolSize;
        eAccelero::Mutex syncConnectorsLock;

        //connector for opTimeout thread
        ReplicationConnector *opTimeoutConnector;

    public:
        /*Initializes the syncConnector Pool with poolSize number of connection instances*/
        int32_t Initialize(uint32_t poolSize,std::vector<ReplicaBean> &replicas,
                CouchbaseConnectorBean &connectionInfo);

        ReplicationSyncConnectorPool()
        {
        }
        /*Gets a sync Connector which is available from the sync connector pool*/
        ReplicationConnector * GetConnector(std::string replicaName);

        /*Releases the sync connector back to the sync connector pool*/
        int32_t ReleaseConnection(std::string replicaName,ReplicationConnector *connection);

        /*Get the connections thats used to test operation timeout */
        ReplicationConnector * GetOpTimeoutConnector()
        {
            return opTimeoutConnector;
        }

        /*Terminates the ReplicationSyncConnectorPool*/
        int32_t Terminate();

        /*Reconnect*/
        int32_t Reconnect(bool all,bool connectToLocal=false);

};








#endif


