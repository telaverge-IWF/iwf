/******************************************************************
 **
 **			   PROPRIETARY NOTICE
 **
 **			Copyright (c) 1995,1996
 **			    By TEKnique, Inc.
 **
 **
 **  The following is licensed program material and is considered
 **  proprietary and confidential.  No part of this program may be
 **  reproduced or used in any form or by any means without the 
 **  express written permission of TEKnique, Inc.
 **
 *****************************************************************/
#ifndef _TXPCIUTIL_H_
#define _TXPCIUTIL_H_

/* Layout of DPR header (see dpruser.h) */

#define TXPCI_MTU		1514		/* the MTU for the board is 1514 */

/* Board statistics */

struct txpcihwstat {
	unsigned long intr;
	unsigned long tx;
	unsigned long rx;
	unsigned long run;
	unsigned long msg;
	unsigned long msgack;
	unsigned long rxack;
	unsigned long load;
	unsigned long ready;
	unsigned long strayintr;
	unsigned long outstate;
	unsigned long outmem;
	unsigned long nochan;
	unsigned long anomaly;
	unsigned long ackunexpected;
	unsigned long ackunexpectedload;
	unsigned long userappabovehiwat;
	unsigned long userappbelowlowat;
	unsigned long getsendbuff_nobufs;
};

/* Channel statistics (per board) */

struct txpcicstat {
	struct txpcichanstat *cs_next;	/* link to next block */
	unsigned long cs_chan;		/* which channel */
	unsigned long cs_txpkts;	/* packets sent */
	unsigned long cs_txbytes;	/* bytes sent */
	unsigned long cs_txdrop;	/* packets dropped on transmission */
	unsigned long cs_rxpkts;	/* packets received */
	unsigned long cs_rxbytes;	/* bytes received */
	unsigned long cs_rxdrop;	/* received packets dropped */
};

/* Driver Registers */

struct txpciregs {
	unsigned char	txint;			
	unsigned char	txmsg;			
	unsigned char	rxint;			
	unsigned char	rxmsg;			
	unsigned char	csr;		/* Control/Status Register */
	unsigned char	nxtrcvack;	/* Next ACK expected */
	unsigned char	nxtrcvseq;	/* Next Sequence Number expected */
	unsigned char	lstsndseq;	/* Last Sequence Number Sent */
};

/* Driver Commands (Requests, Indications, and Acknowledgments) */

/*
 *	NOTE:	The idea for this stuff was 
 *		stolen (shamelessly) from DLPI
 */

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
typedef struct txpci_ok_ack {
	unsigned long	txpci_primitive;
	unsigned long	txpci_correct_primitive;
	unsigned long	txpci_seq;	/* sequence number */
} txpci_ok_ack_t;

/* The acknowledgment when an error occured */
typedef struct txpci_error_ack {
	unsigned long	txpci_primitive;
	unsigned long	txpci_error_primitive;
	unsigned long	txpci_error_type;
} txpci_error_ack_t;

/* Error Types */

#define	TXPCI_OUTSTATE		0
#define	TXPCI_NOMEM		1
#define	TXPCI_INVALID_ARGUMENT	2
#define	TXPCI_OUTHSTATE		3
#define	TXPCI_INVALID_DATA	4
#define	TXPCI_INVALID_SIZE	5
#define	TXPCI_STREAM_FAILURE	6
#define	TXPCI_ALREADY_BOUND	7

/* Map a board to this STREAM */
typedef struct txpci_attach_req {
	unsigned long	txpci_primitive;
	unsigned long	txpci_board;
	unsigned long	pad;		/* padded to make it the size of an error ack */
} txpci_attach_req_t;

/* Unmap the board from this STREAM */
typedef struct txpci_detach_req {
	unsigned long	txpci_primitive;
	unsigned long	pad[2];		/* padded to make it the size of an error ack */
} txpci_detach_req_t;

/* Bind a channel to this STREAM */
typedef struct txpci_bind_req {
	unsigned long	txpci_primitive;
	unsigned long	txpci_channel;
	unsigned long	pad;		/* padded to make it the size of an error ack */
} txpci_bind_req_t;

/* Unbind a channel from this STREAM */
typedef struct txpci_unbind_req {
	unsigned long	txpci_primitive;
	unsigned long	pad[2];		/* padded to make it the size of an error ack */
} txpci_unbind_req_t;

/* Used for sending data to the board (on the indicated channel) */
/* Data is in an M_DATA message following this M_PROTO message */
typedef struct txpci_data_req {
	unsigned long	txpci_primitive;
	unsigned long	txpci_length;	/* length doesn't include this header */
	unsigned long	txpci_loadaddr;	/* for OS loading and Preboot */
	unsigned long	txpci_type;
	unsigned long	txpci_seq;	/* sequence number */
} txpci_data_req_t;

#define	TXPCI_PREBOOT_DATA		0
#define	TXPCI_OS_DATA			1
#define	TXPCI_NORMAL_DATA			2
#define	TXPCI_NORMAL_DATA_NOACKS		3
#define	TXPCI_PREBOOT_DATA_NOSTART	4

/* Data that was received from the board (on a particular channel) */
/* Data is in an M_DATA message following this M_PROTO message */
typedef struct txpci_data_ind {
	unsigned long	txpci_primitive;
	unsigned long	txpci_length;	/* length doesn't include this header */
	unsigned long	txpci_srcchannel;
} txpci_data_ind_t;

/* Tweek the board (set the CSR or request the CSR status) */
typedef struct txpci_board_info_req {
	unsigned long	txpci_primitive;
	unsigned long	txpci_command;	/* See list that follows */
	unsigned long	txpci_image;	/* last 8-bits used only for TXPCI_WRITECSRDIRECT */
	unsigned long	pad[2];		/* make it the size of an info_ack */
} txpci_board_info_req_t;

/* Commands for txpci_board_info_req.txpci_command */

#define	TXPCI_READSTATUS		0
#define	TXPCI_WRITECSRDIRECT	1
#define TXPCI_RUNOS		2

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

typedef struct txpci_start_req {
	unsigned short	year;
	unsigned char	month;
	unsigned char	day;
	unsigned char	hour;
	unsigned char	min;
	unsigned char	sec;
	unsigned char	zone;
	unsigned short	msec;
	unsigned char	microcode;
	unsigned long	entrypoint;
} txpci_start_req_t;

/* Response to a txpci_board_info_req */
typedef struct txpci_board_info_ack {
	unsigned long	txpci_primitive;
	unsigned long	txpci_unit;
	unsigned long	txpci_image;	/* hardware status (CSR Image) */
	unsigned long	txpci_sstate;	/* driver software state */
	unsigned long	txpci_hstate;	/* driver hardware state */
} txpci_board_info_ack_t;

/* Both of the following are used for reading the DPR */
typedef struct txpci_dpr_read_req {
	unsigned long	txpci_primitive;
	unsigned long	txpci_length;	/* length, in bytes, to read */
	unsigned long	txpci_offset;	/* starting address from which to read */
	unsigned long	txpci_seq;	/* sequence number */
} txpci_dpr_read_req_t;

/* The data read is in an M_DATA message following this M_PCPROTO message */
typedef struct txpci_dpr_read_ack {
	unsigned long	txpci_primitive;
	unsigned long	txpci_length;	/* length read */
	unsigned long	txpci_offset;	/* starting offset which was read  */
	unsigned long	txpci_seq;	/* sequence number */
} txpci_dpr_read_ack_t;

/* The following is used for writing the DPR */
/* The data should be contained in an M_DATA message */
/* following this M_PCPROTO message. */
/* This message will be acked (nacked) via a txpci_ok_ack (txpci_error_ack) */
typedef struct txpci_dpr_write_req {
	unsigned long	txpci_primitive;
	unsigned long	txpci_length;	/* length, in bytes, to be written */
	unsigned long	txpci_offset;	/* starting offset to which to write */
	unsigned long	txpci_seq;	/* sequence number */
} txpci_dpr_write_req_t;

/* The (cast-o-matic) primitive union */

union txpci_primitives {
	unsigned long 		txpci_primitive;
	txpci_ok_ack_t		ok_ack;
	txpci_error_ack_t		error_ack;
	txpci_attach_req_t	attach_req;
	txpci_detach_req_t	detach_req;
	txpci_bind_req_t		bind_req;
	txpci_unbind_req_t	unbind_req;
	txpci_data_req_t		data_req;
	txpci_data_ind_t		data_ind;
	txpci_board_info_req_t	board_info_req;
	txpci_board_info_ack_t	board_info_ack;
	txpci_dpr_read_req_t	dpr_read_req;
	txpci_dpr_read_ack_t	dpr_read_ack;
	txpci_dpr_write_req_t	dpr_write_req;
};

/* The various sizes */

#define TXPCI_OK_ACK_SIZE		sizeof(txpci_ok_ack_t)
#define TXPCI_ERROR_ACK_SIZE	sizeof(txpci_error_ack_t)
#define TXPCI_ATTACH_REQ_SIZE	sizeof(txpci_attach_req_t)
#define TXPCI_DETACH_REQ_SIZE	sizeof(txpci_detach_req_t)
#define TXPCI_BIND_REQ_SIZE	sizeof(txpci_bind_req_t)
#define TXPCI_UNBIND_REQ_SIZE	sizeof(txpci_unbind_req_t)
#define	TXPCI_DATA_REQ_SIZE	sizeof(txpci_data_req_t)
#define TXPCI_DATA_IND_SIZE	sizeof(txpci_data_ind_t)
#define TXPCI_BOARD_INFO_REQ_SIZE	sizeof(txpci_board_info_req_t)
#define TXPCI_BOARD_INFO_ACK_SIZE	sizeof(txpci_board_info_ack_t)
#define TXPCI_DPR_READ_REQ_SIZE	sizeof(txpci_dpr_read_req_t)
#define TXPCI_DPR_READ_ACK_SIZE	sizeof(txpci_dpr_read_ack_t)
#define TXPCI_DPR_WRITE_REQ_SIZE	sizeof(txpci_dpr_write_req_t)

/* Ioctls */

/* This first set should match (binarily) those for the TX2 boards */

#define	TXPCI_IOC_CLEARSTATE		TX2_IOC_CLEARSTATE
#define	TXPCI_IOC_CLEARSTAT		TX2_IOC_CLEARSTAT
#define	TXPCI_IOC_GETSTAT		TX2_IOC_GETSTAT
#define	TXPCI_IOC_GETNUMBEROFBOARDS	TX2_IOC_GETNUMBEROFBOARDS
#define	TXPCI_IOC_DUMPRECORDS		TX2_IOC_DUMPRECORDS
#define	TXPCI_IOC_TRACE			TX2_IOC_TRACE
#define	TXPCI_IOC_GETBOUNDCHANNEL	TX2_IOC_GETBOUNDCHANNEL
#define	TXPCI_IOC_GETVERSION		TX2_IOC_GETVERSION
#define	TXPCI_IOC_GETGSTAT		TX2_IOC_GETGSTAT
#define	TXPCI_IOC_ACKS			TX2_IOC_ACKS
#define	TXPCI_IOC_NOACKS		TX2_IOC_NOACKS
#define	TXPCI_IOC_GETATTACHEDBOARD	TX2_IOC_GETATTACHEDBOARD
#define	TXPCI_IOC_GETEEPROM		TX2_IOC_GETEEPROM
#define	TXPCI_IOC_STOREEEPROM		TX2_IOC_STOREEEPROM
#define	TXPCI_IOC_GETREGS		TX2_IOC_GETREGS
#define	TXPCI_IOC_GETHWTYPE		TX2_IOC_GETHWTYPE

/* New ioctls for PCI boards */

#define	TXPCI_IOC_READCTL		TX2_IOC(17)
#define	TXPCI_IOC_WRITECTL		TX2_IOC(18)
#define	TXPCI_IOC_SETLED		TX2_IOC(19)
#define	TXPCI_IOC_NMI			TX2_IOC(20)
#define	TXPCI_IOC_GETCONFIG		TX2_IOC(21)

#ifdef SOLARIS

/* These are the ioctls needed for the hsflib support for Hot Swap */
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


#endif

/* for response from TXPCI_IOC_GETCONFIG ioctl */

typedef struct {
  unsigned long	serialnum;	/* Not used for setting config */
  unsigned long	hardwaretype;   /* Not used for setting config */
  unsigned long	cpid;
  unsigned long	bus;
  unsigned long	slot;
} configinfo_t;

/* Scratch register layout for ioctl use */

#define TXPCIcntSCRATCHREG	8

typedef struct _txpciSCRATCHREG {
    unsigned char   Reg1st;     /* 1st register (0-7) */
    unsigned char   RegCnt;	/* number to read */
    unsigned long   Register[TXPCIcntSCRATCHREG];
}		txpciSCRATCHREG, *PtxpciSCRATCHREG;

#ifndef _INKERNEL
/* the following is necessary only at user level */

#define TXPCI_OK			0	/* Must be 0! */
#define	TXPCI_GENERROR		1
#define TXPCI_MEMERROR		2
#define TXPCI_ERRORACK		3
#define TXPCI_UNKNOWN		4
#define TXPCI_GETMSGFAIL		5
#define TXPCI_BADARG		6
#define TXPCI_BADKERNEL		7
#define	TXPCI_DONE		8
#define	TXPCI_BADTASK		9
#define	TXPCI_CREATEFAIL		10
#define	TXPCI_ALLOCFAIL		11
#define	TXPCI_SENDFAIL		12
#define	TXPCI_RECEIVEFAIL		13
#define	TXPCI_TASKEXISTS		14
#define	TXPCI_READREGFAIL		15
#define	TXPCI_BADADDR		16
#define	TXPCI_WRITEMEMFAIL	17
#define	TXPCI_WRITEREGFAIL	18
#define	TXPCI_TASKSTARTFAIL	19
#define	TXPCI_ERRNO		20

#define MAXINPUT		128

#endif /* _INKERNEL */

/* The following state definitions have been put in txpci.h
   since they are now visible outside of the driver (hsf library) */
/* Board Hardware States (as managed by  the driver) */

#define TXPCI_BOARD_UNINITED	0	/* UNIX system just booted */
#define TXPCI_BOARD_READY	1	/* Basic Initialization (ready for
					 * download of OS) */
#define TXPCI_DPR_READY		6
#define	TXPCI_BOARD_RESET	7


/* The following is the minor number used by the 
   Hot Swap Controller portion of the TX driver */
#define TXPCI_HSCNTRL_MINOR	1024

#endif /* _TXPCIUTIL_H_ */
