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
#include "AvailabilityManager.h"
#include "Pinger.h"


void AvailabilityManager::SendPeerPingReq(uint16_t instanceId) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::SendPeerPingReq() >>>>>>>>>>");

    MeSSEndpoint dest = {COMP_AVAILABILITY_MANAGER, instanceId};
    PeerPingReq peerPingReqObj;

    peerPingReqObj.set_selfsequenceid(m_uiTipcSequenceId++);
    peerPingReqObj.set_selfinstanceid(m_objSelfCurrentStatus.selfInstanceId);
    peerPingReqObj.set_selfinstanceavailabilitystatus( m_objSelfCurrentStatus.selfInstanceAvailabilityStatus);
    peerPingReqObj.set_selfhostname(m_objSelfCurrentStatus.selfHostname);
    timevalue* time =  peerPingReqObj.mutable_selflastgoactivetime();
    time->set_time_seconds(m_objSelfCurrentStatus.selfLastGoActiveTime.tv_sec);
    time->set_time_microseconds( m_objSelfCurrentStatus.selfLastGoActiveTime.tv_usec);

    //This is to trick the peer into believing that self is NOT operational
    if (m_bSwitchoverInProgress)
        peerPingReqObj.set_selfisanyethernetinterfacenotoperational(true);
    else
        peerPingReqObj.set_selfisanyethernetinterfacenotoperational(m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational);

    peerPingReqObj.set_selfcbnodestatus(m_objSelfCurrentStatus.selfCbNodeStatus);

    Stub::AvaMgrPeerStatusInterface peerStatusIf(dest,0);
    peerStatusIf.AvailabilityPeerPingRequest(peerPingReqObj);

    CLOG_INFO("Peer ping request sent for self sequence id %u, self instance id %u, self status %d, self hostname %s self cbNode status %d",
            peerPingReqObj.selfsequenceid(),
            peerPingReqObj.selfinstanceid(),
            peerPingReqObj.selfinstanceavailabilitystatus(),
            peerPingReqObj.selfhostname().c_str(),
	    peerPingReqObj.selfcbnodestatus());
    CLOG_DEBUG("Sending PeerPingReq is %s", peerPingReqObj.DebugString().c_str());

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::SendPeerPingReq() <<<<<<<<<<");
}

int AvailabilityManager::AvailabilityPeerPingRequest(PeerPingReq *req,PeerPingResp *resp) {
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::AvailabilityPeerPingRequest() >>>>>>>>>>");
    CLOG_DEBUG("Received PeerPingReq is %s", req->DebugString().c_str());

    resp->set_responseid(req->requestid());
    resp->set_peersequenceid(req->selfsequenceid());
    resp->set_peerinstanceid(m_objSelfCurrentStatus.selfInstanceId);
    resp->set_peerinstanceavailabilitystatus(m_objSelfCurrentStatus.selfInstanceAvailabilityStatus);
    resp->set_peerhostname(m_objSelfCurrentStatus.selfHostname);
    timevalue* time = resp->mutable_peerlastgoactivetime();
    time->set_time_seconds( m_objSelfCurrentStatus.selfLastGoActiveTime.tv_sec);
    time->set_time_microseconds(m_objSelfCurrentStatus.selfLastGoActiveTime.tv_usec);


    // This is to trick the peer into believing that self is NOT operational
    if (m_bSwitchoverInProgress)
        resp->set_peerisanyethernetinterfacenotoperational(true);
    else
        resp->set_peerisanyethernetinterfacenotoperational(m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational);

    resp->set_peercbnodestatus(m_objSelfCurrentStatus.selfCbNodeStatus);

    CLOG_DEBUG("Sending PeerPingResp is %s", resp->DebugString().c_str());
    CLOG_INFO("Peer ping response being sent for peer sequence id %u, self instance %u, self status %d, self hostname %s self cbNode status %d",
            resp->peersequenceid(),
            resp->peerinstanceid(),
            resp->peerinstanceavailabilitystatus(),
            resp->peerhostname().c_str(),
	    resp->peercbnodestatus());

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::AvailabilityPeerPingRequest() <<<<<<<<<<");

    return 0;

}

int AvailabilityManager::AvailabilityPeerPingRequestRespCbk(PeerPingResp * peerPingRespObj)
{
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::AvailabilityPeerPingRequestRespCbk() >>>>>>>>>>");

    if ((MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || peerPingRespObj == NULL) {
        //Don't print error since Rebind is in progress hence Send failed.
        if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
        {
            CLOG_INFO("MeSS Status is not success since Rebind is in Progress.");
            return 0;
        }
        CLOG_ERROR("PeerPingRespObj is NULL and MeSS State is %d,src is %d",MeSS::Handle().m_state,MeSS::Handle().m_src);        
        return 0;
    }

    CLOG_DEBUG("Received PeerPingResp is %s", peerPingRespObj->DebugString().c_str());
    if ((strcmp(m_objSelfCurrentStatus.selfHostname,peerPingRespObj->peerhostname().c_str()) != 0)) {

        gettimeofday(&m_objLastPeerAckTime, NULL);

        if (strcmp(m_objPeerCurrentStatus.peerHostname, peerPingRespObj->peerhostname().c_str())) {
            std::set<std::string>::iterator iter;
            iter = m_objHostnameSet.find(std::string(m_objPeerCurrentStatus.peerHostname));

            if (iter != m_objHostnameSet.end())
                m_objHostnameSet.erase(iter);
        }

        m_objPeerCurrentStatus.peerSequenceId = peerPingRespObj->peersequenceid();
        m_objPeerCurrentStatus.peerInstanceId = peerPingRespObj->peerinstanceid();
        m_objPeerCurrentStatus.peerInstanceAvailabilityStatus = (eAccelero::InstanceAvailabilityStatus)peerPingRespObj->peerinstanceavailabilitystatus();
        strncpy(m_objPeerCurrentStatus.peerHostname, peerPingRespObj->peerhostname().c_str(), HOSTNAME_LEN);
        m_objPeerCurrentStatus.peerLastGoActiveTime.tv_sec = peerPingRespObj->peerlastgoactivetime().time_seconds();
        m_objPeerCurrentStatus.peerLastGoActiveTime.tv_usec = peerPingRespObj->peerlastgoactivetime().time_microseconds();
        m_objPeerCurrentStatus.peerIsAnyEthernetInterfaceNotOperational = peerPingRespObj->peerisanyethernetinterfacenotoperational();

        m_objHostnameSet.insert(peerPingRespObj->peerhostname());
	m_objPeerCurrentStatus.peerCbNodeStatus = peerPingRespObj->peercbnodestatus();
        //Check if Peer was not reachable before and we are currently ACTIVE,send a clear Alarm.
        if((!m_isPeerAvailable) && (m_objSelfCurrentStatus.selfInstanceAvailabilityStatus == ACTIVE))
        {
            m_avaMgrAlarm->StandbyNodeUpInActiveStandbyAlarm(std::string(m_objSelfCurrentStatus.selfHostname));
        }

        //Since we got response from the Peer.
        m_isPeerAvailable = true;

        CLOG_INFO("Peer ping response received sequence id %u, peer instance id %u, peer status %d, peer hostname %s peer cbNode status %d",
                peerPingRespObj->peersequenceid(),
                peerPingRespObj->peerinstanceid(),
                peerPingRespObj->peerinstanceavailabilitystatus(),
                peerPingRespObj->peerhostname().c_str(),
		peerPingRespObj->peercbnodestatus());
    }
    else {
        CLOG_DEBUG("Peer ping response received for self.. hence ignoring m_objSelfCurrentStatus.selfHostname: %s, peerPingRespObj->peerhostname: %s",m_objSelfCurrentStatus.selfHostname,peerPingRespObj->peerhostname().c_str());
    }

    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::AvailabilityPeerPingRequestRespCbk() <<<<<<<<<<");

    return 0;
}

/*Register timer for ping response  */
void AvailabilityManager::RegisterTimer(uint32_t uiPeriodicTimerMiliSec) {

    m_objPeriodicTimerId = this->GetDispatcher()->AddEventHandler(
            EventSlot<TimerEvent, AvailabilityManager > (this,
                &AvailabilityManager::OnPeriodicTimerExpiry),
            TimerEvent(uiPeriodicTimerMiliSec));
}

/* Remove Event from Register */
void AvailabilityManager::UnRegisterEvent(EventHandlerId Id,unsigned eventType) {
    this->GetDispatcher()->RemoveEventHandler(eventType,Id);
}

/*Register Fd to the epoll for ICMP*/
void AvailabilityManager::RegisterPinger(int16_t iPingFd) {
    m_objIcmpSocketHandlerId = this->GetDispatcher()->AddEventHandler(
            EventSlot<SockEvent, AvailabilityManager > (this, 
                &AvailabilityManager::OnIcmpSocketEvent),
            SockEvent(iPingFd,
                SockEvent::READ_EVENT));
}

int AvailabilityManager::OnPeriodicTimerExpiry(TimerEvent &event) {
    m_objPinger->PingOnPeriodicTimerExpiry(event);
    return 0;
}

int AvailabilityManager::OnIcmpSocketEvent(SockEvent &event) {
    m_objPinger->PingOnIcmpSocketEvent(event);
    return 0;
}

void AvailabilityManager::SetPeerCurrentStatus(eAccelero::InstanceAvailabilityStatus Status) {
    m_objPeerCurrentStatus.peerInstanceAvailabilityStatus =  Status;
}

InstanceAvailabilityStatus AvailabilityManager::GetPeerCurrentStatus() {
    return m_objPeerCurrentStatus.peerInstanceAvailabilityStatus;
}

InstanceAvailabilityStatus AvailabilityManager::GetSelfCurrentStatus() {
    return m_objSelfCurrentStatus.selfInstanceAvailabilityStatus;
}

uint8_t AvailabilityManager::GetCfgNumConsecutivePingAckRcvFailuresFromPeer() {
    return m_uiCfgNumConsecutivePingAckRcvFailuresFromPeer;
}

EventHandlerId AvailabilityManager::GetIcmpSocketHandlerId() {
    return m_objIcmpSocketHandlerId;
}

EventHandlerId AvailabilityManager::GetPeriodicTimerId() {
    return m_objPeriodicTimerId;
}

void AvailabilityManager::SetIcmpSocketHandlerId(EventHandlerId Id) {
    m_objIcmpSocketHandlerId = Id;
}

void AvailabilityManager::SetPeriodicTimerId(EventHandlerId Id) {
    m_objPeriodicTimerId = Id;
}

std::string AvailabilityManager::GetArbitratorIpAddress() {
    return m_strCfgArbitratorIpAddress;
}

uint16_t AvailabilityManager::GetPingPeriodicityForArbitrator() {
    return m_uiCfgMinPingPeriodicityForArbitrator;
}

uint16_t AvailabilityManager::GetWaitingForIcmpPingFromPeer() {
    return m_uiWaitCountForIcmpPingFromPeer;
}

void AvailabilityManager::ResetWaitingForIcmpPingFromPeer() {
    m_uiWaitCountForIcmpPingFromPeer = 0;
}

void AvailabilityManager::SetPeerInstanceId(uint16_t InstanceId) {
    m_objPeerCurrentStatus.peerInstanceId = InstanceId;
}

uint16_t AvailabilityManager::GetSelfInstanceId() {
    return m_objSelfCurrentStatus.selfInstanceId;
}

void AvailabilityManager::SetPeerHostname(char *pHostname) {
    memset(m_objPeerCurrentStatus.peerHostname, 0, HOSTNAME_LEN);
    strncpy(m_objPeerCurrentStatus.peerHostname,pHostname,HOSTNAME_LEN);
}

char* AvailabilityManager::GetSelfHostname() {
    return m_objSelfCurrentStatus.selfHostname;
}

void AvailabilityManager::SetLastPeerAckTime(struct timeval tmVal) {
    m_objLastPeerAckTime.tv_sec = tmVal.tv_sec;
    m_objLastPeerAckTime.tv_usec = tmVal.tv_usec;
}

void AvailabilityManager::SetPeerLastGoActiveTime(struct timeval tmVal) {
    m_objPeerCurrentStatus.peerLastGoActiveTime.tv_sec = tmVal.tv_sec;
    m_objPeerCurrentStatus.peerLastGoActiveTime.tv_usec = tmVal.tv_usec;
}

struct timeval AvailabilityManager::GetSelfLastGoActiveTime() {
    return m_objSelfCurrentStatus.selfLastGoActiveTime;
}

void AvailabilityManager::SetPeerEthernetInterfaceNotOperational(bool val) {
    m_objPeerCurrentStatus.peerIsAnyEthernetInterfaceNotOperational = val;
}

bool AvailabilityManager::GetSelfEthernetInterfaceNotOperational() {
    return m_objSelfCurrentStatus.selfIsAnyEthernetInterfaceNotOperational;
}

uint32_t AvailabilityManager::GetSelfCbNodeStatus()
{
    return m_objSelfCurrentStatus.selfCbNodeStatus;
}

void AvailabilityManager::SetSelfCbNodeStatus(uint32_t cbNodeStatus)
{
    m_objSelfCurrentStatus.selfCbNodeStatus = cbNodeStatus;
}

uint32_t AvailabilityManager::GetPeerCbNodeStatus()
{
    return m_objPeerCurrentStatus.peerCbNodeStatus;
}

void AvailabilityManager::SetPeerCbNodeStatus(uint32_t cbNodeStatus)
{
    m_objPeerCurrentStatus.peerCbNodeStatus = cbNodeStatus;
}

uint32_t AvailabilityManager::SendAddNodeToClusterRequest(std::string couchbaseHostName)
{
    MeSSEndpoint dest = {COMP_AVAILABILITY_MANAGER, 0};
    AddToClusterReq req;
    static uint32_t requestId = 0;
    req.set_requestid(requestId);
    req.set_selfhostname(couchbaseHostName);
    req.set_tipcnodeid(GetSelfTipcNodeId());

    Stub::AvaMgrPeerStatusInterface peerStatusIf(dest,0);
    peerStatusIf.AddCouchbaseNodeToCluster(req);
    requestId++;

    return 0;
}

int AvailabilityManager::AddCouchbaseNodeToCluster(AddToClusterReq *Request,AddToClusterResp *Response)
{
    CLOG_DEBUG(">>>>>>>>>> Entered AvailabilityManager::AddCouchbaseNodeToCluster() >>>>>>>>>>");
    if(Request->tipcnodeid() != GetSelfTipcNodeId())
    {
        //Post an event to Cluster Mgmt thread.

        ClusterManagementEvent event;
        event.operation = CM_OP_ADD_NODE;
        event.node.hostName = Request->selfhostname();
        m_clMgr->PutEvent(event);

        //Send a response.
        Response->set_responseid(Request->requestid());    
        //TODO: See how to send back an error in case of addition fails.
        Response->set_status(0);
    }
    CLOG_DEBUG("<<<<<<<<<< Exiting AvailabilityManager::AddCouchbaseNodeToCluster() <<<<<<<<<<");
    return 0;
}


int AvailabilityManager::AddCouchbaseNodeToClusterRespCbk(AddToClusterResp *Response)
{
    if ((MeSS::Handle().m_state != MESS_STATUS_SUCCESS) || Response == NULL) {
        //Don't print error since Rebind is in progress hence Send failed.
        if(MeSS::Handle().m_state == MESS_STATUS_NOT_READY)
        {
            CLOG_INFO("MeSS Status is not success since Rebind is in Progress.");
            return 0;
        }
        CLOG_ERROR("AddToClusterResp is NULL and MeSS State is %d,src is %d",MeSS::Handle().m_state,MeSS::Handle().m_src);        
        return 0;
    }
    return 0;
}


