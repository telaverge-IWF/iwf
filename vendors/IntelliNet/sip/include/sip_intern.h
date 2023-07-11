/***************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *  ID: $Id: sip_intern.h,v 9.1 2005/03/23 12:54:27 cvsadmin Exp $
 *
 *  $Log: sip_intern.h,v $
 *  Revision 9.1  2005/03/23 12:54:27  cvsadmin
 *  Begin PR6.5
 *
 *  Revision 1.22  2005/03/21 13:53:24  cvsadmin
 *  PR6.4.2 Source Propagated to Current
 *
 *  Revision 1.21.2.5  2005/03/09 07:13:56  mkrishna
 *  Bug fixing cycle
 *
 *  Revision 1.21.2.4  2005/02/07 14:21:58  mkrishna
 *  Modified for PRACK message.
 *
 *  Revision 1.21.2.3  2005/01/18 06:00:44  mkrishna
 *  separate traces for SIP
 *
 *  Revision 1.21.2.2  2005/01/11 12:54:52  craghavendra
 *  Syslog Enhancements.
 *
 *  Revision 1.21.2.1  2004/12/28 13:59:09  mkrishna
 *  SIP code propagated from Current Branch
 *
 *  Revision 1.21  2004/05/16 08:42:23  sjaddu
 *  TCP support is added of SIP.
 *
 *  Revision 1.20  2004/05/03 07:15:28  akumar
 *  Bug fix.
 *
 *  Revision 1.19  2004/04/29 09:55:36  akumar
 *  Mod for 400 bad req.
 *
 *  Revision 1.18  2004/04/27 11:08:08  sjaddu
 *  Transport layer revamping, hope stable now
 *
 *  Revision 1.17  2004/04/23 13:20:03  sjaddu
 *  Added transport delete function.
 *
 *  Revision 1.16  2004/04/21 06:23:07  sjaddu
 *  Added support functions.
 *
 *  Revision 1.15  2004/04/16 04:57:03  akumar
 *  SIP attributes are configurable thru XML.
 *
 *  Revision 1.14  2004/04/15 12:15:27  sjaddu
 *  Added indications for application.
 *
 *  Revision 1.13  2004/04/05 12:53:56  akumar
 *  Bug fix cycle after testing.
 *
 *  Revision 1.12  2004/04/05 07:34:16  sjaddu
 *  Moved some defines to sip_defines.h .
 *
 *  Revision 1.11  2004/04/05 06:57:01  sjaddu
 *  More unit testing ...
 *
 *  Revision 1.10  2004/04/01 06:41:33  sjaddu
 *  testing is in progress...
 *
 *  Revision 1.9  2004/03/30 11:52:18  sjaddu
 *  Commit after some unit testing.
 *
 *  Revision 1.8  2004/03/25 10:06:40  dsatish
 *  Commit after changes done for ip address data type
 *
 *  Revision 1.7  2004/03/25 06:48:03  akumar
 *  Moved some struct to IntelliSS7/SIP side.
 *
 *  Revision 1.6  2004/03/25 06:06:40  dsatish
 *  Commit After Transport Signature Changes
 *
 *  Revision 1.5  2004/03/25 05:39:56  dsatish
 *  Commit After changing the Transport structure changes
 *
 *  Revision 1.4  2004/03/25 04:46:17  dsatish
 *  Commit after changes in the function signature.
 *
 *  Revision 1.3  2004/03/23 07:32:46  dsatish
 *  commit after adding Strcuture for communication between Tranport and Transaction layer
 *
 *  Revision 1.2  2004/03/19 13:55:16  dsatish
 *  Initial Check in of the changes done for Transport layer.
 *
 *  Revision 1.1  2004/03/19 05:59:57  sjaddu
 *  Added first revsion for sip, work in progress.
 *
 ****************************************************************************/
#ifndef  _SIP_INTERN_H_
#define  _SIP_INTERN_H_

#ifdef __cplusplus
extern "C"
{
#endif 

#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <errno.h>
#include <pthread.h>

#include <its_emlist.h>
#include <its_transports.h>
#include <its_thread.h>
#include <its_trace.h>
#include <its_hash.h>
#include <its_timers.h>

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <its.h>

#include <its_tq_trans.h>
#include <its_ip_trans.h>
#include <its_sockets.h>

#include <sip.h>
#include <sip_defines.h>


/*
 * Trace sub system 
 */
extern ITSDLLAPI TRACE_Data* SIP_TraceData;

#define SIP_TRACE_CRITICAL_STRING  ITS_TRACE_CRITICAL_STRING
#define SIP_TRACE_ERROR_STRING     ITS_TRACE_ERROR_STRING
#define SIP_TRACE_WARNING_STRING   ITS_TRACE_WARNING_STRING
#define SIP_TRACE_DEBUG_STRING     ITS_TRACE_DEBUG_STRING

#define SIP_FILE_STRING            ITS_FILE_STRING
#define SIP_STDOUT_STRING          ITS_STDOUT_STRING
#define SIP_SYSLOG_STRING          ITS_SYSLOG_STRING

#define SIP_CRITICAL_STRING        ITS_CRITICAL_STRING
#define SIP_ERROR_STRING           ITS_ERROR_STRING
#define SIP_WARNING_STRING         ITS_WARNING_STRING
#define SIP_DEBUG_STRING           ITS_DEBUG_STRING

#define SIP_TRACE_FILE       ".its-sip-trace"

#define SIP_TRACE_CRITICAL  0
#define SIP_TRACE_ERROR     1
#define SIP_TRACE_WARNING   2
#define SIP_TRACE_DEBUG     3

#define MALLOC_ERROR          -2001
#define TRANSPORT_INIT_ERROR  -2002
#define INSUFF_MEM_ERROR      -2003
#define BAD_HOST_ERROR        -2004
#define INVALID_ARGS_ERROR    -2005
#define BIND_FAIL_ERROR       -2006
#define COULD_NOT_ADD_TO_TBL  -2007
#define COULD_NOT_GET_INDEX   -2008
#define NO_BIT_SET            -2009

#define SIP_CRITICAL(args) \
    TRACE(SIP_TraceData, SIP_TRACE_CRITICAL, args)

#define SIP_ERROR(args) \
    TRACE(SIP_TraceData, SIP_TRACE_ERROR, args)

#define SIP_WARNING(args) \
    TRACE(SIP_TraceData, SIP_TRACE_WARNING, args)

#define SIP_DEBUG(args) \
    TRACE(SIP_TraceData, SIP_TRACE_DEBUG, args)

typedef struct _sip_transport_info SIP_TRANSPORT_INFO;

typedef enum
{
    SIP_PROXY_SERVER,
    SIP_REDIRECT_SERVER,
    SIP_LOCATION_SERVER,
    SIP_UAC
}
SIP_APP_TYPE;

/* This config structur should include all
   possible config data fro SIP */
typedef struct
{
    SIP_APP_TYPE    type;
    ITS_INT         T1;       /* are in ms */
    ITS_INT         T2;
    ITS_INT         T4;
    ITS_INT         trnTimer;

    SIP_TRANSPORT_INFO *transInfo;
}
SIP_CONFIG_INFO;

extern SIP_CONFIG_INFO    SIP_configInfo;

/* Basic transaction types from rfc 3261 section: 17*/
typedef enum
{
    SIP_ICT,
    SIP_IST,
    SIP_NICT,
    SIP_NIST
}
SIP_TRANSACTION_TYPE;


/* fsm types from rfc 3261 section: 17 */
#define    SIP_IDLE                     0x00 

/* states for INVITE CLIENT transaction */
#define    SIP_ICT_CALLING              0x01
#define    SIP_ICT_PROCEEDING           0x02
#define    SIP_ICT_COMPLETED            0x03
#define    SIP_ICT_TERMINATED           0x04

/* states for INVITE SERVER transaction */
#define    SIP_IST_PROCEEDING           0x01
#define    SIP_IST_COMPLETED            0x02
#define    SIP_IST_CONFIRMED            0x03
#define    SIP_IST_TERMINATED           0x04

/* states for NON-INVITE CLIENT transaction */
#define    SIP_NICT_TRYING              0x01
#define    SIP_NICT_PROCEEDING          0x02
#define    SIP_NICT_COMPLETED           0x03
#define    SIP_NICT_TERMINATED          0x04

/* states for NON-INVITE SERVER transaction */
#define    SIP_NIST_TRYING              0x01
#define    SIP_NIST_PROCEEDING          0x02
#define    SIP_NIST_COMPLETED           0x03
#define    SIP_NIST_TERMINATED          0x04

/* Define for Max table index */
#define SIP_MAX_MSGS         120




/*Parser related  functions */
ITSDLLAPI int
SIP_ParserInit();


/*Transport related functions */

/*
 * for udp these are  local port & ip, for tcp
 * these are of remote 
 */
typedef struct fd_tbl
{
    ITS_USHORT          portNo;
    SOCK_IPv4Addr       ipAddr;    /* This is only for tcp */
    ITS_USHORT          refCnt;
    SIP_TRANSPORT_TYPE  type;
}
SIP_TRANS_TBL;

struct _sip_transport_info
{
   ITS_BOOLEAN      isUp;
   ITS_BOOLEAN      isUpdated;
   SOCK_IPv4Addr    ipAddr;
   ITS_USHORT       udpPortNo;
   ITS_USHORT       tcpPortNo;
   ITS_USHORT       maxConn;
   ITS_MUTEX        transMutex;
   ITS_USHORT       currConn;
   ITS_INT          cntlFd[2];
   SIP_TRANS_TBL    *transTbl;
   ITS_SockPollInfo *spInfo;
};

#define SIP_DEFAULT_SOCK_INDEX  0
#define SIP_DEFAULT_SOCK_PORT   5060
#define SIP_INVALID_PORT        0xFFFF

ITSDLLAPI int  
SIP_TransportInit(SIP_TRANSPORT_INFO *trans);

ITSDLLAPI int 
SIP_TransportCreate(SOCK_IPv4Addr ip, int portno,
                    SIP_TRANSPORT_TYPE type, SIP_TRANSPORT_INFO *trans);

ITSDLLAPI int 
SIP_TransportDelete(ITS_INT index, SIP_TRANSPORT_INFO *trans);

ITSDLLAPI int
SIP_TransportSend(SIP_DEST_INFO *destinfo ,int index, 
                 ITS_CHAR *buf, SIP_TRANSPORT_INFO *trans);

ITSDLLAPI int
SIP_TransportRecv(SIP_TRANSPORT_INFO *trans);

/*Transaction related functions */
typedef struct _sip_transaction_context SIP_TRANSACTION_CTXT;

/* Entry function into the specific transaction type */
#define SIP_TRANSACTION_RID     0x1

typedef int (*SIP_TransactionEntryFunc)(SIP_TRANSACTION_CTXT *ctxt,
                                    SIP_MSG_TYPE type,
                                    SIP_MSG *msg, ITS_USHORT src);

ITSDLLAPI int
SIP_ICTEntry(SIP_TRANSACTION_CTXT *ctxt,
                                    SIP_MSG_TYPE type,
                                    SIP_MSG *msg, ITS_USHORT src);
ITSDLLAPI int
SIP_ISTEntry(SIP_TRANSACTION_CTXT *ctxt,
                                    SIP_MSG_TYPE type,
                                    SIP_MSG *msg, ITS_USHORT src);
ITSDLLAPI int
SIP_NICTEntry(SIP_TRANSACTION_CTXT *ctxt,
                                    SIP_MSG_TYPE type,
                                    SIP_MSG *msg, ITS_USHORT src);
ITSDLLAPI int
SIP_NISTEntry(SIP_TRANSACTION_CTXT *ctxt,
                                    SIP_MSG_TYPE type,
                                    SIP_MSG *msg, ITS_USHORT src);

typedef int (*SIP_TransactionHandler)(SIP_TRANSACTION_CTXT *ctxt,
                                     SIP_MSG *msg, ITS_USHORT src);

typedef struct
{
    SIP_TransactionHandler transProc;
}
SIP_FSM_MAP_TABLE;

typedef struct
{
    SIP_CALLID_HDR callId;
    SIP_CSEQ_HDR cSeq;
    SIP_VIA_HDR *via;
}
SIP_TRANSACTION_KEY;

#define SIP_MAX_RETRANSMISSIONS     7

struct _sip_transaction_context
{
    struct _sip_transaction_context * next;

    /* callId, cSeq & via as a key */
    SIP_CALLID_HDR      callId;
    SIP_RACK_HDR        rack;
    SIP_CSEQ_HDR        cSeq;
    SIP_VIA_HDR         topVia;
    SIP_FROM_HDR        from;
    SIP_TO_HDR          to;
    SIP_MAXFWDS_HDR     maxFwds;
    

    /*lock info */
    ITS_BOOLEAN locked;
    ITS_TIME    lockTime;
    ITS_BOOLEAN purge;    /* Fsm sets this flag when it wants to delete tr*/

    /* Transaction info*/
    ITS_INT      tId;               /* Transaction ID*/
    ITS_CHAR     *msgBuf;           /* encoded msg buf for retransmission*/
    SIP_MSG      *sipMsg;           /* holds last req/resp msg for 5xx */ 
    SIP_MSG_TYPE lastRes;
    
    /*state machine */    
    SIP_TRANSACTION_TYPE       sipTransaction;   /*transaction type*/ 
    SIP_FSM_STATE              fsmState;         /* fsm_type*/
    SIP_TransactionEntryFunc   entryFunc;        /* entry function into FSM*/
    ITS_BOOLEAN                isReliableResp;  /* sets this flag when it wants
                                                 to provide reliable response */


    /*Timer stuff*/
    ITS_UINT    timerKey;           /* 0 means no timer is running */
    ITS_UINT    reTranstimer;       /* Retransmission count Max=7 */ 

    /* Transport type*/    
    ITS_USHORT              port;       /*Local port for this tr*/

    /*destination stuff*/
    SIP_DEST_INFO   destInfo;
};

/*
 * SIP configuration related strings
 */
#define SIP_UDP_PORTNO_STRING   "UDPPortNo"
#define SIP_TCP_PORTNO_STRING   "TCPPortNo"
#define SIP_IP_ADDR_STRING      "ipAddr"
#define SIP_TIMER_T1_STRING     "T1"
#define SIP_TIMER_T2_STRING     "T2"

ITSDLLAPI int
SIP_TransactionLayerInit();

ITSDLLAPI int 
SIP_InitTransactionTables();

ITSDLLAPI int
SIP_TermTransactionTables();

ITSDLLAPI int
SIP_ICTLoadFsm();

ITSDLLAPI int
SIP_ISTLoadFsm();

ITSDLLAPI int
SIP_NICTLoadFsm();

ITSDLLAPI int
SIP_NISTLoadFsm();

ITSDLLAPI int 
SIP_HandleMsg(ITS_EVENT* event, ITS_USHORT src);

ITSDLLAPI int 
SIP_HandleTimeOut(ITS_EVENT* event);

ITSDLLAPI SIP_TRANSACTION_CTXT *
SIP_CreateTransactionCtxt(SIP_MSG *msg,
                          ITS_INT *returnCode);               

ITSDLLAPI SIP_TRANSACTION_CTXT *
SIP_FindTransactionCtxt(SIP_TRANSACTION_KEY *key,
                        ITS_INT *returnCode);

ITSDLLAPI int
SIP_CommitTransactionCtxt(SIP_TRANSACTION_CTXT *ctxt);

ITSDLLAPI int
SIP_DeleteTransactionCtxt(SIP_TRANSACTION_CTXT *ctxt);

ITSDLLAPI int
SIP_TransactionKeyFromMsg(SIP_MSG *msg, SIP_TRANSACTION_KEY *key);

ITSDLLAPI SIP_TRANSACTION_TYPE
SIP_GetTransactionType(SIP_MSG *msg, ITS_USHORT src);

ITSDLLAPI SIP_TransactionEntryFunc
SIP_GetTransactionEntryFunc(SIP_TRANSACTION_TYPE type);

ITSDLLAPI int
SIP_CopyHeadersToCtxt(SIP_MSG *msg, SIP_TRANSACTION_CTXT *ctxt);

/*Timer subsystem functions */
typedef struct
{
    ITS_UINT            tranId;
    ITS_OCTET           timerId; 
    SIP_TRANSACTION_KEY transKey;
}
SIP_TIMER_CTXT;

ITSDLLAPI int 
SIP_StartTimer(SIP_TRANSACTION_CTXT *ctxt, ITS_OCTET timerId, ITS_UINT tVal);

ITSDLLAPI int
SIP_StopTimer(SIP_TRANSACTION_CTXT *ctxt);

/* Support functions */
ITSDLLAPI int
SIP_Send100TryingToNet(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg);

ITSDLLAPI int
SIP_Send481ResponseToNet(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg);

ITSDLLAPI int
SIP_Send504ResponseToNet(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg);

ITSDLLAPI int
SIP_Send400Response(SIP_EVENT *sipEvt, SIP_MSG *msg, ITS_UINT errCode);

ITSDLLAPI int
SIP_SendErrorResponseToNet(SIP_EVENT *sipEvt, SIP_MSG *msg, ITS_UINT errorCode);

ITSDLLAPI int
SIP_SendEventToApp(SIP_EVENT *sipEvt);

ITSDLLAPI int
SIP_SendEventToNet(SIP_TRANSACTION_CTXT *ctxt);

ITSDLLAPI int
SIP_SendTimeoutToApp(SIP_TRANSACTION_CTXT *ctxt, SIP_TIMEOUT_REASON reason);

ITSDLLAPI int
SIP_GetLocalTransportForCall(SIP_TRANSACTION_CTXT *ctxt, SIP_MSG *msg);

ITSDLLAPI int
SIP_SendIndicationToApp(ITS_UINT reason, SIP_CALLID_HDR *callId,
                        SIP_CSEQ_HDR *cseq, SIP_MSG_TYPE msgId,
                        SOCK_IPv4Addr remIPAddr);
ITSDLLAPI int
SIP_SendTransactionErrorToApp(SIP_TRANSACTION_CTXT *ctxt, ITS_UINT reason);

ITSDLLAPI int
SIP_HandleMsgFromTransport(SIP_EVENT *sipEvt, SIP_MSG *msg, int retCode);


#ifdef __cplusplus
}
#endif

#endif 
