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
#ifndef __COUCHBASE_CLUSTERMANAGER_H_
#define __COUCHBASE_CLUSTERMANAGER_H_

#include "CouchbaseMgmtClient.h"
#include "Node.h"

namespace eAccelero {
#define CANT_REACH_CLUSTER 1

    class CouchbaseClusterManager:public ClusterManager {
        public:
	    CouchbaseConfig cb_Config;
	    CouchbaseConfig cbPeerConfig;
	    CouchbaseClusterMgmtClient* cb_Client;
        CouchbaseClusterMgmtClient* cbPeerClient;
        CouchbaseClusterManager(ReplicationConfig repConfig);
        ~CouchbaseClusterManager();
        uint32_t Initialize(Node node);
        void Terminate();
        uint16_t GetClusterStatus(std::vector<CouchbaseNode> &nodes);
        uint32_t MonitorCluster();
        uint32_t RebalanceCluster(bool isLocalCbNode);
        uint32_t RebalanceCluster(std::vector<CouchbaseNode> &nodes,CouchbaseClusterMgmtClient* mgmtClient);
        uint32_t AddNodeToCluster(Node& node,bool isLocalCbNode);
        uint32_t HandleFlipInStatus(std::vector<CouchbaseNode>&prevStatus,
                std::vector<CouchbaseNode>&curStatus);
        bool IsLocalCbNodeReachable();
        bool IsMateCbNodeReachable();
        bool IsClusterReachable();
	static uint32_t GetCbStatus(ClusterManagementStatus &cmStatus);
        uint32_t PurgeUnwantedData(std::string replica);
        void Run(void *arg=NULL);

        uint32_t m_failCount;
        uint32_t m_cfgFailCount;
        bool isActive;
        bool isClusterInitialized;
        bool m_localCbMaxRetry;
        bool m_mateCbMaxRetry;
        std::vector<CouchbaseNode> m_RebalanceNodes;
        bool m_RebalanceNodesUpdated;
        bool m_IsClusterHealthy;
        bool m_LocalCbNodeMarkedDown;
        bool m_MateCbNodeMarkedDown; 

	static ClusterManagementStatus m_curClusterStatus;
        bool flipFlag[2];
        std::vector<CouchbaseNode> m_PrevStatus;
        ReplicationConfig m_repConfig;
    };

} //namespace eAccelero


#endif //ifndef __COUCHBASE_CLUSTERMANAGER_H_
