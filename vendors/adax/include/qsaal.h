/*
 *		  Copyright Adax Inc. 1999-2003
 *		  All Rights Reserved
 *		  Use of this code is subject to your agreement with Adax, Inc.
 *
 *		@(#)qsaal.h	1.4 delta 04/01/28
 *
 */
#ifndef _ADAX_QSAAL_H
#define _ADAX_QSAAL_H

#ifdef __cpusplus
extern "C" {
#endif

#define LIO_NPARAM      (768+1) /* Set SSCF NNI parameters */
#define LIO_EMERGENCY   (768+2) /* Set emergency proving mode */
#define LIO_EM_CEASES   (768+3) /* Clear emergency proving mode */
#define LIO_GETSSTATE   (768+4) /* Get SSCF state (c_state, l_state, u_state) */
#define LIO_SET_MPS     (768+5) /* Set the preferred Management Proving State */
#define LIO_SET_LPO     (768+6) /* Set Local Processor Outage */
#define LIO_CLEAR_LPO   (768+7) /* Clear Local Processor Outage */
#define LIO_GNPARAM     (768+8) /* Get SSCF NNI parameters */
#define LIO_SSCF_SDBG   (768+9) /* Sets SSCF debug level */
#define LIO_GET_LRPO    (768+11)/* Gets Local and Remote PO information */
#define LIO_GLMFAULTS	(768+12)/* Get Table 4 ANSI LM faults and performance */

#define LIO_PARAM       514     /* Set SSCOP parameters */
#define LIO_BGN         515     /* Start SSCF link; Synonym for LIO_START */
#define LIO_START       515     /* Start SSCF link */
#define LIO_STOP        519     /* Stop SSCF link */
#define LIO_DISC        522	/* Disconnect SSCF-UNI (SSCOP) link; 
				 * Synonym for LIO_STOP for SSCF-NNI (SSCF) */
#define LIO_GETTQ       525     /* Retrieve msg from retransmit/transmit queue*/
#define LIO_STAT        526     /* Get stats I/O counts,errors V,W,X */
#define LIO_ZERO        527     /* Zero stats and error counts: V,W,X */
#define LIO_GPARAM      528     /* Get SSCOP params */
#define LIO_GETSTATE    529     /* Get SSCOP state, linkup, linkdown times */
#define LIO_EZERO       530     /* Zero SSCOP error counts: O,P,Q,R,S,T,U */
#define LIO_ESTAT       531     /* Return SSCOP error O,P,Q,R,S,T,U  counts */
#define LIO_BSNT        533	/* Retrieve N(S) of last SD PDU received */ 
#define LIO_GETTN       534     /* Get # of msgs on rexmit and xmit queues.*/
#define LIO_SETCVCTR    535     /* Set the 9-tuple of congestion thresholds */
#define LIO_GETCVCTR    536     /* Get the 9-tuple of congestion thresholds */
#define LIO_GETCVALS    537     /* Get current congestion values:txq,confq,sum*/
#define LIO_SSCOP_SDBG  538     /* Set SSCOP debug level */
#define LIO_PDU_COUNT   539     /* Get all SSCOP PDU counts */
#define LIO_RECVESUM    540     /* Get and optionally clear recv err summary */
#define LIO_FSNC        543     /* Update retransmit queue with last seq
                                 * received from remote, but not ACK'd */
#define LIO_GETCSB      544     /* Get SSCOP's MTP2-like "Status Buffer" */


/* SSCF-UNI ioctls */
#define LIO_RELEASE	518	/* Disconnect SSCF-UNI link. 
				 * Not used for SSCF-NNI */
#define LIO_ESTAB_RESP	516	/* AA-ESTABLISH.response for SSCF-UNI */


#define LIO_GFSNC       532     /* Depreciated.  Use LIO_FSNC ioctl instead.
				 * Return VT(S) - 1, e.g. N(S) of last SD tx'd*/
#define LIO_LSTIMES     541     /* Depreciated. Use LIO_GETSTATE ioctl instead.
				 * Get linkup and linkdown times, SSCOP state */
#define LIO_GTBSTATS    542     /* Depreciated. Use LIO_GETCSB ioctl instead. 
				 * Get transmit control variable stats; */
#define LIO_GLMSTATS    (768+10)/* Depreciated. Gets LM stats for congestion. */

/* Structure for LIO_PARAM and LIO_GPARAM */
typedef struct sscop_param {
	int send_max_pdu_size;
	int recv_max_pdu_size;
	int t_cc;		/* T_CC: BGN/END rep interval in milliseconds */
	int t_no_response;	/* T_NO_RESPONSE interval in milliseconds */
	int t_idle;		/* T_IDLE interval in milliseconds */
	int t_keep_alive;	/* T_KEEP_ALIVE interval in milliseconds */
	int t_poll;		/* T_POLL interval in milliseconds */
	int max_pd;		/* max PDUs between polls */
	int max_cc;		/* max Connection requests before error */
	int max_stat;		/* max number of terms in a STAT PDU */
	int default_mr;		/* default max receive window count */
	} SSCOP_PARAM;

/* Structure for the LIO_GETCSB ioctl */
typedef struct sscop_sb {
	unsigned int vt_s;      /* VT(S) - next seq to be sent */
	unsigned int vt_a;      /* VT(A) - next in-seq expected to be ack'd */
	unsigned int vt_pa;     /* VT(PA) - poll seq of next STAT to be ack'd */
	unsigned int vt_ms;     /* VT(MS) - max send seq+1 */
	unsigned int vt_ps;     /* VT(PS) - poll seq number */
	unsigned int vt_pd;     /* VT(PD) - max SDs sent before a poll */
	unsigned int vt_cc;     /* VT(CC) - max reqs to establish connection*/
	unsigned int vt_sq;     /* VT(SQ) */

	unsigned int vr_r;      /* VR(R) - next to be received */
	unsigned int vr_h;      /* VR(H) - highest to be received */
	unsigned int vr_mr;     /* VR(MR)- max advertised to be received */
	unsigned int vr_sq;     /* VR(SQ) */
	} SSCOP_SB;

/* Structure for the LIO_GETSTATE ioctl */
typedef struct sscop_getstate {
	int sscop_state;
	unsigned int linkup_time;
	unsigned int linkdown_time;
	} SSCOP_GETSTATE;

/* SSCOP state defines for sscop_state field in SSCOP_GETSTATE structure */
#define S_IDLE 1	/* Idle */
#define S_OUTCONP 2	/* Outgoing Connection Pending */
#define S_INCONP 3	/* Incoming Connection Pending */
#define S_OUTDISCP 4	/* Outgoing Disconnection Pending */
#define S_OUTRESYNP 5	/* Outgoing Resynchonization Pending */
#define S_INRESYNP 6	/* Incoming Resynchonization Pending */
#define S_OUTRECOVP 7	/* Outgoing Recovery Pending */
#define S_RECOVRESPP 8	/* Recovery Response Pending */
#define S_INRECOVP 9	/* Incoming Recovery Pending */
#define S_INFOTR 10	/* Data Transfer Ready */

/* Structure for the LIO_GETTN ioctl */
typedef struct sscop_gettn {
	unsigned int total_cnt;	/* cnt of frames on rexmit and xmit queues */
	unsigned int rtx_cnt;	/* cnt of frames on retransmit queue only */
	} SSCOP_GETTN;

/* Structure for LIO_STAT ioctl */
typedef struct sscop_stats {
	int error_v_count;
	int error_w_count;
	int error_x_count;	
	int sscop_state;	/* SSCOP state. See defines for LIO_GETSTATE */
	uint sdu_icount;	/* Count of received SD PDUs */
	uint sdu_ocount;	/* Count of sent SD PDUs */
	uint sdu_ibytes;	/* Count of received SD bytes */
	uint sdu_obytes;	/* Count of sent SD bytes */
	uint retrans_count;	/* Count of retransmitted SD PDUs */
	uint retrans_bytes;	/* Count of retransmitted SD bytes */
	uint pdu_icount;	/* Count of received PDUs */
	uint pdu_ibytes;	/* Count of received PDU bytes */
	uint pdu_ocount;	/* Count of sent PDUs (all types) */
	uint pdu_obytes;	/* Count of sent PDU bytes (all types) */
	} SSCOP_STATS;

/* Structure for the LIO_ESTAT ioctl */
typedef struct sscop_estats {
	int error_o_count;
	int error_p_count;
	int error_q_count;
	int error_r_count;
	int error_s_count;
	int error_t_count;
	int error_u_count;
	} SSCOP_ESTATS;

/* Structure for the LIO_PDU_COUNT ioctl */
typedef struct sscop_pdu_count {
	unsigned int bgn_ocount;         /* total BGNs sent  */
	unsigned int bgn_icount;         /* total BGNs recv'd */
	unsigned int bgak_ocount;        /* total BGAKs sent */
	unsigned int bgak_icount;        /* total BGAKs recv'd */
	unsigned int bgrej_ocount;       /* total BGREJs sent  */
	unsigned int bgrej_icount;       /* total BGREJs recv'd*/
	unsigned int rs_ocount;          /* total RSs sent  */
	unsigned int rs_icount;          /* total RSs recv'd  */
	unsigned int rsak_ocount;        /* total RSAKs sent  */
	unsigned int rsak_icount;        /* total RSAKs recv'd */
	unsigned int end_ocount;         /* total ENDs sent  */
	unsigned int end_icount;         /* total ENDs recv'd  */
	unsigned int endak_ocount;       /* total ENDAKs sent  */
	unsigned int endak_icount;       /* total ENDAKs recv'd*/
	unsigned int er_ocount;          /* total ERs sent  */
	unsigned int er_icount;          /* total ERs recv'd  */
	unsigned int erak_ocount;        /* total ERAKs sent  */
	unsigned int erak_icount;        /* total ERAKs recv'd */
	unsigned int poll_ocount;        /* total POLLs sent   */
	unsigned int poll_icount;        /* total POLLs recv'd */
	unsigned int stat_ocount;        /* total STATs sent   */
	unsigned int stat_icount;        /* total STATs recv'd */
	unsigned int ustat_ocount;       /* total USTATs sent  */
	unsigned int ustat_icount;       /* total USTATs recv'd*/
	unsigned int ud_ocount;          /* total UDs sent     */
	unsigned int ud_icount;          /* total UDs recv'd   */
	unsigned int md_ocount;          /* total MDs sent     */
	unsigned int md_icount;          /* total MDs recv'd   */
	unsigned int sdu_ocount;         /* total SDs sent     */
	unsigned int sdu_icount;         /* total SDs recv'd   */
	} SSCOP_PDU_COUNT;

/* Structure for LIO_RECVESUM ioctl */
typedef struct sscop_recvesum {
	uint unexp_count;	/* total unexpected PDUs recv'd count */
				/* these are MAA Errors A-M of GR-2878-CORE */
	uint inval_count;	/* total invalid PDUs recv'd count */
				/* these are MAA Error U of GR-2878-CORE */
	uint listerr_count;	/* total list-err, elements recv'd cnt */
				/* these are MAA Errors Q-T of GR-2878-CORE */
	} SSCOP_RECVESUM;

/* Structure for LIO_SETCVCTR, LIO_GETCVCTR */
typedef int cong_vect_t[9];     /* Congestion vector form */

/* Structure for the LIO_GETCVALS ioctl */
typedef struct sscop_getcvals {
	unsigned int txq_cong_idx;
	unsigned int rtxq_cong_idx;
	unsigned int total_cong_idx;
	} SSCOP_GETCVALS;

/* Structure for the LIO_GNPARAM and LIO_NPARAM ioctls */
typedef struct sscf_param {
        int t1;           /* SSCF: Timer T1 */
        int t2;           /* SSCF: Timer T2 */
        int t3;           /* SSCF: Timer T3 */
        int n1;           /* SSCF: Number of cells to transmit during proving */
        int j;            /* SSCF: UU field size */
        int p_thresh;     /* LM: Max NRP: Max # PDUs rexmit'd during proving */
        int t_no_credit;  /* LM: Timer NC: Maximum time with no credit. */
        int t_rep_srec;   /* LM: Timer RSREC: Min time between RECOVER events */
        int t_sup;        /* LM T_sup: Superblock Size in milliseconds */
        int t_loss;       /* LM T_loss: STAT loss limit in milliseconds */
        int t_tau;        /* LM tau: Error Monitoring interval */
        int iserm_n;      /* LM N: Intervals needed for Algorithm 1 */
        int iserm_nblk;   /* LM N_blk: Intervals in a block for Alg 2 */
        int iserm_thresh; /* LM thresh: Threshold for comparing running QOS */
        int iserm_alpha;  /* LM alpha: Exponential Smoothing Factor for Alg 2 */
	} SSCF_PARAM;


/* Structure for LIO_GLMFAULTS ioctl */
/* See Table 4 of LM standards, Signaling link faults and performance. */
typedef struct sscf_lmfaults {
	unsigned int sl_fail_all;	/* Total signaling link failures */
	unsigned int sl_fail_no_resp;	/* Failures due to no response. */
	unsigned int sl_fail_err_rate;	/* Failures due to excessive err rate */
	unsigned int sl_fail_cong;	/* Failures due to excessive cong time*/
	unsigned int sl_fail_align;	/* Alignment failures */
	unsigned int sl_error_v;	/* Num indications with Error SD Loss */
        unsigned int in_service_time;	/* start unix time of last in service */
        } SSCF_LMFAULTS;

/* Structure for the LIO_GET_LRPO ioctl */
typedef struct sscf_lrpo_info {  
	int lpo;	/* current state LPO: 1 true, 0 false */
	int lpo_cum;	/* cumulative LPO time - all previous LPOs */
	int rpo;	/* current state RPO: 1 true, 0 false */
	int rpo_cum;	/* cumulative RPO time - all previous RPOs */
	unsigned int lpo_time;/* time of current lpo (if true, zero otherwise)*/
	unsigned int rpo_time;/* time of current rpo (if true, zero otherwise)*/
	} SSCF_LRPO_INFO;

/* defines for LIO_SET_MPS ioctl */
#define MPS_NORMAL	0	/* Force Normal Proving */
#define MPS_EMERGENCY	1	/* Force Emergency Proving */
#define MPS_NEUTRAL	2	/* LM has neutral disposition */

/* LIO_GETSSTATE ioctl defines */
typedef struct sscf_getsstate {
	unsigned int combined_state;	/* Combined SSCF state */
	unsigned int lm_state;		/* Layer Management state */
	unsigned int ub_state;		/* Upper Boundary state */
	} SSCF_GETSSTATE;

/* Defines for 'combined_state' field of SSCF_GETSSTATE structure */
#define C_111   0       /* 1/1/1  Out of Service/Idle */
#define C_141   1       /* 1/4/1  Out of Service/Out-disconnection pending */
#define C_212   2       /* 2/1/2  Alignment/Idle */
#define C_222   3       /* 2/2/2  Alignment/Outgoing-connection pending */
#define C_242   4       /* 2/4/2  Alignment/Outgoing-disconnection pending */
#define C_3105  5       /* 3/10/5 In Service/Data transfer ready */
#define C_2103  6       /* 2/10/3 Proving/Data transfer ready */
#define C_2104  7       /* 2/10/4 Aligned ready/Data transfer ready */

/* Defines for 'lm_state' field of SSCF_GETSSTATE structure */
#define L_OUTOFSERVICE 1
#define L_ALIGNMENT 2
#define L_PROVING 3
#define L_ALIGNREADY 4
#define L_INSERVICE 5

/* Defines for 'ub_state' field of SSCF_GETSSTATE structure */
#define U_OUTOFSERVICE 1
#define U_ALIGNMENT 2
#define U_INSERVICE 3


/* Defines for SSCF indications to MTP3 */
#define SSCF_CTL_MSG_IND  0x50

typedef struct sscf_ind_t {
	unsigned int sscf_ind;	/* Always constant SSCF_CTL_MSG_IND (0x50) */
	unsigned int ind_type;	/* One of the indication types below */
	unsigned int opt_param; /* Optional parameter sent with 
				 * AAL_OUT_OF_SERVICE_IND or undefined */
} SSCF_IND;

#define AAL_IN_SERVICE_IND      50      /* In Service Indication */
#define AAL_OUT_OF_SERVICE_IND  51      /* Out of Service Indication */
#define AAL_PROVING_IND         59      /* proving started */
#define AAL_STOP_PROVING_IND    60      /* proving done - waiting for INS */
/* These indicatations are deprecated and are not sent by SSCF/LM */
#define AAL_CONGEST_IND         52
#define AAL_CONGEST_CEASED_IND  53
#define AAL_RETRIEVAL_COMP_IND  54
#define AAL_RETRIEVED_MSGS_IND  55
#define AAL_BSNT_CONF           56
#define AAL_BSNT_NOT_RETR_CONF  57
#define AAL_PROVING_UNS         58

/* Additional parameters sent with AAL_OUT_OF_SERVICE_IND indications */
#define ANS             7       /* alignment not successful */
#define T_NCRED         101     /* T_NO_CREDIT expiry */
#define E_ISERM         102     /* ISERM OOS */

#define AAL_OUT_OF_SERVICE_REASON_STR(s)           \
   (((s) == ANS) ?     "ALIGNMENT UNSUCCESSFUL" :  \
    ((s) == T_NCRED) ? "T_NO_CREDIT EXPIRY" :      \
    ((s) == E_ISERM) ? "SERM REACED" :             \
                       "OTHER/INVALID") 

/* SSCOP codes used to communicate with SSCS (layer above SSCOP) */
#define AA_ESTABLISH_REQ	1
#define AA_ESTABLISH_IND	2
#define AA_ESTABLISH_RSP	3
#define AA_ESTABLISH_CONF	4

#define AA_RELEASE_REQ		5
#define AA_RELEASE_IND		6
#define AA_RELEASE_CONF		7

#define AA_DATA_REQ		8
#define AA_DATA_IND		9

#define AA_RESYNC_REQ		10
#define AA_RESYNC_IND		11
#define AA_RESYNC_RSP		12
#define AA_RESYNC_CONF		13

#define AA_ERROR_IND		14

#define AA_UNIT_DATA_REQ	15
#define AA_UNIT_DATA_IND	16

#define AA_RETRIEVE_REQ		17
#define AA_RETRIEVE_IND		18
#define AA_RETRIEVE_CONF	19

#define AA_RELEASEBUF_REQ	20

#define AA_RECOVERY_IND		21
#define AA_RECOVERY_RSP		22

#define MAA_ERROR_IND		23
#define MAA_UNIT_DATA_REQ	24
#define MAA_UNIT_DATA_IND	25
#define MAA_UNIT_DATA_RSP	26
#define MAA_UNIT_DATA_CONF	27

#define SSCS_IND	64	/* Deprecated definition for SSCOP ctl msgs */
#define SSAAL_IND	80	/* Deprecated synonym for SSCF_CTL_MSG_IND */

/* Error codes used in MAA Error messages */
#define ERROR_A         1
#define ERROR_B         2
#define ERROR_C         3
#define ERROR_D         4
#define ERROR_E         5
#define ERROR_F         6
#define ERROR_G         7
#define ERROR_H         8
#define ERROR_I         9
#define ERROR_J         10
#define ERROR_K         11
#define ERROR_L         12
#define ERROR_M         13      
#define ERROR_N         14
#define ERROR_O         15 
#define ERROR_P         16      /* Timer NO_RESPONSE expired - downs the link */
#define ERROR_Q         17      /* Erroneous SD,POLL,etc. PDU from peer */
#define ERROR_R         18      /* Erroneous STAT.NPS  */ 
#define ERROR_S         19      /* STAT NR or other info was out of range */
#define ERROR_T         20      /* USTAT NR, seq1, or seq2 was out of range */
#define ERROR_U         21
#define ERROR_V         22      /* Lost PDUs Retransmitted with 'count' */
#define ERROR_W         23      /* new: Window NO  CREDIT Indication */ 
#define ERROR_X         24      /* new: Window YES CREDIT Indication */
#define ERROR_Y         25      /* not defined */
#define ERROR_Z         26      /* not defined */



/* Structure for deprecated LIO_GTBSTATS ioctl */
/* Use the LIO_GETCSB ioctl.  The SSCOP_SB structure includes all
 * of this information */
typedef struct sscf_gtbstats {
	int vt_s;  /* transmit sequence number */
	int vt_a;  /* transmit lower ack number (last NR received) */
	int vt_mr; /* transmit max send seq number (last NMR received) */
	} SSCF_GTBSTATS;

/* Structure for deprecated LIO_GLMSTATS ioctl */
/* Should be named SSCOP_LMSTATS, because this retrieves info from SSCOP
 * but we cannot change name in order to preserve compatibility with existing
 * customers. */
typedef struct sscf_lmstats {
        int sl_align_fails;	/* count of failures to align link */
        int no_cred_events;	/* count of events */
        int cum_no_cred_time;	/* sum of time */
        time_t in_service_time;/* time of last in service (start of which) */
        } SSCF_LMSTATS;

/* Structure for deprecated LIO_LSTIMES ioctl */
/* Use the LIO_GETSTATE ioctl which contains this same infomation */
typedef struct sscop_lstimes {
	time_t linkup_time;
	time_t linkdown_time;
	int sscop_state;
	} SSCOP_LSTIMES;

#ifdef __cpusplus
};
#endif

#endif	/* ifndef _ADAX_QSAAL_H */
