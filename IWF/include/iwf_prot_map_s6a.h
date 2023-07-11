#ifndef __IWF_PROT_MAP_S6A_H__
#define __IWF_PROT_MAP_S6A_H__

#include "iwf_prot_defines.h"

#include <itu/map_cpp.h>
#include <itu/map_v13_update_gprs_location_arg.h>
#include <itu/map_v13_update_gprs_location_res.h>
#include <itu/map_v13_insert_subscriber_data_arg.h>
#include <itu/map_v13_insert_subscriber_data_res.h>
#include <itu/map_v13_provide_subscriber_info_arg.h>
#include <itu/map_v13_provide_subscriber_info_res.h>
#include <itu/map_v13_unknown_subscriber_param.h>
#include <itu/map_v13_roaming_not_allowed_param.h>
#include <itu/map_v13_data_missing_param.h>
#include <itu/map_v13_unexpected_data_param.h>
#include <itu/map_v13_facility_not_sup_param.h>
#include <itu/map_v13_system_failure_param.h>
#include <itu/map_v13_illegal_subscriber_param.h>
#include <itu/map_v13_illegal_equipment_param.h>
#include <itu/map_v13_absent_subscriber_param.h>
#include <itu/map_v13_unidentified_sub_param.h>
#include <itu/map_v13_reset_arg.h>
#include <itu/map_v13_ready_for_sm_arg.h>
#include <itu/map_v13_ready_for_sm_res.h>
#include <itu/map_v13_delete_subscriber_data_arg.h>
#include <itu/map_v13_delete_subscriber_data_res.h>
#include <itu/map_v13_activate_trace_mode_arg.h>
#include <itu/map_v13_activate_trace_mode_res.h>
#include <itu/map_v13_deactivate_trace_mode_arg.h>
#include <itu/map_v13_deactivate_trace_mode_res.h>
#include <itu/map_v13_send_authentication_info_arg.h>
#include <itu/map_v13_send_authentication_info_res.h>
#include <itu/map_v13_purge_ms_arg.h>
#include <itu/map_v13_purge_ms_res.h>
#include <itu/map_v13_cancel_location_arg.h>
#include <itu/map_v13_cancel_location_res.h>
#include <itu/map_v13_tracing_buffer_full_param.h>

#include <itu/map_v13_check_imei_arg.h>
#include <itu/map_v13_check_imei_res.h>

#include <diameter/s6a_r10/UpdateLocation.h>
#include <diameter/s6a_r10/InsertSubscriberData.h>
#include <diameter/s6a_r10/DeleteSubscriberData.h>
#include <diameter/s6a_r10/Reset.h>
#include <diameter/s6a_r10/Notify.h>
#include <diameter/s6a_r10/AuthenticationInformation.h>
#include <diameter/s6a_r10/PurgeUE.h>
#include <diameter/s6a_r10/CancelLocation.h>

#include <diameter/s13_r10/MEIdentityCheck.h>

#include "iwf_fsm.h"
#include "iwf_config.h"
#include "iwf_prot_translator.h"

using namespace its;
using namespace map_v13;
namespace s6a = diameter::s6a_r10;
namespace s13 = diameter::s13_r10;

// Populate the config
class MAPS6aConfig
{
    public:
        MAPS6aConfig()
        {
        }
        ~MAPS6aConfig()
        {
        }
        void Parse(Json::Value& val, IwfConfig& conf);

        void SetHlrNumber(std::string hlrNum)
        {
            m_hlrNumber = hlrNum;
        }

        const std::string HlrNumber() const
        {
            return m_hlrNumber;
        }

        void SetVplmnIdFromSgsnNumber(std::string& sgsnNum, std::string& vplmnId)
        {
            m_vplmnMap[sgsnNum] = vplmnId;
        }
        bool VplmnIdFromSgsnNumber(const std::string& sgsnNum, std::string& vplmnId)
        {
            SgsnVplmnIdMap::iterator it = m_vplmnMap.find(sgsnNum);
            if (it == m_vplmnMap.end())
            {
                std::string lsgsnNum(sgsnNum);
                int size=lsgsnNum.size();
                while(size > 1)
                {
                    lsgsnNum.erase(size - 1);
                    SgsnVplmnIdMap::iterator it = m_vplmnMap.find(lsgsnNum);
                    if(it == m_vplmnMap.end())
                    {
                        size--;
                        continue;
                    }
                    else
                    {
                        vplmnId = it->second;
                        return true;
                    }
                }
                return false;
            }
            else
            {
                vplmnId = it->second;
                return true;
            }
        }

        bool FindSgsnEntryInMap(const std::string& sgsnNum, std::string& vplmnId)
        {
            SgsnVplmnIdMap::iterator it = m_vplmnMap.find(sgsnNum);
            if (it == m_vplmnMap.end())
            {
                return false;
            }
            return true;
        }

        bool DeleteSgsnEntryFromMap(const std::string& sgsnNum, std::string& vplmnId)
        {
            SgsnVplmnIdMap::iterator it = m_vplmnMap.find(sgsnNum);
            if (it == m_vplmnMap.end())
            {
                return false;
            }
            m_vplmnMap.erase(it);
            return true;
        }

        bool DeleteVplmnIdFromMap(std::string& vplmnId)
        {
            std::map<std::string, std::string>::iterator it;
            bool isFound = false;
            for(it = m_vplmnMap.begin(); it != m_vplmnMap.end(); ++it)
            {
                if(!strcasecmp(it->second.c_str(), vplmnId.c_str()))
                {
                    isFound = true;
                    m_vplmnMap.erase(it);
                }
            }
            return isFound;
        }
    protected:
        std::string m_hlrNumber;
        typedef std::map<std::string, std::string> SgsnVplmnIdMap;
        SgsnVplmnIdMap m_vplmnMap;
};

class MAPS6aTransactionContext
{
    public:
        MAPS6aTransactionContext()
            : m_s6aSubscrData(NULL),
            m_mapSupportedFeatures(NULL)
    {
    }
        ~MAPS6aTransactionContext()
        {
            this->ClearSubscriptionData();
            this->ClearSupportedFeatures();
        }

        bool HasSubscriptionData()
        {
            return (m_s6aSubscrData != NULL);
        }

        s6a::SubscriptionData* GetSubscriptionData()
        {
            return m_s6aSubscrData;
        }
        void SetSubscriptionData(s6a::SubscriptionData* subsData)
        {
            m_s6aSubscrData = subsData;
        }
        void ClearSubscriptionData()
        {
            if (m_s6aSubscrData != NULL)
            {
                delete m_s6aSubscrData;
                m_s6aSubscrData = NULL;
            }
        }

        bool HasSupportedFeatures()
        {
            return (m_mapSupportedFeatures != NULL);
        }
        SupportedFeatures* GetSupportedFeatures()
        {
            return m_mapSupportedFeatures;
        }
        void SetSupportedFeatures(SupportedFeatures* supFeatures)
        {
            m_mapSupportedFeatures = supFeatures;
        }
        void ClearSupportedFeatures()
        {
            if (m_mapSupportedFeatures != NULL)
            {
                delete m_mapSupportedFeatures;
                m_mapSupportedFeatures = NULL;
            }
        }

    private:
        s6a::SubscriptionData* m_s6aSubscrData;
        SupportedFeatures*     m_mapSupportedFeatures;
};

class MAPToS6aHandler: public IwfTranslator
{
    public:
        MAPToS6aHandler();
        virtual ~MAPToS6aHandler();

        virtual int BuildTCAPMsg(IwfFsm *ctxt,
                DIA_BASE_CMD *cmd, TcapCptList *out,
                DIA_BASE_CMD *&outCmd,
                IwfReturnAction& ret);

        virtual int BuildDiaMsg(IwfFsm *ctxt,
                TCAP_Component *cpt, DIA_BASE_CMD *&cmd,
                IwfReturnAction& ret);

        virtual int BuildInterimTCAPMsg(IwfFsm *ctxt,
                TCAP_Component *in, TCAP_Component *&out,
                IwfReturnAction& ret);

        virtual int BuildTcapResponse(IwfFsm *ctxt,
                TCAP_Component *in,  TCAP_Component *&out,
                IwfReturnAction& ret);

        void ConstructUpdateGprsLocationRes(IwfFsm *ctxt,
                UpdateGprsLocationRes *out);

        virtual int BuildDiaResponse(IwfFsm *ctxt,
                DIA_BASE_CMD *in,
                DIA_BASE_CMD *&cmd,
                IwfReturnAction& ret);

        virtual int BuildDiaErrorResponse(IwfFsm *ctxt,
                DIA_BASE_CMD *in,
                DIA_BASE_CMD *&cmd,
                IwfReturnAction& ret);

        virtual int BuildDiaErrorAnswer(IwfFsm *ctxt,
                int cmdCode,
                int error,
                DIA_BASE_CMD **out);

        virtual bool IsInterimTCAPMsg(TCAP_Dialogue *tcapDlg,
                TCAP_Component *tcapCpt, bool &isReq);

        virtual bool IsInterimDiaMsg(IwfFsm *ctxt, DIA_BASE_CMD *diaCmd, bool &isReq);

        // parse the config details required for MAPToS6aHandler
        virtual int ParseConfig(Json::Value& val, IwfConfig& conf)
        {
            m_config.Parse(val, conf);
            return 0;
        }

        virtual int BuildMultiTCAPMsg(IwfFsm *ctxt,
                TCAP_Component *in,
                TcapCptList *out,
                DIA_BASE_CMD *&outCmd,
                IwfReturnAction& ret);

        int UpdateGprsLocationArg_To_ULR(IwfFsm *ctxt,
                const UpdateGprsLocationArg *in,
                s6a::UpdateLocationRequest *out);

        void UpdateGprsLocationArg_To_NOR(IwfFsm *ctxt,
                const UpdateGprsLocationArg *in,
                s6a::NotifyRequest *out);

        void ULA_To_UpdateGprsLocationRes(IwfFsm *ctxt,
                const s6a::UpdateLocationAnswer *in,
                UpdateGprsLocationRes *out);

        int  SendAuthenticationInfoArg_To_AIR(IwfFsm *ctxt,
                const SendAuthenticationInfoArg *in,
                s6a::AuthenticationInformationRequest *out);

        void AIA_To_SendAuthenticationInfoRes(IwfFsm *ctxt,
                const s6a::AuthenticationInformationAnswer *in,
                map_v13::SendAuthenticationInfoRes *out);

        void PurgeMSArg_To_PUR(IwfFsm *ctxt,
                const PurgeMS_Arg *in,
                s6a::PurgeUERequest *out);

        void PUA_To_PurgeMSRes(IwfFsm *ctxt,
                const s6a::PurgeUEAnswer *in,
                map_v13::PurgeMS_Res *out);

        void IDR_To_ProvideSubscriberInfoArg(IwfFsm *ctxt,
                const s6a::InsertSubscriberDataRequest *in,
                ProvideSubscriberInfoArg *out);

        void ProvideSubscriberInfoRes_To_IDA(IwfFsm *ctxt,
                const map_v13::ProvideSubscriberInfoRes *in,
                s6a::InsertSubscriberDataAnswer *out);

        void IDR_To_ActivateTraceModeArg(IwfFsm *ctxt,
                const s6a::InsertSubscriberDataRequest *in,
                ActivateTraceModeArg *out);

        void DSR_To_DeleteSubscriberDataArg(IwfFsm *ctxt,
                const s6a::DeleteSubscriberDataRequest *in,
                DeleteSubscriberDataArg *out);

        void DeleteSubscriberDataRes_To_DSA(IwfFsm *ctxt,
                const DeleteSubscriberDataRes *in,
                s6a::DeleteSubscriberDataAnswer *out);

        void CancelLocationRes_To_CLA(IwfFsm *ctxt,
                const CancelLocationRes *in,
                s6a::CancelLocationAnswer *out);

        void CLR_To_CancelLocationArg(IwfFsm *ctxt,
                const s6a::CancelLocationRequest *in,
                CancelLocationArg *out);

        void ReadyForSMArg_To_NOR(IwfFsm *ctxt,
                const ReadyForSM_Arg *in,
                s6a::NotifyRequest *out);

        void IDR_To_InsertSubscriberDataArg(IwfFsm *ctxt,
                const s6a::InsertSubscriberDataRequest *in,
                InsertSubscriberDataArg *out);

        void SubscriptionData_To_InsertSubscriberDataArg(IwfFsm *ctxt,
                const s6a::UpdateLocationAnswer *in,
                InsertSubscriberDataArg *out);

        void TraceData_To_ActivateTraceModeArg(IwfFsm *ctxt,
                const s6a::UpdateLocationAnswer *in,
                ActivateTraceModeArg *out);

        void BuildOperatorDeterminedBarring(
                const s6a::SubscriptionData &oSubsData,
                std::vector<byte>& array);

        void BuildOperatorDeterminedBarring(
                const s6a::SubscriptionData& oSubsData,
                ODB_Data &iOdb);

        void BuildGPRSSubscriptionData(
                const s6a::GPRSSubscriptionData in,
                GPRSDataList& out);

        void BuildPDPContext(s6a::PDPContext in , PDP_Context& out);

        void BuildLCS_PrivacyExceptionList(s6a::LCSInfo in, LCS_PrivacyExceptionList& out);
        void BuildExternalClient(
                s6a::ExternalClient& out,
                ExternalClient& in);
        void BuildEPSSubscriptionData(const s6a::InsertSubscriberDataRequest *in,
                InsertSubscriberDataArg *out);

        void BuildEPSSubscriptionData(const s6a::UpdateLocationAnswer *in,
                InsertSubscriberDataArg *out);

        void BuildAPNConfigurationProfile(s6a::APNConfigurationProfile in,
                APN_ConfigurationProfile& out);

        void BuildAPNConfiguration( s6a::APNConfiguration in, APN_Configuration& out);

        void BuildCSGSubscriptionData(const s6a::InsertSubscriberDataRequest *in,
                InsertSubscriberDataArg *out);

        void BuildCSGSubscriptionData(const s6a::UpdateLocationAnswer *in,
                InsertSubscriberDataArg *out);

        void InsertSubscriberDataRes_To_IDA(IwfFsm *ctxt,
                const InsertSubscriberDataRes *in,
                s6a::InsertSubscriberDataAnswer *out);

        void DSR_To_DeactivateTraceModeArg(IwfFsm *ctxt,
                const s6a::DeleteSubscriberDataRequest *in,
                DeactivateTraceModeArg *out);

        void DeactivateTraceModeRes_To_DSA(IwfFsm *ctxt,
                const DeactivateTraceModeRes *in,
                s6a::DeleteSubscriberDataAnswer *out);

        void ActivateTraceModeRes_To_IDA(IwfFsm *ctxt,
                const ActivateTraceModeRes *in,
                s6a::InsertSubscriberDataAnswer *out);

        void ResetReq_To_ResetArg(IwfFsm *ctxt,
                s6a::ResetRequest *in, ResetArg* out);
        void ConstructRSA(IwfFsm *ctxt, const s6a::ResetRequest *in, s6a::ResetAnswer *out);

        void SetDestinationAddrinTcapDlg(IwfFsm *ctxt, std::string imsi, bool IsCancelLocation = false);

        void UpdateSessionCtxt(IwfFsm *ctxt, std::string imsi);

        char GetCheckDigitForIMEI(std::string imei);

        void BuildTcapError(IwfFsm *ctxt, TCAP_Component *&cpt);

        template <class T>
            void ConstructErrorAnswer(int error,
                    T *out);

        virtual void BuildTCAPErrorCpt(IwfFsm *ctxt,
                DIA_BASE_CMD *cmd,
                TCAP_Component *&cpt);

        virtual int SetConfig(IwfTranslationDataConfig *req);

        virtual int DeleteConfig(IwfTranslationDataConfig *req);

        void EncodeMsg(AsnObject* p, Octets** octets);

        virtual int SetTimerConfig(IwfTimersConfig *req);

        virtual int SetMsgSpecCfg(IwfProtocolActionConfig *req);

        virtual int DeleteMsgSpecCfg(IwfProtocolActionConfig *req);

        virtual int TerminateSession(IwfFsm *ctxt,
                TCAP_Component *&outCpt, DIA_BASE_CMD *&outDiaCmd);

        virtual int OnUpstrmFinalReqSent(IwfFsm *ctxt);

        virtual ITS_UINT SetFeaturesConfig(IwfFeatureConfig *req);

        virtual ITS_UINT GetCDRConfig();

        virtual ITS_INT HandleError(IwfFsm* inFsmCtxt,
                            DIA_BASE_CMD*& outCmd,
                            TCAP_Component*& outCpt,
                            IwfReturnAction& outRetAction)
        {
            return ITS_SUCCESS;
        }

    protected:

        // Currently only works for Invoke
        ITS_LONG GetLastMAPOperation(IwfFsm *ctxt)
        {
            ITS_LONG opCode = 0;
            TCAP_Component *cpt = ctxt->GetCurrRcvdTcapCpt();
            if (cpt)
            {
                if (cpt->GetComponentType() == TCPPT_TC_INVOKE)
                {
                    static_cast<TCAP_Invoke*>(cpt)->GetOperation(opCode);
                }
            }
            return opCode;
        }

        DiaCommandCode GetLastDiaOperation(IwfFsm *ctxt)
        {
            DiaCommandCode code = DIA_CMD_UNKNOWN;
            DIA_BASE_CMD* diaCmd = ctxt->GetCurrRcvdDiaMsg();
            if (diaCmd)
            {
                code = (DiaCommandCode)diaCmd->getCommandCode();
            }
            return code;
        }

        void BuildErrorResponse(TCAP_Error *tcapError, s6a::UpdateLocationAnswer *out);

        template <class T>
            void BuildErrorResponse(TCAP_Error *tcapError, T *out);

        void BuildGERANVector(const unsigned idx,
                const AuthenticationTriplet& in,
                s6a::GERANVector& out);

        void BuildUTRANVector(const unsigned idx,
                const AuthenticationQuintuplet& in,
                s6a::UTRANVector& out);

        void BuildEUTRANVector(const unsigned idx,
                const EPC_AV& in,
                s6a::EUTRANVector& out);

        void BuildQuintupletList(const unsigned idx,
                const s6a::UTRANVector& in,
                map_v13::QuintupletList& out);

        void BuildTripletList(const unsigned idx,
                const s6a::GERANVector& in,
                map_v13::TripletList& out);

        void BuildEPSAuthSetList(const unsigned idx,
                const s6a::EUTRANVector& in,
                map_v13::EPC_AV& out);

        void BuildTraceInterfaceList(std::string& trInterfaceList,
                map_v13::TraceInterfaceList *tril);

        void BuildTraceDepthList(s6a::TraceDepth tracedepth,
                map_v13::ActivateTraceModeArg *out);

        void BuildTraceEventList(std::string& trEventList,
                map_v13::TraceEventList *trel);

        void BuildMDTConfiguration(s6a::MDTConfiguration mdtConfig,
                map_v13::MDT_Configuration &out);

        void BuildAreaScope(s6a::AreaScope areaScope,
                map_v13::AreaScope &out);

        void HandleTimeout(ETimerType& inTimerType, IwfFsm* inFsmCtxt,
                TCAP_Component* inTCAPCmpt, TCAP_Dialogue* inTCAPDlg,
                DIA_BASE_CMD*& outDiaCmd,
                TCAP_Component*& cpt,
                IwfReturnAction& outRetAction);

        void StartTimerHandling(IwfFsm* ctxt,ETimerType inTimerType);

        void SetLocalTransId(ITS_CTXT dlgId, IwfFsm* ctxt);

        int DeleteVplmnIdEntryFromMap(IwfTranslationDataConfig *translationDataConfig);

        int DeleteSGSNNumberFromVplmnIdEntryInMap(IwfTranslationDataConfig *translationDataConfig);

        virtual int LogCDRData(IwfFsm *ctxt, ITS_UINT failureCause);

        virtual ITS_UINT GetCDRFailureCause(IwfFsm *iwfFsm);

        MAPS6aConfig m_config;
};

#endif // __IWF_PROT_MAP_MAP_H__
