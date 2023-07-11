/******************************************************************************
*
*       txcpi.h - TXn000 Communications Processor Interface
*
*       This file defines the interface to the NMS/TEKnique CPI library.
*       The CPI library provides access to all TXn000 CPs installed on
*       the given host system.
*
*-----------------------------------------------------------------------------
* REV   DATE           WHO       $Log: txcpi.h,v $
* REV   DATE           WHO       Revision 9.1  2005/03/23 12:55:46  cvsadmin
* REV   DATE           WHO       Begin PR6.5
* REV   DATE           WHO
* REV   DATE           WHO       Revision 8.2  2005/03/21 13:55:06  cvsadmin
* REV   DATE           WHO       PR6.4.2 Source Propagated to Current
* REV   DATE           WHO
* REV   DATE           WHO       Revision 7.1  2002/08/26 22:10:51  mmiers
* REV   DATE           WHO       Begin PR6.2
* REV   DATE           WHO
* REV   DATE           WHO       Revision 6.1  2002/02/28 16:14:54  mmiers
* REV   DATE           WHO       Begin PR7.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1  2001/09/05 20:35:47  mmiers
* REV   DATE           WHO       Consolidate the NMS libraries.  Only the root library so far.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 5.1  2001/08/16 20:46:34  mmiers
* REV   DATE           WHO       Start PR6.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 4.1  2001/05/04 16:22:07  mmiers
* REV   DATE           WHO       Start PR5.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 3.1  2000/08/16 00:10:48  mmiers
* REV   DATE           WHO
* REV   DATE           WHO       Begin round 4.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 2.0  1999/12/03 23:33:12  mmiers
* REV   DATE           WHO
* REV   DATE           WHO       Begin third iteration.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1  1998/01/15 00:54:12  rsonak
* REV   DATE           WHO       *** empty log message ***
* REV   DATE           WHO $NoKeywords: $
* 
* 1     3/10/97 3:24p Adam
* Release 6.5 Beta to NMS Natick
* 
* 11    2/28/97 12:33p Maf
* Got rid of a C++ comment or two
* 
* 10    12/18/96 5:18p Dan
* Fixed OS/2 INVALID handle values!
* 
* 9     12/13/96 9:07a Maf
* Added a definition of putch (to putchar) in the UNIX section
* 
* 8     12/12/96 1:10p Jeffr
* Added message trace level to request/response extension
*
* 7     12/11/96 1:38p Maf
* Updated for UNIX
*
* 6     12/05/96 10:43a Dan
* New functions, YAYYY!!
*
* 5     12/03/96 4:46p Jeffr
* Added message number (API-specific usage) to MSG header
*
* 4     12/03/96 2:25p Jeffr
* Added DPR Request/Response extension headers
*
* 3     12/03/96 1:55p Maf
* Updated for UNIX
*
* 2     12/03/96 9:13a Dan
* New call called cpi_wait_msg
*
* 1     11/20/96 1:03p Jeffd
* Initial Development
*-----------------------------------------------------------------------------
******************************************************************************/

#ifndef __CPI_H
#define __CPI_H

/* ----- Operating System Specific Area */

#ifdef WIN32      /* 32 bit Windows OS */

#include    <windows.h>

#define     TXCPIFUNC               WINAPI
#define     TX_HANDLE               short
#define     CPI_ERR_TYPE            long
#define     CPI_WAIT_TYPE           HANDLE
#define     CPI_INVALID_WAIT_HANDLE INVALID_HANDLE_VALUE
#define     CPI_INVALID_HANDLE      -1

#define CPI_ERRCODE_BASE            50

#endif /* WIN32 */

#ifdef __OS2__      /*IBM OS/2*/

#include    <os2.h>

#define     TXCPIFUNC
#define     TX_HANDLE               HFILE       /*i/o handle to driver*/
#define     CPI_ERR_TYPE            long
#define     CPI_WAIT_TYPE           HEV         /*event semaphore handle*/
#define     CPI_INVALID_WAIT_HANDLE ((HEV)NULLHANDLE)
#define     CPI_INVALID_HANDLE      (NULLHANDLE)

#define CPI_ERRCODE_BASE            50

#endif /* __OS2__ */

#ifdef UNIX       /* UNIX OS */

#ifndef MIN
#define MIN(a,b) (((a)>(b))?(b):(a))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif
#ifndef min
#define min(a,b) (((a)>(b))?(b):(a))
#endif
#ifndef max
#define max(a,b) (((a)>(b))?(a):(b))
#endif

#ifndef far
#define     far
#endif

#define     putch                   putchar

#define     TXCPIFUNC
#define     TX_HANDLE               int
#define     CPI_ERR_TYPE            unsigned long
#define     CPI_WAIT_TYPE           TX_HANDLE
#define     CPI_INVALID_WAIT_HANDLE (-1)
#define     CPI_INVALID_HANDLE      (-1)

#define     CPI_ERRCODE_BASE        50

#define     cpi_wait_obj(x)         ((CPI_WAIT_TYPE)(x))

#endif /* UNIX */

/*
 * These are outdated for NT/OS2 but still needed for the UNIX platform
 */
#ifndef CPIM_CHAN
#define CPIM_CHAN	1
#endif
#ifndef CPIM_PORT
#define CPIM_PORT	2
#endif
#ifndef CPSTRSIZE
#define CPSTRSIZE	20
#endif

/*
 *  Error Return Codes
 */
#define CPI_ERROR           -1
#define CPI_SUCCESS         0
#define CPI_TRUNCATED       1
#define CPI_TIMEOUT         2

/* The CPI_XXXX error codes are ones that a user might see in normal use */
#define CPI_INVALID_HANDLE_PASSED       (CPI_ERRCODE_BASE+0)

#define CPI_INVALID_CHANNEL             (CPI_ERRCODE_BASE+1)
#define CPI_INVALID_BOARD               (CPI_ERRCODE_BASE+2)
#define CPI_INVALID_MODE                (CPI_ERRCODE_BASE+3)
#define CPI_LENGTHS_DONT_MATCH          (CPI_ERRCODE_BASE+4)
#define CPI_NO_OPEN_HANDLES             (CPI_ERRCODE_BASE+5)
#define CPI_INSUFFICIENT_BUFFER_SIZE    (CPI_ERRCODE_BASE+6)
#define CPI_CHANNEL_IN_USE              (CPI_ERRCODE_BASE+7)
#define CPI_CHANREG_FAIL                (CPI_ERRCODE_BASE+8)
#define CPI_CHANDEREG_FAIL              (CPI_ERRCODE_BASE+9)
#define CPI_NO_MEMORY                   (CPI_ERRCODE_BASE+10)
#define CPI_UNSUPPORTED_OPER            (CPI_ERRCODE_BASE+11)
#define CPI_TOO_BIG                     (CPI_ERRCODE_BASE+12)
#define CPI_NOT_READY                   (CPI_ERRCODE_BASE+13)
#define CPI_INVALID_OFFSET              (CPI_ERRCODE_BASE+14)
#define CPI_NOT_BOOT                    (CPI_ERRCODE_BASE+15)
#define CPI_NOT_LOADING                 (CPI_ERRCODE_BASE+16)
#define CPI_INVALID_BOOT_SIZE           (CPI_ERRCODE_BASE+17)


/* ----- CPI header */
typedef struct
{
  unsigned short  src;              /* Source port */
  unsigned short  dst;              /* Destination port */
  short           length;           /* length of packet, including CPI header */
} CPIHDR;

#define CPIBUFSIZE      1468
#define MAXCPIDATA      (CPIBUFSIZE - sizeof(CPIHDR))

/* ----- CPI packet */
typedef struct
{
  CPIHDR          hdr;
  unsigned char   data[MAXCPIDATA];
} CPIPKT;

/* ----- TX API Request/Response extensions to Dual Port Ram header */
typedef struct tx_dpr_hdr
{
  unsigned char  srcchan;         /* source channel number */
  unsigned char  srcboard;        /* source board number (0 = PC) */
  unsigned char  dstchan;         /* destination channel number */
  unsigned char  dstboard;        /* destination board number (0 = PC) */
  unsigned short len;             /* byte length of this header and following data */
} TX_DPR_HDR;

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

typedef struct tx_dpr_reqhdr
{
  TX_DPR_HDR      hdr;            /* Dual Port Ram header */
  TX_DPR_MSGHDR   msg;            /* Message header */
} TX_DPR_REQHDR;

typedef struct tx_dpr_rsphdr
{
  TX_DPR_HDR      hdr;            /* Dual Port Ram header */
  TX_DPR_MSGHDR   msg;            /* Message header */
  short           status;         /* Status of response */
  short           future;         /* area reserved for future extension of TX responses */
} TX_DPR_RSPHDR;

/* ----- CPI structures and literals */

/* TXn000 CP type identifiers */
#define     TX_1000     1000
#define     TX_2000     2000
#define     TX_3000     3000
#define     TX_4000     4000
#define     TX_5000     5000

#define CPI_CONTROL_CHANNEL 0       /* Channel to use for control functions */

/* Boot control channel messages (all 1 byte messages sent over CONTROL CHANNEL)*/
#define CPI_PB_READY      0x80      /* PREBOOT ready for first KERNEL block */
#define CPI_PB_LOAD       0xA8      /* PREBOOT done loading KERNEL block */
#define CPI_KERNEL_READY  0xA1      /* KERNEL completely loaded, init'd, and ready */

/* Bootstate information */
typedef struct
{
  unsigned short  state;
#define BS_BOOT         0           /* waiting to begin PREBOOT */
#define BS_READY        1           /* KERNEL completely loaded, init'd, and ready */
#define BS_INIT         2           /* KERNEL is initializing */
#define BS_DOWN         3           /* KERNEL not responding */
#define BS_BERR         4           /* Bus Error indicated by KERNEL */
#define BS_LOADING      5           /* Loading block of KERNEL */
#define BS_PREBOOTING   6           /* PREBOOT running (not ready for KERNEL yet) */
#define BS_WAIT_KERNEL  7           /* PREBOOT has completed and is waiting for KERNEL block */

  unsigned char   reg[5];
} CPIBS;

/* Driver statistics */
typedef struct
{
  unsigned short Channel;           /* 0..255 or 0xFFFF = ALL */
  unsigned short LowFreeCnt;        /* least free bfrs */
  unsigned long  PktsSentCS;        /* #packets sent */
  unsigned long  BytesSentCS;       /* #bytes sent */
  unsigned long  SendRejCS;         /* #sends rejected as ilgl */
  unsigned long  PktsRecvCS;        /* #packets recvd */
  unsigned long  BytesRecvCS;       /* #bytes recvd */
  unsigned long  RecvRejRegCS;      /* #rcv pkts rejected-no rcvr reg */
  unsigned long  RecvRejBfrCS;      /* #rcv pkts rejected-no buffer avail */
  unsigned long  RecvTruncCS;       /* #rcv pkts truncated */
} CPIDRVSTATS;

/* Macro to build port value from a board and channel */
#define PORT(board,chan) ((board << 8) + chan)

/* Maximum number of CPI channels and CP Boards */
#define MAXCHAN             64
#define MAXBOARD            8

#define MAX_OPEN_CHANNELS   32
#define MAX_HANDLES         MAX_OPEN_CHANNELS

/* ----- CPI Function Prototypes */

#ifdef __cplusplus
extern "C" {
#endif

short          TXCPIFUNC cpi_init           (short dummy, char **idstring);
TX_HANDLE      TXCPIFUNC cpi_open           (unsigned short port, short mode,
                                            short (*receiver)(short handle, short length));
short          TXCPIFUNC cpi_close          (TX_HANDLE handle);
short          TXCPIFUNC cpi_send           (TX_HANDLE handle, CPIPKT *buffer);
short          TXCPIFUNC cpi_get_data       (TX_HANDLE handle, CPIPKT *buffer, short *length);
short          TXCPIFUNC cpi_wait_msg       (TX_HANDLE handle, CPIPKT *buffer, short *length, long millisecs);
short          TXCPIFUNC cpi_check_bs       (TX_HANDLE handle, CPIBS *bsp);
short          TXCPIFUNC cpi_force_bs       (TX_HANDLE handle);
short          TXCPIFUNC cpi_get_resources  (short max_cps, long cps[]);
short          TXCPIFUNC cpi_get_eeprom     (TX_HANDLE handle, char *buffer);
short          TXCPIFUNC cpi_get_stats      (TX_HANDLE handle, short chan,
                                            CPIDRVSTATS *buffer);
short          TXCPIFUNC cpi_clear_stats    (TX_HANDLE handle, short chan);
short          TXCPIFUNC cpi_read_dpr       (TX_HANDLE handle, char *buffer,
                                            short off, short len);
short          TXCPIFUNC cpi_write_dpr      (TX_HANDLE handle, char *buffer,
                                            short off, short len);
short          TXCPIFUNC cpi_pre_boot       (TX_HANDLE handle, char *buffer, short len,
                                            unsigned short off, short xqt);
short          TXCPIFUNC cpi_load_krnl      (TX_HANDLE handle, char *buffer, short len,
                                            short *seqnum, unsigned long destaddr);
short          TXCPIFUNC cpi_exec_krnl      (TX_HANDLE handle, unsigned long startaddr,
                                            unsigned char uCode);
CPI_ERR_TYPE   TXCPIFUNC cpi_get_last_error ();
char *         TXCPIFUNC cpi_get_error_str  (CPI_ERR_TYPE errnum);
unsigned short TXCPIFUNC cpi_cptoh_s        (unsigned short src);
unsigned long  TXCPIFUNC cpi_cptoh_l        (unsigned long src);
unsigned short TXCPIFUNC cpi_htocp_s        (unsigned short src);
unsigned long  TXCPIFUNC cpi_htocp_l        (unsigned long src);
short          TXCPIFUNC cpi_get_board      (TX_HANDLE handle, unsigned char *board, unsigned char *chan);

#ifndef UNIX
CPI_WAIT_TYPE TXCPIFUNC cpi_wait_obj       (TX_HANDLE handle);
#endif /* UNIX */

#ifdef __cplusplus
}
#endif

#endif  /* __CPI_H */
