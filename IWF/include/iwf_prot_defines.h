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

#ifndef __IWF_PROT_DEFINES_H__
#define __IWF_PROT_DEFINES_H__

#include <string>
#include <vector>
#include <stdint.h>
#include <math.h>
#include <arpa/inet.h>

#include <its++.h>
#include <tcap++.h>
#include <Asn.h>
#include <AsnException.h>
#include <ss7_mgmt.h>
#include <ual_config_mgnt.h>

#include <dia_defines.h>
#include <cap_c.h>

#include "iwfconfig.pb.h"
#include "CMAPICommon.h"
#include "IwfErrorResp.h"
#include "IWFConfigFetch.h"
#include "iwf_timer.h"
#include <itu/sccp.h>
#include "Atomic.h"

#define SGSN_SSN 149
#define CAP 146
#define MSC_CAP 146
#define HLR 6

/* Added Sleep while adding a Association as not able to find transportId instantly, Need to fix*/
#define ADD_TRANSPORT_WAIT 1

#define MAP_TO_S6A_STR "MAP-s6a"
#define S6A_TO_MAP_STR "s6a-MAP"
#define CAP_TO_RO_STR "CAP-Ro"

#define CAP_TO_RO_STR_TSL "CAP-Ro-TSL"

#define IWF_MAX_E164_SZ 16
#define IWF_MAX_TIME_BUF 100
#define IWF_TIME_DIFF 1400

#define MAP_GR_RAND_SZ 16
#define MAP_GR_AUTS_SZ 14

#define MAP_GR_REQUESTING_PLMN_ID_SZ 3

#define DIAMETER_3GPP_VENDOR_ID 10415

#define DIAMETER_S6A_APPLICATION_ID "16777251"
#define DIAMETER_RO_APPLICATION_ID    "4"

#define DIAMETER_RO_DICTIONARY_ID 25

#define DIAMETER_ERROR_USER_UNKNOWN (5001)
#define DIAMETER_ERROR_UNKNOWN_EPS_SUBSCRIPTION (5420)
#define DIAMETER_ERROR_RAT_NOT_ALLOWED (5421)
#define DIAMETER_ERROR_ROAMING_NOT_ALLOWED (5004)
#define DIAMETER_ERROR_EQUIPMENT_UNKNOWN (5422)
#define DIAMETER_ERROR_UNKOWN_SERVING_NODE (5423)

#define DIAMETER_ERROR_DIAMETER_END_USER_SERVICE_DENIED 4010
#define DIAMETER_ERROR_CREDIT_CONTROL_NOT_APPLICABLE 4011
#define DIAMETER_ERROR_CREDIT_LIMIT_REACHED 4012   
#define DIAMETER_ERROR_OTHER_ERROR 4015
#define DIAMETER_ERROR_NODE_NOT_RESPONSIBLE 4014
#define DIAMETER_ERROR_RATING_FAILED 5031

#define NORMAL_END_OF_SESSION 0
#define UNSPECIFIED_ERROR 1
#define FEATURE_LIST_ODB_BITS 511

#define SSCODE_BARRING_OF_ALL_OUTGOING_CALLS 0x92
#define SSCODE_BARRING_OF_OUTGOING_INTERNATIONAL_CALLS 0x93
#define SSCODE_BARRING_OF_OUTGOING_INTERN_CALLS_EXCEPT_THOSE_DIRECTED_TO_HOME_PLMN_COUNTRY 0x94
#define SSCODE_BARRING_OF_ALL_INCOMING_CALLS 0x99
#define SSCODE_BARRING_OF_INCOMING_CALLS_WHEN_ROAMING_OUTSIDE_THE_HOME_PLMN_COUNTRY 0x9b

#define IWF_ASSOC_MAX_STR_LEN 32

#define IWF_NATIONAL_INDICATOR 128
#define IWF_INTERNATIONAL_INDICATOR 0
#define IWF_NATIONAL_SIO 131
#define IWF_INTERNATIONAL_SIO 3

#define IWF_DEFAULT_SERVICE_KEY 0

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

#define CAP_GSM_FORWARDING_PENDING_PRESENT 1

#define CDR "LOG_CDR"

#define TANS_TRIGGER "FOLLOWON_TANS_TRIGGER"

#define CONGESTION_MANAGEMENT "CONGESTION_MANAGEMENT"
#define MAX_NUMBER_OF_SESSIONS "MAX_NUMBER_OF_SESSIONS"
#define MAX_COUCHBASE_TTL 600

#define ROUNDOFF_USU_VALUE(usu) nearbyint((usu/10.0))

#define INVOKEID_LEN 3

#define IWF_WAIT_MAX_COUNT 100

#define IWF_SUBSCRIPTION_DATA_AVP_CODE 1400
#define IWF_SERVICE_CONTROL_AVP_CODE 1000
#define IWF_SUBSCR_AUDIT_TIMEOUT 300

#define DIA_S6A_REL10_DICTID 7
#define S6A_MAP_START_SGSN_NUM 100000

#define LENGTH_OF_ADDR_DIGITS 2
#define MAX_SGSN_NUM_LEN 20

#define SGSN_HEADER_DIGITS "91"

using namespace its;

struct SCCPGTTInfo {
    ITS_USHORT m_gttLength;
    ITS_OCTET  m_gttType;
    ITS_OCTET  m_gttInfo[32];
    ITS_OCTET  m_addrIndicator;
    ITS_UINT   m_pointcode;
    ITS_OCTET  m_ssn;
    SCCPGTTInfo():
        m_gttLength(0),
        m_gttType(0),
        m_addrIndicator(0),
        m_pointcode(0),
        m_ssn(0)
    {
        memset(m_gttInfo, 0, 32);
    }
};

struct SCCPParameters {
    SCCPGTTInfo cpd_itu;
    SCCPGTTInfo cpa_itu;
    ITS_UINT m_opc;
    ITS_UINT m_dpc;
    bool isRouteByGT;
    SCCPParameters():
        m_opc(0),
        m_dpc(0),
        isRouteByGT(false)
    {
    }
};

#define MAX_IP_LEN 16
struct RoutingKeyInfo {
    ITS_UINT routingKey;
    char homeIp[MAX_IP_LEN];

};

enum DiaCommandCode
{
    DIA_CMD_UNKNOWN = 0,
    DIA_CMD_CE = 257, // Capabilities Exchange Request/Answer
    DIA_CMD_DP = 282, // Disconnect Peer Request/Answer
    DIA_CMD_UL = 316, // Update Location Request/Answer
    DIA_CMD_CL = 317, // Cancel Location Request/Answer
    DIA_CMD_AI = 318, // Auth Info
    DIA_CMD_ID = 319, // Insert subscriber
    DIA_CMD_DS = 320, // Delete Subscriber
    DIA_CMD_PU = 321, // Purge
    DIA_CMD_RS = 322, // Reset
    DIA_CMD_NO = 323, // Notify
    DIA_CMD_CC = 272, // CreditControl
    DIA_CMD_RA = 258, // Re-Auth-Request/Answer
    DIA_CMD_AS = 274, // Abort-Session/Answer
    DIA_CMD_ST = 275, // Session-termination
};

enum TimeOctets
{
    OCTET_YR = 1,
    OCTET_MT,
    OCTET_DY,
    OCTET_HR,
    OCTET_MN,
    OCTET_SC,
    OCTET_TZ
};

enum InformationTransferCap
{
    SPEECH = 0,
    AUDIO_3_1KHZ = 16,
    VIDEO = 24
};

enum InformationTransferRate
{
    RATE_64KBPS = 16,
    RATE_2X64KBPS = 17,
    RATE_384KBPS = 19,
    RATE_1536KBPS = 21,
    RATE_1920KBPS = 23,
    RATE_MULRATEKBPS = 24
};

enum UserInformationLayer
{
    G711ULAW = 2,
    G711ALAW = 3,
    G721 = 4,
    H221H242 = 5,
    H223H245 = 6
};

enum NORFlagsValue
{
    NOR_FLAG_SINGLE_REGISTRATION_IND = 1 << 0,
    NOR_FLAG_SGSN_AREA_RESTRICTED    = 1 << 1,
    NOR_FLAG_READY_FOR_SM_FROM_SGSN  = 1 << 2,
    NOR_FLAG_UE_REACHABLE_FROM_MME   = 1 << 3,
    NOR_FLAG_RESERVER                = 1 << 4,
    NOR_FLAG_UE_REACHABLE_FROM_SGSN  = 1 << 5,
    NOR_FLAG_READY_FOR_SM_FROM_MME   = 1 << 6,
    NOR_FLAG_HOMOGENEOUS_SUPPORT_OF_VPICE_OVER_PS_SESSIONS = 1 << 7
};

enum PUAFlagsValue
{
    PUA_FLAG_FREEZ_M_TMSI = (1 << 0), 
    PUA_FLAG_FREEZ_P_TMSI = (1 << 1)
};

enum IDRFlagsValue
{
    IDR_FLAG_UE_REACH_REQ       = (1 << 0),
    IDR_FLAG_TADS_DATA_REQ      = (1 << 1),
    IDR_FLAG_EPS_USER_STATE_REQ = (1 << 2),
    IDR_FLAG_EPS_LOC_INFO_REQ   = (1 << 3),
    IDR_FLAG_CUR_LOC_REQ        = (1 << 4),
    IDR_FLAG_LOCAL_TZONE_REQ    = (1 << 5)
};

enum DSRFlagsValue
{
    DSR_FLAG_REGION_SUB_WITHDRAW       = (1 << 0),
    DSR_FLAG_COMPLETE_APN_CONFIG       = (1 << 1),
    DSR_FLAG_SUB_CHARGE_CHAR           = (1 << 2),
    DSR_FLAG_PDN_SUBSCRIPTION_WITHDRAW = (1 << 3),
    DSR_FLAG_STN_SR                    = (1 << 4),
    DSR_FLAG_COMPLETE_PDP_LIST_WITHDRAW= (1 << 5),
    DSR_FLAG_PDP_CONTEXT_WITHDRAW      = (1 << 6),
    DSR_FLAG_ROAM_RESTRICT_UN_SUPPORTED= (1 << 7),
    DSR_FLAG_TRACE_DATA_WITHDRAW       = (1 << 8),
    DSR_FLAG_CSG_DELETED               = (1 << 9),
    DSR_FLAG_ASPN_OI_REPLACEMENT       = (1 << 10),
    DSR_FLAG_GMLC_LIST_WITHDRAW        = (1 << 11),
    DSR_FLAG_LCS_WITHDRAW              = (1 << 12),
    DSR_FLAG_SMS_WITHDRAW              = (1 << 13)
};

enum DSAFlagsValue
{
    DSA_FLAG_NET_NODE_AREA_RESTRICT = (1 << 0)
};

enum ULRFlagsValue
{
    ULR_FLAG_SINGLE_REIGSTRATION_IND = (1<<0),
    ULR_FLAG_S6A_S6D_IND = (1<<1),
    ULR_FLAG_SKIP_SUBSCRIBER_DATA = (1<<2),
    ULR_FLAG_GPRS_SUBSCRIPTION_DATA_IND = (1<<3),
    ULR_FLAGS_NODE_TYPE_IND = (1<<4),
    ULR_FLAGS_INITIAL_ATTACH_IND = (1<<5),
    ULR_FLAGS_PC_LCS_NOT_SUPPORTED = (1<<6)
};

enum ULAFlagsValue
{
    ULA_FLAG_S6A_S6D_IND = (1 << 0)
};

enum IDAFlagsValue
{
    IDA_FLAG_NET_NODE_AREA_RESTRICT = (1 << 0)
};

enum SelectionCriteria
{
    UNKNOWN_SELECTIONCRITERIA = 0,
    SELECT_MCC_MNC = 1,
    SELECT_CLG_GTT_ADDR_DGTS = 8,
    SELECT_CLG_GTT_ADDR_DGTS_AND_MCC_MNC = 9,
    SELECT_SK = 16,
    SELECT_SK_AND_MCC_MNC = 17,
    SELECT_CLG_GTT_ADDR_DGTS_AND_SK = 24,
    SELECT_IMSI_PREFIX_AND_SK = 25
};

enum Call_Type
{
    UNKNOWN = 0,
    MO_VOICE = 1,
    MT_VOICE,
    MO_SMS,
    MO_MMS,
    MT_FW,
    MO_FW,
    MT_SMS
};
namespace TSLConstants
{
    unsigned int CAPV1_VERSION = 1;
    unsigned int CAPV2_VERSION = 2;
    unsigned int CAPV3_VERSION = 3;
    unsigned int MO_DP_EVENT = 2;
    unsigned int MT_DP_EVENT = 12;
    int CONTINUE_CALL_RET = 100;
    unsigned int DEFAULT_DEST_ROUTING_ADDR_NOA = 4;
    unsigned int DEFAULT_DEST_ROUTING_ADDR_NPI = 1;
    unsigned int DEFAULT_DEST_ROUTING_ADDR_INN = 0;
    int INVALID_CONTROL_MODE_CAPV1 = 200;
    int INVALID_CONTROL_MODE = 300;
    unsigned int EVENT_TYPE_BCSM_OANSWER = 7;
    unsigned int EVENT_TYPE_BCSM_TANSWER = 15;
    unsigned int EVENT_TYPE_BCSM_ODISCONNECT = 9;
    unsigned int EVENT_TYPE_BCSM_TDISCONNECT = 17;
    unsigned int DEFAULT_TCAP_ERROR_CAUSE_VAL = 500;
    unsigned int DEFAULT_INVALID_VAL = 1000;
    int CallingLegID = 1;
    int CalledLegID = 2;
    static const unsigned DIGITS_ODD_EVEN_POS = 7;
};

enum LogCDRStatus {
    DISABLE_ALL_CALLS = 0,
    DISABLE_ONLY_SUCCESS_CALLS,
    ENABLE_ONLY_FAILED_CALLS,
    ENABLE_ALL_CALLS
};

enum CdrFailureCode {
    SUCCESS_CALL = 0,
    TX_TIMEOUT_CCR_I,
    TX_TIMEOUT_CCR_U,
    TX_TIMEOUT_CCR_T,
    AUTH_TIMEOUT_CCR_I,
    AUTH_TIMEOUT_CCR_U,
    AUTH_TIMEOUT_CCR_T,
    FAILED_3XXX_CCA_I,
    FAILED_4XXX_CCA_I,
    FAILED_5XXX_CCA_I,
    FAILED_3XXX_CCA_U,
    FAILED_4XXX_CCA_U,
    FAILED_5XXX_CCA_U,
    FAILED_3XXX_CCA_T,
    FAILED_4XXX_CCA_T,
    FAILED_5XXX_CCA_T,
    CDR_CODE_PEER_DOWN
};

enum CdrFailedOverReason {
    CDR_TX_TIMEOUT = 1,
    CDR_PEER_DOWN = 2,
    CDR_UNABLED_TO_DELIVER = 3,
    CDR_TOO_BUSY = 4
};

enum
{
    AVP_HDR_SZ = 8,
    DEST_HOST_AVP_CODE = 293,
    CC_REQUEST_NUMBER_AVP_CODE = 415,
    CC_SESS_FAILOVER_AVP_CODE = 418,
    CMD_HDR_SZ = 20,
    MBIT_FULL = 0x40000000,
    DIA_VERSION_FULL = 0x01000000,
    RESULT_AVP_CODE = 268,
    CC_REQUEST_TYPE_AVP_CODE = 416,

};


/* Application defined ErrorCode */
enum IwfErrorCode {
    IWF_EAUTH_SESSION_TIMEOUT = -300,
    IWF_EBASE_MAND_AVP_MISSING = -301,
    IWF_APP_TX_TIMEOUT = -302,
    IWF_EREJECT_COMP = -303
};
  
struct TServiceKeyStruct
{
    int low;
    int high;
    TServiceKeyStruct()
    {
        low  = -1;
        high = -1;
    }
};
typedef vector<TServiceKeyStruct> TSKList;

typedef map<string,TSKList> RuleNameVsSKList;

  
#endif // __IWF_DEFINES_H__
