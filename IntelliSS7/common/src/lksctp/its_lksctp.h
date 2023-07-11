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
 *  ID: $Id: its_lksctp.h,v 1.4 2008/06/27 14:22:03 mpatri Exp $
 *
 * LOG: $Log: its_lksctp.h,v $
 * LOG: Revision 1.4  2008/06/27 14:22:03  mpatri
 * LOG: Accelero CGI Phase I: Modification to adopt code review comments & Fixing other issues
 * LOG:
 * LOG: Revision 1.3  2008/06/20 11:06:07  mpatri
 * LOG: Accelero CGI Phase I:Fixing compilation & other issues
 * LOG:
 * LOG: Revision 1.2  2008/04/15 05:03:15  kramesh
 * LOG: Merged Persistent Branch Changes to current.
 * LOG:
 * LOG: Revision 1.1.52.2  2008/02/25 10:58:40  omayor
 * LOG: modification to support C++ API for SCTP client Transport
 * LOG:
 * LOG: Revision 1.1.52.1  2007/03/29 06:11:53  pspl
 * LOG: abhijeet: Alarm support for the lksctp module added
 * LOG:
 * LOG: Revision 1.1  2005/06/02 06:54:35  yranade
 * LOG: Linux Kernel SCTP Integration as per ACC652-SDS-LKSC-V1.0.02.
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: its_lksctp.h,v 1.4 2008/06/27 14:22:03 mpatri Exp $"

#if !defined(ITS_LKSCTP_H)
#define ITS_LKSCTP_H

#include <its_tq_trans.h>
#include <dbc_serv.h>
#include <its_sockets.h>

#if defined(linux)
#include <sys/socket.h>
//#include <netinet/in.h>   //commented to fix compilation issue
#include <netinet/sctp.h>
#include <sys/types.h>
#include <sys/socket.h>
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
SCTPDLLAPI extern ITS_Class        itsLKSCTP_Class;        /* protocol engine */
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
 * LKSCTP Alarm numbers (maximum and Minimum)
 *
 *****************************************************************************/
#define LKSCTP_ALARM_START   7001
#define LKSCTP_ALARM_END     7006


/*****************************************************************************
 *
 * The LKSCTP General Configuration.
 *
 *****************************************************************************/
typedef struct
{
    MGMT_AlarmLevel alarmLevel;
    ITS_BOOLEAN     traceOn;     /* on(1), off(0) */
    ITS_CHAR        traceType[ITS_PATH_MAX];
    ITS_CHAR        traceOutput[ITS_PATH_MAX];
}
LKSCTPGeneralCfg;

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
LKSCTP_AssocDb;

/*****************************************************************************
 *
 * hash table contents.
 *
 *****************************************************************************/
typedef struct _SCTP_HE
{
    struct _SCTP_HE     *next;
    LKSCTP_AssocDb      *assocDb;
}
SCTP_HashEntry;



/*****************************************************************************
 *
 * socket table contents.
 *
 *****************************************************************************/
#define LKSCTP_MAX_SOCKETS     256

typedef struct
{
    int fd;
    ITS_USHORT  localPort;     /* source port */
    ITS_BOOLEAN firstInterface;
}
LKSCTP_SockTableEntry;

typedef struct
{
    LKSCTP_SockTableEntry* data[LKSCTP_MAX_SOCKETS];
}
LKSCTP_SocketTable;

/*****************************************************************************
 *
 * Manager structure
 *
 *****************************************************************************/
typedef struct
{
    TQUEUETRAN_Manager  *queue;
    ITS_MUTEX           gate;
    HASH_Table          assocDb;   
    LKSCTP_SocketTable  sockets;
}
LKSCTP_Manager;

#if 0

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
}
LKSCTP_Manager;
#endif

void LKSCTP_Console(DBC_Server *dbc, const char *cmdLine);

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

extern sctp_assoc_t                         
FindAssocId(int sd, struct sockaddr_in *remote); 

#endif /* ITS_LKSCTP_H */


