/*--------------------------------------------------------------------------*/
/*
*                       M O D U L E   H E A D E R
*
* filename - isdnacu.h
*
* $Revision: 9.1 $
*
* $Date: 2005/03/23 12:56:01 $
*
*		- Call Control Automatic Calling Unit Interface header compatible
*        with the TR29 ACU_INT. For Analog and ISDN Call Control.
*/
/*-------------------------------------------------------------------------*/

/*[]---------------------------------------------------[]*/
/*|                                                     |*/
/*|    ISDN-BRICKS                                      |*/
/*|    Call Control (CC) Entity                         |*/
/*|                                                     |*/
/*|    Copyright (c) 1989-1998 by OMNITEL SA            |*/
/*|    All Rights Reserved.                             |*/
/*|                                                     |*/
/*[]---------------------------------------------------[]*/


#ifdef __cplusplus
extern "C" {
#endif
    
    
#ifndef ALIGN_64
#define ALIGN_64
#endif


#ifdef ALIGN_64
    
#define pad1 uchar pad1[1];
#define pad2 uchar pad2[2];
#define pad3 uchar pad3[3];
#define pad4 uchar pad4[4];
#define pad5 uchar pad5[5];
#define pad6 uchar pad6[6];
#define pad7 uchar pad7[7];

   
#else
    
#define pad1 
#define pad2 
#define pad3 
#define pad4 
#define pad5 
#define pad6 
#define pad7 
    
#endif
    
#ifndef ACU_INT
#	define ACU_INT

    
/*----------------------------------------------------------------------------
*				Adressing constants
	*--------------------------------------------------------------------------*/
    
#define	ACU_SAPI					'a'			/* SAP for ACU interface primitives */
#define	ACU_SAPI_CED_CNG			'b'			/* SAP for CED/CNG signalling */
#define	ACU_SAPI_MGT				'A'			/* SAP for Management primitives */
    
#define ACU_SAPI_MULTI_CHAN			'X'			/* Multi-channel SAPI */
    
    /*--------------------------------------------------------------------------*/
    
	/* Network-specific compilation parameters */
    
#define	ACU_MX_SZ_CALLING_NB		32			/* Maximum size for calling nb */
#define	ACU_MX_SZ_CALLING_SUB_ADD	20			/* Maximum size for calling sub address */
#define	ACU_MX_SZ_CALLED_NB      	35          /* Maximum size for called nb */
#define	ACU_MX_SZ_CALLED_SUB_ADD	20          /* Maximum size for called sub address */
#define ACU_MX_SZ_UUI				133			/* Maximum size for UUI */
#define ACU_MX_SZ_CALL_ID			4			/* Maximum size for called ID */
#define ACU_MX_SZ_USER_FAC			7			/* Maximum size for user facility information */
#define ACU_MX_SZ_FACILITY			250			/* Maximum size for facility information */
#define ACU_MX_SZ_DISPLAY			128			/* Maximum size for display information */
#define ACU_MX_SZ_PCS_USER			129			/* Maximum size for display information (128 + 1 for the leading 'protocol-discriminator' field */
#define	ACU_PREFIX_SIZE				5			/* Maximum length of a phone number prefix */
	/* (for accessing public or private telephone network, */
	/* international network, etc.) */
#define ACU_QSIG_MAX_ADDR_SIZE             5
    
    /* Constants to use in Q.SIG Name Identification Services */
#define ACU_SS_NAME_ALLOWED_ISO8859    1
#define ACU_SS_NAME_ALLOWED_T61        2
#define ACU_SS_NAME_RESTRICTED_ISO8859 3
#define ACU_SS_NAME_RESTRICTED_T61     4
#define ACU_SS_NAME_NOT_AVAILABLE      5
	
    /* max number of conn_id per nai */
#define ACU_MX_CALLS                60
    
    /*----------------------------------------------------------------------------
	*				Default selections
	*--------------------------------------------------------------------------*/
    
#ifndef CC_F_A11
#	define	CC_F_A11				OFF
#endif
#ifndef CC_F_A17
#	define	CC_F_A17				OFF
#endif

#if (CC_F_A11 == ON) || (CC_F_A17 == ON)
#	define ARINC_NETWORKS 			ON
#else
#	define ARINC_NETWORKS 			OFF
#endif

#ifndef	ACU_PH_ENTITY
#	define	ACU_PH_ENTITY			ENT_PH_GSTN	/* For Analog ACU only */
#endif

/* NMS_FIX YA 030498 */
#ifndef ACU_PAR_EXTENDED_PRIM
#	define ACU_PAR_EXTENDED_PRIM	ON
#endif

#ifndef ACU_PAR_EXT_LLC
#	define ACU_PAR_EXT_LLC			OFF
#endif

#ifndef ACU_PAR_EXT_CUG
#	define ACU_PAR_EXT_CUG			OFF
#endif

#ifndef ACU_PAR_EXT_FAC_ASN1
#	define ACU_PAR_EXT_FAC_ASN1		OFF
#endif

#ifndef ACU_PAR_EXT_SPF_FAC_IE
#	define ACU_PAR_EXT_SPF_FAC_IE	ON
#endif

#ifndef _CC_SPID_INFO
#	define _CC_SPID_INFO			OFF
#endif

/*----------------------------------------------------------------------------
*				Primitives sent and received to/from ACU by a user entity
*--------------------------------------------------------------------------*/

#define	ACU_CONN_RQ			'A'		/* request establishment of an outgoing call */
#define	ACU_CONN_IN			'a'		/* indiacte an incoming call */
#define	ACU_CONN_RS			'B'		/* request answering to an incoming call */
#define	ACU_CONN_CO			'b'		/* indicate termination of an incoming or outgoing call */

#define	ACU_CLEAR_RQ		'C'		/* request release of the connection */
#define	ACU_CLEAR_IN		'c'		/* connection released indication */
#define	ACU_CLEAR_RS		'D'		/* response to the release of the connection */
#define	ACU_CLEAR_CO		'd'		/* connection released confirmation */

#define	ACU_ALERT_RQ		'E'		/* alert request */
#define	ACU_ALERT_IN		'e'		/* alert indication (ex: incoming ring) */

#define	ACU_PROGRESS_RQ		'F'		/* events for the progression of the call */
#define	ACU_PROGRESS_IN		'f'		/* events from the progressing outgoing call */

#define	ACU_INFO_RQ			'G'		/* information request */
#define	ACU_INFO_CO			'g'		/* information confirmation */

#define	ACU_INIT_RQ			'H'		/* initialization request */
#define	ACU_INIT_CO			'h'		/* initialization confirmation */

#define	ACU_SETPARM_RQ		'I'		/* set parameter request */
#define	ACU_SETPARM_CO		'i'		/* parameter confirmation */

#define	ACU_USER_INFO_RQ	'J'		/* request user to user information */
#define	ACU_USER_INFO_IN	'j'		/* indicate user to user information */

#define	ACU_SUSPEND_RQ		'K'		/* request suspension */
#define	ACU_SUSPEND_CO		'k'		/* confirm suspension */

#define	ACU_RESUME_RQ		'L'		/* request resume */
#define	ACU_RESUME_CO		'l'		/* confirm resume */

#define	ACU_TEST_RQ			'M'		/* request test */
#define	ACU_TEST_CO			'm'		/* confirm test */

#define	ACU_DIGIT_RQ		'N'		/* send several called nb digits in Overlap Sending mode */
#define	ACU_DIGIT_IN		'v'		/* receive several called nb digits in Overlap Receiving mode */
#define	ACU_DIGIT_CO		'n'		/* confirm end-of-called-nb-reached in Overlap Sending mode */

#define	ACU_FACILITY_RQ		'O'		/* request specific facility */
#define	ACU_FACILITY_IN		'o'		/* indicate specific facility */

#define	ACU_SET_MODE_RQ		'Q'		/* request setting of a particular mode */
#define	ACU_SET_MODE_CO		'q'		/* confirm setting of a particular mode */

#define	ACU_RS_MODE_RQ		'R'		/* request response mode to incoming call */
#define	ACU_RS_MODE_CO		'r'		/* confirm response mode to incoming call */

#define	ACU_INFORMATION_RQ	'S'		/* request information */
#define	ACU_INFORMATION_IN	's'		/* indicate information */

#define ACU_SETUP_REPORT_IN	't'		/* indicate incompatible incoming call */

#define	ACU_CALL_PROC_RQ	'U'		/* events for the progression of the call */
#define	ACU_CALL_PROC_IN	'u'		/* events for the progression of the call */

#define	ACU_NOTIFY_RQ		'W'		/* request notify */
#define	ACU_NOTIFY_IN		'w'		/* indicate notify */

#define	ACU_SETUP_ACK_IN	'x'		/* indicate setup acknowledge */

#define	ACU_D_CHANNEL_STATUS_RQ		'>'		/* request D channel status info */
#define	ACU_D_CHANNEL_STATUS_IN		'<'		/* indicate D channel status info */

#define	ACU_ERR_IN			'?'		/* Error indication */

#define	ACU_SERVICE_RQ		'0'		/* SERVICE message request */
#define	ACU_SERVICE_IN		'1'		/* SERVICE message indication */
#define	ACU_SERVICE_CO		'2'		/* SERVICE message confirmation */

#define	ACU_RESTART_IN		'4'		/* RESTART indication */
#define	ACU_RESTART_CO		'5'		/* RESTART indication */


/*----------------------------------------------------------------------------
*				Primitives sent and received to MNS form NS
*--------------------------------------------------------------------------*/
#define	SM_CHANNEL_MAINT_RQ		'Y'				/* D or B channel maintenance request */


/*------------------------------------------------------
* Type of the 'size' fields within the ACU primitives.
*-----------------------------------------------------*/

typedef uchar acu_size_t;

/*----------------------------------------------------------------------------
* Layer 1 information structure and fields values used in ACU_CONN_RQ/IN/RS
* Used for V.110 and V.120 services only.
*
* Fields used by the physical drivers (available for all services):
*   ph_rate:     physical rate
*
* Fields used for the ISDN coding (BC/LLC Information Elements):
* (for ACU_V110_SERVICE and ACU_V120_SERVICE services only)
*   user_rate:   user rate
*   syn_asyn:    synchronous/asynchronous
*   stop_bits:   nb of stop bits
*   data_bits:   nb of data bits
*   parity:      parity
*
*--------------------------------------------------------------------------*/

struct layer_1_info {
	uchar	ph_rate;		/* physical rate */
	uchar	user_rate;		/* user rate */
	uchar	syn_asyn;		/* synchronous/asynchronous */
	uchar	stop_bits;		/* nb of stop bits */
	uchar	data_bits;		/* nb of data bits */
	uchar	parity;			/* parity */
	pad2
};

/* Same values as CCITT */

#define ACU_BYTE_VAL_NIL		(uchar)(~0)				/* NIL byte value */

/* User rates */

#define ACU_RA_50				0x19			/* 0.050 kbits/s CCITT V.6 and X.1 */
#define ACU_RA_75				0x1a	 		/* 0.075 kbits/s CCITT V.6 and X.1 */
#define ACU_RA_75_1200 			0x17			/* 0.075/1.2 kbits/s CCITT V.6 and x.1 */
#define ACU_RA_100				0x16			/* 0.100 kbits/s CCITT V.6 and X.1 */
#define ACU_RA_110				0x1b			/* 0.110 kbits/s CCITT V.6 and X.1 */
#define ACU_RA_134				0x15			/* 0.1345 kbits/s CCITT X.1 */
#define ACU_RA_150				0x1c			/* 0.150 kbits/s CCITT V.6 and X.1 */
#define ACU_RA_200				0x1d			/* 0.200 kbits/s CCITT V.6 and X.1 */
#define ACU_RA_300				0x1e			/* 0.300 kbits/s CCITT V.6 and X.1 */
#define ACU_RA_600				0x01			/* 0.6 kbits/s CCITT V.6 and x.1 */
#define ACU_RA_1200				0x02			/* 1.2 kbits/s CCITT V.6 */
#define ACU_RA_1200_75 			0x18			/* 1.2/0.075 kbits/s CCITT V.6 and x.1 */
#define ACU_RA_2400				0x03			/* 2.4 kbits/s CCITT V.6 and X.1 */
#define ACU_RA_3600				0x04			/* 3.6 kbits/s CCITT V.6 */
#define ACU_RA_4800				0x05			/* 4.8 kbits/s CCITT V.6 and x.1 */
#define ACU_RA_7200				0x06			/* 7.2 kbits/s CCITT V.6 */
#define ACU_RA_8000				0x07			/* 8 kbits/s CCITT I.460 */
#define ACU_RA_9600				0x08			/* 9.6 kbits/s  CCITT V.6 and x.1 */
#define ACU_RA_12000			0x1f			/* 12 kbits/s CCITT V.6 */
#define ACU_RA_14400			0x09			/* 14.4 kbits/s CCITT V.6 */
#define ACU_RA_16000			0x0a			/* 16 kbits/s CCITT I.460 */
#define ACU_RA_19200			0x0b			/* 19.2 kbits/s CCITT V.6 */
#define ACU_RA_32000			0x0c			/* 32 kbits/s CCITT I.460 */
#define ACU_RA_38400			0x11			/* 38.4 kbits/s extended V.14 */
#define ACU_RA_38400_NO_ETSI	0x0d			/* 38.4 kbits/s extended V.14 (VN3) NON ETSI */
#define ACU_RA_48000			0x0e			/* 48 kbits/s CCITT V.6 and X.1 */
#define ACU_RA_56000			0x0f			/* 56 kbits/s CCITT V.6 */
#define ACU_RA_57600			0x12			/* 57.6 kbits/s extended V.14 (VN3) NON ETSI NON CCITT */
#define ACU_RA_64000			0x10			/* 64 kbits/s CCITT I.460 */

/* Sync/Async */

#define ACU_SYN					0x00					/* synchronous */
#define ACU_ASYN				0x01					/* asynchronous */

/* Stop bits */

#define ACU_STOP_BIT_1			0x01				/* 1 bit */
#define ACU_STOP_BIT_1_5		0x02				/* 1.5 bit */
#define ACU_STOP_BIT_2			0x03				/* 2 bits */

/* Data bits */

#define ACU_DATA_BIT_5			0x01				/* 5 bits */
#define ACU_DATA_BIT_7			0x02				/* 7 bits */
#define ACU_DATA_BIT_8			0x03				/* 8 bits */

/* Parity */

#define ACU_ODD					0x00				/* odd */
#define ACU_EVEN				0x02				/* even */
#define ACU_NO_PARITY			0x03				/* none */

/*----------------------------------------------------------------------------
* B channels ids structure used to report B channels to the user
*--------------------------------------------------------------------------*/

#ifndef ACU_MX_CHANI
#	define ACU_MX_CHANI			1	/* default maximum number of B-channel ids in the lists inside the primitives */
#endif

struct chani_tab {
	nai_t   nai;
	uchar   chan_id;
	pad6
};
struct chani_list {
	uchar   nb;				/* number of channel ids in the list */
	uchar	chan_id_excl;	/* chan_ids are preferred (OFF) or exclusive (ON) */
	pad6
	struct chani_tab tab[ACU_MX_CHANI];
};


/*----------------------------------------------------------------------------
* Call Reference related information sub-structure
*----------------------------------------------------------------------------*/

struct acu_call_ref {
	WORD 	value;          /* call reference value */
	uchar 	length;	        /* call reference length */
	pad5
};


/*----------------------------------------------------------------------------
* Name related information sub-structure
*----------------------------------------------------------------------------*/

struct acu_name {
	uchar		active;		/* name ss active ON, inactive OFF */
	uchar		pres;		/* presentation restricted/allowed */
	acu_size_t	size;		/* size of the name in bytes */
	pad5
};
#define acu_name_size(var) var.size

/*----------------------------------------------------------------------------
* Called number related information sub-structure
*----------------------------------------------------------------------------*/

struct acu_called_nb {
	uchar		type;		/* called nb type */
	uchar		plan;		/* called nb plan */
	acu_size_t	size;		/* size of the called number in bytes */
	pad5
};

/*----------------------------------------------------------------------------
* Calling number related information sub-structure
*----------------------------------------------------------------------------*/

struct acu_calling_nb {
	uchar		pres;		/* calling nb presentation */
	uchar		plan;		/* calling nb plan */
	uchar		type;		/* calling nb type */
	uchar		screen;		/* calling nb screening indicator */
	acu_size_t	size;		/* size of the calling number in bytes */
	pad3
};

/*----------------------------------------------------------------------------
* Redirected number related information sub-structure
*----------------------------------------------------------------------------*/

struct acu_redir_nb {
	uchar		pres;		/* redirected nb presentation */
	uchar		type;		/* redirected nb type */
	uchar		plan;		/* redirected nb plan */
	uchar		screen;		/* redirected nb screening indicator */
	uchar		reason;		/* reason for redirection */
	acu_size_t	size;		/* size of the redirected number in bytes */
	pad2
};

/*----------------------------------------------------------------------------
* Original called number related information sub-structure (DMS specific) 
*----------------------------------------------------------------------------*/

struct acu_orig_called_nb {
	uchar		plan;		/* orig called nb plan */
	uchar		type;		/* orig called nb type */
	uchar		pres;		/* orig called nb presentation */
	uchar		screen;		/* orig called nb screening indicator */
	uchar		reason;		/* reason */
	uchar		cfnr;		/* call forwarding no reply busy undergone ind */
	uchar		count;		/* counter */
	acu_size_t	size;		/* size of the redirected number in bytes */
};



/*----------------------------------------------------------------------------
* subaddress related information sub-structure
*----------------------------------------------------------------------------*/

struct acu_subaddress {
	uchar		type;		/* subaddress type */
	uchar		odd_even;	/* odd/even indicator */
	acu_size_t	size;		/* size of the subaddress in bytes */
	pad5
};


/*----------------------------------------------------------------------------
* Progress-indicator IE related information sub-structure
*----------------------------------------------------------------------------*/

#ifndef ACU_MX_PROGRESS_IND
#	define	ACU_MX_PROGRESS_IND		1
#endif

struct acu_progress_ind {
    
	struct {
		uchar	loc;			/* progress location */
		uchar	descr;			/* progress description */
		pad6
	} t [ACU_MX_PROGRESS_IND];

	uchar nb;					/* number of progress_ind elements in the table */
	pad7

};

/*----------------------------------------------------------------------------
* Multiple display management.
*--------------------------------------------------------------------------*/

/* NMS_FIX YA 031798 changed max display to 1 */ 
#ifndef ACU_MX_DISPLAY
#	define	ACU_MX_DISPLAY			1
#endif

struct acu_display_list {
#ifdef _Solaris64_
        DWORD 	        p_display[ACU_MX_DISPLAY];	/* Pointer to the occurences */
#else
	char  *	p_display[ACU_MX_DISPLAY];	/* Pointer to the occurences */
#endif
	uchar 		nb;							/* Nb of present occurences */
	uchar		total_size;					/* total size of the stored strings */
	uchar 		type	 [ACU_MX_DISPLAY];	/* Type of display */
	uchar 		size	 [ACU_MX_DISPLAY];	/* Size of the occurences */
};

#define	Acu_display_nb				p_display -> nb
#define	Acu_display_total_size		p_display -> total_size
#define	Acu_display_type(xx)		p_display -> type[xx]
#define	Acu_display_p_display(xx)	p_display -> p_display[xx]
#define	Acu_display_size(xx)		p_display -> size[xx]

/*----------------------------------------------------------------------------
* Date/Time information
*--------------------------------------------------------------------------*/

struct acu_date_time {
	uchar available;		/* ON if the information is available, else OFF */
	uchar year;				/* year */
	uchar month;			/* month */
	uchar day;				/* day */
	uchar hour;				/* hour */
	uchar minute;			/* minute */
	uchar second;			/* second */
	pad1
};

/*----------------------------------------------------------------------------
* Charging information
*--------------------------------------------------------------------------*/

struct acu_charging_info {
	DWORD value;			/* charging value (nb of units) */
	uchar available;		/* charging info available (ON) or not (OFF) */
	uchar type;				/* charging type */
	uchar period;			/* charging period */
	uchar multi;			/* charging period multiplier */
};

/*---------------------------------------------------------------------------
* Voice supplementary services management.
*--------------------------------------------------------------------------*/

struct voice_supp_service {
	uchar   button_type;    /* Unknown, call appear or feature */
	uchar   module_nb;      /* 0-7, call appear buttons are assigned to module 0 */
	uchar   button_nb;      /* 1-254, 0 and 255 are reserved */
	uchar	call_appear;    /* selected call appearence */
	uchar	switchhook;     /* switchhook indication */
	uchar	conn_id;        /* CONFERENCE : Conn_id of the active call */
	pad2
};

/*---------------------------------------------------------------------------
* SPID / ENDPOINT ID management.
*--------------------------------------------------------------------------*/

#if _CC_SPID_INFO == ON

struct acu_endpoint_id {
	uchar action;		/* Action */
	uchar usid;			/* User Id */
	uchar tid;			/* Terminal Id */
	uchar interpreter;	/* Intrepreter */
	pad4;
};

#endif

/*----------------------------------------------------------------------------
* ACU primitives extension descriptor structure
*----------------------------------------------------------------------------*/

#if ACU_PAR_EXTENDED_PRIM == ON /* { */

/*------------------------------------------------------------------*/
/* 1. Extension descriptor, placed in the ACU primitives structures */
/*------------------------------------------------------------------*/
struct acu_ext_descr {
	WORD		nb;			/* number of options in list. */
	WORD		lgth;		/* total length of list */
	WORD		offset;		/* Offset to start of data*/
	pad2
};
#define Acu_ext_descr_offset	((struct acu_ext_descr  *)p_data) -> offset
#define Acu_ext_descr_address	(((uchar *)p_data)+((struct acu_ext_descr  *)p_data) -> offset)
#define Acu_ext_descr_first_address	Acu_ext_descr_address
#define Acu_ext_descr_next_address	Acu_ext_descr_address+Acu_ext_descr_lgth

#define Acu_ext_descr_nb		((struct acu_ext_descr  *)p_data) -> nb
#define Acu_ext_descr_lgth		((struct acu_ext_descr  *)p_data) -> lgth
/*--------------------------------------------------------*/
/* 2. Extension header placed in each extension structure */
/*--------------------------------------------------------*/

struct u4_acu_ext_hdr {
	WORD		id;			/* identifier */
	WORD		lgth;		/* length in bytes of the contents */
};

/* Access macros thru 'p_ext_data' pointing to the extension header */

#define Acu_ext_id			((struct u4_acu_ext_hdr  *)p_ext_data) -> id
#define Acu_ext_lgth		((struct u4_acu_ext_hdr  *)p_ext_data) -> lgth

/* Extended elements identifiers */


#define	ACU_EXT_SPF_FAC_IE			0x0301	/* Network Specific IE */

#define ACU_EXT_SERVICES		    0x0500

/*-------------------------*/
/* 3. Extension structures */
/*-------------------------*/

/*-----------------------------------*/
/* 3a. LOW LAYER COMPATIBILITY (LLC) */
/*-----------------------------------*/
/*-------------------------*/
/* 3f. Network Specific IE */
/*-------------------------*/

#if ACU_PAR_EXT_SPF_FAC_IE == ON /* { */

#	define	ACU_MX_SZ_NET_ID		5			/* network id array */

struct acu_ext_spf_fac_ie {
	struct u4_acu_ext_hdr hdr;					/* extension header */
	pad4
	uchar		net_id[ACU_MX_SZ_NET_ID];	/* network identification array */

	uchar		net_id_lgth;	 			/* length of network identification */
	uchar		net_id_type;	 			/* type of ID */
	uchar		action;						/* parameterized/binary indicator */
	uchar		serv_feature;				/* service/feature indicator */
	uchar		facility_coding;			/* facility coding */
	uchar		param_fld;					/* parameterized field */
	pad5
};

#	define Acu_ext_spf_fac_ie(field)		(((struct acu_ext_spf_fac_ie  *)p_ext_data) -> field)
#	define Acu_ext_spf_fac_ie_size			Rnd_sizeof (struct acu_ext_spf_fac_ie)

/* net_id_type */

#	define ACU_USER_SPECIFIED_TYPE			0	/* User specified */
#	define ACU_NATIONAL_NETWORK_ID_TYPE		2	/* National network */

/*  action */
#	define ACU_SPF_FAC_PARAMETER			0	/* Parameter are associated with the facility */
#	define ACU_SPF_FAC_BINARY				1	/* Binary facility */

/* serv_feature */

#	define ACU_FAC_SERVICE					1	/* Sewrvice */
#	define ACU_FAC_FEATURE					0	/* Feature */

/* facility coding */

#	define ACU_FAC_CPN_SID_PREFERRED		1	/* CPN (SID) preferred */
#	define ACU_FAC_BN_ANI_PREFERRED			2	/* BN (ANI) preferred */
#	define ACU_FAC_CPN_SID_ONLY				3	/* CPN (SID) only */
#	define ACU_FAC_BN_ANI_ONLY				4	/* BN (ANI) only */
#	define ACU_FAC_CALL_ASSOC_TSC			9	/* Call associated TSC */
#	define ACU_FAC_TSC_CLEAR_RU				10	/* Notification of call associated TSC clearing or resource unavailable */
#	define ACU_FAC_OPERATOR					5	/* Operator */
#	define ACU_FAC_PCCO						6	/* Pre-subscribed Common Carrier Operator */

#	define ACU_FAC_SDN						1	/* SDN including GSDN */
#	define ACU_FAC_MEGACOM_800				2	/* Acces to MEGACOM 800 */
#	define ACU_FAC_MEGACOM					3	/* Acces to MEGACOM */
#	define ACU_FAC_ACCUNET					6	/* ACCUNET */
#	define ACU_FAC_LONG_DISTANCE			7	/* International long distance */
#	define ACU_FAC_INTERNATIONAL_800		8	/* International 800 */
#	define ACU_FAC_ATT_MULTIQUEST			16	/* AT&T MultiQuest */

/* param_fld */

#	define	ACU_FAC_VARI_A_BILL				6	/* Vari-A-Bill (flexible billing) */

#endif  /* ACU_PAR_EXT_SPF_FAC_IE == ON } */

#endif /* ACU_PAR_EXTENDED_PRIM == ON } */

/*----------------------------------------------------------------------------
*		Analog ACU entity configuration
*----------------------------------------------------------------------------*/

#ifndef	ACU_CONFIG_MX_NA
#	define	ACU_CONFIG_MX_NA	1
#endif

struct acu_config {		/* ACU entity configuration */
    
	struct confirm 	acu_confirm;		/* confirmation structure */

	struct acu_config_na {				/* NA description */
			struct {								/* modem chip / PH entity description */
			ent_id_t	ph_ent_id;				/* Name of the PH entity. 0: use default, compiled value */
			sapi_t		ph_sapi;				/* Name of the PH sapiy. 0: use default, compiled value */
			uchar		detect_complete_ri_train;/* ON : the modem chip (PH entity) signals the last RI train when the final silence has expired */
			/* OFF: the modem chip signals the last RI train before, as soon as the signal has disappeared (at the beginning of the silence) */
			/* for Rockwell RC9623: ON */
			uchar		ced_data_by_chip;		/* ON : the modem chip (PH entity) sends CED automatically in data mode */
			/* OFF: the modem chip does not. CED transmisssion is managed by ACU */
			/* for Rockwell RC9623: ON */
			uchar		ced_fax_by_chip;		/* ON : the modem chip (PH entity) sends CED automatically in fax mode */
			/* OFF: the modem chip does not. CED transmisssion is managed by ACU */
			/* for Rockwell RC9623: OFF */
			pad3
			
		} ph;
	
		short			max_rings;			/* (default) maximum number of
											rings before answering.
											> 255 : no autoanswer.
		*/


		uchar			gstn_prefix			 [ACU_PREFIX_SIZE + 1];	/* (PABX) prefix to access the network */
		uchar			international_prefix [ACU_PREFIX_SIZE + 1];	/* international prefix */
		uchar			interregional_prefix [ACU_PREFIX_SIZE + 1];	/* interregional prefix */


		uchar			nai;					/* network access identifier */
		uchar			nlines;				/* number of managed lines */
    
		ent_id_t		user_entity;		/* default user entity */
    
		uchar			can_ph_num_max_size;/* max size of a canonical phone num */
		uchar			cmd_max_num;		/* max size of a command sequence */

	    uchar           dial_mode;			/* default dial mode */
		
		uchar			no_check;				/* ON if no check of phone numbers against regulation */
		/* and also no check of parameters (regmax_call_delay, regmin_call_delay) against regulation */
		
		uchar			direct_seizing;		/* ON if direct line seizing */
		uchar			direct_dialing;		/* ON if direct dialing (no wait for proceed tone) */
		uchar			dial_if_no_proceed;	/* ON if dial even if proceed tone not present */

		timer_val_t		init_delay;				/* ACU entity init delay */
		timer_val_t		intercall_delay;		/* outgoing calls intercall delay */
		timer_val_t		before_seizing_delay;	/* duration for listening before line seizing */
		timer_val_t		proceed_delay;			/* delay for waiting for proceed indication */
		timer_val_t		international_delay;	/* delay for waiting for international proceed indication */
		timer_val_t		interregional_delay;	/* delay for waiting for interregional proceed indication */
		timer_val_t		call_delay;				/* outgoing call max delay */
		timer_val_t		dial_pause_delay;		/* first dial pause duration */
		timer_val_t		comma_pause_delay;		/* 'comma' dial pause duration */
		timer_val_t		dtmf_duration;			/* 'DTMF duration */
		timer_val_t		watchdog_delay;			/* watchdog delay */
		timer_val_t		no_ring_delay;			/* delay after which ring synchronization is lost */
		timer_val_t		before_ced_delay;		/* delay before sending CED */
		timer_val_t		after_ced_delay;		/* delay after sending CED */
		
		timer_val_t		regmax_call_delay;		/* regulation-specified maximum 'maximum duration for establishment of an outgoing call' */
		timer_val_t		regmin_dial_pause_delay;/* regulation-specified minimum dial pause delay */
		timer_val_t		regmax_dial_pause_delay;/* regulation-specified maximum dial pause delay */
		timer_val_t		regmax_comma_pause_delay;/* regulation-specified maximum comma pause delay */
	
		timer_val_t		regmin_dtmf_duration;	/* regulation-specified minimum DTMF duration */
		timer_val_t		regmax_dtmf_duration;	/* regulation-specified maximum DTMF duration */

		uchar			regmin_max_rings;		/* regulation-specified minimum number of rings before answering */
		uchar			regmax_max_rings;		/* regulation-specified maximum number of rings before answering */
		
	
		timer_val_t		regmin_call_delay;		/* regulation-specified minimum 'maximum duration for establishment of an outgoing call' */
		pad3			
	} acu_config_na [ACU_CONFIG_MX_NA];
};

#define		Cfig_can_ph_num_max_size		(P_acu_config->can_ph_num_max_size)
#define		Cfig_nlines						(P_acu_config->nlines)
#define		Cfig_cmd_max_num				(P_acu_config->cmd_max_num)
#define		Cfig_user_entity				(P_acu_config->user_entity)

#define		Cfig_a_na_config(i)				(&(P_acu_config->acu_config_na [i]))

#define		Cfig_nai						(p_acu_config_na->nai)
#define		Cfig_ph_ent_id					(p_acu_config_na->ph.ph_ent_id)
#define		Cfig_ph_sapi					(p_acu_config_na->ph.ph_sapi)
#define		Cfig_detect_complete_ri_train	(p_acu_config_na->ph.detect_complete_ri_train)
#define		Cfig_ced_data_by_chip			(p_acu_config_na->ph.ced_data_by_chip)
#define		Cfig_ced_fax_by_chip			(p_acu_config_na->ph.ced_fax_by_chip)

#define		Cfig_dial_mode					(p_acu_config_na->dial_mode)
#define		Cfig_direct_dialing				(p_acu_config_na->direct_dialing)
#define		Cfig_direct_seizing				(p_acu_config_na->direct_seizing)
#define		Cfig_dial_if_no_proceed			(p_acu_config_na->dial_if_no_proceed)
#define		Cfig_max_rings					(p_acu_config_na->max_rings)
#define		Cfig_no_check					(p_acu_config_na->no_check)

#define		Cfig_after_ced_delay			(p_acu_config_na->after_ced_delay)
#define		Cfig_before_ced_delay			(p_acu_config_na->before_ced_delay)
#define		Cfig_init_delay					(p_acu_config_na->init_delay)
#define		Cfig_intercall_delay			(p_acu_config_na->intercall_delay)
#define		Cfig_before_seizing_delay		(p_acu_config_na->before_seizing_delay)
#define		Cfig_call_delay					(p_acu_config_na->call_delay)
#define		Cfig_dial_pause_delay			(p_acu_config_na->dial_pause_delay)
#define		Cfig_comma_pause_delay			(p_acu_config_na->comma_pause_delay)
#define		Cfig_dtmf_duration				(p_acu_config_na->dtmf_duration)
#define		Cfig_no_ring_delay				(p_acu_config_na->no_ring_delay)
#define		Cfig_proceed_delay				(p_acu_config_na->proceed_delay)
#define		Cfig_international_delay		(p_acu_config_na->international_delay)
#define		Cfig_interregional_delay		(p_acu_config_na->interregional_delay)
#define		Cfig_watchdog_delay				(p_acu_config_na->watchdog_delay)
#define		Cfig_regmin_dial_pause_delay	(p_acu_config_na->regmin_dial_pause_delay)
#define		Cfig_regmax_dial_pause_delay	(p_acu_config_na->regmax_dial_pause_delay)
#define		Cfig_regmin_call_delay			(p_acu_config_na->regmin_call_delay)
#define		Cfig_regmax_call_delay			(p_acu_config_na->regmax_call_delay)
#define		Cfig_regmax_comma_pause_delay	(p_acu_config_na->regmax_comma_pause_delay)
#define		Cfig_regmin_dtmf_duration		(p_acu_config_na->regmin_dtmf_duration)
#define		Cfig_regmax_dtmf_duration		(p_acu_config_na->regmax_dtmf_duration)
#define		Cfig_regmin_max_rings			(p_acu_config_na->regmin_max_rings)
#define		Cfig_regmax_max_rings			(p_acu_config_na->regmax_max_rings)

#define		Cfig_gstn_prefix				(p_acu_config_na->gstn_prefix)
#define		Cfig_international_prefix		(p_acu_config_na->international_prefix)
#define		Cfig_interregional_prefix		(p_acu_config_na->interregional_prefix)


/*----------------------------------------------------------------------------
*			DETAILED DESCRIPTION OF PRIMITIVES SENT TO ACU ENTITY
*--------------------------------------------------------------------------*/

/* length of a 'size' field within a ACU primitive */

#define ACU_SIZE_FIELD_LGTH					sizeof (acu_size_t)

/*---------------------------------------------------------------------------
*
*	ACU_CONN_RQ			request establishment of an outgoing call.
*
*	Arguments :
*		Acu_conn_rq_priority 			: phone call priority normal/urgent
*		Acu_conn_rq_auto_dial 			: automatical dialing (ON) or
*										  just go off hook (OFF)
*		Acu_conn_rq_service				: requested (tele)service
*		Acu_conn_rq_sending_complete	: Sending-complete IE to be generated (ON/OFF)
*		Acu_conn_rq_ph_rate 			: physical rate (for all services)
*		Acu_conn_rq_user_rate			: requested user rate (for V.110 and V.120 services only)
*		Acu_conn_rq_syn_asyn 			: synchronous/asynchronous (for V.110 and V.120 services only)
*		Acu_conn_rq_stop_bits   		: nb of stop bits (for V.110 and V.120 services only)
*		Acu_conn_rq_data_bits   		: nb of data bits (for V.110 and V.120 services only)
*		Acu_conn_rq_parity      		: parity (for V.110 and V.120 services only)
*      Acu_conn_rq_data_chani_nb		: nb of elements in the chani_list.tab field
*      Acu_conn_rq_data_chani  		: data channel to use (B1, B2, etc, D, or 0 for any)
*		Acu_conn_rq_charging_rq			: charging info requested
*		Acu_conn_rq_transfer_rq 		: transfer requested
*		Acu_conn_rq_transfer_con_id 	: conn_id of the call to be transfered
*		Acu_conn_rq_ident_denied_rq 	: identity denied requested
*		Acu_conn_rq_identification_denied_rq : alias macro for Acu_conn_rq_ident_denied_rq
*		Acu_conn_rq_calling_nb_type		: calling nb type
*		Acu_conn_rq_calling_nb_screen	: calling nb screening indicator
*		Acu_conn_rq_calling_nb2_type	: 2nd calling nb type
*		Acu_conn_rq_calling_nb2_screen	: 2nd calling nb screening indicator
*		Acu_conn_rq_called_nb_type		: called nb type
*		Acu_conn_rq_called_nb_plan		: called nb plan
*		Acu_conn_rq_called_nb_size		: called number size in bytes
*		Acu_conn_rq_a_called_nb			: address of the called number.
*		(Acu_conn_rq_ph_num_size		: alias for Acu_conn_rq_called_nb_size)
*		(Acu_conn_rq_a_ph_num 			: alias for Acu_conn_rq_a_called_nb)
*		Acu_conn_rq_calling_nb_size,
*		Acu_conn_rq_a_calling_nb		: calling number.
*		Acu_conn_rq_calling_nb2_size,
*		Acu_conn_rq_a_calling_nb2		: 2nd calling number.
*		Acu_conn_rq_uui_protocol,
*		Acu_conn_rq_uui_size,
*		Acu_conn_rq_a_uui				: ISDN user to User Information
*		Acu_conn_rq_facility_size,
*		Acu_conn_rq_a_facility			: ISDN facility
*		Acu_conn_rq_pcs_user_protocol,
*		Acu_conn_rq_pcs_user_size,
*		Acu_conn_rq_a_pcs_user			: ISDN PCS-to-User/User-to-PCS Info.
*		Acu_conn_rq_call_appear			: call_appearance
*		Acu_conn_rq_progress_location	: progress description
*		Acu_conn_rq_progress_description: progress location
*
*		Warning : when building this primitive, the phone number field must
*		be filled BEFORE the CALLING_NB field.
*
*--------------------------------------------------------------------------*/

struct acu_conn_rq_args {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif

	struct layer_1_info layer_1_info;	/* layer 1 information field */
	struct chani_list   chani_list;		/* list of channel ids to use for data transfer */
	struct acu_called_nb  called_nb;	/* called nb information */
	struct acu_calling_nb calling_nb;	/* calling nb information */
	struct acu_calling_nb calling_nb2;	/* second calling nb information */
	struct acu_redir_nb   redir_nb;		/* redirecting nb information */
	struct acu_display_list display;	/* display list */
	struct acu_progress_ind progress_ind;/* progress indicator */
	struct acu_subaddress called_nb_sub;
	struct acu_subaddress calling_nb_sub;
	struct acu_name  ss_cnip_name;
    
    
	uchar	priority;					/* phone call priority */
	uchar	auto_dial;					/* OFF: go off hook only; ON: dial number */
	uchar	service;					/* requested service */
	uchar	sending_complete;			/* Sending-complete information element generation */
	uchar	charging_rq;				/* request charging ON or OFF */
	uchar	transfer_rq;				/* request transfer ON or OFF */
	add_t	conn_id;					/* transfer conn_id */
	uchar	ident_denied_rq;			/* request identity denied ON or OFF */
	uchar	call_appear;				/* Call appearence */
		
	uchar      uui_protocol;			/* UUI protocol-discriminator value */
	acu_size_t uui_size;				/* size of the ISDN User to User information field */
	acu_size_t facility_size;			/* size of the facility */
	uchar      pcs_user_protocol;		/* PCS-to-User or User-to-PCS protocol-discriminator value */
	acu_size_t pcs_user_size;			/* size of the PCS-to-User or User-to-PCS information */
		
	acu_size_t tsp_ie_list_size;		/* length of the list of transparent IE's */
	pad1		
		
#	if _CC_SPID_INFO == ON
		struct acu_endpoint_id endpoint_id;	/* Endpoint Id */
#	endif
    
	/* phone number is just here */
	/* then all the other strings in order */
};

#define	Acu_conn_rq_					((struct acu_conn_rq_args  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_conn_rq_ext_parms_nb		Acu_conn_rq_ ext_descr.nb
#	define Acu_conn_rq_ext_parms_lgth	Acu_conn_rq_ ext_descr.lgth
#	define Acu_conn_rq_a_ext_parms		((Acu_ext_descr_offset = Acu_conn_rq_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define	Acu_conn_rq_priority			Acu_conn_rq_ priority
#define	Acu_conn_rq_auto_dial			Acu_conn_rq_ auto_dial

#define	Acu_conn_rq_service				Acu_conn_rq_ service
#define	Acu_conn_rq_sending_complete	Acu_conn_rq_ sending_complete

#define	Acu_conn_rq_a_layer_1_info		((struct layer_1_info  *)&Acu_conn_rq_ layer_1_info)
#define	Acu_conn_rq_ph_rate				Acu_conn_rq_ layer_1_info.ph_rate
#define	Acu_conn_rq_user_rate			Acu_conn_rq_ layer_1_info.user_rate
#define	Acu_conn_rq_syn_asyn			Acu_conn_rq_ layer_1_info.syn_asyn
#define	Acu_conn_rq_stop_bits			Acu_conn_rq_ layer_1_info.stop_bits
#define	Acu_conn_rq_data_bits			Acu_conn_rq_ layer_1_info.data_bits
#define	Acu_conn_rq_parity				Acu_conn_rq_ layer_1_info.parity

#define Acu_conn_rq_data_chani_nb       Acu_conn_rq_ chani_list.nb
#define Acu_conn_rq_data_chani          Acu_conn_rq_ chani_list.tab[0].chan_id
#define Acu_conn_rq_data_chani_nai      Acu_conn_rq_ chani_list.tab[0].nai
#define Acu_conn_rq_data_chani_tab(i)   Acu_conn_rq_ chani_list.tab[i].chan_id
#define Acu_conn_rq_data_chani_tab_nai(i) Acu_conn_rq_ chani_list.tab[i].nai
#define Acu_conn_rq_data_chani_excl     Acu_conn_rq_ chani_list.chan_id_excl

#define	Acu_conn_rq_charging_rq			Acu_conn_rq_ charging_rq
#define	Acu_conn_rq_transfer_rq			Acu_conn_rq_ transfer_rq
#define	Acu_conn_rq_transfer_conn_id	Acu_conn_rq_ conn_id
#define	Acu_conn_rq_ident_denied_rq		Acu_conn_rq_ ident_denied_rq
#define	Acu_conn_rq_identification_denied_rq	Acu_conn_rq_ident_denied_rq

#define Acu_conn_rq_call_appear			Acu_conn_rq_ call_appear

#define	Acu_conn_rq_called_nb_type		Acu_conn_rq_ called_nb.type
#define	Acu_conn_rq_called_nb_plan		Acu_conn_rq_ called_nb.plan
#define	Acu_conn_rq_called_nb_size		Acu_conn_rq_ called_nb.size
#define	Acu_conn_rq_ph_num_size			Acu_conn_rq_called_nb_size

#define	Acu_conn_rq_calling_nb_pres		Acu_conn_rq_ calling_nb.pres
#define	Acu_conn_rq_calling_nb_type		Acu_conn_rq_ calling_nb.type
#define	Acu_conn_rq_calling_nb_plan		Acu_conn_rq_ calling_nb.plan
#define	Acu_conn_rq_calling_nb_screen	Acu_conn_rq_ calling_nb.screen
#define	Acu_conn_rq_calling_nb_size		Acu_conn_rq_ calling_nb.size

#define	Acu_conn_rq_calling_nb2_pres	Acu_conn_rq_ calling_nb2.pres
#define	Acu_conn_rq_calling_nb2_type	Acu_conn_rq_ calling_nb2.type
#define	Acu_conn_rq_calling_nb2_screen	Acu_conn_rq_ calling_nb2.screen
#define	Acu_conn_rq_calling_nb2_size	Acu_conn_rq_ calling_nb2.size

#define	Acu_conn_rq_redir_nb_pres		Acu_conn_rq_ redir_nb.pres
#define	Acu_conn_rq_redir_nb_type		Acu_conn_rq_ redir_nb.type
#define	Acu_conn_rq_redir_nb_plan		Acu_conn_rq_ redir_nb.plan
#define	Acu_conn_rq_redir_nb_screen		Acu_conn_rq_ redir_nb.screen
#define	Acu_conn_rq_redir_nb_reason		Acu_conn_rq_ redir_nb.reason
#define	Acu_conn_rq_redir_nb_size		Acu_conn_rq_ redir_nb.size

#define	Acu_conn_rq_called_nb_sub_type		Acu_conn_rq_ called_nb_sub.type
#define	Acu_conn_rq_called_nb_sub_odd_even	Acu_conn_rq_ called_nb_sub.odd_even
#define	Acu_conn_rq_called_nb_sub_size		Acu_conn_rq_ called_nb_sub.size
#define	Acu_conn_rq_calling_nb_sub_type		Acu_conn_rq_ calling_nb_sub.type
#define	Acu_conn_rq_calling_nb_sub_odd_even	Acu_conn_rq_ calling_nb_sub.odd_even
#define	Acu_conn_rq_calling_nb_sub_size		Acu_conn_rq_ calling_nb_sub.size

#define	Acu_conn_rq_ss_cnip_name_size		Acu_conn_rq_ ss_cnip_name.size
#define	Acu_conn_rq_ss_cnip_name_pres		Acu_conn_rq_ ss_cnip_name.pres
#define	Acu_conn_rq_ss_cnip_name_active		Acu_conn_rq_ ss_cnip_name.active
#define	Acu_conn_rq_ss_cnip_name 		  	Acu_conn_rq_ ss_cnip_name

#define	Acu_conn_rq_uui_protocol		Acu_conn_rq_ uui_protocol
#define	Acu_conn_rq_uui_size			Acu_conn_rq_ uui_size
#define	Acu_conn_rq_facility_size		Acu_conn_rq_ facility_size
#define	Acu_conn_rq_display_size		Acu_conn_rq_x_display_total_size
#define	Acu_conn_rq_pcs_user_protocol	Acu_conn_rq_ pcs_user_protocol
#define Acu_conn_rq_pcs_user_size		Acu_conn_rq_ pcs_user_size

#define Acu_conn_rq_tsp_ie_list_size	Acu_conn_rq_ tsp_ie_list_size

#define Acu_conn_rq_x_display_nb		Acu_conn_rq_ display.nb
#define Acu_conn_rq_x_display_total_size Acu_conn_rq_ display.total_size
#define Acu_conn_rq_x_p_display(i) 		Acu_conn_rq_ display.p_display[i]
#define Acu_conn_rq_x_display_type(i)	Acu_conn_rq_ display.type[i]
#define Acu_conn_rq_x_display_size(i)	Acu_conn_rq_ display.size[i]
#define Acu_conn_rq_a_display_list      &(Acu_conn_rq_ display)

#define	Acu_conn_rq_a_called_nb			((char  *)p_data        + Acu_conn_rq_size)
#define	Acu_conn_rq_a_ph_num			Acu_conn_rq_a_called_nb

#define	Acu_conn_rq_a_calling_nb		(Acu_conn_rq_a_called_nb   + Acu_conn_rq_called_nb_size + 1)
#define	Acu_conn_rq_a_calling_nb2		(Acu_conn_rq_a_calling_nb  + Acu_conn_rq_calling_nb_size + 1)

#define	Acu_conn_rq_a_redir_nb			(Acu_conn_rq_a_calling_nb2 + Acu_conn_rq_calling_nb2_size + 1)

#define	Acu_conn_rq_a_uui				(Acu_conn_rq_a_redir_nb   + Acu_conn_rq_redir_nb_size + 1)
#define	Acu_conn_rq_a_facility			(Acu_conn_rq_a_uui         + Acu_conn_rq_uui_size + 1)
#define	Acu_conn_rq_a_display			(Acu_conn_rq_a_facility    + Acu_conn_rq_facility_size + 1)
#define Acu_conn_rq_a_pcs_user			(Acu_conn_rq_a_display	   + Acu_conn_rq_display_size + 1)

#define	Acu_conn_rq_progress_ind_nb		Acu_conn_rq_ progress_ind.nb
#define	Acu_conn_rq_progress_location	Acu_conn_rq_progress_loc
#define	Acu_conn_rq_progress_description Acu_conn_rq_progress_descr
/* aliases */
#define	Acu_conn_rq_progress_loc		Acu_conn_rq_ progress_ind.t[0].loc
#define	Acu_conn_rq_progress_descr		Acu_conn_rq_ progress_ind.t[0].descr
/* access to other occurencies */
#define	Acu_conn_rq_progress_loc_x(i)	Acu_conn_rq_ progress_ind.t[i].loc
#define	Acu_conn_rq_progress_descr_x(i)	Acu_conn_rq_ progress_ind.t[i].descr

#define Acu_conn_rq_a_called_nb_sub     (Acu_conn_rq_a_pcs_user    + Acu_conn_rq_pcs_user_size + 1)
#define Acu_conn_rq_a_calling_nb_sub    (Acu_conn_rq_a_called_nb_sub    + Acu_conn_rq_called_nb_sub_size + 1)

#define Acu_conn_rq_a_ss_cnip_name     (Acu_conn_rq_a_calling_nb_sub    + Acu_conn_rq_calling_nb_sub_size + 1)
#define Acu_conn_rq_a_tsp_ie_list			(Acu_conn_rq_a_ss_cnip_name    + Acu_conn_rq_ss_cnip_name_size + 1)


#	define	Acu_conn_rq_a_first_other		(Acu_conn_rq_a_tsp_ie_list		+ Acu_conn_rq_tsp_ie_list_size + 1)

#define Acu_conn_rq_a_end_strings			(uchar  *)Round8((unsigned long)Acu_conn_rq_a_first_other)
#define Acu_conn_rq_total_size				(Acu_conn_rq_a_end_strings - (uchar  *)p_data) /* not including the ext parms */
#define Acu_conn_rq_start_ext_data			Acu_conn_rq_total_size

#if _CC_SPID_INFO == ON
#	define	Acu_conn_rq_p_endpoint_id		Acu_conn_rq_ endpoint_id
#	define	Acu_conn_rq_endpoint_action		Acu_conn_rq_ endpoint_id.action
#	define	Acu_conn_rq_usid				Acu_conn_rq_ endpoint_id.usid
#	define	Acu_conn_rq_tid					Acu_conn_rq_ endpoint_id.tid
#	define	Acu_conn_rq_interpreter			Acu_conn_rq_ endpoint_id.interpreter
#endif

#define	Acu_conn_rq_size					(Rnd_sizeof (struct acu_conn_rq_args))

/*--------------------------
*
*            =========================================
*             Specifying multiple 'called_nb' fields:
*            =========================================
*
* When calling with multiple B-channels, e.g. aggregated channels,
* the user might have to specify multiple called numbers.
* The first called number is stored using the
* 'Acu_conn_rq_called_nb_size' and 'Acu_conn_rq_a_called_nb' macros,
* as for a single-called-nb call.
* The additional 'called-nb' strings must be stored AFTER having stored
* the last variable-length field (i.e. 'facility', or 'flight_number'
* for ARINC networks).
* The format for each additional 'called_nb' is:
*     - one byte for the exact size of the string,
*     - immediately followed by the string itself.
*
* The additional called-numbers will appear in the data area as follows:
*
* |-----------|
* |-----------| (fixed-length fields)
* |-----------|
* |-----------|
* |           |
* |           | (variable-length fields, e.g. 'called_nb', 'calling_nb',
* |           | etc...)
* |           |
* |-----------|
* |   last    |
* | variable  | ('facility', or 'flight_number' for ARINC networks).
* |  length   |
* |  field    |
* |-----------|
* |  size #1  | (size of first additional called-nb string)
* |-----------|
* |           |
* |  called   | (digits, ended with a '\0' or not)
* |    nb     |
* |    #1     |
* |           |
* |-----------|
* |  size #2  | (size of second additional called-nb string)
* |-----------|
* |  called   |
* |    nb     | (digits, ended with a '\0' or not)
* |    #2     |
* |-----------|
* |     0     | (indicates the end of the called-nb strings list)
* -------------
*
*
* The address of the 'size #1' field is given by the
* 'Acu_conn_rq_a_first_other' macro.
*
* The 'size' fields are 1 byte long; their type is 'acu_size_t', their
* length is given by the 'ACU_SIZE_FIELDS_LENGTH' macro.
*
* If p points to an 'other' 'size' field, then one can use the following
* macro to determine the address of the next 'other' 'size' field:
*
*     Acu_a_next_other (p);
*
* ===============
* !!! WARNING !!!
* ===============
*
* If no 'other' called_nb is to be specified by the application, then
* the first 'size' field of the 'other' called-numbers MUST be set to 0.
*
*--------------------------*/

#define Acu_a_next_other(p_current_other) \
p_current_other += (ACU_SIZE_FIELD_LGTH + *(acu_size_t  *)p_current_other)

#define Acu_conn_rq_other_called_nb_size(idx,size)          \
			{                                                   \
			char  *address;                              \
			Acu_conn_rq_a_other_called_nb (idx, address);   \
			size = *(address - ACU_SIZE_FIELD_LGTH);        \
			}

#define Acu_conn_rq_a_other_called_nb(idx,ret_address)      \
			{													\
			uchar i;                                        \
			ret_address = Acu_conn_rq_a_first_other;        \
			for (i = 1; i < idx; i++) {                     \
			Acu_a_next_other (ret_address);             \
			}                                               \
			ret_address += ACU_SIZE_FIELD_LGTH;             \
			}

/*---------------------------------------------------------------------------
*
*	ACU_CONN_IN		signal an incoming call.
*
*	Arguments :
*       Acu_conn_in_call_ref_length	: length of call reference
*       Acu_conn_in_call_ref_value	: call reference associated with the call	
*		Acu_conn_in_service 		: service requested by the remote
*		Acu_conn_in_service_list_id : service list id associated with the selected services list
*		Acu_conn_in_ph_rate 		: physical rate (for all services)
*		Acu_conn_in_user_rate		: user rate (for V.110 and V.120 services only)
*		Acu_conn_in_syn_asyn  		: synchronous/asynchronous (for V.110 and V.120 services only)
*		Acu_conn_in_stop_bits   	: nb of stop bits (for V.110 and V.120 services only)
*		Acu_conn_in_data_bits   	: nb of data bits (for V.110 and V.120 services only)
*		Acu_conn_in_parity      	: parity (for V.110 and V.120 services only)
*		Acu_conn_in_interworking	: interworking indication (ON/OFF)
*		Acu_conn_in_sending_complete: Sending-complete IE received (ON/OFF)
*       Acu_conn_in_data_chani_nb   : nb of elements in the chani_list field
*       Acu_conn_in_data_chani      : data channel to use (B1, B2, etc, D)
*		Acu_conn_in_calling_nb_pres	: calling nb presentation
*		Acu_conn_in_calling_nb_type	: calling nb type
*		Acu_conn_in_calling_nb_screen	: calling nb screening indicator
*		Acu_conn_in_calling_nb_size	: calling number size in bytes
*		Acu_conn_in_a_calling_nb	: address of the calling number.
*		Acu_conn_in_calling_nb2_pres: 2nd calling nb presentation
*		Acu_conn_in_calling_nb2_type: 2nd calling nb type
*		Acu_conn_in_calling_nb2_screen	: 2nd calling nb screening indicator
*		Acu_conn_in_calling_nb2_size: 2nd calling number size in bytes
*		Acu_conn_in_a_calling_nb2	: address of the 2nd calling number.
*		Acu_conn_in_ph_num_size		: alias for Acu_conn_in_calling_nb_size
*		Acu_conn_in_a_ph_num 		: alias for Acu_conn_in_a_calling_nb
*		Acu_conn_in_called_nb_type	: called nb type
*		Acu_conn_in_called_nb_plan	: called nb plan
*		Acu_conn_in_called_nb_size	: called number*sub-address size in bytes
*		Acu_conn_in_a_called_nb 	: address of the called number*sub-address.
*       Acu_conn_in_orig_called_nb_plan		: (DMS only) original called number plan
*       Acu_conn_in_orig_called_nb_type		: (DMS only) original called number type
*       Acu_conn_in_orig_called_nb_pres		: (DMS only) original called number presentation ind
*       Acu_conn_in_orig_called_nb_screen	: (DMS only) original called number screening ind
*       Acu_conn_in_orig_called_nb_reason	: (DMS only) original called number reason
*       Acu_conn_in_orig_called_nb_cfnr		: (DMS only) original called number call forwarding no reply undergone indicator
*       Acu_conn_in_orig_called_nb_count	: (DMS only) original called number redir counter
*       Acu_conn_in_orig_called_nb_size		: (DMS only) original called number size
*       Acu_conn_in_a_orig_called_nb		: (DMS only) address of original called number
*		Acu_conn_in_uui_protocol,
*		Acu_conn_in_uui_size,
*		Acu_conn_in_a_uui			: ISDN user to User Information
*		Acu_conn_in_facility_size,
*		Acu_conn_in_a_facility		: ISDN facility
*		Acu_conn_in_display_size,
*		Acu_conn_in_a_display		: ISDN display Information
*		Acu_conn_in_pcs_user_protocol,
*		Acu_conn_in_pcs_user_size,
*		Acu_conn_in_a_pcs_user		: ISDN PCS-to-User/User-to-PCS Info.
*		Acu_conn_in_dest_call_appear: destination call_appearance
*		Acu_conn_in_progress_location		: progress description
*		Acu_conn_in_progress_description	: progress location
*
*		Warning : when building this primitive, the phone number field must
*		be filled BEFORE the UUI field.
*
*--------------------------------------------------------------------------*/

struct acu_conn_in_args {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif

    struct acu_call_ref call_ref;	    /* call reference information */

    struct layer_1_info layer_1_info;	/* layer 1 information field */
	struct chani_list chani_list;		/* list of channel ids to use for data transfer */
	struct acu_calling_nb calling_nb;	/* calling nb information */
	struct acu_calling_nb calling_nb2;	/* second calling nb information */
	struct acu_called_nb  called_nb;	/* called nb information */
	struct acu_redir_nb   redir_nb;		/* redirected nb information */

	struct acu_orig_called_nb   orig_called_nb;  /* original called number (DMS specific) */
	struct acu_display_list display;	/* display list */
	struct acu_progress_ind progress_ind;/* progress indicator */

	struct acu_subaddress called_nb_sub;
	struct acu_subaddress calling_nb_sub;
	struct acu_name  ss_cnip_name;
    
    
	uchar	service;					/* (tele)service requested by the remote */
	uchar	service_list_id;			/* service list id associated with the selected services list */
	uchar	interworking;				/* interworking indication (ON/OFF) */
	uchar	sending_complete;			/* Sending-complete information element reception */
    
	uchar      uui_protocol;			/* UUI protocol-discriminator value */
	acu_size_t uui_size;				/* size of the ISDN User to User information field */
	acu_size_t facility_size;			/* size of the facility */
	uchar      pcs_user_protocol;		/* PCS-to-User or User-to-PCS protocol-discriminator value */
	acu_size_t pcs_user_size;			/* size of the PCS-to-User or User-to-PCS information */
		
	acu_size_t q931_size;				/* size of Q.931 message */

	uchar	dest_call_appear;			/* Destination call appearence */
	uchar	semi_permanent_circuit;		/* semi-permanent circuit indication (ON/OFF) */
	/* phone number is just here */
	/* then all the other strings in order */
	uchar   orig_line_info;				/* originating line info  */
	pad3		
		
};

#define	Acu_conn_in_					((struct acu_conn_in_args  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_conn_in_ext_parms_nb		Acu_conn_in_ ext_descr.nb
#	define Acu_conn_in_ext_parms_lgth	Acu_conn_in_ ext_descr.lgth
#	define Acu_conn_in_a_ext_parms		((Acu_ext_descr_offset = Acu_conn_in_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define Acu_conn_in_call_ref_length		Acu_conn_in_ call_ref.length
#define Acu_conn_in_call_ref_value		Acu_conn_in_ call_ref.value

#define	Acu_conn_in_service				Acu_conn_in_ service
#define Acu_conn_in_service_list_id		Acu_conn_in_ service_list_id

#define	Acu_conn_in_a_layer_1_info		((struct layer_1_info  *)&Acu_conn_in_ layer_1_info)
#define	Acu_conn_in_ph_rate				Acu_conn_in_ layer_1_info.ph_rate
#define	Acu_conn_in_user_rate			Acu_conn_in_ layer_1_info.user_rate
#define	Acu_conn_in_syn_asyn			Acu_conn_in_ layer_1_info.syn_asyn
#define	Acu_conn_in_stop_bits			Acu_conn_in_ layer_1_info.stop_bits
#define	Acu_conn_in_data_bits			Acu_conn_in_ layer_1_info.data_bits
#define	Acu_conn_in_parity				Acu_conn_in_ layer_1_info.parity

#define	Acu_conn_in_interworking		Acu_conn_in_ interworking
#define	Acu_conn_in_sending_complete	Acu_conn_in_ sending_complete

#define Acu_conn_in_data_chani_nb       Acu_conn_in_ chani_list.nb
#define Acu_conn_in_data_chani          Acu_conn_in_ chani_list.tab[0].chan_id
#define Acu_conn_in_data_chani_nai      Acu_conn_in_ chani_list.tab[0].nai
#define Acu_conn_in_data_chani_tab(i)   Acu_conn_in_ chani_list.tab[i].chan_id
#define Acu_conn_in_data_chani_tab_nai(i) Acu_conn_in_ chani_list.tab[i].nai
#define Acu_conn_in_data_chani_excl     Acu_conn_in_ chani_list.chan_id_excl

#define	Acu_conn_in_calling_nb_pres		Acu_conn_in_ calling_nb.pres
#define	Acu_conn_in_calling_nb_type		Acu_conn_in_ calling_nb.type
#define	Acu_conn_in_calling_nb_plan		Acu_conn_in_ calling_nb.plan
#define	Acu_conn_in_calling_nb_screen	Acu_conn_in_ calling_nb.screen
#define	Acu_conn_in_calling_nb_size		Acu_conn_in_ calling_nb.size
#define	Acu_conn_in_ph_num_size			Acu_conn_in_ calling_nb_size

#define	Acu_conn_in_calling_nb2_pres	Acu_conn_in_ calling_nb2.pres
#define	Acu_conn_in_calling_nb2_type	Acu_conn_in_ calling_nb2.type
#define	Acu_conn_in_calling_nb2_screen	Acu_conn_in_ calling_nb2.screen
#define	Acu_conn_in_calling_nb2_size	Acu_conn_in_ calling_nb2.size

#define	Acu_conn_in_called_nb_type		Acu_conn_in_ called_nb.type
#define	Acu_conn_in_called_nb_plan		Acu_conn_in_ called_nb.plan
#define	Acu_conn_in_called_nb_size		Acu_conn_in_ called_nb.size

#define	Acu_conn_in_redir_nb_pres		Acu_conn_in_ redir_nb.pres
#define	Acu_conn_in_redir_nb_type		Acu_conn_in_ redir_nb.type
#define	Acu_conn_in_redir_nb_plan		Acu_conn_in_ redir_nb.plan
#define	Acu_conn_in_redir_nb_screen		Acu_conn_in_ redir_nb.screen
#define	Acu_conn_in_redir_nb_reason		Acu_conn_in_ redir_nb.reason
#define	Acu_conn_in_redir_nb_size		Acu_conn_in_ redir_nb.size

#define	Acu_conn_in_orig_called_nb_plan			Acu_conn_in_ orig_called_nb.plan
#define	Acu_conn_in_orig_called_nb_type			Acu_conn_in_ orig_called_nb.type
#define	Acu_conn_in_orig_called_nb_pres			Acu_conn_in_ orig_called_nb.pres
#define	Acu_conn_in_orig_called_nb_screen		Acu_conn_in_ orig_called_nb.screen
#define	Acu_conn_in_orig_called_nb_reason		Acu_conn_in_ orig_called_nb.reason
#define	Acu_conn_in_orig_called_nb_cfnr			Acu_conn_in_ orig_called_nb.cfnr
#define	Acu_conn_in_orig_called_nb_count		Acu_conn_in_ orig_called_nb.count
#define	Acu_conn_in_orig_called_nb_size			Acu_conn_in_ orig_called_nb.size

#define	Acu_conn_in_called_nb_sub_type		Acu_conn_in_ called_nb_sub.type
#define	Acu_conn_in_called_nb_sub_odd_even	Acu_conn_in_ called_nb_sub.odd_even
#define	Acu_conn_in_called_nb_sub_size		Acu_conn_in_ called_nb_sub.size
#define	Acu_conn_in_calling_nb_sub_type		Acu_conn_in_ calling_nb_sub.type
#define	Acu_conn_in_calling_nb_sub_odd_even	Acu_conn_in_ calling_nb_sub.odd_even
#define	Acu_conn_in_calling_nb_sub_size		Acu_conn_in_ calling_nb_sub.size

#define	Acu_conn_in_ss_cnip_name_size		Acu_conn_in_ ss_cnip_name.size
#define	Acu_conn_in_ss_cnip_name_pres		Acu_conn_in_ ss_cnip_name.pres
#define	Acu_conn_in_ss_cnip_name_active		Acu_conn_in_ ss_cnip_name.active
#define	Acu_conn_in_ss_cnip_name		    Acu_conn_in_ ss_cnip_name

#define	Acu_conn_in_uui_protocol		Acu_conn_in_ uui_protocol
#define	Acu_conn_in_uui_size			Acu_conn_in_ uui_size
#define	Acu_conn_in_facility_size		Acu_conn_in_ facility_size
#define	Acu_conn_in_display_size		Acu_conn_in_x_display_total_size
#define	Acu_conn_in_pcs_user_protocol	Acu_conn_in_ pcs_user_protocol
#define Acu_conn_in_pcs_user_size		Acu_conn_in_ pcs_user_size

#define Acu_conn_in_x_display_nb		Acu_conn_in_ display.nb
#define Acu_conn_in_x_display_total_size Acu_conn_in_ display.total_size
#define Acu_conn_in_x_p_display(i) 		Acu_conn_in_ display.p_display[i]
#define Acu_conn_in_x_display_type(i)	Acu_conn_in_ display.type[i]
#define Acu_conn_in_x_display_size(i)	Acu_conn_in_ display.size[i]
#define Acu_conn_in_a_display_list      &(Acu_conn_in_ display)

#define	Acu_conn_in_a_calling_nb		((char  *)p_data       + Acu_conn_in_size)
#define	Acu_conn_in_a_ph_num			Acu_conn_in_a_calling_nb
#define	Acu_conn_in_a_calling_nb2		(Acu_conn_in_a_calling_nb + Acu_conn_in_calling_nb_size)
#define	Acu_conn_in_a_called_nb			(Acu_conn_in_a_calling_nb2+ Acu_conn_in_calling_nb2_size)
#define	Acu_conn_in_a_redir_nb			(Acu_conn_in_a_called_nb  + Acu_conn_in_called_nb_size)
#define	Acu_conn_in_a_orig_called_nb	(Acu_conn_in_a_redir_nb   + Acu_conn_in_redir_nb_size)
#define	Acu_conn_in_a_uui				(Acu_conn_in_a_orig_called_nb   + Acu_conn_in_orig_called_nb_size)
#define	Acu_conn_in_a_facility			(Acu_conn_in_a_uui        + Acu_conn_in_uui_size)
#define	Acu_conn_in_a_display			(Acu_conn_in_a_facility   + Acu_conn_in_facility_size)
#define Acu_conn_in_a_pcs_user			(Acu_conn_in_a_display    + Acu_conn_in_display_size)

#define Acu_conn_in_q931_size			Acu_conn_in_ q931_size

#define Acu_conn_in_orig_line_info 		Acu_conn_in_ orig_line_info

#define	Acu_conn_in_progress_ind_nb		Acu_conn_in_ progress_ind.nb
#define	Acu_conn_in_progress_location	Acu_conn_in_progress_loc
#define	Acu_conn_in_progress_description Acu_conn_in_progress_descr
/* aliases */
#define	Acu_conn_in_progress_loc		Acu_conn_in_ progress_ind.t[0].loc
#define	Acu_conn_in_progress_descr		Acu_conn_in_ progress_ind.t[0].descr
/* access to other occurencies */
#define	Acu_conn_in_progress_loc_x(i)	Acu_conn_in_ progress_ind.t[i].loc
#define	Acu_conn_in_progress_descr_x(i)	Acu_conn_in_ progress_ind.t[i].descr

#define Acu_conn_in_a_called_nb_sub     (Acu_conn_in_a_pcs_user    + Acu_conn_in_pcs_user_size)
#define Acu_conn_in_a_calling_nb_sub    (Acu_conn_in_a_called_nb_sub    + Acu_conn_in_called_nb_sub_size)


#define Acu_conn_in_a_ss_cnip_name      (Acu_conn_in_a_calling_nb_sub    + Acu_conn_in_calling_nb_sub_size)
#define Acu_conn_in_a_q931					(Acu_conn_in_a_ss_cnip_name    + Acu_conn_in_ss_cnip_name_size)


#	define	Acu_conn_in_a_end_strings		(uchar  *)Round8((unsigned long)Acu_conn_in_a_q931 + Acu_conn_in_q931_size)
#define Acu_conn_in_start_ext_data			(Acu_conn_in_a_end_strings-(uchar  *)p_data)

#define Acu_conn_in_dest_call_appear		Acu_conn_in_ dest_call_appear
#define Acu_conn_in_semi_permanent_circuit	Acu_conn_in_ semi_permanent_circuit

#define	Acu_conn_in_size					(Rnd_sizeof (struct acu_conn_in_args))

/*---------------------------------------------------------------------------
*
*	ACU_SETUP_REPORT_IN		signals an incompatible incoming call.
*
*	WARNING : this message is generated when an incompatible incoming call
*			  has been received. It uses the ACU_SAPI_MGT sapi. Its structure
*			  is the same as an ACU_CONN_IN. It is used as an information
*			  report only, no action should be taken in order to answer the
*			  call. It is only generated in an ISDN context.
*
*	Arguments : use the Acu_conn_in_... macros.
*
*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
*
*	ACU_CONN_RS			request answering to an incoming call.
*
*	Arguments :
*		Acu_conn_rs_priority		: answer priority (ACU_PHIGH, ACU_PLOW)
*		Acu_conn_rs_service			: requested (tele)service
*		Acu_conn_rs_ph_rate			: physical rate (for all services)
*		Acu_conn_rs_user_rate		: user rate (for V.110 and V.120 services only)
*		Acu_conn_rs_syn_asyn  		: synchronous/asynchronous (for V.110 and V.120 services only)
*		Acu_conn_rs_stop_bits   	: nb of stop bits (for V.110 and V.120 services only)
*		Acu_conn_rs_data_bits   	: nb of data bits (for V.110 and V.120 services only)
*		Acu_conn_rs_parity      	: parity (for V.110 and V.120 services only)
*       Acu_conn_rs_data_chani_nb   : nb of elements in the chani_list field
*       Acu_conn_rs_data_chani  	: data channel to use (B1, B2, etc, D, or 0 for any)
*		Acu_conn_rs_year			: year
*		Acu_conn_rs_month;			: month
*		Acu_conn_rs_day;			: day
*		Acu_conn_rs_hour;			: hour
*		Acu_conn_rs_minute;			: minute
*		Acu_conn_rs_second;			: second
*		Acu_conn_rs_uui_protocol,
*		Acu_conn_rs_uui_size,
*		Acu_conn_rs_a_uui			: ISDN user to User Information
*		Acu_conn_rs_facility_size,
*		Acu_conn_rs_a_facility		: ISDN facility
*		Acu_conn_rs_pcs_user_protocol,
*		Acu_conn_rs_pcs_user_size,
*		Acu_conn_rs_a_pcs_user		: ISDN PCS-to-User/User-to-PCS Info.
*		Acu_conn_rs_signal_val 		: signal value
*
*--------------------------------------------------------------------------*/

struct acu_conn_rs_args {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif
    
	struct layer_1_info layer_1_info;	/* layer 1 information field */
	struct chani_list   chani_list;		/* list of channel ids to use for data transfer */
	struct acu_charging_info charging_info;	/* charging information */
	struct acu_date_time date_time;		/* date and time */
	struct acu_calling_nb   connected_nb; /*number which was connected, Q.SIG Only*/ 	
	struct acu_subaddress   connected_sub;/*subaddress which was connected, Q.SIG Only*/ 	
	struct acu_display_list display;	/* display list */
	struct acu_name  ss_cnip_name;

	uchar      pcs_user_protocol;		/* PCS-to-User or User-to-PCS protocol-discriminator value */
	acu_size_t pcs_user_size;			/* size of the PCS-to-User or User-to-PCS information */
    
	uchar	signal_val;					/* signal value */

	uchar	priority;					/* phone call priority */
	uchar	service;					/* requested service */
    
	uchar      uui_protocol;			/* UUI protocol-discriminator value */
	acu_size_t uui_size;				/* size of the ISDN User to User information field */
	acu_size_t facility_size;			/* size of the facility */
	acu_size_t tsp_ie_list_size;		/* length of the list of transparent IE's */
	pad7
		
		/* UUI is just here */
		/* then all the other strings in order */
};

#define	Acu_conn_rs_					((struct acu_conn_rs_args  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_conn_rs_ext_parms_nb		Acu_conn_rs_ ext_descr.nb
#	define Acu_conn_rs_ext_parms_lgth	Acu_conn_rs_ ext_descr.lgth
#	define Acu_conn_rs_a_ext_parms		((Acu_ext_descr_offset = Acu_conn_rs_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define	Acu_conn_rs_priority			Acu_conn_rs_ priority
#define	Acu_conn_rs_service				Acu_conn_rs_ service
#define	Acu_conn_rs_a_layer_1_info		((struct layer_1_info  *)&Acu_conn_rs_ layer_1_info)
#define	Acu_conn_rs_ph_rate				Acu_conn_rs_ layer_1_info.ph_rate
#define	Acu_conn_rs_user_rate			Acu_conn_rs_ layer_1_info.user_rate
#define	Acu_conn_rs_syn_asyn			Acu_conn_rs_ layer_1_info.syn_asyn
#define	Acu_conn_rs_stop_bits			Acu_conn_rs_ layer_1_info.stop_bits
#define	Acu_conn_rs_data_bits			Acu_conn_rs_ layer_1_info.data_bits
#define	Acu_conn_rs_parity				Acu_conn_rs_ layer_1_info.parity
#define Acu_conn_rs_data_chani_nb       Acu_conn_rs_ chani_list.nb
#define Acu_conn_rs_data_chani          Acu_conn_rs_ chani_list.tab[0].chan_id
#define Acu_conn_rs_data_chani_nai      Acu_conn_rs_ chani_list.tab[0].nai
#define Acu_conn_rs_data_chani_tab(i)   Acu_conn_rs_ chani_list.tab[i].chan_id
#define Acu_conn_rs_data_chani_tab_nai(i) Acu_conn_rs_ chani_list.tab[i].nai
#define Acu_conn_rs_data_chani_excl     Acu_conn_rs_ chani_list.chan_id_excl
#define	Acu_conn_rs_charging_available	Acu_conn_rs_ charging_info.available
#define Acu_conn_rs_charging_value     	Acu_conn_rs_ charging_info.value
#define Acu_conn_rs_charging_type     	Acu_conn_rs_ charging_info.type
#define Acu_conn_rs_charging_period    	Acu_conn_rs_ charging_info.period
#define Acu_conn_rs_charging_multi     	Acu_conn_rs_ charging_info.multi
#define Acu_conn_rs_charging	     	Acu_conn_rs_charging_value	/* alias */
#define	Acu_conn_rs_date_available		Acu_conn_rs_ date_time.available
#define	Acu_conn_rs_year				Acu_conn_rs_ date_time.year
#define	Acu_conn_rs_month				Acu_conn_rs_ date_time.month
#define	Acu_conn_rs_day					Acu_conn_rs_ date_time.day
#define	Acu_conn_rs_hour				Acu_conn_rs_ date_time.hour
#define	Acu_conn_rs_minute				Acu_conn_rs_ date_time.minute
#define	Acu_conn_rs_second				Acu_conn_rs_ date_time.second
#define	Acu_conn_rs_a_date_time			&(Acu_conn_rs_ date_time)

#define	Acu_conn_rs_ss_cnip_name_size		Acu_conn_rs_ ss_cnip_name.size
#define	Acu_conn_rs_ss_cnip_name_pres		Acu_conn_rs_ ss_cnip_name.pres
#define	Acu_conn_rs_ss_cnip_name_active		Acu_conn_rs_ ss_cnip_name.active
#define	Acu_conn_rs_ss_cnip_name	 		Acu_conn_rs_ ss_cnip_name
/* aliases */
#define	Acu_conn_rs_ss_conp_name_size		Acu_conn_rs_ss_cnip_name_size
#define	Acu_conn_rs_ss_conp_name_pres		Acu_conn_rs_ss_cnip_name_pres
#define	Acu_conn_rs_ss_conp_name_active		Acu_conn_rs_ss_cnip_name_active
#define	Acu_conn_rs_ss_conp_name			Acu_conn_rs_ss_cnip_name	 

#define	Acu_conn_rs_connected_nb	    Acu_conn_rs_ connected_nb
#define	Acu_conn_rs_connected_nb_pres	Acu_conn_rs_ connected_nb.pres
#define	Acu_conn_rs_connected_nb_plan	Acu_conn_rs_ connected_nb.plan
#define	Acu_conn_rs_connected_nb_type	Acu_conn_rs_ connected_nb.type
#define	Acu_conn_rs_connected_nb_screen	Acu_conn_rs_ connected_nb.screen
#define	Acu_conn_rs_connected_nb_size	Acu_conn_rs_ connected_nb.size

#define	Acu_conn_rs_connected_sub			Acu_conn_rs_ connected_sub
#define	Acu_conn_rs_connected_sub_type		Acu_conn_rs_ connected_sub.type
#define	Acu_conn_rs_connected_sub_odd_even	Acu_conn_rs_ connected_sub.odd_even
#define	Acu_conn_rs_connected_sub_size		Acu_conn_rs_ connected_sub.size

#define	Acu_conn_rs_uui_protocol		Acu_conn_rs_ uui_protocol
#define	Acu_conn_rs_uui_size			Acu_conn_rs_ uui_size
#define	Acu_conn_rs_facility_size		Acu_conn_rs_ facility_size
#define	Acu_conn_rs_display_size		Acu_conn_rs_x_display_total_size
#define Acu_conn_rs_pcs_user_protocol	Acu_conn_rs_ pcs_user_protocol
#define Acu_conn_rs_pcs_user_size		Acu_conn_rs_ pcs_user_size

#define Acu_conn_rs_x_display_nb		Acu_conn_rs_ display.nb
#define Acu_conn_rs_x_display_total_size Acu_conn_rs_ display.total_size
#define Acu_conn_rs_x_p_display(i) 		Acu_conn_rs_ display.p_display[i]
#define Acu_conn_rs_x_display_type(i)	Acu_conn_rs_ display.type[i]
#define Acu_conn_rs_x_display_size(i)	Acu_conn_rs_ display.size[i]
#define Acu_conn_rs_a_display_list      &(Acu_conn_rs_ display)

#define Acu_conn_rs_signal_val 			Acu_conn_rs_ signal_val

#define Acu_conn_rs_tsp_ie_list_size	Acu_conn_rs_ tsp_ie_list_size

#define	Acu_conn_rs_a_uui				((char  *)p_data + Acu_conn_rs_size)
#define	Acu_conn_rs_a_facility			(Acu_conn_rs_a_uui  + Acu_conn_rs_uui_size + 1)
#define	Acu_conn_rs_a_display			(Acu_conn_rs_a_facility + Acu_conn_rs_facility_size + 1)
#define	Acu_conn_rs_a_connected_nb		(Acu_conn_rs_a_display + Acu_conn_rs_display_size + 1)
#define	Acu_conn_rs_a_connected_sub		(Acu_conn_rs_a_connected_nb + Acu_conn_rs_connected_nb_size + 1)
#define Acu_conn_rs_a_pcs_user			(Acu_conn_rs_a_connected_sub  + Acu_conn_rs_connected_sub_size  + 1)

#define Acu_conn_rs_a_ss_cnip_name      (Acu_conn_rs_a_pcs_user    + Acu_conn_rs_pcs_user_size + 1)
/* alias */
#define Acu_conn_rs_a_ss_conp_name      Acu_conn_rs_a_ss_cnip_name
#define Acu_conn_rs_a_tsp_ie_list		(Acu_conn_rs_a_ss_cnip_name + Acu_conn_rs_ss_cnip_name_size + 1)

#define Acu_conn_rs_a_end_strings		(uchar  *)Round8((unsigned long)Acu_conn_rs_a_tsp_ie_list + Acu_conn_rs_tsp_ie_list_size + 1)
#define Acu_conn_rs_total_size			(Acu_conn_rs_a_end_strings - (uchar  *)p_data) /* not including the ext parms */
#define Acu_conn_rs_start_ext_data		Acu_conn_rs_total_size

#define	Acu_conn_rs_size				(Rnd_sizeof (struct acu_conn_rs_args))

/*---------------------------------------------------------------------------
*
*	ACU_CONN_CO		signal successful connection of an incoming or outgoing
*					call.
*
*	Arguments:
*       Acu_conn_co_call_ref_length	: length of call reference
*       Acu_conn_co_call_ref_value	: call reference associated with the call	
*		Acu_conn_co_service 		: service finally agreed
*       Acu_conn_co_data_chani_nb	: nb of elements in the chani_list field
*       Acu_conn_co_data_chani  	: data channel to use (B1, B2, etc, D)
*		Acu_conn_co_charging_value	: charging value (nb of units)
*		Acu_conn_co_charging_type	: charging type
*		Acu_conn_co_charging_period	: charging period
*		Acu_conn_co_charging_multi	: charging multiplier
*		Acu_conn_co_year			: year
*		Acu_conn_co_month;			: month
*		Acu_conn_co_day;			: day
*		Acu_conn_co_hour;			: hour
*		Acu_conn_co_minute;			: minute
*		Acu_conn_co_second;			: second
*		Acu_conn_co_uui_protocol,
*		Acu_conn_co_uui_size,
*		Acu_conn_co_a_uui			: ISDN user to User Information
*		Acu_conn_co_facility_size,
*		Acu_conn_co_a_facility		: ISDN facility
*		Acu_conn_co_display_size,
*		Acu_conn_co_a_display		: ISDN display Information
*		Acu_conn_co_pcs_user_protocol,
*		Acu_conn_co_pcs_user_size,
*		Acu_conn_co_a_pcs_user		: ISDN PCS-to-User/User-to-PCS Info.
*		Acu_conn_co_signal_val 		: signal value
*
*--------------------------------------------------------------------------*/

struct acu_conn_co_args {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif

    struct acu_call_ref call_ref;	    /* call reference information */

	struct chani_list    chani_list;    /* list of channel ids to use for data transfer */
	struct acu_charging_info charging_info;	/* charging information */
	struct acu_date_time date_time;		/* date and time */
	struct acu_redir_nb   redir_nb;		/* redirected nb information */

	struct acu_calling_nb   connected_nb; /*number which was connected, Q.SIG Only*/ 	
	struct acu_subaddress   connected_sub;/*subaddress which was connected, Q.SIG Only*/ 	
	struct acu_display_list display;	/* display list */
	struct acu_name  ss_cnip_name;

	uchar      pcs_user_protocol;		/* PCS-to-User or User-to-PCS protocol-discriminator value */
	acu_size_t pcs_user_size;			/* size of the PCS-to-User or User-to-PCS information */
    
	uchar	signal_val;	 				/* signal value */
    
	uchar	service;					/* agreed (tele)service */
    
	uchar      uui_protocol;			/* UUI protocol-discriminator value */
	acu_size_t uui_size;				/* size of the ISDN User to User information field */
	acu_size_t facility_size;			/* size of the facility */
    
	acu_size_t q931_size;				/* size of Q.931 message */
		
		/* UUI is just here */
		/* then all the other strings in order */
};

#define	Acu_conn_co_					((struct acu_conn_co_args  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_conn_co_ext_parms_nb		Acu_conn_co_ ext_descr.nb
#	define Acu_conn_co_ext_parms_lgth	Acu_conn_co_ ext_descr.lgth
#	define Acu_conn_co_a_ext_parms		((Acu_ext_descr_offset = Acu_conn_co_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define Acu_conn_co_call_ref_length		Acu_conn_co_ call_ref.length
#define Acu_conn_co_call_ref_value		Acu_conn_co_ call_ref.value

#define	Acu_conn_co_service				Acu_conn_co_ service
#define Acu_conn_co_data_chani_nb       Acu_conn_co_ chani_list.nb
#define Acu_conn_co_data_chani          Acu_conn_co_ chani_list.tab[0].chan_id
#define Acu_conn_co_data_chani_nai      Acu_conn_co_ chani_list.tab[0].nai
#define Acu_conn_co_data_chani_tab(i)   Acu_conn_co_ chani_list.tab[i].chan_id
#define Acu_conn_co_data_chani_tab_nai(i) Acu_conn_co_ chani_list.tab[i].nai
#define Acu_conn_co_data_chani_excl     Acu_conn_co_ chani_list.chan_id_excl
#define	Acu_conn_co_charging_available	Acu_conn_co_ charging_info.available
#define Acu_conn_co_charging_value     	Acu_conn_co_ charging_info.value
#define Acu_conn_co_charging_type     	Acu_conn_co_ charging_info.type
#define Acu_conn_co_charging_period    	Acu_conn_co_ charging_info.period
#define Acu_conn_co_charging_multi     	Acu_conn_co_ charging_info.multi
#define Acu_conn_co_charging	     	Acu_conn_co_charging_value	/* alias */
#define	Acu_conn_co_date_available		Acu_conn_co_ date_time.available
#define	Acu_conn_co_year				Acu_conn_co_ date_time.year
#define	Acu_conn_co_month				Acu_conn_co_ date_time.month
#define	Acu_conn_co_day					Acu_conn_co_ date_time.day
#define	Acu_conn_co_hour				Acu_conn_co_ date_time.hour
#define	Acu_conn_co_minute				Acu_conn_co_ date_time.minute
#define	Acu_conn_co_second				Acu_conn_co_ date_time.second
#define	Acu_conn_co_a_date_time			&(Acu_conn_co_ date_time)
#define	Acu_conn_co_redir_nb_pres		Acu_conn_co_ redir_nb.pres
#define	Acu_conn_co_redir_nb_type		Acu_conn_co_ redir_nb.type
#define	Acu_conn_co_redir_nb_screen		Acu_conn_co_ redir_nb.screen
#define	Acu_conn_co_redir_nb_reason		Acu_conn_co_ redir_nb.reason
#define	Acu_conn_co_redir_nb_size		Acu_conn_co_ redir_nb.size
#define	Acu_conn_co_ss_cnip_name_size		Acu_conn_co_ ss_cnip_name.size
#define	Acu_conn_co_ss_cnip_name_pres		Acu_conn_co_ ss_cnip_name.pres
#define	Acu_conn_co_ss_cnip_name_active		Acu_conn_co_ ss_cnip_name.active
#define	Acu_conn_co_ss_cnip_name			Acu_conn_co_ ss_cnip_name
/* aliases */
#define	Acu_conn_co_ss_conp_name_size		Acu_conn_co_ss_cnip_name_size
#define	Acu_conn_co_ss_conp_name_pres		Acu_conn_co_ss_cnip_name_pres
#define	Acu_conn_co_ss_conp_name_active		Acu_conn_co_ss_cnip_name_active
#define	Acu_conn_co_ss_conp_name			Acu_conn_co_ss_cnip_name
#define	Acu_conn_co_connected_nb		Acu_conn_rs_ connected_nb
#define	Acu_conn_co_connected_nb_pres	Acu_conn_rs_ connected_nb.pres
#define	Acu_conn_co_connected_nb_type	Acu_conn_rs_ connected_nb.type
#define	Acu_conn_co_connected_nb_screen	Acu_conn_rs_ connected_nb.screen
#define	Acu_conn_co_connected_nb_size	Acu_conn_rs_ connected_nb.size

#define	Acu_conn_co_connected_sub			Acu_conn_co_ connected_sub
#define	Acu_conn_co_connected_sub_type		Acu_conn_co_ connected_sub.type
#define	Acu_conn_co_connected_sub_odd_even	Acu_conn_co_ connected_sub.odd_even
#define	Acu_conn_co_connected_sub_size		Acu_conn_co_ connected_sub.size

#define	Acu_conn_co_uui_protocol		Acu_conn_co_ uui_protocol
#define	Acu_conn_co_uui_size			Acu_conn_co_ uui_size
#define	Acu_conn_co_facility_size		Acu_conn_co_ facility_size
#define	Acu_conn_co_display_size		Acu_conn_co_x_display_total_size
#define	Acu_conn_co_pcs_user_protocol	Acu_conn_co_ pcs_user_protocol
#define Acu_conn_co_pcs_user_size		Acu_conn_co_ pcs_user_size

#define Acu_conn_co_x_display_nb		Acu_conn_co_ display.nb
#define Acu_conn_co_x_display_total_size Acu_conn_co_ display.total_size
#define Acu_conn_co_x_p_display(i) 		Acu_conn_co_ display.p_display[i]
#define Acu_conn_co_x_display_type(i)	Acu_conn_co_ display.type[i]
#define Acu_conn_co_x_display_size(i)	Acu_conn_co_ display.size[i]
#define Acu_conn_co_a_display_list      &(Acu_conn_co_ display)

#define	Acu_conn_co_signal_val 			Acu_conn_co_ signal_val

#define Acu_conn_co_q931_size			Acu_conn_co_ q931_size

#define	Acu_conn_co_a_redir_nb			((char  *)p_data + Acu_conn_co_size)
#define	Acu_conn_co_a_uui				(Acu_conn_co_a_redir_nb + Acu_conn_co_redir_nb_size)
#define	Acu_conn_co_a_facility			(Acu_conn_co_a_uui  + Acu_conn_co_uui_size)
#define	Acu_conn_co_a_display			(Acu_conn_co_a_facility + Acu_conn_co_facility_size)
#define	Acu_conn_co_a_connected_nb		(Acu_conn_co_a_display + Acu_conn_co_display_size)
#define	Acu_conn_co_a_connected_sub		(Acu_conn_co_a_connected_nb + Acu_conn_co_connected_nb_size)
#define Acu_conn_co_a_pcs_user			(Acu_conn_co_a_connected_sub + Acu_conn_co_connected_sub_size)

#define Acu_conn_co_a_ss_cnip_name  	(Acu_conn_co_a_pcs_user + Acu_conn_co_pcs_user_size)
/* alias */
#define Acu_conn_co_a_ss_conp_name  	Acu_conn_co_a_ss_cnip_name

#define Acu_conn_co_a_q931				(Acu_conn_co_a_ss_cnip_name + Acu_conn_co_ss_cnip_name_size)


#define Acu_conn_co_a_end_strings		(uchar  *)Round8((unsigned long)Acu_conn_co_a_q931 + Acu_conn_co_q931_size)
#define Acu_conn_co_total_size			(Acu_conn_co_a_end_strings - (uchar  *)p_data) /* not including the ext parms */
#define Acu_conn_co_start_ext_data		Acu_conn_co_total_size

#define	Acu_conn_co_size				(Rnd_sizeof (struct acu_conn_co_args))

/*---------------------------------------------------------------------------
*
*	ACU_NOTIFY_RQ	Sends a  NOTIFY msg
*
*	Arguments :
*		Acu_notify_rq_tsp_ie_list_size,
*		Acu_notify_rq_a_tsp_ie_list:	transparent IE list size/address
*--------------------------------------------------------------------------*/
struct acu_notify_rq_args {
	acu_size_t tsp_ie_list_size;		/* length of the list of transparent IE's */
	pad7
};

#define	Acu_notify_rq_					((struct acu_notify_rq_args  *)p_data) ->

#define	Acu_notify_rq_tsp_ie_list_size	Acu_notify_rq_ tsp_ie_list_size
#define	Acu_notify_rq_a_tsp_ie_list		((char  *)p_data + Acu_notify_rq_size)

#define	Acu_notify_rq_a_first_other		(Acu_notify_rq_a_tsp_ie_list + Acu_notify_rq_tsp_ie_list_size + 1)
#define Acu_notify_rq_a_end_strings		(uchar  *)Round8((unsigned long)Acu_notify_rq_a_first_other)

#define	Acu_notify_rq_size				(Rnd_sizeof (struct acu_notify_rq_args))
#define Acu_notify_rq_total_size		(Acu_notify_rq_a_end_strings - (uchar  *)p_data) /* not including the ext parms */

/*-------------------------------------------------------------------------------
*
*	ACU_NOTIFY_IN	Signals a  NOTIFY msg
*
*	Arguments :
*		Acu_notify_in_q931_size,
*		Acu_notify_in_a_q931:	Q.931 buffer
*-------------------------------------------------------------------------------*/
struct acu_notify_in_args {
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif
	acu_size_t q931_size;				/* size of Q.931 message */
	pad7
};

#define	Acu_notify_in_					((struct acu_notify_in_args  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_notify_in_ext_parms_nb	Acu_notify_in_ ext_descr.nb
#	define Acu_notify_in_ext_parms_lgth	Acu_notify_in_ ext_descr.lgth
#	define Acu_notify_in_a_ext_parms	((Acu_ext_descr_offset = Acu_notify_in_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define	Acu_notify_in_q931_size			Acu_notify_in_ q931_size
#define	Acu_notify_in_a_q931			((char  *)p_data + Acu_notify_in_size)

#define Acu_notify_in_a_end_strings		Acu_notify_in_a_q931 + Round8(Acu_notify_in_q931_size)
#define Acu_notify_in_start_ext_data    (Acu_notify_in_a_end_strings-(uchar  *)p_data)

#define	Acu_notify_in_size				(Rnd_sizeof (struct acu_notify_in_args))

/*---------------------------------------------------------------------------
*
*	ACU_DIGIT_RQ	Send Called Number digits in Overlap Sending mode.
*					(ISDN only)
*
*	Arguments :
*		Acu_digit_rq_sending_complete: Sending-complete IE to be sent (ON/OFF)
*   	Acu_digit_rq_digit_type     : called number type
*   	Acu_digit_rq_digit_plan     : called number plan
*		Acu_digit_rq_digit_size,
*		Acu_digit_rq_a_digit		: digits string size/address.
*		Acu_digit_rq_display_size,
*		Acu_digit_rq_a_display		: ISDN display Information
*
*--------------------------------------------------------------------------*/

struct acu_digit_rq_args {
	struct acu_display_list display;	/* display list */
    struct acu_called_nb digit;         /* digit string information */

	uchar	sending_complete;			/* Sending-complete IE to be sent (ON/OFF) */
	acu_size_t tsp_ie_list_size;		/* length of the list of transparent IE's */

	pad6
		
		/* digits are just here */
		/* and finally the display strings */
};

#define	Acu_digit_rq_					((struct acu_digit_rq_args  *)p_data) ->
#define	Acu_digit_rq_sending_complete	Acu_digit_rq_ sending_complete

#define	Acu_digit_rq_digit_type			Acu_digit_rq_ digit.type
#define	Acu_digit_rq_digit_plan			Acu_digit_rq_ digit.plan
#define	Acu_digit_rq_digit_size			Acu_digit_rq_ digit.size

#define	Acu_digit_rq_display_size		Acu_digit_rq_x_display_total_size

#define Acu_digit_rq_x_display_nb		Acu_digit_rq_ display.nb
#define Acu_digit_rq_x_display_total_size Acu_digit_rq_ display.total_size
#define Acu_digit_rq_x_p_display(i) 	Acu_digit_rq_ display.p_display[i]
#define Acu_digit_rq_x_display_type(i)	Acu_digit_rq_ display.type[i]
#define Acu_digit_rq_x_display_size(i)	Acu_digit_rq_ display.size[i]

#define	Acu_digit_rq_tsp_ie_list_size	Acu_digit_rq_ tsp_ie_list_size

#define Acu_digit_rq_a_display_list     &(Acu_digit_rq_ display)

#define	Acu_digit_rq_a_digit			((char  *)p_data   + Acu_digit_rq_size)
#define	Acu_digit_rq_a_display			(Acu_digit_rq_a_digit + Acu_digit_rq_digit_size + 1)

#define	Acu_digit_rq_a_tsp_ie_list		(Acu_digit_rq_a_display + Acu_digit_rq_display_size + 1)


#define Acu_digit_rq_a_end_strings		(uchar  *)Round8((unsigned long)Acu_digit_rq_a_tsp_ie_list + Acu_digit_rq_tsp_ie_list_size + 1)

#define Acu_digit_rq_total_size			(Acu_digit_rq_a_end_strings - (uchar  *)p_data) /* not including the ext parms */

#define Acu_digit_rq_start_ext_data		Acu_digit_rq_total_size

#define	Acu_digit_rq_size				(Rnd_sizeof (struct acu_digit_rq_args))

/*---------------------------------------------------------------------------
*
*	ACU_DIGIT_IN	Receive Called Number digits in Overlap Receiving mode.
*					(ISDN only)
*
*	Arguments :
*		Acu_digit_in_sending_complete: Sending-complete IE received (ON/OFF)
*   	Acu_digit_in_digit_type     : called number type
*   	Acu_digit_in_digit_plan     : called number plan
*		Acu_digit_in_digit_size,
*		Acu_digit_in_a_digit		: digits string size/address.
*		Acu_digit_in_display_size,
*		Acu_digit_in_a_display		: ISDN display Information
*
*--------------------------------------------------------------------------*/

struct acu_digit_in_args {
    struct acu_display_list display;	/* display list */
    struct acu_called_nb digit;     /* digit string information */

	uchar	sending_complete;			/* Sending-complete IE to be sent (ON/OFF) */
	acu_size_t q931_size;				/* size of Q.931 message */

	pad6
		/* digits are just here */
		/* and finally the display strings */
};



#define	Acu_digit_in_					((struct acu_digit_in_args  *)p_data) ->

#define	Acu_digit_in_sending_complete	Acu_digit_in_ sending_complete

#define	Acu_digit_in_digit_type			Acu_digit_in_ digit.type
#define	Acu_digit_in_digit_plan			Acu_digit_in_ digit.plan
#define	Acu_digit_in_digit_size			Acu_digit_in_ digit.size

#define	Acu_digit_in_display_size		Acu_digit_in_x_display_total_size

#define Acu_digit_in_x_display_nb		Acu_digit_in_ display.nb
#define Acu_digit_in_x_display_total_size Acu_digit_in_ display.total_size
#define Acu_digit_in_x_p_display(i) 	Acu_digit_in_ display.p_display[i]
#define Acu_digit_in_x_display_type(i)	Acu_digit_in_ display.type[i]
#define Acu_digit_in_x_display_size(i)	Acu_digit_in_ display.size[i]

#define Acu_digit_in_q931_size			Acu_digit_in_ q931_size

#define Acu_digit_in_a_display_list     &(Acu_digit_in_ display)

#define	Acu_digit_in_a_digit			((char  *)p_data   + Acu_digit_in_size)
#define	Acu_digit_in_a_display			(Acu_digit_in_a_digit + Acu_digit_in_digit_size)
#define Acu_digit_in_a_q931				(Acu_digit_in_a_display + Acu_digit_in_display_size)


#define	Acu_digit_in_a_end_strings			(uchar  *)Round8((unsigned long)Acu_digit_in_a_q931 + Acu_digit_in_q931_size)
#define Acu_digit_in_start_ext_data			(Acu_digit_in_a_end_strings-(uchar  *)p_data)

#define	Acu_digit_in_size				(Rnd_sizeof (struct acu_digit_in_args))

/*---------------------------------------------------------------------------
*
*	ACU_DIGIT_CO	Confirm end-of-called-nb-reached in Overlap Sending mode.
*
*	Arguments :
*		Acu_digit_co_display_size,
*		Acu_digit_co_a_display		: ISDN display Information
*
*--------------------------------------------------------------------------*/

struct acu_digit_co_args {
	struct acu_display_list display;	/* display list */
    
	/* display strings are just here */
};

#define	Acu_digit_co_					((struct acu_digit_co_args  *)p_data) ->
#define	Acu_digit_co_display_size		Acu_digit_co_x_display_total_size

#define Acu_digit_co_x_display_nb		Acu_digit_co_ display.nb
#define Acu_digit_co_x_display_total_size Acu_digit_co_ display.total_size
#define Acu_digit_co_x_p_display(i) 	Acu_digit_co_ display.p_display[i]
#define Acu_digit_co_x_display_type(i)	Acu_digit_co_ display.type[i]
#define Acu_digit_co_x_display_size(i)	Acu_digit_co_ display.size[i]
#define Acu_digit_co_a_display_list     &(Acu_digit_co_ display)

#define	Acu_digit_co_a_display			((char  *)p_data + Acu_digit_co_size)

#define	Acu_digit_co_size				(Rnd_sizeof (struct acu_digit_co_args))

/*---------------------------------------------------------------------------
*
*	ACU_CALL_PROC_RQ		Call Proceeding Request
*
*	Arguments :
*      Acu_call_proc_rq_data_chani_nb			: nb of elements in the chani_list.tab field
*      Acu_call_proc_rq_data_chani   			: data channel to use (B1, B2, etc, D, or 0 for any)
*		Acu_call_proc_rq_display_size,
*		Acu_call_proc_rq_a_display    			: ISDN display Information
*		Acu_call_proc_rq_progress_location 		: progress location
*		Acu_call_proc_rq_progress_description	: progress description
*
*--------------------------------------------------------------------------*/

struct acu_call_proc_rq_args {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif
    
	struct chani_list chani_list;		/* list of channel ids to use for data transfer */
    
	struct acu_display_list display;	/* display list */
	struct acu_progress_ind progress_ind;/* progress indicator */

    
	acu_size_t tsp_ie_list_size;		/* length of the list of transparent IE's */
	pad7
		/* display strings are here */
		
};

#define	Acu_call_proc_rq_						((struct acu_call_proc_rq_args  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_call_proc_rq_ext_parms_nb		Acu_call_proc_rq_ ext_descr.nb
#	define Acu_call_proc_rq_ext_parms_lgth		Acu_call_proc_rq_ ext_descr.lgth
#	define Acu_call_proc_rq_a_ext_parms			((Acu_ext_descr_offset = Acu_call_proc_rq_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define Acu_call_proc_rq_data_chani_nb			Acu_call_proc_rq_ chani_list.nb
#define Acu_call_proc_rq_data_chani				Acu_call_proc_rq_ chani_list.tab[0].chan_id
#define Acu_call_proc_rq_data_chani_nai			Acu_call_proc_rq_ chani_list.tab[0].nai
#define Acu_call_proc_rq_data_chani_tab(i)		Acu_call_proc_rq_ chani_list.tab[i].chan_id
#define Acu_call_proc_rq_data_chani_tab_nai(i)	Acu_call_proc_rq_ chani_list.tab[i].nai
#define Acu_call_proc_rq_data_chani_excl    	Acu_call_proc_rq_ chani_list.chan_id_excl

#define	Acu_call_proc_rq_display_size			Acu_call_proc_rq_x_display_total_size

#define Acu_call_proc_rq_x_display_nb			Acu_call_proc_rq_ display.nb
#define Acu_call_proc_rq_x_display_total_size	Acu_call_proc_rq_ display.total_size
#define Acu_call_proc_rq_x_p_display(i) 		Acu_call_proc_rq_ display.p_display[i]
#define Acu_call_proc_rq_x_display_type(i)		Acu_call_proc_rq_ display.type[i]
#define Acu_call_proc_rq_x_display_size(i)		Acu_call_proc_rq_ display.size[i]
#define Acu_call_proc_rq_a_display_list     	&(Acu_call_proc_rq_ display)

#define	Acu_call_proc_rq_progress_ind_nb		Acu_call_proc_rq_ progress_ind.nb
#define	Acu_call_proc_rq_progress_location		Acu_call_proc_rq_progress_loc
#define	Acu_call_proc_rq_progress_description	Acu_call_proc_rq_progress_descr
/* aliases */
#define	Acu_call_proc_rq_progress_loc			Acu_call_proc_rq_ progress_ind.t[0].loc
#define	Acu_call_proc_rq_progress_descr			Acu_call_proc_rq_ progress_ind.t[0].descr
/* access to other occurencies */
#define	Acu_call_proc_rq_progress_loc_x(i)		Acu_call_proc_rq_ progress_ind.t[i].loc
#define	Acu_call_proc_rq_progress_descr_x(i)	Acu_call_proc_rq_ progress_ind.t[i].descr

#define Acu_call_proc_rq_tsp_ie_list_size		Acu_call_proc_rq_ tsp_ie_list_size

#define	Acu_call_proc_rq_a_display				((char  *)p_data + Acu_call_proc_rq_size)

#define Acu_call_proc_rq_a_tsp_ie_list			(Acu_call_proc_rq_a_display + Acu_call_proc_rq_display_size + 1)


#define Acu_call_proc_rq_a_end_strings			(uchar  *)Round8((unsigned long)Acu_call_proc_rq_a_tsp_ie_list + Acu_call_proc_rq_tsp_ie_list_size + 1)
#define Acu_call_proc_rq_total_size				(Acu_call_proc_rq_a_end_strings - (uchar  *)p_data) /* not including the ext parms */
#define Acu_call_proc_rq_start_ext_data         Acu_call_proc_rq_total_size

#define	Acu_call_proc_rq_size					(Rnd_sizeof (struct acu_call_proc_rq_args))

/*----------------------------------------------------------------------------
*
*	ACU_PROGRESS_RQ: 		progress request
*
*	Arguments :
*		Acu_progress_rq_progress_location 	: progress location
*		Acu_progress_rq_progress_description: progress description
*		Acu_progress_rq_cause      			: cause value 
*		Acu_progress_rq_cause_location		: cause location
*
*--------------------------------------------------------------------------*/
struct acu_progress_rq_args {
	struct acu_progress_ind progress_ind;/* progress indicator */
	uchar				cause;			/* cause value */
	uchar	cause_location;				/* clearing cause location */
	acu_size_t tsp_ie_list_size;		/* length of the list of transparent IE's */
	pad5
};

#define	Acu_progress_rq_						((struct acu_progress_rq_args  *)p_data) ->

#define	Acu_progress_rq_progress_location		Acu_progress_rq_progress_loc
#define	Acu_progress_rq_progress_description	Acu_progress_rq_progress_descr
/* aliases */
#define	Acu_progress_rq_progress_loc			Acu_progress_rq_ progress_ind.t[0].loc
#define	Acu_progress_rq_progress_descr			Acu_progress_rq_ progress_ind.t[0].descr

#define	Acu_progress_rq_cause					Acu_progress_rq_ cause
#define	Acu_progress_rq_cause_location			Acu_progress_rq_ cause_location

#define Acu_progress_rq_tsp_ie_list_size		Acu_progress_rq_ tsp_ie_list_size


#define Acu_progress_rq_a_tsp_ie_list			((char  *)p_data + Acu_progress_rq_size)

#define Acu_progress_rq_a_end_strings			(uchar  *)Round8((unsigned long)Acu_progress_rq_a_tsp_ie_list + Acu_progress_rq_tsp_ie_list_size + 1)
#define Acu_progress_rq_total_size				(Acu_progress_rq_a_end_strings - (uchar  *)p_data) /* not including the ext parms */

#define	Acu_progress_rq_size					(Rnd_sizeof (struct acu_progress_rq_args))

/*----------------------------------------------------------------------------
*
*	ACU_PROGRESS_IN: 		progress indication
*
*	Arguments :
*       Acu_progress_in_call_ref_length	    : length of call reference
*       Acu_progress_in_call_ref_value	    : call reference associated with the call	
*		Acu_progress_in_cause      			: cause value
*		Acu_progress_in_progress_location 	: progress location
*		Acu_progress_in_progress_description: progress description
*       Acu_progress_in_data_chani_nb		: nb of elements in the chani_list field
*       Acu_progress_in_data_chani  		: channel id
*		Acu_progress_in_facility_size,
*		Acu_progress_in_a_facility			: ISDN facility
*		Acu_progress_in_display_size,
*		Acu_progress_in_a_display			: ISDN display Information
*		Acu_progress_in_pcs_user_protocol,
*		Acu_progress_in_pcs_user_size,
*		Acu_progress_in_a_pcs_user			: ISDN PCS-to-User/User-to-PCS Info.
*		Acu_progress_in_signal_val 			: signal value
*
*--------------------------------------------------------------------------*/

struct acu_progress_in_args {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif

    struct acu_call_ref call_ref;	    /* call reference information */
    
	struct acu_progress_ind progress_ind;/* progress indicator */
	struct chani_list	chani_list;		/* list of channel ids to use for data transfer */
	struct acu_display_list display;	/* display list */
    
	uchar				cause;			/* cause value */
	uchar				signal_val;		/* signal value */
    
	acu_size_t facility_size;			/* size of the facility */
	uchar      pcs_user_protocol;		/* PCS-to-User or User-to-PCS protocol-discriminator value */
	acu_size_t pcs_user_size;			/* size of the PCS-to-User or User-to-PCS information */
    
	acu_size_t q931_size;				/* size of Q.931 message */
	pad2
		
		/* facility is just here */
		/* then all the other strings in order */
};

#define	Acu_progress_in_						((struct acu_progress_in_args  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_progress_in_ext_parms_nb			Acu_progress_in_ ext_descr.nb
#	define Acu_progress_in_ext_parms_lgth		Acu_progress_in_ ext_descr.lgth
#	define Acu_progress_in_a_ext_parms			((Acu_ext_descr_offset = Acu_progress_in_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define Acu_progress_in_call_ref_length		    Acu_progress_in_ call_ref.length
#define Acu_progress_in_call_ref_value		    Acu_progress_in_ call_ref.value

#define	Acu_progress_in_cause					Acu_progress_in_ cause

#define	Acu_progress_in_progress_ind_nb			Acu_progress_in_ progress_ind.nb
#define	Acu_progress_in_progress_location		Acu_progress_in_progress_loc
#define	Acu_progress_in_progress_description	Acu_progress_in_progress_descr
/* aliases */
#define	Acu_progress_in_progress_loc			Acu_progress_in_ progress_ind.t[0].loc
#define	Acu_progress_in_progress_descr			Acu_progress_in_ progress_ind.t[0].descr
/* access to other occurencies */
#define	Acu_progress_in_progress_loc_x(i)		Acu_progress_in_ progress_ind.t[i].loc
#define	Acu_progress_in_progress_descr_x(i)		Acu_progress_in_ progress_ind.t[i].descr

#define Acu_progress_in_data_chani_nb   		Acu_progress_in_ chani_list.nb
#define Acu_progress_in_data_chani      		Acu_progress_in_ chani_list.tab[0].chan_id
#define Acu_progress_in_data_chani_nai  		Acu_progress_in_ chani_list.tab[0].nai
#define Acu_progress_in_data_chani_tab(i)    	Acu_progress_in_ chani_list.tab[i].chan_id
#define Acu_progress_in_data_chani_tab_nai(i)	Acu_progress_in_ chani_list.tab[i].nai
#define Acu_progress_in_data_chani_excl 		Acu_progress_in_ chani_list.chan_id_excl

#define	Acu_progress_in_facility_size			Acu_progress_in_ facility_size
#define	Acu_progress_in_display_size			Acu_progress_in_x_display_total_size
#define Acu_progress_in_pcs_user_protocol		Acu_progress_in_ pcs_user_protocol
#define Acu_progress_in_pcs_user_size			Acu_progress_in_ pcs_user_size

#define	Acu_progress_in_signal_val				Acu_progress_in_ signal_val

#define Acu_progress_in_x_display_nb			Acu_progress_in_ display.nb
#define Acu_progress_in_x_display_total_size	Acu_progress_in_ display.total_size
#define Acu_progress_in_x_p_display(i) 			Acu_progress_in_ display.p_display[i]
#define Acu_progress_in_x_display_type(i)		Acu_progress_in_ display.type[i]
#define Acu_progress_in_x_display_size(i)		Acu_progress_in_ display.size[i]
#define Acu_progress_in_a_display_list          &(Acu_progress_in_ display)

#define Acu_progress_in_q931_size				Acu_progress_in_ q931_size

#define	Acu_progress_in_a_facility				((char  *)p_data + Acu_progress_in_size)
#define	Acu_progress_in_a_display				(Acu_progress_in_a_facility + Acu_progress_in_facility_size)
#define Acu_progress_in_a_pcs_user				(Acu_progress_in_a_display + Acu_progress_in_display_size)

#define Acu_progress_in_a_q931					(Acu_progress_in_a_pcs_user + Acu_progress_in_pcs_user_size)

#define Acu_progress_in_a_end_strings			(uchar  *)Round8((unsigned long)Acu_progress_in_a_q931 + Acu_progress_in_q931_size)
#define Acu_progress_in_start_ext_data          (Acu_progress_in_a_end_strings-(uchar  *)p_data)

#define	Acu_progress_in_size					(Rnd_sizeof (struct acu_progress_in_args))

/*----------------------------------------------------------------------------
*
*	ACU_CALL_PROC_IN: 		call proceeding indication
*
*	Arguments :
*       Acu_call_proc_in_call_ref_length	: length of call reference
*       Acu_call_proc_in_call_ref_value	    : call reference associated with the call	
*		Acu_call_proc_in_cause      		: cause value
*		Acu_call_proc_in_progress_location 	: progress location
*		Acu_call_proc_in_progress_description: progress description
*       Acu_call_proc_in_data_chani_nb		: nb of elements in the chani_list field
*       Acu_call_proc_in_data_chani  		: channel id
*		Acu_call_proc_in_facility_size,
*		Acu_call_proc_in_a_facility			: ISDN facility
*		Acu_call_proc_in_display_size,
*		Acu_call_proc_in_a_display			: ISDN display Information
*		Acu_call_proc_in_signal_val 			: signal value
*
*--------------------------------------------------------------------------*/

struct acu_call_proc_in_args {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif
    
    struct acu_call_ref call_ref;	    /* call reference information */

	struct acu_progress_ind progress_ind;/* progress indicator */
	struct chani_list	chani_list;		/* list of channel ids to use for data transfer */
	struct acu_display_list display;	/* display list */
    
	uchar				signal_val;		/* signal value */
    
	acu_size_t	facility_size;			/* size of the facility */
	acu_size_t q931_size;				/* size of Q.931 message */
	pad5
		/* facility is just here */
		/* then all the other strings in order */
};

#define	Acu_call_proc_in_						((struct acu_call_proc_in_args  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_call_proc_in_ext_parms_nb			Acu_call_proc_in_ ext_descr.nb
#	define Acu_call_proc_in_ext_parms_lgth		Acu_call_proc_in_ ext_descr.lgth
#	define Acu_call_proc_in_a_ext_parms			((Acu_ext_descr_offset = Acu_call_proc_in_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define Acu_call_proc_in_call_ref_length		Acu_call_proc_in_ call_ref.length
#define Acu_call_proc_in_call_ref_value		    Acu_call_proc_in_ call_ref.value

#define	Acu_call_proc_in_progress_ind_nb		Acu_call_proc_in_ progress_ind.nb
#define	Acu_call_proc_in_progress_location		Acu_call_proc_in_progress_loc
#define	Acu_call_proc_in_progress_description	Acu_call_proc_in_progress_descr
/* aliases */
#define	Acu_call_proc_in_progress_loc			Acu_call_proc_in_ progress_ind.t[0].loc
#define	Acu_call_proc_in_progress_descr			Acu_call_proc_in_ progress_ind.t[0].descr
/* access to other occurencies */
#define	Acu_call_proc_in_progress_loc_x(i)		Acu_call_proc_in_ progress_ind.t[i].loc
#define	Acu_call_proc_in_progress_descr_x(i)		Acu_call_proc_in_ progress_ind.t[i].descr

#define Acu_call_proc_in_data_chani_nb   		Acu_call_proc_in_ chani_list.nb
#define Acu_call_proc_in_data_chani      		Acu_call_proc_in_ chani_list.tab[0].chan_id
#define Acu_call_proc_in_data_chani_nai  		Acu_call_proc_in_ chani_list.tab[0].nai
#define Acu_call_proc_in_data_chani_tab(i)    	Acu_call_proc_in_ chani_list.tab[i].chan_id
#define Acu_call_proc_in_data_chani_tab_nai(i)	Acu_call_proc_in_ chani_list.tab[i].nai
#define Acu_call_proc_in_data_chani_excl 		Acu_call_proc_in_ chani_list.chan_id_excl

#define	Acu_call_proc_in_facility_size			Acu_call_proc_in_ facility_size
#define	Acu_call_proc_in_display_size			Acu_call_proc_in_x_display_total_size

#define Acu_call_proc_in_x_display_nb			Acu_call_proc_in_ display.nb
#define Acu_call_proc_in_x_display_total_size	Acu_call_proc_in_ display.total_size
#define Acu_call_proc_in_x_p_display(i) 			Acu_call_proc_in_ display.p_display[i]
#define Acu_call_proc_in_x_display_type(i)		Acu_call_proc_in_ display.type[i]
#define Acu_call_proc_in_x_display_size(i)		Acu_call_proc_in_ display.size[i]
#define Acu_call_proc_in_a_display_list          &(Acu_call_proc_in_ display)

#define Acu_call_proc_in_q931_size				Acu_call_proc_in_ q931_size

#define	Acu_call_proc_in_a_facility				((char  *)p_data + Acu_call_proc_in_size)
#define	Acu_call_proc_in_a_display				(Acu_call_proc_in_a_facility + Acu_call_proc_in_facility_size)

#define	Acu_call_proc_in_signal_val				Acu_call_proc_in_ signal_val

#define Acu_call_proc_in_a_q931					(Acu_call_proc_in_a_display + Acu_call_proc_in_display_size)

#define Acu_call_proc_in_a_end_strings			(uchar  *)Round8((unsigned long)Acu_call_proc_in_a_q931 + Acu_call_proc_in_q931_size)
#define Acu_call_proc_in_start_ext_data         (Acu_call_proc_in_a_end_strings-(uchar  *)p_data)

#define	Acu_call_proc_in_size					(Rnd_sizeof (struct acu_call_proc_in_args))

/*----------------------------------------------------------------------------
*
*	ACU_SETUP_ACK_IN: 		setup acknowledge indication
*
*	Arguments :
*		Acu_setup_ack_in_cause      			: cause value
*		Acu_setup_ack_in_progress_location 	: progress location
*		Acu_setup_ack_in_progress_description: progress description
*       Acu_setup_ack_in_data_chani_nb		: nb of elements in the chani_list field
*       Acu_setup_ack_in_data_chani  		: channel id
*		Acu_setup_ack_in_facility_size,
*		Acu_setup_ack_in_a_facility			: ISDN facility
*		Acu_setup_ack_in_display_size,
*		Acu_setup_ack_in_a_display			: ISDN display Information
*		Acu_setup_ack_in_a_pcs_user			: ISDN PCS-to-User/User-to-PCS Info.
*		Acu_setup_ack_in_signal_val 			: signal value
*
*--------------------------------------------------------------------------*/

struct acu_setup_ack_in_args {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif
    
	struct acu_progress_ind progress_ind;/* progress indicator */
	struct chani_list	chani_list;		/* list of channel ids to use for data transfer */
	struct acu_display_list display;	/* display list */
    
	uchar				signal_val;		/* signal value */
    
	acu_size_t	facility_size;			/* size of the facility */
	acu_size_t q931_size;				/* size of Q.931 message */
	pad5
		/* facility is just here */
		/* then all the other strings in order */
};

#define	Acu_setup_ack_in_						((struct acu_setup_ack_in_args  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_setup_ack_in_ext_parms_nb			Acu_setup_ack_in_ ext_descr.nb
#	define Acu_setup_ack_in_ext_parms_lgth		Acu_setup_ack_in_ ext_descr.lgth
#	define Acu_setup_ack_in_a_ext_parms			((Acu_ext_descr_offset = Acu_setup_ack_in_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define	Acu_setup_ack_in_progress_ind_nb			Acu_setup_ack_in_ progress_ind.nb
#define	Acu_setup_ack_in_progress_location		Acu_setup_ack_in_progress_loc
#define	Acu_setup_ack_in_progress_description	Acu_setup_ack_in_progress_descr
/* aliases */
#define	Acu_setup_ack_in_progress_loc			Acu_setup_ack_in_ progress_ind.t[0].loc
#define	Acu_setup_ack_in_progress_descr			Acu_setup_ack_in_ progress_ind.t[0].descr
/* access to other occurencies */
#define	Acu_setup_ack_in_progress_loc_x(i)		Acu_setup_ack_in_ progress_ind.t[i].loc
#define	Acu_setup_ack_in_progress_descr_x(i)		Acu_setup_ack_in_ progress_ind.t[i].descr

#define Acu_setup_ack_in_data_chani_nb   		Acu_setup_ack_in_ chani_list.nb
#define Acu_setup_ack_in_data_chani      		Acu_setup_ack_in_ chani_list.tab[0].chan_id
#define Acu_setup_ack_in_data_chani_nai  		Acu_setup_ack_in_ chani_list.tab[0].nai
#define Acu_setup_ack_in_data_chani_tab(i)    	Acu_setup_ack_in_ chani_list.tab[i].chan_id
#define Acu_setup_ack_in_data_chani_tab_nai(i)	Acu_setup_ack_in_ chani_list.tab[i].nai
#define Acu_setup_ack_in_data_chani_excl 		Acu_setup_ack_in_ chani_list.chan_id_excl

#define	Acu_setup_ack_in_facility_size			Acu_setup_ack_in_ facility_size
#define	Acu_setup_ack_in_display_size			Acu_setup_ack_in_x_display_total_size

#define Acu_setup_ack_in_x_display_nb			Acu_setup_ack_in_ display.nb
#define Acu_setup_ack_in_x_display_total_size	Acu_setup_ack_in_ display.total_size
#define Acu_setup_ack_in_x_p_display(i) 			Acu_setup_ack_in_ display.p_display[i]
#define Acu_setup_ack_in_x_display_type(i)		Acu_setup_ack_in_ display.type[i]
#define Acu_setup_ack_in_x_display_size(i)		Acu_setup_ack_in_ display.size[i]
#define Acu_setup_ack_in_a_display_list          &(Acu_setup_ack_in_ display)

#define Acu_setup_ack_in_q931_size				Acu_setup_ack_in_ q931_size

#define	Acu_setup_ack_in_a_facility				((char  *)p_data + Acu_setup_ack_in_size)
#define	Acu_setup_ack_in_a_display				(Acu_setup_ack_in_a_facility + Acu_setup_ack_in_facility_size)
#define	Acu_setup_ack_in_signal_val				Acu_setup_ack_in_ signal_val

#define Acu_setup_ack_in_a_q931					(Acu_setup_ack_in_a_display + Acu_setup_ack_in_display_size)

#define Acu_setup_ack_in_a_end_strings			(uchar  *)Round8((unsigned long)Acu_setup_ack_in_a_q931 + Acu_setup_ack_in_q931_size)
#define Acu_setup_ack_in_start_ext_data         (Acu_setup_ack_in_a_end_strings-(uchar  *)p_data)

#define	Acu_setup_ack_in_size					(Rnd_sizeof (struct acu_setup_ack_in_args))

/*----------------------------------------------------------------------------
*
*	ACU_ALERT_RQ		alert request
*
*	Arguments :
*		Acu_alert_rq_uui_size,
*		Acu_alert_rq_a_uui		: ISDN facility
*		Acu_alert_rq_display_size,
*		Acu_alert_rq_a_display	: ISDN display Information
*		Acu_alert_rq_pcs_user_protocol,
*		Acu_alert_rq_pcs_user_size,
*		Acu_alert_rq_a_pcs_user	: ISDN PCS-to-User/User-to-PCS Info.
*		Acu_alert_rq_signal_val 			: signal value
*		Acu_alert_rq_progress_location 		: progress location
*		Acu_alert_rq_progress_description	: progress description
*
*--------------------------------------------------------------------------*/

struct acu_alert_rq_args {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif
    
	struct chani_list chani_list;		/* list of channel ids to use for data transfer */
	struct acu_display_list display;	/* display list */
	struct acu_progress_ind progress_ind;/* progress indicator */
	struct acu_name  ss_cnip_name;
    
    
	uchar      uui_protocol;			/* UUI protocol-discriminator value */
	acu_size_t uui_size;				/* uui size */
	uchar      pcs_user_protocol;		/* PCS-to-User or User-to-PCS protocol-discriminator value */
	acu_size_t pcs_user_size;			/* size of the PCS-to-User or User-to-PCS information */
    
	uchar	signal_val;					/* signal value */
		
    
	acu_size_t tsp_ie_list_size;		/* length of the list of transparent IE's */
	pad2
		
		/* UUI is just here */
		/* then all the other strings in order */
};

#define	Acu_alert_rq_							((struct acu_alert_rq_args  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_alert_rq_ext_parms_nb			Acu_alert_rq_ ext_descr.nb
#	define Acu_alert_rq_ext_parms_lgth			Acu_alert_rq_ ext_descr.lgth
#	define Acu_alert_rq_a_ext_parms				((Acu_ext_descr_offset = Acu_alert_rq_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define Acu_alert_rq_data_chani_nb				Acu_alert_rq_ chani_list.nb
#define Acu_alert_rq_data_chani					Acu_alert_rq_ chani_list.tab[0].chan_id
#define Acu_alert_rq_data_chani_nai				Acu_alert_rq_ chani_list.tab[0].nai
#define Acu_alert_rq_data_chani_tab(i)			Acu_alert_rq_ chani_list.tab[i].chan_id
#define Acu_alert_rq_data_chani_tab_nai(i)		Acu_alert_rq_ chani_list.tab[i].nai
#define Acu_alert_rq_data_chani_excl        	Acu_alert_rq_ chani_list.chan_id_excl

#define Acu_alert_rq_x_display_nb				Acu_alert_rq_ display.nb
#define Acu_alert_rq_x_display_total_size		Acu_alert_rq_ display.total_size
#define Acu_alert_rq_x_p_display(i) 			Acu_alert_rq_ display.p_display[i]
#define Acu_alert_rq_x_display_type(i)			Acu_alert_rq_ display.type[i]
#define Acu_alert_rq_x_display_size(i)			Acu_alert_rq_ display.size[i]
#define Acu_alert_rq_a_display_list				&(Acu_alert_rq_ display)

#define	Acu_alert_rq_ss_cnip_name_size		    Acu_alert_rq_ ss_cnip_name.size
#define	Acu_alert_rq_ss_cnip_name_pres		    Acu_alert_rq_ ss_cnip_name.pres
#define	Acu_alert_rq_ss_cnip_name_active		Acu_alert_rq_ ss_cnip_name.active
#define	Acu_alert_rq_ss_cnip_name				Acu_alert_rq_ ss_cnip_name
/* aliases */
#define	Acu_alert_rq_ss_conp_name_size		    Acu_alert_rq_ss_cnip_name_size
#define	Acu_alert_rq_ss_conp_name_pres		    Acu_alert_rq_ss_cnip_name_pres
#define	Acu_alert_rq_ss_conp_name_active		Acu_alert_rq_ss_cnip_name_active
#define	Acu_alert_rq_ss_conp_name				Acu_alert_rq_ss_cnip_name

#define	Acu_alert_rq_uui_protocol				Acu_alert_rq_ uui_protocol
#define	Acu_alert_rq_uui_size					Acu_alert_rq_ uui_size
#define	Acu_alert_rq_display_size				Acu_alert_rq_x_display_total_size
#define Acu_alert_rq_pcs_user_protocol			Acu_alert_rq_ pcs_user_protocol
#define Acu_alert_rq_pcs_user_size				Acu_alert_rq_ pcs_user_size

#define	Acu_alert_rq_signal_val					Acu_alert_rq_ signal_val

#define	Acu_alert_rq_progress_ind_nb			Acu_alert_rq_ progress_ind.nb
#define	Acu_alert_rq_progress_location			Acu_alert_rq_ progress_loc
#define	Acu_alert_rq_progress_description		Acu_alert_rq_ progress_descr
/* aliases */
#define	Acu_alert_rq_progress_loc				Acu_alert_rq_ progress_ind.t[0].loc
#define	Acu_alert_rq_progress_descr				Acu_alert_rq_ progress_ind.t[0].descr
/* access to other occurencies */
#define	Acu_alert_rq_progress_loc_x(i)			Acu_alert_rq_ progress_ind.t[i].loc
#define	Acu_alert_rq_progress_descr_x(i)		Acu_alert_rq_ progress_ind.t[i].descr

#define Acu_alert_rq_tsp_ie_list_size			Acu_alert_rq_ tsp_ie_list_size

#define	Acu_alert_rq_a_uui						((char  *)p_data + Acu_alert_rq_size)
#define	Acu_alert_rq_a_display					(Acu_alert_rq_a_uui + Acu_alert_rq_uui_size + 1)
#define Acu_alert_rq_a_pcs_user					(Acu_alert_rq_a_display + Acu_alert_rq_display_size + 1)

#define Acu_alert_rq_a_ss_cnip_name 			(Acu_alert_rq_a_pcs_user + Acu_alert_rq_pcs_user_size + 1)
/* alias */
#define Acu_alert_rq_a_ss_conp_name 			Acu_alert_rq_a_ss_cnip_name
#define Acu_alert_rq_a_tsp_ie_list				(Acu_alert_rq_a_ss_cnip_name + Acu_alert_rq_ss_cnip_name_size + 1)


#define Acu_alert_rq_a_end_strings				(uchar  *)Round8((unsigned long)Acu_alert_rq_a_tsp_ie_list + Acu_alert_rq_tsp_ie_list_size + 1)
#define Acu_alert_rq_total_size					(Acu_alert_rq_a_end_strings - (uchar  *)p_data) /* not including the ext parms */
#define Acu_alert_rq_start_ext_data             Acu_alert_rq_total_size   

#define	Acu_alert_rq_size						(Rnd_sizeof (struct acu_alert_rq_args))

/*----------------------------------------------------------------------------
*
*	ACU_ALERT_IN		alert indication
*
*	Arguments :
*		Acu_alert_in_alert 					: detected alert (Alert code)
*		Acu_alert_in_a_facility				: ISDN facility
*		Acu_alert_in_facility_size,
*		Acu_alert_in_a_facility				: ISDN facility
*		Acu_alert_in_display_size,
*		Acu_alert_in_a_display				: ISDN display Information
*		Acu_alert_in_pcs_user_protocol,
*		Acu_alert_in_pcs_user_size,
*		Acu_alert_in_a_pcs_user				: ISDN PCS-to-User/User-to-PCS Info.
*		Acu_alert_in_signal_val 			: signal value
*		Acu_alert_in_progress_location 		: progress location
*		Acu_alert_in_progress_description	: progress description
*
*--------------------------------------------------------------------------*/

struct acu_alert_in_args {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif
    

    struct acu_call_ref call_ref;	    /* call reference information */

	struct chani_list chani_list; 		/* list of channel ids to use for data transfer */
	struct acu_redir_nb   redir_nb;		/* redirected nb information */
	struct acu_display_list display;	/* display list */
	struct acu_progress_ind progress_ind;/* progress indicator */
	struct acu_name  ss_cnip_name;
    
	uchar	alert;						/* event parameter */
	uchar      uui_protocol;			/* UUI protocol-discriminator value */
	acu_size_t uui_size;				/* uui size */
	acu_size_t facility_size;			/* size of the facility */
	uchar      pcs_user_protocol;		/* PCS-to-User or User-to-PCS protocol-discriminator value */
	acu_size_t pcs_user_size;			/* size of the PCS-to-User or User-to-PCS information */
    
	uchar	signal_val;					/* signal value */
		
    
    
	acu_size_t q931_size;				/* size of Q.931 message */
		/* UUI is just here */
		/* then all the other strings in order */
};

#define	Acu_alert_in_							((struct acu_alert_in_args  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_alert_in_ext_parms_nb			Acu_alert_in_ ext_descr.nb
#	define Acu_alert_in_ext_parms_lgth			Acu_alert_in_ ext_descr.lgth
#	define Acu_alert_in_a_ext_parms				((Acu_ext_descr_offset = Acu_alert_in_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define	Acu_alert_in_alert						Acu_alert_in_ alert

#define Acu_alert_in_call_ref_length		    Acu_alert_in_ call_ref.length
#define Acu_alert_in_call_ref_value		        Acu_alert_in_ call_ref.value

#define Acu_alert_in_data_chani_nb				Acu_alert_in_ chani_list.nb
#define Acu_alert_in_data_chani					Acu_alert_in_ chani_list.tab[0].chan_id
#define Acu_alert_in_data_chani_nai				Acu_alert_in_ chani_list.tab[0].nai
#define Acu_alert_in_data_chani_tab(i)			Acu_alert_in_ chani_list.tab[i].chan_id
#define Acu_alert_in_data_chani_tab_nai(i)		Acu_alert_in_ chani_list.tab[i].nai
#define Acu_alert_in_data_chani_excl        	Acu_alert_in_ chani_list.chan_id_excl

#define	Acu_alert_in_redir_nb_pres				Acu_alert_in_ redir_nb.pres
#define	Acu_alert_in_redir_nb_type				Acu_alert_in_ redir_nb.type
#define	Acu_alert_in_redir_nb_plan				Acu_alert_in_ redir_nb.plan
#define	Acu_alert_in_redir_nb_screen			Acu_alert_in_ redir_nb.screen
#define	Acu_alert_in_redir_nb_reason			Acu_alert_in_ redir_nb.reason
#define	Acu_alert_in_redir_nb_size				Acu_alert_in_ redir_nb.size

#define	Acu_alert_in_ss_cnip_name_size		    Acu_alert_in_ ss_cnip_name.size
#define	Acu_alert_in_ss_cnip_name_pres		    Acu_alert_in_ ss_cnip_name.pres
#define	Acu_alert_in_ss_cnip_name_active		Acu_alert_in_ ss_cnip_name.active
#define	Acu_alert_in_ss_cnip_name				Acu_alert_in_ ss_cnip_name

#define	Acu_alert_in_uui_protocol				Acu_alert_in_ uui_protocol
#define	Acu_alert_in_uui_size					Acu_alert_in_ uui_size
#define	Acu_alert_in_facility_size				Acu_alert_in_ facility_size
#define	Acu_alert_in_display_size				Acu_alert_in_x_display_total_size
#define Acu_alert_in_pcs_user_protocol			Acu_alert_in_ pcs_user_protocol
#define Acu_alert_in_pcs_user_size				Acu_alert_in_ pcs_user_size

#define Acu_alert_in_x_display_nb				Acu_alert_in_ display.nb
#define Acu_alert_in_x_display_total_size		Acu_alert_in_ display.total_size
#define Acu_alert_in_x_p_display(i) 			Acu_alert_in_ display.p_display[i]
#define Acu_alert_in_x_display_type(i)			Acu_alert_in_ display.type[i]
#define Acu_alert_in_x_display_size(i)			Acu_alert_in_ display.size[i]
#define Acu_alert_in_a_display_list   		  &(Acu_alert_in_ display)

#define	Acu_alert_in_signal_val					Acu_alert_in_ signal_val

#define	Acu_alert_in_progress_ind_nb			Acu_alert_in_ progress_ind.nb
#define	Acu_alert_in_progress_location			Acu_alert_in_progress_loc
#define	Acu_alert_in_progress_description		Acu_alert_in_progress_descr
/* aliases */
#define	Acu_alert_in_progress_loc				Acu_alert_in_ progress_ind.t[0].loc
#define	Acu_alert_in_progress_descr				Acu_alert_in_ progress_ind.t[0].descr
/* access to other occurencies */
#define	Acu_alert_in_progress_loc_x(i)			Acu_alert_in_ progress_ind.t[i].loc
#define	Acu_alert_in_progress_descr_x(i)		Acu_alert_in_ progress_ind.t[i].descr

#define Acu_alert_in_q931_size					Acu_alert_in_ q931_size

#define	Acu_alert_in_a_redir_nb					((char  *)p_data + Acu_alert_in_size)
#define	Acu_alert_in_a_uui						(Acu_alert_in_a_redir_nb + Acu_alert_in_redir_nb_size)
#define	Acu_alert_in_a_facility					(Acu_alert_in_a_uui + Acu_alert_in_uui_size)
#define	Acu_alert_in_a_display					(Acu_alert_in_a_facility + Acu_alert_in_facility_size)
#define Acu_alert_in_a_pcs_user					(Acu_alert_in_a_display + Acu_alert_in_display_size)

#define Acu_alert_in_a_ss_cnip_name 			(Acu_alert_in_a_pcs_user + Acu_alert_in_pcs_user_size)
#define Acu_alert_in_a_q931						(Acu_alert_in_a_ss_cnip_name + Acu_alert_in_ss_cnip_name_size)


#define Acu_alert_in_a_end_strings				(uchar  *)Round8((unsigned long)Acu_alert_in_a_q931 + Acu_alert_in_q931_size)
#define Acu_alert_in_start_ext_data				(Acu_alert_in_a_end_strings-(uchar  *)p_data)

#define	Acu_alert_in_size						(Rnd_sizeof (struct acu_alert_in_args))

/*---------------------------------------------------------------------------
*
*	ACU_USER_INFO_RQ/IN		User Information (ISDN only).
*
*--------------------------------------------------------------------------*/

struct acu_user_info {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif
    
	uchar	fac_protocol_discr;			/* user facility protocol discriminator */
	uchar      uui_protocol;			/* UUI protocol-discriminator value */
	acu_size_t uui_size;				/* uui size */
	acu_size_t fac_size;				/* user facility size */
    
	acu_size_t tsp_ie_list_size;		/* length of the list of transparent IE's */
	acu_size_t q931_size;				/* size of Q.931 message */
	pad2
		
		/* UUI is just here */
		/* then all the other strings in order */
};

#define	Acu_user_info_				((struct acu_user_info  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_user_info_ext_parms_nb	Acu_user_info_ ext_descr.nb
#	define Acu_user_info_ext_parms_lgth	Acu_user_info_ ext_descr.lgth
#	define Acu_user_info_a_ext_parms	((Acu_ext_descr_offset = Acu_user_info_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define	Acu_user_info_fac_protocol_discr	Acu_user_info_ fac_protocol_discr

#define	Acu_user_info_uui_protocol	Acu_user_info_ uui_protocol
#define	Acu_user_info_uui_size		Acu_user_info_ uui_size
#define	Acu_user_info_fac_size		Acu_user_info_ fac_size

#define Acu_user_info_tsp_ie_list_size	Acu_user_info_ tsp_ie_list_size

#define Acu_user_info_q931_size		Acu_user_info_ q931_size

#define	Acu_user_info_a_uui			((char  *)p_data  + Acu_user_info_size)
#define	Acu_user_info_a_fac			(Acu_user_info_a_uui + Acu_user_info_uui_size + 1)

#define Acu_user_info_a_tsp_ie_list (Acu_user_info_a_fac + Acu_user_info_fac_size + 1)

#define Acu_user_info_a_q931		(Acu_user_info_a_tsp_ie_list + Acu_user_info_tsp_ie_list_size)

#define Acu_user_info_a_end_strings	(uchar  *)Round8((unsigned long)Acu_user_info_a_q931 + Acu_user_info_q931_size)
#define Acu_user_info_total_size	(Acu_user_info_a_end_strings - (uchar  *)p_data) /* not including the ext parms */
#define Acu_user_info_start_ext_data Acu_user_info_total_size

#define	Acu_user_info_size			(Rnd_sizeof (struct acu_user_info))

/*----------------------------------------------------------------------------
*
*	ACU_CLEAR_RQ			request call clearing.
*
*	Arguments :
*		Acu_clear_rq_priority   : call clear priority normal/urgent (ACU_PHIGH/ACU_PLOW)
*		Acu_clear_rq_cause		: call clearing cause value to be sent
*								  (if 0, "Normal Clearing" (16) is sent).
*		Acu_clear_rq_cause_location: cause location
*		Acu_clear_rq_uui_size,
*		Acu_clear_rq_a_uui		: ISDN user to User Information
*		Acu_clear_rq_facility_size,
*		Acu_clear_rq_facility	: facility
*		Acu_clear_rq_pcs_user_protocol,
*		Acu_clear_rq_pcs_user_size,
*		Acu_clear_rq_a_pcs_user	: ISDN PCS-to-User/User-to-PCS Info.
*		Acu_clear_rq_signal_val	: signal value
*
*--------------------------------------------------------------------------*/

struct acu_clear_rq_args {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif
	struct acu_charging_info charging_info;	/* charging information */
	struct acu_display_list display;	/* display list */
	struct acu_name  ss_cnip_name;
    
	uchar	priority;					/* phone call priority */
	uchar	cause;						/* clearing cause value */
	uchar	cause_location;				/* clearing cause location */
    
	uchar      uui_protocol;			/* UUI protocol-discriminator value */
	acu_size_t uui_size;				/* size of the ISDN User to User information field */
	acu_size_t facility_size;			/* size of the facility */
	uchar      pcs_user_protocol;		/* PCS-to-User or User-to-PCS protocol-discriminator value */
	acu_size_t pcs_user_size;			/* size of the PCS-to-User or User-to-PCS information */
    
	uchar	signal_val;					/* signal value */
    
	acu_size_t tsp_ie_list_size;		/* length of the list of transparent IE's */
	pad6
		
		/* UUI is just here */
		/* then all the other strings in order */
};

#define	Acu_clear_rq_					((struct acu_clear_rq_args  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_clear_rq_ext_parms_nb	Acu_clear_rq_ ext_descr.nb
#	define Acu_clear_rq_ext_parms_lgth	Acu_clear_rq_ ext_descr.lgth
#	define Acu_clear_rq_a_ext_parms		((Acu_ext_descr_offset = Acu_clear_rq_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define	Acu_clear_rq_priority			Acu_clear_rq_ priority
#define	Acu_clear_rq_cause				Acu_clear_rq_ cause
#define	Acu_clear_rq_cause_location		Acu_clear_rq_ cause_location

#define	Acu_clear_rq_charging_available	Acu_clear_rq_ charging_info.available
#define Acu_clear_rq_charging_value     Acu_clear_rq_ charging_info.value
#define Acu_clear_rq_charging_type     	Acu_clear_rq_ charging_info.type
#define Acu_clear_rq_charging_period    Acu_clear_rq_ charging_info.period
#define Acu_clear_rq_charging_multi     Acu_clear_rq_ charging_info.multi
#define Acu_clear_rq_charging	     	Acu_clear_rq_charging_value	/* alias */
#define	Acu_clear_rq_total_cost			Acu_clear_rq_charging /* alias */

#define	Acu_clear_rq_ss_cnip_name_size		    Acu_clear_rq_ ss_cnip_name.size
#define	Acu_clear_rq_ss_cnip_name_pres		    Acu_clear_rq_ ss_cnip_name.pres
#define	Acu_clear_rq_ss_cnip_name_active		Acu_clear_rq_ ss_cnip_name.active
#define	Acu_clear_rq_ss_cnip_name				Acu_clear_rq_ ss_cnip_name
/* aliases */
#define	Acu_clear_rq_ss_conp_name_size		    Acu_clear_rq_ss_cnip_name_size
#define	Acu_clear_rq_ss_conp_name_pres		    Acu_clear_rq_ss_cnip_name_pres
#define	Acu_clear_rq_ss_conp_name_active		Acu_clear_rq_ss_cnip_name_active
#define	Acu_clear_rq_ss_conp_name				Acu_clear_rq_ss_cnip_name

#define	Acu_clear_rq_uui_protocol		Acu_clear_rq_ uui_protocol
#define	Acu_clear_rq_uui_protocol_disc	Acu_clear_rq_uui_protocol /* alias */
#define	Acu_clear_rq_uui_size			Acu_clear_rq_ uui_size
#define	Acu_clear_rq_facility_size		Acu_clear_rq_ facility_size
#define	Acu_clear_rq_display_size		Acu_clear_rq_x_display_total_size
#define Acu_clear_rq_pcs_user_protocol	Acu_clear_rq_ pcs_user_protocol
#define Acu_clear_rq_pcs_user_size		Acu_clear_rq_ pcs_user_size

#define Acu_clear_rq_x_display_nb		Acu_clear_rq_ display.nb
#define Acu_clear_rq_x_display_total_size Acu_clear_rq_ display.total_size
#define Acu_clear_rq_x_p_display(i) 	Acu_clear_rq_ display.p_display[i]
#define Acu_clear_rq_x_display_type(i)	Acu_clear_rq_ display.type[i]
#define Acu_clear_rq_x_display_size(i)	Acu_clear_rq_ display.size[i]
#define Acu_clear_rq_a_display_list		&(Acu_clear_rq_ display)

#define	Acu_clear_rq_signal_val			Acu_clear_rq_ signal_val

#define Acu_clear_rq_tsp_ie_list_size	Acu_clear_rq_ tsp_ie_list_size

#define	Acu_clear_rq_a_uui				((char  *)p_data + Acu_clear_rq_size)
#define	Acu_clear_rq_a_facility			(Acu_clear_rq_a_uui + Acu_clear_rq_uui_size + 1)
#define	Acu_clear_rq_a_display			(Acu_clear_rq_a_facility + Acu_clear_rq_facility_size + 1)
#define Acu_clear_rq_a_pcs_user			(Acu_clear_rq_a_display  + Acu_clear_rq_display_size  + 1)

#define Acu_clear_rq_a_ss_cnip_name 	(Acu_clear_rq_a_pcs_user  + Acu_clear_rq_pcs_user_size  + 1)
/* alias */
#define Acu_clear_rq_a_ss_conp_name 	Acu_clear_rq_a_ss_cnip_name
#define Acu_clear_rq_a_tsp_ie_list		(Acu_clear_rq_a_ss_cnip_name + Acu_clear_rq_ss_cnip_name_size + 1)


#define Acu_clear_rq_a_end_strings		(uchar  *)Round8((unsigned long)Acu_clear_rq_a_tsp_ie_list + Acu_clear_rq_tsp_ie_list_size + 1)
#define Acu_clear_rq_total_size			(Acu_clear_rq_a_end_strings - (uchar  *)p_data) /* not including the ext parms */
#define Acu_clear_rq_start_ext_data     Acu_clear_rq_total_size

#define	Acu_clear_rq_size				(Rnd_sizeof (struct acu_clear_rq_args))

/*----------------------------------------------------------------------------
*
*	ACU_CLEAR_IN			call cleared indication.
*
*	Arguments :
*		Acu_clear_in_ret_code 		: return code (ACURC_BUSY, etc., described
*								  		below)
*		Acu_clear_in_charging_vlaue	: charging value (nb of units)
*		Acu_clear_in_charging_type	: charging type
*		Acu_clear_in_charging_period: charging period
*		Acu_clear_in_charging_multi	: charging multiplier
*		Acu_clear_in_total_cost     : alias for charging field
*		Acu_clear_in_uui_protocol,
*		Acu_clear_in_uui_size,
*		Acu_clear_in_a_uui			: ISDN user to User Information
*		Acu_clear_in_facility_size,
*		Acu_clear_in_a_facility		: ISDN facility
*		Acu_clear_in_display_size,
*		Acu_clear_in_a_display		: ISDN display Information
*		Acu_clear_in_pcs_user_protool
*		Acu_clear_in_pcs_user_size,
*		Acu_clear_in_a_pcs_user		: ISDN PCS-to-User/User-to-PCS Info.
*		Acu_clear_in_signal_val		: signal value
*
*--------------------------------------------------------------------------*/

struct acu_clear_in_args {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif
	struct acu_charging_info charging_info;	/* charging information */
	struct acu_display_list display;	/* display list */
	struct acu_progress_ind progress_ind;/* progress indicator */
	struct acu_name  ss_cnip_name;
    
	uchar	return_code;				/* clear cause code */
	uchar	network_cause;				/* Network-provided clear cause value */
	uchar	network_cause_loc;			/* Network-provided clear cause location */
    
	uchar      uui_protocol;			/* UUI protocol-discriminator value */
	acu_size_t uui_size;				/* size of the ISDN User to User information field */
	acu_size_t facility_size;			/* size of the facility */
	uchar      pcs_user_protocol;		/* PCS-to-User or User-to-PCS protocol-discriminator value */
	acu_size_t pcs_user_size;			/* size of the PCS-to-User or User-to-PCS information */
	uchar	signal_val;					/* signal value */
	acu_size_t q931_size;				/* size of Q.931 message */
	pad6
		/* UUI is just here */
		/* then all the other strings in order */
};

#define	Acu_clear_in_					((struct acu_clear_in_args  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_clear_in_ext_parms_nb	Acu_clear_in_ ext_descr.nb
#	define Acu_clear_in_ext_parms_lgth	Acu_clear_in_ ext_descr.lgth
#	define Acu_clear_in_a_ext_parms		((Acu_ext_descr_offset = Acu_clear_in_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define	Acu_clear_in_ret_code			Acu_clear_in_ return_code
#define	Acu_clear_in_network_cause		Acu_clear_in_ network_cause
#define	Acu_clear_in_network_cause_loc	Acu_clear_in_ network_cause_loc

#define	Acu_clear_in_charging_available	Acu_clear_in_ charging_info.available
#define Acu_clear_in_charging_value     Acu_clear_in_ charging_info.value
#define Acu_clear_in_charging_type     	Acu_clear_in_ charging_info.type
#define Acu_clear_in_charging_period    Acu_clear_in_ charging_info.period
#define Acu_clear_in_charging_multi     Acu_clear_in_ charging_info.multi
#define Acu_clear_in_charging	     	Acu_clear_in_charging_value	/* alias */
#define	Acu_clear_in_total_cost			Acu_clear_in_charging /* alias */
#define	Acu_clear_in_ss_cnip_name_size		    Acu_clear_in_ ss_cnip_name.size
#define	Acu_clear_in_ss_cnip_name_pres		    Acu_clear_in_ ss_cnip_name.pres
#define	Acu_clear_in_ss_cnip_name_active		Acu_clear_in_ ss_cnip_name.active
#define	Acu_clear_in_ss_cnip_name				Acu_clear_in_ ss_cnip_name

#define	Acu_clear_in_uui_protocol		Acu_clear_in_ uui_protocol
#define	Acu_clear_in_uui_size			Acu_clear_in_ uui_size
#define	Acu_clear_in_facility_size		Acu_clear_in_ facility_size
#define	Acu_clear_in_display_size		Acu_clear_in_x_display_total_size
#define Acu_clear_in_pcs_user_protocol	Acu_clear_in_ pcs_user_protocol
#define Acu_clear_in_pcs_user_size		Acu_clear_in_ pcs_user_size

#define Acu_clear_in_x_display_nb		Acu_clear_in_ display.nb
#define Acu_clear_in_x_display_total_size Acu_clear_in_ display.total_size
#define Acu_clear_in_x_p_display(i) 	Acu_clear_in_ display.p_display[i]
#define Acu_clear_in_x_display_type(i)	Acu_clear_in_ display.type[i]
#define Acu_clear_in_x_display_size(i)	Acu_clear_in_ display.size[i]
#define Acu_clear_in_a_display_list   	&(Acu_clear_in_ display)

#define	Acu_clear_in_signal_val			Acu_clear_in_ signal_val

#define	Acu_clear_in_progress_ind_nb	Acu_clear_in_ progress_ind.nb
#define	Acu_clear_in_progress_location	Acu_clear_in_progress_loc
#define	Acu_clear_in_progress_description Acu_clear_in_progress_descr
/* aliases */
#define	Acu_clear_in_progress_loc		Acu_clear_in_ progress_ind.t[0].loc
#define	Acu_clear_in_progress_descr		Acu_clear_in_ progress_ind.t[0].descr
/* access to other occurencies */
#define	Acu_clear_in_progress_loc_x(i)	Acu_clear_in_ progress_ind.t[i].loc
#define	Acu_clear_in_progress_descr_x(i) Acu_clear_in_ progress_ind.t[i].descr

#define Acu_clear_in_q931_size			Acu_clear_in_ q931_size

#define	Acu_clear_in_a_uui				((char  *)p_data + Acu_clear_in_size)
#define	Acu_clear_in_a_facility			(Acu_clear_in_a_uui + Acu_clear_in_uui_size)
#define	Acu_clear_in_a_display			(Acu_clear_in_a_facility + Acu_clear_in_facility_size)
#define Acu_clear_in_a_pcs_user			(Acu_clear_in_a_display  + Acu_clear_in_display_size)

#define Acu_clear_in_a_ss_cnip_name 	(Acu_clear_in_a_pcs_user  + Acu_clear_in_pcs_user_size)
#define Acu_clear_in_a_q931				(Acu_clear_in_a_ss_cnip_name + Acu_clear_in_ss_cnip_name_size)


#define Acu_clear_in_a_end_strings		(uchar  *)Round8((unsigned long)Acu_clear_in_a_q931 + Acu_clear_in_q931_size)
#define Acu_clear_in_start_ext_data     (Acu_clear_in_a_end_strings-(uchar  *)p_data)

#define	Acu_clear_in_size				(Rnd_sizeof (struct acu_clear_in_args))

/*----------------------------------------------------------------------------
*
*	ACU_CLEAR_RS			call clearing response.
*
*	Arguments :
*		Acu_clear_rs_priority   : primitive priority (ACU_PHIGH/ACU_PLOW)
*		Acu_clear_rs_uui_protocol,
*		Acu_clear_rs_uui_size,
*		Acu_clear_rs_a_uui		: ISDN user to User Information
*		Acu_clear_rs_facility_size,
*		Acu_clear_rs_facility	: facility
*		Acu_clear_rs_pcs_user_protocol,
*		Acu_clear_rs_pcs_user_size,
*		Acu_clear_rs_a_pcs_user	: ISDN PCS-to-User/User-to-PCS Info.
*
*--------------------------------------------------------------------------*/

struct acu_clear_rs_args {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif
	struct acu_charging_info charging_info;	/* charging information */
	struct acu_display_list display;	/* display list */
    
	uchar	priority;					/* phone call priority */
    
	uchar      uui_protocol;			/* UUI protocol-discriminator value */
	acu_size_t uui_size;				/* size of the ISDN User to User information field */
	acu_size_t facility_size;			/* size of the facility */
	uchar      pcs_user_protocol;		/* PCS-to-User or User-to-PCS protocol-discriminator value */
	acu_size_t pcs_user_size;			/* size of the PCS-to-User or User-to-PCS information */
	acu_size_t tsp_ie_list_size;		/* length of the list of transparent IE's */
	pad1
		
		/* UUI is just here */
		/* then all the other strings in order */
};

#define	Acu_clear_rs_					((struct acu_clear_rs_args  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_clear_rs_ext_parms_nb	Acu_clear_rs_ ext_descr.nb
#	define Acu_clear_rs_ext_parms_lgth	Acu_clear_rs_ ext_descr.lgth
#	define Acu_clear_rs_a_ext_parms		((Acu_ext_descr_offset = Acu_clear_rs_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define	Acu_clear_rs_priority			Acu_clear_rs_ priority

#define	Acu_clear_rs_charging_available	Acu_clear_rs_ charging_info.available
#define Acu_clear_rs_charging_value     Acu_clear_rs_ charging_info.value
#define Acu_clear_rs_charging_type     	Acu_clear_rs_ charging_info.type
#define Acu_clear_rs_charging_period    Acu_clear_rs_ charging_info.period
#define Acu_clear_rs_charging_multi     Acu_clear_rs_ charging_info.multi
#define Acu_clear_rs_charging	     	Acu_clear_rs_charging_value	/* alias */

#define	Acu_clear_rs_uui_protocol		Acu_clear_rs_ uui_protocol
#define	Acu_clear_rs_uui_size			Acu_clear_rs_ uui_size
#define	Acu_clear_rs_facility_size		Acu_clear_rs_ facility_size
#define	Acu_clear_rs_display_size		Acu_clear_rs_x_display_total_size
#define Acu_clear_rs_pcs_user_protocol	Acu_clear_rs_ pcs_user_protocol
#define Acu_clear_rs_pcs_user_size		Acu_clear_rs_ pcs_user_size

#define Acu_clear_rs_x_display_nb		Acu_clear_rs_ display.nb
#define Acu_clear_rs_x_display_total_size Acu_clear_rs_ display.total_size
#define Acu_clear_rs_x_p_display(i) 	Acu_clear_rs_ display.p_display[i]
#define Acu_clear_rs_x_display_type(i)	Acu_clear_rs_ display.type[i]
#define Acu_clear_rs_x_display_size(i)	Acu_clear_rs_ display.size[i]
#define Acu_clear_rs_a_display_list		&(Acu_clear_rs_ display)

#define Acu_clear_rs_tsp_ie_list_size	Acu_clear_rs_ tsp_ie_list_size

#define	Acu_clear_rs_a_uui				((char  *)p_data + Acu_clear_rs_size)
#define	Acu_clear_rs_a_facility			(Acu_clear_rs_a_uui + Acu_clear_rs_uui_size + 1)
#define	Acu_clear_rs_a_display			(Acu_clear_rs_a_facility + Acu_clear_rs_facility_size + 1)
#define Acu_clear_rs_a_pcs_user			(Acu_clear_rs_a_display  + Acu_clear_rs_display_size  + 1)

#define Acu_clear_rs_a_tsp_ie_list		(Acu_clear_rs_a_pcs_user + Acu_clear_rs_pcs_user_size + 1)

#define Acu_clear_rs_a_end_strings		(uchar  *)Round8((unsigned long)Acu_clear_rs_a_tsp_ie_list + Acu_clear_rs_tsp_ie_list_size + 1)
#define Acu_clear_rs_total_size			(Acu_clear_rs_a_end_strings - (uchar  *)p_data) /* not including the ext parms */
#define Acu_clear_rs_start_ext_data     Acu_clear_rs_total_size

#define	Acu_clear_rs_size				(Rnd_sizeof (struct acu_clear_rs_args))

/*----------------------------------------------------------------------------
*
*	ACU_CLEAR_CO			call cleared confirmation.
*
*	Arguments :
*		Acu_clear_co_ret_code 		: return code (ACURC_BUSY, etc., see ACU_CLEAR_IN)
*		Acu_clear_co_network_cause	: clear cause, as provided by the network
*		Acu_clear_co_charging		: charging (nb of units)
*		Acu_clear_co_charging_type	: charging type
*		Acu_clear_co_charging_period: charging period
*		Acu_clear_co_charging_multi	: charging multiplier
*		Acu_clear_co_total_cost     : alias for charging field
*		Acu_clear_co_uui_protocol,
*		Acu_clear_co_uui_size,
*		Acu_clear_co_a_uui			: ISDN User to User Information
*		Acu_clear_co_facility_size,
*		Acu_clear_co_a_facility		: ISDN facility
*		Acu_clear_co_display_size,
*		Acu_clear_co_a_display		: ISDN display Information
*		Acu_clear_co_pcs_user_protocol,
*		Acu_clear_co_pcs_user_size,
*		Acu_clear_co_a_pcs_user		: ISDN PCS-to-User/User-to-PCS Info.
*
*--------------------------------------------------------------------------*/

struct acu_clear_co_args {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif
    struct acu_charging_info charging_info;	/* charging information */
    struct acu_display_list display;	/* display list */
    
	uchar	return_code;				/* clear cause code */
	uchar	network_cause;				/* Network-provided clear cause value */
	uchar	network_cause_loc;			/* Network-provided clear cause location */
    
	uchar      uui_protocol;			/* UUI protocol-discriminator value */
	acu_size_t uui_size;				/* size of the ISDN User to User information field */
	acu_size_t facility_size;			/* size of the facility */
	uchar      pcs_user_protocol;		/* PCS-to-User or User-to-PCS protocol-discriminator value */
	acu_size_t pcs_user_size;			/* size of the PCS-to-User or User-to-PCS information */
	acu_size_t q931_size;				/* size of Q.931 message */
	pad7
		
		/* UUI is just here */
		/* then all the other strings in order */
};

#define	Acu_clear_co_					((struct acu_clear_co_args  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_clear_co_ext_parms_nb	Acu_clear_co_ ext_descr.nb
#	define Acu_clear_co_ext_parms_lgth	Acu_clear_co_ ext_descr.lgth
#	define Acu_clear_co_a_ext_parms		((Acu_ext_descr_offset = Acu_clear_co_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define	Acu_clear_co_ret_code			Acu_clear_co_ return_code
#define	Acu_clear_co_network_cause		Acu_clear_co_ network_cause
#define	Acu_clear_co_network_cause_loc	Acu_clear_co_ network_cause_loc

#define	Acu_clear_co_charging_available	Acu_clear_co_ charging_info.available
#define Acu_clear_co_charging_value     Acu_clear_co_ charging_info.value
#define Acu_clear_co_charging_type     	Acu_clear_co_ charging_info.type
#define Acu_clear_co_charging_period    Acu_clear_co_ charging_info.period
#define Acu_clear_co_charging_multi     Acu_clear_co_ charging_info.multi
#define Acu_clear_co_charging	     	Acu_clear_co_charging_value	/* alias */
#define	Acu_clear_co_total_cost		 	Acu_clear_co_charging /* alias */

#define	Acu_clear_co_uui_protocol		Acu_clear_co_ uui_protocol
#define	Acu_clear_co_uui_size			Acu_clear_co_ uui_size
#define	Acu_clear_co_facility_size		Acu_clear_co_ facility_size
#define	Acu_clear_co_display_size		Acu_clear_co_x_display_total_size
#define Acu_clear_co_pcs_user_protocol	Acu_clear_co_ pcs_user_protocol
#define Acu_clear_co_pcs_user_size		Acu_clear_co_ pcs_user_size

#define Acu_clear_co_x_display_nb		Acu_clear_co_ display.nb
#define Acu_clear_co_x_display_total_size Acu_clear_co_ display.total_size
#define Acu_clear_co_x_p_display(i) 	Acu_clear_co_ display.p_display[i]
#define Acu_clear_co_x_display_type(i)	Acu_clear_co_ display.type[i]
#define Acu_clear_co_x_display_size(i)	Acu_clear_co_ display.size[i]
#define Acu_clear_co_a_display_list   	&(Acu_clear_co_ display)

#define Acu_clear_co_q931_size			Acu_clear_co_ q931_size

#define	Acu_clear_co_a_uui				((char  *)p_data + Acu_clear_co_size)
#define	Acu_clear_co_a_facility			(Acu_clear_co_a_uui + Acu_clear_co_uui_size)
#define	Acu_clear_co_a_display			(Acu_clear_co_a_facility + Acu_clear_co_facility_size)
#define Acu_clear_co_a_pcs_user			(Acu_clear_co_a_display + Acu_clear_co_display_size)

#define Acu_clear_co_a_q931				(Acu_clear_co_a_pcs_user + Acu_clear_co_pcs_user_size)


#define Acu_clear_co_a_end_strings		(uchar  *)Round8((unsigned long)Acu_clear_co_a_q931 + Acu_clear_co_q931_size)
#define Acu_clear_co_total_size			(Acu_clear_co_a_end_strings - (uchar  *)p_data) /* not including the ext parms */
#define Acu_clear_co_start_ext_data     Acu_clear_co_total_size

#define	Acu_clear_co_size				(Rnd_sizeof (struct acu_clear_co_args))

/*---------------------------------------------------------------------------
*
*	ACU_INFO_RQ		Get a Automatic Call Unit parameter (Analog ACU only)
*
*	Arguments :
*		Acu_info_rq_name : parameter reference (ACU_NRINGS, ACU_PULSE, etc)
*
*--------------------------------------------------------------------------*/

struct acu_info_rq_args {
	uchar	name;		/* parameter name */
	pad7
};

#define	Acu_info_rq_name			(((struct acu_info_rq_args  *)p_data) -> name)

#define	Acu_info_rq_size			(Rnd_sizeof (struct acu_info_rq_args))

/*---------------------------------------------------------------------------
*
*	ACU_INFO_CO		confirmation with informations (Analog ACU only).
*
*	Arguments :
*		Acu_info_co_name	 : parameter name (ACU_NRINGS, ACU_PULSE, etc)
*		Acu_info_co_value	 : parameter value (WORD).
*
*--------------------------------------------------------------------------*/

struct acu_info_co_args {
	timer_val_t		interdigit;		/* pulse dialing interdigit duration */
    WORD			value;			/* parameter value */
	uchar			name;			/* parameter name */
	uchar			ratio;			/* pulse dialing break ratio, 0..100 */
	uchar			rate;			/* pulse dialing rate, 1..20 */
	uchar			p_map;			/* pulse dialing map, 0..2 */
	pad6
};

#define	Acu_info_co_				((struct acu_info_co_args  *)p_data) ->
#define	Acu_info_co_name			Acu_info_co_ name
#define	Acu_info_co_value			Acu_info_co_ value

#define	Acu_info_co_ratio			Acu_info_co_ ratio
#define	Acu_info_co_rate			Acu_info_co_ rate
#define	Acu_info_co_p_map			Acu_info_co_ p_map
#define	Acu_info_co_inter_digit		Acu_info_co_ interdigit

#define Acu_info_co_size			(Rnd_sizeof (struct acu_info_co_args))

/*---------------------------------------------------------------------------
*
*	ACU_INIT_RQ			initialize a 'primitive path'.
*
*	Arguments :
*		Acu_init_rq_priority 	: primitive priority normal/urgent
*		Acu_init_rq_new_user 	: name of the new user entity on the Network Access
*		Acu_init_rq_new_sapi 	: name of the new sapi on the Network Access
*
*--------------------------------------------------------------------------*/

struct acu_init_rq_args {
	uchar			priority;		/* primitive priority */
	ent_id_t		new_user;		/* new user entity */
	sapi_t			new_sapi;		/* new sapi */
	pad5
};

#define	Acu_init_rq_				((struct acu_init_rq_args  *)p_data) ->
#define	Acu_init_rq_priority		Acu_init_rq_ priority
#define	Acu_init_rq_new_user		Acu_init_rq_ new_user
#define	Acu_init_rq_new_sapi		Acu_init_rq_ new_sapi

#define	Acu_init_rq_size			(Rnd_sizeof (struct acu_init_rq_args))

/*---------------------------------------------------------------------------
*
*	ACU_INIT_CO		'primitive path' initialization confirmation
*
*	Arguments :
*		Acu_init_co_ret_code	: return code (OK/NOK)
*      Acu_init_co_diagnostic	: diagnostic
*
*--------------------------------------------------------------------------*/

struct acu_init_co_args {
	struct confirm 		confirm;	/* confirmation structure */
};

#define	Acu_init_co_				((struct acu_init_co_args  *)p_data) ->
#define	Acu_init_co_ret_code		Acu_init_co_ confirm.return_code
#define	Acu_init_co_diagnostic		Acu_init_co_ confirm.diagnostic

#define	Acu_init_co_size			(Rnd_sizeof (struct acu_init_co_args))

/*---------------------------------------------------------------------------
*
*	ACU_SETPARM_RQ		Set a Automatic Call Unit parameter (Analog ACU only).
*
*	Arguments :
*		Acu_setparm_rq_name		: parameter name (ACU_NRINGS, ACU_TPULSE, etc).
*		Acu_setparm_rq_value	: parameter value (WORD)
*
*--------------------------------------------------------------------------*/

struct acu_setparm_rq_args {
 	timer_val_t		inter_digit;	/* pulse dialing interdigit duration */
    WORD			value;			/* parameter value */
	uchar			name;			/* parameter name */
	uchar			ratio;			/* pulse dialing break ratio, 0..100 */
	uchar			rate;			/* pulse dialing rate, 1..20 */
	uchar			p_map;			/* pulse dialing map, 0..2 */
	pad6
};

#define	Acu_setparm_rq_				((struct acu_setparm_rq_args  *)p_data) ->
#define	Acu_setparm_rq_name			Acu_setparm_rq_ name
#define	Acu_setparm_rq_value		Acu_setparm_rq_ value
#define	Acu_setparm_rq_ratio		Acu_setparm_rq_ ratio
#define	Acu_setparm_rq_rate			Acu_setparm_rq_ rate
#define	Acu_setparm_rq_p_map		Acu_setparm_rq_ p_map
#define	Acu_setparm_rq_inter_digit	Acu_setparm_rq_ inter_digit

#define	Acu_setparm_rq_size			(Rnd_sizeof (struct acu_setparm_rq_args))

/*---------------------------------------------------------------------------
*
*	ACU_SETPARM_CO		confirm that parameter has been set.
*
*  Arguments : none
*
*--------------------------------------------------------------------------*/

struct acu_setparm_co_args {
	uchar	dummy;
	pad7
};

#define	Acu_setparm_co_size			(Rnd_sizeof (struct acu_setparm_co_args))

/*---------------------------------------------------------------------------
*
*  ACU_SET_MODE_RQ/CO  request/confirm setting of a particular mode.
*
*  (uses the ACU_SAPI_MGT sapi) (ISDN only).
*
*  Arguments:
*
*  ACU_SET_MODE_RQ:
*
*      Acu_set_mode_action = { ACU_RQ_ACTIVATE, ACU_RQ_CLEAR, ACU_RQ_ENQUIRY }
*
*      Acu_set_mode_code   = {
*
*          - ACU_MODE_ALL_NA_OUT_OF_ORDER: allow/forbid calls on all NAIs.
*
*          - ACU_MODE_NA_OUT_OF_ORDER: allow/forbid calls on NAI given by
*              R_msg_nai.
*
*          - ACU_MODE_CALL_OUT_OF_ORDER: allow/forbid calls on NAI/CONN_ID
*              given by R_msg_nai/R_msg_conn_id.
*
*          - ACU_MODE_CHANI_OUT_OF_ORDER: allow/forbid usage of the
*              B-channel given by Acu_set_mode_data_chani.
*
*  ACU_SET_MODE_CO:
*
*      Acu_set_mode_action: { ACU_CO_ACK, ACU_CO_REJ }
*
*--------------------------------------------------------------------------*/

struct acu_set_mode {
	uchar 	action;
	uchar	code;
    
	uchar	data_chani;
	pad5
};

#define	Acu_set_mode_					((struct acu_set_mode  *)p_data) ->
#define	Acu_set_mode_action				Acu_set_mode_ action
#define	Acu_set_mode_code				Acu_set_mode_ code
#define	Acu_set_mode_data_chani			Acu_set_mode_ data_chani

#define	Acu_set_mode_size				(Rnd_sizeof (struct acu_set_mode))

/*---------------------------------------------------------------------------
*
*	ACU_RS_MODE_RQ/CO		Response mode (global connection). ISDN only.
*
*--------------------------------------------------------------------------*/

struct acu_rs_mode {
	char	fac[ACU_MX_SZ_USER_FAC+1];	/* user facility */
	uchar	service;					/* select the service */
	uchar	mode;						/* response mode */
	uchar	fac_protocol_discr;			/* user facility protocol discriminator */
	uchar	reserved;					/* for fields alignment */
	acu_size_t uui_size;				/* uui size */
	pad3

};

#define	Acu_rs_mode_					((struct acu_rs_mode  *)p_data) ->
#define	Acu_rs_mode_service				Acu_rs_mode_ service
#define	Acu_rs_mode_value				Acu_rs_mode_ mode
#define	Acu_rs_mode_fac_protocol_discr	Acu_rs_mode_ fac_protocol_discr
#define	Acu_rs_mode_a_fac				(&Acu_rs_mode_ fac[0])
#define	Acu_rs_mode_uui_size			Acu_rs_mode_ uui_size
#define	Acu_rs_mode_a_uui				((char  *)p_data + Acu_rs_mode_size)

#define	Acu_rs_mode_size				(Rnd_sizeof (struct acu_rs_mode))

/*---------------------------------------------------------------------------
*
*	ACU_SUSPEND_RQ/CO	Suspend a call. ISDN only.
*
*--------------------------------------------------------------------------*/

struct acu_suspend {
	struct acu_display_list display;	/* display list */
	char	call_id[ACU_MX_SZ_CALL_ID+1];	/* call identity */
	uchar	return_code;				/* return code : OK or NOK */
	uchar	network_cause;				/* Network-provided reject cause value */
	uchar	network_cause_loc;			/* Network-provided clear cause location */
	acu_size_t tsp_ie_list_size;		/* length of the list of transparent IE's */
	acu_size_t q931_size;				/* size of Q.931 message */
	pad6
		
		/* display strings are just here */
};

#define	Acu_suspend_					((struct acu_suspend  *)p_data) ->
#define	Acu_suspend_ret_code			Acu_suspend_ return_code
#define	Acu_suspend_network_cause		Acu_suspend_ network_cause
#define	Acu_suspend_network_cause_loc	Acu_suspend_ network_cause_loc
#define	Acu_suspend_a_call_id	   		Acu_suspend_ call_id

#define	Acu_suspend_display_size		Acu_suspend_x_display_total_size

#define Acu_suspend_x_display_nb		Acu_suspend_ display.nb
#define Acu_suspend_x_display_total_size Acu_suspend_ display.total_size
#define Acu_suspend_x_p_display(i) 		Acu_suspend_ display.p_display[i]
#define Acu_suspend_x_display_type(i)	Acu_suspend_ display.type[i]
#define Acu_suspend_x_display_size(i)	Acu_suspend_ display.size[i]
#define Acu_suspend_a_display_list   	&(Acu_suspend_ display)

#define Acu_suspend_tsp_ie_list_size	Acu_suspend_ tsp_ie_list_size

#define Acu_suspend_q931_size			Acu_suspend_ q931_size

#define	Acu_suspend_a_display			((char  *)p_data + Acu_suspend_size)
#define Acu_suspend_a_tsp_ie_list		(Acu_suspend_a_display + Acu_suspend_display_size + 1)

#define Acu_suspend_a_q931				(Acu_suspend_a_tsp_ie_list + Acu_suspend_tsp_ie_list_size)

#define Acu_suspend_a_end_strings       (uchar  *)Round8((unsigned long)Acu_suspend_a_q931 + Acu_suspend_q931_size)

#define Acu_suspend_total_size			(Acu_suspend_a_end_strings - (uchar  *)p_data) /* not including the ext parms */

#define	Acu_suspend_size				(Rnd_sizeof (struct acu_suspend))

/*---------------------------------------------------------------------------
*
*	ACU_RESUME_RQ/CO	Resume a call. ISDN only.
*
*--------------------------------------------------------------------------*/

struct acu_resume {
    struct acu_display_list display;	/* display list */
	char	call_id[ACU_MX_SZ_CALL_ID+1];	/* call identity (_RQ only) */
	uchar	return_code;				/* return code : OK or NOK */
	uchar	network_cause;				/* Network-provided reject cause value */
	uchar	network_cause_loc;			/* Network-provided clear cause location */
	uchar	service;					/* service to use for resume_RQ */
	uchar	data_chani;					/* B channel id used (_CO only) */
	uchar	chan_id_excl;				/* chan_id preferred (OFF) or exclusive (ON) */
	acu_size_t tsp_ie_list_size;		/* length of the list of transparent IE's */
	acu_size_t q931_size;				/* size of Q.931 message */
	pad3
		/* display strings are just here */
};

#define	Acu_resume_						((struct acu_resume  *)p_data) ->
#define	Acu_resume_ret_code				Acu_resume_ return_code
#define	Acu_resume_network_cause		Acu_resume_ network_cause
#define	Acu_resume_network_cause_loc	Acu_resume_ network_cause_loc
#define	Acu_resume_service				Acu_resume_ service
#define	Acu_resume_data_chani			Acu_resume_ data_chani
#define Acu_resume_data_chani_excl  	Acu_resume_ chan_id_excl
#define	Acu_resume_a_call_id	    	Acu_resume_ call_id
#define	Acu_resume_display_size			Acu_resume_x_display_total_size

#define Acu_resume_x_display_nb			Acu_resume_ display.nb
#define Acu_resume_x_display_total_size Acu_resume_ display.total_size
#define Acu_resume_x_p_display(i) 		Acu_resume_ display.p_display[i]
#define Acu_resume_x_display_type(i)	Acu_resume_ display.type[i]
#define Acu_resume_x_display_size(i)	Acu_resume_ display.size[i]
#define Acu_resume_a_display_list   	&(Acu_resume_ display)

#define Acu_resume_tsp_ie_list_size		Acu_resume_ tsp_ie_list_size

#define Acu_resume_q931_size			Acu_resume_ q931_size

#define	Acu_resume_a_display			((char  *)p_data + Acu_resume_size)
#define Acu_resume_a_tsp_ie_list		(Acu_resume_a_display + Acu_resume_display_size + 1)

#define Acu_resume_a_q931				(Acu_resume_a_tsp_ie_list + Acu_resume_tsp_ie_list_size)

#define Acu_resume_a_end_strings		(uchar  *)Round8((unsigned long)Acu_resume_a_q931 + Acu_resume_q931_size)

#define Acu_resume_total_size			(Acu_resume_a_end_strings - (uchar  *)p_data) /* not including the ext parms */

#define	Acu_resume_size					(Rnd_sizeof (struct acu_resume))

/*---------------------------------------------------------------------------
*
*	ACU_FACILITY_RQ/IN		Facility. ISDN only.
*
*--------------------------------------------------------------------------*/

struct acu_facility {
    
#	if ACU_PAR_EXTENDED_PRIM == ON
	struct acu_ext_descr ext_descr;	/* extended parameters descriptor */
#	endif
	struct acu_display_list display;	/* display list */
	struct voice_supp_service voice;	/* voice supplementary services management */
	char	called_address[ACU_MX_SZ_CALLED_NB + 1 + ACU_MX_SZ_CALLED_SUB_ADD + 1];	/* called address */
    
	uchar	service;					/* service if global connection ID */
	uchar 	action;						/* action code */
	uchar	code;						/* facility code */
	uchar	network_cause;				/* Network-provided facility reject cause value */
    
	acu_size_t facility_size;			/* size of the facility (ACU_FACILITY IN/CO only) */
	acu_size_t calling_nb_size;			/* size of the calling nb */
	acu_size_t calling_nb2_size;		/* size of the 2nd calling nb */
	uchar      pcs_user_protocol;		/* PCS-to-User or User-to-PCS protocol-discriminator value */
	acu_size_t pcs_user_size;			/* size of the PCS-to-User or User-to-PCS information */
		
	uchar	data_chani;					/* B channel to be used */
	acu_size_t tsp_ie_list_size;		/* length of the list of transparent IE's */
	acu_size_t q931_size;				/* size of Q.931 message */
	pad3
		
		/* facility is just here */
		/* then all the other strings in order */
};

#define	Acu_facility_					((struct acu_facility  *)p_data) ->

#if ACU_PAR_EXTENDED_PRIM == ON
#	define Acu_facility_ext_parms_nb	Acu_facility_ ext_descr.nb
#	define Acu_facility_ext_parms_lgth	Acu_facility_ ext_descr.lgth
#	define Acu_facility_a_ext_parms		((Acu_ext_descr_offset = Acu_facility_start_ext_data)? \
                          ((Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address):0)
#endif

#define	Acu_facility_service			Acu_facility_ service
#define	Acu_facility_action				Acu_facility_ action
#define	Acu_facility_code				Acu_facility_ code
#define	Acu_facility_network_cause		Acu_facility_ network_cause
#define	Acu_facility_a_called_address	(&(Acu_facility_ called_address[0]))
#define	Acu_facility_data_chani			Acu_facility_ data_chani

#define	Acu_facility_facility_size		Acu_facility_ facility_size
#define	Acu_facility_calling_nb_size	Acu_facility_ calling_nb_size
#define	Acu_facility_calling_nb2_size	Acu_facility_ calling_nb2_size
#define	Acu_facility_display_size		Acu_facility_x_display_total_size
#define Acu_facility_pcs_user_protocol	Acu_facility_ pcs_user_protocol
#define Acu_facility_pcs_user_size		Acu_facility_ pcs_user_size

#define	Acu_facility_button_type		Acu_facility_ voice.button_type
#define	Acu_facility_module_nb			Acu_facility_ voice.module_nb
#define	Acu_facility_button_nb			Acu_facility_ voice.button_nb
#define	Acu_facility_call_appear		Acu_facility_ voice.call_appear
#define	Acu_facility_switchhook			Acu_facility_ voice.switchhook
#define	Acu_facility_conn_id			Acu_facility_ voice.conn_id

#define Acu_facility_q931_size			Acu_facility_ q931_size

#define Acu_facility_tsp_ie_list_size	Acu_facility_ tsp_ie_list_size

#define Acu_facility_x_display_nb		Acu_facility_ display.nb
#define Acu_facility_x_display_total_size Acu_facility_ display.total_size
#define Acu_facility_x_p_display(i) 	Acu_facility_ display.p_display[i]
#define Acu_facility_x_display_type(i)	Acu_facility_ display.type[i]
#define Acu_facility_x_display_size(i)	Acu_facility_ display.size[i]
#define Acu_facility_a_display_list   	&(Acu_facility_ display)

#define	Acu_facility_a_facility			((char  *)p_data + Acu_facility_size)
#define	Acu_facility_a_calling_nb		(Acu_facility_a_facility + Acu_facility_facility_size + 1)
#define	Acu_facility_a_calling_nb2		(Acu_facility_a_calling_nb + Acu_facility_calling_nb_size + 1)
#define	Acu_facility_a_display			(Acu_facility_a_calling_nb2 + Acu_facility_calling_nb2_size + 1)
#define Acu_facility_a_pcs_user			(Acu_facility_a_display + Acu_facility_display_size + 1)
#define Acu_facility_a_tsp_ie_list		(Acu_facility_a_pcs_user    + Acu_facility_pcs_user_size + 1)
#define Acu_facility_a_q931				(Acu_facility_a_tsp_ie_list + Acu_facility_tsp_ie_list_size + 1)

#define Acu_facility_a_first_other		(Acu_facility_a_q931 + Acu_facility_q931_size + 1)

#define Acu_facility_a_end_strings		((char  *)p_data + Round8((unsigned long)(Acu_facility_a_first_other - (char  *)p_data)))

#define Acu_facility_total_size			(Acu_facility_a_end_strings - (char  *)p_data) /* not including the ext parms */
#define Acu_facility_start_ext_data     Acu_facility_total_size

#define	Acu_facility_size				(Rnd_sizeof (struct acu_facility))

/*---------------------------------------------------------------------------
*
*	ACU_TEST_RQ/CO	:	(with ACU_SAPI_MGT)
*
*--------------------------------------------------------------------------*/

struct acu_test {
	uchar 	action;						/* Action code */
	uchar	code;						/* test code */
	uchar	response_code;				/* response code */
	uchar	b_chan_nb;					/* loop-back B channel nb */
	pad4
};

#define	Acu_test_						((struct acu_test  *)p_data) ->
#define	Acu_test_action					Acu_test_ action
#define	Acu_test_code					Acu_test_ code
#define	Acu_test_response_code			Acu_test_ response_code
#define	Acu_test_b_chan_loop_back_nb	Acu_test_ b_chan_nb

#define	Acu_test_size					(Rnd_sizeof (struct acu_test))

/*---------------------------------------------------------------------------
*
*	ACU_INFORMATION_RQ/IN	Facility. ISDN only.
* Arguments :
*
* 	Acu_information_charging		 		: charging
* 	Acu_information_end_of_three_party		: end-of-three-party
* 	Acu_information_display_size			: display size
* 	Acu_information_keypad_size				: keypad size
*	Acu_information_signal_val				: signal value
*
* 		Acu_information_credit_card_status	: credit card status
* 		Acu_information_nats_avail			: nats_avail
* 		Acu_information_satcom_avail		: satcom_avail
* 		Acu_information_tfts_avail			: tfts_avail
* 		Acu_information_nats_pos			: nats_position
* 		Acu_information_satcom_pos			: satcom_position
* 		Acu_information_tfts_pos			: tfts_position
*		Acu_information_track_1_size		: size of the track #1
*		Acu_information_track_2_size        : size of the track #2
*
*	US-BRI Network side specific :
* 		Acu_information_ces					; Connection Endpoint Suffix on which the SPID was received. (_IN)
* 		Acu_information_tid					: Terminal Endpoint Id (_RQ)
* 		Acu_information_usid				: User Id (_RQ)
* 		Acu_information_interpreter			: Interpreter (_RQ)
*--------------------------------------------------------------------------*/

struct acu_information {
    struct acu_charging_info charging_info;	/* charging information */
	struct acu_display_list display;		/* display list */

	uchar	end_of_three_party;				/* end of three party : ON or OFF */
	acu_size_t keypad_size;					/* keypad size */
    
	uchar	signal_val;						/* signal value */
	uchar	call_appear;				/* Call appearence */
	acu_size_t tsp_ie_list_size;		/* length of the list of transparent IE's */
	acu_size_t q931_size;				/* size of Q.931 message */
	pad2
		/* display strings are just here */
		/* then the keypad */
		/* then the track 1 info */
		/* then the track 2 info */
		/* then the SPID info */

    
#	if _CC_SPID_INFO == ON
	struct 	acu_endpoint_id endpoint_id;/* Endpoint Id information */
	add_t 	ces;						/* Connection Endpoint Suffix */
	uchar	spid_size;					/* SPID size */
	pad6
#	endif
		
		
};

#define	Acu_information_					((struct acu_information  *)p_data) ->
#define	Acu_information_end_of_three_party	Acu_information_ end_of_three_party

#define	Acu_information_charging_available	Acu_information_ charging_info.available
#define Acu_information_charging_value     	Acu_information_ charging_info.value
#define Acu_information_charging_type     	Acu_information_ charging_info.type
#define Acu_information_charging_period    	Acu_information_ charging_info.period
#define Acu_information_charging_multi     	Acu_information_ charging_info.multi
#define Acu_information_charging	     	Acu_information_charging_value	/* alias */

#define	Acu_information_display_size		Acu_information_x_display_total_size
#define	Acu_information_keypad_size			Acu_information_ keypad_size

#define Acu_information_x_display_nb		Acu_information_ display.nb
#define Acu_information_x_display_total_size Acu_information_ display.total_size
#define Acu_information_x_p_display(i) 		Acu_information_ display.p_display[i]
#define Acu_information_x_display_type(i)	Acu_information_ display.type[i]
#define Acu_information_x_display_size(i)	Acu_information_ display.size[i]
#define Acu_information_a_display_list   	&(Acu_information_ display)
#define	Acu_information_a_display			((char  *)p_data + Acu_information_size)
#define	Acu_information_a_keypad			(Acu_information_a_display + Acu_information_display_size + 1)

#define	Acu_information_signal_val			Acu_information_ signal_val

#	if _CC_SPID_INFO == ON
#		define	Acu_information_spid_size	Acu_information_ spid_size
#		define	Acu_information_a_spid		(Acu_information_a_keypad + Acu_information_keypad_size + 1)
#	endif

#if _CC_SPID_INFO == ON
#	define	Acu_information_p_endpoint_id	Acu_information_ endpoint_id
#	define	Acu_information_ces				Acu_information_ ces
#	define	Acu_information_tid				Acu_information_ endpoint_id.tid
#	define	Acu_information_usid	   		Acu_information_ endpoint_id.usid
#	define	Acu_information_interpreter		Acu_information_ endpoint_id.interpreter
#	define	Acu_information_endpoint_action	Acu_information_ endpoint_id.action
#endif

#define	Acu_information_call_appear		    Acu_information_ call_appear
#define Acu_information_tsp_ie_list_size	Acu_information_ tsp_ie_list_size
#define Acu_information_q931_size			Acu_information_ q931_size
#define Acu_information_a_tsp_ie_list		(Acu_information_a_keypad + Acu_information_keypad_size + 1)
#define Acu_information_a_q931				(Acu_information_a_tsp_ie_list + Acu_information_tsp_ie_list_size + 1)


#define Acu_information_a_first_other		(Acu_information_a_q931 + Acu_information_q931_size + 1)

#define Acu_information_a_end_strings		(uchar  *)Round8((unsigned long)Acu_information_a_first_other)
#define Acu_information_total_size			(Acu_information_a_end_strings - (uchar  *)p_data) 

#define	Acu_information_size				(Rnd_sizeof (struct acu_information))

/*---------------------------------------------------------------------------
	ACU_SERVICE_RQ/IN/CO
	use this structure to send a SERVICE message
	(only defined for AT&T and DMS variants)
*--------------------------------------------------------------------------*/

struct acu_service {
	uchar	   preference;				/* service preference */
	uchar	   int_id;					/* Interface Id if preference is I_PREF_D_CHAN or I_PREF_B_CHAN */
	uchar	   b_chan;					/* What B channel if preference is I_PREF_B_CHAN */
	uchar	   status;					/* new status (any case) */
	uchar	   maint_audit;				/* Maintenance or Audit type of action */
	acu_size_t q931_size;				/* size of Q.931 message */
	pad2
};

#define	Acu_service_					((struct acu_service  *)p_data) ->
#define Acu_service_pref				Acu_service_ preference
#define Acu_service_int_id				Acu_service_ int_id
#define Acu_service_b_chan				Acu_service_ b_chan
#define Acu_service_status				Acu_service_ status
#define Acu_service_action_type			Acu_service_ maint_audit
#define Acu_service_q931_size			Acu_service_ q931_size

#define Acu_service_size				(sizeof (struct acu_service))

#define Acu_service_a_q931				((char *)p_data + Acu_service_size)
#define Acu_service_a_end_strings       (uchar *)Round8((unsigned long)Acu_service_a_q931 + Acu_service_q931_size + 1)

#define Acu_service_total_size			(Acu_service_a_end_strings - (uchar *)p_data)

/*---------------------------------------------------------------------------
 *	ACU_RESTART_IN
 *	(only defined for AT&T and DMS variants)
 *--------------------------------------------------------------------------*/

struct acu_restart {
	uchar	   preference;				/* restart preference */
	uchar	   int_id;					/* Interface Id if preference is I_PREF_D_CHAN or I_PREF_B_CHAN */
	uchar	   b_chan;					/* What B channel if preference is I_PREF_B_CHAN */
	acu_size_t q931_size;				/* size of Q.931 message */
	pad4
};

#define	Acu_restart_					((struct acu_restart  *)p_data) ->
#define Acu_restart_pref				Acu_restart_ preference
#define Acu_restart_int_id				Acu_restart_ int_id
#define Acu_restart_b_chan				Acu_restart_ b_chan
#define Acu_restart_q931_size			Acu_restart_ q931_size

#define Acu_restart_size				(sizeof (struct acu_restart))

#define Acu_restart_a_q931              ((unsigned char  *)p_data + Acu_restart_size)
#define Acu_restart_a_end_strings       (uchar  *)Round8((unsigned long)Acu_restart_a_q931 + Acu_restart_q931_size + 1)

#define Acu_restart_total_size				(Acu_restart_a_end_strings - (uchar *)p_data)


/*---------------------------------------------------------------------------
*
*	ACU_D_CHANNEL_STATUS_RQ/IN	:	(with ACU_SAPI_MGT)
*
*--------------------------------------------------------------------------*/

struct acu_d_channel_status {
	uchar 	state;						/* state (ON/OFF) */
	pad7
};

#define ACU_D_CHANNEL_STATUS_RELEASED      0    /* data link released     */
#define ACU_D_CHANNEL_STATUS_ESTABLISHED   1    /* data link established  */
#define ACU_D_CHANNEL_STATUS_AWAITING      7    /* awaiting establishment */

#define	Acu_d_channel_status_				((struct acu_d_channel_status  *)p_data) ->
#define	Acu_d_channel_state					Acu_d_channel_status_ state

#define	Acu_d_channel_status_size			(Rnd_sizeof (struct acu_d_channel_status))


/*---------------------------------------------------------------------------
*
*	ACU_ERR_IN	Error indication. ISDN only.
*
*	Arguments:
*
*		Acu_err_in_cause:      error cause;
*		Acu_err_in_diagnostic: error diagnostic;
*
*		See "DATA TYPES" section for symbolic values used in these fields.
*
*--------------------------------------------------------------------------*/

struct acu_err_in {
	uchar	cause;					/* error cause */
	uchar	diagnostic;				/* diagnostic */
	pad6
};

#define	Acu_err_in_					((struct acu_err_in  *)p_data) ->
#define	Acu_err_in_cause			Acu_err_in_ cause
#define	Acu_err_in_diagnostic		Acu_err_in_ diagnostic

#define	Acu_err_in_size				(Rnd_sizeof (struct acu_err_in))


/*---------------------------------------------------------------------------
SM_CHANNEL_MAINT_RQ 
use this structure to send (from NS to MNS) a SERVICE message
(only defined for AT&T and DMS variants)
*--------------------------------------------------------------------------*/

struct acu_mns_service {
	uchar	preference;								/* service preference */
	uchar	int_id;									/* Interface Id if preference is I_PREF_D_CHAN or I_PREF_B_CHAN */
	uchar	b_chan;									/* What B channel if preference is I_PREF_B_CHAN */
	uchar	status;									/* new status (any case) */
	uchar	error_type;								/* type of error */
	uchar	maint_audit;							/* Maintenance or Audit type of action */
	pad2
};

#define	Acu_mns_service_					((struct acu_mns_service  *)p_data) ->
#define Acu_mns_service_pref				Acu_mns_service_ preference
#define Acu_mns_service_int_id				Acu_mns_service_ int_id
#define Acu_mns_service_b_chan				Acu_mns_service_ b_chan
#define Acu_mns_service_status				Acu_mns_service_ status
#define Acu_mns_service_error				Acu_mns_service_ error_type
#define Acu_mns_service_action_type			Acu_mns_service_ maint_audit

#define Acu_mns_service_size				(sizeof (struct acu_mns_service))


/*--------------------------------------------------------------------------
*		MISCELLANEOUS DATA TYPES AND CONSTANTS EXCHANGED IN PRIMITIVES
*-------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------
*	ACU parameters names (ACU_SETPARM_RQ, ACU_INFO_RQ)
*	Not used in ISDN interface
*-------------------------------------------------------------------------*/

#	define	ACU_NRINGS						'a'	/* number of rings before answering (ATS0) */
#	define	ACU_TPULSE						'b'	/* tone or pulse dialing (ATD, ATP) */
#	define	ACU_WB4_BLINDDIAL				'c'	/* delay to wait before blind dialing (AT S6) */
#	define	ACU_CONN_DEL					'd'	/* max delay between the completion of dialing */
/* and the establishment of the connection (AT S7) */
#	define	ACU_PAUSE_DEL					'e'	/* pause duration (AT S8) */
#	define	ACU_SIGDIGIT_DUR				'f'	/* DTMF duration (AT S11) */
#	define	ACU_NRINGS_DET					'g'	/* Number of rings detected (AT S1) */
#	define	ACU_PULSE_PARM					'h'	/* ACU pulse parameters */
#	define	ACU_DIAL_NO_PROCEED				'i'	/* dial without waiting for proceed tone (AT X0) */
# 	define	ACU_DIAL_PROCEED				'j'	/* dial, waiting for proceed tone (AT X4, etc.) */

/*--------------------------------------------------------------------------
*	Primitive priority (ACU_CONN_RQ/RS, ACU_CLEAR_RQ/RS, ACU_INIT_RQ)
*	Not used in ISDN interface
*-------------------------------------------------------------------------*/

#	define	ACU_PHIGH						'H'	/* urgent */
#   define	ACU_PLOW						'L'	/* normal */

/*--------------------------------------------------------------------------
*	Incoming or outgoing (tele)service (ACU_CONN_IN/RQ/RS)
*-------------------------------------------------------------------------*/

#	define	ACU_FAX_SERVICE					'F'	/* call for G3 facsimile service */
#	define	ACU_FAX_4_SERVICE				'4'	/* call for G4 facsimile service */
#	define	ACU_DATA_SERVICE				'D'	/* call for 'data' service */
#	define	ACU_DATA_GCI_SERVICE			ACU_DATA_SERVICE	/* call for 'data' service on GCI bus */
#	define	ACU_DATA_56KBS_SERVICE			'K'	/* call for 'data at 56 KBS' service */
#	define	ACU_RAW_DATA_SERVICE			'!' /* call for 'raw data' service on GCI bus: no MPH_B_INIT_RQ is generated (i.e. no B-channel driver is associated) */
#	define	ACU_DATA_TRANS_SERVICE			'T'	/* call for transparent data service */
#	define	ACU_MODEM_SERVICE				'M'	/* call for modem data service */
#	define	ACU_AUDIO_7_SERVICE				'7'	/* call for 7kHz Audio service */
#	define	ACU_X25_SERVICE					'X'	/* call for X.25 circuit-mode service */
#	define	ACU_X25_PACKET_SERVICE			'P'	/* call for X.25 packet-mode service */
#	define	ACU_VOICE_SERVICE				'V'	/* call for voice service */
#	define	ACU_VOICE_GCI_SERVICE			'G'	/* call for voice service on GCI bus */
#	define	ACU_RAW_TELEPHONY_SERVICE		':' /* call for 'raw telephony' service on GCI bus: no MPH_B_INIT_RQ is generated (i.e. no B-channel driver is associated) */
#	define	ACU_VOICE_TRANS_SERVICE			'W'	/* call for transparent voice service */
#	define	ACU_V110_SERVICE				'1' /* call for V.110 service */
#	define	ACU_V120_SERVICE				'2' /* call for V.120 service */
#	define	ACU_VIDEO_SERVICE				'O' /* call for VIDEO service */
#	define	ACU_TDD_SERVICE					'Q' /* call for TDD service */
#	define	ACU_DATA_H0_SERVICE				'0' /* call for Data using H0  (384kbs)  channel service (PRI only) */
#	define	ACU_DATA_H11_SERVICE			'H' /* call for Data using H11 (1536kbs) channel service (PRI only) */
#	define	ACU_DATA_H12_SERVICE			'I' /* call for Data using H12 (1536kbs) channel service (PRI only) */
#	define	ACU_DATA_MULTIRATE_SERVICE		'R' /* call for Data using Multirate (2..30*64kbs) channel service (PRI only) */
#	define	ACU_DATA_128KBS_SERVICE			'S' /* call for Data using 2*64kbs channel service (BRI only) */
#	define	ACU_NO_B_CHAN_SERVICE			'N' /* call for no B-channel service (bearer-independent calls - QSIG only) */

/* Services for use with 'Physical Relay' process */

#	define	ACU_FAX_RELAY_SERVICE			'f'	/* call for G3 facsimile service */
#	define	ACU_DATA_RELAY_SERVICE			'd'	/* call for 'data' service */
#	define	ACU_DATA_56KBS_RELAY_SERVICE	'k'	/* call for 'data at 56 KBS' service */
#	define	ACU_DATA_TRANS_RELAY_SERVICE	't'	/* call for 'data transparent' service */
#	define	ACU_MODEM_RELAY_SERVICE			'm'	/* call for modem data service */
#	define	ACU_X25_RELAY_SERVICE			'x'	/* call for X.25 circuit-mode service */
#	define	ACU_VOICE_RELAY_SERVICE			'v'	/* call for voice service */
#	define	ACU_VOICE_GCI_RELAY_SERVICE		'g' /* call for voice service on GCI bus */

#	define	ACU_NO_SERVICE					'U'	/* undefined service */



/*--------------------------------------------------------------------------
*	Calling number presentation (ACU_CONN_RQ/IN, 'calling_nb_pres' field)
*-------------------------------------------------------------------------*/
/* in outgoing messages 0xff in this field will be translated to 0 in the 
actual IE, if no value is set for this field, the stack will insert a 
default value based on the variant.
If the stack receives a 0 in this field in an incoming IE, it sends a
0xff to the application                                                 */
#	define	ACU_NB_PRES_ALLOWED				0xff	/* presentation allowed					*/
#	define	ACU_NB_PRES_RESTRICTED			0x01	/* presentation restricted */
#	define	ACU_NB_PRES_NOT_AVAILABLE		0x02	/* number not available due to interworking */

/*--------------------------------------------------------------------------
*	Calling(ed) number type (ACU_CONN_RQ/IN, 'calling(ed)_nb_type' field)
*-------------------------------------------------------------------------*/
/* in outgoing messages 0xff in this field will be translated to 0 in the 
actual IE, if no value is set for this field, the stack will insert a 
default value based on the variant.
If the stack receives a 0 in this field in an incoming IE, it sends a
0xff to the application                                                 */
#	define	ACU_NB_TYPE_UNKNOWN				0xff	/* unknown				*/
#	define	ACU_NB_TYPE_INTERNATIONAL		0x01	/* international number */
#	define	ACU_NB_TYPE_NATIONAL			0x02	/* national number */
#	define	ACU_NB_TYPE_NET_SPF				0x03	/* network specific number */
#	define	ACU_NB_TYPE_SUBSCRIBER			0x04	/* subscriber number */
#	define	ACU_NB_TYPE_LOCAL				0x04	/* AT5 - local (directory) number */
#	define	ACU_NB_TYPE_ABBREVIATED			0x06	/* abbreviated number */

/*--------------------------------------------------------------------------
*	Called Number plan (ACU_CONN_RQ/IN, 'called_nb_plan' field)
*-------------------------------------------------------------------------*/
/* in outgoing messages 0xff in this field will be translated to 0 in the 
actual IE, if no value is set for this field, the stack will insert a 
default value based on the variant.
If the stack receives a 0 in this field in an incoming IE, it sends a
0xff to the application                                                 */
#	define ACU_NB_PLAN_UNKNOWN				0xff /* unknown	*/
#	define ACU_NB_PLAN_ISDN					0x01 /* ISDN/telephony numbering plan (CCITT E.164/E.163) */
#	define ACU_NB_PLAN_TELEPHONE			0x02 /* telephony - not in CEPT */
#	define ACU_NB_PLAN_DATA					0x03 /* data numbering plan (CCITT X.121) */
#	define ACU_NB_PLAN_TELEX				0x04 /* telex numbering plan (CCITT F.69) */
#	define ACU_NB_PLAN_NATIONAL				0x08 /* national standard numbering plan */
#	define ACU_NB_PLAN_PRIVATE				0x09 /* private numbering plan */
#	define ACU_NB_PLAN_RESERVED				0x0f /* reserved for extension */

/*--------------------------------------------------------------------------
*	Calling number screening indicator (ACU_CONN_RQ/IN, 'calling_nb_screen'
*  and 'calling_nb2_screen' fields)
*-------------------------------------------------------------------------*/
/* in outgoing messages 0xff in this field will be translated to 0 in the 
actual IE, if no value is set for this field, the stack will insert a 
default value based on the variant.
If the stack receives a 0 in this field in an incoming IE, it sends a
0xff to the application                                                 */
#	define ACU_NB_SCREEN_USER_PROVIDED		0xff	/* user-provided, not screened */
#	define ACU_NB_SCREEN_USER_PASSED		0x01	/* user-provided, verified and passed */
#	define ACU_NB_SCREEN_USER_FAILED		0x02	/* user-provided, verified and failed */
#	define ACU_NB_SCREEN_NETWORK_PROVIDED 	0x03	/* network provided */

/*--------------------------------------------------------------------------
*	Redirected number reason (ACU_CONN_IN/CO, ACU_ALERT_IN, 'redir_nb_reason' field)
*-------------------------------------------------------------------------*/
/* in outgoing messages 0xff in this field will be translated to 0 in the 
actual IE, if no value is set for this field, the stack will insert a 
default value based on the variant.
If the stack receives a 0 in this field in an incoming IE, it sends a
0xff to the application                                                 */
#	define ACU_NB_REASON_UNKNOWN							0xff	/* unknown */
#	define ACU_NB_REASON_CALL_FORWARDING_BUSY				0x01	/* call forwarding busy (VN6) */
#	define ACU_NB_REASON_CALL_FORWARDING_NO_REPLY			0x02	/* call forwarding no reply (VN6) */
#	define ACU_NB_REASON_CALL_FORWARDING_DTE_OUT			0x09	/* call forwarding DTE out of order */
#	define ACU_NB_REASON_CALL_FORWARDING_BY_CALLED			0x0a	/* call forwarding by the called equipment (VN6) */
#	define ACU_NB_REASON_CALL_TRANSFER						0x0d	/* call transfer */
#	define ACU_NB_REASON_CALL_PICKUP						0x0e	/* call pickup */
#	define ACU_NB_REASON_CALL_FORWARDING_UNCONDITIONAL		0x0f	/* call forwarding unconditional (VN6) */

/*--------------------------------------------------------------------------
*	subaddress type (ACU_CONN_RQ, 'called(ing)_nb_sub_type' field)
*-------------------------------------------------------------------------*/
#define ACU_SUBADDRESS_TYPE_NSAP		0x00	    /* NSAP */
#define ACU_SUBADDRESS_TYPE_USER		0x02	    /* User specified */

/*--------------------------------------------------------------------------
*	subaddress odd/even indicator (ACU_CONN_RQ, 'called(ing)_nb_sub_odd_even' field)
*-------------------------------------------------------------------------*/
#define ACU_SUBADDRESS_ODD		0x01	       /* odd number of address signals */
#define ACU_SUBADDRESS_EVEN		0x00	       /* even number of address signals */



/*------------------------------------------------------------------------
*  Information Tags (AT&T specific)
*-----------------------------------------------------------------------*/
#define INFO_TAG_CONTINUATION    0x82 /* Continuation                        */
#define INFO_TAG_CALLED_ADD      0x83 /* Called Address                      */
#define INFO_TAG_ACCUM_DGT       0x88 /* Accumulated Digits                  */
#define INFO_TAG_CALLING_ADD     0x8B /* Calling Address                     */
#define INFO_TAG_REASON          0x8C /* Reason                              */
#define INFO_TAG_CALLING_NAME    0x8D /* Calling Party Name                  */
#define INFO_TAG_ORIG_NAME       0x8F /* Original Called Name                */
#define INFO_TAG_REDIR_NAME      0x90 /* Redirecting Party Name              */
#define INFO_TAG_ORIG_RESTR      0x92 /* Originating Restrictions            */
#define INFO_TAG_DATE            0x93 /* Date                                */
#define INFO_TAG_TARGET_NAME     0x96 /* Target Party Name                   */
#define INFO_TAG_TARGET_NUMBER   0x97 /* Target Party Number                 */
#define INFO_TAG_REDIR_NUMBER    0x98 /* Redirecting Number                  */
#define INFO_TAG_ORIG_NUMBER     0x99 /* Original Called Number              */
#define INFO_TAG_TEXT            0x9E /* Text                                */
#define INFO_TAG_ADDRESS         0xA0 /* Address                             */
#define INFO_TAG_STREET          0xA1 /* Street                              */
#define INFO_TAG_CITY            0xA2 /* City                                */
#define INFO_TAG_STATE           0xA3 /* State                               */
#define INFO_TAG_COUNTRY         0xA4 /* Country                             */
#define INFO_TAG_ZIP_CODE        0xA5 /* ZIP Code                            */
#define INFO_TAG_TIME            0xA6 /* Time                                */
#define INFO_TAG_HOPS            0xA7 /* Number of Hops                      */
#define INFO_TAG_ACCNT_NUMBER    0xA8 /* Account Number                      */
#define INFO_TAG_SSN             0xA9 /* Social Security Number              */
#define INFO_TAG_CONFIRM_NUMBER  0xAA /* Confirmation Number                 */
#define INFO_TAG_REG_NUMBER      0xAB /* Product Registration Number         */

/*--------------------------------------------------------------------------
*	Network-provided clearing causes (ACU_CLEAR_IN/CO, ACU_SUSPEND_RQ/CO,
*	ACU_RESUME_RQ/CO, ACU_FACILITY_RQ/CO, 'network_cause' field)
*	The first nibble is the 'cause-class',
*	the second nibble is the value in the class.
*-------------------------------------------------------------------------*/

/* ACU-specific class (=0xF) values */

#	define	ACU_CAUSE_ACU_BAD_ADDRESS	0xF0	/* value 0: bad context addressing info, or no free context available */
#	define	ACU_CAUSE_ACU_BAD_SERVICE	0xF1	/* value 1: bad ACU service value */
#	define	ACU_CAUSE_ACU_COLLISION		0xF2	/* value 2: incoming call collision */
#	define	ACU_CAUSE_ACU_FAC_REJECTED	0xF3	/* value 3: Facility request rejected by ACU */
#	define	ACU_NETWORK_CAUSE_NIL		0xFF	/* value F: unspecified */

/*--------------------------------------------------------------------------
*	Alert codes (ACU_ALERT_IN)
*-------------------------------------------------------------------------*/

#	define	ACUAC_RING						'R'	/* ring detected */
#	define	ACUAC_REMOTE_ALERTED			'A'	/* Remote equipment alerted */

/*--------------------------------------------------------------------------
*	Progress events (ACU_PROGRESS_IN)
*-------------------------------------------------------------------------*/

#	define	ACUEV_DIAL_TONE					'T'	/* Received B-channel id on outgoing calls (Dial tone available in channel, received Setup-Ack or Call-Proceeding message) */
#	define	ACUEV_INTERWORKING				'I'	/* Received Progress message (interworking) */

/*--------------------------------------------------------------------------
*	Clear codes (ACU_CLEAR_RQ/IN/RS/CO)
*-------------------------------------------------------------------------*/

#	define	ACURC_BUSY						'b'	/* busy */
#	define	ACURC_NOPROCEED					'p'	/* no proceed indication (dial tone) */
#	define	ACURC_NOANSWER					'a'	/* no answer */
#	define	ACURC_NOAUTOANSWER				't'	/* no auto-answer tone detected */
#	define	ACURC_CONGESTED					'c'	/* GSTN or System is congested */
#	define	ACURC_INCOMING					'i'	/* incoming call detected while try to dial */
#	define	ACURC_NOLINE					'l'	/* (analog) line is seized by another equipment */
/* (ISDN) Wrong Addressing info, or context already used */
#	define	ACURC_ERRNUM					'e'	/* errored number */
#	define	ACURC_INHNUM					'n'	/* inhibited number */
#	define	ACURC_2MNUM						'2'	/* too many errored/inhibited numbers */
#	define	ACURC_HUNGUP					'h'	/* remote has hung up or incident on connection */
#	define	ACURC_NETWORK_ERROR				'N'	/* (ISDN) network disconnected us */
#	define	ACURC_TIMEOUT					'T'	/* time-out error */
#	define	ACURC_BAD_SERVICE				'S'	/* Bad Service-id in ACU_CONN_RQ/RS */
#	define	ACURC_INTERNAL					'I'	/* other internal error */

/*
*	The following codes are never sent in an ACU_CLEAR_xx message
*/

#	define	ACURC_OK						0	/* No error */
#	define	ACURC_BL_TIMEOUT				1	/* BL time-out error */
#	define	ACURC_IN_CALL					2	/* BL error, still in call */
#	define	ACURC_CLEAR_RQ					3	/* User entity requested CLEAR */


/*--------------------------------------------------------------------------
* 	Exchange time codes (not used)
*-------------------------------------------------------------------------*/

#	define	UUI_ALERT						'a'	/* to transmit at ALERT time */
#	define	UUI_CLEAR						'b'	/* to transmit at CLEAR time */
#	define	UUI_USER_INFORMATION    		'c'	/* immediatly in a user information message */

/*--------------------------------------------------------------------------
*	Response mode codes (ACU_RS_MODE_RQ/CO)
*-------------------------------------------------------------------------*/

#	define RS_MODE_ALERT					'a'	/* ALERT   requested on incoming call */
#	define RS_MODE_CONNECT					'b'	/* CONNECT requested on incoming call */
#	define RS_MODE_CLEAR					'c'	/* CLEAR   requested on incoming call */

/*--------------------------------------------------------------------------
*	Facility codes (ACU_FACILITY_RQ/IN/CO)
*-------------------------------------------------------------------------*/

#	define ACU_FAC_CALL_FORWARDING			21	/* premise transfer */
#	define ACU_FAC_CALL_DEFLECTION			22	/* terminal transfer */
#	define ACU_FAC_CHARGING					23	/* charging */
#	define ACU_FAC_CHARGING_TOTAL			24	/* charging total cost */
#	define ACU_FAC_HOLD						25	/* call hold */
#	define ACU_FAC_RETRIEVE					26	/* call retrieve */
#	define ACU_FAC_ALTERNATE				27	/* to and from facility */
#	define ACU_FAC_TRF						28	/* transfer */
#	define ACU_FAC_THREE_PARTY				29	/* conferencing */
#	define ACU_FAC_MALICIOUS_CALL_ID		32	/* malicious call identification */

#	define ACU_FAC_RECALL					50	/* Recall facility (ETSI) */

#	define ACU_FAC_TRANSPARENT				100	/* transparent facility for CC&NS */

#	define ACU_FAC_CALL_APPEAR				200	/* Call appearence request */
#	define ACU_FAC_FEATURE_ACT				201	/* Feature activation request */
#	define ACU_FAC_DROP						202	/* Drop call */
#	define ACU_FAC_FEATURE_IND				203	/* Feature indication (NT->TE only) */

#	define ACU_FAC_PCS_USER_ONLY			250	/* send PCS-User information only, \
* with no other facility request. \
* Only for VN6,                   \
* within ACU_FACILITY_RQ.         \
*/
#   define ACU_FAC_UNKNOWN  				253 /* Message contains Q931 buffer with unknown Fac.IE inside */

#   define ACU_FAC_EXT_SERVICE				254 /* Used when extended supplementary
* service structures are included in
* message */

/*--------------------------------------------------------------------------
*	Action codes (ACU_FACILITY_RQ/IN/CO, ACU_TEST_RQ/CO, ACU_SET_MODE_RQ/CO)
*-------------------------------------------------------------------------*/

#	define ACU_RQ_ACTIVATE					'A'	/* activate or register action */
#	define ACU_RQ_CLEAR						'C'	/* deactivate or clear action */
#	define ACU_RQ_ENQUIRY					'E'	/* enquiry action */

#	define ACU_IN_TX						't'	/* transmission */
#	define ACU_IN_CLEAR						'c'	/* clear */

#	define ACU_RS_ACK						'a'	/* acknowledgement */
#	define ACU_RS_REJ						'r'	/* reject */

#	define ACU_CO_ACK						'a'	/* acknowledgement */
#	define ACU_CO_REJ						'r'	/* reject */

/*--------------------------------------------------------------------------
*	Test codes (ACU_TEST_RQ/CO)
*-------------------------------------------------------------------------*/

#	define ACU_TEST_B_CHAN_LOOP_BACK		'L'	/* loop back B channel */

/*--------------------------------------------------------------------------
*	ACU_SET_MODE_RQ/CO (codes)
*-------------------------------------------------------------------------*/

#	define ACU_MODE_NA_OUT_OF_ORDER			'a' /* allow/forbid calls on NAI given by R_msg_nai. */
#	define ACU_MODE_CALL_OUT_OF_ORDER		'b' /* allow/forbid calls on NAI/CONN_ID given by R_msg_nai/R_msg_conn_id. */
#	define ACU_MODE_CHANI_OUT_OF_ORDER		'c' /* allow/forbid usage of the B-channel given by Acu_set_mode_data_chani. */
#	define ACU_MODE_ALL_NA_OUT_OF_ORDER		'd' /* allow/forbid calls on all NAIs. */

/*--------------------------------------------------------------------------
*	ACU_ERR_IN cause codes
*-------------------------------------------------------------------------*/

#	define ACUER_PRIMITIVE_CODE				'a'	/* unknown primitive code */
#	define ACUER_PARAM_VAL					'b'	/* invalid parameter */
#	define ACUER_MANDATORY_PARAM_MISSING	'c'	/* mandatory parameter missing */
#	define ACUER_PARAM_TYPE					'd'	/* incorrect parameter type */
#	define ACUER_PARAM_LGTH					'e'	/* incorrect parameter length */
#	define ACUER_UNEXPECTED_PRIMITIVE		'f'	/* unexpected primitive */
#	define ACUER_PRIMITIVE_NOT_IMPLEMENTED 	'j'	/* SSDU primitive not implemented */
#	define ACUER_NO_TIMER_AVAILABLE			'q'	/* no more space to allocate new timer cells */
#	define ACUER_CONGESTION					'm'	/* resource congestion */

/*--------------------------------------------------------------------------
*	ACU_ERR_IN cause diagnostics
*-------------------------------------------------------------------------*/

/*
For ACUER_PRIMITIVE_CODE
and ACUER_PRIMITIVE_NOT_IMPLEMENTED
errors:

  the diagnostic is the ACU primitive code that has generated the error.
*/

/*
For ACUER_PARAM_VAL,
ACUER_MANDATORY_PARAM_MISSING,
ACUER_PARAM_TYPE,
and ACUER_PARAM_LGTH,
errors:
*/

#	define ACUERDIAG_CHAN_ID				0x18	/* Chan_id Information */
#	define ACUERDIAG_DISPLAY				0x28	/* Display Information */
#	define ACUERDIAG_KEYPAD					0x2c	/* Keypad Information */
#	define ACUERDIAG_CALLING_NB				0x6c	/* Calling number Information */
#	define ACUERDIAG_CALLING_SUB_ADD		0x6d	/* Calling sub-address Information */
#	define ACUERDIAG_CALLED_NB				0x70	/* Called number Information */
#	define ACUERDIAG_CALLED_SUB_ADD			0x71	/* Called sub-address Information */
#	define ACUERDIAG_UUI					0x7e	/* UUI Information */

/*
For ACUER_NO_TIMER_AVAILABLE and ACUER_CONGESTION errors:
No diagnostic.
*/

/*--------------------------------------------------------------------------
*	Button management (voice supplementary services)
*-------------------------------------------------------------------------*/

/* Button type */

#define ACU_BUTTON_TYPE_UNKNOWN					0
#define ACU_CALL_APPEAR_BUTTON					1
#define ACU_FEATURE_BUTTON						2
#define ACU_NON_APPLICABLE						3

/* Module number */

#define ACU_MODULE_0							0
#define ACU_MODULE_1							1
#define ACU_MODULE_2							2
#define ACU_MODULE_3							3
#define ACU_MODULE_4							4
#define ACU_MODULE_5							5
#define ACU_MODULE_6							6
#define ACU_MODULE_7							7

/* Switchhook */

#define ACU_HOOK_ON								0		/* on-hook */
#define ACU_HOOK_OFF							1		/* off-hook */

/*--------------------------------------------------------------------------
*	Notify description (ACU_CONN_RQ/IN)
*-------------------------------------------------------------------------*/

#define	ACUNO_DESCRIPTION						0xFF	/* Empty field */
#define	ACUUSER_RESUMED							0x01	/* User resumed */

/*--------------------------------------------------------------------------
*	SPF facility Id (ACU_CONN_RQ/IN)
*-------------------------------------------------------------------------*/

#define ACUSPF_FAC_ABSENT						0xff	/* No SPF FAC */
#define ACUSPF_FAC_GES_PRIV_NET_SELECT			0x00	/* GES private network selection */
#define ACUSPF_FAC_GES_SPECIAL_SERVICE			0x01	/* GES special services */
#define ACUSPF_FAC_GES_SELECTION				0x03	/* GES selection */


/*--------------------------------------------------------------------------
*	Progress description (ACU_CONN_RQ/IN, ACU_ALERT_IN, ACU_PROGRESS_IN)
*-------------------------------------------------------------------------*/
#define	ACUNO_PROGRESS_DESCR					0x00	/* no progress info to be stored */

#define	ACUPROGRESS_DESCR_NON_END_TO_END_ISDN	0x01	/* call is not end-to-end ISDN, further call progress information may be available */
#define	ACUPROGRESS_DESCR_CALL_RETURNED_ISDN	0x04	/* call has returned to the ISDN */
#define	ACUPROGRESS_DESCR_IN_BAND_NOW			0x08	/* in-band information or appropriate pattern now available */

/*--------------------------------------------------------------------------
*	location (ACU_CONN_RQ/IN, ACU_CLEAR_RQ/IN, ACU_ALERT_IN, ACU_PROGRESS_IN)
*-------------------------------------------------------------------------*/
/* in outgoing messages 0xff in this field will be translated to 0 in the 
actual IE, if no value is set for this field, the stack will insert a 
default value based on the variant.
If the stack receives a 0 in this field in an incoming IE, it sends a
0xff to the application                                                 */
#define	ACU_LOC_USER					0xff		/* user */
#define ACU_LOC_PR_LOCAL_USER			0x01		/* private network serving the local user */
#define ACU_LOC_NETWORK					0x02		/* location network (SWD) */
#define ACU_LOC_TRANSIT_NET				0x03		/* transit network */
#define	ACU_LOC_PU_REMOTE_USER			0x04		/* public network serving the remote user */
#define	ACU_LOC_PR_REMOTE_USER			0x05		/* private network serving the remote user */
#define	ACU_LOC_BEYOND_IWP				0x0a		/* network beyond interworking point */

/*--------------------------------------------------------------------------
*	UUI protocol discriminator:
*-------------------------------------------------------------------------*/
/* in outgoing messages 0xff in this field will be translated to 0 in the 
actual IE, if no value is set for this field, the stack will insert a 
default value based on the variant.
If the stack receives a 0 in this field in an incoming IE, it sends a
0xff to the application                                                 */
#define ACU_UUI_USER_SPF						0xff		/* User specific coding */
#define ACU_UUI_OSI								0x01		/* OSI */
#define ACU_UUI_X244							0x02		/* rec. X.244 */
#define ACU_UUI_SYSTEM_MANAGEMENT				0x03		/* reserved for system management convergence function */
#define ACU_UUI_IA5								0x04		/* IA5 characters (ASCII) */
#define ACU_UUI_V120							0x07		/* rec. V.120 */
#define ACU_UUI_Q931							0x08		/* rec. Q.931 */

/*--------------------------------------------------------------------------
*	pcs_user protocol discriminator
*  (ACU_CONN_RQ/IN/RS/CO, ACU_ALERT_IN/RQ, ACU_PROGRESS_IN, ACU_CLEAR_RQ/IN/RS/CO)
*-------------------------------------------------------------------------*/

#define	ACUPCS_USER_TRANSGROUP					0x44		/* Transgroupe */
#define	ACUPCS_USER_PUBLIPHONE					0x45		/* Publiphone */
#define	ACUPCS_USER_CALL_ROUTING				0x46		/* Call-routing */
#define	ACUPCS_USER_DIALOGUE					0x47		/* Dialogue entre PCS et 
                                                               périphérique intelligent */

/*--------------------------------------------------------------------------
*	Charging_info (ACU_CONN_RS/CO, ACU_CLEAR_RQ/IN/RS/CO, ACU_INFORMATION_RQ/IN)
*  (implemented in VN6 only for the time being, further extensions to
*  ETSI-like variants are to be done in the future)
*-------------------------------------------------------------------------*/

/* 'charging_info.type' field */

#define	ACUCHARG_TYPE_FREE_OF_CHARGE			0			/* free of charge (N/A in VN6/FRANCE) */
#define	ACUCHARG_TYPE_CHARGE_ON_DURATION		1			/* charge on duration (N/A in VN6/FRANCE) */
#define	ACUCHARG_TYPE_CHARGE_ON_ANSWER			2			/* charge on answer (N/A in VN6/FRANCE) */
#define	ACUCHARG_TYPE_CHARGE_INCREMENT			3			/* charge increment (N/A in VN6/FRANCE) */
#define	ACUCHARG_TYPE_SUB_TOTAL_CHARGE			4			/* sub-total charge */
#define	ACUCHARG_TYPE_TOTAL_CHARGE				5			/* total charge */

/* 'charging_info.period' field: (N/A in VN6/FRANCE)
*
* - optional
* - only used if the 'charging_info.type' is either
*   ACUCHARG_TYPE_CHARGE_ON_DURATION or ACUCHARG_TYPE_CHARGE_ON_ANSWER.
*/

#define	ACUCHARG_PERIOD_0_1_S					8			/* 0.1 second */
#define	ACUCHARG_PERIOD_1_S						9			/* 1 second */
#define	ACUCHARG_PERIOD_10_S					10			/* 10 seconds */
#define	ACUCHARG_PERIOD_60_S					11			/* 1 minute */

/* 'charging_info.multi' field: (N/A in VN6/FRANCE)
*
* - optional
* - only used if the 'charging_info.type' is either
*   ACUCHARG_TYPE_CHARGE_ON_DURATION or ACUCHARG_TYPE_CHARGE_ON_ANSWER
* - specifies the charging period multiplier;
* - if this field is coded ACU_BYTE_VAL_NIL or 0 (i.e. the field is
*   not provided), then the charging period is in second.
*/

/*--------------------------------------------------------------------------------------
*	Signal values (ACU_ALERT_IN, ACU_CLEAR_RQ/IN, ACU_CONN_RS/CO, ACU_INFORMATION_RQ/IN)
*-------------------------------------------------------------------------*/

#define ACUDIAL_ON								0x00		/* dial tone on */
#define ACURING_BACK_ON							0x01		/* ring back tone on */
#define ACUNET_CONGEST_ON						0x03		/* network congest tone on */
#define ACUBUSY_ON								0x04		/* busy tone on */
#define ACUTONES_OFF							0x3f		/* tones off */
#define ACUALERTING_OFF							0x4f		/* alerting off */
#define	ACUCREDIT_CARD_TONE_ON					0x40		/* credit card tone ON */
#define	ACUOUT_OF_RANGE_TONE_ON					0x41		/* out of range tone ON */
#define	ACUQUEUING_TONE_ON						0x42		/* queuing tone ON */
#define	ACUAUDIBLE_TONE_ON						0x44		/* audible tone ON */
#define	ACUVISUAL_ALERT_1_ON					0x45		/* visual alert #1 ON */
#define	ACUVISUAL_ALERT_2_ON					0x46		/* visual alert #2 ON */
#define	ACUSATCOM_CALL_NOTIFY					0x47		/* SATCOM call notify */

/*-------------------------------------------------------------------------
*	Endpoint Id (ACU_INFORMATION_RQ/IN and ACU_CONN_RQ)
*------------------------------------------------------------------------*/

#if _CC_SPID_INFO == ON

/* Action field */

#	define ACU_ACTION_NO_ENDPOINT_ID			0			/* Don't send any Endpoint Id (ACU_CONN_RQ) */
#	define ACU_ACTION_SND_USID					1			/* SPID was OK, send the Endpoint Id info */
#	define ACU_ACTION_NO_SPID_NEGOTIATION		2			/* SPID negotiation is not supported */
#	define ACU_ACTION_INVALID_SPID				3			/* The received SPID is wrong */
#	define ACU_ACTION_PROMPT_INFO				4			/* Need a SPID from the terminal */

/* Interpreter field */

#	define ACU_INTERPRETER_0					0			/* Terminal is selected if it is assigned the indicated TID and USID value */
#	define ACU_INTERPRETER_1					1			/* Terminal is selected if it is NOT assigned the indicated TID but is assigned the indicated USID value */

#endif


/*Provide common services header */
struct u4_acu_ss_hdr
{
#		define ACU_OP_ID_TRANSFER				1
#		define ACU_OP_ID_NOTIFY_TRANSFER		2
#		define ACU_OP_ID_NOTIFY_HOLD			3
#		define ACU_OP_ID_NOTIFY_RETRIEVE		4
#		define ACU_OP_ID_NOTIFY_DIVERSION		5
#		define ACU_OP_ID_GATEWAY_TRANSFER		6
#		define ACU_OP_ID_BRIDGE_CALLS			7
#		define ACU_OP_ID_DIVERSION				8
#		define ACU_OP_ID_DEFLECTION				9
#		define ACU_OP_ID_AOC_REQUEST			10
#		define ACU_OP_ID_AOC_INFORM				11
#		define ACU_OP_ID_ACTIVATE_DIVERSION		14
#		define ACU_OP_ID_DEACTIVATE_DIVERSION	 15
#		define ACU_OP_ID_ENQUIRE_DIVERSION		 16
#		define ACU_OP_ID_GATEWAY_NOTIF_DIVERSION 17
#		define ACU_OP_ID_HOLD                    18
#		define ACU_OP_ID_RETRIEVE                19
#		define ACU_OP_ID_ACTIVATE_DEFLECTION     20
#		define ACU_OP_ID_DEACTIVATE_DEFLECTION   21
#		define ACU_OP_ID_REMIND_DIVERSION        22
#		define ACU_OP_ID_TBCT_CALLS              23
#		define ACU_OP_ID_NOTIFY_TBCT_CALLS       24
#       define ACU_OP_ID_D_CHANNEL_ID_RQ         25
	uchar operation_id;  
#       define  ACU_OP_TYPE_INVOKE			1
#       define  ACU_OP_TYPE_REJECT			2 
#       define  ACU_OP_TYPE_RETRES			3
#       define  ACU_OP_TYPE_RETERR			4
	uchar operation_type;
	pad2
};


/*General constants used in multiple fields */

#	define ACU_SS_CALL_STATUS_NOT_SPECIFIED 0
#	define ACU_SS_CALL_STATUS_ALERTING      1
#	define ACU_SS_CALL_STATUS_ANSWERED      2

#	define ACU_SS_END_DESIGNATION_NOT_SPECIFIED 0 /*For use in some varients (ETSI)*/
#	define ACU_SS_END_DESIGNATION_PRIMARY       1
#	define ACU_SS_END_DESIGNATION_SECONDARY     2

#	define ACU_SS_DIVERSION_UNKNOWN          6
#	define ACU_SS_DIVERSION_CFU              1
#	define ACU_SS_DIVERSION_CFB              2
#	define ACU_SS_DIVERSION_CFNR             3
#	define ACU_SS_DIVERSION_CD_ALERTING      4
#	define ACU_SS_DIVERSION_CD_IMMEDIATE     5
#	define ACU_SS_DIVERSION_CD				 7   /*Used when unknown call deflection cause*/


#	define ACU_SS_BASIC_SERVICE_ALL_SERVICES			0	/* allServices */						
#	define ACU_SS_BASIC_SERVICE_SPEECH					1	/* speech */
#	define ACU_SS_BASIC_SERVICE_UNRESTR_DIG_INFO		2	/* unrestricted digital information */
#	define ACU_SS_BASIC_SERVICE_AUDIO_3K1HZ				3	/* audio 3k1Hz */
#	define ACU_SS_BASIC_SERVICE_UNR_D_INFO_TONE_AN		4	/* unrestricted digital information with tones and announcements */
#	define ACU_SS_BASIC_SERVICE_TELEPHONY_3K1HZ			32	/* telephony 3k1Hz */
#	define ACU_SS_BASIC_SERVICE_TELETEX					33	/* teletex */
#	define ACU_SS_BASIC_SERVICE_TELEFAX_GROUP4_CL1		34	/* telefax Group4 class1 */
#	define ACU_SS_BASIC_SERVICE_VIDEOTEX_SYNT_BASE		35	/* videotex syntax based */
#	define ACU_SS_BASIC_SERVICE_VIDEO_TELEPHONY			36	/* video telephony */
#	define ACU_SS_BASIC_SERVICE_TELEFAX_GROUP2_3		37	/* telefax Group2-3 */
#	define ACU_SS_BASIC_SERVICE_TELEPHONY_7KHZ			38	/* telephony 7kHz */

#	define ACU_SS_AOC_MULTIPLIER_THOUSANDTH        1
#	define ACU_SS_AOC_MULTIPLIER_HUNDREDTH         2
#	define ACU_SS_AOC_MULTIPLIER_TENTH             3
#	define ACU_SS_AOC_MULTIPLIER_ONE               4 
#	define ACU_SS_AOC_MULTIPLIER_TEN               5
#	define ACU_SS_AOC_MULTIPLIER_HUNDRED           6
#	define ACU_SS_AOC_MULTIPLIER_THOUSAND          7

#	define ACU_SS_AOC_SCALE_HUNDREDTH_SEC          1
#	define ACU_SS_AOC_SCALE_TENTH_SEC              2  
#	define ACU_SS_AOC_SCALE_ONE_SEC                3
#	define ACU_SS_AOC_SCALE_TEN_SEC                4 
#	define ACU_SS_AOC_SCALE_ONE_MIN                5
#	define ACU_SS_AOC_SCALE_ONE_HOUR               6
#	define ACU_SS_AOC_SCALE_24_HOURS               7 

/* The following number types are used in the configuration structure
* when a Q.SIG NAI is configured.  The values pertain the the Q.SIG 
* PINX address within the network.
*/
/* possible types of PINX Node Address */
#define ACU_QSIG_PINX_NB_UNKNOWN			0			/* unknown partyNumber : 'type_of_nb' field is meaningless */
#define ACU_QSIG_PINX_NB_PUBLIC				1			/* Public partyNumber */
#define ACU_QSIG_PINX_NB_PRIVATE			5			/* national standard partyNumber : 'type_of_nb' field is meaningless */
/* possible types of PINX number: Public or Private */
#define ACU_QSIG_PINX_PUB_NB_UNKNOWN			0			/* Public or Private : unknown number */
#define ACU_QSIG_PINX_PUB_NB_INTERNATIONAL		1			/* Public : international number */
#define ACU_QSIG_PINX_PUB_NB_NATIONAL			2			/* Public : national number */
#define ACU_QSIG_PINX_PUB_NB_NETWORK_SPFC		3			/* Public : network specific number */
#define ACU_QSIG_PINX_PUB_NB_SUBSCRIBER			4			/* Public : subscriber number */
#define ACU_QSIG_PINX_PUB_NB_ABBREVIATED		6			/* Public or Private : abbreviated number */

#define ACU_QSIG_PINX_PRIV_NB_UNKNOWN			0			/* Public or Private : unknown number */
#define ACU_QSIG_PINX_PRIV_NB_LEVEL2_REGIONAL	1			/* Private : level 2 regional number */
#define ACU_QSIG_PINX_PRIV_NB_LEVEL1_REGIONAL	2			/* Private : level 1 regional number */
#define ACU_QSIG_PINX_PRIV_NB_PTN_SPECIFIC		3			/* Private : PTN specific number */
#define ACU_QSIG_PINX_PRIV_NB_LOCAL				4			/* Private : local number */
#define ACU_QSIG_PINX_PRIV_NB_ABBREVIATED		6			/* Public or Private : abbreviated number */

#define ACU_SS_SUBSCRIPTION_NO_NOTIFY          1
#define ACU_SS_SUBSCRIPTION_NOTIFY_WITHOUT_NB  2
#define ACU_SS_SUBSCRIPTION_NOTIFY_WITH_NB     3


/*General structures used in multiple services */
struct acu_party_num
{
	uchar  invoke;       /*ON or OFF, indicates presence/absence of this information*/
	uchar  presentation_restricted; /*ON indicates presentation is restricted*/
    
#       define ACU_SS_NUMBER_PLAN_UNKNOWN					0x00
#       define ACU_SS_NUMBER_PLAN_PUBLIC_UNKNOWN			0x01
#       define ACU_SS_NUMBER_PLAN_PUBLIC_INTERNATIONAL		0x11
#       define ACU_SS_NUMBER_PLAN_PUBLIC_NATIONAL			0x21	
#       define ACU_SS_NUMBER_PLAN_PUBLIC_NETWORK_SPECIFIC	0x31
#       define ACU_SS_NUMBER_PLAN_PUBLIC_SUBSCRIBER			0x41
#       define ACU_SS_NUMBER_PLAN_PUBLIC_ABBREVIATED		0x61
#       define ACU_SS_NUMBER_PLAN_PRIVATE_UNKNOWN			0x04
#       define ACU_SS_NUMBER_PLAN_PRIVATE_LEVEL_1_REGIONAL	0x24	
#       define ACU_SS_NUMBER_PLAN_PRIVATE_LEVEL_2_REGIONAL	0x14
#       define ACU_SS_NUMBER_PLAN_PRIVATE_PTN_SPECIFIC		0x34
#       define ACU_SS_NUMBER_PLAN_PRIVATE_LOCAL             0x44
	uchar number_plan;  /*From SS_NUMBER_PLAN... constants*/
    
#       define ACU_SS_SCREEN_UNUSED_FIELD					0
#       define ACU_SS_SCREEN_USER_PROV_NOT_SCREENED			1
#       define ACU_SS_SCREEN_USER_PROV_VERIFIED				2
#       define ACU_SS_SCREEN_USER_PROV_FAILED_VERIFICATION	3
#       define ACU_SS_SCREEN_NETWORK_PROV					4
	uchar screen_ind;  /*From SS_SCREEN... constants */
    
	uchar offset;  /* Offset from start of this structure (address of invoke field)*/
	uchar len;     /* Number of bytes */
	pad2
};

struct acu_party_name
{
	uchar  invoke; /*ON/OFF, indicates presence/absence of party name*/
	uchar pres;    /* From SS_NAME... constants */
	uchar offset;  /* Offset from start of acu_party_name structure */
	uchar len;     /* Number of bytes */
	pad4
};

struct acu_party_subaddress
{
	uchar invoke;         /*ON or OFF, indicates presence/absence of subaddress */
	uchar pad;
	uchar type;           /* ACU_SUBADDRESS_TYPE_NSAP or ACU_SUBADDRESS_TYPE_USER */
	uchar odd_even_ind;   /* ACU_SUBADDRESS_EVEN or ACU_SUBADDRESS_ODD */
	uchar offset;	    /* Offset from start of acu_party_subaddress structure*/
	uchar len;		    /* Number of bytes	*/
	pad2
};

struct acu_address
{
	uchar  invoke;                /*ON or OFF, indicates presence/absence of address*/
	pad7
	struct acu_party_num          num;  /*Number portion of address*/
	struct acu_party_subaddress   sub;  /*Subaddress portion of address*/
};

struct acu_conn_id
{
	uchar  invoke;    /*ON or OFF, indicates presence/absence of conn_id*/
	uchar  board;     /*The board number */
	nai_t  nai;       /*The network access identifier*/
	uchar  conn_num;  /*The connection number */
	pad4
};

struct u4_op_byte_field
{
	uchar	invoke; /*ON or OFF*/
	uchar	value;  /*Interpretation depends on context*/
	pad2
};
struct u4_op_short_field
{
	uchar	invoke;      /*ON or OFF*/
	pad1
	WORD	value; /*Interpretation depends on context*/
};
struct op_long_field
{
	uchar	invoke; /*ON or OFF*/
	pad3
	DWORD	value;  /*Interpretation depends on context*/
};

struct acu_ss_association
{
	uchar	               invoke;
	pad3
	struct acu_party_num   charged_nb;   /*Changed party id by party_num  */
	struct u4_op_short_field  charge_id;    /*Unique ID value assigned by app*/
	pad4
};


struct acu_ss_chan
{
	uchar   invoke;       /*ON/OFF indicates presence/absence of acu_ss_chan */
	uchar	chan_id_excl;   /* chan_ids are preferred (OFF) or exclusive (ON) */
	nai_t   nai;          /*Network Access identifier */
	uchar   chan_id;      /*Channel ID on the nai*/
	pad4
};

#define Acu_ss_calculate_offset(_p_struct, _p_str)	(((uchar  *)_p_str)-((uchar  *)_p_struct))

/*---------------------------------------------------*
* Generic Services identification header and macros *
*---------------------------------------------------*/
struct acu_ss_service_header
{
	struct u4_acu_ext_hdr ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr  ss_hdr;	/* supplementary services header */
};

#   define Acu_ext_ss_op_type ((struct acu_ss_service_header  *)p_ext_data)->ss_hdr.operation_type	
#   define Acu_ext_ss_op_id   ((struct acu_ss_service_header  *)p_ext_data)->ss_hdr.operation_id	

#     define Acu_ext_ss_build_begin(_op_id, _op_type) \
		(uchar  *)p_ext_data = (Acu_ext_descr_nb > 0)?Acu_ext_descr_next_address:Acu_ext_descr_first_address; \
		Acu_ext_id = ACU_EXT_SERVICES; \
		Acu_ext_ss_op_id = _op_id; \
		Acu_ext_ss_op_type = _op_type;

#	define Acu_ext_ss_build_end(_p_end) \
		Acu_ext_lgth = Round8(((uchar  *)(_p_end)) - ((uchar  *)p_ext_data));\
		Acu_ext_descr_lgth += Acu_ext_lgth;\
		Acu_ext_descr_nb ++ ;



/*----------------------------------------*
* Generic Reject Structure               *
*----------------------------------------*/
/*This is only sent in the CC->APPLICATION direction.*/
struct acu_ss_reject
{
	struct u4_acu_ext_hdr ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr  ss_hdr;	/* supplementary services header */
#       define ACU_SS_REJECT_LOCAL_UNUSED_FIELD      0
#       define ACU_SS_REJECT_LOCAL_UNSPECIFIED       1
#		define ACU_SS_REJECT_LOCAL_INVALID_STATE     2
#		define ACU_SS_REJECT_LOCAL_NOT_IMPLEMENTED   3
#		define ACU_SS_REJECT_LOCAL_NO_RESPONSE       4
#		define ACU_SS_REJECT_LOCAL_INVALID_CHAN      5
#		define ACU_SS_REJECT_LOCAL_INVALID_CONN_ID   6
#		define ACU_SS_REJECT_LOCAL_TEMP_BUSY         7
#		define ACU_SS_REJECT_LOCAL_MISSING_PARAMETER 8
	uchar              local_cause; /* From ACU_SS_REJECT_LOCAL_... constants*/
#       define ACU_SS_REJECT_NETWORK_UNUSED_FIELD     0
#       define ACU_SS_REJECT_NETWORK_UNSPECIFIED      1
#		define ACU_SS_REJECT_NETWORK_NOT_SUBSCRIBED   2
#		define ACU_SS_REJECT_NETWORK_NOT_IMPLEMENTED  3
#		define ACU_SS_REJECT_NETWORK_INVALID_STATE    4
#		define ACU_SS_REJECT_NETWORK_BEARER_CAP_ERROR 5
#		define ACU_SS_REJECT_NETWORK_CHAN_NOT_AVAIL             6
#		define ACU_SS_REJECT_NETWORK_REQUESTED_CHAN_NOT_AVAIL   7
#       define ACU_SS_REJECT_NETWORK_DUPLICATE_INVOKE           8
#       define ACU_SS_REJECT_NETWORK_UNRECOGNIZED_OP            9 
#       define ACU_SS_REJECT_NETWORK_RESOURCE_LIMITATION        10
	uchar              network_cause;/* From ACU_SS_REJECT_NETWORK_... constants*/
	pad6
};

/****************************************************
*   Structures used for each of the services are   *
*   defined below.                                 *
****************************************************/

/*----------------------------------------*
* AOC Request Invoke structure           *
*----------------------------------------*/

struct acu_ss_aoc_request_invoke
{
	struct u4_acu_ext_hdr ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr  ss_hdr;	/* supplementary services header */
	uchar              aoc_s;     /* Request AOC-S services (ON/OFF)*/
	uchar              aoc_d;	/* Request AOC-D services (ON/OFF)*/
	uchar              aoc_e;	/* Request AOC-E services (ON/OFF)*/
	pad5
};
    
struct acu_ss_aoc_request_ret_result
{
	struct u4_acu_ext_hdr ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr  ss_hdr;	/* supplementary services header */
	uchar             aoc_s;      /* AOC-S services active (ON/OFF)*/
	uchar             aoc_d;	/* AOC-D services active (ON/OFF)*/
	uchar             aoc_e;	/* AOC-E services active (ON/OFF)*/
	pad5
};

struct acu_ss_aoc_request_ret_error
{
	struct u4_acu_ext_hdr ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr  ss_hdr;	/* supplementary services header */
	WORD             cause;     /* From ACU_SS_AOC_ERR.. constants */
	uchar             aoc_s;      /* Error applies to AOC-S service (ON/OFF)*/
	uchar             aoc_d;	/* Error applies to AOC-D service (ON/OFF)*/
	uchar             aoc_e;	/* Error applies to AOC-E service (ON/OFF)*/
	pad3
#			define             ACU_SS_AOC_ERR_UNSPECIFIED     0
#			define             ACU_SS_AOC_ERR_NO_CH_INF_AVAIL 26
};

#		define MAX_CURRENCY_SIZE 12 

typedef struct
{
	struct op_long_field	currency_amount;  /*Number of currency units charged */
	struct op_long_field	time;             /*Number of time units charged */
	struct op_long_field	granularity;	/*Integer or not included */
	struct u4_op_byte_field	multiplier;       /*Applies ot currency amount */
	struct u4_op_byte_field	time_scale;       /*Applies to time */
	struct u4_op_byte_field	granularity_scale;/*Applies to granularity*/
	struct u4_op_byte_field	currency_id_size; /*Zero if currency id not included */
	uchar	currency_id[MAX_CURRENCY_SIZE]; /*Currency ID */
#		define ACU_SS_AOC_S_TYPE_OF_CHARGE_CONTINUOUS  1
#		define ACU_SS_AOC_S_TYPE_OF_CHARGE_STEP        2
	uchar	type_of_charging; /* From ACU_SS_AOC_S_TYPE_OF_CHARGE... constants*/
	pad3

}tAcuSSAocDuration;

typedef struct sAcuSSAocSpecific
{
	struct op_long_field	currency_amount; 	      /*Number of currency units charged*/
	struct u4_op_byte_field	charge_code; 		/*10*/
	struct u4_op_byte_field	currency_id_size;		/*Number of bytes from currency_id*/
	struct u4_op_byte_field	multiplier;			/*From ACU_SS_AOC_MULTIPLIER constants*/
	pad4
	uchar	currency_id[MAX_CURRENCY_SIZE];
#		define ACU_SS_AOC_RATE_TYPE_FREE_OF_CHARGE                 1		
#		define ACU_SS_AOC_RATE_TYPE_FREE_OF_CHARGE_FROM_BEGINNING  2
#		define ACU_SS_AOC_RATE_TYPE_FLAT_RATE                      3
#		define ACU_SS_AOC_RATE_TYPE_SPECIAL_CHARGING               4 
#		define ACU_SS_AOC_RATE_TYPE_NOT_AVAIL                      5
	uchar	rate_type;				/*From ACU_SS_AOC_RATE_TYPE constants*/
	pad3

}tAcuSSAocSpecific;

typedef struct
{
	struct op_long_field	currency_amount; 	      /*Number of currency units charged*/
	struct u4_op_byte_field	currency_id_size;		/*Number of bytes from currency_id*/
	struct u4_op_byte_field	multiplier;			/*From ACU_SS_AOC_MULTIPLIER constants*/
	uchar	currency_id[MAX_CURRENCY_SIZE];           /*Currency ID string */
#		define ACU_SS_AOC_VOLUME_TYPE_OCTET     1
#		define ACU_SS_AOC_VOLUME_TYPE_SEGMENT   2
#		define ACU_SS_AOC_VOLUME_TYPE_MESSAGE   3
	uchar	volume_type;   /*From ACU_SS_AOC_VOLUME_TYPE constants*/
	pad3

}tAcuSSAocVolume;

typedef struct
{
#		define	ACU_SS_AOC_TYPE_OF_INFO_CHARGE_RATE    1
#		define  ACU_SS_AOC_TYPE_OF_INFO_NOT_AVAILABLE  2
	uchar 	type_of_info; /*From ACU_SS_AOC_TYPE_OF_INFO... constants */
#		define ACU_SS_AOC_CHARGED_ITEM_BASIC			0x01
#		define ACU_SS_AOC_CHARGED_ITEM_ATTEMPT   		0x02
#		define ACU_SS_AOC_CHARGED_ITEM_SETUP			0x04
#		define ACU_SS_AOC_CHARGED_ITEM_USER_TO_USER		0x08
#		define ACU_SS_AOC_CHARGED_ITEM_SUP_SERV			0x10
	uchar 	charged_item;	/*Bitmap of charged item constants*/
#		define ACU_SS_AOC_CHARGING_RATE_VOLUME           1
#		define ACU_SS_AOC_CHARGING_RATE_SPECIFIC         2 
#		define ACU_SS_AOC_CHARGING_RATE_DURATION         3 
	uchar	charging_rate;	/*One of charging rate constants */
	pad5
					union 
				{
					tAcuSSAocDuration	duration;  /* charging_rate == ACU_SS_AOC_CHARGING_RATE_DURATION*/
					tAcuSSAocSpecific	specific;  /* charging_rate == ACU_SS_AOC_CHARGING_RATE_SPECIFIC*/
					tAcuSSAocVolume	volume;    /* charging_rate == ACU_SS_AOC_CHARGING_RATE_VOLUME*/	
				}rate;
} tAcuSSAocSInform;

#	define MAX_RECORDED_UNIT_RECORDS 4
typedef struct
{
		DWORD	num_of_charging_units[MAX_RECORDED_UNIT_RECORDS];     /*Number of charging units */	
#		define ACU_SS_AOC_TYPE_OF_CHARGING_UNITS_UNUSED    255 
	uchar	type_of_charging_units[MAX_RECORDED_UNIT_RECORDS];		/*Used only if type_of_charging is CHARGING_UNITS*/
	uchar invoke;       /*If OFF, then no Recorded Unit information is available*/
	uchar num_records;  /*Indicates how many of the array elements are used */
	pad2
}tRecordedUnits;

typedef struct
{
	struct op_long_field	currency_amount;			/*Used only if type_of_charging is CURRENCY_UNITS*/
	struct u4_op_byte_field	currency_id_size;			/*Used only if type_of_charging is CURRENCY_UNITS*/
	struct u4_op_byte_field	multiplier;				/*Used only if type_of_charging is CURRENCY_UNITS*/
#		define ACU_SS_AOC_BILLING_ID_NORMAL			1
#		define ACU_SS_AOC_BILLING_ID_CREDIT_CARD	2
#		define ACU_SS_AOC_BILLING_ID_REVERSE		3  /*ETSI ONLY*/
#		define ACU_SS_AOC_BILLING_ID_CFU 			4  /*Q.SIG Only*/
#		define ACU_SS_AOC_BILLING_ID_CFB			5  /*Q.SIG Only*/
#		define ACU_SS_AOC_BILLING_ID_CFNR			6  /*Q.SIG Only*/
#		define ACU_SS_AOC_BILLING_ID_CD				7  /*Q.SIG Only*/
#		define ACU_SS_AOC_BILLING_ID_TRF			8  /*Q.SIG Only*/
	struct u4_op_byte_field	billing_id;				/*From ACU_SS_AOC_BILLING_ID constants*/
	pad4
	struct acu_ss_association             charge_association; /* Returns ID of charge for AOC-E after call clearing */
	tRecordedUnits  recorded_units;     	/*Used only if type_of_charging is CHARGING_UNITS*/
	uchar	currency_id[MAX_CURRENCY_SIZE];	/*Used only if type_of_charging is CURRENCY_UNITS*/ 
#		define ACU_SS_AOC_TYPE_OF_CHARGE_SUBTOTAL       1
#		define ACU_SS_AOC_TYPE_OF_CHARGE_TOTAL          2
#		define ACU_SS_AOC_TYPE_OF_CHARGE_NOT_AVAILABLE  3
	uchar	          type_of_charging; 	           /* From SS_AOC_TYPE_OF_CHARGE... constants		*/
#		define ACU_SS_AOC_RECORDED_CHARGES_CHARGING_UNITS  1  
#		define ACU_SS_AOC_RECORDED_CHARGES_CURRENCY_UNITS  2
#		define ACU_SS_AOC_RECORDED_CHARGES_FREE_OF_CHARGE  3
	uchar	recorded_charges;	/* From SS_AOC_RECORDED_CHARGES constants		*/
	uchar   completed; /*Set to OFF if additional recorded units are queued */
                         /*in a subsequent message */
	pad1
} tAcuSSAocDInform;

typedef tAcuSSAocDInform tAcuSSAocEInform;

struct acu_ss_aoc_inform_invoke
{
	struct u4_acu_ext_hdr ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr  ss_hdr;	/* supplementary services header */
#		define ACU_SS_AOC_TYPE_AOC_S_INFORM 1
#		define ACU_SS_AOC_TYPE_AOC_E_INFORM 2
#		define ACU_SS_AOC_TYPE_AOC_D_INFORM 3
	uchar	aoc_type;  /* From ACU_SS_AOC_TYPE... constants */
	pad7
		union
	{
		tAcuSSAocSInform	aoc_s; /*aoc_type==AOC_SS_TYPE_AOC_S_INFORM*/
		tAcuSSAocDInform	aoc_d; /*aoc_type==AOC_SS_TYPE_AOC_D_INFORM*/
		tAcuSSAocEInform	aoc_e; /*aoc_type==AOC_SS_TYPE_AOC_E_INFORM*/
	} aoc_data;
};



/*----------------------------*
* NOTIFY TRANSFER STRUCTURES *
*----------------------------*/
struct acu_ss_notify_transfer_invoke
{
	struct u4_acu_ext_hdr       ext_hdr;        /* extension header */
	struct u4_acu_ss_hdr	    ss_hdr;         /* supplementary services header */
	struct acu_party_name       redir_name;     /* Name of new connected party */
	struct acu_ss_association   charge_id;      /* For AOC-E Interworking, Q.SIG only */
	struct acu_party_num        redir_nb;       /*Inidates number of joined party*/ 
	struct acu_conn_id	        joined_conn_id; /*Applies in APPL->CC direction*/
	struct acu_party_subaddress redir_sub;      /*Subaddress of joined party */
	WORD                      response_rq;    /*If ON, application must respond */
	uchar                       call_status;    /*From ACU_SS_CALL_STATUS... constants */
	uchar                       end_designation;/*Primary/Secondary, for Q.SIG only */
	uchar                       update;         /*If ON, then provides additional info for last transfer*/
	pad3
};

struct acu_ss_notify_transfer_ret_result
{
	struct u4_acu_ext_hdr       ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr	    ss_hdr; 	/* supplementary services header */
	struct acu_party_name       redir_name; /*Provides name of redirecting party */
	struct acu_party_num        redir_nb;   /*Provides number of redirecting party */
	struct acu_party_subaddress redir_sub;  /*Provides subaddress of redirecting party */
};


/*----------------------------*
* BRIDGE CALLS STRUCTURES *
*----------------------------*/
struct acu_ss_bridge_calls_invoke
{
	struct u4_acu_ext_hdr    ext_hdr;	 /* extension header */
	struct u4_acu_ss_hdr	  ss_hdr;	 /* supplementary services header */
	struct acu_conn_id    bridge_to; /* Connection id of call to bridge to */
};

struct acu_ss_bridge_calls_ret_result
{
	struct u4_acu_ext_hdr    ext_hdr;	 /* extension header */
	struct u4_acu_ss_hdr	  ss_hdr;	 /* supplementary services header */
};

/*-------------------------------*
 D CHANNEL IDENTIFIER STRUCTURES
*-------------------------------*/

#ifndef ACU_MX_SZ_D_CHNL_ID
#	define ACU_MX_SZ_D_CHNL_ID			4	/* default maximum size for D-Channel ID */
#endif

struct acu_d_channel_id
{
    uchar   value[ACU_MX_SZ_D_CHNL_ID];  /* D-Channel Identifier value*/
    uchar   length;                       /* length of D-Channel Id. value*/
    pad3
};

struct acu_ss_d_channel_id_rq_invoke
{
	struct u4_acu_ext_hdr    ext_hdr;	 /* extension header */
	struct u4_acu_ss_hdr	 ss_hdr;	 /* supplementary services header */
};

struct acu_ss_d_channel_id_rq_ret_result
{
	struct u4_acu_ext_hdr    ext_hdr;	 /* extension header */
	struct u4_acu_ss_hdr	 ss_hdr;	 /* supplementary services header */
    struct acu_d_channel_id    dCID;
};

struct acu_ss_d_channel_id_rq_ret_err
{
	struct u4_acu_ext_hdr      ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr       ss_hdr;	    /* supplementary services header */
#       define D_CHANNEL_ID_RETERR_NOT_AVAILABLE         3
#       define D_CHANNEL_ID_RETERR_UNSPECIFIED           255
	WORD                     err_id; /* From D_CHANNEL_ID_RETERR... constants */
	pad6
};


/*----------------------------*
* TBCT CALLS STRUCTURES *
*----------------------------*/
struct acu_ss_tbct_calls_invoke
{
	struct u4_acu_ext_hdr    ext_hdr;	 /* extension header */
	struct u4_acu_ss_hdr	  ss_hdr;	 /* supplementary services header */
    struct acu_call_ref      call_ref;   /* call reference of call to tbct to*/
    struct acu_d_channel_id     dCID;    /* D-Channel Identifier, use in multiple PRI case */
};

struct acu_ss_tbct_calls_ret_result
{
	struct u4_acu_ext_hdr    ext_hdr;	 /* extension header */
	struct u4_acu_ss_hdr	  ss_hdr;	 /* supplementary services header */
    DWORD                   call_tag;    /* call tag associated with the transferred call */
    pad4
};

 
struct acu_ss_tbct_calls_ret_err
{
	struct u4_acu_ext_hdr      ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr       ss_hdr;	    /* supplementary services header */
#       define TBCT_RETERR_NOT_SUBSCRIBED                  0
#       define TBCT_RETERR_NOT_AVAILABLE                   3
#       define TBCT_RETERR_INVALID_CALL_STATE              7
#       define TBCT_RETERR_INTERAC_NOT_ALLOWED             10
#       define TBCT_RETERR_NOT_ALLOWED                     32
#       define TBCT_RETERR_LINK_ID_NOT_ASSIGNED            61
#       define TBCT_RETERR_DCHAN_ID_NOT_ASSIGNED           254
#       define TBCT_RETERR_UNSPECIFIED                     255
	WORD                     err_id; /* From TBCT_RETERR_... constants */
	pad6
};

/*------------------------------*
* NOTIFY TBCT CALLS STRUCTURES  *
*-------------------------------*/

struct acu_ss_notify_tbct_calls_ret_result
{
	struct u4_acu_ext_hdr    ext_hdr;	 /* extension header */
	struct u4_acu_ss_hdr	  ss_hdr;	 /* supplementary services header */
    DWORD                   call_tag;    /* call tag identifies the cleared transferred call */
    pad4
};

/*-------------------------------*
* DIVERSION REMINDER STRUCTURES *
*-------------------------------*/
struct acu_ss_reminder_diversion_invoke
{
	struct u4_acu_ext_hdr      ext_hdr; /* extension header */
	struct u4_acu_ss_hdr       ss_hdr;	 /* supplementary services header */
};

/*----------------------------*
* NOTIFY DIVERSION STRUCTURES *
*----------------------------*/
struct acu_ss_notify_diversion_invoke
{
	struct u4_acu_ext_hdr      ext_hdr; /* extension header */
	struct u4_acu_ss_hdr       ss_hdr;	 /* supplementary services header */
	struct u4_op_byte_field	reason;  /* Reason for diversion, from ACU_SS_DIVERSION_... constants */
	struct u4_op_byte_field    basic_service; /* From ACU_SS_BASIC_SERVICE_... constants*/ 
	struct acu_conn_id	    related_conn_id; /*Identifies related connection*/
	struct acu_party_num    redir_nb;       /*At directed-to user, number doing redirection*/
	struct acu_party_num    orig_redir_nb;  /*At directed-to user, first number doing redirection*/
	struct acu_party_num    nominated_nb;  /*Indicates new dest number to calling user*/
	struct acu_party_name redir_name;      /* Name of user invoking the diversion */
	struct acu_party_name orig_redir_name; /* At diverted-to user, first name
                                              * doing redirection */
	struct u4_op_byte_field	subscription;   /*Subscription option for presentation */
	uchar                   completed; /*ON indicates diversion completed, OFF indicates in progress */
	uchar                   diversion_count; /*Passed up to application in acu_ss_divert_invoke */
	pad2
};

struct acu_ss_notify_diversion_ret_result
{
	struct u4_acu_ext_hdr      ext_hdr;      /* extension header */
	struct u4_acu_ss_hdr       ss_hdr;	      /* supplementary services header */
	struct acu_party_name   redir_name;   /*Redirection Name */
	WORD                  pres_allowed; /*Indicates whether diverted-to number can be presented(ON/OFF)*/
	pad6
};

/*----------------------------*
* HOLD STRUCTURES *
*----------------------------*/
struct acu_ss_hold_invoke
{
	struct u4_acu_ext_hdr   ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr    ss_hdr;	/* supplementary services header */
	struct u4_op_byte_field due_to_alternating;  /*ON if alternating between connections*/
	pad4
};

struct acu_ss_hold_ret_result
{
	struct u4_acu_ext_hdr   ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr    ss_hdr;	/* supplementary services header */
};

/*----------------------------*
* RETRIEVE STRUCTURES *
*----------------------------*/
struct acu_ss_retrieve_invoke
{
	struct u4_acu_ext_hdr   ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr    ss_hdr;	/* supplementary services header */
	struct u4_op_byte_field due_to_alternating;  /*ON if alternating between connections*/
	pad4
};

struct acu_ss_retrieve_ret_result
{
	struct u4_acu_ext_hdr   ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr    ss_hdr;	/* supplementary services header */
};
/*----------------------------*
* NOTIFY HOLD STRUCTURES *
*----------------------------*/
struct acu_ss_notify_hold_invoke
{
	struct u4_acu_ext_hdr   ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr    ss_hdr;	/* supplementary services header */
	struct u4_op_byte_field due_to_alternating;  /*ON if alternating between connections*/
	pad4
};


/*----------------------------*
* NOTIFY RETRIEVE STRUCTURES *
*----------------------------*/
struct acu_ss_notify_retrieve_invoke
{
	struct u4_acu_ext_hdr ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr  ss_hdr;	/* supplementary services header */
	struct u4_op_byte_field due_to_alternating;  /*ON if alternating between connections*/
	pad4
};

/*----------------------------*
* TRANSFER STRUCTURES        *
*----------------------------*/
struct acu_ss_transfer_invoke
{
	struct u4_acu_ext_hdr         ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr          ss_hdr;	      /* supplementary services header */
	struct acu_party_num       redir_nb;     /* Number to direct call to */
	struct acu_conn_id         related_conn; /* reference to held connection  */
	struct acu_ss_association  charge_association; /*Optional, used when AOC-E service has been invoked*/
	WORD					   call_status;  /* From ACU_SS_CALL_STATUS_... constants */
	pad6
};

struct acu_ss_transfer_ret_result
{
	struct u4_acu_ext_hdr         ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr          ss_hdr;	      /* supplementary services header */
};

struct acu_ss_transfer_ret_err
{
	struct u4_acu_ext_hdr      ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr       ss_hdr;	    /* supplementary services header */
#       define TRANSFER_RETERR_UNSPECIFIED                     255
#       define TRANSFER_RETERR_RESOURCE_UNAVAILABLE            11
#       define TRANSFER_RETERR_NOT_SUBSCRIBED                  0
#       define TRANSFER_RETERR_NOT_AVAILABLE                   3
#       define TRANSFER_RETERR_INVALID_CALL_STATE              7
#       define TRANSFER_RETERR_INTERAC_NOT_ALLOWED             10
#       define TRANSFER_RETERR_NOT_ALLOWED                     32
	WORD                   err_id; /* From TRANSFER_RETERR_... constants */
	pad6
};

/*----------------------------*
* GATEWAY TRANSFER STRUCTURES*
*----------------------------*/
struct acu_ss_gateway_trf_invoke
{
	struct u4_acu_ext_hdr          ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	    /* supplementary services header */
	struct acu_party_num        redir_nb;      /* Number to direct call to */
	struct acu_party_subaddress redir_sub; /*Subaddress of transfer*/
	WORD					    call_status;/* From ACU_SS_CALL_STATUS_... macros */
	pad6
};
struct acu_ss_gateway_trf_ret_error
{
	struct u4_acu_ext_hdr      ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr       ss_hdr;	    /* supplementary services header */
	WORD                  err_id;
	uchar                   local_cause;
	pad5
};
/*----------------------------*
* GATEWAY NOTIFY DIVERSION STRUCTURES*
*----------------------------*/
struct acu_ss_gateway_notify_div_invoke
{
	struct u4_acu_ext_hdr          ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	    /* supplementary services header */
	struct acu_party_num        redir_nb;   /* Number call has been diverted to */
	struct u4_op_byte_field        reason;     /* Reason for diversion, from ACU_SS_DIVERSION_... macros */
	pad4
};

/*----------------------------*
* DEFLECT CALL STRUCTURES*
*----------------------------*/
struct acu_ss_activate_deflect_invoke
{
	struct u4_acu_ext_hdr          ext_hdr;	/* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	      /* supplementary services header */
	struct acu_address          deflect_to;   /* address to deflect all calls to */
};
struct acu_ss_activate_deflect_ret_result
{
	struct u4_acu_ext_hdr          ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	      /* supplementary services header */
};
struct acu_ss_deactivate_deflect_invoke
{
	struct u4_acu_ext_hdr          ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	      /* supplementary services header */
};

struct acu_ss_deactivate_deflect_ret_result
{
	struct u4_acu_ext_hdr          ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	      /* supplementary services header */
};

struct acu_ss_deflect_invoke
{
	struct u4_acu_ext_hdr          ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	      /* supplementary services header */
	struct acu_address          deflect_to;   /* Number to direct call to */
	struct acu_ss_association   charge_association; /*Optional, used when AOC-E service has been invoked*/
};

struct acu_ss_deflect_ret_result
{
	struct u4_acu_ext_hdr          ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	      /* supplementary services header */
};

struct acu_ss_deflect_ret_error
{
	struct u4_acu_ext_hdr          ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	      /* supplementary services header */
#       define DEFLECT_RETERR_NOT_SUBSCRIBED                  0
#       define DEFLECT_RETERR_NOT_AVAILABLE                   3
#       define DEFLECT_RETERR_SS_INTERACTION_NOT_ALLOWED      10
#       define DEFLECT_RETERR_INVALID_DIVERTED_TO_NB          12
#       define DEFLECT_RETERR_SPECIAL_SERVICE_NB              14
#       define DEFLECT_RETERR_DIVERSION_TO_SERVED_USER_NB     15
	
#       define DEFLECT_RETERR_NUMBER_OF_DIVERSIONS_EXCEEDED   24
#       define DEFLECT_RETERR_INCOMING_CALL_ACCEPTED          23  
#       define DEFLECT_RETERR_REQUEST_ALREADY_ACCEPTED        48
#       define DEFLECT_RETERR_UNSPECIFIED                     255 
	WORD                      err_id;  /* From DEFLECT_RETERR_... constants */
	pad6
};


/*----------------------------*
* DIVERT CALL STRUCTURES     *
*----------------------------*/
struct acu_ss_divert_invoke
{
	struct u4_acu_ext_hdr          ext_hdr;	     /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	         /* supplementary services header */
	struct acu_address          divert_to_nb;    /* Number of new called party   */
	struct acu_party_num        divert_from_nb;  /* Number called in last setup, 
                                                    * if different from orig_called nb */
	struct acu_party_num        orig_called_nb;  /* Number called in first setup*/
	struct acu_address          calling_nb;      /* Calling number in last setup */
	struct acu_party_name calling_name;    /* Calling name in last setup */
	struct acu_party_name redir_name;      /* Name of user invoking this diversion */
	struct acu_party_name orig_called_name;/* Name of the original called party */
	uchar                       procedure;       /* from ACU_SS_DIVERSION_... constants*/
	uchar                       diversion_count; /*Passed to application, meaningless from application */
	uchar						subscription; /*From SS_SUBSCRIPTION_... constants */
	pad5/*uchar                       basic_service;*/
};

struct acu_ss_divert_ret_result
{
	struct u4_acu_ext_hdr          ext_hdr;	   /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	       /* supplementary services header */
	struct u4_op_byte_field        reason;        /* Reason for diversion, from ACU_SS_DIVERSION_... macros */
	struct u4_op_byte_field        basic_service; /* Applies in CC->APP in some varients*/ 
	struct acu_address          calling_party;  
	struct acu_address          served_user;
	struct acu_party_num        orig_called;
	struct acu_party_num        last_redirecting;
};

struct acu_ss_divert_ret_error
{
	struct u4_acu_ext_hdr          ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	      /* supplementary services header */
#       define DIVERT_RETERR_NOT_SUBSCRIBED                  0
#       define DIVERT_RETERR_NOT_AVAILABLE                   3
#       define DIVERT_RETERR_RESOURCE_UNAVAILABLE            11
#       define DIVERT_RETERR_INVALID_DIVERTED_TO_NB          12
#       define DIVERT_RETERR_SPECIAL_SERVICE_NB              14
#       define DIVERT_RETERR_DIVERSION_TO_SERVED_USER_NB     15
#       define DIVERT_RETERR_NUMBER_OF_DIVERSIONS_EXCEEDED   24
#       define DIVERT_RETERR_SS_INTERACTION_NOT_ALLOWED      10
#       define DIVERT_RETERR_UNSPECIFIED                     1008
#       define DIVERT_RETERR_NO_RESPONSE                     2048
#       define DIVERT_RETERR_DIVERTED_LEG_FAILED             2049
	WORD                      err_id; /* From DIVERT_RETERR constants */
	pad6
};


/*-------------------------------*
* ACTIVATE DIVERTION STRUCTURES *
*-------------------------------*/
struct acu_ss_act_divert_invoke
{
	struct u4_acu_ext_hdr          ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	        /* supplementary services header */
	struct acu_address          diverted_to;    /* New destination of call */  
	struct acu_party_num        served_user;    /* User number to activate the service
                                                   * for.  If not invoked, then diversion
                                                   * applies to entire NAI */
	struct acu_party_num        activating_user; /*User activating the diversion, if
                                                    *different from the served user*/
	uchar                       procedure;     /* from ACU_SS_DIVERSION_... constants*/
	uchar                       basic_service; /* from ACU_SS_BASIC_SERVICE... constants */
	pad6
};

struct acu_ss_act_divert_ret_result
{
	struct u4_acu_ext_hdr          ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	      /* supplementary services header */
};
struct acu_ss_act_divert_ret_error
{
	struct u4_acu_ext_hdr          ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	      /* supplementary services header */
#define ACT_DIVERT_RETERR_NOT_SUBSCRIBED           0
#define ACT_DIVERT_RETERR_NOT_AVAILABLE            3
#define ACT_DIVERT_RETERR_INVALID_SERVED_NB        6
#define ACT_DIVERT_RETERR_INTERAC_NOT_ALLOWED      10
#define ACT_DIVERT_RETERR_SERVICE_NOT_PROVIDED     8
#define ACT_DIVERT_RETERR_RESOURCE_UNAVAILABLE     11
#define ACT_DIVERT_RETERR_INV_DIVERTED_TO_NB       12
#define ACT_DIVERT_RETERR_DIV_SPECIAL_SERV_NB      14
#define ACT_DIVERT_RETERR_DIV_TO_SERVED_USER_NB    15
#define ACT_DIVERT_RETERR_UNSPECIFIED           255
	WORD                       err_id; /* From ACUT_DIVERT_RETERR...*/
	pad6
};
/*-------------------------------*
* DEACTIVATE DIVERTION STRUCTURES *
*-------------------------------*/
struct acu_ss_deact_divert_invoke
{
	struct u4_acu_ext_hdr          ext_hdr;	     /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	           /* supplementary services header */
	struct acu_party_num        served_user;       /* User to deactivate diversion for*/
	struct acu_party_num        deactivating_user; /* User initiating the deactivation*/ 
	uchar                       procedure;         /* from ACU_SS_DIVERSION_... constants*/
	uchar                       basic_service;     /* from ACU_SS_BASIC_SERVICE_... constants */
	pad6
};

struct acu_ss_deact_divert_ret_result
{
	struct u4_acu_ext_hdr          ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	      /* supplementary services header */
};
struct acu_ss_deact_divert_ret_error
{
	struct u4_acu_ext_hdr          ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	      /* supplementary services header */
#define DEACT_DIVERT_RETERR_NOT_SUBSCRIBED           0
#define DEACT_DIVERT_RETERR_NOT_AVAILABLE            3
#define DEACT_DIVERT_RETERR_INVALID_SERVED_NB        6
#define DEACT_DIVERT_RETERR_NOT_ACTIVATED            46
#define DEACT_DIVERT_RETERR_UNSPECIFIED              255
	WORD                      err_id;    /*From DEACT_DIVERT_RETERR_... constants*/
	pad6
};
/*-------------------------------*
* ENQUIRE DIVERSION STRUCTURES  *
*-------------------------------*/
struct acu_ss_enquire_divert_invoke
{
	struct u4_acu_ext_hdr          ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	      /* supplementary services header */
	struct acu_party_num        served_user;    /* Leave uninvoked to get information 	*/
										/* on all served numbers			*/
	struct acu_party_num        enquiring_user; /*For remote Q.SIG */ 
	uchar                       procedure;     /* from ACU_SS_DIVERSION_... constants*/
	uchar                       basic_service; /* From SS_BASIC_SERVICE_... constants	*/
	pad6
};


struct acu_ss_enquire_divert_ret_result
{
	struct u4_acu_ext_hdr          ext_hdr;	    /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	        /* supplementary services header */
	struct acu_address          diverted_to;    /* Address that served user is 
                                                   * forwarded to */
	struct acu_party_num        served_user;    /* Served user's address */   
	struct u4_op_byte_field        remote_enabled; /* ON/OFF, inicates remotely enabled */
	struct u4_op_byte_field        procedure;      /* From ACU_SS_DIVERSION_... constants*/
	struct u4_op_byte_field        basic_service;  /* From ACU_SS_BASIC_SERVICE_... constants*/
	uchar                       complete;       /* ON when no more messages coming, OFF if more coming */
	                                            /* Note - when ON, other fields might not be invoked */
	pad3
};

struct acu_ss_enquire_divert_ret_error
{
	struct u4_acu_ext_hdr          ext_hdr;	  /* extension header */
	struct u4_acu_ss_hdr           ss_hdr;	      /* supplementary services header */
#define ENQUIRE_DIVERT_RETERR_NOT_SUBSCRIBED           0
#define ENQUIRE_DIVERT_RETERR_NOT_AVAILABLE            3
#define ENQUIRE_DIVERT_RETERR_INVALID_SERVED_NB        6
#define ENQUIRE_DIVERT_RETERR_UNSPECIFIED              255
	WORD                       err_id;  /* From ENQUIRE_DIVERT_... constants */
	pad6
};



/*---------------------------------------------------------------------------
SM_CHANNEL_MAINT_RQ
*--------------------------------------------------------------------------*/
/* Action type */

#define	I_MAINTENANCE					0

/* Preference */

#define	I_PREF_INTERFACE				0
#define	I_PREF_B_CHANNEL				1
#define	I_PREF_D_CHANNEL				2
#define I_PREF_ALL_INTERFACES           3

/* D channel status */

#define	I_D_STATE_IS					0						/* In Service */
#define	I_D_STATE_OOS					2						/* Out Of Service */

/* B channel status */

#define	I_B_CHAN_IN_SERVICE				0			/* B channel in service */
#define	I_B_CHAN_OUT_OF_SERVICE			2			/* B channel out of order */

/*-------------------------------------------------------------------------
*	ACU and CC entities entry point prototypes
*------------------------------------------------------------------------*/

#if NEW_FCT_STYLE == ON
uchar acu (struct message  *);
uchar cc  (struct message  *);
#else
uchar acu ();
uchar cc  ();
#endif

/*-------------------------------------------------------------------------
*		Simulation routines prototypes
*------------------------------------------------------------------------*/
#if (SIMULATION == ON) || (SIM_ANALYSER == ON)

#	if NEW_FCT_STYLE == ON

uchar 	ana_sdu_acu 			(struct message  *p_msg);
uchar	build_sdu_dte_to_acu 	(void);
uchar	build_sdu_acu_to_dte	(void);

#	else

uchar 	ana_sdu_acu 			();
uchar	build_sdu_dte_to_acu 	();
uchar	build_sdu_acu_to_dte	();

#	endif

#endif

#endif /* ACU_INT */
/*------------------------------------------------------------------------*/


#ifdef ALIGN_64

#undef ALIGN_64
#undef pad1
#undef pad2
#undef pad3
#undef pad4

#undef pad5
#undef pad6
#undef pad7

#endif

#ifdef __cplusplus
        }
#endif
		
		/*EOF*/

