#ifndef __IWF_PROT_S6A_MAP_H__
#define __IWF_PROT_S6A_MAP_H__

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
#include <itu/map_v13_data_missing_param.h>
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
#include "iwf_prot_utils.h"

using namespace its;
using namespace map_v13;
namespace s6a = diameter::s6a_r10;
namespace s13 = diameter::s13_r10;

class TcapCptList;

// populate the config
class S6aMAPConfig
{
    public:
        S6aMAPConfig()
        {
        }
        ~S6aMAPConfig()
        {
        }
        void Parse(Json::Value& val, IwfConfig& conf);

        void SetSGSNNumber(std::string sgsnNum)
        {
            m_sgsnNumber.assign(sgsnNum);
        }

        void GetSGSNNumber(ByteArray& outSgsnNum)
        {
            uint8_t svar[20] = {0};
            //NOTE: Add RoutingPrefix prior to SGSN Number
            std::string sgsnNum = SGSN_HEADER_DIGITS + m_routingPrefix + m_sgsnNumber;
            int len_of_prefix = sizeof(m_routingPrefix);
            int len = IWFUtils::StringToTBCD(sgsnNum.substr(0, LENGTH_OF_ADDR_DIGITS), svar, LENGTH_OF_ADDR_DIGITS, 0, true);
            len += IWFUtils::StringToTBCD(sgsnNum.substr(LENGTH_OF_ADDR_DIGITS), (svar+1), MAX_SGSN_NUM_LEN, 0x0f);
            memset(&outSgsnNum, 0, sizeof(outSgsnNum));
            outSgsnNum.assign(svar, svar + len);
        }
       
        void SetRoutingPrefix(std::string routingPrefix)
        {
            m_routingPrefix.assign(routingPrefix);
        }

        void GetRoutingPrefix(std::string& routingPrefix)
        {
            if(!m_routingPrefix.empty())
            {
                routingPrefix.assign(m_routingPrefix);
            }
        }

        bool SetSGSNAddrFromOHost(std::string& oHost, std::string& ipAddr)
        {
            its::ByteArray outAddr;
            IWFUtils::IpStringToGSNAddress(ipAddr, outAddr);
            m_sgsnMap[oHost] = outAddr;
            return true;
        }
        // Returns false if ohost not found in the map
        bool SGSNAddrFromOHost(const std::string& oHost, its::ByteArray& outAddr)
        {
            SgsnConfigMap::iterator it = m_sgsnMap.find(oHost);
            if (it == m_sgsnMap.end())
            {
                return false;
            }
            outAddr = it->second;
            return true;
        }

        bool RemoveSGSNAddrFromOHost(const std::string& oHost)
        {
            bool retVal = false;
            SgsnConfigMap::iterator it = m_sgsnMap.find(oHost);
            if (it == m_sgsnMap.end())
            {
                ST_ERR(("Failed to remove Host from SGSNAddress : %s not present",oHost.c_str()));
            }
            else
            {
                m_sgsnMap.erase(it);
                retVal = true;
            }
            return retVal;
        }

        bool SetSGSNPrefixFromVplmnId(std::string& vplmnid, std::string& sgsn_prefix)
        {
            std::string vplmnId = vplmnid;
            std::transform(vplmnId.begin(), vplmnId.end(), vplmnId.begin(), (int(*)(int))std::toupper);
            m_sgsnPrefixMap[vplmnId] = sgsn_prefix;
            return true;
        }
        // Returns false if VplmnId not found in the map
        bool GetSGSNPrefixFromVplmnId(const std::string& vplmnid, std::string& sgsn_prefix)
        {
            std::string vplmnId = vplmnid;
            std::transform(vplmnId.begin(), vplmnId.end(), vplmnId.begin(), (int(*)(int))std::toupper);
            SgsnPrefixConfigMap::iterator it = m_sgsnPrefixMap.find(vplmnId);
            if (it == m_sgsnPrefixMap.end())
            {
                return false;
            }
            sgsn_prefix = it->second;
            return true;
        }

        bool RemoveSGSNPrefixFromVplmnId(const std::string& vplmnid)
        {
            bool retVal = false;
            SgsnPrefixConfigMap::iterator it = m_sgsnPrefixMap.find(vplmnid);
            if (it == m_sgsnPrefixMap.end())
            {
                ST_ERR(("Failed to removed SGSNPrefix from VplmnId: %s, entry not found",vplmnid.c_str()));
            }
            else
            {
                m_sgsnPrefixMap.erase(it);
                retVal = true;
            }
            return retVal;
        }

        bool SetSGSNNumberFromOriginHost(std::string& originHost, std::string& sgsn_number)
        {
            m_generatedSgsnNumberMap[originHost] = sgsn_number;
            return true;
        }
        // Returns false if OriginHost not found in the map
        bool GetSGSNNumberFromOriginHost(const std::string& originHost, std::string& sgsn_number)
        {
            SgsnPrefixConfigMap::iterator it = m_generatedSgsnNumberMap.find(originHost);
            if (it == m_generatedSgsnNumberMap.end())
            {
                return false;
            }
            sgsn_number = it->second;
            return true;
        }

        bool RemoveSGSNNumberFromOriginHost(const std::string& originHost)
        {
            bool retVal = false;
            SgsnPrefixConfigMap::iterator it = m_generatedSgsnNumberMap.find(originHost);
            if (it == m_generatedSgsnNumberMap.end())
            {
                ST_ERR(("Failed to remove OriginHost %s from SGSNNumber Map, as entry not present",originHost.c_str()));
            }
            else
            {
                m_generatedSgsnNumberMap.erase(it);
                retVal = true;
            }
            return retVal;
        }
    protected:
        typedef std::map<std::string, its::ByteArray> SgsnConfigMap;
        typedef std::map<std::string, std::string> SgsnPrefixConfigMap;
        typedef std::map<std::string, std::string> GeneratedSgsnNumberConfigMap;

        std::string m_sgsnNumber;
        std::string m_routingPrefix;
        SgsnConfigMap   m_sgsnMap;
        SgsnPrefixConfigMap   m_sgsnPrefixMap;
        GeneratedSgsnNumberConfigMap m_generatedSgsnNumberMap;
        its::ByteArray m_sgsnAddress;
};

class S6aMAPTransactionContext:public StoredUserData
{
    public:
        S6aMAPTransactionContext()
            : m_s6aSubscrData(NULL),
            m_mapSupportedFeatures(NULL)
    {
    }
        ~S6aMAPTransactionContext()
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
        void UpdateSubscriptionData(s6a::SubscriptionData* subsData)
        {
            //m_s6aSubscrData = subsData;
            if (subsData->containsGPRSSubscriptionData())
            {
                s6a::GPRSSubscriptionData newGprsSubsData = subsData->getGPRSSubscriptionData();
                s6a::GPRSSubscriptionData oldGprsSubsData = m_s6aSubscrData->getGPRSSubscriptionData();
                for (int i = 0; i < newGprsSubsData.countPDPContext(); i++)
                {
                    oldGprsSubsData.addPDPContext(newGprsSubsData.getPDPContext(i));
                }
                m_s6aSubscrData->setGPRSSubscriptionData(oldGprsSubsData);
            }

            if (subsData->containsAPNConfigurationProfile())
            {
                s6a::APNConfigurationProfile newAPNConfigProfile = subsData->getAPNConfigurationProfile();
                s6a::APNConfigurationProfile oldAPNConfigProfile = m_s6aSubscrData->getAPNConfigurationProfile();
                for (int i = 0; i < newAPNConfigProfile.countAPNConfiguration(); i++)
                {
                    oldAPNConfigProfile.addAPNConfiguration(newAPNConfigProfile.getAPNConfiguration(i)); 
                }
                m_s6aSubscrData->setAPNConfigurationProfile(oldAPNConfigProfile);
            }

    if (subsData->containsNetworkAccessMode())
    {
        m_s6aSubscrData->setNetworkAccessMode(subsData->getNetworkAccessMode());
    }

    if(subsData->containsRoamingRestrictedDueToUnsupportedFeature())
    {
        m_s6aSubscrData->setRoamingRestrictedDueToUnsupportedFeature(s6a::RoamingRestrictedDueToUnsupportedFeature(s6a::RoamingRestrictedDueToUnsupportedFeature::Roaming_Restricted_Due_To_Unsupported_Feature));
    }


    if (subsData->containsS6a3GPPChargingCharacteristics())
    {
        m_s6aSubscrData->setS6a3GPPChargingCharacteristics(subsData->getS6a3GPPChargingCharacteristics());

    }

    if (subsData->containsAccessRestrictionData())
    {
        m_s6aSubscrData->setAccessRestrictionData(subsData->getAccessRestrictionData());
    }

            // delete the new subsData, since we have stored updates in old subsData
            delete subsData;

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

class S6aToMAPHandler: public IwfTranslator
{
    public:
        S6aToMAPHandler();
        virtual ~S6aToMAPHandler();

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

        // parse the config details required for S6aToMAPHandler
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

        int ULR_To_UpdateGPRSLocationArg(IwfFsm *ctxt,
                const s6a::UpdateLocationRequest *in,
                UpdateGprsLocationArg *out);

        void UpdateGPRSLocationRes_To_ULA(IwfFsm *ctxt,
                const UpdateGprsLocationRes *in,
                s6a::UpdateLocationAnswer *out);

        void InsertSubscriberDataArg_To_SubscriptionData(IwfFsm *ctxt,
                const InsertSubscriberDataArg *in,
                s6a::SubscriptionData *out);

        void ConstructInserSubsciberDataRes(IwfFsm* ctxt,
                const InsertSubscriberDataArg* arg,
                InsertSubscriberDataRes* res);

        int InsertSubscriberDataArg_To_IDR(IwfFsm *ctxt,
                const InsertSubscriberDataArg *in,
                s6a::InsertSubscriberDataRequest *out);

        void IDA_To_InsertSubscriberDataRes(IwfFsm *ctxt,
                const s6a::InsertSubscriberDataAnswer *in,
                InsertSubscriberDataRes* out);

        void ResetArg_To_RSR(IwfFsm *ctxt,
                const ResetArg* in,
                s6a::ResetRequest *out);

        void NOR_To_UpdateGPRSLocationArg(IwfFsm *ctxt,
                const s6a::NotifyRequest *in,
                UpdateGprsLocationArg *out);

        void NOR_To_ReadyForSM(IwfFsm *ctxt,
                const s6a::NotifyRequest *in,
                ReadyForSM_Arg *out);

        void ConstructNOA(IwfFsm *ctxt,
                const s6a::NotifyRequest *in,
                s6a::NotifyAnswer *out);

        template <class T>
            void ConstructErrorAnswer(int error,
                    T *out);

        int ProvideSubscriberInfoArg_To_IDR(IwfFsm *ctxt,
                const map_v13::ProvideSubscriberInfoArg *in,
                s6a::InsertSubscriberDataRequest *out);

        void IDA_To_ProvideSubscribeInfoRes(IwfFsm *ctxt,
                const s6a::InsertSubscriberDataAnswer *in,
                map_v13::ProvideSubscriberInfoRes *out);

        int DeleteSubscriberDataArg_To_DSR(IwfFsm *ctxt,
                const map_v13::DeleteSubscriberDataArg *in,
                s6a::DeleteSubscriberDataRequest *out);

        void DSA_To_DeleteSubscriberDataRes(IwfFsm *ctxt,
                const s6a::DeleteSubscriberDataAnswer *in,
                map_v13::DeleteSubscriberDataRes *out);

        void ActivateTraceModeArg_To_TraceData(IwfFsm *ctxt,
                const ActivateTraceModeArg *in,
                s6a::TraceData *out);

        int ActivateTraceModeArg_To_IDR(IwfFsm *ctxt,
                const ActivateTraceModeArg *in,
                s6a::InsertSubscriberDataRequest *out);

        void IDA_To_ActivateTraceModeRes(IwfFsm *ctxt,
                const s6a::InsertSubscriberDataAnswer *in,
                ActivateTraceModeRes *out);

        int DeactivateTraceModeArg_To_DSR(IwfFsm *ctxt,
                const DeactivateTraceModeArg *in,
                s6a::DeleteSubscriberDataRequest *out);

        void DSA_To_DeactivateTraceModeRes(IwfFsm *ctxt,
                const s6a::DeleteSubscriberDataAnswer *in,
                DeactivateTraceModeRes *out);

        virtual void BuildTCAPErrorCpt(IwfFsm *ctxt,
                DIA_BASE_CMD *cmd,
                TCAP_Component *&cpt);

        int AIR_To_SendAuthenticationInfoArgv3(IwfFsm *ctxt,
                const s6a::AuthenticationInformationRequest *in,
                SendAuthenticationInfoArg *out);

        void SendAuthenticationInfoResv3_To_AIA(IwfFsm *ctxt,
                const SendAuthenticationInfoRes *in,
                s6a::AuthenticationInformationAnswer *out);

        void PUR_To_PurgeMSArgv3(IwfFsm *ctxt,
                const s6a::PurgeUERequest *in,
                PurgeMS_Arg *out);

        void PurgeMS_Resv3_To_PUA(IwfFsm *ctxt,
                const PurgeMS_Res *in,
                s6a::PurgeUEAnswer *out);

        int CancelLocationArg_To_CLR(IwfFsm *ctxt,
                const CancelLocationArg *in,
                s6a::CancelLocationRequest *out);

        void CLA_To_CancelLocationRes(IwfFsm *ctxt,
                const s6a::CancelLocationAnswer *in,
                CancelLocationRes *out);

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

        void BuildTcapError(IwfFsm *ctxt, TCAP_Component *&cpt);

        bool GetSgsnNumberFromConfig(std::string originHost, std::string vplmnId, std::string& sgsnNumber);
        void Generateipv4(string& createdAddress);
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

        void BuildSGSNCapability(IwfFsm *ctxt, const s6a::UpdateLocationRequest *in,
                SGSN_Capability *cap);

        void BuildAddInfo(const s6a::TerminalInformation &in, ADD_Info *oAddInfo,
                bool skipSubsUpdate = false);

        void BuildEPSInfo(unsigned iUlrFlags, EPS_Info *oEpsInfo);

        void BuildErrorResponse(TCAP_Error *tcapError, s6a::UpdateLocationAnswer *out);

        template <class T>
            void BuildErrorResponse(TCAP_Error *tcapError, T *out);

        void BuildOperatorDeterminedBarring(const ODB_GeneralData &iOdb,
                s6a::SubscriptionData *oSubsData);

        void BuildAPNConfigurationProfile(const APN_ConfigurationProfile& in,
                s6a::APNConfigurationProfile& out);

        void BuildAPNConfiguration(const APN_Configuration& in, s6a::APNConfiguration &out);

        void BuildGPRSSubscriptionData(const GPRSSubscriptionData& in,
                s6a::GPRSSubscriptionData& out);

        void BuildPDPContext(const PDP_Context& in, s6a::PDPContext& out);

        void BuildLCSInfo(const LCSInformation& in, s6a::LCSInfo& out);

        void BuildLCSPrivacyException(const LCS_PrivacyClass &in,
                s6a::LCSPrivacyException &out);

        void BuildExternalClient(const ExternalClient& in, s6a::ExternalClient& out);

        void BuildCSGSubscriptionData(const CSG_SubscriptionData& in,
                s6a::CSGSubscriptionData& out);

        void BuildPDNGWIdentity(const s6a::MIP6AgentInfo& in,
                PDN_GW_Identity &out);

        void BuildOdbGeneralData(
                const SupportedFeatures* sf,
                const ODB_GeneralData& iOdb,
                ODB_GeneralData *oOdb);

        void BuildGERANVector(const unsigned idx,
                const AuthenticationTriplet& in,
                s6a::GERANVector& out);

        void BuildUTRANVector(const unsigned idx,
                const AuthenticationQuintuplet& in,
                s6a::UTRANVector& out);

        void BuildEUTRANVector(const unsigned idx,
                const AuthenticationQuintuplet& in,
                s6a::EUTRANVector& out, uint8_t* vplmnId);

        void BuildEUTRANVector(const unsigned idx,
                const EPC_AV& in,
                s6a::EUTRANVector& out);

        void HandleTimeout(ETimerType& inTimerType, IwfFsm* inFsmCtxt,
                TCAP_Component* inTCAPCmpt, TCAP_Dialogue* inTCAPDlg,
                DIA_BASE_CMD*& outDiaCmd,
                TCAP_Component*& cpt,
                IwfReturnAction& outRetAction);

        void StartTimerHandling(IwfFsm* ctxt,ETimerType inTimerType);

        void SetLocalTransId(ITS_CTXT dlgId, IwfFsm* ctxt);

        virtual int LogCDRData(IwfFsm *ctxt, ITS_UINT failureCause);

        virtual ITS_UINT GetCDRFailureCause(IwfFsm *iwfFsm);

        S6aMAPConfig m_config;
};

#endif // __IWF_PROT_S6A_MAP_H__
