/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                  
 * CONTRACT: INTERNAL
 *      
 *  ID: $Id: ual_intern.h,v 9.10.8.1.40.1.2.1 2015/01/22 15:08:26 jkchaitanya Exp $
 *
 *  LOG: $Log: ual_intern.h,v $
 *  LOG: Revision 9.10.8.1.40.1.2.1  2015/01/22 15:08:26  jkchaitanya
 *  LOG: changes for aspid issue faced in the HP site
 *  LOG:
 *  LOG: Revision 9.10.8.1.40.1  2014/10/27 08:18:49  millayaraja
 *  LOG: changes for HA HotStandBy
 *  LOG:
 *  LOG: Revision 9.10.8.1  2010/05/31 14:17:31  ssingh
 *  LOG: fixing issue #2915; Audit Timer Expiry Handling
 *  LOG:
 *  LOG: Revision 9.10  2008/06/30 14:05:14  skatta
 *  LOG: changes done for removing warnings
 *  LOG:
 *  LOG: Revision 9.9  2008/06/29 15:20:00  skatta
 *  LOG: Changes after Code review comments and IPSP porting
 *  LOG:
 *  LOG: Revision 9.8  2008/06/20 10:38:56  mshanmugam
 *  LOG: Accelero CGI Phase I:D0170, D0210
 *  LOG:
 *  LOG: Revision 9.7  2008/05/01 16:18:31  kramesh
 *  LOG: Propagated Bridgeport issue 1541. Routing Key more than 255.
 *  LOG:
 *  LOG: Revision 9.6  2008/04/15 05:03:16  kramesh
 *  LOG: Merged Persistent Branch Changes to current.
 *  LOG:
 *  LOG: Revision 9.5.2.9  2008/02/29 08:38:32  randresol
 *  LOG: Correct __cplusplus define to allow C++ build
 *  LOG:
 *  LOG: Revision 9.5.2.8  2008/02/26 04:52:17  clin
 *  LOG: Add modification to support C++ API for ASP
 *  LOG:
 *  LOG: Revision 9.5.2.7  2007/06/22 11:50:36  pspl
 *  LOG: Auditing support for receipt of SSNM message (SCON/DUNA/DRST)
 *  LOG:
 *  LOG: Revision 9.5.2.6  2007/06/05 05:57:10  pspl
 *  LOG: (PSPL, abhijeet) removed unused UAL_SendASP_ACTIVE(), and few misc changes
 *  LOG:
 *  LOG: Revision 9.5.2.5  2007/05/25 07:15:45  pspl
 *  LOG: (PSPL,Manish)
 *  LOG: - UAL_GetRoutingKeys() is changed to extract RK_Contexts instead of rKeys, and renamed
 *  LOG: - Hardcoading of UAL_OVERRIDE_MODE removed
 *  LOG: - Changed the Parameter type of SendASPActive()
 *  LOG:
 *  LOG: Revision 9.5.2.4  2007/05/02 08:30:00  pspl
 *  LOG: (PSPL, abhijeet) misc review comment changes
 *  LOG:
 *  LOG: Revision 9.5.2.3  2007/04/26 10:02:50  pspl
 *  LOG: (PSPL, abhijeet) misc changes for peg count increment
 *  LOG:
 *  LOG: Revision 9.5.2.2  2007/04/26 06:56:51  pspl
 *  LOG: (PSPL, abhijeet)
 *  LOG: - changed and added macro definitions
 *  LOG:
 *  LOG: Revision 9.5.2.1  2007/04/05 14:51:53  pspl
 *  LOG: enum definition for the msgType used for indexing of ackTimers[]
 *  LOG:
 *  LOG: Revision 9.5  2005/12/08 03:37:52  clin
 *  LOG: fix bug #2482
 *  LOG:
 *  LOG: Revision 9.4  2005/11/23 19:45:02  clin
 *  LOG: fix bug #2531
 *  LOG:
 *  LOG: Revision 9.3  2005/07/04 02:46:56  randresol
 *  LOG: M3UA Enhancement for Accelero Rel 6.5
 *  LOG:
 *  LOG: Revision 9.2  2005/04/01 12:01:25  ssingh
 *  LOG: Sigtran related Bug Fix Propagation to PR6.5/current.
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:53:48  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.2  2005/03/21 13:52:19  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 7.2.2.2.4.2.4.1  2005/01/07 15:03:05  ssingh
 *  LOG: Changed to enhance ACTIVE-BACKUP redundancy.
 *  LOG:
 *  LOG: Revision 7.2.2.2.4.2  2004/10/06 08:40:23  mmanikandan
 *  LOG: Support for windows build.
 *  LOG:
 *  LOG: Revision 7.2.2.2.4.1  2004/05/03 12:45:21  ssingh
 *  LOG: Bug#806/808/790
 *  LOG: UAL_TimerCtx and ASP_Entry record modified for checking of (in)valid resp.
 *  LOG: UAL_SendNotify proc changed to include aspId in case of ASP notification.
 *  LOG:
 *  LOG: Revision 7.2.2.2  2003/09/08 19:32:48  lbana
 *  LOG: Added callback info for pause/resume when transport goes Up/Down
 *  LOG:
 *  LOG: Revision 7.2.2.1  2003/04/04 21:39:49  pmandal
 *  LOG: Port UAL callback changes.
 *  LOG:
 *  LOG: Revision 7.2  2002/12/30 17:28:48  lbana
 *  LOG: Propagating bug fixes in PR6.1 to current
 *  LOG:
 *  LOG: Revision 7.1.2.2  2003/03/19 21:47:58  lbana
 *  LOG: added context for the callback manager
 *  LOG:
 *  LOG: Revision 7.1.2.1  2002/12/26 23:52:04  lbana
 *  LOG: fix missing  open braces while patching
 *  LOG:
 *  LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
 *  LOG: Begin PR6.2
 *  LOG:
 *  LOG: Revision 4.15  2002/08/26 21:52:56  mmiers
 *  LOG: Warning removal.
 *  LOG:
 *  LOG: Revision 4.14  2002/07/22 18:51:23  lbana
 *  LOG: make more readable in aspo active process
 *  LOG:
 *  LOG: Revision 4.13  2002/07/18 18:25:28  lbana
 *  LOG: add family in AS Context to avoid sequency dependancy in xml file
 *  LOG:
 *  LOG: Revision 4.12  2002/07/10 13:29:13  lbana
 *  LOG: removed all warnings
 *  LOG:
 *  LOG: Revision 4.11  2002/07/09 22:23:23  ngoel
 *  LOG: add ual console function
 *  LOG:
 *  LOG: Revision 4.10  2002/07/09 21:19:44  lbana
 *  LOG: Start MML procedures for UALs
 *  LOG:
 *  LOG: Revision 4.9  2002/07/08 18:18:30  ngoel
 *  LOG: add ual alarms
 *  LOG:
 *  LOG: Revision 4.8  2002/05/15 16:19:05  lbana
 *  LOG: Add localPC parsing of the resource manager. Compiled the routeHandler
 *  LOG: module.
 *  LOG:
 *  LOG: Revision 4.7  2002/05/15 15:37:47  lbana
 *  LOG: need to call LINK_AddLinkInfoToTransport.
 *  LOG:
 *  LOG: Revision 4.6  2002/05/14 18:55:09  lbana
 *  LOG: fix compiler errors in macros
 *  LOG:
 *  LOG: Revision 4.5  2002/05/14 18:35:38  lbana
 *  LOG: fixed errors in first reading...
 *  LOG:
 *  LOG: Revision 4.4  2002/05/13 23:24:38  lbana
 *  LOG: Build in current. Now for the testing.....
 *  LOG:
 *  LOG: Revision 4.3  2002/05/13 20:48:26  lbana
 *  LOG: uals in current starts from here
 *  LOG:
 *  LOG: Revision 4.2.2.31  2002/03/21 22:13:23  omayor
 *  LOG: Add IP addresses as static ID for ASP (ie. Static config)
 *  LOG:
 *  LOG: Revision 4.2.2.30  2002/03/15 23:58:14  omayor
 *  LOG: Add payload type stuff in.
 *  LOG:
 *  LOG: Revision 4.2.2.29  2002/03/15 00:13:10  omayor
 *  LOG: Removed variant dependencies plus a few warning on linux.
 *  LOG:
 *  LOG: Revision 4.2.2.28  2002/03/13 22:30:46  ngoel
 *  LOG: Merge SUA specific functionality into UAL
 *  LOG:
 *  LOG: Revision 4.2.2.27  2002/03/06 17:30:36  omayor
 *  LOG: Delete remote route when deregistering an AS.
 *  LOG:
 *  LOG: Revision 4.2.2.26  2002/03/05 20:51:17  omayor
 *  LOG: fixes in Bakeoff
 *  LOG:
 *  LOG: Revision 4.2.2.25  2002/02/22 23:54:21  labuser
 *  LOG: Add the isMember stuff for ASP side configuration.
 *  LOG:
 *  LOG: Revision 4.2.2.24  2002/02/22 23:25:32  omayor
 *  LOG: fixed bud before AS state going down, send err for invalid modes
 *  LOG:
 *  LOG: Revision 4.2.2.23  2002/02/10 00:36:37  omayor
 *  LOG: Added some user notification in dynamic registration.
 *  LOG:
 *  LOG: Revision 4.2.2.22  2002/02/08 21:37:07  labuser
 *  LOG: Polish up registration.
 *  LOG:
 *  LOG: Revision 4.2.2.21  2002/02/08 16:01:29  lbana
 *  LOG: added dump functions for ASTable and fixes related to pending state
 *  LOG:
 *  LOG: Revision 4.2.2.20  2002/02/06 22:48:22  omayor
 *  LOG: Build Changes in RKM procedures.
 *  LOG:
 *  LOG: Revision 4.2.2.19  2002/02/06 21:39:24  omayor
 *  LOG: Finish up Deregistration code.
 *  LOG:
 *  LOG: Revision 4.2.2.18  2002/02/04 15:46:40  omayor
 *  LOG: Add some Layer Management function (ASPDN, ASPAC, ASPIA).
 *  LOG:
 *  LOG: Revision 4.2.2.17  2002/01/30 15:42:54  labuser
 *  LOG: First round of testing.
 *  LOG:
 *  LOG: Revision 4.2.2.16  2002/01/29 21:59:20  lbana
 *  LOG: added missing object file in Makefile
 *  LOG:
 *  LOG: Revision 4.2.2.15  2002/01/29 17:09:09  labuser
 *  LOG: remove compiler warnings
 *  LOG:
 *  LOG: Revision 4.2.2.14  2002/01/25 20:14:53  lbana
 *  LOG: compiled ual subsystem.
 *  LOG:
 *  LOG: Revision 4.2.2.13  2002/01/25 15:52:30  lbana
 *  LOG: more clean up
 *  LOG:
 *  LOG: Revision 4.2.2.12  2002/01/25 15:39:43  omayor
 *  LOG: Added dynamic registration of RKs.
 *  LOG:
 *  LOG: Revision 4.2.2.11  2002/01/23 23:25:52  lbana
 *  LOG: fix type name resolution issues
 *  LOG:
 *  LOG: Revision 4.2.2.10  2002/01/18 00:16:45  lbana
 *  LOG: move sending asp_active to separate function
 *  LOG:
 *  LOG: Revision 4.2.2.9  2002/01/18 00:00:57  omayor
 *  LOG: Done with SCTP indications, config, timers, Codec, now RKM stuff.
 *  LOG:
 *  LOG: Revision 4.2.2.8  2002/01/17 20:56:05  omayor
 *  LOG: Add in timer and pending state logic.
 *  LOG:
 *  LOG: Revision 4.2.2.7  2002/01/17 17:02:21  omayor
 *  LOG: More work on the UAL Manager.
 *  LOG:
 *  LOG: Revision 4.2.2.6  2002/01/17 16:48:39  lbana
 *  LOG: removed conflicts
 *  LOG:
 *  LOG: Revision 4.2.2.5  2002/01/17 00:43:24  omayor
 *  LOG: More work on the UAL Manager.
 *  LOG:
 *  LOG: Revision 4.2.2.4  2002/01/15 17:54:11  omayor
 *  LOG: More work on the ual.
 *  LOG:
 *  LOG: Revision 4.2.2.3  2002/01/15 00:47:46  lbana
 *  LOG: more changes
 *  LOG:
 *  LOG: Revision 4.2.2.2  2002/01/14 16:18:13  omayor
 *  LOG: Commit the UAL Codec and few changes in internal.h
 *  LOG:
 *  LOG: Revision 4.2.2.1  2002/01/09 22:58:28  lbana
 *  LOG: Start working on PR5
 *  LOG:
 ****************************************************************************/
/*******************************************************************************
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference       Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005  BugId: 807      Changes along with code change
 *                                       propagated in ual_route_handler.c
 *                                       Functions added:
 *                                       - UAL_AddLink(..)
 *                                       - UAL_RemLink(..)
 *                                       Hash define
 *                                       - UAL_TRANSPORT_PENDING
 *
 ******************************************************************************/

#include <its.h>
#include <its_types.h>
#include <its_object.h>
#include <its_hash.h>
#include <its_list.h>
#include <its_route.h>
#include <its_link.h>
#include <its_timers.h>
#include <its_assertion.h>
#include <its_trace.h>
#include <its_transports.h>
#include <its_tq_trans.h>
#include <its_sockets.h>
#include <its_callback.h>
#include <dbc_serv.h>

#include <its_ual.h>
#include <its_sctp_trans.h>
#include <ual_alarms.h>

#include <its_redundancy.h>

#ifndef _UAL_INTERN_H
#define _UAL_INTERN_H


#define UAL_MAX_NUM_AS      0xFFFFFFFF
#define UAL_MAX_NUM_ASSOC   256

#define UAL_MAX_MSG_LEN    (ITS_MAX_TIMER_CONTEXT - sizeof(ITS_USHORT) * 3 - \
                            sizeof(ITS_OCTET) - (2 * sizeof(int)) - 4)

#define UAL_TRANSPORT_PENDING(tr) ((TRANSPORT_INSTANCE(tr) >= UAL_PENDING_FIRST_SRC) && \
                                   (TRANSPORT_INSTANCE(tr) <= UAL_PENDING_LAST_SRC))

/*Resource ID for the hash table*/
#define UAL_HASH_RID    0
#define UAL_MAX_TIMERS  4

#define RK_LIST_CONTEXT(x) x->entry

#define ASP_LINK_CODE_MASK 0xFFU

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * variables for IPSP type
 */
#define UAL_IPSP_TYPE_NONE          0x00
#define UAL_IPSP_TYPE_SINGLE_EXCHG  0x01
#define UAL_IPSP_TYPE_DOUBLE_EXCHG  0x02

#define UAL_IPSP_MASK_CLIENT        0x40 /* IPSP client */
#define UAL_IPSP_MASK_SERVER        0x80 /* IPSP server */

#define UAL_IS_IPSP_SERVER(x)       ((x & UAL_IPSP_MASK_SERVER)        \
                                       == UAL_IPSP_MASK_SERVER)
#define UAL_IS_IPSP_CLIENT(x)       ((x & UAL_IPSP_MASK_CLIENT)     \
                                       == UAL_IPSP_MASK_CLIENT)
#define UAL_IS_IPSP_SINGLE_EXCHG(x) ((x & UAL_IPSP_TYPE_SINGLE_EXCHG)  \
                                       == UAL_IPSP_TYPE_SINGLE_EXCHG)
#define UAL_IS_IPSP_DOUBLE_EXCHG(x) ((x & UAL_IPSP_TYPE_DOUBLE_EXCHG)  \
                                       == UAL_IPSP_TYPE_DOUBLE_EXCHG)
#define UAL_IS_IPSP_SE_SERVER(x)    (UAL_IS_IPSP_SINGLE_EXCHG(x) &&    \
                                     UAL_IS_IPSP_SERVER(x))
#define UAL_IS_IPSP_SE_CLIENT(x)    (UAL_IS_IPSP_SINGLE_EXCHG(x) &&    \
                                     UAL_IS_IPSP_CLIENT(x))
#define UAL_IS_IPSP_DE_SERVER(x)    (UAL_IS_IPSP_DOUBLE_EXCHG(x) &&    \
                                     UAL_IS_IPSP_SERVER(x))
#define UAL_IS_IPSP_DE_CLIENT(x)    (UAL_IS_IPSP_DOUBLE_EXCHG(x) &&    \
                                     UAL_IS_IPSP_CLIENT(x))

#define UAL_IS_APP_SGP(x)           (x == UAL_ITW_SG)
#define UAL_IS_APP_ASP(x)           (x == UAL_ITW_ASP)
#define UAL_IS_APP_IPSP(x)          (x == UAL_ITW_IPSP)

extern ITS_UINT localaspId;
typedef struct __UAL_GLOBALS__
{
    ITS_OCTET           ualType;
    ITS_OCTET           local_Version;
    ITS_OCTET           interworking_Mode;
    ITS_OCTET           ipspType;
    ITS_INT             ASP_ACK_Timer;
    ITS_INT             numRetry;
    ITS_INT             ASP_Pending_Timer;
    ITS_INT             HB_Interval;
    ITS_BOOLEAN         heartBeatFlag;
    ITS_SERIAL          HBTimeout;
    ITS_INT             aspId;
    ITS_BOOLEAN         propagMgntToUsr;
    ITS_UINT            localPC;
    ITS_BOOLEAN         debug_flag;
    ITS_INT             ASP_AUD_Timer;
}
UAL_GLOBALS;

UALDLLAPI extern UAL_GLOBALS  __ualGlobals;


#define UAL_PROTOCOL_TYPE     __ualGlobals.ualType
#define UAL_GL_ITW_MODE       __ualGlobals.interworking_Mode
#define UAL_GL_IPSP_TYPE      __ualGlobals.ipspType
#define UAL_GL_VERSION        __ualGlobals.local_Version
#define UAL_GL_ACK_TIMER      __ualGlobals.ASP_ACK_Timer
#define UAL_GL_PEND_TIMER     __ualGlobals.ASP_Pending_Timer
#define UAL_GL_HB_FLAG        __ualGlobals.heartBeatFlag
#define UAL_GL_HB_INTER       __ualGlobals.HB_Interval
#define UAL_GL_NUM_RETRY      __ualGlobals.numRetry
#define UAL_GL_ASP_ID         __ualGlobals.aspId   /* ASP, IPSP only */
#define UAL_PROPAGATE_MGNT    __ualGlobals.propagMgntToUsr
#define UAL_GL_LOCAL_PC       __ualGlobals.localPC
#define UAL_GL_DEBUG_FLAG     __ualGlobals.debug_flag
#define UAL_GL_AUD_TIMER      __ualGlobals.ASP_AUD_Timer

/* default value for the audTimer */
#define UAL_GL_AUD_TIMER_DEFAULT_VAL 10

typedef LIST_Manager RK_List;
typedef LIST_Manager ASP_List;

UALDLLAPI extern char* ITW_STRING;

/*
 * Enum of various messages sent 
 * the enum values are used to index the ackTimer array in the aspEntry
 */
typedef enum
{
    ASP_UP_MSG,
    ASP_DOWN_MSG,
    ASP_ACTIVE_MSG,
    ASP_INACTIVE_MSG
}
UAL_SEND_MSG_TYPE;

/*
 *  ASP Traffic Mode
 */

typedef enum
{
    UAL_MODE_NONE,
    UAL_OVERRIDE,
    UAL_LOADSHARE,
    UAL_BROADCAST
} 
UAL_TRAFFIC_TYPE;

#define UAL_IS_VALID_TM(x)  ((x == UAL_OVERRIDE)  ||   \
                             (x == UAL_LOADSHARE) ||   \
                             (x == UAL_BROADCAST))

#define UAL_BCST_NO_TIMER   (UAL_BROADCAST + 1)

/*
 * Timers types
 */

typedef enum
{
    UAL_RETRANS,
    UAL_PENDING,
    UAL_HB,
    UAL_REG,
    UAL_DAUD_MESG
}
UAL_TIMER_TYPE;

/*
 * Timer data
 */

typedef struct
{
    UAL_TIMER_TYPE    type;                 /* true if pending timer data */
    ITS_USHORT        from;                 /* trid */
    ITS_USHORT        len;                  /* message length */
    UAL_TRAFFIC_TYPE  tm;                   /* mode to select the timer */
    UAL_SEND_MSG_TYPE msgType;		    /* msg type to index the ackTimer array */
    ITS_OCTET         retryCount;
    ITS_OCTET         ackMsgType;           /* Ack message Expected */
    ITS_OCTET         msg[UAL_MAX_MSG_LEN]; /* message for retransmition */
}
UAL_TimerCtx;

typedef struct
{
    ITS_INT      aspid;
    ITS_UINT     home[UAL_MAX_HOME_NUM];
    ITS_UINT     numHome;
}
UAL_ASP_INFO;

/*
 * This is for dynamic registration, to keep tracking
 * on remote ASP/IPSP status
 */

typedef struct
{
    UAL_ASP_STATE     state;       /* State of remote ASP/IPSP */
    UAL_ASP_INFO      aspInfo;     /* ASP/IPSP Identifier + ip addrs */
}
RemoteInfo;

/*
 * ASP entry to put in ASP table for each association
 */

typedef struct 
{
    ITS_SERIAL     ackTimer[UAL_MAX_TIMERS];   /* ACK timers */
    UAL_ASP_STATE  state;                      /* state info */
    ITS_USHORT     trId;                       /* Transport ID */
    ITS_OCTET      pad[2];                     /* dummy */
    ITS_BOOLEAN    isStateInactive;            /* Previous state is INACTIVE */
    RK_List        *asList;                    /* list of AS for this ASP */
    ITS_INT        aspId;                      /* ASPID */            
    SUA_ASP_LABEL  label;
    SCTP_PAYLOAD   payload;                    /* Payload type */    
    UAL_TimerCtx   timerCtx;                   /* for timers */
    RemoteInfo     remoteInfo;                 /* for dynamic registration only */
} 
ASP_Entry;

#define UAL_SUPPORTED_PAYLOADS(x)    (( x == SCTP_PAYLOAD_M3UA ) || \
                                      ( x == SCTP_PAYLOAD_SUA ))

/* 
 * AS entry for each routing contex that we receive/send to be
 * placed in AS Hash table
 */

typedef struct
{
    UAL_AS_STATE      state;         /* state */
    UAL_DYNAMIC_REQ_STATE reqState;  /* for dynamic reg/dereg state */
    ITS_UINT          rCtxt;         /* Routing Key */
    UAL_TRAFFIC_TYPE  trafficMode;   /* ASP traffic mode */
    ITS_SERIAL        pendingTimer;  /* pending timer */
    ITS_HANDLE        pendingTrans;  /* Ptr to TQUEUETRAN_Manager */
    ITS_USHORT        nActives;      /* minimum active ASPs */
    ITS_USHORT        kStandby;      /* minimum standby ASP */
    ROUTE_BasicInfo   asInfo;        /* AS routing parameters */
    ASP_List          *aspList;      /* Keep all ASP's belongs to this AS */
    ITS_USHORT        instance;      /* used for RKM proc on ASP side */
    ITS_BOOLEAN       isMember;      /* for ASP side configuration */
    SUA_ASP_CAPAB     aspCapab;      /* SUA specific */
    ITS_OCTET         linkSet;       /* linkSet for this AS */
    UAL_NET_APP       na;            /* Network Appearance (Use NI) */
    char              *family;       /* need family here to avoid sequence 
                                      * dependency in xml file
                                      */
}
RK_Context;


/* 
 * this is the AS manager structure
 */

typedef struct _AS_Manager
{
    HASH_Table   asTable;                   /* Hash table to store RK_Context's*/ 
    ITS_INT      numEntries;                /* num of entries in AS_Table */
}
AS_Manager;


/*
 *To keep ASP belongs to AS in a aspList
 */

typedef struct
{
    UAL_ASP_STATE     state;       /* State of ASP */
    ITS_USHORT        trId;        /* Transportt ID for this ASP */
    ITS_OCTET         pad[2];      /* dummy */
    UAL_ASP_INFO      aspInfo;     /* ASP Identifier + ip addrs */
    ASP_Entry         *entry;      /* back pointer to ASP table */
}
ASPListNode;


/*
 * To keep AS that belong to ASP in a aspList
 */

typedef struct
{
    ITS_UINT    rCtxt;            /* RoutingKey for this AS */ 
    ITS_OCTET   linkCode;         /* link code */
    ITS_OCTET   pad[3];
    RK_Context  *entry;           /* back pointer to AS table */
}
RKListNode;

/* To store data for sending ASP Active */
typedef struct StoreASPActiveConfigData
{
    ITS_UINT*     rKey;
    int          rKeyLen;
    ASP_Entry*   aspRec;
    UAL_TRAFFIC_TYPE mode;
	ITS_BOOLEAN  flag;
} StoreASPActiveConfigData;

/* To get RoutingKey from Application */
typedef struct AspIdRoutingKeyConfigData
{
    char remoteIp[16];
    ITS_UINT port;
    ITS_UINT routingKey;
    char homeIp[16];
}AspIdRoutingKeyConfigData;

/*
 * To check and return error to remote site, 
 * in case of error in Decoding a msg
 */
#define CHECK_UAL_DECODEMSG_ERROR(trid, retVal) {                                      \
    switch((retVal))                                                                   \
    {                                                                                  \
        case UAL_ERR_UNEXP_PARAM:                                                      \
            UAL_SendERR((trid), UAL_ERR_UNEXP_PARAM, NULL, 0);                         \
	    UAL_IncrementMIBStats(trid, UAL_PEG_ERR_SENT_ID);                          \
            break;                                                                     \
        case UAL_ERR_PARM_FIELD_ERR:                                                   \
            UAL_SendERR((trid), UAL_ERR_PARM_FIELD_ERR, NULL, 0);                      \
	    UAL_IncrementMIBStats(trid, UAL_PEG_ERR_SENT_ID);                          \
            break;                                                                     \
        case ITS_EOVERFLOW:                                                            \
            UAL_SendERR((trid), UAL_ERR_PROT_ERROR, NULL, 0);                          \
	    UAL_IncrementMIBStats(trid, UAL_PEG_ERR_SENT_ID);                          \
            break;                                                                     \
        case ITS_EMISSMAND:                                                            \
            UAL_SendERR((trid), UAL_ERR_MISSING_PARAM, NULL, 0);                       \
	    UAL_IncrementMIBStats(trid, UAL_PEG_ERR_SENT_ID);                          \
            break;                                                                     \
        case ITS_SUCCESS:                                                              \
            break;                                                                     \
        default:                                                                       \
            UAL_ERROR(("Problem in checking return value from of UAL_DecodeMsg()\n")); \
            break;                                                                     \
    }                                                                                  \
}    

/*******************************************************************
 *
 * ASList/ASPList operations.
 * These operations are useful when you add/remove entities from 
 * IntelliSS7 HashTable.
 *
 ******************************************************************/
UALDLLAPI extern  ITS_MUTEX   __ualGuard;       /*mutual exclusion for ual manager*/

UALDLLAPI extern  HASH_Table  __UAL_ASP_Table;  /*Keep track of all ASPs*/

UALDLLAPI extern  AS_Manager  __UAL_AS_Manager; /*Keep track of all AS's*/

UALDLLAPI extern HASH_Table   __UAL_Audit_Timer_Table; /*Keep track of Timers for Auditing*/ 

/*
 * Init/Delete operations
 */
UALDLLAPI LIST_Manager* UAL_CreateList();
UALDLLAPI int UAL_DeleteList(LIST_Manager *lm);

UALDLLAPI int UAL_InitializeInternalTables();
UALDLLAPI int UAL_DeleteInternalTables();

/*
 * Macros to get Counters in a lists/tables
 */
#define ASP_LIST_COUNT(x)  LIST_COUNT(x)
#define AS_LIST_COUNT(x)   LIST_COUNT(x)

#define AS_CONTEXT_COUNT __UAL_AS_Manager.numEntries
#define UAL_ASSOC_COUNT  HASH_TABLE_COUNT(__UAL_ASP_Table) 


/*
 * helper function 
 * (Moved from "its_ual.h", because parameter changed to "RK_Context")
 */
UALDLLAPI int SendASPActive(RK_Context *rCtxt);

/* 
 * ASP List operations
 */

UALDLLAPI int ASPList_AddEntry(ASP_List* al, ASPListNode* ent);

UALDLLAPI int ASPList_RemoveEntry(ASP_List* al, ITS_USHORT trId);

UALDLLAPI ASPListNode* ASPList_Iterate(ASP_List* al);
 
UALDLLAPI ASPListNode* ASPList_FindEntry(ASP_List* al, ITS_USHORT trId);

UALDLLAPI int ASP_ListGetNumASP(ASP_List* al);

UALDLLAPI ITS_BOOLEAN IsAspAddress(ASPListNode *aspNode, SOCK_IPv4Addr address,
                                   ITS_INT *aspId);

/* 
 * RK List operations
 */

UALDLLAPI int RKList_AddEntry(RK_List* asl, RKListNode* ent);

UALDLLAPI int RKList_RemoveEntry(RK_List* asl, ITS_UINT rCtxt);

UALDLLAPI RKListNode* RKList_Iterate(RK_List* asl);

UALDLLAPI RKListNode* RKList_FindEntry(RK_List* asl, ITS_UINT rCtxt);


/*
 * ASP table operations
 */

UALDLLAPI ASP_Entry* ASPTable_AddEntry(ASP_Entry* ent);

UALDLLAPI int ASPTable_FindEntry(ITS_USHORT context, ASP_Entry** data);

UALDLLAPI int ASPTable_RemoveEntry(ITS_USHORT context);

UALDLLAPI int ASPTable_GetAllTransportIds(ITS_USHORT* trid, ITS_INT size, 
                                ITS_INT* avail);

UALDLLAPI int
UAL_SendASP_ACTIVE(ITS_UINT *rkArray, int rk_len, ASP_Entry* aspRec, 
                       UAL_TRAFFIC_TYPE mode, ITS_BOOLEAN flag /*used for ipsp */);
/*
 * AS table operations
 */

UALDLLAPI int RKManager_Init();

UALDLLAPI int RKManager_AddEntry(ITS_UINT index, RK_Context* ent);

UALDLLAPI ITS_UINT RKManager_GetNextFreeSlot();

UALDLLAPI RK_Context* RKManager_FindEntry(ITS_UINT rc);

UALDLLAPI int RKManager_RemoveEntry(RK_Context* ent);

UALDLLAPI int RKManager_RemoveEntryContext(ITS_UINT rc);

UALDLLAPI ROUTE_Info* FindBestMatchInISS7Routes(ROUTE_Info* rInfo);

/*
 * UAL functions
 */

ITSDLLAPI extern CALLBACK_Manager    *UAL_ASP_ManagementCallbacks;

UALDLLAPI void UAL_SCTPTransCallback(ITS_POINTER object, ITS_POINTER userData, 
                                      ITS_POINTER callData);
 
UALDLLAPI void UAL_SCCPMgmtCallback(ITS_POINTER object, ITS_POINTER userData, 
                                    ITS_POINTER callData);

UALDLLAPI void UAL_RedundancyCallback(ITS_POINTER object, ITS_POINTER userData,
                                      ITS_POINTER callData);

UALDLLAPI int
UAL_HandleSuaSNMClassMsg(ITS_EVENT *ev, ITS_USHORT msgType, ASP_Entry *aspEntry);

/* 
 * Handling
 */

UALDLLAPI int UAL_HandleSCTPIndication(ITS_EVENT *UALEvent);

UALDLLAPI int UAL_HandleTimerEvent(ITS_TimerData *td);

UALDLLAPI ITS_INT UAL_HandleManagementClassMsg(ITS_EVENT* ualEvent, ITS_OCTET  msgType,
                                     ASP_Entry* aspRec);

UALDLLAPI ITS_INT UAL_HandleStateMaintMsg(ITS_EVENT* ualEvent, ITS_OCTET  msgType,
                                ASP_Entry* aspRec);

UALDLLAPI ITS_INT UAL_HandleTrafficMaintMsg(ITS_EVENT* ualEvent, ITS_OCTET  msgType,
                                  ASP_Entry* aspRec);

UALDLLAPI int UAL_HandleRKMMsg(ITS_EVENT *UALEvent, ITS_USHORT msgType,
                     ASP_Entry *aspEntry);

UALDLLAPI int UAL_HandleSCTPDataMsg(ITS_EVENT *ualEvent);

UALDLLAPI int UAL_HandleLayerMgntMsg(ITS_EVENT *UALEvent);


/* 
 * Sending
 */

UALDLLAPI int UAL_SendNotify(ITS_USHORT trid, ITS_USHORT type, ITS_USHORT id,
                          ITS_UINT *rkArray, int len, ITS_INT aspId);

UALDLLAPI int UAL_SendERR(ITS_USHORT trId, ITS_UINT errCode, 
                ITS_UAL_IE* mandatory, ITS_INT numParms);

UALDLLAPI int UAL_SendASPUP(ASP_Entry *aspEntry);

UALDLLAPI int UAL_BroadCastMsg(ITS_EVENT *UALEvent, UAL_ASP_STATE state,
                     ITS_BOOLEAN timer);

UALDLLAPI int UAL_LMSendASPSMandTMMsg(ITS_EVENT *UALEvent, UAL_ASP_STATE state,
                                      ITS_UINT trafficMode);

UALDLLAPI int UAL_SendRKMMsg(ITS_EVENT *UALEvent, UAL_DYNAMIC_REQ_STATE state);

/*
 * Timers
 */

UALDLLAPI int UAL_CancelPendingTimer(ITS_USHORT trId, RK_Context* ctxt);

UALDLLAPI int UAL_SetTimerMsgData(UAL_TimerCtx *ctx, ITS_EVENT *evt);

/*
 * Pending State
 */

UALDLLAPI int UAL_StartPendingStateProcedure(RK_Context* asContext);

UALDLLAPI ITS_BOOLEAN UAL_CheckASPending(RK_Context* context);
UALDLLAPI ITS_BOOLEAN UAL_CheckASDown(RK_Context* context);

/* 
 * Routing Keys
 */

UALDLLAPI int UAL_AllocateLocalRKId(ITS_UINT *rCtxt);

UALDLLAPI int UAL_RoutingKeyToRKContext(RK_Context *ctxt, ITS_OCTET *rkData,
                                        int dataLen);

UALDLLAPI int UAL_CheckNewRoutingKeyValid(RK_Context *asCtxt, 
                                          ITS_OCTET *resultData);

UALDLLAPI void UAL_CheckNewSuaRoutingKeyValid(RK_Context *asCtxt, 
                                              ITS_OCTET *resultData);

UALDLLAPI int UAL_CheckRoutingInfoValid(ITS_UINT *rkey, RK_Context *asCtxt);

UALDLLAPI int UAL_RoutingKeyGetLRKID(ITS_OCTET *rkData, int dataLen);



UALDLLAPI void UAL_SetRegRes(ITS_OCTET *resultData, ITS_UINT localRCtxt, 
                   ITS_UINT result, ITS_UINT rCtxt);
 
UALDLLAPI void UAL_SetSuaRegRes(ITS_OCTET *resultData, ITS_UINT localRCtxt, 
                   ITS_UINT result, ITS_UINT rCtxt);

UALDLLAPI int UAL_GetRegRes(ITS_OCTET *resultData, int size, ITS_UINT *localRCtxt,
                  ITS_UINT *result, ITS_UINT *rCtxt);

UALDLLAPI int UAL_GetSuaRegRes(ITS_OCTET *resultData, int size, ITS_UINT *localRCtxt,
                  ITS_UINT *result, ITS_UINT *rCtxt);

UALDLLAPI int UAL_EncodeSuaRoutingKey(UAL_AS_DEF *as, ITS_UAL_IE *ie,
                            ITS_UINT *localRctxt);

UALDLLAPI int UAL_DecodeSuaRoutingKey(ITS_OCTET *rkey, ITS_USHORT rKeyLen, ITS_UINT *rkid,
                                      ITS_SUA_IE *ies, ITS_OCTET *ieCount);

UALDLLAPI int UAL_SuaRoutingKeyToRKContext(RK_Context *ctxt, ITS_OCTET *rkData, 
                                 int dataLen);

UALDLLAPI ITS_BOOLEAN UAL_CheckTMValid(ITS_UINT tm); 

UALDLLAPI int UAL_GetPointCodeValue(UAL_PC pointCode);

UALDLLAPI int UAL_AddLinkSetAndDestination(RK_Context *asEntry);

UALDLLAPI ITS_OCTET
UAL_GetNextAvailableLinkCode(ITS_OCTET linkSet);

UALDLLAPI ITS_INT
UAL_AddASInfoToASManager(RESFILE_Manager *appRes, ITS_BOOLEAN fromUser);

UALDLLAPI ITS_INT
UAL_UpdateISS7_RouteInfo(ASP_Entry* aspRec, ASPListNode* prev,
                         RK_Context* rk_context, ITS_BOOLEAN flag);

ITS_INT
UAL_AddLink(RK_Context *rk_context, RKListNode *rkNode, TRANSPORT_Control *trCtrl);

ITS_INT
UAL_RemLink(ITS_OCTET linkSet, ITS_OCTET linkCode);

UALDLLAPI int
UAL_GetPadding(int size);

UALDLLAPI void
UAL_Console(DBC_Server *dbc, const char *cmdLine);

/*
 * Transport callback registration/Deregistration.
 */
UALDLLAPI void UAL_RegisterTransportCallbacks();
UALDLLAPI void UAL_DeregisterTransportCallbacks();


UALDLLAPI int UAL_UpdateASListToASP (ITS_UINT rCtxt);

ITS_INT
UAL_ProcessASPUP_IPSP_SE(ASP_Entry *aspRec, ITS_EVENT *ualEvent);

UALDLLAPI int
AuditTimersTable_FindEntry(ITS_UINT pcContext, ITS_SERIAL** timerVal);

UALDLLAPI int
AuditTimersTable_RemoveEntry(ITS_USHORT pcContext);

UALDLLAPI ITS_INT
AuditTimersTable_AddEntry(ITS_UINT pc, ITS_SERIAL *timerVal);

UALDLLAPI ITS_INT
AuditTimersTable_TimerExpiry(UAL_TimerCtx ctx);

void
UAL_NComHdrToH(UAL_MSG_HDR *msgHdr);

#if defined(__cplusplus)
}
#endif

#endif
