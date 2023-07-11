/* 
 * File:   IwfFsm.h
 * Author: adey
 *
 * Created on December 18, 2012, 4:15 PM
 */

#ifndef FSM_H
#define FSM_H

#include "iwf_sm_defines.h"
#include "iwf_prot_defines.h"
//#include "iwf_prot_utils.h"
#include "iwf_timer_defines.h"
#include "dia_cmn.h"
#include "iwf.pb.h"
#include "pbReplicationUtils.h"

class IwfTranslator;

class TransactionManager;

class State;

class StoredUserData {
    public:

        StoredUserData()
        {}
        virtual ~StoredUserData()
        {}
};
struct RoutingLabel {
    ITS_UINT oPc;
    bool isNational;
    ITS_OCTET oSsn;
    bool useSccpCdPAFromInMsg;
};
class TcapCptList {
    public:
        TcapCptList(){}
        ~TcapCptList(){}
        void BuildTcapCptList(TCAP_Component tcapCpt);

        std::list<TCAP_Component> GetTcapCptList();

        void ClearTcapCptList();
    private:
        std::list<TCAP_Component> m_listCpt;
};

class IwfFsm : public ReplicableData
{
    public:

        IwfFsm(TransactionManager *txnMgr);

        IwfFsm(TransactionManager *txnMgr, States initialState);

        ~IwfFsm();

        States GetCurrentStateId();

        void SetCurrentState(States currState);

        void SetPreviousState(States prevState);

        const char* GetCurrentStateName();

        States GetPreviousStateId();

        const char* GetPreviousStateName();

        void MakeStateTransition(Events event, DIA_BASE_CMD *diaCmd, TCAP_Dialogue *tcapDlg, TCAP_Component *tcapCpt);

        void StartTimer();

        void CancelTimer();

        void SetTimerStarted(bool isTimerStarted);

        bool GetIsTimerStarted();

        struct timeval* GetConfigTimeVal();

        struct event* GetEvent();

        struct timeval* GetTimerInvokeTimeVal();

        TransactionManager* GetTransactionManager();

        void SetUpstrmReqProtocol(pbProtocol upstrmReqProtocol);

        pbProtocol GetUpstrmReqProtocol();

        void SetDnstrmReqProtocol(pbProtocol dnstrmReqProtocol);

        pbProtocol GetDnstrmReqProtocol();

        void SetDiaSessionId(std::string diaSessionId);

        std::string& GetDiaSessionId();

        void SetDiaSessionIdx(unsigned int diaSessionIndex);

        unsigned int GetDiaSessionIdx();

        void SetTcapDlgId(ITS_CTXT tcapDlgId);

        ITS_CTXT GetTcapDlgId();

        void SetCurrRcvdDiaMsg(DIA_BASE_CMD *diaCmd);

        DIA_BASE_CMD* GetCurrRcvdDiaMsg();

        void SetCurrRcvdTcapDlg(TCAP_Dialogue *tcapDlg);

        TCAP_Dialogue* GetCurrRcvdTcapDlg();

        void SetTcapBeginDlg(TCAP_Begin *tcapbegin);

        TCAP_Begin* GetTcapBeginDlg();

        void SetCurrRcvdTcapCpt(TCAP_Component *tcapCpt);

        TCAP_Component* GetCurrRcvdTcapCpt();

        bool IsCurrRcvdMsgDia();

        bool IsCurrRcvdMsgTcap();

        void SetCurrSendErr(bool isCurrSendErr);

        void SetErrorCode(int errorCode);

        int GetErrorCode();

        void SetImsi(std::string username);

        std::string& GetImsi();

        // Do we need to set default value to false?
        void SetIntmdteIsdSent(bool IsdSent);

        bool GetIntmdteIsdSent();

        void SetSgsnAddress(SCCPParameters sccpParam){m_sccpParams = sccpParam;};

        SCCPParameters GetSgsnAddress(){return m_sccpParams;};

        void SetInvokeId(ITS_OCTET ivkId);

        ITS_OCTET GetInvokeId();

        bool IsCurrSendErr();

        bool IsDiaRespSent()
        {
            return m_pbIwfFsmRepData.isdiarespsent();
        }

        void SetDiaRespSent(bool bVal)
        {
            m_pbIwfFsmRepData.set_isdiarespsent(bVal);
        }

        void SetRouteByGT(bool val)
        {
            m_pbIwfFsmRepData.set_isroutebygt(val);
        }

        bool IsRouteByGT()
        {
            return m_pbIwfFsmRepData.isroutebygt();
        }

        void SetInvkId(ITS_OCTET ivkId)
        {
            m_pbIwfFsmRepData.set_invokeid(ivkId);
        }

        ITS_OCTET GetInvkId()
        {
            return m_pbIwfFsmRepData.invokeid();
        }

        void SetTranslator(IwfTranslator* trnsltr);

        IwfTranslator* GetTranslator();

        void SetRoutingLabel(pbRoutingLabel routinglabel);

        const pbRoutingLabel& GetRoutingLabel();

        /**
         * Used to store interim user data for the caller's consumption later.
         * The stored user data is opaque to the IWF state machine.
         * 
         * @param storedUserData
         */
        void SetStoredUserData(StoredUserData *storedUserData);

        /**
         * Used to retrieve the stored user data.
         * The caller must know how to retrieve the data by down casting.
         * 
         * @return  Handle to the stored user data as a void pointer. 
         */
        StoredUserData* GetStoredUserData();

        /**
         * Used to store the self SCCP address.
         * This is used to support Multiple (Virtual) GT.
         * 
         * @param selfSccpAddr
         */
        void SetSelfSccpAddr(SCCP_CalledPartyAddr& selfSccpAddr);

        void SetSelfSccpAddr(pbSccpAddress pbSelfSccpAddr);

        /**
         * Used to retrieve the self SCCP address.
         * This is used to support Multiple (Virtual) GT.
         * 
         * @return  Self SCCP address 
         */
        SCCP_CalledPartyAddr GetSelfSccpAddr();  

        bool GetSelfSccpAddr(SCCP_CalledPartyAddr& sccpCdPA);  

        int GetTimerInfo(ETimerType& timerType, STimerInfo& o_sTimerInfo);

        void SetTimerInfo(STimerInfo& timerInfo);

        void RemoveTimerInfo(unsigned int& uiTimerId);

        void ResetTimerInfo();

        void SetIsTCAPEnd(bool isTCAPEnd);

        bool IsTCAPEnd();

        void SetStartNoEventTimer(bool noEventTimer);

        bool IsStartNoEventTimerSet();

        void SetTcapCptList(TcapCptList &tcapcptlist);

        TcapCptList* GetTcapCptList();

        void SetFinalUpstrmReqSent(bool isFinalReponseSent);

        bool IsFinalUpstrmReqSent();

        void StopAllTimers();

        void GotoPrevState();

        void StoreOutgoingInvokeId(ITS_OCTET invokeId);

        vector<ITS_OCTET>& GetStoredOutGoingInvokeIdList();

        void ResetInvokeIdVector();

        bool IsMarkedForRollback()
        {
            return m_pbIwfFsmRepData.markforrollback();
        }
        void SetMarkForRollback(bool rollback = true)
        {
            m_pbIwfFsmRepData.set_markforrollback(rollback);
        }

        bool IsFlowFailed() const
        {
            return m_pbIwfFsmRepData.flowfailure();
        }
        void SetFlowFailure(bool failure = true)
        {
            m_pbIwfFsmRepData.set_markforrollback(failure);
        }

        void SetDontTriggerFollowOnForCCAUError(bool trigger = false)
        {
            m_pbIwfFsmRepData.set_donttriggerfollowonsessionforccauerror(trigger);
        }

        bool IsDontTriggerFollowOnForCCAUErrorSet()
        {
            return m_pbIwfFsmRepData.donttriggerfollowonsessionforccauerror();
        }

        bool IsMovingToCloseState();

        void MoveToCloseState(bool state = false);
        
        void SetActionRuleName(std::string& rrbRuleName);
        
        std::string GetActionRuleName();
        
        int UpdateIwfFsmReplicableData();

        uint32_t GetTcapLocalTid();

        void SetTcapLocalTid(uint32_t ltid);

        uint32_t GetTcapRemoteTid();

        void SetTcapRemoteTid(uint32_t rtid);

        int GetTcapOrgAddr(SCCP_ADDR& orgAddr);

        void SetTcapOrgAddr(SCCP_ADDR& oAddr);

        int GetTcapDestAddr(SCCP_ADDR& destAddr);

        void SetTcapDestAddr(SCCP_ADDR& dAddr);

        int GetTcapMtp3Label(MTP3_HEADER& mtpHdr);

        void SetTcapMtp3Label(MTP3_HEADER& label);

        void SetReplicaIndexKey(uint32_t val);

        uint32_t GetReplicaIndexKey();

        pbCapRoTsl* GetCapRoTslData()
        {
            if ( m_pbIwfFsmRepData.has_userdata())
            {
                m_pbIwfFsmRepData.clear_userdata();
            }
             pbStoredUserData* userData = m_pbIwfFsmRepData.mutable_userdata();
             pbCapRoTsl* capRoTsl = userData->mutable_caprotsl();
             capRoTsl->Clear();
             return capRoTsl;
        }
        
        void CopyIwfFsmFromReplica(pbIwfFsmInfo& pbIwfFsmData)
        {
            m_pbIwfFsmRepData.CopyFrom(pbIwfFsmData);
        }

        void SetSessionAcrossSwitchover(bool value);

        bool IsSessionAcrossSwitchover();
    
        void PurgeSession(bool purge = false);

        bool IsSessionPurged();

        void SetCallingPartyAddr(SCCP_Address* sccpAddr)
        {
            if (m_pbIwfFsmRepData.has_callingsccpaddr())
            {
                m_pbIwfFsmRepData.clear_callingsccpaddr();
            }
            pbSccpAddress *sccpCPA = m_pbIwfFsmRepData.mutable_callingsccpaddr();
            FillPbFromSccpAddress(sccpAddr, sccpCPA);
        }

        const pbSccpAddress& GetCallingPartyAddr()
        {
            return m_pbIwfFsmRepData.callingsccpaddr();
        }

        ITS_UINT GetSelfSSN()
        {
            if (m_pbIwfFsmRepData.has_selfsccpaddr() && m_pbIwfFsmRepData.selfsccpaddr().has_ssn())
            {
                return m_pbIwfFsmRepData.selfsccpaddr().ssn();
            }
            return 0;
        }
        const bool HasCallingPartyAddr()
        {
            return m_pbIwfFsmRepData.has_callingsccpaddr();
        }

        bool GetDiameterIdentityFromCallingPartyAddr(std::string& diamIdentityForCgPA)
        {
            const pbSccpAddress& cgPA = m_pbIwfFsmRepData.callingsccpaddr();

            if (cgPA.has_pointcode() && cgPA.haspc())
            {
                char strPointCode[10] = {0};
                sprintf(strPointCode, "%d", cgPA.pointcode());
                diamIdentityForCgPA.assign(strPointCode);
                return true;
            }
            else if (cgPA.has_globtitle() && cgPA.globaltitle())
            {
                std::string strGtt = "";
                int len = cgPA.gttlen();
                unsigned char* tbcd = (unsigned char*)cgPA.globtitle().c_str();
                const std::string sDigits("0123456789ABCDEF");
                //IWFUtils::TBCDToString(cgPA.globtitle().c_str(), cgPA.gttlen(), strGtt, true, false, true);
                for (int bIdx = 0; bIdx < len; bIdx++)
                {
                    strGtt += sDigits[0x0f & (tbcd[bIdx])];
                    /* // This is not required
                    if (len % 2 && (bIdx == len -1))
                    {
                        break;
                    }
                    */
                    strGtt += sDigits[(tbcd[bIdx]) >> 4];
                }
                diamIdentityForCgPA.assign(strGtt);
                return true;
            }
            else
            {
                return false;
            }
        }

        void FillPbFromSccpAddress(SCCP_Address* sccpAddr, pbSccpAddress* outPbSccpAddr)
        {
            if (!sccpAddr || !outPbSccpAddr)
            {
                return;
            }
            if (sccpAddr->HasPointCode())
            {
                outPbSccpAddr->set_haspc(true);
                outPbSccpAddr->set_pointcode(sccpAddr->GetPointCode());
            }
            if (sccpAddr->HasSSN())
            {
                outPbSccpAddr->set_hasssn(true);
                outPbSccpAddr->set_ssn(sccpAddr->GetSSN());
            }

            if(sccpAddr->HasGlobalTitle())
            {
                ITS_USHORT gttLength;
                ITS_OCTET  gttType;
                ITS_OCTET  gttInfo[64] = {0};
                sccpAddr->GetGlobalTitle(gttType, gttInfo, gttLength);
                outPbSccpAddr->set_globaltitle(true);
                outPbSccpAddr->set_gtttype(gttType);
                outPbSccpAddr->set_gttlen(gttLength);
                outPbSccpAddr->set_globtitle((void*)gttInfo, gttLength);
            }

            if (sccpAddr->IsRoutedByPCSSN())
            {
                outPbSccpAddr->set_routepcssn(true);
            }

            if (sccpAddr->IsInternationalRouting())
            {
                outPbSccpAddr->set_internationalroute(true);
            }

        }

        void SaveDestHostFromRequest(const std::string& destHost)
        {
            m_originHostForCancelLocationAnswer.assign(destHost);
            m_originHostFromCLRSet = true;
        }

        bool IsDestHostSetFromRequest()
        {
            return m_originHostFromCLRSet;
        }

        bool GetOriginHostFromRequest(std::string& originHost)
        {
            if (m_originHostFromCLRSet)
            {
                originHost.assign(m_originHostForCancelLocationAnswer);
                return true;
            }

            return false;

        }

        void SetLastSentTcapCptOpcode(ITS_LONG opCode)
        {
            m_pbIwfFsmRepData.set_lastsenttcapcptopcode(opCode);
        }

        const ITS_LONG GetLastSentTcapCptOpcode()
        {
            return m_pbIwfFsmRepData.lastsenttcapcptopcode();
        }

        const bool HasLastSentTcapCptOpcode()
        {
            return m_pbIwfFsmRepData.has_lastsenttcapcptopcode();
        }

        void SetCCFHActionDone(bool status)
        {
            m_pbIwfFsmRepData.set_isccfhactiontaken(status);
        }

        const bool IsCCFHActionTaken()
        {
            return m_pbIwfFsmRepData.isccfhactiontaken();
        }
        void MarkFsmForDeletion(bool deleteFsm)
        {
            m_markedForDeletion = deleteFsm;
        }

        bool IsFsmMarkedForDeletion()
        {
            return m_markedForDeletion;
        }

        void SetVplmnId(const uint8_t *plmn)
        {
            memset(m_vplmn, 0, sizeof(m_vplmn));
            memcpy(m_vplmn, plmn, sizeof(m_vplmn));
        }

        void GetVplmnId(uint8_t *plmn)
        {
            memcpy(plmn, m_vplmn, sizeof(plmn));
        }

        void SetEUTRANRcvdInReq(bool status)
        {
            m_isEUTRANRcvdinReq = status;
        }

        bool IsEUTRANRcvdInReq()
        {
            return m_isEUTRANRcvdinReq;
        }

        void SetUTRANRcvdInReq(bool status)
        {
            m_isUTRANRcvdinReq = status;
        }

        bool IsUTRANRcvdInReq()
        {
            return m_isUTRANRcvdinReq;
        }

        void SetResetDestHost(const std::string& destHost)
        {
           m_resetDestHost.assign(destHost);
        }

        void GetResetDestHost(std::string& destHost)
        {
            destHost.assign(m_resetDestHost);
        }
        void SetResetDestRealm(const std::string& destRealm)
        {
            m_resetDestRealm.assign(destRealm);
        }
        void GetResetDestRealm(std::string& destRealm)
        {
            destRealm.assign(m_resetDestRealm);
        }

        void AddProxyInfo(const diameter::base::ProxyInfo& pxyInfo)
        {
            m_pxyInfoList.push_back(new diameter::base::ProxyInfo(pxyInfo));
        }

        unsigned CountProxyInfo()
        {
            return m_pxyInfoList.size();
        }

        const diameter::base::ProxyInfo& GetProxyInfo(int index) const
        {
            return *(m_pxyInfoList[index]);
        }


    private:

        bool m_isTimerStarted;

        struct timeval *m_configTimeVal;

        struct event *m_timerEvent;

        State *m_graph[MAX_STATES];

        struct timeval *m_timerInvokeTimeVal;

        TransactionManager *m_txnMgr;

        TcapCptList m_tcapCptList;

        State *m_current;

        State *m_prevState;

        DIA_BASE_CMD *m_currRcvdDiaMsg;

        TCAP_Dialogue *m_currRcvdTcapDlg;

        TCAP_Component *m_currRcvdTcapCpt;

        TCAP_Begin *m_currTcapBeginDlg;

        StoredUserData *m_storedUserData;

        SCCPParameters m_sccpParams;

        IwfTranslator* m_translator;

        struct RoutingLabel *m_routingLabel;

#ifdef USE_FULL_SCCP_ADDRESS
        SCCP_CalledPartyAddr m_selfSccpAddr;
#endif

        vector<STimerInfo> m_timerList;

        vector<ITS_OCTET> m_outGoingInvokeIdList;

        bool m_IntmdteisdSent;

        bool m_acrossSwitchover;

        string m_originHostForCancelLocationAnswer;

        bool m_originHostFromCLRSet;

        string m_resetDestHost;

        string m_resetDestRealm;

#if 0

        pbProtocol m_upstrmReqProtocol;

        pbProtocol m_dnstrmReqProtocol;

        std::string m_diaSessionId;

        unsigned int m_diaSessionIdx;

        ITS_CTXT m_tcapDialogueId;

        bool m_isCurrSendErr;

        int m_errCode;

        std::string m_username;

        ITS_OCTET m_invokeId;

        bool m_bIsDiaRespSent;

        bool m_isroutebyGT;

        ITS_OCTET invoke_id;

        bool m_isTCAPEnd;

        bool m_startNoEventTimer;

        bool m_isFinalUpstrmReqSent;

        bool m_markForRollback;

        bool m_flowFailure;

        bool m_isCloseState;

        string m_actionRuleName;
#endif

        pbIwfFsmInfo m_pbIwfFsmRepData;

        bool m_isSessionPurged;

        bool m_markedForDeletion;

        uint8_t m_vplmn[3];

        bool m_isEUTRANRcvdinReq;

        bool m_isUTRANRcvdinReq;

        typedef std::vector<diameter::base::ProxyInfo*> ProxyInfoList;

        ProxyInfoList m_pxyInfoList;
};

#endif  /* FSM_H */

