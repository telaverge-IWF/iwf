/*****************************************************************************
 *
 * tx2.h - This header is for the NMS Communications TX2000 Communication
 *         controller STREAMS based driver for SCO UNIX
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

#ifndef _TX2_H
#define _TX2_H

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


/* For use in STREAMS flow control */

#define TX2_FCMTU	(TX2_MTU + 20)  /* MTU plus max proto msg size for */

/*
 * The usable Dual Ported RAM is 4096 bytes total, the communication
 * buffers are therefore 4096/2 -  (sizeof(signature)|sizeof(mailbox control))
 * = 2048 - 4 =  2044. all of the rest of the DPR memory is mapped to the
 * CSR (the second 4096 bytes worth).
 */

#define TX2_MEM		8192            /* Total mapped DPR size */
#define TX2_DPRMAXBUF	(2048 - 4)  /* Maximum Message Size */
                    /* (sans sig or mbox ctrl) */

/* Default CP number */

#define TX2_CPNUM	0

/* Maximum number of boards */

/* NOTE: this should be configurable but it is needed
 * in the driver for the control block structure and
 * Thus we can't use TX2_UNITS (which comes from config.h).
 * Hence we will make it "big".
 */

#define	TX2MAXBOARDS	8

/* Layout of the Dual Ported Ram After OS is running on the Board */

#pragma pack(1)
struct dpr
{
    U8   txbuff[TX2_DPRMAXBUF];  /* Transmit buffer (to board) */
    U32  signature;  /* NMS Communications Kernel identifier */
    U8   rxbuff[TX2_DPRMAXBUF];  /* RX buffer (from board) */
    U8   txint;
    U8   txmsg;
    U8   rxint;
    U8   rxmsg;
    U8   csr;        /* Control/Status Register */
};

#pragma pack()

/* Signature */

#define TX2_SIG		0x3e32543c      /* "<T2>" */
#define TX3_SIG		0x3e33543c      /* "<T3>" */

/* Layout of Dual Ported RAM during OS load */

#define TX2_MAXPREBOOT	996
#define	TX2_MAXCPKBUFF	512

#pragma pack(1)
struct dprload
{
    U8   preboot[TX2_MAXPREBOOT];
    S8   timestr[4];
    U16  year;
    U8   month;
    U8   day;
    U8   hour;
    U8   min;
    U8   sec;
    U8   zone;
    U16  msec;
    U8   cpnum;
    U8   cpstr[3];
    U8   microcode;
    U8   micstr[3];
    U8   filler1[8];
    U8   tocmd;
    U8   filler2;
    U32  bootaddr;
    S16  length;
    U8   cpkbuff[TX2_MAXCPKBUFF];
    U8   filler3[498];
    U32  signature;
    U8   filler4[1792];
    U8   checkpoint;
    U8   diecode;
    U8   ramspeed;
    U8   ramparity;
    U32  ramsize;
    U8   filler5[244];
    U8   txint;
    U8   txmsg;
    U8   rxint;
    U8   rxmsg;
    U8   csr;
};

#pragma pack()

/* Bits used in the txmsg and rxmsg fields during DPR xmit/rcv */

#define	TX2_DPR_RESET	0x01        /* Reset  */
#define	TX2_DPR_TXMSG	0x02        /* message is waiting */
#define	TX2_DPR_INTACK	0x04        /* interrupt seen */
#define	TX2_DPR_MSGACK	0x08        /* message read and processed */
#define TX2_DPR_PCTOCP	0x10        /* PC->CP message */
#define TX2_DPR_CPTOPC	0x20        /* CP->PC message */
#define TX2_DPR_PREBOOT	0x80        /* Part of preboot sequence */

/* Command codes from CP to PC during normal DPR xmit/rcv */

#define TX2_CPK_RXACK	(TX2_DPR_CPTOPC | TX2_DPR_MSGACK)
#define TX2_CPK_MSG	(TX2_DPR_CPTOPC | TX2_DPR_TXMSG)
#define TX2_CPK_MSGACK	(TX2_DPR_CPTOPC | TX2_DPR_TXMSG | TX2_DPR_MSGACK)

/* Command codes from CP to PC during OS load (in the rxmsg field) */

#define	TX2_CPK_READY	(TX2_DPR_PREBOOT | 0x00)
#define	TX2_CPK_LOAD	(TX2_DPR_PREBOOT | TX2_DPR_CPTOPC | TX2_DPR_MSGACK)
#define	TX2_CPK_RUN	(TX2_DPR_PREBOOT | TX2_DPR_CPTOPC | TX2_DPR_RESET)

/* Local code for determining which board interrupted */

#define TX2_CPK_IDLE	0xff

/* Preboot command codes (tocmd field) for PC->CP */

#define	TX2_CP_WAIT	0xf0            /* PC informing CP to wait */
#define	TX2_CP_READ	0xf1            /* PC informing CP to read */
#define	TX2_CP_BOOT	0xf2            /* PC informing CP to */
                        /* execute loaded kernel */

/* Device control block (one per board) */

struct tx2device
{
    U16  unit;       /* The board unit number */
    unsigned int    irq;        /* The Interrupt */
    unsigned int    dprbase;    /* The Phys Addr of the DPR */
    struct dpr     *dprp;       /* The V Addr of the DPR (after OS is running) */
    struct dprload *dprloadp;   /* The V Addr of the DPR (before Loading OS) */
    U16  state;      /* The State of the board */
    U16  refcount;   /* The number of minors attached */
    struct msgb    *pendmp;     /* Outstanding message to transmit */
    struct queue   *pendq;      /* Queue for ack of message */
    U32   pendprimtype;   /* Primtype of unacknowledged message */
    U8   txmsg;      /* Image of the txmsg register for re-txs */
    U8   rxmsg;      /* Image of the rxmsg register for intr */
#ifdef __sun
#ifdef SOL8
    timeout_id_t    timeoutid;  /* Watchdog timer id */
#else
    unsigned int    timeoutid;  /* Watchdog timer id */
#endif
#else
    unsigned int    timeoutid;  /* Watchdog timer id */
#endif
    U32   flags;      /* Information fields */
    struct tx2cb   *cblist;     /* The list of cbs attached to this board */
    struct tx2hwstat *hwstat;   /* Board statistics */
    struct tx2cstat *chanstat;  /* per channel statistics list */
    TX2EE          *eeprom;     /* eeprom contents for board */
    U8   nxtrcvack;  /* Next ACK expected */
    U8   nxtrcvseq;  /* Next Sequence Number expected */
    U8   lstsndseq;  /* Last Sequence Number Sent */
    unsigned int    hardwaretype;   /* Type of board */
#if (_DDI == 8)
    /* STG - needed for UnixWare DDI 8 initialization and locking */
    void           *intr_cookie;    /* DDI 8 interrupt handle */
    lock_t         *bd_mutex;   /* DDI 8 per board mutex */
#endif
};

/* Board Types (value of unit field in sdevice file) */

#define TX2_2000		0
#define TX2_3000		1

/* Flags for device control block */

#define TX2_ACKSOFF		0x00000001

/* Sequence Number Manipulation Manifests */

#define	TX2_NIB			4           /* Size of a nibble */
#define	TX2_SEQNUMBERMASK	0x0f    /* For Wrapping the seq #s */

/* Board Hardware States (as managed by  the driver) */

#define TX2_BOARD_UNINITED	0       /* UNIX system just booted */
#define TX2_BOARD_READY		1       /* Basic Initialization (ready for download of OS) */
#define TX2_LOADING_PRELOADER	2
#define TX2_PRELOADER_RUNNING	3
#define TX2_LOADING_OS		4
#define TX2_OS_LOADED		5
#define TX2_DPR_READY		6

/* general field values */

#define TX2_INVALID_UNIT	(-1)    /* needed to initialize unit field */

/* Driver control block (one per Stream) */

struct tx2cb
{
    struct tx2cb   *next;       /* Used internally for the freelist */
    U16             index;      /* Used internally for list manipulation */
    struct tx2device *devp;     /* The pointer to the board structure */
    struct queue    *qp;         /* The READ queue pointer */
    U16             state;      /* State of the End Point */
    U16             flags;      /* Configuration information about the endpoint */
    S16             rxchan;     /* Bound Receive channel number */
    U32             punit;      /* The primary board number */
    struct tx2cb   *link[TX2MAXBOARDS]; /* control block linkage */
};

#define	TX2_ALLFLAG		0x01        /* All boards are attached to this endpoint */

#define	UNBOUND_CHANNEL		(-1)
#define TX2_MINCHAN		0           /* minimum usable channel number */
#define TX2_MAXCHAN		63          /* maximum usable channel number */

/* Driver Software States */

#define	TX2_UNINITED		0
#define	TX2_OPENED		1
#define	TX2_PROCESSING_CLOSE	2
#define TX2_ATTACHED		3
#define	TX2_BOUND		4

/* Driver return values for tx2proto */

#define TX2_FAIL		0
#define TX2_SUCCESS		1
#define TX2_QUEUE		2

/* Arguments for tx2sendack and tx2senderrorack */

#define TX2_NORMAL		0
#define TX2_ALWAYSQUEUE		1
#define TX2_NEVERQUEUE		2

/* Debugging items */

/* Debugging circular buffer */

#define TBUFFSIZE	10              /* 16 bytes total with header */
#define	TBUFFRECORDS	32

#pragma pack(1)
struct trecord
{
    dprheader_t     head;
    U8              data[TBUFFSIZE];
    int             tstamp;
};

#pragma pack()

/* Global variable externs (all defined in Space.c) */

extern unsigned int tx2_itype;  /* 1 = seperate interrupts, 2 = shared */

                    /* see manual page for sdevice */
#define TX2_SEPERATE			1
#define TX2_SHARED			2

extern unsigned int tx2_units;  /* Number of boards (units) */
extern unsigned int tx2_minors; /* Number of minors per board (unit) */

/* STG - Sun and UnixWare DDI 8 have similar locking */
#if defined(__sun) || (_DDI == 8) || defined(UNIXWARE)

/*
 * Set the max numbers here - actual configured sizes are
 * determined later
 */
#define	TX2_CNTLS	8               /* define the max number here */
#define	TX2_MINORS	16              /* 16 minors per device */
#endif

#if defined(__sun)

#define	TX2_BADPROP	(-1)
#ifndef ETXDRIVER

extern int      tx2want, tx2have;

#define	TX2_INTR_ENTER()	(tx2want=__LINE__, \
				 mutex_enter(&tx2_intr_mutex), \
				 tx2want=0, tx2have=__LINE__)

#define	TX2_INTR_EXIT()		(tx2have=0,mutex_exit(&tx2_intr_mutex))
#define	TX2_FREEZESTR(Q)	freezestr(Q)
#define	TX2_UNFREEZESTR(Q)	unfreezestr(Q)
#define TX2_MP_INIT(Q)		qprocson(Q)
#define TX2_MP_SHUTDOWN(Q)	qprocsoff(Q)
#undef splstr
#undef splx
#define splstr()		(TX2_INTR_ENTER(),0xdeadbeef)
#define splx(S)			TX2_INTR_EXIT()

/*
 * Mutexes	- intr mutex is used instead of splstr and splx to lock out
 *		  the interrupt handler.
 */
extern kmutex_t tx2_intr_mutex;

#endif  /* ETXDRIVER */

#else   /* __sun */

/* STG - UnixWare DDI 8 locking and MP related macros */

#define	TX2_INTR_ENTER()	LOCK(glob_mutex, plstr)
#define	TX2_INTR_EXIT()		UNLOCK(glob_mutex, plstr)
#define	TX2_FREEZESTR(Q)	freezestr(Q)
#define	TX2_UNFREEZESTR(Q)	unfreezestr(Q)
#define TX2_MP_INIT(Q)		qprocson(Q)
#define TX2_MP_SHUTDOWN(Q)	qprocsoff(Q)
#undef splstr
#undef splx
#define splstr()		(LOCK(glob_mutex,plstr), 0xdeadbeef)
#define splx(S)			UNLOCK(glob_mutex, plstr)

#endif  /* __sun */

extern struct tx2device tx2devs[];  /* Array of board control blocks */
extern struct tx2cb tx2minor_table[];   /* Array of minor device (Streams) control blocks */

extern struct tx2cb *tx2freelist;   /* Minor free list */

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

#endif  /* _TX2_H */
