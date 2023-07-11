#ifndef __IWF_PROT_CAP_RO_H__
#define __IWF_PROT_CAP_RO_H__

#include "iwf_prot_defines.h"

#include <cap_cpp.h>
#include <itu/cap_v3_initial_dp_arg.h>
#include <itu/cap_v3_initial_dpsms_arg.h>
#include <itu/cap_v3_request_report_bcsm_event_arg.h>
#include <itu/cap_v3_request_report_sms_event_arg.h>
#include <itu/cap_v3_release_sms_arg.h>
#include <itu/cap_v3_event_report_sms_arg.h>
#include <itu/cap_v3_apply_charging_arg.h>
#include <itu/cap_v3_apply_charging_report_arg.h>
#include <itu/cap_v3_camel_a_ch_billing_charging_characteristics.h>
#include <itu/cap_v3_bcsm_event.h>
#include <itu/cap_v3_event_type_bcsm.h>
#include <itu/cap_v3_release_call_arg.h>
#include <itu/cap_v3_event_report_bcsm_arg.h>
#include <itu/cap_v3_camel_call_result.h>

#include <diameter/nasreq/NasreqAVP.h>
#include <diameter/dcca/DccaAVP.h>
#include <diameter/base/AbortSession.h>
#include <diameter/base/SessionTermination.h>
#include <diameter/ro_r10/Ro_r10AVP.h>
#include <diameter/ro_r10/CreditControl.h>
//#include <diameter/ro_r10/ReAuth.h>
#include <diameter/base/ReAuth.h>

#include "iwf_fsm.h"
#include "iwf_config.h"
#include "iwf_prot_translator.h"


#define NORMAL_UNSPECIFIED 0x9f
#define NO_ROUTE_TO_DEST 0x83

using namespace its;
using namespace cap_v3;
using namespace diameter::nasreq;
using namespace diameter::dcca;
namespace Ro = diameter::ro_r10;

// Populate the config
class CAPRoConfig
{
    public:
        CAPRoConfig()
            :m_nodeFunctionality(0),
            m_origIOI(""),
            m_termIOI(""),
            m_sipMethod(""),
            m_idpServCtxtId(""),
            m_idpSmsServCtxtId(""),
            m_causeCode(""),
            m_idpMscServSpcfcType(0),
            m_idpGmscServSpcfcType(0),
            m_idpCpcServSpcfcType(0),
            m_idpSmsMscServSpcfcType(0),
            m_idpSmsSgsnServSpcfcType(0),
            m_mulServIndicator(0),
            m_smsNode(0),
            m_rplyPathRqsted(0),
            m_clientAddress(""),
            m_originatorSCCPAddr(""),
            m_isNodeFunctionalitySet(false),
            m_isIdpMscServSpcfcTypeSet(false),
            m_isIdpGmscServSpcfcTypeSet(false),
            m_isIdpCpcServSpcfcTypeSet(false),
            m_isIdpSmsMscServSpcfcTypeSet(false),
            m_isIdpSmsSgsnServSpcfcTypeSet(false),
            m_isMulServIndicatorSet(false),
            m_isSmsNodeSet(false),
            m_isRplyPathRqstedSet(false),
            m_isTeleSrvcMapSet(false),
            m_isBeareSrvcMapSet(false)
    {
    }
        ~CAPRoConfig()
        {
        }
        void Parse(Json::Value& val, IwfConfig& conf);

        void SetNodeFunctionality(ITS_UINT nodeFunc)
        {
            m_nodeFunctionality = nodeFunc;
        }
        ITS_UINT NodeFunctionality() const
        {
            return m_nodeFunctionality;
        }

        void SetOriginatingIOI(std::string origIOI)
        {
            m_origIOI = origIOI;
        }
        const std::string OriginatingIOI() const
        {
            return m_origIOI;
        }

        void SetTerminatingIOI(std::string termIOI)
        {
            m_termIOI = termIOI;
        }
        const std::string TerminatingIOI() const
        {
            return m_termIOI;
        }

        void SetSipMethod(std::string sipMethod)
        {
            m_sipMethod = sipMethod;
        }
        const std::string SipMethod() const
        {
            return m_sipMethod;
        }

        void SetIDPServiceContextId(std::string servContextId)
        {
            m_idpServCtxtId = servContextId;
        }
        const std::string GetIDPServiceContextId() const
        {
            return m_idpServCtxtId;
        }

        void SetIDPSMSServiceContextId(std::string servContextId)
        {
            m_idpSmsServCtxtId = servContextId;
        }
        const std::string GetIDPSMSServiceContextId() const
        {
            return m_idpSmsServCtxtId;
        }

        void SetCauseCode(std::string causeCode)
        {
            m_causeCode = causeCode;
        }
        const std::string CauseCode() const
        {
            return m_causeCode;
        }

        void SetIDPMscServiceSpecificType(uint32_t servSpecificType)
        {
            m_idpMscServSpcfcType = servSpecificType;
        }
        uint32_t IDPMscServiceSpecificType() const
        {
            return m_idpMscServSpcfcType;
        }

        void SetIDPGmscServiceSpecificType(uint32_t servSpecificType)
        {
            m_idpGmscServSpcfcType = servSpecificType;
        }
        uint32_t IDPGmscServiceSpecificType() const
        {
            return m_idpGmscServSpcfcType;
        }

        void SetIDPCPCServiceSpecificType(uint32_t servSpecificType)
        {
            m_idpCpcServSpcfcType = servSpecificType;
        }
        uint32_t IDPCPCServiceSpecificType() const
        {
            return m_idpCpcServSpcfcType;
        }

        void SetIDPSMSMscServiceSpecificType(uint32_t servSpecificType)
        {
            m_idpSmsMscServSpcfcType = servSpecificType;
        }
        uint32_t IDPSMSMscServiceSpecificType() const
        {
            return m_idpSmsMscServSpcfcType;
        }

        void SetIDPSMSsgsnServiceSpecificType(uint32_t servSpecificType)
        {
            m_idpSmsSgsnServSpcfcType = servSpecificType;
        }
        uint32_t IDPSMSsgsnServiceSpecificType() const
        {
            return m_idpSmsSgsnServSpcfcType;
        }

        void SetMultipleServiceIndicator(ITS_UINT mulServInd)
        {
            m_mulServIndicator = mulServInd;
        }
        ITS_UINT MultipleServiceIndicator() const
        {
            return m_mulServIndicator;
        }

        void SetSMSNode(ITS_UINT smsNode)
        {
            m_smsNode = smsNode;
        }
        ITS_UINT SMSNode() const
        {
            return m_smsNode;
        }

        void SetReplyPathRequested(ITS_UINT rplyPathReq)
        {
            m_rplyPathRqsted = rplyPathReq;
        }
        ITS_UINT ReplyPathRequested() const
        {
            return m_rplyPathRqsted;
        }

        void SetClientAddress(std::string clientAdd)
        {
            m_clientAddress = clientAdd;
        }
        std::string ClientAddress() const
        {
            return m_clientAddress;
        }

        void SetOriginatorSCCPAddr(std::string origSccpAdd)
        {
            m_originatorSCCPAddr = origSccpAdd;
        }
        std::string OriginatorSCCPAddr() const
        {
            return m_originatorSCCPAddr;
        }

        void SetServiceIdFromExtTeleService(uint32_t& extTeleService, uint32_t& servId)
        {
            m_extTeleServiceMap[extTeleService] =  servId;
        }

        bool ServiceIdFromExtTeleService(const uint32_t& extTeleService, uint32_t& servId)
        {
            ExtTeleServiceConfigMap::iterator it = m_extTeleServiceMap.find(extTeleService);
            if (it == m_extTeleServiceMap.end())
            {
                return false;
            }
            servId = it->second;
            return true;
        }

        bool RemoveServiceIdFromExtTeleService(const uint32_t& extTeleService)
        {
            bool retVal = false;
            ExtTeleServiceConfigMap::iterator it = m_extTeleServiceMap.find(extTeleService);
            if (it == m_extTeleServiceMap.end())
            {
                ST_DBG(("Failed to removed ext-TeleService Code : %d not present",extTeleService));
            }
            else
            {
                m_extTeleServiceMap.erase(it);
                ST_DBG(("Successfully removed ext-TeleService Code : %d",extTeleService));
                retVal = true;
            }
            return retVal;
        }

        void SetServiceIdFromExtBearerService(uint32_t& extBearService, uint32_t& servId)
        {
            m_extBearerServiceMap[extBearService] = servId;
        }

        bool ServiceIdFromExtBearerService(const uint32_t& extBearService, uint32_t& servId)
        {
            ExtBearerServiceConfigMap::iterator it = m_extBearerServiceMap.find(extBearService);
            if (it == m_extBearerServiceMap.end())
            {
                return false;
            }
            servId = it->second;
            return true;
        }
        bool RemoveServiceIdFromExtBearerService(const uint32_t& extBearerService)
        {
            bool retVal = false;
            ExtBearerServiceConfigMap::iterator it = m_extBearerServiceMap.find(extBearerService);
            if (it == m_extBearerServiceMap.end())
            {
                ST_DBG(("Failed to removed ext-BearerService Code : %d not present",extBearerService));
            }
            else
            {
                m_extBearerServiceMap.erase(it);
                ST_DBG(("Successfully removed ext-BearerService Code : %d",extBearerService));
                retVal = true;
            }
            return retVal;
        }

        void SetNodeFunctionalityFlag(bool NodeFunc)
        {
            m_isNodeFunctionalitySet = NodeFunc;
        }
        bool IsNodeFunctionalityFlagSet()
        {
            return m_isNodeFunctionalitySet;
        }

        void SetIdpMscServiceSpecifictypeFlag(bool servSpecificType)
        {
            m_isIdpMscServSpcfcTypeSet = servSpecificType;
        }
        bool IsIdpMscServiceSpecifictypeFlagSet()
        {
            return m_isIdpMscServSpcfcTypeSet ;
        }

        void SetIdpGmscServiceSpecifictypeFlag(bool servSpecificType)
        {
            m_isIdpGmscServSpcfcTypeSet = servSpecificType;
        }
        bool IsIdpGmscServiceSpecifictypeFlagSet()
        {
            return m_isIdpGmscServSpcfcTypeSet;
        }

        void SetIdpCpcServSpcfcTypeFlag(bool servSpecificType)
        {
            m_isIdpCpcServSpcfcTypeSet = servSpecificType;
        }
        bool IsIdpCpcServSpcfcTypeFlagSet()
        {
            return m_isIdpCpcServSpcfcTypeSet;
        }

        void SetIdpSmsMscServSpcfcTypeflag(bool servSpecificType)
        {
            m_isIdpSmsMscServSpcfcTypeSet = servSpecificType;
        }
        bool IsIdpSmsMscServSpcfcTypeFlagSet()
        {
            return m_isIdpSmsMscServSpcfcTypeSet;
        }

        void SetIdpSmsSgsnServSpcfcTypeFlag(bool servSpecificType)
        {
            m_isIdpSmsSgsnServSpcfcTypeSet = servSpecificType;
        }
        bool IsIdpSmsSgsnServSpcfcTypeFlagSet()
        {
            return m_isIdpSmsSgsnServSpcfcTypeSet;
        }

        void SetMulServIndicatorFlag(bool multiServindicator)
        {
            m_isMulServIndicatorSet = multiServindicator;
        }
        bool IsMulServIndicatorFlagSet()
        {
            return m_isMulServIndicatorSet;
        }

        void SetSmsNodeFlag(bool smsNode)
        {
            m_isSmsNodeSet = smsNode;
        }
        bool IsSmsNodeFlagSet()
        {
            return m_isSmsNodeSet;
        }

        void SetRplyPathRqstedFlag(bool replyPathRqstd)
        {
            m_isRplyPathRqstedSet = replyPathRqstd;
        }
        bool IsRplyPathRqstedFlagSet()
        {
            return m_isRplyPathRqstedSet;
        }

        void SetTeleSrvcMapFlag(bool replyPathRqstd)
        {
            m_isTeleSrvcMapSet = replyPathRqstd;
        }
        bool IsTeleSrvcMapFlagSet()
        {
            return m_isTeleSrvcMapSet;
        }

        void SetBearerSrvcMapFlag(bool replyPathRqstd)
        {
            m_isBeareSrvcMapSet = replyPathRqstd;
        }
        bool IsBearerSrvcMapFlagSet()
        {
            return m_isBeareSrvcMapSet;
        }
    protected:
        ITS_UINT m_nodeFunctionality;
        std::string m_origIOI;
        std::string m_termIOI;
        std::string m_sipMethod;
        std::string m_idpServCtxtId;
        std::string m_idpSmsServCtxtId;
        std::string m_causeCode;
        uint32_t m_idpMscServSpcfcType;
        uint32_t m_idpGmscServSpcfcType;
        uint32_t m_idpCpcServSpcfcType;
        uint32_t m_idpSmsMscServSpcfcType;
        uint32_t m_idpSmsSgsnServSpcfcType;
        ITS_UINT m_mulServIndicator;
        ITS_UINT m_smsNode;
        ITS_UINT m_rplyPathRqsted;
        std::string m_clientAddress;
        std::string m_originatorSCCPAddr;
        typedef std::map<ITS_UINT, ITS_UINT> ExtTeleServiceConfigMap;
        typedef std::map<ITS_UINT, ITS_UINT> ExtBearerServiceConfigMap;
        ExtTeleServiceConfigMap   m_extTeleServiceMap;
        ExtBearerServiceConfigMap m_extBearerServiceMap;
        bool m_isNodeFunctionalitySet;
        bool m_isIdpMscServSpcfcTypeSet;
        bool m_isIdpGmscServSpcfcTypeSet;
        bool m_isIdpCpcServSpcfcTypeSet;
        bool m_isIdpSmsMscServSpcfcTypeSet;
        bool m_isIdpSmsSgsnServSpcfcTypeSet;
        bool m_isMulServIndicatorSet;
        bool m_isSmsNodeSet;
        bool m_isRplyPathRqstedSet;
        bool m_isTeleSrvcMapSet;
        bool m_isBeareSrvcMapSet;
};

class CAPRoTransactionContext:public StoredUserData
{
    public:
        CAPRoTransactionContext()
            :m_bcsmEventflag(false),
            m_capCallingPartyNumber(NULL),
            m_serviceIdentifier(0),
            m_receivedBasicService(false),
            m_roUserSessId(NULL),
            m_imschargingidentifier(NULL),
            m_roServiceContextId(NULL),
            m_roSubscriptionId(NULL),
            m_roCUGInformation(NULL),
            m_capMscAddress(NULL),
            m_capGmscAddress(NULL),
            m_ccaInitialResultCode(0),
            m_ccaUpdateResultCode(0),
            m_ccaTerminateResultCode(0),
            m_receivedTcapContinue(false),
            m_reveivedASR(false),
            m_isReceivedIDPSMS(false),
            m_isTimeZoneBitSet(false),
            m_TimeZoneSeconds(0),
            m_ccaUpdateMsccResultCode(0),
            m_isccaMsccGrantedCCTimeZero(false),
            m_isReleaseSent(false),
            m_lastSentCCRequestType(0),
            m_ccRequestNumber(0),
            m_isFirstERBrcvd(0),
            m_relCause(0x9f),
            m_isOnlyERBInTcEnd(false),
            m_servicekey(0),
            m_userName("")
    {
    }
        ~CAPRoTransactionContext()
        {
            this->ClearCallingPartyNumber();
            this->ClearUserSessionID();
            this->ClearIMSChargingIdentifier();
            this->ClearSubscriptionId();
            this->ClearCUGInformation();
            this->ClearServiceContextId();
            this->ClearMscAddress();
            this->ClearGmscAddress();
        }

        bool HasCallingPartyNumber()
        {
            return (m_capCallingPartyNumber != NULL);
        }
        cap_v3::CallingPartyNumber* GetCallingPartyNumber()
        {
            return m_capCallingPartyNumber;
        }
        void SetCallingPartyNumber(cap_v3::CallingPartyNumber* callParNum)
        {
            m_capCallingPartyNumber = callParNum;
        }
        void ClearCallingPartyNumber()
        {
            if (m_capCallingPartyNumber != NULL)
            {
                delete m_capCallingPartyNumber;
                m_capCallingPartyNumber = NULL;
            }
        }

        void SetBcsmEventMO(bool bcsmflag)
        {
            m_bcsmEventflag = bcsmflag;
        }
        bool GetBcsmEventMO()
        {
            return m_bcsmEventflag;
        }

        void SetServiceIdentifier(int si)
        {
            m_serviceIdentifier = si;
        }
        int GetServiceIdentifier()
        {
            return m_serviceIdentifier;
        }

        void SetBasicServiceReceived(bool bVal)
        {
            m_receivedBasicService = bVal;
        }
        bool IsBasicServiceReceived()
        {
            return m_receivedBasicService;
        }

        bool HasUserSessionId()
        {
            return (m_roUserSessId != NULL);
        }
        Ro::UserSessionID* GetUserSessionID()
        {
            return m_roUserSessId;
        }
        void SetUserSessionID(Ro::UserSessionID* usrSessId)
        {
            m_roUserSessId  = usrSessId;
        }
        void ClearUserSessionID()
        {
            if (m_roUserSessId != NULL)
            {
                delete m_roUserSessId;
                m_roUserSessId = NULL;
            }
        }

        bool HasServiceContextId()
        {
            return (m_roServiceContextId != NULL);
        }
        void SetServiceContextId(Ro::ServiceContextId* scid)
        {
            m_roServiceContextId = scid;
        }
        Ro::ServiceContextId* GetServiceContextId()
        {
            return m_roServiceContextId;
        }
        void ClearServiceContextId()
        {
            if(m_roServiceContextId != NULL)
            {
                delete m_roServiceContextId;
                m_roServiceContextId = NULL;
            }
        }

        bool HasCUGInformation()
        {
            return (m_roCUGInformation != NULL);
        }
        void SetCUGInformation(Ro::CUGInformation* cugi)
        {
            m_roCUGInformation = cugi;
        }
        Ro::CUGInformation* GetCUGInformation()
        {
            return m_roCUGInformation;
        }
        void ClearCUGInformation()
        {
            if(m_roCUGInformation != NULL)
            {
                delete m_roCUGInformation;
                m_roCUGInformation = NULL;
            }
        }

        bool HasSubscriptionId()
        {
            return (m_roSubscriptionId != NULL);
        }
        void SetSubscriptionId(Ro::SubscriptionId* sid)
        {
            m_roSubscriptionId = sid;
        }
        Ro::SubscriptionId* GetSubscriptionId()
        {
            return m_roSubscriptionId;
        }
        void ClearSubscriptionId()
        {
            if(m_roSubscriptionId != NULL)
            {
                delete m_roSubscriptionId;
                m_roSubscriptionId = NULL;
            }
        }

        bool HasIMSChargingIdentifier()
        {
            return (m_imschargingidentifier != NULL);
        }
        Ro::IMSChargingIdentifier* GetIMSChargingIdentifier()
        {
            return m_imschargingidentifier;
        }
        void SetIMSChargingIdentifier(Ro::IMSChargingIdentifier* imsci)
        {
            m_imschargingidentifier = imsci;
        }
        void ClearIMSChargingIdentifier()
        {
            if(m_imschargingidentifier != NULL)
            {
                delete m_imschargingidentifier;
                m_imschargingidentifier = NULL;
            }
        }

        bool HasMscAddress()
        {
            return (m_capMscAddress != NULL);
        }
        cap_v3::ISDN_AddressString* GetMscAddress()
        {
            return m_capMscAddress;
        }
        void SetMscAddress(cap_v3::ISDN_AddressString* mscAddr)
        {
            m_capMscAddress = mscAddr;
        }
        void ClearMscAddress()
        {
            if (m_capMscAddress != NULL)
            {
                delete m_capMscAddress;
                m_capMscAddress = NULL;
            }
        }

        bool HasGmscAddress()
        {
            return (m_capGmscAddress != NULL);
        }
        cap_v3::ISDN_AddressString* GetGmscAddress()
        {
            return m_capGmscAddress;
        }
        void SetGmscAddress(cap_v3::ISDN_AddressString* callParNum)
        {
            m_capGmscAddress = callParNum;
        }
        void ClearGmscAddress()
        {
            if (m_capGmscAddress != NULL)
            {
                delete m_capGmscAddress;
                m_capGmscAddress = NULL;
            }
        }

        void SetCurrentCCAIResultCode(unsigned int resultCode) 
        {
            m_ccaInitialResultCode = resultCode;
        }
        unsigned int GetCurrentCCAIResultCode()
        {
            return m_ccaInitialResultCode;
        }

        void SetCurrentCCAUResultCode(unsigned int resultCode) 
        {
            m_ccaUpdateResultCode = resultCode;
        }
        unsigned int GetCurrentCCAUResultCode()
        {
            return m_ccaUpdateResultCode;
        }

        void SetCurrentCCATResultCode(unsigned int resultCode) 
        {
            m_ccaTerminateResultCode = resultCode;
        }
        unsigned int GetCurrentCCATResultCode()
        {
            return m_ccaTerminateResultCode;
        }

        void SetCurrentReceivedTcapContinue(bool bVal)
        {
            m_receivedTcapContinue = bVal;
        }
        bool IsCurrentReceivedTcapContinue()
        {
            return m_receivedTcapContinue;
        }

        void SetASRReceived(bool bVal)
        {
            m_reveivedASR = bVal;
        }
        bool IsASRReceived()
        {
            return m_reveivedASR;
        }

        void SetIDPSMSReceived(bool bVal)
        {
            m_isReceivedIDPSMS = bVal;
        }
        bool IsIDPSMSReceived()
        {
            return m_isReceivedIDPSMS;
        }

        bool IsTimeZoneBitSet()
        {
            return m_isTimeZoneBitSet;
        }
        void SetTimeZoneBit(bool bit)
        {
            m_isTimeZoneBitSet = bit;
        }

        void SetTimeZoneSeconds(uint32_t seconds) 
        {
            m_TimeZoneSeconds = seconds;
        }
        uint32_t GetTimeZoneSeconds()
        {
            return m_TimeZoneSeconds;
        }

        void SetCurrentCCAUMsccResultCode(unsigned int resultCode) 
        {
            m_ccaUpdateMsccResultCode = resultCode;
        }
        unsigned int GetCurrentCCAUMsccResultCode()
        {
            return m_ccaUpdateMsccResultCode;
        }

        void SetCurrentCCAMsccGrantedCCTimeZero(bool value) 
        {
            m_isccaMsccGrantedCCTimeZero = value;
        }
        unsigned int IsCurrentCCAMsccGrantedCCTimeZero()
        {
            return m_isccaMsccGrantedCCTimeZero;
        }

        void SetReleaseCallSent(bool value) 
        {
            m_isReleaseSent = value;
        }
        unsigned int IsReleaseCallSent()
        {
            return m_isReleaseSent;
        }

        void SetLastSentCCRequestType(unsigned int type)
        {
            m_lastSentCCRequestType = type;
        }

        unsigned int GetLastSentCCRequestType()
        {
            return m_lastSentCCRequestType;
        }

        void SetCCRequestNumber(unsigned int num)
        {   
            m_ccRequestNumber = num;
        }   

        unsigned int GetCCRequestNumber()
        {   
            return m_ccRequestNumber;
        } 

        void SetFirstERBReceived(bool bval)
        {
            m_isFirstERBrcvd = bval;
        }

        bool IsFirstERBrcvd()
        {
            return m_isFirstERBrcvd;
        }

        void SetReleaseCause(byte val)
        {   
            m_relCause = val;
        }   

        byte GetReleaseCause()
        {   
            return m_relCause;
        }   

        void SetOnlyERBinTCEndFlag(bool onlyERBinTC_End)
        {
            m_isOnlyERBInTcEnd = onlyERBinTC_End;
        }
        bool IsOnlyERBinTCEndFlagSet()
        {
            return m_isOnlyERBInTcEnd;
        }

        unsigned int GetServiceKey()
        {
            return m_servicekey;
        }

        void SetServiceKey(unsigned int value)
        {
            m_servicekey = value;
        }

        void SetUserName(std::string userName)
        {
            m_userName.assign(userName);
        }

        const std::string& GetUserName()
        {
            return m_userName;
        }
    private:
        bool m_bcsmEventflag;
        cap_v3::CallingPartyNumber *m_capCallingPartyNumber;
        int m_serviceIdentifier;
        bool m_receivedBasicService;
        Ro::UserSessionID *m_roUserSessId;
        Ro::IMSChargingIdentifier *m_imschargingidentifier;
        Ro::ServiceContextId *m_roServiceContextId;
        Ro::SubscriptionId *m_roSubscriptionId;
        Ro::CUGInformation *m_roCUGInformation;
        cap_v3::ISDN_AddressString *m_capMscAddress;
        cap_v3::ISDN_AddressString *m_capGmscAddress;
        unsigned int m_ccaInitialResultCode;
        unsigned int m_ccaUpdateResultCode;
        unsigned int m_ccaTerminateResultCode;
        bool m_receivedTcapContinue;
        bool m_reveivedASR;
        bool m_isReceivedIDPSMS;
        bool m_isTimeZoneBitSet;
        uint32_t m_TimeZoneSeconds;
        unsigned int m_ccaUpdateMsccResultCode;
        bool m_isccaMsccGrantedCCTimeZero;
        bool m_isReleaseSent;
        unsigned int m_lastSentCCRequestType;
        unsigned int m_ccRequestNumber;
        bool m_isFirstERBrcvd;
        byte m_relCause;
        bool m_isOnlyERBInTcEnd;
        unsigned int m_servicekey;
        std::string m_userName;
};

class CAPToRoHandler: public IwfTranslator
{
    public:
        CAPToRoHandler();
        virtual ~CAPToRoHandler();

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

        // parse the config details required for CAPToS6aHandler
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

        virtual int SetConfig(IwfTranslationDataConfig *req);

        virtual int DeleteConfig(IwfTranslationDataConfig *req);

        int InitialDPArg_To_CCR_Initial(IwfFsm *ctxt,
                const cap_v3::InitialDPArg *in,
                Ro::CreditControlRequest *out);

        template <class T> 
            void ConstructErrorAnswer(int error, 
                    T *out);

        virtual void BuildTCAPErrorCpt(IwfFsm *ctxt,
                DIA_BASE_CMD *cmd,
                TCAP_Component *&cpt);

        int BuildRRB(IwfFsm *ctxt,
                Ro::CreditControlAnswer *in,
                TCAP_Component *&cpt);

        int BuildACH(IwfFsm *ctxt,
                Ro::CreditControlAnswer *in,
                TCAP_Component *&cpt);

        int BuildContinue(IwfFsm *ctxt,
                Ro::CreditControlAnswer *in,
                TCAP_Component *&cpt);

        int BuildRelease(IwfFsm *ctxt,
                Ro::CreditControlAnswer *in,
                TCAP_Component *&cpt, byte causecode = NORMAL_UNSPECIFIED);

        virtual int BuildCCRTerminate(IwfFsm *ctxt,
                diameter::base::TerminationCause::Value causeCode ,
                DIA_BASE_CMD *&cmd);

        void CCA_Initial_to_RequestReportBCSMEvent(IwfFsm *ctxt,
                const Ro::CreditControlAnswer *in,
                cap_v3::RequestReportBCSMEventArg *out);

        void CCA_to_ApplyChargingArg(IwfFsm *ctxt,
                const Ro::CreditControlAnswer *in,
                cap_v3::ApplyChargingArg *out);

        void HandleCCAInitialErrorConditions(IwfFsm *ctxt, 
                Ro::CreditControlAnswer *cca, 
                TCAP_Component *&cpt,
                DIA_BASE_CMD *&outCmd,
                IwfReturnAction& ret);

        void HandleCCAUpdateErrorConditions(IwfFsm *ctxt, 
                Ro::CreditControlAnswer *cca, 
                TCAP_Component *&cpt,
                DIA_BASE_CMD *&outCmd,
                IwfReturnAction& ret);

        void HandleCCATerminateErrorConditions(IwfFsm *ctxt, 
                Ro::CreditControlAnswer *cca, 
                TCAP_Component *&cpt,
                DIA_BASE_CMD *&outCmd,
                IwfReturnAction& ret);

        void EventReportBCSM_to_CCR_Terminate( IwfFsm *ctxt,
                const cap_v3::EventReportBCSMArg *in,
                Ro::CreditControlRequest *out);

        void TranslateAcrToCcr(IwfFsm* ctxt,
                const cap_v3::CAMEL_CallResult *in,
                Ro::CreditControlRequest *out,
                IwfReturnAction& ret);

        void ConstructASA(IwfFsm *ctxt, 
                const diameter::base::AbortSessionRequest *in,
                diameter::base::AbortSessionAnswer *out);

        void ConstructRAA(IwfFsm *ctxt, 
                const diameter::base::ReAuthRequest *in,
                diameter::base::ReAuthAnswer *out);

        int InitialDPSMSArg_To_CCR_Initial(IwfFsm *ctxt,
                const cap_v3::InitialDPSMSArg *in,
                Ro::CreditControlRequest *out);

        void EventReportSMSArg_To_CCRT(IwfFsm* ctxt,
                const cap_v3::EventReportSMSArg *in,
                Ro::CreditControlRequest *out);

        void CCA_Initial_to_RequestReportSMSEvent(IwfFsm *ctxt,
                const Ro::CreditControlAnswer *in,
                cap_v3::RequestReportSMSEventArg *out);

        int BuildReleaseSMS(IwfFsm *ctxt,
                Ro::CreditControlAnswer *in,
                TCAP_Component *&cpt, byte causecode = NORMAL_UNSPECIFIED);

        int BuildContinueSMS(IwfFsm *ctxt,
                Ro::CreditControlAnswer *in,
                TCAP_Component *&cpt);

        int BuildRRBSMS(IwfFsm *ctxt,
                Ro::CreditControlAnswer *in,
                TCAP_Component *&cpt);

        int FillSDPMediaDescription(const uint8_t *tbcd, int len, std::stringstream &mediaName,
                std::stringstream &mediaDesc);

        int TimeStamp(const uint8_t *tbcd, int len, uint32_t &seconds, 
                CAPRoTransactionContext* userData);

        uint32_t ConstructTimeStamp(CAPRoTransactionContext* userData);

        void EncodeMsg(AsnObject* p, Octets** octets);

        void ReleaseSession(string &sessString, ITS_UINT sessIdx);

        virtual int SetTimerConfig(IwfTimersConfig *req);

        virtual int SetMsgSpecCfg(IwfProtocolActionConfig *req);
        
        virtual int DeleteMsgSpecCfg(IwfProtocolActionConfig *req);

        virtual int LogCDRData(IwfFsm *ctxt, ITS_UINT failureCause);

        virtual int TerminateSession(IwfFsm *ctxt,
                TCAP_Component *&outCpt, DIA_BASE_CMD *&outDiaCmd);
        
        virtual int OnUpstrmFinalReqSent(IwfFsm *ctxt);

        virtual ITS_UINT SetFeaturesConfig(IwfFeatureConfig *req);

        virtual ITS_UINT GetCDRConfig();

        virtual ITS_UINT GetCDRFailureCause(IwfFsm *iwfFsm);

        virtual ITS_INT HandleError(IwfFsm* inFsmCtxt,
                            DIA_BASE_CMD*& outCmd,
                            TCAP_Component*& outCpt,
                            IwfReturnAction& outRetAction)
        {
            outRetAction.action = IWF_RA_RESPOND_ONLY;
            return ITS_SUCCESS;
        }

    protected:

        ITS_LONG GetLastCAPOperation(IwfFsm *ctxt)
        {
            ITS_LONG opCode = 0;
            if( ctxt != NULL )
            { 
                TCAP_Component *cpt = ctxt->GetCurrRcvdTcapCpt();
                if (cpt)
                {
                    if (cpt->GetComponentType() == TCPPT_TC_INVOKE)
                    {
                        static_cast<TCAP_Invoke*>(cpt)->GetOperation(opCode);
                    }
                }
            }
            return opCode;
        }

        DiaCommandCode GetLastDiaOperation(IwfFsm *ctxt)
        {
            DiaCommandCode code = DIA_CMD_UNKNOWN;
            if( ctxt != NULL )
            {
                DIA_BASE_CMD* diaCmd = ctxt->GetCurrRcvdDiaMsg();
                if (diaCmd)
                {
                    code = (DiaCommandCode)diaCmd->getCommandCode();        
                }
            }

            return code;
        }

        void CheckEventTypeBCSMAndSetReleaseCause(IwfFsm *ctxt, cap_v3::EventTypeBCSM eventType);

        int CheckMSCCGrantedServiceUnitCCTime(Ro::CreditControlAnswer *cca);

        int CheckMSCCFinalUnitAction(Ro::CreditControlAnswer *cca);

        unsigned int GetMSCCResultCode(Ro::CreditControlAnswer *cca);

        unsigned int GetTerminationCauseCode(CAPRoTransactionContext* userData);

        int BuildBcsmEvent(cap_v3::EventTypeBCSM eventType, 
                cap_v3::MonitorMode monitorMode,
                std::string legid,
                cap_v3::BCSMEvent *bcsmEvent);

        template <class T> void BuildErrorResponse(TCAP_Error *tcapError, T *out);

        virtual void HandleTimeout(ETimerType& inTimerType, IwfFsm* inFsmCtxt,
                TCAP_Component* inTCAPCmpt, TCAP_Dialogue* inTCAPDlg,
                DIA_BASE_CMD*& outDiaCmd,
                TCAP_Component*& cpt,
                IwfReturnAction& outRetAction);

        virtual void StartTimerHandling(IwfFsm* ctxt,ETimerType inTimerType);

        void SetLocalTransId(ITS_CTXT dlgId, IwfFsm* ctxt);

        unsigned int IsOddIndicator(const unsigned char oddEvenField)
        { 
            unsigned int ret = oddEvenField >> 7;
            return ret;
        }


        CAPRoConfig m_config;
};

#endif // __IWF_PROT_CAP_CAP_H__
