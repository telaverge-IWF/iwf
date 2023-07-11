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
#include "AvailabilityManager.h"
#include "ManagementInterface.h"
#include "Pinger.h"


uint32_t AvailabilityManager::PerformClusterOperation(ClusterManagementEvent event)
{

    switch(event.operation)
    {
        case CM_OP_PURGE_METADATA:
            {
                m_clMgr->PutEvent(event);
                //calculate new purge time
                m_secondsToPurgeUnwantedData.tv_sec=event.tv.tv_sec + m_replicationConfig.purgeDataInterval;
                break;
            }
        case  CM_OP_MONITOR_CLUSTER:
            break;
        case  CM_OP_ADD_NODE:
            break;
        case CM_OP_REM_NODE:
            break;

    }
    return 0;
}


void AvailabilityManager::BeActiveInstance() {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::BeActiveInstance() >>>>>>>>>>");

    // In a normal scenario, the instance should remain ACTIVE
    bool makeSelfInstanceStandby = false;
    bool isSelfManagementInterfaceDown = false;
    static bool interfaceNotOperational = false;

    do {
        // If the instance is started in stand-alone mode, no further checks are necessary
        // The instance should remain ACTIVE
        if (m_iInstanceStartMode == STANDALONE_MODE) {
            CLOG_INFO("Instance started in STANDALONE mode. Remaining ACTIVE");

            break;
        }

        if(m_objPeerCurrentStatus.peerInstanceAvailabilityStatus == STANDBY)
        {
            if(m_OneTimePeerActiveBroadCast)
            {
                //Send the stand broadcast message here
                //This is done to inform all components who are dependent on one node becoming ACTIVE in cluster.
                SendAvailabilityActiveUpdateReqToComponents(MESS_MULTICAST_ACTIVE);
                m_OneTimePeerActiveBroadCast = false;
            }
        }
        m_objSelfCurrentStatus.selfCbNodeStatus=m_CmStatus.localCbHealth;

        m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational = false;

        std::set<std::string>::const_iterator iter;
        for (iter = m_objEthernetInterfaceSet.begin(); iter != m_objEthernetInterfaceSet.end(); iter++) {

            if (!IsEthernetInterfaceOperational((*iter).c_str())) {

                if(m_iInstanceStartMode == ACTIVE_HOT_STANDBY_MODE && 
                        m_objInterfaceMap[(*iter)].interfaceType == MANAGEMENT )
                {
                    CLOG_WARNING("Management Interface %d is NOT operational",(*iter).c_str());
                    isSelfManagementInterfaceDown=true; 
                }



                //Check if Failure of this interface should cause change in state of Node.
                //If interface config specifies that failure should not lead to switchover
                //then honour the same.
                m_bIsNeedToAssignIpAddressToInterface = true;
                if(m_objInterfaceMap[(*iter)].failureLeadsToSwitchOver)
                {
                    m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational = true;
                    CLOG_ERROR("Ethernet interface %s is NOT operational. Going STANDBY", (*iter).c_str());
                    makeSelfInstanceStandby = true;

                    // Raise an Unplanned Switchover initiated Alarm.
                    CLOG_INFO("Raising an UnPlannedSwitchoverInitiatedAlarm Alarm");
                    m_avaMgrAlarm->UnplannedSwitchoverInitiatedAlarm(std::string(m_objSelfCurrentStatus.selfHostname));
                }
                else
                {
                    CLOG_WARNING("Ethernet interface %s is NOT operational. But failureLeadsToSwitchOver is disabled", (*iter).c_str());
                    continue;
                }
                CLOG_ERROR("Ethernet interface %s is NOT operational.", (*iter).c_str());

                m_avaMgrAlarm->RaiseIntfDownAlarm((*iter));
                interfaceNotOperational = true;


                break;
            }

        }

        if(!m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational)
        {
            CLOG_DEBUG("Inside Group Interface Validation");
            std::map<std::string,InterfaceGroupAttributes>::iterator itGrp;
            for (itGrp = m_objInterfaceGroupMap.begin(); itGrp !=
                    m_objInterfaceGroupMap.end(); itGrp++) {
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
                        CLOG_ERROR("Ethernet interface Group %s is NOT operational. Going STANDBY", (*itGrp).first.c_str());
                        makeSelfInstanceStandby = true;
                        // Raise an Unplanned Switchover initiated Alarm.
                        CLOG_INFO("Raising an UnPlannedSwitchoverInitiatedAlarm Alarm");
                        m_avaMgrAlarm->UnplannedSwitchoverInitiatedAlarm(std::string(m_objSelfCurrentStatus.selfHostname));
                        break;
                    }
                }
            }
        }

        // If any configured ethernet interface was not operational in a previous run for which switchover was not initiated
        // (for example, if an ethernet cable was plugged out in a previous run),
        // need to assign all IP addresses to the corresponding interfaces again
        // This may be a redundant step for some interfaces, but a harmless and 'necessary' one
        if (m_bIsNeedToAssignIpAddressToInterface) {

            CLOG_NOTICE("Ethernet interface(s) are NOW operational. Assigning IP addresses again...");

            std::map<std::string, std::string>::const_iterator mapIter;
            for (mapIter = m_objVirtualIpAddressEthernetInterfaceMap.begin(); mapIter != m_objVirtualIpAddressEthernetInterfaceMap.end(); mapIter++) {
                AssignIpAddressToInterface((*mapIter).second.c_str(),
                        (*mapIter).first.c_str(),
                        m_objVirtualIpAddressRoutingPrefixMap.find((*mapIter).first)->second);
                //Add Route on the interface.
                std::map<std::string,InterfaceAttributes>::iterator interfaceMapIter = m_objInterfaceMap.find((*mapIter).second);
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
            if(!interfaceNotOperational)
                m_avaMgrAlarm->RaiseIntfUpAlarm("");

            m_bIsNeedToAssignIpAddressToInterface = false;
#if 0
            //Send GARP to all Virtual Addresses since the IP address
            //has been assigned due to an interface going down if we are ACTIVE.
            if(m_objSelfCurrentStatus.selfInstanceAvailabilityStatus == ACTIVE)
                SendGratuitousArpForAllVirtualAddresses();
#endif
        }

        // If any configured ethernet interface is not operational, switch to STANDBY,
        // because the instance cannot properly function as ACTIVE
        if (makeSelfInstanceStandby)
            break;

        // Check if the peer instance is ACTIVE (race condition)
        CLOG_DEBUG("Peer instance current state = %d",m_objPeerCurrentStatus.peerInstanceAvailabilityStatus);
        CLOG_DEBUG("Peer Last Go Active time = %ld  %ld",m_objPeerCurrentStatus.peerLastGoActiveTime.tv_sec,m_objPeerCurrentStatus.peerLastGoActiveTime.tv_usec);
        CLOG_DEBUG("Self Last Go Active time = %ld",m_objSelfCurrentStatus.selfLastGoActiveTime.tv_sec,m_objSelfCurrentStatus.selfLastGoActiveTime.tv_usec);
        if (m_objPeerCurrentStatus.peerInstanceAvailabilityStatus == ACTIVE) {

            // Determine who should be ACTIVE, based on last go ACTIVE time, i.e.,
            // the instance that has less recent last go ACTIVE time should remain ACTIVE in this case
            CLOG_DEBUG(" time = %ld",((1000000 * (m_objPeerCurrentStatus.peerLastGoActiveTime.tv_sec -
                                m_objSelfCurrentStatus.selfLastGoActiveTime.tv_sec)) +
                        (m_objPeerCurrentStatus.peerLastGoActiveTime.tv_usec -
                         m_objSelfCurrentStatus.selfLastGoActiveTime.tv_usec)));

            if (((1000000 * (m_objPeerCurrentStatus.peerLastGoActiveTime.tv_sec - m_objSelfCurrentStatus.selfLastGoActiveTime.tv_sec)) +
                        (m_objPeerCurrentStatus.peerLastGoActiveTime.tv_usec - m_objSelfCurrentStatus.selfLastGoActiveTime.tv_usec)) < 0) {

                CLOG_NOTICE("Both instances are ACTIVE. Peer was ACTIVE less recently. Going STANDBY");

                makeSelfInstanceStandby = true;
                break;
            }

            //Since we are coming back from a race condition where we are the one who
            //is active GARP needs to be sent so that all nearby gateways update their
            //ARP table.
            SendGratuitousArpForAllVirtualAddresses();
        }

        // Get the current time
        struct timeval tv;
        uint32_t timeDiff;
        gettimeofday(&tv, NULL);

        //check if purge data is required
        if(m_iInstanceStartMode == ACTIVE_HOT_STANDBY_MODE)
        {
            if(tv.tv_sec >= m_secondsToPurgeUnwantedData.tv_sec)
            {
                CLOG_DEBUG("Purging Metadata ...");
                ClusterManagementEvent event;
                event.operation=CM_OP_PURGE_METADATA;
                event.isActive=true;
                event.tv.tv_sec=tv.tv_sec;
                PerformClusterOperation(event);
            }
        }
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
            strncpy(m_objPeerCurrentStatus.peerHostname, "\0", HOSTNAME_LEN);
            m_objPeerCurrentStatus.peerIsAnyEthernetInterfaceNotOperational = true;

            gettimeofday(&m_objLastPeerAckTime, NULL);

            CLOG_NOTICE("Unable to communicate with STANDBY using MeSS. Trying to determine whether isolated from network using ICMP ping to arbitrator");
            //If Peer is available previously then flip the flag.
            if(m_isPeerAvailable)
            {
                m_isPeerAvailable = false;
                m_isPeerStandby=false;
                if(m_iInstanceStartMode == ACTIVE_HOT_STANDBY_MODE)
                {
                    m_objPeerCurrentStatus.peerCbNodeStatus=UNHEALTHY;
                }
            }

            //Raise an Alarm since Standby is not reachable.
            //Have a check to suppress multiple alarms.
            if(!m_isPeerAvailable)
            {
                if(m_isPeerStandby == false)
                {
                    CLOG_INFO("Raising an StandbyNodeDownInActiveStandbyAlarm Alarm");
                    m_avaMgrAlarm->StandbyNodeDownInActiveStandbyAlarm(std::string(m_objSelfCurrentStatus.selfHostname));
                    m_isPeerStandby=true;
                }
            }

            if(isArbitratorEnabled())
            {

                for (uint8_t i = 0; i < m_uiCfgNumConsecutivePingAckRcvFailuresFromArbitrator; i++) {

                    // Successive retries allow more time to receive a response from the Arbitrator
                    // Hence, the multiplying factor 'i+1' in the 3rd parameter
                    m_objPinger->PingNearHopGateway(m_strCfgArbitratorIpAddress.c_str(),
                            NULL,
                            m_uiCfgMinPingPeriodicityForArbitrator ,
                            AF_INET);


                }
            }
        }
        makeSelfInstanceStandby = false;
        if( m_iInstanceStartMode ==  ACTIVE_HOT_STANDBY_MODE)
        {
            if(CheckAndHandleCbCluster(!m_isPeerAvailable,isSelfManagementInterfaceDown)!= CB_OK)
            {
                //local cb node is down , so switchover
                makeSelfInstanceStandby=true;
            }
        }

        makeSelfInstanceStandby = false;
        if( m_iInstanceStartMode ==  ACTIVE_HOT_STANDBY_MODE)
        {
            if(CheckAndHandleCbCluster(!m_isPeerAvailable,isSelfManagementInterfaceDown)!= CB_OK)
            {
                //local cb node is down , so switchover
                makeSelfInstanceStandby=true;
            }
        }

    } while (false);

    //Check if all components are aligned with Status of AM.
    //This shows that Node is stabilized after State Change i.e from either ACTIVE to STANDBY or vice-versa.
    CheckComponentStatusAndUpdateHeartBeatFlag(InstanceAvailabilityStatus::ACTIVE);

    if (makeSelfInstanceStandby)
        MakeStandbyInstance(true);

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::BeActiveInstance() <<<<<<<<<<");
}


void AvailabilityManager::MakeActiveInstance(bool switchOver = false) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::MakeActiveInstance() >>>>>>>>>>");

    m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational = false;
    bool immediateRebind = true;

    //Stop Heart beat with Child processes since Node state change is initiated.
    //Heart beat is restarted once State change of Node stabilized.
    m_bStopComponentHeartBeat = true;

    if (m_iInstanceStartMode == STANDALONE_MODE)
    {
        //since we are in standalone mode let us skip checking of configured interfaces.
    }
    else
    {
        std::set<std::string>::const_iterator iter;
        for (iter = m_objEthernetInterfaceSet.begin(); iter != m_objEthernetInterfaceSet.end(); iter++) {
            //Set Bonding Option to send GARP if cable is plugged back in.
            //SetGratArpCountAttribOnInterface(ETH_INTF_NUM_GRAT_ARP_COUNT_ACTIVE,(*iter).c_str());
            SetGratArpCountAttribOnInterface(m_objInterfaceMap[(*iter).c_str()].bondingOptionNumGratArp,(*iter).c_str());

            if (!IsEthernetInterfaceOperational((*iter).c_str())) {

                m_bIsNeedToAssignIpAddressToInterface = true;
                if(m_objInterfaceMap[(*iter)].failureLeadsToSwitchOver) {
                m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational = true;
                CLOG_ERROR("Ethernet interface %s is NOT operational. Hence, going STANDBY", (*iter).c_str());
                } else {
                    CLOG_NOTICE("Ethernet interface %s is NOT operational..",(*iter).c_str());
                    continue;
                }

                break;
            }

        }
    }

    if (m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational) {
        CLOG_ERROR("Could not make instance ACTIVE, because at least one ethernet interface is NOT operational. Hence, going STANDBY");

        MakeStandbyInstance(true);

        return;
    }

    MeSSObj().Self().instance = MESS_MIN_ACTIVE_INSTANCE;
    MeSSObj().Self().compId = COMP_AVAILABILITY_MANAGER;

    {
        std::set<std::string>::iterator iter;
        iter = m_objHostnameSet.find(std::string(m_objSelfCurrentStatus.selfHostname));

        if (iter != m_objHostnameSet.end())
            m_objHostnameSet.erase(iter);
    }

    m_objSelfCurrentStatus.selfInstanceId = MeSSObj().Self().instance;
    m_objSelfCurrentStatus.selfInstanceAvailabilityStatus = ACTIVE;
    gettimeofday(&(m_objSelfCurrentStatus.selfLastGoActiveTime), NULL);

    m_objHostnameSet.insert(std::string(m_objSelfCurrentStatus.selfHostname));

    MeSSObj().Rebind(MeSSObj().Self(),immediateRebind);

    std::map<std::string,InterfaceAttributes>::iterator interfaceMapIter;
    for (interfaceMapIter = m_objInterfaceMap.begin(); interfaceMapIter != m_objInterfaceMap.end(); interfaceMapIter++) {

        //if its a traffic interface Enable ARP on interface
	if(interfaceMapIter->second.interfaceType == TRAFFIC )
	{
	    SetArpAttribOnInterface((interfaceMapIter->first).c_str(), true);
	}
	else
        //Here we are assigning IP, since node has become Active
        if(interfaceMapIter->second.interfaceType == MANAGEMENT )
        {
            //assign the Management VIP
            AssignIPAddresses(interfaceMapIter->second.ipAddresses,
			      (interfaceMapIter->first).c_str(),
			      true);

        }


    }

    // Remove the ARP tables rule to drop all the ARP requests in and out
    AddArpTableRulesForTrafficVIPs(false);

    SendGratuitousArpForAllVirtualAddresses();

    SwitchChildProcessesToActive(switchOver);

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::MakeActiveInstance() <<<<<<<<<<");
}


bool AvailabilityManager::SwitchChildProcessesToActive(bool switchOver) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::SwitchAllChildProcessesToActive() >>>>>>>>>>");
    unsigned int index;
    for(index = 0; index < m_objComponentIdVector.size();index++)
    {
        SendAvailabilityStatusResetReq(m_objComponentIdVector[index],
                MESS_MULTICAST_ACTIVE,
                MESS_MIN_ACTIVE_INSTANCE, switchOver);
        SendAvailabilityStatusResetReq(m_objComponentIdVector[index],
                MESS_MULTICAST_STANDBY,
                MESS_MIN_ACTIVE_INSTANCE, switchOver);
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SwitchAllChildProcessesToActive() <<<<<<<<<<");


    return true;
}
