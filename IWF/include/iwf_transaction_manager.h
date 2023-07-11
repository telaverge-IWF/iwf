/*
 * File:   TransactionManager.h
 * Author: adey
 *
 * Created on December 21, 2012, 5:56 PM
 */

#ifndef TRANSACTIONMANAGER_H
#define TRANSACTIONMANAGER_H

#include <dia_frame.h>
#include "iwf_sm_defines.h"
#include "iwf_prot_defines.h"
//#include "iwf_mess.h"
//#include "iwf_prot_utils.h"
#include "iwf_prot_translator.h"
#include "iwf_alarms.h"
#include "AlarmId.h"
#include "ComponentDefines.h"
#include "iwf.pb.h"
#include "tcap_intern.h"
#include "dia_mgmt.h"

#include "ConfigReader.h"
#include "CouchbaseNode.h"
#include "CouchbaseMgmtClient.h"

#define TCAP_OPERATION_CLASS    1
#define TX_TIMEOUT 0x77
#define INVALID_SERVICE_KEY -1

#define IWF_MAX_TCAP_TXN_ENTRY 512

#define IWF_PEER_STATUS "PeerStatus"

class IwfFsm;

ITS_USHORT peerInstance = UNKNOWN_PEER_INST;
ITS_UINT flags = 0;

typedef std::list <TCAP_Component> TcapComponentList;

class ProtocolConverterStub;

class SessionCtxt : public ReplicableData
{
    public:
        SessionCtxt():ReplicableData(&(this->m_pbIwfSessionCtxtData))
        {
            m_pbIwfSessionCtxtData.Clear();
        }

        void SetOriginHost(std::string& originHost)
        {
            m_pbIwfSessionCtxtData.set_originhost(originHost);
        }

        void SetOriginRealm(std::string& originRealm)
        {
            m_pbIwfSessionCtxtData.set_originrealm(originRealm);
        }

        const std::string& GetOriginHost()
        {
            return m_pbIwfSessionCtxtData.originhost();
        }

        const std::string& GetOriginRealm()
        {
            return m_pbIwfSessionCtxtData.originrealm();
        }

        void UpdateOldHostRealm()
        {
            m_pbIwfSessionCtxtData.set_oldhost(m_pbIwfSessionCtxtData.originhost());
            m_pbIwfSessionCtxtData.set_oldrealm(m_pbIwfSessionCtxtData.originrealm());
        }

        bool HasOldHost()
        {
            return m_pbIwfSessionCtxtData.has_oldhost();
        }

        const std::string& GetOldHost()
        {
            return m_pbIwfSessionCtxtData.oldhost();
        }

        const std::string& GetOldRealm()
        {
            return m_pbIwfSessionCtxtData.oldrealm();
        }

        const pbSCCPParameters& GetPbSccpParameters()
        {
            return m_pbIwfSessionCtxtData.sccpparameters();
        }

        /*
           void SetOldCallingPartyAddrpresent(bool oldCPAPresent)
           {
           m_pbIwfSessionCtxtData.set_oldcallingpartyaddrpresent(oldCPAPresent);
           }
           */

        void SetOldCallingPartyAddress(const pbSccpAddress& oldCPA)
        {
            pbSccpAddress *sccpCPA = m_pbIwfSessionCtxtData.mutable_oldcpaitu();
            sccpCPA->CopyFrom(oldCPA);
        }

        ITS_UINT GetOPC()
        {
            return m_pbIwfSessionCtxtData.sccpparameters().opc();
        }

        void SetOldOPC(ITS_UINT oldOPC)
        {
            m_pbIwfSessionCtxtData.set_oldopc(oldOPC);
        }

        ITS_UINT GetOldOPC()
        {
            return m_pbIwfSessionCtxtData.oldopc();
        }

#if 0
        std::string originHost;
        std::string originRealm;
        std::string oldHost;
        std::string oldRealm;
        SCCPParameters sccpParameter;
        //SCCP_CallingPartyAddr oldcpa_itu;
        SCCPGTTInfo oldcpa_itu;
        bool OldCallingPartyAddrpresent;
        ITS_UINT m_oldopc;
#endif
        void CopySessionContextFromReplica(pbIwfSessionContextData& pbSessCtxtData)
        {
            m_pbIwfSessionCtxtData.CopyFrom(pbSessCtxtData);
        }

        bool OldCallingPartyAddrpresent()
        {
            return m_pbIwfSessionCtxtData.has_oldcpaitu();
        }

        void ClearOldCallingPartyAddr()
        {
            m_pbIwfSessionCtxtData.clear_oldcpaitu();
        }

        void SetPbSccpParameters(SCCPParameters& sccpParams);

        static void FillPbFromSccpAddress(SCCPGTTInfo* sccpAddr, pbSccpAddress* outPbSccpAddr);

        static void FillPbFromSccpAddress(SCCP_Address* sccpAddr, pbSccpAddress* outPbSccpAddr);

        void GetCallingPartyAddr(SCCP_CallingPartyAddr* cpa_itu);

        void GetCalledPartyAddr(SCCP_CalledPartyAddr* cpd_itu);

        void GetOldCallingPartyAddress(SCCP_CallingPartyAddr* cpa_itu);

        void UpdateSessionContext(SCCP_CallingPartyAddr& cpa_itu, ITS_UINT opc);

        static void FillSccpAddressFromPb(const pbSccpAddress& pbSccpAddr, SCCP_Address* sccpAddr);
    private:
        pbIwfSessionContextData m_pbIwfSessionCtxtData;
};

struct RoutingParams {
    ITS_UINT oPc;
    ITS_UINT aPc;
    ITS_USHORT ivkTimeout;
    bool useSccpCdPAFromInMsg;

    unsigned family;
    ITS_OCTET oSsn;

    bool isNational;
    ITS_UINT dPc;
    ITS_OCTET dSsn;
    bool        dSSNPresent;
    bool        routeByGT;
    ITS_OCTET   gti;
    ITS_OCTET   tt;
    ITS_OCTET   np;
    bool        ecsNationalSpecific;
    std::string gtAddr;
    ITS_INT transId;
};

class IwfCallSessionContext {
    public:
        IwfCallSessionContext():m_isNew(true)
        {
        }

        ~IwfCallSessionContext()
        {
        }

        std::list<IwfCallSessionContext*>::iterator& GetAuditIterator()
        {
            return m_auditIterator;
        }
        void SetAuditIterator(std::list<IwfCallSessionContext*>::iterator& it)
        {
            m_isNew = false;
            m_auditIterator = it;
        }

        std::string GetKey()
        {
            return key;
        }

        void SetKey(const std::string& val)
        {
            key = val;
        }

        void UpdateExpiry(unsigned expiresAt)
        {
            m_expiresAt = expiresAt;
        }

        unsigned GetExpiryTime()
        {
            return m_expiresAt;
        }

        bool IsNew()
        {
            return m_isNew;
        }

    protected:
        std::string key;
        bool m_isNew;
        // For audit purposes
        std::list<IwfCallSessionContext*>::iterator m_auditIterator;
        unsigned m_expiresAt;
};

struct QueuedDiaCommand
{
    QueuedDiaCommand(DIA_BASE_CMD* aCmd, unsigned int aSessionIdx, ITS_USHORT aPeerInstance, ITS_UINT aFlags)
    {
        cmd = aCmd;
        sessionIdx = aSessionIdx;
        peerInstance = aPeerInstance;
        flags = aFlags;
    }
    DIA_BASE_CMD* cmd;
    unsigned int sessionIdx;
    ITS_USHORT peerInstance;
    ITS_UINT flags;
};

class TransactionManager {
    public:

        static TransactionManager* Instance();
 
        void IncrementFSMCount()
        {
            CurrentFSMCount++;
        }

        void DecrementFSMCount()
        {
            CurrentFSMCount--;
        }

        static void Destroy();

        /**
         * Need to be called by the IWM core when it receives a Diameter message.
         * Single-threaded model only.
         *
         * @param cmd               IN      Diameter Command object
         * @return                  OUT     ITS_SUCCESS on success
         */
        int ProcessDiaMsg(DIA_BASE_CMD *cmd);

        /**
         * Need to be called by the IWM core when it receives a TCAP message.
         * Single-threaded model only.
         *
         * @param itsEvent          IN      TCAP event
         * @return                  OUT     ITS_SUCCESS on success
         */
        int ProcessTcapMsg(ITS_Event &itsEvent);

        /**
         * @param imsi              IN      IMSI for which origination parameters at MME/SGSN is required
         * @return                  OUT     Origination parameters at MME/SGSN, or NULL is IMSI is not found
         */
        SessionCtxt* GetSessionCtxt(const std::string& imsi);

        /**
         *
         * @param imsi              IN      IMSI for which origination parameters at MME/SGSN must be purged
         * @return                  OUT     True if purged, false otherwise
         */
        bool PurgeSessionCtxt(const std::string& imsi);

        /**
         *
         * @param isSs7Active       IN      Whether SS7 is active
         */
        void SetSs7Active(bool isSs7Active);

        /**
         *
         * @return                  OUT     Whether SS7 is active
         */
        bool IsSs7Active();

        void SetDestCldPartyAddress(SCCP_CalledPartyAddr destAddr);

        bool IsInterimMsg(IwfFsm*, pbProtocol upstrmReqProt, DIA_BASE_CMD *diaCmd, TCAP_Dialogue *tcapDlg, TCAP_Component *tcapCpt);

        int ProcessErr(IwfFsm *iwfFsm);

        int SendTcapBegin(IwfFsm *iwfFsm);

        int SendTcapContinue(IwfFsm *iwfFsm);

        int SendTcapEnd(IwfFsm *iwfFsm, bool isTransRequired = true);

        int SendTcapErrResp(IwfFsm *iwfFsm);

        int SendDiaMsg(IwfFsm *iwfFsm);

        int SendDiaErrResp(IwfFsm *iwfFsm);

        int GetRoutingParams(IwfFsm *iwfFsm, RoutingParams *&routingParams);

        int GetAlternateRoutingParams(IwfFsm *iwfFsm, RoutingParams *lRoutingParams);

        int GetTranslatorId(std::string userName, int32_t serviceKey = 0, IwfFsm *iwfFsm = NULL);

        std::string GetSelectionCriteria(SelectionCriteria selectionCrit);

        void SetOrigSSN(ITS_OCTET ssn);

        ITS_OCTET GetOrigSSN();

        void SetNetworkIndicatorFlag(bool networkInd);

        bool IsNetworkIndicatorSet();

        /* TODO: Change this API name as now we are taking imsi and serviceKey both */
        int PopulateImsiFromTcapMsg(IwfFsm *iwfFsm, std::string& imsi, int32_t &serviceKey);

        void SetReqProtocols(IwfFsm *&iwfFsm);

        int ProcessDiaTimeout(DiaMsg* dmsg);

        int ProcessDiaMsgIndicationWithData(DIA_BASE_CMD *cmd);

        IwfTranslator* GetTranslatorFromRcvdDiaMsg(DIA_BASE_CMD *cmd, IwfFsm *iwfFsm);

        template <class T> int ExtractImsi(IwfFsm *ctxt, T arg, std::string &imsi);

        std::vector<byte> EncodeRemoteGTTAddress(RoutingParams *rtparams);
        std::vector<byte> EncodeRemoteGTTAddress(SCCPParameters*);

        std::vector<byte> EncodeLocalGTTAddress(ITS_OCTET& localAddrIndicator);

        int SendTcapUni(IwfFsm *iwfFsm);

        int IsDiaErrorSetInIwfFsm(IwfFsm *iwfFsm);

        void HandleTimeout(STimerContext& timerCtxt);

        int ClearDiaAndTcapSession(IwfFsm *ctxt);

        int RemoveDiaSessionTxnEntry(std::string& diaSessionId);

        void GetSCCPParameters(IwfFsm *ctxt, SCCPParameters& sccpParam);

        ITS_UINT GetOPC(IwfFsm *ctxt);

        int ValidateTranslator(IwfTranslator* translator);

        bool IsDestinationAvailable(IwfFsm *ctxt);

        bool IsDestinationAvailable(IwfFsm *ctxt, ITS_OCTET ssn, ITS_UINT dpc, bool isNational);

        int Evaluate(std::string& imsiPrefix, int32_t& serviceKey, std::string& RuleId, int32_t& Ossn);

        int CreateTcapTransactionEntryFromReplica(pbIwfFsmInfo& IwfFsm, bool isLast = false);

        int UpdateTcapLocalTransactionTable(uint32_t aspId);

        int CreateIwfFsmFromReplica(pbIwfFsmInfo& iwfFsmInfo);

        int CreateDiameterSessionEntry(pbIwfFsmInfo& IwfFsm);

        int DeleteFirstSessionEntryFromReplica(std::string firstSessionId, IwfFsm* iwfFsm);

        void UpdateAuditList(IwfCallSessionContext* ctxt);

        void AuditSubscriberTable();

        IwfCallSessionContext* LookupSubscriberContext(const std::string& subscriber);

        bool InsertSubscriberContext(const std::string& subscriber, IwfCallSessionContext* ctxt);

        bool UpdateSubscriberContext(const std::string& subscriber, IwfCallSessionContext* ctxt);
        int DeleteSubscriberContext(const std::string& subscriber);
        int DeleteSubscriberContext(IwfCallSessionContext *ctxt);

        unsigned GetSubscribersCount()
        {
            return m_subscriberEntries;
        }

        void RestartSubscrAuditTimer();

        void StopSubscrAuditTimer();

        // Run the subscriber audit, periodically (in seconds)
        static const unsigned THF_SUBSCR_AUDIT_TIMEOUT = 30;

        void HandlePurgeSubscriberRequest(std::string& strIMSIToClear);

        bool CheckPeerStateForRouting(std::string PeerName, std::string RealmName);

        int PerformLocalBulkFetch(std::vector<std::string>&);

        void AcquireBulkFetchLock()
        {
            m_bulkFetchGuard.Acquire();
        }

        void ReleaseBulkFetchLock()
        {
            m_bulkFetchGuard.Release();
        }

        void SetRebalancingStatus(bool running)
        {
            m_rebalanceDone = running;
        }

        bool IsRebalanceInProgress()
        {
            double reb1,reb2;
            uint32_t rebalanceRet = 0;

            if (m_rebalanceDone)
            {
                return false;
            }

            if (m_couchbaseClient)
            {
                if(((rebalanceRet = m_couchbaseClient->CheckRebalanceStatus(reb1,reb2)) == CB_REBALANCE_INPROGRESS) || (rebalanceRet == CB_CURL_REBALANCE_FAILED))
                {
                    return true;
                }
                else
                {
                    m_rebalanceDone = true;
                    return false;
                }
            }
            else
            {
                // Couchbase cluster management client is not initialised, initilaize it
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
                CouchbaseConfig cb_Config;
                std::map<std::string, std::string> m_objConfigReaderMap;
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

                //default values
                if(cb_Config.adminUserName.empty())
                {
                    CLOG_DEBUG("adminUserName is empty, assigning default value.");
                    cb_Config.adminUserName="dquser";
                }

                if(cb_Config.port == 0)
                {
                    CLOG_DEBUG("port is empty, assigning default value.");
                    cb_Config.port=8091;
                }

                if(cb_Config.adminPassword.empty())
                {
                    CLOG_DEBUG("adminPassword is empty, assigning default value.");
                    cb_Config.adminPassword="diametriq@123";
                }

                CLOG_DEBUG("cb_Config.adminUserName=%s",cb_Config.adminUserName.c_str());
                CLOG_DEBUG("cb_Config.port=%d",cb_Config.port);
                CLOG_DEBUG("cb_Config.adminPassword=%s",cb_Config.adminPassword.c_str());
                CLOG_DEBUG("cb_Config.hostName=%s",cb_Config.hostName.c_str());

                m_couchbaseClient = new CouchbaseClusterMgmtClient(cb_Config);
                m_couchbaseClient->Initialize();

                if(((rebalanceRet = m_couchbaseClient->CheckRebalanceStatus(reb1,reb2)) == CB_REBALANCE_INPROGRESS) || (rebalanceRet == CB_CURL_REBALANCE_FAILED))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }

        void AddPeerToPeerStatusDb(std::string, std::string);

        void UpdatePeerStatusInPeerStatusDb(std::string, std::string, bool);

        bool ComparePeerStatus();

        bool ComparePeerStatus(const std::string&, const std::string&, bool);

        bool SendDiaMsgToStack(std::string&, DIA_BASE_CMD*, unsigned int, ITS_USHORT, ITS_UINT);

        // Method to insert a Diameter message into the temporary pending queue
        bool InsertDiaMsgIntoPendingQueue(std::string& peerName, std::string& sessionId, QueuedDiaCommand& msg);

        // Method to pop a Diameter message off the temporary pending queue
        bool RemoveDiaMsgFromPendingQueue(std::string peerName, QueuedDiaCommand* msg);

        void ProcessPendingQueueExpiry(STimerContext& timerCtxt);

        void ProcessPendingDiaMsgs(const std::string& peer, const std::string& realm);

        void HandleDumpIwfInfoRequest();

        void SetBulkFetchIwfFsmCount(uint64_t count)
        {
            m_bulkFetchIwfFsmCount = count;
        }

        TransactionManager() {
            m_isSs7Active = false;
            m_diaMgtObj = DiaMgmt::GetDiaMgmt();
            m_couchbaseClient = NULL;
            m_rebalanceDone = false;
            m_peerStatusUpdateCounter = 0;
            m_bulkFetchIwfFsmCount = 0;
        };

        TransactionManager(TransactionManager const&) {
        };

        TransactionManager& operator=(TransactionManager const&) {
            return *this;
        };

        ~TransactionManager();

    private:

        friend class IwfFsm;

        friend class TcapCptList;

        //IwfAlarms *m_iwfAlarms;

        int ResetCurrRcvdDiaMsg(IwfFsm *iwfFsm);

        int ResetCurrRcvdTcapMsg(IwfFsm *iwfFsm);

        bool IsRcvdDiaReqMsgServerInitiated(DIA_BASE_CMD *cmd);

        bool IsRcvdDiaMsgResetReq(DIA_BASE_CMD *cmd);

        bool IsRcvdDiaMsgResetResp(DIA_BASE_CMD *cmd);

        bool IsRcvdTcapReqMsgServerInitiated(TCAP_Component *tcapCpt);

        bool IsRcvdTcapReqMsgResetArg(TCAP_Component *tcapCpt);

        bool IsSubscriptionDataPresentInULA(DIA_BASE_CMD * cmd);

        void ProcessBulkFetchTimeout(STimerContext& stimerInfo);

        static its::ITS_Mutex m_bulkFetchGuard;

        static TransactionManager *m_pInstance;

        std::vector<std::string> m_localCBReplica;

        static its::ITS_Mutex m_cbFlushGuard;

        map<int, std::string> m_sessionsToFlushFromCB;

        map<std::string, IwfFsm*> m_diaSessionIdTxnEntryMap;

        map<ITS_CTXT, IwfFsm*> m_tcapDialogueIdTxnEntryMap;

        map<ITS_CTXT, TCAP_Dialogue*> m_rcvdTcapDialogueIdDialogueMap;

        map<std::string, SessionCtxt*> m_imsiMap;

        bool m_isSs7Active;

        SCCP_CalledPartyAddr m_destAddr;

        ITS_OCTET m_ssn;

        bool m_networkIndicator;

        DiaMgmt *m_diaMgtObj;

        // For checking the rebalance status, to decide to bulk fetch or not
        CouchbaseClusterMgmtClient *m_couchbaseClient;

        bool m_rebalanceDone;

        // Peer specific queues for storing the messages to be queued
        std::map<std::string, std::map<std::string, std::list<QueuedDiaCommand>>> m_tmpPendingDiaMsgQueue;

        static its::ITS_Mutex m_pendingQueueGuard;

        uint32_t m_peerStatusUpdateCounter;

        uint64_t m_bulkFetchIwfFsmCount;

        eAccelero::Atomic<uint64_t> CurrentFSMCount;
    protected:

        typedef std::unordered_map<std::string, IwfCallSessionContext*> SubscriberTable;

        eAccelero::ThreadSpec<SubscriberTable> m_subscriberTable;

        // For constant time insert and erase
        typedef std::list<IwfCallSessionContext*> SubscrAuditList;

        // For Subscriber Table Counter
        eAccelero::Atomic<uint32_t> m_subscriberEntries;

        // Subscriber audit procedure related
        eAccelero::ThreadSpec<SubscrAuditList> m_subscrAuditList;
        uint32_t m_auditTimerId;

};


#endif  /* TRANSACTIONMANAGER_H */

