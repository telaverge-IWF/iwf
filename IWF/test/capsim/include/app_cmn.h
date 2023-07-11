/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: app_cmn.h,v $
 * LOG: Revision 1.1.2.4.2.1.10.1.2.1  2014/12/04 05:09:24  jkchaitanya
 * LOG: changes for increment imsi to a limit mentioned as per repeatImsi count mentioned in runfile
 * LOG:
 * LOG: Revision 1.1.2.4.2.1.4.1  2014/12/04 04:54:17  jkchaitanya
 * LOG: changes for supporing imcrement imsi for load setup in MapS6a
 * LOG:
 * LOG: Revision 1.1.2.4.2.1.10.1  2014/09/22 04:58:54  jkchaitanya
 * LOG: changes for enhancement bugs 5045, 5053
 * LOG:
 * LOG: Revision 1.1.2.4.2.1  2014/01/23 09:51:20  jkchaitanya
 * LOG: changes for merging iwf code from poc to productization
 * LOG:
 * LOG: Revision 1.1.2.4  2013/10/04 13:05:58  jkchaitanya
 * LOG: changes for bug 2250, 2319
 * LOG:
 * LOG: Revision 1.1.2.3  2013/09/10 09:38:12  jkchaitanya
 * LOG: changes after merging from map directory for the bug 2155 done by sarvesh
 * LOG:
 * LOG: Revision 1.1.2.2  2013/08/28 10:09:49  jkchaitanya
 * LOG: changes for the bug 2078 cause IE length is changed from 2 octets to 32 octets in cap_v3_lrf.asn
 * LOG:
 * LOG: Revision 1.1.2.1  2013/08/21 12:14:15  jkchaitanya
 * LOG: sub directories in capsim
 * LOG:
 * LOG: Revision 1.1.1.1.2.12.2.8  2013/08/13 07:27:24  jsarvesh
 * LOG: Changes done for CallReferenceNumber and TimeAndTimeZone
 * LOG:
 * LOG: Revision 1.1.1.1.2.12.2.7  2013/08/13 04:50:52  jkchaitanya
 * LOG: changes for encoding LEG-ID IE in ACR and ERB
 * LOG:
 * LOG: Revision 1.1.1.1.2.12.2.6  2013/08/12 13:45:51  jsarvesh
 * LOG: Changes done for Encodong Rest of the IE's from CAP-Tool Side
 * LOG:
 * LOG: Revision 1.1.1.1.2.12.2.5  2013/08/12 09:19:51  jsarvesh
 * LOG: changes for encoding issues of some cap IE's
 * LOG:
 * LOG: Revision 1.1.1.1.2.12.2.4  2013/07/30 05:03:52  jkchaitanya
 * LOG: changes to handle Release for SMS
 * LOG:
 * LOG: Revision 1.1.1.1.2.12.2.3  2013/07/30 04:46:55  jkchaitanya
 * LOG: changes to ahndle RRB and Continue for SMS
 * LOG:
 * LOG: Revision 1.1.1.1.2.12.2.2  2013/07/29 12:27:45  jkchaitanya
 * LOG: changes for sms support messages in cap tool and asn
 * LOG:
 * LOG: Revision 1.1.1.1.2.12.2.1  2013/07/09 11:26:31  jkchaitanya
 * LOG: changes for cap tool enhancement
 * LOG:
 * LOG: Revision 1.1.1.1.2.12  2013/05/24 13:31:18  millayaraja
 * LOG: Added Activate and Deactivate Trace Mode mapping
 * LOG:
 * LOG: Revision 1.1.1.1.2.11  2013/05/21 11:18:43  jsarvesh
 * LOG: enhancement for MAP-DIAMETER translator Phase-II
 * LOG:
 * LOG: Revision 1.1.1.1.2.10  2013/05/02 04:31:52  jsarvesh
 * LOG: IWFPhaseII Changes for UGL, SAI and PurgeMS
 * LOG:
 * LOG: Revision 1.1.1.1.2.9  2013/03/15 07:38:58  jsarvesh
 * LOG: enhancement for map simulator added Activate tracemode reset arg deactivate trace mode
 * LOG:
 * LOG: Revision 1.1.1.1.2.8  2013/03/08 04:17:59  jsarvesh
 * LOG: implementation for map message through json
 * LOG:
 * LOG: Revision 1.1.1.1.2.7  2013/02/22 19:59:13  lakshman
 * LOG: add gtt test info.
 * LOG:
 * LOG: Revision 1.1.1.1.2.6  2013/02/15 15:52:19  jvikas
 * LOG: PurgeUE related changes.
 * LOG:
 * LOG: Revision 1.1.1.1.2.5  2013/02/15 12:46:28  brajappa
 * LOG: Sending and receiving Cancel Location Arg
 * LOG:
 * LOG: Revision 1.1.1.1.2.4  2013/02/14 09:55:16  brajappa
 * LOG: ISD sending withing UGLA is handled through command line, handling readyForSM
 * LOG:
 * LOG: Revision 1.1.1.1.2.3  2013/01/31 19:30:54  arnabd
 * LOG: Handling of SendAuthenticationInfoArg
 * LOG:
 * LOG: Revision 1.1.1.1.2.2  2013/01/17 23:49:15  lakshman
 * LOG: Update DeleteSubscriberdata and TCAP error handling function with few tests.
 * LOG:
 * LOG: Revision 1.1.1.1.2.1  2013/01/15 21:21:30  lakshman
 * LOG: get Delete subscriber and Insert subscriber conversions in cvs.
 * LOG:
 * LOG: Revision 1.1.1.1  2013/01/09 16:41:37  brajappa
 * LOG: Initial import
 * LOG:
 * LOG: Revision 1.1.2.2  2013/01/05 15:27:14  lakshman
 * LOG: add enums for update gprs loc res
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/31 14:52:10  lakshman
 * LOG: add includes.
 * LOG:
 * LOG: Revision 1.1.1.1  2011/04/13 08:12:31  nvijikumar
 * LOG: Initial Draft for SSG
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: app_cmn.h,v 1.1.2.4.2.1.10.1.2.1 2014/12/04 05:09:24 jkchaitanya Exp $"

#ifndef APP_COMMON_H
#define  APP_COMMON_H

#include <iostream>

#include <fstream>
#include <string>
#include <its++.h>
#include <json/json.h>

#include <AsnObject.h>
#include <AsnException.h>
#include <map_prot_utils.h>

#include <cap_cpp.h>
using namespace cap;
#if defined(USE_CAP_V2)
#include <cap_v2_initial_dp_arg.h>
#include <cap_v2_request_report_bcsm_event_arg.h>
#include <cap_v2_connect_arg.h>
#include <cap_v2_release_call_arg.h>
#include <cap_v2_event_report_bcsm_arg.h>
#include <cap_v2_apply_charging_arg.h>
#include <cap_v2_cancel_arg.h>
#include <cap_v2_apply_charging_report_arg.h>
#include<cap_v2_event_report_bcsm_arg.h>
#include<cap_v2_camel_call_result.h>
using namespace cap_v2;
#elif defined(USE_CAP_V3)
#include<cap_v3_initial_dp_arg.h>
#include<cap_v3_initial_dpsms_arg.h>
#include<cap_v3_request_report_bcsm_event_arg.h>
#include<cap_v3_request_report_sms_event_arg.h>
#include<cap_v3_continue_with_argument_arg.h>
#include<cap_v3_event_report_bcsm_arg.h>
#include<cap_v3_event_report_sms_arg.h>
#include<cap_v3_apply_charging_arg.h>
#include<cap_v3_apply_charging_report_arg.h>
#include<cap_v3_camel_a_ch_billing_charging_characteristics.h>
#include<cap_v3_release_call_arg.h>
#include<cap_v3_release_sms_arg.h>
#include<cap_v3_event_report_bcsm_arg.h>
#include<cap_v3_camel_call_result.h>
using namespace cap_v3;
#endif

#include <map_cpp.h>
#include <map_v13_update_location_arg.h>
#include <map_v13_update_location_res.h>
#include <map_v13_insert_subscriber_data_arg.h>
#include <map_v13_insert_subscriber_data_res.h>
#include <map_v13_update_gprs_location_arg.h>
#include <map_v13_update_gprs_location_res.h>
#include <map_v13_provide_subscriber_info_arg.h>
#include <map_v13_provide_subscriber_info_res.h>
#include <map_v13_delete_subscriber_data_arg.h>
#include <map_v13_delete_subscriber_data_res.h>
#include <map_v13_send_authentication_info_arg.h>
#include <map_v13_send_authentication_info_res.h>
#include <map_v13_ready_for_sm_arg.h>
#include <map_v13_ready_for_sm_res.h>
#include <map_v13_cancel_location_arg.h>
#include <map_v13_cancel_location_res.h>
#include <map_v13_purge_ms_arg.h>
#include <map_v13_purge_ms_res.h>
#include <map_v13_activate_trace_mode_arg.h>
#include <map_v13_deactivate_trace_mode_arg.h>
#include <map_v13_reset_arg.h>
#include <map_v13_unknown_subscriber_param.h>
#include <map_v13_roaming_not_allowed_param.h>
#include <map_v13_data_missing_param.h>
#include <map_v13_unexpected_data_param.h>
#include <map_v13_facility_not_sup_param.h>
#include <map_v13_system_failure_param.h>
#include <map_v13_illegal_subscriber_param.h>
#include <map_v13_illegal_equipment_param.h>
#include <map_v13_absent_subscriber_param.h>
#include <map_v13_unauthorized_requesting_network_param.h>
#include <map_v13_unauthorized_lcs_client_param.h>
#include <map_v13_position_method_failure_param.h>
#include <map_v13_unidentified_sub_param.h>
#include <map_v13_deactivate_trace_mode_res.h>
#include <map_v13_activate_trace_mode_res.h>





#if defined(ITS_NAMESPACE)
using namespace its;
//using namespace map_v6;
using namespace std;
#endif

uint64_t imsiforload = 0;
uint64_t repeatImsiLimit = 0;

#define SC_TYPE_1 1
#define SC_TYPE_2 2
#define SC_TYPE_3 3
#define SC_TYPE_4 4
#define SC_TYPE_5 5

#define MAX_CALLED_PARTY_NUMBER_DIGITS 36
#define MAX_CALLED_PARTY_NUMBER_HEADER_LENGTH 4
#define MAX_CALLING_PARTY_NUMBER_DIGITS 20
#define MAX_CALLING_PARTY_NUMBER_HEADER_LENGTH 4
#define MAX_IPSSP_CAPABILITY_DIGITS 8
#define MAX_LOCATION_NUMBER_DIGITS 20
#define MAX_LOCATION_NUMBER_HEADER_LENGTH 4
#define MAX_ORG_CALLED_PARTY_ID_DIGITS 36
#define MAX_ORG_CALLED_PARTY_ID_HEADER_LENGTH 4
#define MAX_ADDITIONAL_CALLING_PARTY_NUMBER_DIGITS 20
#define MAX_ADDITIOANL_CALLING_PARTY_NUMBER_HEADER_LENGTH 6
#define MAX_CAUSE_DIGITS 64
#define MAX_LOCATION_NUMBER_DIGITS 20
#define MAX_LOCATION_NUMBER_HEADER_LENGTH 4
#define MAX_VLR_NUMBER_DIGITS 18
#define MAX_VLR_NUMBER_HEADER_LENGTH 2
#define MAX_MSC_NUMBER_DIGITS 18
#define MAX_MSC_NUMBER_HEADER_LENGTH 2
#define MAX_BASIC_SERVICE_CODE_DIGITS 10
#define MAX_TELE_SERVICE_CODE_DIGITS 10
#define MAX_CALL_REFERENCE_NUMBER_DIGITS 16
#define MAX_MSC_ADDRESS_DIGITS 18
#define MAX_MSC_ADDRESS_HEADER_LENGTH 2
#define MAX_CALLED_PARTY_BCD_NUMBER_DIGITS 20
#define MAX_CALLED_PARTY_BCD_NUMBER_HEADER_LENGTH 2
#define MAX_TIME_AND_TIME_ZONE_DIGITS 16
#define MAX_CARRIER_DIGITS 8
#define MAX_CARRIER_DIGITS_LENGTH 4
#define MAX_CUG_INTERLOCK_DIGITS 8
#define MAX_GMSC_ADDRESS_DIGITS 18
#define MAX_GMSC_ADDRESS_HEADER_LENGTH 2
#define MAX_DEST_SUBSCRIBER_NUMBER_DIGITS 20
#define MAX_DEST_SUBSCRIBER_NUMBER_HEADER_LENGTH 2
#define MAX_ISDN_ADDRESS_DIGITS 18
#define MAX_ISDN_ADDRESS_HEADER_LENGTH 2
#define MAX_TP_SHORT_MESSAGE_SUB_SPE_INFO_DIGITS 2
#define MAX_TP_PROTOCOL_IDENTIFIER_DIGITS 2
#define MAX_TP_DATA_CODING_SCHEME_DIGITS 2
#define MAX_SMS_REFERENCE_NUMBER_DIGITS 16
#define MAX_SGSN_NUMBER_DIGITS 18
#define MAX_SGSN_NUMBER_HEADER_LENGTH 2
#define MAX_REDIRECTING_PARTY_ID_DIGITS 20
#define MAX_REDIRECTING_PARTY_ID_HEADER_LENGTH 4
#define MAX_REDIRECTION_INFORMATION_DIGITS 4
#define MAX_LSA_ID_DIGITS 6
#define MAX_TP_VALIDITY_PERIOD_DIGITS_2 2
#define MAX_TP_VALIDITY_PERIOD_DIGITS_14 14
#define MAX_LEG_ID_DIGITS 2
#define MAX_SS_CODE_DIGITS 2
#define MAX_RAND_DIGITS 32
#define MAX_SRES_DIGITS 8
#define MAX_XRES_DIGITS 32
#define MAX_AUTN_DIGITS 32
#define MAX_KASME_DIGITS 64
#define MAX_KC_DIGITS 16
#define MAX_CK_DIGITS 32
#define MAX_IK_DIGITS 32
// Sing of Lattitude values : 3GPP TS 23.032
enum
{
  NORTH,
  SOUTH
};

ITS_UINT optionfromserver = 0;
#define NUM_OF_CALLFLOWS_SUPPORTED 20

typedef enum {

    MAP_V13_UPDATE_GPRS_LOC = 80,
    MAP_V2_UPDATE_GPRS_LOC,
    MAP_V1_UPDATE_GPRS_LOC,
    MAP_V13_SAI_ARG_AND_UGL_ARG,

    MAP_V13_UPDATE_LOC = 85,
    MAP_V2_UPDATE_LOC,
    MAP_V1_UPDATE_LOC,

    MAP_V13_UPDATE_LOC_RES = 90,
    MAP_V2_UPDATE_LOC_RES,
    MAP_V1_UPDATE_LOC_RES,

    MAP_V13_INSERT_SUB_DATA = 95,
    MAP_V2_INSERT_SUB_DATA,
    MAP_V1_INSERT_SUB_DATA,
    MAP_V13_INSERT_SUB_DATA_RES,

    MAP_V13_UPDATE_GPRS_LOC_RES = 100,
    MAP_V2_UPDATE_GPRS_LOC_RES,

    MAP_V13_PROVIDE_SUB_INFO = 105,
    MAP_V13_PROVIDE_SUB_INFO_RES,

    MAP_V13_DELETE_SUB_DATA = 110,
    MAP_V13_DELETE_SUB_DATA_RES,
            
    MAP_V13_SEND_AUTHENTICATION_INFO_RES = 115,

    MAP_V13_READY_FOR_SM_RES = 120,

    MAP_V13_CANCEL_LOCATION = 125,
    MAP_V13_CANCEL_LOCATION_RES,

    MAP_V13_PURGEMS_RES = 130,

    MAP_V13_TRACE_ACTIVATE_MODE_ARG = 135,
    MAP_V13_TRACE_ACTIVATE_MODE_RES,

    MAP_V13_TRACE_DEACTIVATE_MODE_ARG = 140,
    MAP_V13_TRACE_DEACTIVATE_MODE_RES,

    MAP_V13_RESET_ARG = 145,

    MAP_V13_PURGE_MS_ARG = 150,

    MAP_V13_SEND_AUTH_INFO_ARG = 155,

    MAP_V13_READY_FOR_SM_ARG = 160,

    MAP_OPCODE_INVALID = 0xFF
}
MAP_OPCODE;

AsnObject* BuildCapMsg(int opCode);
AsnObject* BuildInitialDPArg();
AsnObject* BuildEventReportBCSMArginTcCont();
AsnObject* BuildEventReportBCSMArginTcContAgain();
AsnObject* BuildEventReportBCSMArginTcEnd();
AsnObject* BuildApplyChargingReportinTcCont();
AsnObject* BuildApplyChargingReportinTcContAgain();
AsnObject* BuildApplyChargingReportinTcEnd();
AsnObject* BuildInitialDPSMSArg();
AsnObject* BuildEventReportSMSArg(); 

AsnObject* BuildMapMsg(MAP_OPCODE opCode);
AsnObject* BuildUpdateLocV13();
AsnObject* BuildMapResMsgV13();
AsnObject* BuildInsertSubDataV13();
AsnObject* BuildUpdateGPRSLocV13();
AsnObject* BuildUpdateGPRSLocResV13();
AsnObject* BuildProvideSubscriberInfoArgV13();
AsnObject* BuildDeleteSubscriberDatArgV13();
AsnObject* BuildSendAuthenticationInfoResV13();
AsnObject* BuildReadyForSM_ResV13();
AsnObject* BuildCancelLocationArgV13();
AsnObject* BuildCancelLocationResV13();
AsnObject* BuildPurgeMSResV13();
AsnObject* BuildTraceActivateModeArgV13();
AsnObject* BuildTraceDeActivateModeArgV13();
AsnObject* BuildResetArg();
AsnObject* BuildPurgeMSArg();
AsnObject* BuildSendAuthenticationInfoArg();
AsnObject* BuildInsertSubscriberDataResV13();
AsnObject* BuildDeleteSubscriberDatResV13();
AsnObject* BuildProvideSubscriberInfoResV13();
AsnObject* BuildReadyForSM_ArgV13();
AsnObject* BuildTraceDeActivateModeResV13();
AsnObject* BuildTraceActivateModeResV13();
void BuildLocationInformation(map_v13::LocationInformation* li);
void BuildLocationInformationGPRS(map_v13::LocationInformationGPRS* ligprs);
void BuildPS_SubscriberState(map_v13::PS_SubscriberState* psstate);
void BuildEPS_SubscriberState(map_v13::PS_SubscriberState *psstate);

AsnObject * SAIArg=NULL;
AsnObject * UGLArg=NULL;
AsnObject * PURGEArg=NULL;

Json::Value parseCapConfig();
Json::Value parseMapConfig();
Json::Value* m_jsonRoot;
Json::Value* m_jsonRoot1;
Json::Value* c_jsonRoot;
Json::Value* c_jsonRoot1;

#endif

