/***************************************************************************
*                                  ISDNVAL.H
*
*  Values for ISDN supplementary services arguments used in
*  Natural MicroSystems AG ISDN - Layer 4.
*
*  Copyright (c)1998 Natural MicroSystems Corporation. All rights reserved.
****************************************************************************/

/*--------------------------------------------------------------------------
 *	Requested ISDN service
 *-------------------------------------------------------------------------*/

#define FAX_SERVICE            'F'	/* call for G3 facsimile service       */
#define FAX_4_SERVICE          '4'	/* call for G4 facsimile service       */
#define DATA_SERVICE           'D'	/* call for 'data' service             */
#define DATA_GCI_SERVICE       ACU_DATA_SERVICE	/* call for 'data' service */
                                    /* on GCI bus                          */
#define DATA_56KBS_SERVICE     'K'	/* call for 'data at 56 KBS' service   */
#define RAW_DATA_SERVICE       '!'  /* call for 'raw data' service on GCI  */
                                    /* bus: no MPH_B_INIT_RQ is generated  */
                                    /* (no B-channel driver is associated) */
#define DATA_TRANS_SERVICE     'T'	/* call for transparent data service   */
#define MODEM_SERVICE          'M'	/* call for modem data service         */
#define AUDIO_7_SERVICE        '7'	/* call for 7kHz Audio service         */
#define X25_SERVICE            'X'	/* call for X.25 circuit-mode service  */
#define X25_PACKET_SERVICE     'P'	/* call for X.25 packet-mode service   */
#define VOICE_SERVICE          'V'	/* call for voice service              */
#define VOICE_GCI_SERVICE      'G'	/* call for voice service on GCI bus   */
#define RAW_TELEPHONY_SERVICE  ':'  /* call for 'raw telephony' service on */
                                    /* GCI bus: no MPH_B_INIT_RQ generated */
                                    /* (no B-channel driver is associated) */
#define VOICE_TRANS_SERVICE    'W'  /* call for transparent voice service  */
#define V110_SERVICE           '1'  /* call for V.110 service              */
#define V120_SERVICE           '2'  /* call for V.120 service              */
#define VIDEO_SERVICE          'O'  /* call for VIDEO service              */
#define TDD_SERVICE            'Q'  /* call for TDD service                */
#define DATA_H0_SERVICE        '0'  /* call for Data using H0  (384kbs)    */
                                    /* channel service (PRI only)          */
#define DATA_H11_SERVICE       'H'  /* call for Data using H11             */
                                    /* (1536kbs) channel service           */
#define DATA_H12_SERVICE       'I'  /* call for Data using H12 (1536kbs)   */
                                    /* channel service                     */
#define DATA_MULTIRATE_SERVICE 'R'  /* call for Data using Multirate       */
                                    /* (2..30*64kbs) channel service       */
#define DATA_128KBS_SERVICE    'S'  /* call for Data using 2*64kbs channel */
                                    /* service (BRI only)                  */
#define NO_B_CHAN_SERVICE      'N'  /* call for no B-channel service       */
                                    /* (bearer-independent calls -         */
                                    /* QSIG only)                          */

/* Services for use with 'Physical Relay' process */

#define FAX_RELAY_SERVICE        'f' /* call for G3 facsimile service      */
#define DATA_RELAY_SERVICE       'd' /* call for 'data' service            */
#define DATA_56KBS_RELAY_SERVICE 'k' /* call for 'data at 56 KBS' service  */
#define DATA_TRANS_RELAY_SERVICE 't' /* call for data transparent service  */
#define MODEM_RELAY_SERVICE      'm' /* call for modem data service        */
#define X25_RELAY_SERVICE        'x' /* call for X.25 circuit-mode service */
#define VOICE_RELAY_SERVICE      'v' /* call for voice service             */
#define VOICE_GCI_RELAY_SERVICE  'g' /* call for voice service on GCI bus  */

#define NO_SERVICE               'U' /* undefined service                  */

/*--------------------------------------------------------------------------
 *	calling and redirecting number presentation 
 *-------------------------------------------------------------------------*/
/* in outgoing messages 0xff in this field will be translated to 0 in the 
   actual IE, if no value is set for this field, the stack will insert a 
   default value based on the variant.
   If the stack receives a 0 in this field in an incoming IE, it sends a
   0xff to the application                                                 */
#define N_PRES_ALLOWED       0xff /* presentation allowed				   */
#define N_PRES_RESTRICTED    0x01 /* presentation restricted               */
#define N_PRES_NOT_AVAILABLE 0x02 /* number not available                  */

/*--------------------------------------------------------------------------
 *	calling, called, redirecting number type 
 *-------------------------------------------------------------------------*/
/* in outgoing messages 0xff in this field will be translated to 0 in the 
   actual IE, if no value is set for this field, the stack will insert a 
   default value based on the variant.
   If the stack receives a 0 in this field in an incoming IE, it sends a
   0xff to the application                                                 */
#define N_TYPE_UNKNOWN               0xff /* unknown                       */
#define N_TYPE_INTERNATIONAL         0x01 /* international number          */
#define N_TYPE_NATIONAL              0x02 /* national number               */
#define N_TYPE_NET_SPF               0x03 /* network specific number       */
#define N_TYPE_SUBSCRIBER            0x04 /* subscriber number             */
#define N_TYPE_LOCAL                 0x04 /* AT5 local (directory) number  */
#define N_TYPE_ABBREVIATED           0x06 /* abbreviated number            */

/*--------------------------------------------------------------------------
 *	calling, called, redirecting number plan 
 *-------------------------------------------------------------------------*/
/* in outgoing messages 0xff in this field will be translated to 0 in the 
   actual IE, if no value is set for this field, the stack will insert a 
   default value based on the variant.
   If the stack receives a 0 in this field in an incoming IE, it sends a
   0xff to the application                                                 */
#define N_PLAN_UNKNOWN               0xff /* unknown                       */
#define N_PLAN_ISDN                  0x01 /* ISDN/telephony numbering plan */
                                          /* (CCITT E.164/E.163)           */
#define N_PLAN_TELEPHONE             0x02 /* telephony - not in CEPT       */
#define N_PLAN_DATA                  0x03 /* data n. plan (CCITT X.121)    */
#define N_PLAN_TELEX                 0x04 /* telex n. plan (CCITT F.69)    */
#define N_PLAN_NATIONAL              0x08 /* national std numbering plan   */
#define N_PLAN_PRIVATE               0x09 /* private numbering plan        */

/*--------------------------------------------------------------------------
 *	calling and redirecting number screening indicator 
 *-------------------------------------------------------------------------*/
/* in outgoing messages 0xff in this field will be translated to 0 in the 
   actual IE, if no value is set for this field, the stack will insert a 
   default value based on the variant.
   If the stack receives a 0 in this field in an incoming IE, it sends a
   0xff to the application                                                 */
#define N_SCREEN_USER_PROVIDED       0xff /* user-provided, not screened   */
#define N_SCREEN_USER_PASSED         0x01 /* user-provided, verified and   */
                                          /* passed                        */
#define N_SCREEN_USER_FAILED         0x02 /* user-provided, verified and   */
                                          /* failed                        */
#define N_SCREEN_NETWORK_PROVIDED    0x03 /* network provided              */
 
/*--------------------------------------------------------------------------
 *	redirecting reason 
 *-------------------------------------------------------------------------*/
/* in outgoing messages 0xff in this field will be translated to 0 in the 
   actual IE, if no value is set for this field, the stack will insert a 
   default value based on the variant.
   If the stack receives a 0 in this field in an incoming IE, it sends a
   0xff to the application                                                 */
#define REASON_UNKNOWN                       0xff	/* unknown             */
#define REASON_CALL_FORWARDING_BUSY          0x01	/* call forwarding     */
                                                    /* busy                */
#define REASON_CALL_FORWARDING_NO_REPLY      0x02	/* call forwarding no  */
                                                    /* reply               */
#define REASON_CALL_FORWARDING_DTE_OUT       0x09	/* call forwarding DTE */
                                                    /* out of order        */
#define REASON_CALL_FORWARDING_BY_CALLED     0x0a	/* call forwarding by  */
                                                    /* called equipment    */
#define REASON_CALL_TRANSFER                 0x0d	/* call transfer       */
#define REASON_CALL_PICKUP                   0x0e	/* call pickup         */
#define REASON_CALL_FORWARDING_UNCONDITIONAL 0x0f	/* call forwarding     */
                                                    /* unconditional       */

/*--------------------------------------------------------------------------
 *	subaddress type
 *-------------------------------------------------------------------------*/
#define SUBADDRESS_TYPE_NSAP         0x00 /* NSAP                          */
#define SUBADDRESS_TYPE_USER         0x02 /* User specified                */

/*--------------------------------------------------------------------------
 *	subaddress odd/even indicator
 *-------------------------------------------------------------------------*/
#define SUBADDRESS_ODD               0x01 /* odd number of address signals */
#define SUBADDRESS_EVEN              0x00 /* even number of addr. signals  */

/*--------------------------------------------------------------------------
 *	Progress message description
 *-------------------------------------------------------------------------*/

#define NO_PROGRESS_DESCR                  0x00 /* no progress info        */
#define PROGRESS_DESCR_NON_END_TO_END_ISDN 0x01 /* call is not end-to-end  */
                                                /* ISDN                    */
#define PROGRESS_DESCR_NON_ISDN_DEST       0x02 /* destination address is  */
                                                /* non-ISDN                */
#define PROGRESS_DESCR_NON_ISDN_ORIG       0x03 /* origination address is  */
                                                /* non-ISDN                */
#define PROGRESS_DESCR_CALL_RETURNED_ISDN  0x04 /* call returned to ISDN   */
#define PROGRESS_DESCR_SERVICE_CHANGE      0x05 /* interworking has        */
                                                /* occurred and resulted   */
                                                /* in a telecommunication  */
                                                /* service change          */
#define PROGRESS_DESCR_IN_BAND_NOW         0x08 /* in-band information or  */
                                                /* appropriate pattern     */
                                                /* now available           */
#define PROGRESS_DESCR_DELAY_AT_CALLED     0x0a /* DMS100 - delay in       */
                                                /* response at called      */
                                                /* interface               */

/*--------------------------------------------------------------------------
 *	location 
 *-------------------------------------------------------------------------*/
/* in outgoing messages 0xff in this field will be translated to 0 in the 
   actual IE, if no value is set for this field, the stack will insert a 
   default value based on the variant.
   If the stack receives a 0 in this field in an incoming IE, it sends a
   0xff to the application                                                 */
#define LOC_USER                     0xff /* user						   */
#define LOC_PR_LOCAL_USER            0x01 /* private network serving the   */
                                          /* local user                    */
#define LOC_NETWORK                  0x02 /* location network (SWD)        */
#define LOC_TRANSIT_NET              0x03 /* transit network               */
#define LOC_PU_REMOTE_USER           0x04 /* public network serving the    */
                                          /* remote user                   */
#define LOC_PR_REMOTE_USER           0x05 /* private network serving the   */
                                          /* remote user                   */
#define	LOC_PSTN                     0x06 /* internetworking with the PSTN */
#define	LOC_INTERNATIONAL_NET        0x07 /* international network         */
#define BEYOND_IWP                   0x0a /* network beyond interworking   */
                                          /* point                         */

/*--------------------------------------------------------------------------
 *	UUI protocol discriminator:
 *-------------------------------------------------------------------------*/
/* in outgoing messages 0xff in this field will be translated to 0 in the 
   actual IE, if no value is set for this field, the stack will insert a 
   default value based on the variant.
   If the stack receives a 0 in this field in an incoming IE, it sends a
   0xff to the application                                                 */
#define UUI_USER_SPF                 0xff /* User specific coding          */
#define UUI_OSI                      0x01 /* OSI                           */
#define UUI_X244                     0x02 /* rec. X.244                    */
#define UUI_SYSTEM_MANAGEMENT        0x03 /* reserved for system management*/
                                          /* convergence function          */
#define UUI_IA5                      0x04 /* IA5 characters (ASCII)        */
#define UUI_V120                     0x07 /* rec. V.120                    */
#define UUI_Q931                     0x08 /* rec. Q.931                    */

/*--------------------------------------------------------------------------
 *	pcs_user protocol discriminator (first byte of the pcs_user string)
 *-------------------------------------------------------------------------*/

#define PCS_USER_TRANSGROUP          0x44 /* Transgroupe                   */
#define PCS_USER_PUBLIPHONE          0x45 /* Publiphone                    */
#define PCS_USER_CALL_ROUTING        0x46 /* Call-routing                  */

/*--------------------------------------------------------------------------
 *	Signal values 
 *-------------------------------------------------------------------------*/

#define ACUDIAL_ON                   0x00 /* dial tone on                  */
#define ACURING_BACK_ON              0x01 /* ring back tone on             */
#define ACUNET_CONGEST_ON            0x03 /* network congest tone on       */
#define ACUBUSY_ON                   0x04 /* busy tone on                  */
#define ACUTONES_OFF                 0x3f /* tones off                     */
#define ACUALERTING_OFF              0x4f /* alerting off                  */
#define	ACUCREDIT_CARD_TONE_ON       0x40 /* credit card tone ON           */
#define	ACUOUT_OF_RANGE_TONE_ON      0x41 /* out of range tone ON          */
#define	ACUQUEUING_TONE_ON           0x42 /* queuing tone ON               */
#define	ACUAUDIBLE_TONE_ON           0x44 /* audible tone ON               */
#define	ACUVISUAL_ALERT_1_ON         0x45 /* visual alert #1 ON            */
#define	ACUVISUAL_ALERT_2_ON         0x46 /* visual alert #2 ON            */
#define	ACUSATCOM_CALL_NOTIFY        0x47 /* SATCOM call notify            */

/*--------------------------------------------------------------------------
 *	Notify description 
 *-------------------------------------------------------------------------*/

#define	NO_DESCRIPTION				 0xFF /* Empty field                   */
#define	USER_SUSPENDED				 0x00 /* User suspended                */
#define	USER_RESUMED				 0x01 /* User resumed                  */
#define	BEARER_CHANGE				 0x02 /* bearer service change         */

/*--------------------------------------------------------------------------
 *	SPF facility Id 
 *-------------------------------------------------------------------------*/

#define SPF_FAC_ABSENT				 0xff /* No SPF FAC                    */
#define SPF_FAC_GES_PRIV_NET_SELECT	 0x00 /* GES private network selection */
#define SPF_FAC_GES_SPECIAL_SERVICE	 0x01 /* GES special services          */
#define SPF_FAC_GES_SELECTION		 0x03 /* GES selection                 */

/*--------------------------------------------------------------------------
 *	Network Specific Facilities
 *  the values are variant specific
 *-------------------------------------------------------------------------*/
/* serv_feature */

#define AT4_FAC_FEATURE			0	/* Feature */
#define AT4_FAC_SERVICE			1	/* Sewrvice */

/* facility coding */
/* Feature */
#define AT4_FAC_CPN_SID_PREFERRED	0x01	/* CPN (SID) preferred */
#define AT4_FAC_BN_ANI_PREFERRED	0x02	/* BN (ANI) preferred */
#define AT4_FAC_CPN_SID_ONLY		0x03	/* CPN (SID) only */
#define AT4_FAC_BN_ANI_ONLY		0x04	/* BN (ANI) only */
#define AT4_FAC_CALL_ASSOC_TSC		0x09	/* Call associated TSC */
#define AT4_FAC_TSC_CLEAR_RU		0x0a	/* Notification of call associated TSC clearing or resource unavailable */
#define AT4_FAC_OPERATOR		0x05	/* Operator */
#define AT4_FAC_PCCO			0x06	/* Pre-subscribed Common Carrier Operator */

/* Service */
#define AT4_FAC_SDN			0x01	/* SDN including GSDN */
#define AT4_FAC_MEGACOM_800		0x02	/* Acces to MEGACOM 800 */
#define AT4_FAC_MEGACOM			0x03	/* Acces to MEGACOM */
#define AT4_FAC_ACCUNET			0x06	/* ACCUNET */
#define AT4_FAC_LONG_DISTANCE		0x07	/* International long distance */
#define AT4_FAC_INTERNATIONAL_800	0x08	/* International 800 */
#define AT4_FAC_ATT_MULTIQUEST		0x10	/* AT&T MultiQuest */
