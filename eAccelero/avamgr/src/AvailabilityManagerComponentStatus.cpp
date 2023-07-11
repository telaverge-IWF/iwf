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
#include "ManagementInterface.h"

int AvailabilityManager::CheckAndUpdateComponentStatusFlag()
{
    std::unordered_map<uint16_t, ProcessAttributes>::iterator it;
    for(it = m_objProcessMap.begin();it != m_objProcessMap.end(); it++)
    {
        if(it->second.currentComponentStatus != COMPONENT_STATUS_INITIALIZED)
        {
            //Don't Set the flag since all components are not initialized.
            return -1;
        }
    }
    //Since all components are initialized
    m_bAllComponentsInitialized = true;

    static bool isInitial = true;
    //Raise a DRE BringUp Alarm since all processes are launched and Initialized
    //successfully. Do it only during DRE bringup.
    if(isInitial)
    {
        /* In Active Cold Standby IWF/High priority process will not be running hence raising
         *          * alarms for the IWF/High priority process backup */
        if (m_iInstanceStartMode == ACTIVE_COLD_STANDBY_MODE)
        {
            if (m_objPeerCurrentStatus.peerInstanceAvailabilityStatus == STANDBY)
            {
                CLOG_INFO("Raising and High priority process lauched Alarm successfully");
                uint32_t index = 0;
                for (;index < m_objComponentIdVector.size();index++)        
                {
                    if (m_objProcessMap[m_objComponentIdVector[index]].priority == PROCESS_PRIORITY_HIGH)
                    {
                        ProcessAttributes* pAttrib = &(m_objProcessMap[m_objComponentIdVector[index]]);
                        std::string processNameWithArgs = pAttrib->processName;
                        m_avaMgrAlarm->RaiseHighPriorityProcessUpAlarm(processNameWithArgs);
                    }
                }
            }
        }
        ClearAllAvalabilityAlarms();
        CLOG_INFO("Raising an DRE Bringup Alarm since DRE was brought up successfully");
        m_avaMgrAlarm->RaiseDREBringupAlarm(m_objSelfCurrentStatus.selfHostname);
        isInitial = false;
    }
    return 0;
}

int AvailabilityManager::ComponentStatusUpdateBroadcastRespCbk(ComponentStatusUpdateResp *Response)
{
    CLOG_DEBUG("Entered AvailabilityManager::ComponentStatusUpdateBroadcastRespCbk >>>>>");
    if ((MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Response == NULL)    {
        //Don't print error since Rebind is in progress hence Send failed.
        if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
        {
            CLOG_INFO("MeSS Status is not success since Rebind is in Progress.");
            return 0;
        }
        CLOG_ERROR("ComponentStatusUpdateResp is NULL and MeSS State is %d,src is %d",MeSS::Handle().m_state,MeSS::Handle().m_src);
        return 0;
    }
    return 0;
}

void AvailabilityManager::UpdateComponentStatus(uint16_t componentId, HAComponentStatus componentStatus)
{
    m_objProcessMap[componentId].currentComponentStatus = componentStatus;
}

int AvailabilityManager::ComponentStatusUpdate(ComponentStatusUpdateReq *Request,ComponentStatusUpdateResp *Response)
{
    CLOG_DEBUG("Entered AvailabilityManager::ComponentStatusUpdate >>>>>");

    if(Request)
    {
        if(Request->tipcnodeid() == GetSelfTipcNodeId())
        {
            //Since an Update request would always contain only 1 component status
            //hence safely assuming and retrieveing from index 0.
            uint16_t componentId = Request->currentcomponentstatus(0).componentid();
            HAComponentStatus status = (HAComponentStatus)Request->currentcomponentstatus(0).currentstatus();
            Response->set_responseid(Request->requestid());
            CLOG_INFO("Received ComponentStatusUpdate from %d component with new Status %d",componentId,status);

            CLOG_DEBUG("Check if its because of a IWF component restart.. in a no backup case");
            if(m_objPeerCurrentStatus.peerInstanceId == PEER_INVALID_INSTANCE_ID)
            {
                std::unordered_map<uint16_t, ProcessAttributes>::iterator iter;
                if ((iter = m_objProcessMap.find(componentId)) != m_objProcessMap.end())
                {
                    if(((*iter).second.priority == PROCESS_PRIORITY_HIGH) && (*iter).second.processRestartCounter)
                    {
                        SendAvailabilityStatusResetReq(componentId, MESS_MULTICAST_ACTIVE, m_objSelfCurrentStatus.selfInstanceId, false);
                        SendAvailabilityStatusGetReq(componentId,
                                MeSSObj().Self().instance);
                    }
                }
            }
            //Update AM Status Map
            m_objProcessMap[componentId].currentComponentStatus = status;

            CheckAndUpdateComponentStatusFlag();

            //Broadcast the status update to all components monitored
            std::unordered_map<uint16_t, ProcessAttributes>::iterator it;
            for(it = m_objProcessMap.begin();it != m_objProcessMap.end(); it++)
            {
                SendComponentStatusRequest(it->first,MESS_MULTICAST_ACTIVE,*Request);
                SendComponentStatusRequest(it->first,MESS_MULTICAST_STANDBY,*Request);
            }
        }
    }

    CLOG_DEBUG("Exiting AvailabilityManager::ComponentStatusUpdate >>>>>");
    return 0;
}


int AvailabilityManager::SendComponentStatusRequest(uint16_t componentId,
        uint16_t destInstanceId,ComponentStatusUpdateReq req)
{
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::SendComponentStatusRequest() >>>>>>>>>>");

    MeSSEndpoint dest = {componentId, destInstanceId};
    static uint32_t requestId = 0;
    req.set_requestid(requestId++);
    req.set_tipcnodeid(GetSelfTipcNodeId());
    Stub::AvaMgrProcessStatusInterface processStatusInterface(dest,0);
    processStatusInterface.ComponentStatusUpdateBroadcast(req);
    CLOG_INFO("Component status Update request sent to component %d for self request id %u",
            componentId,req.requestid());
    CLOG_DEBUG("%s",req.DebugString().c_str());

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SendComponentStatusRequest() <<<<<<<<<<");
    return 0;
}


int AvailabilityManager::AvailabilityStatusGetRequestRespCbk(AvailabilityStatusGetResp *response) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::AvailabilityStatusGetRequestRespCbk() >>>>>>>>>>");

    if (( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            response == NULL)
    {
        //Don't print error since Rebind is in progress hence Send failed.
        if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
        {
            CLOG_INFO("MeSS Status is not success since Rebind is in Progress.");
            return 0;
        }
        CLOG_ERROR("AvailabilityStatusGetResp is NULL. MeSS State is %d,src is %d",MeSS::Handle().m_state,MeSS::Handle().m_src);
        return 0;
    }

    CLOG_DEBUG("Received Status %s",response->DebugString().c_str());

    uint16_t instanceId;
    uint16_t componentId;

    if(response->has_peerhostname())
    {
        if (!strcmp(m_objSelfCurrentStatus.selfHostname, response->peerhostname().c_str())) {

            std::map<uint16_t, InstanceAvailabilityStatus>::iterator map_iterator;

            instanceId = (uint16_t)(response->instanceid());
            componentId = (uint16_t)(response->componentid());

            map_iterator = m_objComponentIdAvailabilityStatusMap.find(componentId);

            if (map_iterator != m_objComponentIdAvailabilityStatusMap.end()) {
                if (MESS_ISStandbyInst(instanceId)) {
                    map_iterator->second = InstanceAvailabilityStatus::STANDBY;
                } else if (MESS_ISActiveInst(instanceId)) {
                    map_iterator->second = InstanceAvailabilityStatus::ACTIVE;
                } else {
                    map_iterator->second = InstanceAvailabilityStatus::INDETERMINATE;
                }
                //Check if Heart-beating is on...only then verify the HB Count
                if((!m_bStopComponentHeartBeat) && m_bIsHeartbeatEnabled)
                {
                    if(response->currentprocessstatus() == HEARTBEAT_OK )
                    {
                        //Reset HeartBeat Miss Count.
                        m_objComponentIdHBInfoMap[componentId].HBMissCount = 0;
                        CLOG_INFO("Component Id %d, Resetting HBMissCount since a response is received for Status Rquest with HEARTBEAT_OK",componentId);
                    } else {
                        //Increment HeartBeat Miss Count.
                        m_objComponentIdHBInfoMap[componentId].HBMissCount++;
                        CLOG_WARNING("Component Id %d, Incrementing HBMissCount since a response is received for Status Rquest with not ok:%d. Current HBMissCount is %d",
                                componentId,response->currentprocessstatus(),m_objComponentIdHBInfoMap[componentId].HBMissCount);
                    }
                }
                else
                {
                    //Since HB is disabled don't increment the count.
                    m_objComponentIdHBInfoMap[componentId].HBMissCount = 0;
                }

                // Update the component status as well
                if (response->has_currentcomponentstatus())
                {
                    UpdateComponentStatus(componentId, (eAccelero::HAComponentStatus)response->currentcomponentstatus());
                }

                CLOG_INFO("Component Id %d has an Availability Status of %d", componentId, map_iterator->second);
            } else {
                CLOG_ERROR("Unknown Component Id %d received while trying to get Availability Status", componentId);
            }
        }
    }
    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::AvailabilityStatusGetRequestRespCbk() <<<<<<<<<<");

    return 0;

}


void AvailabilityManager::SendAvailabilityStatusResetReq(uint16_t componentId,
        uint16_t destInstanceId,
        uint16_t newInstanceId, bool switchOver) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::SendAvailabilityStatusResetReq() >>>>>>>>>>");

    MeSSEndpoint dest = {componentId, destInstanceId};

    static uint32_t requestId = 0;

    AvailabilityStatusResetReq Req;
    Req.set_requestid(requestId++);
    Req.set_selfhostname(m_objSelfCurrentStatus.selfHostname);
    Req.set_newinstanceid(newInstanceId);
    Req.set_switchover(switchOver);

    //Invoke the API to send StatusResetRequest.
    Stub::AvaMgrProcessStatusInterface processStatusInterface(dest,0);
    processStatusInterface.AvailabilityStatusResetRequest(Req);

    CLOG_INFO("Availability status RESET request sent to component %d for self request id %u, new instance id %u, self hostname %s",
            componentId,Req.requestid(),Req.newinstanceid(),Req.selfhostname().c_str());
    CLOG_DEBUG("RESET req sent is %s",Req.DebugString().c_str());

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SendAvailabilityStatusResetReq() <<<<<<<<<<");
}

void AvailabilityManager::SendAvailabilityStatusGetReq(uint16_t componentId,
        uint16_t destInstanceId) {

    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::SendAvailabilityStatusGetReq() >>>>>>>>>>");

    MeSSEndpoint dest = {componentId, destInstanceId};

    static uint32_t requestId = 0;
    AvailabilityStatusGetReq Req;
    Req.set_requestid(requestId++);
    Req.set_selfhostname(m_objSelfCurrentStatus.selfHostname);

    //Invoke the API to send StatusResetRequest.
    Stub::AvaMgrProcessStatusInterface processStatusInterface(dest,0);
    processStatusInterface.AvailabilityStatusGetRequest(Req);


    CLOG_INFO("Availability status GET request sent to component %d for self request id %u, self hostname %s.",
            componentId,Req.requestid(),Req.selfhostname().c_str());

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SendAvailabilityStatusGetReq() <<<<<<<<<<");
}


int AvailabilityManager::AvailabilityStatusResetRequestRespCbk(AvailabilityStatusResetResp *response) {

    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::AvailabilityStatusResetRequestRespCbk() >>>>>>>>>>");

    if (( MeSS::Handle().m_state != MESS_STATUS_SUCCESS) ||
            response == NULL)
    {
        //Don't print error since Rebind is in progress hence Send failed.
        if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
        {
            CLOG_INFO("MeSS Status is not success since Rebind is in Progress.");
            return 0;
        }
        CLOG_ERROR("MeSS Status is not success or AvailabilityStatusResetResp is NULL. MeSS State is %d,src is %d",MeSS::Handle().m_state,MeSS::Handle().m_src);
        return 0;
    }
    uint16_t componentId;
    uint16_t newInstanceId;
    if(response->has_peerhostname())
    {
        componentId = (uint16_t)(response->componentid());
        newInstanceId = (uint16_t)(response->newinstanceid());
        if (!strcmp(m_objSelfCurrentStatus.selfHostname, response->peerhostname().c_str())) {

            std::map<uint16_t, InstanceAvailabilityStatus>::iterator map_iterator;

            map_iterator = m_objComponentIdAvailabilityStatusMap.find(componentId);

            if (map_iterator != m_objComponentIdAvailabilityStatusMap.end()) {
                if (MESS_ISStandbyInst(newInstanceId)) {
                    map_iterator->second = InstanceAvailabilityStatus::STANDBY;
                } else if (MESS_ISActiveInst(newInstanceId)) {
                    map_iterator->second = InstanceAvailabilityStatus::ACTIVE;
                } else {
                    map_iterator->second = InstanceAvailabilityStatus::INDETERMINATE;
                }
                CLOG_INFO("Component Id %d has an Availability Status of %d", componentId,map_iterator->second);

                //Update Alarms Destination since Instance ID has been changed for SubAgent Process
                if( componentId == COMP_SUB_AGENT )
                {
                    m_avaMgrAlarm->UpdateDestInstanceId(newInstanceId);
                }

                //Update the component's process status in the process map
                if (response->has_currentcomponentstatus())
                {
                    UpdateComponentStatus(componentId, (eAccelero::HAComponentStatus)response->currentcomponentstatus());
                }

            } else {
                CLOG_ERROR("Unknown Component Id %d received while trying to get Availability Status", componentId);
            }
        }
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::AvailabilityStatusResetRequestRespCbk() <<<<<<<<<<");

    return 0;

}

void AvailabilityManager::UpdateAvailabilityStatus() {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::UpdateAvailabilityStatus() >>>>>>>>>>");
    unsigned int index;
    uint16_t componentId;
    for(index=0;index < m_objComponentIdVector.size();index++)
    {
        componentId = m_objComponentIdVector[index];
        if (m_objSelfCurrentStatus.selfInstanceAvailabilityStatus !=
                m_objComponentIdAvailabilityStatusMap.find(componentId)->second) {

            CLOG_NOTICE("Availability status mismatch for component id %d found. Sending reset to match status", componentId);

            SendAvailabilityStatusResetReq(componentId,
                    MESS_MULTICAST_ACTIVE,
                    m_objSelfCurrentStatus.selfInstanceId, m_isPlannedSwitchOver);
            SendAvailabilityStatusResetReq(componentId,
                    MESS_MULTICAST_STANDBY,
                    m_objSelfCurrentStatus.selfInstanceId, m_isPlannedSwitchOver);
        }

        SendAvailabilityStatusGetReq(componentId,
                MeSSObj().Self().instance);
        /*MESS_MIN_ACTIVE_INSTANCE);
          SendAvailabilityStatusGetReq(componentId,
          MESS_MIN_STANDBY_INSTANCE);*/

        //Check if Heart beat is on...only then verify the HB Count
        if(!m_bStopComponentHeartBeat && m_bIsHeartbeatEnabled)
        {
            //Increment HeartBeatMissCount so that in case response is not received
            //this can be used to determine if a process is in defunct/bad state.
            m_objComponentIdHBInfoMap[componentId].HBMissCount++;
            CLOG_INFO("Availability status GET request sent to component %d. Incrementing HBMissCount,Current count is %d",
                    componentId,m_objComponentIdHBInfoMap[componentId].HBMissCount);
        }
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::UpdateAvailabilityStatus() <<<<<<<<<<");
}

void AvailabilityManager::CheckHeartBeatStatusOfChildProcesses()
{
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::CheckHeartBeatStatusOfChildProcesses");
    std::map<uint16_t, HeartBeatInfo>::iterator it;
    pid_t pid;
    for(it = m_objComponentIdHBInfoMap.begin();it!=m_objComponentIdHBInfoMap.end();it++)
    {
        if(m_objProcessMap[(*it).first].pauseHeartBeat || m_objProcessMap[(*it).first].currentComponentStatus == COMPONENT_STATUS_STOPPED)
        {
            //Since heartbeat is paused,which means process MeSS thread is not yet up or process has restarted
            //So don't do heartbeat check.
            //Reset the HBMissCount so that when process update is received we start tracking HBCount afresh.
            //
            //In case of cold standby we will not run high priority process, so don't do heartbeat check.
            (*it).second.HBMissCount = 0;
            continue;
        }
        //Check if heartbeat miss count is more than configured count.
        if(((*it).second.HBMissCount) > m_uiCfgMaxProcessHBAckFailures )
        {
            CLOG_CRITICAL("Heart beat miss count  %d more than max configured heartbeat count %d for component with id %d,hence restarting component",
                    ((*it).second.HBMissCount),m_uiCfgMaxProcessHBAckFailures,(*it).first);
            pid = m_objProcessMap[(*it).first].pid;
            //Check if the PID exists or not.
            if(kill(pid,0) == 0)
            {
                if ( m_objProcessMap[(*it).first].sigkillTimerHandle == (unsigned)-1 && m_objProcessMap[(*it).first].sigtermTimerHandle == (unsigned)-1)
		{
 
	            //Kill the process .
                    kill(pid, SIGTERM);

                    // Start the timer so that if a SIGCHLD is not received in time, we will send SIGKILL
                    StartSigtermTimer((*it).first, m_uiCfgMaxTimeToWaitBeforeSendingSigkill);
                    CLOG_DEBUG("Started SIGTERM timer for component %d.",it->first);
		}
		else
		{
		    if (m_objProcessMap[(*it).first].sigkillTimerHandle != (unsigned)-1)
		    {
		        CLOG_INFO("Not sending SIGTERM to component %d with pid %d as SIGKILL timer is active, timer handle: [%d]",
				   (*it).first,m_objProcessMap[(*it).first].pid,
				   m_objProcessMap[(*it).first].sigkillTimerHandle);
		    }
		    else
		    if(m_objProcessMap[(*it).first].sigtermTimerHandle != (unsigned)-1)
		    {
		        CLOG_INFO("Not sending SIGTERM to component %d with pid %d as SIGTERM timer is active,timer handle: [%d]",
				  (*it).first,m_objProcessMap[(*it).first].pid,
				   m_objProcessMap[(*it).first].sigtermTimerHandle); 
		    }	
		}

            } else {
                //PID doesn't exist.
                if(errno == ESRCH)
                {
                    CLOG_CRITICAL("PID %d for component %d doesn't exist.Hence creating a dummy signal to simulate SIGCHLD",pid,it->first) ;
                }
                else {
                    CLOG_CRITICAL("PID %d for component %d is assigned to some other process.Hence creating a dummy signal to simulate SIGCHLD",pid,it->first);
                }
                //Create a dummy signal Event and queue it so that on Next
                //Recurring timer the component is restarted.
                //This would address scenario where 2 signals are raised at same time
                //and one or mor of the signals did not get queued.
                CreateAndQueueDummySignal(pid);
            }
            //Pause the Heart beat until the process has restarted.
            m_objProcessMap[(*it).first].pauseHeartBeat = true;
            //Resetting HBMiSS Count since we killed the process.
            (*it).second.HBMissCount = 0;
        }
    }
    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::CheckHeartBeatStatusOfChildProcesses");
}

void AvailabilityManager::SendComponentStatusUpdate(uint16_t componentId)
{
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::SendComponentUpdate() >>>>>>>>>>");
    std::unordered_map<uint16_t, ProcessAttributes>::iterator it;
    ComponentStatusUpdateReq Request;
    for(it = m_objProcessMap.begin();it != m_objProcessMap.end(); it++)
    {
        //Send the status of all other components
        if(it->first != componentId)
        {
            ComponentStatus *compStatus =  Request.add_currentcomponentstatus();
            compStatus->set_componentid(it->first);
            compStatus->set_currentstatus(it->second.currentComponentStatus);
        }
  }
    SendComponentStatusRequest(componentId,MESS_MULTICAST_ACTIVE,Request);
    SendComponentStatusRequest(componentId,MESS_MULTICAST_STANDBY,Request);
    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SendComponentUpdate() <<<<<<<<<<");
}

void AvailabilityManager::CheckComponentStatusAndUpdateHeartBeatFlag(InstanceAvailabilityStatus currentNodeStatus) {

    std::map<uint16_t, InstanceAvailabilityStatus>::iterator it;
    for(it = m_objComponentIdAvailabilityStatusMap.begin();it != m_objComponentIdAvailabilityStatusMap.end(); it++)
    {
        if(it->second != currentNodeStatus)
        {
            //If status of atleast one component doesn't match with that of AvaMgr's current status then return.
            return;
        }
    }
    //We reached here means that all components are in alignment with the node.
    //Hence starting Heart beat with components again.
    m_bStopComponentHeartBeat = false;
}


uint32_t AvailabilityManager::SendStartReplicationToComponents(uint16_t destInstanceId)
{
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::SendStartReplicationToComponents() >>>>>>>>>>");
    static uint32_t requestId = 0;
    std::unordered_map<uint16_t, ProcessAttributes>::iterator it;
    for(it = m_objProcessMap.begin();it != m_objProcessMap.end(); it++)
    {
        MeSSEndpoint dest = {it->first, destInstanceId};
        ReplicationReq req;
        req.set_requestid(requestId++);
        req.set_tipcnodeid(GetSelfTipcNodeId());
        Stub::AvaMgrProcessStatusInterface processStatusInterface(dest,0);
        processStatusInterface.StartReplication(req);
        CLOG_DEBUG("Sending Start Replication to component %d",it->first);
        CLOG_DEBUG("%s",req.DebugString().c_str());
    }
    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SendStartReplicationToComponents() <<<<<<<<<<");
    return 0;
}

uint32_t AvailabilityManager::SendStopReplicationToComponents(uint16_t destInstanceId)
{
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::SendStopReplicationToComponents() >>>>>>>>>>");
    static uint32_t requestId = 0;
    std::unordered_map<uint16_t, ProcessAttributes>::iterator it;
    for(it = m_objProcessMap.begin();it != m_objProcessMap.end(); it++)
    {
        MeSSEndpoint dest = {it->first, destInstanceId};
        ReplicationReq req;
        req.set_requestid(requestId++);
        req.set_tipcnodeid(GetSelfTipcNodeId());
        Stub::AvaMgrProcessStatusInterface processStatusInterface(dest,0);
        processStatusInterface.StopReplication(req);
        CLOG_DEBUG("Sending Start Replication to component %d",it->first);
        CLOG_DEBUG("%s",req.DebugString().c_str());
    }
    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SendStopReplicationToComponents() <<<<<<<<<<");
    return 0;
}

int AvailabilityManager::StartReplicationRespCbk(ReplicationResp *Response)
{
    CLOG_DEBUG("Entered AvailabilityManager::StartReplicationRespCbk >>>>>");
    if ((MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Response == NULL)    {
        //Don't print error since Rebind is in progress hence Send failed.
        if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
        {
            CLOG_INFO("MeSS Status is not success since Rebind is in Progress.");
            return 0;
        }
        CLOG_ERROR("StartReplicationResp is NULL and MeSS State is %d,src is %d",MeSS::Handle().m_state,MeSS::Handle().m_src);
        return 0;
    }
    return 0;

}

int AvailabilityManager::StopReplicationRespCbk(ReplicationResp *Response)
{
    CLOG_DEBUG("Entered AvailabilityManager::StopReplicationRespCbk >>>>>");
    if ((MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Response == NULL)    {
        //Don't print error since Rebind is in progress hence Send failed.
        if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
        {
            CLOG_INFO("MeSS Status is not success since Rebind is in Progress.");
            return 0;
        }
        CLOG_ERROR("StopReplicationResp is NULL and MeSS State is %d,src is %d",MeSS::Handle().m_state,MeSS::Handle().m_src);
        return 0;
    }
    return 0;

}

int AvailabilityManager::SendAvailabilityActiveUpdateReqToComponents(uint16_t destInstanceId)
{
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::SendAvailabilityActiveUpdateReqToComponents() >>>>>>>>>>");
    static uint32_t requestId = 0;
    std::unordered_map<uint16_t, ProcessAttributes>::iterator it;
    for(it = m_objProcessMap.begin();it != m_objProcessMap.end(); it++)
    {
        MeSSEndpoint dest = {it->first, destInstanceId};
        AvailabilityActiveReq req;
        req.set_requestid(requestId++);
        Stub::AvaMgrProcessStatusInterface processStatusInterface(dest,0);
        processStatusInterface.AvailabilityActiveUpdateBroadcast(req);
        CLOG_DEBUG("Sending Availability Active Update Request to Component %u",it->first);
        CLOG_DEBUG("%s",req.DebugString().c_str());
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SendAvailabilityActiveUpdateReqToComponents() <<<<<<<<<<");
    return 0;
}

int AvailabilityManager::AvailabilityActiveUpdateBroadcastRespCbk(AvailabilityActiveResp *Response)
{
    CLOG_DEBUG("Entered AvailabilityManager::AvailabilityActiveUpdateBroadcastRespCbk >>>>>");
    if ((MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Response == NULL)    {
        //Don't print error since Rebind is in progress hence Send failed.
        if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
        {
            CLOG_INFO("MeSS Status is not success since Rebind is in Progress.");
            return 0;
        }
        CLOG_ERROR("AvailabilityActiveUpdateBroadcastResp is NULL and MeSS State is %d,src is %d",MeSS::Handle().m_state,MeSS::Handle().m_src);
        return 0;
    }

    return 0;
}

void AvailabilityManager::StartSigtermTimer(uint16_t componentBeingKilled, uint32_t timeToWaitForSigchld)
{
    m_objProcessMap[componentBeingKilled].sigtermTimerHandle =
               this->GetDispatcher()->AddEventHandler(
                   EventSlot<TimerEvent, AvailabilityManager>
                   (this, &AvailabilityManager::HandleSigtermTimeout),
                   TimerEvent(timeToWaitForSigchld, (void*)componentBeingKilled));
    CLOG_DEBUG("SIGTERM timer started for component [%d] with handle [%d] ",
              componentBeingKilled,
              m_objProcessMap[componentBeingKilled].sigtermTimerHandle);
}

int AvailabilityManager::HandleSigkillTimeout(TimerEvent& event)
{
    if(m_bProcessTerminationInProgress)
    {
	CLOG_NOTICE("Termination in progress..hence not taking any action and returning.");
        return 0;
    }
    uint16_t componentToBeKilled = (uint16_t)((unsigned long)(event.Cookie()));
    uint32_t retValue = 0;
    if(m_objProcessMap[componentToBeKilled].sigkillTimerCount > 2)
    {
	    //There is some issue which is causing component not to go down
	    //Hence killing self. 
	    //TODO: Better to restart the syste in this case.
	    CLOG_DEBUG("Component [%d] with pid [%d] is not going down even after sending SIGKILL, hence sending SIGTERM to every process in group.",componentToBeKilled,m_objProcessMap[componentToBeKilled].pid);
	    kill(0, SIGTERM);
	    m_bProcessTerminationInProgress = true;
	    return 0;
    }
    if((retValue = kill(m_objProcessMap[componentToBeKilled].pid, 0)) == 0)
    {
	    CLOG_INFO("SIGKILL for component [%d] with pid [%d] is not yet handled/delivered, restarting timer."
            , componentToBeKilled,
            m_objProcessMap[componentToBeKilled].pid) ;
	m_objProcessMap[componentToBeKilled].sigkillTimerCount++;
	//Hence restarting timer.
	return 1;
    }
    else if(errno == ESRCH)
    {
	    //pid is no longer there, hence we can ensure that child is respawned.
	    CLOG_DEBUG("Creating a dummy signal info for component [%sd] pid [%d] so that it will be restarted.",
		componentToBeKilled,
		m_objProcessMap[componentToBeKilled].pid);
	    CreateAndQueueDummySignal(m_objProcessMap[componentToBeKilled].pid);
    }
    m_objProcessMap[componentToBeKilled].sigkillTimerHandle=-1;
    return 0;
}

int AvailabilityManager::HandleSigtermTimeout(TimerEvent& event)
{
    if(m_bProcessTerminationInProgress)
    {
	CLOG_NOTICE("Termination in progress..hence not taking any action and returning.");
        return 0;
    }
    uint16_t componentToBeKilled = (uint16_t)((unsigned long)(event.Cookie()));
    uint32_t retValue = 0;
    //Check if the PID exists or not.
    if((retValue = kill(m_objProcessMap[componentToBeKilled].pid, 0)) == 0)
    {
        CLOG_INFO("SIGTERM for component [%d] with pid [%d] didn't result "
            "in a SIGCHLD, so sending SIGKILL", componentToBeKilled,
            m_objProcessMap[componentToBeKilled].pid) ;
        // now its time to send SIGKILL
        if((retValue = kill(m_objProcessMap[componentToBeKilled].pid, SIGKILL)) != 0)
        {
            CLOG_CRITICAL("SIGKILL for component [%d] with pid [%d] couldn't"
                " be sent, return code [%d] errno [%d]", componentToBeKilled,
                m_objProcessMap[componentToBeKilled].pid, retValue, errno);
        }
	//Start a timer to verify if the SIGKILL killed the component.
	m_objProcessMap[componentToBeKilled].sigkillTimerHandle =
		this->GetDispatcher()->AddEventHandler(
				EventSlot<TimerEvent, AvailabilityManager>
				(this, &AvailabilityManager::HandleSigkillTimeout),
				TimerEvent(m_uiCfgMaxTimeToWaitAfterSendingSigkill,
					(void*)componentToBeKilled));
	m_objProcessMap[componentToBeKilled].sigkillTimerCount++;

    }
    else
    {
	    CLOG_DEBUG("Cannot kill component [%d]'s pid [%d] return value [%d]"
                   " errno [%d] ", componentToBeKilled,
                m_objProcessMap[componentToBeKilled].pid, retValue, errno);
    }

    m_objProcessMap[componentToBeKilled].sigtermTimerHandle = -1;

    return 0;
}

void AvailabilityManager::StopSigtermTimer(uint16_t componentBeingKilled)
{
    this->GetDispatcher()->RemoveEventHandler(TIMER_EVENT_TYPE,
        m_objProcessMap[componentBeingKilled].sigtermTimerHandle);
    CLOG_DEBUG("SIGTERM timer stopped for component [%d] with handle [%d] ",
              componentBeingKilled,
              m_objProcessMap[componentBeingKilled].sigtermTimerHandle);
}

