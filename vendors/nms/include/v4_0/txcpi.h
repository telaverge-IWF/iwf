/*****************************************************************************
 *
 * txcpi.h - TXn000 Communications Processor Interface
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

#ifndef _TXCPI_H
#define _TXCPI_H

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

#include <txnuser.h>                /* include base TXN user interface */
#include <txstats.h>                /* include TX statistics definitions */
#include <dpriface.h>
#include <sys/types.h>

#ifdef TXXPORT
#undef TXXPORT
#endif

#define MAX_CHANNELS (100)
#define CPIO_NOT_IN_USE (-1)

/* ----- Operating System Specific Area */

/* WIN32: CPI API is a DLL */

#ifdef WIN32                        /* 32 bit Windows OS */

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


#define     TX_HANDLE               S16
#define     CPI_ERR_TYPE            S32
#define     CPI_WAIT_TYPE           HANDLE
#define     CPI_INVALID_WAIT_HANDLE INVALID_HANDLE_VALUE
#define     CPI_INVALID_HANDLE      -1

#endif  /* WIN32 */

#ifdef UNIX                         /* UNIX OS */

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

#ifndef TRUE
#define TRUE    1
#endif
#ifndef FALSE
#define FALSE   0
#endif

#ifndef far
#define     far
#endif

#define     putch                   putchar

#define     TXCPIFUNC
#define     TXXPORT
#define     TX_HANDLE               int
#define     CPI_ERR_TYPE            U32
#define     CPI_WAIT_TYPE           TX_HANDLE
#define     CPI_INVALID_WAIT_HANDLE (-1)
#define     CPI_INVALID_HANDLE      (-1)

#endif  /* UNIX */

/*
 * CP Type Identifiers
 */
#define CPI_ISA_BUS     1
#define CPI_PCI_BUS     2

/*
 * These are outdated for NT but still needed for the UNIX platform
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
#define CPI_ACK_READ        3

/* The CPI_XXXX error codes are ones that a user might see in normal use */

#define CPI_ERRCODE_BASE                7000

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
#define CPI_QUEUE_FULL                  (CPI_ERRCODE_BASE+20)
#define CPI_CHANNEL_STATE               (CPI_ERRCODE_BASE+21)
#define CPI_INVALID_ARGUMENT            (CPI_ERRCODE_BASE+22)
#define CPI_BOARD_STATE                 (CPI_ERRCODE_BASE+23)
#define CPI_INVALID_DATA                (CPI_ERRCODE_BASE+24)
#define CPI_INVALID_SIZE                (CPI_ERRCODE_BASE+25)
#define CPI_NOT_CONTIGUOS               (CPI_ERRCODE_BASE+26)
#define CPI_NO_CHANNEL                  (CPI_ERRCODE_BASE+27)
#define CPI_NO_BOARD                    (CPI_ERRCODE_BASE+28)
#define CPI_CORRUPT_MSG                 (CPI_ERRCODE_BASE+29)
#define CPI_TX_REJECTED                 (CPI_ERRCODE_BASE+30)
#define CPI_RESET                       (CPI_ERRCODE_BASE+31)
#define CPI_THREAD_FAIL                 (CPI_ERRCODE_BASE+32)
#define CPI_COMM_ERROR                  (CPI_ERRCODE_BASE+33)
#define CPI_COMM_UNKNOWN                (CPI_ERRCODE_BASE+34)
#define CPI_UNKNOWN_DRIVER_ERROR        (CPI_ERRCODE_BASE+35)
#define CPI_SEQNUM_MISMATCH             (CPI_ERRCODE_BASE+36)
#define CPI_DRIVER_OPEN                 (CPI_ERRCODE_BASE+37)
#define CPI_RX_FAIL                     (CPI_ERRCODE_BASE+38)

/* ----- CPI header */
typedef struct
{
    U16             src;        /* Source port */
    U16             dst;        /* Destination port */
    S16             length;     /* length of packet, including CPI header */
#ifdef NMSTX_ALIGN_32
    U8              pad_end[2]; /* pad to 32-bit aligned structure size */
#endif
}
CPIHDR;

/* ----- CPI packet */
typedef struct
{
    CPIHDR          hdr;
    U8              data[MAXCPIDATA];
}
CPIPKT;

/* ----- CPI structures and literals */

/* TX CP type identifiers */
#define     TX_1000     1000
#define     TX_2000     2000
#define     TX_3000     3000
#define     TX_3210     3210
#define     TX_3220     3220
#define     TX_4000     4000
#define     TX_5000     5000
#define     TX_H2H      0001    /* host-to-host interface */
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
    U16             state;
#define BS_BOOT         0       /* waiting to begin PREBOOT */
#define BS_READY        1       /* KERNEL completely loaded, init'd, and ready */
#define BS_INIT         2       /* KERNEL is initializing */
#define BS_DOWN         3       /* KERNEL not responding */
#define BS_BERR         4       /* Bus Error indicated by KERNEL */
#define BS_LOADING      5       /* Loading block of KERNEL */
#define BS_PREBOOTING   6       /* PREBOOT running (not ready for KERNEL yet) */
#define BS_WAIT_KERNEL  7       /* PREBOOT has completed and is waiting for KERNEL block */

    U8              reg[5];
}
CPIBS;

/* Driver statistics */
/* This structure is provided to support legacy applications that call cpi_get_stats.
 * All statistics are now maintained using the TX_STATS structure (see txstats.h).
 * See field comments below for new meaning of each legacy statistic: */
typedef struct
{
    U16             Channel;        /* channel number associated with CPI handle */
    U16             LowFreeCnt;     /* # of interrupt indications */
    U32             PktsSentCS;     /* # of packets sent successfully */
    U32             BytesSentCS;    /* # of sends currently in progress */
    U32             SendRejCS;      /* # of failed send attempts */
    U32             PktsRecvCS;     /* # of packets received successfully */
    U32             BytesRecvCS;    /* # of receives currently in progress */
    U32             RecvRejRegCS;   /* # of failed receives */
    U32             RecvRejBfrCS;   /* count of out-of-memory conditions */
    U32             RecvTruncCS;    /* # of anomalies detected */
}
CPIDRVSTATS;

/* TX Device Information */
typedef struct
{
    U16          cp_number;      /* CP number assigned to TX board (0 = undefined) */
    U16          board_type;     /* type of TX board (from TX CP type identifiers [above]) */
    U16          bus;            /* PCI bus that board resides in */
    U16          slot;           /* PCI slot that board resides in */
} CPI_DEV_INFO;

/* Macros to convert between port value and board/channel */
#ifdef NMSTX_HOST_BIGENDIAN
#define PORT(board,chan) ((chan << 8) + board)
#define BOARD(port)      (port & 0x00FF)
#define CHANNEL(port)    ((port >> 8) & 0x00FF)
#else
#define PORT(board,chan) ((board << 8) + chan)
#define BOARD(port)      ((port >> 8) & 0x00FF)
#define CHANNEL(port)    (port & 0x00FF)
#endif  /* NMSTX_HOST_BIGENDIAN */

/* Maximum number of CPI channels and CP Boards */
#define MAXCHAN             256
#define MAXBOARD            32

#define MAX_OPEN_CHANNELS   256
#define MAX_HANDLES         MAX_OPEN_CHANNELS


/* NMI comntrol state constants used with cpi_nmi() */

#define CPI_NMI_ASSERT          1   /* assert NMI */
#define CPI_NMI_DEASSERT        0   /* deassert NMI */

/* ----- CPI Function Prototypes */

#ifdef __cplusplus
extern          "C"
{
#endif

    TXXPORT S16 TXCPIFUNC cpi_init(S16 dummy, S8 **idstring);
    TXXPORT TX_HANDLE TXCPIFUNC cpi_open(U16 port, S16 mode,
                                         S16 (*receiver) (S16 handle, S16 len));
    TXXPORT TX_HANDLE TXCPIFUNC cpia_open(void *chkey, U16 board, U16 channel,
                                          void ((*rxnotify)(TX_HANDLE handle,
                                                            void *chkey)),
                                          void ((*txnotify)(TX_HANDLE handle,
                                                            void *chkey,
                                                            CPIPKT *buffer,
                                                            void *user_tx_key,
                                                            CPI_ERR_TYPE ccode)));
    TXXPORT void *TXCPIFUNC cpia_chkey(TX_HANDLE handle);
    TXXPORT S16 TXCPIFUNC cpi_close(TX_HANDLE handle);
    TXXPORT S16 TXCPIFUNC cpi_send(TX_HANDLE handle, CPIPKT *buffer);
    TXXPORT S16 TXCPIFUNC cpia_send(TX_HANDLE handle, CPIPKT *buffer,
                                    void *user_tx_key);
    TXXPORT S16 TXCPIFUNC cpi_get_data(TX_HANDLE handle, CPIPKT *buffer,
                                       S16 *len);
    TXXPORT S16 TXCPIFUNC cpia_get_data(TX_HANDLE handle, CPIPKT *buffer,
                                        S16 *len);
    TXXPORT CPI_ERR_TYPE TXCPIFUNC cpia_intr(TX_HANDLE handle);
    TXXPORT S16 TXCPIFUNC cpi_wait_msg(TX_HANDLE handle, CPIPKT *buffer,
                                       S16 *len, S32 millisecs);
    TXXPORT S16 TXCPIFUNC cpi_check_bs(TX_HANDLE handle, CPIBS *bsp);
    TXXPORT S16 TXCPIFUNC cpi_force_bs(TX_HANDLE handle);
    TXXPORT S16 TXCPIFUNC cpi_get_resources(S16 max_cps, S32 cps[]);
    TXXPORT S16 TXCPIFUNC cpi_stats(TX_HANDLE handle, U32 options,
                                    TX_STATS *stats);
    TXXPORT S16 TXCPIFUNC cpi_show_stats( TX_STATS_COMMON *stats );
    TXXPORT S16 TXCPIFUNC cpi_read_dpr(TX_HANDLE handle, S8 *buffer,
                                       U32 off, S16 len);
    TXXPORT S16 TXCPIFUNC cpi_write_dpr(TX_HANDLE handle, S8 *buffer,
                                        U32 off, S16 len);
    TXXPORT CPI_ERR_TYPE TXCPIFUNC cpi_get_last_error();
    TXXPORT S8 *TXCPIFUNC cpi_get_error_str(CPI_ERR_TYPE errnum);
#define cpi_cptoh_s(x) NMSTX_CPTOH_S(x)
#define cpi_cptoh_l(x) NMSTX_CPTOH_L(x)
#define cpi_htocp_s(x) NMSTX_HTOCP_S(x)
#define cpi_htocp_l(x) NMSTX_HTOCP_L(x)
    TXXPORT S16 TXCPIFUNC cpi_get_board(TX_HANDLE handle, U8 *board, U8 *chan);

    TXXPORT S16 TXCPIFUNC cpi_read_control(TX_HANDLE handle,
                                           U16 basereg,
                                           U16 numreg,
                                           U32 *regarray,
                                           U16 *actcnt);
    TXXPORT S16 TXCPIFUNC cpi_write_control(TX_HANDLE handle,
                                            U16 basereg,
                                            U16 numreg,
                                            U32 *regarray,
                                            U16 *actcnt);
    S16 TXXPORT TXCPIFUNC cpi_nmi(TX_HANDLE handle, U32 state);
    S16 TXXPORT TXCPIFUNC cpi_set_cpid(S16 type, U32 param1,
                                       U32 param2, U32 cpId);
    TXXPORT CPI_ERR_TYPE TXCPIFUNC cpi_get_dev_info(CPI_DEV_INFO *devinfo, U16 *numdevs);

    TXXPORT CPI_WAIT_TYPE TXCPIFUNC cpi_wait_obj(TX_HANDLE handle);

    /* ----- manager communication functions ----- */
    TXXPORT S16    TXCPIFUNC cpi_mgr_msg( TX_HANDLE handle, CPIPKT *buffer, U8 command );
    TXXPORT void * TXCPIFUNC cpi_mgr_rx ( TX_HANDLE handle, CPIPKT *buffer, U8 command );

    /* ----- functions no longer supported by CPI library ----- */
    /* NOTE: Prototypes are left here to avoid compile/link issues.
     *       Each of the following functions fails with CPI_UNSUPPORTED_OPER
     *       if the function is called.
     *       These dummy prototypes will be removed in a future release.
     */
    TXXPORT S16 TXCPIFUNC cpi_get_eeprom(TX_HANDLE handle, S8 *buffer);
    TXXPORT S16 TXCPIFUNC cpi_get_stats(TX_HANDLE handle, S16 chan,
                                        CPIDRVSTATS *stats);
    TXXPORT S16 TXCPIFUNC cpi_clear_stats(TX_HANDLE handle, S16 chan);
    TXXPORT S16 TXCPIFUNC cpi_pre_boot(TX_HANDLE handle, S8 *buffer,
                                       S16 len, U16 off,
                                       S16 xqt);
    TXXPORT S16 TXCPIFUNC cpi_load_krnl(TX_HANDLE handle, S8 *buffer,
                                        S16 len, S16 *seqnum, U32 destaddr);
    TXXPORT S16 TXCPIFUNC cpi_exec_krnl(TX_HANDLE handle,
                                        U32 startaddr, U8 uCode);
    TXXPORT S16 TXCPIFUNC cpi_set_led(TX_HANDLE handle, U8 andmask, U8 ormask);

#ifdef  UNIX
#ifndef _REENTRANT
#define _REENTRANT
#endif
#include <errno.h>              /* get reentrant definition of errno */
#include <time.h>
#include <pthread.h>
    CPI_ERR_TYPE    __cpi_geterr(void);
#define cpi_errno       __cpi_geterr()
#define CPI_SETERR(x)   __cpi_seterr(x)
#else                           /* UNIX */
#define CPI_SETERR(x)   (cpi_errno = x)
#endif                          /* UNIX */

#ifdef __cplusplus
}
#endif

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

#endif  /* _TXCPI_H */
