/*
 * Copyright 2002-2004 ADAX, Inc.
 *      Use of this code is subject to your agreement with ADAX, Inc.
 */


/* ver[] = @(#)atmii_user.h	1.5 delta 05/03/22 */

#ifdef	__cplusplus
extern "C" {
#endif

#define CTL_PORT_REQ 0x80000000
#define HDLC_PORT_REQ 0x20000000
#define AAL2_PORT_REQ 0x10000000
#define AAL5_PORT_REQ 0x00000000
#define AAL0_PORT_REQ 0x00000000

#define MAX_HDLC_FRAME 4224
#define MAX_AAL5_FRAME 4224
#define MAX_AAL2_FRAME 64
#define MAX_AAL0_FRAME 52

#define NPORTS 8	/* don't change this.. */

/* recommended value for the switch service  */
#define SW_TX_QSIZE	80    /* MAX_AAL5_FRAME/53 recommended Tx queue size for switch service */
#define SW_EPD_THD	255 /* recommended EPD threshold for switch service */

#define AIOCSTAT 	1	/* Get daughter card modem status */
#define	AIOCDIVERT 	21	/* Divert received data to control port */

#define	AIOCCCOUNTS 	22	/* ACT/HDC compatible stats */
#define	AIOCCZERO 	23	/* Zero ACT/HDC compatible stats */
#define AIOCLOOPBK      25	/* Set loopback mode */
#define AIOCBITS 	29	/* Write data to daughter card */
#define AIOCSBITDLY 	30	/* set delay for above routine */

#define	AIOCBCOUNTS 	31	/* per board counts */
#define	AIOCSCOUNTS 	32	/* per stream counts */
#define	AIOCVCOUNTS 	33	/* per VC counts */

#define	AIOCBZERO 	34	/* Zero per board counts */
#define	AIOCSZERO 	35	/* Zero per stream counts */
#define	AIOCVZERO 	36	/* Zero per VC counts */

#define	AIOCDEBUG 	40	/* Alter debug level */

#define AIOCSETVC	53	/* bind a vpi/vci to an ATM stream */
#define AIOCSETTTS	53	/* Bind a timeslot mask to a HDLC stream */
#define AIOCSETPORT 	58	/* Set the port for an ATMII user clone open */
#define	AIOCFNDSLT 	61	/* a synonym for AIOCFNDSVC */
#define	AIOCFNDSVC 	61	/* find physical VC for ctl VC */

#define AIOCTIMSTAMP 	65	/* toggle frame timestamping */
#define AIOCSTIMR 	66	/* set timr for min ISR interval */
#define AIOCSETQ  	69	/* Change High/Low water marks of 
				 * stream head read queue */
#define AIOCGETALRM	90	/* Get trunk alarm status */
#define AIOCSETALRM	91	/* Set trunk alarm status */
#define AIOCSETSCRAMB	92	/* Set/Clear Payload scrambling */

#define AIOCRAMLR 200  /* RAM LWORD read    All of these have first lword as */
#define AIOCRAMLW 201  /* RAM LWORD write   offset from ATMIIs-PCI start */
#define AIOCRAMSR 202  /* RAM 16-bit read   and transfer the remaining data. */
#define AIOCRAMSW 203  /* RAM 16-bit write  Reads return data at buffer start */
#define AIOCIOLR 204   /* IO LWORD write */
#define AIOCIOLW 205   /* IO LWORD read */
#define AIOCGIOCR 206	/* GENIO char read */
#define AIOCGIOCW 207	/* GENIO char write */

#define AIOCGVERR 240   /* Get the board Version Register */
 
#define AIOCGJTAG 247   /* Get the JTAG programming register */
#define AIOCSJTAG 248   /* Set the JTAG programming register */
#define AIOCSSLED 249   /* Set the Status RED/GREEN LED:D0 is Green,D1 is Red */
#define AIOCGSTPROG 251 /* Get ST flash programming register */
#define AIOCSSTPROG 252 /* Set ST flash programming register */
#define AIOCBER1  271	/* Sets a Bit Error Rate of 1 for n ms (debugging) */

/* ATMII ioctls */
#define ATM2 ('A'<<24)
#define AIOCCFGFMWK	(ATM2|1)	/* Only for use by atmiid */
#define AIOCGETINDQ	(ATM2|2)	/* get indication queue */
#define AIOCGETCMDQ	(ATM2|3)	/* get command queue */
#define AIOCGETHB	(ATM2|4)	/* get host block */
#define AIOCGETEB	(ATM2|5)	/* get EM block */
#define AIOCGETINPOOL	(ATM2|6)	/* get inpool */
#define AIOCGETOUTPOOL	(ATM2|7)	/* get outpool */
#define AIOCCFGINTR	(ATM2|8)	/* Only for use by atmiid */
#define AIOCPHYSTATUS   (ATM2|9)	/* PHY registers for use by atmiitest */
#define AIOCEMPCOUNTS   (ATM2|10)	/* per port statistics */
#define AIOCEMPCNTZERO  (ATM2|11)	/* zero per port statistics */
#define AIOCCFGAAL2	(ATM2|12)	/* Only for use by atmiitest */
#define AIOCSETSUBC	(ATM2|13)	/* Bind a CPS subchannel to an AAL2 VC*/
#define AIOCGETTXB	(ATM2|14)	/* ZZZ for debugging.. */
#define AIOCGETRXB	(ATM2|15)	/* ZZZ for debugging.. */
#define AIOCALRMIND	(ATM2|16)	/* Enable trunk alarm indications */
#define AIOCSUBCOUNTS	(ATM2|17)	/* get AAL2 subchannel stats */
#define AIOCSUBZERO	(ATM2|18)	/* zero AAL2 subchannel stats */
#define AIOCGPTYPE	(ATM2|19)	/* Get physical port type (OC3/T1/E1) */
#define AIOCSETBULK     (ATM2|20)       /* configure the AAL0 bulk mode */
#define AIOCSETCLK	(ATM2|21)	/* Set port clock opts (ATMII-PMC-OC3)*/
#define AIOCSETCLKREF	(ATM2|22)	/* Set board ref clk on ATMII-OC3-PMC */
#define AIOCGETCLKREF	(ATM2|23)	/* Get board ref clk info */
#define AIOCCLKIND	(ATM2|24)	/* Control clock count indications */
#define AIOCPHYCOUNTS	(ATM2|25)       /* Get counters from OC3 PHY */
#define AIOCSETPHYMODE	(ATM2|26)   	/* Set ATMII-OC3 STM1/OC3/SONET mode */

/* This symbol must be defined if code has been written
 * for the ATMX driver but is now compiled with this header file 
 */
#ifdef ATMX_COMPATABLE

#define AIOCSUPERMUX	2	/* set stream to use multiplexing mode */
#define AIOCTIMR  	6	/* Initialize counter/timer with given value */
#define AIOCGETRT 	9	/* get the Receive Table */
#define AIOCGETTT 	10	/* get the Transmit Table */
#define AIOCCSTOP 	14	/* Stop stream */
#define AIOCTRANS 	16	/* Initialize in Transparent mode */
#define AIOCSETDESC	17	/* set the number of descriptors set on strm */
#define AIOCGETDESC	18	/* get the number of descriptors set on strm */
#define AIOCGETDESCFREE	19	/* get the number of descriptors free */
#define AIOCHRESET	47	/* Reset hardware to known state */
#define AIOC7HRESET	47	/* Synonym for AIOCHRESET */
#define AIOCGETCURD 	59	/* Get the current RX descriptor */
#define AIOCGETCUTD 	60	/* Get the current TX descriptor */
#define AIOCGETID 	63	/* get pci device and vender id.  (debugging) */
#define AIOCRIQDMP 	70	/* dump receive interrupt queue */
#define AIOCTIQDMP 	71	/* dump transmit interrupt queue */
#define AIOCREGDMP 	72	/* dump all siemens registers */
#define AIOCLSSU   	73	/* transmit 3 or 4 byte frame continuously */
#define AIOCSETPROTO	74	/* set channel to run mtp2 */
#define AIOCGETURT	75	/* get upper receive descriptor table */
#define AIOCGETUTT	76	/* get upper transmit descriptor table */
#define AIOCMVIP	80	/* H.100/MVIP control (ATM-cPCI only) */
#define AIOCSTRMDMP	81	/* dump board ATMX_SA_CHAN struct */
#define AIOCGETCRSH	84	/* get crash results from abort handler */
#define AIOCSTACKDMP	85	/* dump processor stack */
/* 86 is reserved for TRACEDMP */
#define AIOCPRINTDMP	87	/* dump printf buffer */
#define AIOCTXCQDMP	88	/* dump command queue to board */
#define AIOCRXCQDMP	89	/* dump command queue to HOST */
#define AIOCSETWATCHDOG 93	/* Enable watchdog/Set watchdog alarm type */

#define AIOCSETSWITCH   106     /* set and initialize the soft switch mode */
#define AIOCSWCOUNTS    107     /* get the statistics of Software Switch */
#define AIOCSWZERO      108     /* Reset the statistics of Software Switch */
#define AIOCSWMETHODSET 109     /* Modify the cell process method */


#define AIOCKICKDOG     270	/* Start/stop sending watchdog msgs to board to
				 * test watchdog alarm */
#define AIOCSHSCR 241   /* Set the Hot Swap Control Register */
#define AIOCGHSCR 242   /* Get the Hot Swap Control Register */
 
#define AIOCGPMEM 243   /* Get the current PCI bus memory addr (use for swap) */
#define AIOCSPMEM 244   /* Set the current PCI bus memory addr (use for swap) */
#define AIOCDPMEM 245   /* Disable PCI bus memory address (use for swap) */
#define AIOCEPMEM 246   /* Enable  PCI bus memory address (use for swap) */

#define SAIO ('S'<<24)	/* ATMX Processor Bound ioctl */
#define ETIO ('E'<<24)	/* ATMX Ethernet port ioctl */

#define ETIOSETPORT	(ETIO|AIOCSETPORT)	/* set ethernet port */
#define ETIOTRANS	(ETIO|AIOCTRANS)	/* start Rx side of eth port */
#define ETIOGETRT	(ETIO|AIOCGETRT)	/* get ethernet RT */
#define ETIOGETTT	(ETIO|AIOCGETTT)	/* get ethernet TT */
#define ETIOGETCUTD	(ETIO|AIOCGETCUTD)	/* get current TD */
#define ETIOGETCURD	(ETIO|AIOCGETCURD)	/* get current RD */
#define ETIOCCOUNTS	(ETIO|AIOCCCOUNTS)	/* get ethernet stats */
#define ETIOCZERO	(ETIO|AIOCCZERO)	/* zero ethernet stats */
#define ETIOSTAT	(ETIO|AIOCSTAT)		/* Get SCB status from 82559 */

#define HDIO ('H'<<16)	/* Stream head ioctl */
#define DRIO ('D'<<16)	/* atmx board level driver ioctl */

#define SAIOPSHMOD	(SAIO|HDIO|1)	/* push protocol module onto a stream*/
#define SAIOPOPMOD	(SAIO|HDIO|2)	/* pop a protocol module onto a stream*/
#define SAIOCLOSE	(SAIO|HDIO|3)	/* close a stream (don't dismantle...)*/

#define SAIOMEMFREE	(SAIO|DRIO|100)	/* reports mblks/dblks/mbuffs utilized*/
#define SAIOQUEUE	(SAIO|DRIO|101)	/* dump queue structure by index */
#define SAIOMBLK	(SAIO|DRIO|102)	/* finds first alloc'd mblk from index*/
#define SAIOMBLKDMP	(SAIO|DRIO|103)	/* dumps mblk by address or index */
#define SAIOTEST3	(SAIO|DRIO|104)	/* print list of alloc'd mblks*/
#define SAIOSUNMAPDISP	(SAIO|DRIO|105)	/* set unmapped cell disposition */
#define SAIOSETRTE	(SAIO|DRIO|106)	/* write a routing table entry in RCTL*/
#define SAIOGETRTETBL	(SAIO|DRIO|107)	/* return RCTL routing table */
#define SAIOALRMIND	(SAIO|DRIO|108)	/* setup for receiving alarm ind. */

#define SAIOSUPERMUX	(SAIO|DRIO|AIOCSUPERMUX)/* set multiplexed stream mode*/
#define SAIOSETVC	(SAIO|DRIO|AIOCSETVC)/* set multiplexed stream mode*/
#define SAIOSETDESC	(SAIO|DRIO|AIOCSETDESC)	/* set num desc for strm */
#define SAIOBCOUNTS	(SAIO|DRIO|AIOCBCOUNTS)	/* return board stats */
#define SAIOSCOUNTS	(SAIO|DRIO|AIOCSCOUNTS)	/* return stream stats */
#define SAIOVCOUNTS	(SAIO|DRIO|AIOCVCOUNTS)	/* return VC stats */
#define SAIOBZERO	(SAIO|DRIO|AIOCBZERO)	/* zero board stats */
#define SAIOSZERO	(SAIO|DRIO|AIOCSZERO)	/* zero stream stats */
#define SAIOVZERO	(SAIO|DRIO|AIOCVZERO)	/* zero VC stats */
#define SAIOGETCURD	(SAIO|DRIO|AIOCGETCURD)	/* get current rx desc */
#define SAIOGETCUTD	(SAIO|DRIO|AIOCGETCUTD)	/* get current tx desc */
#define SAIOSTRMDMP	(SAIO|DRIO|AIOCSTRMDMP) /* dump ATMX_SA_CHAN struct */

/* Structs and defines for AIOCMVIP  */
typedef struct
	{
	unsigned int trunk;
	unsigned int starting_slot;
	unsigned int ending_slot;
	} MVIP_CMD;

/* defines for the MVIP_CMD struct */

/* These defines set the mode for the H.110 bus controller */
#define MVIP_H110_CTL 	 0xC0000000
#define H110_DISABLE	 0x00000000 /* Disconnect ATM-cPCI from H.110 bus */
#define H110_MASTER	 0x00000010 /* Become H.110 bus timing master */
#define H110_SLAVE_NOQCX 0x00000020 /* Become H.110 bus timing slave w/no QCX */
#define H110_SLAVE_QCX 	 0x00000030 /* Become H.110 bus timing slave w/QCX */
#define H110_CLOCK_A	 0x00000000 /* Drive H.110 clock set 'A' */
#define H110_CLOCK_B	 0x00000008 /* Drive H.110 clock set 'B' */
#define H110_TRUNK_MASK	 0x00001F00

/* This define is used to turn on mappings between
 * ports and TDM data streams */
#define MVIP_CTL 		0x80000000

/* This define is used to turn off mappings between
 * ports and TDM data streams */
#define MVIP_DISABLE_CTL	0x00000000

#define MVIP_TRUNK_MASK		0x00001F00
#define MVIP_SUBTRUNK_MASK	0x00000003

/* This define is set in the 'ending_slot' field of the MVIP_CMD
 * struct with MVIP_CTL to set up an external loopback
 * on a trunk when the H.110 controller is in H110_DISABLE mode
 */
#define MVIP_LOOPBACK		0x00000020

/* ATMX compatible T1/E1 Alarm types */
#define ALRM_T1E1_NONE	  0x00000001	/* No alarm/ Alarm cleared */
#define ALRM_T1E1_TRANS   0x00000121    /* Transitional alarm.  Ignore this. */
#define ALRM_T1E1_BLULOS  0x00004121	/* Blue or LOS alarm on trunk */
#define ALRM_T1E1_YELRAI  0x00004001	/* Yellow (T1) or RAI (E1) alarm */

#endif /* ATMX compatible ioctl definitions */



#define CLP_BIT		0x1/* CLP bit set (ind) or set CLP bit (req)*/
#define CRC10_BIT	0x2/* CRC-10 error (ind) or insert CRC-10 (req) */
#define CI_BIT		0x4/* CI bit set (ind) or set CI bit (req)*/

#define AAL5_UNITDATA_REQ 0x0	/* Regular data request.  Required for AAL2 */

typedef struct aal0_bulk_cfg {
        unsigned char enable;    /* enable/disable AAL0 bulk mode */
        unsigned char threshold; /* receive threshold (cells) */
        unsigned short timeintl;  /* time interval */
}aal0_bulk_cfg_t;


typedef struct aal5_unitdata_req {
	unsigned int prim;	/* Always AAL_UNITDATA_REQ */
	unsigned int vc_key;	/* Value returned from AIOCSETVC */
	unsigned int ci_clp;	/* or of CLP_BIT, CI_BIT to set these bits */
	unsigned int cs_uui;	/* CPS-UUI field to send with data */
	unsigned int cos;	/* Class of service from 0 to 3 (0 is highest)*/
	unsigned int len;	/* length of frame in data part */
} aal5_unitdata_req_t;

/* For AAL5 AAL5_UNITDATA_IND is implicit.  All data is sent to user space
 * in M_DATA currently. */
#define AAL5_UNITDATA_IND 0x80	/* AAL5 data indication. */

typedef struct aal5_unitdata_ind {
	unsigned int prim;	/* Always AAL5_UNITDATA_IND */
	unsigned int vc_key;	/* Value returned from AIOCSETVC */
	unsigned int ci_clp;	/* or of CLP_BIT, CI_BIT bits set in PDU */
	unsigned int cs_uui;	/* CS-UUI field received with data */
	unsigned int cpi;	/* Common Part Indicator from AAL5 trailer */
	unsigned int timestamp;	/* timestamp in usec if AIOCTIMSTAMP */
	unsigned int len;	/* length of frame in data part */
} aal5_unitdata_ind_t;

/* AAL2 multiplexed chans ctl part.
 * 'vc_key' is the value returned from AIOCSETVC. */
#define CPS_UNITDATA_REQ 0x0	/* AAL2 CPS unitdata request. */

typedef struct cps_unitdata_req {
	unsigned int prim;	/* Always CPS_UNITDATA_REQ */
	unsigned int vc_key;	/* Value returned from AIOCSETVC */
	unsigned int cps_cid;	/* CPS_CID to send data on */
	unsigned int sscs_uui;	/* SSCS_UUI field to send with data */
	unsigned int cos;	/* Class of service from 0 to 3 (0 is highest)*/
	unsigned int len;	/* length of frame in data part */
} cps_unitdata_req_t;

/* AAL2 multiplexed chans ctl part.
 * 'vc_key' is the value returned from AIOCSETVC. */
#define CPS_UNITDATA_IND 0x80	/* AAL2 CPS unitdata indication. */

typedef struct cps_unitdata_ind {
	unsigned int prim;	/* Always CPS_UNITDATA_IND */
	unsigned int vc_key;	/* Value returned from AIOCSETVC */
	unsigned int cps_cid;	/* CPS_CID data was recevied on */
	unsigned int sscs_uui;	/* SSCS_UUI field received from data */
	unsigned int timestamp;	/* timestamp in usec if AIOCTIMSTAMP */
	unsigned int len;	/* length of frame in data part */
} cps_unitdata_ind_t;

/* All protocols ctl part.
 * 'vc_key' is the value returned from AIOCSETVC. */
#define ATM_RAWDATA_REQ	0x1	/* Raw cell or RAW cell request */
#define MAX_BULK_CELL_NUM 34	/* the maximum number of cell per bulk packet */

typedef struct atm_rawdata_req {
	unsigned int prim;	/* Always ATM_RAWDATA_REQ */
	unsigned int vc_key;	/* Value returned from AIOCSETVC */
	unsigned int crc10_ins;	/* CRC10_BIT=chip will insert CRC-10, 
				 * 0=CRC-10 is specified in data */
	unsigned int cos;	/* Class of service from 0 to 3 (0 is highest)*/
	unsigned int len;	/* length of frame in data part */
} atm_rawdata_req_t;

/* All protocols ctl part.
 * 'vc_key' is the value returned from AIOCSETVC. */
#define ATM_RAWDATA_IND	0x81	/* Raw cell or RAW cell indication */

typedef struct atm_rawdata_ind {
	unsigned int prim;	/* Always ATM_RAWDATA_IND */
	unsigned int vc_key;	/* Value returned from AIOCSETVC */
	unsigned int ctl;	/* CLP_BIT,CRC10_BIT,and CI_BIT if set in cell*/
	unsigned int timestamp;	/* timestamp in usec if AIOCTIMSTAMP */
	unsigned int len;	/* length of frame */
} atm_rawdata_ind_t;

#define ATM_CLKCNT_IND	0x82
typedef struct atm_clkcnt_ind {
	unsigned int prim;	/* Always ATM_CLKCNT_IND */
	unsigned int phy_los;	/* Set to 1 if one of the PHYs is the board
				 * clock reference and that PHY has lost it's 
				 * signal so the on-board OSC is being used. */
	unsigned int clk_count;	/* Total count of the number of board reference
				 * clock ticks */
} atm_clkcnt_ind_t;

union atmii_ctl_primitives {
	unsigned int prim;
	aal5_unitdata_req_t aal5_unitdata_req;
	aal5_unitdata_ind_t aal5_unitdata_ind;
	cps_unitdata_req_t cps_unitdata_req;
	cps_unitdata_ind_t cps_unitdata_ind;
	atm_rawdata_req_t atm_rawdata_req;
	atm_rawdata_ind_t atm_rawdata_ind;
	atm_clkcnt_ind_t  atm_clkcnt_ind;
};

/* structs for AIOCSETVC */
/* These are set up by the atmii_create_XXXX_setvc_opts() function
 * in atmii_user.c, if needed */
typedef struct aal2_opts {
	unsigned int cutim_shappri;
	unsigned int pcr;
	unsigned int scr;
	unsigned int mbs;
	unsigned int reserved0;
	unsigned int reserved1;
	unsigned int raw_subc_class;
} aal2_opts_t;

typedef struct aal5_opts {
	unsigned int pcr;
	unsigned int mcr_scr;
	unsigned int mbs;
	unsigned int icr;
	unsigned int rdf_rif_cdf;
	unsigned int maxSDU_aal_pri_traf;
	unsigned int buffer_class;
} aal5_opts_t;

typedef struct aal0_opts {
	unsigned int pcr;
	unsigned int mcr_scr;
	unsigned int mbs;
	unsigned int icr;
	unsigned int rdf_rif_cdf;
	unsigned int maxSDU_aal_pri_traf;
	unsigned int buffer_class;
} aal0_opts_t;

typedef struct hdlc_opts {
	unsigned int max_packet_size;
	unsigned int buffer_class;
} hdlc_opts_t;

typedef struct atmii_setvc_opts {
	unsigned int vpi_vci;	/* VPI/VCI in little endian format */
	unsigned int reserved;	/* reserved. must be set to 0 */
	union 
		{
		aal2_opts_t aal2cfg;
		aal5_opts_t aal5cfg;
		aal0_opts_t aal0cfg;
		} cfg;
} atmii_setvc_opts_t;

/* struct for AIOCSETSWITCH */
typedef struct switch_opts {
        unsigned int src_atm_hdr;
        unsigned int dst_atm_hdr;
        unsigned short src_port_id;
        unsigned short dst_port_id;
        unsigned int a5_srv_pri_oam_buf;        /* AAL5, service, Prioriety,OAM,Buffer */
        unsigned short pcr;
        unsigned short pcr_limit;       /* CDVT=pcr_limit/pcr */
        unsigned short scr;
        unsigned short scr_limit;
        unsigned short tx_queue_size;
        unsigned short epd_thd;
        unsigned short efci_thd;
        unsigned short clp_thd;
        unsigned int reserve0;
} switch_opts_t;

typedef struct switch_process_param{
        unsigned char usr_modified; /* if the user cell process method is modified */
        unsigned char usr_cell_method; /* method to process the user cell */
        unsigned char oam_modified; /* if the oam cell process method is modified */
        unsigned char oam_cell_method; /* method to process the oam cell */
	unsigned int rsv[2];
}switch_process_param_t;



typedef struct atmii_setswitch_opts {
        unsigned int shape_policing; /*size of int, reserved the space for extension.*/
        switch_opts_t cfg;
} atmii_setswitch_opts_t;


/* struct for AIOCSETTTS */
typedef struct atmii_setts_opts {
	unsigned int ds0set;	/* timeslots to use for this connection */
	unsigned int fill_mask;	/* determines 64K (0xff) or 56K (0xfe) ds0s */
	unsigned int data_inv;	/* 1 if data is to be inverted, 0 if not */
	hdlc_opts_t cfg;
} atmii_setts_opts_t;

/* struct for AIOCSETSUBC */
typedef struct atmii_setsubc_opts {
	unsigned int vc_key;		/* VC key returned from AIOCSETVC */
	unsigned short cps_cid;		/* CPS-CID of channel */
	unsigned short dflt_uui;	/* default UUI of subchan. */
	unsigned int max_sdu_len;	/* Max SDU len. 45 or 64 bytes only */
	unsigned int rsvd1;		/* for future use, set to 0. */
	unsigned int rsvd2;		/* for future use, set to 0. */
} atmii_setsubc_opts_t;

/* flags for setting loopback mode with AIOCLOOPBK */
#define LOOP_OFF 	0x0	/* turn off loop back mode(regardless of type)*/
#define LOOP_COMPI	0x1	/* Turn on internal loopback */
#define LOOP_COMPE	0x2	/* Turn on external loopback */
#define LOOP_COMPI_FIBER 0x4	/* Turn on internal loopback at 
				 * fiber interface (OC-3c only) */

/* defines for AIOCGETALRM or DLP_ALRM_IND */
/* If the AIOCALRMIND ioctl enables alarm indications, 
 * then a DLP_ALRM_IND indication will be received as a M_PROTO
 * message when there is a change in alarm status and the
 * alarm is stable for the debouncing period
 */
#define DLP_ALRM_IND	0xf0000003  /* alarm status change indication */

/* OC-3 ONLY alarm types */
#define ALRM_LINE_FEBE	0x00008000 /* Line Far-End Block Error 
				    * (nonzero (1-24) M1 octet) */
#define ALRM_CD		0x00004000 /* Missing Carrier Detect from PHY
				    * (only in current alarm status word) */
#define ALRM_PATH_LMIS	0x00002000 /* Signal Label Mismatch. (C2 != 0x13 for 7
				    * consecutive frames) */
#define ALRM_PATH_FERF	0x00001000 /* Path Far-End Recv Failure 
                                    * (G1 upper nibble == 9).  The ATMII-OC3
				    * cannot detect these. */
#define ALRM_PATH_FEBE	0x00000800 /* Path Far-End Block Error 
				    * (G1 upper nibble = 1-8) */
#define ALRM_BIP_ERROR  0x00000400 /* BIP error.
				    * (Error in any of B1, B2, or B3)*/
#define ALRM_LINE_FERF	0x00000200 /* Line Far-End Recv Failure 
				    * (K2 & 0x7) == 6 for 5 consec. frames */
#define ALRM_LOSS_CD	0x00000100 /* Loss of Cell Delination.  
				    * 7 consecutive HEC errors */
#define ALRM_STS_LOF3	0x00000080 /* Loss of Framing (3 seconds)
				    * Set if LOF for 3 consecutive seconds */
#define ALRM_STS_LOF	0x00000040 /* Loss of Framing.  Set if Out of Framing 
				    * (OOF) for 24 consecutive frames */
#define ALRM_STS_OOF	0x00000020 /* Out of Framing.  Set if 4 consecutive
				    * errored A1/A2 paterns are observed. */
#define ALRM_PATH_YEL_P	0x00000010 /* Path Yellow alarm.  Remote Defect.
				    * (G1 bits 5,6,7 == '100) */
#define ALRM_PATH_YEL_EPP 0x00010010 /* Path Yellow alarm.  Payload Defect.
				      * (G1 bits 5,6,7 == '010) */
#define ALRM_PATH_YEL_EPS 0x00020010 /* Path Yellow alarm.  Server Defect.
				      * (G1 bits 5,6,7 == '101) */
#define ALRM_PATH_YEL_EPC 0x00030010 /* Path Yellow alarm.  Connectivity Defect.
				      * (G1 bits 5,6,7 == '110) */
#define ALRM_PATH_AIS	0x00000008 /* Path Alarm Indication Signal.
				    * H1 and H2 are all 1's in 3 consec frames*/
#define ALRM_LINE_AIS	0x00000004 /* Line Alarm Indication Signal. Set if 3 
				    * LSB of K2 are '111 for 3 consec. frames*/
#define ALRM_STS_LOP	0x00000002 /* Loss of Pointer. Set if valid pointer 
				    * cannot be found in H1/H2 bytes */
#define ALRM_LOS	0x00000001 /* Loss of Signal from PHY */
#define ALRM_PATH_YEL_MASK 0x00030010 /* Mask to determine type of 
				       * Yellow alarm */

/* ATMII T1/E1 alarm types */
#define ALRM_T1E1_NONE	  0x00000001 /* No alarm/ Alarm cleared */
#define ALRM_T1E1_ALRM	  0x00004121 /* an alarm is set, check with 
				      * anc_command() */

/* defines for setting OC-3c/STS-3c/STM-1 alarms with AIOCSETALRM */
#define SET_LINE_AIS	0x00000010
#define SET_LINE_FERF	0x00000020
#define SET_PATH_YEL	0x00000040
#define SET_PATH_FERF	0x00000080
#define SET_PATH_AIS	0x00000100

/* defines for AIOCSETPHYMODE */
#define PHY_SONET	0x0	/* Set PHY to SONET mode, H1/H2 bytes = 62/0A */
#define PHY_STM1	0x1	/* Set PHY to STM-1 mode, H1/H2 bytes = 6A/0A */
#define PHY_OC3		0x2	/* Set PHY to OC-3 mode, H1/H2 bytes = 33/33 */

/* flags returned from AIOCSTAT */
#ifdef M_ERR
#undef M_ERR
#define M_ERR      0x0020	/* Modem error (no CD from daughtercard) */
#endif
#define D_ERR      0x0040	/* Bad Cell Alignment (ATMII-OC-3 only) */

/* status LED register defines for AIOCSSLED */
#define STAT_LED_OFF	0x0
#define STAT_LED_GREEN	0x1
#define STAT_LED_RED	0x2
#define STAT_LED_YELLOW	0x3

/* HDLC type streams are not yet supported. */
typedef struct {
	unsigned int tx_pdu;
	unsigned int rx_pdu;
	unsigned int rx_errors;
} HDLC_VC_STATS;

/* Structure returned from AIOCVCOUNTS on AAL5 streams */
typedef struct {
	unsigned int tx_pdu;
	unsigned int rx_pdu;

	unsigned int tx_empdu;
	unsigned int tx_discards;
	unsigned int tx_lenerr;	   /* large SDUs discarded (unsupported) */
	unsigned int tx_cells_clp0;
	unsigned int tx_cells_clp1;

	unsigned int rx_empdu;
	unsigned int rx_discards;
	unsigned int rx_lenerr;
	unsigned int crc_discard;
	unsigned int rx_cells_clp0;
	unsigned int rx_cells_clp1;
} AAL5_VC_STATS;

/* Structure returned from AIOCSUBCOUNTS on AAL2 streams */
typedef struct {
	unsigned int tx_pdu;
	unsigned int rx_pdu;

	unsigned int null0;	/* Always zero */
	unsigned int null1;	/* Always zero */
	unsigned int null2;	/* Always zero */
	unsigned int null3;	/* Always zero */
} AAL2_SUBCHAN_STATS;

/* Structure returned from AIOCVCOUNTS on AAL2 streams */
typedef struct {
	unsigned int tx_pdu;
	unsigned int rx_pdu;

	unsigned int tx_cells;
	unsigned int rx_cells;
	unsigned int rx_discard;	/* cells discarded */
	unsigned int rx_sdudiscard;	/* SDUs discarded */
} AAL2_VC_STATS;

typedef struct {
        unsigned int usr_cells_rx_clp0; /* number of user cells with CLP bit equal to 0 */
        unsigned int usr_cells_rx_clp1; /* number of user cells with CLP bit equal to 1 */
        unsigned int oam_cells_rx;      /* number of oam cells received */
        unsigned int pkts_rx;           /* For AAL5 channel, number of pkts received exclude OAM cell*/
        unsigned int pkts_tx_success;   /* For AAL5 channel, number of pkts transmitted, exclude OAM cell */
        unsigned int cells_discard;     /* number of cells discarded */
}SW_SHAPE_CHANN_STATS;

typedef struct {
        unsigned int usr_cells_rx_clp0; /* number of user cells with CLP bit equal to 0 */
        unsigned int usr_cells_rx_clp1; /* number of user cells with CLP bit equal to 1 */
        unsigned int oam_cells_rx;      /* number of oam cells received */
        unsigned int pkts_rx;           /* For AAL5 channel, number of pkts received exclude OAM cell*/
        unsigned int pkts_tx_success;   /* For AAL5 channel, number of pkts transmitted, exclude OAM cell */
        unsigned int cells_tagged_clp0_scr; /*cell tagged due to clp0 scr */
        unsigned int cells_discard_clp_pcr; /* number of cells discarded */
        unsigned int cells_discard_clp0_scr; /* cell discarded due to clp0 scr */
        unsigned int cells_discard_others;   /* cell discarded due to other reasons */
}SW_POLICE_CHANN_STATS;



/* Structure returned from AIOCSCOUNTS */
typedef struct {
	unsigned int tx_pdu;		/* PDUs Tx'd */
	unsigned int rx_pdu;		/* PDUs Rx'd */
	unsigned int tx_flc;		/* tx flow control events */
	unsigned int rx_flc;		/* rx flow control events */
	unsigned int tx_intr;		/* tx interrupts for this stream */
	unsigned int rx_intr;		/* rx interrupts for this stream */
	unsigned int tx_err;		/* tx error indications */
	unsigned int rx_holdq_discards;	/* rx msgs discarded due to lack of
					 * space in the holdq */
	unsigned int tx_srv;		/* times the wsrv routine runs */
	unsigned int rx_srv;		/* times the rsrv routine runs */
} ATMII_STRM_STATS;

/* Structure returned from AIOCEMPCOUNTS on ATM AAL5/2/0 ports 
 * (per physical trunk) */
typedef struct {
	unsigned int tx_cells;
	unsigned int rx_cells;
	unsigned int rx_hecerr;
	unsigned int rx_headererr;
} ATMII_EM_PORT_STATS;

/* Structure returned from AIOCEMPCOUNTS on HDLC ports 
 * (per connection, not per physical trunk) */
typedef struct {
	unsigned int rsvd1;
	unsigned int rx_packets;
	unsigned int rsvd2;
	unsigned int tx_packets;
	unsigned int rx_noresource;
	unsigned int rx_error;
} ATMII_EM_PKT_PORT_STATS;

/* Structure returned from AIOCPHYCOUNTS on ATMII-OC3 boards (per PHY) */
typedef struct {
	unsigned char   locd_events;	/* Loss of Cell Delination Events */
	unsigned char   corr_hec;	/* corrected HEC Errors */
	unsigned char   uncorr_hec;	/* uncorrected HEC Errors */
	unsigned char   oof_events;	/* Out Of Framing Events */
	unsigned int    line_bip;	/* Line BIP Errors */
	unsigned short  section_bip;	/* Section BIP Errors */
	unsigned short  path_bip;	/* Path BIP Errors */
	unsigned int    line_rei;	/* Line REI Errors */
	unsigned short  path_rei;	/* Path REI Errors */
	unsigned short  nonmatch;	/* Non-Matching Cell Counter */
	unsigned int    tx_cell;	/* Transmitted Cells */
	unsigned int    rx_cell;	/* Received Cells */
} ATMII_PHY_STATS;

/* Structure returned from AIOCBCOUNTS */
typedef struct {
	unsigned int interrupts;        /* total interrupts for this board */  
	unsigned int pad;		/* unused on ATM2 */
	unsigned int tx_pdu[NPORTS];    /* PDUs Tx'd (per port) */
	unsigned int rx_pdu[NPORTS];    /* PDUs Rx'd (per port) */
	unsigned int spurious_intrs;	/* number of interrupts where there
					 * were no indications to process */
} ATMII_BC_STATS;

/* Defines for AIOCGPTYPE */
#define T1_PORT 1
#define E1_PORT 2
#define OC3_PORT 3

/* Defines for Switch Service */
#define SW_SHAPE_CHANN  1	/* Shape Switch Channel */
#define SW_POLICE_CHANN 2	/* Policing Switch Channel */

/* Defines for AIOCSETCLK */
#define PCLK_REF	0x0	/* Use board reference as transmit clk */
#define PCLK_OWN	0x1	/* Use own port's receive clk as transmit clk */

/* Defines for AIOCSETCLKREF and AIOCGETCLKREF */
#define CLK_SRC_OCX	0x0	/* Crystal Oscillator as master clock source*/
#define CLK_SRC_BNC	0x1	/* BNC connector as master clock source*/
#define CLK_SRC_PMCA	0x2	/* PMC P3 pin 12 master clock source*/
#define CLK_SRC_PMCB	0x4	/* PMC P3 pin 13 master clock source*/
#define CLK_SRC_PMCC	0x8	/* PMC P3 pin 42 master clock source*/
#define CLK_SRC_PMCD	0x10	/* PMC P3 pin 34 master clock source*/
#define CLK_SRC_RX0	0x20	/* Port 0 PHY as master clock source*/
#define CLK_SRC_RX1	0x40	/* Port 1 PHY as master clock source*/

#define CLK_DST_NONE	0x0	/* No destination for master clock */
#define CLK_DST_BNC	0x1	/* BNC connector as master clock destination*/
#define CLK_DST_PMCA	0x2	/* PMC P3 Pin 12 as master clock destination*/
#define CLK_DST_PMCB	0x4	/* PMC P3 Pin 13 as master clock destination*/
#define CLK_DST_PMCC	0x8	/* PMC P3 Pin 42 as master clock destination*/
#define CLK_DST_PMCD	0x10	/* PMC P3 Pin 34 as master clock destination*/
#define CLK_DST_MASK	(CLK_DST_BNC|CLK_DST_PMCA|CLK_DST_PMCB| \
			 CLK_DST_PMCC|CLK_DST_PMCD)

/* Structure returned from AIOCGETCLKREF */
typedef struct {
	unsigned int clk_src;	/* One of CLK_SRC_XXX which is the source of 
				 * the board reference clock */
	unsigned int clk_dst;	/* Bitmask of CLK_DST_XXX defines which indicate
				 * which pins board reference clock is being 
				 * driven on. */
	unsigned short phy_los;	/* Set to 1 if one of the PHYs is the board
				 * clock reference and that PHY has lost it's 
				 * signal so the on-board OSC is being used. */
	unsigned short ptenb;	/* PTMC PTENB bit.  When set to 1 signifies that
				 * the PMC's host board allows PT1MC 
				 * boards and it is safe to drive PMC P3 Pins
				 * 12 and 13.  If set to 0, the user should 
				 * ensure with the host board manufacturer that
				 * it is safe to drive PMC P3 Pins 12 and 13 
				 * before setting them with AIOCSETCLKREF */
} ATMII_GETCLKREF;

#ifdef	__cplusplus
}
#endif
