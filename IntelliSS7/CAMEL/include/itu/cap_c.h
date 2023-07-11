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
 *  ID: $Id: cap_c.h,v 9.1 2005/03/23 12:51:11 cvsadmin Exp $
 *
 *----------------------------------------------------------------------------*/

#if !defined(_CAP_C_H_)
#define _CAP_C_H_

#include <its.h>

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */





/*------------------------------------------------------------------------------
 *                                                                            
 *  CAP protocol constants.
 *
 */

/*
 *  Operation codes (V2 and V3).
 */



/* gsmSCF activation ASE/Package. */
                                                
#define CAP_OP_INITIAL_DP                           0


/* gsmSCF/gsmSRF activation of assist ASE/Package. */

#define CAP_OP_ASSIST_REQUEST_INSTRUCTIONS          16


/* Assist connection establishment ASE/Package. */ 

#define CAP_OP_ESTABLISH_TEMPORARY_CONNECTION       17


/* Generic disconnect resource ASE/Package. */

#define CAP_OP_DISCONNECT_FORWARD_CONNECTION        18


/* Non-assisted connection establishment ASE/Package. */ 

#define CAP_OP_CONNECT_TO_RESOURCE                  19


/* Connect (elementary gsmSSF function) ASE/Package. */

#define CAP_OP_CONNECT                              20


/* Call handling (elementary gsmSSF function) ASE/Package. */

#define CAP_OP_RELEASE_CALL                         22


/* BCSM Event handling ASE/Package. */

#define CAP_OP_REQUEST_REPORT_BCSM_EVENT            23
#define CAP_OP_EVENT_REPORT_BCSM                    24


/* gsmSSF call processing ASE/Package. */

#define CAP_OP_CONTINUE                             31
#define CAP_OP_CONTINUE_WITH_ARGUMENT               56     /* V3 only. */


/* Timer ASE/Package. */

#define CAP_OP_RESET_TIMER                          33


/* Billing ASE/Package. */

#define CAP_OP_FURNISH_CHARGING_INFORMATION         34


/* Charging ASE/Package. */

#define CAP_OP_APPLY_CHARGING                       35
#define CAP_OP_APPLY_CHARGING_REPORT                36


/* Traffic Management Package. */

#define CAP_OP_CALL_GAP                             41     /* V3 only. */


/* Call report ASE/Package. */

#define CAP_OP_CALL_INFORMATION_REPORT              44
#define CAP_OP_CALL_INFORMATION_REQUEST             45


/* Signalling control ASE/Package. */

#define CAP_OP_SEND_CHARGING_INFORMATION            46


/* Specialized resource control ASE/Package. */

#define CAP_OP_PLAY_ANNOUNCEMENT                    47
#define CAP_OP_PROMPT_AND_COLLECT_USER_INFORMATION  48
#define CAP_OP_SPECIALIZED_RESOURCE_REPORT          49


/* Cancel ASE/Package. */

#define CAP_OP_CANCEL                               53     /* V3 only. */


/* Activity Test ASE/Package. */

#define CAP_OP_ACTIVITY_TEST                        55     /* V3 only. */


/* Sms Activation Package. */

#define CAP_OP_INITIAL_DPSMS                        60     /* V3 only. */


/* Sms Activity Test Package. */

#define CAP_OP_ACTIVITY_TEST_SMS                    61     /* V3 only. */


/* Sms Billing Package. */

#define CAP_OP_FURNISH_CHARGING_INFORMATION_SMS     62     /* V3 only. */


/* Sms Connect Package. */

#define CAP_OP_CONNECT_SMS                          63     /* V3 only. */


/* Sms Event Handling Package. */ 

#define CAP_OP_REQUEST_REPORT_SMS_EVENT             64     /* V3 only. */
#define CAP_OP_EVENT_REPORT_SMS                     65     /* V3 only. */


/* Sms Processing Package. */

#define CAP_OP_CONTINUE_SMS                         66     /* V3 only. */


/* Sms Release Package. */  

#define CAP_OP_RELEASE_SMS                          67     /* V3 only. */


/* Sms Timer Package. */ 

#define CAP_OP_RESET_TIMER_SMS                      68     /* V3 only. */


/* Gprs Activity Test Package. */

#define CAP_OP_ACTIVITY_TEST_GPRS                   70     /* V3 only. */


/* Gprs Charging Package. */

#define CAP_OP_APPLY_CHARGING_GPRS                  71     /* V3 only. */
#define CAP_OP_APPLY_CHARGING_REPORT_GPRS           72     /* V3 only. */


/* Gprs Cancel Package. */

#define CAP_OP_CANCEL_GPRS                          73     /* V3 only. */


/* Gprs Connect Package. */

#define CAP_OP_CONNECT_GPRS                         74     /* V3 only. */


/* Gprs Processing Package. */

#define CAP_OP_CONTINUE_GPRS                        75     /* V3 only. */


/* Gprs Exception Information Package. */

#define CAP_OP_ENTITY_RELEASED_GPRS                 76     /* V3 only. */


/* Gprs Billing Package. */

#define CAP_OP_FURNISH_CHARGING_INFORMATION_GPRS    77     /* V3 only. */


/* Gprs Scf Activation Package. */

#define CAP_OP_INITIAL_DPGPRS                       78     /* V3 only. */


/* Gprs Release Package. */ 

#define CAP_OP_RELEASE_GPRS                         79     /* V3 only. */


/* Gprs Event Handling Package. */

#define CAP_OP_EVENT_REPORT_GPRS                    80     /* V3 only. */
#define CAP_OP_REQUEST_REPORT_GPRS_EVENT            81     /* V3 only. */


/* Gprs Timer Package. */

#define CAP_OP_RESET_TIMER_GPRS                     82     /* V3 only. */


/* Gprs Charge Advice Package. */

#define CAP_OP_SEND_CHARGING_INFORMATION_GPRS       83     /* V3 only. */




/*
 *  Error codes (V2 and V3).
 */

#define CAP_ERR_CANCELLED                       0
#define CAP_ERR_CANCEL_FAILED                   1
#define CAP_ERR_ETC_FAILED                      3
#define CAP_ERR_IMPROPER_CALLER_RESPONSE        4
#define CAP_ERR_MISSING_CUSTOMER_RECORD         6
#define CAP_ERR_MISSING_PARAMETER               7
#define CAP_ERR_PARAMETER_OUT_OF_RANGE          8
#define CAP_ERR_REQUESTED_INFO_ERROR            10
#define CAP_ERR_SYSTEM_FAILURE                  11
#define CAP_ERR_TASK_REFUSED                    12
#define CAP_ERR_UNAVAILABLE_RESOURCE            13
#define CAP_ERR_UNEXPECTED_COMPONENT_SEQUENCE   14
#define CAP_ERR_UNEXPECTED_DATA_VALUE           15
#define CAP_ERR_UNEXPECTED_PARAMETER            16
#define CAP_ERR_UNKNOWN_LEG_ID                  17
#define CAP_ERR_UNKNOWN_PDPID                   18      /* V3 only. */
#define CAP_ERR_UNKNOWN_GPRS_REFERENCE          19      /* V3 only. */
#define CAP_ERR_OVERLAPPING_DIALOGUE            20      /* V3 only. */




/*------------------------------------------------------------------------------
 *                                                                            
 *  CAP Application Context constants.
 *
 */

#define CAP_OID_CPT_CCITT            0
#define CAP_OID_CPT_IDEN_ORG         4
#define CAP_OID_CPT_ETSI             0
#define CAP_OID_CPT_MOBILE_DOMAIN    0
#define CAP_OID_CPT_GSM_NETWORK      1



#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_CAP_C_H_) */



