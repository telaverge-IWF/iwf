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
#ifndef _TXUTIL_H_
#define _TXUTIL_H_

/* Layout of DPR header (see dpruser.h) */

typedef DPRH dprheader_t;

#ifndef MIN
#define MIN(a,b) (((a)>(b))?(b):(a))
#endif
#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#define TX2_MTU		1514		/* the MTU for the board is 1514 */

/* Board statistics */

struct tx2hwstat {
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
	unsigned long userappabovehiwat; /* unused in tx2 driver */
	unsigned long userappbelowlowat; /* unused in tx2 driver */
	unsigned long rhiwatdropped;	 /* unused in tx2 driver */
	unsigned long getsendbuff_nobufs; /* unused in tx2 driver */
    unsigned long writethrottle;    /* unused in tx2 driver */
    unsigned long nosendbufs;       /* unused in tx2 driver */
    unsigned long unacked;          /* unused in tx2 driver */
    unsigned long outplistcnt;      /* unused in tx2 driver */
    unsigned long outpliststat;     /* unused in tx2 driver */
    unsigned long outplistmask;     /* unused in tx2 driver */
    unsigned long inplistcnt;       /* unused in tx2 driver */
    unsigned short wqcount;       /* unused in tx2 driver */
    unsigned long rq_msgcnt;       /* unused in tx2 driver */
    unsigned long rq_msgmax;       /* unused in tx2 driver */
};

/* Channel statistics (per board) */

struct tx2cstat {
	struct tx2chanstat *cs_next;	/* link to next block */
	unsigned long cs_chan;		/* which channel */
	unsigned long cs_txpkts;	/* packets sent */
	unsigned long cs_txbytes;	/* bytes sent */
	unsigned long cs_txdrop;	/* packets dropped on transmission */
	unsigned long cs_rxpkts;	/* packets received */
	unsigned long cs_rxbytes;	/* bytes received */
	unsigned long cs_rxdrop;	/* received packets dropped */
};

/* Driver Registers */

struct tx2regs {
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

/* The primitives */

#define TX2_NOTYPE		0
#define	TX2_OK_ACK		1
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

/* The acknowledgment when all went well */
typedef struct tx2_ok_ack {
	unsigned long	tx2_primitive;
	unsigned long	tx2_correct_primitive;
	unsigned long	tx2_seq;	/* sequence number */
} tx2_ok_ack_t;

/* The acknowledgment when an error occured */
typedef struct tx2_error_ack {
	unsigned long	tx2_primitive;
	unsigned long	tx2_error_primitive;
	unsigned long	tx2_error_type;
} tx2_error_ack_t;

/* Error Types */

#define	TX2_OUTSTATE		0
#define	TX2_NOMEM		1
#define	TX2_INVALID_ARGUMENT	2
#define	TX2_OUTHSTATE		3
#define	TX2_INVALID_DATA	4
#define	TX2_INVALID_SIZE	5
#define	TX2_STREAM_FAILURE	6
#define	TX2_ALREADY_BOUND	7

/* Map a board to this STREAM */
typedef struct tx2_attach_req {
	unsigned long	tx2_primitive;
	unsigned long	tx2_board;
	unsigned long	pad;		/* padded to make it the size of an error ack */
} tx2_attach_req_t;

#define	ATTACHALL	0xffffffff	/* attach all boards to this Stream */

/* Unmap the board from this STREAM */
typedef struct tx2_detach_req {
	unsigned long	tx2_primitive;
	unsigned long	pad[2];		/* padded to make it the size of an error ack */
} tx2_detach_req_t;

/* Bind a channel to this STREAM */
typedef struct tx2_bind_req {
	unsigned long	tx2_primitive;
	unsigned long	tx2_channel;
	unsigned long	pad;		/* padded to make it the size of an error ack */
} tx2_bind_req_t;

/* Unbind a channel from this STREAM */
typedef struct tx2_unbind_req {
	unsigned long	tx2_primitive;
	unsigned long	pad[2];		/* padded to make it the size of an error ack */
} tx2_unbind_req_t;

/* Used for sending data to the board (on the indicated channel) */
/* Data is in an M_DATA message following this M_PROTO message */
typedef struct tx2_data_req {
	unsigned long	tx2_primitive;
	unsigned long	tx2_length;	/* length doesn't include this header */
	unsigned long	tx2_loadaddr;	/* for OS loading and Preboot */
	unsigned long	tx2_type;
	unsigned long	tx2_seq;	/* sequence number */
} tx2_data_req_t;

#define	TX2_PREBOOT_DATA		0
#define	TX2_OS_DATA			1
#define	TX2_NORMAL_DATA			2
#define	TX2_NORMAL_DATA_NOACKS		3
#define	TX2_PREBOOT_DATA_NOSTART	4

/* Data that was received from the board (on a particular channel) */
/* Data is in an M_DATA message following this M_PROTO message */
typedef struct tx2_data_ind {
	unsigned long	tx2_primitive;
	unsigned long	tx2_length;	/* length doesn't include this header */
	unsigned long	tx2_srcchannel;
} tx2_data_ind_t;

/* Tweek the board (set the CSR or request the CSR status) */
typedef struct tx2_board_info_req {
	unsigned long	tx2_primitive;
	unsigned long	tx2_command;	/* See list that follows */
	unsigned long	tx2_image;	/* last 8-bits used only for TX2_WRITECSRDIRECT */
	unsigned long	pad[2];		/* make it the size of an info_ack */
} tx2_board_info_req_t;

/* Commands for tx2_board_info_req.tx2_command */

#define	TX2_READSTATUS		0
#define	TX2_WRITECSRDIRECT	1
#define TX2_RUNOS		2

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

typedef struct tx2_start_req {
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
} tx2_start_req_t;

/* Response to a tx2_board_info_req */
typedef struct tx2_board_info_ack {
	unsigned long	tx2_primitive;
	unsigned long	tx2_unit;
	unsigned long	tx2_image;	/* hardware status (CSR Image) */
	unsigned long	tx2_sstate;	/* driver software state */
	unsigned long	tx2_hstate;	/* driver hardware state */
} tx2_board_info_ack_t;

/* Both of the following are used for reading the DPR */
typedef struct tx2_dpr_read_req {
	unsigned long	tx2_primitive;
	unsigned long	tx2_length;	/* length, in bytes, to read */
	unsigned long	tx2_offset;	/* starting address from which to read */
	unsigned long	tx2_seq;	/* sequence number */
} tx2_dpr_read_req_t;

/* The data read is in an M_DATA message following this M_PCPROTO message */
typedef struct tx2_dpr_read_ack {
	unsigned long	tx2_primitive;
	unsigned long	tx2_length;	/* length read */
	unsigned long	tx2_offset;	/* starting offset which was read  */
	unsigned long	tx2_seq;	/* sequence number */
} tx2_dpr_read_ack_t;

/* The following is used for writing the DPR */
/* The data should be contained in an M_DATA message */
/* following this M_PCPROTO message. */
/* This message will be acked (nacked) via a tx2_ok_ack (tx2_error_ack) */
typedef struct tx2_dpr_write_req {
	unsigned long	tx2_primitive;
	unsigned long	tx2_length;	/* length, in bytes, to be written */
	unsigned long	tx2_offset;	/* starting offset to which to write */
	unsigned long	tx2_seq;	/* sequence number */
} tx2_dpr_write_req_t;

/* The (cast-o-matic) primitive union */

union tx2_primitives {
	unsigned long 		tx2_primitive;
	tx2_ok_ack_t		ok_ack;
	tx2_error_ack_t		error_ack;
	tx2_attach_req_t	attach_req;
	tx2_detach_req_t	detach_req;
	tx2_bind_req_t		bind_req;
	tx2_unbind_req_t	unbind_req;
	tx2_data_req_t		data_req;
	tx2_data_ind_t		data_ind;
	tx2_board_info_req_t	board_info_req;
	tx2_board_info_ack_t	board_info_ack;
	tx2_dpr_read_req_t	dpr_read_req;
	tx2_dpr_read_ack_t	dpr_read_ack;
	tx2_dpr_write_req_t	dpr_write_req;
};

/* The various sizes */

#define TX2_OK_ACK_SIZE		sizeof(tx2_ok_ack_t)
#define TX2_ERROR_ACK_SIZE	sizeof(tx2_error_ack_t)
#define TX2_ATTACH_REQ_SIZE	sizeof(tx2_attach_req_t)
#define TX2_DETACH_REQ_SIZE	sizeof(tx2_detach_req_t)
#define TX2_BIND_REQ_SIZE	sizeof(tx2_bind_req_t)
#define TX2_UNBIND_REQ_SIZE	sizeof(tx2_unbind_req_t)
#define	TX2_DATA_REQ_SIZE	sizeof(tx2_data_req_t)
#define TX2_DATA_IND_SIZE	sizeof(tx2_data_ind_t)
#define TX2_BOARD_INFO_REQ_SIZE	sizeof(tx2_board_info_req_t)
#define TX2_BOARD_INFO_ACK_SIZE	sizeof(tx2_board_info_ack_t)
#define TX2_DPR_READ_REQ_SIZE	sizeof(tx2_dpr_read_req_t)
#define TX2_DPR_READ_ACK_SIZE	sizeof(tx2_dpr_read_ack_t)
#define TX2_DPR_WRITE_REQ_SIZE	sizeof(tx2_dpr_write_req_t)

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

struct gstat {
	unsigned long intr;
	unsigned long rsrv;
	unsigned long wsrv;
	unsigned long wput;
	unsigned long rqueue;
	unsigned long wqueue;
	unsigned long wputbq;
	unsigned long rputbq;
	unsigned long protofail;
	unsigned long protosuccess;
	unsigned long strayintr;
	unsigned long intrcalled;
	unsigned long timeout;
	unsigned long config;
	unsigned long retry;
};

/* TX2000 EEPROM layout and constants */
/* The National Semiconductor NM93C06 EEPROM has 16 register of 16 bits each */

#define TX1000_AT_20	1

#define ETH_10BASE2	01
#define ETH_10BASE5	02
#define ETH_10BASET	03

#define NONE		00
#define V24		01
#define V35		02
#define V24X		03

#pragma pack(1)
struct tx2ee {
	unsigned short signrev;		/*  1: Signature */
	unsigned short ethaddr0;	/*  2: Ethernet address - most-sign word */
	unsigned short ethaddr1;        /*  3:  */
	unsigned short ethaddr2;	/*  4: Ethernet address - least-sign word */
	unsigned char  sn12;		/*     Serial Number digits 1 & 2 */
	unsigned char  board_info;	/*  5: Board Info : high nyb = type  low nyb = Rev */
	unsigned char  sn56;		/*     Serial Number digits 5 & 6 */
	unsigned char  sn34;		/*  6: Serial Number digits 3 & 4 */
	unsigned char  sn90;		/*     Serial Number digits 9 & 10 */
	unsigned char  sn78;		/*  7: Serial Number digits 7 & 8 */
	unsigned char  bus_adapter;   	/*     Bus    Adapters Installed */
	unsigned char  serial_adapter;  /*  8: Serial Adapters Installed */
	/* Currently unused area */
	unsigned short avail1;          /*  9:  */
	unsigned short avail2;          /* 10:  */
	unsigned short avail3;          /* 11:  */
	unsigned short avail4;          /* 12:  */
	unsigned short avail5;          /* 13:  */
	unsigned short avail6;          /* 14:  */
	unsigned short avail7;          /* 15:  */
	unsigned short checksum;        /* 16:  */
};
#pragma pack()

#define EE_WORDS_USED	8		/* # of words used */
#define EE_WORDS_TOTAL	16		/* # of total words */

#ifndef _INKERNEL
/* the following is necessary only at user level */

#define	BOARDDEV		"/dev/tx2000"
#define	PCIBOARDDEV		"/dev/txpci"

#define BOOTCHAN		0
#define TASKCHAN		7
#define DEFAULTCONCHAN		6
#define DEFAULTBOARD		1

#define TX2_OK			0	/* Must be 0! */
#define	TX2_GENERROR		1
#define TX2_MEMERROR		2
#define TX2_ERRORACK		3
#define TX2_UNKNOWN		4
#define TX2_GETMSGFAIL		5
#define TX2_BADARG		6
#define TX2_BADKERNEL		7
#define	TX2_DONE		8
#define	TX2_BADTASK		9
#define	TX2_CREATEFAIL		10
#define	TX2_ALLOCFAIL		11
#define	TX2_SENDFAIL		12
#define	TX2_RECEIVEFAIL		13
#define	TX2_TASKEXISTS		14
#define	TX2_READREGFAIL		15
#define	TX2_BADADDR		16
#define	TX2_WRITEMEMFAIL	17
#define	TX2_WRITEREGFAIL	18
#define	TX2_TASKSTARTFAIL	19
#define	TX2_ERRNO		20

#define MAXINPUT		128

/* Some prototypes */

extern long txswablong(long longval);
extern short txswabshort(short shortval);
extern int tx2attach(int fd, unsigned long board);
extern int tx2detach(int fd);
extern int tx2bind(int fd, unsigned int chan);
extern int tx2unbind(int fd);

extern int txsenddata(
	int fd,
	unsigned long length,
	unsigned long type,
	unsigned long loadaddr,
	unsigned char *datap,
	unsigned long *eprimp,
	unsigned long *etypep
);

extern int txrecvdata(
	int fd,
	unsigned long *chanp,
	unsigned char *datap,
	unsigned long *lengthp,
	unsigned long *eprimp,
	unsigned long *etypep
);

extern int txsendcontrol(
	int fd,
	unsigned long cmd,
	unsigned long *imagep,
	unsigned char *datap,
	unsigned long *hstatep,
	unsigned long *sstatep,
	unsigned long *unitp,
	unsigned long *eprimp,
	unsigned long *etypep
);

extern int txsendprim(
	int fd,
	unsigned long ptype,
	unsigned long arg,
	unsigned long *eprimp,
	unsigned long *etypep
);

/* CPI Compatability */

#define CPIM_CHAN	1
#define CPIM_PORT	2
#define	CPIFORMAT	"CPIDRVR TX2000 V%d"
#define CPSTRSIZE	20 

#ifndef __CPI_H

#define PORT(b,c)	(((b) << 8) + (c))

/* CPI Prototypes */

#ifdef __STDC__
extern int cpi_init(short dummy, char **idstring);
extern int cpi_open(unsigned short port, short mode, void (*rec)());
extern int cpi_close(int fd);
extern int cpi_send(int fd, char *buf);
extern int cpi_get_data(int fd, char *buf, short *length);
extern short cpi_read_dpr(int fd, char *buf, short off, short len);
extern short cpi_write_dpr(int fd, char *buf, short off, short len);
#else
extern int cpi_init();
extern int cpi_open();
extern int cpi_close();
extern int cpi_send();
extern int cpi_get_data();
extern short cpi_read_dpr();
extern short cpi_write_dpr();
#endif /* __STDC__ */

extern unsigned long cpi_errno;

#endif /* not __CPI_H */

#endif /* _INKERNEL */

#endif /* _TXUTIL_H_ */
