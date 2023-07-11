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
/*
 *
 * Author:		M.A.Firman
 * Organization: 	TEKnique, Inc.
 * Original Writing:	April 1996
 *
 * Author:		S.M.Bytnar
 * Organization:	Software Technologies Group, Inc.
 * Updated: 			February 2000
 * Comments about flow control added.
 */

/* OLD_FLOW_CONTROL==1 is defined as: use STREAMs hiwat/lowat
 * marks as the limiting factor on machine memory usage.
 *
 * OLD_FLOW_CONTROL==0 is defined as: use STREAMs hiwat/lowat
 * marks only for flow controlling unresponding processes,
 * while maintaining a FREEINBUF only when an application
 * has read the data.
 */
#define OLD_FLOW_CONTROL 1

#ifndef _TXPCI_H
#define _TXPCI_H

/* For use in STREAMS flow control */

#define TXPCI_FCMTU	(TXPCI_MTU + 20)	/* MTU plus max proto msg size for */

/*
 * The usable Dual Ported RAM is 4096 bytes total, the communication
 * buffers are therefore 4096/2 -  (sizeof(signature)|sizeof(mailbox control))
 * = 2048 - 4 =  2044. all of the rest of the DPR memory is mapped to the
 * CSR (the second 4096 bytes worth).
 */

#define	TXPCI_MTU	1514
#define TXPCI_MEM	0x100000	/* Total mapped DPR size */
#define TXPCI_DPRMAXBUF	(2048 - 4)	/* Maximum Message Size */
 /* (sans sig or mbox ctrl) */
/* Default CP number */

#define TXPCI_CPNUM	0

/* Maximum number of boards */

#define	TXPCIMAXBOARDS	26

/* Signature */

#define TXPCI_SIG	0x3e32543c	/* "<T2>" */

/* Layout of Dual Ported RAM during OS load */

#define TXPCI_MAXPREBOOT	996
#define	TXPCI_MAXCPKBUFF	512


/* Bits used in the txmsg and rxmsg fields during DPR xmit/rcv */

#define	TXPCI_DPR_RESET	0x01	/* Reset  */
#define	TXPCI_DPR_TXMSG	0x02	/* message is waiting */
#define	TXPCI_DPR_INTACK	0x04	/* interrupt seen */
#define	TXPCI_DPR_MSGACK	0x08	/* message read and processed */
#define TXPCI_DPR_PCTOCP	0x10	/* PC->CP message */
#define TXPCI_DPR_CPTOPC	0x20	/* CP->PC message */
#define TXPCI_DPR_PREBOOT	0x80	/* Part of preboot sequence */

/* Command codes from CP to PC during normal DPR xmit/rcv */

#define TXPCI_CPK_RXACK	(TXPCI_DPR_CPTOPC | TXPCI_DPR_MSGACK)
#define TXPCI_CPK_MSG	(TXPCI_DPR_CPTOPC | TXPCI_DPR_TXMSG)
#define TXPCI_CPK_MSGACK (TXPCI_DPR_CPTOPC|TXPCI_DPR_TXMSG|TXPCI_DPR_MSGACK)

/* Command codes from CP to PC during OS load (in the rxmsg field) */

#define	TXPCI_CPK_READY	(TXPCI_DPR_PREBOOT | 0x00)
#define	TXPCI_CPK_LOAD	(TXPCI_DPR_PREBOOT|TXPCI_DPR_CPTOPC|TXPCI_DPR_MSGACK)
#define	TXPCI_CPK_RUN	(TXPCI_DPR_PREBOOT|TXPCI_DPR_CPTOPC|TXPCI_DPR_RESET)

/* Local code for determining which board interrupted */

#define TXPCI_CPK_IDLE	0xff

/* Preboot command codes (tocmd field) for PC->CP */

#define	TXPCI_CP_WAIT	0xf0	/* PC informing CP to wait */
#define	TXPCI_CP_READ	0xf1	/* PC informing CP to read */
#define	TXPCI_CP_BOOT	0xf2	/* PC informing CP to */
 /* execute loaded kernel */

/* Board Types (value of unit field in sdevice file) */

#define TXPCI_2000		0
#define TXPCI_3000		1

/* Value of CpId before it has been set */
#define TXPCI_UNASSIGNED_CPID	-1

/* Flags for device control block */

#define TXPCI_ACKSOFF		0x00000001
#define	TXPCI_INTR_OCCURED	0x00000002
#define	TXPCI_INTR_ACTIVE	0x00000004

/* Sequence Number Manipulation Manifests */

#define	TXPCI_NIB			4	/* Size of a nibble */
#define	TXPCI_SEQNUMBERMASK	0x0f	/* For Wrapping the seq #s */

/* Board Hardware States (as managed by  the driver) */

#define TXPCI_BOARD_UNINITED	0	/* UNIX system just booted */
#define TXPCI_BOARD_READY	1	/* Basic Initialization (ready for
					 * download of OS) */
#define TXPCI_DPR_READY		6
#define	TXPCI_BOARD_RESET	7

#define	UNBOUND_CHANNEL		(-1)
#define TXPCI_MINCHAN		0	/* minimum usable channel number */
#define TXPCI_MAXCHAN		63	/* maximum usable channel number */

/* Driver Software States */

#define	TXPCI_UNINITED		0
#define	TXPCI_OPENED		1
#define	TXPCI_PROCESSING_CLOSE	2
#define TXPCI_ATTACHED		3
#define	TXPCI_BOUND		4

/* Driver return values for txpciproto */

#define TXPCI_FAIL		0
#define TXPCI_SUCCESS		1
#define TXPCI_QUEUE		2
#define TXPCI_FULL		3

/* Arguments for txpcisendack and txpcisenderrorack */

#define TXPCI_NORMAL		0
#define TXPCI_ALWAYSQUEUE	1
#define TXPCI_NEVERQUEUE		2


#define	TXPCI_CBFCOMPAT		1	/* Control block flag */
#define	TXPCI_CBFDEFAULT	TXPCI_CBFCOMPAT

/* Mutex macros */
#define TXPCI_INTR_ENTER(DP)    mutex_enter(&(DP)->intr_mutex)
#define TXPCI_INTR_EXIT(DP)     mutex_exit(&(DP)->intr_mutex)

#define TXPCI_GLOBAL_ENTER()    mutex_enter(&txpci_global_mutex)
#define TXPCI_GLOBAL_EXIT()     mutex_exit(&txpci_global_mutex)


/* Message access macros */
#define MSG_I2OHDR(rp)	((rp)->common)
#define	MSG_REQHDR(rp)	((rp)->p2p.p2preq)
#define	MSG_MSGHDR(rp)	((rp)->p2p.req.DeviceSend.msg)
#define	MSG_REPLYHDR(rp) ((rp)->p2p.p2preply)
#define	MSG_SENDREQ_SIZE	(sizeof(P2PI2O_HDR)+sizeof(P2PREQ_HDR)+sizeof(P2PMSG_HDR))
#define	MSG_STOPREPLY_SIZE	(sizeof(P2PI2O_HDR)+sizeof(P2PREQ_HDR)+sizeof(P2PMSG_HDR))
#define	MSG_REPLY_SIZE	(sizeof(P2PI2O_HDR)+sizeof(P2PREQ_HDR))
#define	MSG_ALIVEREQ_SIZE	(sizeof(P2PI2O_HDR)+sizeof(P2PREQ_HDR))

/* Debugging items */

#ifdef DEBUG
#define HEXDUMP(x)	txpci_hexdump x
#define CFGDUMP(x)	txpci_cfgdump x
#else
#define HEXDUMP(x)
#define CFGDUMP(x)
#endif

/* Debugging circular buffer */

#define TBUFFSIZE	10	/* 16 bytes total with header */
#define	TBUFFRECORDS	32

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


/* Set the max numbers here - actual configured sizes are determined later */

#define	TXPCI_BADPROP	(-1)
#define	TXPCI_CNTLS	TXPCIMAXBOARDS	/* define the max number here */
#define	TXPCI_MINORS	16	/* 16 minors per device */

/* micro seconds to wait for board to reset - interrupts are enabled and
 * the Stopped message is checked */
#define TXPCI_RESTART_USECS     1000000


#define	TXPCI_FREEZESTR(Q)	freezestr(Q)
#define	TXPCI_UNFREEZESTR(Q)	unfreezestr(Q)

#undef STATIC
#ifdef DEBUG
extern int txpci_lineno;
#define	TXSETLINE		(txpci_lineno = __LINE__)
#define	MSGDUMP(x)		txpci_msgdump x
#else
#define TXSETLINE
#define	MSGDUMP(x)
#endif	/* DEBUG */

#define STATIC

#ifndef isprint
#define isprint(c)		((c)>=' '&&(c)<='~')	/* ASCII only */
#endif

static int IsLittleEndian_16(char *cmem)
{
    unsigned short *wmem = (unsigned short*)cmem;
    unsigned short savew = *wmem;
    char savec;
    *wmem = 0x1234;
    savec = cmem[0];
    *wmem = savew;
    return (savec != 0x12);
}

#define FIELD_OFFSET(type, field)    ((ULONG)&(((type *)0)->field))

#define	GETSENDBUF		txpci_GetSendBuf
#define	GETRECVBUF		txpci_GetRecvBuf
#define	MSGISREPLY(mp)		((mp)->common.MessageFlags&P2PI2O_REPLY?1:0)
#define	GETMSGTYPE(mp)		(MSGISREPLY(mp) \
				 ?(mp)->p2p.p2preply.DetailedStatusCode.p2p.XFuncCode \
                                 :(mp)->p2p.p2preq.XFunctionCode)

#if 0 /* defined(NODEF) */
#define	ADDR2OFF(dp,mp)		((mp && (dp)->iospacep)?((caddr_t)mp)-(dp)->iospacep:-1)
#define	OFF2ADDR(dp,off)	((off && (dp)->iospacep)?(dp)->iospacep+(off):NULL)
#define SENDBUF(dp,mp)		((dp)->csrp->InQue = ADDR2OFF(dp,mp))
#define	FREEINBUF(dp,mp)	((dp)->csrp->OutQue = ADDR2OFF(dp,mp))
#else
#define	ADDR2OFF(dp,mp)		txpci_Addr2Off(dp,mp)
#define	OFF2ADDR(dp,off)	txpci_Off2Addr(dp, off)
#define SENDBUF(dp,mp)		txpci_SendBuf(dp, mp)
#define	FREEINBUF(dp,mp)	txpci_FreeInBuf(dp, mp)
#endif

#ifndef TRUE
#define TRUE	1
#define	FALSE	0
#endif
/*
 * These are from the NT driver file hdwr32xx.h - 3210 has been
 * replaced with pci
 */
/* Reset Register Bit Layout */

#define TXPCIrstRST360         0x01	/* 1: assert reset to 360s */
#define TXPCIrstRST060         0x02	/* 1: assert reset to 68060 */
#define TXPCIrstSDRAM          0x04	/* 1: enbl SDRAM cycles */
#define TXPCIrstBOOT360        0x08	/* 1: 68360 in master mode */
#define TXPCIrstNMI            0x10	/* 1: enable NMI to device */

/* Reset Register interface conditioning (via DEC par ROM intf) */

#define TXPCIromiSETUP         0x7E00	/* setup to access PLD */


/* LED Control Register Layout */

#define TXPCIled1TOP           0x01	/* 1: LED 1 top on */
#define TXPCIled1MID           0x02	/* 1: LED 1 middle on */
#define TXPCIled1BOT           0x04	/* 1: LED 1 bottom on */
#define TXPCIled1MASK          0x07	/* mask for LED 1 */

#define TXPCIled2TOP           0x08	/* 1: LED 2 top on */
#define TXPCIled2MID           0x10	/* 1: LED 2 middle on */
#define TXPCIled2BOT           0x20	/* 1: LED 2 bottom on */
/*****************************************************************
 * End of #defines
 *****************************************************************/

/*****************************************************************
 * Begin Structure Definitions
 *****************************************************************/

/*****************************************************************
 * Begin PACKED structures:
 */

#pragma pack(1)	/* Make sure these are packed */

/* PLD Address Space layout of host accessible registers */
/* From hdwr32xx.h in NT driver */
typedef struct _txpciPLDSPACE
{
    UCHAR           Reset;	/* reset reg */
    UCHAR           LEDs;	/* LED control reg */
    UCHAR           Reserved[2];/* future */
}               txpciPLDSPACE, *PtxpciPLDSPACE;

typedef
struct _dprload	/* PACKED struct */
{
    unsigned char   preboot[TXPCI_MAXPREBOOT];
    char            timestr[4];
    unsigned short  year;
    unsigned char   month;
    unsigned char   day;
    unsigned char   hour;
    unsigned char   min;
    unsigned char   sec;
    unsigned char   zone;
    unsigned short  msec;
    unsigned char   cpnum;
    unsigned char   cpstr[3];
    unsigned char   microcode;
    unsigned char   micstr[3];
    unsigned char   filler1[8];
    unsigned char   tocmd;
    unsigned char   filler2;
    unsigned long   bootaddr;
    short           length;
    unsigned char   cpkbuff[TXPCI_MAXCPKBUFF];
    unsigned char   filler3[498];
    unsigned long   signature;
    unsigned char   filler4[1792];
    unsigned char   checkpoint;
    unsigned char   diecode;
    unsigned char   ramspeed;
    unsigned char   ramparity;
    unsigned long   ramsize;
    unsigned char   filler5[244];
    unsigned char   txint;
    unsigned char   txmsg;
    unsigned char   rxint;
    unsigned char   rxmsg;
    unsigned char   csr;
} dprload, *Pdprload;

typedef
struct _trecord	/* PACKED struct */
{
    dprheader_t     head;
    unsigned char   data[TBUFFSIZE];
    int             tstamp;
} trecord, *Ptrecord;

#pragma pack()

/*
 * End Packed Structures
 *****************************************************************/


/* Device control block (one per board) */

typedef
struct _txpcidevice
{
  /* id for soft interrupt */
  ddi_softintr_t		id;

  /* for interrupt control */
  kmutex_t			intr_mutex;
  ddi_iblock_cookie_t		icookie;

  struct _txpcidevice		*next;
  /* Per board configuration parameters */
  ULONG				SerialNum; /* Serial from CSR */
  CHAR				CpId;	   /* Assigned ID - 0 to MAX */
    UINT	Mvip90Enable;	/* Boolean - H100 to MVIP converter present */

  /* Other stuff */
  int			ddi_instance;
  Pcsr2155x		csrp;		/* The Addr of the CSR block */
  caddr_t		iospacep; 	/* The Addr of the CP buffer space */
  ddi_acc_handle_t	csr_handle;
  ddi_acc_handle_t	io_handle;
  unsigned char		EthAddr1[6];
  unsigned char		EthAddr2[6];
  unsigned short	state;	/* The State of the board */
  unsigned short	hsState; /* The hot swap state of the board */
  unsigned short	refcount;	/* The number of minors attached */
  unsigned short	intr_added;	/* Flag for interrupt added success */

  int			timeoutid;	/* Watchdog timer id */
  UINT			alivetimeout; /* Watchdog reset time. 0 when NMI is asserted. */
  int			missedalive;
    unsigned int    passedhiwat; /* STREAMs flow control kicked in... dropping data when != 0. */
  unsigned long   flags;	/* Information fields */
  struct _txpcicb  *cblist;	/* The list of cbs attached to this board */
  struct _txpcihwstat *hwstat;	/* Board statistics */
  struct _txpcicstat *chanstat;	/* per channel statistics list */
  /* These are now shorts - with the PCI device, we can accumulate
     higher numbers */
  unsigned long   nxtrcvack;	/* Next ACK expected */
  unsigned long   nxtrcvseq;	/* Next Sequence Number expected */
  unsigned long   lstsndseq;	/* Last Sequence Number Sent */
  unsigned long   unacked;	/* # of messages not acknowledged
				   by the board */
  unsigned int    hardwaretype;	/* Type of board */

  /*
   * Solaris specific items
   */
  dev_info_t *		dip;
  P2P_MSG		ReqProto;	/* Request */
  P2P_MSG		SendProto;	/* Send */
  P2P_MSG		AnsProto;	/* Answer */
  P2P_MSG		DefAnsProto;	/* Deferred Answer */
  uint32_t		bus;		/* Which PCI bus the card is on */
  uint32_t		slot;		/* Slot that the card is in */

    /* control flags */
    int       id_isvalid;       /* Flag indicating whether driver attached to software interrupt */
} txpcidevice, *Ptxpcidevice;

/* Driver control block (one per Stream) */

typedef
struct _txpcicb
{
    struct _txpcicb  *next;	/* Used internally for the freelist */
    unsigned short  index;	/* Used internally for list manipulation */
    struct _txpcidevice *devp;	/* The pointer to the board structure */
    struct queue   *qp;		/* The READ queue pointer */
    unsigned short  state;	/* State of the End Point */
    unsigned short  flags;	/* Configuration information about the
				 * endpoint */
    ULONG           rxchan;	/* Bound Receive channel number */
    unsigned long   punit;	/* The primary board number */
    struct _txpcicb  *link;	/* control block linkage */
} txpcicb, *Ptxpcicb;

typedef
struct _txpciconfig
{
    /* Global parameters */
    int		TimeOffset;	/* Time Zone offset in minutes */
    UINT	TotalBoards;	/* Total number of boards */
    UINT	AliveTimeout;	/* Seconds between alives - 0 disables */
} txpciconfig, *Ptxpciconfig;

typedef
struct _txpcihwstat
{
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
    unsigned long rhiwatdropped;
    unsigned long getsendbuff_nobufs;
    unsigned long writethrottle;
    unsigned long nosendbufs;
    unsigned long unacked;
    unsigned long outplistcnt;
    unsigned long outpliststat;
    unsigned long outplistmask;
    unsigned long inplistcnt;
    unsigned short wqcount;
    unsigned long rq_msgcnt;
    unsigned long rq_msgmax;
} txpcihwstat, *Ptxpcihwstat;

typedef struct gstat	txpcigstat;

typedef struct  _txtm
{                               /* see ctime(3) */
    int     tm_sec;
    int     tm_min;
    int     tm_hour;
    int     tm_mday;
    int     tm_mon;
    int     tm_year;
    int     tm_wday;
    int     tm_yday;
} TxTime;


typedef struct  /* Reg propertry structure */
{
    uint32_t   pciInfo;
    uint32_t   StartHI;
    uint32_t   Start;
    uint32_t   SizeHI;
    uint32_t   Size;
} PCIREG_t;

/* Macros to unpack  bus, device and function values from the phys-hi
   cell of the reg property.  They are based on the structure above. */

#define PI_FUN(A)       ( ( A >> 8  ) & 0x07 )
#define PI_DEV(A)       ( ( A >> 11 ) & 0x1F )
#define PI_BUS(A)       ( ( A >> 16 ) & 0xFF )
#define PI_TYPE(A)      ( ( A >> 24 ) & 0x03 )
#define PI_PREFETCH(A)  ( ( A >> 30 ) & 0x01 )

/*****************************************************************
 * End Structure Definitions
 *****************************************************************/

/*****************************************************************
 * Begin External Declarations
 *****************************************************************/


extern UINT txpci_units; /* Number of boards (units) */
extern UINT txpci_minors;/* Number of minors per board (unit) */

extern txpcidevice	txpcidevs[];	/* Array of board control blocks */
extern txpcidevice	txpci_hsdev;    /* Device for Hot Swap Interface */
extern txpcicb		txpciminor_table[];	/* Array of minor device
					   (Streams) control blocks */
extern kmutex_t		txpci_global_mutex;
extern ddi_iblock_cookie_t	txpci_icookie;
extern Ptxpcicb		txpcifreelist;	/* Minor free list */
extern P2P_MSG		txpci_ReqProto;		/* Request */
extern P2P_MSG		txpci_SendProto;	/* Send */
extern P2P_MSG		txpci_AnsProto;		/* Answer */
extern P2P_MSG		txpci_DefAnsProto;	/* Deferred Answer */
extern txpciconfig	txpci_GlobalConfig;
extern Ptxpcidevice	txpci_devbusy;
extern Ptxpcidevice	txpci_devfree;
extern void		*txpci_hsProcRef;


extern Ptxpciconfig	txpci_GetConfigEntry(ULONG);
extern void		txpci_ReadConfigFile(dev_info_t *);
extern int		txpci_NextCpId(int);
extern void		txpci_FreeConfigEntry(USHORT);
extern Ptxpcidevice	txpci_dip2dev(dev_info_t *);
extern void		txpci_hexdump(caddr_t, int, int);
extern void		txpci_cfgdump(UCHAR *, int);
extern Ptxpcidevice	txpci_AllocDevice(Ptxpciconfig);
extern P2P_MSG *	txpci_GetSendBuf(Ptxpcidevice);
extern void		txpci_msgdump(Ptxpcidevice, P2P_MSG *, int);
extern void		txpci_ResetBoard(Ptxpcidevice);
extern void		txpci_Suspend060(Ptxpcidevice);
extern void		txpci_InitMsgs (Ptxpcidevice);
extern P2P_MSG *	txpci_GetRecvBuf(Ptxpcidevice);
extern txpcigstat	txpciglobalstat;
extern Ptxpcihwstat	txpciallochwstat(void);
extern void		txpcifreehwstat(Ptxpcihwstat);
extern void		txpci_enableintr(Ptxpcidevice);
extern ULONG		txpci_disableintr(Ptxpcidevice);
extern void		txpci_restoreintr(Ptxpcidevice, ULONG);
extern int		Time2TxTime(time_t, TxTime *);
extern void		txpcidevinit(void);
extern Ptxpcidevice	txpciallocdev(void);
extern void		txpcifreedev(Ptxpcidevice);
extern void		txpci_CheckAlive(void *);
extern void		txpci_CheckBoard(void *);
extern void		txpci_RestartBoard(Ptxpcidevice);
extern void		txpci_SendAlive(Ptxpcidevice);
extern ULONG		txpci_Addr2Off(Ptxpcidevice dp, P2P_MSG *mp);
extern P2P_MSG		*txpci_Off2Addr(Ptxpcidevice dp, ULONG off);
extern void		txpci_SendBuf(Ptxpcidevice dp, P2P_MSG *mp);
extern void		txpci_FreeInBuf(Ptxpcidevice dp, P2P_MSG *mp);
extern Ptxpcidevice	txpci_hsFindBoard(uint32_t bus, uint32_t slot);
#endif				/* _TXPCI_H */
