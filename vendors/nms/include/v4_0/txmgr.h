/*****************************************************************************
 *
 * txmgr.h - TX manager message definitions
 *
 *****************************************************************************/

/*****************************************************************************
 *
 *                         PROPRIETARY NOTICE
 *
 *                      Copyright (c) 1988-2004
 *                       by NMS Communications.
 *
 *  The following is licensed program material and is considered
 *  proprietary and confidential.  No part of this program may be
 *  reproduced or used in any form or by any means without the express
 *  written permission of NMS Communications.
 *
 *****************************************************************************/

#ifndef _TXMGR_H
#define _TXMGR_H

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 * PACKING: pack on 1-byte boundaries
 *xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#ifdef UNIX
#pragma pack(1)
#endif
#ifdef __HIGHC__
#pragma Push_align_members(1)
#endif
#ifdef _WINNT
#pragma pack(1)
#endif

#include <txnuser.h>                /* primitive field type definitions */
#include <dpriface.h>
#include <cosinfo.h>                /* System Information definitions */

/*###########################################################################*
 *
 * MANAGER COMMAND INTERFACE
 *
 * The manager task provides host applications with a variety of management
 * services.  The header structure defined below is used for all
 * communication to the manager task.  Other include files provide additional
 * definitions for particular management functions.
 *###########################################################################*/

/*---------------------------------------------------------------------------
 * Command Header
 *---------------------------------------------------------------------------*/
typedef struct __mgr_cmdhdr
{
    U8              version;    /* version of message protocol in use */
#define MGR_VERSION_LEGACY1 1   /* version used by legacy code (prior to SS7 4.0) */
#define MGR_VERSION         2   /* current version */

    U8              subver;     /* sub-version of message protocol */
#define MGR_SUBVER   1          /* current sub-version */

    U8              category;   /* category of commands */
#define MGR_FLASH    1          /* internal protocol: FLASH Control */
#define MGR_EEPROM   2          /* internal protocol: EEPROM Control */
#define MGR_LED      3          /* internal protocol: LED Control */
#define MGR_SYSTEM   4          /* common protocol: SYSTEM Management */

    U8              command;    /* command to perform */
#define MGR_CATEG    0x80       /* base for category-specific commands */

    U8              dir;        /* direction of command */
#define MGR_REQUEST  1          /* Request where Reply expected */
#define MGR_REPLY    2          /* Reply to previous Request */
#define MGR_NOTIF    3          /* Notification (no Reply expected) */

    U8              boardType;  /* Responses contain the board type */
#define MGR_BT_TX4000 4
    U8              avail[2];
}
MGR_CMDHDR;

/*===========================================================================
 * Common Protocol: SYSTEM Management Category
 *===========================================================================*/

/*---------------------------------------------------------------------------
 * SYSTEM Command Definitions
 *---------------------------------------------------------------------------*/
#define MGR_SYSTEM_INFO     (MGR_CATEG+0)   /* obtain copy of System Information */

/*---------------------------------------------------------------------------
 * MGR_SYSTEM_INFO Response
 *---------------------------------------------------------------------------*/
typedef struct __mgr_sysinfo
{
    MGR_CMDHDR      cmdhdr;         /* common command header */

    SYSINFO         sysinfo;        /* TX board system information */
}
MGR_SYSINFO;

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
 * PACKING: return to default
 *xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#ifdef UNIX
#pragma pack()
#endif
#ifdef _WINNT
#pragma pack()
#endif
#ifdef __HIGHC__
#pragma Pop_align_members
#endif

#endif /* _TXMGR_H */
