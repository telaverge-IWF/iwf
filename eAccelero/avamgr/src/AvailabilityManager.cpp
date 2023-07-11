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
#include "ClusterManager.h"
#include "CouchbaseClusterManager.h"
#include "AvailabilityManager.h"
#include "ManagementInterface.h"
#include "Pinger.h"


const char DREVer[]=DRE_VER;
using namespace eAccelero;

bool AvailabilityManager::stopReplication = false;


static void Daemonize(void) {
    pid_t pid, sid;

    // Already a daemon
    if (getppid() == 1)
        return;

    // Fork off the parent process
    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    // If we got a good PID, then we can exit the parent process
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    /* At this point we are executing as the child process */

    // Change the file mode mask
    umask(0);

    // Create a new SID for the child process
    sid = setsid();

    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Change the current working directory.  This prevents the current
       directory from being locked; hence not being able to remove it. */
    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }
}

AvailabilityManager::AvailabilityManager()
    : MeSSComponent("AvailabilityManager", COMP_AVAILABILITY_MANAGER),
    m_bAllComponentsInitialized(false),
    m_objIcmpSocketHandlerId(0),
    m_objPeriodicTimerId(0),
    m_isPeerAvailable(false),
    m_OneTimePeerActiveBroadCast(false),
    m_bIsNeedToAssignIpAddressToInterface(false),
    m_bIsHeartbeatEnabled(true),
    m_isPlannedSwitchOver(false),
    m_uiArpMechanism(ARP_MECHANISM_ARP_ANNOUNCE),
    m_uiWaitCountForIcmpPingFromPeer(0),
    m_bComponentsRunning(false),
    m_bSuppressHigPriorityProcessAlarm(false){
	m_uiCfgMaxTimeToWaitAfterSendingSigkill = TIME_TO_WAIT_AFTER_SIGKILL;
        CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::AvailabilityManager() >>>>>>>>>>");

        // Read component configuration from a configuration file
        // TODO: In future, component configuration will be read from a database
        ReadConfiguration();

#ifdef FOR_IWF
        string errlog = m_strCfgLogFileLocation + "/iwf_console_err.log";
        string dbglog = m_strCfgLogFileLocation + "/iwf_console_out.log";
#else
        string errlog = m_strCfgLogFileLocation + "/dre_console_err.log";
        string dbglog = m_strCfgLogFileLocation + "/dre_console_out.log";
#endif
        // Redirect standard files (input) to /dev/null
        freopen("/dev/null", "r", stdin);
        // Redirect standard files (output and error) to respective log files
        freopen(dbglog.c_str(), "w", stdout);
        freopen(errlog.c_str(), "w", stderr);

        // Register callback handler for processing HB ack from components
        // HeartBeat uses MeSS
        Stub::AvaMgrProcessStatusInterfaceRespCbk::RegisterAvaMgrProcessStatusInterfaceRespHandler();

        // Register callback handler for processing ping ack from peer (Availability Manager)
        // Peer ping processing uses MeSS
        Stub::AvaMgrPeerStatusInterfaceRespCbk::RegisterAvaMgrPeerStatusInterfaceRespHandler();

        //Initialize Alarms Library
        m_avaMgrAlarm = new AvailabilityManagerAlarms(MESS_MIN_STANDBY_INSTANCE,COMP_AVAILABILITY_MANAGER);


        // Initialize ICMP Ping
        m_objPinger = new Pinger(this);
        CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::AvailabilityManager() <<<<<<<<<<");
    }

AvailabilityManager::~AvailabilityManager() {

    if(m_avaMgrAlarm != NULL)
    {
        delete m_avaMgrAlarm;
        m_avaMgrAlarm = NULL;
    }

    if(m_objPinger != NULL)
    {
        delete m_objPinger;
        m_objPinger = NULL;
    }

}

void AvailabilityManager::Initialize() {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::Initialize() >>>>>>>>>>");

    MeSSComponent::Initialize();
    //m_objTopologyService.Initialize();

    m_iInstanceStartMode = atoi(((std::string)m_cmdArgs.mode).c_str());

    m_bProcessTerminationInProgress = false;

    m_bSwitchoverInProgress = false;

    m_isRebalanceStuck = false;
    // Instantiate the Management Interface with self
    m_objMgmtIface = new ManagementInterface(this);

    // Add handler for TIPC topology service events, so that on TIPC_WITHDRAWN and TIPC_SUBSCR_TIMEOUT events,
    // the service can be re-subscribed
    // This is to ensure that the TIPC topology service is 'always' available
    // This is intended as a line of defense

    TopologyEvent nodeEvent(TIPC_TOP_SRV, 1, TIPC_MAX_INST);
    MeSS::MeSSObj().TopSvc().Subscribe(
            EventSlot<TopologyEvent, AvailabilityManager > (this, &AvailabilityManager::OnNodeEvent),
            nodeEvent);


    // Add handler for processing the SIGCHLD signal, raised when a process launched and monitored by Availability Manager dies
    m_objSigChldHandlerId = this->GetDispatcher()->AddEventHandler(
            EventSlot<SignalEvent, AvailabilityManager > (this, &AvailabilityManager::OnSigChld),
            SignalEvent(SIGCHLD));

    // STL set containing the unique ethernet interfaces used for Diameter traffic and Management client communication
    std::set<std::string>::const_iterator iter;
    for (iter = m_objEthernetInterfaceSet.begin(); iter != m_objEthernetInterfaceSet.end(); iter++) {
        CLOG_NOTICE("Using virtual interface %s", (*iter).c_str());
    }

    // Initialize own data structure for peer communication (uses MeSS)
    m_objSelfCurrentStatus.selfSequenceId = PEER_INITIAL_SEQUENCE_ID;
    m_objSelfCurrentStatus.selfInstanceId = MeSSObj().Self().instance;
    m_objSelfCurrentStatus.selfInstanceAvailabilityStatus = INDETERMINATE;
    gethostname(m_objSelfCurrentStatus.selfHostname, HOSTNAME_LEN);
    m_objSelfCurrentStatus.selfCbNodeStatus = WARMUP;

    // Invalidating the Last Go Active Time as Tue, 19 Jan 2038 00:00:00 GMT
    // This value will also work for 32-bit
    m_objSelfCurrentStatus.selfLastGoActiveTime.tv_sec = 2147472000;
    m_objSelfCurrentStatus.selfLastGoActiveTime.tv_usec = 0;

    m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational = true;

    // Put host name in an alphabetically sorted set
    // Alphabetical ordering is important to resolve a race condition, when both Availability Manager components become STANDBY
    m_objHostnameSet.insert(std::string(m_objSelfCurrentStatus.selfHostname));

    CLOG_INFO("Self status initialized with sequence id %u, instance id %u, status %d",
            m_objSelfCurrentStatus.selfSequenceId,
            m_objSelfCurrentStatus.selfInstanceId,
            m_objSelfCurrentStatus.selfInstanceAvailabilityStatus);

    // Initialize peer data structure, which the peer populates and sends in the MeSS callback
    m_objPeerCurrentStatus.peerSequenceId = PEER_INITIAL_SEQUENCE_ID;
    m_objPeerCurrentStatus.peerInstanceId = PEER_INVALID_INSTANCE_ID;
    m_objPeerCurrentStatus.peerInstanceAvailabilityStatus = INDETERMINATE;
    strncpy(m_objPeerCurrentStatus.peerHostname, "\0", HOSTNAME_LEN);
    m_objPeerCurrentStatus.peerCbNodeStatus = WARMUP;

    // Invalidating the Last Go Active Time as Tue, 19 Jan 2038 00:00:00 GMT
    // This value will also work for 32-bit
    m_objPeerCurrentStatus.peerLastGoActiveTime.tv_sec = 2147472000;
    m_objPeerCurrentStatus.peerLastGoActiveTime.tv_usec = 0;

    m_objPeerCurrentStatus.peerIsAnyEthernetInterfaceNotOperational = true;

    CLOG_INFO("Peer status initialized with sequence id %u, instance id %u, status %d",
            m_objPeerCurrentStatus.peerSequenceId,
            m_objPeerCurrentStatus.peerInstanceId,
            m_objPeerCurrentStatus.peerInstanceAvailabilityStatus);

    m_uiTipcSequenceId = 0;




    // Register a recurring timer expiry handler
    // An IMPORTANT event handler, which keeps the peer communication going
    m_objRecurringTimerId = this->GetDispatcher()->AddEventHandler(
            EventSlot<TimerEvent, AvailabilityManager > (this,
                &AvailabilityManager::OnRecurringTimerExpiry),
            TimerEvent(m_uiCfgPingPeriodicityForPeer));

    m_uiOwnTipcNodeId = GetSelfTipcNodeId();

    CLOG_INFO("Self TIPC node id is %u", m_uiOwnTipcNodeId);

    // Populate the Component Id (STL)vector
    // This is used to identify the MeSS endpoint, which the Availability Manager sends become-STANDBY and become-ACTIVE commands
#ifdef STANDALONE_TEST

    m_objComponentIdVector.push_back(COMP_CLI_PROC_DUMMY);
    m_objComponentIdVector.push_back(COMP_CONFIG_MANAGER_DUMMY);
    m_objComponentIdVector.push_back(COMP_DRE_APP_DUMMY);

    //m_objComponentIdAvailabilityStatusMap.insert(std::pair<uint16_t, InstanceAvailabilityStatus > (COMP_REPLICATION_MANAGER_DUMMY, InstanceAvailabilityStatus::INDETERMINATE));
    m_objComponentIdAvailabilityStatusMap.insert(std::pair<uint16_t, InstanceAvailabilityStatus >
            (COMP_CLI_PROC_DUMMY, InstanceAvailabilityStatus::INDETERMINATE));
    m_objComponentIdAvailabilityStatusMap.insert(std::pair<uint16_t, InstanceAvailabilityStatus >
            (COMP_CONFIG_MANAGER_DUMMY, InstanceAvailabilityStatus::INDETERMINATE));
    m_objComponentIdAvailabilityStatusMap.insert(std::pair<uint16_t, InstanceAvailabilityStatus >
            (COMP_DRE_APP_DUMMY, InstanceAvailabilityStatus::INDETERMINATE));
#else

    std::unordered_map<uint16_t, ProcessAttributes>::iterator it;
    //Populate the Component HeartBeat info map.
    // Populate the Component Id (STL)vector
    HeartBeatInfo hb;
    hb.HBMissCount = 0;
    for(it = m_objProcessMap.begin();it != m_objProcessMap.end(); it++)
    {
        m_objComponentIdAvailabilityStatusMap.insert(std::pair<uint16_t, InstanceAvailabilityStatus>
                (it->first,InstanceAvailabilityStatus::STANDBY));

        m_objComponentIdHBInfoMap.insert(std::pair<uint16_t,HeartBeatInfo>(it->first,hb));

        // Subscribe for Topology Events for all components monitored by AM.
        TopologyEvent compEvent(it->first);
        MeSS::MeSSObj().TopSvc().Subscribe( EventSlot<TopologyEvent, AvailabilityManager>
                (this,&AvailabilityManager::OnComponentEvent),compEvent);
    }

#endif
    if(m_iInstanceStartMode == ACTIVE_HOT_STANDBY_MODE)
    {
        //Start the Cluster Management Thread
        Node initNode;
        m_clMgr = new CouchbaseClusterManager(m_replicationConfig);
        CLOG_DEBUG("Starting Cluster Thread");
        m_clMgr->Initialize(initNode);
        cmThread = new eAccelero::Thread("Cluster Management Thread");
        cmThread->Start(m_clMgr);
        struct timeval tv;
        gettimeofday(&tv,NULL);
        //calculate the time for next meta data purge in the couchbase cluster
        m_secondsToPurgeUnwantedData.tv_sec=tv.tv_sec + m_replicationConfig.purgeDataInterval;
    }

    m_utilityThreadrunning = true;

    m_utilityThread = new eAccelero::Thread("Utility Thread");
    m_utilityThread->Start(this,&AvailabilityManager::UtilityThread);

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::Initialize() <<<<<<<<<<");
}

// Called by MeSS during termination

void AvailabilityManager::Terminate() {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::Terminate() >>>>>>>>>>");

    m_bProcessTerminationInProgress = true;

    if(m_iInstanceStartMode == ACTIVE_HOT_STANDBY_MODE)
    {
        m_clMgr->Terminate();
        delete cmThread;
    }

    // Remove the ARP tables rule to drop all the ARP requests in and out
    //AddArpTableRulesForTrafficVIPs(false);
    //Flush arptables.
    FlushArpTables();


    //Raise an alarm to indicate Avamgr going down.
    m_avaMgrAlarm->RaiseDREDownAlarm(m_objSelfCurrentStatus.selfHostname);

    //Remove Event handlers since we are going down.
    this->GetDispatcher()->RemoveEventHandler(TIMER_EVENT_TYPE, m_objRecurringTimerId);
    this->GetDispatcher()->RemoveEventHandler(SIGNAL_EVENT_TYPE,m_objSigChldHandlerId);

    //Delete all routes that have been added.
    std::map<std::string,InterfaceAttributes>::iterator interfaceMapIter;
    for (interfaceMapIter = m_objInterfaceMap.begin();
            interfaceMapIter != m_objInterfaceMap.end(); interfaceMapIter++)
    {
        if(interfaceMapIter->second.ipAddresses.size() == 1)
        {
            //Delete route on interface.
            PerformRouteOpOnInterface((interfaceMapIter->first).c_str(),
                    (interfaceMapIter->second.ipAddresses[0]).c_str()
                    ,DELETE);
        }
    }
    // We assigned the Virtual IP addresses (VIPs) to the various ethernet interfaces
    // Hence, we must unassign them.
    // Note the last parameter in AssignIpAddressToInterface()
    std::map<std::string, std::string>::const_iterator mapIter;
    for (mapIter = m_objVirtualIpAddressEthernetInterfaceMap.begin();
            mapIter != m_objVirtualIpAddressEthernetInterfaceMap.end(); mapIter++) {
        AssignIpAddressToInterface((*mapIter).second.c_str(),
                (*mapIter).first.c_str(),
                m_objVirtualIpAddressRoutingPrefixMap.find((*mapIter).first)->second,
                false);
    }

    // Ensure that ARP is enabled on the various ethernet interfaces
    //std::set<std::string>::const_iterator setIter;
    for (interfaceMapIter = m_objInterfaceMap.begin(); interfaceMapIter != m_objInterfaceMap.end(); interfaceMapIter++) {
        if(interfaceMapIter->second.interfaceType == TRAFFIC)
        {
            SetArpAttribOnInterface((interfaceMapIter->first).c_str(), true);
        }
        SetGratArpCountAttribOnInterface((interfaceMapIter->second).bondingOptionNumGratArp,(interfaceMapIter->first).c_str());
    }



    // Kill all child processes (other MeSS components)
    TerminateAllComponents();
    //m_objTopologyService.Terminate();

    m_utilityThreadrunning = false;
    m_utilityThread->Join();

    MeSSComponent::Terminate();

    if (m_objSyslogChannel != NULL) {
        delete m_objSyslogChannel;
        m_objSyslogChannel = NULL;
    }

    if (m_objFileLogChannel != NULL) {
        delete m_objFileLogChannel;
        m_objFileLogChannel = NULL;
    }

    if (m_objMgmtIface != NULL) {
        delete m_objMgmtIface;
        m_objMgmtIface = NULL;
    }

}

int AvailabilityManager::ActivateSwitchover() {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::ActivateSwitcover() >>>>>>>>>>");

    //Instance started in Standalone mode.
    if(m_iInstanceStartMode == STANDALONE_MODE)
    {
        CLOG_INFO("Not Switching over because instance is started in standalone Mode");
        return AVAMGR_SWITCHOVER_ERR_IS_STANDALONE;
    }

    if (m_objSelfCurrentStatus.selfInstanceAvailabilityStatus == InstanceAvailabilityStatus::ACTIVE ) {

        //Check if Peer (Standby Node) is not Available.
        if(m_objPeerCurrentStatus.peerInstanceId == PEER_INVALID_INSTANCE_ID)
        {
            CLOG_INFO("Standby Not Available.Hence, remaining Active");
            m_isPlannedSwitchOver = false;
            return AVAMGR_SWITCHOVER_ERR_STANDBY_NOT_AVAILABLE;
        }

        if(m_isPlannedSwitchOver)
        {
            CLOG_INFO("Raising a PlannedSwitchoverInitiatedAlarm Alarm");
            m_avaMgrAlarm->PlannedSwitchoverInitiatedAlarm(std::string(m_objSelfCurrentStatus.selfHostname));
        }
        else
        {
            CLOG_INFO("Raising an UnPlannedSwitchoverInitiatedAlarm Alarm");
            m_avaMgrAlarm->UnplannedSwitchoverInitiatedAlarm(std::string(m_objSelfCurrentStatus.selfHostname));
        }

        CLOG_NOTICE("Switching over to STANDBY");

        MakeStandbyInstance(true);

        m_bSwitchoverInProgress = true;

        m_objSwitchoverTimerId = this->GetDispatcher()->AddEventHandler(
                EventSlot<TimerEvent, AvailabilityManager > (this, &AvailabilityManager::OnSwitchoverCompleteEvent),
                TimerEvent(2 * m_uiCfgNumConsecutivePingAckRcvFailuresFromPeer * m_uiCfgPingPeriodicityForPeer));

        CLOG_NOTICE("Waiting for %d milli-seconds for switchover to stabilize",
                (2 * m_uiCfgNumConsecutivePingAckRcvFailuresFromPeer * m_uiCfgPingPeriodicityForPeer));

    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::ActivateSwitcover() <<<<<<<<<<");
    return SWITCHOVER_SUCCESS;
}


void AvailabilityManager::RegisterMethods() {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::RegisterMethods() >>>>>>>>>>");

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::RegisterMethods() <<<<<<<<<<");
}

int AvailabilityManager::OnNodeEvent(TopologyEvent &event) {

    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::OnNodeEvent() >>>>>>>>>>");

    CLOG_NOTICE("TIPC node event received is %d", event.NotificationType());

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::OnNodeEvent() <<<<<<<<<<");

    return 0;
}


int AvailabilityManager::OnComponentEvent(TopologyEvent &event)
{
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::OnComponentEvent() >>>>>>>>>>");

    uint16_t componentId = event.Subscription().Type();
    uint8_t notificationType = event.NotificationType();
    TIPCAddr nodeAddr = event.Port();

    //Check if Topology event received is from Self Node.
    uint32_t selfNodeId = GetSelfTipcNodeId();
    uint32_t evNodeId = GetTipcNodeId(nodeAddr);

    CLOG_NOTICE("TIPC component event %d received for component %d from Node: %u", notificationType, componentId,evNodeId);
    if(evNodeId != selfNodeId)
    {
        //Ignoring the event since it is not from Self Node.
        CLOG_INFO("Received Component Event from Peer Node, hence ignoring.");
        return 0;
    }

    if (notificationType == TIPC_PUBLISHED)
    {

        if( componentId < TIPC_TYPE_RESERVED_MAX )
        {
            return 0;
        }

        CLOG_INFO("MeSS thread of component %d has come up",componentId);

        SendComponentStatusUpdate(componentId);
        m_objProcessMap[componentId].pauseHeartBeat = false;
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::OnComponentEvent() <<<<<<<<<<");

    return 0;
}


int AvailabilityManager::OnRecurringTimerExpiry(TimerEvent &ev) {
    CLOG_DEBUG("---------------------------------------------------------------------------");
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::OnRecurringTimerExpiry() >>>>>>>>>>");
    static bool initialState = true;
    static bool isCbHealthy=true;
    if(m_bProcessTerminationInProgress)
    {
	CLOG_NOTICE("Termination in progress..hence returning and not starting Recurring timer again.");
        return 0;
    }
    if(m_iInstanceStartMode == ACTIVE_HOT_STANDBY_MODE)
    {
        //Post an event to monitor the Cluster
        ClusterManagementEvent event;
        event.operation = CM_OP_MONITOR_CLUSTER;
        if (m_objSelfCurrentStatus.selfInstanceAvailabilityStatus == ACTIVE)
        {

            //if node is active update the event with status
            event.isActive=true;
            event.isPeerAvailable=m_isPeerAvailable;
        }
        else
        {
            event.isActive=false;
            event.isPeerAvailable=m_isPeerAvailable;
        }
        m_clMgr->PutEvent(event);
	//get the previous status of local couchbase node
        CouchbaseClusterManager::GetCbStatus(m_CmStatus);
  	CLOG_DEBUG("LocalCbHealth=%d",m_CmStatus.localCbHealth);
        if(m_CmStatus.localCbHealth != HEALTHY)
        {
            if(isCbHealthy)
            {
                CLOG_CRITICAL("Raise alarm to indicate local couchbase went down!");
                m_avaMgrAlarm->RaiseCouchaseDownAlarm();
                isCbHealthy=false;
            }
        }
        else
        {
            if(!isCbHealthy)
            {
                CLOG_DEBUG("Raise clear alarm to indicate local couchbase is back up!");
                m_avaMgrAlarm->RaiseCouchbaseIsBackUpAlarm();
                isCbHealthy=true;
            }

        }
        if(m_CmStatus.isRebalanceStuck)
        {
            if(!m_isRebalanceStuck)
            {
                m_isRebalanceStuck=true;
                m_avaMgrAlarm->RaiseCouchbaseRebalanceStuckAlarm();
                CLOG_DEBUG("Raise alarm indicating Rebalance is stuck!");
            }
        }
        else
        {
            if(m_isRebalanceStuck)
            {
                m_isRebalanceStuck=false;
                m_avaMgrAlarm->RaiseCouchbaseRebalanceRestoredAlarm();
                CLOG_DEBUG("Raise clear alarm for Rebalance stuck!");
            }
        }

        static bool isReplicationStarted = false;
        if(isReplicationStarted != AvailabilityManager::stopReplication)
        {
            CLOG_DEBUG("isReplicationStarted=%d AvailabilityManager::stopReplication=%d",isReplicationStarted,AvailabilityManager::stopReplication);
            isReplicationStarted = AvailabilityManager::stopReplication;
            if(AvailabilityManager::stopReplication)
            {
                CLOG_DEBUG("Send Stop Replication to all components.");
                //Send Stop Replication to all components.
                SendStopReplicationToComponents(MESS_MIN_ACTIVE_INSTANCE);
                SendStopReplicationToComponents(MESS_MIN_STANDBY_INSTANCE);
            }
            else
            {
                CLOG_DEBUG("Send Start Replication to all components.");
                //Send Start Replication to all components.
                SendStartReplicationToComponents(MESS_MIN_ACTIVE_INSTANCE);
                SendStartReplicationToComponents(MESS_MIN_STANDBY_INSTANCE);
            }
        }
    }

    if(m_bIsHeartbeatEnabled)
    {
        //Check HeartBeat Status and initiate further actions.
        CheckHeartBeatStatusOfChildProcesses();
    }

    //Check and Update AvailabilityStatus Flag
    CheckAndUpdateComponentStatusFlag();

    for(unsigned int index=0;index < m_objComponentIdVector.size();index++)
    {
        uint16_t componentId = m_objComponentIdVector[index];
        if (COMPONENT_STATUS_INDETERMINATE == m_objProcessMap.find(componentId)->second.currentComponentStatus) {

            CLOG_NOTICE("Component id %d is still in INDETERMINATE status. Hence, sending the component status of all other components to it.", componentId);

            SendComponentStatusUpdate(componentId);
        }
    }


    while ((m_signalList.GetSize())) {
        SignalEventInfo sigInfo;
        
        if(m_signalList.GetFirstSignalData(sigInfo)==-1) {
            break;
        }

        //Find out the component Id due to which the SIGCHLD has been raised.
        //Also raise an alarm for the same and capture the time at which it has exited.
        uint16_t componentId = HandleQueuedSignalInfo(sigInfo);

        std::unordered_map<uint16_t, ProcessAttributes>::iterator it;
        it = m_objProcessMap.find(componentId);

        if(it !=  m_objProcessMap.end())
        {
            if((m_objSelfCurrentStatus.selfInstanceAvailabilityStatus == STANDBY) &&
                    (m_iInstanceStartMode == ACTIVE_COLD_STANDBY_MODE))
            {
		//Restart only if its low priority process
		if(m_objProcessMap[componentId].priority == PROCESS_PRIORITY_LOW)
		{
		    //Pause the Heartbeat since the component is being restarted.
		    m_objProcessMap[componentId].pauseHeartBeat = true;

		    if(!m_bProcessTerminationInProgress)
		    {
                        bool status = StartComponent(componentId,true);
                        if (!status)
			{
                            CLOG_FATAL("Sending SIGTERM to every process in process group. MANUAL intervention required.");
                            kill(0, SIGTERM);
                            //Raise an Alarm for failure to restart process.
                    	}
                    }

		}
            }else
            {
                //Pause the HeartBeat since the component is being restarted.
                m_objProcessMap[componentId].pauseHeartBeat = true;

                if(!m_bProcessTerminationInProgress){
                    bool status = StartComponent(componentId,true);
                    if (!status){
                        CLOG_FATAL("Sending SIGTERM to every process in process group. MANUAL intervention required.");
                        kill(0, SIGTERM);
                        //Raise an Alarm for failure to restart process.
                    }
                }
            }
            //Reset the HB Counter since process has been restarted
            m_objComponentIdHBInfoMap[componentId].HBMissCount = 0;
        }

    }
    if (m_objSelfCurrentStatus.selfInstanceAvailabilityStatus == ACTIVE) {

        CLOG_NOTICE("Self status is ACTIVE with instance id %u, component id %u",
                m_objSelfCurrentStatus.selfInstanceId,
                MeSSObj().Self().compId);

        SendPeerPingReq(MESS_MULTICAST_ACTIVE);
        SendPeerPingReq(MESS_MULTICAST_STANDBY);

        BeActiveInstance();

        UpdateAvailabilityStatus();

    } else if (m_objSelfCurrentStatus.selfInstanceAvailabilityStatus == STANDBY) {

        CLOG_NOTICE("Self status is STANDBY with instance id %u, component id %u",
                m_objSelfCurrentStatus.selfInstanceId,
                MeSSObj().Self().compId);

        SendPeerPingReq(MESS_MULTICAST_ACTIVE);
        SendPeerPingReq(MESS_MULTICAST_STANDBY);

        BeStandbyInstance();

        UpdateAvailabilityStatus();

    } else {

        CLOG_NOTICE("Self status is INDETERMINATE with instance id %u, component id %u",
                m_objSelfCurrentStatus.selfInstanceId,
                MeSSObj().Self().compId);

        SendPeerPingReq(MESS_MULTICAST_ACTIVE);
        SendPeerPingReq(MESS_MULTICAST_STANDBY);

        gettimeofday(&m_objLastPeerAckTime, NULL);


        std::map<std::string,InterfaceAttributes>::iterator interfaceMapIter;
        for (interfaceMapIter = m_objInterfaceMap.begin(); interfaceMapIter != m_objInterfaceMap.end(); interfaceMapIter++) {
            if(interfaceMapIter->second.interfaceType == TRAFFIC)
            {
                SetArpAttribOnInterface((interfaceMapIter->first).c_str(), false);
            }
        }

        std::map<std::string, std::string>::const_iterator mapIter;
        for (mapIter = m_objVirtualIpAddressEthernetInterfaceMap.begin(); mapIter != m_objVirtualIpAddressEthernetInterfaceMap.end(); mapIter++) {
            AssignIpAddressToInterface((*mapIter).second.c_str(),
                    (*mapIter).first.c_str(),
                    m_objVirtualIpAddressRoutingPrefixMap.find((*mapIter).first)->second);
        }
        if(initialState)
        {
            //Since this is initialization state, add routes.
            std::map<std::string,InterfaceAttributes>::iterator interfaceMapIter;
            for (interfaceMapIter = m_objInterfaceMap.begin();
                    interfaceMapIter != m_objInterfaceMap.end(); interfaceMapIter++)
            {
                if(interfaceMapIter->second.ipAddresses.size() == 1)
                {
                    //Add route only if 1 VIP is configured on interface.
                    PerformRouteOpOnInterface((interfaceMapIter->first).c_str(),
                            (interfaceMapIter->second.ipAddresses[0]).c_str() ,ADD);
                }
            }
            initialState = false;
        }

        MakeStandbyInstance(false);
        BeStandbyInstance();
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::OnRecurringTimerExpiry() <<<<<<<<<<");
    CLOG_DEBUG("---------------------------------------------------------------------------");

    return 1;
}

int AvailabilityManager::OnSwitchoverCompleteEvent(TimerEvent &ev) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::OnSwitchoverCompleteEvent() >>>>>>>>>>");

    m_bSwitchoverInProgress = false;

    CLOG_NOTICE("Switchover stabilized");

    if(m_isPlannedSwitchOver)
    {
        m_avaMgrAlarm->PlannedSwitchoverCompletedAlarm(std::string(m_objSelfCurrentStatus.selfHostname));
        //Reset the flag
        m_isPlannedSwitchOver = false;
    }
    else
    {
        m_avaMgrAlarm->UnplannedSwitchoverCompletedAlarm(std::string(m_objSelfCurrentStatus.selfHostname));
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::OnSwitchoverCompleteEvent() <<<<<<<<<<");

    return 0;
}


void AvailabilityManager::FlushArpTables()
{
    UtilityEvent event;
    event.ev_type = UTILITY_FLUSH_ARP_TABLES;
    CLOG_DEBUG("Pushing event UTILITY_FLUSH_ARP_TABLES into utility thread.");
    m_utility_q.Push(event);
}

void AvailabilityManager::AddArpTableRulesForTrafficVIPs(bool disableArp)
{

    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::AddArpTableRulesForTrafficVIPs() >>>>>>>>>>");
    std::map<std::string, InterfaceAttributes>::const_iterator mapIter;
    for (mapIter = m_objInterfaceMap.begin(); mapIter != m_objInterfaceMap.end(); mapIter++) {
        // Update ARP tables if its a TRAFFIC interface
        if (mapIter->second.interfaceType == TRAFFIC)
        {
            CLOG_DEBUG("AvailabilityManager::AddArpTableRulesForTrafficVIPs(): %s : %s", (*mapIter).first.c_str(),  (disableArp?"Disable":"Enable"));
            std::map<std::string, std::string>::const_iterator itrVIPMap;
            for (itrVIPMap = m_objVirtualIpAddressEthernetInterfaceMap.begin();
                 itrVIPMap != m_objVirtualIpAddressEthernetInterfaceMap.end();
                 itrVIPMap++)
            {
                if (!strcmp((*itrVIPMap).second.c_str(), (*mapIter).first.c_str()))
                {
                    CLOG_DEBUG("AvailabilityManager::AddArpTableRulesForTrafficVIPs(): Updating ARP table for %s : %s ",
                            (*itrVIPMap).first.c_str(),  (*itrVIPMap).second.c_str());

                    char* ipAddress = strdup((*itrVIPMap).first.c_str());

                    UtilityEvent event;
                    if(disableArp)
                    {
                        event.ev_type = UTILITY_BLOCK_ARP_VIP;
                    }
                    else
                    {
                        event.ev_type = UTILITY_UNBLOCK_ARP_VIP;
                    }

                    event.data = ipAddress;
                    CLOG_DEBUG("Pushing event %s for IP %s." ,
                            (disableArp? "UTILITY_BLOCK_ARP_VIP":"UTILITY_UNBLOCK_ARP_VIP"),ipAddress);
                    m_utility_q.Push(event);

                }
            }
        }
    }
    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::AddArpTableRulesForTrafficVIPs() <<<<<<<<<<");
    return;
}

void AvailabilityManager::AddArpTableRulesForInterface(const char* ipAddress, bool outwardDirection, bool disableArp)
{

    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::AddArpTableRulesForInterface() >>>>>>>>>>");
    int addrFamily = GetAddrFamily(ipAddress);

    if (addrFamily == -1) {
        CLOG_ERROR("Cannot change ARP table for invalid IP address %s", ipAddress);
        return;
    }

    char processArgs[ARGUMENT_LEN];
    if (addrFamily == AF_INET) {

        sprintf(processArgs, "%s %s %s -j DROP", (disableArp?"-A":"-D"), (outwardDirection?"OUT -s":"IN -d"), ipAddress);
        CLOG_DEBUG("AvailabilityManager::AddArpTableRulesForInterface(): Launching -> arptables %s ", processArgs);
        LaunchProcessAndWait("/sbin/arptables", processArgs);

    } else if (addrFamily == AF_INET6) {

        CLOG_DEBUG("Not adding any ARP table rules since IPv6.");
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::AddArpTableRulesForInterface() <<<<<<<<<<");

}

void AvailabilityManager::SendGratuitousArpForAllVirtualAddresses()
{
    std::map<std::string, std::string>::const_iterator mapIter;
    struct SendGARPEventData* evData = NULL;
    UtilityEvent event;

    for (mapIter = m_objVirtualIpAddressEthernetInterfaceMap.begin(); mapIter != m_objVirtualIpAddressEthernetInterfaceMap.end(); mapIter++)
    {

        evData = (struct SendGARPEventData*)malloc(sizeof(struct SendGARPEventData));

        strncpy(evData->intfName, (*mapIter).second.c_str(),INTF_NAME_LEN);
        strncpy(evData->ipAddress, (*mapIter).first.c_str(),IP_ADDR_LEN);

        event.ev_type = UTILITY_SENDGARP_VIP;
        event.data = evData;
        CLOG_DEBUG("Pushing event UTILITY_SENDGARP_VIP into Queue for interface : %s,VIP: %s.",
                evData->intfName,evData->ipAddress);
        m_utility_q.Push(event);

    }
    return;
}

void AvailabilityManager::SendGratuitousArp(const char *interfaceName, const char *ipAddress,bool useBroadCastIp) {

    int addrFamily = GetAddrFamily(ipAddress);
    CLOG_DEBUG("Entering SendGratuitousArp >>>>>>>>>>>>>>>");

    if (addrFamily == -1) {
        CLOG_ERROR("Cannot send gratuitous ARP for invalid IP address %s", ipAddress);
        return;
    }

    char processArgs[ARGUMENT_LEN];
    string targetIpAddress;
    if (addrFamily == AF_INET)
    {
        if(useBroadCastIp)
        {
            targetIpAddress = "255.255.255.255";
        }
        else
        {
            targetIpAddress = ipAddress;
        }
        sprintf(processArgs, "-c 3 -U -s %s -I %s %s", ipAddress, interfaceName,targetIpAddress.c_str());
        LaunchProcessAndWait("/usr/sbin/arping", processArgs);

    } else if (addrFamily == AF_INET6)
    {
        sprintf(processArgs, "ff02:: %s", interfaceName);
        LaunchProcessAndWait("/usr/sbin/ndisc6", processArgs);
    }

    CLOG_DEBUG("Exiting SendGratuitousArp <<<<<<<<<<");
}

void AvailabilityManager::LaunchProcess(const char *processName, const char *processArgs, pid_t &pid) {

    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::LaunchProcess() >>>>>>>>>>");

    pid = fork();

    if (pid == 0) {
        int ret = 0;

        char args[ARGUMENT_LEN];
        const char *argv[ARGUMENT_COUNT];
        char *ptr = NULL;

        strncpy(args, processArgs, ARGUMENT_LEN);
        args[255] = 0;

        int count = 0;
        argv[count++] = processName;
        char *token = strtok_r(args, " ", &ptr);

        while (token) {
            argv[count++] = token;
            token = strtok_r(NULL, " ", &ptr);
        }

        argv[count] = NULL;

        ret = execv((const char*) processName, (char * const*) argv);

        if (ret < 0) {
            CLOG_FATAL("Component %s launch failed with error %s. Sending SIGTERM to every process in process group. MANUAL intervention required", processName, strerror(errno));
            kill(0, SIGTERM);
	    m_bProcessTerminationInProgress = true;
        }
        exit(-1);
    } else if (pid < 0) {
        CLOG_FATAL("Process %s launch failed with error %s", processName, strerror(errno));
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::LaunchProcess() <<<<<<<<<<");
}

void AvailabilityManager::ClearAllAvalabilityAlarms()
{

    std::unordered_map<uint16_t, ProcessAttributes>::iterator iter;
    for(iter = m_objProcessMap.begin(); iter != m_objProcessMap.end(); iter++)
    {
        if((*iter).second.priority == PROCESS_PRIORITY_HIGH)
        {
            m_avaMgrAlarm->RaiseHighPriorityProcessUpAlarm((*iter).second.processName,false);
        }
        else
        {
            m_avaMgrAlarm->RaiseLowPriorityProcessUpAlarm((*iter).second.processName,false);
        }
    }
    m_avaMgrAlarm->RaiseDREBringupAlarm(m_objSelfCurrentStatus.selfHostname,false);

    m_avaMgrAlarm->RaiseLicenseViolationClearAlarm();
    if (m_iInstanceStartMode != STANDALONE_MODE)
    {
        m_avaMgrAlarm->RaiseIntfUpAlarm("",false);
        m_avaMgrAlarm->UnplannedSwitchoverCompletedAlarm(m_objSelfCurrentStatus.selfHostname,false);
        m_avaMgrAlarm->PlannedSwitchoverCompletedAlarm(m_objSelfCurrentStatus.selfHostname,false);
        m_avaMgrAlarm->StandbyNodeUpInActiveStandbyAlarm(m_objSelfCurrentStatus.selfHostname,false);

	if(m_iInstanceStartMode == ACTIVE_HOT_STANDBY_MODE)
	{
	    CLOG_DEBUG("Raising Session Replication Restored and Couchbase is Up Alarm");
            m_avaMgrAlarm->RaiseSessionReplicaionRestoredAlarm(false);
            m_avaMgrAlarm->RaiseCouchbaseIsBackUpAlarm(false);
	}
    }
    //m_avaMgrAlarm->RaiseLicenseViolationAlarm("Clearing the alarm on coming up",false);
}
int main(int argc, char *argv[]) {

    if ((argc >= 2 && argv[1] && !strcmp(argv[1], "--version")))
    {
        printf("Diametriq DRE %s\n",DREVer);
        exit(0);
    }

    Daemonize();

    AvailabilityManager *app = NULL;

    try {
        app = new AvailabilityManager();

        app->Init(argc, argv);

        CLOG_NOTICE("Application initialized");

        app->Run();

    } catch (CmdParseException &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << CmdParser::Instance().Help() << std::endl;
    } catch (Exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    cout << "Application exiting" << endl;

    if (app) delete app;
    app = NULL;

    return 0;
}
