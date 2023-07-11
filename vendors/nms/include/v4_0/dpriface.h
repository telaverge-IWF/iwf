/*****************************************************************************
 *
 * dpriface.h - TXn000 Dual Port Ram Interface Definitions
 *
 *****************************************************************************/

/*****************************************************************************
 *
 *                         PROPRIETARY NOTICE
 *
 *                      Copyright (c) 1988-2003
 *                       by NMS Communications.
 *
 *  The following is licensed program material and is considered
 *  proprietary and confidential.  No part of this program may be
 *  reproduced or used in any form or by any means without the express
 *  written permission of NMS Communications.
 *
 *****************************************************************************/

#ifndef _DPRIFACE_H
#define _DPRIFACE_H

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

/* ----- Well-known CPI channels */
#define PT_MGR      0x00            /* Host Control Manager [$manager channel] */

#define PT_SWI      0x03            /* Switching Control Channel */

#define PT_CONSOLE  0x06            /* Console Channel */
#define PT_LOADER   0x07            /* Loader Channel */
#define PT_DEBUG    0x08            /* Debug Channel */
#define PT_MVIP     0x09            /* MVIP Control Channel */
#define PT_T1E1C    0x0A            /* T1/E1 Control Channel */
#define PT_T1E1S    0x0B            /* T1/E1 Status Channel */
#define PT_INF      0x0C            /* Alarm Manager (raw alarm channel) */
#define PT_ALARM    PT_INF          /* alternate name for alarm channel */

#define PT_SS7MON   0x0F            /* SS7 Monitor API port #1 */

#define PT_ARP      0x12            /* ARP Protocol Channel */
#define PT_SS7MON2  0x13            /* SS7 Monitor API port #2 */
#define PT_ISUP     0x14            /* SS7 ISUP Task Channel */
#define PT_MTP      0x15            /* SS7 MTP Task Channel */

#define PT_TCAP     0x17            /* SS7 TCAP Task Channel */
#define PT_IUP      0x18            /* SS7 IUP Task Channel */
#define PT_TXMON    0x19            /* TX Monitor Task Channel */

#define PT_TUP      0x1D            /* SS7 TUP Task Channel */
#define PT_SCCP     0x1E            /* SS7 SCCP Task Channel */

#define PT_TEST     0x80            /* Test Task Channel */
#define PT_INTTEST  0x81            /* Internal Test Channel */
#define PT_POUND    0x82            /* Data Load (Pounding) Test Channel */

#define PT_CONSOLE_ 0x90            /* Additional [Host-Side] Console Channel */

#define PT_VERSION  0xF3            /* Version Verification Channel */
#define PT_RESET    0xF4            /* Board Reset Channel */
#define PT_FLASH    0xF5            /* FLASH Access Channel */
#define PT_EEPROM   0xF6            /* EEPROM Access Channel */
#define PT_DUMP     0xF7            /* Memory Dump Channel */
#define PT_SNAP     0xF8            /* Snapshot Analysis Channel */
#define PT_DIAG     0xF9            /* Diagnostic Task Channel */
#define PT_REFLECT  0xFA            /* Reflect Task Channel */
#define PT_PRINTF   0xFB            /* TX-based printf Channel */
#define PT_TRACE    0xFC            /* TX-based Trace Channel */
#define PT_LOCATE   0xFD            /* TXLOCATE host channel */
#define PT_STATS    0xFE            /* TX (driver) statistics */

/* ----- TXn000 Dual Port Ram header */
typedef struct tx_dpr_hdr
{
    U8            srcchan;    /* source channel number */
    U8            srcboard;   /* source board number (0 = PC) */
    U8            dstchan;    /* destination channel number */
    U8            dstboard;   /* destination board number (0 = PC) */
    U16          len;        /* byte length of this header and following data */
#ifdef NMSTX_ALIGN_32
    U8            pad_end[2]; /* pad to 32-bit aligned structure size */
#endif
}
TX_DPR_HDR;

/* ----- TXn000 Dual Port Ram Buffer Limits */
#define CPIBUFSIZE      1996    /* max size of any CPI buffer (including DPR header) */
#define MAXCPIDATA      (CPIBUFSIZE - sizeof(TX_DPR_HDR))

/* ----- Basic Packet Definition */
typedef struct tx_dpr_pkt
{
    TX_DPR_HDR      hdr;
    U8              data[MAXCPIDATA];
}
TX_DPR_PKT;

/* ----- Message Header (used to extend basic packet capabilities) */
typedef struct tx_dpr_msghdr
{
    U8            msgdir;
#define TXMSG_TOCP    '>'       /* message being passed from HOST to TXn000 CP */
#define TXMSG_TOHOST  '<'       /* message being passed from TXn000 CP to HOST */

    U8            msgtype;
#define TXMSG_COMMAND   'C'     /* command request */
#define TXMSG_RESULT    'R'     /* result (response to command request) */
#define TXMSG_NOTIF     'N'     /* notification */
#define TXMSG_ACK       'A'     /* acknowledgement (response to notification) */

    U8          msgnum;     /* message number (specific to application interface) */
    U8          msgtrc;     /* trace level    (specific to application interface) */
    U32         msgid;      /* unique id of COMMAND|NOTIF [returned in RESULT|ACK] */
    U32         msgkey;     /* key assoc'd w/ COMMAND|NOTIF [returned in RESULT|ACK] */
    U32         future;     /* area reserved for future extension of TX MSG control */
}
TX_DPR_MSGHDR;

/* ----- Request Message Header */
typedef struct tx_dpr_reqhdr
{
    TX_DPR_HDR      hdr;        /* Dual Port Ram header */
    TX_DPR_MSGHDR   msg;        /* Message header */
}
TX_DPR_REQHDR;

/* ----- Response Message Header */
typedef struct tx_dpr_rsphdr
{
    TX_DPR_HDR      hdr;        /* Dual Port Ram header */
    TX_DPR_MSGHDR   msg;        /* Message header */
    S16             status;     /* Status of response */
    S16             future;     /* area reserved for future extension of TX responses */
}
TX_DPR_RSPHDR;

/* ----- Notification Message Header */
typedef struct tx_dpr_notifhdr
{
    TX_DPR_HDR      hdr;        /* Dual Port Ram header */
    TX_DPR_MSGHDR   msg;        /* Message header */
}
TX_DPR_NOTIFHDR;

/* ----- Acknowledgment Message Header */
typedef struct tx_dpr_ackhdr
{
    TX_DPR_HDR      hdr;        /* Dual Port Ram header */
    TX_DPR_MSGHDR   msg;        /* Message header */
}
TX_DPR_ACKHDR;

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

#endif  /* _DPRIFACE_H */
