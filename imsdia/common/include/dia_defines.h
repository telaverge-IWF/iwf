/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: dia_defines.h,v $
 * LOG: Revision 3.20.6.4.6.1.4.1.4.1.2.1.4.2.2.1  2020/02/14 11:36:10  jkchaitanya
 * LOG: TCP Timeout fix ported from DRE
 * LOG:
 * LOG: Revision 3.20.6.4.6.1.4.1.4.1.2.1.4.2  2014/10/27 08:28:37  pramana
 * LOG: changes for HA HotStandBy
 * LOG:
 * LOG: Revision 3.20.6.4.6.1.4.1.4.1.2.1.4.1  2014/09/16 09:35:37  jkchaitanya
 * LOG: changes for tickets 472, 473 and bug 4475
 * LOG:
 * LOG: Revision 3.20.6.4.6.1.4.1.4.1.2.1  2014/07/02 06:39:26  millayaraja
 * LOG: updated to handle answer message without mandatory field missing
 * LOG:
 * LOG: Revision 3.20.6.4.6.1.4.1.4.1  2014/05/06 13:09:12  jkchaitanya
 * LOG: changes for ccfh feature
 * LOG:
 * LOG: Revision 3.20.6.4.6.1.4.1  2013/12/13 09:34:58  vsarath
 * LOG: Merged the session-splict changes
 * LOG:
 * LOG: Revision 3.20.6.4.6.1  2013/03/12 04:47:30  vsarath
 * LOG: Fix for coverity issue
 * LOG:
 * LOG: Revision 3.20.6.4  2012/11/20 17:39:44  pramana
 * LOG: Merged from CMAPI branch for 212-07 release
 * LOG:
 * LOG: Revision 3.20.6.1.12.1  2012/11/20 10:21:54  rgovardhan
 * LOG: merge from 00 Nov20Rel
 * LOG:
 * LOG: Revision 3.20.6.2  2012/11/06 16:31:20  pramana
 * LOG: Reverse merged from B-DRE-0212-00-COMP and B-DRE-0212-00-TLS branches for 212-06 release
 * LOG:
 * LOG: Revision 3.20.6.1.16.1  2012/11/06 08:50:05  vsarath
 * LOG: Added for TLS enhancements
 * LOG:
 * LOG: Revision 3.20.6.1.18.1  2012/11/05 13:00:24  mallikarjun
 * LOG: Bug 385 fixes
 * LOG:
 * LOG: Revision 3.20.6.1  2012/10/03 15:09:39  cprem
 * LOG: Merged from ERLBF branch B-DRE-0212-02
 * LOG:
 * LOG: Revision 3.20.12.1  2012/09/20 07:36:42  cprem
 * LOG: Added a macro for max number of dictionary id's that can be configured per peer.
 * LOG:
 * LOG: Revision 3.20  2010/08/19 11:26:01  nvijikumar
 * LOG: Porting changes from B-MOTO-IDIA-0421-00
 * LOG: 1. New Overload implimentation changes are not being ported.
 * LOG: 2. Force disconnect changes are not being ported.
 * LOG:
 * LOG: Revision 3.19  2009/08/25 10:18:01  rajeshak
 * LOG: Fix for Issue:2322 (IDS unable to send Heartbeat Message to DMC client)
 * LOG:
 * LOG: Revision 3.18  2009/07/13 06:02:49  rajeshak
 * LOG: Reverting back session table changes.
 * LOG:
 * LOG: Revision 3.17  2009/06/29 14:34:09  rajeshak
 * LOG: Changes done for performance enhancement (splitting the session table).
 * LOG:
 * LOG: Revision 3.16  2009/04/09 12:43:19  nvijikumar
 * LOG: HeartBeat support for MML API Interface
 * LOG:
 * LOG: Revision 3.15  2009/04/07 14:37:32  sureshj
 * LOG: Defined indications for Overload and Overload abate.
 * LOG:
 * LOG: Revision 3.14  2009/03/19 13:27:07  sureshj
 * LOG: DIA_VERSION defined
 * LOG:
 * LOG: Revision 3.13  2009/03/19 03:08:54  rajeshak
 * LOG: Enhanced MML API support.
 * LOG:
 * LOG: Revision 3.12  2009/03/03 10:47:26  nvijikumar
 * LOG: New event src for IDS down stream msg handling at stack
 * LOG:
 * LOG: Revision 3.11  2009/01/03 06:35:21  nvijikumar
 * LOG: Fix for Typo in define
 * LOG:
 * LOG: Revision 3.10  2009/01/03 06:23:48  rajeshak
 * LOG: New defines added
 * LOG:
 * LOG: Revision 3.9  2008/12/05 11:44:26  nvijikumar
 * LOG: Alarm support
 * LOG:
 * LOG: Revision 3.8  2008/10/31 05:28:53  nvijikumar
 * LOG: IssueID:1189
 * LOG: FeatureID: none
 * LOG: Description: Introducing additional TQs and Threads for better
 * LOG:              Performance on PP50
 * LOG:
 * LOG: Revision 3.7  2008/09/08 14:01:54  ssaxena
 * LOG:  Added a new Source for redundancy messages from Diameter stack to Application. (Hemant)
 * LOG:
 * LOG: Revision 3.6  2008/08/27 10:23:08  ssaxena
 * LOG: Missing parenthesis in INDICATION_TO_TEXT
 * LOG:
 * LOG: Revision 3.5  2008/08/25 05:56:56  ssaxena
 * LOG: New defines for Failover and Failback
 * LOG:
 * LOG: Revision 3.4  2008/06/13 11:06:44  hbhatnagar
 * LOG: Added the TLS related defines
 * LOG:
 * LOG: Revision 3.3  2008/04/07 18:23:36  hbhatnagar
 * LOG: Added new define to indicate error in case of proxy
 * LOG:
 * LOG: Revision 3.2  2008/04/01 16:00:08  hbhatnagar
 * LOG: Changes for Proxy and Relay support (3.0 release) - (Viji, Hemant)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:21  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.14  2008/03/27 11:50:34  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.11.4.2  2007/04/19 09:27:34  nvijikumar
 * LOG: Defines for Successful Result code range.
 * LOG:
 * LOG: Revision 2.11.4.1  2007/03/13 15:31:26  nvijikumar
 * LOG: Moved error code defines here from dia_err.h file.
 * LOG:
 * LOG: Revision 2.11  2007/01/12 13:47:20  nvijikumar
 * LOG: Provided TO_TEXT macros.
 * LOG:
 * LOG: Revision 2.10  2006/12/20 15:01:26  tpanda
 * LOG: New GCS source added for incoming messages from peer
 * LOG:
 * LOG: Revision 2.9  2006/11/30 13:41:24  hbhatnagar
 * LOG: Shifted here the declaration of DCCA ERROR from DCCA Module
 * LOG:
 * LOG: Revision 2.8  2006/11/25 02:03:01  nvijikumar
 * LOG: changes for redundancy
 * LOG:
 * LOG: Revision 2.7  2006/11/24 16:23:24  hbhatnagar
 * LOG: inserted the declaration for stack release indication from DCCA module
 * LOG:
 * LOG: Revision 2.6  2006/11/16 15:00:20  tpanda
 * LOG: Minor changes for redundancy
 * LOG:
 * LOG: Revision 2.5  2006/11/14 10:29:24  nvijikumar
 * LOG:
 * LOG: define for DCCA_FEATURE used in DCCA module.
 * LOG:
 * LOG: Revision 2.4  2006/10/30 16:14:50  yranade
 * LOG: Update.
 * LOG:
 * LOG: Revision 2.3  2006/10/27 09:19:17  nvijikumar
 * LOG: Define for Acct Interim timeout.
 * LOG:
 * LOG: Revision 2.2  2006/10/25 11:05:51  hbhatnagar
 * LOG: DCCA Integration with ITS_Diameter (badri)
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.13  2006/09/13 08:55:18  yranade
 * LOG: Defines added for ITS-Diameter.
 * LOG:
 * LOG: Revision 1.12  2006/06/15 11:52:26  kamakshilk
 * LOG: DIA_MAX_EVENT_SIZE changed to 4096
 * LOG:
 * LOG: Revision 1.11  2006/06/12 12:32:04  yranade
 * LOG: Enhancements to the way, message is formatted when sending to the application.
 * LOG: Used to fix issue in routing when applicationid in the header is 0, for
 * LOG: applications like Rf-Ro, GqGq'
 * LOG:
 * LOG: Revision 1.10  2006/05/05 10:26:16  yranade
 * LOG: Added indication with data.
 * LOG:
 * LOG: Revision 1.9  2006/04/07 11:35:46  yranade
 * LOG: DoxyGen Compatible Code Comments.
 * LOG:
 * LOG: Revision 1.8  2006/04/06 11:21:54  adutta
 * LOG: Added new defines
 * LOG:
 * LOG: Revision 1.7  2006/03/18 11:56:33  nvijikumar
 * LOG: Added corrupted message indication.(yranade)
 * LOG:
 * LOG: Revision 1.6  2006/03/15 09:56:29  yranade
 * LOG: Added DIA_DIR_BIT.
 * LOG:
 * LOG: Revision 1.5  2006/03/13 16:27:58  yranade
 * LOG: Added more defines, for position markers in the message.
 * LOG:
 * LOG: Revision 1.4  2006/03/13 05:16:10  adutta
 * LOG: Event types/size defined
 * LOG:
 * LOG: Revision 1.3  2006/03/13 05:07:11  yranade
 * LOG: Added Msg Types to discriminate message and indications from Diameter
 * LOG: stack to application.
 * LOG:
 * LOG: Revision 1.2  2006/03/03 11:39:56  adutta
 * LOG: App source defined
 * LOG:
 * LOG: Revision 1.1  2006/03/02 13:03:08  tpanda
 * LOG: Building IMS Infrastructure
 * LOG:
 *
 * ID: $Id: dia_defines.h,v 3.20.6.4.6.1.4.1.4.1.2.1.4.2.2.1 2020/02/14 11:36:10 jkchaitanya Exp $
 ****************************************************************************/
#ident "$Id: dia_defines.h,v 3.20.6.4.6.1.4.1.4.1.2.1.4.2.2.1 2020/02/14 11:36:10 jkchaitanya Exp $"

#ifndef DIA_DEFINES_H
#define DIA_DEFINES_H


#define DIA_VERSION                     1
#define MAX_WORKERS_PER_MODULE          10

#define MIN_ROUTER_THREADS           1
#define MAX_ROUTER_THREADS           25

/* Session Table Id */
#define SESSION_TABLE_ID          0x52


#define DIA_DIST_MODULE_NAME         "Distribution"
#define DIA_CHARGING_MODULE_NAME     "Charging"
#define DIA_POLICY_MODULE_NAME       "Policy"
#define DIA_MAP_IWF_MODULE_NAME      "MA-IWF"
#define DIASTACK_TQ_NAME             "ITSDiaTQ"
#define DIA_DCCA_MODULE_NAME         "DCCA"
#define DCCA_FEATURE_NAME            "DCCA"
#define DIASTACK_SENDER_TQ_NAME      "ITSDiaSenderTQ"

/* Define Application Ids */
#define DIA_BASE_NASREQ_APPID		1
#define DIA_BASE_DIAMMIP_APPID		2
#define DIA_BASE_ACCOUNTING_APPID 	3

/**
 *  Event sources 
 **/
#define ITS_DIA_SRC                  (0xFFD1U)
#define ITS_APP_SRC                  (0xFFD2U)
#define ITS_DCCA_SRC                 (0xFFD3U)
#define ITS_DIAMETER                 ((1<<14)|(1))

#define DIA_APP_INST                 (0xFFD5U)
#define DIA_NET_INST                 (0xFFD6U)
#define DIASTACK_TQ_INST             (0xFFD7U)
#define DIA_APP_REM_SESS_INST        (0xFFD8U)
/* GCS source from Application to Network --Downstream */
#define DIA_GCS_APP_INST             (0xFFD9U)
#define DIA_GCS_APP_REM_SESS_INST    (0xFFDAU)
/* GCS source from Network to Application --Upstream */
#define DIA_GCS_NO_SRC_INST          (0xFFDBU)
#define DIA_GCS_NET_INST             (0xFFDCU)
/* Dynamic Peer Discovery */
#define DIA_DYN_PEER_INST            (0xFFDDU)

/** 
 * Added a new Source for redundancy messages
 * from Diameter stack to Application.
 */
#define DIA_REDUNDANCY_SRC           (0xFFDDU)

#define DIASTACK_SENDER_TQ_INST      (0xFFDEU)

#define DIA_IDS_APP_INST             (0xFFDFU)

/* Event size */
#define DIA_MAX_EVENT_SIZE                (4096)

#define ITS_DIA_MSG_TYPE_DATA             (0x01U)
#define ITS_DIA_MSG_TYPE_IND              (0x02U)
#define ITS_DIA_MSG_TYPE_IND_WITH_DATA    (0x03U)

#define ITS_DIA_MSG_TYPE_DATA_REQ         (0x04U)
#define ITS_DIA_MSG_TYPE_DATA_ANS         (0x05U)

#define DIA_DATA_POS        9

#define DIA_DIR_BIT        0x8000


/*
 * List of Indications from the Dimeter-Stack
 */

#define DISCONECT_IND_FROM_STACK               2
#define TIME_OUT_IND_FROM_STACK                3
#define AUTH_LIFE_TIME_OUT_IND_FROM_STACK      4
#define AUTH_GRACE_TIME_OUT_IND_FROM_STACK     5
#define ABORT_IND_FROM_STACK                   6
#define CORRUPTED_MSG_IND_FROM_STACK           7
#define ACCT_INTERIM_TIME_OUT_IND_FROM_STACK   8
#define GCS_CTX_INSERT_IND_FROM_STACK          9
#define GCS_CTX_MODIFY_IND_FROM_STACK          10
#define GCS_CTX_REMOVE_IND_FROM_STACK          11
#define INVALID_AVP_LEN_ERR_IND_FROM_STACK     12
#define APP_REL_SESS_IND_FROM_STACK            13  // App request rel session
#define MANDATORY_AVP_MISSING_IND_FROM_STACK   14 //Inidcation to app for base Mandatory avp missing
#define APP_CREATE_SESS_IND_FROM_STACK         15 // Indication from app to create a session

/**
 * New indication defines for proxy. Starts from 21
 */ 
#define MSG_INVALID_IND_FROM_STACK             21

/**
 * New indication define for Failover and Failback 
 */
#define FAILOVER_IND_FROM_STACK             31
#define FAILBACK_IND_FROM_STACK             32

/**
* New Indications defined for Overload control
*/
#define OVERLOAD_IND_FROM_STACK             41
#define OVLD_ABATED_IND_FROM_STACK          42
#define PEER_DOWN_IND_FROM_STACK            45
#define PEER_CONG_START_IND_FROM_STACK      46
#define PEER_CONG_ABATE_IND_FROM_STACK      47

#define INDICATION_TO_TEXT(x) \
    ((x==AUTH_LIFE_TIME_OUT_IND_FROM_STACK)    ?  \
     "AUTH_LIFE_TIME_OUT_IND_FROM_STACK" :                                    \
    ((x==AUTH_GRACE_TIME_OUT_IND_FROM_STACK)   ?  \
     "AUTH_GRACE_TIME_OUT_IND_FROM_STACK" :                                   \
    ((x==AUTH_GRACE_TIME_OUT_IND_FROM_STACK)   ?  \
     "AUTH_GRACE_TIME_OUT_IND_FROM_STACK" :                                   \
    ((x==CORRUPTED_MSG_IND_FROM_STACK)         ?  \
      "CORRUPTED_MSG_IND_FROM_STACK" :                                         \
    ((x==ACCT_INTERIM_TIME_OUT_IND_FROM_STACK) ?  \
     "ACCT_INTERIM_TIME_OUT_IND_FROM_STACK" :                                 \
    ((x==ABORT_IND_FROM_STACK)           ? "ABORT_IND_FROM_STACK"          :  \
    ((x==DISCONECT_IND_FROM_STACK)       ? "DISCONECT_IND_FROM_STACK"      :  \
    ((x==TIME_OUT_IND_FROM_STACK)        ? "TIME_OUT_IND_FROM_STACK"       :  \
    ((x==GCS_CTX_INSERT_IND_FROM_STACK)  ? "GCS_CTX_INSERT_IND_FROM_STACK" :  \
    ((x==GCS_CTX_MODIFY_IND_FROM_STACK)  ? "GCS_CTX_MODIFY_IND_FROM_STACK" :  \
    ((x==GCS_CTX_REMOVE_IND_FROM_STACK)  ? "GCS_CTX_REMOVE_IND_FROM_STACK" :  \
    ((x==FAILOVER_IND_FROM_STACK)       ? "FAILOVER_IND_FROM_STACK"      :  \
    ((x==FAILBACK_IND_FROM_STACK)       ? "FAILBACK_IND_FROM_STACK"      :  \
    ((x==OVERLOAD_IND_FROM_STACK)       ? "OVERLOAD_IND_FROM_STACK"      :  \
    ((x==OVLD_ABATED_IND_FROM_STACK)       ? "OVLD_ABATED_IND_FROM_STACK":  \
    ((x==PEER_CONG_START_IND_FROM_STACK)          ? "PEER_CONG_START_IND_FROM_STACK" : \
    ((x==PEER_CONG_ABATE_IND_FROM_STACK)          ? "PEER_CONG_ABATE_IND_FROM_STACK" : \
((x==INVALID_AVP_LEN_ERR_IND_FROM_STACK) ? "INVALID_AVP_LEN_ERR_IND_FROM_STACK" : \
    "INVALID"))))))))))))))))


/*
 *List of Indications from the DCCA-Stack 
 */

#define DCCA_RELEASE_SESSION_IND        0xFFFFFF

/* The below define is returned as permanent error by DCCA stack
 * in case of DCCA State Machine Error and should interpreted as
 * DCCA ERROR.The value given is 5040 which is not defined in 
 * RFC4006 and can be changed.
 */
#define ITS_DIA_DCCA_ERROR            5040

/*
 * List of Return Values
 */
#define DIA_REGISTRATION_ERROR                 0x7FFFFFFF
#define DIA_SUCCESS                            0
#define DIA_FAILURE                            -1 //error
#define DIA_SESSION_ID_NOT_FOUND               0xFF
#define DIA_CONFIG_FILE_NOT_FOUND              0x1FF
#define DIA_STACK_NOT_INITIALIZED              0x2FF
#define DIA_EVENT_SENT_TO_APP_SUCCESS          0x3FF
#define DIA_EVENT_SENT_TO_APP_FAILED           0x4FF
#define DIA_APP_ID_NOT_REGISTERED              0x5FF


/* 
 * RFC 3588: Section 7: Error Values
 */

/* 
 * Informational Errors 
 */

#define ITS_DIA_MULTI_ROUND_AUTH      1001
#define ITS_DIA_INVALID_EVENT         1100

/* 
 * Success 
 */
#define ITS_DIA_SUCCESS               2001
#define ITS_DIA_LIMITED_SUCCESS       2002
#define ITS_DIA_SUCCESS_MIN_RANGE     2000
#define ITS_DIA_SUCCESS_MAX_RANGE     2999

/* 
 * Protocol Errors 
 */
#define ITS_DIA_PROT_ERR_MIN_RANGE    3000
#define ITS_DIA_CMD_UNSUPPORTED       3001
#define ITS_DIA_UNABLE_TO_DELIVER     3002
#define ITS_DIA_REALM_NOT_SERVED      3003
#define ITS_DIA_TOO_BUSY              3004
#define ITS_DIA_LOOP_DETECTED         3005
#define ITS_DIA_REDIRECT_INDICATION   3006
#define ITS_DIA_APP_UNSUPPORTED       3007
#define ITS_DIA_INVALID_HDR_BITS      3008
#define ITS_DIA_INVALID_AVP_BITS      3009
#define ITS_DIA_UNKNOWN_PEER          3010
#define ITS_DIA_PROT_ERR_MAX_RANGE    3999

/* 
 * Transient Failures 
 */
#define ITS_DIA_4XXX_ERR_MIN_RANGE    4000
#define ITS_DIA_AUTH_REJECTED         4001
#define ITS_DIA_OUT_OF_SPACE          4002
#define ITS_DIA_ELECTION_LOST         4003
#define ITS_DIA_4XXX_ERR_MAX_RANGE    4999

/* 
 * Permanent Failures 
 */
#define ITS_DIA_5XXX_ERR_MIN_RANGE    5000
#define ITS_DIA_AVP_UNSUPPORTED       5001
#define ITS_DIA_UNKNOWN_SESSION_ID    5002
#define ITS_DIA_AUTHORIZATION_REJECT  5003
#define ITS_DIA_INVALID_AVP_VALUE     5004
#define ITS_DIA_MISSING_AVP           5005
#define ITS_DIA_RESOURCES_EXCEEDED    5006
#define ITS_DIA_CONTRADICTING_AVPS    5007
#define ITS_DIA_AVP_NOT_ALLOWED       5008
#define ITS_DIA_AVP_MULTI_OCCUR       5009
#define ITS_DIA_NO_COMMON_APP         5010
#define ITS_DIA_UNSUPPORTED_VERSION   5011
#define ITS_DIA_UNABLE_TO_COMPLY      5012
#define ITS_DIA_INVALID_BIT_IN_HDR    5013
#define ITS_DIA_INVALID_AVP_LENGTH    5014
#define ITS_DIA_INVALID_MSG_LENGTH    5015
#define ITS_DIA_INVALID_AVP_BIT_COMBO 5016
#define ITS_DIA_NO_COMMON_SECURITY    5017
#define ITS_DIA_5XXX_ERR_MAX_RANGE    5999


/**
 * Defines for Inband-Security-Id AVP
 */
#define DIA_NO_INBAND_SECURITY      0
#define DIA_TLS                     1

/**
 * Defines for the CipherSuiteList
 */
#define MAX_CIPHER_SUITE_SUPPORTED  8
#define CIPHER_SUITE_LIST           (MAX_CIPHER_SUITE_SUPPORTED +1)

/*
 *  Diameter common Alarm Range
 */
#define DIA_ALARM_START    15000
#define DIA_ALARM_END      15499

/*
 * Defines for Sending Indication
 */
#define MAX_INDIC_BUFF_LEN       255
#define MAX_SESSION_ID_LEN       250
#define MAX_HOST_NAME_LEN        60
#define MAX_REALM_NAME_LEN       60
#define MAX_ALT_HOST_NAME_LEN    60
#define MAX_ALT_REALM_NAME_LEN   60

#define MAX_SWITCHOVER_TIME_CORRECTION 3
 /*
  * Defines for Dictionaries.
  */

#define MAX_DICT_IDS_PER_PEER 9

/*
 * API
 */

void  DIA_Alarm(int which, const char *file, const int line,const char *format, ...);

/*
 * IDS Commands
 */ 
#define GET_IDC_CONN_TABLE_SZ         1
#define GET_IDC_CONN_INFO             2

typedef void (*DIA_CALLBACK)(void *arg);
typedef void (*DMS_CALLBACK)(void *arg1, void *arg2);
#endif
