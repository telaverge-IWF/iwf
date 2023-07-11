/********************************-*-C++-*-*************************************
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
#include "CouchbaseNode.h"
#include "ClusterManager.h"
#include "CouchbaseClusterManager.h"
#include "HAComponent.h"
#include "AvaMgr.h"
#include "AvaMgr.pb.h"
#include "AvaMgrPeerStatusInterface_caller.h"
#include "AvaMgrProcessStatusInterface_caller.h"
#include "AvaMgrComponentStatusInterface_caller.h"
#include "AvailabilityManager.h"
#define NO_OF_NODES_IN_CLUSTER 2
#define MAX_RETRY_FOR_FAILOVER 3
#define MAX_RETRY_FOR_UNKNOWN 10
#define DEFAULT_BUCKET "DiameterSession"
#ifdef FOR_DRE
#define INIT_COUCHBASE "/opt/diametriq/dre/scripts/config_cb.sh"
#elif defined FOR_IWF
#define INIT_COUCHBASE "/opt/diametriq/iwf/scripts/config_cb.sh"
#endif
#define MAX_REBALANCE_FAIL_COUNT 1800 //15 mins
#define MAX_FAILED_TO_CONNECT 3
eAccelero::ClusterManagementStatus eAccelero::CouchbaseClusterManager::m_curClusterStatus;
namespace eAccelero {

    ClusterManager::~ClusterManager()
    {
    }

    uint32_t ClusterManager::Initialize(Node node)
    {
        done = false;
        return 0;
    }

    void ClusterManager::Terminate()
    {
        done = true;
    }

    uint16_t ClusterManager::GetClusterStatus()
    {
        return 0;
    }

    uint32_t ClusterManager::AddNodeToCluster(Node& node)
    {
        return 0;
    }


    uint32_t ClusterManager::PutEvent(ClusterManagementEvent event)
    {
        CLOG_DEBUG("Putting Event with operation %d in Queue",event.operation);
        tQueue.Push(event);
        return 0;
    }

    CouchbaseClusterManager::CouchbaseClusterManager(ReplicationConfig repConfig):
        m_failCount(0),isActive(false),isClusterInitialized(false),
        m_RebalanceNodesUpdated(false),m_IsClusterHealthy(false),m_LocalCbNodeMarkedDown(false),m_MateCbNodeMarkedDown(false),flipFlag{false,false}
    {

        char *iss7ConfigDir = (char *)::getenv("ISS7_CONFIG_DIR");
        string confFile;

        if(iss7ConfigDir != NULL)
            confFile = iss7ConfigDir;
        else {
            CLOG_CRITICAL("ISS7_CONFIG_DIR environment variable not set, exiting...");
            ::exit(-1);
        }

        confFile += "/";
        confFile += "couchbase.cfg";

        bool isConfigFileOpenSuccessful = false;
        ConfigReader configReader(confFile.c_str(), isConfigFileOpenSuccessful);
        map<string, string>::const_iterator map_iterator;

        if (isConfigFileOpenSuccessful) {
            m_objConfigReaderMap = configReader.getConfigMap();

            string couchbaseCfgInfo;

            couchbaseCfgInfo += "Couch-Base Server configuration:\n";

            for (map_iterator = m_objConfigReaderMap.begin(); map_iterator != m_objConfigReaderMap.end(); map_iterator++)
            {
                couchbaseCfgInfo += map_iterator->first;
                couchbaseCfgInfo += " ==>";
                couchbaseCfgInfo += map_iterator->second;
                couchbaseCfgInfo += "\n";
            }
            CLOG_DEBUG(couchbaseCfgInfo.c_str());
        } else {
            CLOG_ERROR("couchbase.cfg open failed");
            exit(1);
        }
        map_iterator=m_objConfigReaderMap.begin();
        map_iterator = m_objConfigReaderMap.find("cb_hostname");
        if (map_iterator != m_objConfigReaderMap.end()) {
            cb_Config.hostName = map_iterator->second;
        }

        map_iterator = m_objConfigReaderMap.find("cb_port");
        if (map_iterator != m_objConfigReaderMap.end()) {
            cb_Config.port = atoi((char *)map_iterator->second.c_str());
        }

        map_iterator = m_objConfigReaderMap.find("cb_userName");
        if (map_iterator != m_objConfigReaderMap.end()) {
            cb_Config.adminUserName = map_iterator->second;
        }

        map_iterator = m_objConfigReaderMap.find("cb_pass");
        if (map_iterator != m_objConfigReaderMap.end()) {
            cb_Config.adminPassword = map_iterator->second;


        }

        map_iterator = m_objConfigReaderMap.find("cb_matehostname");
        if (map_iterator != m_objConfigReaderMap.end()) {
            cb_Config.mateHostName = map_iterator->second;
        }

        CLOG_INFO("Parsed %s",cb_Config.adminPassword.c_str());
        map_iterator = m_objConfigReaderMap.find("cb_mateip");
        if (map_iterator != m_objConfigReaderMap.end()) {
            cb_Config.mateIP = map_iterator->second;
        }


        cbPeerConfig.adminUserName=cb_Config.adminUserName;
        cbPeerConfig.port=cb_Config.port;
        cbPeerConfig.adminPassword=cb_Config.adminPassword;
        cbPeerConfig.hostName=cb_Config.mateIP;

        //default values
        if(cbPeerConfig.adminUserName.empty())
        {
            CLOG_DEBUG("adminUserName is empty, assigning default value.");
            cbPeerConfig.adminUserName="dquser";
            cb_Config.adminUserName="dquser";
        }

        if(cbPeerConfig.port == 0)
        {
            CLOG_DEBUG("port is empty, assigning default value.");
            cbPeerConfig.port=8091;
            cb_Config.port=8091;
        }

        if(cbPeerConfig.adminPassword.empty())
        {
            CLOG_DEBUG("adminPassword is empty, assigning default value.");
            cbPeerConfig.adminPassword="diametriq@123";
            cb_Config.adminPassword="diametriq@123";
        }

        CLOG_DEBUG("cb_Config.adminUserName=%s",cb_Config.adminUserName.c_str());
        CLOG_DEBUG("cb_Config.port=%d",cb_Config.port);
        CLOG_DEBUG("cb_Config.adminPassword=%s",cb_Config.adminPassword.c_str());
        CLOG_DEBUG("cb_Config.hostName=%s",cb_Config.hostName.c_str());

        CLOG_DEBUG("cbPeerConfig.adminUserName=%s",cbPeerConfig.adminUserName.c_str());
        CLOG_DEBUG("cbPeerConfig.port=%d",cbPeerConfig.port);
        CLOG_DEBUG("cbPeerConfig.adminPassword=%s",cbPeerConfig.adminPassword.c_str());
        CLOG_DEBUG("cbPeerConfig.hostName=%s",cbPeerConfig.hostName.c_str());

        cb_Client = new CouchbaseClusterMgmtClient(cb_Config);
        cbPeerClient = new CouchbaseClusterMgmtClient(cbPeerConfig);
        cb_Client->Initialize();
        //cb client initialization for communicating with peer cb node:w
        //
        cbPeerClient->Initialize();
        m_repConfig = repConfig;
    }

    CouchbaseClusterManager::~CouchbaseClusterManager()
    {
        delete cb_Client;
        delete cbPeerClient;

    }

    void CouchbaseClusterManager::Run(void* arg)
    {
        CLOG_DEBUG("Starting Cluster Mgmt Thread");
        ClusterManagementEvent event;
        uint32_t ret = 0;
        static int count=0;
        uint32_t rebalanceRet=0;
        while(!done)
        {
            rebalanceRet=0;
            if(!tQueue.WaitAndPop(event,TQ_WAIT_TIMEOUT))
            {
		//Timeout has happened.
		continue;
            }
            std::vector<CouchbaseNode> curStatus;
            Node& node = event.node;
            switch (event.operation) {
                case CM_OP_MONITOR_CLUSTER:

                    {
                        count++;
                        CLOG_DEBUG("Got CM_OP_MONITOR_CLUSTER event");
                        if(event.isActive)
                        {
                            CLOG_DEBUG("ACTIVE NODE");
                            isActive=true;
                        }
                        else
                        {
                            CLOG_DEBUG("STANDBY NODE");
                            isActive=false;
                        }
                        // ret = MonitorCluster();
                        //local vector of couchbaseNodes
			static int32_t failedToConnectCount=0;
                        if((ret = GetClusterStatus(curStatus)) == CB_OK)
                        {
                            if( isActive)
                            {
                                if( (rebalanceRet=cb_Client->CheckRebalanceStatus(m_curClusterStatus.node1RebalanceProgress, m_curClusterStatus.node2RebalanceProgress)) == CB_CURL_REBALANCE_FAILED)
                                {
                                    CLOG_WARNING("Rebalance failed! Retrying...");
                                    RebalanceCluster(true);
                                    m_node1PrevRebalanceProgress=0.0;
                                    m_node2PrevRebalanceProgress=0.0;
                                    m_curClusterStatus.node1RebalanceProgress=0.0;
                                    m_curClusterStatus.node2RebalanceProgress=0.0;
                                    m_rebalanceStuckCounter=0;
                                    m_curClusterStatus.isRebalanceStuck=false;
                                }
                                else
                                if(rebalanceRet == CB_REBALANCE_INPROGRESS)
                                {
                                    CLOG_DEBUG("Rebalance in progress");
                                    CLOG_DEBUG("Rebalance progress = %f , %f",m_curClusterStatus.node1RebalanceProgress,m_curClusterStatus.node2RebalanceProgress);

                                    if( m_curClusterStatus.node1RebalanceProgress == m_node1PrevRebalanceProgress &&
                                        m_curClusterStatus.node2RebalanceProgress == m_node2PrevRebalanceProgress)
                                    {
                                        m_rebalanceStuckCounter++;
                                        CLOG_DEBUG("Rebalance stuck counter=%u",m_rebalanceStuckCounter);
                                        if(m_rebalanceStuckCounter >= MAX_REBALANCE_FAIL_COUNT)
                                        {
                                            //Set the flag to raise alarm
                                            CLOG_ERROR("Couchbase Rebalance is not progressing and has stopped!");
                                            CLOG_ERROR("Progress in node 1=%f% , Progress in node 2=%f ",m_curClusterStatus.node1RebalanceProgress*100,m_curClusterStatus.node2RebalanceProgress*100);
                                            m_curClusterStatus.isRebalanceStuck=true;
                                        }
                                    }
                                    else
                                    {
                                        m_rebalanceStuckCounter=0;
                                        m_node1PrevRebalanceProgress=m_curClusterStatus.node1RebalanceProgress;
                                        m_node2PrevRebalanceProgress=m_curClusterStatus.node2RebalanceProgress;
                                        m_curClusterStatus.isRebalanceStuck=false;

                                    }




                                }
                                else
                                if(rebalanceRet == CB_OK)
                                {
                                    CLOG_DEBUG("Resetting all rebalance related variables!");
                                    m_node1PrevRebalanceProgress=0.0;
                                    m_node2PrevRebalanceProgress=0.0;
                                    m_curClusterStatus.node1RebalanceProgress=0.0;
                                    m_curClusterStatus.node2RebalanceProgress=0.0;
                                    m_rebalanceStuckCounter=0;
                                    m_curClusterStatus.isRebalanceStuck=false;
                                }

                            }

			     failedToConnectCount=0;
                        }
                        else
                        {
                            CLOG_ERROR("Failed to get local cluster status!");
                        }

                        //if GettingClusterStatus failed, try to ping the local cb node to check if
                        //its reachable
                        bool isLocalNodeReachable=IsLocalCbNodeReachable();
                        if(ret != CB_OK && isLocalNodeReachable)
                        {

                            CLOG_DEBUG("Local Node is reachable!");
                            //when a DRE node is active, and we start second DRE node
                            //Initially isPeerAvailable flag is set to false until it gets peerPingResp
                            //from the Already running DRE node. So count 5 here is to give some time to
                            //get the actual peer status.
                            if(event.isPeerAvailable ||  count < 5)
                            {
                                CLOG_DEBUG("Peer Node is available!");
                                CLOG_DEBUG("Peer Node to add it back to cluster!");
                                m_curClusterStatus.localCbHealth=HEALTHY;
                            }
                            else
                            {
                                int initCbRet=0;
                                CLOG_DEBUG("Marking local couchbase node as healthy");
                                m_curClusterStatus.localCbHealth=HEALTHY;
                                //try to perform couchbase initialization
                                CLOG_DEBUG("Initializing local couchbase node...");
                                if((initCbRet=system(INIT_COUCHBASE)!=0))
                                {
                                    CLOG_ERROR("ret=%d,Couchbase initialization failed!",initCbRet);
                                }
                                else
                                {
                                    CLOG_DEBUG("Couchbase initialization success!");
                                }
                            }
			    failedToConnectCount=0;

                        }
                        else if(!isLocalNodeReachable)
                        {
                            CLOG_ERROR("Local Node is not reachable!");
			    if(failedToConnectCount >= MAX_FAILED_TO_CONNECT)
			    {
				m_curClusterStatus.localCbHealth=UNHEALTHY;
				CLOG_ERROR("failedToConnectCount=%d",failedToConnectCount);
			    }
			    else
			    {
				m_curClusterStatus.localCbHealth=HEALTHY;
				CLOG_ERROR("failedToConnectCount=%d",failedToConnectCount);
			    }
			    failedToConnectCount++;
                        }
                    }
                    break;

                case CM_OP_ADD_NODE:
                    {
                        CLOG_DEBUG("Got CM_OP_ADD_NODE event");
                        //stop rebalance if any
                        //cb_Client->StopRebalance();

                        node.hostName=cb_Config.mateIP;
                        ret = AddNodeToCluster(node,false);
                        if(ret != CB_OK)
                        {
                            CLOG_ERROR("Failed to add node %s to cluster,error code: %d",node.hostName.c_str(),ret);
                            continue;
                        }

                        //if add node is success form the CouchbaseNode and Perform Rebalance
                        std::vector<CouchbaseNode> initRebalance;
                        ret = GetClusterStatus(initRebalance);
                        if(ret != CB_OK)
                        {
                            CLOG_ERROR("Failed on GetClusterStatus, error code: %d", ret);
                            break;
                        }
                        uint32_t initRebalanceSize = initRebalance.size();
                        CLOG_DEBUG("No of nodes in the cluster :%d", initRebalanceSize);
                        for(uint32_t index = 0; index < initRebalanceSize; index++)
                        {
                            CLOG_DEBUG("Node :%d --> %s", index, initRebalance[index].getOtpNode().c_str());
                        }

                        ret = cb_Client->RebalanceCluster(initRebalance);
                        if(ret != CB_OK)
                        {
                            CLOG_ERROR("Failed to rebalance after adding node %s to cluster,error code: %d"
                                    ,node.hostName.c_str(),ret);
                        }
                    }   break;
                case CM_OP_REM_NODE:
                    {
                        //stop rebalance if any
                        //cb_Client->StopRebalance();
                        CouchbaseNode failoverCbNode;
                        std::vector<CouchbaseNode> rebalanceNodes;
                        ret = GetClusterStatus(rebalanceNodes);
                        if(ret != CB_OK)
                        {
                            CLOG_ERROR("Failed on GetClusterStatus, error code: %d", ret);
                            break;
                        }
                        uint32_t initRebalanceSize = rebalanceNodes.size();
                        CLOG_DEBUG("No of nodes in the cluster :%d", initRebalanceSize);
                        std::string tmp;
                        for(uint32_t index = 0; index < initRebalanceSize; index++)
                        {
                            CLOG_DEBUG("Node :%d --> %s", index, rebalanceNodes[index].getOtpNode().c_str());
                            tmp=rebalanceNodes[index].getOtpNode();
                            if(tmp.find(cb_Config.mateIP) != std::string::npos)
                            {
                                failoverCbNode.setOtpNode(rebalanceNodes[index].getOtpNode());
                                CLOG_DEBUG("Failover mate node %d",rebalanceNodes[index].getOtpNode().c_str());
                            }
                        }

                        cb_Client->FailOverNode(failoverCbNode);
                        cb_Client->RebalanceCluster(rebalanceNodes);
                    }
                    break;

                case CM_OP_PURGE_METADATA:
                    {
                        ret= cb_Client->PurgeUnwantedData(DEFAULT_BUCKET);
                        break;
                    }

                default:
                    CLOG_DEBUG("Unknown event with operation %d.",event.operation);
                    break;
            }
        }

    }

    uint16_t CouchbaseClusterManager::GetClusterStatus(std::vector<CouchbaseNode> &nodes)
    {
        uint32_t ret=CB_OK;
        //Use REST API to get cluster status.
        nodes.clear();
        if ((ret=cb_Client->FetchClusterStatus(nodes))!= CB_OK)
        {
            CLOG_DEBUG("Failed to fetch cluster status from local couchbase node! ");
            m_curClusterStatus.status=CB_GENERIC_ERROR;
            m_curClusterStatus.nodesInCluster=0;
            m_curClusterStatus.localCbHealth=UNHEALTHY;
            return ret;
        }

        bool isPeerNode=false;
        m_curClusterStatus.nodesInCluster=0;
        m_curClusterStatus.status=CB_OK;
        //set the couchbase node status
        CLOG_DEBUG("Got Cluster Status :size=%d",nodes.size());
        for( uint32_t i=0; i< nodes.size(); i++)
        {
            m_curClusterStatus.nodesInCluster++;
            isPeerNode=false;
            if(cbPeerConfig.hostName.compare(nodes[i].hostName) == 0)
            {
                isPeerNode=true;
            }
            switch(nodes[i].nodeStatus)
            {

                case HEALTHY:
                    {
                        CLOG_DEBUG("Node %d is Healthy",i);
                        m_curClusterStatus.operation=CM_OP_MONITOR_CLUSTER;
                        m_curClusterStatus.status=CB_OK;
                        if(isPeerNode)
                        {
                            m_curClusterStatus.peerCbHealth=HEALTHY;
                        }
                        else
                        {
                            m_curClusterStatus.localCbHealth=HEALTHY;
                        }
                    }
                    break;

                case UNHEALTHY:
                    {
                        CLOG_DEBUG("Node %d is Unhealthy",i);
                        if(isPeerNode)
                        {
                            m_curClusterStatus.peerCbHealth=UNHEALTHY;
                        }
                        else
                        {
                            m_curClusterStatus.localCbHealth=UNHEALTHY;
                        }

                    }
                    break;

                case WARMUP:
                    {
                        CLOG_DEBUG("Node %d is Warming Up",i);
                        if(isPeerNode)
                        {
                            m_curClusterStatus.peerCbHealth=WARMUP;
                        }
                        else
                        {
                            m_curClusterStatus.localCbHealth=WARMUP;
                        }

                    }
                    break;
            }

        }
        return ret;
    }


    uint32_t CouchbaseClusterManager::HandleFlipInStatus(std::vector<CouchbaseNode>&prevStatus,
            std::vector<CouchbaseNode>&curStatus)
    {
        uint32_t ret=0;
        static uint32_t localCbRetryCount;
        static uint32_t mateCbRetryCount;
        bool bothNodesReachable=false;
        static uint32_t cbUnknownStateCount;
        //check if there is any diffrence in status b/w previous status
        //and current status of the couchbase nodes
        if ( isActive )
        {

            if(IsLocalCbNodeReachable() && IsMateCbNodeReachable())
            {
                bothNodesReachable=true;
            }
            uint32_t i=0;
            if(prevStatus.size() != curStatus.size())
            {
                CLOG_DEBUG("prev node Status not updated");
                return ret;
            }
            for(  i=0; i< curStatus.size(); i++)
            {
                if(!m_RebalanceNodesUpdated)
                {
                    //if there are 2 nodes update the m_RebalanceNodes
                    //to take care of future rebalances

                    m_RebalanceNodes.clear();
                    for(uint32_t j=0; j<curStatus.size(); j++)
                    {
                        m_RebalanceNodes.push_back(curStatus[i]);
                    }
                    if( curStatus.size() == NO_OF_NODES_IN_CLUSTER)
                    {
                        CLOG_DEBUG("m_RebalanceNodesUpdated");
                        m_RebalanceNodesUpdated=true;
                        CLOG_DEBUG("m_IsClusterHealthy=true");
                        m_IsClusterHealthy=true;

                    }
                }

                CLOG_DEBUG("curStatus[%d].hostname=%s",i,curStatus[i].hostName.c_str());
                //Ensure that we are comparing the same nodes( Previous status and current status)
                if(!curStatus[i].getOtpNode().compare(prevStatus[i].getOtpNode()) )
                {
                    CLOG_DEBUG("Nodes match");
                }
                else
                {
                    CLOG_DEBUG("Nodes do not match , swapping...");
                    std::swap(curStatus[i],curStatus[i+1]);
                }
                //equal
                if ( curStatus[i].nodeStatus != prevStatus[i].nodeStatus)
                {
                    CLOG_INFO("There is a flip in node status");
                    CLOG_DEBUG("Current status of %s ",curStatus[i].getOtpNode().c_str());
                    CLOG_DEBUG("nodes[%d].nodeStatus=%u",i,curStatus[i].nodeStatus);
                    CLOG_DEBUG("Previous status of %s ",prevStatus[i].getOtpNode().c_str());
                    CLOG_DEBUG("nodes[%d].nodeStatus=%u",i,prevStatus[i].nodeStatus);
                    flipFlag[i]=true;


                }
                else
                {
                    CLOG_DEBUG("No flip in the node status");
                    CLOG_DEBUG("Current status of %s ",curStatus[i].getOtpNode().c_str());
                    CLOG_DEBUG("nodes[%d].nodeStatus=%u",i,curStatus[i].nodeStatus);
                    CLOG_DEBUG("Previous status of %s ",prevStatus[i].getOtpNode().c_str());
                    CLOG_DEBUG("nodes[%d].nodeStatus=%u",i,prevStatus[i].nodeStatus);

                    if ( (m_RebalanceNodesUpdated))
                    {

                        //check if the node which is up is the peer node ,
                        //if yes Try Adding the local couchbase node to the cluster
                        //else try adding the peer node to the cluster

                        if(m_LocalCbNodeMarkedDown && IsLocalCbNodeReachable() && (curStatus[i].nodeStatus != WARMUP))
                        {

                            CLOG_DEBUG("Peer couchbase node is up, Try adding local couchbase node to the cluster");
                            Node localNode;
                            localNode.hostName=cb_Config.hostName;
                            //have to add the local couchbase node to the cluster
                            if(AddNodeToCluster(localNode,true) == CB_OK)
                            {
                                std::vector<CouchbaseNode> rebalanceNodes;
                                CLOG_DEBUG("Added peer couchbase node to the cluster");

                                if(GetClusterStatus(rebalanceNodes) != CB_OK)
                                {
                                    CLOG_ERROR("Failed on GetClusterStatus, error code: %d", ret);
                                }
                                else
                                {
                                    uint32_t rebalanceNodesSize = rebalanceNodes.size();
                                    CLOG_DEBUG("No of nodes in the cluster :%d", rebalanceNodesSize);
                                    for(uint32_t index = 0; index < rebalanceNodesSize; index++)
                                    {
                                        CLOG_DEBUG("Node :%d --> %s", index, rebalanceNodes[index].getOtpNode().c_str());
                                    }

                                    //rebalance
                                    RebalanceCluster(rebalanceNodes,cb_Client);
                                    CLOG_DEBUG("m_IsClusterHealthy=true");
                                    m_IsClusterHealthy=true;
                                    CLOG_DEBUG("MARKING LOCAL NODE UP");
                                    m_LocalCbNodeMarkedDown=false;
                                }
                            }
                        }
                        else
                            if(m_MateCbNodeMarkedDown && IsMateCbNodeReachable() && (curStatus[i].nodeStatus != WARMUP))
                            {
                                CLOG_DEBUG("Local couchbase node is up, Try adding Peer couchbase node to the cluster");
                                //try adding the mate couchbase node to the cluster
                                Node mateNode;
                                mateNode.hostName=cbPeerConfig.hostName;
                                //have to add the peer couch base to the cluster
                                if(AddNodeToCluster(mateNode,false) == CB_OK)
                                {
                                    std::vector<CouchbaseNode> rebalanceNodes;
                                    CLOG_DEBUG("Added local couchbase node to the cluster");

                                    if(GetClusterStatus(rebalanceNodes) != CB_OK)
                                    {
                                        CLOG_ERROR("Failed on GetClusterStatus, error code: %d", ret);
                                    }
                                    else
                                    {
                                        uint32_t rebalanceNodesSize = rebalanceNodes.size();
                                        CLOG_DEBUG("No of nodes in the cluster :%d", rebalanceNodesSize);
                                        for(uint32_t index = 0; index < rebalanceNodesSize; index++)
                                        {
                                            CLOG_DEBUG("Node :%d --> %s", index, rebalanceNodes[index].getOtpNode().c_str());
                                        }

                                        //rebalance
                                        RebalanceCluster(rebalanceNodes,cbPeerClient);
                                        CLOG_DEBUG("m_IsClusterHealthy=true");
                                        m_IsClusterHealthy=true;
                                        CLOG_DEBUG("MARKING MATE NODE UP");
                                        m_MateCbNodeMarkedDown=false;
                                    }
                                }
                            }
                    }
                    CLOG_DEBUG("CLUSTER SIZE=%d",curStatus.size());

                }
                if(flipFlag[i])
                {
                    //if the current status of the node us unhealthy perform failover and rebalance
                    if( curStatus[i].nodeStatus == UNHEALTHY )
                    {
                        //m_IsClusterHealthy=false;
                        CLOG_DEBUG(" Node %s became UNHEALTHY",curStatus[i].getOtpNode().c_str());
                        std::string tmp="ns_1@";
                        tmp.append(cbPeerConfig.hostName);
                        //check if the node is present in the local machine
                        if (cbPeerConfig.hostName.compare(curStatus[i].hostName)!= 0)
                        {
                            //local couchbase node has become unhealthy
                            if(localCbRetryCount == MAX_RETRY_FOR_FAILOVER)
                            {
                                CouchbaseNode localCbNode;
                                std::vector<CouchbaseNode> rebalanceNodes;
                                localCbNode.setOtpNode(curStatus[i].getOtpNode());

                                //max retries reached so failover and rebalance
                                CLOG_DEBUG("Failover %s",curStatus[i].getOtpNode().c_str());
                                cbPeerClient->FailOverNode(localCbNode);
                                CLOG_DEBUG("Rebalance scheduled");
                                CLOG_DEBUG("Rebalancing %s",curStatus[0].getOtpNode().c_str());
                                if( curStatus.size() == NO_OF_NODES_IN_CLUSTER )
                                {
                                    rebalanceNodes.push_back(curStatus[0]);
                                    rebalanceNodes.push_back(curStatus[1]);
                                }
                                else
                                {
                                    rebalanceNodes.push_back(curStatus[0]);
                                }
                                cbPeerClient->RebalanceCluster(rebalanceNodes);

                                //reset the count
                                CLOG_DEBUG("Reset m_localCbMaxRetry");
                                localCbRetryCount=0;
                                flipFlag[i]=false;
                                m_IsClusterHealthy=false;
                                CLOG_DEBUG("MARKING LOCAL NODE DOWN");
                                m_LocalCbNodeMarkedDown=true;;
                            }
                            else
                            {
                                localCbRetryCount++;
                                CLOG_DEBUG("Incrementing mateCbRetryCount: %u",localCbRetryCount);
                            }

                        }
                        else
                        {
                            //mate couchbase node has become unhealthy
                            if(mateCbRetryCount == MAX_RETRY_FOR_FAILOVER)
                            {
                                CouchbaseNode mateCbNode;
                                std::vector<CouchbaseNode> rebalanceNodes;
                                mateCbNode.setOtpNode(curStatus[i].getOtpNode().c_str());

                                //max retries reached so failover and rebalance
                                CLOG_DEBUG("Failover %s",curStatus[i].getOtpNode().c_str());
                                cb_Client->FailOverNode(mateCbNode);
                                CLOG_DEBUG("Rebalance scheduled");
                                CLOG_DEBUG("Rebalancing %s",curStatus[0].getOtpNode().c_str());
                                rebalanceNodes.push_back(curStatus[0]);
                                if( curStatus.size() == NO_OF_NODES_IN_CLUSTER)
                                {
                                    rebalanceNodes.push_back(curStatus[1]);
                                }
                                cb_Client->RebalanceCluster(rebalanceNodes);

                                //reset the count
                                CLOG_DEBUG("Reset m_mateCbMaxRetry");
                                mateCbRetryCount=0;
                                flipFlag[i]=false;
                                m_IsClusterHealthy=false;
                                CLOG_DEBUG("MARKING MATE NODE DOWN");
                                m_MateCbNodeMarkedDown=true;
                            }
                            else
                            {
                                mateCbRetryCount++;
                                CLOG_DEBUG("Incrementing mateCbRetryCount: %u",mateCbRetryCount);
                            }


                        }
                    }
                    else
                        if( curStatus[i].nodeStatus == HEALTHY )
                        {
                            CLOG_DEBUG(" Node %s became HEALTHY",curStatus[i].getOtpNode().c_str());
                            flipFlag[i]=false;
                            //if node became healthy reset the RetryCount
                            if(localCbRetryCount != 0)
                            {
                                CLOG_DEBUG("Reset localCbRetryCount");
                                localCbRetryCount = 0;
                            }

                            if(mateCbRetryCount != 0)
                            {
                                CLOG_DEBUG("Reset mateCbRetryCount");
                                mateCbRetryCount=0;
                            }

                        }
                        else
                            if ( curStatus[i].nodeStatus ==  WARMUP)
                            {
                                CLOG_DEBUG(" Node %s is in WARMUP state",curStatus[i].getOtpNode().c_str());
                                flipFlag[i]=false;
                                if(localCbRetryCount != 0)
                                {
                                    CLOG_DEBUG("Reset localCbRetryCount");
                                    localCbRetryCount = 0;
                                }

                                if(mateCbRetryCount != 0)
                                {
                                    CLOG_DEBUG("Reset mateCbRetryCount");
                                    mateCbRetryCount=0;
                                }

                            }
                }

            }
            //If switchover is done after a failover,rebalance
            //markedDown flag information is lost,so below code
            //is to handle such case
            if(bothNodesReachable && (curStatus.size() ==1))
            {
                CLOG_DEBUG("Both nodes are reachable but only one node in the cluster!");
                if(cbUnknownStateCount == MAX_RETRY_FOR_UNKNOWN)
                {
                    CLOG_DEBUG("Seems like couchbase is in unknown state");
                    //Add the node which is not in the cluster
                    //find out which node to be added
                    Node nodeToAdd;
                    std::string tmpStr="ns_1@";
                    tmpStr.append(cbPeerConfig.hostName);
                    std::string curNodeStr;
                    // curNodeStr=curStatus[0].getOtpNode();
                    curNodeStr=curStatus[0].hostName;
                    CLOG_DEBUG("curNodeStr=%s curStatus[i].getOtpNode()=%s tmpStr=%s",curNodeStr.c_str(),curStatus[0].getOtpNode().c_str(),
                            tmpStr.c_str());
                    if(cbPeerConfig.hostName.compare(curNodeStr) == 0)
                    {
                        //Peer node is already in the cluster so add the local node
                        CLOG_DEBUG("Adding local couchbase node to the cluster");
                        nodeToAdd.hostName=cb_Config.hostName;
                        if(AddNodeToCluster(nodeToAdd,true) == CB_OK)
                        {
                            CLOG_DEBUG("Performing rebalance operation by connecting to peer couchbase");
                            RebalanceCluster(false);
                        }

                    }
                    else
                    {
                        //Local node is already in the cluster so add the peer node
                        CLOG_DEBUG("Adding peer couchbase node to the cluster");
                        nodeToAdd.hostName=cbPeerConfig.hostName;
                        if(AddNodeToCluster(nodeToAdd,false) == CB_OK)
                        {
                            CLOG_DEBUG("Performing rebalance operation by connecting to local couchbase");
                            RebalanceCluster(true);
                        }
                    }
                    //And do a rebalance
                    CLOG_DEBUG("Resetting cbUnknownStateCount");
                    cbUnknownStateCount=0;
                }
                cbUnknownStateCount++;
            }
        }

        return CB_OK;
    }



    bool CouchbaseClusterManager::IsClusterReachable()
    {
        //If both the nodes in the cluster are not reachable
        //return false
        if(!IsLocalCbNodeReachable() && !IsMateCbNodeReachable())
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    uint32_t CouchbaseClusterManager::MonitorCluster()
    {
        static bool isCouchbaseReachable = false;
        uint32_t ret = 0;

        if (!isClusterInitialized)
        {
            if((ret = GetClusterStatus(m_PrevStatus)) == CB_OK)
            {
                isClusterInitialized=true;
            }
            return ret;
        }
        //local vector of couchbaseNodes
        std::vector<CouchbaseNode> curStatus;

        if((ret = GetClusterStatus(curStatus)) == CB_OK)
        {
            //Check any rebalance failure has happened,
            //if so retry rebalance
            double node1RebalanceProgress,node2RebalanceProgress;
            if( cb_Client->CheckRebalanceStatus(node1RebalanceProgress,node2RebalanceProgress) == CB_CURL_REBALANCE_FAILED)
            {
                CLOG_WARNING("Rebalance failed! Retrying...");
                RebalanceCluster(true);

            }

            //check and handle flip

            HandleFlipInStatus(m_PrevStatus,curStatus);
        }
        else
        {
            CLOG_DEBUG("Got error %d in cluster status",ret);
        }

        if(!IsClusterReachable())
        {
            m_failCount++;
            isCouchbaseReachable = false;
            CLOG_ERROR("CANT_REACH_CLUSTER: count=%d",m_failCount);
        }
        else
        {
            m_failCount = 0;
            isCouchbaseReachable = true;
            AvailabilityManager::stopReplication = false;
        }

        if(m_failCount > m_repConfig.clusterConnRetryFailure)
        {
            //Raise an Alarm
            CLOG_ERROR("STOP REPLICATION");

            flipFlag[0]=true;
            flipFlag[1]=true;
            //Inform AvaMgr thread to Send Stop Replication msg to all components.
            AvailabilityManager::stopReplication = true;
        }
        m_PrevStatus=curStatus;
        return 0;
    }


    // Rebalance function used when one of the nodes went down.
    // mgmtClient is the connection towards the existing couchbase node
    uint32_t CouchbaseClusterManager::RebalanceCluster(std::vector<CouchbaseNode> &nodes, CouchbaseClusterMgmtClient *mgmtClient)
    {

        uint32_t ret=CB_OK;
        if(nodes.size() == NO_OF_NODES_IN_CLUSTER)
        {
            CLOG_DEBUG("Performing Rebalance operation");
            if(mgmtClient)
            {
                ret=mgmtClient->RebalanceCluster(nodes);
            }
        }
        else
        {
            CLOG_ERROR("Cannot rebalance node.size == 0");
            ret=!CB_OK;
        }
        return ret;
    }

    //Rebalance function used when one of the node has been added back to the
    //cluster, if isLocalCbNode==true, then peer couchbase node has been added
    //back, if isLocalCbNode==false , then local couchbase node has been added
    //back to the cluster
    uint32_t CouchbaseClusterManager::RebalanceCluster(bool isLocalCbNode)
    {
        uint32_t ret = CB_OK;
        std::vector<CouchbaseNode> rebalanceNodes;

        ret = GetClusterStatus(rebalanceNodes);
        if(ret != CB_OK)
        {
            CLOG_ERROR("Failed on GetClusterStatus, error code: %d", ret);
            return ret;
        }

        uint32_t rebalanceNodesSize = rebalanceNodes.size();
        CLOG_DEBUG("No of nodes in the cluster :%d", rebalanceNodesSize);
        for(uint32_t index = 0; index < rebalanceNodesSize; index++)
        {
            CLOG_DEBUG("Node :%d --> %s", index, rebalanceNodes[index].getOtpNode().c_str());
        }

        //Invoke the API to rebalance
        //if local coubhase node has to be rebalanced
        if(isLocalCbNode)
        {
            CLOG_DEBUG("Performing rebalance on local couchbase node");
            ret=cb_Client->RebalanceCluster(rebalanceNodes);
        }
        else //if peer couchbase node has to be rebalanced
        {
            CLOG_DEBUG("Performing rebalance on peer couchbase node");
            ret=cbPeerClient->RebalanceCluster(rebalanceNodes);
        }

        return ret;
    }

    uint32_t CouchbaseClusterManager::AddNodeToCluster(Node& node,bool isLocalCbNode)
    {
        uint32_t ret=CB_OK;
        CouchbaseNode cbNode;

        cbNode.setUserName(cb_Config.adminUserName);
        cbNode.setPassword(cb_Config.adminPassword);
        cbNode.hostName=node.hostName;
        CLOG_DEBUG("Adding node with hostname %s to couchbase cluster",node.hostName.c_str());
        if(isLocalCbNode)
        {
            CLOG_DEBUG("Connecting to Peer couchbase to add local couchbase node");
            ret=cbPeerClient->AddNodeToCluster(cbNode);
        }
        else
        {

            CLOG_DEBUG("Connecting to Local couchbase to add peer couchbase node");
            ret=cb_Client->AddNodeToCluster(cbNode);
        }
        return ret;
    }


    bool CouchbaseClusterManager::IsLocalCbNodeReachable()
    {
        uint32_t ret=cb_Client->PingNode();
        if (ret != CB_OK)
        {
            CLOG_DEBUG("Local CB Node is not reachable");
            return false;
        }
        else
        {
            CLOG_DEBUG("Local CB Node is reachable");
            return true;
        }
    }

    bool CouchbaseClusterManager::IsMateCbNodeReachable()
    {
        uint32_t ret=cbPeerClient->PingNode();
        if (ret != CB_OK)
        {
            CLOG_DEBUG("Mate CB Node is not reachable");
            return false;
        }
        else
        {
            CLOG_DEBUG("Mate CB Node is reachable");
            return true;
        }
    }

    uint32_t CouchbaseClusterManager::PurgeUnwantedData(std::string replica)
    {
        uint32_t ret=CB_OK;
        ret=cb_Client->PurgeUnwantedData(replica);
        return ret;
    }

    uint32_t CouchbaseClusterManager::GetCbStatus(ClusterManagementStatus &cmStatus)
    {
        uint32_t ret=CB_OK;
        CLOG_DEBUG(">>>>CouchbaseClusterManager::GetCbStatus>>>>");
        CLOG_DEBUG("Health=%d",m_curClusterStatus.localCbHealth);
        cmStatus=m_curClusterStatus;
        CLOG_DEBUG("<<<<CouchbaseClusterManager::GetCbStatus<<<<");
        return ret;

    }

} //namespace eAccelero
