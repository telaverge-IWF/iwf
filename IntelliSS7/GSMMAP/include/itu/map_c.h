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
 *  ID: $Id: map_c.h,v 9.1 2005/03/23 12:51:24 cvsadmin Exp $
 *
 *----------------------------------------------------------------------------*/

#if !defined(_MAP_C_H_)
#define _MAP_C_H_

#include <its.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */



/*------------------------------------------------------------------------------
 *                                                                            
 *  MAP general constants.
 *
 */

#define MAP_SSN         5
#define MAP_HLR_SSN     6
#define MAP_VLR_SSN     7
#define MAP_MSC_SSN     8
#define MAP_EIR_SSN     9
#define MAP_AC_SSN      10




/*------------------------------------------------------------------------------
 *                                                                            
 *  MAP protocol constants.
 *
 */

/*
 *  Operation codes.
 */


/* Location registration operation codes. */

#define MAP_OP_UPDATE_LOCATION                      2
#define MAP_OP_CANCEL_LOCATION                      3
#define MAP_OP_PURGE_MS                             67
#define MAP_OP_SEND_IDENTIFICATION                  55

/* Handover operation codes. */

#define MAP_OP_PREPARE_HANDOVER                     68
#define MAP_OP_SEND_END_SIGNAL                      29
#define MAP_OP_PROCESS_ACCESS_SIGNALLING            33
#define MAP_OP_FORWARD_ACCESS_SIGNALLING            34
#define MAP_OP_PREPARE_SUBSEQUENT_HANDOVER          69

/* Authentication operation codes. */

#define MAP_OP_SEND_AUTHENTICATION_INFO             56


/* IMEI MANAGEMENT operation codes. */

#define MAP_OP_CHECK_IMEI                           43


/* Subscriber management operation codes. */

#define MAP_OP_INSERT_SUBSCRIBER_DATA               7
#define MAP_OP_DELETE_SUBSCRIBER_DATA               8


/* Fault recovery operation codes. */

#define MAP_OP_RESET                                37
#define MAP_OP_FORWARD_CHECK_SS_INDICATION          38
#define MAP_OP_RESTORE_DATA                         57


/* Operation and maintenance operation codes. */

#define MAP_OP_ACTIVATE_TRACE_MODE                  50
#define MAP_OP_DEACTIVATE_TRACE_MODE                51
#define MAP_OP_SEND_IMSI                            58


/* Call handling operation codes. */

#define MAP_OP_SEND_ROUTING_INFO                    22
#define MAP_OP_PROVIDE_ROAMING_NUMBER               4
#define MAP_OP_RESUME_CALL_HANDLING                 6
#define MAP_OP_PROVIDE_SIWFS_NUMBER                 31
#define MAP_OP_SIWFS_SIGNALLING_MODIFY              32
#define MAP_OP_SET_REPORTING_STATE                  73
#define MAP_OP_STATUS_REPORT                        74
#define MAP_OP_REMOTE_USER_FREE                     75


/* Supplementary service handling operation codes. */

#define MAP_OP_REGISTER_SS                          10
#define MAP_OP_ERASE_SS                             11
#define MAP_OP_ACTIVATE_SS                          12
#define MAP_OP_DEACTIVATE_SS                        13
#define MAP_OP_INTERROGATE_SS                       14
#define MAP_OP_PROCESS_UNSTRUCTURED_SS_REQUEST      59
#define MAP_OP_UNSTRUCTURED_SS_REQUEST              60
#define MAP_OP_UNSTRUCTURED_SS_NOTIFY               61
#define MAP_OP_REGISTER_PASSWORD                    17
#define MAP_OP_GET_PASSWORD                         18
#define MAP_OP_REGISTER_CC_ENTRY                    76
#define MAP_OP_ERASE_CC_ENTRY                       77


/* Short message service operation codes. */

#define MAP_OP_SEND_ROUTING_INFO_FOR_SM             45
#define MAP_OP_MO_FORWARD_SM                        46
#define MAP_OP_MT_FORWARD_SM                        44
#define MAP_OP_REPORTSM_DELIVERY_STATUS             47
#define MAP_OP_INFORM_SERVICE_CENTRE                63
#define MAP_OP_ALERT_SERVICE_CENTRE                 64
#define MAP_OP_READY_FOR_SM                         66


/* Provide subscriber info operation codes. */

#define MAP_OP_PROVIDE_SUBSCRIBER_INFO              70


/* Any time interrogation operation codes. */

#define MAP_OP_ANY_TIME_INTERROGATION               71


/* Supplementary service invocation notification operation codes. */

#define MAP_OP_SS_INVOCATION_NOTIFICATION           72


/* Group Call operation codes. */

#define MAP_OP_PREPARE_GROUP_CALL                   39
#define MAP_OP_SEND_GROUP_CALL_END_SIGNAL           40
#define MAP_OP_PROCESS_GROUP_CALL_SIGNALLING        41
#define MAP_OP_FORWARD_GROUP_CALL_SIGNALLING        42


/* Gprs location updating operation codes. */

#define MAP_OP_UPDATE_GPRS_LOCATION                 23


/* Gprs location information retrieval operation codes. */

#define MAP_OP_SEND_ROUTING_INFO_FOR_GPRS           24


/* Failure reporting operation codes. */

#define MAP_OP_FAILURE_REPORT                       25


/* GPRS notification operation codes. */

#define MAP_OP_NOTE_MS_PRESENT_FOR_GPRS             26


/* V1 operation codes (not defined by V2 and V4). */

#define MAP_OP_UPDATE_LOCATION_AREA                 1
#define MAP_OP_DETACH_IMSI                          5
#define MAP_OP_ATTACH_IMSI                          6
#define MAP_OP_SEND_PARAMETERS                      9
#define MAP_OP_INVOKE_SS                            15
#define MAP_OP_FORWARD_SS_NOTIFICATION              16
#define MAP_OP_PROCESS_UNSTRUCTURED_SS_DATA         19
#define MAP_OP_SEND_INFO_FOR_INCOMING_CALL          20
#define MAP_OP_SEND_INFO_FOR_OUTGOING_CALL          21
#define MAP_OP_COMPLETE_CALL                        23
#define MAP_OP_CONNECT_TO_FOLLOWING_ADDRESS         24
#define MAP_OP_PROCESS_CALL_WAITING                 25
#define MAP_OP_PAGE                                 26
#define MAP_OP_SEARCH_FOR_MOBILE_SUBSCRIBER         27
#define MAP_OP_PERFORM_HANDOVER                     28
#define MAP_OP_PERFORM_SUBSEQUENT_HANDOVER          30
#define MAP_OP_ALLOCATE_HANDOVER_NUMBER             31
#define MAP_OP_SEND_HANDOVER_REPORT                 32
#define MAP_OP_NOTE_INTERNAL_HANDOVER               35
#define MAP_OP_REGISTER_CHARGING_INFORMATION        36
#define MAP_OP_AUTHENTICATE                         39
#define MAP_OP_PROVIDE_IMSI                         40
#define MAP_OP_FORWARD_NEW_TMSI                     41
#define MAP_OP_SET_CIPHERING_MODE                   42
#define MAP_OP_FORWARD_SHORT_MESSAGE                46
#define MAP_OP_SET_MESSAGE_WAITING_DATA             47
#define MAP_OP_NOTE_MS_PRESENT                      48
#define MAP_OP_ALERT_SERVICE_CENTER                 49
#define MAP_OP_TRACE_SUBSCRIBER_ACTIVITY            52
#define MAP_OP_PROCESS_ACCESS_REQUEST               53
#define MAP_OP_BEGIN_SUBSCRIBER_ACTIVITY            54




/*
 *  Error codes.
 */

/* Generic error codes. */

#define MAP_ERR_SYSTEM_FAILURE                      34
#define MAP_ERR_DATA_MISSING                        35
#define MAP_ERR_UNEXPECTED_DATA_VALUE               36
#define MAP_ERR_FACILITY_NOT_SUPPORTED              21
#define MAP_ERR_INCOMPATIBLE_TERMINAL               28
#define MAP_ERR_RESOURCE_LIMITATION                 51


/* Identification and numbering error codes. */

#define MAP_ERR_UNKNOWN_SUBSCRIBER                  1
#define MAP_ERR_NUMBER_CHANGED                      44
#define MAP_ERR_UNKNOWN_MSC                         3
#define MAP_ERR_UNIDENTIFIED_SUBSCRIBER             5
#define MAP_ERR_UNKNOWN_EQUIPMENT                   7


/* Subscription error codes. */

#define MAP_ERR_ROAMING_NOT_ALLOWED                 8
#define MAP_ERR_ILLEGAL_SUBSCRIBER                  9
#define MAP_ERR_ILLEGAL_EQUIPMENT                   12
#define MAP_ERR_BEARER_SERVICE_NOT_PROVISIONED      10
#define MAP_ERR_TELESERVICE_NOT_PROVISIONED         11


/* Handover error codes. */

#define MAP_ERR_NO_HANDOVER_NUMBER_AVAILABLE        25
#define MAP_ERR_SUBSEQUENT_HANDOVER_FAILURE         26


/* Operation and maintenance error codes. */

#define MAP_ERR_TRACING_BUFFER_FULL                 40


/* Call handling error codes. */

#define MAP_ERR_NO_ROAMING_NUMBER_AVAILABLE         39
#define MAP_ERR_ABSENT_SUBSCRIBER                   27
#define MAP_ERR_BUSY_SUBSCRIBER                     45
#define MAP_ERR_NO_SUBSCRIBER_REPLY                 46
#define MAP_ERR_CALL_BARRED                         13
#define MAP_ERR_FORWARDING_FAILED                   47
#define MAP_ERR_OR_NOT_ALLOWED                      48
#define MAP_ERR_FORWARDING_VIOLATION                14
#define MAP_ERR_CUG_REJECT                          15


/* Any time interrogation error codes. */
    
#define MAP_ERR_ATI_NOT_ALLOWED                     49


/* Group Call error codes. */

#define MAP_ERR_NO_GROUP_CALL_NUMBER_AVAILABLE      50


/* Supplementary service error codes. */

#define MAP_ERR_ILLEGAL_SS_OPERATION                16
#define MAP_ERR_SS_ERROR_STATUS                     17
#define MAP_ERR_SS_NOT_AVAILABLE                    18
#define MAP_ERR_SS_SUBSCRIPTION_VIOLATION           19
#define MAP_ERR_SS_INCOMPATIBILITY                  20
#define MAP_ERR_UNKNOWN_ALPHABET                    71
#define MAP_ERR_USSD_BUSY                           72
#define MAP_ERR_PW_REGISTRATION_FAILURE             37
#define MAP_ERR_NEGATIVE_PW_CHECK                   38
#define MAP_ERR_NUMBER_OF_PW_ATTEMPTS_VIOLATION     43
#define MAP_ERR_SHORT_TERM_DENIAL                   29
#define MAP_ERR_LONG_TERM_DENIAL                    30


/* Short message service error codes. */

#define MAP_ERR_SUBSCRIBER_BUSY_FOR_MT_SMS          31
#define MAP_ERR_SM_DELIVERY_FAILURE                 32
#define MAP_ERR_MESSAGE_WAITING_LIST_FULL           33
#define MAP_ERR_ABSENT_SUBSCRIBER_SM                6


/* V1 error codes (not defined by V2 and V4). */

#define MAP_ERR_UNKNOWN_BASE_STATION                2
#define MAP_ERR_UNKNOWN_LOC_AREA                    4
#define MAP_ERR_UNALLOCATED_ROAMING_NUMBER          6
#define MAP_ERR_ILLEGAL_MS                          9
#define MAP_ERR_INSUFFICIENT_BEARER_CAPABILITIES    12
#define MAP_ERR_INVALID_TARGET_BASE_STATION         23
#define MAP_ERR_NO_RADIO_RESOURCE_AVAILABLE         24
#define MAP_ERR_V1_BUSY_SUBSCRIBER                  28
#define MAP_ERR_V1_NO_SUBSCRIBER_REPLY              29
#define MAP_ERR_RADIO_CONGESTION                    30
#define MAP_ERR_IMPOSSIBLE_CALL_COMPLETION          31
#define MAP_ERR_PASSWORD_REGISTRATION_FAILURE       37
#define MAP_ERR_NEGATIVE_PASSWORD_CHECK             38



/*------------------------------------------------------------------------------
 *                                                                            
 *  MAP Application Context constants.
 *
 */

#define MAP_OID_CPT_CCITT            0
#define MAP_OID_CPT_IDEN_ORG         4
#define MAP_OID_CPT_ETSI             0
#define MAP_OID_CPT_MOBILE_DOMAIN    0
#define MAP_OID_CPT_GSM_NETWORK      1
#define MAP_OID_CPT_AC_ID            0



#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_MAP_C_H_) */



