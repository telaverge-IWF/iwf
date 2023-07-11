/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *             Copyright 2011 IntelliNet Technologies, Inc.                 *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 */

#include "iwf.h"
#include "iwf_transaction_manager.h"
#include "iwf_fsm.h"
#include "iwf_prot_s6a_map.h"
#include "iwf_prot_map_s6a.h"
#include "iwf_prot_cap_ro.h"
#include "iwf_prot_utils.h"
#include <its_dia_config.h>
#include <diameter/ro_r10_transatel/CreditControl.h>
#include <dcca_conf.h>

#include <dia_frame.h>
#include <dia_peer_table.h>
#include <list>
#include <ssg_statistics.h>
#include <map_c.h>

SsgStackStatistics mapStats;

static ITS_OCTET s_tcapIvkId = 0;
ITS_Mutex TransactionManager::m_bulkFetchGuard(0);
ITS_Mutex TransactionManager::m_cbFlushGuard(0);
//ITS_USHORT peerInstance = UNKNOWN_PEER_INST;
//ITS_UINT flags = 0;

std::string SetSessionIdForReset(uint32_t &sIdx, s6a::ResetRequest *cmd)
{

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    if(cmd)
    {
        std::string sessId = "";
        // allocate new session id
        int ret = DiaFrame::GetDiaFrame()->AllocateSessionIndex(
                0U, sIdx, sessId);
        if (ret != ITS_SUCCESS)
        {
            DLOG_ERROR("SetSessionIdForReset : Failed to Allocate SessionId");
            return NULL;
        }
        cmd->setSessionIndex(sIdx);

        cmd->setSessionId(diameter::base::SessionId(sessId));
        return sessId;
    }
    return NULL;
}

void TcapCptList::BuildTcapCptList(TCAP_Component tcapCpt)
{
    m_listCpt.push_back(tcapCpt);
}

std::list<TCAP_Component> TcapCptList::GetTcapCptList()
{
    return m_listCpt;
}

void TcapCptList::ClearTcapCptList()
{
    m_listCpt.clear();
}

TransactionManager* TransactionManager::m_pInstance = NULL;

TransactionManager* TransactionManager::Instance() {

    if (m_pInstance == NULL)
        m_pInstance = new TransactionManager;

    return m_pInstance;
}

void TransactionManager::Destroy() {
    if (m_pInstance != NULL) {
        delete m_pInstance;
        m_pInstance = NULL;
    }
}

TransactionManager::~TransactionManager() {

    map<std::string, IwfFsm*>::iterator diaSessIdTxnEntryMapIter;
    uint32_t ltid = 0;
    ITS_OCTET tidKey[4] = {0};
    int tidKeyLen = 0;

    for (diaSessIdTxnEntryMapIter = m_diaSessionIdTxnEntryMap.begin(); diaSessIdTxnEntryMapIter != m_diaSessionIdTxnEntryMap.end(); ) {

        IwfFsm *iwfFsm = diaSessIdTxnEntryMapIter->second;

        std::string diaSessionId = diaSessIdTxnEntryMapIter->first;
        DiaFrame::GetDiaFrame()->ReleaseSession(diaSessionId.c_str());

        /* Freeing the Shared DSM Transaction Context */
        if(iwfFsm != NULL)
        {
            ltid = iwfFsm->GetTcapLocalTid();
            TCAP_FindAndFreeTransactionContext_CCITT(ltid, tidKey, &tidKeyLen);

            this->ResetCurrRcvdDiaMsg(iwfFsm);
            this->ResetCurrRcvdTcapMsg(iwfFsm);

            /* Already deleted in TransactionManager::ProcessDiaMsg hence not deleting here */

                delete iwfFsm;
                iwfFsm = NULL;
            }
        m_diaSessionIdTxnEntryMap.erase(diaSessIdTxnEntryMapIter++);
        }


    map<ITS_CTXT, IwfFsm*>::iterator tcapDialogueIdTxnEntryIter;
    for (tcapDialogueIdTxnEntryIter = m_tcapDialogueIdTxnEntryMap.begin(); tcapDialogueIdTxnEntryIter != m_tcapDialogueIdTxnEntryMap.end(); ) {

        ITS_CTXT did = tcapDialogueIdTxnEntryIter->first;
        TCAP_FreeLocalTx_CCITT(did);
        //The IwfFsm objects have already been cleaned up
        //Hence, just erasing the map entries
        m_tcapDialogueIdTxnEntryMap.erase(tcapDialogueIdTxnEntryIter++);
    }

    map<ITS_CTXT, TCAP_Dialogue*>::iterator tcapDialogueIdDialogueIter;
    for (tcapDialogueIdDialogueIter = m_rcvdTcapDialogueIdDialogueMap.begin(); tcapDialogueIdDialogueIter != m_rcvdTcapDialogueIdDialogueMap.end(); ) {

        //The TCAP_Dialogue objects have already been cleaned up
        //Hence, just erasing the map entries
        m_rcvdTcapDialogueIdDialogueMap.erase(tcapDialogueIdDialogueIter++);
    }

    map<std::string, SessionCtxt*>::iterator imsiMapIter;
    for (imsiMapIter = m_imsiMap.begin(); imsiMapIter != m_imsiMap.end();) {

        SessionCtxt *sessionCtxt = imsiMapIter->second;

        if (sessionCtxt != NULL) {
            delete sessionCtxt;
            sessionCtxt = NULL;
        }

        m_imsiMap.erase(imsiMapIter++);
        DECREMENT_SSG_STATS_CURRENT_ACTIVE_SUBSCRIBERS;
    }

    //NOTE: CleanUp subscriber audit map
    if(IwfController::Instance().Config().LocalConfig().IsClearSessionContextSet())
    {
        StopSubscrAuditTimer();
        unordered_map<std::string, IwfCallSessionContext*>::iterator suscMapIter;
        for(suscMapIter = m_subscriberTable->begin(); suscMapIter != m_subscriberTable->end();) {

            IwfCallSessionContext* ctxt = suscMapIter->second;
            m_subscriberTable->erase(suscMapIter);
            m_subscrAuditList->erase(ctxt->GetAuditIterator());

            delete ctxt;
        }
    }
}

int TransactionManager::ProcessDiaMsg(DIA_BASE_CMD *diaCmd) {

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    //DLOG_DEBUG("TransactionManager::processDiaMsg() Entry");

    int ret = ITS_SUCCESS;

    try {

    diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(diaCmd))->GetBaseGenCommand();

    if ( diaBaseGenCmd->countSessionId() > 0 )
    {
        std::string diaSessionId = diaBaseGenCmd->getSessionId()->value();
        unsigned int diaSessionIdx = diaBaseGenCmd->getSessionIndex();

        map<std::string, IwfFsm*>::iterator diaSessIdTxnEntryMapIter = m_diaSessionIdTxnEntryMap.find(diaSessionId);

        map<ITS_CTXT, IwfFsm*>::iterator tcapDialogueIdTxnEntryIter;

        map<ITS_CTXT, TCAP_Dialogue*>::iterator rcvdTcapDialogueIdDialogueIter;

        IwfFsm *iwfFsm = NULL;

        if (diaSessIdTxnEntryMapIter != m_diaSessionIdTxnEntryMap.end()) {

            iwfFsm = static_cast<IwfFsm *> (diaSessIdTxnEntryMapIter->second);

            if (diaBaseGenCmd->isRequest()) {

                if(IsInterimMsg(iwfFsm, iwfFsm->GetUpstrmReqProtocol(), diaCmd, NULL, NULL))
                {
                    iwfFsm->MakeStateTransition(RECV_INTRM_DNSTRM_REQ, diaCmd, NULL, NULL);
                }
                else
                {
                    DLOG_CRITICAL("Diameter REQUEST received in state %s. Session id %s already exists. This is NOT allowed. Cleaning up",
                            iwfFsm->GetCurrentStateName(),
                            diaSessionId.c_str());

                    if (!(diaBaseGenCmd->isRetransmit()))
                    {
                        this->ResetCurrRcvdDiaMsg(iwfFsm);
                        iwfFsm->MakeStateTransition(ERROR, diaCmd, NULL, NULL);
                        if(iwfFsm)
                        {
                            delete iwfFsm;
                            iwfFsm = NULL;
                        }
                    }
                }
            }
            else
            {
                /*DLOG_DEBUG("Diameter RESPONSE received in state %s. Session id %s already exists",
                        iwfFsm->GetCurrentStateName(),
                        diaSessionId.c_str());*/

                this->ResetCurrRcvdDiaMsg(iwfFsm);

                if (iwfFsm->GetUpstrmReqProtocol() == MAP_GR)
                {
                    ITS_UINT pointCode = GetOPC(iwfFsm);
                    if (IwfHssToSgsnCache::getInstance()->isEntryPresentFor(diaBaseGenCmd->getOriginHost()->value()))
                    {
                        if(!IwfHssToSgsnCache::getInstance()->isSgsnPresent(diaBaseGenCmd->getOriginHost()->value(), pointCode))
                        {
                            SCCPParameters sccpParam;
                            GetSCCPParameters(iwfFsm, sccpParam);
                            SHssWatcherInfo osHssWatcherInfo;
                            //Add SGSN to exsiting entry
                            IwfHssToSgsnCache::getInstance()->addSgsn(diaBaseGenCmd->getOriginHost()->value(), sccpParam);
                        }
                    }
                    else
                    {
                        SCCPParameters sccpParam;
                        GetSCCPParameters(iwfFsm, sccpParam);
                        SHssWatcherInfo osHssWatcherInfo;
                        //Alloc HSS Num
                        std::string strHssNum = IwfHssToSgsnCache::getInstance()->allocE164Num();
                        osHssWatcherInfo.m_strHssNumber = strHssNum;
                        osHssWatcherInfo.m_vecSgsn.push_back(sccpParam);

                        //Crate entry in OrigHost ---> HSS Num, SGSNAddr map
                        IwfHssToSgsnCache::getInstance()->addElement(diaBaseGenCmd->getOriginHost()->value(), osHssWatcherInfo);
                    }
                }

                if(IsInterimMsg(iwfFsm, iwfFsm->GetUpstrmReqProtocol(),diaCmd, NULL, NULL))
                {
                    iwfFsm->MakeStateTransition(RECV_INTRM_DNSTRM_RESP, diaCmd, NULL, NULL);
                    if (IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
                    {
                        IwfTranslator *translator = iwfFsm->GetTranslator();
                        if (translator != NULL)
                        {
                            std::string diaSessionId = iwfFsm->GetDiaSessionId();
                            if (translator->GetTranslatorState(iwfFsm) == RRB_SENT ||
                                    translator->GetTranslatorState(iwfFsm) == FOLLOW_ON)
                            {
                                iwfFsm->UpdateIwfFsmReplicableData();
                                uint32_t indexKey = IwfController::GetNextReplicationEntryFromFreeList();
                                iwfFsm->SetReplicaIndexKey(indexKey);
                                /*DLOG_DEBUG("Creating Replication entry for SessionId : %s with index Key :%d",
                                        diaSessionId.c_str(),indexKey);*/
                                if ( indexKey != 0xffffffff)
                                {
                                    ReplicableData::CreateTransactionEntryInReplica(IWF_SESSION_ENTRY_LIST,
                                            indexKey, diaSessionId);
                                    iwfFsm->CreateEntryInReplica(IWF_STATE_REPLICATION, diaSessionId);
                                }
                                else
                                {
                                    DLOG_CRITICAL("Replicaiton limit reached, these session will not be replicated");
                                }
                            }
                            else if (translator->GetTranslatorState(iwfFsm) == ACH_SENT ||
                                    translator->GetTranslatorState(iwfFsm) == FAKE_ACH_SENT ||
                                    translator->GetTranslatorState(iwfFsm) == IS_FOLLOW_ON )
                            {
                                /*DLOG_DEBUG("Updating Replication entry for SessionId : %s with index Key :%d",
                                        diaSessionId.c_str(),iwfFsm->GetReplicaIndexKey());*/
                                if (iwfFsm->GetReplicaIndexKey() != 0xffffffff)
                                {
                                    iwfFsm->UpdateIwfFsmReplicableData();
                                    iwfFsm->UpdateEntryInReplica(IWF_STATE_REPLICATION, diaSessionId, MAX_COUCHBASE_TTL);
                                    iwfFsm->UpdateTransactionEntryInReplica(IWF_SESSION_ENTRY_LIST, iwfFsm->GetReplicaIndexKey(), diaSessionId, MAX_COUCHBASE_TTL);
                                }
                                else
                                {
                                    DLOG_CRITICAL("Replicaiton limit reached, these session will not be replicated");
                                }

                            }
                        }
                        DIA_BASE_CMD *currRcvdDiaMsg = iwfFsm->GetCurrRcvdDiaMsg();

                        if (currRcvdDiaMsg != NULL) 
                        {
                            diameter::base::BaseGenericCommand* dbGenCmd = (const_cast<DIA_BASE_CMD*>(currRcvdDiaMsg))->GetBaseGenCommand();

                            if(dbGenCmd != NULL && dbGenCmd->getOriginHost())
                            {
                                // Check if there is any message queued for this peer/session already and try to send it next
                                std::string& origHost = const_cast<std::string&>(dbGenCmd->getOriginHost()->value());
                                ProcessPendingDiaMsgs(origHost, diaSessionId);
                            }
                        }
                    }
                }
                else if((iwfFsm->GetUpstrmReqProtocol() == MAP_GR) && IsSubscriptionDataPresentInULA(diaCmd))
                {
                    iwfFsm->SetIntmdteIsdSent(true);
                    iwfFsm->MakeStateTransition(RECV_CBDNSTRM_RESP, diaCmd, NULL, NULL);
                }
                else
                {
                    iwfFsm->MakeStateTransition(RECV_DNSTRM_RESP, diaCmd, NULL, NULL);
                }

                std::string userName;

                // For CAP session context is not used. Details are extracted
                // from the IwfFsm itself
                // TODO add a translator method like IsStateful, instead of the
                // upstream protocol check
                if(iwfFsm->GetUpstrmReqProtocol() != CAP_GE &&
                        !iwfFsm->GetImsi().empty() && !iwfFsm->IsCurrSendErr())
                {
                    userName = iwfFsm->GetImsi().c_str();
                    map<std::string, SessionCtxt*>::iterator imsiMapIter = m_imsiMap.find(userName);

                    if (imsiMapIter == m_imsiMap.end())
                    {
                        // Check if the session context is present in CB and fetch
                        if(!iwfFsm->IsSessionPurged())
                        {
                            SessionCtxt *sessionCtxt = new SessionCtxt();

                            if (IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
                            {
                                int retVal = sessionCtxt->FetchEntryInReplica(IWF_SESSION_CONTEXT_REPLICA, userName);

                                if (retVal == REPL_KEY_ENOENT)
                                {
                                    SCCPParameters sccpParam;
                                    GetSCCPParameters(iwfFsm, sccpParam);

                                    //NOTE: Creating Session context for new imsi for the first time
                                    std::string& origHost = const_cast<std::string&>(diaBaseGenCmd->getOriginHost()->value());
                                    sessionCtxt->SetOriginHost(origHost);
                                    std::string& origRealm = const_cast<std::string&>(diaBaseGenCmd->getOriginRealm()->value());
                                    sessionCtxt->SetOriginRealm(origRealm);
                                    sessionCtxt->SetPbSccpParameters(sccpParam);
                                    DLOG_DEBUG("New Session Context created for IMSI %s with Origin Host %s and Origin Realm %s",
                                            userName.c_str(), origHost.c_str(), origRealm.c_str());
                                    sessionCtxt->CreateEntryInReplica(IWF_SESSION_CONTEXT_REPLICA, userName);
                                }
                                else if (retVal == PB_REPL_UTILS_SUCCESS)
                                {
                                    DLOG_DEBUG("Session Context re-created from replica for IMSI %s with Origin Host %s and Origin Realm %s",
                                            userName.c_str(), sessionCtxt->GetOriginHost().c_str(), sessionCtxt->GetOriginRealm().c_str());
                                    std::string& origHost = const_cast<std::string&>(diaBaseGenCmd->getOriginHost()->value());
                                    sessionCtxt->SetOriginHost(origHost);
                                    std::string& origRealm = const_cast<std::string&>(diaBaseGenCmd->getOriginRealm()->value());
                                    sessionCtxt->SetOriginRealm(origRealm);
                                    DLOG_DEBUG("Session Context for IMSI %s updated with Origin Host %s and Origin Realm %s",
                                            userName.c_str(), origHost.c_str(), origRealm.c_str());
                                    sessionCtxt->UpdateEntryInReplica(IWF_SESSION_CONTEXT_REPLICA, userName);
                                }
                            }
                            else
                            {
                                SCCPParameters sccpParam;
                                GetSCCPParameters(iwfFsm, sccpParam);

                                //NOTE: Creating Session context for new imsi for the first time
                                std::string& origHost = const_cast<std::string&>(diaBaseGenCmd->getOriginHost()->value());
                                sessionCtxt->SetOriginHost(origHost);
                                std::string& origRealm = const_cast<std::string&>(diaBaseGenCmd->getOriginRealm()->value());
                                sessionCtxt->SetOriginRealm(origRealm);
                                sessionCtxt->SetPbSccpParameters(sccpParam);
                                DLOG_DEBUG("New Session Context created for IMSI %s with Origin Host %s and Origin Realm %s",
                                        userName.c_str(), origHost.c_str(), origRealm.c_str());

                            }
                            m_imsiMap.insert(pair<std::string, SessionCtxt*> (userName, sessionCtxt));
                            INCREMENT_SSG_STATS_CURRENT_ACTIVE_SUBSCRIBERS;
                            iwfFsm->PurgeSession(false);
                        }

                        //NOTE: Insert into Subscriber context map
                        if(IwfController::Instance().Config().LocalConfig().IsClearSessionContextSet())
                        {
                            IwfCallSessionContext *SubscriberCallContext = new IwfCallSessionContext();
                            InsertSubscriberContext(userName, SubscriberCallContext);
                        }
                    }
                    else
                    {
                        SessionCtxt *sctxt= imsiMapIter->second;
                        std::string& origHost = const_cast<std::string&>(diaBaseGenCmd->getOriginHost()->value());
                        sctxt->SetOriginHost(origHost);
                        std::string& origRealm = const_cast<std::string&>(diaBaseGenCmd->getOriginRealm()->value());
                        sctxt->SetOriginRealm(origRealm);
                        DLOG_DEBUG("Session Context for IMSI %s updated with Origin Host %s and Origin Realm %s",
                                userName.c_str(), origHost.c_str(), origRealm.c_str());
                        sctxt->UpdateEntryInReplica(IWF_SESSION_CONTEXT_REPLICA, userName);

                        if(IwfController::Instance().Config().LocalConfig().IsClearSessionContextSet())
                        {
                            //NOTE: Update Subscriber Context
                            LookupSubscriberContext(userName);
                        }
                    }
                }
            }
        } else {

            if(IsRcvdDiaMsgResetResp(diaCmd))
            {
                DLOG_DEBUG("Reset Response Received from peer, Consume the message");
                delete diaCmd;
                diaCmd = NULL;
                return ITS_SUCCESS;
            }
            if((IwfController::Instance().Config().LocalConfig().isCongestionManagementEnabled()) &&
                    CurrentFSMCount >= IwfController::Instance().Config().LocalConfig().GetMaxNumberOfSessionsToHold())
            {
                //NOTE: Check for Congestion Management
                DLOG_CRITICAL("Max Number of Sessions %d reached dropping the new requests.",
                        IwfController::Instance().Config().LocalConfig().GetMaxNumberOfSessionsToHold());
                delete diaCmd;
                diaCmd = NULL;
                return !ITS_SUCCESS;
            }
            
	    if (diaBaseGenCmd->isRequest()) {
		    // Build IwfFsm only if its new diameter session request
		    iwfFsm = new IwfFsm(this, CLOSED);

		    iwfFsm->SetUpstrmReqProtocol(DIAMETER_S6A);
		    iwfFsm->SetDnstrmReqProtocol(MAP_GR);

		    iwfFsm->SetDiaSessionId(diaSessionId);
		    iwfFsm->SetDiaSessionIdx(diaSessionIdx);

		    /* Check and save the ProxyInfo AVPs */
		    //DLOG_DEBUG(" Rcvd ProfyInfo Count = %d", diaCmd->countProxyInfo());
		    for (int pxyInfoIdx = 0; pxyInfoIdx < diaCmd->countProxyInfo(); pxyInfoIdx++)
		    {
			    const diameter::base::ProxyInfo *proxyInfo = diaBaseGenCmd->getProxyInfo(pxyInfoIdx);
			    iwfFsm->AddProxyInfo(*proxyInfo);
		    }

		    m_diaSessionIdTxnEntryMap.insert(pair<std::string, IwfFsm*> (diaSessionId, iwfFsm));

		    /*DLOG_DEBUG("Diameter REQUEST received in state %s. Created transaction entry for new session id %s",
				    iwfFsm->GetCurrentStateName(),
				    diaSessionId.c_str());*/

		    this->ResetCurrRcvdDiaMsg(iwfFsm);
		    iwfFsm->MakeStateTransition(RECV_UPSTRM_REQ, diaCmd, NULL, NULL);

		    if(iwfFsm->IsMovingToCloseState())
		    {
			    //NOTE: After processing RSR explicitly move to CLOSE STATE to clean up FSM
			    iwfFsm->SetCurrentState(CLOSED);
		    }
	    } else {
		DLOG_ERROR("Dropping the answer message received for session id %s as session context not found", diaSessionId.c_str());
	    }
        }

        if (iwfFsm != NULL) {

            if (iwfFsm->GetUpstrmReqProtocol() == DIAMETER_S6A &&
                    !IsRcvdDiaReqMsgServerInitiated(iwfFsm->GetCurrRcvdDiaMsg()))
            {
                std::string userName;

                if(diaBaseGenCmd->getUserName())
                {
                    userName = diaBaseGenCmd->getUserName()->value();

                    std::string imsi(userName.substr(0, userName.find('@')));

                    SessionCtxt *sessionCtxt = GetSessionCtxt(imsi);

                    if (!sessionCtxt)
                    {
                        sessionCtxt = new SessionCtxt();
                        std::string& origHost = const_cast<std::string&>(diaBaseGenCmd->getOriginHost()->value());
                        sessionCtxt->SetOriginHost(origHost);
                        std::string& origRealm = const_cast<std::string&>(diaBaseGenCmd->getOriginRealm()->value());
                        sessionCtxt->SetOriginRealm(origRealm);
                        sessionCtxt->CreateEntryInReplica(IWF_SESSION_CONTEXT_REPLICA, imsi);
                    }

                    if(m_imsiMap.find(imsi) == m_imsiMap.end())
                    {
                        m_imsiMap.insert(pair<std::string, SessionCtxt*> (imsi, sessionCtxt));
                        INCREMENT_SSG_STATS_CURRENT_ACTIVE_SUBSCRIBERS;
                    }

                    if(IwfController::Instance().Config().LocalConfig().IsClearSessionContextSet())
                    {
                        //NOTE: Insert into Subscriber context map
                        IwfCallSessionContext *SubscriberCallContext = new IwfCallSessionContext();
                        InsertSubscriberContext(imsi, SubscriberCallContext);
                    }
                }
            }

            if (iwfFsm->IsCurrSendErr()) {

                iwfFsm->MakeStateTransition(ERROR, diaCmd, NULL, NULL);
                delete iwfFsm;
                iwfFsm = NULL;

            } else if (iwfFsm->GetCurrentStateId() == CLOSED) {

                std::string diaSessionId = iwfFsm->GetDiaSessionId();
                ITS_CTXT tcapDlgId = iwfFsm->GetTcapDlgId();

                if (IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
                {
                    uint32_t indexKey = iwfFsm->GetReplicaIndexKey();

                    if (iwfFsm->IsFsmMarkedForDeletion())
                    {
                        DLOG_DEBUG("FSM entry for SessionId : %s with index Key :%d is already marked for deletion",
                                diaSessionId.c_str(),indexKey);
                    }
                    else
                    {
                        iwfFsm->MarkFsmForDeletion(true);
                        /*DLOG_DEBUG("Deleting Replication entry for SessionId : %s with index Key :%d",
                                diaSessionId.c_str(),indexKey);*/
                        if ( indexKey != 0xffffffff)
			{
				if (ReplicableData::DeleteTransactionEntryInReplica(IWF_SESSION_ENTRY_LIST, indexKey) != PB_REPL_UTILS_SUCCESS)
				{
					// Unable to delete from CB, save it for future
					DLOG_DEBUG("Unable to delete [ %s ] from CB, save it for future", diaSessionId.c_str());
					m_cbFlushGuard.Acquire();
					m_sessionsToFlushFromCB.insert(pair<int, std::string> (indexKey, diaSessionId));
					IwfController::Instance().StartBulkFetchTimer();
					m_cbFlushGuard.Release();
				}
				else
				{
					iwfFsm->DeleteEntryInReplica(IWF_STATE_REPLICATION, diaSessionId);
					IwfController::SetReplicationEntryToFreeList(indexKey);
				}
			}
                    }
                }

                diaSessIdTxnEntryMapIter = m_diaSessionIdTxnEntryMap.find(diaSessionId);

                if (diaSessIdTxnEntryMapIter != m_diaSessionIdTxnEntryMap.end())
                    m_diaSessionIdTxnEntryMap.erase(diaSessIdTxnEntryMapIter);

                tcapDialogueIdTxnEntryIter = m_tcapDialogueIdTxnEntryMap.find(tcapDlgId);
                if (tcapDialogueIdTxnEntryIter != m_tcapDialogueIdTxnEntryMap.end())
                    m_tcapDialogueIdTxnEntryMap.erase(tcapDialogueIdTxnEntryIter);

                rcvdTcapDialogueIdDialogueIter = m_rcvdTcapDialogueIdDialogueMap.find(tcapDlgId);
                if (rcvdTcapDialogueIdDialogueIter != m_rcvdTcapDialogueIdDialogueMap.end())
                {
                    TCAP_Dialogue *tcapDialogue = rcvdTcapDialogueIdDialogueIter->second;
                    m_rcvdTcapDialogueIdDialogueMap.erase(rcvdTcapDialogueIdDialogueIter);

                    if(tcapDialogue != NULL)
                    {
                        delete tcapDialogue;
                        tcapDialogue = NULL;
                    }
                }

                if(NULL != iwfFsm)
                    iwfFsm->SetCurrRcvdTcapDlg(NULL);

                this->ResetCurrRcvdDiaMsg(iwfFsm);
                this->ResetCurrRcvdTcapMsg(iwfFsm);

                delete iwfFsm;
                iwfFsm = NULL;
            }
        }

        if (iwfFsm)
        {
            iwfFsm->SetFlowFailure(false);
        }
    }
    else
    {
        DLOG_ERROR("Diameter message received without SessionId, dropping the recieved message...!");
    }
    }
    catch(std::exception& e)
    {
        DLOG_ERROR("### Exception on decode %s ###", e.what());
    }
    catch(...)
    {
        DLOG_ERROR("### Unknown exception on Decode ###");
    }
    //DLOG_DEBUG("TransactionManager::processDiaMsg() Exit");

    return ret;
}

int TransactionManager::ProcessTcapMsg(ITS_Event &itsEvent) {

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::processTcapMsg() Entry");

    int ret = ITS_SUCCESS;

    ITS_CTXT tcapDlgId;

    TCAP_Dialogue *tcapDlg = NULL;
    TCAP_Component *tcapCpt = NULL;

    ITS_USHORT tcapCptType = 0;
    ITS_USHORT tcapDlgType = 0;

    IwfFsm *iwfFsm = NULL;
    static stringstream strSgsn;

    tcapDlgId = ITS_GET_CTXT(&itsEvent.GetData()[1]);

    map<ITS_CTXT, IwfFsm*>::iterator tcapDialogueIdTxnEntryIter = m_tcapDialogueIdTxnEntryMap.find(tcapDlgId);

    map<ITS_CTXT, TCAP_Dialogue*>::iterator rcvdTcapDialogueIdDialogueIter = m_rcvdTcapDialogueIdDialogueMap.find(tcapDlgId);

    map<std::string, IwfFsm*>::iterator diaSessIdTxnEntryMapIter;

    switch (TCAP_MSG_TYPE(&(itsEvent.GetEvent()))) {

        case ITS_TCAP_DLG:

            //DLOG_DEBUG("Received TCAP dialogue with dialogue id %d", tcapDlgId);

            if ((ret = TCAP_Dialogue::Receive(ISS7_Stack, itsEvent, &tcapDlg)) != ITS_SUCCESS) {

                DLOG_CRITICAL("Error retrieving TCAP dialogue");

                if (tcapDlg != NULL) {
                    delete tcapDlg;
                    tcapDlg = NULL;
                }

                break;
            }

            if(tcapDlg->GetDialogueType() == TCPPT_TC_NOTICE)
            {
                TCAP_Notice *tcapNotice = (TCAP_Notice*)tcapDlg;
                DLOG_WARNING("TCAP notice received for DialogueId [ %d ] with Report cause [ %d ]", tcapDlgId, tcapNotice->GetReportCause());
                break;
            }

            if (!tcapDlg->IsComponentPresent()) {
                DLOG_WARNING("TCAP dialogue with dialogue id %d does not have a TCAP component", tcapDlgId);
                if(tcapDlg->GetDialogueType() == TCPPT_TC_P_ABORT ||
                        tcapDlg->GetDialogueType() == TCPPT_TC_U_ABORT)
                {
                    DLOG_WARNING("TCAP Abort Received without Component DialogueId = %d", tcapDlgId);
                    if (rcvdTcapDialogueIdDialogueIter != m_rcvdTcapDialogueIdDialogueMap.end())
                    {
                        if(tcapDialogueIdTxnEntryIter == m_tcapDialogueIdTxnEntryMap.end())
                        {
                            DLOG_WARNING(" Unable to get FSMContext for DialogueId = %d, no action taken.",tcapDlgId);
                            break;
                        }
                        iwfFsm = tcapDialogueIdTxnEntryIter->second;
                        this->ResetCurrRcvdTcapMsg(iwfFsm);
                        iwfFsm->MakeStateTransition(RECV_UPSTRM_RESP, NULL, tcapDlg, NULL);
                    }
                }


                break;
            }

            if (rcvdTcapDialogueIdDialogueIter != m_rcvdTcapDialogueIdDialogueMap.end()) {

                DLOG_DEBUG("TCAP dialogue object found for dialogue id %d. Deleting dialogue object", tcapDlgId);

                TCAP_Dialogue *tcapDialogue = rcvdTcapDialogueIdDialogueIter->second;
                m_rcvdTcapDialogueIdDialogueMap.erase(rcvdTcapDialogueIdDialogueIter);

                if (tcapDialogue != NULL)
                {
                    delete tcapDialogue;
                    tcapDialogue = NULL;
                }

		if(tcapDialogueIdTxnEntryIter != m_tcapDialogueIdTxnEntryMap.end()) {
			iwfFsm = tcapDialogueIdTxnEntryIter->second;

			if (iwfFsm != NULL)
				iwfFsm->SetCurrRcvdTcapDlg(NULL);

			if(tcapDlg->GetDialogueType() == TCPPT_TC_P_ABORT ||
					tcapDlg->GetDialogueType() == TCPPT_TC_U_ABORT)
			{
				DLOG_DEBUG("TCAP Abort Received with DialogueId = %d", tcapDlgId);
				this->ResetCurrRcvdTcapMsg(iwfFsm);
				iwfFsm->MakeStateTransition(RECV_UPSTRM_RESP, NULL, tcapDlg, NULL);
			}
		} else {
			DLOG_WARNING("Unable to get FSMContext for DialogueId = %d",tcapDlgId);
		}
            }

            DLOG_DEBUG("Creating TCAP dialogue id <---> newly received dialogue object mapping for dialogue id %d", tcapDlgId);

            m_rcvdTcapDialogueIdDialogueMap.insert(pair<ITS_CTXT, TCAP_Dialogue*> (tcapDlgId, tcapDlg));
            if (iwfFsm != NULL)
                iwfFsm->SetCurrRcvdTcapDlg(tcapDlg);

            if (tcapDlg->GetDialogueType() == TCPPT_TC_BEGIN || tcapDlg->GetDialogueType() == TCPPT_TC_UNI)
            {
                TCAP_Begin *begin = (TCAP_Begin*)tcapDlg;
                ITS_UINT pointCode = 0;

                bool isNational = false;
                ITS_OCTET ssn = 0;
                begin->GetOrigAddr(isNational, pointCode, ssn);
                if (iwfFsm)
                {
                    SCCP_CallingPartyAddr cgPA;
                    begin->GetOrigAddr(cgPA);
                    iwfFsm->SetCallingPartyAddr((SCCP_Address*)&cgPA);
                }
                begin->GetOPC(pointCode);
                this->SetOrigSSN(ssn);
                this->SetNetworkIndicatorFlag(isNational);
                if (ssn == SGSN_SSN)
                {
                    strSgsn.str(std::string());
                    strSgsn << pointCode;
                }

                SCCP_CalledPartyAddr destAddr;
                begin->GetDestAddr(destAddr);
                this->SetDestCldPartyAddress(destAddr);
            }

            break;

        case ITS_TCAP_CPT:

            //DLOG_DEBUG("Received TCAP component for dialogue id %d", tcapDlgId);

            if (tcapDialogueIdTxnEntryIter != m_tcapDialogueIdTxnEntryMap.end()) {

                //DLOG_DEBUG("TCAP dialogue with dialogue id %d already exists", tcapDlgId);

                iwfFsm = static_cast<IwfFsm *> (tcapDialogueIdTxnEntryIter->second);

            } else {

                DLOG_DEBUG("New TCAP dialogue with dialogue id %d received. Creating transaction entry", tcapDlgId);

                iwfFsm = new IwfFsm(this, CLOSED);

                iwfFsm->SetTcapDlgId(tcapDlgId);
                /*if (!strSgsn.str().empty())
                  iwfFsm->SetSgsnAddress(strSgsn.str().c_str());*/

                m_tcapDialogueIdTxnEntryMap.insert(pair<ITS_CTXT, IwfFsm*> (tcapDlgId, iwfFsm));
            }

            if (rcvdTcapDialogueIdDialogueIter != m_rcvdTcapDialogueIdDialogueMap.end()) {

                tcapDlg = static_cast<TCAP_Dialogue *> (rcvdTcapDialogueIdDialogueIter->second);

                ITS_C_REQUIRE(tcapDlg != 0);

                if (tcapDlg->GetDialogueType() == TCPPT_TC_BEGIN || tcapDlg->GetDialogueType() == TCPPT_TC_UNI) {

                    TCAP_Begin *begin = (TCAP_Begin*) tcapDlg;

                    if (!iwfFsm->HasCallingPartyAddr())
                    {
                        SCCP_CallingPartyAddr cgPA;
                        begin->GetOrigAddr(cgPA);
                        iwfFsm->SetCallingPartyAddr((SCCP_Address*)&cgPA);
                    }

                    SCCP_CalledPartyAddr selfSccpAddr;
                    begin->GetDestAddr(selfSccpAddr);

                    iwfFsm->SetSelfSccpAddr(selfSccpAddr);

                    SetReqProtocols(iwfFsm);
                }
            }

            if ((ret = TCAP_Component::Receive(ISS7_Stack, itsEvent, tcapDlg, &tcapCpt)) != ITS_SUCCESS) {

                DLOG_CRITICAL("Error retrieving TCAP component for dialogue id %d", tcapDlgId);

                this->ResetCurrRcvdTcapMsg(iwfFsm);
                iwfFsm->MakeStateTransition(ERROR, NULL, tcapDlg, tcapCpt);

                if (tcapCpt) {
                    delete tcapCpt;
                    tcapCpt = NULL;
                }

                break;
            }

            if(tcapCpt)
            {
                UPDATE_SSG_STATS_NUM_OF_TCCOMP_RCVD;
                tcapCptType = tcapCpt->GetComponentType();
            }

            if (tcapCptType == TCPPT_TC_L_CANCEL) {

                DLOG_CRITICAL("TCAP Local CANCEL received for TCAP dialogue id %d", tcapDlgId);

                this->ResetCurrRcvdTcapMsg(iwfFsm);
                iwfFsm->MakeStateTransition(TIMEOUT, NULL, NULL, tcapCpt); //L_CANCEL is a primitive, hence dialogue object is NULL

            }
            else if (tcapCptType == TCPPT_TC_L_REJECT)
            {
                ITS_OCTET family, code;
                TCAP_Reject *rejc = dynamic_cast<TCAP_Reject *>(tcapCpt);
                rejc->GetProblem(family, code);

                DLOG_CRITICAL("TCAP Dialog Id obtained from the Event Data is %d", tcapDlgId);
                DLOG_CRITICAL("TCAP REJECT received with Dialog Id :%d Invoke Id :%d", rejc->GetDialogueID(), rejc->GetInvokeID());
                DLOG_CRITICAL("TCAP REJECT with Problem Type:%d Problem Code: %d", family, code);

                this->ResetCurrRcvdTcapMsg(iwfFsm);
                iwfFsm->SetErrorCode(IWF_EREJECT_COMP);
                iwfFsm->MakeStateTransition(ERROR, NULL, NULL, tcapCpt);

            }
            else {
                if(tcapDlg)
                {
                    tcapDlgType = tcapDlg->GetDialogueType();

                    switch (tcapCptType) {

                        case TCPPT_TC_INVOKE:

                            if (tcapDlgType == TCPPT_TC_BEGIN || tcapDlgType == TCPPT_TC_UNI)
                            {
                                // This is the first invoke
                                // Hence, this is an upstream request

                                //DLOG_DEBUG("TCAP INVOKE received for BEGIN with dialogue id %d", tcapDlgId);

                                if (!iwfFsm->HasCallingPartyAddr())
                                {
                                    SCCP_CallingPartyAddr cgPA;
                                    ((TCAP_Begin*)tcapDlg)->GetOrigAddr(cgPA);
                                    iwfFsm->SetCallingPartyAddr((SCCP_Address*)&cgPA);
                                }

                                this->ResetCurrRcvdTcapMsg(iwfFsm);
                                iwfFsm->MakeStateTransition(RECV_UPSTRM_REQ, NULL, tcapDlg, tcapCpt);

                            }
                            else if (tcapDlgType == TCPPT_TC_CONTINUE)
                            {
                                // This is an interim invoke
                                // It is assumed that Diameter is the request origination
                                // Hence, this is a downstream request

                                //DLOG_DEBUG("TCAP INVOKE received for CONTINUE with dialogue id %d", tcapDlgId);


                                this->ResetCurrRcvdTcapMsg(iwfFsm);

                                /*1. If the CAP Msg is Interim Response say ERB/ACR
                                 *   then IWF would have recved INTERIM_UPSTRM_RESP
                                 *   for which IWF sends INTERIM_UPSTRM_REQ which in this case
                                 *   will be CCR-U
                                 *   This is a INVOKE and not RESULT - This is a ACRARg*/

                                if(IsInterimMsg(iwfFsm, iwfFsm->GetUpstrmReqProtocol(),NULL,tcapDlg,tcapCpt))
                                {
                                    iwfFsm->MakeStateTransition(RECV_INTRM_UPSTRM_RESP, NULL, tcapDlg, tcapCpt);

                                    if (IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
                                    {
                                        IwfTranslator *translator = iwfFsm->GetTranslator();
                                        if (translator != NULL)
                                        {
                                            std::string diaSessionId = iwfFsm->GetDiaSessionId();

                                            TransState translatorState = translator->GetTranslatorState(iwfFsm);
                                            if ( (translatorState  == ERB_RCVD) ||
                                                    (translatorState == RRB_SENT) ||
                                                    (translatorState == ACR_CALLACT_TRUE) ||
                                                    (translatorState == ACR_CALLACT_FALSE) )
                                            {
                                                /*DLOG_DEBUG("Updating Replication entry for SessionId : %s with indexkey :%d",
                                                        diaSessionId.c_str(),iwfFsm->GetReplicaIndexKey());*/
                                                if (iwfFsm->GetReplicaIndexKey() != 0xffffffff)
                                                {
                                                    iwfFsm->UpdateIwfFsmReplicableData();
                                                    iwfFsm->UpdateEntryInReplica(IWF_STATE_REPLICATION, diaSessionId, MAX_COUCHBASE_TTL);
                                iwfFsm->UpdateTransactionEntryInReplica(IWF_SESSION_ENTRY_LIST, iwfFsm->GetReplicaIndexKey(), diaSessionId, MAX_COUCHBASE_TTL);
                                                }
                                                else
                                                {
                                                    DLOG_CRITICAL("Replicaiton limit reached, these session will not be replicated");
                                                }
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    iwfFsm->MakeStateTransition(RECV_DNSTRM_REQ, NULL, tcapDlg, tcapCpt);
                                }

                            } else if (tcapDlgType == TCPPT_TC_END) {

                                // This is the last invoke
                                // It is assumed that Diameter is the request originator
                                // Hence, this is a downstream response

                                //DLOG_DEBUG("TCAP INVOKE received for END with dialogue id %d", tcapDlgId);

                                this->ResetCurrRcvdTcapMsg(iwfFsm);
                                if(!IsInterimMsg(iwfFsm, iwfFsm->GetUpstrmReqProtocol(),NULL,tcapDlg,tcapCpt))
                                {
                                    iwfFsm->MakeStateTransition(RECV_UPSTRM_RESP, NULL, tcapDlg, tcapCpt);
                                    if (IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
                                    {
                                        IwfTranslator *translator = iwfFsm->GetTranslator();
                                        if (translator != NULL)
                                        {
                                            std::string diaSessionId = iwfFsm->GetDiaSessionId();

                                            TransState translatorState = translator->GetTranslatorState(iwfFsm);
                                            if ( (translatorState  == ERB_RCVD) ||
                                                    (translatorState == ACR_CALLACT_FALSE) ||
                                                    (translatorState == ACR_CALLACT_TRUE) ||
                                                    (translatorState == ER_SMS_RCVD) )
                                            {
                                                /*DLOG_DEBUG("Updating Replication entry for SessionId : %s with indexkey :%d",
                                                        diaSessionId.c_str(),iwfFsm->GetReplicaIndexKey());*/
                                                if (iwfFsm->GetReplicaIndexKey() != 0xffffffff)
                                                {
                                                    iwfFsm->UpdateIwfFsmReplicableData();
                                                    iwfFsm->UpdateEntryInReplica(IWF_STATE_REPLICATION, diaSessionId, MAX_COUCHBASE_TTL);
                                                    iwfFsm->UpdateTransactionEntryInReplica(IWF_SESSION_ENTRY_LIST, iwfFsm->GetReplicaIndexKey(), diaSessionId, MAX_COUCHBASE_TTL);
                                                }
                                                else
                                                {
                                                    DLOG_CRITICAL("Replicaiton limit reached, these session will not be replicated");
                                                }
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    iwfFsm->MakeStateTransition(RECV_DNSTRM_REQ, NULL, tcapDlg, tcapCpt);
                                }

                            } else {

                                DLOG_CRITICAL("TCAP INVOKE received for dialogue type %d with dialogue id %d",
                                        tcapDlgType,
                                        tcapDlgId);

                                this->ResetCurrRcvdTcapMsg(iwfFsm);
                                iwfFsm->MakeStateTransition(ERROR, NULL, tcapDlg, tcapCpt);
                            }

                            break;

                        case TCPPT_TC_RESULT_L:
                            if (tcapDlgType == TCPPT_TC_END) {

                                //DLOG_DEBUG("TCAP RESULT_L received for END with dialogue id %d", tcapDlgId);

                                this->ResetCurrRcvdTcapMsg(iwfFsm);
                                if(IsInterimMsg(iwfFsm, iwfFsm->GetUpstrmReqProtocol(),NULL,tcapDlg,tcapCpt))
                                {
                                    iwfFsm->MakeStateTransition(RECV_UPSTRM_RESP, NULL, tcapDlg, tcapCpt);
                                }
                                else
                                {
                                    iwfFsm->MakeStateTransition(RECV_DNSTRM_RESP, NULL, tcapDlg, tcapCpt);
                                }
                            }
                            else if (tcapDlgType == TCPPT_TC_CONTINUE)
                            {
                                //DLOG_DEBUG("TCAP RESULT_L received for CONTINUE with dialogue id %d", tcapDlgId);

                                this->ResetCurrRcvdTcapMsg(iwfFsm);
                                if(iwfFsm->GetUpstrmReqProtocol() == CAP_GE)
                                {
                                    //DLOG_DEBUG("Result Component received in TC_CONTINUE");
                                    iwfFsm->MakeStateTransition(RECV_INTRM_UPSTRM_RESP, NULL, tcapDlg, tcapCpt);
                                }
                                else
                                {
                                    iwfFsm->SetIntmdteIsdSent(false);
                                    iwfFsm->MakeStateTransition(RECV_UPSTRM_RESP, NULL, tcapDlg, tcapCpt);
                                }
                            }
                            else {

                                DLOG_CRITICAL("TCAP RESULT_L received for dialogue type %d with dialogue id %d",
                                        tcapDlgType,
                                        tcapDlgId);

                                this->ResetCurrRcvdTcapMsg(iwfFsm);
                                iwfFsm->MakeStateTransition(ERROR, NULL, tcapDlg, tcapCpt);
                            }

                            break;

                        case TCPPT_TC_U_ERROR:
                            if (tcapDlgType == TCPPT_TC_END) {

                                DLOG_DEBUG("TCAP ERROR received for END with dialogue id %d", tcapDlgId);

                                this->ResetCurrRcvdTcapMsg(iwfFsm);
                                if(IsInterimMsg(iwfFsm, iwfFsm->GetUpstrmReqProtocol(),NULL,tcapDlg,tcapCpt))
                                {
                                    iwfFsm->MakeStateTransition(RECV_UPSTRM_RESP, NULL, tcapDlg, tcapCpt);
                                }
                                else
                                {
                                    iwfFsm->MakeStateTransition(RECV_DNSTRM_RESP, NULL, tcapDlg, tcapCpt);
                                }
                            }
                            else if (tcapDlgType == TCPPT_TC_CONTINUE)
                            {
                                DLOG_CRITICAL("TCAP Error received for dialogue type %d with dialogue id %d",
                                        tcapDlgType,
                                        tcapDlgId);
                                this->ResetCurrRcvdTcapMsg(iwfFsm);
                                iwfFsm->MakeStateTransition(RECV_INTRM_UPSTRM_RESP, NULL, tcapDlg, tcapCpt);
                            }
                            else {

                                DLOG_CRITICAL("TCAP Error received for dialogue type %d with dialogue id %d",
                                        tcapDlgType,
                                        tcapDlgId);

                                this->ResetCurrRcvdTcapMsg(iwfFsm);
                                DLOG_DEBUG("TCAP Error received with dialogue id %d", tcapDlgId);
                                iwfFsm->MakeStateTransition(RECV_DNSTRM_RESP, NULL, tcapDlg, tcapCpt);
                            }


                            break;

                        default:

                            DLOG_CRITICAL("Unknown TCAP component received %d", (int) TCAP_MSG_TYPE((&itsEvent.GetEvent())));

                            this->ResetCurrRcvdTcapMsg(iwfFsm);
                            iwfFsm->MakeStateTransition(ERROR, NULL, tcapDlg, tcapCpt);

                            break;
                    }
                }
            }

            break;

        default:
            DLOG_CRITICAL("Unknown TCAP event received %d", (int) TCAP_MSG_TYPE((&itsEvent.GetEvent())));
    }

    if (iwfFsm != NULL) {

        if (iwfFsm->IsCurrSendErr()) {
            iwfFsm->MakeStateTransition(ERROR, NULL, tcapDlg, tcapCpt);
            delete iwfFsm;
            iwfFsm = NULL;
        }
        else if (iwfFsm->GetCurrentStateId() == CLOSED) {

            std::string diaSessionId = iwfFsm->GetDiaSessionId();
            ITS_CTXT tcapDlgId = iwfFsm->GetTcapDlgId();

            if (IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
            {
                uint32_t indexKey = iwfFsm->GetReplicaIndexKey();

                if (iwfFsm->IsFsmMarkedForDeletion())
                {
                        DLOG_DEBUG("FSM entry for SessionId : %s with index Key :%d is already marked for deletion",
                                diaSessionId.c_str(),indexKey);
                }
                else
                {
                    iwfFsm->MarkFsmForDeletion(true);
                    /*DLOG_DEBUG("Deleting replicaton entry for SessionId : %s with indexKey : %d",
                            diaSessionId.c_str(),indexKey);*/
#if 0
                    iwfFsm->DeleteEntryInReplica(IWF_STATE_REPLICATION, diaSessionId);
                    ReplicableData::DeleteTransactionEntryInReplica(IWF_SESSION_ENTRY_LIST,indexKey);
                    IwfController::SetReplicationEntryToFreeList(indexKey);
#endif

		    if ( indexKey != 0xffffffff)
		    {
			    if (ReplicableData::DeleteTransactionEntryInReplica(IWF_SESSION_ENTRY_LIST, indexKey) != PB_REPL_UTILS_SUCCESS)
			    {
				    // Unable to delete from CB, save it for future
				    DLOG_DEBUG("Unable to delete [ %s ] from CB, save it for future", diaSessionId.c_str());
				    m_cbFlushGuard.Acquire();
				    m_sessionsToFlushFromCB.insert(pair<int, std::string> (indexKey, diaSessionId));
				    IwfController::Instance().StartBulkFetchTimer();
				    m_cbFlushGuard.Release();
			    }
			    else
			    {
				    iwfFsm->DeleteEntryInReplica(IWF_STATE_REPLICATION, diaSessionId);
				    IwfController::SetReplicationEntryToFreeList(indexKey);
			    }
		    }
                }
            }

            diaSessIdTxnEntryMapIter = m_diaSessionIdTxnEntryMap.find(diaSessionId);
            if (diaSessIdTxnEntryMapIter != m_diaSessionIdTxnEntryMap.end())
                m_diaSessionIdTxnEntryMap.erase(diaSessIdTxnEntryMapIter);

            tcapDialogueIdTxnEntryIter = m_tcapDialogueIdTxnEntryMap.find(tcapDlgId);
            if (tcapDialogueIdTxnEntryIter != m_tcapDialogueIdTxnEntryMap.end())
                m_tcapDialogueIdTxnEntryMap.erase(tcapDialogueIdTxnEntryIter);

            rcvdTcapDialogueIdDialogueIter = m_rcvdTcapDialogueIdDialogueMap.find(tcapDlgId);
            if (rcvdTcapDialogueIdDialogueIter != m_rcvdTcapDialogueIdDialogueMap.end())
            {
                TCAP_Dialogue *tcapDialogue = rcvdTcapDialogueIdDialogueIter->second;
                m_rcvdTcapDialogueIdDialogueMap.erase(rcvdTcapDialogueIdDialogueIter);

                if(tcapDialogue != NULL)
                {
                    delete tcapDialogue;
                    tcapDialogue = NULL;
                }
            }

            if(NULL != iwfFsm)
                iwfFsm->SetCurrRcvdTcapDlg(NULL);

            this->ResetCurrRcvdDiaMsg(iwfFsm);
            this->ResetCurrRcvdTcapMsg(iwfFsm);

            delete iwfFsm;
            iwfFsm = NULL;
        }
    }
    if (iwfFsm)
    {
        iwfFsm->SetFlowFailure(false);
    }

    //DLOG_DEBUG("TransactionManager::processTcapMsg() Exit");

    return ret;
}

SessionCtxt* TransactionManager::GetSessionCtxt(const std::string& imsi) {


    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::GetSessionCtxt() Entry");

    map<std::string, SessionCtxt*>::iterator imsiMapIter = m_imsiMap.find(imsi);

    if (imsiMapIter != m_imsiMap.end())
    {
        //DLOG_DEBUG("TransactionManager::GetSessionCtxt() SessionContext Found in Map");
        //DLOG_DEBUG("TransactionManager::GetSessionCtxt() Exit");
        return (imsiMapIter->second);
    }
    else
    {
        //DLOG_DEBUG("TransactionManager::GetSessionCtxt() SessionContext Not Found in Map");
        // Check if the session context is present in CB and fetch
        if (IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
        {
            SessionCtxt *sessionCtxt = new SessionCtxt();

            int retVal = sessionCtxt->FetchEntryInReplica(IWF_SESSION_CONTEXT_REPLICA, imsi);

            if (retVal == REPL_KEY_ENOENT)
            {
                delete sessionCtxt;
                return NULL;
            }
            else if (retVal == PB_REPL_UTILS_SUCCESS)
            {
                if(m_imsiMap.find(imsi) == m_imsiMap.end())
                {
                    m_imsiMap.insert(pair<std::string, SessionCtxt*> (imsi, sessionCtxt));
                    INCREMENT_SSG_STATS_CURRENT_ACTIVE_SUBSCRIBERS;
                }
                return sessionCtxt;
            }
        }
    }

    //DLOG_DEBUG("TransactionManager::GetSessionCtxt() Exit");
    return NULL;
}

bool TransactionManager::PurgeSessionCtxt(const std::string& imsi) {

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::PurgeSessionCtxt() Entry");

    map<std::string, SessionCtxt*>::iterator imsiMapIter = m_imsiMap.find(imsi);

    if (imsiMapIter != m_imsiMap.end()) {

        SessionCtxt *sessionCtxt = imsiMapIter->second;

        if (sessionCtxt != NULL) {
            sessionCtxt->DeleteEntryInReplica(IWF_SESSION_CONTEXT_REPLICA, imsi);
            delete sessionCtxt;
            sessionCtxt = NULL;
        }

        m_imsiMap.erase(imsiMapIter);
        DECREMENT_SSG_STATS_CURRENT_ACTIVE_SUBSCRIBERS;

        //DLOG_DEBUG("Session context purged for IMSI %s", imsi.c_str());

        return true;

    } else {

        //DLOG_DEBUG("Session context purge failed for IMSI %s", imsi.c_str());

    }

    //DLOG_DEBUG("TransactionManager::PurgeSessionCtxt() Exit");
    return false;
}

void TransactionManager::SetSs7Active(bool isSs7Active) {

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::SetSs7Active() Entry");

    m_isSs7Active = isSs7Active;

    //DLOG_DEBUG("TransactionManager::SetSs7Active() Exit");
}

bool TransactionManager::IsSs7Active() {

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::IsSs7Active() Entry");

    //DLOG_DEBUG("TransactionManager::IsSs7Active() Entry");

    return m_isSs7Active;
}


int TransactionManager::ProcessErr(IwfFsm *iwfFsm) {

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::processErr() Entry");

    map<std::string, IwfFsm*>::iterator diaSessIdTxnEntryMapIter;

    map<ITS_CTXT, IwfFsm*>::iterator tcapDialogueIdTxnEntryIter;

    map<ITS_CTXT, TCAP_Dialogue*>::iterator rcvdTcapDialogueIdDialogueIter;

    if (iwfFsm != NULL) {

        IwfReturnAction retAction;
        DIA_BASE_CMD* outCmd = NULL;
        TCAP_Component* outCpt = NULL;

        if (iwfFsm->GetTranslator() != NULL)
        {
            int ret = iwfFsm->GetTranslator()->HandleError(iwfFsm, outCmd, outCpt, retAction);
            if (ret == ITS_SUCCESS)
            {
                if (retAction.action == IWF_RA_CONSUME_AND_RETRY)
                {
                    unsigned int diaSessionIdx = outCmd->getSessionIndex();
                    std::string diaSessionId = outCmd->getSessionId()->value();
#ifdef NO_QUEUEING
                    if ((ret = DiaFrame::GetDiaFrame()->Send(outCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
                    {
                        DLOG_DEBUG("ConsumeAndRetry: Diameter message with session id %s sent successfully", diaSessionId.c_str());

                    } else {
                        DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

                    }
#else
                    if ((ret = SendDiaMsgToStack(diaSessionId, outCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
                    {
                        DLOG_DEBUG("ConsumeAndRetry: Diameter message with session id %s sent successfully", diaSessionId.c_str());

                    } else {
                        DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

                    }
#endif
                    iwfFsm->GotoPrevState();
                    iwfFsm->SetErrorCode(ITS_SUCCESS);
                }
                else if (retAction.action == IWF_RA_RESPOND_AND_FORWARD_WITH_TERM)
                {
                    iwfFsm->GotoPrevState();
                    this->ClearDiaAndTcapSession(iwfFsm);
                }
                else if (retAction.action == IWF_RA_RESPOND_ONLY)
                {
                    if(iwfFsm->GetCurrRcvdTcapCpt())
                    {
                        //DLOG_DEBUG("Component Type %d", iwfFsm->GetCurrRcvdTcapCpt()->GetComponentType());
                        if(TCPPT_TC_L_REJECT == iwfFsm->GetCurrRcvdTcapCpt()->GetComponentType())
                        {
                            DLOG_DEBUG("Moving to Previous State for REJECT Case");
                            iwfFsm->GotoPrevState();
                        }
                    }
                    else
                    {
                        DLOG_DEBUG("Last Received Tcap Dialogue doesn't have component.");
                    }
                    this->ClearDiaAndTcapSession(iwfFsm);
                }
                else if (retAction.action == IWF_RA_CONSUME)
                {
                    this->ClearDiaAndTcapSession(iwfFsm);
                }
            }
        }

        if (iwfFsm->GetCurrentStateId() == CLOSED) {

            std::string diaSessionId = iwfFsm->GetDiaSessionId();
            DiaFrame::GetDiaFrame()->ReleaseSession(diaSessionId.c_str());
            ITS_CTXT tcapDlgId = iwfFsm->GetTcapDlgId();

            if (IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
            {
                uint32_t indexKey = iwfFsm->GetReplicaIndexKey();

                if (iwfFsm->IsFsmMarkedForDeletion())
                {
                    DLOG_DEBUG("FSM entry for SessionId : %s with index Key :%d is already marked for deletion",
                            diaSessionId.c_str(),indexKey);
                }
                else
                {
                    iwfFsm->MarkFsmForDeletion(true);
                    /*DLOG_DEBUG("Deleting replicaton entry for SessionId : %s with indexKey : %d",
                            diaSessionId.c_str(),indexKey);*/
#if 0
                    iwfFsm->DeleteEntryInReplica(IWF_STATE_REPLICATION, diaSessionId);
                    ReplicableData::DeleteTransactionEntryInReplica(IWF_SESSION_ENTRY_LIST,indexKey);
                    IwfController::SetReplicationEntryToFreeList(indexKey);
#endif
		    if ( indexKey != 0xffffffff)
		    {
			    if (ReplicableData::DeleteTransactionEntryInReplica(IWF_SESSION_ENTRY_LIST, indexKey) != PB_REPL_UTILS_SUCCESS)
			    {
				    // Unable to delete from CB, save it for future
				    DLOG_DEBUG("Unable to delete [ %s ] from CB, save it for future", diaSessionId.c_str());
				    m_cbFlushGuard.Acquire();
				    m_sessionsToFlushFromCB.insert(pair<int, std::string> (indexKey, diaSessionId));
				    IwfController::Instance().StartBulkFetchTimer();
				    m_cbFlushGuard.Release();
			    }
			    else
			    {
				    iwfFsm->DeleteEntryInReplica(IWF_STATE_REPLICATION, diaSessionId);
				    IwfController::SetReplicationEntryToFreeList(indexKey);
			    }
		    }
                }
            }
            diaSessIdTxnEntryMapIter = m_diaSessionIdTxnEntryMap.find(diaSessionId);
            if (diaSessIdTxnEntryMapIter != m_diaSessionIdTxnEntryMap.end())
                m_diaSessionIdTxnEntryMap.erase(diaSessIdTxnEntryMapIter);

            tcapDialogueIdTxnEntryIter = m_tcapDialogueIdTxnEntryMap.find(tcapDlgId);
            if (tcapDialogueIdTxnEntryIter != m_tcapDialogueIdTxnEntryMap.end())
                m_tcapDialogueIdTxnEntryMap.erase(tcapDialogueIdTxnEntryIter);

            rcvdTcapDialogueIdDialogueIter = m_rcvdTcapDialogueIdDialogueMap.find(tcapDlgId);
            if (rcvdTcapDialogueIdDialogueIter != m_rcvdTcapDialogueIdDialogueMap.end())
            {
                TCAP_Dialogue *tcapDialogue = rcvdTcapDialogueIdDialogueIter->second;
                m_rcvdTcapDialogueIdDialogueMap.erase(rcvdTcapDialogueIdDialogueIter);

                if(tcapDialogue != NULL)
                {
                    delete tcapDialogue;
                    tcapDialogue = NULL;
                }
            }
            if(NULL != iwfFsm)
                iwfFsm->SetCurrRcvdTcapDlg(NULL);

            this->ResetCurrRcvdTcapMsg(iwfFsm);
            this->ResetCurrRcvdDiaMsg(iwfFsm);
        }
    }

    //DLOG_DEBUG("TransactionManager::processErr() Exit");

    return ITS_SUCCESS;
}

int TransactionManager::SendTcapUni(IwfFsm *iwfFsm)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("TransactionManager::sendTcapUni() Entry");
    int ret = ITS_SUCCESS;
    RoutingParams *routingParams = NULL;
    IwfTranslator* translator = NULL;

    if (iwfFsm == NULL)
        return (!ITS_SUCCESS);

    if ((ret = GetRoutingParams(iwfFsm, routingParams)) != ITS_SUCCESS)
    {
        if((ret == ITS_ENOROUTE) && IsRcvdDiaMsgResetReq(iwfFsm->GetCurrRcvdDiaMsg()))
        {
            translator = IwfController::Instance().GetTranslator(MAP_TO_S6A_STR);
        }
        else
        {
            DLOG_CRITICAL("TransactionManager::sendTcapUni Unable to determine routing parameters");
            if (routingParams != NULL) {
                delete routingParams;
                routingParams = NULL;
            }
            return ret;
        }
    }
    else
    {
        translator = IwfController::Instance().GetTranslator(routingParams->transId);
    }


    ITS_CTXT tcapDlgId;

    if ((ret = TCAP_AllocateDialogueId(ISS7_Stack, &tcapDlgId)) != ITS_SUCCESS) {

        DLOG_CRITICAL("TransactionManager::sendTcapUni Unable to allocate TCAP dialogue id");

        if (routingParams != NULL) {
            delete routingParams;
            routingParams = NULL;
        }

        return ret;
    }

    TCAP_Unidirectional *uni = new TCAP_Unidirectional();

    uni->SetDialogueID(tcapDlgId);

    if(IsRcvdDiaMsgResetReq(iwfFsm->GetCurrRcvdDiaMsg()))
    {
        SCCPParameters sccpparam = iwfFsm->GetSgsnAddress();

        if (sccpparam.isRouteByGT)
        {
            ITS_OCTET l_addrInd = 0;

            std::vector<byte> vecGTTaddr = EncodeLocalGTTAddress(l_addrInd);

            uni->SetDestAddr(l_addrInd,
                    sccpparam.m_opc,
                    sccpparam.cpa_itu.m_ssn,
                    &vecGTTaddr[0], vecGTTaddr.size());

            std::vector<byte> gttaddr = EncodeRemoteGTTAddress(&sccpparam);
            ITS_OCTET   addrInd = sccpparam.cpd_itu.m_addrIndicator;
            uni->SetOrigAddr(addrInd,
                    sccpparam.m_dpc,
                    sccpparam.cpd_itu.m_ssn,
                    &gttaddr[0], gttaddr.size());
        }
        else
        {
            bool isNational = false;
            if (sccpparam.cpa_itu.m_addrIndicator & SCCP_CPA_ROUTE_INT)
            {
                isNational = false;
            }
            else if (sccpparam.cpa_itu.m_addrIndicator & SCCP_CPA_ROUTE_NAT)
            {
                isNational = true;
            }

            uni->SetDestAddr(isNational,
                    sccpparam.m_opc,
                    sccpparam.cpa_itu.m_ssn);
            if (sccpparam.cpd_itu.m_addrIndicator & SCCP_CPA_ROUTE_INT)
            {
                isNational = false;
            }
            else if (sccpparam.cpd_itu.m_addrIndicator & SCCP_CPA_ROUTE_NAT)
            {
                isNational = true;
            }
            uni->SetOrigAddr(isNational,
                    sccpparam.m_dpc,
                    sccpparam.cpd_itu.m_ssn);
        }
#if 0
        uni->SetOPC(sccpparam.m_dpc);
        uni->SetOrigAddr(sccpparam.cpd_itu);
        uni->SetDPC(sccpparam.m_opc);
        uni->SetDestAddr(sccpparam.cpa_itu);
#endif
    }
    else
    {
        if (!routingParams->routeByGT)
        {
            uni->SetOrigAddr(routingParams->isNational,
                    routingParams->oPc,
                    routingParams->oSsn);
            uni->SetDestAddr(routingParams->isNational,
                    routingParams->dPc,
                    routingParams->dSsn);
        }
        else
        {
            ITS_OCTET l_addrInd = 0;

            std::vector<byte> vecGTTaddr = EncodeLocalGTTAddress(l_addrInd);

            uni->SetOrigAddr(l_addrInd,
                    routingParams->oPc,
                    routingParams->oSsn,
                    &vecGTTaddr[0], vecGTTaddr.size());

            std::vector<byte> gttaddr = EncodeRemoteGTTAddress(routingParams);
            ITS_OCTET   addrInd = SCCP_CPA_ROUTE_GTTI |
                (routingParams->gti << 2);
            if (routingParams->dSSNPresent)
            {
                addrInd |= SCCP_CPA_HAS_SSN;
            }

            if (routingParams->isNational)
            {
                addrInd |= SCCP_CPA_ROUTE_NAT;
            }
            else
            {
                addrInd |= SCCP_CPA_ROUTE_INT;
            }
            uni->SetDestAddr(addrInd,
                    routingParams->aPc,
                    routingParams->dSsn,
                    &gttaddr[0], gttaddr.size());
        }
    }

    uni->SetQualityOfService(QOSI_SEQ_CTRL|QOSI_SLS_KEY|QOSI_RET_OPT, tcapDlgId % IWF_NUM_SLS);
    TCAP_Component *tcapCpt = NULL;
    TCAP_Invoke *tcapIvkCpt = NULL;
    IwfReturnAction retAct;
    DIA_BASE_CMD* outCmd = NULL;

    TcapCptList tcapCptList;
    if ((ret = translator->BuildTCAPMsg(iwfFsm, iwfFsm->GetCurrRcvdDiaMsg(),
                    &tcapCptList, outCmd, retAct)) != ITS_SUCCESS) {

        DLOG_CRITICAL("TransactionManager::sendTcapUni Unable to build TCAP component with MAP from Diameter message");

        if (tcapCpt != NULL) {
            delete tcapCpt;
            tcapCpt = NULL;
        }

        delete uni;
        uni = NULL;

        return ret;
    }

    if (retAct.action == IWF_RA_FORWARD ||
            retAct.action == IWF_RA_RESPOND_AND_FORWARD)
    {
        vector<byte> acEnc = map_common::EncodeApplicationContext(retAct.appContext);
        uni->SetApplicationContext(&acEnc[0], acEnc.size());

        std::list <TCAP_Component> outTcapCpt = tcapCptList.GetTcapCptList();
        tcapCptList.ClearTcapCptList();

        bool send = true;
        while(!outTcapCpt.empty())
        {
            TCAP_Component tcapCpt = outTcapCpt.front();
            if ((ret = TCAP_Component::Send(ISS7_Stack, uni, &tcapCpt)) != ITS_SUCCESS) {
                send = false;
                break;
            }
            UPDATE_SSG_STATS_NUM_OF_TCCOMP_SENT;
            outTcapCpt.pop_front();
        }
        if(send)
        {
            if ((ret = TCAP_Dialogue::Send(ISS7_Stack, uni)) != ITS_SUCCESS) {

                DLOG_CRITICAL("TransactionManager::sendTcapUni TCAP component sent successfully. But TCAP dialogue could not be sent");

            }
            else {

                DLOG_DEBUG("TCAP request with dialogue id %d successfully sent", tcapDlgId);
            }
        }
        else {
            DLOG_CRITICAL("TransactionManager::sendTcapUni Unable to send TCAP message");
        }
    }

    if (retAct.action == IWF_RA_RESPOND_AND_FORWARD && (!iwfFsm->IsDiaRespSent()))
    {
        // Send a dia response also, here the dia response doesn't wait for TCAP
        // response
        DIA_BASE_CMD *diaCmd = NULL;
        ret = translator->BuildDiaResponse(iwfFsm, iwfFsm->GetCurrRcvdDiaMsg(),
                diaCmd, retAct);
        if (ret != ITS_SUCCESS)
        {
            DLOG_ERROR("Unable to send Dia Response!!");

            delete tcapCpt;
            delete uni;
            delete routingParams;
            return ret;
        }

        diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(diaCmd))->GetBaseGenCommand();

        unsigned int diaSessionIdx = diaBaseGenCmd->getSessionIndex();
        std::string diaSessionId = diaBaseGenCmd->getSessionId()->value();

        if ((ret = DiaFrame::GetDiaFrame()->Send(diaCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
        {
            /* Remove the session entry from the m_diaSessionIdTxnEntryMap?
             * Or keep the entry and let the state machine destroy it */

            DLOG_DEBUG("Diameter message with session id %s mapping to dialog Id %d sent successfully", diaSessionId.c_str(),tcapDlgId);

        } else {
            DLOG_CRITICAL("Diameter message with session id %s mapping to dialog Id %d send failed", diaSessionId.c_str(),tcapDlgId);

        }

        /* commented because in diameter stack the Send function deletes the
         * diaCmd not need to delete explicitly */
        //delete diaCmd;
        //diaCmd = NULL;
    }

    if (routingParams != NULL) {
        delete routingParams;
        routingParams = NULL;
    }

    if (tcapCpt != NULL) {
        delete tcapCpt;
        tcapCpt = NULL;
        tcapIvkCpt = NULL;
    }

    if (uni != NULL) {
        delete uni;
        uni = NULL;
    }

    DLOG_DEBUG("TransactionManager::sendTcapUni() Exit");

    return ITS_SUCCESS;

}

int TransactionManager::SendTcapBegin(IwfFsm *iwfFsm) {

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("TransactionManager::sendTcapBegin() Entry");
    int ret = ITS_SUCCESS;
    RoutingParams *routingParams = NULL;
    IwfTranslator* translator = NULL;

    if (iwfFsm == NULL)
        return (!ITS_SUCCESS);

    try
    {
        DIA_BASE_CMD *cmd = iwfFsm->GetCurrRcvdDiaMsg();
        diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(cmd))->GetBaseGenCommand();

        if ((diaBaseGenCmd != NULL) && (diaBaseGenCmd->getHeader().code == DIA_CMD_RS))
        {
            DLOG_DEBUG("Received RESET..TransactionManager::sendTcapUni() Entry");
            //Get the related SGSN Numbers and send MAP Reset.
            IwfHssToSgsnCache* pocCache = IwfHssToSgsnCache::getInstance();
            if (pocCache)
            {
                vector<SCCPParameters> vecSgsn;
                pocCache->getSgsnListForHss(diaBaseGenCmd->getOriginHost()->value(), vecSgsn);
                if(!vecSgsn.empty())
                {
                    for(unsigned int iIndex = 0;iIndex < vecSgsn.size(); iIndex++)
                    {
                        iwfFsm->SetSgsnAddress(vecSgsn[iIndex]);
                        if(SendTcapUni(iwfFsm) != ITS_SUCCESS)
                        {
                            DLOG_ERROR("Unable to Build Tcap Uni Msg");
                            return !ITS_SUCCESS;
                        }
                        iwfFsm->SetDiaRespSent(true);
                    }
                }
                else
                {
                    DLOG_ERROR("getSgsnListForHss in empty ");
                    iwfFsm->SetErrorCode(ITS_DIA_UNABLE_TO_COMPLY);
                    return !ITS_SUCCESS;
                }
            }//End of if
            //NOTE: Move to close state after processing RSR Request from server
            iwfFsm->MoveToCloseState(true);
            return ITS_SUCCESS;
        }

        if((iwfFsm->GetUpstrmReqProtocol() == DIAMETER_S6A) && IsRcvdDiaReqMsgServerInitiated(iwfFsm->GetCurrRcvdDiaMsg()))
        {
            /* Should we take trnslatorId from sessionCtxt */
            translator = IwfController::Instance().GetTranslator(MAP_TO_S6A_STR);
        }
        else if ((ret = GetRoutingParams(iwfFsm, routingParams)) != ITS_SUCCESS)
        {
            DLOG_CRITICAL("TransactionManager::sendTcapBegin Unable to determine routing parameters");
            if (routingParams != NULL) {
                delete routingParams;
                routingParams = NULL;
            }
            iwfFsm->SetErrorCode(IwfController::Instance().Config().LocalConfig().DiaErroCode());
            return ret;
        }
        else
        {
            translator = IwfController::Instance().GetTranslator(routingParams->transId);
        }

        iwfFsm->SetTranslator(translator);

        ITS_CTXT tcapDlgId;

        if ((ret = TCAP_AllocateDialogueId(ISS7_Stack, &tcapDlgId)) != ITS_SUCCESS) {

            DLOG_CRITICAL("TransactionManager::sendTcapBegin Unable to allocate TCAP dialogue id");

            if (routingParams != NULL) {
                delete routingParams;
                routingParams = NULL;
            }

            return ret;
        }

        TCAP_Begin *begin = new TCAP_Begin();

        begin->SetDialogueID(tcapDlgId);

        if(iwfFsm->GetUpstrmReqProtocol() == DIAMETER_S6A && IsRcvdDiaReqMsgServerInitiated(iwfFsm->GetCurrRcvdDiaMsg()))
        {
            std::string userName = "";
            DIA_BASE_CMD *cmd = iwfFsm->GetCurrRcvdDiaMsg();
            diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(cmd))->GetBaseGenCommand();

            SessionCtxt *sctxt = NULL;

            if(diaBaseGenCmd->getUserName())
            {
                userName = diaBaseGenCmd->getUserName()->value();
                std::string temp(userName.substr(0, userName.find('@')));
                sctxt= iwfFsm->GetTransactionManager()->GetSessionCtxt(temp);
                if(sctxt != NULL)
                {
                    ITS_UINT pointCode = sctxt->GetPbSccpParameters().dpc();
                    begin->SetOPC(pointCode);
                    SCCP_CalledPartyAddr cpd_itu;
                    sctxt->GetCalledPartyAddr(&cpd_itu);
                    begin->SetOrigAddr(cpd_itu);
                }
                else
                {
                    DLOG_ERROR("TransactionManager::SendTcapBegin :: SessionContext not found for imsi : %s",
                            userName.c_str());
                    iwfFsm->SetErrorCode(DIAMETER_ERROR_USER_UNKNOWN);
                    if(begin != NULL)
                    {
                        delete begin;
                        begin = NULL;
                    }
                    return !ITS_SUCCESS;
                }
            }
        }
        else
        {
            //NOTE: Check the Destination is up or not else set the alternate Destination for routing
            if(IsDestinationAvailable(iwfFsm, routingParams->dSsn, routingParams->dPc, routingParams->isNational) == false)
            {
                DLOG_ERROR("Primary Destination is not Up");
                if((ret = GetAlternateRoutingParams(iwfFsm, routingParams)) != ITS_SUCCESS)
                {
                    DLOG_ERROR("Secondary Destination is not configured");
                }
            }

            if (!routingParams->routeByGT)
            {
                begin->SetOrigAddr(routingParams->isNational,
                        routingParams->oPc,
                        routingParams->oSsn);

                begin->SetDestAddr(routingParams->isNational,
                        routingParams->dPc,
                        routingParams->dSsn);
            }
            else
            {
                ITS_OCTET l_addrInd = 0;

                std::vector<byte> vecGTTaddr = EncodeLocalGTTAddress(l_addrInd);

                begin->SetOrigAddr(l_addrInd,
                        routingParams->oPc,
                        routingParams->oSsn,
                        &vecGTTaddr[0], vecGTTaddr.size());

                std::vector<byte> gttaddr = EncodeRemoteGTTAddress(routingParams);
                ITS_OCTET   addrInd = SCCP_CPA_ROUTE_GTTI |
                    (routingParams->gti << 2);
                if (routingParams->dSSNPresent)
                {
                    addrInd |= SCCP_CPA_HAS_SSN;
                }

                if (routingParams->isNational)
                {
                    addrInd |= SCCP_CPA_ROUTE_NAT;
                }
                else
                {
                    addrInd |= SCCP_CPA_ROUTE_INT;
                }
                begin->SetDestAddr(addrInd,
                        routingParams->dPc,
                        routingParams->dSsn,
                        &gttaddr[0], gttaddr.size());
            }
        }

        begin->SetQualityOfService(QOSI_SEQ_CTRL|QOSI_SLS_KEY|QOSI_RET_OPT, tcapDlgId % IWF_NUM_SLS);

        //NOTE: Setting current built tcap begin in IWFFSM to access in map-s6a translator
        iwfFsm->SetTcapBeginDlg(begin);

        TCAP_Invoke *tcapIvkCpt = NULL;
        IwfReturnAction retAct;
        DIA_BASE_CMD* outCmd = NULL;

        TcapCptList tcapCptList;
        if ((ret = translator->BuildTCAPMsg(iwfFsm, iwfFsm->GetCurrRcvdDiaMsg(),
                        &tcapCptList, outCmd, retAct)) != ITS_SUCCESS) {

            DLOG_CRITICAL("TransactionManager::sendTcapBegin Unable to build TCAP component with MAP from Diameter message");

            if (routingParams != NULL) {
                delete routingParams;
                routingParams = NULL;
            }

            if(begin != NULL)
            {
                delete begin;
                begin = NULL;
            }

            return ret;
        }

        if (retAct.action == IWF_RA_FORWARD ||
                retAct.action == IWF_RA_RESPOND_AND_FORWARD)
        {
            vector<byte> acEnc = map_common::EncodeApplicationContext(retAct.appContext);
            begin->SetApplicationContext(&acEnc[0], acEnc.size());

            std::list <TCAP_Component> outTcapCpt = tcapCptList.GetTcapCptList();
            tcapCptList.ClearTcapCptList();

            bool send = true;
            while(!outTcapCpt.empty())
            {
                TCAP_Component tcapCpt = outTcapCpt.front();
                if ((ret = TCAP_Component::Send(ISS7_Stack, begin, &tcapCpt)) != ITS_SUCCESS) {
                    send = false;
                    break;
                }
                UPDATE_SSG_STATS_NUM_OF_TCCOMP_SENT;
                outTcapCpt.pop_front();
            }
            if(send)
            {
                if ((ret = TCAP_Dialogue::Send(ISS7_Stack, begin)) != ITS_SUCCESS) {
                    DLOG_CRITICAL("TCAP component sent successfully. But TCAP dialogue could not be sent");
                }
                else {

                    m_tcapDialogueIdTxnEntryMap.insert(pair<ITS_CTXT, IwfFsm*> (tcapDlgId, iwfFsm));

                    iwfFsm->SetTcapDlgId(tcapDlgId);

                    DLOG_DEBUG("TCAP request with dialogue id %d mapping to session Id %s successfully sent", tcapDlgId,iwfFsm->GetDiaSessionId().c_str());
                }
            }
            else {
                DLOG_CRITICAL("TransactionManager::sendTcapBegin Unable to send TCAP message");
            }
        }

        if (retAct.action == IWF_RA_RESPOND_AND_FORWARD)
        {
            // Send a dia response also, here the dia response doesn't wait for TCAP
            // response
            DIA_BASE_CMD *diaCmd = NULL;
            ret = translator->BuildDiaResponse(iwfFsm, iwfFsm->GetCurrRcvdDiaMsg(),
                    diaCmd, retAct);
            if (ret != ITS_SUCCESS)
            {
                DLOG_ERROR("Unable send Dia Response!!");

                delete begin;
                delete routingParams;
                return ret;
            }

            diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(diaCmd))->GetBaseGenCommand();

            unsigned int diaSessionIdx = diaBaseGenCmd->getSessionIndex();
            std::string diaSessionId = diaBaseGenCmd->getSessionId()->value();

            if ((ret = DiaFrame::GetDiaFrame()->Send(diaCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
            {
                /* Remove the session entry from the m_diaSessionIdTxnEntryMap?
                 * Or keep the entry and let the state machine destroy it */

                DLOG_DEBUG("Diameter message with session id %s mapping to dialog Id %d sent successfully", diaSessionId.c_str(),tcapDlgId);

            } else {
                DLOG_CRITICAL("Diameter message with session id %s mapping to dialog Id %d send failed", diaSessionId.c_str(),tcapDlgId);

            }

            /* commented because in diameter stack the Send function deletes the
             * diaCmd not need to delete explicitly */
            //delete diaCmd;
            //diaCmd = NULL;
        }

        if (routingParams != NULL) {
            delete routingParams;
            routingParams = NULL;
        }

        if (begin != NULL) {
            delete begin;
            begin = NULL;
        }
    }
    catch(...)
    {
        DLOG_CRITICAL("TransactionManager::sendTcapBegin:: Caught An Unknown Exception:");
        ret = !ITS_SUCCESS;
    }

    DLOG_DEBUG("TransactionManager::sendTcapBegin() Exit");

    return ret;
}

int TransactionManager::SendTcapContinue(IwfFsm *iwfFsm) {

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::sendTcapContinue() Entry");

    int ret = ITS_SUCCESS;

    RoutingParams *routingParams = NULL;
    pbRoutingLabel routingLabel;
    IwfTranslator* translator  = iwfFsm->GetTranslator();

    TCAP_Dialogue *inTcapDlg = iwfFsm->GetCurrRcvdTcapDlg();
    TCAP_Component *inTcapCpt = iwfFsm->GetCurrRcvdTcapCpt();

    if(inTcapDlg == NULL || inTcapCpt == NULL)
    {
        DLOG_DEBUG("TcapDlg or TcapCpt is NULL");
        //DLOG_DEBUG("TransactionManager::sendTcapContinue() Exit");
        return !ITS_SUCCESS;
    }


    ITS_USHORT inTcapDlgType = inTcapDlg->GetDialogueType();

    TCAP_Continue *outTcapDlg = new TCAP_Continue();


    if (((inTcapDlgType == TCPPT_TC_BEGIN) || (inTcapDlgType == TCPPT_TC_CONTINUE) || (inTcapDlgType == TCPPT_TC_END)))
    {
        TCAP_Component *outTcapCpt = NULL;

        IwfReturnAction retAct;

        if(iwfFsm->GetUpstrmReqProtocol() != CAP_GE && inTcapDlgType != TCPPT_TC_END)
        {

            if ((ret = translator->BuildInterimTCAPMsg(iwfFsm, inTcapCpt, outTcapCpt, retAct)) != ITS_SUCCESS)
            {
                DLOG_CRITICAL("TransactionManager::sendTcapContinue Unable to build outgoing TCAP component from incoming TCAP component");

                if (outTcapCpt != NULL) {
                    delete outTcapCpt;
                    outTcapCpt = NULL;
                }

                delete outTcapDlg;
                outTcapDlg = NULL;

                if (routingParams != NULL) {
                    delete routingParams;
                    routingParams = NULL;
                }

                return ret;
            }
            ITS_ByteArray app_ctxt = map_common::EncodeApplicationContext(map_common::subscriberDataMngtContext_v3);
            outTcapDlg->SetApplicationContext(app_ctxt);
            outTcapDlg->SetDialogueID(inTcapDlg->GetDialogueID());
            //DLOG_DEBUG("TCAP Dialogue Id: %d", inTcapDlg->GetDialogueID());

            routingLabel = iwfFsm->GetRoutingLabel();
#ifdef USE_FULL_SCCP_ADDRESS
            SCCP_CalledPartyAddr selfSccpAddr = iwfFsm->GetSelfSccpAddr();
#else
            SCCP_CalledPartyAddr selfSccpAddr;
            iwfFsm->GetSelfSccpAddr(selfSccpAddr);
#endif

            if (!iwfFsm->IsRouteByGT())
            {
                outTcapDlg->SetOrigAddr(routingLabel.isnational(),
                        routingLabel.opc(),
                        routingLabel.ossn());
            }
            else
            {
                outTcapDlg->SetOrigAddr(selfSccpAddr);
                outTcapDlg->SetOPC(routingLabel.opc());
            }

            // Get QoS from incoming dialogue.
            ITS_OCTET flags = 0x00;
            ITS_OCTET slsK  = 0x00;
            ITS_OCTET prio  = 0x00;
            ITS_OCTET nind  = 0x00;

            inTcapDlg->GetQualityOfService(flags, slsK, prio, nind);

            outTcapDlg->SetQualityOfService(QOSI_SEQ_CTRL|QOSI_SLS_KEY|QOSI_RET_OPT, inTcapDlg->GetDialogueID() % IWF_NUM_SLS, prio, nind);

            if ((ret = TCAP_Component::Send(ISS7_Stack, outTcapDlg, outTcapCpt)) == ITS_SUCCESS) {

                if ((ret = TCAP_Dialogue::Send(ISS7_Stack, outTcapDlg)) != ITS_SUCCESS) {

                    DLOG_CRITICAL("TransactionManager::sendTcapContinue TCAP Result Last sent successfully. But TCAP Continue could not be sent");

                } else {

                    UPDATE_SSG_STATS_NUM_OF_TCCOMP_SENT;
                    //DLOG_DEBUG("TCAP Continue with dialogue id %d mapping to session Id %s successfully sent", outTcapDlg->GetDialogueID(),iwfFsm->GetDiaSessionId().c_str());

                }
            } else {
                DLOG_CRITICAL("TransactionManager::sendTcapContinue Unable to send TCAP message (Result Last in Continue");
            }


            if (routingParams != NULL) {
                delete routingParams;
                routingParams = NULL;
            }

            if (outTcapCpt != NULL) {
                delete outTcapCpt;
                outTcapCpt = NULL;
            }

            if (outTcapDlg != NULL) {
                delete outTcapDlg;
                outTcapDlg = NULL;
            }
        }
        else /* UPSTRM Protocol = CAP_GE: CAP-Ro Translator Case*/
        {
            TcapCptList tcapCptList;
            DIA_BASE_CMD *outCmd = NULL;
            if ((ret = translator->BuildMultiTCAPMsg(iwfFsm, inTcapCpt, &tcapCptList, outCmd, retAct)) != ITS_SUCCESS)
            {
                DLOG_CRITICAL("TransactionManager::sendTcapContinue Unable to build outgoing TCAP component from incoming TCAP component");

                if (outTcapDlg != NULL) {
                    delete outTcapDlg;
                    outTcapDlg = NULL;
                }

                if (routingParams != NULL) {
                    delete routingParams;
                    routingParams = NULL;
                }

                return ret;
            }

            if(retAct.action == IWF_RA_CONSUME_AND_RESPOND)
            {
                diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(outCmd))->GetBaseGenCommand();

                unsigned int diaSessionIdx = diaBaseGenCmd->getSessionIndex();
                std::string diaSessionId = diaBaseGenCmd->getSessionId()->value();

#ifdef NO_QUEUEING
                if ((ret = DiaFrame::GetDiaFrame()->Send(outCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
                {
                    /* Remove the session entry from the m_diaSessionIdTxnEntryMap?
                     * Or keep the entry and let the state machine destroy it */

                    //DLOG_DEBUG("Diameter message with session id %s sent successfully", diaSessionId.c_str());
                    m_diaSessionIdTxnEntryMap.insert(pair<std::string, IwfFsm*> (diaSessionId, iwfFsm));

                } else {
                    DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

                }
#else
                if ((ret = SendDiaMsgToStack(diaSessionId, outCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
                {
                    //DLOG_DEBUG("Diameter message with session id %s sent successfully", diaSessionId.c_str());
                    m_diaSessionIdTxnEntryMap.insert(pair<std::string, IwfFsm*> (diaSessionId, iwfFsm));

                } else {
                    DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

                }
#endif
            }

            if(retAct.action == IWF_RA_CONSUME_AND_RETRY)
            {
                unsigned int diaSessionIdx = outCmd->getSessionIndex();
                std::string diaSessionId = outCmd->getSessionId()->value();
#ifdef NO_QUEUEING
                if ((ret = DiaFrame::GetDiaFrame()->Send(outCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
                {
                    DLOG_DEBUG("ConsumeAndRetry: Diameter message with session id %s sent successfully", diaSessionId.c_str());

                } else {
                    DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

                }
#else
                if ((ret = SendDiaMsgToStack(diaSessionId, outCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
                {
                    DLOG_DEBUG("ConsumeAndRetry: Diameter message with session id %s sent successfully", diaSessionId.c_str());

                } else {
                    DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

                }
#endif
                iwfFsm->SetMarkForRollback(true);
            }

            if( retAct.action == IWF_RA_RESPOND_AND_FORWARD_WITH_TERM ||
                    (retAct.action == IWF_RA_FORWARD && retAct.isReleaseEnd) )
            {
                iwfFsm->SetCCFHActionDone(true);
                SendTcapEnd(iwfFsm, true);
                iwfFsm->SetCCFHActionDone(false);
                /* Send the CCR-T incase of CCA-I received with error code*/
                if( retAct.action == IWF_RA_RESPOND_AND_FORWARD_WITH_TERM )
                {
                    if( outCmd != NULL)
                    {
                        diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(outCmd))->GetBaseGenCommand();

                        unsigned int diaSessionIdx = diaBaseGenCmd->getSessionIndex();
                        std::string diaSessionId = diaBaseGenCmd->getSessionId()->value();

#ifdef NO_QUEUEING
                        if ((ret = DiaFrame::GetDiaFrame()->Send(outCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
                        {
                            /* Remove the session entry from the m_diaSessionIdTxnEntryMap?
                             * Or keep the entry and let the state machine destroy it */
                            translator->OnUpstrmFinalReqSent(iwfFsm);
                            //DLOG_DEBUG("Diameter message with session id %s sent successfully", diaSessionId.c_str());

                        } else {
                            DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

                        }
#else
                        if ((ret = SendDiaMsgToStack(diaSessionId, outCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
                        {
                            translator->OnUpstrmFinalReqSent(iwfFsm);
                            //DLOG_DEBUG("Diameter message with session id %s sent successfully", diaSessionId.c_str());

                        } else {
                            DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

                        }
#endif


                        /* commented because in diameter stack the Send function deletes the
                         * diaCmd not need to delete explicitly */
                        //delete outCmd;
                        //outCmd = NULL;
                    }
                }
                else
                {
                    //DLOG_DEBUG("Changing Current FSM State to CLOSED");
                    iwfFsm->SetCurrentState(CLOSED);
                }
            }
            else if (retAct.action == IWF_RA_FORWARD || retAct.action == IWF_RA_RESPOND_AND_FORWARD)
            {
                outTcapDlg->SetApplicationContext(retAct.app_ctxt);
                outTcapDlg->SetDialogueID(inTcapDlg->GetDialogueID());
                //DLOG_DEBUG("Interim TCAP Dialogue Id: %d", inTcapDlg->GetDialogueID());

                routingLabel = iwfFsm->GetRoutingLabel();
#ifdef USE_FULL_SCCP_ADDRESS
                SCCP_CalledPartyAddr selfSccpAddr = iwfFsm->GetSelfSccpAddr();
#else
                SCCP_CalledPartyAddr selfSccpAddr;
                iwfFsm->GetSelfSccpAddr(selfSccpAddr);
#endif

                if (!IwfController::Instance().Config().LocalConfig().SelfSccpAddress().IsRouteByGT())
                {
                    outTcapDlg->SetOrigAddr(routingLabel.isnational(),
                            routingLabel.opc(),
                            routingLabel.ossn());
                }
                else
                {
                    outTcapDlg->SetOrigAddr(selfSccpAddr);
                    outTcapDlg->SetOPC(routingLabel.opc());
                }

                // Get QoS from incoming dialogue.
                ITS_OCTET flags = 0x00;
                ITS_OCTET slsK  = 0x00;
                ITS_OCTET prio  = 0x00;
                ITS_OCTET nind  = 0x00;

                inTcapDlg->GetQualityOfService(flags, slsK, prio, nind);

                outTcapDlg->SetQualityOfService(QOSI_SEQ_CTRL|QOSI_SLS_KEY|QOSI_RET_OPT, inTcapDlg->GetDialogueID() % IWF_NUM_SLS, prio, nind);

                std::list <TCAP_Component> outTcapCpt = tcapCptList.GetTcapCptList();
                tcapCptList.ClearTcapCptList();

                bool send = true;
                while(!outTcapCpt.empty())
                {
                    TCAP_Component tcapCpt = outTcapCpt.front();
                    if ((ret = TCAP_Component::Send(ISS7_Stack, outTcapDlg, &tcapCpt)) != ITS_SUCCESS) {
                        send = false;
                        break;
                    }
                    UPDATE_SSG_STATS_NUM_OF_TCCOMP_SENT;
                    outTcapCpt.pop_front();
                }
                if(send)
                {
                    if ((ret = TCAP_Dialogue::Send(ISS7_Stack, outTcapDlg)) != ITS_SUCCESS) {

                        DLOG_CRITICAL("TransactionManager::sendTcapContinue TCAP Continue could not be sent");

                    }
                    else {

                        //DLOG_DEBUG("TCAP Continue with dialogue id %d mapping to session Id %s successfully sent", outTcapDlg->GetDialogueID(),iwfFsm->GetDiaSessionId().c_str());
                        /*To detect when NO_EVENT_TIMER should be started, Value will be true when condition to construct RRB msg is hit in TSL call flows, else default set to false*/
                        if(iwfFsm->IsStartNoEventTimerSet())
                        {
                            translator->StartTimerHandling(iwfFsm,ETimerType::NO_EVENT_TIMER);
                            iwfFsm->SetStartNoEventTimer(false);
                        }
                        //DLOG_DEBUG("TransactionManager::sendTcapContinue Store LocalTransactionId in userData.");
                        translator->SetLocalTransId(outTcapDlg->GetDialogueID(),iwfFsm);
                    }
                }
                else {
                    DLOG_CRITICAL("TransactionManager::sendTcapContinue Unable to send TCAP message (Result Last in Continue");
                }

                if (routingParams != NULL) {
                    delete routingParams;
                    routingParams = NULL;
                }

                if (outTcapDlg != NULL) {
                    delete outTcapDlg;
                    outTcapDlg = NULL;
                }
            }

            /* This condition is moved after because as per callFlow ASA should be triggered after sending
             * ReleaseCall to MSC */
            if(retAct.action == IWF_RA_RESPOND_ONLY || retAct.action == IWF_RA_RESPOND_AND_FORWARD
                    || (retAct.action == IWF_RA_RESPOND_AND_FORWARD_WITH_TERM && retAct.isASRReceived))
            {
                // Send a dia response also, here the dia response doesn't wait for TCAP
                // response
                DIA_BASE_CMD *diaCmd = NULL;
                ret = translator->BuildDiaResponse(iwfFsm, iwfFsm->GetCurrRcvdDiaMsg(),
                        diaCmd, retAct);
                if (ret != ITS_SUCCESS)
                {
                    DLOG_ERROR("Unable send Dia Response!!");

                    delete diaCmd;
                    delete outTcapCpt;
                    delete outTcapDlg;
                    delete routingParams;
                    return ret;
                }

                diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(diaCmd))->GetBaseGenCommand();

                unsigned int diaSessionIdx = diaBaseGenCmd->getSessionIndex();
                std::string diaSessionId = diaBaseGenCmd->getSessionId()->value();

                if ((ret = DiaFrame::GetDiaFrame()->Send(diaCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
                {
                    /* Remove the session entry from the m_diaSessionIdTxnEntryMap?
                     * Or keep the entry and let the state machine destroy it */

                    //DLOG_DEBUG("Diameter message with session id %s sent successfully", diaSessionId.c_str());

                } else {
                    DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

                }
                /* this method is called here so that after sending ASA we can trigger CCR-T
                 * and close the session */
                /* Dont Trigger CCR-T if return action is RESPOND_ONLY for RSR case */
                if(retAct.action != IWF_RA_RESPOND_ONLY)
                {
                    this->ClearDiaAndTcapSession(iwfFsm);
                }
                /* commented because in diameter stack the Send function deletes the
                 * diaCmd not need to delete explicitly */
                //delete diaCmd;
                //diaCmd = NULL;
            }
        }
    }
    if (outTcapDlg != NULL) {
        delete outTcapDlg;
        outTcapDlg = NULL;
    }
    //DLOG_DEBUG("TransactionManager::sendTcapContinue() Exit");

    return ret;
}

int TransactionManager::SendTcapEnd(IwfFsm *iwfFsm, bool isTranslationReqd) {

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::sendTcapEnd() Entry");

    int ret = ITS_SUCCESS;
    TCAP_Dialogue *rcvdDlg = iwfFsm->GetCurrRcvdTcapDlg();

    if(rcvdDlg == NULL)
    {
        return !ITS_SUCCESS;
    }

    TCAP_End *outTcapEndDlg = new TCAP_End();
    TCAP_Component *tcapCpt = NULL;
    IwfReturnAction retAct;
    retAct.action = IWF_RA_FORWARD;
    IwfTranslator *translator = NULL;
    TcapCptList tcapCptList;
    DIA_BASE_CMD* outCmd = NULL;
    TcapComponentList outTcapCptLst;

    if (isTranslationReqd)
    {
        translator = iwfFsm->GetTranslator();

        if ((ret = translator->BuildTCAPMsg(iwfFsm,
                        iwfFsm->GetCurrRcvdDiaMsg(), &tcapCptList, outCmd, retAct))
                != ITS_SUCCESS)
        {

            DLOG_CRITICAL("TransactionManager::sendTcapEnd Unable to build outgoing TCAP component");

            delete outTcapEndDlg;
            outTcapEndDlg = NULL;

            return ret;
        }
    }
    else
    {
        translator = iwfFsm->GetTranslator();
        translator->BuildTCAPErrorCpt(iwfFsm, 0, tcapCpt);
        /* setting this component to TcapCptList so that in case
         * of IWF_RA_ERROR it will be generic for all translators */
        tcapCptList.BuildTcapCptList(*tcapCpt);
        retAct.action = IWF_RA_ERROR;
    }

    if (retAct.action == IWF_RA_FORWARD)
    {
        std::vector<byte> rcvdAppCtxt;
        rcvdDlg->GetApplicationContext(rcvdAppCtxt);
        outTcapEndDlg->SetApplicationContext(rcvdAppCtxt);
        outTcapEndDlg->SetDialogueID(iwfFsm->GetTcapDlgId());
#if 0
        if((iwfFsm->GetUpstrmReqProtocol() == MAP_GR) &&
                IsSubscriptionDataPresentInULA(iwfFsm->GetCurrRcvdDiaMsg()))
        {
            outTcapCpt->SetInvokeID(iwfFsm->GetInvokeId());
        }

#endif
        DIA_BASE_CMD* diaCmd = iwfFsm->GetCurrRcvdDiaMsg();
        diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(diaCmd))->GetBaseGenCommand();
        std::string diaSessionId = diaBaseGenCmd->getSessionId()->value();

        // Get QoS from incoming dialogue.
        ITS_OCTET flags = 0x00;
        ITS_OCTET slsK  = 0x00;
        ITS_OCTET prio  = 0x00;
        ITS_OCTET nind  = 0x00;
        rcvdDlg->GetQualityOfService(flags, slsK, prio, nind);
        outTcapEndDlg->SetQualityOfService(QOSI_SEQ_CTRL|QOSI_SLS_KEY|QOSI_RET_OPT, iwfFsm->GetTcapDlgId() % IWF_NUM_SLS, prio, nind);

        outTcapCptLst = tcapCptList.GetTcapCptList();
        tcapCptList.ClearTcapCptList();

        bool send = false;
        while(!outTcapCptLst.empty())
        {
            send = true;
            TCAP_Component tcapCpt = outTcapCptLst.front();
            if ((ret = TCAP_Component::Send(ISS7_Stack, outTcapEndDlg, &tcapCpt)) != ITS_SUCCESS) {
                send = false;
                break;
            }
            UPDATE_SSG_STATS_NUM_OF_TCCOMP_SENT;
            outTcapCptLst.pop_front();
        }
        if(send)
        {
            if ((ret = TCAP_Dialogue::Send(ISS7_Stack, outTcapEndDlg)) == ITS_SUCCESS) {
                DLOG_DEBUG("TCAP End with dialogue id %d mapping to session Id %s successfully sent", outTcapEndDlg->GetDialogueID(),diaSessionId.c_str());

            }
            else {
                DLOG_CRITICAL("TransactionManager::sendTcapEnd TCAP Result Last sent successfully. But TCAP End could not be sent");
            }
        }
        else {
            DLOG_CRITICAL("TransactionManager::sendTcapEnd Unable to send TCAP message");
        }
    }
    else if (retAct.action == IWF_RA_ERROR)
    {
        std::vector<byte> rcvdAppCtxt;
        rcvdDlg->GetApplicationContext(rcvdAppCtxt);
        outTcapEndDlg->SetApplicationContext(rcvdAppCtxt);
        outTcapEndDlg->SetDialogueID(iwfFsm->GetTcapDlgId());

        // Get QoS from incoming dialogue.
        ITS_OCTET flags = 0x00;
        ITS_OCTET slsK  = 0x00;
        ITS_OCTET prio  = 0x00;
        ITS_OCTET nind  = 0x00;

        rcvdDlg->GetQualityOfService(flags, slsK, prio, nind);
        outTcapEndDlg->SetQualityOfService(QOSI_SEQ_CTRL|QOSI_SLS_KEY|QOSI_RET_OPT, iwfFsm->GetTcapDlgId() % IWF_NUM_SLS, prio, nind);

        outTcapCptLst = tcapCptList.GetTcapCptList();
        tcapCptList.ClearTcapCptList();

        bool send = false;
        while(!outTcapCptLst.empty())
        {
            send = true;
            TCAP_Component tcapCpt = outTcapCptLst.front();
            if ((ret = TCAP_Component::Send(ISS7_Stack, outTcapEndDlg, &tcapCpt)) != ITS_SUCCESS) {
                send = false;
                break;
            }
            UPDATE_SSG_STATS_NUM_OF_TCCOMP_SENT;
            outTcapCptLst.pop_front();
        }
        if(send)
        {
            if ((ret = TCAP_Dialogue::Send(ISS7_Stack, outTcapEndDlg)) == ITS_SUCCESS) {

                DLOG_DEBUG("TCAP End with dialogue id %d successfully sent", outTcapEndDlg->GetDialogueID());
            }
            else {
                DLOG_CRITICAL("TransactionManager::sendTcapEnd TCAP Result Last sent successfully. But TCAP End could not be sent");
            }
        }
        else {
            DLOG_CRITICAL("TransactionManager::sendTcapEnd Unable to send TCAP message");
        }
    }
    else if(retAct.action == IWF_RA_CONSUME_AND_RETRY)
    {
        unsigned int diaSessionIdx = outCmd->getSessionIndex();
        std::string diaSessionId = outCmd->getSessionId()->value();
#ifdef NO_QUEUEING
        if ((ret = DiaFrame::GetDiaFrame()->Send(outCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
        {
            DLOG_DEBUG("ConsumeAndRetry: Diameter message with session id %s sent successfully", diaSessionId.c_str());

        } else {
            DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

        }
#else
        if ((ret = SendDiaMsgToStack(diaSessionId, outCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
        {
            DLOG_DEBUG("ConsumeAndRetry: Diameter message with session id %s sent successfully", diaSessionId.c_str());

        } else {
            DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

        }
#endif
        // Don't go to previous state yet. Mark the FSM.
        // SendTcapEnd might be invoked as an Before action in the FSM>
        //iwfFsm->GotoPrevState();
        iwfFsm->SetMarkForRollback(true);
    }

    if (tcapCpt != NULL) {
        delete tcapCpt;
        tcapCpt = NULL;
    }

    if (outTcapEndDlg != NULL) {
        delete outTcapEndDlg;
        outTcapEndDlg = NULL;
    }

    //DLOG_DEBUG("TransactionManager::sendTcapEnd() Exit");

    return ret;
}

int TransactionManager::SendTcapErrResp(IwfFsm *iwfFsm) {

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::SendTcapErrResp() Entry");

    if(iwfFsm != NULL)
    {
        std::string imsi = "";
        TCAP_Dialogue *rcvdDlg = iwfFsm->GetCurrRcvdTcapDlg();
        TCAP_End *outTcapEndDlg = new TCAP_End();
        TCAP_Component *outTcapCpt = NULL;
        IwfTranslator* translator = iwfFsm->GetTranslator();
        int ret = ITS_SUCCESS;

        //PopulateImsiFromTcapMsg(iwfFsm, imsi, serviceKey);

        /*if ((ret = GetTranslatorId(imsi, serviceKey, iwfFsm)) > 0)
          {
          translator = IwfController::Instance().GetTranslator(ret);
          }
          else
          {
          translator = IwfController::Instance().GetTranslator(0);
          }*/
        /* As translator is stored on IwfFsm so no need to look into
         * RoutingRules if it is not set we can set to default translator*/
        if(translator == NULL)
        {
            translator = IwfController::Instance().GetTranslator(0);
        }

        translator->BuildTCAPErrorCpt(iwfFsm, 0, outTcapCpt);

        if( outTcapCpt != NULL )
        {
            std::vector<byte> rcvdAppCtxt;
            rcvdDlg->GetApplicationContext(rcvdAppCtxt);
            outTcapEndDlg->SetApplicationContext(rcvdAppCtxt);
            outTcapEndDlg->SetDialogueID(iwfFsm->GetTcapDlgId());

            if((iwfFsm->GetUpstrmReqProtocol() == MAP_GR))
            {
                outTcapCpt->SetInvokeID(iwfFsm->GetCurrRcvdTcapCpt()->GetInvokeID());
            }

            // Get QoS from incoming dialogue.
            ITS_OCTET flags = 0x00;
            ITS_OCTET slsK  = 0x00;
            ITS_OCTET prio  = 0x00;
            ITS_OCTET nind  = 0x00;

            rcvdDlg->GetQualityOfService(flags, slsK, prio, nind);
            outTcapEndDlg->SetQualityOfService(QOSI_SEQ_CTRL|QOSI_SLS_KEY|QOSI_RET_OPT, iwfFsm->GetTcapDlgId() % IWF_NUM_SLS, prio, nind);

            if ((ret = TCAP_Component::Send(ISS7_Stack, outTcapEndDlg, outTcapCpt)) == ITS_SUCCESS) {

                if ((ret = TCAP_Dialogue::Send(ISS7_Stack, outTcapEndDlg)) == ITS_SUCCESS) {
                    DLOG_DEBUG("TCAP End with dialogue id %d successfully sent", outTcapEndDlg->GetDialogueID());
                    UPDATE_SSG_STATS_NUM_OF_TCCOMP_SENT;

                } else {
                    DLOG_CRITICAL("TransactionManager::SendTcapErrResp TCAP Error Last sent successfully. But TCAP End could not be sent");
                }
            } else {
                DLOG_CRITICAL("TransactionManager::SendTcapErrResp Unable to send TCAP message (Result Last in End");
            }

            if (outTcapCpt != NULL) {
                delete outTcapCpt;
                outTcapCpt = NULL;
            }

            if (outTcapEndDlg != NULL) {
                delete outTcapEndDlg;
                outTcapEndDlg = NULL;
            }
        }

        if (iwfFsm->GetCurrentStateId() == CLOSED) {

            std::string diaSessionId = iwfFsm->GetDiaSessionId();
            ITS_CTXT tcapDlgId = iwfFsm->GetTcapDlgId();

            if (IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
            {
                uint32_t indexKey = iwfFsm->GetReplicaIndexKey();
                /*DLOG_DEBUG("Deleting Replication entry for SessionId : %s with index Key :%d",
                        diaSessionId.c_str(),indexKey);*/
		if ( indexKey != 0xffffffff)
		{       
			if (ReplicableData::DeleteTransactionEntryInReplica(IWF_SESSION_ENTRY_LIST, indexKey) != PB_REPL_UTILS_SUCCESS)
			{
				// Unable to delete from CB, save it for future
				DLOG_DEBUG("Unable to delete [ %s ] from CB, save it for future", diaSessionId.c_str());
				m_cbFlushGuard.Acquire();
				m_sessionsToFlushFromCB.insert(pair<int, std::string> (indexKey, diaSessionId));
				IwfController::Instance().StartBulkFetchTimer();
				m_cbFlushGuard.Release();
			}
			else
			{
				iwfFsm->DeleteEntryInReplica(IWF_STATE_REPLICATION, diaSessionId);
				IwfController::SetReplicationEntryToFreeList(indexKey);
			}
		}
            }

            map<std::string, IwfFsm*>::iterator diaSessIdTxnEntryMapIter = m_diaSessionIdTxnEntryMap.find(diaSessionId);

            if (diaSessIdTxnEntryMapIter != m_diaSessionIdTxnEntryMap.end())
                m_diaSessionIdTxnEntryMap.erase(diaSessIdTxnEntryMapIter);

            map<ITS_CTXT, IwfFsm*>::iterator tcapDialogueIdTxnEntryIter;
            tcapDialogueIdTxnEntryIter = m_tcapDialogueIdTxnEntryMap.find(tcapDlgId);
            if (tcapDialogueIdTxnEntryIter != m_tcapDialogueIdTxnEntryMap.end())
                m_tcapDialogueIdTxnEntryMap.erase(tcapDialogueIdTxnEntryIter);

            map<ITS_CTXT, TCAP_Dialogue*>::iterator rcvdTcapDialogueIdDialogueIter;
            rcvdTcapDialogueIdDialogueIter = m_rcvdTcapDialogueIdDialogueMap.find(tcapDlgId);
            if (rcvdTcapDialogueIdDialogueIter != m_rcvdTcapDialogueIdDialogueMap.end())
            {
                TCAP_Dialogue *tcapDialogue = rcvdTcapDialogueIdDialogueIter->second;
                m_rcvdTcapDialogueIdDialogueMap.erase(rcvdTcapDialogueIdDialogueIter);

                if(tcapDialogue != NULL)
                {
                    delete tcapDialogue;
                    tcapDialogue = NULL;
                }
            }

            if(NULL != iwfFsm)
                iwfFsm->SetCurrRcvdTcapDlg(NULL);

            this->ResetCurrRcvdDiaMsg(iwfFsm);
            this->ResetCurrRcvdTcapMsg(iwfFsm);
        }
    }

    //DLOG_DEBUG("TransactionManager::SendTcapErrResp() Exit");

    return ITS_SUCCESS;
}

int TransactionManager::SendDiaMsg(IwfFsm *iwfFsm) {

    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::sendDiaMsg() Entry");

    int ret = ITS_SUCCESS;

    try
    {

        TCAP_Dialogue *inTcapDlg = iwfFsm->GetCurrRcvdTcapDlg();
        TCAP_Component *inTcapCpt = iwfFsm->GetCurrRcvdTcapCpt();

        ITS_USHORT inTcapDlgType = inTcapDlg->GetDialogueType();
        ITS_USHORT inTcapCptType;
        if((inTcapDlgType != TCPPT_TC_P_ABORT)
                && (inTcapDlgType != TCPPT_TC_U_ABORT))
        {
            inTcapCptType = inTcapCpt->GetComponentType();
        }

        DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
        RoutingParams *routingParams = NULL;
        std::string imsi = "";
        IwfTranslator* translator = iwfFsm->GetTranslator();

        if(translator == NULL)
        {
            if((IwfController::Instance().Config().LocalConfig().isCongestionManagementEnabled()) &&
                    CurrentFSMCount > IwfController::Instance().Config().LocalConfig().GetMaxNumberOfSessionsToHold())
            {
                //NOTE: Check for Congestion Management
                DLOG_CRITICAL("Max Number of Sessions %d reached dropping the new requests.",
                        IwfController::Instance().Config().LocalConfig().GetMaxNumberOfSessionsToHold());

                if(iwfFsm->GetUpstrmReqProtocol() == MAP_GR)
                {
                    iwfFsm->SetErrorCode(MAP_ERR_RESOURCE_LIMITATION);
                }
                else if(iwfFsm->GetUpstrmReqProtocol() == CAP_GE)
                {
                    iwfFsm->SetErrorCode(CAP_ERR_UNAVAILABLE_RESOURCE);
                }
                return ITS_ENOROUTE;
            }

            if ((ret = GetRoutingParams(iwfFsm, routingParams)) != ITS_SUCCESS)
            {
                if((ret == ITS_ENOROUTE) && IsRcvdTcapReqMsgServerInitiated(inTcapCpt))
                {
                    translator = IwfController::Instance().GetTranslator(S6A_TO_MAP_STR);
                }
                else
                {
                    DLOG_CRITICAL("TransactionManager::sendDiaMsg Unable to determine routing parameters");
                    if (routingParams != NULL) {
                        delete routingParams;
                        routingParams = NULL;
                    }
                    if(iwfFsm->GetUpstrmReqProtocol() == MAP_GR)
                    {
                        iwfFsm->SetErrorCode(MAP_ERR_UNKNOWN_SUBSCRIBER);
                    }
                    return ret;
                }
            }
            else
            {
                translator = IwfController::Instance().GetTranslator(routingParams->transId);
                //DLOG_DEBUG("IWF::TransactionManager - Translator for IWF retreived %d", routingParams->transId);
            }

            iwfFsm->SetTranslator(translator);
        }

        if (inTcapDlgType == TCPPT_TC_UNI && inTcapCptType == TCPPT_TC_INVOKE)
        {
            IwfReturnAction retAct;

            ITS_LONG opCode = 0;
            TCAP_Invoke *tcapIvk = static_cast<TCAP_Invoke*>(inTcapCpt);
            tcapIvk->GetOperation(opCode);
            if (opCode == map_common::OP_reset)
            {
                DLOG_DEBUG("Sending S6A RSR for incoming MAP ResetArg");
                UPDATE_SSG_STATS_RSR_ARG_RECVD;
                map<std::string, SessionCtxt*>::iterator imsiMapIter = m_imsiMap.begin();
                std::string diaSessionId = ""; 
                while(imsiMapIter != m_imsiMap.end()) 
                {
                    SessionCtxt *sessionCtxt = imsiMapIter->second;

                    DIA_BASE_CMD *diaCmd = NULL;
                    CLOG_DEBUG("destHost = %s, destRealm = %s",sessionCtxt->GetOriginHost().c_str(), sessionCtxt->GetOriginRealm().c_str());

                    iwfFsm->SetResetDestHost(sessionCtxt->GetOriginHost());
                    iwfFsm->SetResetDestRealm(sessionCtxt->GetOriginRealm());
                    if ((ret = translator->BuildDiaMsg(iwfFsm, inTcapCpt, diaCmd, retAct)) != ITS_SUCCESS) {
                        if (diaCmd != NULL) {
                            delete diaCmd;
                            diaCmd = NULL;
                        }
                        if (routingParams != NULL)
                        {
                            delete routingParams;
                            routingParams = NULL;
                        }
                        if(translator != IwfController::Instance().GetTranslator(CAP_TO_RO_STR_TSL))
                        {
                            SendTcapEnd(iwfFsm, false);
                        }
                        return ret;
                    }
                    stringstream str;
                    diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(diaCmd))->GetBaseGenCommand();

                    unsigned int diaSessionIdx = diaBaseGenCmd->getSessionIndex();
                    diaSessionId = diaBaseGenCmd->getSessionId()->value();

                    DIA_BASE_CMD *rstDiaCmd(diaCmd);
#ifdef NO_QUEUEING
                    if ((ret = diaFrame->Send(rstDiaCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS) {
                        DLOG_DEBUG("Diameter RESET message sent successfully");
                    } else {
                        DLOG_CRITICAL("Diameter RESET message send failed");
                    }
#else
                    if ((ret = SendDiaMsgToStack(diaSessionId, rstDiaCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
                    {
                        DLOG_DEBUG("Diameter RESET message sent successfully");

                    } else {
                        DLOG_CRITICAL("Diameter RESET message send failed");
                    }
#endif
                    imsiMapIter++;
                }
                m_diaSessionIdTxnEntryMap.insert(pair<std::string, IwfFsm*> (diaSessionId, iwfFsm));
                if (routingParams != NULL) {
                    delete routingParams;
                    routingParams = NULL;
                }
                return ret;
            }
        }

        DIA_BASE_CMD *diaCmd = NULL;
        IwfReturnAction retAct;

        if ((ret = translator->BuildDiaMsg(iwfFsm, inTcapCpt, diaCmd, retAct)) != ITS_SUCCESS) {
            if (diaCmd != NULL) {
                delete diaCmd;
                diaCmd = NULL;
            }
            if (routingParams != NULL)
            {
                delete routingParams;
                routingParams = NULL;
            }
            if(translator != IwfController::Instance().GetTranslator(CAP_TO_RO_STR_TSL))
            {
                SendTcapEnd(iwfFsm, false);
            }
            return ret;
        }

        if (retAct.action == IWF_RA_FORWARD || retAct.action == IWF_RA_RESPOND_AND_FORWARD)
        {
            diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(diaCmd))->GetBaseGenCommand();

            unsigned int diaSessionIdx = diaBaseGenCmd->getSessionIndex();
            std::string diaSessionId = diaBaseGenCmd->getSessionId()->value();

            if (inTcapDlgType == TCPPT_TC_UNI && inTcapCptType == TCPPT_TC_INVOKE) {
                ITS_LONG opCode = 0;
                m_diaSessionIdTxnEntryMap.insert(pair<std::string, IwfFsm*> (diaSessionId, iwfFsm));
                TCAP_Invoke *tcapIvk = static_cast<TCAP_Invoke*>(inTcapCpt);
                tcapIvk->GetOperation(opCode);
                if (opCode == map_common::OP_reset)
                {
                    DLOG_DEBUG("Sending S6A RSR for incoming MAP ResetArg");
                    PEER_ENTRY *entry = PeerTable::GetPeerTable()->FindFirstEntry();
                    ret = !ITS_SUCCESS;
                    while (entry != NULL)
                    {
                        stringstream str;
                        DIA_BASE_CMD *rstDiaCmd(diaCmd);
                        diameter::base::DestinationHost dh(DIA_PE_HOST(entry));
                        diameter::base::DestinationRealm dr(DIA_PE_REALM(entry));
                        ((s6a::ResetRequest *)rstDiaCmd)->setDestinationHost(dh);
                        ((s6a::ResetRequest *)rstDiaCmd)->setDestinationRealm(dr);
                        //str<< *rstDiaCmd << std::endl;
                        //DLOG_DEBUG("%s", str.str().c_str());

#ifdef NO_QUEUEING
                        if ((ret = diaFrame->Send(rstDiaCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS) {
                            DLOG_DEBUG("Diameter RESET message sent successfully");
                        } else {
                            DLOG_CRITICAL("Diameter RESET message send failed");
                        }
#else
                        if ((ret = SendDiaMsgToStack(diaSessionId, rstDiaCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
                        {
                            DLOG_DEBUG("Diameter RESET message sent successfully");

                        } else {
                            DLOG_CRITICAL("Diameter RESET message send failed");

                        }
#endif
                        entry = PEER_TABLE->FindNextEntry(entry);
                        if(entry)
                        {
                            diaSessionIdx++;
                            diaSessionId = SetSessionIdForReset(diaSessionIdx, (s6a::ResetRequest *)diaCmd);
                            m_diaSessionIdTxnEntryMap.insert(pair<std::string, IwfFsm*> (diaSessionId, iwfFsm));
                        }
                    }
                    if (diaCmd)
                    {
                        //delete diaCmd;
                        //diaCmd = NULL;
                    }
                    if (routingParams != NULL) {
                        delete routingParams;
                        routingParams = NULL;
                    }
                    return ret;
                }
            }


#ifdef NO_QUEUEING
            if ((ret = diaFrame->Send(diaCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS) {

                if (inTcapDlgType == TCPPT_TC_BEGIN && inTcapCptType == TCPPT_TC_INVOKE) {

                    m_diaSessionIdTxnEntryMap.insert(pair<std::string, IwfFsm*> (diaSessionId, iwfFsm));
                }

                translator->OnUpstrmFinalReqSent(iwfFsm);

                //DLOG_DEBUG("Diameter message with session id %s mapping to dialog Id %d sent successfully", diaSessionId.c_str(),iwfFsm->GetTcapDlgId());

            } else {
                DLOG_CRITICAL("Diameter message with session id %s mapping to dialog Id %d send failed", diaSessionId.c_str(),iwfFsm->GetTcapDlgId());

            }
#else
            if ((ret = SendDiaMsgToStack(diaSessionId, diaCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
            {
                if (inTcapDlgType == TCPPT_TC_BEGIN && inTcapCptType == TCPPT_TC_INVOKE) {

                    m_diaSessionIdTxnEntryMap.insert(pair<std::string, IwfFsm*> (diaSessionId, iwfFsm));
                }

                translator->OnUpstrmFinalReqSent(iwfFsm);

                //DLOG_DEBUG("Diameter message with session id %s mapping to dialog Id %d sent successfully", diaSessionId.c_str(),iwfFsm->GetTcapDlgId());


            } else {
                DLOG_CRITICAL("Diameter message with session id %s mapping to dialog Id %d send failed", diaSessionId.c_str(),iwfFsm->GetTcapDlgId());

            }
#endif
        }

        if(retAct.action == IWF_RA_RESPOND_AND_FORWARD)
        {
            TCAP_Component *outTcapCpt = NULL;
            ret = translator->BuildTcapResponse(iwfFsm, inTcapCpt, outTcapCpt, retAct);
            if(ret != ITS_SUCCESS)
            {
                DLOG_ERROR("TransactionManager::sendDiaMsg Unable to Build TCAP Component..!!");
                delete diaCmd;
                return ret;
            }

            if ( outTcapCpt != NULL || retAct.action == IWF_RA_FORWARD_DUMMY_TCEND )
            {
                TCAP_End *outTcapEndDlg = new TCAP_End();
                std::vector<byte> rcvdAppCtxt;
                inTcapDlg->GetApplicationContext(rcvdAppCtxt);
                outTcapEndDlg->SetApplicationContext(rcvdAppCtxt);
                outTcapEndDlg->SetDialogueID(iwfFsm->GetTcapDlgId());


                // Get QoS from incoming dialogue.
                ITS_OCTET flags = 0x00;
                ITS_OCTET slsK  = 0x00;
                ITS_OCTET prio  = 0x00;
                ITS_OCTET nind  = 0x00;
                inTcapDlg->GetQualityOfService(flags, slsK, prio, nind);
                outTcapEndDlg->SetQualityOfService(QOSI_SEQ_CTRL|QOSI_SLS_KEY|QOSI_RET_OPT, iwfFsm->GetTcapDlgId() % IWF_NUM_SLS, prio, nind);

                if ( retAct.action == IWF_RA_FORWARD_DUMMY_TCEND )
                {
                    if ((ret = TCAP_Dialogue::Send(ISS7_Stack, outTcapEndDlg)) == ITS_SUCCESS) {
                        //DLOG_DEBUG("TransactionManager::SendDiaMsg TCAP End sent successfully");
                    }
                    else {
                        DLOG_CRITICAL("TransactionManager::SendDiaMsg TCAP End could not be sent");
                    }
                }
                else
                {
                    if ((ret = TCAP_Component::Send(ISS7_Stack, outTcapEndDlg, outTcapCpt)) == ITS_SUCCESS) {

                        if ((ret = TCAP_Dialogue::Send(ISS7_Stack, outTcapEndDlg)) == ITS_SUCCESS) {

                            UPDATE_SSG_STATS_NUM_OF_TCCOMP_SENT;
                            //DLOG_DEBUG("TCAP End with dialogue id %d successfully sent", outTcapEndDlg->GetDialogueID());

                        } else {
                            DLOG_CRITICAL("TransactionManager::sendDiaMsg TCAP Result Last sent successfully. But TCAP End could not be sent");
                        }
                    } else {
                        DLOG_CRITICAL("TransactionManager::sendDiaMsg Unable to send TCAP message (Result Last in End");
                    }
                }
                if(outTcapEndDlg)
                {
                    delete outTcapEndDlg;
                    outTcapEndDlg = NULL;
                }
                if(outTcapCpt)
                {
                    delete outTcapCpt;
                    outTcapCpt = NULL;
                }
            }
        }

        if(retAct.action == IWF_RA_RESPOND_ONLY)
        {
            pbRoutingLabel routingLabel;
            TCAP_Continue *outTcapDlg = new TCAP_Continue();
            TcapCptList *tcapCptList = iwfFsm->GetTcapCptList();
            outTcapDlg->SetApplicationContext(retAct.app_ctxt);
            outTcapDlg->SetDialogueID(inTcapDlg->GetDialogueID());
            //DLOG_DEBUG("Interim TCAP Dialogue Id: %d", inTcapDlg->GetDialogueID());

            routingLabel = iwfFsm->GetRoutingLabel();
#ifdef USE_FULL_SCCP_ADDRESS
            SCCP_CalledPartyAddr selfSccpAddr = iwfFsm->GetSelfSccpAddr();
#else
            SCCP_CalledPartyAddr selfSccpAddr;
            iwfFsm->GetSelfSccpAddr(selfSccpAddr);
#endif

            if (!IwfController::Instance().Config().LocalConfig().SelfSccpAddress().IsRouteByGT())
            {
                outTcapDlg->SetOrigAddr(routingLabel.isnational(),
                        routingLabel.opc(),
                        routingLabel.ossn());
            }
            else
            {
                outTcapDlg->SetOrigAddr(selfSccpAddr);
                outTcapDlg->SetOPC(routingLabel.opc());
            }

            // Get QoS from incoming dialogue.
            ITS_OCTET flags = 0x00;
            ITS_OCTET slsK  = 0x00;
            ITS_OCTET prio  = 0x00;
            ITS_OCTET nind  = 0x00;

            inTcapDlg->GetQualityOfService(flags, slsK, prio, nind);

            outTcapDlg->SetQualityOfService(QOSI_SEQ_CTRL|QOSI_SLS_KEY|QOSI_RET_OPT, inTcapDlg->GetDialogueID() % IWF_NUM_SLS, prio, nind);

            std::list <TCAP_Component> outTcapCpt = tcapCptList->GetTcapCptList();
            tcapCptList->ClearTcapCptList();

            bool send = true;
            while(!outTcapCpt.empty())
            {
                TCAP_Component tcapCpt = outTcapCpt.front();
                if ((ret = TCAP_Component::Send(ISS7_Stack, outTcapDlg, &tcapCpt)) != ITS_SUCCESS) {
                    send = false;
                    break;
                }
                UPDATE_SSG_STATS_NUM_OF_TCCOMP_SENT;
                outTcapCpt.pop_front();
            }
            if(send)
            {
                if ((ret = TCAP_Dialogue::Send(ISS7_Stack, outTcapDlg)) != ITS_SUCCESS) {

                    DLOG_CRITICAL("TransactionManager::sendDiaMsg TCAP Continue could not be sent");

                }
                else {

                    //DLOG_DEBUG("TCAP Continue with dialogue id %d mapping to session Id %s successfully sent", outTcapDlg->GetDialogueID(),iwfFsm->GetDiaSessionId().c_str());
                    if(iwfFsm->IsStartNoEventTimerSet())
                    {
                        translator->StartTimerHandling(iwfFsm,ETimerType::NO_EVENT_TIMER);
                        iwfFsm->SetStartNoEventTimer(false);
                    }

                    //DLOG_DEBUG("TransactionManager::sendDiaMsg Store LocalTransactionId in userData.");
                    translator->SetLocalTransId(outTcapDlg->GetDialogueID(),iwfFsm);
                }
            }
            else {
                DLOG_CRITICAL("TransactionManager::sendDiaMsg Unable to send TCAP message (Result Last in Continue");
            }

            if (outTcapDlg != NULL) {
                delete outTcapDlg;
                outTcapDlg = NULL;
            }
        }


        if (diaCmd)
        {
            //delete diaCmd;
            //diaCmd = NULL;
        }

        //DLOG_DEBUG("TransactionManager::sendDiaMsg() Exit");

        if (routingParams != NULL) {
            delete routingParams;
            routingParams = NULL;
        }
    }
    catch(diameter::CodecExceptionToApp& e)
    {
        DLOG_ERROR("Exception: %s, Error Cause: %s ", e.name(), e.what());
        DLOG_ERROR("errorcode for sessionId %s is %d", e.sessionId(), e.errcode());
        std::vector<int> missingAvpList = e.getMissingAVPList();
        for(unsigned int i = 0 ; i<missingAvpList.size() ; i++)
        {
            DLOG_ERROR("Missing avp : %d",missingAvpList[i]);
        }
    }
    catch(std::exception& e)
    {
        DLOG_ERROR("### Exception on decode %s ###", e.what());
        ret = !ITS_SUCCESS;
    }
    catch(...)
    {
        DLOG_ERROR("### Unknown exception on Decode ###");
        ret = !ITS_SUCCESS;
    }

    return ret;
}

int TransactionManager::SendDiaErrResp(IwfFsm *iwfFsm)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("TransactionManager::sendDiaErrResp() Entry");
    int ret = ITS_SUCCESS;
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
    DIA_BASE_CMD *inCmd = iwfFsm->GetCurrRcvdDiaMsg();
    IwfTranslator *translator = iwfFsm->GetTranslator();

    /* As translator is stored on IwfFsm so no need to look into
     * RoutingRules if it is not set we can set to default translator*/
    if (translator == NULL)
    {
        translator = IwfController::Instance().GetTranslator(0);
    }

    /*if(iwfFsm->GetUpstrmReqProtocol() == CAP_GE)
      {
      translator = IwfController::Instance().GetTranslator(CAP_TO_RO_STR);
      }
      else
      {
      translator = GetTranslatorFromRcvdDiaMsg(inCmd, iwfFsm);
      }*/

    DIA_BASE_CMD *diaCmd = NULL;
    DIA_BASE_CMD *out = NULL;
    IwfReturnAction retAct;

    if ((ret = translator->BuildDiaErrorResponse(iwfFsm, inCmd, diaCmd, retAct)) != ITS_SUCCESS) {
        if (diaCmd != NULL) {
            DLOG_ERROR("TransactionManager::sendDiaErrResp Unable Build Dia Error Response!!");
            delete diaCmd;
            diaCmd = NULL;
        }
    }

    if(retAct.action != IWF_RA_DROP)
    {
        if (ret == ITS_DIA_MISSING_AVP)
        {
            if ((ret = translator->BuildDiaErrorAnswer(iwfFsm,inCmd->getCommandCode(), ret, &out)) == ITS_SUCCESS)
            {

                if ((ret = diaFrame->Send(out, iwfFsm->GetDiaSessionIdx(), peerInstance, flags)) == ITS_SUCCESS) {
                    DLOG_DEBUG("Diameter Error Response sent Successfully");
                }
                else
                {
                    DLOG_ERROR("TransactionManager::sendDiaErrResp Diameter Error Response sent Failed");
                }
            }
            else
            {
                DLOG_ERROR("Unable to build Diameter Error Answer");
            }
        }
        else if((ret = IsDiaErrorSetInIwfFsm(iwfFsm)))
        {
            if ((ret = translator->BuildDiaErrorAnswer(iwfFsm,inCmd->getCommandCode(), ret, &out)) == ITS_SUCCESS)
            {
                if ((ret = diaFrame->Send(out, iwfFsm->GetDiaSessionIdx(), peerInstance, flags)) == ITS_SUCCESS) {
                    DLOG_DEBUG("Diameter Error Response sent Successfully");
                }
                else
                {
                    DLOG_ERROR("TransactionManager::sendDiaErrResp Diameter Error Response sent Failed");
                }
            }
            else
            {
                DLOG_ERROR("Unable to build Diameter Error Answer");
            }
            iwfFsm->SetErrorCode(0);
        }
    }

    DLOG_DEBUG("TransactionManager::sendDiaErrResp() Exit");

    return ITS_SUCCESS;
}

int TransactionManager::IsDiaErrorSetInIwfFsm(IwfFsm* iwfFsm)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int error = 0;
    //DLOG_DEBUG("TransactionManager::IsDiaErrorSetInIwfFsm() Entry");
    if(iwfFsm)
    {
        error = iwfFsm->GetErrorCode();
        if(error == ITS_DIA_UNABLE_TO_DELIVER ||
                error == ITS_DIA_UNABLE_TO_COMPLY ||
                error == DIAMETER_ERROR_USER_UNKNOWN ||
                error == DIAMETER_ERROR_ROAMING_NOT_ALLOWED ||
                error == DIAMETER_ERROR_EQUIPMENT_UNKNOWN ||
                error == DIAMETER_ERROR_UNKOWN_SERVING_NODE ||
                error == DIAMETER_ERROR_DIAMETER_END_USER_SERVICE_DENIED ||
                error == DIAMETER_ERROR_CREDIT_CONTROL_NOT_APPLICABLE ||
                error == DIAMETER_ERROR_OTHER_ERROR ||
                error == DIAMETER_ERROR_NODE_NOT_RESPONSIBLE)
        {
            DLOG_DEBUG("Error set on IwfFsm is valid");
        }
        else
        {
            DLOG_ERROR("Invalid Error set on IwfFsm");
        }
    }
    //DLOG_DEBUG("TransactionManager::IsDiaErrorSetInIwfFsm() Exit");
    return error;
}

int TransactionManager::ResetCurrRcvdDiaMsg(IwfFsm* iwfFsm) {

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::ResetCurrRcvdDiaMsg() Entry");

    DIA_BASE_CMD *currRcvdDiaMsg = NULL;

    if (iwfFsm != NULL) {

        currRcvdDiaMsg = iwfFsm->GetCurrRcvdDiaMsg();

        if (currRcvdDiaMsg != NULL) {

            delete currRcvdDiaMsg;
            currRcvdDiaMsg = NULL;

            iwfFsm->SetCurrRcvdDiaMsg(NULL);
        }
    }

    //DLOG_DEBUG("TransactionManager::ResetCurrRcvdDiaMsg() Exit");

    return ITS_SUCCESS;
}

int TransactionManager::ResetCurrRcvdTcapMsg(IwfFsm* iwfFsm) {

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::ResetCurrRcvdTcapMsg() Entry");

    TCAP_Component *currRcvdTcapCpt = NULL;

    bool deleteDialogue = false;

    if (iwfFsm != NULL) {

        currRcvdTcapCpt = iwfFsm->GetCurrRcvdTcapCpt();

        if (currRcvdTcapCpt != NULL) {
            if(currRcvdTcapCpt->GetLast())
                deleteDialogue = true;

            delete currRcvdTcapCpt;
            currRcvdTcapCpt = NULL;

            iwfFsm->SetCurrRcvdTcapCpt(NULL);
        }
        else
        {
            /* Setting this flag to true as Component is NULL but
             * need to delete Dialogue Portion */
            deleteDialogue = true;
        }
        /*Commenting below code since on every recv of Dlg part of Tcap,
         * deletion is taken care after erase from <transId,TcapDlg> map */
#if 0
        currRcvdTcapDlg = iwfFsm->GetCurrRcvdTcapDlg();

        if (currRcvdTcapDlg != NULL && deleteDialogue)
        {
            delete currRcvdTcapDlg;
            currRcvdTcapDlg = NULL;

            iwfFsm->SetCurrRcvdTcapDlg(NULL);
        }
#endif

    }

    //DLOG_DEBUG("TransactionManager::ResetCurrRcvdTcapMsg() Exit");

    return ITS_SUCCESS;
}

bool TransactionManager::IsRcvdDiaReqMsgServerInitiated(DIA_BASE_CMD *diaCmd) {

    bool ret = true;

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::IsRcvdDiaReqMsgServerInitiated() Entry");

    switch (diaCmd->getCommandCode()) {
        case DIA_CMD_CL: //Cancel Location
            break;

        case DIA_CMD_ID: //Insert Subscriber Data
            break;

        case DIA_CMD_DS: //Delete Subscriber Data
            break;

        case DIA_CMD_RS: //Reset
            break;

        default:
            ret = false;
    }

    //DLOG_DEBUG("TransactionManager::IsRcvdDiaReqMsgServerInitiated() Exit");
    return ret;

}

bool TransactionManager::IsRcvdDiaMsgResetResp(DIA_BASE_CMD *diaCmd) {
    bool ret = true;
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::IsRcvdDiaMsgResetResp Entry");
    if (diaCmd->isRequest()) {

        //DLOG_DEBUG("Received Diameter message is NOT a Response");
        ret = false;
    }
    switch (diaCmd->getCommandCode()) {
        case DIA_CMD_RS: //Reset
            break;

        default:
            ret = false;
    }
    //DLOG_DEBUG("TransactionManager::IsRcvdDiaMsgResetResp Exit");
    return ret;
}

bool TransactionManager::IsRcvdDiaMsgResetReq(DIA_BASE_CMD *diaCmd) {

    bool ret = true;

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::IsRcvdDiaMsgResetReq Entry");

    if (!(diaCmd->isRequest())) {

        //DLOG_ERROR("Received Diameter message is NOT a Request");
        ret = false;
    }

    switch (diaCmd->getCommandCode()) {
        case DIA_CMD_RS: //Reset
            break;

        default:
            ret = false;
    }

    //DLOG_DEBUG("TransactionManager::IsRcvdDiaMsgResetReq Exit");
    return ret;

}

bool TransactionManager::IsRcvdTcapReqMsgServerInitiated(TCAP_Component *tcapCpt) {

    bool ret = true;
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::IsRcvdTcapReqMsgServerInitiated() Entry");

    ITS_LONG opCode = 0;
    ITS_ByteArray buf;
    ITS_USHORT cptType = tcapCpt->GetComponentType();

    if (cptType != TCPPT_TC_INVOKE)
    {
        return !ITS_SUCCESS;
    }

    TCAP_Invoke *tcapIvk = static_cast<TCAP_Invoke*>(tcapCpt);
    tcapIvk->GetOperation(opCode);

    switch (opCode)
    {
        case map_common::OP_insertSubscriberData:
        case map_common::OP_provideSubscriberInfo:
        case map_common::OP_deleteSubscriberData:
        case map_common::OP_cancelLocation:
        case map_common::OP_activateTraceMode:
        case map_common::OP_deactivateTraceMode:
        case map_common::OP_reset:
            break;

        default:
            ret = false;
    }

    //DLOG_DEBUG("TransactionManager::IsRcvdTcapReqMsgServerInitiated() Exit");
    return ret;

}

bool TransactionManager::IsRcvdTcapReqMsgResetArg(TCAP_Component *tcapCpt) {

    bool ret = true;
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::IsRcvdTcapReqMsgServerInitiated() Entry");

    ITS_LONG opCode = 0;
    ITS_ByteArray buf;
    ITS_USHORT cptType = tcapCpt->GetComponentType();

    if (cptType != TCPPT_TC_INVOKE)
    {
        return !ITS_SUCCESS;
    }

    TCAP_Invoke *tcapIvk = static_cast<TCAP_Invoke*>(tcapCpt);
    tcapIvk->GetOperation(opCode);

    switch (opCode)
    {
        case map_common::OP_reset:
            break;

        default:
            ret = false;
    }

    //DLOG_DEBUG("TransactionManager::IsRcvdTcapReqMsgServerInitiated() Exit");
    return ret;

}

int TransactionManager::GetTranslatorId(std::string userName, int32_t serviceKey, IwfFsm *iwfFsm)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::GetTranslatorId Entry");
    ITS_INT result = -1;
    std::string mcc = "", mnc = "";
    std::string appId = DIAMETER_S6A_APPLICATION_ID;
    std::string gtAddrDigits = "";
    int32_t Ossn = HLR;

    if(userName.empty())
    {
        return result;
    }

    if(iwfFsm && iwfFsm->GetUpstrmReqProtocol() == CAP_GE)
    {
        appId = DIAMETER_RO_APPLICATION_ID;
        Ossn = CAP;
    }

    IWFUtils::ExtractMncMcc(userName, mcc, mnc);

    //if(IwfController::Instance().Config().RoutingRules().IsRouteAvailable(mcc, mnc, appId, serviceKey, gtAddrDigits))
    std::string RuleName("");
    std::string imsiPrefix = mcc + mnc;
    if(ITS_SUCCESS != iwfFsm->GetTransactionManager()->Evaluate(imsiPrefix,serviceKey,RuleName,Ossn))
    {
        DLOG_ERROR("Could not find a RuleName configured.");
        return !ITS_SUCCESS;
    }

    if(IwfController::Instance().Config().RoutingRules().IsRouteAvailable(RuleName,gtAddrDigits))
    {
        //return (IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId, serviceKey, gtAddrDigits)->TranslatorId());
        return (IwfController::Instance().Config().RoutingRules().Route(RuleName,gtAddrDigits)->TranslatorId());

    }

    //DLOG_DEBUG("TransactionManager::GetTranslatorId Exit");
    return result;
}

#if 0
int TransactionManager::GetRoutingParams(std::string strSgsnAddr, RoutingParams *&routingParams)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    RoutingParams *lRoutingParams = new RoutingParams();
    routingParams = lRoutingParams;

    if (lRoutingParams != NULL) {

        lRoutingParams->oPc = IwfController::Instance().Config().LocalConfig().OriginPointCode();
        lRoutingParams->aPc = IwfController::Instance().Config().LocalConfig().AdjacentPointCode();

        lRoutingParams->ivkTimeout = IwfController::Instance().Config().LocalConfig().InvokeTimeout();

        lRoutingParams->useSccpCdPAFromInMsg = IwfController::Instance().Config().LocalConfig().IsUseSccpCdPAFromInMsg();

        //lRoutingParams->oSsn = (ITS_OCTET) IwfController::Instance().Config().getOssnFor();
        lRoutingParams->oSsn = HLR;

        lRoutingParams->family = IwfController::Instance().Config().Destinations().GetDestForPC(strSgsnAddr).Family();

        lRoutingParams->isNational = IwfController::Instance().Config().Destinations().GetDestForPC(strSgsnAddr).IsNational();
        lRoutingParams->dPc = IwfController::Instance().Config().Destinations().GetDestForPC(strSgsnAddr).PointCode();
        lRoutingParams->dSsn = (ITS_OCTET) IwfController::Instance().Config().Destinations().GetDestForPC(strSgsnAddr).SSN();

        IwfAddrType adrType = IwfController::Instance().Config().Destinations().GetDestForPC(strSgsnAddr).Type();
        lRoutingParams->dSSNPresent = IwfController::Instance().Config().Destinations().GetDestForPC(strSgsnAddr).IsSSNPresent();
        lRoutingParams->routeByGT = false;
        if (adrType == IWF_ADDR_GT)
        {
            lRoutingParams->routeByGT = true; // TODO: use it from configuration
        }

        lRoutingParams->gti = IwfController::Instance().Config().Destinations().GetDestForPC(strSgsnAddr).GTI();

        lRoutingParams->tt = IwfController::Instance().Config().Destinations().GetDestForPC(strSgsnAddr).TransType();

        lRoutingParams->np = IwfController::Instance().Config().Destinations().GetDestForPC(strSgsnAddr).NumberingPlan();

        lRoutingParams->ecsNationalSpecific =
            IwfController::Instance().Config().Destinations().GetDestForPC(strSgsnAddr).IsNationalSpecificECS();
        std::string gtaddr = IwfController::Instance().Config().Destinations().GetDestForPC(strSgsnAddr).GtAddr();

        lRoutingParams->gtAddr = gtaddr;

    } else {

        DLOG_ERROR("Could not allocate memory for storing routing information");

        routingParams = NULL;

        return ITS_ENOMEM;
    }
    return ITS_SUCCESS;
}
#endif

int TransactionManager::GetRoutingParams(IwfFsm *iwfFsm, RoutingParams *&routingParams)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::GetRoutingParams Entry");
    std::string mcc = "", mnc = "";
    std::string  appId = "";
    std::string gtAddrDigits = "";
    int32_t serviceKey = INVALID_SERVICE_KEY;
    int32_t Ossn = HLR;
    std::string userName = "",imsi = "";

    if(iwfFsm->GetUpstrmReqProtocol() == DIAMETER_S6A)
    {
        DIA_BASE_CMD* diaCmd = iwfFsm->GetCurrRcvdDiaMsg();
        diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(diaCmd))->GetBaseGenCommand();

        if(diaBaseGenCmd->getUserName())
        {
            userName = diaBaseGenCmd->getUserName()->value();
        }
        else
        {
            DLOG_ERROR("Diameter AVP UserName is not present");
            return ITS_ENOROUTE;
        }

        IWFUtils::ExtractMncMcc(userName.substr(0, userName.find('@')), mcc, mnc);
        char buf[10] = {0};
        sprintf(buf, "%u", (diaBaseGenCmd->getApplicationId()));
        appId = buf;
        imsi = mcc + mnc;
        serviceKey = WILDCARD_SERVICE_KEY;
    }
    else
    {
        /*Extract mcc and mnc from the IMSI of the MAP message*/
        if((PopulateImsiFromTcapMsg(iwfFsm, imsi, serviceKey)) == ITS_SUCCESS)
        {
            iwfFsm->SetImsi(imsi);
            DLOG_DEBUG("IMSI received in Message : %s", imsi.c_str());
            IWFUtils::ExtractMncMcc(imsi, mcc, mnc);
            if(iwfFsm->GetUpstrmReqProtocol() != CAP_GE)
            {
                appId = DIAMETER_S6A_APPLICATION_ID;
                Ossn = SGSN_SSN;
            }
            else
            {
                appId = DIAMETER_RO_APPLICATION_ID;
                Ossn = CAP;
            }
        }
        else
        {
            DLOG_ERROR("Unable to Determine imsi from incoming TCAP message");
            return ITS_ENOROUTE;
        }
    }

    //Setting wildcard "*" character based on set SelectionCriteria value.
    SelectionCriteria sc = IwfController::Instance().Config().LocalConfig().GetSelectionCriteria();
    if(SELECT_MCC_MNC == sc || SELECT_CLG_GTT_ADDR_DGTS_AND_MCC_MNC == sc)
        serviceKey = WILDCARD_SERVICE_KEY;
    if(SELECT_SK == sc)
        imsi = "*";

    std::string RuleName("");
    if(ITS_SUCCESS != Evaluate(imsi,serviceKey,RuleName,Ossn))
    {
        DLOG_ERROR("Could not find a RuleName configured.");
        return ITS_ENOROUTE;
    }

    RoutingParams *lRoutingParams = new RoutingParams();
    routingParams = lRoutingParams;


    if (lRoutingParams != NULL) {

        if (IwfController::Instance().Config().RoutingRules().IsRouteAvailable(RuleName,gtAddrDigits)) {
            lRoutingParams->oPc = IwfController::Instance().Config().LocalConfig().OriginPointCode();
            lRoutingParams->aPc = IwfController::Instance().Config().LocalConfig().AdjacentPointCode();

            lRoutingParams->ivkTimeout = IwfController::Instance().Config().LocalConfig().InvokeTimeout();

            lRoutingParams->useSccpCdPAFromInMsg = IwfController::Instance().Config().LocalConfig().IsUseSccpCdPAFromInMsg();

            lRoutingParams->oSsn = (ITS_OCTET) IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->OriginSSN();

            pbRoutingLabel routingLabel;
            routingLabel.set_isnational(this->IsNetworkIndicatorSet());
            routingLabel.set_opc(routingParams->oPc);
            routingLabel.set_ossn(routingParams->oSsn);
            routingLabel.set_usesccpcdpafrominmsg(routingParams->useSccpCdPAFromInMsg);

            iwfFsm->SetRoutingLabel(routingLabel);

            DLOG_DEBUG("Route FOUND for SelectionCriteria %s",
                    (GetSelectionCriteria(IwfController::Instance().Config().LocalConfig().GetSelectionCriteria())).c_str());

            /* As these Destination Parameters are only required for s6a-Map translation so checking for upstream protocol */
            /* Added the SGSN_SSN check to handle unexpected message ULR when IWF is acting as a HLR in case of MAP-S6a */
            if(iwfFsm->GetUpstrmReqProtocol() == DIAMETER_S6A && (!(IsRcvdDiaReqMsgServerInitiated(iwfFsm->GetCurrRcvdDiaMsg())) &&
                        lRoutingParams->oSsn == (ITS_OCTET)SGSN_SSN))
            {
                //lRoutingParams->family = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId, serviceKey, gtAddrDigits)->Dest().Family();

                //lRoutingParams->isNational = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId, serviceKey, gtAddrDigits)->Dest().IsNational();
                //lRoutingParams->dPc = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId, serviceKey, gtAddrDigits)->Dest().PointCode();
                //lRoutingParams->dSsn = (ITS_OCTET) IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId, serviceKey, gtAddrDigits)->Dest().SSN();

                //IwfAddrType adrType = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId, serviceKey, gtAddrDigits)->Dest().Type();
                //lRoutingParams->dSSNPresent = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId, serviceKey, gtAddrDigits)->Dest().IsSSNPresent();

                lRoutingParams->family = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->Dest().Family();

                lRoutingParams->isNational = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->Dest().IsNational();
                lRoutingParams->dPc = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->Dest().PointCode();
                lRoutingParams->dSsn = (ITS_OCTET) IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->Dest().SSN();

                IwfAddrType adrType = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->Dest().Type();
                lRoutingParams->dSSNPresent = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->Dest().IsSSNPresent();
                lRoutingParams->routeByGT = false;
                if (adrType == IWF_ADDR_GT)
                {
                    iwfFsm->SetRouteByGT(true);
                    lRoutingParams->routeByGT = true; // TODO: use it from configuration
                }
                //lRoutingParams->gti = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId, serviceKey, gtAddrDigits)->Dest().GTI();
                //lRoutingParams->tt = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId, serviceKey, gtAddrDigits)->Dest().TransType();
                //lRoutingParams->np = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId, serviceKey, gtAddrDigits)->Dest().NumberingPlan();
                //lRoutingParams->ecsNationalSpecific = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId, serviceKey, gtAddrDigits)->Dest().IsNationalSpecificECS();
                //std::string gtaddr = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId, serviceKey, gtAddrDigits)->Dest().GtAddr();


                lRoutingParams->gti = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->Dest().GTI();
                lRoutingParams->tt = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->Dest().TransType();
                lRoutingParams->np = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->Dest().NumberingPlan();
                lRoutingParams->ecsNationalSpecific = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->Dest().IsNationalSpecificECS();
                std::string gtaddr = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->Dest().GtAddr();
                if (gtaddr.length() <= 0)
                {
                    lRoutingParams->gtAddr = userName.substr(0, userName.find('@'));
                }
                else
                {
                    lRoutingParams->gtAddr = gtaddr;
                }
            }

            /*Get the Translator Id based on the Routing Rules*/
            //lRoutingParams->transId = IwfController::Instance().Config().RoutingRules().Route(mcc, mnc, appId, serviceKey, gtAddrDigits)->TranslatorId();
            lRoutingParams->transId = IwfController::Instance().Config().RoutingRules().Route(RuleName,gtAddrDigits)->TranslatorId();
            DLOG_DEBUG("IWF Translator populated into Routing Params:: lRoutingParams->transId %d",
                    lRoutingParams->transId);
            IwfTranslator* translator = IwfController::Instance().GetTranslator(lRoutingParams->transId);
            iwfFsm->SetActionRuleName(IwfController::Instance().Config().RoutingRules().Route(RuleName,gtAddrDigits)->GetProtActionRuleName());
            DLOG_DEBUG("ProtActionRuleName : %s, set in IwfFsm.",(IwfController::Instance().Config().RoutingRules().Route(RuleName,gtAddrDigits)->GetProtActionRuleName()).c_str());

            if(ValidateTranslator(translator) != ITS_SUCCESS)
            {
                DLOG_ERROR("TranslatorId %d selected is not allowed ot access.",lRoutingParams->transId);
                return ITS_ENOROUTE;
            }
        }
        else
        {
            DLOG_DEBUG("Route NOT FOUND for SelectionCriteria %s",
                    (GetSelectionCriteria(IwfController::Instance().Config().LocalConfig().GetSelectionCriteria())).c_str());

            if(iwfFsm->GetUpstrmReqProtocol() == DIAMETER_S6A)
            {
                iwfFsm->SetErrorCode(IwfController::Instance().Config().LocalConfig().DiaErroCode());
            }
            else if(iwfFsm->GetUpstrmReqProtocol() == MAP_GR)
            {
                iwfFsm->SetErrorCode(MAP_ERR_UNKNOWN_SUBSCRIBER);
            }

            delete lRoutingParams;
            lRoutingParams = NULL;
            routingParams = NULL;

            return ITS_ENOROUTE;
        }
    } else {

        DLOG_ERROR("Could not allocate memory for storing routing information");

        routingParams = NULL;

        return ITS_ENOMEM;
    }
    //DLOG_DEBUG("TransactionManager::GetRoutingParams Exit");
    return ITS_SUCCESS;
}

int TransactionManager::GetAlternateRoutingParams(IwfFsm *iwfFsm, RoutingParams *lRoutingParams)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::GetAlternateRoutingParams Entry");
    std::string mcc = "", mnc = "";
    std::string  appId = "";
    std::string gtAddrDigits = "";
    int32_t serviceKey = INVALID_SERVICE_KEY;
    int32_t Ossn = HLR;
    std::string userName = "",imsi = "";

    if(iwfFsm->GetUpstrmReqProtocol() == DIAMETER_S6A)
    {
        DIA_BASE_CMD* diaCmd = iwfFsm->GetCurrRcvdDiaMsg();
        diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(diaCmd))->GetBaseGenCommand();

        if(diaBaseGenCmd->getUserName())
        {
            userName = diaBaseGenCmd->getUserName()->value();
        }
        else
        {
            DLOG_ERROR("Diameter AVP UserName is not present");
            return ITS_ENOROUTE;
        }

        IWFUtils::ExtractMncMcc(userName.substr(0, userName.find('@')), mcc, mnc);
        char buf[10] = {0};
        sprintf(buf, "%u", (diaBaseGenCmd->getApplicationId()));
        appId = buf;
        imsi = mcc + mnc;
        serviceKey = WILDCARD_SERVICE_KEY;
    }

    //Setting wildcard "*" character based on set SelectionCriteria value.
    SelectionCriteria sc = IwfController::Instance().Config().LocalConfig().GetSelectionCriteria();
    if(SELECT_MCC_MNC == sc || SELECT_CLG_GTT_ADDR_DGTS_AND_MCC_MNC == sc)
        serviceKey = WILDCARD_SERVICE_KEY;
    if(SELECT_SK == sc)
        imsi = "*";

    std::string RuleName("");
    if(ITS_SUCCESS != Evaluate(imsi,serviceKey,RuleName,Ossn))
    {
        DLOG_ERROR("Could not find a RuleName configured.");
        return ITS_ENOROUTE;
    }

    if (lRoutingParams != NULL) {

        if (IwfController::Instance().Config().RoutingRules().IsRouteAvailable(RuleName,gtAddrDigits)) {

            if(IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->IsAltDestinationSet())
            {
                lRoutingParams->family = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->AltDest().Family();

                lRoutingParams->isNational = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->AltDest().IsNational();
                lRoutingParams->dPc = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->AltDest().PointCode();
                lRoutingParams->dSsn = (ITS_OCTET) IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->AltDest().SSN();

                IwfAddrType adrType = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->AltDest().Type();
                lRoutingParams->dSSNPresent = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->AltDest().IsSSNPresent();
                lRoutingParams->routeByGT = false;
                if (adrType == IWF_ADDR_GT)
                {
                    iwfFsm->SetRouteByGT(true);
                    lRoutingParams->routeByGT = true; // TODO: use it from configuration
                }

                lRoutingParams->gti = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->AltDest().GTI();
                lRoutingParams->tt = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->AltDest().TransType();
                lRoutingParams->np = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->AltDest().NumberingPlan();
                lRoutingParams->ecsNationalSpecific = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->AltDest().IsNationalSpecificECS();
                std::string gtaddr = IwfController::Instance().Config().RoutingRules().Route(RuleName, gtAddrDigits)->AltDest().GtAddr();
                if (gtaddr.length() <= 0)
                {
                    lRoutingParams->gtAddr = userName.substr(0, userName.find('@'));
                }
                else
                {
                    lRoutingParams->gtAddr = gtaddr;
                }
            }
            else
            {
                DLOG_DEBUG("Alternate Destination is Not Configured for this Translator Rule");
                return !ITS_SUCCESS;
            }
        }
    }
    //DLOG_DEBUG("TransactionManager::GetAlternateRoutingParams Exit");
    return ITS_SUCCESS;
}

std::vector<byte>
TransactionManager::EncodeRemoteGTTAddress(SCCPParameters *rtparams)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    uint8_t digits[20];
    int     dglen = 0;
    std::vector<byte> address;

    for (int i=0;i<rtparams->cpd_itu.m_gttLength;i++)
    {
        address.push_back(rtparams->cpd_itu.m_gttInfo[i]);
    }

    return address;
}

    std::vector<byte>
TransactionManager::EncodeRemoteGTTAddress(RoutingParams *rtparams)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    uint8_t digits[20];
    int     dglen = 0;
    std::vector<byte> address;

    std::string valstr = rtparams->gtAddr.substr(0, rtparams->gtAddr.find('@'));

    dglen = IWFUtils::StringToTBCD(valstr, digits, sizeof(digits));
    bool isOdd = valstr.length() & 0x01? true:false;

    if ((rtparams->family == ITS_FLAG_ANSI && rtparams->gti == ANSI_SCCP_GTI_001) ||
            (rtparams->family == ITS_FLAG_CCITT && rtparams->gti == ITU_SCCP_GTI_003))
    {
        uint8_t ecs = ((rtparams->np << 4) & 0xF0);
        address.push_back(rtparams->tt);

        if (rtparams->ecsNationalSpecific && rtparams->family == ITS_FLAG_CCITT)
        {
            ecs |= SCCP_GTT_ES_NATIONAL_SPECIFIC;
        }
        else
        {
            if (isOdd)
            {
                ecs |= SCCP_GTT_ES_BCD_ODD; // make this an odd digit
            }
            else
            {
                ecs |= SCCP_GTT_ES_BCD_EVEN;
            }
        }
        address.push_back(ecs);
    }
    else if ((rtparams->family == ITS_FLAG_ANSI && rtparams->gti == ANSI_SCCP_GTI_002) ||
            (rtparams->family == ITS_FLAG_CCITT && rtparams->gti == ITU_SCCP_GTI_002))
    {
        address.push_back(rtparams->tt);
    }
    else if ((rtparams->family == ITS_FLAG_CCITT && rtparams->gti == ITU_SCCP_GTI_001))
    {
        uint8_t nai = ITU_SCCP_NAI_INTERNATIONAL;
        if (isOdd)
        {
            nai |= ITU_SCCP_ENABLE_ODD_IND;
        }
        address.push_back(nai);
    }
    else if (rtparams->family == ITS_FLAG_CCITT && rtparams->gti == ITU_SCCP_GTI_004)
    {
        uint8_t ecs = ((rtparams->np << 4) & 0xF0);
        address.push_back(rtparams->tt);
        if (rtparams->ecsNationalSpecific)
        {
            ecs |= SCCP_GTT_ES_NATIONAL_SPECIFIC;
        }
        else
        {
            if (isOdd)
            {
                ecs |= SCCP_GTT_ES_BCD_ODD; // make this an odd digit
            }
            else
            {
                ecs |= SCCP_GTT_ES_BCD_EVEN;
            }
        }
        address.push_back(ecs);
        address.push_back(ITU_SCCP_NAI_INTERNATIONAL); // International or national.
    }
    else
    {
        DLOG_ERROR("Invalid GTT Address Indicators");
    }

    address.insert(address.end(), digits, (digits + dglen));

    return address;
}

    std::vector<byte>
TransactionManager::EncodeLocalGTTAddress(ITS_OCTET& localAddrIndicator)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());

    ITS_OCTET gti = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().GTI();
    localAddrIndicator = SCCP_CPA_ROUTE_GTTI |
        (gti << 2);

    localAddrIndicator |= SCCP_CPA_HAS_SSN;

    if(IwfController::Instance().Config().LocalConfig().SelfSccpAddress().IsLocalPCIndicatorSet())
    {
        localAddrIndicator |= SCCP_CPA_HAS_PC;
    }

    if (IwfController::Instance().Config().LocalConfig().LocalNetworkIndicator())
    {
        localAddrIndicator |= SCCP_CPA_ROUTE_NAT;
    }
    else
    {
        localAddrIndicator |= SCCP_CPA_ROUTE_INT;
    }

    std::vector<byte> gttInfo;
    ITS_OCTET l_addInd = 0;
    ITS_OCTET l_tranType = 0;
    ITS_OCTET l_encScheme = 0;
    ITS_OCTET l_numPlan = 0;
    ITS_OCTET gTi = 0;
    uint8_t digits[20] = {0};
    int     dglen = 0;

    /* Storing the GT Type */
    gTi = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().GTI();
    std::string selfGtDigits = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().GtDigits();
    dglen = IWFUtils::StringToTBCD(selfGtDigits, digits, sizeof(digits));
    bool isOdd = selfGtDigits.length() & 0x01? true:false;

    switch(gTi)
    {
        case ITU_SCCP_GTI_001:
            {
                l_addInd = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().AddressIndicator();
                /* Encoding the Nature Of Address Indicator for GT Type 1 */
                uint8_t nai = (l_addInd & 0x7f);
                if (isOdd)
                {
                    nai |= ITU_SCCP_ENABLE_ODD_IND;
                }
                gttInfo.push_back(nai);
                break;
            }
        case ITU_SCCP_GTI_002:
            {
                l_tranType = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().TranslationType();
                /* Encoding the Translation Type for GT Type 1 */
                gttInfo.push_back(l_tranType);
                break;
            }
        case ITU_SCCP_GTI_003:
            {
                l_tranType = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().TranslationType();
                l_numPlan = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().NumberingPlan();
                l_encScheme = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().EncodingScheme();

                /* Encoding the Translation Type in first Octet
                 * Encoding the Numbering Plan in Higher Nibble of Second Octet
                 * and Encoding Scheme in lower nibble */

                gttInfo.push_back(l_tranType);
                uint8_t ecs = (l_numPlan & 0xf) << 4;
                if (l_encScheme == SCCP_GTT_ES_NATIONAL_SPECIFIC)
                {
                    ecs |= SCCP_GTT_ES_NATIONAL_SPECIFIC;
                }
                else
                {
                    if (isOdd)
                    {
                        ecs |= SCCP_GTT_ES_BCD_ODD; // make this an odd digit
                    }
                    else
                    {
                        ecs |= SCCP_GTT_ES_BCD_EVEN;
                    }
                }
                gttInfo.push_back(ecs);

                break;
            }
        case ITU_SCCP_GTI_004:
            {
                l_tranType = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().TranslationType();
                l_numPlan = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().NumberingPlan();
                l_encScheme = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().EncodingScheme();
                l_addInd = IwfController::Instance().Config().LocalConfig().SelfSccpAddress().AddressIndicator();

                /* Encoding the Translation Type in first Octet
                 * Encoding the Numbering Plan in Higher Nibble of Second Octet
                 * and Encoding Scheme in lower nibble
                 * Encoding Nature of Address Indicator in third Octet*/

                gttInfo.push_back(l_tranType);
                uint8_t ecs = (l_numPlan & 0xf) << 4;
                if (l_encScheme == SCCP_GTT_ES_NATIONAL_SPECIFIC)
                {
                    ecs |= SCCP_GTT_ES_NATIONAL_SPECIFIC;
                }
                else
                {
                    if (isOdd)
                    {
                        ecs |= SCCP_GTT_ES_BCD_ODD; // make this an odd digit
                    }
                    else
                    {
                        ecs |= SCCP_GTT_ES_BCD_EVEN;
                    }
                }
                gttInfo.push_back(ecs);
                gttInfo.push_back(l_addInd & 0x7f);
                break;
            }
        default:
            {
                DLOG_ERROR("Unknown GTI received");
            }
    }
    gttInfo.insert(gttInfo.end(), digits, (digits + dglen));

    return gttInfo;
}

/* For extracting imsi from received tcap message */

int TransactionManager::PopulateImsiFromTcapMsg(IwfFsm *iwfFsm, std::string &imsi, int32_t &serviceKey)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::PopulateImsiFromTcapMsg Entry");
    ITS_LONG opCode = 0;
    ITS_ByteArray buf;
    ITS_INT ret = ITS_SUCCESS;

    TCAP_Component* cpt = iwfFsm->GetCurrRcvdTcapCpt();
    ITS_USHORT cptType = cpt->GetComponentType();

    if (cptType != TCPPT_TC_INVOKE)
    {
        return !ITS_SUCCESS;
    }
    TCAP_Invoke *tcapIvk = static_cast<TCAP_Invoke*>(cpt);
    tcapIvk->GetOperation(opCode);
    switch (opCode)
    {
        case cap::OP_initialDP:
            {
                InitialDPArg idp;
                tcapIvk->GetParameter(buf);

                Octets oct(buf);
                idp.Decode(oct);
                serviceKey = idp.GetServiceKey().GetValue();
                DLOG_DEBUG("Service Key received in IDP Message : %d", serviceKey);
                if(idp.OptionIMSI())
                {
                    const std::vector<byte>& vec = idp.GetIMSI().GetArray();
                    IWFUtils::TBCDToString(&vec[0], vec.size(), imsi);
                    size_t fPos = imsi.find('F');
                    if (fPos != std::string::npos)
                    {
                        imsi.erase(fPos, std::string::npos);
                    }
                }
                else
                {
		    // As per Transatel flows, IMSI is optional in incoming IDP, so setting this imsi to dummy value for passsing translation rules 
		    imsi = "000000000000";
                    /*DLOG_ERROR(" No IMSI in IDP ");
                    iwfFsm->SetErrorCode(CAP_ERR_MISSING_PARAMETER);
                    DLOG_DEBUG("TransactionManager::PopulateImsiFromTcapMsg Exit");
                    ret = !ITS_SUCCESS;*/
                }
                break;
            }
        case cap::OP_initialDPSMS:
            {
                InitialDPSMSArg idpsms;
                tcapIvk->GetParameter(buf);

                Octets oct(buf);
                idpsms.Decode(oct);
                serviceKey = idpsms.GetServiceKey().GetValue();
                DLOG_DEBUG("Service Key received in IDPSMS Message : %d", serviceKey);
                if(idpsms.OptionIMSI())
                {
                    const std::vector<byte>& vec = idpsms.GetIMSI().GetArray();
                    IWFUtils::TBCDToString(&vec[0], vec.size(), imsi);
                    size_t fPos = imsi.find('F');
                    if (fPos != std::string::npos)
                    {
                        imsi.erase(fPos, std::string::npos);
                    }
                }
                else
                {
                    DLOG_ERROR(" No IMSI in IDPSMS ");
                    iwfFsm->SetErrorCode(CAP_ERR_MISSING_PARAMETER);
                    DLOG_DEBUG("TransactionManager::PopulateImsiFromTcapMsg Exit");
                    ret = !ITS_SUCCESS;
                }
                break;
            }

        case cap::OP_applyChargingReport:
        case cap::OP_eventReportBCSM:
        case cap::OP_eventReportSMS:
            {
                if(!(iwfFsm->GetImsi().empty()))
                {
                    imsi = iwfFsm->GetImsi();
                }
                else
                {
                    DLOG_WARNING("IMSI not set in IwfFsm");
                    ret = !ITS_SUCCESS;
                }
                break;
            }
        case map_common::OP_updateGprsLocation:
            {
                UpdateGprsLocationArg ugla;
                tcapIvk->GetParameter(buf);

                Octets oct(buf);
                ugla.Decode(oct);

                ret = ExtractImsi(iwfFsm, ugla, imsi);
                break;
            }
        case map_common::OP_sendAuthenticationInfo:
            {
                SendAuthenticationInfoArg saiarg;
                tcapIvk->GetParameter(buf);

                Octets oct(buf);
                saiarg.Decode(oct);

                ret = ExtractImsi(iwfFsm, saiarg, imsi);
                break;
            }
        case map_common::OP_purgeMS:
            {
                PurgeMS_Arg pmsarg;
                tcapIvk->GetParameter(buf);

                Octets oct(buf);
                pmsarg.Decode(oct);

                ret = ExtractImsi(iwfFsm, pmsarg, imsi);
                break;
            }
        case map_common::OP_readyForSM:
            {
                ReadyForSM_Arg rfsarg;
                tcapIvk->GetParameter(buf);

                Octets oct(buf);
                rfsarg.Decode(oct);

                ret = ExtractImsi(iwfFsm, rfsarg, imsi);
                break;
            }

        default:
            {
                DLOG_ERROR("Unexpected opCode %d on TC_Invoke", opCode);
                ret = !ITS_SUCCESS;
                break;
            }
    }
    //DLOG_DEBUG("TransactionManager::PopulateImsiFromTcapMsg Exit");
    return ret;
}

int TransactionManager::Evaluate(std::string& imsiPrefix, int32_t& serviceKey, std::string& RuleId, int32_t& Ossn)
{
    int ret = !ITS_SUCCESS;
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::Evaluate Entry");
    vector<string> matchRulesLst;
    string gtAddrDigits = "";
    std::string wildcard_imsi_prefix_value = "*";
    map<string,string>::iterator itr = IwfController::Instance().Config().GetImsiPrefixVsRuleMap().find(wildcard_imsi_prefix_value);

    if(itr != (IwfController::Instance().Config().GetImsiPrefixVsRuleMap()).end())
    {
        matchRulesLst.push_back(itr->second);
        //DLOG_DEBUG("TransactionManager::Evaluate WildCard IMSI-Prefi : '*' set for RuleName : %s.",(itr->second).c_str());
    }
    IwfController::Instance().Config().GetPrefixRulesStore().SearchString(imsiPrefix,matchRulesLst);

    //DLOG_DEBUG("Ossn to be matched for rule:%d",Ossn);

    for(int i = matchRulesLst.size() - 1; i >= 0; i--)
    {
        if(((ret = IwfController::Instance().Config().SearchServiceKey(matchRulesLst[i],serviceKey)) == ITS_SUCCESS) &&
                (IwfController::Instance().Config().RoutingRules().Route(matchRulesLst[i], gtAddrDigits)->DestinationSSN() == Ossn))
        {
            RuleId = matchRulesLst[i];
            return ret;
        }
    }
    return ret;
}

    template <class T>
int TransactionManager::ExtractImsi(IwfFsm *ctxt, T arg, std::string &imsi)
{

    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::ExtractImsi Entry");
    std::string oImsi;
    const std::vector<byte>& vec = arg.GetImsi().GetArray();
    IWFUtils::TBCDToString(&vec[0], vec.size(), oImsi);
    if(!(oImsi.empty()))
    {
        imsi = oImsi;
    }
    else
    {
        ctxt->SetErrorCode(MAP_ERR_UNKNOWN_SUBSCRIBER);
        DLOG_ERROR("Imsi not present in incoming Component");
        return !ITS_SUCCESS;
    }
    //DLOG_DEBUG("TransactionManager::ExtractImsi Exit");
    return ITS_SUCCESS;
}

bool TransactionManager::IsSubscriptionDataPresentInULA(DIA_BASE_CMD * cmd)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("TransactionManager::IsSubscriptionDataPresentInULA Entry");
    try
    {
        if(cmd)
        {
            diameter::Command* diacmd = (const_cast<DIA_BASE_CMD*>(cmd))->GetBaseGenCommand();
            if((DiaCommandCode)diacmd->getCommandCode() == DIA_CMD_UL)
            {
                s6a::SubscriptionData oSubsData;
                if (diacmd->getAvpValue(IWF_SUBSCRIPTION_DATA_AVP_CODE, &oSubsData,
                            diameter::GroupedType) == 0)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            DLOG_DEBUG("TransactionManager::IsSubscriptionDataPresentInULA Exit");
        }
    }
    catch(std::exception& e)
    {
        DLOG_ERROR("### Exception on decode %s ###", e.what());
    }
    catch(...)
    {
        DLOG_ERROR("### Unknown exception on Decode ###");
    }
    return false;
}

IwfTranslator* TransactionManager::GetTranslatorFromRcvdDiaMsg(DIA_BASE_CMD *cmd, IwfFsm *iwfFsm)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("TransactionManager::GetTranslatorFromRcvdDiaMsg() Entry");
    IwfTranslator* translator;
    std::string userName = "";
    int ret = ITS_SUCCESS;

    diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(cmd))->GetBaseGenCommand();

    if(diaBaseGenCmd->getUserName())
    {
        userName = diaBaseGenCmd->getUserName()->value();
        if ((ret = GetTranslatorId(userName, IWF_DEFAULT_SERVICE_KEY, iwfFsm)) > 0)
        {
            translator = IwfController::Instance().GetTranslator(ret);
        }
        else
        {
            translator = IwfController::Instance().GetTranslator(0);
        }
    }
    else
    {
        DLOG_ERROR("Diameter AVP UserName is not present, setting default translator");
        translator = IwfController::Instance().GetTranslator(0);
    }
    DLOG_DEBUG("TransactionManager::GetTranslatorFromRcvdDiaMsg() Exit");
    return translator;
}


void TransactionManager::SetDestCldPartyAddress(SCCP_CalledPartyAddr destAddr)
{
    m_destAddr = destAddr;
}

void TransactionManager::SetOrigSSN(ITS_OCTET ssn)
{
    m_ssn = ssn;
}

ITS_OCTET TransactionManager::GetOrigSSN()
{
    return m_ssn;
}

void TransactionManager::SetNetworkIndicatorFlag(bool networkInd)
{
    m_networkIndicator = networkInd;
}

bool TransactionManager::IsNetworkIndicatorSet()
{
    return m_networkIndicator;
}

void TransactionManager::SetReqProtocols(IwfFsm *&iwfFsm)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    /* clasify if upstream is CAP or MAP here
     * Then Set Upstrm protocol as MAP or CAP */

    //DLOG_DEBUG("TransactionManager::SetReqProtocols() Entry");
    //ITS_UINT ssn = m_destAddr.GetSSN();
#ifdef USE_FULL_SCCP_ADDRESS
    ITS_UINT ssn = iwfFsm->GetSelfSccpAddr().GetSSN();
#else
    ITS_UINT ssn = iwfFsm->GetSelfSSN();
#endif

    //DLOG_DEBUG("SSN %d received", ssn);
    switch(ssn)
    {
        case 146:
            {
                iwfFsm->SetUpstrmReqProtocol(CAP_GE);
                iwfFsm->SetDnstrmReqProtocol(DIAMETER_RO);
                break;
            }
        case 149:
        case 6:
            {
                iwfFsm->SetUpstrmReqProtocol(MAP_GR);
                iwfFsm->SetDnstrmReqProtocol(DIAMETER_S6A);
                break;
            }
        default:
            DLOG_DEBUG("Unknown OpCode %d received", m_destAddr.GetSSN());
    }
    //DLOG_DEBUG("TransactionManager::SetReqProtocols() Exit");
}

bool TransactionManager::IsInterimMsg(IwfFsm *ctxt, pbProtocol upstrmReqProt,
        DIA_BASE_CMD *diaCmd, TCAP_Dialogue *tcapDlg, TCAP_Component *tcapCpt)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::IsInterimMsg() Entry");
    bool status = false;
    bool isReq;
    IwfTranslator* translator = ctxt->GetTranslator();

    if(translator != NULL)
    {
        if (upstrmReqProt == CAP_GE)
        {
            if(diaCmd)
            {
                status = translator->IsInterimDiaMsg(ctxt, diaCmd, isReq);
            }
            else if (tcapDlg && tcapCpt)
            {
                status = translator->IsInterimTCAPMsg(tcapDlg, tcapCpt, isReq);
            }
        }
    }
    else
    {
        DLOG_ERROR("Translator not found in IwfFsm");
    }
    //DLOG_DEBUG("TransactionManager::IsInterimMsg() Exit");
    return status;
}

int TransactionManager::ProcessDiaTimeout(DiaMsg *dmsg)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int rc = ITS_SUCCESS;
    IwfTranslator* translator = NULL;

    //DLOG_DEBUG("TransactionManager:: ProcessDiaTimeout Entry");

    if ( dmsg->IsIndication() )
    {
        char *sessId = NULL;
        IwfFsm *iwfFsm = NULL;
        DLOG_DEBUG("Diameter indicationType %d for Session Id : %s",dmsg->GetIndication(),dmsg->GetIndicationData());

        switch(dmsg->GetIndication())
        {
            case TX_TIMEOUT:
                {
                    sessId = (char *) dmsg->GetIndicationData();
                    DLOG_DEBUG("TransactionManager:: DCCA Tx Timeout Indication from stack for SessionId : %s",sessId);

                    map<std::string, IwfFsm*>::iterator diaSessIdTxnEntryMapIter = m_diaSessionIdTxnEntryMap.find(sessId);

                    if (diaSessIdTxnEntryMapIter != m_diaSessionIdTxnEntryMap.end())
                    {
                        iwfFsm = static_cast<IwfFsm *> (diaSessIdTxnEntryMapIter->second);
#if 0
                        /* log the CDR for Failed calls, currently only for
                         * CAP_TO_RO_TSL */
                        if ( iwfFsm->GetUpstrmReqProtocol() == CAP_GE )
                        {
                            translator = IwfController::Instance().GetTranslator(CAP_TO_RO_STR_TSL);
                            {
                                ITS_UINT failureCause = translator->GetCDRFailureCause(iwfFsm);
                                translator->LogCDRData(iwfFsm, failureCause);
                            }
                        }
#endif

                        iwfFsm->SetErrorCode(ITS_ETIMEOUT);
                        this->ResetCurrRcvdDiaMsg(iwfFsm);
                        iwfFsm->MakeStateTransition(TIMEOUT, NULL, NULL, NULL);

                        if (iwfFsm->GetCurrentStateId() == CLOSED) {

                            std::string diaSessionId = iwfFsm->GetDiaSessionId();
                            ITS_CTXT tcapDlgId = iwfFsm->GetTcapDlgId();

                            if (IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
                            {
                                uint32_t indexKey = iwfFsm->GetReplicaIndexKey();
                                /*DLOG_DEBUG("Deleting Replication entry for SessionId : %s with index Key :%d",
                                        diaSessionId.c_str(),indexKey);*/

				if ( indexKey != 0xffffffff)
				{
					if (ReplicableData::DeleteTransactionEntryInReplica(IWF_SESSION_ENTRY_LIST, indexKey) != PB_REPL_UTILS_SUCCESS)
					{
						// Unable to delete from CB, save it for future
						DLOG_DEBUG("Unable to delete [ %s ] from CB, save it for future", diaSessionId.c_str());
						m_cbFlushGuard.Acquire();
						m_sessionsToFlushFromCB.insert(pair<int, std::string> (indexKey, diaSessionId));
						IwfController::Instance().StartBulkFetchTimer();
						m_cbFlushGuard.Release();
					}
					else
					{
						iwfFsm->DeleteEntryInReplica(IWF_STATE_REPLICATION, diaSessionId);
						IwfController::SetReplicationEntryToFreeList(indexKey);
					}
				}
                            }

                            diaSessIdTxnEntryMapIter = m_diaSessionIdTxnEntryMap.find(diaSessionId);

                            if (diaSessIdTxnEntryMapIter != m_diaSessionIdTxnEntryMap.end())
                                m_diaSessionIdTxnEntryMap.erase(diaSessIdTxnEntryMapIter);

                            map<ITS_CTXT, IwfFsm*>::iterator tcapDialogueIdTxnEntryIter;
                            tcapDialogueIdTxnEntryIter = m_tcapDialogueIdTxnEntryMap.find(tcapDlgId);
                            if (tcapDialogueIdTxnEntryIter != m_tcapDialogueIdTxnEntryMap.end())
                                m_tcapDialogueIdTxnEntryMap.erase(tcapDialogueIdTxnEntryIter);

                            map<ITS_CTXT, TCAP_Dialogue*>::iterator rcvdTcapDialogueIdDialogueIter;
                            rcvdTcapDialogueIdDialogueIter = m_rcvdTcapDialogueIdDialogueMap.find(tcapDlgId);
                            if (rcvdTcapDialogueIdDialogueIter != m_rcvdTcapDialogueIdDialogueMap.end())
                            {
                                TCAP_Dialogue *tcapDialogue = rcvdTcapDialogueIdDialogueIter->second;
                                m_rcvdTcapDialogueIdDialogueMap.erase(rcvdTcapDialogueIdDialogueIter);

                                if(tcapDialogue != NULL)
                                {
                                    delete tcapDialogue;
                                    tcapDialogue = NULL;
                                }
                            }

                            if(NULL != iwfFsm)
                                iwfFsm->SetCurrRcvdTcapDlg(NULL);

                            this->ResetCurrRcvdDiaMsg(iwfFsm);
                            this->ResetCurrRcvdTcapMsg(iwfFsm);

                            delete iwfFsm;
                            iwfFsm = NULL;
                        }
                    }
                    else
                    {
                        DLOG_ERROR("TransactionManger::Session Transaction entry not found");
                    }
                }
                break;
            case DISCONECT_IND_FROM_STACK:
                {
                    DLOG_DEBUG("TransactionManger:: Disconnect Indication from stack");
                    char* peerInfo = (char*)dmsg->GetIndicationData();
                    char* peerName, *realmName, *ptrTkn;
                    peerName = strtok_r(peerInfo, "|", &ptrTkn);
                    realmName = strtok_r(NULL, "|", &ptrTkn);
                    UpdatePeerStatusInPeerStatusDb(peerName, realmName, false);
                    if (IwfController::Instance().m_becameStandby)
                    {
                        // Compare the local peer status and the one obtained from couchbase, if local peer status matches the CB, that means
                        // The node has connected to all the peers as before
                        if (ComparePeerStatus(peerName, realmName, false))
                        {
                            // What to do here? 
                        }
                        if (ComparePeerStatus())
                        {
                            CLOG_DEBUG("TransactionManger:: setting became standby to false");
                            IwfController::Instance().m_becameStandby = false;
                        }
                    }
                    else
                    {
                        // We got a peer up indication while we are active, so replicate the state to CB
                        Json::StyledWriter writer;
                        std::string strPeerStatusData = writer.write(IwfController::Instance().m_peerStatusRoot);
                        if (ReplicableData::UpdateCommonEntryInReplica (IWF_PEER_STATUS, IWF_PEER_STATUS, strPeerStatusData, -1) != PB_REPL_UTILS_SUCCESS)
                        {
                            DLOG_DEBUG("Unable to update peer status in CB");
                            IwfController::Instance().StartBulkFetchTimer();
                        }
                        else if (m_peerStatusUpdateCounter <= IwfController::Instance().Config().LocalConfig().GetMaxPeerStatusUpdates())
                        {
                            m_peerStatusUpdateCounter++;
                            DLOG_DEBUG("Try to update peer status in CB [ %d ] times", m_peerStatusUpdateCounter);
                            IwfController::Instance().StartBulkFetchTimer();
                        }
                    }
                }
                break;
            case TIME_OUT_IND_FROM_STACK:
            case MANDATORY_AVP_MISSING_IND_FROM_STACK:
                {
                    sessId = (char *) dmsg->GetIndicationData();
                    DLOG_DEBUG("TransactionManger:: Indication from stack type %d",dmsg->GetIndication());

                    map<std::string, IwfFsm*>::iterator diaSessIdTxnEntryMapIter = m_diaSessionIdTxnEntryMap.find(sessId);

                    if (diaSessIdTxnEntryMapIter != m_diaSessionIdTxnEntryMap.end())
                    {
                        iwfFsm = static_cast<IwfFsm *> (diaSessIdTxnEntryMapIter->second);
                        translator = iwfFsm->GetTranslator();

                        /* log the CDR for Failed calls now only for
                         * CAP_TO_RO_TSL */
                        translator->CheckAndLogCDR(iwfFsm);

                        if (dmsg->GetIndication() == MANDATORY_AVP_MISSING_IND_FROM_STACK)
                        {
                            iwfFsm->SetErrorCode(IWF_EBASE_MAND_AVP_MISSING);
                        }
                        else
                        {
                            iwfFsm->SetErrorCode(IWF_EAUTH_SESSION_TIMEOUT);
                        }
                        this->ResetCurrRcvdDiaMsg(iwfFsm);
                        iwfFsm->MakeStateTransition(TIMEOUT, NULL, NULL, NULL);
                        if(iwfFsm->GetUpstrmReqProtocol() != CAP_GE && iwfFsm != NULL)
                        {
                            delete iwfFsm;
                            iwfFsm = NULL;
                        }
                    }
                    else
                    {
                        DLOG_ERROR("Session Transaction entry not found");
                    }
                }
                break;
            case AUTH_LIFE_TIME_OUT_IND_FROM_STACK:
                DLOG_DEBUG("TransactionManager:: Auth Life Timeout Indication from stack");
                break;
            case AUTH_GRACE_TIME_OUT_IND_FROM_STACK:
                DLOG_DEBUG("TransactionManager:: Auth Grace Timeout Indication from stack");
                break;
            case ABORT_IND_FROM_STACK:
                DLOG_DEBUG("TransactionManager:: Abort Indication from stack");
                break;
            case CORRUPTED_MSG_IND_FROM_STACK:
                DLOG_DEBUG("TransactionManager:: Corrupted Message Indication from stack");
                break;
            default:
                DLOG_DEBUG("TransactionManager:: Unknown Indication from stack");
                break;
        }
        if (iwfFsm)
        {
            iwfFsm->SetFlowFailure(false);
        }
    }

    //DLOG_DEBUG("TransactionManager:: ProcessDiaTimeout Exit");
    return rc;
}

int TransactionManager::ProcessDiaMsgIndicationWithData(DIA_BASE_CMD *cmd)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = ITS_SUCCESS;

    //DLOG_DEBUG("TransactionManager:: ProcessDiaMsgIndicationWithData() Entry");

    //diameter::base::BaseGenericCommand* diaBaseGenCmd = (DIA_GEN_CMD*)cmd;
    DIA_GEN_CMD* diaBaseGenCmd = cmd->GetBaseGenCommand();
    if( diaBaseGenCmd->getSessionId() == NULL )
    {
        DLOG_DEBUG("Diameter message received without SessionId, checking message...!");
        // Check the message type if its a peer message then we need to update the 
        // Peer status in the CB accordingly
        //diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_GEN_CMD*>(cmd))->GetBaseGenCommand();

        switch (diaBaseGenCmd->getCommandCode())
        {
            case DIA_CMD_CE:
                {
                    DLOG_DEBUG("Received CER/CEA from peer");
                    // If the node was standby earlier, we have to get the info from CB and compare
                    const std::string& peer = diaBaseGenCmd->getOriginHost()->value();
                    const std::string& realm = diaBaseGenCmd->getOriginRealm()->value();
                    UpdatePeerStatusInPeerStatusDb(peer, realm, true);
                    if (IwfController::Instance().m_becameStandby)
                    {
                        DLOG_DEBUG("We were standby so checking the peer status");
                        // Compare the local peer status and the one obtained from couchbase, if local peer status matches the CB, that means
                        // The node has connected to all the peers as before
                        if (ComparePeerStatus(peer, realm, true))
                        {
                            // Start sending the queued messages
                            DIA_PEER_STATUS peerStatus = { 0 };
                            PEER_INFO pInfo;
                            pInfo.peerName = peer.c_str();
                            pInfo.realmName = realm.c_str();
                            DiaMgmt::GetDiaMgmt()->GetDiaPeerStatus(&peerStatus, &pInfo);
                            if (peerStatus.pState == PEER_ST_I_OPEN ||
                                    peerStatus.pState == PEER_ST_R_OPEN)
                            {
                                ProcessPendingDiaMsgs(peer, "");
                            }
                            else
                            {
                                usleep(500000);
                                ProcessPendingDiaMsgs(peer, "");
                            }
                        }
                        if (ComparePeerStatus())
                        {
                            CLOG_DEBUG("TransactionManger:: setting became standby to false");
                            IwfController::Instance().m_becameStandby = false;
                        }
                    }
                    else
                    {
                        // We got a peer up indication while we are active, so replicate the state to CB
                        Json::StyledWriter writer;
                        std::string strPeerStatusData = writer.write(IwfController::Instance().m_peerStatusRoot);
                        DLOG_DEBUG("Update the peer status in CB [ %s ]", strPeerStatusData.c_str());
                        if (ReplicableData::UpdateCommonEntryInReplica (IWF_PEER_STATUS, IWF_PEER_STATUS, strPeerStatusData, -1) != PB_REPL_UTILS_SUCCESS)
                        {
                            DLOG_DEBUG("Unable to update peer status in CB");
                            IwfController::Instance().StartBulkFetchTimer();
                        }
                        else if (m_peerStatusUpdateCounter <= IwfController::Instance().Config().LocalConfig().GetMaxPeerStatusUpdates())
                        {
                            m_peerStatusUpdateCounter++;
                            DLOG_DEBUG("Try to update peer status in CB [ %d ] times", m_peerStatusUpdateCounter);
                            IwfController::Instance().StartBulkFetchTimer();
                        }
                    }
                    delete cmd;
                    cmd = NULL;
                }
                break;
            case DIA_CMD_DP:
                {
                    DLOG_DEBUG("Received DPR/DPA from peer");
                    // If the node was standby earlier, we have to get the info from CB and compare
                    UpdatePeerStatusInPeerStatusDb(diaBaseGenCmd->getOriginHost()->value(), diaBaseGenCmd->getOriginRealm()->value(), false);
                    if (IwfController::Instance().m_becameStandby)
                    {
                        // Compare the local peer status and the one obtained from couchbase, if local peer status matches the CB, that means
                        // The node has connected to all the peers as before
                        if (ComparePeerStatus(diaBaseGenCmd->getOriginHost()->value(), diaBaseGenCmd->getOriginRealm()->value(), false))
                        {
                            // What to do here? 
                        }
                        if (ComparePeerStatus())
                        {
                            CLOG_DEBUG("TransactionManger:: setting became standby to false");
                            IwfController::Instance().m_becameStandby = false;
                        }
                    }
                    else
                    {
                        // We got a peer up indication while we are active, so replicate the state to CB
                        Json::StyledWriter writer;
                        std::string strPeerStatusData = writer.write(IwfController::Instance().m_peerStatusRoot);
                        if (ReplicableData::UpdateCommonEntryInReplica (IWF_PEER_STATUS, IWF_PEER_STATUS, strPeerStatusData, -1) != PB_REPL_UTILS_SUCCESS)
                        {
                            DLOG_DEBUG("Unable to update peer status in CB");
                            IwfController::Instance().StartBulkFetchTimer();
                        }
                        else if (m_peerStatusUpdateCounter <= IwfController::Instance().Config().LocalConfig().GetMaxPeerStatusUpdates())
                        {
                            m_peerStatusUpdateCounter++;
                            DLOG_DEBUG("Try to update peer status in CB [ %d ] times", m_peerStatusUpdateCounter);
                            IwfController::Instance().StartBulkFetchTimer();
                        }
                    }
                    delete cmd;
                    cmd = NULL;
                }
                break;
            default:
                {
                    delete cmd;
                    cmd = NULL;
                    break;
                }
        }

        ret = !ITS_SUCCESS;
    }
    else
    {
        std::string sessionId = cmd->getSessionId()->value();
        IwfFsm *iwfFsm = NULL;

        DLOG_DEBUG("Unable to deliver diameter message with SessionId %s",sessionId.c_str());

        map<std::string, IwfFsm*>::iterator diaSessIdTxnEntryMapIter = m_diaSessionIdTxnEntryMap.find(sessionId.c_str());
        if (diaSessIdTxnEntryMapIter != m_diaSessionIdTxnEntryMap.end())
        {
            iwfFsm = static_cast<IwfFsm *> (diaSessIdTxnEntryMapIter->second);

            iwfFsm->SetErrorCode(ITS_DIA_UNABLE_TO_DELIVER);
            this->ResetCurrRcvdDiaMsg(iwfFsm);
            iwfFsm->MakeStateTransition(ERROR, NULL, NULL, NULL);
        }
        if (iwfFsm)
        {
            iwfFsm->SetFlowFailure(false);
            if(iwfFsm->GetCurrentStateId() == CLOSED)
            {
                delete iwfFsm;
                iwfFsm = NULL;
            }
        }
        delete cmd;
        cmd = NULL;
    }

    //DLOG_DEBUG("TransactionManager:: ProcessDiaMsgIndicationWithData() Exit");
    return ret;
}

std::string TransactionManager::GetSelectionCriteria(SelectionCriteria selectionCrit)
{
    std::string selectionCriteria = "";
    switch (IwfController::Instance().Config().LocalConfig().GetSelectionCriteria())
    {
        case SELECT_MCC_MNC:
            {
                selectionCriteria = "MCC and MNC";
                break;
            }
        case SELECT_CLG_GTT_ADDR_DGTS:
            {
                selectionCriteria = "CALLING_GT_ADDRESS_DIGITS";
                break;
            }
        case SELECT_CLG_GTT_ADDR_DGTS_AND_MCC_MNC:
            {
                selectionCriteria = "CALLING_GT_ADDRESS_DIGITS, MCC AND MNC";
                break;
            }
        case SELECT_SK:
            {
                selectionCriteria = "SERVICE_KEY";
                break;
            }
        case SELECT_SK_AND_MCC_MNC:
            {
                selectionCriteria = "SERVICE_KEY, MCC AND MNC";
                break;
            }
        case SELECT_CLG_GTT_ADDR_DGTS_AND_SK:
            {
                selectionCriteria = "CALLING_GT_ADDRESS_DIGITS AND SERVICE_KEY";
                break;
            }
        case SELECT_IMSI_PREFIX_AND_SK:
            {
                selectionCriteria = "IMSI_PREFIX AND SERVICE_KEY";
                break;
            }
        default:
            {
                selectionCriteria = "Invalid SelectionCriteria Configured";
                break;
            }
    }
    return selectionCriteria;
}

void TransactionManager::HandleTimeout(STimerContext& timerCtxt)
{

    //DLOG_DEBUG("TransactionManager:: HandleTimeout() Entry");
    //3 TODO :Log TimerData values.

    IwfFsm *iwfFsm = NULL;
    switch(timerCtxt.m_eKeyType)
    {
        case SESSION_ID :
            {
                map<std::string, IwfFsm*>::iterator diaSessIdIwfFsmMapIter = m_diaSessionIdTxnEntryMap.find(timerCtxt.m_strSessionId);
                if(diaSessIdIwfFsmMapIter != m_diaSessionIdTxnEntryMap.end())
                    iwfFsm = static_cast<IwfFsm *> (diaSessIdIwfFsmMapIter->second);

                break;
            }
        case DIALOG_ID :
            {
                map<ITS_CTXT, IwfFsm*>::iterator dlgIdIwfFsmMapIter = m_tcapDialogueIdTxnEntryMap.find(timerCtxt.m_uiDlgId);
                if(dlgIdIwfFsmMapIter != m_tcapDialogueIdTxnEntryMap.end())
                    iwfFsm = static_cast<IwfFsm *> (dlgIdIwfFsmMapIter->second);

                break;
            }
        case INVLAID_KEY :
            {
                DLOG_DEBUG("TransactionManager:: HandleTimeout() KeyTYpe set to INVALID_KEY in TimerData.");
                break;
            }
        case SUBSC_AUDIT:
            {
                DLOG_DEBUG("TransactionManager:: HandleTimeout() KeyType set to SUBSC_AUDIT in TimerData.");
                AuditSubscriberTable();
                break;
            }
        case BULK_FETCH:
            {
                ProcessBulkFetchTimeout(timerCtxt);
                break;
            }
        case PENDING_QUEUE_EXPIRY:
            {
                ProcessPendingQueueExpiry(timerCtxt);
                break;
            }
        default:
            {
                DLOG_DEBUG("TransactionManager:: HandleTimeout() TimerData keytype set to : %d.",timerCtxt.m_eKeyType);
                break;
            }
    }

    IwfReturnAction retVal;
    int ret = ITS_SUCCESS;

    if(NULL != iwfFsm)
    {
        DIA_BASE_CMD *outCmd = NULL;
        TCAP_Component* outCpt = NULL;

        iwfFsm->GetTranslator()->HandleTimeout(timerCtxt.m_eTimerType,
                iwfFsm,
                iwfFsm->GetCurrRcvdTcapCpt(),
                iwfFsm->GetCurrRcvdTcapDlg(),
                outCmd,
                outCpt,
                retVal);

        if(IWF_RA_RESPOND_AND_FORWARD_WITH_TERM == retVal.action)
        {
            this->ClearDiaAndTcapSession(iwfFsm);
#if 0
            SendTcapEnd(iwfFsm, true);
            /* Send the CCR-T */


            if( outCmd != NULL)
            {
                diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(outCmd))->GetBaseGenCommand();

                unsigned int diaSessionIdx = diaBaseGenCmd->getSessionIndex();
                std::string diaSessionId = diaBaseGenCmd->getSessionId()->value();

                if ((ret = DiaFrame::GetDiaFrame()->Send(outCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
                {
                    DLOG_DEBUG("Diameter message with session id %s sent successfully", diaSessionId.c_str());

                }
                else
                {
                    DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

                }

            }
#endif

        }
        else if(IWF_RA_FORWARD == retVal.action)
        {
            if( outCmd != NULL)
            {
                diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(outCmd))->GetBaseGenCommand();

                unsigned int diaSessionIdx = diaBaseGenCmd->getSessionIndex();
                std::string diaSessionId = diaBaseGenCmd->getSessionId()->value();

#ifdef NO_QUEUEING
                if ((ret = DiaFrame::GetDiaFrame()->Send(outCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
                {
                    iwfFsm->GetTranslator()->OnUpstrmFinalReqSent(iwfFsm);
                    //DLOG_DEBUG("Diameter message with session id %s sent successfully", diaSessionId.c_str());

                }
                else
                {
                    DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

                }
#else
                if ((ret = SendDiaMsgToStack(diaSessionId, outCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
                {
                    iwfFsm->GetTranslator()->OnUpstrmFinalReqSent(iwfFsm);
                    //DLOG_DEBUG("Diameter message with session id %s sent successfully", diaSessionId.c_str());

                } else {
                    DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

                }
#endif

            }
            if( outCpt != NULL )
            {
                pbRoutingLabel routingLabel;
                TCAP_Dialogue *inTcapDlg = iwfFsm->GetCurrRcvdTcapDlg();

                if(inTcapDlg == NULL)
                {
                    return;
                }

                TCAP_Continue *outTcapDlg = new TCAP_Continue();

                outTcapDlg->SetApplicationContext(retVal.app_ctxt);
                outTcapDlg->SetDialogueID(inTcapDlg->GetDialogueID());
                //DLOG_DEBUG("Interim TCAP Dialogue Id: %d", inTcapDlg->GetDialogueID());

                routingLabel = iwfFsm->GetRoutingLabel();
#ifdef USE_FULL_SCCP_ADDRESS
                SCCP_CalledPartyAddr selfSccpAddr = iwfFsm->GetSelfSccpAddr();
#else
                SCCP_CalledPartyAddr selfSccpAddr;
                iwfFsm->GetSelfSccpAddr(selfSccpAddr);
#endif

                if (!IwfController::Instance().Config().LocalConfig().SelfSccpAddress().IsRouteByGT())
                {
                    outTcapDlg->SetOrigAddr(routingLabel.isnational(),
                            routingLabel.opc(),
                            routingLabel.ossn());
                }
                else
                {
                    outTcapDlg->SetOrigAddr(selfSccpAddr);
                    outTcapDlg->SetOPC(routingLabel.opc());
                }

                // Get QoS from incoming dialogue.
                ITS_OCTET flags = 0x00;
                ITS_OCTET slsK  = 0x00;
                ITS_OCTET prio  = 0x00;
                ITS_OCTET nind  = 0x00;

                inTcapDlg->GetQualityOfService(flags, slsK, prio, nind);

                outTcapDlg->SetQualityOfService(QOSI_SEQ_CTRL|QOSI_SLS_KEY|QOSI_RET_OPT, inTcapDlg->GetDialogueID() % IWF_NUM_SLS, prio, nind);

                if ((ret = TCAP_Component::Send(ISS7_Stack, outTcapDlg, outCpt)) == ITS_SUCCESS) {

                    if ((ret = TCAP_Dialogue::Send(ISS7_Stack, outTcapDlg)) != ITS_SUCCESS) {

                        DLOG_CRITICAL("TransactionManager::HandleTimeout TCAP Result Last sent successfully. But TCAP Continue could not be sent");

                    } else {

                        UPDATE_SSG_STATS_NUM_OF_TCCOMP_SENT;
                        //DLOG_DEBUG("TCAP Continue with dialogue id %d mapping to session Id %s successfully sent", outTcapDlg->GetDialogueID(),iwfFsm->GetDiaSessionId().c_str());

                    }
                } else {
                    DLOG_CRITICAL("TransactionManager::HandleTimeout Unable to send TCAP message (Result Last in Continue)");
                }

                if (outCpt != NULL) {
                    delete outCpt;
                    outCpt = NULL;
                }

                if (outTcapDlg != NULL) {
                    delete outTcapDlg;
                    outTcapDlg = NULL;
                }
            }
        }
    }
    if (iwfFsm)
    {
        iwfFsm->SetFlowFailure(false);
    }
}

/* This method is used to clear the session on both CAP and Diameter side
 * currently its used only for CAP_RO_TSL */
int TransactionManager::ClearDiaAndTcapSession(IwfFsm* iwfFsm)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::ClearDiaAndTcapSession Entry");
    IwfTranslator *translator = NULL;
    TCAP_Component *outCpt = NULL;
    DIA_BASE_CMD *outCmd = NULL;
    ITS_UINT ret = ITS_SUCCESS;
    TCAP_Dialogue *rcvdDlg = iwfFsm->GetCurrRcvdTcapDlg();
    TCAP_End *outTcapEndDlg = new TCAP_End();

    translator = iwfFsm->GetTranslator();

    if( translator && (ITS_SUCCESS == translator->TerminateSession(iwfFsm, outCpt, outCmd) ))
    {
        if( outCpt != NULL )
        {
            std::vector<byte> rcvdAppCtxt;
            rcvdDlg->GetApplicationContext(rcvdAppCtxt);
            outTcapEndDlg->SetApplicationContext(rcvdAppCtxt);
            outTcapEndDlg->SetDialogueID(iwfFsm->GetTcapDlgId());

            ITS_OCTET flags = 0x00;
            ITS_OCTET slsK  = 0x00;
            ITS_OCTET prio  = 0x00;
            ITS_OCTET nind  = 0x00;
            rcvdDlg->GetQualityOfService(flags, slsK, prio, nind);
            outTcapEndDlg->SetQualityOfService(QOSI_SEQ_CTRL|QOSI_SLS_KEY|QOSI_RET_OPT, iwfFsm->GetTcapDlgId() % IWF_NUM_SLS, prio, nind);
            if ((ret = TCAP_Component::Send(ISS7_Stack, outTcapEndDlg, outCpt)) == ITS_SUCCESS)
            {
                if ((ret = TCAP_Dialogue::Send(ISS7_Stack, outTcapEndDlg)) == ITS_SUCCESS)
                {
                    //DLOG_DEBUG("TCAP End with dialogue id %d successfully sent", outTcapEndDlg->GetDialogueID());
                    UPDATE_SSG_STATS_NUM_OF_TCCOMP_SENT;
                }
                else
                {
                    DLOG_CRITICAL("TransactionManager::sendTcapEnd TCAP Result Last sent successfully. But TCAP End could not be sent");
                }
            }
            else
            {
                DLOG_CRITICAL("TransactionManager::sendTcapEnd Unable to send TCAP message (Result Last in End");
            }
        }
        if( outCmd != NULL )
        {
            diameter::base::BaseGenericCommand* diaBaseGenCmd = (const_cast<DIA_BASE_CMD*>(outCmd))->GetBaseGenCommand();

            unsigned int diaSessionIdx = diaBaseGenCmd->getSessionIndex();
            std::string diaSessionId = diaBaseGenCmd->getSessionId()->value();

#ifdef NO_QUEUEING
            if ((ret = DiaFrame::GetDiaFrame()->Send(outCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
            {
                /* Remove the session entry from the m_diaSessionIdTxnEntryMap?
                 * Or keep the entry and let the state machine destroy it */

                translator->OnUpstrmFinalReqSent(iwfFsm);

                //DLOG_DEBUG("Diameter message with session id %s sent successfully", diaSessionId.c_str());

            } else {
                DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

            }
#else
            if ((ret = SendDiaMsgToStack(diaSessionId, outCmd, diaSessionIdx, peerInstance, flags)) == ITS_SUCCESS)
            {

                translator->OnUpstrmFinalReqSent(iwfFsm);

                //DLOG_DEBUG("Diameter message with session id %s sent successfully", diaSessionId.c_str());

            } else {
                DLOG_CRITICAL("Unable to send Diameter message with session id %s ", diaSessionId.c_str());

            }
#endif

        }
    }
    else
    {
        DLOG_ERROR("Failed to TerminateSession for Timeout");
        ret = !ITS_SUCCESS;
    }

    if (outCpt != NULL) {
        delete outCpt;
        outCpt = NULL;
    }

    if (outTcapEndDlg != NULL) {
        delete outTcapEndDlg;
        outTcapEndDlg = NULL;
    }
    //DLOG_DEBUG("TransactionManager::ClearDiaAndTcapSession Exit");
    return ret;
}

int TransactionManager::RemoveDiaSessionTxnEntry(std::string& diaSessionId)
{
    int ret = ITS_SUCCESS;
    map<std::string, IwfFsm*>::iterator diaSessIdTxnEntryMapIter = m_diaSessionIdTxnEntryMap.find(diaSessionId);
    if (diaSessIdTxnEntryMapIter != m_diaSessionIdTxnEntryMap.end())
    {
        //DLOG_DEBUG("Removing the Session Id %s from diaSessionIdTxnEntryMap",diaSessionId.c_str());
        m_diaSessionIdTxnEntryMap.erase(diaSessIdTxnEntryMapIter);
    }
    else
    {
        DLOG_ERROR("Unable to remove Session Id : %s, does not exists in diaSessionIdTxnEntryMap", diaSessionId.c_str());
        ret = !ITS_SUCCESS;
    }
    return ret;
}

ITS_UINT TransactionManager::GetOPC(IwfFsm *ctxt)
{
    ITS_UINT opc = 0;
    TCAP_Dialogue* tcapDlg = ctxt->GetCurrRcvdTcapDlg();
    if(tcapDlg->GetDialogueType() == TCPPT_TC_BEGIN)
    {
        TCAP_Begin *begin = (TCAP_Begin*)tcapDlg;
        begin->GetOPC(opc);
    }
    return opc;
}

void TransactionManager::GetSCCPParameters(IwfFsm *ctxt, SCCPParameters& sccpParam)
{
    SCCP_CallingPartyAddr calligpartyaddr;
    SCCP_CalledPartyAddr calledpartyaddr;
    ITS_UINT opc = 0, dpc = 0;
    TCAP_Dialogue* tcapDlg = ctxt->GetCurrRcvdTcapDlg();
    if(tcapDlg->GetDialogueType() == TCPPT_TC_BEGIN)
    {
        TCAP_Begin *begin = (TCAP_Begin*)tcapDlg;
        begin->GetOrigAddr(calligpartyaddr);
        begin->GetDestAddr(calledpartyaddr);
        begin->GetOPC(opc);
        begin->GetDPC(dpc);
        sccpParam.cpa_itu.m_addrIndicator = 0;
        sccpParam.cpd_itu.m_addrIndicator = 0;

        if(!calligpartyaddr.IsRoutedByPCSSN())
        {
            sccpParam.isRouteByGT = true;
        }
        else
        {
            sccpParam.cpa_itu.m_addrIndicator |= SCCP_CPA_ROUTE_SSN;
        }

        if(calligpartyaddr.IsInternationalRouting())
        {
            sccpParam.cpa_itu.m_addrIndicator |= SCCP_CPA_ROUTE_INT;
        }
        else
        {
            sccpParam.cpa_itu.m_addrIndicator |= SCCP_CPA_ROUTE_NAT;
        }

        if(calligpartyaddr.HasPointCode())
        {
            sccpParam.cpa_itu.m_addrIndicator |= SCCP_CPA_HAS_PC;
            sccpParam.cpa_itu.m_pointcode = calligpartyaddr.GetPointCode();
        }

        if(calligpartyaddr.HasSSN())
        {
            sccpParam.cpa_itu.m_addrIndicator |= SCCP_CPA_HAS_SSN;
            sccpParam.cpa_itu.m_ssn = calligpartyaddr.GetSSN();
        }

        if(calligpartyaddr.HasGlobalTitle())
        {
            calligpartyaddr.GetGlobalTitle(sccpParam.cpa_itu.m_gttType,
                    sccpParam.cpa_itu.m_gttInfo,
                    sccpParam.cpa_itu.m_gttLength);
        }

        if(calledpartyaddr.IsRoutedByPCSSN())
        {
            sccpParam.cpd_itu.m_addrIndicator |= SCCP_CPA_ROUTE_SSN;
        }

        if(calledpartyaddr.IsInternationalRouting())
        {
            sccpParam.cpd_itu.m_addrIndicator |= SCCP_CPA_ROUTE_INT;
        }
        else
        {
            sccpParam.cpd_itu.m_addrIndicator |= SCCP_CPA_ROUTE_NAT;
        }

        if(calledpartyaddr.HasPointCode())
        {
            sccpParam.cpd_itu.m_addrIndicator |= SCCP_CPA_HAS_PC;
            sccpParam.cpd_itu.m_pointcode = calledpartyaddr.GetPointCode();
        }
        if(calledpartyaddr.HasSSN())
        {
            sccpParam.cpd_itu.m_addrIndicator |= SCCP_CPA_HAS_SSN;
            sccpParam.cpd_itu.m_ssn = calledpartyaddr.GetSSN();
        }

        if(calledpartyaddr.HasGlobalTitle())
        {
            calledpartyaddr.GetGlobalTitle(sccpParam.cpd_itu.m_gttType,
                    sccpParam.cpd_itu.m_gttInfo,
                    sccpParam.cpd_itu.m_gttLength);
        }

        sccpParam.m_opc = opc;
        sccpParam.m_dpc = dpc;
    }
}

int TransactionManager::ValidateTranslator(IwfTranslator* translator)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager:: ValidateTranslator() Entry");
    string translatorName = translator->Name();
    if(!strcasecmp(translatorName.c_str(), CAP_TO_RO_STR_TSL))
    {
        if(!LICENSE_VerifyCapability(ITS_LIC_IWF_CAP_RO_TSL))
        {
            DLOG_ERROR("License Validation failed for %s translator.",translatorName.c_str());
            IwfController::Instance().GetIwfAlarmInstance()->RaiseTranslatorLicenceViolationAlarm(LICENSE_VIOLATION_FOR_CAP_RO_TSL,
                    ALARM_IWF_TEXT_LICENSE_VIOLATED_FOR_CAP_RO_TSL_TRANSLATOR);
            //DLOG_DEBUG("TransactionManager:: ValidateTranslator() Exit");
            return ITS_ENOLICENSE;
        }
    }
    else if(!strcasecmp(translatorName.c_str(), CAP_TO_RO_STR))
    {
        if (!LICENSE_VerifyCapability(ITS_LIC_IWF_CAP_RO))
        {
            DLOG_ERROR("License Validation failed for %s translator.",translatorName.c_str());
            IwfController::Instance().GetIwfAlarmInstance()->RaiseTranslatorLicenceViolationAlarm(
                    LICENSE_VIOLATION_FOR_CAP_RO,
                    ALARM_IWF_TEXT_LICENSE_VIOLATED_FOR_CAP_RO_TRANSLATOR);
            //DLOG_DEBUG("TransactionManager:: ValidateTranslator() Exit");
            return ITS_ENOLICENSE;
        }
    }
    else if(!strcasecmp(translatorName.c_str(), MAP_TO_S6A_STR))
    {
        if (!LICENSE_VerifyCapability(ITS_LIC_IWF_MAP_S6A))
        {
            DLOG_ERROR("License Validation failed for %s translator.",translatorName.c_str());
            IwfController::Instance().GetIwfAlarmInstance()->RaiseTranslatorLicenceViolationAlarm(
                    LICENSE_VIOLATION_FOR_MAP_S6A,
                    ALARM_IWF_TEXT_LICENSE_VIOLATED_FOR_MAP_S6A_TRANSLATOR);
            //DLOG_DEBUG("TransactionManager:: ValidateTranslator() Exit");
            return ITS_ENOLICENSE;
        }
    }
    else if(!strcasecmp(translatorName.c_str(), S6A_TO_MAP_STR))
    {
        if (!LICENSE_VerifyCapability(ITS_LIC_IWF_S6A_MAP))
        {
            DLOG_ERROR("License Validation failed for %s translator.",translatorName.c_str());
            IwfController::Instance().GetIwfAlarmInstance()->RaiseTranslatorLicenceViolationAlarm(
                    LICENSE_VIOLATION_FOR_S6A_MAP,
                    ALARM_IWF_TEXT_LICENSE_VIOLATED_FOR_S6A_MAP_TRANSLATOR);
            //DLOG_DEBUG("TransactionManager:: ValidateTranslator() Exit");
            return ITS_ENOLICENSE;
        }
    }
    //DLOG_DEBUG("TransactionManager:: ValidateTranslator() Exit");
    return ITS_SUCCESS;
}


int TransactionManager::UpdateTcapLocalTransactionTable(uint32_t aspId)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = ITS_SUCCESS;
    ITS_UINT tcapDataLength = 0;
    ITS_OCTET tcapTxnData[IWF_MAX_TCAP_TXN_ENTRY] = {0};
    ITS_EVENT event;
    TCAP_TRANS_ENTRY tmpTx;
    SCCP_ADDR dAddr, oAddr;
    MTP3_HEADER mtpHdr;

    //DLOG_DEBUG("AspId for IWF: %d",aspId);
    tmpTx.ltid = 0x00ffffff | (aspId << 24);

    //Set some dummy value
    ITS_SET_CTXT(&tcapTxnData[0], 1);
    tcapDataLength += sizeof(ITS_CTXT);

    memcpy(&tcapTxnData[tcapDataLength],&tmpTx, sizeof(TCAP_TRANS_ENTRY));
    tcapDataLength += sizeof(TCAP_TRANS_ENTRY);
 
    ITS_EVENT_INIT(&event, ITS_TXID_UPDATE_EVENT_FROM_APP, tcapDataLength);
    memcpy(event.data, tcapTxnData, tcapDataLength);

    ret = TRANSPORT_PutEvent(ITS_TCAP_CCITT_SRC, &event);
    if (ret != ITS_SUCCESS)
    {
        DLOG_ERROR("Failed to post tcap transaction replication event to TCAP");
        ITS_EVENT_TERM(&event);
    }
    else
    {
        DLOG_DEBUG("Successfully posted Tcap transaction replication to TCAP");
    }
    return ret;

}

int TransactionManager::CreateTcapTransactionEntryFromReplica(pbIwfFsmInfo& pbIwfFsm, bool isLastTxn)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    int ret = ITS_SUCCESS;
    ITS_UINT tcapDataLength = 0;
    ITS_OCTET tcapTxnData[IWF_MAX_TCAP_TXN_ENTRY] = {0};
    ITS_EVENT event;
    TCAP_TRANS_ENTRY tmpTx;
    pbTcapTransactionData tcapData =  pbIwfFsm.tcapinfo();
    SCCP_ADDR dAddr, oAddr;
    MTP3_HEADER mtpHdr;

    /*DLOG_DEBUG("tcapdata->ltid : %u",tcapData.ltid());
    DLOG_DEBUG("tcapdata->rtid : %u",tcapData.rtid());
    DLOG_DEBUG("tcapdata->oaddr.len : %d",tcapData.oaddr().length());
    DLOG_DEBUG("tcapdata->oaddr.data : %x",tcapData.oaddr().addr().c_str());
    DLOG_DEBUG("tcapdata->daddr.len : %d",tcapData.daddr().length());
    DLOG_DEBUG("tcapdata->daddr.data : %x",tcapData.daddr().addr().c_str());
    DLOG_DEBUG("tcapdata->label.sio : %d",tcapData.label().sio());
    DLOG_DEBUG("tcapdata->label.label.data : %x",tcapData.label().label().c_str());
    */
    tmpTx.ltid = tcapData.ltid();
    tmpTx.rtid = tcapData.rtid();
    tmpTx.rtidLen = 4;
    tmpTx.isLastTxn = isLastTxn;
    dAddr.len = tcapData.daddr().length();
    std::string pbdaddr = tcapData.daddr().addr();
    //DLOG_DEBUG("DestAddr : %s",pbdaddr.c_str());
    int len = IWFUtils::StringToTBCD(pbdaddr, dAddr.data, pbdaddr.length());
    //memcpy(dAddr.data, (tcapData.daddr().addr().c_str()),tcapData.daddr().length());
    //tmpTx.daddr = dAddr;

    oAddr.len = tcapData.oaddr().length();
    std::string pboaddr = tcapData.oaddr().addr();
    //DLOG_DEBUG("OrgAddr : %s",pboaddr.c_str());
    len = IWFUtils::StringToTBCD(pboaddr, oAddr.data, pbdaddr.length());
    //memcpy(oAddr.data, (tcapData.oaddr().addr().c_str()),tcapData.oaddr().length());
    //tmpTx.oaddr = oAddr;

    tmpTx.daddr = oAddr;
    tmpTx.oaddr = dAddr;
    tmpTx.state = ITS_TCAP_ACTIVE;
    tmpTx.dstate = ITS_DLG_ACTIVE;
    tmpTx.dir = 2;

    mtpHdr.sio = tcapData.label().sio();
#ifndef USE_ANSI_SCCP
    memcpy(mtpHdr.label.data, tcapData.label().label().c_str(), 4);
#endif
    tmpTx.label = mtpHdr;

    //event.data[0] = (ITS_REP_EVENT_FROM_APP >> 8); // not required
    //event.data[1] = (ITS_REP_EVENT_FROM_APP & 0xFF); // not required
    //event.data[2] = pbIwfFsm.tcapdialogueid();

    ITS_SET_CTXT(&tcapTxnData[0], pbIwfFsm.tcapdialogueid());
    tcapDataLength += sizeof(ITS_CTXT);

    memcpy(&tcapTxnData[tcapDataLength],&tmpTx, sizeof(TCAP_TRANS_ENTRY));
    tcapDataLength += sizeof(TCAP_TRANS_ENTRY);

    ITS_EVENT_INIT(&event, ITS_REP_EVENT_FROM_APP, tcapDataLength);
    memcpy(event.data, tcapTxnData, tcapDataLength);

    ret = TRANSPORT_PutEvent(ITS_TCAP_CCITT_SRC, &event);
    if (ret != ITS_SUCCESS)
    {
        DLOG_ERROR("Failed to post tcap transaction replication event to TCAP");
        ITS_EVENT_TERM(&event);
    }
    else
    {
        DLOG_DEBUG("Successfully posted Tcap transaction replication to TCAP");
    }
    return ret;
}

int TransactionManager::CreateIwfFsmFromReplica(pbIwfFsmInfo& iwfFsmInfo)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::CreateIwfFsmFromReplica Entry");

    int retVal = ITS_SUCCESS;
    pbState currState = iwfFsmInfo.current();
    if((IwfController::Instance().Config().LocalConfig().isCongestionManagementEnabled()) &&
            CurrentFSMCount >= IwfController::Instance().Config().LocalConfig().GetMaxNumberOfSessionsToHold())
    {
        //NOTE: Check for Congestion Management
        DLOG_CRITICAL("TransactionManager::CreateIwfFsmFromReplica: Max Number of Sessions %d reached dropping the new requests.",
                IwfController::Instance().Config().LocalConfig().GetMaxNumberOfSessionsToHold());
        return !ITS_SUCCESS;
    }
    IwfFsm *iwfFsm = new IwfFsm(this, (States) currState.id());

    //Set the switchover flag to be used for logging CDR
    iwfFsm->SetSessionAcrossSwitchover(true);

    pbState prevState =  iwfFsmInfo.prevstate();
    iwfFsm->SetPreviousState( (States) prevState.id());

    iwfFsm->CopyIwfFsmFromReplica(iwfFsmInfo);

    DLOG_DEBUG("SessionId %s", iwfFsmInfo.diasessionid().c_str());
    m_diaSessionIdTxnEntryMap.insert(pair<std::string, IwfFsm*> (iwfFsmInfo.diasessionid(), iwfFsm));

    DLOG_DEBUG("populating m_tcapDialogueIdTxnEntryMap with DialogueId %d", iwfFsmInfo.tcapdialogueid());
    m_tcapDialogueIdTxnEntryMap.insert(pair<ITS_CTXT, IwfFsm*> (iwfFsmInfo.tcapdialogueid(), iwfFsm));

    DLOG_DEBUG("populating m_rcvdTcapDialogueIdDialogueMap with DialogueId %d", iwfFsmInfo.tcapdialogueid());
    TCAP_Dialogue* tcapDlg=NULL;
    m_rcvdTcapDialogueIdDialogueMap.insert(pair<ITS_CTXT, TCAP_Dialogue*> (iwfFsmInfo.tcapdialogueid(), tcapDlg));

    IwfTranslator *translator = IwfController::Instance().GetTranslator(iwfFsmInfo.translator().id());
    iwfFsm->SetTranslator(translator);

    if (iwfFsmInfo.has_currrcvdtcapdlg())
    {
        pbTcapDialogue tcapDlg = iwfFsmInfo.currrcvdtcapdlg();
        TCAP_Dialogue *inTcapDlg = new TCAP_Dialogue(tcapDlg.dialoguetype());
        inTcapDlg->SetDialogueID(tcapDlg.dialogueid());
        inTcapDlg->SetApplicationContext((unsigned char*)tcapDlg.applicationcontext().c_str(), tcapDlg.applicationcontext().length());
        QualityOfService pbQos = tcapDlg.qos();
        inTcapDlg->SetQualityOfService(pbQos.flags(),pbQos.slskey(),pbQos.priority(),pbQos.networkind());
        iwfFsm->SetCurrRcvdTcapDlg(inTcapDlg);
    }

    if (iwfFsmInfo.has_currrcvddiamsg())
    {
        pbDiaMsg diaMsg = iwfFsmInfo.currrcvddiamsg();
        if (diaMsg.requestbit())
        {
            diameter::ro_r10_transatel::CreditControlRequest *ccr =
                new diameter::ro_r10_transatel::CreditControlRequest();
            ccr->setSessionId(diameter::base::SessionId(diaMsg.sessionid()));
            if (diaMsg.has_username())
            {
                const diameter::base::UserName userName(diaMsg.username().c_str());
                ccr->setUserName(userName);
            }
            DIA_BASE_CMD *cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)ccr);
            if ( iwfFsmInfo.has_diameterinfo())
            {
                pbDiameterSessionData diameterInfo = iwfFsmInfo.diameterinfo();
                if ( diameterInfo.has_peerinst())
                {
                    cmd->SetIncomingPeerInst(diameterInfo.peerinst());
                }
            }
            iwfFsm->SetCurrRcvdDiaMsg(cmd);
        }
        else
        {
            diameter::ro_r10_transatel::CreditControlAnswer *cca =
                new diameter::ro_r10_transatel::CreditControlAnswer();
            cca->setSessionId(diameter::base::SessionId(diaMsg.sessionid()));
            DIA_BASE_CMD *cmd = new DIA_BASE_CMD((diameter::base::BaseGenericCommand*)cca);
            if ( iwfFsmInfo.has_diameterinfo())
            {
                pbDiameterSessionData diameterInfo = iwfFsmInfo.diameterinfo();
                if ( diameterInfo.has_peerinst())
                {
                    cmd->SetIncomingPeerInst(diameterInfo.peerinst());
                }
            }
            iwfFsm->SetCurrRcvdDiaMsg(cmd);
        }
    }

    if (iwfFsmInfo.has_currrcvdtcapcpt())
    {
        pbTcapComponent tcapCpt = iwfFsmInfo.currrcvdtcapcpt();
        TCAP_Component *inTcapCpt = new TCAP_Component(tcapCpt.componenttype());
        inTcapCpt->SetInvokeID(tcapCpt.invokeid());
        iwfFsm->SetCurrRcvdTcapCpt(inTcapCpt);
    }

    if (iwfFsmInfo.has_selfsccpaddr())
    {
        pbSccpAddress pbSelfAddr = iwfFsmInfo.selfsccpaddr();
#ifdef USE_FULL_SCCP_ADDRESS
        SCCP_CalledPartyAddr selfSccpAddr;
        selfSccpAddr.SetPointCode(pbSelfAddr.pointcode());
        selfSccpAddr.SetSSN(pbSelfAddr.ssn());
        selfSccpAddr.SetRouteByPCSSN(pbSelfAddr.routepcssn());
        selfSccpAddr.SetInternationalRouting(pbSelfAddr.internationalroute());
        std::string gtdigits = pbSelfAddr.globtitle();
        //CLOG_DEBUG("GTT digits : %s",gtdigits.c_str());
        ITS_OCTET gttInfo[32] = {0};
        int gttLen = IWFUtils::StringToTBCD(gtdigits, gttInfo, gtdigits.length());

        selfSccpAddr.SetGlobalTitle(pbSelfAddr.gtttype(),
                                    gttInfo,gttLen);
        iwfFsm->SetSelfSccpAddr(selfSccpAddr);
#else
        iwfFsm->SetSelfSccpAddr(pbSelfAddr);
#endif

        //CLOG_DEBUG("Recieved SelfSCCPAddress : %s",pbSelfAddr.DebugString().c_str());

    }

    translator->CreateUserDataContext(iwfFsm, iwfFsmInfo.userdata());

    for(int i = 0 ; i < iwfFsmInfo.timerinfo_size() ; i++)
    {
        const pbIwfTimerData& iwfTimerData = iwfFsmInfo.timerinfo(i);
        translator->StartTimerHandling(iwfFsm, iwfTimerData);
    }

    if(translator->GetTranslatorState(iwfFsm) == ER_SMS_RCVD)
    {
        if (iwfFsmInfo.userdata().caprotsl().has_callanswertimestamp())
        {
            pbIwfTimerData iwfTimerData;
            iwfTimerData.set_m_etimertype(pbIwfTimerData_ETimerType_IWF_DCCA_TX_TIMER);
            uint32_t timeDuration = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_TX_TIMER);
            DLOG_DEBUG("Starting Tx Timer at application for SMS case for duration : %d in translator state %d",
                    timeDuration,
                    translator->GetTranslatorState(iwfFsm));
            iwfTimerData.set_m_tstarttime(iwfFsmInfo.userdata().caprotsl().callanswertimestamp());
            iwfTimerData.set_m_uiduration(timeDuration);
            translator->StartTimerHandling(iwfFsm, iwfTimerData);
        }
        else
        {
            DLOG_DEBUG("CallAnswerTimeStamp missing, hence not stargin Tx Timer at application");
        }
    }

    if((translator->GetTranslatorState(iwfFsm) == ERB_RCVD || translator->GetTranslatorState(iwfFsm) == ACR_CALLACT_TRUE) &&
            iwfFsmInfo.userdata().caprotsl().has_updatetriggertimestamp())
    {
        pbIwfTimerData iwfTimerData;
        iwfTimerData.set_m_etimertype(pbIwfTimerData_ETimerType_IWF_DCCA_TX_TIMER);
        uint32_t timeDuration = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_TX_TIMER);
        DLOG_DEBUG("Starting Tx Timer at application for voice case for duration : %d in translator state %d",
                timeDuration,
                translator->GetTranslatorState(iwfFsm));
        iwfTimerData.set_m_tstarttime(iwfFsmInfo.userdata().caprotsl().updatetriggertimestamp());
        iwfTimerData.set_m_uiduration(timeDuration);
        translator->StartTimerHandling(iwfFsm, iwfTimerData);
    }

    if ( (translator->GetTranslatorState(iwfFsm) == ERB_RCVD) ||
            (translator->GetTranslatorState(iwfFsm) == ACR_CALLACT_FALSE) ||
            (translator->GetTranslatorState(iwfFsm) == FOLLOW_ON) )
    {
        if (iwfFsmInfo.userdata().caprotsl().has_discontriggertimestamp())
        {
            pbIwfTimerData iwfTimerData;
            iwfTimerData.set_m_etimertype(pbIwfTimerData_ETimerType_IWF_DCCA_TX_TIMER);
            uint32_t timeDuration = DCCAConf::GetDCCAConf()->GetConf(DCCA_CONF_TX_TIMER);
            DLOG_DEBUG("Starting Tx Timer at application for voice case for duration : %d in translator state %d",
                timeDuration,
                translator->GetTranslatorState(iwfFsm));
            iwfTimerData.set_m_tstarttime(iwfFsmInfo.userdata().caprotsl().discontriggertimestamp());
            iwfTimerData.set_m_uiduration(timeDuration);
            translator->StartTimerHandling(iwfFsm, iwfTimerData);
        }
        else
        {
            DLOG_DEBUG("DisconnnectTriggerTimeStamp missing, hence not stargin Tx Timer at application");
        }
    }
#if 0
    if (translator->GetTranslatorState(iwfFsm) == FOLLOW_ON)
    {
        pbIwfTimerData iwfTimerData;
        iwfTimerData.set_m_etimertype(pbIwfTimerData_ETimerType_IWF_ISFOLLOWON_TIMER);
        uint32_t timeDuration = SWITCHOVER_DELTA_TIME;
        DLOG_DEBUG("Starting IWF_ISFOLLOWON_TIMER for FollwOn second session with duration : %d in translator state %d",
                timeDuration,
                translator->GetTranslatorState(iwfFsm));
        iwfTimerData.set_m_tstarttime(iwfFsmInfo.userdata().caprotsl().discontriggertimestamp());
        iwfTimerData.set_m_uiduration(timeDuration);
        translator->StartTimerHandling(iwfFsm, iwfTimerData);


    }
#endif
    //DLOG_DEBUG("TransactionManager::CreateIwfFsmFromReplica Exit");
    return retVal;
}

int TransactionManager::CreateDiameterSessionEntry(pbIwfFsmInfo& pbIwfFsm)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::CreateDiameterSessionEntry entry");
    if (!pbIwfFsm.has_diasessionid() || !pbIwfFsm.has_diameterinfo())
    {
        DLOG_ERROR("No SissionId or Diameter Information");
        return !ITS_SUCCESS;
    }

    int ret = ITS_SUCCESS;
    ITS_EVENT event;
    std::string diaSessionId = pbIwfFsm.diasessionid();
    int sessionDataLength = 0;
    // Define the IWF_MAX_REP_DIA_SESSION_DATA_LENGTH macro as 256
    ITS_OCTET sessionData[IWF_MAX_REP_DIA_SESSION_DATA_LENGTH] = {0};

    const pbDiameterSessionData& pbSessionEntry = pbIwfFsm.diameterinfo();

    /* fill peer instance */
    if (pbSessionEntry.has_peerinst())
    {
    ITS_USHORT peerInst = pbSessionEntry.peerinst();
        sessionData[0] = (ITS_OCTET)(peerInst >> 8);
        sessionData[1] = (ITS_OCTET)(peerInst);
    }
    sessionDataLength += 2;

    /* get the timer values */
    if (pbSessionEntry.has_timeout())
    {
        ITS_SERIAL timeOut = pbSessionEntry.timeout();
        sessionData[sessionDataLength] = (ITS_OCTET)(timeOut >> 24);
        sessionData[sessionDataLength + 1] = (ITS_OCTET)(timeOut >> 16);
        sessionData[sessionDataLength + 2] = (ITS_OCTET)(timeOut >> 8);
        sessionData[sessionDataLength + 3] = (ITS_OCTET)(timeOut);
    }
    else
    {
        // Get it from configuration and fill
    }
    sessionDataLength += 4;

    if (pbSessionEntry.has_lifetime())
    {
    ITS_SERIAL lifeTime = pbSessionEntry.lifetime();
        sessionData[sessionDataLength] = (ITS_OCTET)(lifeTime >> 24);
        sessionData[sessionDataLength + 1] = (ITS_OCTET)(lifeTime >> 16);
        sessionData[sessionDataLength + 2] = (ITS_OCTET)(lifeTime >> 8);
        sessionData[sessionDataLength + 3] = (ITS_OCTET)(lifeTime);
    }
    else
    {
        // Get it from configuration and fill
    }
    sessionDataLength += 4;

    if (pbSessionEntry.has_graceperiod())
    {
    ITS_SERIAL gracePeriod = pbSessionEntry.graceperiod();
        sessionData[sessionDataLength] = (ITS_OCTET)(gracePeriod >> 24);
        sessionData[sessionDataLength + 1] = (ITS_OCTET)(gracePeriod >> 16);
        sessionData[sessionDataLength + 2] = (ITS_OCTET)(gracePeriod >> 8);
        sessionData[sessionDataLength + 3] = (ITS_OCTET)(gracePeriod);
    }
    else
    {
        // Get it from configuration and fill
    }
    sessionDataLength += 4;

    ITS_UINT appId = 4;
    sessionData[sessionDataLength] = (ITS_OCTET)(appId >> 24);
    sessionData[sessionDataLength + 1] = (ITS_OCTET)(appId >> 16);
    sessionData[sessionDataLength + 2] = (ITS_OCTET)(appId >> 8);
    sessionData[sessionDataLength + 3] = (ITS_OCTET)(appId);

    sessionDataLength += 4;

    // Add the session start time, last CCR time
    time_t sessionStartTime;
    time_t lastCCRSentTime;
    if (pbIwfFsm.has_userdata())
    {
        const pbStoredUserData& userData = pbIwfFsm.userdata();
        if (userData.has_caprotsl())
        {
            const pbCapRoTsl& capRoTsl = userData.caprotsl();
            if (capRoTsl.has_sessionstarttimestamp())
            {
                sessionStartTime = capRoTsl.sessionstarttimestamp();
            }
        }
    }

    for (int timerIdx = 0; timerIdx < pbIwfFsm.timerinfo_size(); timerIdx++)
    {
        const pbIwfTimerData& iwfTimerData = pbIwfFsm.timerinfo(timerIdx);
        if (iwfTimerData.m_etimertype() == pbIwfTimerData::NO_EVENT_TIMER)
        {
            sessionStartTime = iwfTimerData.m_tstarttime();
        }
        else if (iwfTimerData.m_etimertype() == pbIwfTimerData::FAKE_ACH_TIMER ||
                 iwfTimerData.m_etimertype() == pbIwfTimerData::ACR_TIMER)
        {
            lastCCRSentTime = iwfTimerData.m_tstarttime();
        }
    }

    sessionData[sessionDataLength] = (ITS_OCTET)(sessionStartTime >> 24);
    sessionData[sessionDataLength + 1] = (ITS_OCTET)(sessionStartTime >> 16);
    sessionData[sessionDataLength + 2] = (ITS_OCTET)(sessionStartTime >> 8);
    sessionData[sessionDataLength + 3] = (ITS_OCTET)(sessionStartTime);
    sessionDataLength += 4;

    sessionData[sessionDataLength] = (ITS_OCTET)(lastCCRSentTime >> 24);
    sessionData[sessionDataLength + 1] = (ITS_OCTET)(lastCCRSentTime >> 16);
    sessionData[sessionDataLength + 2] = (ITS_OCTET)(lastCCRSentTime >> 8);
    sessionData[sessionDataLength + 3] = (ITS_OCTET)(lastCCRSentTime);
    sessionDataLength += 4;

    // Append the session ID at the end
    memcpy(sessionData+sessionDataLength, diaSessionId.c_str(), diaSessionId.length());
    sessionDataLength += diaSessionId.length();

    ITS_EVENT_INIT(&event, ITS_REP_EVENT_FROM_APP, sessionDataLength);
    memcpy(event.data, sessionData, sessionDataLength);

    ret = DiaFrame::GetDiaFrame()->ReCreateSessionEntry(diaSessionId, event);

    if (ret != ITS_SUCCESS)
    {
        DLOG_ERROR("Failed to create Diameter session entry for [%s]", diaSessionId.c_str());
        ITS_EVENT_TERM(&event);
    }
    else
    {
        DLOG_DEBUG("Successfully create Diameter session entry for [%s]", diaSessionId.c_str());
    }
    //DLOG_DEBUG("TransactionManager::CreateDiameterSessionEntry exit");
    return ret;
}

int TransactionManager::DeleteFirstSessionEntryFromReplica(std::string firstSessionId,
        IwfFsm* iwfFsm)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::DeleteFirstSessionEntryFromReplica entry");
    if (IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
    {
        uint32_t indexKey = iwfFsm->GetReplicaIndexKey();

        if (iwfFsm->IsFsmMarkedForDeletion())
        {
            DLOG_DEBUG("FSM entry for SessionId : %s with index Key :%d is already marked for deletion",
                    firstSessionId.c_str(),indexKey);
        }
        else
        {
            iwfFsm->MarkFsmForDeletion(true);
            /*DLOG_DEBUG("Deleting Replication entry for SessionId : %s with index Key :%d",
                    firstSessionId.c_str(),indexKey);*/
#if 0
            iwfFsm->DeleteEntryInReplica(IWF_STATE_REPLICATION, firstSessionId);
            ReplicableData::DeleteTransactionEntryInReplica(IWF_SESSION_ENTRY_LIST,indexKey);
            IwfController::SetReplicationEntryToFreeList(indexKey);
#endif
	    if ( indexKey != 0xffffffff)
	    {
		    if (ReplicableData::DeleteTransactionEntryInReplica(IWF_SESSION_ENTRY_LIST, indexKey) != PB_REPL_UTILS_SUCCESS)
		    {
			    // Unable to delete from CB, save it for future
			    DLOG_DEBUG("Unable to delete [ %s ] from CB, save it for future", firstSessionId.c_str());
			    m_cbFlushGuard.Acquire();
			    m_sessionsToFlushFromCB.insert(pair<int, std::string> (indexKey, firstSessionId));
			    IwfController::Instance().StartBulkFetchTimer();
			    m_cbFlushGuard.Release();
		    }
		    else
		    {
			    iwfFsm->DeleteEntryInReplica(IWF_STATE_REPLICATION, firstSessionId);
			    IwfController::SetReplicationEntryToFreeList(indexKey);
		    }
	    }
        }
    }
    //DLOG_DEBUG("TransactionManager::DeleteFirstSessionEntryFromReplica exit");
    return ITS_SUCCESS;
}

IwfCallSessionContext* TransactionManager::LookupSubscriberContext(const std::string& subscriber)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("TransactionManager::LookupSubscriberContext entry");
    SubscriberTable::iterator it = m_subscriberTable->find(subscriber);
    if (it == m_subscriberTable->end())
    {
        //subscriber context not found
        DLOG_DEBUG("TransactionManager::LookupSubscriberContext exit");
        return NULL;
    }
    this->UpdateAuditList(it->second);
    DLOG_DEBUG("TransactionManager::LookupSubscriberContext exit");
    return it->second;
}

bool TransactionManager::InsertSubscriberContext(const std::string& subscriber, IwfCallSessionContext* ctxt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("TransactionManager::InsertSubscriberContext entry");
    //If entry is present first delete and insert again with updated time
    DeleteSubscriberContext(subscriber);
    std::pair<SubscriberTable::iterator, bool> ret;
    ret = m_subscriberTable->insert(std::make_pair(subscriber, ctxt));
    if (ret.second)
    {
        m_subscriberEntries++;
        ctxt->SetKey(subscriber);
        this->UpdateAuditList(ctxt);

        DLOG_INFO("Inserted Subscriber Context <%s> and Audit list updated."
                " Subscriber Count <%u>", subscriber.c_str(),
                (unsigned)m_subscriberEntries);
    }
    DLOG_DEBUG("TransactionManager::InsertSubscriberContext exit");
    return ret.second;
}

void TransactionManager::UpdateAuditList(IwfCallSessionContext *ctxt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    unsigned expiryTime = time(NULL) + IwfController::Instance().Config().LocalConfig().GetSessionContextCleanUpTimerValue();
    ctxt->UpdateExpiry(expiryTime);
    // remove from the current position and put it at the end
    if (!ctxt->IsNew())
    {
        m_subscrAuditList->erase(ctxt->GetAuditIterator());
    }
    SubscrAuditList::iterator it = m_subscrAuditList->insert(
            m_subscrAuditList->end(), ctxt);
    ctxt->SetAuditIterator(it);
    DLOG_DEBUG("TransactionManager::UpdateAuditList Updated AuditList for User %s.",ctxt->GetKey().c_str());
}

int TransactionManager::DeleteSubscriberContext(const std::string& subscriber)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    SubscriberTable::iterator it = m_subscriberTable->find(subscriber);
    if (it != m_subscriberTable->end())
    {
        IwfCallSessionContext* ctxt = it->second;
        m_subscriberTable->erase(it);
        m_subscrAuditList->erase(ctxt->GetAuditIterator());

        delete ctxt;
        m_subscriberEntries--;
        DLOG_INFO("Deleting Subscriber Context <%s>. Subs count <%u>",
                subscriber.c_str(), (unsigned)m_subscriberEntries);

        return 1;
    }

    return 0;
}

int TransactionManager::DeleteSubscriberContext(IwfCallSessionContext *ctxt)
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    #if 0
    //delete THFSubscriberContextEntry from replica
    if(DREController::Instance().m_dreMeSS.isReplicationEnabled())
    {
        THFReplicationUtils::DeleteTHFSubscriberContextEntryInReplica(ctxt->GetKey());
    }
#endif
    m_subscriberTable->erase(ctxt->GetKey());
    m_subscriberEntries--;
    m_subscrAuditList->erase(ctxt->GetAuditIterator());
    DLOG_INFO("Deleting subscriber context <%s>, Subs count <%u>",
            ctxt->GetKey().c_str(),
            (unsigned)m_subscriberEntries);

    map<std::string, SessionCtxt*>::iterator imsiMapIter = m_imsiMap.find(ctxt->GetKey());

    if (imsiMapIter != m_imsiMap.end()) {
        SessionCtxt *sessionCtxt = imsiMapIter->second;
        if (sessionCtxt != NULL) {
            sessionCtxt->DeleteEntryInReplica(IWF_SESSION_CONTEXT_REPLICA, ctxt->GetKey());
            delete sessionCtxt;
            sessionCtxt = NULL;
        }
        m_imsiMap.erase(imsiMapIter);
        DECREMENT_SSG_STATS_CURRENT_ACTIVE_SUBSCRIBERS;
    }
    delete ctxt;
    return 0;
}

void TransactionManager::AuditSubscriberTable()
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("TransactionManager::AuditSubscriberTable() entry");
    static const unsigned NUM_DELETES_PER_ITERATION = 500;
    unsigned delCount = 0;
    unsigned curTime = time(NULL);
    IwfCallSessionContext *ctxt = NULL;

    for(SubscrAuditList::iterator it = m_subscrAuditList->begin();
            it != m_subscrAuditList->end();)
    {
        ctxt = *it;
        if (ctxt->GetExpiryTime() > curTime)
        {
            DLOG_DEBUG("Subscriber Table, nothing more to delete");
            break;
        }

        it++; // go to next iterator
        this->DeleteSubscriberContext(ctxt);
        delCount++;

        // Don't keep hogging when deletion, keep some for next iteration
        if (delCount >= NUM_DELETES_PER_ITERATION)
        {
            DLOG_INFO("Too many subscriber entries to delete, take it in next iteration");
            break;
        }
    }
    DLOG_INFO("Subscriber Table audit, deleted %d expired entries", delCount);
    // Restart the timer again
    this->RestartSubscrAuditTimer();
    DLOG_DEBUG("TransactionManager::AuditSubscriberTable() exit");
}

void TransactionManager::RestartSubscrAuditTimer()
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("TransactionManager::RestartSubscrAuditTimer() entry");
    STimerContext sTimerCtxt;
    sTimerCtxt.m_eTimerType = ETimerType::IWF_SUBSCRIBER_AUDIT_TIMER;
    sTimerCtxt.m_eKeyType = SUBSC_AUDIT;
    IwfTimer timerObj;
    uint32_t timerId = timerObj.StartTimer(sTimerCtxt.m_eTimerType,sTimerCtxt,IWF_SUBSCR_AUDIT_TIMEOUT);
    DLOG_DEBUG("started Subscriber Audit Timer with timerId %d",timerId);
    m_auditTimerId = timerId;
    DLOG_DEBUG("TransactionManager::RestartSubscrAuditTimer() exit");
}

void TransactionManager::StopSubscrAuditTimer()
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("TransactionManager::StopSubscrAuditTimer() entry");
    IwfTimer timerObj;
    timerObj.StopTimer(m_auditTimerId);
    DLOG_DEBUG("Subscriber Audit Timer with timerId %d is stopped",m_auditTimerId);
    DLOG_DEBUG("TransactionManager::StopSubscrAuditTimer() exit");
}

int TransactionManager::PerformLocalBulkFetch(std::vector<std::string>& outData)
{
    m_bulkFetchGuard.Acquire();
    outData = m_localCBReplica;
    m_bulkFetchGuard.Release();
    return ITS_SUCCESS;
}

void TransactionManager::ProcessBulkFetchTimeout(STimerContext& timerCtxt)
{
    //std::vector<std::string> outData;
    CLOG_DEBUG("TransactionManger::ProcessBulkFetchTimeout entry");

    IwfController::Instance().SetIfBulkFetchTimerRunning(false);
    if (IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
    {
        if (!IwfController::Instance().m_initializationFlagsSet)
        {
            IwfController::Instance().m_initializationFlagsSet = true;
            if (IwfController::Instance().GetNodeStatus())
            {
                CLOG_DEBUG("TransactionManger::ProcessBulkFetchTimeout setting active");
                // Active
                IwfController::Instance().m_becameActive = true;
            }
            else
            {
                CLOG_DEBUG("TransactionManger::ProcessBulkFetchTimeout setting standby");
                // Standby
                IwfController::Instance().m_becameStandby = true;
            }
        }
        // Check if rebalance is in progress, in which case dont do any bulkfetch..
        if( IsRebalanceInProgress())
        {
            IwfController::Instance().StartBulkFetchTimer();
        }
        else
        {
            // On Active we just check if there are any entries to be flushed from CB
            if (IwfController::Instance().GetNodeStatus())
            {
                CLOG_DEBUG("Check if there is any peer status to be update in CB");
                if (!IwfController::Instance().m_becameStandby)
                {
                    Json::StyledWriter writer;
                    std::string strPeerStatusData = writer.write(IwfController::Instance().m_peerStatusRoot);
                    if (ReplicableData::UpdateCommonEntryInReplica (IWF_PEER_STATUS, IWF_PEER_STATUS, strPeerStatusData, -1) != PB_REPL_UTILS_SUCCESS)
                    {
                        DLOG_DEBUG("Unable to update peer status in CB");
                        IwfController::Instance().StartBulkFetchTimer();
                        return;
                    }
                    else if (m_peerStatusUpdateCounter <= IwfController::Instance().Config().LocalConfig().GetMaxPeerStatusUpdates())
                    {
                        DLOG_DEBUG("Try to update peer status in CB [ %d ] times", m_peerStatusUpdateCounter);
                        m_peerStatusUpdateCounter++;
                        IwfController::Instance().StartBulkFetchTimer();
                    }
                }

                CLOG_DEBUG("Check if there are any entries to be flushed from CB");
                m_cbFlushGuard.Acquire();
                if (!m_sessionsToFlushFromCB.empty())
                {
                    CLOG_DEBUG("There are [ %d ] entries to be flushed from CB", m_sessionsToFlushFromCB.size());
                    map<int, std::string>::iterator itrFlusher = m_sessionsToFlushFromCB.begin();
                    while (itrFlusher != m_sessionsToFlushFromCB.end())
                    {
                        if (ReplicableData::DeleteTransactionEntryInReplica(IWF_SESSION_ENTRY_LIST, itrFlusher->first) != PB_REPL_UTILS_SUCCESS)
                        {
                            // Unable to delete from CB, save it for future
                            DLOG_DEBUG("Unable to delete [ %s ] from CB, save it for future", itrFlusher->second.c_str());
                            IwfController::Instance().StartBulkFetchTimer();
                        }
                        else
                        {
                            ReplicableData::DeleteEntryInReplica(IWF_STATE_REPLICATION, itrFlusher->second);
                            IwfController::SetReplicationEntryToFreeList(itrFlusher->first);
                            m_sessionsToFlushFromCB.erase(itrFlusher);
                        }
                        itrFlusher++;
                    }
                }
                m_cbFlushGuard.Release();

            }
            /* On STBY, Fetch the IwfFsm entries from CB here */
            else //if (!IwfController::Instance().GetNodeStatus())
            {
                int retVal = PB_REPL_UTILS_SUCCESS;
                uint32_t maxSessions = MAX_BULK_FETCH_SIZE;

                // Fetch the peer status from DB
                retVal = ReplicableData::FetchCommonEntryFromReplica(IWF_PEER_STATUS,
                        IWF_PEER_STATUS, IwfController::Instance().IwfController::Instance().m_peerStatusInDb);

                if (retVal == PB_REPL_UTILS_SUCCESS || retVal == REPL_KEY_ENOENT)
                {

                    if (IwfController::Instance().Config().LocalConfig().isCongestionManagementEnabled())
                    {
                        maxSessions =  IwfController::Instance().Config().LocalConfig().GetMaxNumberOfSessionsToHold();
                    }

                    CLOG_DEBUG("Bulk fetch starting...");
                    m_bulkFetchGuard.Acquire();
                    retVal = ReplicableData::FetchBulkEntriesInReplica(IWF_SESSION_ENTRY_LIST,
                            LIST_START, maxSessions, m_localCBReplica);

                    if (retVal == PB_REPL_UTILS_SUCCESS)
                    {
                        // No need to parse the recevied data, just store it in the vector
                        // for later use, when it actually becomes active
#if 0
                        for(uint32_t currFsm = 0; currFsm <  m_localCBReplica.size() ; currFsm++)
                        {
                            pbIwfFsmInfo iwfFsm;
                            std::string tmpStr =  m_localCBReplica[currFsm];
                            iwfFsm.ParseFromArray(tmpStr.c_str(), tmpStr.length());

                            CLOG_DEBUG("Extraced Fsm Data %s",iwfFsm.DebugString().c_str());
                            map<std::string, IwfFsm*>::iterator diaSessIdTxnEntryMapIter = m_diaSessionIdTxnEntryMap.find(iwfFsm.diasessionid());
                            if (diaSessIdTxnEntryMapIter == m_diaSessionIdTxnEntryMap.end())
                            {
                                TransactionManager::Instance()->CreateTcapTransactionEntryFromReplica(iwfFsm);
                                TransactionManager::Instance()->CreateDiameterSessionEntry(iwfFsm);
                                TransactionManager::Instance()->CreateIwfFsmFromReplica(iwfFsm);
                            }
                            else
                            {
                                CLOG_DEBUG("Session entry : %s already recreated hence not creating IwfFsm",iwfFsm.diasessionid().c_str());
                            }
                        }

                        CLOG_DEBUG("Successsfully FetchBulkEntriesInReplica for %d entries ", m_localCBReplica.size());
#endif
                        // Keep restarting the timer till we become active
                        if (!IwfController::Instance().GetNodeStatus())
                        {
                            IwfController::Instance().StartBulkFetchTimer();
                        }
                        CLOG_DEBUG("Bulk fetch returned [ %d ] entries!", m_localCBReplica.size());
                    }
                    else if (retVal == REPL_KEY_ENOENT)
                    {
                        CLOG_DEBUG("No entries to BulkFetch, Starting BulkFetch Timer again...!");
                        // Keep restarting the timer till we become active
                        if (!IwfController::Instance().GetNodeStatus())
                        {
                            IwfController::Instance().StartBulkFetchTimer();
                        }
                    }
                    else
                    {
                        uint32_t bulkfetchRetry = IwfController::Instance().GetBulkFetchRetryCount();
                        CLOG_ERROR("Failed to BulkFetch the entries for %d times, Starting BulkFetch Timer again...!",bulkfetchRetry);
                        IwfController::Instance().SetBulkFetchRetryCount(bulkfetchRetry+1);
                        // Keep restarting the timer till we become active
                        if (!IwfController::Instance().GetNodeStatus())
                        {
                            IwfController::Instance().StartBulkFetchTimer();
                        }
                    }
                    m_bulkFetchGuard.Release();
                }
                else
                {
                    IwfController::Instance().StartBulkFetchTimer();
                }
            }
        }
    }
    else
    {
        CLOG_DEBUG("Replication is disabled not invoking BulkFetch()");
    }
    CLOG_DEBUG("TransactionManger::ProcessBulkFetchTimeout exit");
}

void TransactionManager::HandleDumpIwfInfoRequest()
{
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    DLOG_DEBUG("TransactionManager::HandleDumpIwfInfoRequest() Entry");

    DLOG_CRITICAL(" Active IwfFsm Count = %lld", (uint64_t)CurrentFSMCount);
    DLOG_CRITICAL(" DialogueId-IwfFsm map Size = %lld", m_tcapDialogueIdTxnEntryMap.size());
    DLOG_CRITICAL(" SessionId-IwfFsm map Size = %lld",m_diaSessionIdTxnEntryMap.size());
    DLOG_CRITICAL(" Active Subscriber Count = %lld", m_imsiMap.size());
    DLOG_CRITICAL(" Last BulkFetched IwfFsm Count = %lld", m_bulkFetchIwfFsmCount); 

    //Get Queued Message Count
    uint64_t queue_count = 0;
    std::map<std::string, std::map<std::string, std::list<QueuedDiaCommand>>>::iterator it;
    for(it = m_tmpPendingDiaMsgQueue.begin(); it != m_tmpPendingDiaMsgQueue.end(); ++it)
    {
        std::map<std::string, std::list<QueuedDiaCommand>>::iterator itrTmpMap = (*it).second.begin();
        while(itrTmpMap != (*it).second.end())
        {
             queue_count = queue_count + (*itrTmpMap).second.size();
             itrTmpMap++;
        }
    }
    DLOG_CRITICAL(" Queued Diameter Message Count = %lld",queue_count);
    DLOG_CRITICAL(" Active Diameter Session Count = %lld",m_diaMgtObj->GetSessionTableSize());

    if(IwfController::Instance().m_iwfMeSS.isReplicationEnabled())
    {
        if(IwfController::GetNodeStatus())
        {
            DLOG_CRITICAL(" IWF node Status = HA-Active ");
        }
        else
        {
            DLOG_CRITICAL(" IWF node Status = HA-StandBy ");
        }
    }
    else
    {
        DLOG_CRITICAL(" IWF node Status = StandAlone ");
    }

    DLOG_CRITICAL(" Pending Sessions to delete in CouchBase = %lld",m_sessionsToFlushFromCB.size());

    //Diameter Peer State
    DIA_PEER_STATES *allPeers = NULL;
    unsigned int nPeers = 0;
    allPeers = m_diaMgtObj->GetPeersState(nPeers);
    DLOG_CRITICAL(" Total Diameter Peers: %d", nPeers);
    if ((allPeers != NULL) && (nPeers > 0))
    {
        for (unsigned int idx = 0; idx < nPeers; idx++)
        {
            if((int) allPeers[idx].pState == PEER_CLOSED)
            {
                DLOG_CRITICAL(" Peer State for Host %s - Realm %s : PEER_CLOSED",(const char*) allPeers[idx].peerName, 
                        (const char*) allPeers[idx].realmName);
            }
            else if((int) allPeers[idx].pState == PEER_WAIT_CONN_ACK)
            {
                DLOG_CRITICAL(" Peer State for Host %s - Realm %s : PEER_WAIT_CONN_ACK",(const char*) allPeers[idx].peerName,
                        (const char*) allPeers[idx].realmName);
            }
            else if((int) allPeers[idx].pState == PEER_WAIT_I_CEA)
            {
                DLOG_CRITICAL(" Peer State for Host %s - Realm %s : PEER_WAIT_I_CEA",(const char*) allPeers[idx].peerName, 
                        (const char*) allPeers[idx].realmName);
            }
            else if((int) allPeers[idx].pState == PEER_WAIT_CONN_ACK_ELECT)
            {
                DLOG_CRITICAL(" Peer State for Host %s - Realm %s : PEER_WAIT_CONN_ACK_ELECT",(const char*) allPeers[idx].peerName,
                        (const char*) allPeers[idx].realmName);
            }
            else if((int) allPeers[idx].pState == PEER_WAIT_RETURNS)
            {
                DLOG_CRITICAL(" Peer State for Host %s - Realm %s : PEER_WAIT_RETURNS",(const char*) allPeers[idx].peerName,
                        (const char*) allPeers[idx].realmName);
            }
            else if((int) allPeers[idx].pState == PEER_I_OPEN)
            {
                DLOG_CRITICAL(" Peer State for Host %s - Realm %s : PEER_I_OPEN",(const char*) allPeers[idx].peerName,
                        (const char*) allPeers[idx].realmName);
            }
            else if((int) allPeers[idx].pState == PEER_R_OPEN)
            {
                DLOG_CRITICAL(" Peer State for Host %s - Realm %s : PEER_R_OPEN",(const char*) allPeers[idx].peerName,
                        (const char*) allPeers[idx].realmName);
            }
            else if((int) allPeers[idx].pState == PEER_CLOSING)
            {
                DLOG_CRITICAL(" Peer State for Host %s - Realm %s : PEER_CLOSING",(const char*) allPeers[idx].peerName,
                        (const char*) allPeers[idx].realmName);
            }
        }
        delete [] allPeers;
        allPeers = NULL;
    }

    DLOG_DEBUG("TransactionManager::HandleDumpIwfInfoRequest() Exit");
}

void TransactionManager::HandlePurgeSubscriberRequest(std::string& strIMSIToClear)
{
    DLOG_DEBUG("TransactionManager:: HandlePurgeSubscriberRequest() Entry");

    // Check if the request is for a single subscriber or all subs
    if (strIMSIToClear.compare("all")) // single IMSI
    {
        map<std::string, SessionCtxt*>::iterator imsiMapIter = m_imsiMap.find(strIMSIToClear);

        if (imsiMapIter != m_imsiMap.end())
        {
            DLOG_DEBUG("TransactionManager::HandlePurgeSubscriberRequest() IMSI [%s] Found"
                       ,strIMSIToClear.c_str());
            SessionCtxt *sessionCtxt = imsiMapIter->second;

            if (sessionCtxt != NULL) {
                delete sessionCtxt;
                sessionCtxt = NULL;
            }

            m_imsiMap.erase(imsiMapIter);
            DECREMENT_SSG_STATS_CURRENT_ACTIVE_SUBSCRIBERS;
            DLOG_DEBUG("TransactionManager::HandlePurgeSubscriberRequest() IMSI [%s] deleted successfully"
                    ,strIMSIToClear.c_str());
        }
        else
        {
            DLOG_DEBUG("TransactionManager::HandlePurgeSubscriberRequest() IMSI [%s] NOT found",
                       strIMSIToClear.c_str());
        }
    }
    else // all IMSIs need to be purged
    {
        map<std::string, SessionCtxt*>::iterator imsiMapIter;
        for (imsiMapIter = m_imsiMap.begin(); imsiMapIter != m_imsiMap.end();) {

            SessionCtxt *sessionCtxt = imsiMapIter->second;

            if (sessionCtxt != NULL) {
                delete sessionCtxt;
                sessionCtxt = NULL;
            }

            m_imsiMap.erase(imsiMapIter++);
            DECREMENT_SSG_STATS_CURRENT_ACTIVE_SUBSCRIBERS;
        }

        if (imsiMapIter == m_imsiMap.end())
        {
            DLOG_DEBUG("TransactionManager::HandlePurgeSubscriberRequest(): All IMSIs purged");
        }
        else
        {
            DLOG_DEBUG("TransactionManager::HandlePurgeSubscriberRequest(): All IMSIs could not"
                       " be purged");
        }
    }

    DLOG_DEBUG("TransactionManager:: HandlePurgeSubscriberRequest() Exit");
}

bool TransactionManager::CheckPeerStateForRouting(std::string PeerName, std::string RealmName)
{
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::CheckPeerStateForRouting() Entry");

    DIA_PEER_STATUS peerStatus;
    PEER_INFO peerInfo;
    peerInfo.peerName = PeerName.c_str();
    peerInfo.realmName = RealmName.c_str();
    int retVal = m_diaMgtObj->GetDiaPeerStatus((void *) &peerStatus, &peerInfo);
    if ((retVal == ITS_SUCCESS) && (peerStatus.pState == PEER_R_OPEN || peerStatus.pState == PEER_I_OPEN))
    {
        //DLOG_DEBUG("Peer %s in Realm %s is in open state.",PeerName.c_str(), RealmName.c_str());
        //DLOG_DEBUG("TransactionManager::CheckPeerStateForRouting() Exit");
        return true;
    }
    else
    {
        DLOG_ERROR("Peer %s in Realm %s is not in open state.",PeerName.c_str(), RealmName.c_str());
    }
    //DLOG_DEBUG("TransactionManager::CheckPeerStateForRouting() Exit");
    return false;
}

bool TransactionManager::IsDestinationAvailable(IwfFsm *ctxt)
{
    bool isRouteAvailable = false;
    SS7_Destination* ss7Dest = NULL;
    bool isNational = false;
    ITS_OCTET ssn = 0;
    ITS_UINT dpc = 0, sio = IWF_INTERNATIONAL_SIO;
    TCAP_Begin *begin = ctxt->GetTcapBeginDlg();
    begin->GetDestAddr(isNational, dpc, ssn);
    begin->GetDPC(dpc);
    SS7_Family family = IwfController::Instance().Config().LocalConfig().Family();
    if(isNational)
    {
        sio = IWF_NATIONAL_SIO;
    }
    MTP3_OSS_GetRemoteRoute_CCITT(dpc, sio, family, &ss7Dest);
    if(ss7Dest != NULL)
    {
        if(ss7Dest->status == DESTINATION_UNAVAILABLE)
        {
            DLOG_ERROR("Destination with PointCode : %d is not avaliable", dpc);
            ctxt->SetErrorCode(ITS_DIA_UNABLE_TO_DELIVER);
            isRouteAvailable = false;
        }
        else
        {
            isRouteAvailable = true;
        }
    }
    return isRouteAvailable;
}

bool TransactionManager::IsDestinationAvailable(IwfFsm *ctxt, ITS_OCTET ssn, ITS_UINT dpc, bool isNational)
{
    bool isRouteAvailable = false;
    SS7_Destination* ss7Dest = NULL;
    ITS_UINT sio = IWF_INTERNATIONAL_SIO;
    SS7_Family family = IwfController::Instance().Config().LocalConfig().Family();
    if(isNational)
    {
        sio = IWF_NATIONAL_SIO;
    }
    MTP3_OSS_GetRemoteRoute_CCITT(dpc, sio, family, &ss7Dest);
    if(ss7Dest != NULL)
    {
        if(ss7Dest->status == DESTINATION_UNAVAILABLE)
        {
            DLOG_ERROR("Destination with PointCode : %d is not avaliable", dpc);
            isRouteAvailable = false;
        }
        else
        {
            isRouteAvailable = true;
        }
    }
    return isRouteAvailable;
}

void TransactionManager::AddPeerToPeerStatusDb(std::string peer, std::string realm)
{
    // Get the peer information one by one and update m_peerStatusRoot
    DLOG_DEBUG("TransactionManager::AddPeerToPeerStatusDb() adding [ Peer : %s ], [ Realm : %s ]", peer.c_str(), realm.c_str());
    if (IwfController::Instance().m_peerStatusRoot["Peers"].empty())
    {
        IwfController::Instance().m_peerStatusRoot["Peers"][0]["PeerName"] = peer;
        IwfController::Instance().m_peerStatusRoot["Peers"][0]["RealmName"] = realm;
        IwfController::Instance().m_peerStatusRoot["Peers"][0]["Status"] = 0;
    }
    else
    {
        Json::Value peerInfo;
        peerInfo["PeerName"] = peer;
        peerInfo["RealmName"] = realm;
        peerInfo["Status"] = 0;
        //m_peerStatusRoot["Peers"].append(peerInfo);
        IwfController::Instance().m_peerStatusRoot["Peers"][IwfController::Instance().m_peerStatusRoot["Peers"].size()] = peerInfo;
    }
}

void TransactionManager::UpdatePeerStatusInPeerStatusDb(std::string peer, std::string realm, bool status)
{
    // Get the peer information one by one and update m_peerStatusRoot
    Json::StyledWriter jsonWriter;
    std::string peerStatusFromDb = jsonWriter.write(IwfController::Instance().m_peerStatusRoot);
    DLOG_DEBUG("TransactionManager::UpdatePeerStatusInPeerStatusDb() status before update :: %s ", peerStatusFromDb.c_str());
    DLOG_DEBUG("TransactionManager::UpdatePeerStatusInPeerStatusDb() updating status of [ Peer : %s ], [ Realm : %s ] to [ Status : %d ]", peer.c_str(), realm.c_str(), status);
    for (int idx = 0; idx < IwfController::Instance().m_peerStatusRoot["Peers"].size(); idx++)
    {
        Json::Value peerInfo =  IwfController::Instance().m_peerStatusRoot["Peers"][idx];
        if (strcasecmp(peer.c_str(),peerInfo["PeerName"].asString().c_str()) == 0 &&
                strcasecmp(realm.c_str(),peerInfo["RealmName"].asString().c_str()) == 0)
        {
            peerInfo["Status"] = (int)status;
            IwfController::Instance().m_peerStatusRoot["Peers"][idx] = peerInfo;
        }
    }
    peerStatusFromDb = jsonWriter.write(IwfController::Instance().m_peerStatusRoot);
    DLOG_DEBUG("TransactionManager::UpdatePeerStatusInPeerStatusDb() status after update :: %s ", peerStatusFromDb.c_str());
}

bool TransactionManager::ComparePeerStatus(const std::string& peer, const std::string& realm, bool status)
{
    Json::Reader reader;
    Json::Value root;
    reader.parse(IwfController::Instance().m_peerStatusInDb, root);
    bool statusInLocalDb = false;
    int idx = 0;
    DLOG_DEBUG("TransactionManager::ComparePeerStatus() Entry");
    for (; idx < IwfController::Instance().m_peerStatusRoot["Peers"].size(); idx++)
    {
        Json::Value peerInfo =  IwfController::Instance().m_peerStatusRoot["Peers"][idx];
        DLOG_DEBUG("TransactionManager::ComparePeerStatus() Checking the local peer : %s and realm : %s status [ %d ]", peerInfo["PeerName"].asString().c_str(), peerInfo["RealmName"].asString().c_str(), peerInfo["Status"].asInt());
        if (strcasecmp(peerInfo["PeerName"].asString().c_str(),peer.c_str()) == 0 &&
                strcasecmp(peerInfo["RealmName"].asString().c_str(),realm.c_str()) == 0)
        {
            statusInLocalDb = peerInfo["Status"].asInt();
            break;
        }
    }

    if (idx == IwfController::Instance().m_peerStatusRoot["Peers"].size())
    {
        DLOG_DEBUG("TransactionManager::ComparePeerStatus() Adding Peer : %s [ Realm : %s ] to status DB as its not found locally", peer.c_str(), realm.c_str());
        AddPeerToPeerStatusDb(peer, realm);
    }

    for (idx = 0; idx < root["Peers"].size(); idx++)
    {
        Json::Value peerInfo =  root["Peers"][idx];
        DLOG_DEBUG("TransactionManager::ComparePeerStatus() Checking the peer in CB : %s and realm : %s status [ %d ]", peerInfo["PeerName"].asString().c_str(), peerInfo["RealmName"].asString().c_str(), peerInfo["Status"].asInt());
        if (strcasecmp(peerInfo["PeerName"].asString().c_str(),peer.c_str()) == 0 &&
                strcasecmp(peerInfo["RealmName"].asString().c_str(),realm.c_str()) == 0)
        {

            DLOG_DEBUG("TransactionManager::ComparePeerStatus() Peer : %s [ Realm : %s ] status was [ %d ] now its [ %d ]", peer.c_str(), realm.c_str(), peerInfo["Status"].asInt(), statusInLocalDb);
            if (peerInfo["Status"].asInt())
            {
                if (peerInfo["Status"].asInt() == statusInLocalDb)
                {
                    return true; 
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return true;
            }
        }
    }

    if (idx == root["Peers"].size())
    {
        DLOG_DEBUG("TransactionManager::ComparePeerStatus() Peer : %s [ Realm : %s ] was not found in CB ", peer.c_str(), realm.c_str());
        return true;
    }
    DLOG_DEBUG("TransactionManager::ComparePeerStatus() Exit");
    return true;
}

bool TransactionManager::ComparePeerStatus()
{
    Json::StyledWriter jsonWriter;
    std::string peerStatusFromDb = jsonWriter.write(IwfController::Instance().m_peerStatusRoot);
    if (IwfController::Instance().m_peerStatusInDb.compare(peerStatusFromDb))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool TransactionManager::InsertDiaMsgIntoPendingQueue(std::string& peerName, std::string& sessionId, QueuedDiaCommand& msgToQueue)
{
    // check if the peer is already there in the queue 
    ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::InsertDiaMsgIntoPendingQueue() Entry");
    std::map<std::string, std::map<std::string, std::list<QueuedDiaCommand>>>::iterator itrPendQueue;
    itrPendQueue = m_tmpPendingDiaMsgQueue.find(peerName);
    if (itrPendQueue == m_tmpPendingDiaMsgQueue.end())
    {
        std::map<std::string, std::list<QueuedDiaCommand>> tmpMap;
        std::list<QueuedDiaCommand> tmpList;
        tmpList.push_back(msgToQueue);
        //tmpMap.insert(make_pair<std::string, std::list<QueuedDiaCommand>>(sessionId, tmpList));
        tmpMap.insert(make_pair(sessionId, tmpList));
        //m_tmpPendingDiaMsgQueue.insert(make_pair<std::string, std::map<std::string, std::list<QueuedDiaCommand>>>(peerName, tmpMap));
        m_tmpPendingDiaMsgQueue.insert(make_pair(peerName, tmpMap));
        DLOG_DEBUG("TransactionManager::InsertDiaMsgIntoPendingQueue() Queuing message for [ Peer : %s ], [ Session : %s ]", peerName.c_str(), sessionId.c_str());
    }
    else
    {
        std::map<std::string, std::list<QueuedDiaCommand>>::iterator itrTmpMap = (*itrPendQueue).second.find(sessionId);

        if (itrTmpMap == (*itrPendQueue).second.end())
        {
            std::list<QueuedDiaCommand> tmpList;
            tmpList.push_back(msgToQueue);
            (*itrPendQueue).second.insert(make_pair(sessionId, tmpList));
            //(*itrPendQueue).second.insert(make_pair<std::string, std::list<QueuedDiaCommand>>(sessionId, tmpList));
            DLOG_DEBUG("TransactionManager::InsertDiaMsgIntoPendingQueue() Queuing message for [ Peer : %s ], [ Session : %s ]", (*itrPendQueue).first.c_str(), sessionId.c_str());
        }
        else
        {
            (*itrTmpMap).second.push_back(msgToQueue);
            DLOG_DEBUG("TransactionManager::InsertDiaMsgIntoPendingQueue() Queuing message for [ Peer : %s ], [ Session : %s ]", (*itrPendQueue).first.c_str(), (*itrTmpMap).first.c_str());
        }
    }
    //DLOG_DEBUG("TransactionManager::InsertDiaMsgIntoPendingQueue() Exit");
    return ITS_SUCCESS;
}

bool TransactionManager::SendDiaMsgToStack(std::string& sessionId, DIA_BASE_CMD* cmd, unsigned int sessionIdx, ITS_USHORT peerInst, ITS_UINT diaFlags)
{
    // Check if there is a need for queuing
    //ScopedLogger scopedLogger(IwfController::Instance().GetLogger());
    //DLOG_DEBUG("TransactionManager::SendDiaMsgToStack() Entry");

    if (!IwfController::Instance().m_iwfMeSS.isReplicationEnabled() ||
            (!IwfController::Instance().m_becameStandby || !cmd->isRequest()))
    {
        return DiaFrame::GetDiaFrame()->Send(cmd, sessionIdx, peerInst, diaFlags);
    }
    else
    {
        std::string& peerName = cmd->getDestinationHost()->value();
        std::string& realmName = cmd->getDestinationRealm()->value();
        // Check if the messages needs to be queued or not
        if (!ComparePeerStatus(peerName, realmName, true))
        {
            QueuedDiaCommand msgToQueue(cmd, sessionIdx, peerInst, diaFlags);
            InsertDiaMsgIntoPendingQueue(peerName, sessionId, msgToQueue);
            //DLOG_DEBUG("TransactionManager::SendDiaMsgToStack() Exit");
            return ITS_SUCCESS;
        }
        else
        {
            //DLOG_DEBUG("TransactionManager::SendDiaMsgToStack() Exit");
            return DiaFrame::GetDiaFrame()->Send(cmd, sessionIdx, peerInst, diaFlags);
        }
    }
}

void TransactionManager::ProcessPendingQueueExpiry(STimerContext& timerCtxt)
{
    //std::vector<std::string> outData;
    CLOG_DEBUG("TransactionManger::ProcessPendingQueueExpiry setting the  became standby flag to false");

    if (IwfController::Instance().GetNodeStatus())
    {
        CLOG_DEBUG("TransactionManger:: setting became standby to false");
        IwfController::Instance().m_becameStandby = false;
    }
    else
    {
        CLOG_DEBUG("TransactionManger:: setting became standby to true");
        IwfController::Instance().m_becameStandby = true;
    }
    //NOTE: Send all pending Queue messages
    ProcessPendingDiaMsgs("","");
}

void TransactionManager::ProcessPendingDiaMsgs(const std::string& peer, const std::string& sessionId)
{
    // check if the peer is already there in the queue 
    CLOG_DEBUG("TransactionManger::ProcessPendingDiaMsgs Entry");

    std::map<std::string, std::map<std::string, std::list<QueuedDiaCommand>>>::iterator itrPendQueue;
    if(!peer.empty())
    {
        itrPendQueue = m_tmpPendingDiaMsgQueue.find(peer);
        if (itrPendQueue == m_tmpPendingDiaMsgQueue.end())
        {
            CLOG_DEBUG("TransactionManger::ProcessPendingDiaMsgs nothing to be dequeued for [ Peer : %s ]", peer.c_str());
            return;
        }
        else
        {
            if (sessionId.empty())
            {
                std::map<std::string, std::list<QueuedDiaCommand>>::iterator itrTmpMap = (*itrPendQueue).second.begin();

                while (itrTmpMap != (*itrPendQueue).second.end())
                {
#ifndef SEND_ONLY_LAST_CCR
                    std::list<QueuedDiaCommand>::iterator itrTmpLst = (*itrTmpMap).second.begin();
                    if (itrTmpLst != (*itrTmpMap).second.end())
                    {
                        DiaFrame::GetDiaFrame()->Send((*itrTmpLst).cmd, (*itrTmpLst).sessionIdx, (*itrTmpLst).peerInstance, (*itrTmpLst).flags);
                        (*itrTmpMap).second.erase(itrTmpLst++);
                    }

                    if (itrTmpLst == (*itrTmpMap).second.end())
                    {
                        (*itrPendQueue).second.erase(itrTmpMap++);
                    }
                    else
                    {
                        itrTmpMap++;
                    }
#else
                    CLOG_DEBUG("TransactionManger::ProcessPendingDiaMsgs  sent msg related to [ session : %s ]", (*itrTmpMap).first.c_str());
                    QueuedDiaCommand& msg = (*itrTmpMap).second.back();
                    DiaFrame::GetDiaFrame()->Send(msg.cmd, msg.sessionIdx, msg.peerInstance, msg.flags);
                    (*itrTmpMap).second.pop_back();
                    (*itrTmpMap).second.clear(); // have to delete the stored msgs as well
                    (*itrPendQueue).second.erase(itrTmpMap++);
#endif
                }

                if ((*itrPendQueue).second.empty())
                {
                    m_tmpPendingDiaMsgQueue.erase(itrPendQueue);
                }
            }
            else
            {
                CLOG_DEBUG("TransactionManger::ProcessPendingDiaMsgs  sending pending msg related to [ session : %s ]", sessionId.c_str());
                std::map<std::string, std::list<QueuedDiaCommand>>::iterator itrTmpMap = (*itrPendQueue).second.find(sessionId);

                if (itrTmpMap != (*itrPendQueue).second.end())
                {
                    std::list<QueuedDiaCommand>::iterator itrTmpLst = (*itrTmpMap).second.begin();
                    if (itrTmpLst != (*itrTmpMap).second.end())
                    {
                        DiaFrame::GetDiaFrame()->Send((*itrTmpLst).cmd, (*itrTmpLst).sessionIdx, (*itrTmpLst).peerInstance, (*itrTmpLst).flags);
                        (*itrTmpMap).second.erase(itrTmpLst++);
                    }

                    if (itrTmpLst == (*itrTmpMap).second.end())
                    {
                        (*itrPendQueue).second.erase(itrTmpMap);
                    }
                }
            }
        }
    }
    else
    {
        DLOG_DEBUG("PendingQueueTimer Expired, send all pending diameter msgs");
        for(itrPendQueue = m_tmpPendingDiaMsgQueue.begin(); itrPendQueue != m_tmpPendingDiaMsgQueue.end(); ++itrPendQueue)
        {
            std::map<std::string, std::list<QueuedDiaCommand>>::iterator itrTmpMap = (*itrPendQueue).second.begin();

            while (itrTmpMap != (*itrPendQueue).second.end())
            {
#ifndef SEND_ONLY_LAST_CCR
                std::list<QueuedDiaCommand>::iterator itrTmpLst = (*itrTmpMap).second.begin();
                if (itrTmpLst != (*itrTmpMap).second.end())
                {
                    DiaFrame::GetDiaFrame()->Send((*itrTmpLst).cmd, (*itrTmpLst).sessionIdx, (*itrTmpLst).peerInstance, (*itrTmpLst).flags);
                    (*itrTmpMap).second.erase(itrTmpLst++);
                }

                if (itrTmpLst == (*itrTmpMap).second.end())
                {
                    (*itrPendQueue).second.erase(itrTmpMap++);
                }
                else
                {
                    itrTmpMap++;
                }
#else
                CLOG_DEBUG("TransactionManger::ProcessPendingDiaMsgs  sent msg related to [ session : %s ]", (*itrTmpMap).first.c_str());
                QueuedDiaCommand& msg = (*itrTmpMap).second.back();
                DiaFrame::GetDiaFrame()->Send(msg.cmd, msg.sessionIdx, msg.peerInstance, msg.flags);
                (*itrTmpMap).second.pop_back();
                (*itrTmpMap).second.clear(); // have to delete the stored msgs as well
                (*itrPendQueue).second.erase(itrTmpMap++);
#endif
            }

            if ((*itrPendQueue).second.empty())
            {
                m_tmpPendingDiaMsgQueue.erase(itrPendQueue);
            }
        }
    }
}
