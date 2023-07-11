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
#include "AvailabilityManager.h"
#include "Pinger.h"

void AvailabilityManager::BeStandbyInstance() {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::BeStandbyInstance() >>>>>>>>>>");

    // In a normal scenario, the instance should remain STANDBY
    bool makeSelfInstanceActive = false;
    static bool nodeAddedToCluster = false;

    do {

        // If the instance is started in stand-alone mode then just wait for all components
        // to get initialized only after which the instance should switch to ACTIVE
        if (m_iInstanceStartMode == STANDALONE_MODE) {
            CLOG_NOTICE("Instance started in STANDALONE mode. Going ACTIVE");

            makeSelfInstanceActive = true;
            break;
        }

        // If switchover is in progress, the instance should remain STANDBY
        if (m_bSwitchoverInProgress) {
            CLOG_INFO("Switchover is in progress. Remaining STANDBY");
            break;
        }

        if(m_objPeerCurrentStatus.peerInstanceAvailabilityStatus == ACTIVE)
        {
            if(!m_OneTimePeerActiveBroadCast)
            {
                //Send the stand broadcast message here
                SendAvailabilityActiveUpdateReqToComponents(MESS_MULTICAST_STANDBY);
                m_OneTimePeerActiveBroadCast = true;
            }
        }

        //update the local couchbase node status
        m_objSelfCurrentStatus.selfCbNodeStatus=m_CmStatus.localCbHealth;

        m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational = false;

        std::set<std::string>::const_iterator iter;
        for (iter = m_objEthernetInterfaceSet.begin(); iter != m_objEthernetInterfaceSet.end(); iter++) {

            if (!IsEthernetInterfaceOperational((*iter).c_str())) {

                m_avaMgrAlarm->RaiseIntfDownAlarm((*iter));

                CLOG_ERROR("Ethernet interface %s is NOT operational.", (*iter).c_str());

                m_bIsNeedToAssignIpAddressToInterface = true;
                if(m_objInterfaceMap[(*iter)].failureLeadsToSwitchOver) {
                    m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational = true;
                } else {
                    CLOG_WARNING("Ethernet interface %s is NOT operational. But failureLeadsToSwitchOver is disabled", (*iter).c_str());
                    continue;
                }

                CLOG_ERROR("Ethernet interface %s is NOT operational. Remaining STANDBY", (*iter).c_str());
                break;
            }
        }

        if(!m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational)
        {
            std::map<std::string,InterfaceGroupAttributes>::iterator itGrp;
            for (itGrp= m_objInterfaceGroupMap.begin(); itGrp!= m_objInterfaceGroupMap.end(); itGrp++) {
                if(itGrp->second.failureLeadsToSwitchOver)
                {
                    bool IsOperational = false;
                    for(unsigned int i = 0; i < itGrp->second.interfaceName.size(); i++)
                    {
                        if (IsEthernetInterfaceOperational(itGrp->second.interfaceName.at(i).c_str())) {
                            IsOperational = true;
                            break;
                        }
                    }
                    if(!IsOperational)
                    {
                        m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational = true;
                        break;
                    }
                }
            }
        }

        if (m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational)
            break;

        // If any configured ethernet interface was not operational in a previous run
        // (for example, if an ethernet cable was plugged out in a previous run),
        // need to assign all IP addresses to the corresponding interfaces again
        // This may be a redundant step for some interfaces, but a harmless and 'necessary' one
        if (m_bIsNeedToAssignIpAddressToInterface) {

            CLOG_NOTICE("Ethernet interface(s) are NOW operational. Assigning IP addresses again...");

            std::map<std::string, std::string>::const_iterator mapIter;
            for (mapIter = m_objVirtualIpAddressEthernetInterfaceMap.begin(); mapIter != m_objVirtualIpAddressEthernetInterfaceMap.end(); mapIter++) {
	
                std::map<std::string,InterfaceAttributes>::iterator interfaceMapIter = m_objInterfaceMap.find((*mapIter).second);
		if(interfaceMapIter != m_objInterfaceMap.end())
		{
		    if(interfaceMapIter->second.interfaceType == MANAGEMENT )
		    {
		        CLOG_DEBUG("Not assigning VIP for management VIP");
		        continue;
		    }
		}
                AssignIpAddressToInterface((*mapIter).second.c_str(),
                        (*mapIter).first.c_str(),
                        m_objVirtualIpAddressRoutingPrefixMap.find((*mapIter).first)->second);
                //Add Route on the interface.
                if(interfaceMapIter != m_objInterfaceMap.end())
                {
                    if(interfaceMapIter->second.ipAddresses.size() == 1)
                    {
                        //Add route only if 1 VIP is configured on interface.
                        PerformRouteOpOnInterface((interfaceMapIter->first).c_str(),
                                (interfaceMapIter->second.ipAddresses[0]).c_str() ,ADD);
                    }
                }
            }
            //TODO:Find the interface wihch was down so that the same can be
            //sent in clear alarm.
            m_avaMgrAlarm->RaiseIntfUpAlarm("");

            m_bIsNeedToAssignIpAddressToInterface = false;

        }

	//In Active-Hot-Standby mode , there has to be few extra checks wrt couchbase process monitoring
	//If all the checks are satisfied set isCbOK flag to true, else set to false
	//In Case of modes other than Active-Hot-Standby by default the flag to be set to true
    //isCbOK flag is used to indicate that the node can become active after checking couchbase conditions
    bool isCbOK=true;
	if(m_iInstanceStartMode == ACTIVE_HOT_STANDBY_MODE)
        {

	    CLOG_DEBUG("m_objSelfCurrentStatus.selfCbNodeStatus=%d  m_objPeerCurrentStatus.peerCbNodeStatus=%d m_CmStatus.nodesInCluster=%d",
	m_objSelfCurrentStatus.selfCbNodeStatus,m_objPeerCurrentStatus.peerCbNodeStatus,m_CmStatus.nodesInCluster);



	    if((m_objSelfCurrentStatus.selfCbNodeStatus == HEALTHY  && m_CmStatus.nodesInCluster !=0) ||
	       (m_objPeerCurrentStatus.peerCbNodeStatus !=  HEALTHY &&
	        (m_objSelfCurrentStatus.selfCbNodeStatus != HEALTHY||m_CmStatus.nodesInCluster == 0)) )
        {

            CLOG_NOTICE("Local CB node is up or All CB nodes in cluster are down.Hence can become ACTIVE");
            isCbOK=true;
        }
	    else
	    {
                if(m_objPeerCurrentStatus.peerInstanceAvailabilityStatus == INDETERMINATE)
                {
                    CLOG_DEBUG("Peer is INDETERMINATE and local couchbase is down, Hence can become ACTIVE");
                    isCbOK=true;
                }
                else
                {
                    if( m_objPeerCurrentStatus.peerIsAnyEthernetInterfaceNotOperational)
                    {
                        CLOG_DEBUG("Local CB node is down and Peer Ethernet interface is not operational, Hence can become ACTIVE");
                        isCbOK=true;
                    }
                    else
                    {
                        isCbOK=false;
                        CLOG_ERROR("Local CB node is down and Peer CB node is up. Hence have to remain STANDBY");
                    }
                    //  break;
                }
	    }
	}
	else
	{
	    isCbOK=true;
	}




        // If both instances become STANDBY (for example,
        // when they were neither 'previously' able to communicate with each other using TIPC,
        // nor each able to communicate with the Arbitrator, and thus isolated from the network),
        // determine whether all configured interfaces are operational on self, but
        // any configured interface is not operational on peer
        // In such a case, switch instance to ACTIVE
        if (m_objPeerCurrentStatus.peerInstanceAvailabilityStatus == STANDBY) {
            if ((!m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational) &&
                    (m_objPeerCurrentStatus.peerIsAnyEthernetInterfaceNotOperational) && isCbOK) {

		 CLOG_NOTICE("Both instances are STANDBY. At least one NON-OPERATIONAL interface found on peer. All interfaces are OPERATIONAL on self. Hence, going ACTIVE");

                 makeSelfInstanceActive = true;
                 break;


            }
        }

        if(m_iInstanceStartMode == ACTIVE_HOT_STANDBY_MODE)
        {
            //if peer node is standby and peer couchbase node is UNHEALTHY and self couchbase node is HEALTHY become ACTIVE
            if(m_objPeerCurrentStatus.peerInstanceAvailabilityStatus == STANDBY  &&
                    (m_objPeerCurrentStatus.peerCbNodeStatus ==  UNHEALTHY ||(m_CmStatus.status== CB_OK && m_CmStatus.peerCbHealth != HEALTHY))&&
                    m_objSelfCurrentStatus.selfCbNodeStatus == HEALTHY &&
                    !m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational)
            {
                CLOG_NOTICE("Both instances are STANDBY, self Cb Node is HEALTHY and peer Cb Node is UNHEALTHY.All interfaces are OPERATIONAL on self. Hence, going ACTIVE");
                makeSelfInstanceActive = true;
                break;
            }
        }


        // If both instances become STANDBY (for example,
        // when they were neither 'previously' able to communicate with each other using TIPC,
        // nor each able to communicate with the Arbitrator, and thus isolated from the network),
        // determine who should remain STANDBY, based on the ASCII value of host name, i.e.,
        // the node that has lower ASCII value of host name, should remain STANDBY in this case
        if (m_objPeerCurrentStatus.peerInstanceAvailabilityStatus == STANDBY) {
            if ((strcmp(m_objPeerCurrentStatus.peerHostname, m_objSelfCurrentStatus.selfHostname) < 0)) {

                if(isCbOK)
                {
                    makeSelfInstanceActive = true;
                    CLOG_NOTICE("Both instances are STANDBY. Peer has lower ASCII value of host name. Hence, going ACTIVE");
                    break;
                }
                else
                {
                    CLOG_DEBUG("CB not OK so remaining STANDBY");
                }
            }
            else
            {
                //Be Standby
                if(m_iInstanceStartMode == ACTIVE_COLD_STANDBY_MODE)
                {
                    //If it is Active Cold-Standby mode then terminate only High priority components.
		            TerminateAllComponents(true);
                    m_bComponentsRunning = false;
                    break;
                }
            }
        }

        if (m_objPeerCurrentStatus.peerInstanceAvailabilityStatus == INDETERMINATE) {
            if(isArbitratorEnabled())
            {
                if(m_uiWaitCountForIcmpPingFromPeer > m_uiCfgNumConsecutivePingAckRcvFailuresFromArbitrator) {
                    CLOG_NOTICE("Peer instance state is INDETERMINATE  . Hence, going ACTIVE");
                    ResetWaitingForIcmpPingFromPeer();
                    makeSelfInstanceActive = true;
                    break;
                } else {
                    CLOG_NOTICE("Peer instance state is INDETERMINATE  . Waiting for ICMP Ping from Peer");
                    m_uiWaitCountForIcmpPingFromPeer++;

                }
            } else {

                CLOG_NOTICE("Peer instance state is INDETERMINATE  . Hence, going ACTIVE");
                makeSelfInstanceActive = true;
                break;
            }
        }

        // Get the current time
        struct timeval tv;
        uint32_t timeDiff;
        gettimeofday(&tv, NULL);

        // Get the time difference between the current time and the time the last acknowledgment was received from the peer
        // The time difference uses a sliding window mechanism - it uses the current time as the upper bound,
        // to see if the last peer acknowledgment time (lower bound) is within the allowed window
        timeDiff = ((1000 * (tv.tv_sec - m_objLastPeerAckTime.tv_sec)) + ((tv.tv_usec - m_objLastPeerAckTime.tv_usec) / 1000));


        // If the time difference computed in the previous step is more than that allowed,
        // try to ping the Arbitrator to determine whether the instance should remain ACTIVE
        if (timeDiff > (m_uiCfgNumConsecutivePingAckRcvFailuresFromPeer * m_uiCfgPingPeriodicityForPeer)) {
            m_objPeerCurrentStatus.peerSequenceId = PEER_INITIAL_SEQUENCE_ID;
            m_objPeerCurrentStatus.peerInstanceId = PEER_INVALID_INSTANCE_ID;
            m_objPeerCurrentStatus.peerInstanceAvailabilityStatus = INDETERMINATE;
            m_objPeerCurrentStatus.peerCbNodeStatus = UNHEALTHY;
            strncpy(m_objPeerCurrentStatus.peerHostname, "\0", HOSTNAME_LEN);
            m_objPeerCurrentStatus.peerIsAnyEthernetInterfaceNotOperational = true;
            gettimeofday(&m_objLastPeerAckTime, NULL);

            CLOG_NOTICE("Unable to communicate with ACTIVE using MeSS. Trying to determine whether isolated from network using ICMP ping to arbitrator");


            if(isArbitratorEnabled())
            {
                for (uint8_t k = 0; k < m_uiCfgNumConsecutivePingAckRcvFailuresFromArbitrator; k++) {

                    // Successive retries allow more time to receive a response from the Arbitrator
                    // Hence, the multiplying factor 'i+1' in the 3rd parameter
                    m_objPinger->PingNearHopGateway(m_strCfgArbitratorIpAddress.c_str(), NULL, m_uiCfgMinPingPeriodicityForArbitrator , AF_INET);
                }
            }
            else
            {
                //Since Peer is not reachable and Arbitrator is not present.
                //Standby instance will become active.
                makeSelfInstanceActive = true;
                break;
            }

        }

        makeSelfInstanceActive = false;
    } while (false);

    //Check if all components are aligned with Status of AM.
    //This shows that Node is stabilized after State Change i.e from either ACTIVE to STANDBY or vice-versa.
    CheckComponentStatusAndUpdateHeartBeatFlag(InstanceAvailabilityStatus::STANDBY);

    if((m_iInstanceStartMode == ACTIVE_COLD_STANDBY_MODE) &&
            (m_objPeerCurrentStatus.peerInstanceAvailabilityStatus == ACTIVE)
            && m_bComponentsRunning)
    {
        //Terminate Components.
        TerminateAllComponents(true);
        m_bComponentsRunning = false;
    }

    if ((m_objPeerCurrentStatus.peerInstanceAvailabilityStatus == ACTIVE)
            && (m_iInstanceStartMode == ACTIVE_HOT_STANDBY_MODE))
    {
        if(!nodeAddedToCluster)
        {
            //Send req to Active AM to add node.
            SendAddNodeToClusterRequest(m_objSelfCurrentStatus.selfHostname);
            //TODO: how to confirm if addition was successful.
            nodeAddedToCluster = true;
        }
    }

    if(makeSelfInstanceActive && (m_iInstanceStartMode == ACTIVE_COLD_STANDBY_MODE))
    {
        //Start all components if mode is Cold Standby.
        StartAllComponents();
        m_bComponentsRunning = true;
    }

    if (makeSelfInstanceActive && m_bAllComponentsInitialized)
        MakeActiveInstance(false);

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::BeStandbyInstance() <<<<<<<<<<");
}



void AvailabilityManager::MakeStandbyInstance(bool switchOver = false) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::MakeStandbyInstance() >>>>>>>>>>");

    if(m_iInstanceStartMode == ACTIVE_HOT_STANDBY_MODE)
    {
        //clear rebalance stuck alarm
        CLOG_DEBUG("Raising Rebalance Restored Alarm!");
        m_avaMgrAlarm->RaiseCouchbaseRebalanceRestoredAlarm(false);
        m_isRebalanceStuck=false; 
    }

    bool immediateRebind = true;

    //Stop Heart beat with Child processes since Node state change is initiated.
    //Heart beat is restarted once State change of Node stabilized.
    m_bStopComponentHeartBeat = true;

    //Loop through configured interfaces and set Bonding Option not to send GARP
    //if cable is plugged back in.
    std::set<std::string>::const_iterator iter;
    for (iter = m_objEthernetInterfaceSet.begin(); iter != m_objEthernetInterfaceSet.end(); iter++) {
        SetGratArpCountAttribOnInterface(ETH_INTF_NUM_GRAT_ARP_COUNT_STANDBY,(*iter).c_str());
    }

    MeSSObj().Self().instance = MESS_MIN_STANDBY_INSTANCE;
    MeSSObj().Self().compId = COMP_AVAILABILITY_MANAGER;

    {
        std::set<std::string>::iterator iter;
        iter = m_objHostnameSet.find(std::string(m_objSelfCurrentStatus.selfHostname));

        if (iter != m_objHostnameSet.end())
            m_objHostnameSet.erase(iter);
    }

    m_objSelfCurrentStatus.selfInstanceId = MeSSObj().Self().instance;
    m_objSelfCurrentStatus.selfInstanceAvailabilityStatus = STANDBY;

    // Invalidating the Last Go Active Time as Tue, 19 Jan 2038 00:00:00 GMT
    // This value will also work for 32-bit
    m_objSelfCurrentStatus.selfLastGoActiveTime.tv_sec = 2147472000;
    m_objSelfCurrentStatus.selfLastGoActiveTime.tv_usec = 0;

    m_objHostnameSet.insert(std::string(m_objSelfCurrentStatus.selfHostname));

    //If it is a planned switchover then don't do an immediate Rebind.
    if(m_isPlannedSwitchOver)
    {
        immediateRebind = false;
    }
    MeSSObj().Rebind(MeSSObj().Self(),immediateRebind);

   // std::set<std::string>::const_iterator setIter;
    std::map<std::string,InterfaceAttributes>::iterator interfaceMapIter;
    for (interfaceMapIter = m_objInterfaceMap.begin(); interfaceMapIter != m_objInterfaceMap.end(); interfaceMapIter++) {
        //if its a traffic interface Disable ARP on inteface
        if(interfaceMapIter->second.interfaceType == TRAFFIC )
        {
            SetArpAttribOnInterface((interfaceMapIter->first).c_str(), false);
        }
        else
        //if its a management interface then unassign all IP addresses
        if(interfaceMapIter->second.interfaceType == MANAGEMENT )
        {
            //unassign the Management VIP
            AssignIPAddresses(interfaceMapIter->second.ipAddresses,
                    (interfaceMapIter->first).c_str(),
                    false);
#if 0
            for(uint8_t i =0;i< interfaceMapIter->second.ipAddresses.size();i++)
            {
                //get the routing prefix

                std::map<std::string, unsigned char>::iterator rtPrefixIter;
                rtPrefixIter = m_objVirtualIpAddressRoutingPrefixMap.find(interfaceMapIter->second.ipAddresses[i]);
                if( rtPrefixIter != m_objVirtualIpAddressRoutingPrefixMap.end())
                {
                    CLOG_DEBUG("unassigning VIP %s",(interfaceMapIter->second.ipAddresses[i]).c_str());
                    AssignIpAddressToInterface((*setIter).c_str(),
                            (interfaceMapIter->second.ipAddresses[i]).c_str(),
                            rtPrefixIter->second,
                            false);

                }
            }
#endif
        }

    }


    // Add ARP tables rule to drop all the ARP requests in and out
    AddArpTableRulesForTrafficVIPs(true);

    SwitchChildProcessesToStandby(switchOver);

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::MakeStandbyInstance() <<<<<<<<<<");
}


bool AvailabilityManager::SwitchChildProcessesToStandby(bool switchOver) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::SwitchAllChildProcessesToStandby() >>>>>>>>>>");

    static bool isLaunch = true;
    unsigned int index;

    //Launch Processes only if Instance is not started in Cold Standby mode.
    if (isLaunch && (m_iInstanceStartMode != ACTIVE_COLD_STANDBY_MODE)) {
        StartAllComponents();

        isLaunch = false;
        m_bComponentsRunning = true;

    }
    else if(m_iInstanceStartMode == ACTIVE_COLD_STANDBY_MODE)
    {
	CLOG_DEBUG("Kill high priority since we are supposed to run in Cold Standby mode");
        //Kill high priority components since we are supposed to run in Cold Standby mode.
        if(m_bComponentsRunning == true)
        {
  	    CLOG_DEBUG("m_bComponentsRunning == true");

            bool ret = TerminateAllComponents(true);
            for(index=0;index < m_objComponentIdVector.size(); index++)
            {
		CLOG_DEBUG("m_bComponentsRunning == true %d",index);
                SendAvailabilityStatusResetReq(m_objComponentIdVector[index],
                        MESS_MULTICAST_ACTIVE,
                        MESS_MIN_STANDBY_INSTANCE, switchOver);
                SendAvailabilityStatusResetReq(m_objComponentIdVector[index],
                        MESS_MULTICAST_STANDBY,
                        MESS_MIN_STANDBY_INSTANCE, switchOver);
            }

        if(!ret)
        {
            //starting low priority process...
            //main intention is to launch low priority process when
            //avamgr comes up
            StartAllComponents(true);
        }
        m_bStopComponentHeartBeat = true;
        m_bComponentsRunning = false;
        }
        else
        {
            //starting low priority process...
            //main intention is to launch low priority process when
            //avamgr comes up
            StartAllComponents(true);
        }
    }
    else {
        for(index=0;index < m_objComponentIdVector.size(); index++)
        {
            SendAvailabilityStatusResetReq(m_objComponentIdVector[index],
                    MESS_MULTICAST_ACTIVE,
                    MESS_MIN_STANDBY_INSTANCE, switchOver);
            SendAvailabilityStatusResetReq(m_objComponentIdVector[index],
                    MESS_MULTICAST_STANDBY,
                    MESS_MIN_STANDBY_INSTANCE, switchOver);
        }
        //Suppress the alarm to avoid any wrong intimation as the process
        //restart was intended.
        m_bSuppressHigPriorityProcessAlarm = true;
        //Terminate high priority processes which will be restarted so that
        //stale session information is no longer in the process.
        //TerminateAllComponents(true);
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SwitchAllChildProcessesToStandby() <<<<<<<<<<");

    return true;
}
