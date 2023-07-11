
/*********************************-*-C-*-************************************
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
 *
 * LOG: $Log: its_sctp_trans.h,v $
 * LOG: Revision 9.5.40.2  2014/03/03 10:13:08  nazad
 * LOG: mh related: changes for sctp new parameters and reconnect issues...
 * LOG:
 * LOG: Revision 9.5.40.1  2014/02/20 14:19:00  jkchaitanya
 * LOG: fix for mh
 * LOG:
 * LOG: Revision 9.5  2008/06/27 14:31:30  mpatri
 * LOG: Accelero CGI Phase I: Modification to adopt code review comments & Fixing other issues
 * LOG:
 * LOG: Revision 9.4  2008/06/20 11:10:09  mpatri
 * LOG: Accelero CGI Phase I:D0250 Multihoming Support & fixing other issues
 * LOG:
 * LOG: Revision 9.3  2008/04/15 05:03:14  kramesh
 * LOG: Merged Persistent Branch Changes to current.
 * LOG:
 * LOG: Revision 9.2.2.3  2008/02/25 10:55:49  omayor
 * LOG: Add C++ API for SCTP client transport
 * LOG:
 * LOG: Revision 9.2.2.2  2007/06/15 15:13:17  pspl
 * LOG: Added multihome support for sctp (Rahul/Rajnikant)
 * LOG:
 * LOG: Revision 9.2.2.1  2007/06/04 14:20:18  pspl
 * LOG: Multihome support added (Rajnikant)
 * LOG:
 * LOG: Revision 9.2  2007/01/10 11:15:04  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2002/12/30 17:30:31  lbana
 * LOG: propagating bug fixes in PR6.1 to current.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2002/01/15 23:04:57  mmiers
 * LOG: Add CRC32C.  Update M2PA as far as I can without SCTP support.
 * LOG:
 * LOG: Revision 5.3  2002/01/09 21:21:58  mmiers
 * LOG: Update for M2PA.  It (and SAAL) require larger BSNT fields
 * LOG: (16 and 24 bits, respectively).  Update SNMM to reflect this,
 * LOG: additional updates to SUPPORT for M2PA.
 * LOG:
 * LOG: Revision 5.2  2002/01/03 23:25:16  mmiers
 * LOG: Change codec signature.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:57  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.15  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.14  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.13  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.12  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.11  2000/12/19 17:43:33  mmiers
 * LOG: Start testing.
 * LOG:
 * LOG: Revision 3.10  2000/11/29 00:59:30  mmiers
 * LOG: Got read done.  Write should be simple.
 * LOG:
 * LOG: Revision 3.9  2000/11/28 23:44:29  mmiers
 * LOG: Today's SCTPTRAN installment.  About finished, just need to create
 * LOG: remote transports when clients connect/destroy when they leave.
 * LOG:
 * LOG: Revision 3.8  2000/11/16 23:01:55  mmiers
 * LOG: Add the SCTP transport.  Getting close on this...
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_SCTP_TRANS_H)
#define ITS_SCTP_TRANS_H

#include <its.h>
#include <its_object.h>
#include <its_callback.h>
#include <its_sctp.h>
#include <its_ip_trans.h>

#ident "$Id: its_sctp_trans.h,v 9.5.40.2 2014/03/03 10:13:08 nazad Exp $"

/********************************
 * Macro definitions
 *******************************/


#define SCTP_MAX_HOMES              4

#define MAX_IN_STREAMS_STRING       "maxInStreams"
#define NUM_OUT_STREAMS_STRING      "numOutStreams"
#define MAX_ATTEMPTS_STRING         "maxAttempts"
#define INIT_COOKIE_LIFE_STRING     "cookieLife"
#define ASOC_FAILURE_RETRY_STRING   "asocMaxAttempt"
#define INIT_HB_ON_STRING           "hbOn"
#define INIT_TIMEOUT_STRING         "initTimeOut"
#define SEND_TIMEOUT_STRING         "sendTimeOut"
#define RECV_TIMEOUT_STRING         "recvTimeOut"
#define RECONN_TIMEOUT_STRING       "reconnTimeOut"
#define HB_TIMEOUT_STRING           "hbTimeOut"
#define SHUT_TIMEOUT_STRING         "shutdownTimeOut"
#define PMTU_TIMEOUT_STRING         "pmtuTimeOut"
#define IS_CLIENT_STRING            "isClient"
#define ACK_DELAY_STRING            "sackDelay"
#define RTO_MAX_STRING              "rtoMax"
#define RTO_MIN_STRING              "rtoMin"
#define RTO_INITIAL_STRING          "rtoInitial"
#define SEND_BUFFER_SIZE_STRING     "sendBufSize"
#define RECV_BUFFER_SIZE_STRING     "recvBufSize"
#define PATH_FAILURE_RETRY_STRING   "pathmaxrxt"

#ifndef _LKSCTP_MAX_BUFF_SIZE_
#define LKSCTP_MAX_BUFF_SIZE 0x00010000
#endif

#ifndef _LKSCTP_MAX_BUFF_SIZE_
#define LKSCTP_MAX_BUFF_SIZE 0x00010000
#endif

/*
 * payload type
 */
#define PAYLOAD_TYPE_STRING         "payloadType"

/*
 * forward
 */
typedef struct _sctptran_Manager *SCTPTRAN_ManagerPtr;

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * IP transport API
 */
ITSDLLAPI int   SCTPTRAN_Open(SOCKTRAN_Manager *m);
ITSDLLAPI int   SCTPTRAN_Connect(SOCKTRAN_Manager *m);
ITSDLLAPI void  SCTPTRAN_Close(SOCKTRAN_Manager *m);
ITSDLLAPI int   SCTPTRAN_GetAssocState(SOCKTRAN_Manager *m, 
                                       ITS_SCTP_STATE *state);

#if defined(__cplusplus)
}
#endif


typedef int (*SCTP_CodecPtr)(SCTPTRAN_ManagerPtr m,
                             ITS_EVENT *ev,
                             ITS_BOOLEAN *isManagement,
                             ITS_OCTET *sls);



typedef void  (*SCTPTRAN_SocketProc) (SCTPTRAN_ManagerPtr sctp_transport_obj);

typedef int   (*SCTPTRAN_BindProc)   (SCTPTRAN_ManagerPtr sctp_transport_obj);

typedef int   (*SCTPTRAN_ListenProc) (SCTPTRAN_ManagerPtr sctp_transport_obj, 
                                      int backlog);

typedef ITS_USHORT  (*SCTPTRAN_AcceptProc) (SCTPTRAN_ManagerPtr sctp_transport_obj);
typedef int   (*SCTPTRAN_ConnectProc)(SCTPTRAN_ManagerPtr sctp_transport_obj);

typedef int   (*SCTPTRAN_SendMsgProc)(SCTPTRAN_ManagerPtr sctp_transport_obj, 
                                      SCTP_API_MSG_HDR *msg, 
                                      int flags);
typedef int   (*SCTPTRAN_RecvMsgProc)(SCTPTRAN_ManagerPtr sctp_transport_obj, 
                                      SCTP_API_MSG_HDR *msg, 
                                      int flags);
typedef int   (*SCTPTRAN_CloseProc)  (SCTPTRAN_ManagerPtr sctp_transport_obj);
typedef int   (*SCTPTRAN_PendingProc)(SCTPTRAN_ManagerPtr sctp_transport_obj);
typedef int   (*SCTPTRAN_IoctlProc)  (SCTPTRAN_ManagerPtr sctp_transport_obj, 
                                      int req, ...);
typedef void  (*SCTPTRAN_FreePeerAddrsProc) (SOCK_AddrStore* sctp_peer_addresses);


/*
 * Association State
 */
typedef enum
{
    ITS_ASSOC_DOWN,
    ITS_ASSOC_CONNECTING,
    ITS_ASSOC_CONNECTED
}
ITS_ASSOC_STATE;

/*
 * SCTP transport class record
 */


typedef struct
{
    SCTPTRAN_SocketProc    socket;
    SCTPTRAN_BindProc      bind;
    SCTPTRAN_ListenProc    listen;
    SCTPTRAN_AcceptProc    accept;
    SCTPTRAN_ConnectProc   connect;
    SCTPTRAN_SendMsgProc   sendmsg;
    SCTPTRAN_RecvMsgProc   recvmsg;
    SCTPTRAN_CloseProc     close;
    SCTPTRAN_PendingProc   pending;
    SCTPTRAN_IoctlProc     ioctl;
    SCTPTRAN_FreePeerAddrsProc freePeerAddrs;
} SCTPTRAN_ClassPart;


/*
 * codec data struct
 */
typedef struct
{
    char            *name;
    SCTP_PAYLOAD    type;
    SCTP_CodecPtr   encode;
    SCTP_CodecPtr   decode;
}
SCTPTRAN_CodecRec;

/*
 * local object needs
 */
typedef struct
{
    SCTP_PAYLOAD    ptype;
    SCTP_CodecPtr   encode;
    SCTP_CodecPtr   decode;
    char *          buffer;
    ITS_BOOLEAN     isClient;
    ITS_USHORT      inStreams;
    ITS_USHORT      outStreams;
    /* M2PA, being weird, needs some stuff here */
    ITS_INT         state;
    ITS_UINT        flags;
    ITS_SERIAL      t1;
    ITS_SERIAL      t2;
    ITS_SERIAL      t3;
    ITS_SERIAL      t6;
    ITS_SERIAL      pd;
    ITS_SERIAL      ls;
    ITS_UINT        numExtraHomes;
    ITS_SocketInfo  *extraHomes;   /* This will be typically an array
                                      of ITS_SocketInfo. The size allocated
                                      for this pointer should be equal to
                                      numExtraHomes * sizeof(ITS_SocketInfo)
                                   */
    ITS_INT	    inReconnectState;
    ITS_INT	    connectToSecondary;
    ITS_ASSOC_STATE assocState;
}
SCTPTRAN_ObjectPart;

#define SCTPTRAN_FLAG_EMERG         0x0001
#define SCTPTRAN_FLAG_ALIGN_SENT    0x0002
#define SCTPTRAN_FLAG_ALIGN_RCVD    0x0004
#define SCTPTRAN_FLAG_ASSOC_UP      0x0008
#define SCTPTRAN_FLAG_READY         0x0010
#define SCTPTRAN_FLAG_LPO           0x0020
#define SCTPTRAN_FLAG_PD_MASK       0x0f00
#define SCTPTRAN_FLAG_PD_SHIFT      8
#define SCTPTRAN_FLAG_PDM_MASK      0xf000
#define SCTPTRAN_FLAG_PDM_SHIFT     12

typedef struct _sctptran_Manager
{
    ITS_CoreObjectPart      core;
    TRANSPORT_ObjectPart    transport;
    SOCKTRAN_ObjectPart     socket;
    SCTPTRAN_ObjectPart     sctp;
}
SCTPTRAN_Manager;

/************************************
 * Macros to access function pointers
 ***********************************/

#define SCTPTRAN_SOCKET(x)      sctptranClass.socket
#define SCTPTRAN_BIND(x)        sctptranClass.bind
#define SCTPTRAN_LISTEN(x)      sctptranClass.listen
#define SCTPTRAN_ACCEPT(x)      sctptranClass.accept
#define SCTPTRAN_CONNECT(x)     sctptranClass.connect
#define SCTPTRAN_SENDMSG(x)     sctptranClass.sendmsg
#define SCTPTRAN_RECVMSG(x)     sctptranClass.recvmsg
#define SCTPTRAN_CLOSE(x)       sctptranClass.close
#define SCTPTRAN_PENDING(x)     sctptranClass.pending
#define SCTPTRAN_IOCTL(x)       sctptranClass.ioctl
#define SCTPTRAN_FREEPADDRS(x)  sctptranClass.freePeerAddrs

#define SCTPTRAN_INSTREAMS(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.inStreams)
 
#define SCTPTRAN_OUTSTREAMS(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.outStreams)

#define SCTPTRAN_PAYLOAD(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.ptype)

#define SCTPTRAN_ENCODE(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.encode)

#define SCTPTRAN_DECODE(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.decode)

#define SCTPTRAN_BUFFER(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.buffer)

#define SCTPTRAN_IS_CLIENT(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.isClient)

#define SCTPTRAN_STATE(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.state)

#define SCTPTRAN_FLAGS(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.flags)

#define SCTPTRAN_T1(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.t1)

#define SCTPTRAN_T2(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.t2)

#define SCTPTRAN_T3(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.t3)

#define SCTPTRAN_T6(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.t6)

#define SCTPTRAN_PD(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.pd)

#define SCTPTRAN_LS(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.ls)

#define SCTPTRAN_NUMEXTRAHOMES(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.numExtraHomes)

#define SCTPTRAN_EXTRAHOMES(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.extraHomes)

#define SCTPTRAN_RECONN_STATE(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.inReconnectState)

#define SCTPTRAN_CONN_TO_SEC(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.connectToSecondary)

#define SCTPTRAN_ASSOC_STATE(x) \
    (((SCTPTRAN_Manager *)(x))->sctp.assocState)

#define SCTPTRAN_LOCAL_ENDPOINT_CLASS_NAME  "SCTPTRAN_LocalEndPoint"
#define SCTPTRAN_REMOTE_ENDPOINT_CLASS_NAME "SCTPTRAN_RemoteEndPoint"


/* These will be defined in lksctp or sksctp */
ITSDLLAPI extern SOCKTRAN_ClassRec    itsSCTPTRAN_LocalEndPointClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsSCTPTRAN_LocalEndPointClass;
ITSDLLAPI extern SOCKTRAN_ClassRec    itsSCTPTRAN_RemoteEndPointClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsSCTPTRAN_RemoteEndPointClass;


extern SCTPTRAN_ClassPart  sctptranClass;

/*
 * UA usage
 */
#ifdef __cplusplus
extern "C"
{
#endif

ITSDLLAPI int SCTPTRAN_RegisterCodec(char *name, SCTP_PAYLOAD ptype,
                                     SCTP_CodecPtr encode, SCTP_CodecPtr decode);
ITSDLLAPI int SCTPTRAN_DeregisterCodec(char *name);

#ifdef __cplusplus
}
#endif
/*
 * UA usage
 */
ITSDLLAPI extern CALLBACK_Manager    *SCTPTRAN_ManagementCallbacks;

#endif /* ITS_SCTP_TRANS_H */

