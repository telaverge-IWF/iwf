/*----------------------------------------------------------------------------*
 *                                                                            *
 *      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     *
 *              Manufactured in the United States of America.                 *
 *        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                            *
 *    This product and related documentation is protected by copyright and    *
 *    distributed under licenses restricting its use, copying, distribution   *
 *    and decompilation.  No part of this product or related documentation    *
 *    may be reproduced in any form by any means without prior written        *
 *    authorization of IntelliNet Technologies and its licensors, if any.     *
 *                                                                            *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       *
 *    government is subject to restrictions as set forth in subparagraph      *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software        *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                         *
 *                                                                            *
 *----------------------------------------------------------------------------*
 *                                                                            *
 * CONTRACT: INTERNAL                                                         *
 *                                                                            *
 *----------------------------------------------------------------------------*
 *
 *  ID: $Id: inap_c.h,v 9.1 2005/03/23 12:51:42 cvsadmin Exp $
 *
 *----------------------------------------------------------------------------*/

#if !defined(_INAP_C_H_)
#define _INAP_C_H_

#include <its.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */



/*------------------------------------------------------------------------------
 *                                                                            
 *  INAP general constants.
 *
 */


/* None. */



/*------------------------------------------------------------------------------
 *                                                                            
 *  INAP protocol constants.
 *
 */


/*
 *  Operation codes.
 */

#define INAP_OP_INITIAL_DP                              0
#define INAP_OP_ORIGINATION_ATTEMPT_AUTHORIZED          1
#define INAP_OP_COLLECTED_INFORMATION                   2
#define INAP_OP_ANALYSED_INFORMATION                    3
#define INAP_OP_ROUTE_SELECT_FAILURE                    4
#define INAP_OP_O_CALLED_PARTY_BUSY                     5
#define INAP_OP_O_NO_ANSWER                             6
#define INAP_OP_O_ANSWER                                7
#define INAP_OP_O_DISCONNECT                            8
#define INAP_OP_TERM_ATTEMPT_AUTHORIZED                 9
#define INAP_OP_T_BUSY                                  10
#define INAP_OP_T_NO_ANSWER                             11
#define INAP_OP_T_ANSWER                                12
#define INAP_OP_T_DISCONNECT                            13
#define INAP_OP_O_MID_CALL                              14
#define INAP_OP_T_MID_CALL                              15
#define INAP_OP_ASSIST_REQUEST_INSTRUCTIONS             16
#define INAP_OP_ESTABLISH_TEMPORARY_CONNECTION          17
#define INAP_OP_DISCONNECT_FORWARD_CONNECTION           18
#define INAP_OP_CONNECT_TO_RESOURCE                     19
#define INAP_OP_CONNECT                                 20
#define INAP_OP_HOLD_CALL_IN_NETWORK                    21
#define INAP_OP_RELEASE_CALL                            22
#define INAP_OP_REQUEST_REPORT_BCSM_EVENT               23
#define INAP_OP_EVENT_REPORT_BCSM                       24
#define INAP_OP_REQUEST_NOTIFICATION_CHARGING_EVENT     25
#define INAP_OP_EVENT_NOTIFICATION_CHARGING             26
#define INAP_OP_COLLECT_INFORMATION                     27
#define INAP_OP_ANALYSE_INFORMATION                     28
#define INAP_OP_SELECT_ROUTE                            29
#define INAP_OP_SELECT_FACILITY                         30
#define INAP_OP_CONTINUE                                31
#define INAP_OP_INITIATE_CALL_ATTEMPT                   32
#define INAP_OP_RESET_TIMER                             33
#define INAP_OP_FURNISH_CHARGING_INFORMATION            34
#define INAP_OP_APPLY_CHARGING                          35
#define INAP_OP_APPLY_CHARGING_REPORT                   36
#define INAP_OP_REQUEST_CURRENT_STATUS_REPORT           37
#define INAP_OP_REQUEST_EVERY_STATUS_CHANGE_REPORT      38
#define INAP_OP_REQUES_TFIRST_STATUS_MATCH_REPORT       39
#define INAP_OP_STATUS_REPORT                           40
#define INAP_OP_CALL_GAP                                41
#define INAP_OP_ACTIVATE_SERVICE_FILTERING              42
#define INAP_OP_SERVICE_FILTERING_RESPONSE              43
#define INAP_OP_CALL_INFORMATION_REPORT                 44
#define INAP_OP_CALL_INFORMATION_REQUEST                45
#define INAP_OP_SEND_CHARGING_INFORMATION               46
#define INAP_OP_PLAY_ANNOUNCEMENT                       47
#define INAP_OP_PROMPT_AND_COLLECT_USER_INFORMATION     48
#define INAP_OP_SPECIALIZED_RESOURCE_REPORT             49
#define INAP_OP_CANCEL                                  53
#define INAP_OP_CANCEL_STATUS_REPORT_REQUEST            54
#define INAP_OP_ACTIVITY_TEST                           55
#define INAP_OP_REQUEST_CURRENT_STATUS_REPORT_RESULT    56



/*
 *  Error codes.
 */

#define INAP_ERR_CANCELLED                          0
#define INAP_ERR_CANCEL_FAILED                      1
#define INAP_ERR_E_TC_FAILED                        3
#define INAP_ERR_IMPROPER_CALLER_RESPONSE           4
#define INAP_ERR_MISSING_CUSTOMER_RECORD            6
#define INAP_ERR_MISSING_PARAMETER                  7
#define INAP_ERR_PARAMETER_OUT_OF_RANGE             8
#define INAP_ERR_REQUESTED_INFO_ERROR               10
#define INAP_ERR_SYSTEM_FAILURE                     11
#define INAP_ERR_TASK_REFUSED                       12
#define INAP_ERR_UNAVAILABLE_RESOURCE               13
#define INAP_ERR_UNEXPECTED_COMPONENT_SEQUENCE      14
#define INAP_ERR_UNEXPECTED_DATA_VALUE              15
#define INAP_ERR_UNEXPECTED_PARAMETER               16
#define INAP_ERR_UNKNOWN_LEG_ID                     17
#define INAP_ERR_UNKNOWN_RESOURCE                   18



#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_INAP_C_H_) */



