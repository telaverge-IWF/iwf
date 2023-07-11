/* ********************************-*-CPP-*-***********************************
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
#include <its++.h>
#include "its_dre_exit_error_codes.h"
#include "ReplicationClient.h"
#include "IWFStateReplication.h"
#include "HAMeSSComponent.h"
#include "iwf.h"
#include "Logger.h"
#include "ConfigReader.h"

int iwf::IWFStateReplication::syncThreadPoolSize=4;
int iwf::IWFStateReplication::asyncThreadPoolSize=4;
//vector<ReplicaBean> iwf::IWFStateReplication::replicas;
CouchbaseConnectorBean iwf::IWFStateReplication::connDetails;
namespace iwf
{

    std::map<std::string, std::string> IWFStateReplication::m_objConfigReaderMap;
    int IWFStateReplication::Initialize(std::string repConfigFile,ReplicationStatusCbk replStatusCbk)
    {

        std::vector<ReplicaBean> replicas;

        printf("Config File is %s",repConfigFile.c_str());
        if(ParseReplicationConfig(repConfigFile) < 0)
        {
            return REPL_CONFIG_PARSE_FAILED;
        }

        //register the replication status callback
        ReplicationClient::RegisterReplicationStatusCbk(replStatusCbk);
        //Initialize the details of replicas to be created.
        CLOG_DEBUG("Passing connDetails to ReplicationClient Initialize Host-Address:%s,port:%d,username:%s,password:%s,retryConnMax=%d",
                connDetails.serverAddress.c_str(),connDetails.serverPort,connDetails.userName.c_str(),connDetails.password.c_str(),connDetails.retryConnMax);
        if(ReplicationClient::Initialize(syncThreadPoolSize,
                    asyncThreadPoolSize,
                    connDetails,
                    replicas,
                    IwfController::Instance().GetLogger()) != SUCCESS)       
        {
            CLOG_DEBUG("return REPL_CLINT_INIT_FAILED\n");
            return REPL_CLINT_INIT_FAILED;
        } 
        else
        {
            IwfController::Instance().repClient=ReplicationClient::GetInstance();
            CLOG_DEBUG("repClient = %p\n",IwfController::Instance().repClient);
            CLOG_DEBUG("ReplicationClient::GetInstance()=%p\n",ReplicationClient::GetInstance());
        }
        return 0;
    }

    int IWFStateReplication::ParseReplicationConfig(std::string configFile) 
    {

        std::vector<ReplicaBean> replicas;
        Json::Reader configFileReader;
        std::ifstream doc(configFile);
        Json::Value root;
        if(!(configFileReader.parse(doc,root)))
        {
            CLOG_ERROR("Failed to parse %s configuration. %s\n",configFile.c_str(), 
                    configFileReader.getFormattedErrorMessages().c_str());
            return REPL_CONFIG_PARSE_FAILED;
        }
        Json::Value replicationConfig = root["Replication-Config"];
        Json::Value connConfig = replicationConfig["Couchbase-Config"];

        /*Populate the connection details*/
        if(!replicationConfig["Couchbase-Config"]["Host-Name"].isNull())
        {
            connDetails.serverAddress=replicationConfig["Couchbase-Config"]["Host-Name"].asString();
        }else {
            connDetails.serverAddress = DEFAULT_COUCHBASE_HOST_NAME;
        }

        if(!replicationConfig["No-Of-Sync-Threads"].isNull())
        {
            syncThreadPoolSize=replicationConfig["No-Of-Sync-Threads"].asInt();
            CLOG_INFO ("No-Of-Sync-Threads=%d",syncThreadPoolSize);
        }
        else
        {
            syncThreadPoolSize=4;
            CLOG_INFO ("No-Of-Sync-Threads=%d",syncThreadPoolSize);
        }

        if(!replicationConfig["No-Of-Async-Threads"].isNull())
        {
            asyncThreadPoolSize=replicationConfig["No-Of-Async-Threads"].asInt();
            CLOG_INFO ("No-Of-Async-Threads=%d",asyncThreadPoolSize);

        }
        else
        {
            asyncThreadPoolSize=4;
            CLOG_INFO ("No-Of-Async-Threads=%d",asyncThreadPoolSize);
        }
        if(!replicationConfig["Couchbase-Config"]["Port"].isNull())
        {
            connDetails.serverPort= replicationConfig["Couchbase-Config"]["Port"].asInt();
        }else {
            connDetails.serverPort=DEFAULT_COUCHBASE_PORT;
        }
        connDetails.userName="";
        if(!replicationConfig["Couchbase-Config"]["Password"].isNull())
        {
            connDetails.password=replicationConfig["Couchbase-Config"]["Password"].asString();
        }else {
            connDetails.password=DEFAULT_COUCHBASE_PASSWORD;
        }

        if(!replicationConfig["Couchbase-Config"]["Retry-Conn-Max"].isNull())
        {
            connDetails.retryConnMax=replicationConfig["Couchbase-Config"]["Retry-Conn-Max"].asInt();
        }else {
            connDetails.retryConnMax=DEFAULT_RETRY_CONN_MAX;
        }


        //Populate the replica details
        Json::Value replicaConfig = replicationConfig["Replica-Config"];
        if(!replicaConfig.isNull())
        {
            for( Json::ValueIterator itr = replicaConfig.begin() ; 
                    itr != replicaConfig.end() ; itr++ ) {

                ReplicaBean rBean;
    //            rBean.replicaName = (*itr)["Replica-Name"].asString();
                rBean.replicaSize = (*itr)["Replica-Size"].asInt();
                rBean.replicaTTL = (*itr)["Replica-TTL"].asInt();

                replicas.push_back(rBean);

            }
        }
        CLOG_DEBUG("Parse Host-Address:%s,port:%d,username:%s,password:%s,retryConnMax=%d",
                connDetails.serverAddress.c_str(),connDetails.serverPort,connDetails.userName.c_str(),connDetails.password.c_str(),connDetails.retryConnMax);

        ParseCouchbaseCfg();

        return 0;
    }

    int IWFStateReplication::ParseCouchbaseCfg()
    {
        printf(" >>>>>>>>>> IWFStateReplication::ParseCouchbaseCfg >>>>>>>>>>\n");
        char *iss7ConfigDir = (char *)::getenv("ISS7_CONFIG_DIR");
        string confFile;

        if(iss7ConfigDir != NULL)
        {
            confFile = iss7ConfigDir;
        }
        else 
        {
            CLOG_ERROR("ISS7_CONFIG_DIR environment variable not set, exiting...");
            ::exit(ITS_DRE_REPLICATION_INIT_FAILURE);
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
        } 
        else 
        {
            CLOG_ERROR("couchbase.cfg open failed");
            exit(ITS_DRE_REPLICATION_INIT_FAILURE);
        }   
        map_iterator=m_objConfigReaderMap.begin();
        map_iterator = m_objConfigReaderMap.find("cb_hostname");
        if (map_iterator != m_objConfigReaderMap.end()) {
            //	cb_Config.hostName = map_iterator->second;
            connDetails.serverAddress=map_iterator->second;
        }   


        map_iterator = m_objConfigReaderMap.find("cb_mateip");
        if (map_iterator != m_objConfigReaderMap.end()) {
            //	cb_Config.mateIP = map_iterator->second;
            connDetails.serverAddress.append(";");
            connDetails.serverAddress.append(map_iterator->second);
        }

        printf("CLUSTER ADDRESS=%s\n",connDetails.serverAddress.c_str());
        printf("<<<<<<<<<<< IWFStateReplication::ParseCouchbaseCfg <<<<<<<<<<\n");

    }


} //namespace iwf
