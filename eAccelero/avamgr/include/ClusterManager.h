/********************************-*-H-*-*************************************
 *                                                                          *
 *     Copyright 2012 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *    This product and related documentation is protected by copyright and  *
 *    distributed under licenses restricting its use, copying, distribution *
 *    and decompilation.  No part of this product or related documentation  *
 *    may be reproduced in any form by any means without prior written      *
 *    authorization of IntelliNet Technologies and its licensors, if any.   *
 *                                                                          *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     *
 *    government is subject to restrictions as set forth in subparagraph    *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software      *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                       *
 *                                                                          *
 ****************************************************************************/
#ifndef _CLUSTERMANAGER_H_
#define _CLUSTERMANAGER_H_

#include "Node.h"
#include "Thread.h"
#include "ThreadQueue.h"
#include "CouchbaseMgmtClient.h"
namespace eAccelero {

#define TQ_WAIT_TIMEOUT 1000000

    enum ClusterMgmtEventType{
        CM_OP_MONITOR_CLUSTER=1,
        CM_OP_ADD_NODE,
        CM_OP_REM_NODE,
        CM_OP_PURGE_METADATA
    };

    typedef struct _ReplicationConfig_ {
        uint32_t clusterConnRetryFailure;
        uint32_t purgeDataInterval;
    }ReplicationConfig;

    class ClusterManagementEvent {
        public:
            ClusterMgmtEventType operation;
            bool isActive;
            bool isPeerAvailable;
            Node node;
            struct timeval tv;

    };

    class ClusterManagementStatus
    {
        public:
            ClusterMgmtEventType operation;
            CouchbaseApiError status;
            Node node;
            CouchbaseStatus localCbHealth;
            CouchbaseStatus peerCbHealth;
            double node1RebalanceProgress;
            double node2RebalanceProgress;
            bool isRebalanceStuck;
            uint32_t nodesInCluster;
            ClusterManagementStatus():operation(CM_OP_MONITOR_CLUSTER),status(CB_OK),
            localCbHealth(WARMUP),peerCbHealth(WARMUP),node1RebalanceProgress(0.0),
            node2RebalanceProgress(0.0),isRebalanceStuck(false),
            nodesInCluster(0)
        {
        }
    };

    class ClusterManager:public eAccelero::Runnable {
        public:
            ClusterManager():m_node1PrevRebalanceProgress(0.0),m_node2PrevRebalanceProgress(0.0),
            m_rebalanceStuckCounter(0)
        {
        }
            ~ClusterManager();
            uint32_t Initialize(Node node);
            void Terminate();
            uint16_t GetClusterStatus();
            uint32_t AddNodeToCluster(Node& node);
            virtual void Run(void *arg=NULL) = 0;
            uint32_t PutEvent(ClusterManagementEvent event);
            double m_node1PrevRebalanceProgress;
            double m_node2PrevRebalanceProgress;
            uint32_t m_rebalanceStuckCounter;
            std::map<std::string, std::string> m_objConfigReaderMap;
        private:
        protected:
            bool done;
            ThreadQueue<ClusterManagementEvent> tQueue;
    };



} //namespace eAccelero

#endif //ifndef _CLUSTERMANAGER_H_
