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
 * LOG: Revision 1.1.2.3  2013/03/18 12:25:21  jvikas
 * LOG: Code Changes for CLR/CLA.
 * LOG:
 * LOG: Revision 1.1.2.2  2013/02/13 11:43:19  jvikas
 * LOG: MAP Simulator Changes Feb13
 * LOG:
 * LOG: Revision 1.1.2.1  2013/02/12 14:11:30  jvikas
 * LOG: Map Simulator Changes for IWF
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
#ident "$Id: app_cmn.h,v 1.1.2.3 2013/03/18 12:25:21 jvikas Exp $"

#ifndef APP_COMMON_H
#define  APP_COMMON_H

#include <iostream>

#include <fstream>
#include <string>
#include <its++.h>

#include <AsnObject.h>
#include <AsnException.h>
/*
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
#include<cap_v3_request_report_bcsm_event_arg.h>
#include<cap_v3_continue_with_argument_arg.h>
#include<cap_v3_event_report_bcsm_arg.h>
#include<cap_v3_apply_charging_arg.h>
#include<cap_v3_apply_charging_report_arg.h>
#include<cap_v3_release_call_arg.h>
#include<cap_v3_event_report_bcsm_arg.h>
#include<cap_v3_camel_call_result.h>
using namespace cap_v3;
#endif
*/

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

#if defined(ITS_NAMESPACE)
using namespace its;
//using namespace map_v6;
using namespace std;
#endif

#define SC_TYPE_1 1
#define SC_TYPE_2 2
#define SC_TYPE_3 3
#define SC_TYPE_4 4
#define SC_TYPE_5 5

// Sing of Lattitude values : 3GPP TS 23.032
enum
{
  NORTH,
  SOUTH
};

typedef enum {
    MAP_V13_UPDATE_LOC = 50,
    MAP_V2_UPDATE_LOC,
    MAP_V1_UPDATE_LOC,

    MAP_V13_INSERT_SUB_DATA = 55,
    MAP_V2_INSERT_SUB_DATA,
    MAP_V1_INSERT_SUB_DATA,

    MAP_V13_UPDATE_LOC_RES = 60,
    MAP_V2_UPDATE_LOC_RES,
    MAP_V1_UPDATE_LOC_RES,

    MAP_V13_UPDATE_GPRS_LOC = 65,
    MAP_V2_UPDATE_GPRS_LOC,
    MAP_V1_UPDATE_GPRS_LOC,

    MAP_V13_UPDATE_GPRS_LOC_RES = 70,
    MAP_V2_UPDATE_GPRS_LOC_RES,

    MAP_V13_PROVIDE_SUB_INFO = 75,

    MAP_V13_DELETE_SUB_DATA = 85,
            
    MAP_V13_SEND_AUTHENTICATION_INFO_RES = 90,

    MAP_V13_READY_FOR_SM_RES = 95,

    MAP_V13_CANCEL_LOCATION = 100,

    MAP_V13_PURGEMS_RES = 105,

    MAP_OPCODE_INVALID = 0xFF
}
MAP_OPCODE;

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
AsnObject* BuildPurgeMSResV13();

#endif

