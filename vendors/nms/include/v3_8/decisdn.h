/*****************************************************************************
*  FILE: decisdn.h
*
*    contains useful defines to decode and build Q.931 messages
*    NOTE: for some switch variants some of the values here defined might be
*    not acceptable.
*
* Copyright 1998 Natural MicroSystems Corporation.
*****************************************************************************/
#ifndef DECISDN_INCLUDED
#define DECISDN_INCLUDED

/* ISDN include files */

#include "isdntype.h"
#include "isdnacu.h"

/******************************************************************************
   protocol discriminator 
******************************************************************************/
  #define PD_Q931_MNT            0x03    /* Q.931 Maintenance */
  #define PD_Q931_CC             0x08    /* Q.931 Call Control */

/******************************************************************************
   message types   
******************************************************************************/
  /* escape to nationally specific message type */
  #define MSG_ESCAPE            0x00 /* Q.931 */

  /* call establishment messages */
  #define MSG_ALERTING          0x01 /* Q.931 */
  #define MSG_CALL_PROC         0x02 /* Q.931 */
  #define MSG_PROGRESS          0x03 /* Q.931 */
  #define MSG_SETUP             0x05 /* Q.931 */
  #define MSG_CONNECT           0x07 /* Q.931 */
  #define MSG_SETUP_ACK         0x0d /* Q.931 */
  #define MSG_CONNECT_ACK       0x0f /* Q.931 */

  /* call information phase messages */
  #define MSG_USER_INFO         0x20 /* Q.931 */
  #define MSG_SUSPEND_REJ       0x21 /* Q.931 */
  #define MSG_RESUME_REJ        0x22 /* Q.931 */
  #define MSG_HOLD              0x24 /* Q.932 */
  #define MSG_SUSPEND           0x25 /* Q.931 */
  #define MSG_RESUME            0x26 /* Q.931 */
  #define MSG_HOLD_ACK          0x28 /* Q.932 */
  #define MSG_SUSPEND_ACK       0x2d /* Q.931 */
  #define MSG_RESUME_ACK        0x2e /* Q.931 */
  #define MSG_HOLD_REJ          0x30 /* Q.932 */
  #define MSG_RETRIEVE          0x31 /* Q.932 */
  #define MSG_RETRIEVE_ACK      0x33 /* Q.932 */
  #define MSG_RETRIEVE_REJ      0x37 /* Q.932 */

  /* call clearing messages */
  #define MSG_DISCONNECT        0x45 /* Q.931 */
  #define MSG_RESTART           0x46 /* Q.931 */
  #define MSG_RELEASE           0x4d /* Q.931 */
  #define MSG_RESTART_ACK       0x4e /* Q.931 */
  #define MSG_RELEASE_COMP      0x5a /* Q.931 */

  /* miscellaneous messages */
  #define MSG_SEGMENT           0x60 /* Q.931 */
  #define MSG_FACILITY          0x62 /* Q.931 */
  #define MSG_REGISTER          0x34 /* Q.932 */
  #define MSG_NOTIFY            0x6e /* Q.931 */
  #define MSG_STATUS_ENQ        0x75 /* Q.931 */
  #define MSG_CONGESTION_CTRL   0x79 /* Q.931 */
  #define MSG_INFO              0x7b /* Q.931 */
  #define MSG_STATUS            0x7d /* Q.931 */

  /* messages not defined in Q.931/Q.932 */
  #define MSG_SERVICE           0x0f /* according with 235-900-342 (5ESS) */
  #define MSG_SERVICE_ACK       0x07 /* according with 235-900-342 (5ESS) */

/******************************************************************************
   information elements identifiers
******************************************************************************/
  /* single octect information elements */
  #define IE_SHIFT              0x90    /* all values from 0x90 to 0x9f 
                                           indicate "shift" */
  #define IE_MORE_DATA          0xa0    /* more data */
  #define IE_SENDING_COMPL      0xa1    /* sending complete */
  #define IE_CONG_LEVEL         0xb0    /* all values from 0xb0 to 0xbf 
                                           indicate "congestion level" */
  #define IE_REPEAT_IND         0xd0    /* all values from 0xd0 to 0xdf 
                                           indicate "repeat indicator" */

  /* variable length information elements */
  #define IE_SEGMENTED          0x00    /* segmented message */
  #define IE_BC                 0x04    /* bearer capability */
  #define IE_CAUSE              0x08    /* cause */
  #define IE_CALL_ID            0x10    /* call identity */
  #define IE_CALL_STATE         0x14    /* call state */
  #define IE_CHANNEL_ID         0x18    /* channel identification */
  #define IE_FACILITY           0x1c    /* facility */
  #define IE_PROGRESS_IND       0x1e    /* progress indicator */
  #define IE_NSF                0x20    /* network-specific facilities */
  #define IE_NOTIFY_IND         0x27    /* notification indicator */
  #define IE_DISPLAY            0x28    /* display */
  #define IE_DATE_TIME          0x29    /* date/time */
  #define IE_KEYPAD             0x2c    /* keypad facility */
  #define IE_INFO_RQ            0x32    /* information request */
  #define IE_SIGNAL             0x34    /* signal */
  #define IE_SWITCHHOOK         0x36    /* switchhook */
  #define IE_FEATURE_ACK        0x38    /* feature activation */
  #define IE_FEATURE_IND        0x39    /* feature indication */
  #define IE_SERVICE_PROF       0x3a    /* service profile identification */
  #define IE_ENDPOINT_ID        0x3b    /* endpoint identifier */
  #define IE_INFO_RATE          0x40    /* information rate */
  #define IE_END_TO_END_DELAY   0x42    /* end to end transit delay */
  #define IE_TDSI               0x43    /* transit delay selection and indication */
  #define IE_PKT_BIN_PAR        0x44    /* packet layer binary parameters */
  #define IE_PKT_WIN_SIZE       0x45    /* packet layer window size */
  #define IE_PKT_SIZE           0x46    /* packet size */
  #define IE_MIN_THR_CLASS      0x47    /* minimum throughput class */
  #define IE_CALLING            0x6c    /* calling party number */
  #define IE_CALLING_SUB        0x6d    /* calling party subaddress */
  #define IE_CALLED             0x70    /* called party number */
  #define IE_CALLED_SUB         0x71    /* called party subaddress */
  #define IE_REDIRECTING        0x74    /* redirecting number */
  #define IE_TRANSIT_SEL        0x78    /* transit network selection */
  #define IE_REST_IND           0x79    /* restart indicator */
  #define IE_LLC                0x7c    /* low layer compatibility */
  #define IE_HLC                0x7d    /* high layer compatibility */
  #define IE_UUI                0x7e    /* user-user info */
  #define IE_ESCAPE             0xff    /* escape for extension */

  /* information elements not defined in Q.931/Q.932 */
  #define IE_CHANGE_STATUS      0x01    /* change status according with 
                                           235-900-342 (5ESS) */
/******************************************************************************
   information element contents 
******************************************************************************/
  
  /* cause */
  #define CAU_UNALL             0x01    /* unallocated number */
  #define CAU_NOR_STN           0x02    /* no route to transit network */
  #define CAU_NOR_D             0x03    /* no route to destination */
  #define CAU_CH_UNACC          0x06    /* channel unnacceptable */
  #define CAU_AWARD             0x07    /* call awarded and delivered in an est. ch. */
  #define CAU_NORMAL_CC         0x10    /* normal call clearing */
  #define CAU_BUSY              0x11    /* user busy */
  #define CAU_NO_USER_RES       0x12    /* no user responding */
  #define CAU_NO_ANSW           0x13    /* no answer from user */
  #define CAU_REJ               0x15    /* call rejected */
  #define CAU_NUM_CHANGED       0x16    /* number changed */
  #define CAU_NON_SEL           0x1a    /* non-selected user clearing */
  #define CAU_DEST_OOF          0x1b    /* destination out of order */
  #define CAU_INV               0x1c    /* invalid number format */
  #define CAU_FAC_REJ           0x1d    /* facility rejected */
  #define CAU_RES_TO_SE         0x1e    /* response to STATUS ENQUIRY */
  #define CAU_NORMAL_UNSPEC     0x1f    /* normal, unspecified */
/*--------------------------------------------------------------------------*/
  #define CAU_NO_CIRC_CHAN      0x22    /* no circuit/channel available */
  #define CAU_NET_OOF           0x26    /* network out of order */
  #define CAU_TEMP_FAIL         0x29    /* temporary failure */
  #define CAU_CONG              0x2a    /* switching equipment congestion */
  #define CAU_ACC_INF_DISC      0x2b    /* access information discarded */
  #define CAU_NOT_AVAIL         0x2c    /* requested circuit/channel not available */
  #define CAU_RES_UNAVAIL       0x2f    /* resource unavailable */
/*--------------------------------------------------------------------------*/
  #define CAU_QOF_UNAVAIL       0x31    /* quality of service unavailable */
  #define CAU_FAC_NOT_SUB       0x32    /* requested facility not subscribed */
  #define CAU_BC_NOT_AUT        0x39    /* bearer capability not authorized */
  #define CAU_BC_NOT_AVAIL      0x3a    /* bearer capability not presently available */
  #define CAU_SERV_NOTAVAIL     0x3f    /* service or option not available */
/*--------------------------------------------------------------------------*/
  #define CAU_BC_NOT_IMP        0x41    /* bearer capability not implemented */
  #define CAU_CHT_NOT_IMP       0x42    /* channel type not implemented */
  #define CAU_FAC_NOT_IMP       0x45    /* requested facility non implemented */
  #define CAU_RESTR_BC          0x46    /* only restricted digital bearer cap. is available */
  #define CAU_SERV_NOT_IMP      0x4f    /* service or option not implemented */
/*--------------------------------------------------------------------------*/
  #define CAU_INV_CRV           0x51    /* invalid call reference value */
  #define CAU_CH_NOT_EX         0x52    /* identified channel does not exist */
  #define CAU_CALL_ID_NOT_EX    0x53    /* call identity does not exist */
  #define CAU_CALL_ID_IN_USE    0x54    /* call identity in use */
  #define CAU_NO_CALL_SUSP      0x55    /* no call suspended */
  #define CAU_CALL_CLEARED      0x56    /* the call has been cleared */
  #define CAU_INCOMP_DEST       0x58    /* incompatible destination */
  #define CAU_INV_TN            0x5b    /* invalid transit network selection */
  #define CAU_INV_MSG           0x5f    /* invalid message */
/*--------------------------------------------------------------------------*/
  #define CAU_MAND_IE_MISSING   0x60    /* mandatory information element is missing */
  #define CAU_MSGT_NOT_EX       0x61    /* message type not existent/implemented */
  #define CAU_MSG_NOT_COMP      0x62    /* msg not compatible with call state or msg type not existent */
  #define CAU_IE_NOT_EX         0x63    /* information element not existent/implemented */
  #define CAU_INV_IE_CONTENTS   0x64    /* invalid information element contents */
  #define CAU_MSG_NOT_COMP_CS   0x65    /* message not compatible with call state */
  #define CAU_RECOVERY          0x66    /* recovery on timer expiry */
  #define CAU_PROTO_ERR         0x6f    /* protocol error */
/*--------------------------------------------------------------------------*/
  #define CAU_INTERW            0x7f    /* interworking */
/*--------------------------------------------------------------------------*/
  /* the following cause values are defined in the 4ESS, 5ESS and DMS specs
       the ETS and NI2 specs do not add any value to the Q.931 specs */
  #define CAU_PREEMPTION        0x08    /* preemption (5ESS) */
  #define CAU_PREEMPTION_CRR    0x09    /* preemption, circuit reserved for reuse (5ESS) */
  #define CAU_PREC_CALL_BLK     0x2e    /* precedence call blocked (5ESS) */
  #define CAU_BC_INCOMP_SERV    0x33    /* bearer capability incompatible with service request (5ESS) */
  #define CAU_OUT_CALLS_BARRED  0x34    /* outgoing calls barred (4ESS,5ESS) */
  #define CAU_SERV_VIOLATED     0x35    /* service operation violated (5ESS) */
  #define CAU_IN_CALLS_BARRED   0x3b    /* incoming calls barred (DMS,4ESS,5ESS) */
  #define CAU_DEST_ADD_MISSING  0x5a    /* destination address missing and direct call not subscribed (DMS) */

/*--------------------------------------------------------------------------*/
  /* the following cause values are created internally by the ISDN stack */
  #define CAU_RESTART           0xb1    /* call clearing due to restart procedure */

  #define CAU_TIMER_300         0x80    /* call clearing due to internal timer 300 expiration */
  #define CAU_TIMER_302         0x82    /* call clearing due to internal timer 302 expiration */
  #define CAU_TIMER_303         0x83    /* call clearing due to internal timer 303 expiration */
  #define CAU_TIMER_304         0x84    /* call clearing due to internal timer 304 expiration */
  #define CAU_TIMER_308         0x88    /* call clearing due to internal timer 308 expiration */
  #define CAU_TIMER_309         0x89    /* call clearing due to internal timer 309 expiration */
  #define CAU_TIMER_310         0x8a    /* call clearing due to internal timer 310 expiration */
  #define CAU_TIMER_316         0x8b    /* call clearing due to internal timer 316 expiration */
  #define CAU_TIMER_317         0x8c    /* call clearing due to internal timer 317 expiration */
  #define CAU_TIMER_318         0x8d    /* call clearing due to internal timer 318 expiration */
  #define CAU_TIMER_319         0x8e    /* call clearing due to internal timer 319 expiration */
  #define CAU_TIMER_399         0x8f    /* call clearing due to internal timer 399 expiration */

  /* class */
  #define CLA_CHAN              0x00    /* indicated channels (in channel id IE ) */
  #define CLA_INT               0x06    /* sigle interface */
  #define CLA_ALL               0x07    /* all interfaces */

  /* class ( for facility IE ) */
  #define CLA_F_UN              0x00    /* universal */
  #define CLA_F_CS              0x80    /* context specific */

  /* coding standard */
  #define CS_CCITT              0x00    /* CCITT */
  #define CS_RES                0x20    /* reserved for other standards */
  #define CS_NTL                0x40    /* national */
  #define CS_DEF                0x60    /* defined for the network on the other side */

  /* call state */
  #define CST_NULL              0x00    /* null */
  #define CST_CALL_INI          0x01    /* call initiated */
  #define CST_OVL_SND           0x02    /* overlap sending */
  #define CST_OUT_PROC          0x03    /* outgoing call proceeding */
  #define CST_CALL_DEL          0x04    /* call delivered */
  #define CST_CALL_PRES         0x06    /* call present */
  #define CST_CALL_RCV          0x07    /* call received */
  #define CST_CONN_RQ           0x08    /* connect request */
  #define CST_IN_CALL_PROC      0x09    /* incoming call proceeding */
  #define CST_ACTIVE            0x0a    /* active */
  #define CST_DISC_RQ           0x0b    /* disconnect request */
  #define CST_DISC_IN           0x0c    /* disconnect indication */
  #define CST_SUSP_RQ           0x0f    /* suspend request */
  #define CST_RES_RQ            0x11    /* resume request */
  #define CST_REL_RQ            0x13    /* release request */
  #define CST_CALL_ABORT        0x16    /* call abort */
  #define CST_OVL_RCV           0x19    /* overlap receiving */

  /* channel type */
  #define CHT_B                 0x03    /* B channel */
  #define CHT_H0                0x06    /* H0 channel */
  #define CHT_H11               0x08    /* H11 channel */
  #define CHT_H12               0x09    /* H12 channel */

  /* component tag */
  #define CT_INV                0x01    /* invoke */
  #define CT_RETRES             0x02    /* return result */
  #define CT_RETERR             0x03    /* return error */
  #define CT_REJ                0x04    /* reject */

  /* id tag ( for facility IE ) */
  #define ID_TAG_INVOKE         0x02    /* invoke identifier tag */
  #define ID_TAG_OP_VAL_INT     0x02    /* operation value tag, integer */
  #define ID_TAG_OP_OCTET_STRING 0x04   /* operation value tag, octet string */
  #define ID_TAG_OP_VAL_OBJ_ID  0x06    /* operation value tag, object 
                                           identifier */
  #define ID_TAG_SEQUENCE       0x10    /* sequence tag */
  #define ID_TAG_SET            0x11    /* set tag */
  #define ID_TAG_SERVICE        0x01    /* service tag */
  #define ID_TAG_PREF           0x02    /* preferred tag */
  #define ID_TAG_ERROR_VAL_INT  0x02    /* error value tag, integer */
  #define ID_TAG_ERROR_VAL_OBJ_ID 0x06  /* error value tag, object identifier */
  #define ID_TAG_LINKED         0x80    /* linked identifier data element */
  #define ID_TAG_GENERAL_RROBLEM 0x80   /* general problem */
  #define ID_TAG_INVOKE_RROBLEM 0x81    /* invoke problem */
  #define ID_TAG_RETRES_RROBLEM 0x82    /* return result problem */
  #define ID_TAG_RETERR_RROBLEM 0x83    /* return error problem */

  /* D-channel ind */
  #define DCI_NOT               0x00    /* not */
  #define DCI_YES               0x04    /* yes */

  /* FORM */
  #define FRM_PRIMITIVE         0x00    /* primitive */
  #define FRM_CONST             0x20    /* constructor */

  /* global interface state */
  #define GLOB_REST0            0x00    /* null */
  #define GLOB_REST1            0x3d    /* restart request */
  #define GLOB_REST2            0x3e    /* restart */
  
  /* high layer characteristics id */
  #define HLC_TEL               0x01    /* telephony */
  #define HLC_FAX4              0x04    /* fax group 4 */
  #define HLC_DAPG4             0x21    /* doc. app. prof. group 4  */
  #define HLC_DAPMM             0x24    /* doc. app. prof. mixed-mode */
  #define HLC_DAPPF             0x28    /* doc. app. prof. processable form */
  #define HLC_TELETEXT          0x31    /* teletext */
  #define HLC_DAPV              0x32    /* doc. app. prof. videotext */
  #define HLC_TELEX             0x35    /* telex */
  #define HLC_MHS               0x38    /* message handling system */
  #define HLC_OSI               0x41    /* OSI application */
  #define HLC_RES_MAINT         0x5e    /* reserved for maintenance */
  #define HLC_RES_MNG           0x5f    /* reserved for management */

  /* info channel selection */
  #define ICS_NO                0x00    /* no channel */
  #define ICS_B1                0x01    /* B1 */
  #define ICS_B2                0x02    /* B2 */
  #define ICS_ANY               0x03    /* any channel */

  /* inteface identifier */
  #define IID_IMPL              0x00    /* implicitly identified */
  #define IID_EXPL              0x40    /* explicitly identified */

  /* interpretation */
  #define INT_FIRST             0x10    /* first HLC to be used in the call */

  /* inteface type */
  #define IT_BASIC              0x00    /* basic */
  #define IT_OTHER              0x20    /* PRI */
  
  /* information transfer capability */
  #define ITC_SPEECH            0x00    /* speech */
  #define ITC_UDI               0x08    /* unrestricted digital info */
  #define ITC_RDI               0x09    /* restricted digital info */
  #define ITC_31K               0x10    /* 3.1 Khz audio */
  #define ITC_7K                0x11    /* 7 Khz audio */
  #define ITC_VIDEO             0x18    /* video */
 
  /* information transfer rate */
  #define ITR_PKT               0x00    /* code for packet mode */
  #define ITR_64K               0x10    /* 64 Kbit/s */
  #define ITR_2X64K             0x11    /* 2*64 Kbit/s */
  #define ITR_384K              0x13    /* 384 Kbit/s */
  #define ITR_1536K             0x15    /* 1536 Kbit/s */
  #define ITR_1920K             0x17    /* 1920 Kbit/s */

  /* location */
  #define LOC_USR               0x00    /* user */
  #define LOC_PRI_LOC           0x01    /* private network serving local user */
  #define LOC_PUB_LOC           0x02    /* public network serving local user */
  #define LOC_TN                0x03    /* transit network */
  #define LOC_PUB_REM           0x04    /* public network serving remote user */
  #define LOC_PRI_REM           0x05    /* private network serving remote user */
  #define LOC_INTL              0x07    /* international network */
  #define LOC_NBIP              0x0a    /* network beyond interworking point */

  /* new status ( according with 235-900-342 (5ESS) ) */
  #define NEW_STAT_IS           0x00    /* in service */
  #define NEW_STAT_MNT          0x01    /* maintenance */
  #define NEW_STAT_OOS          0x02    /* out of service */

  /* negotiation indicator */
  #define NI_NEG_NOT_POSS       0x00    /* out-band negotiation not possible */
  #define NI_NEG_POSS           0x20    /* out-band negotiation possible */

  /* network identification plan */
  #define NIP_UNKNOWN           0x00    /* unknown */
  #define NIP_CIC               0x01    /* carrier identification code */
  #define NIP_DNIC              0x03    /* data network identification code */

  /* number/map */
  #define NM_NUMB               0x00    /* number */
  #define NM_MAP                0x10    /* map */
  
  /* numbering plan */
  #define NP_UNKNOWN            0x00    /* unknown */
  #define NP_ISDN               0x01    /* ISDN */
  #define NP_DATA               0x03    /* data */
  #define NP_TELEX              0x04    /* telex */
  #define NP_NTL                0x08    /* national */
  #define NP_PRIVATE            0x09    /* private */
  #define NP_RES                0x0f    /* reserved for extension */
  
  /* odd/even indicator */
  #define OE_EVEN               0x00    /* even number of address signals */
  #define OE_ODD                0x08    /* odd number of address signals */

  /* protocol discriminator (in UUI IE) */
  #define PD_UUS                0x00    /* user-user specific */
  #define PD_OSI                0x01    /* OSI */
  #define PD_X244               0x02    /* X.244 */
  #define PD_SM                 0x03    /* system management */
  #define PD_IA5                0x04    /* IA5 */
  #define PD_V120               0x07    /* V.120 */
  #define PD_Q931               0x08    /* Q.931 user-network message */

  /* pref/excl */
  #define PE_PREF               0x00    /* preferred */
  #define PE_EXCL               0x08    /* exclusive */
  
  /* presentation ind */
  #define PI_ALLOWED            0x00    /* allowed */
  #define PI_RESTRICTED         0x20    /* restricted */
  #define PI_NOT_AVAIL          0x40    /* number not available */
  
  /* presentation method */
  #define PM_HLPP               0x01    /* high layer protocol profile */

  /* progress description */
  #define PRD_NOT_ISDN          0x01    /* call is not end-to-end ISDN */
  #define PRD_DEST_NOT_ISDN     0x02    /* destination address is non-ISDN */
  #define PRD_ORIG_NOT_ISDN     0x03    /* origination address is non-ISDN */
  #define PRD_RET_ISDN          0x04    /* call has returned to ISDN */
  #define PRD_IN_BAND           0x08    /* in-band info is now available */

  /* preference ( according with 235-900-342 (5ESS)  ) */
  #define PREF_INTERFACE        0x00    /* all interface */
  #define PREF_CHANNEL          0x40    /* channel */
  
  /* reccomendation */
  #define REC_Q931              0x00    /* Q.931 */
  #define REC_X21               0x03    /* X.21 */
  #define REC_X25               0x04    /* X.25 */

  /* reason for redirection */
  #define RR_CFB                0x01    /* call forwarding busy */
  #define RR_CFNR               0x02    /* call forwarding no reply */
  #define RR_DTEOO              0x09    /* called DTE out of order */
  #define RR_CFU                0x0f    /* call forwarding unconditional */
  #define RR_CFBYDTE            0x0a    /* call forwarding by the called DTE */
    
  /* service discriminator */
  #define SD_SSA                0x11    /* supplementary service applications */
  
  /* screening ind */
  #define SI_UP_NS              0x00    /* user provided, not screened */
  #define SI_UP_VP              0x01    /* user provided, verified and passed */
  #define SI_UP_VF              0x02    /* user provided, verified and failed */
  #define SI_NP                 0x03    /* network provided */
  
  /* transfer mode */
  #define TM_CIRCUIT            0x00    /* circuit mode */
  #define TM_PKT                0x40    /* packet mode */

  /* type of network identification */
  #define TOI_USER              0x00    /* user specified */
  #define TOI_NTL               0x20    /* national */
  #define TOI_INTL              0x30    /* international */

  /* type of number */
  #define TON_UNKNOWN           0x00    /* unknown */
  #define TON_INTL              0x10    /* international */
  #define TON_NTL               0x20    /* national */
  #define TON_NET               0x30    /* network specific */
  #define TON_SUB               0x40    /* subscriber */
  #define TON_ABB               0x60    /* abbreviated */
  #define TON_RES               0x70    /* reserved for extension */

  /* type of subaddress */
  #define TOS_NSAP              0x00    /* NSAP */
  #define TOS_USER              0x20    /* user specified */

  /* user info layer 1 */
  #define UIL1_CCITT            0x01    /* CCITT V.110/X.30*/
  #define UIL1_MULAW            0x02    /* mu law */
  #define UIL1_ALAW             0x03    /* A law */
  #define UIL1_G721             0x04    /* G.721 */
  #define UIL1_G722             0x05    /* G.722 */
  #define UIL1_H261             0x06    /* H.261 */
  #define UIL1_NOCCITT          0x07    /* non CCITT */
  #define UIL1_V120             0x08    /* CCITT V.120 */
  #define UIL1_X31              0x09    /* CCITT X.31 */

  /* notification description */

  #define USER_SUSPENDED        0x00    /* user suspended */
  #define USER_RESUMED          0x01    /* user resumed */
  #define CALL_FORWARDED        0x08    /* call forwarded */
  #define BEARER_SERVICE_CHANGE 0x02    /* bearer service change */
  
  #define EXTENDED_DESCRIPTION  0x03    /* discriminator for notification 
                                           extension */
  #define EXT_ISO_ASN1_NOTIF_DATA 0x70  /* discriminator for extension to ISO 
                                           defined ASN.1 encoded notification 
                                           data structure (QSIG) */
  
/******************************************************************************
        Q.921 defines
******************************************************************************/

  #define  Q921_RR              0x01
  #define  Q921_SABME           0x7f
  #define  Q921_UA              0x73
  #define  Q921_DISC            0x53
  #define  Q921_RNR             0x05
  #define  Q921_DM              0x1f
  #define  Q921_REJ             0x09
  #define  Q921_UI		0x03	
  #define  Q921_BROADCAST 0xff	
  #define  Q921_TEI_MGT 0x0f	

#endif

