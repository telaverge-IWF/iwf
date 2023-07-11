/*********************************-*-H-*-**************************************
 * *                                                                          *
 * *          Copyright 2012 Diametriq, LLC All Rights Reserved.              *
 * *            Manufactured in the United States of America.                 *
 * *      1990 W. New Haven Ste. 303, Melbourne, Florida, 32904 U.S.A.        *
 * *                                                                          *
 * *   This product and related documentation is protected by copyright and   *
 * *   distributed under licenses restricting its use, copying, distribution  *
 * *   and decompilation.  No part of this product or related documentation   *
 * *   may be reproduced in any form by any means without prior written       *
 * *   authorization of Diametriq and its licensors, if any.                  *
 * *                                                                          *
 * *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 * *   government is subject to restrictions as set forth in subparagraph     *
 * *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 * *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 * *                                                                          *
 * ****************************************************************************/

#ifndef _ALARM_ID_H_
#define _ALARM_ID_H_

//Resource Related Alarms
#define CPU_USAGE_HIGHER_THRESHOLD_CROSSED 10000
#define CPU_USAGE_SECOND_THRESHOLD_CROSSED 10001
#define CPU_USAGE_MINIMUM_THRESHOLD_CROSSED 10002
#define CPU_USAGE_NORMAL 10003

#define MEM_USAGE_HIGHER_THRESHOLD_CROSSED 10100
#define MEM_USAGE_SECOND_THRESHOLD_CROSSED 10101
#define MEM_USAGE_MINIMUM_THRESHOLD_CROSSED 10102
#define MEM_USAGE_NORMAL 10103

#define DISK_USAGE_HIGHER_THRESHOLD_CROSSED 10200
#define DISK_USAGE_NORMAL 10201


//ConfigManager Alarms
//--------------------------------------------
//Mysql monitoring Sub Component
#define CONFIGMGR_MYSQL_SUB_COMP 0
//-------------------------------------------
#define MYSQL_CONNECTIVITY_LOST 1
#define MYSQL_CONNECTIVITY_RESTORED 2
#define MYSQL_REPLICATION_FAILED 3
#define MYSQL_REPLICATION_RESTORED 4
#define MYSQL_REPLICATION_NOT_IN_SYNC 5

//ConfigManager Sub Component
#define CONFIGMGR_SUB_COMP 1
//-------------------------------------------
#define COMP_CONFIG_RETRY 1



//Availability Manager Alarms
//--------------------------------------------
//Process monitoring Sub Component
#define AVAMGR_SUB_COMP_PROCESS_MONITORING 1
//-------------------------------------------
#define HIGH_PRIORITY_PROC_DOWN 1
#define HIGH_PRIORITY_PROC_UP 2
#define LOW_PRIORITY_PROC_DOWN 3
#define LOW_PRIORITY_PROC_UP 4
#define DRE_GRACEFUL_SHUTDOWN 5
#define DRE_UP_AFTER_SHUTDOWN 6
#define DRE_LICENSE_VIOLATION 7
#define DRE_CLEAR_LICENSE_VIOLATION 8


//---------------------------------------------------
//Availability/redundancy Sub Component
#define AVAMGR_SUB_COMP_AVAILABILITY 2
//---------------------------------------------------

#define UNPLANNED_SWITCHOVER_TO_STANDBY_INITIATED 1
#define UNPLANNED_SWITCHOVER_TO_STANDBY_SUCCESS 2

#define PLANNED_SWITCHOVER_TO_STANDBY_INITIATED 3
#define PLANNED_SWITCHOVER_TO_STANDBY_SUCCESS 4


#define BOTH_ACTIVE_IN_ACTIVE_STANDBY_MODE  5
#define ACTIVE_STANDBY_RESTORED  6

#define BOTH_STANDBY_IN_ACTIVE_STANDBY_MODE 7
#define ACTIVE_STANDBY_RESTORED_2 8

#define STANDBY_NOT_AVAILABLE 9
#define STANDBY_AVAILABLE 10

//----------------------------------------------
//Interface monitoring sub component
#define AVAMGR_SUB_COMP_INTERFACE_MONITORING 3
//----------------------------------------------
#define CONFIGURED_ETH_INTERFACE_DOWN 1
#define CONFIGURED_ETH_INTERFACE_UP 2


//----------------------------------------------
//Replication sub component
#define AVAMGR_SUB_COMP_REPLICATION 4
//---------------------------------------------
#define REPLICATION_DISABLED 1
#define REPLICATION_RESTORED 2
#define COUCHBASE_DOWN 3
#define COUCHBASE_UP 4
#define COUCHBASE_REBALANCE_STUCK 5
#define COUCHBASE_REBALANCE_RESTORED 6

//----------------------------------------------

//Stack peer connectivity sub component
#define STACK_PEER_CONNECTIVITY 1
//----------------------------------------------
#define CER_OR_CEA_EXCHANGE_FAILURE 1
#define CER_OR_CEA_EXCHANGE_SUCCESS 2
#define CEA_RECEIVED_WITH_WRONG_RESULT_CODE 3
#define SCTP_OR_TCP_CONNECTION_FAILURE 4
#define SCTP_OR_TCP_CONNECTION_ESTABLISHED 5
#define TCP_CONNECTION_FAIL_AND_FAILOVER_TO_PEER 6
#define TCP_CONNECTION_ESTABLISH_AND_FAILBACK_TO_PRIMARY 7
#define TRANSPORT_CONNECTION_CLOSED_WITH_PEER 8
#define MISMATCH_ORIGINHOST_OR_ORIGINREALM_WITH_PEERTABLES 9
#define RECIEVE_MSG_FAILURE_FROM_PEER 10
#define NO_MORE_MSG_FAILURE_FROM_PEER 11
#define FAILED_TO_TRANSMIT_MSG_TO_PEER 12
#define FAILOVER_TRANSMIT_MSG_TO_ALT_PEER 13
#define FAILOVER_TRANSMIT_MSG_TO_ALT_PEER_COMPLETE 14
#define FAILED_TO_DELIVER_THE_MSG 15
#define CEA_RECEIVED_WITH_SUCCESS_RESULT_CODE 16
#define MESSAGE_FORWARD_TO_PEER_SUCCESS 17


//----------------------------------------------
//Stack message processing sub component
#define STACK_MESSAGE_PROCESSING 2
//----------------------------------------------

#define RATE_LIMITING_FILTER_STARTED_REJECTING_THE_MESSAGE 1
#define RATE_LIMITING_FILTER_STOPPED_REJECTING_THE_MESSAGE 2
#define DPR_RECEIVED_WITH_CAUSE_DO_NOT_WANT_TO_TALK_TO_YOU 3
#define DPR_RECEIVED_WITH_CAUSE_BUSY 4
#define DPR_RECEIVED_WITH_CAUSE_REBOOT 5
#define TRANSFORM_PLUGIN_PROVISIONED_OR_UNLOADED 6
#define DWA_RECEIVED_WITH_WRONG_RESULT_CODE 7
#define DPA_RECEIVED_WITH_INVALID_RESLUT_CODE 8
#define INVALID_VERSION 9

//----------------------------------------------
//Stack general sub component
#define STACK_GENERAL 3
//----------------------------------------------
#define DIAMETER_STACK_FAILED_TO_INITIALIZE 1
#define DIAMETER_STACK_TERMINATION 2
#define DIAMETER_STACK_PEER_DELETED_OR_DISABLED 3
#define DIAMETER_STACK_SUCCESSFULLY_INITIALIZED 4
#define DIAMETER_STACK_STARTED_SUCCESSFULLY 5


//----------------------------------------------
//CLI and GUI related Alarms
#define MAX_ADMIN_LOGIN_RETRY 13100

//---------------------------------------------
//IWF message processing sub component
#define IWF_TRANSLATOR_SUB_COMP 5
//---------------------------------------------
#define LICENSE_VIOLATION_FOR_CAP_RO 1
#define LICENSE_VIOLATION_FOR_CAP_RO_TSL 2
#define LICENSE_VIOLATION_FOR_MAP_S6A 3
#define LICENSE_VIOLATION_FOR_S6A_MAP 4

#endif
