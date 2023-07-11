/*
 * Copyright (c) Adax, Inc., 1999 - 2001
 *   Use of this code is subject to your agreement with Adax, Inc.
 *   All rights reserved.
 *
 *  @(#)mtp2_user.h	1.6 delta 02/01/03
 *
 */

#define MAX_MTP2_LINK   32
#define MAX_MTP2_FRAME  274

#define SAIO ('S'<<24)	/* Processor Bound ioctl */
#define M2IO ('M'<<16)	/* MTP2 ioctl */

#define MTP2GETSB	(SAIO|M2IO|1) /* Get Status Buffer mtp2_status_buff_t */
#define MTP2STOP	(SAIO|M2IO|2) /* Stop channel and remove RTS */
#define MTP2START	(SAIO|M2IO|3) /* Start alianment procedure */
#define	MTP2COUNTS	(SAIO|M2IO|4) /* Provide Iframe cnts and error counts */
#define MTP2ZERO	(SAIO|M2IO|5) /* zero MTP2COUNTS */
#define	MTP2LPO		(SAIO|M2IO|6) /* Enter local processor outage mode */
#define	MTP2LPR		(SAIO|M2IO|7) /* Enter local processor recovered mode */
#define	MTP2RBSNT	(SAIO|M2IO|8) /* Retrieve entire status (a no-op) */
#define	MTP2FSNC	(SAIO|M2IO|9) /* free msgs up to and incl. FNSC */
#define	MTP2GETTB	(SAIO|M2IO|10) /* ret up a TX Buff indexed by 'j' */
#define	MTP2GETTQ	(SAIO|M2IO|11) /* ret up a TX q'd stream message */
#define	MTP2EMRGNCY	(SAIO|M2IO|12) /* Emergency prov to be used in START */
#define	MTP2EMRGEND	(SAIO|M2IO|13) /* end Emergency proving period */
#define MTP2GETTS	(SAIO|M2IO|14) /* get number of messages to retreive 
					* after performing MTP2FNSC */
#define MTP2FLUSH	(SAIO|M2IO|15) /* perform MTP2 flush command */
#define MTP2CONTINUE	(SAIO|M2IO|16) /* perform MTP2 continue command */
#define MTP2GETIB	(SAIO|M2IO|17) /* get init block */
#define MTP2SETIB	(SAIO|M2IO|18) /* set init block */
#define MTP2SIOSON	(SAIO|M2IO|19) /* turn on SIOS transmission */
#define MTP2SIOSOFF	(SAIO|M2IO|20) /* turn off SIOS transmission */
#define MTP2LPB		(SAIO|M2IO|21) /* flow control on read side, send SIB*/
#define MTP2LPBR	(SAIO|M2IO|22) /* flow control on read side ended */
#define MTP2GETAPC7SB	(SAIO|M2IO|23) /* Get APC7-like status buffer */
#define MTP2SPROTOMODE	(SAIO|M2IO|24) /* Set proto mode ITU/JT/ANNEXA, etc.. */
#define MTP2GETAAIB	(SAIO|M2IO|25) /* Get ITU Annex-A init Block */
#define MTP2SETAAIB	(SAIO|M2IO|26) /* Set ITU Annex-A init Block */
#define MTP2GETAASB	(SAIO|M2IO|27) /* Get Status Buff annex_a_status_buff */

#define MTP2_PHASE_IND	(SAIO|M2IO|256)	/* MK5027 like phase indication */
#define MTP2_PPRIM_IND	(SAIO|M2IO|257)	/* MK5027 like PPRIM */

/* flags for MTP2SPROTOMODE ioctl */
#define ITU_Q703 	0	/* ITU Q.703 protocol mode */
#define ANSI_Q703 	0	/* ANSI Q.703 protocol mode */
#define ITU_ANNEX_A	2	/* ITU 7/96 Q.703 ANNEX A */
#define ITU_ANNEX_A_EXT	3	/* ITU 7/96 Q.703 ANNEX A with 
				 * large sequence numbers.
				 * (currently unsupported) */
#define JT_Q703		4	/* JT-Q.703 Japanese MTP 2 
				 * (currently unsupported) */

/* mtp2 status defines */
#define OUTOFSERVICE		0
#define ALIGNMENTINPROCESS	1
#define INSERVICE		2

/* mtp2 states */
#define	OUT_OF_SERVICE		0
#define	INITIAL_ALIGNMENT	1
#define	ALIGNED_NOT_READY	2
#define	PROVING			3
#define	ALIGNED_READY		4
#define	IN_SERVICE		5

/* define the event causes */
#define T1_EXPIRY		0
#define T2_EXPIRY		1
#define T3_EXPIRY		2
#define T6_EXPIRY		3
#define T7_EXPIRY		4
#define START_LINK_FROM_MTP3	5
#define STOP_LINK_FROM_MTP3	6
#define SIOS_FROM_NETWORK	7
#define SIO_FROM_NETWORK	8
#define SIN_FROM_NETWORK	9
#define SIE_FROM_NETWORK	10
#define LINK_FAILED		11
#define SUERM_EXPIRY		12
#define INCORRECT_FIB_BSN	13
#define CURRENT_PROVING_ATTEMPT_FAILURE	14
#define ALL_PROVING_ATTEMPT_FAILURE	15
#define PROCESSOR_OUTAGE_FROM_MTP3	16
#define SIPO_FROM_NETWORK	17
#define LPO_RECOVERY		18
#define RPO_RECOVERY		19
#define LOCAL_CONG		20
#define SIB_FROM_NETWORK	21
#define LCONG_RECOVERY		22
#define RCONG_RECOVERY		23
#define CONG_LEVEL_CHANGE	24
#define DISCARD_LEVEL_CHANGE	25
#define FISU_FROM_NETWORK	26
#define MSU_FROM_NETWORK	27
#define N1_N2_LEVEL_HIT		28
#define N1_N2_LEVEL_CLEARED	29
#define MSU_DROPPED		30

char *mtp2_states[] = {"OUT_OF_SERVICE","INITIAL_ALIGNMENT","ALIGNED_NOT_READY",
		       "PROVING","ALIGNED_READY","IN_SERVICE"};

char *mtp2_status[] = {"OUTOFSERVICE", "ALIGNMENTINPROCESS", "INSERVICE"};

char *mtp2_events[] = {"T1_EXPIRY","T2_EXPIRY","T3_EXPIRY","T6_EXPIRY",
		       "T7_EXPIRY","START_LINK_FROM_MTP3","STOP_LINK_FROM_MTP3",
		       "SIOS_FROM_NETWORK","SIO_FROM_NETWORK",
		       "SIN_FROM_NETWORK","SIE_FROM_NETWORK","LINK_FAILED",
		       "SUERM_EXPIRY","INCORRECT_FIB_BSN",
		       "CURRENT_PROVING_ATTEMPT_FAILURE",
		       "ALL_PROVING_ATTEMPT_FAILURE",
		       "PROCESSOR_OUTAGE_FROM_MTP3","SIPO_FROM_NETWORK",
		       "LPO_RECOVERY","RPO_RECOVERY","LOCAL_CONG",
		       "SIB_FROM_NETWORK","LCONG_RECOVERY","RCONG_RECOVERY",
		       "CONG_LEVEL_CHANGE","DISCARD_LEVEL_CHANGE",
		       "FISU_FROM_NETWORK","MSU_FROM_NETWORK","N1_N2_LEVEL_HIT",
		       "N1_N2_LEVEL_CLEARED","MSU_DROPPED"};

typedef struct mtp2_stat_param
{
unsigned int link_in_service_start_time;/* Time stamp, when link go inservice */
unsigned int sl_failure_all_reason;	/* Link failure : all reasons */
unsigned int sl_failure_abnormal_fib_bsnr;/* Link failure :abnormal FIBR/BSNR */
unsigned int sl_failure_t7_expiry;	/* Link failure : delay of ack */
unsigned int sl_cong_too_long;		/* Link failure : excessive cong. */
unsigned int sl_failure_suerm;		/* Link failure : SUERM */
unsigned int sl_failure_t2t3_expiry;	/* Proving failure: T2 T3 expiry*/
unsigned int sl_prov_algn_failed;	/* Proving failure: AERM */
unsigned int num_su_error;		/* Number of SUs in error */
unsigned int num_neg_ack;		/* Number of negative ack recv */
unsigned int num_msu_rtx;		/* Number of MSUs retransmitted */
unsigned int num_octet_rtx;		/* Number of octets retransmitted */
unsigned int num_sif_sio_octet_tx;	/* Number of MSU octets transmitted */
unsigned int num_sif_sio_octet_rx;	/* Number of MSU octets recevied */
unsigned int num_msu_tx;		/* Number of MSUs transmitted */
unsigned int num_msu_rx;		/* Number of MSUs received */
unsigned int num_sib_tx;		/* Number of SIBs transmitted */
unsigned int num_sib_rx;		/* Number of SIBs received */
unsigned int num_interval_err;          /* Number of interval with SU in error */
unsigned int num_forced_rtx_n1;         /* Number of forced rtx event due to N1 */
unsigned int num_forced_rtx_n2;         /* Number of forced rtx events due to N2 */
} mtp2_stat_param_t;


#define TOTAL_LINKS (MAX_LINKSETS * MAX_LINKS_PER_LINKSET)

typedef struct
{
ITS_OCTET linkset;                      /* Linkset id */
ITS_OCTET linkcode;                     /* Link id */
}mtp2_ls_ln; 

typedef struct
{
  mtp2_ls_ln mtp2Hdr[MAX_LINKSETS][MAX_LINKS_PER_LINKSET];
  mtp2_stat_param_t statData[MAX_LINKSETS][MAX_LINKS_PER_LINKSET];
} mtp2_stat_table;

mtp2_stat_table mtp2LinkOmImage[2];

typedef struct
{
  ITS_OCTET activeOm;
  ITS_OCTET inactiveOm;
}
mtp2OmBuffer;

typedef struct
{
  SS7_Family family;
  ITS_UINT count;
  mtp2_ls_ln hdr[TOTAL_LINKS];
  mtp2_stat_param_t stats[TOTAL_LINKS];
} mtp2Om;


typedef struct mtp2_status_buff
{
unsigned char bsnr;        /* last BSN received */
unsigned char bsnt;        /* last BSN transmitted */
unsigned char fsnr;        /* last FSN received */
unsigned char fsnt;        /* last FSN transmitted */
 
unsigned char fsnx;        /* next expected FSN to be received */
unsigned char rfsn;        /* FSN of oldest MSU in rexmit buffer */
unsigned char ridx;        /* always 0; has no meaning for SW MTP2 */
unsigned char tidx;        /* always 0; has no meaning for SW MTP2 */
 
unsigned char phase;       /* Protocol Phase */
unsigned char rtidx;       /* always 0; has no meaning for SW MTP2 */
unsigned char rxstate;     /* always 0; has no meaning for SW MTP2 */
unsigned char txstate;     /* always 0; has no meaning for SW MTP2 */
 
unsigned short rsv_rev;    /* reserved */
unsigned short oct_rtx;    /* number of octets retransmitted */
} mtp2_status_buff_t;

typedef struct annex_a_status_buff
{
unsigned short bsnr;        /* last BSN received */
unsigned short bsnt;        /* last BSN transmitted */
unsigned short fsnr;        /* last FSN received */
unsigned short fsnt;        /* last FSN transmitted */
 
unsigned short fsnx;        /* next expected FSN to be received */
unsigned short rfsn;        /* FSN of oldest MSU in rexmit buffer */
unsigned short ridx;        /* always 0; has no meaning for SW MTP2 */
unsigned short tidx;        /* always 0; has no meaning for SW MTP2 */
 
unsigned short phase;       /* Protocol Phase */
unsigned short rtidx;       /* always 0; has no meaning for SW MTP2 */
unsigned short rxstate;     /* always 0; has no meaning for SW MTP2 */
unsigned short txstate;     /* always 0; has no meaning for SW MTP2 */
 
unsigned short rsv_rev;    /* reserved */
unsigned short oct_rtx;    /* number of octets retransmitted */
} annex_a_status_buff_t;

/* All timer values are specified in 10s of milliseconds 
 * (100 * desired value in seconds = IBLOCK value) */

/* positions of timers values in IB */
#define IB_TIMER_T1 		0
#define IB_TIMER_T2 		1
#define IB_TIMER_T3 		2
#define IB_TIMER_T4n 		3	/* used for timer_dur */
#define IB_TIMER_T5 		4
#define IB_TIMER_T6 		5
#define IB_TIMER_T7 		6
#define IB_TIMER_OCT		7
#define IB_TIMER_T4e 		8	/* used for timer_dur */
#define IB_NUM_TIMERS		10	/* number of timers in IBLOCK  */

/* the MTP2 module IBLOCK structure */
typedef struct init_block {
	unsigned short	timer_val[IB_NUM_TIMERS];/* timer values set by user*/
	unsigned short  SUERM_thresh;
	unsigned short  SUERM_err_rate;
	unsigned short	AERM_norm;
	unsigned short	AERM_emerg;
	unsigned short	M;		/* proving abort limit */
	unsigned short	m;		/* max frame length */
	unsigned short Tftimer;         /* TTC Tf FISU send interval */
	unsigned short Tstimer;         /* TTC Ts SIOS send interval */
	unsigned short Totimer;         /* TTC To SIO send interval */
	unsigned short Tatimer;         /* TTC Ta SIE send interval */
	unsigned short scaler;
	unsigned short scaler16;
} init_block_t;

typedef struct annex_a_init_block {
	unsigned int t8_timer;	/* T8 timer value */
	unsigned int Te;	/* Threshold count for ANNEX A ITU 96 */
	unsigned int Ue;	/* Up count for ANNEX A ITU 96 */
	unsigned int De;	/* Down count for ANNEX A ITU 96 */
} annex_a_init_block_t;
