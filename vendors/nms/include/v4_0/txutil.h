/*****************************************************************************
 *
 * txutil.h
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

#ifndef _TXUTIL_H
#define _TXUTIL_H

#include <txnuser.h>            /* primitive field type definitions */

/* define TX_LONG_FILL as DWORD declaration for OS versions that use 'long' as 32-bit value */
#if defined(_Solaris64_)
#define TX_LONG_FILL(name)
#define TX_LONG_ZERO(structname,name)
#else
#define TX_LONG_FILL(name) U32   name;
#define TX_LONG_ZERO(structname,name) structname->name = 0;
#endif /* _Solaris64_ */

/* Layout of DPR header (see dpruser.h) */

typedef DPRH    dprheader_t;

#ifndef MIN
#define MIN(a,b) (((a)>(b))?(b):(a))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#define TX2_MTU		1514            /* the MTU for the board is 1514 */

/* Board statistics */

struct tx2hwstat
{
    U32         intr;
    U32         tx;
    U32         rx;
    U32         run;
    U32         msg;
    U32         msgack;
    U32         rxack;
    U32         load;
    U32         ready;
    U32         strayintr;
    U32         outstate;
    U32         outmem;
    U32         nochan;
    U32         anomaly;
    U32         ackunexpected;
    U32         ackunexpectedload;
    U32         userappabovehiwat;  /* unused in tx2 driver */
    U32         userappbelowlowat;  /* unused in tx2 driver */
    U32         rhiwatdropped;      /* unused in tx2 driver */
    U32         getsendbuff_nobufs; /* unused in tx2 driver */
    U32         writethrottle;      /* unused in tx2 driver */
    U32         nosendbufs;         /* unused in tx2 driver */
    U32         unacked;            /* unused in tx2 driver */
    U32         outplistcnt;        /* unused in tx2 driver */
    U32         outpliststat;       /* unused in tx2 driver */
    U32         outplistmask;       /* unused in tx2 driver */
    U32         inplistcnt;         /* unused in tx2 driver */
    U32         wqcount;            /* unused in tx2 driver */
    U32         rq_msgcnt;          /* unused in tx2 driver */
    U32         rq_msgmax;          /* unused in tx2 driver */
};

/* Channel statistics (per board) */

struct tx2cstat
{
    struct tx2chanstat *cs_next;    /* link to next block */
    U32         cs_chan;            /* which channel */
    U32         cs_txpkts;          /* packets sent */
    U32         cs_txbytes;         /* bytes sent */
    U32         cs_txdrop;          /* packets dropped on transmission */
    U32         cs_rxpkts;          /* packets received */
    U32         cs_rxbytes;         /* bytes received */
    U32         cs_rxdrop;          /* received packets dropped */
};

/* Driver Registers */

struct tx2regs
{
    U8          txint;
    U8          txmsg;
    U8          rxint;
    U8          rxmsg;
    U8          csr;                /* Control/Status Register */
    U8          nxtrcvack;          /* Next ACK expected */
    U8          nxtrcvseq;          /* Next Sequence Number expected */
    U8          lstsndseq;          /* Last Sequence Number Sent */
};

/* Driver Commands (Requests, Indications, and Acknowledgments) */

/*
 *	NOTE:	The idea for this stuff was
 *          stolen (shamelessly) from DLPI
 */

/* The primitives */

#define TX2_NOTYPE          0
#define TX2_OK_ACK          1
#define	TX2_ERROR_ACK		2
#define	TX2_ATTACH_REQ		3
#define	TX2_DETACH_REQ		4
#define	TX2_BIND_REQ		5
#define	TX2_UNBIND_REQ		6
#define	TX2_DATA_REQ		7
#define	TX2_DATA_IND		8
#define	TX2_BOARD_INFO_REQ	9
#define	TX2_BOARD_INFO_ACK	10
#define	TX2_DPR_READ_REQ	11
#define	TX2_DPR_READ_ACK	12
#define	TX2_DPR_WRITE_REQ	13

/* The templates */

/*
 * These templates are overlayed onto M_PROTO messages, any other
 * data involved in the protocol will/should be attached to the
 * M_PROTO message containing the template (via the b_cont field)
 * and should be contained in an M_DATA message.
 *
 * Note: all requests are made to be at least the size of an error ack
 * so that the message can be reused for either and ok_ack or error_ack.
 */

#define TX_DATA_BAND	0
#define TX_ACK_BAND     1               /* STREAMS priority band for ACKs and ERRACKs */
#define TX_READ_BAND	TX_ACK_BAND

/* The acknowledgment when all went well */
typedef struct tx2_ok_ack
{
    U32             tx2_primitive;
    U32             tx2_align1;         /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_tid;            /* thread ID [or pointer to thread key] */
    U32             tx2_correct_primitive;
    U32             tx2_align2;         /* 64-bit alignment */
    TX_LONG_FILL(seq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_seq;            /* sequence number [or pointer as sequencing key] */
    TX_LONG_FILL(unq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_unique;         /* unique ID (provided by PCI driver on ATTACH) */
}
tx2_ok_ack_t;

/* The acknowledgment when an error occured */
typedef struct tx2_error_ack
{
    U32             tx2_primitive;
    U32             tx2_align1;         /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_tid;            /* thread ID [or pointer to thread key] */
    U32             tx2_error_primitive;
    U32             tx2_error_type;
/* NOTE: The following error types are duplicated in txpciuti.h (as TXPCI_ACK_xxx).
 *       Any changes to these values must also be made in txpciuti.h */
#define TX2_ACK_OUTSTATE            1   /* channel in invalid state for request */
#define TX2_ACK_NOMEM               2   /* unable to allocate memory for request */
#define TX2_ACK_INVALID_ARGUMENT    3   /* invalid argument provided in request */
#define TX2_ACK_OUTHSTATE           4   /* device (TX board) in invalid state for request */
#define TX2_ACK_INVALID_DATA        5   /* an unsupported data type was requested */
#define TX2_ACK_INVALID_SIZE        6   /* invalid buffer size associated with request */
#define TX2_ACK_STREAM_PULLUP       7   /* unable to create contiguous memory block */
#define TX2_ACK_ALREADY_BOUND       8   /* another stream is already bound to the channel */
#define TX2_ACK_FULL                9   /* max outstanding requests already in progress */
#define TX2_ACK_NOCHAN              10  /* no channel associated with stream */
#define TX2_ACK_NODEV               11  /* no device (TX board) associated with stream */
#define TX2_ACK_TXCOMM_MSG          12  /* corrupted TX communication message detected */
#define TX2_ACK_NOT_COMPATIBLE      13  /* current mode is not compatible with request type */
#define TX2_ACK_TXCP_ERROR          14  /* error reported from TX board */
#define TX2_ACK_TXRESET             15  /* request failed due to reset of TX board */

    TX_LONG_FILL(seq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_seq;            /* sequence number [or pointer as sequencing key] */
    U32             pad[2];             /* padded to make it the size of an ok ack */
}
tx2_error_ack_t;

/* Map a board to this STREAM */
typedef struct tx2_attach_req
{
    U32             tx2_primitive;
    U32             tx2_align1;         /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_tid;            /* thread ID [or pointer to thread key] */
    U32             tx2_board;
    U32             pad[5];             /* padded to make it the size of an error ack */
}
tx2_attach_req_t;

#define ATTACHALL   0xffffffff          /* attach all boards to this Stream */

/* Unmap the board from this STREAM */
typedef struct tx2_detach_req
{
    U32             tx2_primitive;
    U32             tx2_align1;         /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_tid;            /* thread ID [or pointer to thread key] */
    U32             pad[6];             /* padded to make it the size of an error ack */
}
tx2_detach_req_t;

/* Bind a channel to this STREAM */
typedef struct tx2_bind_req
{
    U32             tx2_primitive;
    U32             tx2_align1;         /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_tid;            /* thread ID [or pointer to thread key] */
    U32             tx2_channel;
    U32             tx2_options;        /* channel control options */
#define TX2_BIND_DATA_IOCTL     (1<<0)  /* set = driver passes DATA payload via IOCTL */

    U32             pad[4];             /* padded to make it the size of an error ack */
}
tx2_bind_req_t;

/* Unbind a channel from this STREAM */
typedef struct tx2_unbind_req
{
    U32             tx2_primitive;
    U32             tx2_align1;         /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_tid;            /* thread ID [or pointer to thread key] */
    U32             pad[6];             /* padded to make it the size of an error ack */
}
tx2_unbind_req_t;

/* Used for sending data to the board (on the indicated channel) */

/* Data is in an M_DATA message following this M_PROTO message */
typedef struct tx2_data_req
{
    U32             tx2_primitive;
    U32             tx2_align1;         /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_tid;            /* thread ID [or pointer to thread key] */
    U32             tx2_length;         /* length doesn't include this header */
    U32             tx2_loadaddr;       /* for OS loading and Preboot */
    U32             tx2_type;
    U32             tx2_align2;         /* 64-bit alignment */
    TX_LONG_FILL(seq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_seq;            /* sequence number [or pointer as sequencing key] */
}
tx2_data_req_t;

#define TX2_PREBOOT_DATA            0
#define TX2_OS_DATA                 1
#define TX2_NORMAL_DATA             2
#define	TX2_NORMAL_DATA_NOACKS		3
#define	TX2_PREBOOT_DATA_NOSTART	4

/* Data that was received from the board (on a particular channel) */

/* Data is in an M_DATA message following this M_PROTO message */
typedef struct tx2_data_ind
{
    U32             tx2_primitive;
    U32             tx2_align1;         /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_tid;            /* thread ID [or pointer to thread key] */
    U32             tx2_length;         /* length doesn't include this header */
    U32             tx2_srcchannel;
    U32             pad;
}
tx2_data_ind_t;

/* Tweek the board (set the CSR or request the CSR status) */
typedef struct tx2_board_info_req
{
    U32             tx2_primitive;
    U32             tx2_align1;         /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_tid;            /* thread ID [or pointer to thread key] */
    U32             tx2_command;        /* See list that follows */
    U32             tx2_image;          /* last 8-bits used only for TX2_WRITECSRDIRECT */
    U32             pad[2];             /* make it the size of an info_ack */
}
tx2_board_info_req_t;

/* Commands for tx2_board_info_req.tx2_command */

#define	TX2_READSTATUS		0
#define	TX2_WRITECSRDIRECT	1
#define TX2_RUNOS           2

/* CSR image bits (for tx2_image field in both req and ack) */

#define TX2_CSR_IRQ7		0x10
#define TX2_CSR_BERR		0x08
#define TX2_CSR_HALT		0x04
#define TX2_CSR_RESET		0x02

/*
 * If the command is TX2_RUNOS then there will be a start
 * request structure following the tx2_board_info_req.
 * NOTE: this is NOT a primitive! It is a template for
 * data (b_cont) following the tx2_board_info_req primitive.
 */

typedef struct tx2_start_req
{
    U16             year;
    U8              month;
    U8              day;
    U8              hour;
    U8              min;
    U8              sec;
    U8              zone;
    U16             msec;
    U8              microcode;
    U32             entrypoint;
}
tx2_start_req_t;

/* Response to a tx2_board_info_req */
typedef struct tx2_board_info_ack
{
    U32             tx2_primitive;
    U32             tx2_align1;         /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_tid;            /* thread ID [or pointer to thread key] */
    U32             tx2_unit;
    U32             tx2_image;          /* hardware status (CSR Image) */
    U32             tx2_sstate;         /* driver software state */
    U32             tx2_hstate;         /* driver hardware state */
    U32             pad[2];             /* make it the size of an info_ack */
}
tx2_board_info_ack_t;

/* Both of the following are used for reading the DPR */
typedef struct tx2_dpr_read_req
{
    U32             tx2_primitive;
    U32             tx2_align1;         /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_tid;            /* thread ID [or pointer to thread key] */
    U32             tx2_length;         /* length, in bytes, to read */
    U32             tx2_offset;         /* starting address from which to read */
    TX_LONG_FILL(seq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_seq;            /* sequence number [or pointer as sequencing key] */
}
tx2_dpr_read_req_t;

/* The data read is in an M_DATA message following this M_PCPROTO message */
typedef struct tx2_dpr_read_ack
{
    U32             tx2_primitive;
    U32             tx2_align1;         /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_tid;            /* thread ID [or pointer to thread key] */
    U32             tx2_length;         /* length read */
    U32             tx2_offset;         /* starting offset which was read  */
    TX_LONG_FILL(seq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_seq;            /* sequence number [or pointer as sequencing key] */
}
tx2_dpr_read_ack_t;

/* The following is used for writing the DPR */

/* The data should be contained in an M_DATA message */

/* following this M_PCPROTO message. */

/* This message will be acked (nacked) via a tx2_ok_ack (tx2_error_ack) */
typedef struct tx2_dpr_write_req
{
    U32             tx2_primitive;
    U32             tx2_align1;         /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_tid;            /* thread ID [or pointer to thread key] */
    U32             tx2_length;         /* length, in bytes, to be written */
    U32             tx2_offset;         /* starting offset to which to write */
    TX_LONG_FILL(seq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_seq;            /* sequence number [or pointer as sequencing key] */
}
tx2_dpr_write_req_t;

/* The (cast-o-matic) primitive common section */

typedef struct
{
    U32             tx2_primitive;
    U32             tx2_align1;         /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   tx2_tid;            /* thread ID [or pointer to thread key] */
}
tx2_generic_prim_t;

/* The (cast-o-matic) primitive union */

union tx2_primitives
{
    U32                     tx2_primitive;
    tx2_ok_ack_t            ok_ack;
    tx2_error_ack_t         error_ack;
    tx2_attach_req_t        attach_req;
    tx2_detach_req_t        detach_req;
    tx2_bind_req_t          bind_req;
    tx2_unbind_req_t        unbind_req;
    tx2_data_req_t          data_req;
    tx2_data_ind_t          data_ind;
    tx2_board_info_req_t    board_info_req;
    tx2_board_info_ack_t    board_info_ack;
    tx2_dpr_read_req_t      dpr_read_req;
    tx2_dpr_read_ack_t      dpr_read_ack;
    tx2_dpr_write_req_t     dpr_write_req;
};

/* The various sizes */

#define TX2_OK_ACK_SIZE         sizeof(tx2_ok_ack_t)
#define TX2_ERROR_ACK_SIZE      sizeof(tx2_error_ack_t)
#define TX2_ATTACH_REQ_SIZE     sizeof(tx2_attach_req_t)
#define TX2_DETACH_REQ_SIZE     sizeof(tx2_detach_req_t)
#define TX2_BIND_REQ_SIZE       sizeof(tx2_bind_req_t)
#define TX2_UNBIND_REQ_SIZE     sizeof(tx2_unbind_req_t)
#define TX2_DATA_REQ_SIZE       sizeof(tx2_data_req_t)
#define TX2_DATA_IND_SIZE       sizeof(tx2_data_ind_t)
#define TX2_BOARD_INFO_REQ_SIZE	sizeof(tx2_board_info_req_t)
#define TX2_BOARD_INFO_ACK_SIZE	sizeof(tx2_board_info_ack_t)
#define TX2_DPR_READ_REQ_SIZE	sizeof(tx2_dpr_read_req_t)
#define TX2_DPR_READ_ACK_SIZE	sizeof(tx2_dpr_read_ack_t)
#define TX2_DPR_WRITE_REQ_SIZE	sizeof(tx2_dpr_write_req_t)

#define TX2_MAX_PRIM_SIZE       sizeof(union tx2_primitives)
#define TX2_MAX_DATA_SIZE	TX2_MEM /* 8K from tx2.h, see the snap routine's calls to cpi_dpr_read */

/* Ioctls */

#define	TX2_IOC(x)			(('T' << 8) | (x))
#define	TX2_IOC_CLEARSTATE		TX2_IOC(1)
#define	TX2_IOC_CLEARSTAT		TX2_IOC(2)
#define	TX2_IOC_GETSTAT			TX2_IOC(3)
#define	TX2_IOC_GETNUMBEROFBOARDS	TX2_IOC(4)
#define	TX2_IOC_DUMPRECORDS		TX2_IOC(5)
#define	TX2_IOC_TRACE			TX2_IOC(6)
#define	TX2_IOC_GETBOUNDCHANNEL		TX2_IOC(7)
#define	TX2_IOC_GETVERSION		TX2_IOC(8)
#define	TX2_IOC_GETGSTAT		TX2_IOC(9)
#define	TX2_IOC_ACKS			TX2_IOC(10)
#define	TX2_IOC_NOACKS			TX2_IOC(11)
#define	TX2_IOC_GETATTACHEDBOARD	TX2_IOC(12)
#define	TX2_IOC_GETEEPROM		TX2_IOC(13)
#define	TX2_IOC_STOREEEPROM		TX2_IOC(14)
#define	TX2_IOC_GETREGS			TX2_IOC(15)
#define	TX2_IOC_GETHWTYPE		TX2_IOC(16)

/* global statistic structure */

struct gstat
{
    U32             intr;
    U32             rsrv;
    U32             wsrv;
    U32             wput;
    U32             rqueue;
    U32             wqueue;
    U32             wputbq;
    U32             rputbq;
    U32             protofail;
    U32             protosuccess;
    U32             strayintr;
    U32             intrcalled;
    U32             timeout;
    U32             config;
    U32             retry;
};

/* TX2000 EEPROM layout and constants */

/* The National Semiconductor NM93C06 EEPROM has 16 register of 16 bits each */

#define TX1000_AT_20	1

#define ETH_10BASE2	01
#define ETH_10BASE5	02
#define ETH_10BASET	03

#define NONE		00
#define V24         01
#define V35         02
#define V24X		03

#pragma pack(1)
typedef struct
{
    U16             signrev;            /*  1: Signature */
    U16             ethaddr0;           /*  2: Ethernet address - most-sign word */
    U16             ethaddr1;           /*  3:  */
    U16             ethaddr2;           /*  4: Ethernet address - least-sign word */
    U8              sn12;               /*     Serial Number digits 1 & 2 */
    U8              board_info;         /*  5: Board Info : high nyb = type  low nyb = Rev */
    U8              sn56;               /*     Serial Number digits 5 & 6 */
    U8              sn34;               /*  6: Serial Number digits 3 & 4 */
    U8              sn90;               /*     Serial Number digits 9 & 10 */
    U8              sn78;               /*  7: Serial Number digits 7 & 8 */
    U8              bus_adapter;        /*     Bus    Adapters Installed */
    U8              serial_adapter;     /*  8: Serial Adapters Installed */
    /* Currently unused area */
    U16             avail1;             /*  9:  */
    U16             avail2;             /* 10:  */
    U16             avail3;             /* 11:  */
    U16             avail4;             /* 12:  */
    U16             avail5;             /* 13:  */
    U16             avail6;             /* 14:  */
    U16             avail7;             /* 15:  */
    U16             checksum;           /* 16:  */
}
TX2EE;

#pragma pack()

#define EE_WORDS_USED   8               /* # of words used */
#define EE_WORDS_TOTAL  16              /* # of total words */

#ifndef _INKERNEL

/* the following is necessary only at user level */

#define	BOARDDEV		"/dev/tx2000"
#define	PCIBOARDDEV		"/dev/txpci"

#define BOOTCHAN            0
#define TASKCHAN            7
#define DEFAULTCONCHAN		6
#define DEFAULTBOARD		1

#define TX2_OK              0           /* Must be 0! */
#define	TX2_GENERROR		1
#define TX2_MEMERROR		2
#define TX2_ERRORACK		3
#define TX2_UNKNOWN         4
#define TX2_GETMSGFAIL		5
#define TX2_BADARG          6
#define TX2_BADKERNEL		7
#define TX2_DONE            8
#define TX2_BADTASK         9
#define	TX2_CREATEFAIL		10
#define	TX2_ALLOCFAIL		11
#define	TX2_SENDFAIL		12
#define	TX2_RECEIVEFAIL		13
#define	TX2_TASKEXISTS		14
#define	TX2_READREGFAIL		15
#define TX2_BADADDR         16
#define	TX2_WRITEMEMFAIL	17
#define	TX2_WRITEREGFAIL	18
#define	TX2_TASKSTARTFAIL	19
#define TX2_ERRNO           20

#define MAXINPUT		128

/* CPI Compatability */

#define CPIM_CHAN	1
#define CPIM_PORT	2
#define	CPIFORMAT	"CPIDRVR TX2000 V%d"
#define CPSTRSIZE	20

#endif  /* _INKERNEL */

#endif  /* _TXUTIL_H */
