/*********************************-*-C++-*-************************************
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

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include "AlarmId.h"
#include "HAComponent.h"
#include "AvaMgr.h"
#include "AvaMgr.pb.h"
#include "ErrorResp.h"
#include "AvaMgrPeerStatusInterface_caller.h"
#include "AvaMgrProcessStatusInterface_caller.h"
#include "AvaMgrComponentStatusInterface_caller.h"
#include "AvaMgrKPIInterface_caller.h"
#include "DreKPIInterface_caller.h"
#include "AvailabilityManager.h"
#include "ManagementInterface.h"

using namespace eAccelero;


std::string AvailabilityManager::GetNodeStatus() {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::GetNodeStatus() >>>>>>>>>>");

    char nodeStatus[NODE_STATUS_SIZE];

    memset(nodeStatus, 0, sizeof (nodeStatus));
    std::string installMode;
    std::string selfEthIfStatus;

#ifdef STANDALONE_TEST
    sprintf(nodeStatus, "Node Status (0 - INDETERMINATE; 1 - STANDBY; 2 - ACTIVE):\nNode Name: %s\nTIPC Node Id: %d\n\tavamgr: %d\n\tcmgr: %d\n\tdre: %d\n\tcli: %d\n\trepmgr: %d\n\n",
            m_objSelfCurrentStatus.selfHostname,
            m_uiOwnTipcNodeId,
            m_objSelfCurrentStatus.selfInstanceAvailabilityStatus,
            (m_objComponentIdAvailabilityStatusMap.find(COMP_CONFIG_MANAGER_DUMMY))->second,
            (m_objComponentIdAvailabilityStatusMap.find(COMP_DRE_APP_DUMMY))->second,
            (m_objComponentIdAvailabilityStatusMap.find(COMP_CLI_PROC_DUMMY))->second,
            (m_objComponentIdAvailabilityStatusMap.find(COMP_REPLICATION_MANAGER_DUMMY))->second);
#else


    if(m_iInstanceStartMode == STANDALONE_MODE)
    {
        //StandAlone Mode .. hence only copy the self node details.
        installMode="Stand-Alone";
    snprintf(nodeStatus,NODE_STATUS_SIZE, "Node Status (0 - INDETERMINATE; 1 - STANDBY; 2 - ACTIVE):\
            \n\tHA Mode: %s\
            \n\tSelf Node Details:\
            \n\t\tNode Name            : %s\
            \n\t\tNode Status          : %d\n",
            installMode.c_str(),
            m_objSelfCurrentStatus.selfHostname,
            m_objSelfCurrentStatus.selfInstanceAvailabilityStatus
            );
    }
    else
    {
        if(m_iInstanceStartMode == ACTIVE_COLD_STANDBY_MODE)
        {
            installMode="Active-Cold-Standby";
        } else if(m_iInstanceStartMode == ACTIVE_STANDBY_MODE)
        {
            installMode="Active-Standby";
        } else {
            installMode="Active-Hot-Standby";
        }
        std::string peerHostname;
        //Copy the Self Node Details
        snprintf(nodeStatus,NODE_STATUS_SIZE, "Node Status (0 - INDETERMINATE; 1 - STANDBY; 2 - ACTIVE):\n\tHA Mode: %s\
                \n\tSelf Node Details:\
                \n\t\tNode Name           : %s\
                \n\t\tNode Status         : %d\n",
                installMode.c_str(),
                m_objSelfCurrentStatus.selfHostname,
                m_objSelfCurrentStatus.selfInstanceAvailabilityStatus
                );

        if(m_objSelfCurrentStatus.selfInstanceAvailabilityStatus == InstanceAvailabilityStatus::ACTIVE)
        {
            std::string lastGoActivetime;
            time_t activetime;
            struct tm *actm;
            char tmbuf[64];
            activetime = m_objSelfCurrentStatus.selfLastGoActiveTime.tv_sec;
            actm = localtime(&activetime);
            strftime(tmbuf, sizeof tmbuf, "%d-%m-%Y %H:%M:%S", actm);
            lastGoActivetime = tmbuf;

            snprintf(nodeStatus+strlen(nodeStatus),NODE_STATUS_SIZE - strlen(nodeStatus),"\t\tLast Go-Active Time : %s\n",lastGoActivetime.c_str());
        }

        if(m_objPeerCurrentStatus.peerInstanceId == PEER_INVALID_INSTANCE_ID)
        {
            //Peer Status is not available
            peerHostname = "<Peer Name Not Available>";
            snprintf(nodeStatus+strlen(nodeStatus),NODE_STATUS_SIZE - strlen(nodeStatus),"\
                    \n\tPeer Node Details:\
                    \n\t\tNode Name           : %s\
                    \n\t\tNode Status         : %d\n",
                    peerHostname.c_str(),
                    m_objPeerCurrentStatus.peerInstanceAvailabilityStatus);
        }else {
            peerHostname = m_objPeerCurrentStatus.peerHostname;

            //Copy the Peer Node Details
            snprintf(nodeStatus+strlen(nodeStatus),NODE_STATUS_SIZE - strlen(nodeStatus),"\
                    \n\tPeer Node Details:\
                    \n\t\tNode Name           : %s\
                    \n\t\tNode Status         : %d\n",
                    peerHostname.c_str(),
                    m_objPeerCurrentStatus.peerInstanceAvailabilityStatus);
            if(m_objPeerCurrentStatus.peerInstanceAvailabilityStatus == InstanceAvailabilityStatus::ACTIVE)
            {
                std::string lastGoActivetime;
                time_t activetime;
                struct tm *actm;
                char tmbuf[64];
                activetime = m_objPeerCurrentStatus.peerLastGoActiveTime.tv_sec;
                actm = localtime(&activetime);
                strftime(tmbuf, sizeof tmbuf, "%d-%m-%Y %H:%M:%S", actm);
                lastGoActivetime = tmbuf;

                snprintf(nodeStatus+strlen(nodeStatus),NODE_STATUS_SIZE - strlen(nodeStatus),"\t\tLast Go-Active Time : %s\n",lastGoActivetime.c_str());
            }
        }
    }
#endif

    std::string strNodeStatus = nodeStatus;

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::GetNodeStatus() <<<<<<<<<<");

    return strNodeStatus;
}

int AvailabilityManager::AvaMgrSetConfiguration(AvaMgrConfig *req, AvaMgrConfigResp *resp) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::AvaMgrSetConfiguration() >>>>>>>>>>");

    // Set the response id as CMAPI_SUCCESS
    // It will be set to CMAPI_FAILURE in relevant condition(s)
    resp->set_responseid(CMAPI_SUCCESS);

    if ((req != NULL) || (req->IsInitialized())) {

        if (req->has_peerpingperiodicity())
            m_uiCfgPingPeriodicityForPeer = req->peerpingperiodicity();

        if (req->has_arbitratorpingperiodicity())
            m_uiCfgMinPingPeriodicityForArbitrator = req->arbitratorpingperiodicity();

        if (req->has_peernumconsecpingackrcvfailures())
            m_uiCfgNumConsecutivePingAckRcvFailuresFromPeer = req->peernumconsecpingackrcvfailures();

        if (req->has_arbitratornumconsecpingackrcvfailures())
            m_uiCfgNumConsecutivePingAckRcvFailuresFromArbitrator = req->arbitratornumconsecpingackrcvfailures();

        if (req->has_processrestartmaxallowedinterval())
            m_uiCfgProcessRestartMaxAllowedInterval = req->processrestartmaxallowedinterval();

        if (req->has_processrestartmaxallowedcount())
            m_uiCfgProcessRestartMaxAllowedCount = req->processrestartmaxallowedcount();

       /* if ((req->has_virtualipaddressescidrformat()) && (req->has_ethernetinterfaces())) {
            //m_objCfgVirtualIpAddressVector = this->Split((req->virtualipaddressescidrformat()).c_str(), ',');
            //m_objCfgEthernetInterfaceVector = this->Split((req->ethernetinterfaces()).c_str(), ',');
            m_objInterfaceMap[req->ethernetinterfaces().c_str()]

            ProcessIpAddressCidr();
        } else {
            CLOG_ERROR("Virtual IP addresses in CIDR format, and ethernet interfaces MUST be provided together from CLI/WebUI");

            resp->set_responseid(CMAPIRetCodes::CMAPI_ERROR);
        }*/

        if (req->has_arbitratoripaddress())
            m_strCfgArbitratorIpAddress = req->arbitratoripaddress();

        /*if (req->has_processes())
          m_objCfgProcessNameVector = this->Split((req->processes()).c_str(), ',');

          if (req->has_processpriorities())
          m_objCfgProcessPriorityVector = this->Split((req->processpriorities()).c_str(), ',');*/

        if (req->has_timetolaunchprocesses())
            m_uiCfgTimeToLaunchProcesses = req->timetolaunchprocesses();
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::AvaMgrSetConfiguration() <<<<<<<<<<");

    return 0;
}

int AvailabilityManager::AvaMgrGetConfiguration(ComponentActionReq *req, AvaMgrConfigResp *resp) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::AvaMgrGetConfiguration() >>>>>>>>>>");

    AvaMgrConfig* amData = NULL;
    if ((req != NULL) || (req->IsInitialized())) {
        switch (req->requestid()) {
            case GET_NODESTATUS:
                CLOG_INFO("AvaMgrGetConfiguration() GET_NODESTATUS in %d", m_objSelfCurrentStatus.selfInstanceId);
                resp->set_requestid(req->requestid());
                resp->set_nodestatus(GetNodeStatus());
                resp->set_responseid(CMAPIRetCodes::CMAPI_SUCCESS);
                break;
            case GET_AMCONFIG:
                CLOG_INFO("AvaMgrGetConfiguration() GET_AMCONFIG in %d", m_objSelfCurrentStatus.selfInstanceId);
                amData = resp->mutable_avamgrdata();
                amData->set_peerpingperiodicity(m_uiCfgPingPeriodicityForPeer);
                amData->set_arbitratorpingperiodicity(m_uiCfgMinPingPeriodicityForArbitrator);
                amData->set_peernumconsecpingackrcvfailures(m_uiCfgNumConsecutivePingAckRcvFailuresFromPeer);
                amData->set_arbitratornumconsecpingackrcvfailures(m_uiCfgNumConsecutivePingAckRcvFailuresFromArbitrator);
                amData->set_processrestartmaxallowedinterval(m_uiCfgProcessRestartMaxAllowedInterval);
                amData->set_processrestartmaxallowedcount(m_uiCfgProcessRestartMaxAllowedCount);
                amData->set_arbitratoripaddress(m_strCfgArbitratorIpAddress);
                amData->set_processrestartmaxallowedcountforstop(m_uiCfgProcessRestartMaxAllowedCountHp);
                amData->set_processrestartmaxallowedintervalforstop(m_uiCfgProcessRestartMaxAllowedIntervalHp);
                resp->set_responseid(CMAPIRetCodes::CMAPI_SUCCESS);
                resp->set_requestid(req->requestid());
                break;
            default:
                CLOG_INFO("AvaMgrGetConfiguration() default in %d", m_objSelfCurrentStatus.selfInstanceId);
                resp->set_responseid(CMAPIRetCodes::CMAPI_ERROR);
                resp->set_requestid(req->requestid());
                break;
        }
    }
    CLOG_DEBUG("Config Response being sent is %s",resp->DebugString().c_str());

    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::AvaMgrGetConfiguration() >>>>>>>>>>");

    return 0;
}

int AvailabilityManager::AvaMgrSwitchOverRequest(ComponentActionReq *req, AvaMgrConfigResp *resp) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::AvaMgrSwitchOverRequest() >>>>>>>>>>");
    int ret = 0;
    if ((req != NULL) || (req->IsInitialized())) {
        switch (req->requestid()) {
            case HA_SWITCHOVER:
                CLOG_INFO("AvaMgrSwitchOverRequest() HA_SWITCHOVER in %d", m_objSelfCurrentStatus.selfInstanceId);
                m_isPlannedSwitchOver = true;
                ret = ActivateSwitchover();
                if(ret != SWITCHOVER_SUCCESS)
                {
                    ErrorDetails* err = resp->add_errordetails();
                    err->set_errorcode(ret);
                    err->set_errormsgkey(m_cfgErrorMap[ret]);
                }
                resp->set_requestid(req->requestid());
                resp->set_responseid(CMAPIRetCodes::CMAPI_SUCCESS);
                break;
            default:
                CLOG_INFO("AvaMgrSwitchOverRequest() default in %d", m_objSelfCurrentStatus.selfInstanceId);
                resp->set_responseid(CMAPIRetCodes::CMAPI_ERROR);
                resp->set_requestid(req->requestid());
                break;
        }
    }
    CLOG_DEBUG("Config Response being sent is %s",resp->DebugString().c_str());

    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::AvaMgrSwitchOverRequest() >>>>>>>>>>");

    return 0;
}


Logger::Channel AvailabilityManager::GetLogChannel() {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::GetLogChannel() >>>>>>>>>>");

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::GetLogChannel() <<<<<<<<<<");

    return (this->GetLogChannel());
}

void AvailabilityManager::SetLogChannel(Logger::Channel logChannel) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::SetLogChannel() >>>>>>>>>>");

    if (logChannel == Logger::EACC_CHANNEL_SYSLOG) {
        this->GetLogger().SetLogChannel(m_objSyslogChannel);
    } else if (logChannel == Logger::EACC_CHANNEL_FILE) {
        /*commented to avoid creation empty log file since Avmgr uses syslog by
         * deafult */
        //this->GetLogger().SetLogChannel(m_objFileLogChannel);
    } else {
        this->GetLogger().SetLogChannel(ConsoleLogChannel::Instance());
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SetLogChannel() <<<<<<<<<<");
}

Logger::Level AvailabilityManager::GetLogLevel() {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::GetLogLevel() >>>>>>>>>>");

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::GetLogLevel() <<<<<<<<<<");

    return (this->GetLogger().GetLevel());
}

void AvailabilityManager::SetLogLevel(Logger::Level logLevel) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::GetLogLevel() >>>>>>>>>>");

    this->GetLogger().SetLevel(logLevel, true);

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::GetLogLevel() <<<<<<<<<<");
}

std::string AvailabilityManager::GetLogFileLocation() {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::GetLogFileLocation() >>>>>>>>>>");

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::GetLogFileLocation() <<<<<<<<<<");

    return m_strCfgLogFileLocation;
}

void AvailabilityManager::SetLogFileLocation(std::string strCfgLogFileLocation) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::SetLogFileLocation() >>>>>>>>>>");

    m_strCfgLogFileLocation = strCfgLogFileLocation;

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SetLogFileLocation() <<<<<<<<<<");
}


void AvailabilityManager::ReadConfiguration() {

    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::ReadConfiguration() >>>>>>>>>>");

    char *avamgrConfDir = (char *) ::getenv("AVAMGR_CONFDIR");

    std::string confFile;

    if (avamgrConfDir != NULL)
        confFile = avamgrConfDir;
    else {
        CLOG_ERROR("AVAMGR_CONFDIR environment variable not defined");
        CLOG_NOTICE("Trying to read configuration file from current directory...");
        confFile = ".";
    }

    confFile += "/";
    //confFile += "avamgr.cfg";
    confFile += "avamgr.json";

    //bool isConfigFileOpenSuccessful = false;

    //ConfigReader configReader(confFile.c_str(), isConfigFileOpenSuccessful);

    /*std::map<std::string, std::string>::const_iterator map_iterator;

      if (isConfigFileOpenSuccessful) {
      m_objCfgReaderMap = configReader.getConfigMap();
      } else {
      exit(EXIT_FAILURE);
      }*/
    std::ifstream doc(confFile);
    if(!(m_jsonConfigFileReader.parse(doc,m_jsonRoot)))
    {
        std::cout << "Failed to parse avamgr.json configuration\n"
            <<m_jsonConfigFileReader.getFormattedErrorMessages();
        exit(EXIT_FAILURE);
    }

    SetLogLevel(Logger::EACC_LOG_ERROR);

    PopulateConfig();

    PopulateConfigErrorMap();

    m_objSyslogChannel = new SyslogChannel("AvailabilityManager", (LOG_PID),LOG_LOCAL6);

    //commented to avoid creation of empty log file
    //m_objFileLogChannel = new FileLogChannel("AvailabilityManager.log", m_strCfgLogFileLocation.c_str());

    if (m_uiCfgLogChannel == Logger::EACC_CHANNEL_SYSLOG) {
        this->GetLogger().SetLogChannel(m_objSyslogChannel);
    } else if (m_uiCfgLogChannel == Logger::EACC_CHANNEL_FILE) {
        //this->GetLogger().SetLogChannel(m_objFileLogChannel,true);
    } else {
        this->GetLogger().SetLogChannel(ConsoleLogChannel::Instance());
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::ReadConfiguration() <<<<<<<<<<");
}


void AvailabilityManager::PopulateConfigErrorMap()
{
    m_cfgErrorMap[AVAMGR_SWITCHOVER_ERR_IS_STANDALONE] = "avamgr.switchover.err.is.standalone";
    m_cfgErrorMap[AVAMGR_SWITCHOVER_ERR_STANDBY_NOT_AVAILABLE] = "avamgr.switchover.err.standby.not.available";
}

void AvailabilityManager::PopulateConfig()
{
    Json::Value peerConfig =  m_jsonRoot["Peer-Config"];

    if(!peerConfig.isNull())
    {
        m_uiCfgPingPeriodicityForPeer = abs(peerConfig["Ping-Periodicity"].asInt());
        if (m_uiCfgPingPeriodicityForPeer == 0 || m_uiCfgPingPeriodicityForPeer < CONFIG_PING_PERIODICITY_FOR_PEER) {
            m_uiCfgPingPeriodicityForPeer = CONFIG_PING_PERIODICITY_FOR_PEER;
        }
        CLOG_INFO("Peer-Config->Ping-Periodicity=> %d", m_uiCfgPingPeriodicityForPeer);

        m_uiCfgNumConsecutivePingAckRcvFailuresFromPeer = abs(peerConfig["Ack-Failures"].asInt());
        if (m_uiCfgNumConsecutivePingAckRcvFailuresFromPeer == 0 ) {
            m_uiCfgNumConsecutivePingAckRcvFailuresFromPeer = CONFIG_NUMBER_OF_CONSECUTIVE_PING_ACKNOWLEDGMENT_RECEIVE_FAILURES_FROM_PEER;
        }

        CLOG_INFO("Peer-Config->Ack-Failures=> %d", m_uiCfgNumConsecutivePingAckRcvFailuresFromPeer);
    }
    else {
        if (m_uiCfgPingPeriodicityForPeer == 0) {
            m_uiCfgPingPeriodicityForPeer = CONFIG_PING_PERIODICITY_FOR_PEER;
        }
        CLOG_INFO("Peer-Config->Ping-Periodicity=> %d", m_uiCfgPingPeriodicityForPeer);

        if (m_uiCfgNumConsecutivePingAckRcvFailuresFromPeer == 0) {
            m_uiCfgNumConsecutivePingAckRcvFailuresFromPeer = CONFIG_NUMBER_OF_CONSECUTIVE_PING_ACKNOWLEDGMENT_RECEIVE_FAILURES_FROM_PEER;
        }

        CLOG_INFO("Peer-Config->Ack-Failures=> %d", m_uiCfgNumConsecutivePingAckRcvFailuresFromPeer);
    }


    Json::Value arbitratorConfig =  m_jsonRoot["Arbitrator-Config"];
    if(!arbitratorConfig.isNull())
    {
        m_uiCfgMinPingPeriodicityForArbitrator = abs(arbitratorConfig["Min-Ping-Periodicity"].asInt());
        if (m_uiCfgMinPingPeriodicityForArbitrator == 0) {
            m_uiCfgMinPingPeriodicityForArbitrator = CONFIG_MINIMUM_PING_PERIODICITY_FOR_ARBITRATOR;
        }
        CLOG_INFO("Arbitrator-Config->Min-Ping-Periodicity=> %d", m_uiCfgMinPingPeriodicityForArbitrator);

        m_uiCfgNumConsecutivePingAckRcvFailuresFromArbitrator = abs(arbitratorConfig["Ack-Failures"].asInt());
        if (m_uiCfgNumConsecutivePingAckRcvFailuresFromArbitrator == 0) {
            m_uiCfgNumConsecutivePingAckRcvFailuresFromArbitrator = CONFIG_NUMBER_OF_CONSECUTIVE_PING_ACKNOWLEDGMENT_RECEIVE_FAILURES_FROM_ARBITRATOR;
        }
        CLOG_INFO("Arbitrator-Config->Ack-Failures=> %d", m_uiCfgNumConsecutivePingAckRcvFailuresFromArbitrator);
        m_strCfgArbitratorIpAddress = arbitratorConfig["Gateway-IP-Address"].asString();
        if(m_strCfgArbitratorIpAddress.empty())
        {
            CLOG_CRITICAL("Arbitrator-Config->Gateway-IP-Address is missing... Exiting");
            exit(EXIT_FAILURE);
        }
    } else {
        CLOG_CRITICAL("Arbitrator-Config->Gateway-IP-Address is missing... Exiting");
        exit(EXIT_FAILURE);
    }

    Json::Value logConfig =  m_jsonRoot["Log-Config"];
    if(!logConfig.isNull())
    {

        m_uiCfgLogChannel = abs(logConfig["Log-Channel"].asInt());

        /* To Do  ensure that even if we configure log channel as file or
         * console, by default syslog will be taken as log channel */
        if (m_uiCfgLogChannel == 1)
        {
            m_uiCfgLogChannel = Logger::EACC_CHANNEL_FILE;
        }
        else
        {
            m_uiCfgLogChannel = Logger::EACC_CHANNEL_SYSLOG;
        }

        CLOG_INFO("Log-Config->Log-Channel=> %d", m_uiCfgLogChannel);

        m_strCfgLogFileLocation = logConfig["Log-File-Location"].asString();
        if(m_strCfgLogFileLocation.empty())
        {
            CLOG_INFO("Log-Config->Log-File-Location is missing... Exiting");
            exit(EXIT_FAILURE);
        }
        CLOG_INFO("Log-Config->Log-File-Location=> %s", m_strCfgLogFileLocation.c_str());
    } else {
        CLOG_INFO("Log-Config->Log-File-Location is missing... Exiting");
        exit(EXIT_FAILURE);
    }

    if(!m_jsonRoot["Interface-Config"]["ARP-Mechanism"].isNull())
    {
        m_uiArpMechanism  = abs(m_jsonRoot["Interface-Config"]["ARP-Mechanism"].asInt());
    } else
    {
        m_uiArpMechanism = ARP_MECHANISM_ARPTABLES;
    }

    Json::Value interfaceConfig =  m_jsonRoot["Interface-Config"]["Interfaces"];

    if(!interfaceConfig.isNull())
    {
        for( Json::ValueIterator itr = interfaceConfig.begin() ; itr != interfaceConfig.end() ; itr++ ) {
            struct InterfaceAttributes ifattrib;

            if (!((*itr)["Interface-Type"]).isNull())
            {
                ifattrib.interfaceType = (InterfaceType) (*itr)["Interface-Type"].asInt();
            }
            if( ifattrib.interfaceType != TRAFFIC && ifattrib.interfaceType != MANAGEMENT )
            {

                CLOG_CRITICAL("Invalid Interface-Type... Exiting");
                exit(EXIT_FAILURE);
            }
            ifattrib.failureLeadsToSwitchOver = (*itr)["Failure-Triggers-Switchover"].asBool();


            Json::Value ipAddresses = (*itr)["IP-Addresses"];
            for( Json::ValueIterator itr1 = ipAddresses.begin();itr1 != ipAddresses.end(); itr1++)
            {
                ifattrib.ipAddresses.push_back((*itr1)["Virtual-IP-Address"].asString());
                if(!((*itr1)["Configure-Route"].isNull()))
                {
                    ifattrib.addRoute = false;
                    if(!((*itr1)["Configure-Route"].asString()).compare("yes"))
                    {
                        ifattrib.addRoute = true;
                        Json::Value routes= (*itr1)["Routes"];
                        Json::ValueIterator itr2 = routes.begin();
                        for( ; itr2 != routes.end(); itr2++)
                        {
                            struct Route route;
                            route.metric = 0;
                            route.destination= (*itr2)["Destination"].asString();
                            route.gateway = (*itr2)["Gateway"].asString();
                            if(!(*itr2)["metric"].isNull())
                            {
                                route.metric = (*itr2)["metric"].asInt();
                            }
                            if(!(*itr2)["tableId"].isNull())
                            {
                                route.tableId= (*itr2)["tableId"].asString();
                            }
                            ifattrib.routes.push_back(route);
                        }
                        //break from here so that only 1 IP Address is allowed since
                        //route has to be added on this interface.
                        break;
                    }
                }
            }

            ifattrib.bondingOptionNumGratArp = GetGratArpCountAttribOfInterface((*itr)["Interface-Name"].asCString());
            ifattrib.arpIgnoreOption =GetArpIgnoreValueOfInterface((*itr)["Interface-Name"].asCString());
            m_objInterfaceMap[(*itr)["Interface-Name"].asString()] = ifattrib;
        }
    }
    else
    {
        CLOG_CRITICAL("Interface configuration is missing... Exiting");
        exit(EXIT_FAILURE);
    }

    ProcessIpAddressCidr();

    Json::Value interfaceGroup = m_jsonRoot["Interface-Config"]["Interfaces-Group"];

    if(!interfaceGroup.isNull())
    {
        for( Json::ValueIterator itr = interfaceGroup.begin() ; itr !=
                interfaceGroup.end() ; itr++ )
        {
            InterfaceGroupAttributes ifGrpAttrb;
            ifGrpAttrb.failureLeadsToSwitchOver = (*itr)["Failure-Triggers-Switchover"].asBool();
            Json::Value interfaces = (*itr)["Interfaces"];
            for( Json::ValueIterator itr1 = interfaces.begin() ; itr1 !=
                    interfaces.end() ; itr1++ )
            {
                ifGrpAttrb.interfaceName.push_back((*itr1)["Interface-Name"].asString());
            }
            m_objInterfaceGroupMap[(*itr)["Interface-Group-Name"].asString()] = ifGrpAttrb;
        }
    }

    if(m_objInterfaceMap.size() == 0 )
    {
        CLOG_CRITICAL("Interface configuration is missing... Exiting");
        exit(EXIT_FAILURE);
    }


    Json::Value procCommonConfig =  m_jsonRoot["Process-Common-Config" ];
    if(!procCommonConfig.isNull())
    {
        m_uiCfgProcessRestartMaxAllowedInterval = abs(procCommonConfig["Restart-Max-Interval"].asInt());
        if (m_uiCfgProcessRestartMaxAllowedInterval == 0) {
            m_uiCfgProcessRestartMaxAllowedInterval = CONFIG_PROCESS_RESTART_MAXIMUM_ALLOWED_INTERVAL;
        }
        CLOG_INFO("Process-Common-Config->Restart-Max-Interval=> %d", m_uiCfgProcessRestartMaxAllowedInterval);
        m_uiCfgProcessRestartMaxAllowedCount = abs(procCommonConfig["Restart-Max-Count"].asInt());
        if (m_uiCfgProcessRestartMaxAllowedCount == 0) {
            m_uiCfgProcessRestartMaxAllowedCount = CONFIG_PROCESS_RESTART_MAXIMUM_ALLOWED_COUNT;
        }

        CLOG_INFO("Process-Common-Config->Restart-Max-Count=> %d", m_uiCfgProcessRestartMaxAllowedCount);

        m_uiCfgProcessRestartMaxAllowedIntervalHp = abs(procCommonConfig["Restart-Max-Interval-For-Stop"].asInt());
        if (m_uiCfgProcessRestartMaxAllowedIntervalHp == 0) {
            m_uiCfgProcessRestartMaxAllowedIntervalHp = CONFIG_PROCESS_RESTART_MAXIMUM_ALLOWED_INTERVAL_HP;
        }

        CLOG_INFO("Process-Common-Config->Restart-Max-Interval-For-Stop=> %d", m_uiCfgProcessRestartMaxAllowedIntervalHp);

        m_uiCfgProcessRestartMaxAllowedCountHp = abs(procCommonConfig["Restart-Max-Count-For-Stop"].asInt());
        if (m_uiCfgProcessRestartMaxAllowedCountHp == 0) {
            m_uiCfgProcessRestartMaxAllowedCountHp = CONFIG_PROCESS_RESTART_MAXIMUM_ALLOWED_COUNT_HP;
        }

        CLOG_INFO("Process-Common-Config->Restart-Max-Count-For-Stop=> %d", m_uiCfgProcessRestartMaxAllowedCountHp);

        m_bIsHeartbeatEnabled = procCommonConfig["Process-HeartBeat"].asBool();
        CLOG_INFO("Process-Common-Config->Process-HeartBeat=> %d", m_bIsHeartbeatEnabled);

        m_uiCfgMaxProcessHBAckFailures = abs(procCommonConfig["Max-HeartBeat-Ack-Failures"].asInt());
        if (m_uiCfgMaxProcessHBAckFailures == 0 || m_uiCfgMaxProcessHBAckFailures < CONFIG_NO_HB_ACK_FAILURES) {
            m_uiCfgMaxProcessHBAckFailures = CONFIG_NO_HB_ACK_FAILURES;
        }

        CLOG_INFO("Process-Common-Config->Max-HeartBeat-Ack-Failures=> %d", m_uiCfgMaxProcessHBAckFailures);

        m_uiCfgMaxTimeToWaitBeforeSendingSigkill = abs(procCommonConfig["Max-Time-To-Wait-Before-Sending-SIGKILL"].asInt());
        if (m_uiCfgMaxTimeToWaitBeforeSendingSigkill == 0 || m_uiCfgMaxTimeToWaitBeforeSendingSigkill < CONFIG_MAX_TIME_TO_WAIT_BEFORE_SENDING_SIGKILL) {
            m_uiCfgMaxTimeToWaitBeforeSendingSigkill = CONFIG_MAX_TIME_TO_WAIT_BEFORE_SENDING_SIGKILL;
        }

        CLOG_INFO("Process-Common-Config->Max-Time-To-Wait-Before-Sending-SIGKILL => %d", m_uiCfgMaxTimeToWaitBeforeSendingSigkill);

    }else
    {
        m_uiCfgProcessRestartMaxAllowedInterval = CONFIG_PROCESS_RESTART_MAXIMUM_ALLOWED_INTERVAL;
        CLOG_INFO("Process-Common-Config->Restart-Max-Interval=> %d (default)", m_uiCfgProcessRestartMaxAllowedInterval);
        m_uiCfgProcessRestartMaxAllowedCount = CONFIG_PROCESS_RESTART_MAXIMUM_ALLOWED_COUNT;
        CLOG_INFO("Process-Common-Config->Restart-Max-Count=> %d (default)", m_uiCfgProcessRestartMaxAllowedCount);
        m_uiCfgMaxProcessHBAckFailures = CONFIG_NO_HB_ACK_FAILURES;
        CLOG_INFO("Process-Common-Config->Max-HeartBeat-Ack-Failures=> %d (default)", m_uiCfgMaxProcessHBAckFailures);
        m_uiCfgMaxTimeToWaitBeforeSendingSigkill = CONFIG_MAX_TIME_TO_WAIT_BEFORE_SENDING_SIGKILL;
        CLOG_INFO("Process-Common-Config->Max-Time-To-Wait-Before-Sending-SIGKILL => %d (default)", m_uiCfgMaxTimeToWaitBeforeSendingSigkill);

    }
    Json::Value processConfig =  m_jsonRoot["Process-Config"]["Processes"];
    if(!processConfig.isNull())
    {
        for( Json::ValueIterator itr = processConfig.begin() ; itr != processConfig.end() ; itr++ ) {

            ProcessAttributes processAttributes;
            processAttributes.processName = (*itr)["Process-Name-With-Args"].asString();
            processAttributes.priority = abs((*itr)["Priority"].asInt());
            processAttributes.pauseHeartBeat = true;
            processAttributes.pid = 0;

            processAttributes.processRestartCounterForShutdownApplication = 0;
            processAttributes.processRestartCounter = 0;
            processAttributes.sigtermTimerHandle = -1;
            processAttributes.sigkillTimerHandle = -1;
            processAttributes.sigkillTimerCount = 0;

            CLOG_INFO("Initializing component status to COMPONENT_STATUS_STOPPED");
            processAttributes.currentComponentStatus= COMPONENT_STATUS_STOPPED;
            m_objProcessMap[abs((*itr)["Component-Id"].asInt())] = processAttributes;
            //Populate the componentId vector.
            m_objComponentIdVector.push_back(abs((*itr)["Component-Id"].asInt()));
        }
    } else {
        CLOG_CRITICAL("Process-Config is missing... Exiting");
        exit(EXIT_FAILURE);
    }
    if(m_objProcessMap.size() == 0 )
    {
        CLOG_CRITICAL("Process-Config->Processes is missing... Exiting");
        exit(EXIT_FAILURE);
    }
    m_uiCfgMaxProcesses = m_objProcessMap.size();

    //Replication Config
    Json::Value repConfig = m_jsonRoot["Replication-Config"];
    m_replicationConfig.clusterConnRetryFailure = repConfig["Cluster-Connectivity-Failure-Count"].asInt();
    m_replicationConfig.purgeDataInterval = repConfig["Purge-Data-Interval"].asInt();

}

void AvailabilityManager::ProcessIpAddressCidr() {

    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::SplitIpAddressCidr() >>>>>>>>>>");

    char ipAddress[43];
    unsigned char routingPrefix;

    char *ptr;

    char ipAddressCidrNotation[47];

    size_t foundBackSlash;
    uint8_t i;

    std::map<std::string,InterfaceAttributes>::iterator it;
    for(it = m_objInterfaceMap.begin();it != m_objInterfaceMap.end() ;it++)
    {
        for(i = 0; i < it->second.ipAddresses.size(); i ++)
        {

            foundBackSlash = it->second.ipAddresses.at(i).find('/');

            if (foundBackSlash == std::string::npos) {
                CLOG_ERROR("IP address %s NOT in CIDR format. Exiting", it->second.ipAddresses.at(i).c_str());

                exit(EXIT_FAILURE);
            }

            memset(ipAddressCidrNotation, 0, sizeof (ipAddressCidrNotation));
            strncpy(ipAddressCidrNotation, it->second.ipAddresses.at(i).c_str(), sizeof (ipAddressCidrNotation));

            ptr = NULL;

            memset(ipAddress, 0, sizeof (ipAddress));
            char *token = strtok_r(ipAddressCidrNotation, "/", &ptr);
            strncpy(ipAddress, token, sizeof (ipAddress));

            token = strtok_r(NULL, "/", &ptr);
            routingPrefix = atoi(token);

            it->second.ipAddresses.at(i) = (std::string)ipAddress;

            m_objVirtualIpAddressEthernetInterfaceMap.insert(std::pair<std::string, std::string > (it->second.ipAddresses.at(i),
                        it->first));

            m_objVirtualIpAddressRoutingPrefixMap.insert(std::pair<std::string, unsigned char > (it->second.ipAddresses.at(i),
                        routingPrefix));

            m_objEthernetInterfaceSet.insert(it->first);

            CLOG_NOTICE("Virtual IP address %s has routing prefix %d",  it->second.ipAddresses.at(i).c_str(),
                    routingPrefix);
        }
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SplitIpAddressCidr() <<<<<<<<<<");
}


bool AvailabilityManager::isArbitratorEnabled()
{
    //Short-Circuiting Arbitrator Functinoality when localhost IP is configured.
    if((m_strCfgArbitratorIpAddress.compare("localhost") == 0) ||
            (m_strCfgArbitratorIpAddress.compare("127.0.0.1") == 0) )
    {
        return false;
    }
    else
    {
        return true;
    }
}

int AvailabilityManager::FetchClusterInfo(ClusterInfoReq *req, ClusterInfoResp *resp)
{
    resp->set_responseid(CMAPI_SUCCESS);
    CLOG_DEBUG(">>>>>>>>>> Entered %s >>>>>>>>>>",__FUNCTION__);
    switch(m_iInstanceStartMode)
    {


        case ACTIVE_COLD_STANDBY_MODE:
        case ACTIVE_STANDBY_MODE:
        case ACTIVE_HOT_STANDBY_MODE:
            //Fall through for above cases.
            {
                NodeInfo *pNodeInfo = resp->add_nodesinfo();
                pNodeInfo->set_hostname(m_objPeerCurrentStatus.peerHostname);
                if(m_objPeerCurrentStatus.peerInstanceAvailabilityStatus == INDETERMINATE)
                {
                    pNodeInfo->set_nodestate(NodeInfo_states_INDETERMINATE);
                }
                else if(m_objPeerCurrentStatus.peerInstanceAvailabilityStatus == STANDBY)
                {
                    pNodeInfo->set_nodestate(NodeInfo_states_STANDBY);
                }
                else if(m_objPeerCurrentStatus.peerInstanceAvailabilityStatus == ACTIVE)
                {
                    pNodeInfo->set_nodestate(NodeInfo_states_ACTIVE);
                }
                pNodeInfo->set_lastgoactivetime(m_objPeerCurrentStatus.peerLastGoActiveTime.tv_sec);
            }
        case STANDALONE_MODE:
            //Fall through for above cases
            {
                NodeInfo *pNodeInfo = resp->add_nodesinfo();
                pNodeInfo->set_hostname(m_objSelfCurrentStatus.selfHostname);
                if(m_objSelfCurrentStatus.selfInstanceAvailabilityStatus == INDETERMINATE)
                {
                    pNodeInfo->set_nodestate(NodeInfo_states_INDETERMINATE);
                }
                else if(m_objSelfCurrentStatus.selfInstanceAvailabilityStatus == STANDBY)
                {
                    pNodeInfo->set_nodestate(NodeInfo_states_STANDBY);
                }
                else if(m_objSelfCurrentStatus.selfInstanceAvailabilityStatus == ACTIVE)
                {
                    pNodeInfo->set_nodestate(NodeInfo_states_ACTIVE);
                }
                pNodeInfo->set_lastgoactivetime(m_objSelfCurrentStatus.selfLastGoActiveTime.tv_sec);

                break;
            }
        default:
            break;
    }

    CLOG_DEBUG("ClusterInfoResp %s ",resp->DebugString().c_str());
    CLOG_DEBUG("<<<<<<<<<< Exiting %s <<<<<<<<<<",__FUNCTION__);
    return 0;
}

string AvailabilityManager::GetFileNameFromPath(string path, string &filename)
{

    CLOG_DEBUG("<<<<<<<<<< Entering %s <<<<<<<<<<",__FUNCTION__);
    size_t pos;

    pos = path.find_first_of(" ");
    if(pos != std::string::npos)
        filename.assign(path.begin(),path.begin() + pos);
    else
        filename = path;


    pos = filename.find_last_of("/");
    if(pos != std::string::npos)
        filename.assign(filename.begin() + pos + 1, filename.end());

    CLOG_DEBUG("<<<<<<<<<< Exiting %s <<<<<<<<<<",__FUNCTION__);
    return filename;
}

int AvailabilityManager::FetchProcessState(ProcessStateReq *req, ProcessStateResp *resp)
{
    CLOG_DEBUG("<<<<<<<<<< Entering %s <<<<<<<<<<",__FUNCTION__);
    resp->set_responseid(CMAPI_SUCCESS);
    std::unordered_map<uint16_t, ProcessAttributes>::iterator it;
    resp->set_hostname(m_objSelfCurrentStatus.selfHostname);
    for(it = m_objProcessMap.begin();it != m_objProcessMap.end(); it++)
    {
        std::string sFilename;
        ProcessState *pProcessState = resp->add_processstateinfo();
        pProcessState->set_processname(GetFileNameFromPath(it->second.processName,sFilename));
        if(it->second.currentComponentStatus == COMPONENT_STATUS_INDETERMINATE)
        {
            pProcessState->set_processstate(ProcessState_state_INDETERMINATE);
        }
        else if(it->second.currentComponentStatus == COMPONENT_STATUS_INITIALIZED)
        {
            pProcessState->set_processstate(ProcessState_state_INITIALIZED);
        }
    }
    CLOG_DEBUG("ProcessStateResp = %s",resp->DebugString().c_str());
    CLOG_DEBUG("<<<<<<<<<< Exiting %s <<<<<<<<<<",__FUNCTION__);
    return 0;
}
