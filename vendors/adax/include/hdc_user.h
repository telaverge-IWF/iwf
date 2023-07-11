/*
 * Copyright 2000 ADAX, Inc.
 *      Use of this code is subject to your agreement with ADAX, Inc.
 */


/* ver[] = @(#)hdc_user.h	1.6  delta  01/11/08 */

#define HDCRAMSIZE 0x200000	/* HDC has 2M ram */

#define MAXTXFRAME 2040
#define MAXRXFRAME 2100

#define MAXFRAME MAXRXFRAME

#define MODULE_MTP2 1		/* protocol type param passed to SAIOPSHMOD */

/* HDC ioctl defines */
#define AIOCSTAT 1	/* get Modem (CD) status */
#define AIOCGETCSPEC 8	/* get the CSPEC from HDLC proc */
#define AIOCGETLRT 9	/* get the Lower Receive Table */
#define AIOCGETLTT 10	/* get the Lower Transmit Table */
#define AIOCCSTOP 14	/* Stop channel and remove RTS */
#define AIOCTRANS 16	/* Initialize in Transparent mode */
#define AIOCSMODE 17	/* Set mode register */
#define AIOCGMODE 18	/* Get mode register */
#define	AIOCDIVERT 21	/* Divert received data to control port */
#define	AIOCCOUNTS 22	/* Provide I-frame counts and error counts */
#define	AIOCCZERO 23	/* Zero I-frame counts and error counts */
#define	AIOCLOOPBK 25	/* Start up with loop-back */
#define AIOCBITS 29     /* go read the driver code, it's too complicated */
#define AIOCSBITDLY 30  /* set delay for above routine */
#define	AIOCDEBUG 40	/* Alter debug level */

#define AIOC7HRESET 47  /* Reset hardware to known state */
#define AIOCGETTTS 52	/* Get the Siemens MPC channel time slots */
#define AIOCSETTTS 53	/* Set the Siemens MPC channel time slots */
#define AIOCFREETTS 54	/* Free the Siemens MPC channel time slots */
#define AIOCSETPORT 58	/* Set the port for an HDC user clone open */
#define AIOCGETCURD 59	/* Get the current RX descriptor */
#define AIOCGETCUTD 60	/* Get the current TX descriptor */
#define	AIOCFNDSLT 61	/* find mpc timeslot assignment 'index' for ctl port */
#define AIOCGETTSA 62	/* get all timeslot assignment descriptors */
#define AIOCGETID 63	/* get pci device and vender id.  debugging ioctl */
#define AIOCFISU 64	/* toggle FISU filtering for Pac Bell */
#define AIOCTIMSTAMP 65 /* toggle frame timestamping for Pac Bell */
#define AIOCSTIMR 66    /* set value of 8254 timr for min isr interval */
#define AIOCSETTSA 67	/* set time slot fill mask for a open channel */
#define AIOCSETCM 68	/* Set channel mode */
#define AIOCSETQ  69	/* Change High/Low water marks of driver */
#define AIOCRIQDMP 70	/* dump receive interrupt queue */
#define AIOCTIQDMP 71	/* dump transmit interrupt queue */
#define AIOCREGDMP 72	/* dump all siemens registers */
#define AIOCLSSU   73	/* transmit 3 or 4 byte frame continuously */
#define AIOCSETPROTO   74 /* set channel to run mtp2 */

#define AIOCGETURT	75	/* get upper receive descriptor table */
#define AIOCGETUTT	76	/* get upper transmit descriptor table */
#define AIOCGETCUURD	77	/* get current upper recevie descriptor */
#define AIOCGETCUUTD	78	/* get current upper transmit descriptor */
#define AIOCMVIP	80	/* H.100/MVIP control (HDC-cPCI only) */
#define AIOCSADCDMP	81	/* dump board HDC_SA_CHAN struct */
#define AIOCHCOUNTS	82	/* get counts from the host */
#define AIOCHCZERO	83	/* zero counts from the host */
#define AIOCGETCRSH	84	/* get crash results from abort handler */
#define AIOCSTACKDMP	85	/* dump stack */
#define AIOCTRACEDMP	86	/* dump strace buffer */
#define AIOCPRINTDMP	87	/* dump printf buffer */
#define AIOCTXCQDMP	88	/* dump command queue to SA */
#define AIOCRXCQDMP	89	/* dump command queue to HOST */

#define AIOCRAMLR 200  /* RAM LWORD read    All of these have first lword as */
#define AIOCRAMLW 201  /* RAM LWORD write   offset from HDCs-PCI start */
#define AIOCRAMSR 202  /* RAM 16-bit read   and transfer the remaining data. */
#define AIOCRAMSW 203  /* RAM 16-bit write  Reads return data at buffer start */

#define AIOCGVERR 240   /* Get the board Version Register */
#define AIOCSHSCR 241   /* Set the Hot Swap Control Register */
#define AIOCGHSCR 242   /* Get the Hot Swap Control Register */
 
#define AIOCGPMEM 243   /* Get the current PCI bus memory addr (use for swap) */
#define AIOCSPMEM 244   /* Set the current PCI bus memory addr (use for swap) */
#define AIOCDPMEM 245   /* Disable PCI bus memory address (use for swap) */
#define AIOCEPMEM 246   /* Enable  PCI bus memory address (use for swap) */
 
#define AIOCGJTAG 247   /* Get the JTAG programming register */
#define AIOCSJTAG 248   /* Set the JTAG programming register */
#define AIOCSSLED 249   /* Set the Status RED/GREEN LED:D0 is Green,D1 is Red */

#define SAIO ('S'<<24)	/* Strong Arm Bound ioctl */
#define COMP ('C'<<24)  /* APC7 Source Code Compatibility Mode ioctl */

#define HDIO ('H'<<16)	/* Stream head ioctl */
#define DRIO ('D'<<16)	/* hdc driver ioctl */
#define M2IO ('M'<<16)	/* MTP2 ioctl */
#define LAIO ('L'<<16)	/* LAP(B/D/V5/F) ioctl */

#define SAIOPSHMOD	(SAIO|HDIO|1)	/* push protocol module onto a stream*/
#define SAIOPOPMOD	(SAIO|HDIO|2)	/* pop a protocol module onto a stream*/

#define SAIOMEMFREE	(SAIO|DRIO|100)	/* reports mblks/dblks/mbuffs utilized*/
#define SAIOQUEUE	(SAIO|DRIO|101)	/* dump queue structure by index */
#define SAIOMBLK	(SAIO|DRIO|102)	/* finds first alloc'd mblk from index*/
#define SAIOMBLKDMP	(SAIO|DRIO|103)	/* dumps mblk by address or index */
#define SAIOTEST3	(SAIO|DRIO|104)	/* have SA print list of alloc'd mblks*/

#define SAIOSETTTS	(SAIO|DRIO|AIOCSETTTS)/* set timeslots for connection */
#define SAIOCOUNTS	(SAIO|DRIO|AIOCCOUNTS)/* return connection stats */
#define SAIOZERO	(SAIO|DRIO|AIOCCZERO)	/* zero connection stats */
#define SAIOGETCURD	(SAIO|DRIO|AIOCGETCURD)	/* get current rx desc */
#define SAIOGETCUTD	(SAIO|DRIO|AIOCGETCUTD)	/* get current tx desc */
#define SAIOSETCM	(SAIO|DRIO|AIOCSETCM)  	/* set channel mode (INV) */
#define SAIOSADCDMP	(SAIO|DRIO|AIOCSADCDMP)	/* dump sa_chan structure */


/*********** APC7 Source Code Compatibility ************/

/* Compatibility mode ioctls */
#define AIOCCOMPAT (COMP|1) /* Places the HDC Driver into 
			     * APC7 Source Compatibility Mode */
#define AIOCTIMR  (COMP|2)  /* Initialize counter/timer with given value */
#define AIOCGETIB (COMP|3)  /* Retrieve apc7 compatible IBLOCK structure */
#define AIOCGETRT (COMP|4)  /* Return MK5027 Receive ring entries */
#define AIOCGETTT (COMP|5)  /* Return MK5027 Transmit ring entries */
#define AIOCGETSB (COMP|6)  /* Return MK5027 Status Buffer */
#define AIOCSETIB (COMP|7)  /* Set apc7 compatible IBLOCK structure */
#define AIOCSTOP  (COMP|8)  /* Stop the specified channel, enter OOS */
#define AIOCSTART (COMP|9)  /* Start the MTP2 alignment procedure */
#define AIOCLPO   (COMP|10) /* Enter Local Processor Outage Mode */
#define AIOCLPR   (COMP|11) /* Recover Local Processor Outage Mode */
#define AIOCPON   (COMP|12) /* Enter Power On mode. */
#define AIOCPOFF  (COMP|13) /* Enter Power Off mode. */
#define AIOCINIT  (COMP|14) /* Initialize according to values in IBLOCK */
#define AIOCRBSNT (COMP|15) /* Write contents of MK5027 status block to RAM */
#define AIOCFSNC  (COMP|16) /* Release buffers in retransmit queue up to FSNC */
#define AIOCGETTB (COMP|17) /* Get retransmit buffer at specified index */
#define AIOCGETTQ (COMP|18) /* Retrieve MSU from transmit or streams buffer */
#define AIOCEMRGNCY (COMP|19)  /* Set Emergency Proving Mode */
#define AIOCEMRGEND (COMP|20)  /* End Emergency Proving Mode */
#define AIOCGETTS   (COMP|21)  /* Get number of bytes and number of 
                                * messages to be retrieved */
#define AIOCSIOSON  (COMP|22)  /* Allow sending of SIOS SUs in OOS mode */
#define AIOCSIOSOFF (COMP|23)  /* Stop sending of SIOS SUs in OOS mode */

/* APC7 ioctls that are not supported under 
 * HDC APC7 Source Compatibility Mode.
 * These ioctls will always fail with errno set to ENOENT
 */
#define AIORESET	(COMP|0)
#define AIOCMSTAT	(COMP|0)
#define AIOCREAD	(COMP|0)
#define AIOCRR01	(COMP|0)
#define AIOCLOCK	(COMP|0)
#define AIOCSMODE2	(COMP|0) /* Set mode 2 register */
#define AIOCGMODE2	(COMP|0) /* Get mode 2 register */
#define	AIOCSTWT	(COMP|0) /* Set transmit clock watchdog timer */
#define	AIOCSRWT	(COMP|0) /* Set receive  clock watchdog timer */
#define	AIOCSRSUTE	(COMP|0) /* Set received SU timer  */
#define	AIOCHILOWAT	(COMP|0) /* Set the Stream high and low water marks */
#define	AIOCPRESET	(COMP|0) /* Reset one MK5025 */
#define AIOCTMRSET	(COMP|0) /* Set the SS7 timer values based on */
				 /* clock speed in range 10MHZ - 33MHZ */
#define AIOCCGABAT	(COMP|0) /* Set the congestion abated threshold */
#define AIOCGTABAT	(COMP|0) /* Get congestion relieved threshold value */

#define	AIOCGCSR	(COMP|0) /* Get MK5025 control/status register */
#define	AIOCSCSR	(COMP|0) /* Set MK5025 control/status register */
#define AIOCSFLAG	(COMP|0)

/* Compatibility Mode Indications to MTP3 */
#define DLP_INIT 0        /* initialization complete */ 
#define DLP_INSERVICE 1   /* In Service */
#define DLP_TCW   3       /* Transmit Clock Watchdog timer expired */
#define DLP_RCW   4       /* Receive Clock Watchdog timer expired */
#define DLP_RSUTE 5       /* Receive SU Timer Expired */
#define DLP_ALGNOOS 8     /* Alignment Out of Service */
#define DLP_LSSUOOS 9     /* LSSU Out of Service */
#define DLP_T1OOS 10      /* T1 Out of Service */
#define DLP_TXOOS 11      /* Transmit Out of Service. (T6/T7 expiration) */
#define DLP_RXOOS 12      /* Receive Out of Service. (FIB/BSN errors) */ 
#define DLP_SUERMOOS 13   /* SUERM Out of Service */
#define DLP_RPO 16        /* Remote Processor Outage */
#define DLP_RPOR 17       /* Remote Processor Outage Recovered */
#define DLP_BSNT 18       /* 5027 has written the BSNT to the status buffer */
#define DLP_RETCOMP 19    /* completed retrieval of FSNC, updated Tx table */
#define DLP_RPB 20        /* Remote Processor Busy */
#define DLP_RPBR 21       /* Remote Processor Busy Recovered */
#define DLP_TTCPRI 0x10000

/* Structs and defines for AIOCMVIP */
typedef struct
	{
	unsigned int trunk;
	unsigned int starting_slot;
	unsigned int ending_slot;
	} MVIP_CMD;

/* defines for the MVIP_CMD struct */

/* These defines set the mode for the H.110 bus controller */
#define MVIP_H110_CTL 	 0xC0000000
#define H110_DISABLE	 0x00000000 /* Disconnect HDC-cPCI from H.110 bus */
#define H110_MASTER	 0x00000010 /* Become H.110 bus timing master */
#define H110_SLAVE_NOQCX 0x00000020 /* Become H.110 bus timing slave w/no QCX */
#define H110_SLAVE_QCX 	 0x00000030 /* Become H.110 bus timing slave w/QCX */
#define H110_CLOCK_A	 0x00000000 /* Drive H.110 clock set 'A' */
#define H110_CLOCK_B	 0x00000008 /* Drive H.110 clock set 'B' */
#define H110_TRUNK_MASK	 0x00001F00

/* This define is used to turn on mappings between
 * HDC ports and TDM data streams */
#define MVIP_CTL 		0x80000000

/* This define is used to turn off mappings between HDC
 * ports and TDM data streams */
#define MVIP_DISABLE_CTL	0x00000000

#define MVIP_TRUNK_MASK		0x00001F00
#define MVIP_SUBTRUNK_MASK	0x00000003

/* Compatibility Misc defines */
#define XPC_OWNA 0x8000
#define OWNA 0x8000	/* a synonym for XPC_OWNA */
#define NT 64		/* number of APC7 compatibility transmit descriptors */
#define NR 64 		/* number of APC7 compatibility receive descriptors */

#define SBACNT 25	/* Number of shorts returned from APC7 AIOCGETSB.
			 * HDC's MTP2 returns only an APC7_STATUS structure.
			 * User must supply buffer of at least 50 bytes
			 * to AIOCGETSB to be compatible with both
			 * APC7 AIOCGETSB and HDC AIOCGETSB, but only
			 * the first 16 bytes contain useful information 
			 * in both cases 
			 */

/* Compatibility Mode structures */

/* apc7 status buffer structure */
typedef struct apc7_status {
unsigned char bsnr;        /* last BSN received */
unsigned char bsnt;        /* last BSN transmitted */
unsigned char fsnr;        /* last FSN received */
unsigned char fsnt;        /* last FSN transmitted */
 
unsigned char fsnx;        /* next expected FSN to be received */
unsigned char rfsn;        /* FSN of oldest MSU in rexmit buffer */
unsigned char ridx;        /* index of current Rx descriptor */
unsigned char tidx;        /* index of current Tx descriptor */
 
unsigned char phase;       /* Protocol phase */
unsigned char rtidx;       /* index of current rexmit descriptor */
unsigned char rxstate;     /* Rx state of SS7 HW */
unsigned char txstate;     /* Tx state of SS7 HW */
 
unsigned short rsv_rev;    /* reserved and chip revision level */
unsigned short oct_rtx;    /* number of octets retransmitted */
} APC7_STATUS;

/* APC7 like phases for compatiblity with APC7 */
#define APC7_POWER_OFF			0
#define APC7_OUT_OF_SERVICE		2
#define APC7_INIT_ALIGN_NOT_ALGN	4
#define APC7_INIT_ALIGN_PROVING		6
#define APC7_ALIGN_NOT_READY		7
#define APC7_ALIGN_READY		8
#define APC7_IN_SERVICE			9
#define APC7_PROCESSOR_OUTAGE		10

typedef struct apc7_iblock {
    unsigned short Mode;            /* mode register */
    unsigned short N2_Scaler;       /* N2: (upper bits) count, and scaler */
    unsigned short N2;              /* N2: (lower 16 bits) */
    unsigned short T1timer;         /* T1: aligned ready timer value */
    unsigned short T2timer;         /* T2: not aligned timer value */
    unsigned short T3timer;         /* T3: aligned timeout timer value */
    unsigned short T4ntimer;        /* T4n: normal proving timer value */
    unsigned short T4etimer;        /* T4e: emergency proving timer value */
    unsigned short T5timer;         /* T5: busy transmit timer value */
    unsigned short T6timer;         /* T6: excess busy timer value */
    unsigned short T7timer;         /* T7: excess acknowledge timer value */
    unsigned short Tptimer;         /* TP: transmit polling timer value */
    unsigned short RES1;            /* Reserved field */
    unsigned short PO;              /* Protocol Options */
    unsigned short T_M;             /* SUERM threshold, proving abort lim */
    unsigned short D;               /* SUERM error rate (lower bound) */
    unsigned short Tin_Tie;         /* normal AERM, emerg AERM thresholds */
    unsigned short m;               /* maximum frame before count begins */
    unsigned short RLEN;            /* ring and window lengths */
    unsigned short RDRAl;           /* low 16 bits of Recv desc ring addr*/
    unsigned short TLEN;            /* transmit ring and window lengths */
    unsigned short TDRAl;           /* low 16 bits of xmit desc ring addr*/
    unsigned short SBAh;            /* high byte of status buffer addr */
    unsigned short SBAl;            /* high byte of status buffer addr */
    unsigned short RES2;            /* Reserved */
    unsigned short stats[47];       /* statistics and reserved */
    unsigned short Tftimer;         /* TTC Tf FISU send interval */
    unsigned short Tstimer;         /* TTC Ts SIOS send interval */
    unsigned short Totimer;         /* TTC To SIO send interval */
    unsigned short Tatimer;         /* TTC Ta SIE send interval */
    unsigned short RES3[24];        /* Reserved */
} APC7_IBLOCK;

/* the old name for APC7_IBLOCK in apc7_user.h was IBLOCK */
typedef APC7_IBLOCK IBLOCK;

typedef struct apc7_desc {
	unsigned short DFlags;		/* varius flags, upper 8 bits of addr */
	unsigned short BADRl;		/* low 16 bits of the buffer address */
	unsigned short BCNT;		/* size(in bytes,2's comp)of buffer */
	unsigned short MCNT;		/* size(in bytes,2's comp)of mesg */
} APC7_DESC;

/* the old name for APC7_DESC in apc7_user.h was DENTRY */
typedef APC7_DESC DENTRY;

/* apc7 statistics structure from the IBLOCK */
typedef struct apc7_stats {
        unsigned short SLFail_abnorm;  /* link failures due to abn. FIB, BSN */
        unsigned short SLFail_T7;      /* link failures due to T7 exp. */
        unsigned short SLFail_suerm;   /* link failures due to SUERM. */
        unsigned short SLFail_cong;    /* link failures due to T6 exp. */
        unsigned short ALFail_T2T3;    /* alignment failures due to T2 or T3*/
        unsigned short ALFail_aerm;    /* alignment failures due to aerm */
        unsigned short numNegAck;      /* number of neg. acks */
        unsigned short numErrSu;       /* number of SUs in error */
        unsigned char  reserved[56];   /* reserved as zeros */
        unsigned short SIBtx;          /* SIB tx'd */
        unsigned short SIBrx;          /* SIB rx'd */
        unsigned short N1rtx;          /* number of retransmissions due to N1*/
        unsigned short N2rtx;          /* number of retransmissions due to N2*/
        unsigned short MSUrtx;         /* num MSUs retransmitted */
        unsigned short MSUrtx_octets;  /* num MSU octets retransmitted */
        unsigned char  reserved2[10];  /* reserved as zeros */
} APC7_STATS;

typedef struct apc7_counts {
   struct apc7_stats stat;            /* SS7 stats from IBLOCK */
   unsigned char res[2];             /* reserved */
   unsigned int MSUsrx;              /* number of MSUs Rx'd by host */
   unsigned int MSUstx;              /* number of MSUs Tx'd by host */
} APC7_COUNTS;
/********** END COMPATIBILITY SECTION **********/

/* Control port flag for AIOCSETTTS */
#define CTL_PORT_REQ 0x80000000

/* Flags and bitmasks for AIOCSETCM */
#define CSPEC_MODE     0x00000006 /* 6=HDLC mode, 0=TMA mode */
#define CSPEC_HDLC     0x00000006 /* 6=HDLC mode */
#define CSPEC_TMA      0x00000000 /* 0=TMA mode */

#define CSPEC_FA       0x00000008 /* flag filtering in TMA mode */
#define CSPEC_INV      0x00000080 /* Data inversion mode */
#define CSPEC_TFLAG    0x0000ff00 /* mask for supplying a FLAG for TMA mode */

/* Flags returned from AIOCSTAT */
#define M_ERR 32	/* Modem error */
#define W_ERROR 8	/* not used by HDC */
#define W_DONE 2	/* not used by HDC */

/* flags for setting loopback mode */
#define LOOP_OFF 	0x0	/* turn off loop back mode(regardless of type)*/
#define LOOP_COMPI	0x1	/* Turn on complete internal loopback */
#define LOOP_COMPE	0x2	/* Turn on complete external loopback */
#define LOOP_CHANI	0x5	/* Turn on Channel-wise internal loopback */
#define LOOP_CHANE	0x6	/* Turn on Channel-wise external loopback */

/* hot_swap register bits */
#define HOTSWAP_EDM	0x01
#define HOTSWAP_INS	0x02
#define HOTSWAP_EXT	0x04
#define HOTSWAP_LOO	0x08

/* types of crashes for AIOCGETCRSH */
#define UNDEF_HANDLER		0x55
#define SWI_HANDLER		0x53
#define PREFETCH_HANDLER	0x51
#define ABORT_HANDLER		0x49
#define FIQ_HANDLER		0x47

/* stats kept for each link */
typedef struct Lstats {
	unsigned short ncrc_err;	/* count of CRC errors encountered */
	unsigned short creads;		/* count of RX ring reorganizations */
	unsigned short n_null1;		/* count of T1 timeouts */
	unsigned short n_rejsrx;	/* count of rejs recv'd */
	unsigned short n_rejstx;	/* count of rejs sent */
	unsigned short n_shortf;	/* count of short frames received */
	unsigned int frames_in;		/* count of I-frames received */
	unsigned int frames_out;	/* count of I-frames out to network */
	unsigned int fisus;		/* count of recvd FISUs */
	unsigned int rxintrs;		/* number of Rx intr vectors */
	unsigned int txintrs;		/* number of Tx intr vectors */
	unsigned int rx_fiint;		/* num of Rx FI intrs */
	unsigned int tx_fiint;		/* num of Tx FI intrs */
	unsigned int rx_errint;		/* num of Rx ERR intrs */
	unsigned int tx_errint;		/* num of Tx ERR intrs */
	unsigned int rx_foint;		/* num of Rx FO intrs */
	unsigned int tx_foint;		/* num of Tx FO intrs */
	unsigned int rx_sfint;		/* num of Rx SF intrs */
	unsigned int tx_fe2int;		/* num of Tx FE2 intrs */
	unsigned int rx_ra;		/* num of Rx RA descriptors */
	unsigned int rx_rof;		/* num of Rx ROF descriptors */
	unsigned int rx_loss;		/* num of Rx LOSS descriptors */
	unsigned int rx_nob;		/* num of Rx NOB descriptors */
	unsigned int rx_lfd;		/* num of Rx LFD descriptors */
	} LSTATS;

/* stats kept by the host */
typedef struct Hstats {
	unsigned int frames_in;		/* count of I-frames received */
	unsigned int frames_out;	/* count of I-frames out to network */
	unsigned int rputfail;		/* count of rsrv canput failures */
	unsigned int rxintrs;
	unsigned int txintrs;
} HSTATS;

#define NUTPC 16 	/* number of upper TXDESC per channel */
#define NURPC 16	/* number of upper RXDESC per channel */
#define NTPC 16		/* number of lower TXDESC per channel */ 
#define NRPC 32		/* number of lower RXDESC per channel */

/* Receive Descriptor */
typedef struct urxdesc {
	volatile unsigned int rhold_hi;	/* flags: hold,h_int,rx max len,null */
	volatile unsigned int next;	/* next ptr; NON_CACHED board rel */
	volatile unsigned int baddr;	/* pointer to data area */
	volatile unsigned int rbno_stat;/* flags: fe,c,rx buff len,stat */
	volatile unsigned int pm;	/* board rel. mblk address. */
	} URXDESC;

/* Receive Descriptor */
typedef struct rxdesc {
	volatile unsigned int rhold_hi;	/* flags: hold,h_int,rx max len,null */
	volatile unsigned int next;	/* next ptr; CACHED board rel */
	volatile unsigned int baddr;	/* CACHED-type buffer address */
	volatile unsigned int rbno_stat;/* flags: fe,c,rx buff len,stat */
	} RXDESC;

/* Transmit Descriptor */
typedef struct txdesc {
	volatile unsigned int tbno_fnum;/* various flags, tx len, fill count */
	volatile unsigned int next;	/* next ptr; NON-CACHED board rel */
	volatile unsigned int baddr;	/* NON-CACHED-type buffer address */	
	} TXDESC;

/* Lower Transmit Descriptor */
typedef struct ltxdesc {
	volatile unsigned int tbno_fnum;/* various flags, tx len, fill count */
	volatile unsigned int next;	/* next ptr; CACHED board rel */
	volatile unsigned int baddr;	/* CACHED-type buffer address */
	volatile unsigned int pm;	/* Ptr to mblk_t that holds the */
	} LTXDESC;			/* data buffer baddr points to. */

#define TRACELEN 1024
typedef struct {
unsigned int lbolt;	/* time of trace entry */
unsigned char hdc_num;
unsigned char scc_num;
char chno;
unsigned char type;	/* type of message being traced, one of 
			 * M_DATA, M_PROTO, M_CTL, or M_IOCTL */
unsigned int len;	/* length of data for M_DATA or M_PROTO ,
			 * length of optional data for M_CTL or M_IOCTL */
unsigned int opt1;	/* command type for M_IOCTL, others ZZZZ */
} hdc_trace_info_t;
