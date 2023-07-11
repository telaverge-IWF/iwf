/**************************************************************************
 **
 **			   				PROPRIETARY NOTICE
 **
 **                         Copyright (c) 1997
 **                     By Natural MicroSystems, Inc.
 **
 **
 **  The following is licensed program material and is considered
 **  proprietary and confidential.  No part of this program may be
 **  reproduced or used in any form or by any means without the express
 **  written permission of Natural MicroSystems, Inc.
 **
 **	 This product also contains software that is protected by the
 **  following copyrights.
 **
 **		(c) Copyright 1989-1995, Trillium Digital Systems, Inc.
 *************************************************************************/

#ifndef _ISUPMSGS_H
#define _ISUPMSGS_H

#include "isuptype.h"

/* The following defines are required for compatibility with
 * this version of the ISUP process; do not remove them.
 */
#define SS7_ANS88       1
#define SS7_ANS92    	1

#define MF_SIZE_TKNSTR  132		  /* token string size - regular */

typedef struct tknHdr             /* token header */
{
   Bool pres;                     /* present */
} TknHdr;

typedef struct elmtHdr            /* element header */
{
   Bool pres;                     /* present */
   U8   spare1;                   /* for alignment */
   U16  spare2;                   /* for alignment */
} ElmtHdr;

/* coding for "pres" indicators - type Bool or type U8 */
#define	NOT_PRESENT		0
#define PRESENT			1

/* token typedefs */

typedef struct tknU8              /* token U8 */
{
   U8   pres;                     /* present flag */
   U8   val;                      /* value */
   U16  spare1;                   /* for alignment */
} TknU8;

typedef struct tknU16             /* token U16 */
{
   U8   pres;                     /* present flag */
   U8   spare1;                   /* for alignment */
   U16  val;                      /* value */
} TknU16;

typedef struct tknU32             /* token U32 */
{
   U8   pres;                     /* present flag */
   U8   spare1;                   /* for alignment */
   U16  spare2;                   /* for alignment */
   U32  val;                      /* value */
} TknU32;

typedef struct tknStr             /* token string */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
   U8   val[(MF_SIZE_TKNSTR + 4) & 0xffc]; /* string value */
} TknStr;

/* Message Element Structures */

typedef struct accDelInfo        /* Access delivery information */
{
   ElmtHdr eh;                   /* element header */
   TknU8 delInd;                 /* delivery indicator */
} SiAccDelInfo;

typedef struct parmCom           /* parameter compatibility information */
{
   ElmtHdr eh;                   /* element header */
   TknU8 upgrPar1;               /* upgraded parm 1 */
   TknU8 tranXInd1;              /* transit exchange indicator */
   TknU8 relCllInd1;             /* release call indicator */
   TknU8 sndNotInd1;             /* send notification indicator */
   TknU8 dcrdMsgInd1;            /* discard message indicator */
   TknU8 dcrdParInd1;            /* discard parameter indicator */
#if SS7_Q767IT
   TknU8 passNtPoss1;            /* pass not possible indicator */
#endif
   TknU8 upgrPar2;               /* upgraded parm 2 */
   TknU8 tranXInd2;              /* transit exchange indicator */
   TknU8 relCllInd2;             /* release call indicator */
   TknU8 sndNotInd2;             /* send notification indicator */
   TknU8 dcrdMsgInd2;            /* discard message indicator */
   TknU8 dcrdParInd2;            /* discard parameter indicator */
#if SS7_Q767IT
   TknU8 passNtPoss2;            /* pass not possible indicator */
#endif
   TknU8 upgrPar3;               /* upgraded parm 3 */
   TknU8 tranXInd3;              /* transit exchange indicator */
   TknU8 relCllInd3;             /* release call indicator */
   TknU8 sndNotInd3;             /* send notification indicator */
   TknU8 dcrdMsgInd3;            /* discard message indicator */
   TknU8 dcrdParInd3;            /* discard parameter indicator */
#if SS7_Q767IT
   TknU8 passNtPoss3;            /* pass not possible indicator */
#endif
} SiParmCompInfo;

typedef struct msgCom            /* message compatibility information */
{
   ElmtHdr eh;                   /* element header */
   TknU8 tranXInd;               /* transit exchange indicator */
   TknU8 relCllInd;              /* release call indicator */
   TknU8 sndNotInd;              /* send notification indicator */
   TknU8 dcrdMsgInd;             /* discard message indicator */
   TknU8 passNotPoss;            /* pass on not possible indicator */
   TknU8 tranXInd1;              /* transit exchange indicator */
   TknU8 relCllInd1;             /* release call indicator */
   TknU8 sndNotInd1;             /* send notification indicator */
   TknU8 dcrdMsgInd1;            /* discard message indicator */
   TknU8 passNotPoss1;           /* pass on not possible indicator */
} SiMsgCompInfo;

typedef struct cllDivr           /* call Diversion information */
{
   ElmtHdr eh;                   /* element header */
   TknU8 notSuscr;               /* Notification subscribtion */
   TknU8 redirRsn;               /* redirection reason */
} SiCllDiverInfo;

/* Notification Subscribtion Option */

#define PRES_UNKNOWN       0x00
#define PRES_NOTALLOW      0x01
#define PRES_ALLOWWREDNUM  0x02
#define PRES_ALLOW         0x03

/* see redirInfo for redirRsn values */

typedef struct propDly           /* propagation delay */
{
   ElmtHdr eh;                   /* element header */
   TknU16 delayVal;              /* delay value */
} SiPropDly;

typedef struct redirRstr         /* redirection restriction */
{
   ElmtHdr eh;                   /* element header */
   TknU8 presRest;               /* presentation restriction */
} SiRedirRestr;

/* see calling party number for presentation restriction values */

typedef struct remotOper         /* remote operations */
{
   ElmtHdr eh;                   /* element header */
   TknU8 protProf;               /* protocol profile */
   TknStr compon;                /* components */
} SiRemotOper;

/* Protocol profile  */

#define PP_REMOPPROT       0x11

typedef struct netFac            /* network specific facility */
{
   ElmtHdr eh;                   /* element header */
   TknStr netFac;                /* network facility1 */
} SiNetSpecFacil;

typedef struct mcidRsp           /* MCID response indicators  */
{
   ElmtHdr eh;                   /* element header */
   TknU8 rspInd;                 /* mcid response indicators */
   TknU8 hldInd;                 /* hold indicators */
} SiMcidRspInd;

/* MCID response Indicator */

#define MCID_NOTINCLDD     0x00
#define MCID_INCLDD        0x01

/* Hold provided indicator */

#define HOLD_NOTPROV       0x00
#define HOLD_PROV          0x01

typedef struct mcidReq           /* MCID request indicators  */
{
   ElmtHdr eh;                   /* element header */
   TknU8 reqInd;                 /* mcid request indicators */
   TknU8 hldInd;                 /* hold indicators */
} SiMcidReqInd;

/* MCID request Indicator */

#define MCID_NOTREQD       0x00
#define MCID_REQD          0x01

/* Holding Indicator */

#define HOLD_NOTREQD       0x00
#define HOLD_REQD          0x01

typedef struct mlppPrec          /* MLPP precedence  */
{
   ElmtHdr eh;                   /* element header */
   TknU8 precdLvl;               /* precedence level */
   TknU8 lfb;                    /* LFB */
   TknU8 frstDig;                /* first digit */
   TknU8 scndDig;                /* second digit */
   TknU8 thrdDig;                /* third digit */
   TknU8 frthDig;                /* fourth digit */
   TknU32 servDomain;            /* service domain */
} SiMlppPrec;

/* Precedence level */

#define PL_FLASHORD        0x00
#define PL_FLASH           0x01
#define PL_IMMDT           0x02
#define PL_PRIOR           0x03
#define PL_ROUTINE         0x04

/* LFB */

#define LFB_ALLWD          0x00
#define LFB_PTHRSRVD       0x01
#define LFB_NOTALLWD       0x02

typedef struct accTrnspt         /* Access transport */
{
   ElmtHdr eh;                   /* element header */
   TknStr infoElmts;             /* Information elements */
} SiAccTrnspt;

#if SS7_SINGTEL
typedef struct chrgeInfo         /* Charge Information */
{
   ElmtHdr eh;                   /* element header */
   TknU8 typeCalls;              /* type of calls */
   TknU8 chgeMeth;               /* charging method */
   TknU8 chgePrty;               /* chargeable party */
   TknU8 chgePoint;              /* charge point */
   TknU16 pntCde;                /* point code */
} CllChrgeInfo;

typedef struct rateInfo          /* Charge rate Information */
{
   ElmtHdr eh;                   /* element header */
   TknU8 pktChrgng;              /* packet chagring */
   TknU8 tariffCat;              /* tariff category */
   TknU8 tariffUnit;             /* tariff unit */
   TknU8 tariffFact;             /* tariff factor chagring */
   TknU16 nominalTime;           /* nominal time */
} ChrgeRateInfo;

typedef struct trnkOff           /* trunk offering Information */
{
   ElmtHdr eh;                   /* element header */
   TknU8 trnkOffInfo;            /* trunk offering Information */
} TrnkOff;
#endif

typedef struct autoCongLvl       /* Autonatic Congestion Level */
{
   ElmtHdr eh;                   /* element header */
   TknU8 auCongLvl;              /* auto congestion level */
} SiAutoCongLvl;

/* Automatic Congestion Level Defines */

#define ACLVL_LVL1         0x01
#define ACLVL_LVL2         0x02

typedef struct bckCalInd         /* Backward Call Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 chrgInd;                /* Charge Indicator */
   TknU8 cadPtyStatInd;          /* called party status indicator */
   TknU8 cadPtyCatInd;           /* called party category indicator */
   TknU8 end2EndMethInd;         /* end to end method indicator */
   TknU8 intInd;                 /* interworking indicator */
   TknU8 end2EndInfoInd;         /* end to end information indicator */
   TknU8 isdnUsrPrtInd;          /* ISDN User Part indicator */
   TknU8 holdInd;                /* holding indicator */
   TknU8 isdnAccInd;             /* ISDN access indicator */
   TknU8 echoCtrlDevInd;         /* echo control device indicator */
   TknU8 sccpMethInd;            /* SCCP method indicator */
} SiBckCalInd;

/* Charge Indicator Defines */

#define CHRG_NOIND         0x00
#define CHRG_NOCHRG        0x01
#define CHRG_CHRG          0x02

/* Called Party's Status Defines  */

#define CADSTAT_NOIND      0x00
#define CADSTAT_SUBFREE    0x01
#define CADSTAT_CONNFREE   0x02
#define CADSTAT_DELAY      0x03

/* Called Party's Category Defines */

#define CADCAT_NOIND       0x00
#define CADCAT_ORDSUBS     0x01
#define CADCAT_PAYPHONE    0x02

/* End to end method indicator defines */

#define E2EMTH_NOMETH      0x00
#define E2EMTH_PASSALNG    0x01
#define E2EMTH_SCCPMTH     0x02
#define E2EMTH_BOTH        0x03

/* Interworking Indicator */

#define INTIND_NOINTW      0x00
#define INTIND_INTW        0x01

/* End to end Information Indicator */

#define E2EINF_NOINFO      0x00
#define E2EINF_INFO        0x01

/* ISDN User Part Indicator */

#define ISUP_NOTUSED       0x00
#define ISUP_USED          0x01

/* see MCID req for hold indicator values */

/* ISDN Access Indicator */

#define ISDNACC_NONISDN    0x00
#define ISDNACC_ISDN       0x01

/* Echo Control device indicator */

#define ECHOCDEV_NOTINCL   0x00
#define ECHOCDEV_INCL      0x01

/* SCCP Method Indicator */

#define SCCPMTH_NOIND      0x00
#define SCCPMTH_CONLESS    0x01
#define SCCPMTH_CONORNTD   0x02
#define SCCPMTH_BOTH       0x03

typedef struct calModInd         /* Call Modification Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 modInd;                 /* call modification indicators */
} SiCalModInd;

/* Modification Indicator */

#define MOD_SERV1          0x01
#define MOD_SERV2          0x02

typedef struct callRef           /* Call Reference */
{
   ElmtHdr eh;                   /* element header */
   TknU32 callId;                /* call identity */
   TknU16 pntCde;                /* point code */
} SiCallRef;

#if (SS7_ANS88 || SS7_ANS92)
typedef struct callRefA          /* Call Reference */
{
   ElmtHdr eh;                   /* element header */
   TknU32 callId;                /* call identity */
   TknU32 pntCde;                /* point code */
} SiCallRefA;

#endif
typedef struct cdPtyNum          /* Called Party Number */
{
   ElmtHdr eh;                   /* element header */
   TknU8 natAddrInd;             /* nature of addresss indicator */
   TknU8 oddEven;                /* odd or even */
   TknU8 numPlan;                /* numbering plan */
   TknU8 innInd;                 /* international network number indicator */
   TknStr addrSig;               /* Address Signal */
} SiCdPtyNum;

/* Nature of Address Defines ISUP */

#define SUBSNUM           0x01
#define NATNUM            0x03
#define INTNATNUM         0x04

/* defines for ANSI */

#define SUBSNUMOPREQ       0xe1  /* subscriber number, operator requested */
#define NATNUMOPREQ        0xe2  /* national number, operator requested */
#define INTNATNUMOPREQ     0xe3  /* international number, operator requested */
#define NONUMPRESOPREQ     0xe4  /* no number present, operator requested */
#define NONUMPRESCUTTHRU   0xe5  /* no number present, cut-through call to carrier */
#define TSTLINETSTCODE     0xe7  /* test line test code */

/* Odd - Even Indicator */

#define NMB_EVEN           0
#define NMB_ODD            1

/* numbering plan */

#define NP_UNK         0x00  /* unknown */
#define NP_ISDN        0x01  /* ISDN/telephony numbering - E.164/E.163 */
#define NP_TEL         0x02  /* telephony numbering - E.163 */
#define NP_DATA        0x03  /* data numbering - X.121 */
#define NP_TELEX       0x04  /* telex numbering - Recommendation F.69 */
#define NP_NATIONAL    0x08  /* national standard numbering */
#define NP_PRIVATE     0x09  /* private numbering */
#define NP_EXT         0x0f  /* reserved for extension */

/* Internal Network Number */

#define INN_ALLOW          0x00
#define INN_NOTALLOW       0x01

typedef struct cgPtyNum          /* Calling Party Number */
{
   ElmtHdr eh;                   /* element header */
   TknU8 natAddrInd;             /* nature of addresss indicator */
   TknU8 oddEven;                /* odd or even */
   TknU8 scrnInd;                /* screen indicator */
   TknU8 presRest;               /* Address presentation restricted ind. */
   TknU8 numPlan;                /* numbering plan */
   TknU8 niInd;                  /* number incomplete indicator */
   TknStr addrSig;               /* Address Signal */
} SiCgPtyNum;

/* Screen Indicator Defines */

#define USRPROVNOTVER      0x00
#define USRPROV            0x01
#define USRPROVVERFAIL     0x02
#define NETPROV            0x03

/* Presentation Restriction Defines */

#define PRESALLOW          0x00
#define PRESREST           0x01
#define ADDRNOAVAIL        0x02

/* number incomplete indicator */

#define NBMCMLTE           0x00
#define NBMINCMLTE         0x01

typedef struct genNum           /* Generic Number */
{
   ElmtHdr eh;                   /* element header */
   TknU8 nmbQual;                /* number qualifier */
   TknU8 natAddrInd;             /* nature of addresss indicator */
   TknU8 oddEven;                /* odd or even */
   TknU8 scrnInd;                /* screen indicator */
   TknU8 presRest;               /* Address presentation restricted ind. */
   TknU8 numPlan;                /* numbering plan */
   TknU8 niInd;                  /* number incomplete indicator */
   TknStr addrSig;               /* Address Signal */
} SiGenNum;

/* Number qualifier indicator */

#define NQ_ADDCDMNB        0x01
#define NQ_ADDCONMNB       0x05
#define NQ_ADDCGNMB        0x06
#define NQ_ORIGCDNMB       0x07
#define NQ_ORIGRGDNMB      0x08
#define NQ_ORIGRDNMB       0x09

typedef struct cgPtyCat          /* Calling Party Category */
{
   ElmtHdr eh;                   /* element header */
   TknU8 cgPtyCat;               /* calling party category */
} SiCgPtyCat;

/* Calling Party Categories */

#define CAT_UNKNOWN        0x00
#define CAT_OPLANGFR       0x01
#define CAT_OPLANGENG      0x02
#define CAT_OPLANGGER      0x03
#define CAT_OPLANGRUS      0x04
#define CAT_OPLANGSP       0x05
#define CAT_ADMIN1         0x06
#define CAT_ADMIN2         0x07
#define CAT_ADMIN3         0x08
#define CAT_ORD            0x0a
#define CAT_PRIOR          0x0b
#define CAT_DATA           0x0c
#define CAT_TEST           0x0d
#define CAT_PAYPHONE       0x0f

/* defines for ANSI */

#define CAT_PRECLVL2       0xfa
#define CAT_PRECLVL3       0xfb
#define CAT_PRECLVL4       0xfc
#define CAT_PRECLVL5       0xfd

typedef struct siCauseDgn        /* Cause Indicator */
{
   ElmtHdr eh;                   /* element header */
   TknU8 location;               /* location */
   TknU8 cdeStand;               /* coding standard */
   TknU8 recommend;              /* recommendation */
   TknU8 causeVal;               /* cause value */
   TknStr dgnVal;                /* diagnostics */
} SiCauseDgn;

/* location */

#define ILOC_USER           0x00  /* user */
#define ILOC_PRIVNETLU      0x01  /* private network serving local user */
#define ILOC_PUBNETLU       0x02  /* public network serving local user */
#define ILOC_TRANNET        0x03  /* transit network */
#define ILOC_PRIVNETRU      0x04  /* private network serving the remote user */
#define ILOC_PUBNETRU       0x05  /* public network serving the remote user */
#define ILOC_INTNET         0x07  /* international network */
#define ILOC_NETINTER       0x0a  /* network beyond internetworking point */
#define ILOC_NOINFOAV       0x0f  /* no info concerning origin location */

/* coding standards */

#define CSTD_CCITT         0x00  /* CCITT standards */
#define CSTD_INT           0x01  /* Reserved for other international standards */
#define CSTD_NAT           0x02  /* National Standard */
#define CSTD_SPECLOC       0x03  /* Standard Specific to Identified Location */
#define CSTD_NET           0x03  /* Standard Specific Network */

/* recommendation */

#define REC_Q763           0x00     /* CCITT Recommendation Q.763 */
#define REC_X21            0x03     /* CCITT Recommendation X.21 */
#define REC_X25            0x04     /* CCITT Recommendation X.25 */
#define REC_Q1000          0x05     /* CCITT Recommendation Q.1000 */

/* cause value */

/* Class 000 and 001 */

#define CCUNALLOC          1     /* unassigned number */
#define CCNORTTOTSFNET     2     /* no route to transit network */
#define CCNORTTODEST       3     /* no route to destination */
#define CCSENDSPCLTONE     4     /* send special infomation tone */
#define CCMISDIALDTRNK     5     /* misdialed trunk prefix */
#define CCCALLCLR          16    /* normal call clearing */
#define CCUSRBSY           17    /* user busy */
#define CCNOUSRRSP         18    /* no user response */
#define CCNOANSWR          19    /* no answer (user alerted ) */
#define CCCALLRJT          21    /* call rejected */
#define CCNMBRCHG          22    /* number changed */
#define CCDESTOUTORD       27    /* destination out of order */
#define CCADDRINCOMP       28    /* Address incomplete */
#define CCFACREJ           29    /* facility rejected */
#define CCNORMUNSPEC       31    /* normal unspecified */

/* Class 010 */

#define CCNOCIRCUIT        34    /* no circuit/channel available */
#define CCNETAOL           38    /* network out of order */
#define CCTMPFAIL          41    /* Temporary failure */
#define CCSWTCHCONG        42    /* Switch equipment congestion */
#define CCREQUNAVAIL       44    /* requested circuit/channel unavailable */
#define CCRESCUNAVAIL      47    /* resources unavailable, unspecified */

/* defines for ANSI */

#define CCUSRINFDISCARD    43    /* user information discarded */
#define CCPREEMPT          47    /* preemption */

/* Class 011 */

#define CCFACNOTSUB        50    /* requested facility not subscribed */
#define CCINCBARRDCUG      55    /* incoming calls barred within CUG */
#define CCNOTAUTHBCAP      57    /* bearer capability not authorized */
#define CCBCAPUNAVAIL      58    /* bearer capability not available */
#define CCSERVUNAVAIL      63    /* Service or option unavailable */

/* Class 101 */

#define CCBCAPNOTIMP       65    /* bearer capability not implemented */
#define CCFACNOTIMP        69    /* requested facility not implemented */
#define CCRESTDIG          70    /* only restricted digital bear cap is avail. */
#define CCSERVNOTIMP       79    /* service or option not implemented */

#define CCCUNOTMEMBR       87    /* Called User Not member of CUG */
#define CCINCOMPDEST       88    /* incompatible destination */
#define CCINVTRNSTNET      91    /* invalid transit network selection */
#define CCINVMSG           95    /* invalid message, unspecified */

/* defines for ANSI */

#define CCINVALCALLREF     81    /* invalid call reference value */

/* Class 110 */

#define CCNOMSGTYP         97    /* msg type is non-existent or not
                                    implemented */
#define CCNOPARAMDISC      99    /* Param. non-existant, or not impl.,
                                    discard */
#define CCTMRRECOV         102   /* timeout recovery */
#define CCNOPARAMPASS      103   /* Param. non-existant, or not impl. pass
                                    along */
#define CCPROTERR          111   /* protocol error, unspecified */

/* defines for ANSI */

#define CCINVALPARAMCONT   100   /* invalid parameter contents */

/* Class 111 */

#define CCINTRWRK          127   /* interworking unspecified */

typedef struct cirGrpSupMTypInd  /* Circuit Group Supervision Msg. Type Ind. */
{
   ElmtHdr eh;                   /* element header */
   TknU8 typeInd;                /* circuit group supervision msg. type ind. */
} SiCirGrpSupMTypInd;

/* Type Indicator Defines */

#define MAINT              0x00
#define HARDFAIL           0x01

/* defines for ANSI */

#define SOFTWAREGEN        0x02  /* software generated */

/* defines for ANSI 92 */
#define BLOCK_WO_REL       0x00
#define BLOCK_REL          0x01

typedef struct cirStateInd       /* Circuit State Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknStr cirSteInd;             /* circuit state indicator. */
} SiCirStateInd;

typedef struct cugIntCode        /* Closed User Group Interlock Code */
{
   ElmtHdr eh;                   /* element header */
   TknU8 dig2;                   /* Digit 2 */
   TknU8 dig1;                   /* Digit 1 */
   TknU8 dig4;                   /* Digit 4 */
   TknU8 dig3;                   /* Digit 3 */
   TknU16 binCde;                /* binary Code */
} SiCugIntCode;

#if SS7_ANS88
typedef struct cugIntCodeA       /* Closed User Group Interlock Code */
{
   ElmtHdr eh;                   /* element header */
   TknU16 binCde;                /* Binary Code */
   TknU16 ISDNIdent;             /* ISDN identifier */
} SiCugIntCodeA;

#endif
typedef struct connectedNum      /* Connected number */
{
   ElmtHdr eh;                   /* element header */
   TknU8 natAddr;                /* nature of addresss indicator */
   TknU8 oddEven;                /* odd or even */
   TknU8 scrnInd;                /* screen indicator */
   TknU8 presRest;               /* Address presentation restricted ind. */
   TknU8 numPlan;                /* numbering plan */
   TknStr addrSig;               /* Address Signal */
} SiConnectedNum;

/* See calling/called party number for values */

typedef struct connReq           /* Connection Request */
{
   ElmtHdr eh;                   /* element header */
   TknU32 locRef;                /* local reference(really a 24bit quantity) */
   TknU16 pntCde;                /* point code */
   TknU8 protClass;              /* protocol classs */
   TknU8 credit;                 /* credit */
} SiConnReq;

#if (SS7_ANS88 || SS7_ANS92)
typedef struct connReqA          /* Connection Request */
{
   ElmtHdr eh;                   /* element header */
   TknU32 locRef;                /* local reference (really a 24bit quantity) */
   TknU32 pntCde;                /* point code */
   TknU8 protClass;              /* protocol classs */
   TknU8 credit;                 /* credit */
} SiConnReqA;

#endif
typedef struct contInd           /* Continuity indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 contInd;                /* continuity indicator */
} SiContInd;

/* Continuity indicators */

#define CONT_CHKFAIL       0x00
#define CONT_CHKSUCC       0x01

typedef struct evntInfo          /* Event Information */
{
   ElmtHdr eh;                   /* element header */
   TknU8 evntInd;                /* event indicators */
   TknU8 evntPresResInd;         /* event presentation restriction indicators */
} SiEvntInfo;

/* Event Indicator Defines */

#define EV_ALERT           0x01
#define EV_PROGRESS        0x02
#define EV_INBAND          0x03
#define EV_FWDONBUSY       0x04
#define EV_FWDONNOREP      0x05
#define EV_FWDUNCONDIT     0x06

/* defines for ANSI 92 */
#define EV_NOTSUPPSERV     0x08   /* notification of suppl. services */
#define EV_SRVINFINC       0x06f  /* service information included */

/* Event Presentation Restriction Indicators */

#define EVPR_NOIND         0x00
#define EVPR_PRESRES       0x01

typedef struct facInd            /* Facility Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 facInd;                 /* facility indicator */
} SiFacInd;

/* Facility Indicators  */

#define FI_USR2USRSERV     0x02

/* defines for ANSI */

#define FI_COMPCALLBUSY    0x01  /* completion of calls to busy subscriber */
#define FI_CCBSCONT        0xfd  /* CCBS continue */
#define FI_BUSYFREE        0xfe  /* busy/free status information */

typedef struct fwdCallInd        /* Forward Call Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 natIntCallInd;          /* National/International Call Indicator */
   TknU8 end2EndMethInd;         /* end to end method indicator */
   TknU8 intInd;                 /* interworking indicator */
   TknU8 end2EndInfoInd;         /* end to end information indicator */
   TknU8 isdnUsrPrtInd;          /* ISDN User Part indicator */
   TknU8 isdnUsrPrtPrfInd;       /* ISDN User Part preference indicator */
   TknU8 isdnAccInd;             /* ISDN access indicator */
   TknU8 sccpMethInd;            /* SCCP method indicator */
} SiFwdCallInd;

/* national/international call indicators  */

#define CALL_NAT           0x00
#define CALL_INTERNAT      0x01

/* ISDN User Part Preference Indicator Defines */

#define PREF_PREFAW        0x00
#define PREF_NOTREQAW      0x01
#define PREF_REQAW         0x02

/* see backward call indicators for other values */

typedef struct infoInd           /* Information Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 cgPtyAddrRespInd;       /* calling party address response ind. */
   TknU8 holdProvInd;            /* hold provided indicator */
   TknU8 cgPtyCatRespInd;        /* calling party category response ind. */
   TknU8 chrgInfoRespInd;        /* charge information response indicator */
   TknU8 solInfoInd;             /* solicitation information indicator */
   TknU8 spare;                  /* spare (insure we get second octet) */
} SiInfoInd;

#if SS7_ANS88
typedef struct infoIndA          /* Information Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 cgPtyAddrRespInd;       /* calling party address response ind. */
   TknU8 connAddrRspInd;         /* connected address response indicator */
   TknU8 cgPtyCatRespInd;        /* calling party category response ind. */
   TknU8 chrgInfoRespInd;        /* charge information response indicator */
   TknU8 redirAddrRspInda;       /* redirection address response indicator*/
   TknU8 redirAddrRspIndb;       /* redirection address response indicator*/
   TknU8 indexRspInd;            /* index response indicator */
} SiInfoIndA;

#endif

/* Calling Party Address Response Indicator defines */

#define CGPRTYADDRESP_NOTINCL    0x00
#define CGPRTYADDRESP_NOTAVAIL   0x01
#define CGPRTYADDRESP_INCL       0x03

/* defines for ANSI */

#define CGPTYADDRSPINCLNOHOLD    0x03
#define CGPTYADDRSPINCLHOLD      0x04

/* Hold provided indicator  - see mcidRsp */

/* Calling Party Category Response Indicator */

#define CGPRTYCATRESP_NOTINCL 0x00
#define CGPRTYCATRESP_INCL    0x01

/* Charge Information reponse Indicator */

#define CHRGINFO_NOTINCL   0x00
#define CHRGINFO_INCL      0x01

/* Soliciated Information  Indicator */

#define SOLINFO_SOLICIT    0x00
#define SOLINFO_UNSOLICIT  0x01

/* connected address response indicator */

#define CONNADDRNOTINCL    0x00  /* connected address not included */
#define CONNADDRNOTAVAIL   0x01  /* connected address not available */
#define CONNADDRINCL       0x03  /* connected address included */

/* redirecting address response indicator */

#define REDIRGADDRNOTINCL  0x00  /* redirecting address not included */
#define REDIRGADDRNOTAVAIL 0x01  /* redirecting address not available */
#define REDIRGADDRINCL     0x03  /* redirecting address included */

/* index response indicator */

#define INDEXNOTINCL       0x00  /* index not included */
#define INDEXINCL          0x01  /* index included */

typedef struct infoReqInd        /* Information Request Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 cgPtyAdReqInd;          /* calling party address request ind. */
   TknU8 holdingInd;             /* holding indicator */
   TknU8 cgPtyCatReqInd;         /* calling party category request ind. */
   TknU8 chrgInfoReqInd;         /* charge information request indicator */
   TknU8 malCaIdReqInd;          /* malicious call id request indicator */
   TknU8 spare;                  /* spare (insure second octet...) */
} SiInfoReqInd;

#if SS7_ANS88
typedef struct infoReqIndA       /* Information Request Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 cgPtyAdReqInd;          /* calling party address request ind. */
   TknU8 connAddrReqInd;         /* connected address request indicator */
   TknU8 cgPtyCatReqInd;         /* calling party category request ind. */
   TknU8 chrgInfoReqInd;         /* charge information request indicator */
   TknU8 redirAddrReqInd;        /* redirection address request indicator */
   TknU8 indexReqInd;            /* index request indicator */
   TknU8 malCaIdReqInd;          /* malicious call id request indicator */
   TknU8 holdingInd;             /* holding id request indicator */
} SiInfoReqIndA;

#endif

/* Calling Party Address Request Indicator */

#define CGPRTYADDREQ_NOTREQ   0x00
#define CGPRTYADDREQ_REQ      0x01

/* defines for ANSI */

#define CGPRTYADDREQREQNOHOLD    0x01
#define CGPRTYADDREQREQHOLD      0x03

/* Holding Indicators - see mcidReq */

/* Calling Party Category Request Indicators */

#define CGPRTYCATREQ_NOTREQ  0x00
#define CGPRTYCATREQ_REQ     0x01

/* Charge Information request Indicator */

#define CHRGINFO_NOTREQ    0x00
#define CHRGINFO_REQ       0x01

/* Malicious Call Indentification Request Indicator */

#define MALCAID_NOTREQ     0x00
#define MALCAID_REQ        0x01

/* connected address request indicator */

#define CONNADDRNOTREQ     0x00  /* connected address not requested */
#define CONNADDRREQ        0x01  /* connected address requested */

/* redirecting address request indicator */

#define REDIRADDRNOTREQ     0x00  /* redirecting address not requested */
#define REDIRADDRREQ        0x01  /* redirecting address requested */

/* index request indicator */

#define INDEXNOTREQ         0x00  /* index not requested */
#define INDEXREQ            0x01  /* index requested */

typedef struct natConInd         /* Nature of Connection Indicator */
{
   ElmtHdr eh;                   /* element header */
   TknU8 satInd;                 /* Satellite Indicator */
   TknU8 contChkInd;             /* continuity check indicator */
   TknU8 echoCntrlDevInd;        /* echo control device indicator */
} SiNatConInd;

/* Nature of Circuit Indicator */

#define SAT_NONE          0x00
#define SAT_ONE           0x01
#define SAT_TWO           0x02
#define SAT_THREE         0x03

/* Continuity Check Indicator */

#define CONTCHK_NOTREQ     0x00
#define CONTCHK_REQ        0x01
#define CONTCHK_PREV       0x02
#define CONTCHK_SPARE      0x03

/* Echo Control device indicator  - see backward call indicators */


typedef struct optBckCalInd      /* Optional Backward Call Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 inbndInfoInd;           /* in-band information indicator */
   TknU8 caFwdMayOcc;            /* call forwarding may occur indicator */
   TknU8 usrNetIneractInd;       /* user-network interaction indicator */
} SiOptBckCalInd;

#if SS7_Q767
typedef struct optBckCalIndQ     /* Optional Backward Call Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 inbndInfoInd;           /* in-band information indicator */
   TknU8 caFwdMayOcc;            /* call forwarding may occur indicator */
} SiOptBckCalIndQ;
#endif

/* In-band Information Indicator */

#define INBND_NOIND        0x00
#define INBND_AVAIL        0x01

/* Call Forwarding May Occur Indicator */

#define CAFWD_NOIND        0x00
#define CAFWD_MAYOCC       0x01

/* User-Network Interaction Indicator */

#define USERNET_NOIND          0x00
#define USERNET_INTERACTOCCUR  0x01

typedef struct opFwdCalInd       /* Optional Forward Call Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 clsdUGrpCaInd;          /* closed user group call indicator */
} SiOpFwdCalInd;


#if SS7_ANS88
typedef struct opFwdCalIndA      /* Optional Forward Call Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 clsdUGrpCaInd;          /* closed user group call indicator */
   TknU8 ccbsCallInd;            /* CCBS call indicator */
   TknU8 callgPtyNumIncomInd;    /* calling party number incomplete ind. */
   TknU8 connAddrReqInd1;        /* connected address request indicator */
} SiOpFwdCalIndA;
#endif

#if SS7_Q767
typedef struct opFwdCalIndQ      /* Optional Forward Call Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 clsdUGrpCaInd;          /* closed user group call indicator */
   TknU8 connAddrReqInd1;        /* connected address request indicator */
} SiOpFwdCalIndQ;
#endif

/* Closed User Group Call Indicator */

#define CUG_NONCUG         0x00
#define CUG_ACCALLOW       0x02
#define CUG_ACCNOTALLOW    0x03

/* defines for ANSI */

#define CUG_GRPCALL        0x00
#define CUG_ORDCALL        0x01

/* CCBS call indicator */

#define NOTCCBSCALL         0x00  /* not a CCBS call */
#define CCBSCALL            0x01  /* CCBS call */

/* calling party number incomplete indicator */

#define CALLGPTYNUMCOMPL    0x00  /* calling party number complete */
#define CALLGPTYNUMINCOMPL  0x01  /* calling party number incomplete */

/* connected address request indicator - see infoReqInd */

#if SS7_Q767IT
typedef struct fwdVadInd         /* Forward Vad Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 srvSteInd;              /* service state indicator */
   TknU8 procInd;                /* procedure indicator */
} SiFwdVadInd;

typedef struct backVadInd         /* Backward Vad Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 snInd;                  /* sn indicator */
   TknU8 oddEven;                /* odd or even */
   TknStr addrSig;               /* Address Signal */
} SiBackVadInd;
#endif

typedef struct origCdNum         /* Original Called Number */
{
   ElmtHdr eh;                   /* element header */
   TknU8 natAddr;                /* nature of addresss indicator */
   TknU8 oddEven;                /* odd or even */
   TknU8 presRest;               /* Address presentation restricted ind. */
   TknU8 numPlan;                /* numbering plan */
   TknStr addrSig;               /* Address Signal */
} SiOrigCdNum;

/* see called/calling party number for values */

typedef struct rangStat          /* Range and Status */
{
   ElmtHdr eh;                   /* element header */
   TknU8 range;                  /* range */
   TknStr status;                /* status */
} SiRangStat;

typedef struct redirNum          /* Redirection Number */
{
   ElmtHdr eh;                   /* element header */
   TknU8 natAddr;                /* nature of addresss indicator */
   TknU8 oddEven;                /* odd or even */
   TknU8 presRest;               /* Address presentation restricted ind. */
   TknU8 numPlan;                /* numbering plan */
   TknStr addrSig;               /* Address Signal */
} SiRedirNum;

/* see called/calling party number for values */

typedef struct redirInfo         /* Redirection Information */
{
   ElmtHdr eh;                   /* element header */
   TknU8 redirInd;               /* redirection indicator */
   TknU8 origRedirReas;          /* original redirection reason */
   TknU8 redirCnt;               /* redirection count */
   TknU8 redirReas;              /* redirection reason */
} SiRedirInfo;

/* redirecting indicators */

#define RI_NOREDIR               0x00
#define RI_CALLRERTE             0x01
#define RI_CALLRERTEALLRIPRESRES 0x02
#define RI_CALLFWD               0x03
#define RI_CALLFWDALLRIPRESRES   0x04
#define RI_CARERTEPRESRES        0x05
#define RI_CALLFWDPRESRES        0x06

/* original redirecting reason  */

#define REAS_UNKNWN           0x00
#define REAS_USRBUSY          0x01
#define REAS_NOREPLY          0x02
#define REAS_UNCOND           0x03
#define REAS_DFLCDURALRT      0x04
#define REAS_DFLCIMMDRSP      0x05
#define REAS_MBLSUBNOTRCHBL   0x06

/* defines for ANSI */

#define REAS_FIXED         0x03
#define REAS_VARIABLE      0x04

typedef struct sigPointCode      /* Signalling Point Code */
{
   ElmtHdr eh;                   /* element header */
   TknU16 sigPointCode;          /* signalling point code */
} SiSigPointCode;

#if SS7_ANS88
typedef struct sigPointCodeA     /* Signalling Point Code */
{
   ElmtHdr eh;                   /* element header */
   TknU32 sigPointCode;          /* signalling point code */
} SiSigPointCodeA;

#endif
typedef struct subNum            /* Subsequent Number */
{
   ElmtHdr eh;                   /* element header */
   TknU8 oddEven;                /* odd or even */
   TknStr addrSig;               /* Address Signal */
} SiSubNum;

typedef struct susResInd         /* Suspend/Resume indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 susResInd;              /* suspend/resume indicators */
} SiSusResInd;

/* Suspend/Resume Indicators */

#define SR_ISDNSUBINIT     0x00
#define SR_NETINIT         0x01

typedef struct echoControl       /* echo control indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 outEchoRsp;             /* outgoing echo control device response */
   TknU8 incEchoRsp;             /* incoming echo control device response */
   TknU8 outEchoReq;             /* outgoing echo control device request */
   TknU8 incEchoReq;             /* incoming echo control device request */
} SiEchoCtl;

/* Echo Control device req/rsp */

#define ECHCDEV_NOINFOINCL 0x00
#define ECHCDEV_NOTINCL    0x01
#define ECHCDEV_INCL       0x02

#define ECHCDEV_ACTREQ	   0x01
#define ECHCDEV_DEACTREQ   0x02

typedef struct tranNetSel        /* Transit Network Selection */
{
   ElmtHdr eh;                   /* element header */
   TknU8 netIdPln;               /* network id plan */
   TknU8 typNetId;               /* type of network identification */
   TknU8 oddEven;                /* odd/even */
   TknStr netId;                 /* network identification */
} SiTranNetSel;

/* Network Identification Plan */

#define NI_UNKNWN          0x00
#define NI_DNIC_X21        0x03
#define NI_MNIC_E212       0x06

/* defines for ANSI92 */
#define NI_3DIGCIC          0x01
#define NI_4DIGCIC          0x02

/* Network Identification Plan */

#define TNI_CCITT          0x00
#define TNI_NATNET         0x02

typedef struct txMedReq          /* Transmission Medium Requirement */
{
   ElmtHdr eh;                   /* element header */
   TknU8 trMedReq;               /* tranmission medium requirement */
} SiTxMedReq;

/* Transmission Mediuum Requirements */

#define TMR_SPEECH      0x00
#define TMR_64KBITS     0x02
#define TMR_31KHZ       0x03
#define TMR_ALTSPEECH   0x04
#define TMR_ALT64KBITS  0x05
#define TMR_2X64KBITS   0x07
#define TMR_384KBITS    0x08
#define TMR_1536KBITS   0x09
#define TMR_1920KBITS   0x0a

typedef struct usrServInfo       /* User Service Information */
{
   ElmtHdr eh;                   /* element header */
   TknU8 infoTranCap;            /* information transfer capability */
   TknU8 cdeStand;               /* coding standard */
   TknU8 infoTranRate0;          /* information transfer rate */
   TknU8 tranMode;               /* transfer mode */
   TknU8 establish;              /* establishment */
   TknU8 config;                 /* configuration */
   TknU8 chanStruct;             /* structure */
   TknU8 infoTranRate1;          /* information transfer rate */
   TknU8 symmetry;               /* symmetry */
   TknU8 usrInfLyr1Prot;         /* usr information layer 1 protocol */
   TknU8 lyr1Ident;              /* layer 1 identity */
   TknU8 usrRate;                /* user rate */
   TknU8 negot;                  /* negotiation */
   TknU8 syncAsync;              /* synchronous/asynchronous */
   TknU8 flcOnRx;                /* flow control on reception */
   TknU8 flcOnTx;                /* flow control on transmission */
   TknU8 niClkOnRx;              /* network independent clock on reception */
   TknU8 niClkOnTx;              /* network independent clock on transmission*/
   TknU8 interRate;              /* intermediate rate */
   TknU8 inOutBandNeg;           /* inband/outband negotiation */
   TknU8 asgnrAsgne;             /* assignor/assignee */
   TknU8 logLnkNegot;            /* logical link identifier negotiation */
   TknU8 mode;                   /* mode of operation */
   TknU8 multiFrm;               /* multiple frame establishment support */
   TknU8 hdrNohdr;               /* rate adaption header/no header */
   TknU8 parity;                 /* parity information */
   TknU8 nmbDatBits;             /* number of data bits excluding parity bit */
   TknU8 nmbStpBits;             /* number of stop bits */
   TknU8 modemType;              /* modem type */
   TknU8 duplexMode;             /* duplex mode */
   TknU8 usrInfLyr2Prot;         /* user information layer 2 protocol */
   TknU8 lyr2Ident;              /* layer 2 identity */
   TknU8 usrInfLyr3Prot;         /* user information layer 3 protocol */
   TknU8 lyr3Ident;              /* layer 3 identity */
} SiUsrServInfo;

/* information transfer capability */

#define ITC_SPEECH     0x00  /* speech */
#define ITC_UNRDIG     0x08  /* unrestricted digital information */
#define ITC_RESDIG     0x09  /* restricted digital information */
#define ITC_A31KHZ     0x10  /* 3.1kHz audio */
#define ITC_A7KHZ      0x11  /* 7 kHz audio */
#define ITC_A15KHZ     0x12  /* 15 kHz audio */
#define ITC_VIDEO      0x18  /* video */

/* coding standard - see siCauseDgn for values */

/* information transfer mode */

#define TM_CIRCUIT     0x00  /* circuit mode */
#define TM_PACKET      0x02  /* packet mode */

/* information transfer rate */

#define ITR_PKT        0x00  /* packet mode */
#define ITR_64KBIT     0x10  /* circuit mode - 64 kbits */
#define ITR_2X64KBIT   0x11  /* circuit mode - 2 X 64 kbits */
#define ITR_384KBIT    0x13  /* circuit mode - 384 kbits */
#define ITR_1472KBIT   0x14  /* circuit mode - 1472 kbits */
#define ITR_1536KBIT   0x15  /* circuit mode - 1536 kbits */
#define ITR_1920KBIT   0x17  /* circuit mode - 1920 kbits */
#define ITR_MULIRATE   0x18  /* circuit mode - multi rate */

/* establishement */

#define E_DEMAND       0x00  /* demand */
#define E_PERM         0x01  /* permanent */

/* configuration */

#define POINT2POINT    0x00  /* point to point */
#define MULTIPOINT     0x01  /* multipoint */

/* structure */

#define S_DEF          0x00  /* default */
#define S_8KHZINTEG    0x01  /* 8 khz integrity */
#define S_SDUINTEG     0x04  /* service data unit integrity */
#define S_UNSTRUCT     0x07  /* unstructured */

/* symmetry */

#define S_BISYM        		0x00  /* bidirectional symmetry */
#define S_BIASM             0x01    /* bidirectional asymetric */
#define S_UNI_ORIGDEST      0x02    /* unidirectional orig -> dest */
#define S_UNI_DESTORIG      0x03    /* unidirectional dest -> orig */

/* layer 1 identity */

#define L1_IDENT           0x01  /* layer 1 identity */

/* user rate */

#define UR_EINI460         0x00  /* determined by E bits in I.460 */
#define UR_600             0x01  /* 0.6 kbits, V.6 and X.1 */
#define UR_1200            0x02  /* 1.2 kbits, V.6 */
#define UR_2400            0x03  /* 2.4 kbits, V.6 and X.1 */
#define UR_3600            0x04  /* 3.6 kbits, V.6 */
#define UR_4800            0x05  /* 4.8 kbits, V.6 and X.1 */
#define UR_7200            0x06  /* 7.2 kbits, V.6 */
#define UR_8000            0x07  /* 8.0 kbits, I.460 */
#define UR_9600            0x08  /* 9.6 kbits, V.6 and X.1 */
#define UR_14400           0x09  /* 14.4 kbits, V.6 */
#define UR_16000           0x0a  /* 16 kbits, I.460 */
#define UR_19200           0x0b  /* 19.2 kbits, V.6 */
#define UR_32000           0x0c  /* 32 kbits, I.460 */
#define UR_48000           0x0e  /* 48 kbits, V.6 and X.1 */
#define UR_56000           0x0f  /* 56 kbits, V.6 */
#define UR_64000           0x10  /* 56 kbits, V.6 */
#define UR_134             0x15  /* .1345 kbits, X.1 */
#define UR_100             0x16  /* .100 kbits, X.1 */
#define UR_75_1200         0x17  /* .075/1200 kbits, V.6 and X.1 */
#define UR_1200_75         0x18  /* 1200/.075 kbits, V.6 and X.1 */
#define UR_50              0x19  /* .050 kbits, V.6 and X.1 */
#define UR_75              0x1a  /* .075 kbits, V.6 and X.1 */
#define UR_110             0x1b  /* .110 kbits, V.6 and X.1 */
#define UR_150             0x1c  /* .150 kbits, V.6 and X.1 */
#define UR_200             0x1d  /* .200 kbits, V.6 and X.1 */
#define UR_300             0x1e  /* .300 kbits, V.6 and X.1 */
#define UR_12000           0x1f  /* 12 kbits, V.6 */

/* negotiation */

#define N_IBNOTPOSS    0x00  /* inband not possible */
#define N_IBPOSS       0x01  /* inband possible */

/* negotiation indicator */

#define N_OBNOTPOSS    0x00  /* outband not possible */
#define N_OBPOSS       0x01  /* outband possible */

/* synchronous/asynchronous */

#define SA_SYNC        0x00  /* synchronous */
#define SA_ASYNC       0x01  /* asynchronous */

/* flow control on reception */

#define FLCRX_NOTACC       0x00  /* cannot accept data with flow control */
#define FLCRX_ACC          0x01  /* can accept data with flow control */

/* flow control on transmission */

#define FLCTX_NOTREQ       0x00  /* not required to send with flow control */
#define FLCTX_REQ          0x01  /* required to send with flow control */

/* network independent clock on reception */

#define NICRX_NOTACC       0x00  /* cannot accept data with nic */
#define NICRX_ACC          0x01  /* can accept data with nic */

/* network independent clock on transmission */

#define NICTX_NOTREQ       0x00  /* not required to send with nic */
#define NICTX_REQ          0x01  /* required to send with nic */

/* intermediate rate */

#define IR_NONE        0x00  /* none specified */
#define IR_8KBIT       0x01  /* 8 kbits */
#define IR_16KBIT      0x02  /* 16 kbits */
#define IR_32KBIT      0x03  /* 32 kbits */

/* assignor/assignee */

#define AA_ORGASGNEE   0x00  /* originator is assignee */
#define AA_ORGASGNOR   0x01  /* originator is assignor */

/* logical link identifier */

#define LLI_DEF        0x00  /* default */
#define LLI_FULLNEG    0x01  /* full protocol negotiation */

/* mode of operation */

#define MOO_BITTRANS   0x00  /* bit transparent */
#define MOO_PROTSEN    0x01  /* protocol sensitive */

/* multiple frame establishment */

#define MFE_NOTSUP     0x00  /* not supported */
#define MFE_SUP        0x01  /* supported */

/* rate adaption header/not header */

#define IRAH_INC            0x00  /* included */
#define IRAH_NOTINC         0x01  /* not included */

/* number of stop bits */

#define NSB_UNUSED     0x00  /* none specified */
#define NSB_1          0x01  /* 1 stop bit */
#define NSB_15         0x02  /* 1.5 stop bits */
#define NSB_2          0x03  /* 2 stop bits */

/* number of data bits */

#define NDB_UNUSED     0x00  /* none specified */
#define NDB_5          0x01  /* 5 bits */
#define NDB_7          0x02  /* 7 bits */
#define NDB_8          0x03  /* 8 bits */

/* parity information */

#define PARI_ODD       0x00  /* odd */
#define PARI_EVEN      0x02  /* even */
#define PARI_NONE      0x03  /* none */
#define PARI_0         0x04  /* force to 0 */
#define PARI_1         0x05  /* force to 1 */

/* duplex mode */

#define DUPMODE_HALF   0x00  /* half duplex */
#define DUPMODE_FULL   0x01  /* full duplex */

/* modem type */

#define MODEM_V21      0x01  /* V.21 */
#define MODEM_V22      0x02  /* V.21 */
#define MODEM_V22BIS   0x03  /* V.21 */
#define MODEM_V23      0x04  /* V.21 */
#define MODEM_V26      0x05  /* V.21 */
#define MODEM_V26BIS   0x06  /* V.21 */
#define MODEM_V26TER   0x07  /* V.21 */
#define MODEM_V27      0x08  /* V.21 */
#define MODEM_V27BIS   0x09  /* V.21 */
#define MODEM_V27TER   0x0a  /* V.21 */
#define MODEM_V29      0x0b  /* V.21 */
#define MODEM_V32      0x0c  /* V.21 */
#define MODEM_V35      0x0d  /* V.21 */

/* user information layer 1 */

#define UIL1_CCITTV110 0x01  /* CCITT Standardized Rate Adaptation V.110/X.30. */
#define UIL1_G711ULAW  0x02  /* Reccomendation G.711 u-Law */
#define UIL1_G711ALAW  0x03  /* Recommendation G.711 A-Law */
#define UIL1_G721ADCPM 0x04  /* Recommendation G.721 32 kbit/s ADCPM and */
							 /* Recommendation I.460 */
#define UIL1_G722G725  0x05  /* Recommendation G.722 and G.725 - 7kHz Audio */
#define UIL1_H261      0x06  /* Recommendation H.261 - 384 kbit/s Video */
#define UIL1_NONCCITT  0x07  /* Non-CCITT  standardized Rate adaptation */
#define UIL1_CCITTV120 0x08  /* CCITT Standardized Rate Adaptation V.120 */
#define UIL1_CCITTX31  0x09  /* CCITT Standardized Rate Adaptation X.31 HDLC */

/* defines for ANSI */

#define UIL1_CCITTI412     0x00  /* CCITT Recommendation I.412 */
#define UIL1_RATEADAPT     0x01  /* Rate Adaptation */

/* user information layer 2 protocol */

#define UIL2_BASIC     0x01  /* basic mode - ISO 1745 */
#define UIL2_Q921      0x02  /* CCITT Recommendation Q.921 */
#define UIL2_X25SLP    0x06  /* CCITT Recommendation X.25, single link */
#define UIL2_X25MLP    0x07  /* CCITT Recommendation X.25, multi link */
#define UIL2_T71       0x08  /* extended LAPB for half duplex, */
							 /* CCITT Recommendation T.71 */
#define UIL2_HDLCARM   0x09  /* HDLC ARM - ISO 4335 */
#define UIL2_HDLCNRM   0x0a  /* HDLC NRM - ISO 4335 */
#define UIL2_HDLCABM   0x0b  /* HDLC ABM - ISO 4335 */
#define UIL2_LANLLC    0x0c  /* LAN LLC - ISO 8802/2 */
#define UIL2_X75SLP    0x0d  /* CCITT Recommendation X.75, single link */
#define UIL2_Q922      0x0e  /* CCITT Recommendation Q.922 */
#define UIL2_USRSPEC   0x10  /* CCITT User specified */
#define UIL2_T90       0x11  /* CCITT T.90 */

/* user information layer 3 protocol */

#define UIL3_Q931      0x02  /* CCITT Recommendation Q.931 */
#define UIL3_T90       0x05  /* CCITT T.90 */
#define UIL3_X25PLP    0x06  /* CCITT Recommendation X.25, packet layer */
#define UIL3_ISO8208   0x07  /* ISO 8208 */
#define UIL3_ISO8348   0x08  /* ISO 8348 */
#define UIL3_ISO8473   0x09  /* ISO 8473 */
#define UIL3_T70       0x0a  /* CCITT Recommendation T.70 */
#define UIL3_USRSPEC   0x10  /* CCITT User specified */

/* layer 2 identity */

#define L2_IDENT           0x02  /* layer 2 identity */

/* layer 3 identity */

#define L3_IDENT           0x03  /* layer 3 identity */

typedef struct usr2UsrInd        /* User to User indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 type;                   /* type */
   TknU8 serv1;                  /* service 1 */
   TknU8 serv2;                  /* service 2 */
   TknU8 serv3;                  /* service 3 */
} SiUsr2UsrInd;

typedef struct usr2UsrInfo       /* User to user information */
{
   ElmtHdr eh;                   /* element header */
   TknStr info;                  /* user to user information */
} SiUsr2UsrInfo;

typedef struct passAlng          /* Pass Along */
{
   ElmtHdr eh;                   /* element header */
   TknStr passAlng;              /* pass along */
} SiPassAlng;

typedef struct siEndOp           /* End of Optional Parameters */
{
   ElmtHdr eh;                   /* element header */
   TknU8 nullVal;                /* null value, if present */
} SiEndOp;

typedef struct siPduHdr          /* pdu header */
{
   ElmtHdr eh;                   /* element header */
   TknU8 msgType;                /* Message Type */
} SiPduHdr;

#if (SS7_ANS88 || SS7_ANS92)
typedef struct chargeNum         /* Charge Number */
{
   ElmtHdr eh;                   /* element header */
   TknU8 natAddr;                /* nature of addresss indicator */
   TknU8 oddEven;                /* odd or even */
   TknU8 numPlan;                /* numbering plan */
   TknStr addrSig;               /* Address Signal */
} SiChargeNum;

/* see called/calling party number for values */

typedef struct cirGrpCharInd     /* Circuit group characteristic indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 cirGrpCarInd;           /* circuit group carrier indicator */
   TknU8 dblSzCtrlInd;           /* double seizing control indicator */
   TknU8 alarmCarInd;            /* alarm carrier indicator */
   TknU8 contChkReqInd;          /* continuity check requirements indicator */
} SiCirGrpCharInd;

/* circuit group carrier indicator */

#define CG_UNKNOWN         0x00  /* unknown */
#define CG_ANALOG          0x01  /* analog */
#define CG_DIGITAL         0x02  /* digital */
#define CG_ANALDIG         0x03  /* digital and analog */

/* double seizing control indicator */

#define DS_UNKNOWN         0x00  /* unknown */
#define DS_ODDCIC          0x01  /* odd cic control */
#define DS_EVENCIC         0x02  /* even cic control */

/* defines for ANSI92 */
#define DS_ALLCIC          0x03  /* all cic control */

/* alarm carrier indicator */

#define AC_UNKNOWN         0x00  /* unknown */
#define AC_SOFTCARHAND     0x01  /* software carrier handling */
#define AC_HARDCARHAND     0x02  /* hardware carrier handling */

/* continuity check requirements indicator */

#define CO_UNKNOWN         0x00  /* unknown */
#define CO_NONE            0x01  /* none */
#define CO_STATIS          0x02  /* statistical */
#define CO_PERCALL         0x03  /* per call */

typedef struct cirIdName         /* Circuit ID Name */
{
   ElmtHdr eh;                   /* element header */
   TknStr trunkNumClli;          /* trunk number and clli code */
} SiCirIdName;

typedef struct cirValRspInd      /* Circuit validation response indicator */
{
   ElmtHdr eh;                   /* element header */
   TknU8 cirValRspInd;           /* user to user info */
} SiCirValRspInd;

#endif

/* circuit validation response indicator */

#define CV_SUCCESS         0x00  /* successful */
#define CV_FAILURE         0x01  /* failure */

#if SS7_ANS88
typedef struct cugChkRspInd      /* CUG check */
{
   ElmtHdr eh;                   /* element header */
   TknU8 accessInd;              /* access indicator */
   TknU8 divergInd;              /* divergence indicator */
   TknU8 chkSuccInd;             /* check successful indicator */
   TknU8 normCallInd;            /* normal call indicator */
   TknU8 cugCallInd;             /* closed user group call indicator */
} SiCUGChkRspInd;

#endif

/* access indicator */

#define ACCESS_BARRED      0x00  /* access barred */
#define ACCESS_ALLOW       0x01  /* access allowed */

/* divergence indicator */

#define DIVERGENCE         0x00  /* divergence */
#define NO_DIVERGENCE      0x01  /* no divergence */

/* check successful indicator */

#define CHK_UNSUCCESS      0x00  /* check unsuccessful */
#define CHK_SUCCESS        0x01  /* check successful */

/* normal call indicator */

#define NOT_NORMAL_CALL    0x00  /* not a normal call */
#define NORMAL_CALL        0x01  /* normal (non-CUG) call */

/* closed user group call indicator */

#define CUG_CALL              0x01  /* closed user group call */
#define CUG_CALLOUTACCALL     0x02  /* closed user group call -
									   outgoing access allowed */
#define CUG_CALLOUTACCNOTALL  0x03  /* closed user group call - outgoing access not allowed */

#if (SS7_ANS88 || SS7_ANS92)
typedef struct clli              /* Common Language Location Idenification */
{
   ElmtHdr eh;                   /* element header */
   TknStr clliCode;              /* clli codes */
} SiCLLI;

#endif
#if SS7_ANS88
typedef struct facInfInd         /* Facility Information Indicators */
{
   ElmtHdr eh;                   /* element header */
   TknU8 calldPtyFreeInd;        /* called party free indicator */
   TknU8 callgPtyAnsInd;         /* callg party answer indicator */
   TknU8 facReqEnqInd;           /* facility request enquiry indicator */
   TknU8 facReqActInd;           /* facility request active indicator */
} SiFacInfInd;

/* called party free indicator */

#define CDPTY_FREE          0x00  /* called party free */
#define CDPTY_BUSY          0x01  /* called party busy */

/* calling party answer indicator */

#define NOCGPTYANS          0x00  /* no calling party answer */
#define CGPTYANS            0x01  /* calling party answer  */

/* facility request enquiry indicator */

#define NOENQUIRY           0x00  /* no enquiry */
#define FACREQACTENQ        0x01  /* facility request active enquiry */

/* facility request active indicator */

#define FACREQNOTACTIVE     0x00  /* facility request not active */
#define FACREQACTIVE        0x01  /* facility request active */

typedef struct index             /* Index  */
{
   ElmtHdr eh;                   /* element header */
   TknU32 index;                 /* index */
} SiIndex;
#endif

#if (SS7_ANS88 || SS7_ANS92)
typedef struct origLineInf       /* Orignating Line Information */
{
   ElmtHdr eh;                   /* element header */
   TknU8 lineInfo;               /* originating line information */
} SiOrigLineInf;

/* originating line information */

#define OL_IDENTLINE             0x00  /* identified line - no special treatment */
#define OL_ONI                   0x01  /* ONI (multiparty) */
#define OL_ANIFAIL               0x02  /* ANI failure (unavailable) */
#define OL_HOTEL                 0x05  /* hotle (without room identification) */
#define OL_COINLESS              0x07  /* coinless, hospital, inmate, and the like */
#define OL_INTERLATA             0x08  /* interLATA restricted */
#define OL_AIOD                  0x14  /* AIOD - listed DN sent */
#define OL_COINELINE             0x1b  /* coin line */
#define OL_INTERLATA_HOTEL       0x44  /* interLATA restricted - hotel */
#define OL_INTERLATA_COINLESS    0x4e  /* interLATA restricted - coinless, and the like */


typedef struct outgTrkGrpNum     /* Outgoing Trunk Group Number */
{
   ElmtHdr eh;                   /* element header */
   TknStr digits;                /* digits */
} SiOutgTrkGrpNum;

#endif

typedef struct notifInd          /* Notification Indicator */
{
   ElmtHdr eh;                   /* element header */
   TknU8 notifInd;               /* Notification Indicator */
} SiNotifInd;

#define	NI_CALLDELAY	0x04	/* call completion delay */
#define NI_CALLWAIT		0x60	/* call waiting */
#define NI_REMHLD		0x79	/* remote hold */
#define NI_REMHLDREL	0x7a	/* remote hold released */
#define NI_CALLFWDED	0x7b	/* call is forwarded */

typedef struct serviceAct        /* Service Activation */
{
   ElmtHdr eh;                   /* element header */
   TknStr serviceAct;            /* service activation */
} SiServiceAct;

typedef struct genAddr           /* Generic Address */
{
   ElmtHdr eh;                   /* element header */
   TknU8 typeOfAddr;             /* type of address */
   TknU8 natAddr;                /* nature of address indicator */
   TknU8 oddEven;                /* odd or even address signal */
   TknU8 presRest;               /* presentation restriction */
   TknU8 numPlan1;               /* numbering plan */
   TknStr addrSig;               /* addressing signal */
} SiGenAddr;

/* Type Of Address */
#define DIALNUM            0x00
#define DESTNUM            0x01
#define SUPADDR_FAIL       0x02
#define SUPADDR_NOTSCREEN  0x03
#define COMPLNUM           0x04

/* others - see called/calling party */

typedef struct genDigits         /* Generic Digits */
{
   ElmtHdr eh;                   /* element header */
   TknU8 typeOfDigits;           /* type of digits */
   TknU8 encodeScheme;           /* encoding scheme */
   TknStr digits;                /* digits */
} SiGenDigits;

/* Type of Digits */
#define ACCTCODE           0x00
#define AUTHCODE           0x01
#define PRIVNETMARK        0x02
#define BUSCOMMGRID        0x03

/* Encoding Scheme */
#define ENC_BCD_EVEN       0x00
#define ENC_BCD_ODD        0x01
#define ENC_IA5            0x02
#define ENC_BIN            0x03

#if SS7_ANS92
typedef struct businessGrp       /* Business Group */
{
   ElmtHdr eh;                   /* element header */
   TknU8 partySel;               /* party selector */
   TknU8 linePrivInfInd;         /* line privileges info. ident. */
   TknU8 BGIDident;              /* BGID identifier  */
   TknU8 attendStat;             /* attendant status */
   TknU32 busiGrpIdent;          /* business group identifier */
   TknU16 subGrpIdent;           /* sub-group identifier */
   TknU8 linePriv;               /* line privileges */
} SiBusinessGrp;

/* Party Selection */
#define PRTY_NOIND          0x00
#define PRTY_CGPTYNUM       0x01
#define PRTY_CDPTYNUM       0x02
#define PRTY_CONNDPTYNUM    0x03
#define PRTY_REDIRGNUM      0x04
#define PRTY_ORIGCALLNUM    0x05

/* Line Priviledges Information Indicator */
#define PRIV_FIXED          0x00
#define PRIV_CUSTDEF        0x01

/* BGID identification indicator */
#define BGID_MULTILOC       0x00
#define BGID_INTERNET       0x01

/* Attendant Status */
#define ATTEN_NOIND         0x00
#define ATTEN_ATTENDLINE    0x01

/* Line Priviledges */
#define LP_RESTRICT              0x00
#define LP_SEMIRESTRICT          0x01
#define LP_FULLRESTRICT          0x02
#define LP_FULLRESTRICT_INSWTCH  0x03
#define LP_DENIED                0x04

typedef struct carrierId         /* Carrier ID */
{
   ElmtHdr eh;                   /* element header */
   TknU8 netIdPln1;              /* network id plan */
   TknU8 typNetId2;              /* type of network identification */
   TknU8 CIDigit1;               /* Network Identity Digit 1 */
   TknU8 CIDigit2;               /* Network Identity Digit 2 */
   TknU8 CIDigit3;               /* Network Identity Digit 3 */
   TknU8 CIDigit4;               /* Network Identity Digit 4 */
} SiCarrierId;

/* network id plane, type of network id - see SiTranNetSel */

typedef struct carrierSelInf     /* Carrier Selection Information  */
{
   ElmtHdr eh;                   /* element header */
   TknU8 carrierSelInf;          /* carrier selection information */
} SiCarrierSelInf;

/* Carrier Selection Information */
#define CARSEL_NOIND              0x00
#define CARSEL_PRESUB_NOINPUT     0x01
#define CARSEL_PRESUB_INPUT       0x02
#define CARSEL_PRESUB_INPUTUNDET  0x03
#define CARSEL_NOTPRESUB_INPUT    0x04

typedef struct egress            /* Egress Service */
{
   ElmtHdr eh;                   /* element header */
   TknStr egress;                /* egress */
} SiEgress;

typedef struct jurisInf          /* Jurisdiction Information */
{
   ElmtHdr eh;                   /* element header */
   TknU8 addrSig1;               /* address signal 1 */
   TknU8 addrSig2;               /* address signal 2 */
   TknU8 addrSig3;               /* address signal 3 */
   TknU8 addrSig4;               /* address signal 4 */
   TknU8 addrSig5;               /* address signal 5 */
   TknU8 addrSig6;               /* address signal 6 */
} SiJurisInf;

typedef struct netTransport      /* Network Transport */
{
   ElmtHdr eh;                   /* element header */
   TknStr netTransport;          /* network transport */
} SiNetTransport;

typedef struct specProcReq       /* Special Processing Request */
{
   ElmtHdr eh;                   /* element header */
   TknU8 specProcReq;            /* special processing request */
} SiSpecProcReq;

typedef struct transReq          /* Transaction Request */
{
   ElmtHdr eh;                   /* element header */
   TknU32 transId;               /* transaction id */
   TknStr SCCPAddr;              /* SCCP address */
} SiTransReq;

#endif

/* Events */

typedef struct siConEvnt         /* ISUP Connect Event */
{
   SiNatConInd natConInd;        /* Nature of connection indicators */
   SiFwdCallInd fwdCallInd;      /* forward call indicators */
   SiCgPtyCat cgPtyCat;          /* calling party category */
   SiTxMedReq txMedReq;          /* transmission medium requirement */
#if (SS7_ANS88 || SS7_ANS92)
   SiUsrServInfo usrServInfoA;   /* user service info */
#endif
   SiCdPtyNum cdPtyNum;          /* called party number */
   SiTranNetSel tranNetSel;      /* transit network selection */
#if (SS7_ANS88 || SS7_ANS92)
   SiCallRefA callRefA;          /* call reference */
#endif
   SiCallRef callRef;            /* call reference */
   SiCgPtyNum cgPtyNum;          /* calling party number */
   SiOpFwdCalInd opFwdCalInd;    /* optional forward call indicators */
#if SS7_Q767
   SiOpFwdCalIndQ opFwdCalIndQ;  /* optional forward call indicators */
#endif
#if SS7_Q767IT
   SiFwdVadInd fwdVad;           /* forward vad indicators */
#endif
#if SS7_ANS88
   SiOpFwdCalIndA opFwdCalIndA;  /* optional forward call indicators */
#endif
   SiRedirNum redirgNum;         /* redirection number */
   SiRedirInfo redirInfo;        /* redirection information */
   SiCugIntCode cugIntCode;      /* closed group interlock code */
#if SS7_ANS88
   SiCugIntCodeA cugIntCodeA;    /* closed group interlock code */
#endif
#if (SS7_ANS88 || SS7_ANS92)
   SiConnReqA connReqA;          /* connection request */
#endif
#if SS7_ANS88
   SiUsr2UsrInfo usr2UsrInfoA;   /* user to user information */
#endif
   SiConnReq connReq;            /* connection request */
   SiOrigCdNum origCdNum;        /* original called number */
   SiUsr2UsrInfo usr2UsrInfo;    /* user to user information */
   SiAccTrnspt accTrnspt;        /* access transport */
#if SS7_ANS88
   SiRedirInfo redirInfoA;       /* redirection information */
#endif
#if (SS7_ANS88 || SS7_ANS92)
   SiChargeNum chargeNum;        /* connected number */
   SiOrigLineInf origLineInf;    /* originating line information */
#endif
   SiUsrServInfo usrServInfo;
   SiUsr2UsrInd usr2UsrInd;      /* user to user indicators */
   SiPropDly propDly;            /* propagation delay counter */
   SiUsrServInfo usrServInfo1;   /* user service info prime */
   SiNetSpecFacil netFac;        /* network specific facility */
   SiSigPointCode orgPteCde;     /* originating ISC point code */
   SiGenDigits genDigits;        /* generic digits */
   SiGenNum genNmb;              /* generic number */
   SiUsrServInfo usrServInfo2;   /* user service info prime */
   SiRemotOper remotOper;        /* remote operations */
   SiParmCompInfo parmCom;       /* parameter compatibility information */
   SiNotifInd notifInd;          /* notification indicator */
   SiServiceAct serviceAct;      /* service activation */
   SiMlppPrec mlppPrec;          /* MLPP precedence */
   SiTxMedReq txMedUsPr;         /* transmission medium used */
   SiBckCalInd bckCallInd;       /* backward call indicators */
   SiCgPtyNum cgPtyNum1;         /* calling party number */
   SiOptBckCalInd optBckCalInd;  /* optional backward call indicators */
#if SS7_Q767
   SiOptBckCalIndQ optBckCalIndQ;/* Q767 optional backward call indicators */
#endif
   SiConnectedNum connNum;       /* connected number */
   SiAccDelInfo accDelInfo;      /* access delivery information */
   SiPropDly cllHstry;           /* call history information */
   SiRedirNum redirNum;          /* redirection number */
   SiRedirRestr redirRstr;       /* redirection restriction */
#if SS7_Q767IT
   SiBackVadInd backVad;         /* backward vad indicators */
#endif
#if SS7_ANS92
   SiBusinessGrp businessGrp;    /* business group */
   SiCarrierId carrierId;        /* carrier identification */
   SiCarrierSelInf carSelInf;    /* carrier selection information */
   SiEgress egress;              /* ergress service */
   SiGenAddr genAddr;            /* generic address */
   SiInfoReqInd infoReqInd;      /* information request indicators */
   SiJurisInf jurisInf;          /* jurisdiction information */
   SiNetTransport netTransport;  /* network transport */
   SiSpecProcReq specProcReq;    /* special processing request */
   SiTransReq transReq;          /* transaction request */
#endif
} SiConEvnt;

typedef struct  siCnStEvnt       /* Connect Status Event */
{
   SiSubNum subNum;              /* subsequent number */
   SiBckCalInd bckCallInd;       /* backward call indicators */
#if (SS7_ANS88 || SS7_ANS92)
   SiChargeNum chargeNum;        /* connected number */
   SiCallRefA callRefA;          /* call reference */
   SiConnReqA connReqA;          /* connection request */
#endif
   SiOptBckCalInd optBckCalInd;  /* optional backward call indicators */
#if SS7_Q767
   SiOptBckCalIndQ optBckCalIndQ;/* Q767 optional backward call indicators */
#endif
   SiCauseDgn causeDgn;          /* cause indicators */
   SiConnectedNum connNum;       /* connected number */
   SiUsr2UsrInd usr2UsrInd;      /* user to user indicators */
   SiUsr2UsrInfo usr2UsrInfo;    /* user to user information */
#if SS7_ANS88
   SiRedirInfo redirInfo;        /* redirection information */
#endif
   SiAccTrnspt accTrnspt;        /* access transport */
   SiCalModInd calModInd;        /* call modification indicators */
   SiEvntInfo evntInfo;          /* event information */
   SiRedirNum redirNum;          /* redirection number */
   SiInfoInd infoInd;            /* information indicators */
   SiInfoReqInd infoReqInd;      /* information request indicators */
#if SS7_ANS88
   SiRedirNum redirgNum;         /* redirecting number */
   SiInfoIndA infoIndA;          /* information indicators */
   SiInfoReqIndA infoReqIndA;    /* information request indicators */
#endif
   SiCgPtyCat cgPtyCat;          /* calling party category */
   SiCgPtyNum cgPtyNum;          /* calling party number */
#if SS7_ANS88
   SiIndex index;                /* index */
#endif
   SiConnReq connReq;            /* connection request */
   SiCallRef callRef;            /* call reference */
   SiNotifInd notifInd;          /* notification indicator */
   SiTxMedReq txMedUsed;         /* transmission medium used */
   SiEchoCtl echoControl;        /* echo control */
   SiAccDelInfo accDelInfo;      /* access delivery information */
   SiGenNum genNmb;              /* generic number */
   SiParmCompInfo parmCom;       /* parameter compatibility information */
   SiCllDiverInfo cllDivr;       /* call Diversion information */
   SiNetSpecFacil netFac;        /* network specific facility */
   SiRemotOper remotOper;        /* remote operations */
   SiServiceAct serviceAct;      /* service activation */
   SiRedirRestr redirRstr;       /* redirection restriction */
   SiMcidReqInd mcidReq;         /* MCID request indicators */
   SiMcidRspInd mcidRsp;         /* MCID response indicators */
   SiMsgCompInfo msgCom;         /* message compatibility information */
#if (SS7_ANS88 || SS7_ANS92)
   SiOrigLineInf origLineInf;    /* originating line information */
#endif
#if SS7_ANS92
   SiBusinessGrp businessGrp;    /* business group */
   SiNetTransport netTransport;  /* network transport */
   SiInfoInd infoInd2;           /* information indicators */
   SiNotifInd notifInd1;         /* notification indicator */
   SiRedirInfo redirInf;         /* redirection information */
#endif
#if SS7_Q767IT
   SiBackVadInd backVad;         /* backward vad indicators */
#endif
#if SS7_SINGTEL
   CllChrgeInfo chrgeInfo;       /* call charge info */
   ChrgeRateInfo rateInfo;       /* charge rate information */
   TrnkOff trnkOff;              /* trunk offering information */
#endif
} SiCnStEvnt;

typedef struct siInfoEvnt        /* Information Event */
{
   SiCallRef callRef;            /* call reference */
   SiPassAlng passAlng;          /* pass along */
   SiUsr2UsrInfo usr2UsrInfo;    /* user to user information */
   SiAccTrnspt accTrnspt;        /* access transport */
} SiInfoEvnt;

typedef struct siResmEvnt        /* resume event */
{
   SiSusResInd susResInd;        /* Suspend/Resume indicators */
#if (SS7_ANS88 || SS7_ANS92)
   SiCallRefA callRefA;          /* call reference */
#endif
   SiCallRef callRef;            /* call reference */
} SiResmEvnt;

typedef struct siStaEvnt         /* Status Event */
{
   SiRangStat rangStat;          /* range and status */
   SiCirGrpSupMTypInd cgsmti;    /* circuit grp. supervision msg. type ind. */
   SiCirStateInd cirStateInd;    /* circuit state indicators */
   SiContInd contInd;            /* continuity indicator */
   SiCauseDgn causeDgn;          /* cause indicators */
   SiParmCompInfo parmCom;       /* parameter compatibility information */
#if SS7_ANS92
   SiNatConInd natConInd;        /* Nature of connection indicators */
#endif
} SiStaEvnt;

typedef struct siRelEvnt         /* Release Event */
{
   SiCauseDgn causeDgn;          /* cause indicators */
#if SS7_ANS88
   SiRedirInfo redirInfoA;       /* redirection information */
#endif
   SiRedirInfo redirInfo;        /* redirection information */
   SiRedirNum redirNum;          /* redirection number */
#if SS7_ANS88
   SiRedirNum redirgNum;         /* redirection number */
#endif
#if (SS7_ANS88 || SS7_ANS92)
   SiCallRefA callRefA;          /* call reference */
#endif
#if SS7_ANS88
   SiSigPointCodeA sigPointCodeA;/* Signalling point code */
   SiCugIntCodeA cugIntCodeA;    /* closed group interlock code */
#endif
   SiSigPointCode sigPointCode;  /* signalling point code */
   SiAccTrnspt accTrnspt;        /* access transport */
   SiUsr2UsrInfo usr2UsrInfo;    /* user to user information */
   SiAutoCongLvl autoCongLvl;    /* automatic congestion level */
   SiAccDelInfo accDelInfo;      /* access delivery information */
   SiParmCompInfo parmCom;       /* parameter compatibility information */
   SiNetSpecFacil netFac;        /* network specific facility */
   SiRedirRestr redirRstr;       /* redirection restriction */
   SiUsr2UsrInd usr2UsrInd;      /* user to user indicators */
#if SS7_ANS92
   SiChargeNum chargeNum;        /* charge number */
   SiGenAddr genAddr;            /* generic address */
#endif
#if SS7_Q767IT
   SiBackVadInd backVad;         /* backward vad indicators */
#endif
#if SS7_SINGTEL
   TrnkOff trnkOff;              /* trunk offering information */
#endif
} SiRelEvnt;

typedef struct siSuspEvnt        /* suspend event */
{
   SiSusResInd susResInd;        /* suspend/resume indicators */
#if (SS7_ANS88 || SS7_ANS92)
   SiCallRefA callRefA;          /* call reference */
#endif
   SiCallRef callRef;            /* call reference */
} SiSuspEvnt;

typedef struct siFacEvnt         /* facility event */
{
   SiFacInd facInd;              /* facility indicator */
#if SS7_ANS88
   SiFacInfInd facInfInd;        /* facility information indicator */
   SiCdPtyNum cdPtyNum;          /* called party number */
   SiCgPtyNum cgPtyNum;          /* calling party number */
   SiCallRefA callRefA;          /* call reference */
#endif
   SiUsr2UsrInd usr2UsrInd;      /* user to user indicator */
   SiCallRef callRef;            /* call reference */
   SiCauseDgn causeDgn;          /* cause indicator */
   SiMsgCompInfo msgCom;         /* message compatibility information */
   SiParmCompInfo parmCom;       /* parameter compatibility information */
   SiRemotOper remotOper;        /* remote operations */
   SiServiceAct serviceAct;      /* service activation */
} SiFacEvnt;

typedef struct siAllSdus         /* all sdu messages */
{
   union
   {
      SiConEvnt siConEvnt;       /* ISUP Connect Event */
      SiCnStEvnt  siCnStEvnt;    /* Connect Status Event */
      SiFacEvnt siFacEvnt;       /* facility event */
      SiInfoEvnt siInfoEvnt;     /* Information Event */
      SiResmEvnt siResmEvnt;     /* resume event */
      SiStaEvnt siStaEvnt;       /* Status Event */
      SiRelEvnt siRelEvnt;       /* Release Event */
      SiSuspEvnt siSuspEvnt;     /* suspend event */
   } m;
} SiAllSdus;

#endif
