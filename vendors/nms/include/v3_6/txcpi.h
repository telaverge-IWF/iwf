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
* REV   DATE           WHO       Revision 9.1  2005/03/23 12:55:57  cvsadmin
* REV   DATE           WHO       Begin PR6.5
* REV   DATE           WHO
* REV   DATE           WHO       Revision 8.2  2005/03/21 13:55:21  cvsadmin
* REV   DATE           WHO       PR6.4.2 Source Propagated to Current
* REV   DATE           WHO
* REV   DATE           WHO       Revision 7.1  2002/08/26 22:10:59  mmiers
* REV   DATE           WHO       Begin PR6.2
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.2  2002/05/16 15:53:32  hcho
* REV   DATE           WHO       Modifications for v3_6.
* REV   DATE           WHO
* REV   DATE           WHO       Revision 1.1.2.1  2001/12/21 21:25:25  hcho
* REV   DATE           WHO       Initialize v3.6 build.
* REV   DATE           WHO $NoKeywords: $
* 
* 30    4/14/:0 5:06p Raranas
* Merging PR333 to rel_5_0/Mainline.
* 
* 29    4/07/:0 3:14p Jrego
* CPI short/long conversion functions changed to macros [txnuser
* determines macro functions]
*
* 28    4/07/:0 1:45p Jrego
*
* 29    4/05/:0 1:56p Jrego
* removed merge conflicts
*
* 28    4/05/:0 11:42a Jrego
* Merging cpi_set_cpid function
*
* 29    3/21/:0 3:56p Jrego
* changed raw read/write offsets to longs
*
* 28    3/21/:0 12:04p Jrego
*
* 27    4/05/:0 11:33a Jrego
* Merging PR334 to rel_5_0/Mainline.
*
* 30    4/02/:0 12:56p Jrego
*
* 29    3/21/:0 2:08p Jrego
* added cpi_set_cpid function
*
* 28    3/20/:0 3:28p Jrego
*
* 26    3/16/:0 12:35p Jrego
* Merging PR311 from rel_4_2 to rel_5_0/Mainline.
*
* 29    3/15/:0 11:35a Jrego
* using NMSTX_ALIGN_32 to control natural alignment
*
* 28    3/06/:0 4:49p Jrego
* padding only within #ifdef __sparc
*
* 27    2/29/:0 11:01a Jrego
* Natural Alignment applied to structure definitions
*
* 26    2/28/:0 5:12p Jrego
*
* 24    5/26/99 6:00p Jrego
* Migrating to new Core Group source control system
*
* 23    8/21/98 2:05p Vince
* Added end-of-line at end-of-file.
*
* 22    8/10/98 10:16a Jeffr
* Support for co-existance with TXn PCI devices [changes by Don Dement]
*
*=========> D.DeMent   3210/20 support
*
* 21    3/30/98 9:05a Maf
* Put in changes for Solaris port (mostly ifdefed with __sun)
*
* 20    1/06/98 10:32a Vince
* Added literal for preboot error.
*
* 19    10/22/97 10:20a Vince
* Duplicated function prototypes and changed location of export
* directives so that the OS2 compiler would accept the declarations.
*
* 18    10/07/97 4:06p Sajani
* MAXCHAN and MAX_OPEN_CHANNEL changed to 256
*
* 17    9/10/97 3:52p Adam
* Fix export problems
*
* 16    8/29/97 6:12p Jeffd
* Convert _syscall function modifier for OS/2 to _System for
* compatibility with IBM compiler.
*
* 15    6/26/97 2:52p Jeffr
* Moved common structure definitions to dpriface.h
*
* 14    6/19/97 12:23p Vince
* Added headers for notification (CP->host) and acknowledgement
* (host->CP) packets.
*
* 13    5/16/97 12:49p Vince
* Removed keyword extern from macro TXCPIFUNC (DLL source definition).
*
* 12    5/16/97 10:37a Vince
* Changed the macro TXCPIFUNC to export DLL routines correctly for WIN32
* and OS/2.
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

#include <txnuser.h>          /* include base TXN user interface */
#include <dpriface.h>

#ifdef TXXPORT
#undef   TXXPORT
#endif

/* ----- Operating System Specific Area */
/* WIN32: CPI API is a DLL */

#ifdef WIN32      /* 32 bit Windows OS */

#include    <windows.h>
/*
 * The following macro conditional is to ensure proper export of CPI
 * routines.
 */
#ifdef _TX_CPI_SOURCE_
#define     TXXPORT     __declspec( dllexport )
#define     TXCPIFUNC   WINAPI
#else
    /* CPI API caller's definition */
#define     TXXPORT
#define     TXCPIFUNC   WINAPI
#endif  /* _TX_CPI_SOURCE_ */


#define     TX_HANDLE               short
#define     CPI_ERR_TYPE            long
#define     CPI_WAIT_TYPE           HANDLE
#define     CPI_INVALID_WAIT_HANDLE INVALID_HANDLE_VALUE
#define     CPI_INVALID_HANDLE      -1

#define CPI_ERRCODE_BASE            50

#endif /* WIN32 */

#ifdef __OS2__      /*IBM OS/2*/

#include    <os2.h>

/*
 * The following macro conditional is to ensure proper export of CPI
 * routines.
 */
#ifdef _TX_CPI_SOURCE_
    /* CPI API source definition */
#define     TXXPORT     __export
#define     TXCPIFUNC   _System
#else
    /* CPI API caller's definition */
#define     TXXPORT
#define     TXCPIFUNC   _System
#endif

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
#define     TXXPORT
#define     TX_HANDLE               int
#define     CPI_ERR_TYPE            unsigned long
#define     CPI_WAIT_TYPE           TX_HANDLE
#define     CPI_INVALID_WAIT_HANDLE (-1)
#define     CPI_INVALID_HANDLE      (-1)

#define     CPI_ERRCODE_BASE        50

#define     cpi_wait_obj(x)         ((CPI_WAIT_TYPE)(x))

#endif /* UNIX */

/*
 * CP Type Identifiers
 */
#define CPI_ISA_BUS     1
#define CPI_PCI_BUS     2

/*
 * These are outdated for NT/OS2 but still needed for the UNIX platform
 */
#ifndef CPIM_CHAN
#define CPIM_CHAN       1
#endif
#ifndef CPIM_PORT
#define CPIM_PORT       2
#endif
#ifndef CPSTRSIZE
#define CPSTRSIZE       20
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
#define CPI_INVALID_LED                 (CPI_ERRCODE_BASE+18)
#define CPI_READ_TIMEOUT                (CPI_ERRCODE_BASE+19)

#ifdef __sun
#pragma pack(1)
#endif  /* __sun */
/* ----- CPI header */
typedef struct
{
  unsigned short  src;              /* Source port */
  unsigned short  dst;              /* Destination port */
  short           length;           /* length of packet, including CPI header */
#ifdef NMSTX_ALIGN_32
  unsigned char   pad_end[2];       /* pad to 32-bit aligned structure size */
#endif
} CPIHDR;

/* ----- CPI packet */
typedef struct
{
  CPIHDR          hdr;
  unsigned char   data[MAXCPIDATA];
} CPIPKT;

/* ----- CPI structures and literals */

/* TXn000 CP type identifiers */
#define     TX_1000     1000
#define     TX_2000     2000
#define     TX_3000     3000
#define     TX_3210     3210
#define     TX_3220     3220
#define     TX_4000     4000
#define     TX_5000     5000
#define     TX_UNKN     0xFFFF

#define CPI_CONTROL_CHANNEL 0       /* Channel to use for control functions */

/* Boot control channel messages (all 1 byte messages sent over CONTROL CHANNEL)*/
#define CPI_PB_READY      0x80      /* PREBOOT ready for first KERNEL block */
#define CPI_PB_LOAD       0xA8      /* PREBOOT done loading KERNEL block */
#define CPI_PB_ERR        0xA9      /* PREBOOT err while loading KERNEL block */
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

#ifdef __sun
#pragma pack()
#endif  /* __sun */

/* Macros to convert between port value and board/channel */
#ifdef NMSTX_HOST_BIGENDIAN
#define PORT(board,chan) ((chan << 8) + board)
#define BOARD(port)      (port & 0x00FF)
#define CHANNEL(port)    ((port >> 8) & 0x00FF)
#else
#define PORT(board,chan) ((board << 8) + chan)
#define BOARD(port)      ((port >> 8) & 0x00FF)
#define CHANNEL(port)    (port & 0x00FF)
#endif /* NMSTX_HOST_BIGENDIAN */

/* Maximum number of CPI channels and CP Boards */
#define MAXCHAN             256
#define MAXBOARD            32

#define MAX_OPEN_CHANNELS   256
#define MAX_HANDLES         MAX_OPEN_CHANNELS


/* NMI comntrol state constants used with cpi_nmi() */

#define CPI_NMI_ASSERT          1       /* assert NMI */
#define CPI_NMI_DEASSERT        0       /* deassert NMI */

/* ----- CPI Function Prototypes */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __OS2__
short TXXPORT   TXCPIFUNC cpi_init                   (short dummy, char **idstring);
TX_HANDLE TXXPORT       TXCPIFUNC cpi_open           (unsigned short port, short mode,
                                                      short (*receiver)(short handle, short length));
short TXXPORT           TXCPIFUNC cpi_close          (TX_HANDLE handle);
short TXXPORT           TXCPIFUNC cpi_send           (TX_HANDLE handle, CPIPKT *buffer);
short TXXPORT           TXCPIFUNC cpi_get_data       (TX_HANDLE handle, CPIPKT *buffer, short *length);
short TXXPORT           TXCPIFUNC cpi_wait_msg       (TX_HANDLE handle, CPIPKT *buffer, short *length, long millisecs);
short TXXPORT           TXCPIFUNC cpi_check_bs       (TX_HANDLE handle, CPIBS *bsp);
short TXXPORT           TXCPIFUNC cpi_force_bs       (TX_HANDLE handle);
short TXXPORT           TXCPIFUNC cpi_get_resources  (short max_cps, long cps[]);
short TXXPORT           TXCPIFUNC cpi_get_eeprom     (TX_HANDLE handle, char *buffer);
short TXXPORT           TXCPIFUNC cpi_get_stats      (TX_HANDLE handle, short chan,
                                                      CPIDRVSTATS *buffer);
short TXXPORT           TXCPIFUNC cpi_clear_stats    (TX_HANDLE handle, short chan);
short TXXPORT           TXCPIFUNC cpi_read_dpr       (TX_HANDLE handle, char *buffer,
                                                      unsigned long off, short len);
short TXXPORT           TXCPIFUNC cpi_write_dpr      (TX_HANDLE handle, char *buffer,
                                                      unsigned long off, short len);
short TXXPORT           TXCPIFUNC cpi_pre_boot       (TX_HANDLE handle, char *buffer, short len,
                                                      unsigned short off, short xqt);
short TXXPORT           TXCPIFUNC cpi_load_krnl      (TX_HANDLE handle, char *buffer, short len,
                                                      short *seqnum, unsigned long destaddr);
short TXXPORT           TXCPIFUNC cpi_exec_krnl      (TX_HANDLE handle, unsigned long startaddr,
                                                      unsigned char uCode);
CPI_ERR_TYPE    TXXPORT TXCPIFUNC cpi_get_last_error ();
char *          TXXPORT TXCPIFUNC cpi_get_error_str  (CPI_ERR_TYPE errnum);
#define cpi_cptoh_s(x) NMSTX_CPTOH_S(x)
#define cpi_cptoh_l(x) NMSTX_CPTOH_L(x)
#define cpi_htocp_s(x) NMSTX_HTOCP_S(x)
#define cpi_htocp_l(x) NMSTX_HTOCP_L(x)
short TXXPORT           TXCPIFUNC cpi_get_board      (TX_HANDLE handle, unsigned char *board, unsigned char *chan);


#ifndef UNIX
CPI_WAIT_TYPE TXXPORT   TXCPIFUNC cpi_wait_obj       (TX_HANDLE handle);
#endif /* UNIX */
#else
TXXPORT short          TXCPIFUNC cpi_init           (short dummy, char **idstring);
TXXPORT TX_HANDLE      TXCPIFUNC cpi_open           (unsigned short port, short mode,
                                                     short (*receiver)(short handle, short length));
TXXPORT short          TXCPIFUNC cpi_close          (TX_HANDLE handle);
TXXPORT short          TXCPIFUNC cpi_send           (TX_HANDLE handle, CPIPKT *buffer);
TXXPORT short          TXCPIFUNC cpi_get_data       (TX_HANDLE handle, CPIPKT *buffer, short *length);
TXXPORT short          TXCPIFUNC cpi_wait_msg       (TX_HANDLE handle, CPIPKT *buffer, short *length, long millisecs);
TXXPORT short          TXCPIFUNC cpi_check_bs       (TX_HANDLE handle, CPIBS *bsp);
TXXPORT short          TXCPIFUNC cpi_force_bs       (TX_HANDLE handle);
TXXPORT short          TXCPIFUNC cpi_get_resources  (short max_cps, long cps[]);
TXXPORT short          TXCPIFUNC cpi_get_eeprom     (TX_HANDLE handle, char *buffer);
TXXPORT short          TXCPIFUNC cpi_get_stats      (TX_HANDLE handle, short chan,
                                                     CPIDRVSTATS *buffer);
TXXPORT short          TXCPIFUNC cpi_clear_stats    (TX_HANDLE handle, short chan);
TXXPORT short          TXCPIFUNC cpi_read_dpr       (TX_HANDLE handle, char *buffer,
                                                     unsigned long off, short len);
TXXPORT short          TXCPIFUNC cpi_write_dpr      (TX_HANDLE handle, char *buffer,
                                                     unsigned long off, short len);
TXXPORT short          TXCPIFUNC cpi_pre_boot       (TX_HANDLE handle, char *buffer, short len,
                                                     unsigned short off, short xqt);
TXXPORT short          TXCPIFUNC cpi_load_krnl      (TX_HANDLE handle, char *buffer, short len,
                                                     short *seqnum, unsigned long destaddr);
TXXPORT short          TXCPIFUNC cpi_exec_krnl      (TX_HANDLE handle, unsigned long startaddr,
                                                     unsigned char uCode);
TXXPORT CPI_ERR_TYPE   TXCPIFUNC cpi_get_last_error ();
TXXPORT char *         TXCPIFUNC cpi_get_error_str  (CPI_ERR_TYPE errnum);
#define cpi_cptoh_s(x) NMSTX_CPTOH_S(x)
#define cpi_cptoh_l(x) NMSTX_CPTOH_L(x)
#define cpi_htocp_s(x) NMSTX_HTOCP_S(x)
#define cpi_htocp_l(x) NMSTX_HTOCP_L(x)
TXXPORT short          TXCPIFUNC cpi_get_board      (TX_HANDLE handle, unsigned char *board, unsigned char *chan);

TXXPORT short          TXCPIFUNC cpi_read_control    (TX_HANDLE handle, unsigned short basereg,
                                                      unsigned short numreg,
                                                      unsigned long * regarray,
                                                      unsigned short * actcnt);
TXXPORT short          TXCPIFUNC cpi_write_control   (TX_HANDLE handle, unsigned short basereg,
                                                      unsigned short numreg,
                                                      unsigned long * regarray,
                                                      unsigned short * actcnt);
TXXPORT short          TXCPIFUNC cpi_set_led         (TX_HANDLE handle,
                                                      unsigned char andmask,
                                                      unsigned char ormask);
short TXXPORT          TXCPIFUNC cpi_nmi             (TX_HANDLE handle, unsigned long state);
short TXXPORT          TXCPIFUNC cpi_set_cpid        (short type, unsigned long param1, unsigned long param2,
                                                      unsigned long cpId);

#ifndef UNIX
TXXPORT CPI_WAIT_TYPE TXCPIFUNC cpi_wait_obj         (TX_HANDLE handle);
#endif /* UNIX */
#endif /* OS2 */

#ifdef  __sun
#ifndef _REENTRANT
#define _REENTRANT
#endif
#include <errno.h>      /* get reentrant definition of errno */
#include <pthread.h>
CPI_ERR_TYPE    __cpi_geterr(void);
#define cpi_errno       __cpi_geterr()
#define CPI_SETERR(x)   __cpi_seterr(x)
#else   /* __sun */
#define CPI_SETERR(x)   (cpi_errno = x)
#endif  /* __sun */

#ifdef __cplusplus
}
#endif

#endif  /* __CPI_H */
