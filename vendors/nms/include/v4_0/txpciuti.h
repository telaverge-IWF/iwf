/*****************************************************************************
 *
 * txpciuti.h - interface between CPI library and TX PCI driver
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

#ifndef _TXPCIUTIL_H
#define _TXPCIUTIL_H

#include <txnuser.h>            /* primitive field type definitions */
#include <txstats.h>            /* TX statistics */
#include <dpruser.h>

/* define TX_LONG_FILL as DWORD declaration for OS versions that use 'long' as 32-bit value */
#if defined(_Solaris64_)
#define TX_LONG_FILL(name)
#define TX_LONG_ZERO(structname,name)
#else
#define TX_LONG_FILL(name) U32   name;
#define TX_LONG_ZERO(structname,name) structname->name = 0;
#endif /* _Solaris64_ */

#ifdef LINUX
#define LIMIT_TOAPP_MESSAGES    /* use interface that limits number of messages from driver to app */
#endif /* LINUX */

/* Layout of DPR header (see dpruser.h) */

#define TXPCI_MTU		1514        /* the MTU for the board is 1514 */

/* PCI-driver's layer-specific statistics */
#define TXPCI_S_INTRRESET       0   /* received interrupt when resetting */
#define TXPCI_S_MAXRXINPROG     1   /* max number of receives in progress (awaiting DATAACK) */
#define TXPCI_S_MAXTXINPROG     2   /* max number of transmits in progress (awaiting ACK) */
#define TXPCI_S_STOPSHADOW      3   /* received stopped request 'shadow' */
#define TXPCI_S_MAX             3   /* maximum PCI-driver layer-specific stat */

/* Driver Registers */

struct txpciregs
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

/* Driver Tracing */

#define TXPCI_TCOUNT    64          /* number of records in trace block */
#define TXPCI_TMASK     0x003F      /* mask to apply (to next) to get index */

/* trace record */
typedef struct __txpci_trecord
{
  U8            cpnum;              /* CP number of device logging entry */
  U8            func;               /* function / unique code location logging entry */
                                    /* 0 = record never written */
/* --- FUNCTIONS --- */
#define TXPCI_T_INIT_TXINPROG       0x01    /* txpci_init_txinprog */
#define TXPCI_T_ASSIGN_TXINPROG     0x02    /* txpci_assign_txinprog */
#define TXPCI_T_LOCATE_TXINPROG     0x03    /* txpci_locate_txinprog */
#define TXPCI_T_RETURN_TXINPROG     0x04    /* txpci_return_txinprog */
#define TXPCI_T_FAIL_TXINPROG       0x05    /* txpci_fail_txinprog */
#define TXPCI_T_PURGE_TXINPROG      0x06    /* txpci_purge_txinprog */
#define TXPCI_T_SENDMSG             0x07    /* txpci_SendMsg */
#define TXPCI_T_ACKSEND             0x08    /* txpci_AckSend */
#define TXPCI_T_GETRECVBUF          0x09    /* txpci_GetRecvBuf */
#define TXPCI_T_FREEINBUF           0x0A    /* txpci_FreeInBuf */
#define TXPCI_T_GETSENDBUF          0x0B    /* txpci_GetSendBuf */

#define TXPCI_T_RETURN_RXWAITAPP    0x0C    /* txpci_return_rxwaitapp */

/* --- ERROR DETECTION --- */
#define TXPCI_T_ERR_RX_ACK          0x80    /* index from ACK message doesn't match any in use */

  U16           parm1;
  U32           parm2;
} TXPCI_TRECORD;

/* full trace block */
typedef struct __txpci_trace
{
    U16         next;               /* index into trace entries where next record will be stored */
    U8          type;               /* type of tracing information provided */
#define TXPCI_T_TXINPROG  1         /* tracing usage of txinprog */

    U8          flags;              /* trace control flags */
#define TXPCI_T_ENABLED   (1<<0)    /* set when tracing is currently enabled */
#define TXPCI_T_OFFEVENT  (1<<1)    /* set when tracing turned off due to event detected by driver */

    TXPCI_TRECORD   entry[TXPCI_TCOUNT];  /* trace record entries */
} TXPCI_TRACE;

/* Driver Commands (Requests, Indications, and Acknowledgments) */

/*
 *	NOTE:	The idea for this stuff was
 *		stolen (shamelessly) from DLPI
 */

/* The primitives */

#define TXPCI_NOTYPE              TX2_NOTYPE
#define TXPCI_OK_ACK              TX2_OK_ACK
#define TXPCI_ERROR_ACK           TX2_ERROR_ACK
#define TXPCI_ATTACH_REQ          TX2_ATTACH_REQ
#define TXPCI_DETACH_REQ          TX2_DETACH_REQ
#define TXPCI_BIND_REQ            TX2_BIND_REQ
#define TXPCI_UNBIND_REQ          TX2_UNBIND_REQ
#define TXPCI_DATA_REQ            TX2_DATA_REQ
#define TXPCI_DATA_IND            TX2_DATA_IND
#define TXPCI_BOARD_INFO_REQ      TX2_BOARD_INFO_REQ
#define TXPCI_BOARD_INFO_ACK      TX2_BOARD_INFO_ACK
#define TXPCI_DPR_READ_REQ        TX2_DPR_READ_REQ
#define TXPCI_DPR_READ_ACK        TX2_DPR_READ_ACK
#define TXPCI_DPR_WRITE_REQ       TX2_DPR_WRITE_REQ
#define TXPCI_DATAACK_REQ         (TX2_DPR_WRITE_REQ+1)
#define TXPCI_RXCHANNEL_REQ       (TX2_DPR_WRITE_REQ+2)

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

/* The acknowledgment when all went well */
typedef struct txpci_ok_ack
{
    U32             txpci_primitive;
    U32             txpci_align1;       /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_tid;          /* thread ID [or pointer to thread key] */
    U32             txpci_correct_primitive;
    U32             txpci_align2;       /* 64-bit alignment */
    TX_LONG_FILL(seq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_seq;          /* sequence number [or pointer as sequencing key] */
    TX_LONG_FILL(unq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_unique;       /* unique ID (provided by PCI driver on ATTACH) */
}
txpci_ok_ack_t;

/* The acknowledgment when an error occured */
typedef struct txpci_error_ack
{
    U32             txpci_primitive;
    U32             txpci_align1;       /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_tid;          /* thread ID [or pointer to thread key] */
    U32             txpci_error_primitive;
    U32             txpci_error_type;
/* NOTE: The following error types are duplicated in txutil.h (as TX2_ACK_xxx).
 *       Any changes to these values must also be made in txutil.h */
#define TXPCI_ACK_OUTSTATE          1   /* channel in invalid state for request */
#define TXPCI_ACK_NOMEM             2   /* unable to allocate memory for request */
#define TXPCI_ACK_INVALID_ARGUMENT  3   /* invalid argument provided in request */
#define TXPCI_ACK_OUTHSTATE         4   /* device (TX board) in invalid state for request */
#define TXPCI_ACK_INVALID_DATA      5   /* an unsupported data type was requested */
#define TXPCI_ACK_INVALID_SIZE      6   /* invalid buffer size associated with request */
#define TXPCI_ACK_STREAM_PULLUP     7   /* unable to create contiguous memory block */
#define TXPCI_ACK_ALREADY_BOUND     8   /* another stream is already bound to the channel */
#define TXPCI_ACK_FULL              9   /* max outstanding requests already in progress */
#define TXPCI_ACK_NOCHAN            10  /* no channel associated with stream */
#define TXPCI_ACK_NODEV             11  /* no device (TX board) associated with stream */
#define TXPCI_ACK_TXCOMM_MSG        12  /* corrupted TX communication message detected */
#define TXPCI_ACK_NOT_COMPATIBLE    13  /* current mode is not compatible with request type */
#define TXPCI_ACK_TXCP_ERROR        14  /* error reported from TX board */
#define TXPCI_ACK_TXRESET           15  /* request failed due to reset of TX board */

    TX_LONG_FILL(seq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_seq;          /* sequence number [or pointer as sequencing key] */
    U32             pad[2];             /* padded to make it the size of an ok ack */
}
txpci_error_ack_t;

/* Map a board to this STREAM */
typedef struct txpci_attach_req
{
    U32             txpci_primitive;
    U32             txpci_align1;       /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_tid;          /* thread ID [or pointer to thread key] */
    U32             txpci_board;
    U32             txpci_comm_chan;    /* set to channel when attaching using shared memory comm. window */
#define TXPCI_ATTACH_COMM_CHAN  (1<<15) /* bit or'd with channel to show attaching to comm. window */

    U32             pad[4];             /* padded to make it the size of an error ack */
}
txpci_attach_req_t;

/* Unmap the board from this STREAM */
typedef struct txpci_detach_req
{
    U32             txpci_primitive;
    U32             txpci_align1;       /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_tid;          /* thread ID [or pointer to thread key] */
    U32             pad[6];             /* padded to make it the size of an error ack */
}
txpci_detach_req_t;

/* Bind a channel to this STREAM */
typedef struct txpci_bind_req
{
    U32             txpci_primitive;
    U32             txpci_align1;       /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_tid;          /* thread ID [or pointer to thread key] */
    U32             txpci_channel;
    U32             txpci_options;      /* channel control options [NOT CURRENTLY USED] */
    U32             pad[4];             /* padded to make it the size of an error ack */
}
txpci_bind_req_t;

/* Unbind a channel from this STREAM */
typedef struct txpci_unbind_req
{
    U32             txpci_primitive;
    U32             txpci_align1;       /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_tid;          /* thread ID [or pointer to thread key] */
    U32             pad[6];             /* padded to make it the size of an error ack */
}
txpci_unbind_req_t;

/* Used for sending data to the board (on the indicated channel) */

/* Data is in an M_DATA message following this M_PROTO message */
typedef struct txpci_data_req
{
    U32             txpci_primitive;
    U32             txpci_align1;       /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_tid;          /* thread ID [or pointer to thread key] */
    U32             txpci_length;       /* length doesn't include this header */
    U32             txpci_loadaddr;     /* for OS loading and Preboot */
    U32             txpci_type;
    U32             txpci_align2;       /* 64-bit alignment */
    TX_LONG_FILL(seq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long txpci_seq;            /* sequence number [or pointer as sequencing key] */
}
txpci_data_req_t;

/* No message follows this M_PROTO message */
typedef struct txpci_dataack_req
{
    U32             txpci_primitive;
    U32             txpci_rcvkey;       /* RX key provided in previous DATA IND */
}
txpci_dataack_req_t;

/* No message follows this M_PROTO message */
typedef struct txpci_rxchannel_req
{
    U32             txpci_primitive;
    U32             txpci_align1;       /* 64-bit alignment */
    TX_LONG_FILL(ach_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_attach_id;    /* unique ID of stream being attached to */
}
txpci_rxchannel_req_t;

#define TXPCI_PREBOOT_DATA          0
#define TXPCI_OS_DATA               1
#define	TXPCI_NORMAL_DATA			2
#define TXPCI_NORMAL_DATA_NOACKS    3
#define	TXPCI_PREBOOT_DATA_NOSTART	4

/* Data that was received from the board (on a particular channel) */

/* Data is in an M_DATA message following this M_PROTO message */
typedef struct txpci_data_ind
{
    U32             txpci_primitive;
    U32             txpci_align1;       /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_tid;          /* thread ID [or pointer to thread key] */
    U32             txpci_length;       /* length doesn't include this header */
    U32             txpci_srcchannel;
    U32             txpci_rcvkey;       /* receive-specific key to be passed back on app read */
}
txpci_data_ind_t;

/* Tweek the board (set the CSR or request the CSR status) */
typedef struct txpci_board_info_req
{
    U32             txpci_primitive;
    U32             txpci_align1;       /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_tid;          /* thread ID [or pointer to thread key] */
    U32             txpci_command;      /* See list that follows */
    U32             txpci_image;        /* last 8-bits used only for TXPCI_WRITECSRDIRECT */
    U32             pad[2];             /* make it the size of an info_ack */
}
txpci_board_info_req_t;

/* Commands for txpci_board_info_req.txpci_command */

#define	TXPCI_READSTATUS		0
#define	TXPCI_WRITECSRDIRECT	1
#define TXPCI_RUNOS             2

/* CSR image bits (for txpci_image field in both req and ack) */

#define TXPCI_CSR_IRQ7		0x10
#define TXPCI_CSR_BERR		0x08
#define TXPCI_CSR_HALT		0x04
#define TXPCI_CSR_RESET		0x02

/*
 * If the command is TXPCI_RUNOS then there will be a start
 * request structure following the txpci_board_info_req.
 * NOTE: this is NOT a primitive! It is a template for
 * data (b_cont) following the txpci_board_info_req primitive.
 */

typedef struct txpci_start_req
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
txpci_start_req_t;

/* Response to a txpci_board_info_req */
typedef struct txpci_board_info_ack
{
    U32             txpci_primitive;
    U32             txpci_align1;       /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_tid;          /* thread ID [or pointer to thread key] */
    U32             txpci_unit;
    U32             txpci_image;        /* hardware status (CSR Image) */
    U32             txpci_sstate;       /* driver software state */
    U32             txpci_hstate;       /* driver hardware state */
    U32             pad[2];             /* make it the size of an info_ack */
}
txpci_board_info_ack_t;

/* Both of the following are used for reading the DPR */
typedef struct txpci_dpr_read_req
{
    U32             txpci_primitive;
    U32             txpci_align1;       /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_tid;          /* thread ID [or pointer to thread key] */
    U32             txpci_length;       /* length, in bytes, to read */
    U32             txpci_offset;       /* starting address from which to read */
    TX_LONG_FILL(seq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_seq;          /* sequence number [or pointer as sequencing key] */
}
txpci_dpr_read_req_t;

/* The data read is in an M_DATA message following this M_PCPROTO message */
typedef struct txpci_dpr_read_ack
{
    U32             txpci_primitive;
    U32             txpci_align1;       /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_tid;          /* thread ID [or pointer to thread key] */
    U32             txpci_length;       /* length read */
    U32             txpci_offset;       /* starting offset which was read  */
    TX_LONG_FILL(seq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_seq;          /* sequence number [or pointer as sequencing key] */
}
txpci_dpr_read_ack_t;

/* The following is used for writing the DPR */

/* The data should be contained in an M_DATA message */

/* following this M_PCPROTO message. */

/* This message will be acked (nacked) via a txpci_ok_ack (txpci_error_ack) */
typedef struct txpci_dpr_write_req
{
    U32             txpci_primitive;
    U32             txpci_align1;       /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_tid;          /* thread ID [or pointer to thread key] */
    U32             txpci_length;       /* length, in bytes, to be written */
    U32             txpci_offset;       /* starting offset to which to write */
    TX_LONG_FILL(seq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_seq;          /* sequence number [or pointer as sequencing key] */
}
txpci_dpr_write_req_t;

/* The (cast-o-matic) primitive union */

typedef struct
{
    U32             txpci_primitive;
    U32             txpci_align1;       /* 64-bit alignment */
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   txpci_tid;          /* thread ID [or pointer to thread key] */
}
txpci_generic_prim_t;

union txpci_primitives
{
    U32                     txpci_primitive;
    txpci_ok_ack_t          ok_ack;
    txpci_error_ack_t       error_ack;
    txpci_attach_req_t      attach_req;
    txpci_detach_req_t      detach_req;
    txpci_bind_req_t        bind_req;
    txpci_unbind_req_t      unbind_req;
    txpci_data_req_t        data_req;
    txpci_data_ind_t        data_ind;
    txpci_dataack_req_t     dataack_req;
    txpci_rxchannel_req_t   rxchannel_req;
    txpci_board_info_req_t  board_info_req;
    txpci_board_info_ack_t  board_info_ack;
    txpci_dpr_read_req_t    dpr_read_req;
    txpci_dpr_read_ack_t    dpr_read_ack;
    txpci_dpr_write_req_t   dpr_write_req;
};

/* The various sizes */

#define TXPCI_OK_ACK_SIZE           sizeof(txpci_ok_ack_t)
#define TXPCI_ERROR_ACK_SIZE        sizeof(txpci_error_ack_t)
#define TXPCI_ATTACH_REQ_SIZE       sizeof(txpci_attach_req_t)
#define TXPCI_DETACH_REQ_SIZE       sizeof(txpci_detach_req_t)
#define TXPCI_BIND_REQ_SIZE         sizeof(txpci_bind_req_t)
#define TXPCI_UNBIND_REQ_SIZE       sizeof(txpci_unbind_req_t)
#define TXPCI_DATA_REQ_SIZE         sizeof(txpci_data_req_t)
#define TXPCI_DATA_IND_SIZE         sizeof(txpci_data_ind_t)
#define TXPCI_DATAACK_REQ_SIZE      sizeof(txpci_dataack_req_t)
#define TXPCI_RXCHANNEL_REQ_SIZE    sizeof(txpci_rxchannel_req_t)
#define TXPCI_BOARD_INFO_REQ_SIZE	sizeof(txpci_board_info_req_t)
#define TXPCI_BOARD_INFO_ACK_SIZE	sizeof(txpci_board_info_ack_t)
#define TXPCI_DPR_READ_REQ_SIZE     sizeof(txpci_dpr_read_req_t)
#define TXPCI_DPR_READ_ACK_SIZE     sizeof(txpci_dpr_read_ack_t)
#define TXPCI_DPR_WRITE_REQ_SIZE	sizeof(txpci_dpr_write_req_t)

/* Ioctls */

/* This first set should match (binarily) those for the TX2 boards */

#define	TXPCI_IOC_CLEARSTATE		TX2_IOC_CLEARSTATE
#define	TXPCI_IOC_GETNUMBEROFBOARDS	TX2_IOC_GETNUMBEROFBOARDS
#define	TXPCI_IOC_DUMPRECORDS		TX2_IOC_DUMPRECORDS
#define TXPCI_IOC_TRACE             TX2_IOC_TRACE
#define	TXPCI_IOC_GETBOUNDCHANNEL	TX2_IOC_GETBOUNDCHANNEL
#define	TXPCI_IOC_GETVERSION		TX2_IOC_GETVERSION
#define TXPCI_IOC_ACKS              TX2_IOC_ACKS
#define TXPCI_IOC_NOACKS            TX2_IOC_NOACKS
#define	TXPCI_IOC_GETATTACHEDBOARD	TX2_IOC_GETATTACHEDBOARD
#define TXPCI_IOC_GETEEPROM         TX2_IOC_GETEEPROM
#define	TXPCI_IOC_STOREEEPROM		TX2_IOC_STOREEEPROM
#define TXPCI_IOC_GETREGS           TX2_IOC_GETREGS
#define TXPCI_IOC_GETHWTYPE         TX2_IOC_GETHWTYPE

/* New ioctls for PCI boards */

#define TXPCI_IOC_READCTL       TX2_IOC(18)
#define TXPCI_IOC_WRITECTL      TX2_IOC(19)
#define TXPCI_IOC_SETLED        TX2_IOC(20)
#define TXPCI_IOC_NMI           TX2_IOC(21)
#define TXPCI_IOC_GETCONFIG     TX2_IOC(22)

/* These are the ioctls needed for the hsflib support for Hot Swap */
#ifdef LINUX
/* The following definitions are copied from NA2004\software\api\hotswap\inc\hsioctl.h.
 * The TXHSF library is not used for Linux; instead, the standard NMS HSF is used.
 */
#define HOT_SWAP_FUNCTION_BASE       0x10000
#define CTL_CODE_HOT_SWAP(Function)  (HOT_SWAP_FUNCTION_BASE | (Function))
#define IOCTL_HOT_SWAP_START_DEVICE         CTL_CODE_HOT_SWAP(0)    /* not used */
#define IOCTL_HOT_SWAP_STOP_DEVICE          CTL_CODE_HOT_SWAP(1)
#define IOCTL_HOT_SWAP_ENABLE_OPENING       CTL_CODE_HOT_SWAP(2)    /* not used */
#define IOCTL_HOT_SWAP_DISABLE_OPENING      CTL_CODE_HOT_SWAP(3)    /* not used */
#define IOCTL_HOT_SWAP_SURPRISE_EXTRACTION  CTL_CODE_HOT_SWAP(4)    /* not used */
#define IOCTL_HOT_SWAP_QUERY_STATE          CTL_CODE_HOT_SWAP(5)
#define IOCTL_HOT_SWAP_QUERY_NAME           CTL_CODE_HOT_SWAP(6)    /* not used */
#define IOCTL_HOT_SWAP_QUERY_PCI_ADDRESS    CTL_CODE_HOT_SWAP(7)    /* not used */
#define IOCTL_HOT_SWAP_QUERY_ALL_INSTANCES  CTL_CODE_HOT_SWAP(8)    /* not used */
#define IOCTL_HOT_SWAP_REGISTER_FOR_EVENTS  CTL_CODE_HOT_SWAP(9)    /* not used */
#define IOCTL_HOT_SWAP_QUERY_IDENT          CTL_CODE_HOT_SWAP(10)

/* Values for Board HotSwap State */
#define TXLINUX_HS_PREPARED         0x100   /* Device instance is created, board is prepared */
#define TXLINUX_HS_USAGE_DISABLING  0x200   /* DISABLE_CHANNEL_CREATION ioctl was called. Disabling in progress */
#define TXLINUX_HS_USAGE_DISABLED   0x400   /* All channels are closed. This bit is valid only when HS_USAGE_DISABLING is set */
#endif /* LINUX */

#define TXPCI_IOC_STARTDEV		TX2_IOC(23)
#define TXPCI_IOC_STOPDEV		TX2_IOC(24)
#define TXPCI_IOC_ENABLECH		TX2_IOC(25)
#define TXPCI_IOC_DISABLECH		TX2_IOC(26)
#define TXPCI_IOC_QDSTATE		TX2_IOC(27)
#define TXPCI_IOC_PCI2LOGIC		TX2_IOC(28)
#define TXPCI_IOC_LOGIC2PCI		TX2_IOC(29)
#define TXPCI_IOC_BOARDBUSY		TX2_IOC(30)

/* Used to set configuration for board - right now only cpId */
#define TXPCI_IOC_SETCONFIG		TX2_IOC(31)

/* Used to force a system panic! - driver debugging tool */
#define TXPCI_IOC_FORCEPANIC    TX2_IOC(32)

/* Used to activate TX-board-based tracking - driver debugging tool */
#define TXPCI_IOC_TXTRACK       TX2_IOC(33)

#define TXPCI_IOC_GETDEVINFO    TX2_IOC(34)
#define TXPCI_IOC_STATS         TX2_IOC(35)

/* Used to trigger driver to process to_drv shared memory ring */
#define TXPCI_IOC_TODRV         TX2_IOC(36)

/* Used to tell driver that TX COMPLETE has been received */
#define TXPCI_IOC_TXACK         TX2_IOC(37)

/* for response from TXPCI_IOC_GETCONFIG & TXPCI_IOC_GETDEVINFO ioctl */
typedef struct
{
    U32             serialnum;          /* Not used for setting config */
    U32             hardwaretype;       /* Not used for setting config */
#define TXPCI_HWTYPE_3220   0x3220      /* hardware type for TX 3220[C] boards */
#define TXPCI_HWTYPE_4000   0x3430      /* hardware type for TX 4000[C] boards */

    U32             cpid;
    U32             bus;
    U32             slot;
}
configinfo_t;

#define TXPCI_MAX_BOARDS    32          /* maximum number of TX boards in a chassis */

/* for response from TXPCI_IOC_GETDEVINFO ioctl */
typedef struct
{
    configinfo_t    board[TXPCI_MAX_BOARDS];    /* board device information */
} txpciDEVINFO;

/* for request to and response from TXPCI_IOC_STATS ioctl */
typedef struct
{
    U32             options;            /* see txstats.h for full description */
    TX_STATSSET     set;                /* statistics provided as immediate response */
} txpciSTATS;

/* Scratch register layout for ioctl use */

#define TXPCIcntSCRATCHREG	8

typedef struct _txpciSCRATCHREG
{
    U8              Reg1st;             /* 1st register (0-7) */
    U8              RegCnt;             /* number to read */
    U8              Padding[2];
    U32             Register[TXPCIcntSCRATCHREG];
}
txpciSCRATCHREG, *PtxpciSCRATCHREG;

/*---------------------------------------------------------------------------*
 * I/O Communication Rings
 * (providing high-speed path between application and TX driver)
 *
 * from_drv for all messages (and payloads) from the driver to the application
 *
 * to_drv for all messages (and payloads) from the application to the driver
 *---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*
 * I/O Communication Control
 *---------------------------------------------------------------------------*/
typedef struct txpci_comm_ctl
{
    U32             ctl_type;           /* type of control message */
#define TXPCI_COMM_CTL_FREE         0   /* entry free for use */
#define TXPCI_COMM_CTL_TX_COMPLETE  1   /* transmit complete notification */
#define TXPCI_COMM_CTL_RX_INDIC     2   /* receive indication */
#define TXPCI_COMM_CTL_RX_ACK       3   /* receive acknowledgement */
#define TXPCI_COMM_CTL_ATTACH       4   /* app attaching window [board=ctl_ccode;channel=ctl_seq] */

    U32             ctl_ccode;          /* completion code assoc'd with CTL */

    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   ctl_tid;            /* thread ID [or pointer to thread key] */

    TX_LONG_FILL(seq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   ctl_seq;            /* sequence number [or pointer as sequencing key] */

} TXPCI_COMM_CTL;

/*---------------------------------------------------------------------------*
 * I/O Communication Message Header
 *---------------------------------------------------------------------------*/
typedef struct txpci_comm_msg_hdr
{
    TX_LONG_FILL(tid_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   msg_tid;            /* thread ID [or pointer to thread key] */

    TX_LONG_FILL(seq_fill)              /* filler to account for diff in long size when 32-bit */
    unsigned long   msg_seq;            /* sequence number [or pointer as sequencing key] */

    DPRH            msg_dpr;            /* Dual Port Ram header of message */
} TXPCI_COMM_MSG_HDR;

/*---------------------------------------------------------------------------*
 * I/O Communication Message
 *---------------------------------------------------------------------------*/
#define TXPCI_COMM_MSG_HDR_AREA 32      /* space reserved for message header area */
#define TXPCI_COMM_MSG_PAYLOAD  (2048-(TXPCI_COMM_MSG_HDR_AREA+(sizeof(TXPCI_COMM_CTL)*2)))

typedef struct txpci_comm_msg
{
    U8              payload[TXPCI_COMM_MSG_PAYLOAD];    /* RX or TX data payload */

    union
    {
        TXPCI_COMM_MSG_HDR  hdr;                        /* header of message */
        U8          hdr_area[TXPCI_COMM_MSG_HDR_AREA];  /* raw header overlay */
    } uhdr;

} TXPCI_COMM_MSG;

/*---------------------------------------------------------------------------*
 * I/O Communication Ring (1 CTL and 1 MSG ring for a given flow direction)
 *---------------------------------------------------------------------------*/
#define TXPCI_COMM_MSG_COUNT        16  /* this should match P2P_MAX_OUT_CHAN */
#define TXPCI_COMM_CTL_COUNT        (TXPCI_COMM_MSG_COUNT*2)    /* (DATA INDIC's + TX COMPLETE's) */

typedef struct txpci_comm_ring
{
    TXPCI_COMM_CTL  ctl[TXPCI_COMM_CTL_COUNT];  /* control ring */
    TXPCI_COMM_MSG  msg[TXPCI_COMM_MSG_COUNT];  /* message ring */
} TXPCI_COMM_RING;

/*---------------------------------------------------------------------------*
 * I/O Communication Shared Memory Area
 *
 *     from_drv.ctl[] for TX_COMPLETE and RX_INDIC
 *     from_drv.msg[] for messages received from TX boards
 *
 *       to_drv.ctl[] for RX_ACK
 *       to_drv.msg[] for messages bound for TX boards
 *---------------------------------------------------------------------------*/
typedef struct txpci_comm_mem
{
    TXPCI_COMM_RING from_drv;       /* comm ring for all flow from driver to application */
    TXPCI_COMM_RING to_drv;         /* comm ring for all flow from application to driver */
} TXPCI_COMM_MEM;

#ifndef _INKERNEL

/* the following is necessary only at user level */

#define TXPCI_OK			0       /* Must be 0! */
#define	TXPCI_GENERROR		1
#define TXPCI_MEMERROR		2
#define TXPCI_ERRORACK		3
#define TXPCI_UNKNOWN		4
#define TXPCI_GETMSGFAIL    5
#define TXPCI_BADARG		6
#define TXPCI_BADKERNEL		7
#define TXPCI_DONE          8
#define	TXPCI_BADTASK		9
#define TXPCI_CREATEFAIL    10
#define	TXPCI_ALLOCFAIL		11
#define	TXPCI_SENDFAIL		12
#define TXPCI_RECEIVEFAIL   13
#define TXPCI_TASKEXISTS    14
#define TXPCI_READREGFAIL   15
#define	TXPCI_BADADDR		16
#define	TXPCI_WRITEMEMFAIL	17
#define	TXPCI_WRITEREGFAIL	18
#define	TXPCI_TASKSTARTFAIL	19
#define TXPCI_ERRNO         20

#define MAXINPUT		128

#endif  /* _INKERNEL */

/* The following state definitions have been put in txpci.h
   since they are now visible outside of the driver (hsf library) */

/* Board Hardware States (as managed by  the driver) */

#define TXPCI_BOARD_UNINITED	0   /* UNIX system just booted */
#define TXPCI_BOARD_READY       1   /* Basic Initialization
                                     * (ready for download of OS) */
#define TXPCI_DPR_READY         6
#define TXPCI_BOARD_RESET       7


/* The following is the minor number used by the
   Hot Swap Controller portion of the TX driver */
#ifdef __sun
#define TXPCI_HSCNTRL_MINOR	1024
#else
#define	TXPCI_HSCNTRL_MINOR	416
#endif

#endif  /* _TXPCIUTIL_H */
