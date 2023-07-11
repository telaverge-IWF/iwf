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

#ifndef __IWF_PROT_CAP_RO_TRANSATEL_H__
#define __IWF_PROT_CAP_RO__TRANSATELH__

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
#include <itu/cap_v3_imei.h>

#include <itu/cap_v1_initial_dp_arg.h>
#include <itu/cap_v1_bcsm_event.h>
#include <itu/cap_v1_event_type_bcsm.h>
#include <itu/cap_v1_request_report_bcsm_event_arg.h>
#include <itu/cap_v1_bcsm_event.h>
#include <itu/cap_v1_event_type_bcsm.h>
#include <itu/cap_v1_release_call_arg.h>
#include <itu/cap_v1_event_report_bcsm_arg.h>
#include <itu/cap_v1_connect_arg.h>




#include <itu/cap_v2_initial_dp_arg.h>
#include <itu/cap_v2_bcsm_event.h>
#include <itu/cap_v2_event_type_bcsm.h>
#include <itu/cap_v2_request_report_bcsm_event_arg.h>
#include <itu/cap_v2_apply_charging_arg.h>
#include <itu/cap_v2_apply_charging_report_arg.h>
#include <itu/cap_v2_camel_a_ch_billing_charging_characteristics.h>
#include <itu/cap_v2_bcsm_event.h>
#include <itu/cap_v2_event_type_bcsm.h>
#include <itu/cap_v2_release_call_arg.h>
#include <itu/cap_v2_event_report_bcsm_arg.h>
#include <itu/cap_v2_camel_call_result.h>
#include <itu/cap_v2_connect_arg.h>



#include <diameter/nasreq/NasreqAVP.h>
#include <diameter/dcca/DccaAVP.h>
#include <diameter/base/AbortSession.h>
#include <diameter/base/SessionTermination.h>
//#include <diameter/ro_r10/Ro_r10AVP.h>
#include<diameter/transatel_custom_avps/Transatel_custom_avpsAVP.h>
#include <diameter/ro_r10_transatel/Ro_r10_transatelAVP.h>
//#include <diameter/ro_r10/CreditControl.h>
#include <diameter/ro_r10_transatel/CreditControl.h>

//#include <diameter/ro_r10/ReAuth.h>
#include <diameter/base/ReAuth.h>

#include "iwf_fsm.h"
#include "iwf_config.h"
#include "iwf_prot_translator.h"

#include "iwf_prot_utils.h"
#include "iwf_cdr.h"
#include "iwf_dcca.h"
#include "iwf.pb.h"
#include "pbReplicationUtils.h"

/* Transatel specific Diameter Error Code */
#define DIAMETER_ERROR_CUSTOMER_NOT_FOUND 4014
#define DIAMETER_USER_UNKNOWN 5030

#define NORMAL_UNSPECIFIED 0x9f
#define NO_ROUTE_TO_DEST 0x83
#define CallingLegId "1"
#define CalledLegId "2"
#define NORMAL_CALL_CLEARING 0x90
#define USER_BUSY 0x91
#define NO_ANSWER_FROM_USER 0x93
#define CAUSE_LOCATION_USER 0x80
#define CAUSE_LOCATION_RLN 0x84
#define OPERATOR_DETERMINED_BARRING 0x08
#define MSCC_AVP_INDEX 0

#define DIA_TERM_CAUSE_INVALID_SCP_ACTION 98
#define DIA_TERM_CAUSE_NOT_CONTROLLED_CALL 99
#define DIA_TERM_CAUSE_INVALID_GSU_UNIT 97
#define DIA_TERM_CAUSE_INVALID_CONTROL_MODE 96

static int ccrnum = 0;

#define PROTOCOL_ERROR_UNSPECIFIED 0x6f
#define UNIDENTIFIED_SUBSCRIBER 0x1c
#define UNKNOWN_SUBSCRIBER 0x1e


#define BYTE_SIZE 8
#define NYBBLE_SIZE 4

#define BYTE_POS_0 0
#define BYTE_POS_1 1
#define BYTE_POS_2 2
#define BYTE_POS_3 3
#define BYTE_POS_4 4
#define BYTE_POS_5 5
#define BYTE_POS_6 6
#define BYTE_POS_7 7


#define SUB_STR_POS_0 0
#define SUB_STR_POS_2 2
#define SUB_STR_POS_4 4
#define SUB_STR_POS_5 5
#define SUB_STR_LEN_1 1
#define SUB_STR_LEN_2 2
#define SUB_STR_LEN_4 4
#define SUB_STR_LEN_5 5


#define DEFAULT_RP_CAUSE 0x15

#define DEFAULT_AT_TIMER 180
#define DEFAULT_AT_RETRY_COUNT 3
#define DEFAULT_AT_RESP_TIMEOUT 10
#define DECREMENT_AT_RETRY_COUNT(retryCount) (retryCount-1)

#define SWITCHOVER_DELTA_TIME 2


using namespace its;
using namespace cap_v3;
using namespace cap_v1;
using namespace cap_v2;

using namespace diameter::nasreq;
using namespace diameter::dcca;
namespace TransCustomAvp = diameter::transatel_custom_avps;
namespace Ro_TSL = diameter::ro_r10_transatel;

#if 0
struct StoredIDPSMSToCCRIData
{
    StoredIDPSMSToCCRIData()
        :callTypeVal(UNKNOWN),
        CAP_Service_Key(0),
        CAP_Dialed_Digits(""),
        CAP_Called_TON(TSLConstants::DEFAULT_INVALID_VAL),
        CAP_CLI(""),
        CAP_Location_Number(""),
        CAP_IMSI(""),
        CAP_VLR_Number(""),
        CAP_Call_Reference(""),
        CAP_MSC_Address(""),
        CAP_Called_NPI(TSLConstants::DEFAULT_INVALID_VAL),
        CAP_Calling_NOA(TSLConstants::DEFAULT_INVALID_VAL),
        CAP_CLI_NPI(TSLConstants::DEFAULT_INVALID_VAL),
        CAP_Version(TSLConstants::DEFAULT_INVALID_VAL),
        CAP_SMSC_Address(""),
        CAP_SGSN_Address(""),
        CAP_SM_IMEI(""),
        CAP_SM_StatusReportRequest(""),
        CAP_SM_UserDataHeaderIndicator(""),
        CAP_SM_ReplyPath(""),
        CAP_SM_VPFormat(""),
        CAP_SM_MessageTypeIndicator(""),
        CAP_SM_ProtocolID(""),
        CAP_SM_DCS(""),
        CAP_SM_ValidityPeriod(""),
        CAP_SM_RejectDuplicate(""),
        CAP_SCCP_CallingGT(""),
        CAP_SCCP_CalledGT(""),
        CAP_TCAP_Remote_Transaction_Id(""),
        CAP_TCAP_Local_Transaction_Id(""),
        CAP_CellID_AreaID_LAI(""),
        CAP_Event_Type_SMS(TSLConstants::DEFAULT_INVALID_VAL),
        CAP_TCAP_Error_Cause(TSLConstants::DEFAULT_TCAP_ERROR_CAUSE_VAL),
        CAP_SCCP_Error_Cause(0),
        m_totalGSUCCService(0),
        m_totalUSUCCService(0)
    {
    }
    Call_Type callTypeVal;
    unsigned int CAP_Service_Key;
    std::string CAP_Dialed_Digits;
    unsigned int CAP_Called_TON;
    std::string CAP_CLI;
    std::string CAP_Location_Number;
    std::string CAP_IMSI;
    std::string CAP_VLR_Number;
    std::string CAP_Call_Reference;
    std::string CAP_MSC_Address;
    unsigned int CAP_Called_NPI;
    unsigned int CAP_Calling_NOA;
    unsigned int CAP_CLI_NPI;
    unsigned int CAP_Version;
    std::string CAP_SMSC_Address;
    std::string CAP_SGSN_Address;
    std::string CAP_SM_IMEI;
    std::string CAP_SM_StatusReportRequest;
    std::string CAP_SM_UserDataHeaderIndicator;
    std::string CAP_SM_ReplyPath;
    std::string CAP_SM_VPFormat;
    std::string CAP_SM_MessageTypeIndicator;
    std::string CAP_SM_ProtocolID;
    std::string CAP_SM_DCS;
    std::string CAP_SM_ValidityPeriod;
    std::string CAP_SM_RejectDuplicate;
    std::string CAP_SCCP_CallingGT;
    std::string CAP_SCCP_CalledGT;
    std::string CAP_TCAP_Remote_Transaction_Id;
    std::string CAP_TCAP_Local_Transaction_Id;
    std::string CAP_CellID_AreaID_LAI;
    unsigned int CAP_Event_Type_SMS;
    unsigned int CAP_TCAP_Error_Cause;
    unsigned int CAP_SCCP_Error_Cause;
    std::string CAP_SMSpecificInfo;
    ITS_UINT m_totalGSUCCService;
    ITS_UINT m_totalUSUCCService;

};

//Structure to store the cap v2 & v1 IDP mapped CCR-I AVPvalues, which is
//retrieved for subsequent CCR-U or CCR-T msgs
//Below struct contains all sub AVPs of TSL CS-Information grouped AVP.
struct IDPToCCRIData
{
    Call_Type callTypeVal;
    unsigned int Service_Key;
    std::string Dialed_Digits;
    unsigned int Called_TON;
    std::string CLI;
    unsigned int Calling_Category;
    std::string Location_Number;
    std::string Redirecting_Number;
    unsigned int Redirecting_Indicator;
    unsigned int Original_Redirecting_Reason;
    unsigned int Redirection_Counter;
    unsigned int Redirecting_Reason;
    std::string IMSI;
    std::string VLR_Number;
    std::string Call_Reference;
    std::string MSC_Address;
    unsigned int Called_NPI;
    unsigned int Calling_NOA;
    unsigned int CLI_NPI;
    unsigned int CLIR;
    unsigned int Version;
    std::string SCCP_CallingGT;
    std::string SCCP_CalledGT;
    unsigned int GSM_Forwarding_Pending;
    std::string TCAP_Remote_Transaction_Id;
    std::string TCAP_Local_Transaction_Id;
    std::string CellID_AreaID_LAI;
    unsigned int Event_Type_BCSM;
    unsigned int TCAP_Error_Cause;
    unsigned int SCCP_Error_Cause;
    std::string GMSC;
    std::string Ext_Basic_Service_Code;
    std::string Bearer_Capability;
    std::string Bearer_Capability_Transfer;
    std::string Bearer_Capability_Transfer_Rate;
    std::string Bearer_Capability_Transfer_Mode;
    std::string Bearer_Capability_Cdr;
    bool CAPIsFollowingOn;

    IDPToCCRIData()
    {
        callTypeVal = UNKNOWN;
        Service_Key = 0;
        Dialed_Digits = "";
        Called_TON = TSLConstants::DEFAULT_INVALID_VAL;
        CLI = "";
        Location_Number = "";
        IMSI = "";
        VLR_Number = "";
        Call_Reference = "";
        MSC_Address = "";
        Called_NPI = TSLConstants::DEFAULT_INVALID_VAL;
        Calling_NOA = TSLConstants::DEFAULT_INVALID_VAL;
        CLI_NPI = TSLConstants::DEFAULT_INVALID_VAL;
        Version = TSLConstants::DEFAULT_INVALID_VAL;
        SCCP_CallingGT = "";
        SCCP_CalledGT = "";
        GSM_Forwarding_Pending = TSLConstants::DEFAULT_INVALID_VAL;
        TCAP_Remote_Transaction_Id = "";
        TCAP_Local_Transaction_Id = "";
        CellID_AreaID_LAI = "";
        Event_Type_BCSM = TSLConstants::DEFAULT_INVALID_VAL;
        TCAP_Error_Cause = TSLConstants::DEFAULT_TCAP_ERROR_CAUSE_VAL;
        SCCP_Error_Cause = TSLConstants::DEFAULT_INVALID_VAL;
        Calling_Category = TSLConstants::DEFAULT_INVALID_VAL;
        Redirecting_Number = "";
        Redirecting_Indicator = TSLConstants::DEFAULT_INVALID_VAL;
        Original_Redirecting_Reason = TSLConstants::DEFAULT_INVALID_VAL;
        Redirection_Counter = TSLConstants::DEFAULT_INVALID_VAL;
        Redirecting_Reason = TSLConstants::DEFAULT_INVALID_VAL;
        CLIR = TSLConstants::DEFAULT_INVALID_VAL;
        GMSC = "";
        Ext_Basic_Service_Code = "";
        Bearer_Capability = "";
        Bearer_Capability_Transfer = "";
        Bearer_Capability_Transfer_Rate = "";
        Bearer_Capability_Transfer_Mode = "";
        Bearer_Capability_Cdr = "";
        CAPIsFollowingOn = false;
    }

    Call_Type GetCallType();
    void SetCallType(Call_Type val);;
    unsigned int GetService_Key();
    void SetService_Key(unsigned int val);
    unsigned int GetCalled_TON();
    void SetCalled_TON(unsigned int val);
    unsigned int GetCalled_NPI();
    void SetCalled_NPI(unsigned int val);
    unsigned int GetCalling_NOA();
    void SetCalling_NOA(unsigned int val);
    unsigned int GetCLI_NPI();
    void SetCLI_NPI(unsigned int val);
    unsigned int GetVersion();
    void SetVersion(unsigned int val);
    unsigned int GetEvent_Type_BCSM();
    void SetEvent_Type_BCSM(unsigned int val);
    unsigned int GetTCAP_Error_Cause();
    void SetTCAP_Error_Cause(unsigned int val);
    unsigned int GetSCCP_Error_Cause();
    void SetSCCP_Error_Cause(unsigned int val);
    unsigned int GetCalling_Category();
    void SetCalling_Category(unsigned int val);
    unsigned int GetRedirecting_Indicator();
    void SetRedirecting_Indicator(unsigned int val);
    unsigned int GetOriginal_Redirecting_Reason();
    void SetOriginal_Redirecting_Reason(unsigned int val);
    unsigned int GetRedirection_Counter();
    void SetRedirection_Counter(unsigned int val);
    unsigned int GetRedirecting_Reason();
    void SetRedirecting_Reason(unsigned int val);
    unsigned int GetCLIR();
    void SetCLIR(unsigned int val);
    unsigned int GetGSM_Forwarding_Pending();
    void SetGSM_Forwarding_Pending(unsigned int val);
    std::string GetRedirecting_Number();
    void SetRedirecting_Number(std::string val);
    std::string GetGMSC();
    void SetGMSC(std::string val);
    std::string GetExt_Basic_Service_Code();
    void SetExt_Basic_Service_Code(std::string val);
    std::string GetBearer_Capability();
    void SetBearer_Capability(std::string val);
    std::string GetBearer_Capability_Transfer();
    void SetBearer_Capability_Transfer(std::string val);
    std::string GetBearer_Capability_Transfer_Rate();
    void SetBearer_Capability_Transfer_Rate(std::string val);
    std::string GetBearer_Capability_Transfer_Mode();
    void SetBearer_Capability_Transfer_Mode(std::string val);
    std::string GetDialed_Digits();
    void SetDialed_Digits(std::string val);
    std::string GetCLI();
    void SetCLI(std::string val);
    std::string GetLocation_Number();
    void SetLocation_Number(std::string val);
    std::string GetIMSI();
    void SetIMSI(std::string val);
    std::string GetVLR_Number();
    void SetVLR_Number(std::string val);
    std::string GetCall_Reference();
    void SetCall_Reference(std::string val);
    std::string GetMSC_Address();
    void SetMSC_Address(std::string val);
    std::string GetSCCP_CallingGT();
    void SetSCCP_CallingGT(std::string val);
    std::string GetSCCP_CalledGT();
    void SetSCCP_CalledGT(std::string val);
    std::string GetTCAP_Remote_Transaction_Id();
    void SetTCAP_Remote_Transaction_Id(std::string val);
    std::string GetTCAP_Local_Transaction_Id();
    void SetTCAP_Local_Transaction_Id(std::string val);
    std::string GetCellID_AreaID_LAI();
    void SetCellID_AreaID_LAI(std::string val);
    void SetBearerCapabilityForCdr(std::string val);
    std::string GetBearerCapabilityForCdr();
    void SetCAPIsFollowingOnSet(bool isFollowingOnSet);
    bool GetCAPIsFollowingOnSet();
};

struct ERBData
{
    unsigned int erbRecvEvtType;
    std::string eventSpecInfo;
    unsigned int recvlegId;
    unsigned int msgType;

    ERBData()
    {
        erbRecvEvtType = 0;
        eventSpecInfo = "";
        recvlegId = 0;
        msgType = 0;
    }
    std::string GetEvtSpecInfo();;
    void SetEvtSpecInfo(std::string val);
    unsigned int GetRecvEvntType();
    void SetRecvEvntType(unsigned int val);
    unsigned int GetRecvLegId();
    void SetRecvLegId(unsigned int val);
    unsigned int GetMsgType();
    void SetMsgType(unsigned int val);
    void ResetERBData();
};
#endif

struct TLegIDAndModeData
{
    string legId;
    int monitorMode;
};
struct TCAPV2Event_ArmData
{
    cap_v2::EventTypeBCSM eventType;
    std::vector<TLegIDAndModeData> legIdMonMode;
    TCAPV2Event_ArmData(){};
    TCAPV2Event_ArmData(cap_v2::EventTypeBCSM val)
    {
        eventType = val;
    }
};
struct TCAPV1Event_ArmData
{
    cap_v1::EventTypeBCSM eventType;
    std::vector<TLegIDAndModeData> legIdMonMode;
    TCAPV1Event_ArmData(){};
    TCAPV1Event_ArmData(cap_v1::EventTypeBCSM val)
    {
        eventType = val;
    }
};

struct TCAPV3SMSEvent_ArmData
{
    cap_v3::EventTypeSMS smsEvntType;
    std::vector<int> monitorMode;
    TCAPV3SMSEvent_ArmData(){};
    TCAPV3SMSEvent_ArmData(cap_v3::EventTypeSMS val)
    {
        smsEvntType = val;
    }

};

/*typedef union CapVersion
{
    TCAPV1Event_ArmData v1EventData;
    TCAPV2Event_ArmData v2EventData;
    TCAPV3SMSEvent_ArmData v3EventData;
}CapVersion_t;*/

/*typedef union CapVersion
{
    TCAPV3SMSEvent_ArmData v3EventData;
}CapVersion_t;*/

typedef vector<TCAPV1Event_ArmData> V1EventLst;
typedef vector<TCAPV2Event_ArmData> V2EventLst;
typedef vector<TCAPV3SMSEvent_ArmData> V3SMSEventLst;


//typedef boost::variant<TCAPV1Event_ArmData,TCAPV2Event_ArmData,TCAPV3SMSEvent_ArmData> Version;

//typedef boost::variant<Version,Version,Version> CallScenario_t;


typedef struct Callscenario
{
     V1EventLst MO_V1;
     V2EventLst MO_V2;
     V1EventLst MT_V1;
     V2EventLst MT_V2;
     V3SMSEventLst SMS_V3;
}CallScenario_t;

typedef vector<CallScenario_t> CallScenarioLst;

typedef map<string,CallScenarioLst> RRBRuleIdVsCallScenario;




struct ActivityTimerConfig
{
    ITS_UINT timerValue;
    ITS_UINT retryCount;
    ITS_UINT responseTimeout;

    ActivityTimerConfig(ITS_UINT time, ITS_UINT count, ITS_UINT responseTime)
    {
        timerValue = time;
        retryCount = count;
        responseTimeout = responseTime;
    }
};

#if 0
struct ActivityTimerData {
    ITS_UINT atTimer;
    ITS_UINT responseTimeout;
    ITS_UINT retryCount;
    ITS_OCTET invokeId;

    ActivityTimerData(ITS_UINT atTime, ITS_UINT responseTime,ITS_UINT count, ITS_OCTET ivkId)
    {
        atTimer = atTime;
        responseTimeout = responseTime;
        retryCount = count;
        invokeId = ivkId;
    }
};

#endif

// Populate the config
class CAPRoTSLConfig
{
    public:
        CAPRoTSLConfig()
            :m_voiceNoEventTimer(120),
            m_smsNoEventTimer(30),
            m_noAcrTimer(0),
            m_activityTimer(DEFAULT_AT_TIMER,DEFAULT_AT_RETRY_COUNT,DEFAULT_AT_RESP_TIMEOUT),
            m_smsServCtxtId(""),
            m_capv2MOCldPtyBusyEvnt(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_OCALLED_PARTY_BUSY),
            m_capv2MONoAnsEvnt(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_ONO_ANSWER),
            m_capv2MOAnsEvnt(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_OANSWER),
            m_capv2MODisconEvnt(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_ODISCONNECT),
            m_capv2MORouteSelFail(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_ROUTE_SELECT_FAILURE),
            m_capv2MTBusyEvnt(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TBUSY),
            m_capv2MTNoAnsEvnt(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TNO_ANSWER),
            m_capv2MTAnsEvnt(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TANSWER),
            m_capv2MTDisconEvnt(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TDISCONNECT),
            m_capv2MTAbandonEvt(cap_v2::EventTypeBCSM::EVENT_TYPE_BCSM_TABANDON),
            m_capv1MOAnsEvnt(cap_v1::EventTypeBCSM::EVENT_TYPE_BCSM_OANSWER),
            m_capv1MODisconEvnt(cap_v1::EventTypeBCSM::EVENT_TYPE_BCSM_ODISCONNECT),
            m_capv1MTAnsEvnt(cap_v1::EventTypeBCSM::EVENT_TYPE_BCSM_TANSWER),
            m_capv1MTDisconEvnt(cap_v1::EventTypeBCSM::EVENT_TYPE_BCSM_TDISCONNECT),
            m_smsReleaseCause(0),
            m_voiceReleaseCause(0),
            m_AnnNumberINN(0),
            m_AnnNumberNOA(0),
            m_AnnNumberNPI(0),
            m_DestNumberINN(0),
            m_DestNumberNOA(0),
            m_DestNumberNPI(0),
            m_ConnectCallMaxDuration(0),
            m_voiceRelCauseLoc(0),
            m_voiceRelCauseStd(0),
            m_voiceRelExtIndicator1(0),
            m_voiceRelExtIndicator2(0),
            m_GenNumberNQI(0),
            m_GenNumberNOA(0),
            m_GenNumberNII(0),
            m_GenNumberARI(0),
            m_GenNumberSCI(0),
            m_GenNumberNPI(0),
            m_RedirectNumberNOA(0),
            m_RedirectNumberNPI(0),
            m_RedirectNumberARI(0),
            m_OrgCldNumberNOA(0),
            m_OrgCldNumberNPI(0),
            m_OrgCldNumberARI(0),
            m_enableCdr(ENABLE_ONLY_FAILED_CALLS),
            m_includeTimeoutInCCTime(false),
            m_followOnTAnsTrigger(true),
            m_enableFollowOnSession(true)
    {
    }
        ~CAPRoTSLConfig()
        {
        }
        void Parse(Json::Value& val, IwfConfig& conf);

        void SetVoiceNoEventTimer(ITS_UINT value)
        {
            m_voiceNoEventTimer = value;
        }

        const ITS_UINT VoiceNoEventTimer() const
        {
            return m_voiceNoEventTimer;
        }

        void SetSmsNoEventTimer(ITS_UINT value)
        {
            m_smsNoEventTimer = value;
        }

        const ITS_UINT SmsNoEventTimer() const
        {
            return m_smsNoEventTimer;
        }

        void SetNoACRTimer(ITS_UINT value)
        {
            m_noAcrTimer = value;
        }

        const ITS_UINT NoACRTimer() const
        {
            return m_noAcrTimer;
        }

        void SetActivityTimer(ITS_UINT value)
        {
            m_activityTimer.timerValue = value;
        }

        const ActivityTimerConfig& ActivityTimer() const
        {
            return m_activityTimer;
        }

        void SetActivityRetryCount(ITS_UINT value)
        {
            m_activityTimer.retryCount = value;
        }

        void SetActivityResponseTimer(ITS_UINT value)
        {
            m_activityTimer.responseTimeout = value;
        }

        const std::string SMSServiceContextId() const
        {
            return m_smsServCtxtId;
        }
        void GetMOCAPV2_EventList(std::vector<TCAPV2Event_ArmData>& evntLst,std::string& rrbRuleId);
        void GetMTCAPV2_EventList(std::vector<TCAPV2Event_ArmData>& evntLst,std::string& rrbRuleId);
        void GetMOCAPV1_EventList(std::vector<TCAPV1Event_ArmData>& evntLst,std::string& rrbRuleId);
        void GetMTCAPV1_EventList(std::vector<TCAPV1Event_ArmData>& evntLst,std::string& rrbRuleId);
        void GetMOSMSCAPV3_EventList(std::vector<TCAPV3SMSEvent_ArmData>& evntLst, std::string& rrbRuleId);


        void SetReleaseCallCauseCode(ITS_UINT value)
        {
            m_voiceReleaseCause = value;
        }

        const ITS_UINT ReleaseCallCauseCode() const
        {
            return m_voiceReleaseCause;
        }

        void SetReleaseSmsCauseCode(ITS_UINT value)
        {
            m_smsReleaseCause = value;
        }

        const ITS_UINT ReleaseSmsCauseCode() const
        {
            return m_smsReleaseCause;
        }

        void SetAnnNoINN(ITS_UINT value)
        {
            m_AnnNumberINN = value;
        }

        const ITS_UINT GetAnnNoINN() const
        {
            return m_AnnNumberINN;
        }
        void SetAnnNoNOA(ITS_UINT value)
        {
            m_AnnNumberNOA = value;
        }

        const ITS_UINT GetAnnNoNOA() const
        {
            return m_AnnNumberNOA;
        }
        void SetAnnNoNPI(ITS_UINT value)
        {
            m_AnnNumberNPI = value;
        }

        const ITS_UINT GetAnnNoNPI() const
        {
            return m_AnnNumberNPI;
        }
        void SetDestNoINN(ITS_UINT value)
        {
            m_DestNumberINN = value;
        }

        const ITS_UINT GetDestNoINN() const
        {
            return m_DestNumberINN;;
        }
        void SetDestNoNOA(ITS_UINT value)
        {
            m_DestNumberNOA = value;
        }

        const ITS_UINT GetDestNoNOA() const
        {
            return m_DestNumberNOA;
        }
        void SetDestNoNPI(ITS_UINT value)
        {
            m_DestNumberNPI = value;
        }

        const ITS_UINT GetDestNoNPI() const
        {
            return m_DestNumberNPI;
        }

        void SetConnectMaxCallDuration(ITS_UINT value)
        {
            m_ConnectCallMaxDuration = value;
        }

        const ITS_UINT GetConnectMaxCallDuration() const
        {
            return m_ConnectCallMaxDuration;
        }

        const ITS_UINT GetGenericNumNQI() const
        {
            return m_GenNumberNQI;
        }

        const ITS_UINT GetGenericNumNOA() const
        {
            return m_GenNumberNOA;
        }

        const ITS_UINT GetGenericNumNII() const
        {
            return m_GenNumberNII;
        }

        const ITS_UINT GetGenericNumARI() const
        {
            return m_GenNumberARI;
        }

        const ITS_UINT GetGenericNumSCI() const
        {
            return m_GenNumberSCI;
        }

        const ITS_UINT GetGenericNumNPI() const
        {
            return m_GenNumberNPI;
        }

        const ITS_UINT GetRedirectNumNOA() const
        {
            return m_RedirectNumberNOA;
        }

        const ITS_UINT GetRedirectNumNPI() const
        {
            return m_RedirectNumberNPI;
        }

        const ITS_UINT GetRedirectNumARI() const
        {
            return m_RedirectNumberARI;
        }

        const ITS_UINT GetOrgCalledNumNOA() const
        {
            return m_OrgCldNumberNOA;
        }

        const ITS_UINT GetOrgCalledNumNPI() const
        {
            return m_OrgCldNumberNPI;
        }

        const ITS_UINT GetOrgCalledNumARI() const
        {
            return m_OrgCldNumberARI;
        }

        const ITS_UINT GetRelCauseLoc() const
        {
            return m_voiceRelCauseLoc;
        }

        const ITS_UINT GetRelCauseStd() const
        {
            return m_voiceRelCauseStd;
        }

        const ITS_UINT GetRelCauseExtIndicator1() const
        {
            return m_voiceRelExtIndicator1;
        }

        const ITS_UINT GetRelCauseExtIndicator2() const
        {
            return m_voiceRelExtIndicator2;
        }

        void SetCdrConfig(ITS_UINT value)
        {
            m_enableCdr = value;
        }

        ITS_UINT GetCdrConfig()
        {
            return m_enableCdr;
        }

        void SetFollowOnTAnsTrigger(bool value)
        {
            m_followOnTAnsTrigger = value;
        }

        bool GetFollowOnTAnsTrigger()
        {
            return m_followOnTAnsTrigger;
        }

        bool GetIncludeTimeoutInCCTimeConfig()
        {
            return m_includeTimeoutInCCTime;
        }

        void SetRRBRuleIdLst(RRBRuleIdVsCallScenario &rrbruleLst)
        {
            m_RRBRuleLst = rrbruleLst;
        }

        void InsertActionRuleVsCallScenMap(std::string& ActionRuleName, CallScenarioLst& callScenLst)
        {
            std::pair<string,CallScenarioLst> ruleCallScenListPair(ActionRuleName, callScenLst);
            m_RRBRuleLst.insert(ruleCallScenListPair);
        }

        void DeleteEntryFromActionRuleVsCallScenMap(std::string& ActionRuleName)
        {
            std::map<string,CallScenarioLst> ::iterator itr = m_RRBRuleLst.find(ActionRuleName);
            if(itr != m_RRBRuleLst.end())
            {
                m_RRBRuleLst.erase(itr);
            }
        }

        RRBRuleIdVsCallScenario& GetRRBRuleLst()
        {
            return m_RRBRuleLst;
        }

        void SetTriggerFollowOnSession(bool value)
        {
            m_enableFollowOnSession = value;
        }

        bool GetTriggerFollowOnSession()
        {
            return m_enableFollowOnSession;
        }

    protected:
        ITS_UINT m_voiceNoEventTimer;
        ITS_UINT m_smsNoEventTimer;
        ITS_UINT m_noAcrTimer;
        ActivityTimerConfig m_activityTimer;
        std::string m_smsServCtxtId;
        TCAPV2Event_ArmData m_capv2MOCldPtyBusyEvnt;
        TCAPV2Event_ArmData m_capv2MONoAnsEvnt;
        TCAPV2Event_ArmData m_capv2MOAnsEvnt;
        TCAPV2Event_ArmData m_capv2MODisconEvnt;
        TCAPV2Event_ArmData m_capv2MORouteSelFail;
        TCAPV2Event_ArmData m_capv2MTBusyEvnt;
        TCAPV2Event_ArmData m_capv2MTNoAnsEvnt;
        TCAPV2Event_ArmData m_capv2MTAnsEvnt;
        TCAPV2Event_ArmData m_capv2MTDisconEvnt;
        TCAPV2Event_ArmData m_capv2MTAbandonEvt;
        TCAPV1Event_ArmData m_capv1MOAnsEvnt;
        TCAPV1Event_ArmData m_capv1MODisconEvnt;
        TCAPV1Event_ArmData m_capv1MTAnsEvnt;
        TCAPV1Event_ArmData m_capv1MTDisconEvnt;
        ITS_UINT m_smsReleaseCause;
        ITS_UINT m_voiceReleaseCause;
        ITS_UINT m_AnnNumberINN;
        ITS_UINT m_AnnNumberNOA;
        ITS_UINT m_AnnNumberNPI;
        ITS_UINT m_DestNumberINN;
        ITS_UINT m_DestNumberNOA;
        ITS_UINT m_DestNumberNPI;
        ITS_UINT m_ConnectCallMaxDuration;
        ITS_UINT m_voiceRelCauseLoc;
        ITS_UINT m_voiceRelCauseStd;
        ITS_UINT m_voiceRelExtIndicator1;
        ITS_UINT m_voiceRelExtIndicator2;
        ITS_UINT m_GenNumberNQI;
        ITS_UINT m_GenNumberNOA;
        ITS_UINT m_GenNumberNII;
        ITS_UINT m_GenNumberARI;
        ITS_UINT m_GenNumberSCI;
        ITS_UINT m_GenNumberNPI;
        ITS_UINT m_RedirectNumberNOA;
        ITS_UINT m_RedirectNumberNPI;
        ITS_UINT m_RedirectNumberARI;
        ITS_UINT m_OrgCldNumberNOA;
        ITS_UINT m_OrgCldNumberNPI;
        ITS_UINT m_OrgCldNumberARI;
        ITS_UINT m_enableCdr;
        bool m_includeTimeoutInCCTime;
        bool m_followOnTAnsTrigger;
        RRBRuleIdVsCallScenario m_RRBRuleLst;
        bool m_enableFollowOnSession;
};

class TransatelCAPRoTransactionContext:public StoredUserData
{
    public:
        TransatelCAPRoTransactionContext(pbCapRoTsl* caprotsl):m_pbCapRoTsl(caprotsl),
             m_roSubscriptionId(NULL),
             m_isRetransmitReq(false)
    {
    }
#if 0
        TransatelCAPRoTransactionContext()
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
            m_isReceivedIDP(false),
            m_isTimeZoneBitSet(false),
            m_TimeZoneSeconds(0),
            m_ccaUpdateMsccResultCode(0),
            m_isccaMsccGrantedCCTimeZero(false),
            m_isReleaseSent(false),
            m_lastSentCCRequestType(0),
            m_ccRequestNumber(0),
            m_isFirstERBrcvd(0),
            m_relCause(0x15),
            m_callType(UNKNOWN),
            m_scpAction(0),
            m_origScpAction(0),
            m_capControlMode(-1),
            m_terminationCause(0),
            m_recvAppContextName(cap::UNKNOWN),
            m_recvGSUCCTime(0),
            m_recvNoAnsTime(0),
            m_currUSUCCTime(0),
            m_cumulativeGSUCCTime(0),
            m_cumulativeUSUCCTime(0),
            m_bIsFinalUnitsReceived(false),
            m_callAnswerTimeStamp(0),
            m_isFollowingOn(false),
            m_activityTimerData(0, 0, 0, 0),
            m_strRemoteTransIdForCDR(""),
            m_strLocalTransIdForCDR(""),
            m_bIsContinueCallSet(false),
            m_sessionStartTime(0),
            m_connectMaxDuration(0),
            m_erbAnswerTimeStamp(0),
            m_erbSpecificInfo(""),
            m_isFailedCDRLogged(false)
    {
    }
        ~TransatelCAPRoTransactionContext()
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
#endif
        /*bool HasCallingPartyNumber()
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
        }*/
        ~TransatelCAPRoTransactionContext()
        {
            this->ClearSubscriptionId();
        }

        void SetBcsmEventMO(bool bcsmflag)
        {
            m_pbCapRoTsl->set_bcsmeventflag(bcsmflag);
        }
        bool GetBcsmEventMO()
        {
            return m_pbCapRoTsl->bcsmeventflag();
        }

        void SetServiceIdentifier(int si)
        {
            m_pbCapRoTsl->set_serviceidentifier(si);
        }
        int GetServiceIdentifier()
        {
            return m_pbCapRoTsl->serviceidentifier();
        }

        void SetBasicServiceReceived(bool bVal)
        {
            m_pbCapRoTsl->set_receivedbasicservice(bVal);
        }
        bool IsBasicServiceReceived()
        {
            return m_pbCapRoTsl->receivedbasicservice();
        }

        /*bool HasUserSessionId()
        {
            return (m_roUserSessId != NULL);
        }
        Ro_TSL::UserSessionID* GetUserSessionID()
        {
            return m_roUserSessId;
        }
        void SetUserSessionID(Ro_TSL::UserSessionID* usrSessId)
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
        }*/
        void SetOriginalSCPAction(int scpaction)
        {
            m_pbCapRoTsl->set_orgscpaction(scpaction);
        }

        int GetOriginalSCPAction()
        {
            return m_pbCapRoTsl->orgscpaction();
        }
        void SetSCPAction(int scpaction)
        {
            m_pbCapRoTsl->set_scpaction(scpaction);
        }

        int GetSCPAction()
        {
            return m_pbCapRoTsl->scpaction();
        }

        void SetCAPControlMode(int mode)
        {
            m_pbCapRoTsl->set_capcontrolmode(mode);
        }

        signed int GetCAPControlMode()
        {
            return m_pbCapRoTsl->capcontrolmode();
        }

        bool HasServiceContextId()
        {
            return m_pbCapRoTsl->has_roservicecontextid();
        }
        void SetServiceContextId(std::string scid)
        {
            m_pbCapRoTsl->set_roservicecontextid(scid);
        }
        std::string GetServiceContextId()
        {
            return m_pbCapRoTsl->roservicecontextid();
        }

        /*bool HasCUGInformation()
        {
            return (m_roCUGInformation != NULL);
        }
        void SetCUGInformation(Ro_TSL::CUGInformation* cugi)
        {
            m_roCUGInformation = cugi;
        }
        Ro_TSL::CUGInformation* GetCUGInformation()
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
        }*/

        bool HasSubscriptionId()
        {
            return (m_roSubscriptionId != NULL);
        }
        void SetSubscriptionId(Ro_TSL::SubscriptionId* sid)
        {
            m_roSubscriptionId = sid;
        }
        Ro_TSL::SubscriptionId* GetSubscriptionId()
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

        /*bool HasIMSChargingIdentifier()
        {
            return (m_imschargingidentifier != NULL);
        }
        Ro_TSL::IMSChargingIdentifier* GetIMSChargingIdentifier()
        {
            return m_imschargingidentifier;
        }
        void SetIMSChargingIdentifier(Ro_TSL::IMSChargingIdentifier* imsci)
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
        }*/

        void SetCurrentCCAIResultCode(unsigned int resultCode)
        {
            m_pbCapRoTsl->set_ccainitialresultcode(resultCode);
        }
        unsigned int GetCurrentCCAIResultCode()
        {
            return m_pbCapRoTsl->ccainitialresultcode();
        }

        void SetCurrentCCAUResultCode(unsigned int resultCode)
        {
            m_pbCapRoTsl->set_ccaupdateresultcode(resultCode);
        }
        unsigned int GetCurrentCCAUResultCode()
        {
            return m_pbCapRoTsl->ccaupdateresultcode();
        }

        void SetCurrentCCATResultCode(unsigned int resultCode)
        {
            m_pbCapRoTsl->set_ccaterminateresultcode(resultCode);
        }
        unsigned int GetCurrentCCATResultCode()
        {
            return m_pbCapRoTsl->ccaterminateresultcode();
        }

        void SetCurrentReceivedTcapContinue(bool bVal)
        {
            m_pbCapRoTsl->set_receivedtcapcontinue(bVal);
        }
        bool IsCurrentReceivedTcapContinue()
        {
            return m_pbCapRoTsl->receivedtcapcontinue();
        }

        void SetASRReceived(bool bVal)
        {
            m_pbCapRoTsl->set_receivedasr(bVal);
        }
        bool IsASRReceived()
        {
            return m_pbCapRoTsl->receivedasr();
        }

        void SetIDPSMSReceived(bool bVal)
        {
            m_pbCapRoTsl->set_receivedidpsms(bVal);
        }
        bool IsIDPSMSReceived()
        {
            return m_pbCapRoTsl->receivedidpsms();
        }

        void SetIDPReceived(bool bVal)
        {
            m_pbCapRoTsl->set_receivedidp(bVal);
        }
        bool IsIDPReceived()
        {
            return m_pbCapRoTsl->receivedidp();
        }

        bool IsTimeZoneBitSet()
        {
            return m_pbCapRoTsl->istimezoneseconds();
        }
        void SetTimeZoneBit(bool bit)
        {
            m_pbCapRoTsl->set_istimezoneseconds(bit);
        }

        void SetTimeZoneSeconds(uint32_t seconds)
        {
            m_pbCapRoTsl->set_timezoneseconds(seconds);
        }
        uint32_t GetTimeZoneSeconds()
        {
            return m_pbCapRoTsl->timezoneseconds();
        }

        void SetCurrentCCAUMsccResultCode(unsigned int resultCode)
        {
            m_pbCapRoTsl->set_ccaupdatemsccresultcode(resultCode);
        }
        unsigned int GetCurrentCCAUMsccResultCode()
        {
            return m_pbCapRoTsl->ccaupdatemsccresultcode();
        }

        void SetCurrentCCAMsccGrantedCCTimeZero(bool value)
        {
            m_pbCapRoTsl->set_isccamsccgrantedcctimezero(value);
        }
        unsigned int IsCurrentCCAMsccGrantedCCTimeZero()
        {
            return m_pbCapRoTsl->isccamsccgrantedcctimezero();
        }

        void SetCapReleaseSent(bool value)
        {
            m_pbCapRoTsl->set_isreleasesent(value);
        }
        unsigned int IsCapReleaseSent()
        {
            return m_pbCapRoTsl->isreleasesent();
        }

        void SetLastSentCCRequestType(unsigned int type)
        {
            m_pbCapRoTsl->set_lastsentccrequesttype(type);
        }

        unsigned int GetLastSentCCRequestType()
        {
            return m_pbCapRoTsl->lastsentccrequesttype();
        }

        void SetCCRequestNumber(unsigned int num)
        {
            m_pbCapRoTsl->set_ccrequestnumber(num);
        }

        unsigned int GetCCRequestNumber()
        {
            return m_pbCapRoTsl->ccrequestnumber();
        }

        void SetFirstERBReceived(bool bval)
        {
            m_pbCapRoTsl->set_isfirsterbrcvd(bval);
        }

        bool IsFirstERBrcvd()
        {
            return m_pbCapRoTsl->isfirsterbrcvd();
        }

        void SetReleaseCause(byte val)
        {
            m_pbCapRoTsl->set_releasecause(val);
        }

        byte GetReleaseCause()
        {
            return m_pbCapRoTsl->releasecause();
        }

        bool IsCCRTBuiltForInvalidCCAI()
        {
            return m_pbCapRoTsl->isccrtbuiltforinvalidccai();
        }

        void SetCCRTBuiltForInvalidCCAI(bool val)
        {
            m_pbCapRoTsl->set_isccrtbuiltforinvalidccai(val);
        }

        void SetTerminationCause(int val)
        {
            m_pbCapRoTsl->set_terminationcause(val);
        }

        int GetTerminationCause()
        {
            return m_pbCapRoTsl->terminationcause();
        }

        Call_Type GetCallType()
        {
            return (Call_Type)m_pbCapRoTsl->calltype();
        }

        void SetCallType(Call_Type val)
        {
            m_pbCapRoTsl->set_calltype(val);
        }
        void SetStoredIDPSMSToCCRIData(StoredIDPSMSToCCRIData val)
        {
            if(m_pbCapRoTsl->has_mappedidptoccridata())
            {
                m_pbCapRoTsl->clear_mappedidptoccridata();
            }
            StoredIDPSMSToCCRIData *storedIDPSMSToCCRIData = m_pbCapRoTsl->mutable_mappedidptoccridata();
            storedIDPSMSToCCRIData->CopyFrom(val);
        }
        StoredIDPSMSToCCRIData GetStoredIDPSMSToCCRIData()
        {
            return m_pbCapRoTsl->mappedidptoccridata();
        }
        void SetRecvAppCtxt(cap::CAP_AC val)
        {
            m_pbCapRoTsl->set_recvappcontextname(val);
        }
        cap::CAP_AC GetRecvAppCtxt()
        {
            return (cap::CAP_AC)m_pbCapRoTsl->recvappcontextname();
        }
        IDPToCCRIData GetIDPToCCRIData()
        {
            return m_pbCapRoTsl->idpccridata();
        }
        void SetIDPToCCRIData(IDPToCCRIData val)
        {
            if(m_pbCapRoTsl->has_idpccridata())
            {
                m_pbCapRoTsl->clear_idpccridata();
            }
            IDPToCCRIData *idpToCCRIData = m_pbCapRoTsl->mutable_idpccridata();
            idpToCCRIData->CopyFrom(val);
        }

        unsigned int GetGSUCCTime()
        {
            return m_pbCapRoTsl->recvgsucctime();
        }

        void SetGSUCCTime(const unsigned int& val)
        {
            m_pbCapRoTsl->set_recvgsucctime(val);
        }

        unsigned int GetCumulativeGSUCCTime()
        {
            return m_pbCapRoTsl->cumulativegsucctime();
        }

        void SetCumulativeGSUCCTime(const unsigned int& val)
        {
            m_pbCapRoTsl->set_cumulativegsucctime(m_pbCapRoTsl->cumulativegsucctime() + val);
        }

        void ResetCumulativeGSUCCTime()
        {
            m_pbCapRoTsl->clear_cumulativegsucctime();
        }

        unsigned int GetNoAnsTime()
        {
            return m_pbCapRoTsl->recvnoanstime();
        }

        void SetNoAnsTime(const unsigned int& val)
        {
            m_pbCapRoTsl->set_recvnoanstime(val);
        }

        unsigned int GetUSUCCTime()
        {
            return m_pbCapRoTsl->currusucctime();
        }

        void SetUSUCCTime(const unsigned int& val)
        {
            m_pbCapRoTsl->set_currusucctime(val);
        }
        const pbERBData& GetERBData()
        {
            return m_pbCapRoTsl->recverbdata();
        }
        void ClearERBData()
        {
            m_pbCapRoTsl->clear_recverbdata();
        }
        void SetERBData(pbERBData& val)
        {
            if(m_pbCapRoTsl->has_recverbdata())
            {
                m_pbCapRoTsl->clear_recverbdata();
            }
            pbERBData *pbERBData = m_pbCapRoTsl->mutable_recverbdata();
            pbERBData->CopyFrom(val);
        }

        bool HasERBData()
        {
            return m_pbCapRoTsl->has_recverbdata();
        }

        uint32_t GetCallAnsTimeStamp()
        {
            return m_pbCapRoTsl->callanswertimestamp();
        }

        void SetCallAnsTimeStamp(const uint32_t& val)
        {
            m_pbCapRoTsl->set_callanswertimestamp(val);
        }

        void SetIsFinalUnitsReceived(bool val)
        {
            m_pbCapRoTsl->set_isfinalunitreceived(val);
        }

        bool GetIsFinalUnitsReceived()
        {
            return m_pbCapRoTsl->isfinalunitreceived();
        }

        void SetIsFollowingOn(bool val)
        {
            m_pbCapRoTsl->set_isfollowingon(val);
        }

        bool IsFollowingOnSet()
        {
            return m_pbCapRoTsl->isfollowingon();
        }

        void SetTriggerFollowOnSession(bool value)
        {
            m_pbCapRoTsl->set_triggerfollowonsession(value);
        }

        bool GetTriggerFollowOnSession()
        {
            return m_pbCapRoTsl->triggerfollowonsession();
        }

        const pbActivityTimerData& GetActivityTimerData()
        {
            return m_pbCapRoTsl->activitytimerdata();
        }
        /* Invoke this function only first time invoking of Activity timer */
        void SetActivityTimerData(pbActivityTimerData& val)
        {
            if(m_pbCapRoTsl->has_activitytimerdata())
            {
                m_pbCapRoTsl->clear_activitytimerdata();
            }
            pbActivityTimerData *pbActTimerData = m_pbCapRoTsl->mutable_activitytimerdata();
            pbActTimerData->CopyFrom(val);
        }

        void SetRemoteTransIdForCDR(string& val)
        {
           m_pbCapRoTsl->set_strremotetransidforcdr(val);
        }
        string GetRemoteTransIdForCDR()
        {
            return const_cast<std::string &> (m_pbCapRoTsl->strremotetransidforcdr());
        }

        void SetLocalTransIdForCDR(string& val)
        {
            m_pbCapRoTsl->set_strlocaltransidforcdr(val);
        }
        string GetLocalTransIdForCDR()
        {
            return const_cast<std::string &> (m_pbCapRoTsl->strlocaltransidforcdr());
        }
        void SetContinueCall(bool bVal)
        {
            m_pbCapRoTsl->set_biscallcontinueset(bVal);
        }
        bool IsContinueCallSet()
        {
            return m_pbCapRoTsl->biscallcontinueset();
        }

        void SetSessionStartTime(ITS_UINT val)
        {
            m_pbCapRoTsl->set_sessionstarttimestamp(val);
        }
        ITS_UINT SessionStartTime()
        {
            return m_pbCapRoTsl->sessionstarttimestamp();
        }

        unsigned int GetConnectMaxDuration()
        {
            return m_pbCapRoTsl->connectmaxduration();
        }

        void SetConnectMaxDuration(const unsigned int& val)
        {
            m_pbCapRoTsl->set_connectmaxduration(val);
        }

        void SetErbAnswerTimeStamp(ITS_UINT val)
        {
            m_pbCapRoTsl->set_erbanswertimestamp(val);
        }
        ITS_UINT ErbAnswerTimeStamp()
        {
            return m_pbCapRoTsl->erbanswertimestamp();
        }

        void SetErbSpecificInfoForCDR(string& val)
        {
           m_pbCapRoTsl->set_erbspecificinfo(val);
        }
        string& GetErbSpecificInfoForCDR()
        {
            return const_cast<std::string &> (m_pbCapRoTsl->erbspecificinfo());
        }

        IwfDccaSessionCtxt& GetDccaContext()
        {
            return m_dccaCtxt;
        }


        void ReplicateDccaCtxt()
        {
            pbIwfDccaSessionCtxt* dccaCtxt = m_pbCapRoTsl->mutable_dccactxt();
            dccaCtxt->CopyFrom(m_dccaCtxt.GetDccaReplicableData());
        }

        void SetFailedCDRLogged(bool bVal)
        {
            m_pbCapRoTsl->set_isfailedcdrlogged(bVal);
        }
        bool IsFailedCDRLogged()
        {
            return m_pbCapRoTsl->isfailedcdrlogged();
        }

        void SetTranslatorState(TransState state)
        {
            m_pbCapRoTsl->set_currstate(state);
        }

        TransState GetTranslatorState()
        {
            return m_pbCapRoTsl->currstate();
        }
        /*

        pbCapRoTsl& GetReplicableData()
        {
           return m_pbCapRoTsl;
        }
        */

        pbCapRoTsl* GetCapRoTslData()
        {
            return m_pbCapRoTsl;
        }

        pbConnectArgData GetConnectArgData()
        {
            return m_pbCapRoTsl->connectarg();
        }

        void SetConnectArgData(pbConnectArgData val)
        {
            if(m_pbCapRoTsl->has_connectarg())
            {
                m_pbCapRoTsl->clear_connectarg();
            }
            pbConnectArgData* connectArgData = m_pbCapRoTsl->mutable_connectarg();
            connectArgData->CopyFrom(val);
        }

        pbACHData GetACHData()
        {
            return m_pbCapRoTsl->achdata();
        }

        void SetACHData(pbACHData val)
        {
            if(m_pbCapRoTsl->has_achdata())
            {
                m_pbCapRoTsl->clear_achdata();
            }
            pbACHData* achData = m_pbCapRoTsl->mutable_achdata();
            achData->CopyFrom(val);
        }

        void EnabledRetransmission(bool value)
        {
            m_isRetransmitReq = value;
        }

        bool IsRetransmissionEnabled()
        {
            return m_isRetransmitReq;
        }

        uint32_t GetDisconTriggerTimeStamp()
        {
            return m_pbCapRoTsl->discontriggertimestamp();
        }

        void SetDisconTriggerTimeStamp(const uint32_t& val)
        {
            if ( m_pbCapRoTsl->has_discontriggertimestamp())
            {
                 m_pbCapRoTsl->clear_discontriggertimestamp();
            }
            m_pbCapRoTsl->set_discontriggertimestamp(val);
        }

        void ClearDisconTriggerTimeStamp()
        {
            if (m_pbCapRoTsl->has_discontriggertimestamp())
            {
                m_pbCapRoTsl->clear_discontriggertimestamp();
            }
        }

        void SetCcfhFailedoverReason(uint32_t reason)
        {
            if (m_pbCapRoTsl->has_ccfhfailedoverreason())
            {
                m_pbCapRoTsl->clear_ccfhfailedoverreason();
            }
            m_pbCapRoTsl->set_ccfhfailedoverreason(reason);
        }

        uint32_t GetUpdateTriggerTimeStamp()
        {
            return m_pbCapRoTsl->updatetriggertimestamp();
        }

        void SetUpdateTriggerTimeStamp(const uint32_t& val)
        {
            if ( m_pbCapRoTsl->has_updatetriggertimestamp())
            {
                 m_pbCapRoTsl->clear_updatetriggertimestamp();
            }
            m_pbCapRoTsl->set_updatetriggertimestamp(val);
        }

        void ClearUpdateTriggerTimeStamp()
        {
            if (m_pbCapRoTsl->has_updatetriggertimestamp())
            {
                m_pbCapRoTsl->clear_updatetriggertimestamp();
            }
        }
        uint32_t GetCcfhFailedoverReason()
        {
            return m_pbCapRoTsl->ccfhfailedoverreason();
        }

    private:
#if 0
        bool m_bcsmeventflag;
        //cap_v3::callingpartynumber *m_capcallingpartynumber;
        int m_serviceidentifier;
        bool m_receivedbasicservice;
        //ro_tsl::usersessionid *m_rousersessid
        //ro_tsl::imschargingidentifier *m_imschargingidentifier;
        //ro_tsl::cuginformation *m_rocuginformation;
        //cap_v3::isdn_addressstring *m_capmscaddress;
        //cap_v3::isdn_addressstring *m_capgmscaddress;
        unsigned int m_ccainitialresultcode;
        unsigned int m_ccaupdateresultcode;
        unsigned int m_ccaterminateresultcode;
        bool m_receivedtcapcontinue;
        bool m_reveivedasr;
        bool m_isreceivedidpsms;
        bool m_isreceivedidp;
        bool m_istimezonebitset;
        uint32_t m_timezoneseconds;
        unsigned int m_ccaupdatemsccresultcode;
        bool m_isccamsccgrantedcctimezero;
        bool m_isreleasesent;
        unsigned int m_lastsentccrequesttype;
        unsigned int m_ccrequestnumber;
        bool m_isfirsterbrcvd;
        byte m_relcause;
        call_type m_calltype;
        int m_scpaction;
        int m_origscpaction;
        signed int m_capcontrolmode;
        int m_terminationcause;
        storedidpsmstoccridata m_mappedidptoccridata;
        cap::cap_ac m_recvappcontextname;
        idptoccridata m_idpccridata;
        unsigned int m_recvgsucctime;
        unsigned int m_recvnoanstime;
        unsigned int m_currusucctime;
        unsigned int m_cumulativegsucctime;
        unsigned int m_cumulativeusucctime;
        bool m_bisfinalunitsreceived;
        erbdata m_recvfirsterbdata;
        erbdata m_recverbdata;
        uint32_t m_callanswertimestamp;
        bool m_isfollowingon;
        activitytimerdata m_activitytimerdata;
        string m_strremotetransidforcdr;
        string m_strlocaltransidforcdr;
        bool m_biscontinuecallset;
        its_uint m_sessionstarttime;
        unsigned int m_connectmaxduration;
        its_uint m_erbanswertimestamp;
        std::string m_erbspecificInfo;
        IwfDccaSessionCtxt m_dccaCtxt;
        bool m_isFailedCDRLogged;
#endif
        //Ro_TSL::ServiceContextId *m_roServiceContextId;
        pbCapRoTsl* m_pbCapRoTsl;
        Ro_TSL::SubscriptionId *m_roSubscriptionId;
        IwfDccaSessionCtxt m_dccaCtxt;
        bool m_isRetransmitReq;
};

class TransatelCAPToRoHandler: public IwfTranslator
{
    public:
        TransatelCAPToRoHandler();
        virtual ~TransatelCAPToRoHandler();

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

	    virtual int SetTimerConfig(IwfTimersConfig *req);

        virtual int SetMsgSpecCfg(IwfProtocolActionConfig *req);

        virtual int DeleteMsgSpecCfg(IwfProtocolActionConfig *req);

        int InitialDPArg_To_CCR_Initial(IwfFsm *ctxt,
                const cap_v3::InitialDPArg *in,
                Ro_TSL::CreditControlRequest *out);

        template <class T>
            void ConstructErrorAnswer(int error,
                    T *out);

        virtual void BuildTCAPErrorCpt(IwfFsm *ctxt,
                DIA_BASE_CMD *cmd,
                TCAP_Component *&cpt);

        int BuildRRB(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer *in,
                TCAP_Component *&cpt);

        int BuildConnect(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer *in,
                TCAP_Component *&cpt);

        int BuildACH(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer *in,
                TCAP_Component *&cpt);

        int BuildContinue(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer *in,
                TCAP_Component *&cpt);

        int BuildRelease(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer *in,
                TCAP_Component *&cpt, byte causecode = NORMAL_UNSPECIFIED);

        int BuildCCRTerminateForIDPSMS(IwfFsm *ctxt,
                diameter::base::TerminationCause::Value causeCode ,
                DIA_BASE_CMD *&cmd);

        int BuildCCRTerminateForIDP(IwfFsm *ctxt,
                diameter::base::TerminationCause::Value causeCode ,
                DIA_BASE_CMD *&cmd, uint32_t ccTime = 0);

        //void CCA_Initial_to_RequestReportBCSMEvent(IwfFsm *ctxt,
        //        const Ro_TSL::CreditControlAnswer *in,
        //        RequestReportBCSMEventArg *out);
        void CCA_Initial_to_V2RequestReportBCSMEvent(Call_Type callTypeVal,
                                                               cap_v2::RequestReportBCSMEventArg& rrbArg,
                                                               unsigned int uiNoAnsTimeout,
                                                               std::string rrbRuleId);

        void CCA_Initial_to_V1RequestReportBCSMEvent(Call_Type callTypeVal,
                                                     cap_v1::RequestReportBCSMEventArg& rrbArg,
                                                     std::string rrbRuleId);


        int BuildBcsmEvent(cap_v1::EventTypeBCSM eventType,
                           cap_v1::MonitorMode monitorMode,
                           std::string legid,
                           cap_v1::BCSMEvent *bcsmEvent);

        void CCA_to_ApplyChargingArg(IwfFsm *ctxt,
                const Ro_TSL::CreditControlAnswer *in,
                cap_v2::ApplyChargingArg *out);

        void HandleCCAInitialErrorConditions(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer *cca,
                TCAP_Component *&cpt,
                DIA_BASE_CMD *&outCmd,
                IwfReturnAction& ret);

        void HandleCCAUpdateErrorConditions(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer *cca,
                TCAP_Component *&cpt,
                DIA_BASE_CMD *&outCmd,
                IwfReturnAction& ret);

        void HandleCCATerminateErrorConditions(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer *cca,
                TCAP_Component *&cpt,
                DIA_BASE_CMD *&outCmd,
                IwfReturnAction& ret);

        void EventReportBCSM_to_CCR_Terminate( IwfFsm *ctxt,
                const cap_v3::EventReportBCSMArg *in,
                Ro_TSL::CreditControlRequest *out);

        void TranslateAcrToCcr(IwfFsm* ctxt,
                const cap_v2::CAMEL_CallResult *in,
                Ro_TSL::CreditControlRequest *out,
                IwfReturnAction& ret);

        void ConstructASA(IwfFsm *ctxt,
                const diameter::base::AbortSessionRequest *in,
                diameter::base::AbortSessionAnswer *out);

        void ConstructRAA(IwfFsm *ctxt,
                const diameter::base::ReAuthRequest *in,
                diameter::base::ReAuthAnswer *out);

        int InitialDPSMSArg_To_CCR_Initial(IwfFsm *ctxt,
                const cap_v3::InitialDPSMSArg *in,
                Ro_TSL::CreditControlRequest *out);

        void EventReportSMSArg_To_CCRT(IwfFsm* ctxt,
                const cap_v3::EventReportSMSArg *in,
                Ro_TSL::CreditControlRequest *out);

        void CCA_Initial_to_RequestReportSMSEvent(IwfFsm *ctxt,
                const Ro_TSL::CreditControlAnswer *in,
                cap_v3::RequestReportSMSEventArg *out,
                std::string rrbRuleId);

        void CCA_Initial_to_ConnectV2(IwfFsm *ctxt,
                const Ro_TSL::CreditControlAnswer *in,
                cap_v2::ConnectArg& out);

        void CCA_Initial_to_ConnectV1(IwfFsm *ctxt,
                const Ro_TSL::CreditControlAnswer *in,
                cap_v1::ConnectArg& out);

        int BuildReleaseSMS(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer *in,
                TCAP_Component *&cpt, byte causecode = NORMAL_UNSPECIFIED);

        int BuildContinueSMS(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer *in,
                TCAP_Component *&cpt);

        int BuildRRBSMS(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer *in,
                TCAP_Component *&cpt);

        int FillSDPMediaDescription(const uint8_t *tbcd, int len, std::stringstream &mediaName,
                std::stringstream &mediaDesc);

        int TimeStamp(const uint8_t *tbcd, int len, uint32_t &seconds,
                TransatelCAPRoTransactionContext* userData);

        uint32_t ConstructTimeStamp(TransatelCAPRoTransactionContext* userData);

        void EncodeMsg(AsnObject* p, Octets** octets);

        void ReleaseSession(string &sessString, ITS_UINT sessIdx);

        int ReturnStartOctet(ITS_OCTET type);

        int ProcessInitialDP(IwfFsm *ctxt);

        void UpdateCCAResultCodeForCDR(diameter::Command* cmd,
                                                TransatelCAPRoTransactionContext* userData);

        IwfCallDetailRecorder& GetCDRRecorder()
        {
            return m_cdrRecorder;
        }

        int BuildActivityTest(IwfFsm *ctxt,
                TCAP_Component *&cpt);

        int BuildSuccessiveCCRInitial(IwfFsm *ctxt, DIA_BASE_CMD *&cmd, std::string& hostName, std::string& realmName);

        virtual int LogCDRData(IwfFsm *ctxt, ITS_UINT failureCause = 0);

        virtual int TerminateSession(IwfFsm *ctxt,
                TCAP_Component *&outCpt, DIA_BASE_CMD *&outDiaCmd);

        virtual int OnUpstrmFinalReqSent(IwfFsm *ctxt);

        virtual ITS_UINT SetFeaturesConfig(IwfFeatureConfig *req);

        virtual ITS_UINT GetCDRConfig();

        virtual ITS_UINT GetCDRFailureCause(IwfFsm *iwfFsm);

        virtual ITS_INT HandleError(IwfFsm* inFsmCtxt,
                            DIA_BASE_CMD*& outCmd,
                            TCAP_Component*& outCpt,
                            IwfReturnAction& outRetAction);

        IwfDcca& GetDccaHandler()
        {
            return m_dccaHandler;
        }
        unsigned int IsDigitsOdd(const unsigned char &oddEvenField)
        {
            unsigned int ret = oddEvenField >> TSLConstants::DIGITS_ODD_EVEN_POS;
            return ret;
        }

        int HandleACR_Recv_Before_CallAnswered(IwfFsm* ctxt,
                const cap_v2::CAMEL_CallResult *in,
                Ro_TSL::CreditControlRequest *out,
                IwfReturnAction& ret);
        void ConstructCCRTMessage(IwfFsm* ctxt,
            Ro_TSL::CreditControlRequest *out);

        void CheckAndLogCDR(IwfFsm *ctxt);

        int GetArmDataDetails(ArmData& armDataInst, TLegIDAndModeData& legIdMode);

        void CheckAndLogCDRForCCATerminate(IwfFsm*, diameter::ro_r10_transatel::CreditControlAnswer*);

        void CreateUserDataContext(IwfFsm* ctxt, pbStoredUserData storedUserData);

        void SetTranslatorState(IwfFsm *ctxt, TransState state);

        template <class T>
        void CheckAndUpdateDisconTriggerTimeStamp(IwfFsm *ctxt, T& evntBcsm);

        TransState GetTranslatorState(IwfFsm *ctxt);

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

        int CheckMSCCGrantedServiceUnitCCTime(Ro_TSL::CreditControlAnswer *cca,
                TransatelCAPRoTransactionContext* userData);

        int CheckMSCCGSUServiceSpecificUnits(Ro_TSL::CreditControlAnswer *cca,
                TransatelCAPRoTransactionContext* userData);

        int CheckMSCCFinalUnitAction(Ro_TSL::CreditControlAnswer& cca);

        int CheckSCPAction(Ro_TSL::CreditControlAnswer* cca,
                TransatelCAPRoTransactionContext* userData);

        int CheckControlMode(Ro_TSL::CreditControlAnswer* cca,
                TransatelCAPRoTransactionContext* userData);

        void CheckAndUpdateReleaseCause(unsigned int &resultCode,
                TransatelCAPRoTransactionContext*& userData);

        void CheckIsCAPReleaseCausePresent(IwfFsm *ctxt, Ro_TSL::CreditControlAnswer *cca);

        unsigned int GetMSCCResultCode(Ro_TSL::CreditControlAnswer *cca);

        unsigned int GetTerminationCauseCode(TransatelCAPRoTransactionContext* userData);

        int BuildBcsmEvent(cap_v2::EventTypeBCSM eventType,
                cap_v2::MonitorMode monitorMode,
                std::string legid,
                cap_v2::BCSMEvent *bcsmEvent,
                unsigned int& uiNoAnsTimeout);

        template <class T> void BuildErrorResponse(TCAP_Error *tcapError, T *out);

        void CheckHexDigit(string& in_sOctDigitVal, string& out_sOctDigitVal);

        void HandleTimeout(ETimerType& inTimerType, IwfFsm* inFsmCtxt,
                TCAP_Component* inTCAPCmpt, TCAP_Dialogue* inTCAPDlg,
                DIA_BASE_CMD*& outDiaCmd,
                TCAP_Component*& cpt,
                IwfReturnAction& outRetAction);

        void StartTimerHandling(IwfFsm* ctxt,ETimerType inTimerType);

        void GetCCRIAvpVal(TransCustomAvp::CAPInformation& capInfo, StoredIDPSMSToCCRIData ccriAvpVal);

        void SetLocalTransId(ITS_CTXT dlgId, IwfFsm* ctxt);

        void RetrieveIDPToCCRIData(TransCustomAvp::CAPInformation& capInfo, IDPToCCRIData ccriAvpVal);

        template <class T>
            int InitialDPToCCRI(IwfFsm *ctxt,
                    T& in,
                    Ro_TSL::CreditControlRequest *out);

        int PopulateV2SpecificIE(IwfFsm *ctxt,
                const cap_v2::InitialDPArg& in,
                Ro_TSL::CreditControlRequest *&inout);

        int ExtractScpActionData(Ro_TSL::CreditControlAnswer* cca,
                TransatelCAPRoTransactionContext* userData,
                TransCustomAvp::SCPAction::Value& scpActionVal);

        int ExtractCtrlModeData(Ro_TSL::CreditControlAnswer* cca,
                TransatelCAPRoTransactionContext* userData,
                TransCustomAvp::CAPControlMode::Value& ctrlModeVal);

        int DeduceAndConstructCAMELMsg(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer& cca,
                TcapCptList *&cmptList);

        int ConstructRRB_CONT_ACh(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer& cca,
                TcapCptList *&cmptList);
        int ConstructRRB_CONT(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer& cca,
                TcapCptList *&cmptList);

        int ConstructRRB_CON(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer* cca,
                TcapCptList *&cmptList);

        int ConstructRRB_CON_ACh(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer* cca,
                TcapCptList *&cmptList);

        int ConstructCptInTCEnd(IwfFsm *ctxt,
                Ro_TSL::CreditControlAnswer& cca,
                TcapCptList *&cmptList);

        void ApplyChargingReport_V2_To_CCR_Update(IwfFsm *ctxt,
                const cap_v1::EventReportBCSMArg *in,
                Ro_TSL::CreditControlRequest *out);

        template<class T1,class T2>
        int BuildCCRFromIncomingERBEvent(IwfFsm *ctxt, T1& erb,
                T2& eventBcsm, DIA_BASE_CMD *&cmd, IwfReturnAction& ret);

        template<class T>
        void ERB_To_CCR_Update(IwfFsm *ctxt,
                const T& in,
                Ro_TSL::CreditControlRequest *out, bool bIsTimeout=false);

        template<class T>
        void ERB_To_CCR_Terminate(IwfFsm *ctxt,
                const T& in,
                Ro_TSL::CreditControlRequest *out, bool bIsTimeout=false);

        int ExtractAndSetNoAnsTime(TransatelCAPRoTransactionContext* userData,
                                          Ro_TSL::CreditControlAnswer& cca);

        int UpdateGSUValues(TransatelCAPRoTransactionContext* userData,
                                          Ro_TSL::CreditControlAnswer& cca);

        void StoreCallAnswerTimeStamp(TransatelCAPRoTransactionContext* userData);

        uint32_t RetrieveTotalCallTimeDuration(IwfFsm *ctxt);

        int GetBeepToneFromCCA(Ro_TSL::CreditControlAnswer& cca,
                                       unsigned int& BeepToneVal);

        int CheckAndGetGSUCCTime(IwfFsm *ctxt,
                                          Ro_TSL::CreditControlAnswer& cca);

        void RetrieveERBData(TransCustomAvp::CAPERBSInformation& capERBInfo,
                                 pbERBData& erbAvpVal);

        int HandleBuildReleaseConditions(IwfFsm* ctxt,Ro_TSL::CreditControlAnswer& cca);

        template<class T1, class T2>
        bool CheckBCSMEventAndDialogueType(IwfFsm* ctxt, T1& erb,
                T2& eventBcsm, IwfReturnAction& ret);

        template<class T1>
        int ExtractLegIdFromErb(T1& erb);

        int ValidateRecvERBEvent(cap_v2::EventReportBCSMArg& erbV2,
                                 IwfFsm* ctxt,
                                 DIA_BASE_CMD *&cmd);

        int ValidateRecvERBV1Event(cap_v1::EventReportBCSMArg& erbV1,
                                   IwfFsm* ctxt,
                                   DIA_BASE_CMD *&cmd);

        template<class T1>
        void FetchDisconEvtSpecInfo(T1& erb, string& strEventSpecInfo, IwfFsm* ctxt);

        int ExtractAndSetConnectMaxDuration(IwfFsm* ctxt, Ro_TSL::CreditControlAnswer& cca);

        std::string GetStrBCSMEventType(cap_v2::EventTypeBCSM& eventType);

        std::string& GetStrSCPAction(int scpAction);

        std::string& GetStrCAPControlMode(signed int controlMode);

        std::string GetStrTimerType(ETimerType& timerType);

        void StartTimerHandling(IwfFsm* ctxt, const pbIwfTimerData timerData);

	    ITS_UINT GetCurrentTimeStamp();

        struct timeval GetCurrentMonotonic();

        void ReleaseInvokeId(IwfFsm* ctxt, const ITS_OCTET invokeId, bool isOutGoing = false);

        void ReleaseStoredInvokeIds(IwfFsm* ctxt);

        void ResetInitialSessionContext(IwfFsm* ctxt);

        void StoreConnectArgDataInUserData(IwfFsm *ctxt, const Ro_TSL::CreditControlAnswer *in);

        void StoreApplyChargignDataInUserData(IwfFsm *ctxt, const Ro_TSL::CreditControlAnswer *in);

        CAPRoTSLConfig m_config;

        IwfCallDetailRecorder m_cdrRecorder;

        IwfDcca m_dccaHandler;
};



#endif // __IWF_PROT_CAP_CAP_H__
