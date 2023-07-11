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
 *  ID: $Id: its_sksctp.h,v 1.4 2008/07/16 07:25:02 skatta Exp $
 *
 * LOG: $Log: its_sksctp.h,v $
 * LOG: Revision 1.4  2008/07/16 07:25:02  skatta
 * LOG: Accelero CGI: Fixing compilation issue
 * LOG:
 * LOG: Revision 1.3  2008/06/04 06:32:06  ssingh
 * LOG: ALU porting, B-0100LX-LUSG-00 (june 04,2008 base)
 * LOG:
 * LOG: Revision 1.2  2007/01/10 11:15:10  yranade
 * LOG: Merge changes from 6.5.3 and Lucent branches
 * LOG:
 * LOG: Revision 1.1.2.2  2006/10/21 04:07:50  dsatish
 * LOG: Change number of associations
 * LOG:
 * LOG: Revision 1.1.2.1  2006/03/15 10:56:15  dsatish
 * LOG: Initial code base for Solaris Kernel SCTP.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_SKSCTP_H)
#define ITS_SKSCTP_H

#include <its_tq_trans.h>
#include <dbc_serv.h>
#include <its_sockets.h>

#if defined(solaris)
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/sctp.h>
#endif

#if !defined(SCTP_IMPLEMENTATION)
#define SCTPDLLAPI   ITSDLLAPI
#else
#define SCTPDLLAPI
#endif

/*
 * feature record(s)
 */
SCTPDLLAPI extern ITS_Class        itsSKSCTP_Class;        /* protocol engine */
ITSDLLAPI  extern ITS_ClassRec     itsSCTPTRAN_ClassRec;   /* transport wrapper */
ITSDLLAPI  extern ITS_Class        itsSCTPTRAN_Class;      /* transport wrapper */

#define SCTPTRAN_CLASS_NAME "SCTP Transport Feature"


/*****************************************************************************
 *
 * Generic management data.
 *
 *****************************************************************************/
/*
 * alarm levels
 */
typedef enum
{
    ALARM_OFF,
    ALARM_DEFAULT,
    ALARM_DEBUG,
    ALARM_DETAIL
}
MGMT_AlarmLevel;

/*****************************************************************************
 *
 * The SKSCTP General Configuration.
 *
 *****************************************************************************/
typedef struct
{
    MGMT_AlarmLevel alarmLevel;
    ITS_BOOLEAN     traceOn;     /* on(1), off(0) */
    ITS_CHAR        traceType[ITS_PATH_MAX];
    ITS_CHAR        traceOutput[ITS_PATH_MAX];
}
SKSCTPGeneralCfg;

/*****************************************************************************
 *
 * Association Database Block
 *
 *****************************************************************************/
typedef struct
{
    ITS_USHORT     localPort;          /* source port */
    SOCK_AddrStore remote;             /* remote address */
    sctp_assoc_t   assocId;            /* Assocation Id */
}
SKSCTP_AssocDb;

/*****************************************************************************
 *
 * hash table contents.
 *
 *****************************************************************************/
typedef struct _SCTP_HE
{
    struct _SCTP_HE     *next;
    SKSCTP_AssocDb      *assocDb;
}
SCTP_HashEntry;

/*****************************************************************************
 *
 * socket table contents.
 *
 *****************************************************************************/
#define SKSCTP_MAX_SOCKETS     1500

typedef struct
{
    int fd;
    ITS_USHORT  localPort;
    ITS_BOOLEAN firstInterface;
}
SKSCTP_SockTableEntry;

typedef struct
{
    SKSCTP_SockTableEntry* data[SKSCTP_MAX_SOCKETS];
}
SKSCTP_SocketTable;

/*****************************************************************************
 *
 * Manager structure
 *
 *****************************************************************************/
typedef struct
{
    TQUEUETRAN_Manager  *queue;
    ITS_MUTEX           gate;
    ITS_USHORT          localPort;     /* source port */
    HASH_Table          assocDb;   
    SKSCTP_SocketTable  sockets;
}
SKSCTP_Manager;

void SKSCTP_Console(DBC_Server *dbc, const char *cmdLine);

/*****************************************************************************
 *
 * These two constants are defined for socket-level recv and send timeouts.
 * Depending on performance change these values.
 * The values are in seconds.
 *
 *****************************************************************************/
#define RCV_NON_BLOCKING_TIMEOUT_VAL 5
#define SND_NON_BLOCKING_TIMEOUT_VAL 2

/*****************************************************************************
 *
 * These two IOCTLs are used for the above two timeouts.
 *
 *****************************************************************************/
#define IOCTL_SET_RCV_NON_BLOCKING_TIMEOUT 0x0021
#define IOCTL_SET_SND_NON_BLOCKING_TIMEOUT 0x0022


/*****************************************************************************
 *
 * Transport state NOTE NOTE NOTE
 * This is a exact copy of SCTP_STATE in <its_sctp_impl.h>
 * and should alway reflect the same!
 *
 *****************************************************************************/
#if 0
typedef enum
{
    ITS_SCTP_CLOSED,
    ITS_SCTP_COOKIE_WAIT,
    ITS_SCTP_COOKIE_SENT,    /* This is COOKIE_ECHOED */
    ITS_SCTP_ESTABLISHED,
    ITS_SCTP_SHUTDOWN_PENDING,
    ITS_SCTP_SHUTDOWN_SENT,
    ITS_SCTP_SHUTDOWN_RECEIVED,
    ITS_SCTP_SHUTDOWN_ACK_SENT
}
ITS_SCTP_STATE;

#endif /* ITS_SKSCTP_H */
#endif /* ITS_SKSCTP_H */

