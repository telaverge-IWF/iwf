/******************************************************************************
*
*       dpriface.h - TXn000 Dual Port Ram Interface Definitions
*
*       This file defines the common header structures used when a host
*       is communicating with software on the TXn000 [via the Dual Port Ram].
*
*-----------------------------------------------------------------------------
* REV   DATE           WHO       $Log: dpriface.h,v $
* REV   DATE           WHO       Revision 9.1  2005/03/23 12:55:50  cvsadmin
* REV   DATE           WHO       Begin PR6.5
* REV   DATE           WHO
* REV   DATE           WHO       Revision 8.2  2005/03/21 13:55:14  cvsadmin
* REV   DATE           WHO       PR6.4.2 Source Propagated to Current
* REV   DATE           WHO
* REV   DATE           WHO       Revision 7.1  2002/08/26 22:10:52  mmiers
* REV   DATE           WHO       Begin PR6.2
* REV   DATE           WHO
* REV   DATE           WHO       Revision 6.1  2002/02/28 16:14:54  mmiers
* REV   DATE           WHO       Begin PR7.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1  2001/09/05 20:35:47  mmiers
* REV   DATE           WHO       Consolidate the NMS libraries.  Only the root library so far.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 5.1  2001/08/16 20:46:39  mmiers
* REV   DATE           WHO       Start PR6.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 4.1  2001/05/04 16:22:07  mmiers
* REV   DATE           WHO       Start PR5.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 3.1  2000/08/16 00:11:22  mmiers
* REV   DATE           WHO
* REV   DATE           WHO       Begin round 4.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.4  2000/06/09 22:02:24  randresol
* REV   DATE           WHO       Adding file to current tree
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1.2.1  2000/05/16 21:17:18  randresol
* REV   DATE           WHO       Add include files for SS7 Version 3 software for TX3220
* REV   DATE           WHO $NoKeywords: $
* 
* 15    5/26/99 10:07a Jrego
* Migrating to new Core Group source control system
* 
* 14    4/30/99 10:19a Sdalal
* PT_ROUTER moved from 0x23 to 0x1A
*
* 13    4/27/99 1:35p Sdalal
* added channel for router task
*
* 12    3/03/99 2:34p Jeffr
* Added well known ports for TEST and SNAPSHOT interface
*
* 11    2/24/99 1:37p Jdement
* Add entity ID/host bus channel for TXMON task
*
* 10    10/19/98 3:41p Drothschild
* Selected entity ID for IUP
*
* 9     9/30/98 5:25p Adam
* Add PT_HIP2 Port.
*
* 8     6/09/98 2:54p Jeffr
* Added PT_MGR - host control manager
*
* 7     6/04/98 4:48p Jeffd
* Assign 2 DPR channels on host side for use by SS7 monitor process;
* re-use
* obsolete generic "PT_SS7" channel.
*
* 6     5/26/98 4:39p Jeffr
* Added TEST port definition
*
* 5     3/30/98 9:05a Maf
* Put in changes for Solaris port (mostly ifdefed with __sun)
*
* 4     10/17/97 10:23a Adam
* Merge from DEVTXN back into TXN
*
* 5     8/25/97 12:27p Adam
* Move ICMP Well known port
*
* 4     8/22/97 12:01p Adam
* Add ICMP Port type
*
* 3     7/18/97 1:28p Adam
*
* 2     6/26/97 3:12p Adam
* H323 Development
*
* 1     6/26/97 2:52p Jeffr
* Moved common structure definitions to dpriface.h
*-----------------------------------------------------------------------------
******************************************************************************/

#ifndef __DPRIFACE_H
#define __DPRIFACE_H

/* ----- Dual Port RAM ports */
#define PT_MGR      0x00       /* Host Control Manager [$manager channel] */
#define PT_NBX      0x01       /* NetBios to X25 id */
#define PT_HIP      0x02       /* Host IP port id */
#define PT_FILEMNGR 0x03       /* file manager id */
#define PT_X25      0x04       /* X25 transmission over packet driver */
#define PT_NETMNGR  0x05       /* network manager id */
#define PT_CONSOLE  0x06       /* console port id */
#define PT_LOADER   0x07       /* task loader port id */
#define PT_DEBUG    0x08       /* debug port id */
#define PT_MVIP     0x09       /* MVIP Control port */
#define PT_T1E1C    0x0a       /* T1/E1 Control port */
#define PT_T1E1S    0x0b       /* T1/E1 Status port */
#define PT_INF      0x0c       /* INF raw alarm port id */
#define PT_VPD      0x0d       /* Virtual Port Driver */
#define PT_ICMP     0x0e       /* ICMP Protocol */

#define PT_SS7MON   0x0f       /* SS7 Monitor API port #1 */
#define PT_RTCP     0x10       /* Real-Time Transport Control Protocol */
#define PT_RTP      0x11       /* Real-Time Transport Protocol */
#define PT_ARP      0x12       /* ARP Protocol */
#define PT_SS7MON2  0x13       /* SS7 Monitor API port #2 */

#define PT_ISUP     0x14
#define PT_MTP      0x15
#define PT_TCAP     0x17
#define PT_IUP      0x18
#define PT_TXMON    0x19       /* TX Monitor task on board */
#define PT_ROUTER   0x1A       /* Router task channel */

#define PT_HIP2     0x1C       /* Host IP port #2 */

#define PT_TUP      0x1d
#define PT_SCCP     0x1e
#define PT_RMTDPR   0x1f       /* Remote DPR control port id */
#define PT_TEST     0x20       /* Test task port */
#define PT_INTTEST  0x21       /* Internal test port id */
#define PT_SNAP     0x22       /* snapshot analysis channel */

#ifdef __sun
#pragma pack(1)
#endif	/* __sun */
/* ----- TXn000 Dual Port Ram header */
typedef struct tx_dpr_hdr
{
  unsigned char  srcchan;         /* source channel number */
  unsigned char  srcboard;        /* source board number (0 = PC) */
  unsigned char  dstchan;         /* destination channel number */
  unsigned char  dstboard;        /* destination board number (0 = PC) */
  unsigned short len;             /* byte length of this header and following data */
} TX_DPR_HDR;

/* ----- TXn000 Dual Port Ram Buffer Limits */
#define CPIBUFSIZE      1468      /* max size of any Dual Port Ram buffer */
#define MAXCPIDATA      (CPIBUFSIZE - sizeof(TX_DPR_HDR))

/* ----- Basic Packet Definition */
typedef struct tx_dpr_pkt
{
  TX_DPR_HDR      hdr;
  unsigned char   data[MAXCPIDATA];
} TX_DPR_PKT;

/* ----- Message Header (used to extend basic packet capabilities) */
typedef struct tx_dpr_msghdr
{
  unsigned char   msgdir;
#define TXMSG_TOCP    '>'         /* message being passed from HOST to TXn000 CP */
#define TXMSG_TOHOST  '<'         /* message being passed from TXn000 CP to HOST */

  unsigned char   msgtype;
#define TXMSG_COMMAND   'C'       /* command request */
#define TXMSG_RESULT    'R'       /* result (response to command request) */
#define TXMSG_NOTIF     'N'       /* notification */
#define TXMSG_ACK       'A'       /* acknowledgement (response to notification) */

  unsigned char   msgnum;         /* message number (specific to application interface) */
  unsigned char   msgtrc;         /* trace level    (specific to application interface) */
  unsigned long   msgid;          /* unique id of COMMAND|NOTIF [returned in RESULT|ACK] */
  unsigned long   msgkey;         /* key assoc'd w/ COMMAND|NOTIF [returned in RESULT|ACK] */
  unsigned long   future;         /* area reserved for future extension of TX MSG control */
} TX_DPR_MSGHDR;

/* ----- Request Message Header */
typedef struct tx_dpr_reqhdr
{
  TX_DPR_HDR      hdr;            /* Dual Port Ram header */
  TX_DPR_MSGHDR   msg;            /* Message header */
} TX_DPR_REQHDR;

/* ----- Response Message Header */
typedef struct tx_dpr_rsphdr
{
  TX_DPR_HDR      hdr;            /* Dual Port Ram header */
  TX_DPR_MSGHDR   msg;            /* Message header */
  short           status;         /* Status of response */
  short           future;         /* area reserved for future extension of TX responses */
} TX_DPR_RSPHDR;

/* ----- Notification Message Header */
typedef struct tx_dpr_notifhdr
{
  TX_DPR_HDR      hdr;            /* Dual Port Ram header */
  TX_DPR_MSGHDR   msg;            /* Message header */
} TX_DPR_NOTIFHDR;

/* ----- Acknowledgment Message Header */
typedef struct tx_dpr_ackhdr
{
  TX_DPR_HDR      hdr;            /* Dual Port Ram header */
  TX_DPR_MSGHDR   msg;            /* Message header */
} TX_DPR_ACKHDR;

#ifdef __sun
#pragma pack()
#endif /* __sun */

#endif  /* __DPRIFACE_H */
