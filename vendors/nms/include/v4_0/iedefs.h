/* Message Element Structures */
#ifndef __IEDEFS__
#define __IEDEFS__

/* Turn on structure packing for Solaris */
#ifdef UNIX
#pragma pack(1)
#endif

#define netIdPln1   netIdPln
#define typNetId2   typNetId

typedef struct _accDelInfo       /* Access delivery information */
{
    ElmtHdr eh;                     /* element header */
    TknU8   delInd;                 /* delivery indicator */
    TknU8   reserved;               /* reserved for future use */
} SiAccDelInfo;

typedef struct _opServInfo       /* Operator services information */
{
    ElmtHdr eh;                     /* element header */
    TknU8   infoType;               /* information type */
    TknU8   infoVal;                /* information vaule */
} SiOpServInfo;

/* information type */

#define OSITYP_ORIGACC          0x01
#define OSITYP_BILLINFO         0x02
#define OSITYP_BILLTYPE         0x03
#define OSITYP_BILLSPEC         0x04
#define OSITYP_SPECHAND         0x05
#define OSITYP_ACCSIG           0x07

/* information value */

#define OSIVAL_UNKNOWN          0x00
#define OSIVAL_ONEPLUS          0x01
#define OSIVAL_ZEROPLUS         0x02
#define OSIVAL_ZERO             0x03

#define OSIVAL_MANSTAT          0x01
#define OSIVAL_MANPERS          0x02
#define OSIVAL_AUTOTONESTAT     0x03
#define OSIVAL_UNKSTAT          0x04
#define OSIVAL_UNKPERS          0x05
#define OSIVAL_MANUNK           0x06
#define OSIVAL_AUTOTONEUNK      0x07
#define OSIVAL_AUTOTONEPERS     0x08
#define OSIVAL_AUTOSPUNK        0x09
#define OSIVAL_AUTOSPSTAT       0x0a
#define OSIVAL_AUTOSPPERS       0x0b

#define OSIVAL_CARD14           0x01
#define OSIVAL_CARD89C          0x02
#define OSIVAL_CARDOTHER        0x03
#define OSIVAL_COLLECT          0x04
#define OSIVAL_THIRDNUM         0x05
#define OSIVAL_SENTPAID         0x06

#define OSIVAL_NIDBAUTH         0x01
#define OSIVAL_NIDBRPTAUTO      0x02
#define OSIVAL_NIDBRPTOPER      0x03
#define OSIVAL_NONIDBQRY        0x04
#define OSIVAL_NONIDBRSP        0x05
#define OSIVAL_NIDBRPTUNAVAIL   0x06
#define OSIVAL_NONIDBRSPTMOUT   0x07
#define OSIVAL_NONIDBRSPREJ     0x08
#define OSIVAL_NONIDBRSPACG     0x09
#define OSIVAL_NONIDBSCCPFAIL   0x0a

#define OSIVAL_CALLCOMP         0x01
#define OSIVAL_RATEINFO         0x02
#define OSIVAL_TROUBLE          0x03
#define OSIVAL_TIMECHRG         0x04
#define OSIVAL_CREDIT           0x05
#define OSIVAL_ASSIST           0x06

#define OSIVAL_DIAL             0x01
#define OSIVAL_DTMF             0x02

typedef struct _parmCom          /* parameter compatibility information */
{
    ElmtHdr eh;                     /* element header */
    TknU8   upgrPar1;               /* upgraded parm 1 */
    TknU8   tranXInd1;              /* transit exchange indicator */
    TknU8   relCllInd1;             /* release call indicator */
    TknU8   sndNotInd1;             /* send notification indicator */
    TknU8   dcrdMsgInd1;            /* discard message indicator */
    TknU8   dcrdParInd1;            /* discard parameter indicator */
    TknU8   spare1;                 /* spare */
    TknU8   upgrPar2;               /* upgraded parm 2 */
    TknU8   tranXInd2;              /* transit exchange indicator */
    TknU8   relCllInd2;             /* release call indicator */
    TknU8   sndNotInd2;             /* send notification indicator */
    TknU8   dcrdMsgInd2;            /* discard message indicator */
    TknU8   dcrdParInd2;            /* discard parameter indicator */
    TknU8   spare2;                 /* spare */
    TknU8   upgrPar3;               /* upgraded parm 3 */
    TknU8   tranXInd3;              /* transit exchange indicator */
    TknU8   relCllInd3;             /* release call indicator */
    TknU8   sndNotInd3;             /* send notification indicator */
    TknU8   dcrdMsgInd3;            /* discard message indicator */
    TknU8   dcrdParInd3;            /* discard parameter indicator */
    TknU8   spare3;                 /* spare */
} SiParmCompInfo;

typedef struct _msgCom           /* message compatibility information */
{
    ElmtHdr eh;                     /* element header */
    TknU8   tranXInd;               /* transit exchange indicator */
    TknU8   relCllInd;              /* release call indicator */
    TknU8   sndNotInd;              /* send notification indicator */
    TknU8   spare;                  /* spare */
    TknU8   dcrdMsgInd;             /* discard message indicator */
    TknU8   passNotPoss;            /* pass on not possible indicator */
    TknU8   tranXInd1;              /* transit exchange indicator */
    TknU8   relCllInd1;             /* release call indicator */
    TknU8   sndNotInd1;             /* send notification indicator */
    TknU8   spare1;                 /* spare */
    TknU8   dcrdMsgInd1;            /* discard message indicator */
    TknU8   passNotPoss1;           /* pass on not possible indicator */
} SiMsgCompInfo;

typedef struct _cllDivr          /* call Diversion information */
{
    ElmtHdr eh;                     /* element header */
    TknU8   notSuscr;               /* Notification subscribtion */
    TknU8   redirRsn;               /* redirection reason */
    TknU8   spare;
} SiCllDiverInfo;


/* Notification Subscribtion Option */

#define PRES_UNKNOWN       0x00
#define PRES_NOTALLOW      0x01
#define PRES_ALLOWWREDNUM  0x02
#define PRES_ALLOW         0x03

/* see redirInfo for redirRsn values */

typedef struct _propDly          /* propagation delay */
{
    ElmtHdr eh;                     /* element header */
    TknU16  delayVal;               /* delay value */
} SiPropDly;

typedef struct _redirRstr        /* redirection restriction */
{
    ElmtHdr eh;                     /* element header */
    TknU8   presRest;               /* presentation restriction */
    TknU8   spare;                  /* spare */
} SiRedirRestr;

/* see calling party number for presentation restriction values */

typedef struct _remotOper        /* remote operations */
{
    ElmtHdr eh;                     /* element header */
    TknU8   protProf;               /* protocol profile */
    TknU8   spare;                  /* spare */
    TknStr  compon;                 /* components */
} SiRemotOper;

/* Protocol profile  */

#define PP_REMOPPROT       0x11

typedef struct _netFac           /* network specific facility */
{
    ElmtHdr eh;                     /* element header */
    TknStr  netFac;                 /* network facility1 */
} SiNetSpecFacil;

typedef struct _mcidRsp          /* MCID response indicators  */
{
    ElmtHdr eh;                     /* element header */
    TknU8   rspInd;                 /* mcid response indicators */
    TknU8   hldInd;                 /* hold indicators */
    TknU8   spare;                  /* spare */
} SiMcidRspInd;

/* MCID response Indicator */

#define MCID_NOTINCLDD     0x00
#define MCID_INCLDD        0x01

/* Hold provided indicator */

#define HOLD_NOTPROV       0x00
#define HOLD_PROV          0x01

typedef struct _mcidReq          /* MCID request indicators  */
{
    ElmtHdr eh;                     /* element header */
    TknU8   reqInd;                 /* mcid request indicators */
    TknU8   hldInd;                 /* hold indicators */
    TknU8   spare;                  /* spare */
} SiMcidReqInd;

/* MCID request Indicator */

#define MCID_NOTREQD       0x00
#define MCID_REQD          0x01

/* Holding Indicator */

#define HOLD_NOTREQD       0x00
#define HOLD_REQD          0x01

typedef struct _mlppPrec         /* MLPP precedence  */
{
    ElmtHdr eh;                     /* element header */
    TknU8   precdLvl;               /* precedence level */
    TknU8   spare1;                 /* spare */
    TknU8   lfb;                    /* LFB */
    TknU8   spare2;                 /* spare */
    TknU8   frstDig;                /* first digit */
    TknU8   scndDig;                /* second digit */
    TknU8   thrdDig;                /* third digit */
    TknU8   frthDig;                /* fourth digit */
    TknU32  servDomain;             /* service domain */
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

typedef struct _accTrnspt        /* Access transport */
{
    ElmtHdr eh;                    /* element header */
    TknStr  infoElmts;             /* Information elements */
} SiAccTrnspt;

typedef struct _autoCongLvl      /* Autonatic Congestion Level */
{
    ElmtHdr eh;                     /* element header */
    TknU8   auCongLvl;              /* auto congestion level */
} SiAutoCongLvl;

/* Automatic Congestion Level Defines */

#define ACLVL_LVL1         0x01
#define ACLVL_LVL2         0x02
#define ACLVL_LVL3         0x03

typedef struct _bckCalInd        /* Backward Call Indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   chrgInd;                /* Charge Indicator */
    TknU8   cadPtyStatInd;          /* called party status indicator */
    TknU8   cadPtyCatInd;           /* called party category indicator */
    TknU8   end2EndMethInd;         /* end to end method indicator */
    TknU8   intInd;                 /* interworking indicator */
    TknU8   segInd;                 /* segmentation indicator */
    TknU8   end2EndInfoInd;         /* end to end information indicator */
    TknU8   isdnUsrPrtInd;          /* ISDN User Part indicator */
    TknU8   holdInd;                /* holding indicator */
    TknU8   isdnAccInd;             /* ISDN access indicator */
    TknU8   echoCtrlDevInd;         /* echo control device indicator */
    TknU8   sccpMethInd;            /* SCCP method indicator */
    TknU8   spare;                  /* spare bits */
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

/* Segmentation Indicator */

#define SEGIND_NOIND       0x00
#define SEGIND_INFO        0x01

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

typedef struct _calModInd        /* Call Modification Indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   modInd;                 /* call modification indicators */
    TknU8   spare;
} SiCalModInd;

/* Modification Indicator */

#define MOD_SERV1          0x01
#define MOD_SERV2          0x02

typedef struct _callRef          /* Call Reference */
{
    ElmtHdr eh;                     /* element header */
    TknU32  callId;                 /* call identity */
    TknU32  pntCde;                 /* point code */
} SiCallRef;

typedef struct _cdPtyNum         /* Called Party Number */
{
    ElmtHdr eh;                     /* element header */
    TknU8   natAddrInd;             /* nature of addresss indicator */
    TknU8   oddEven;                /* odd or even */
    TknU8   spare;
    TknU8   reserved;
    TknU8   numPlan;                /* numbering plan */
    TknU8   innInd;                 /* international network number indicator */
    TknStr  addrSig;                /* Address Signal */
} SiCdPtyNum;

/* Nature of Address Defines ISUP */

#define SUBSNUM           0x01
#define NATNUM            0x03
#define INTNATNUM         0x04

/* defines for ANSI - called party number */

#define SUBSNUMOPREQ       0x71  /* subscriber number, operator requested */
#define NATNUMOPREQ        0x72  /* national number, operator requested */
#define INTNATNUMOPREQ     0x73  /* international number, operator requested */
#define NONUMPRESOPREQ     0x74  /* no number present, operator requested */
#define NONUMPRESCUTTHRU   0x75  /* no number present, cut-through call to carrier */
#define NINEFIVEOH         0x76  /* 950+ service */
#define TSTLINETSTCODE     0x77  /* test line test code - for both called and calling party number */

/* additional defines for ANSI - calling party number */
#define NONUNQSUBSNUM      0x71  /* non-unique subscriber number */
#define NONUNQNATNUM       0x73  /* non-unique national number */
#define NONUNQINTNATNUM    0x74  /* non-unique international number */

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

typedef struct _locNum         /* Location Number */
{
    ElmtHdr eh;                     /* element header */
    TknU8   natAddrInd;             /* nature of addresss indicator */
    TknU8   oddEven;                /* odd or even */
    TknU8   scrnInd;                /* screen indicator */
    TknU8   presRest;               /* Address presentation restricted ind. */
    TknU8   numPlan;                /* numbering plan */
    TknU8   niInd;                  /* number incomplete indicator */
    TknStr  addrSig;                /* Address Signal */
} SiLocNum;

typedef struct _cgPtyNum         /* Calling Party Number */
{
    ElmtHdr eh;                     /* element header */
    TknU8   natAddrInd;             /* nature of addresss indicator */
    TknU8   oddEven;                /* odd or even */
    TknU8   scrnInd;                /* screen indicator */
    TknU8   presRest;               /* Address presentation restricted ind. */
    TknU8   numPlan;                /* numbering plan */
    TknU8   niInd;                  /* number incomplete indicator */
    TknU8   spare;
    TknStr  addrSig;                /* Address Signal */
} SiCgPtyNum;

/*
 * additional defines for ANSI nature of address indicator - calling party number
 * see above in called party number
 */

/* Screen Indicator Defines */

#define USRPROVNOTVER      0x00
#define USRPROV            0x01
#define USRPROVVERFAIL     0x02
#define NETPROV            0x03

/* Presentation Restriction Defines */

#define PRESALLOW          0x00
#define PRESREST           0x01
#define ADDRNOAVAIL        0x02
#define PRESBLKTGL         0x02
#define PRESNOIND          0x03


/* number incomplete indicator */

#define NBMCMLTE           0x00
#define NBMINCMLTE         0x01
#define NMBCOMPLETE        0x00
#define NMBINCOMPLETE      0x01

typedef struct _genNum           /* Generic Number */
{
    ElmtHdr eh;                     /* element header */
    TknU8   nmbQual;                /* number qualifier */
    TknU8   natAddrInd;             /* nature of addresss indicator */
    TknU8   oddEven;                /* odd or even */
    TknU8   scrnInd;                /* screen indicator */
    TknU8   presRest;               /* Address presentation restricted ind. */
    TknU8   numPlan;                /* numbering plan */
    TknU8   niInd;                  /* number incomplete indicator */
    TknStr  addrSig;                /* Address Signal */
} SiGenNum;

/* Number qualifier indicator */

#define NQ_ADDCDMNB        0x01
#define NQ_ADDCONMNB       0x05
#define NQ_ADDCGNMB        0x06
#define NQ_ORIGCDNMB       0x07
#define NQ_ORIGRGDNMB      0x08
#define NQ_ORIGRDNMB       0x09

typedef struct _cgPtyCat         /* Calling Party Category */
{
    ElmtHdr eh;                     /* element header */
    TknU8   cgPtyCat;               /* calling party category */
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

typedef struct _siCauseDgn       /* Cause Indicator */
{
    ElmtHdr eh;                     /* element header */
    TknU8   location;               /* location */
    TknU8   spare;
    TknU8   cdeStand;               /* coding standard */
    TknU8   recommend;              /* recommendation */
    TknU8   causeVal;               /* cause value */
    TknStr  dgnVal;                 /* diagnostics */
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

#define CCINFOELMSSG       96    /* mandatory info element is missing */

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

typedef struct _cirGrpSupMTypInd /* Circuit Group Supervision Msg. Type Ind. */
{
    ElmtHdr eh;                     /* element header */
    TknU8   typeInd;                /* circuit group supervision msg. type ind. */
    TknU8   spare;
} SiCirGrpSupMTypInd;

/* Type Indicator Defines */

#define MAINT              0x00
#define HARDFAIL           0x01

/* defines for ANSI */

#define SOFTWAREGEN        0x02  /* software generated */

/* defines for ANSI 92 */
#define BLOCK_WO_REL       0x00
#define BLOCK_REL          0x01

typedef struct _cirStateInd      /* Circuit State Indicators */
{
    ElmtHdr eh;                     /* element header */
    TknStr  cirSteInd;              /* circuit state indicator. */
} SiCirStateInd;

typedef struct _cugIntCode       /* Closed User Group Interlock Code */
{
    ElmtHdr eh;                     /* element header */
    TknU8   dig2;                   /* Digit 2 */
    TknU8   dig1;                   /* Digit 1 */
    TknU8   dig4;                   /* Digit 4 */
    TknU8   dig3;                   /* Digit 3 */
    TknU16  binCde;                 /* binary Code */
    TknU16  ISDNIdent;              /* ISDN identifier */
} SiCugIntCode;

typedef struct _connectedNum     /* Connected number */
{
    ElmtHdr eh;                     /* element header */
    TknU8   natAddr;                /* nature of addresss indicator */
    TknU8   oddEven;                /* odd or even */
    TknU8   scrnInd;                /* screen indicator */
    TknU8   presRest;               /* Address presentation restricted ind. */
    TknU8   numPlan;                /* numbering plan */
    TknU8   spare;
    TknStr  addrSig;                /* Address Signal */
} SiConnectedNum;

/* See calling/called party number for values */

typedef struct _connReq          /* Connection Request */
{
    ElmtHdr eh;                     /* element header */
    TknU32  locRef;                 /* local reference(really a 24bit quantity) */
    TknU32  pntCde;                 /* point code */
    TknU8   protClass;              /* protocol classs */
    TknU8   credit;                 /* credit */
} SiConnReq;

typedef struct _contInd          /* Continuity indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   contInd;                /* continuity indicator */
    TknU8   spare;
} SiContInd;

/* Continuity indicators */

#define CONT_CHKFAIL       0x00
#define CONT_CHKSUCC       0x01

typedef struct _evntInfo         /* Event Information */
{
    ElmtHdr eh;                     /* element header */
    TknU8   evntInd;                /* event indicators */
    TknU8   evntPresResInd;         /* event presentation restriction indicators*/
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

typedef struct _facInd           /* Facility Indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   facInd;                 /* facility indicator */
} SiFacInd;

/* Facility Indicators  */

#define FI_USR2USRSERV     0x02

/* defines for ANSI */

#define FI_COMPCALLBUSY    0x01  /* completion of calls to busy subscriber */
#define FI_CCBSCONT        0xfd  /* CCBS continue */
#define FI_BUSYFREE        0xfe  /* busy/free status information */

typedef struct _fwdCallInd       /* Forward Call Indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   natIntCallInd;          /* National/International Call Indicator */
    TknU8   end2EndMethInd;         /* end to end method indicator */
    TknU8   intInd;                 /* interworking indicator */
    TknU8   segInd;                 /* segmentation indicator */
    TknU8   end2EndInfoInd;         /* end to end information indicator */
    TknU8   isdnUsrPrtInd;          /* ISDN User Part indicator */
    TknU8   isdnUsrPrtPrfInd;       /* ISDN User Part preference indicator */
    TknU8   isdnAccInd;             /* ISDN access indicator */
    TknU8   sccpMethInd;            /* SCCP method indicator */
    TknU8   spare;                  /* spare bit */
    TknU8   natReserved;            /* reserved for national use */
} SiFwdCallInd;

/* national/international call indicators  */

#define CALL_NAT           0x00
#define CALL_INTERNAT      0x01

/* ISDN User Part Preference Indicator Defines */

#define PREF_PREFAW        0x00
#define PREF_NOTREQAW      0x01
#define PREF_REQAW         0x02

/* see backward call indicators for other values */

typedef struct _infoInd          /* Information Indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   cgPtyAddrRespInd;       /* calling party address response ind. */
    TknU8   holdProvInd;            /* hold provided indicator */
    TknU8   spare1;                 /* spare */
    TknU8   cgPtyCatRespInd;        /* calling party category response ind. */
    TknU8   chrgInfoRespInd;        /* charge information response indicator */
    TknU8   solInfoInd;             /* solicitation information indicator */
    TknU8   connAddrRspInd;         /* connected address response indicator */
    TknU8   redirAddrRspInd;        /* redirection address response indicator*/
    TknU8   indexRspInd;            /* index response indicator */
    TknU8   spare2;                 /* spare */
    TknU8   mlbgInfoInd;            /* multi location business group information indicator */
    TknU8   reserved;               /* reserved */
} SiInfoInd;

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

/* multi-location business group information response indicator */

#define MLBGINFONOTINCL     0x00  /* multi-location business group information not included */
#define MLBGINFOINCL        0x01  /* multi-location business group information included */

typedef struct _infoReqInd       /* Information Request Indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   cgPtyAdReqInd;          /* calling party address request ind. */
    TknU8   holdingInd;             /* holding indicator */
    TknU8   spare1;                 /* spare */
    TknU8   cgPtyCatReqInd;         /* calling party category request ind. */
    TknU8   chrgInfoReqInd;         /* charge information request indicator */
    TknU8   malCaIdReqInd;          /* malicious call id request indicator */
    TknU8   mlbgInfoInd;            /* multi location business group information indicator */
    TknU8   connAddrReqInd;         /* connected address request indicator */
    TknU8   redirAddrReqInd;        /* redirection address request indicator */
    TknU8   indexReqInd;            /* index request indicator */
    TknU8   spare2;                 /* spare */
    TknU8   spare3;                 /* spare */
    TknU8   reserved;
} SiInfoReqInd;

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

/* multi-location business group information request indicator */

#define MLBGINFONOTREQ      0x00  /* multi-location business group information not requested */
#define MLBGINFOREQ         0x01  /* multi-location business group information requested */

typedef struct _natConInd         /* Nature of Connection Indicator */
{
   ElmtHdr eh;                   /* element header */
   TknU8 satInd;                 /* Satellite Indicator */
   TknU8 contChkInd;             /* continuity check indicator */
   TknU8 echoCntrlDevInd;        /* echo control device indicator */
   TknU8 spare;
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


typedef struct _optBckCalInd     /* Optional Backward Call Indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   inbndInfoInd;           /* in-band information indicator */
    TknU8   caFwdMayOcc;            /* call forwarding may occur indicator */
    TknU8   segInd;                 /* simple segmentation indicator */
    TknU8   netDelay;               /* network excessive delay indicator */
    TknU8   usrNetIneractInd;       /* user-network interaction indicator */
    TknU8   mlppUsrInd;             /* MLPP user indicator */
    TknU8   spare;
    TknU8   reserved;               /* reserved for national use */
} SiOptBckCalInd;

/* In-band Information Indicator */

#define INBND_NOIND        0x00
#define INBND_AVAIL        0x01

/* Call Forwarding May Occur Indicator */

#define CAFWD_NOIND        0x00
#define CAFWD_MAYOCC       0x01

/* User-Network Interaction Indicator */

#define USERNET_NOIND          0x00
#define USERNET_INTERACTOCCUR  0x01

typedef struct _opFwdCalInd      /* Optional Forward Call Indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   clsdUGrpCaInd;          /* closed user group call indicator */
    TknU8   segInd;                 /* simple segmentation indicator */
    TknU8   spare;                  /* spare */
    TknU8   clidReqInd;             /* connected line identity request indicator */
    TknU8   ccbsCallInd;            /* CCBS call indicator */
    TknU8   callgPtyNumIncomInd;    /* calling party number incomplete ind. */
    TknU8   connAddrReqInd1;        /* connected address request indicator */
} SiOpFwdCalInd;

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

/* simple segmentation indicator */

#define NOTSEGMENTED    0x00    /* message not segmented */
#define SEGMENTED	0x001	/* message is segmented */

/* connected line identity request indicator */

#define CLIDNOTREQ	0x00	/* connected line identity not requested */
#define CLIDREQ     0x01    /* connected line identity requested */

typedef struct _origCdNum        /* Original Called Number */
{
    ElmtHdr eh;                     /* element header */
    TknU8   natAddr;                /* nature of addresss indicator */
    TknU8   oddEven;                /* odd or even */
    TknU8   spare1;                 /* spare */
    TknU8   presRest;               /* Address presentation restricted ind. */
    TknU8   numPlan;                /* numbering plan */
    TknU8   spare2;                 /* spare */
    TknStr  addrSig;                /* Address Signal */
} SiOrigCdNum;

/* see called/calling party number for values */

typedef struct _rangStat         /* Range and Status */
{
    ElmtHdr eh;                     /* element header */
    TknU8   range;                  /* range */
    TknStr  status;                 /* status */
} SiRangStat;

/* maintenance blocking states */

#define MNOBLK          0x00   /* not blocked */
#define MLOCBLKED       0x01   /* locally blocked */
#define MRMTBLKED       0x02   /* remotely blocked */
#define MLOCRMTBLKED    0x03   /* locally and remotely blocked */

#define UNEQUIP         0x03   /* unequipped */

/* hardware blocking states */

#define HNOBLK          0x00   /* not blocked */
#define HLOCBLKED       0x10   /* locally blocked */
#define HRMTBLKED       0x20   /* remotely blocked */
#define HLOCRMTBLKED    0x30   /* locally and remotely blocked */

/* call processing states */

#define CALL_IDLE       0x0c   /* idle */
#define INCBUSY         0x04   /* incoming busy */
#define OUTBUSY         0x08   /* outgoing busy */
#define TRANS           0x00   /* transient */

#define CSIDLE          0x0c
#define CSINCBUSY       0x04
#define CSOUTBUSY       0x08

#define BSNOTBLK		0x00
#define BSLOCBLK        0x01
#define BSRMTBLK        0x02
#define BSLOCRMTBLK     0x03

typedef struct _redirgNum        /* Redirecting Number */
{
    ElmtHdr eh;                     /* element header */
    TknU8   natAddr;                /* nature of addresss indicator */
    TknU8   oddEven;                /* odd or even */
    TknU8   spare1;                 /* spare */
    TknU8   presRest;               /* Address presentation restricted ind. */
    TknU8   numPlan;                /* numbering plan */
    TknU8   spare2;                 /* spare */
    TknStr  addrSig;                /* Address Signal */
} SiRedirgNum;

typedef struct _redirNum         /* Redirection Number */
{
    ElmtHdr eh;                     /* element header */
    TknU8   natAddr;                /* nature of addresss indicator */
    TknU8   oddEven;                /* odd or even */
    TknU8   spare;                  /* spare */
    TknU8   numPlan;                /* numbering plan */
    TknU8   innInd;                 /* internal network number indicator */
    TknStr  addrSig;                /* Address Signal */
} SiRedirNum;

/* see called/calling party number for values */

typedef struct _redirInfo        /* Redirection Information */
{
    ElmtHdr eh;                     /* element header */
    TknU8   redirInd;               /* redirection indicator */
    TknU8   spare1;                 /* spare */
    TknU8   origRedirReas;          /* original redirection reason */
    TknU8   redirCnt;               /* redirection count */
    TknU8   spare2;                 /* spare */
    TknU8   redirReas;              /* redirection reason */
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

/* maximum number of redirections */

#define MAX_REDIR          5

/* defines for ANSI */

#define REAS_FIXED         0x03
#define REAS_VARIABLE      0x04

typedef struct _sigPointCode     /* Signalling Point Code */
{
    ElmtHdr eh;                     /* element header */
    TknU32  sigPointCode;           /* signalling point code */
} SiSigPointCode;

typedef struct _subNum           /* Subsequent Number */
{
    ElmtHdr eh;                     /* element header */
    TknU8   oddEven;                /* odd or even */
    TknU8   spare;                  /* spare */
    TknStr  addrSig;                /* Address Signal */
} SiSubNum;

typedef struct _susResInd        /* Suspend/Resume indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   susResInd;              /* suspend/resume indicators */
    TknU8   spare;                  /* spare */
} SiSusResInd;

/* Suspend/Resume Indicators */

#define SR_ISDNSUBINIT     0x00
#define SR_NETINIT         0x01

typedef struct _echoControl      /* echo control indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   outEchoRsp;             /* outgoing echo control device response */
    TknU8   incEchoRsp;             /* incoming echo control device response */
    TknU8   outEchoReq;             /* outgoing echo control device request */
    TknU8   incEchoReq;             /* incoming echo control device request */
} SiEchoCtl;

/* Echo Control device req/rsp */

#define ECHCDEV_NOINFOINCL 0x00
#define ECHCDEV_NOTINCL    0x01
#define ECHCDEV_INCL       0x02

#define ECHCDEV_ACTREQ	   0x01
#define ECHCDEV_DEACTREQ   0x02

typedef struct _tranNetSel       /* Transit Network Selection */
{
    ElmtHdr eh;                     /* element header */
    TknU8   netIdPln;               /* network id plan */
    TknU8   typNetId;               /* type of network identification */
    TknU8   oddEven;                /* odd/even */
    TknU8   spare;
    TknStr  netId;                  /* network identification */
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

typedef struct _txMedReq         /* Transmission Medium Requirement */
{
    ElmtHdr eh;                     /* element header */
    TknU8   trMedReq;               /* tranmission medium requirement */
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

typedef struct _usrServInfo      /* User Service Information */
{
    ElmtHdr eh;                     /* element header */
    TknU8   infoTranCap;            /* information transfer capability */
    TknU8   cdeStand;               /* coding standard */
    TknU8   infoTranRate0;          /* information transfer rate */
    TknU8   tranMode;               /* transfer mode */
    TknU8   establish;              /* establishment */
    TknU8   config;                 /* configuration */
    TknU8   chanStruct;             /* structure */
    TknU8   infoTranRate1;          /* information transfer rate */
    TknU8   symmetry;               /* symmetry */
    TknU8   usrInfLyr1Prot;         /* usr information layer 1 protocol */
    TknU8   lyr1Ident;              /* layer 1 identity */
    TknU8   usrRate;                /* user rate */
    TknU8   negot;                  /* negotiation */
    TknU8   syncAsync;              /* synchronous/asynchronous */
    TknU8   flcOnRx;                /* flow control on reception */
    TknU8   flcOnTx;                /* flow control on transmission */
    TknU8   niClkOnRx;              /* network independent clock on reception */
    TknU8   niClkOnTx;              /* network independent clock on transmission*/
    TknU8   interRate;              /* intermediate rate */
    TknU8   inOutBandNeg;           /* inband/outband negotiation */
    TknU8   asgnrAsgne;             /* assignor/assignee */
    TknU8   logLnkNegot;            /* logical link identifier negotiation */
    TknU8   mode;                   /* mode of operation */
    TknU8   multiFrm;               /* multiple frame establishment support */
    TknU8   hdrNohdr;               /* rate adaption header/no header */
    TknU8   parity;                 /* parity information */
    TknU8   nmbDatBits;             /* number of data bits excluding parity bit */
    TknU8   nmbStpBits;             /* number of stop bits */
    TknU8   modemType;              /* modem type */
    TknU8   duplexMode;             /* duplex mode */
    TknU8   usrInfLyr2Prot;         /* user information layer 2 protocol */
    TknU8   lyr2Ident;              /* layer 2 identity */
    TknU8   usrInfLyr3Prot;         /* user information layer 3 protocol */
    TknU8   lyr3Ident;              /* layer 3 identity */
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

typedef struct _usr2UsrInd       /* User to User indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   type;                   /* type */
    TknU8   serv1;                  /* service 1 */
    TknU8   serv2;                  /* service 2 */
    TknU8   serv3;                  /* service 3 */
    TknU8   spare;                  /* spare */
    TknU8   netDscrdInd;            /* network discard indicator */
} SiUsr2UsrInd;

typedef struct _usr2UsrInfo      /* User to user information */
{
    ElmtHdr eh;                     /* element header */
    TknStr  info;                   /* user to user information */
} SiUsr2UsrInfo;

typedef struct _passAlng          /* Pass Along */
{
   ElmtHdr eh;                   /* element header */
   TknStr passAlng;              /* pass along */
} SiPassAlng;

typedef struct _siEndOp           /* End of Optional Parameters */
{
   ElmtHdr eh;                   /* element header */
   TknU8 nullVal;                /* null value, if present */
} SiEndOp;

typedef struct _siPduHdr          /* pdu header */
{
   ElmtHdr eh;                   /* element header */
   TknU8 msgType;                /* Message Type */
} SiPduHdr;

typedef struct _chargeNum        /* Charge Number */
{
    ElmtHdr eh;                     /* element header */
    TknU8   natAddrInd;             /* nature of addresss indicator */
    TknU8   oddEven;                /* odd or even */
    TknU8   reserved;
    TknU8   numPlan;                /* numbering plan */
    TknU8   spare;
    TknStr  addrSig;                /* Address Signal */
} SiChargeNum;

/* see called/calling party number for values */

typedef struct _cirGrpCharInd    /* Circuit group characteristic indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   cirGrpCarInd;           /* circuit group carrier indicator */
    TknU8   dblSzCtrlInd;           /* double seizing control indicator */
    TknU8   alarmCarInd;            /* alarm carrier indicator */
    TknU8   contChkReqInd;          /* continuity check requirements indicator */
} SiCirGrpCharInd;

/* circuit group carrier indicator */

#define CG_UNKNOWN         0x00  /* unknown */
#define CG_ANALOG          0x01  /* analog */
#define CG_DIGITAL         0x02  /* digital */
#define CG_ANALDIG         0x03  /* digital and analog */

/* double seizing control indicator */

#define DS_UNKNOWN         0x00  /* unknown */
#define DS_NOCIC           0x00  /* no cic control */
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

typedef struct _cirIdName        /* Circuit ID Name */
{
    ElmtHdr eh;                     /* element header */
    TknStr  trunkNumClli;           /* trunk number and clli code */
    TknStr  clliCodeA;              /* CLLI Code - Office A */
    TknStr  clliCodeZ;              /* CLLI Code - Office Z */
} SiCirIdName;

typedef struct _cirValRspInd     /* Circuit validation response indicator */
{
    ElmtHdr eh;                     /* element header */
    TknU8   cirValRspInd;           /* user to user info */
} SiCirValRspInd;

/* circuit validation response indicator */

#define CV_SUCCESS         0x00  /* successful */
#define CV_FAILURE         0x01  /* failure */

typedef struct _cugChkRspInd     /* CUG check */
{
    ElmtHdr eh;                     /* element header */
    TknU8   accessInd;              /* access indicator */
    TknU8   divergInd;              /* divergence indicator */
    TknU8   chkSuccInd;             /* check successful indicator */
    TknU8   normCallInd;            /* normal call indicator */
    TknU8   cugCallInd;             /* closed user group call indicator */
} SiCUGChkRspInd;

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

typedef struct _clli             /* Common Language Location Idenification */
{
    ElmtHdr eh;                     /* element header */
    TknStr  clliCode;               /* clli codes */
} SiCLLI;

typedef struct _facInfInd        /* Facility Information Indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   calldPtyFreeInd;        /* called party free indicator */
    TknU8   callgPtyAnsInd;         /* callg party answer indicator */
    TknU8   facReqEnqInd;           /* facility request enquiry indicator */
    TknU8   facReqActInd;           /* facility request active indicator */
    TknU8   spare;                  /* spare bits E-H */
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

typedef struct _index            /* Index  */
{
    ElmtHdr eh;                     /* element header */
    TknU32  index;                  /* index */
} SiIndex;

typedef struct _origLineInf      /* Orignating Line Information */
{
    ElmtHdr eh;                     /* element header */
    TknU8   lineInfo;               /* originating line information */
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


typedef struct _outgTrkGrpNum    /* Outgoing Trunk Group Number */
{
    ElmtHdr eh;                     /* element header */
    TknStr  digits;                 /* digits */
} SiOutgTrkGrpNum;


typedef struct _notifInd         /* (Generic) Notification Indicator */
{
    ElmtHdr eh;                     /* element header */
    TknU8   notifInd;               /* Notification Indicator */
} SiNotifInd;

#define	NI_CALLDELAY	0x04	/* call completion delay */
#define NI_CALLWAIT		0x60	/* call waiting */
#define NI_REMHLD		0x79	/* remote hold */
#define NI_REMHLDREL	0x7a	/* remote hold released */
#define NI_CALLFWDED	0x7b	/* call is forwarded */

typedef struct _serviceAct       /* Service Activation */
{
    ElmtHdr eh;                     /* element header */
    TknStr  serviceAct;             /* service activation */
} SiServiceAct;

typedef struct _serviceCode      /* Service Code */
{
    ElmtHdr eh;                     /* element header */
    TknU8   serviceCode;            /* service code */
} SiServiceCode;

typedef struct _genAddr          /* Generic Address */
{
    ElmtHdr eh;                     /* element header */
    TknU8   typeOfAddr;             /* type of address */
    TknU8   natAddr;                /* nature of address indicator */
    TknU8   oddEven;                /* odd or even address signal */
    TknU8   reserved;               /* reserved for national use */
    TknU8   presRest;               /* presentation restriction */
    TknU8   numPlan;                /* numbering plan */
    TknU8   spare;                  /* spare bit */
    TknStr  addrSig;                /* addressing signal */
} SiGenAddr;

/* Type Of Address */
#define DIALNUM            0x00
#define DESTNUM            0x01
#define SUPADDR_FAIL       0x02
#define SUPADDR_NOTSCREEN  0x03
#define COMPLNUM           0x04
#define TRANSFER1          0xfd
#define TRANSFER2          0xfc
#define TRANSFER3          0xfb
#define TRANSFER4          0xfa
#define TRANSFER5          0xf9
#define TRANSFER6          0xf8
#define CESID              0xfe
/* others - see called/calling party */

typedef struct _genDigits        /* Generic Digits */
{
    ElmtHdr eh;                     /* element header */
    TknU8   typeOfDigits;           /* type of digits */
    TknU8   encodeScheme;           /* encoding scheme */
    TknStr  digits;                 /* digits */
} SiGenDigits;

/* Type of Digits */
#define ACCTCODE           0x00
#define AUTHCODE           0x01
#define PRIVNETMARK        0x02
#define BUSCOMMGRID        0x03

/* Encoding Scheme */
#define ES_BCD_EVEN       0x00
#define ES_BCD_ODD        0x01
#define ES_IA5            0x02
#define ES_BIN            0x03

typedef struct _businessGrp      /* Business Group */
{
    ElmtHdr eh;                     /* element header */
    TknU8   partySel;               /* party selector */
    TknU8   linePrivInfInd;         /* line privileges info. ident. */
    TknU8   BGIDident;              /* BGID identifier  */
    TknU8   attendStat;             /* attendant status */
    TknU8   spare;
    TknU32  busiGrpIdent;           /* business group identifier */
    TknU16  subGrpIdent;            /* sub-group identifier */
    TknU8   linePriv;               /* line privileges */
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

typedef struct _carrierId        /* Carrier ID */
{
    ElmtHdr eh;                     /* element header */
    TknU8   netIdPln;               /* network id plan */
    TknU8   typNetId;               /* type of network identification */
    TknU8   spare;
    TknU8   CIDigit1;               /* Network Identity Digit 1 */
    TknU8   CIDigit2;               /* Network Identity Digit 2 */
    TknU8   CIDigit3;               /* Network Identity Digit 3 */
    TknU8   CIDigit4;               /* Network Identity Digit 4 */
} SiCarrierId;

/* network id plan, type of network id - see SiTranNetSel */

typedef struct _carrierSelInf    /* Carrier Selection Information  */
{
    ElmtHdr eh;                     /* element header */
    TknU8   carrierSelInf;          /* carrier selection information */
} SiCarrierSelInf;

/* Carrier Selection Information */
#define CARSEL_NOIND              0x00
#define CARSEL_PRESUB_NOINPUT     0x01
#define CARSEL_PRESUB_INPUT       0x02
#define CARSEL_PRESUB_INPUTUNDET  0x03
#define CARSEL_NOTPRESUB_INPUT    0x04

typedef struct _egress           /* Egress Service */
{
    ElmtHdr eh;                     /* element header */
    TknStr  egress;                 /* egress */
} SiEgress;

typedef struct _jurisInf         /* Jurisdiction Information */
{
    ElmtHdr eh;                     /* element header */
    TknU8   addrSig1;               /* address signal 1 */
    TknU8   addrSig2;               /* address signal 2 */
    TknU8   addrSig3;               /* address signal 3 */
    TknU8   addrSig4;               /* address signal 4 */
    TknU8   addrSig5;               /* address signal 5 */
    TknU8   addrSig6;               /* address signal 6 */
} SiJurisInf;

typedef struct _netTransport     /* Network Transport */
{
    ElmtHdr eh;                     /* element header */
    TknStr  netTransport;           /* network transport */
} SiNetTransport;

typedef struct _specProcReq      /* Special Processing Request */
{
    ElmtHdr eh;                     /* element header */
    TknU8   specProcReq;            /* special processing request */
} SiSpecProcReq;

typedef struct _transReq          /* Transaction Request */
{
   ElmtHdr eh;                   /* element header */
   TknU32 transId;               /* transaction id */
   TknStr SCCPAddr;              /* SCCP address */
} SiTransReq;

typedef struct _cirAssignMap     /* Circuit Assignment Map */
{
    ElmtHdr eh;                   /* element header */
    TknU8   mapFormat;              /* map format */
    TknU8   spare;
    TknStr  map;                    /* map */
} SiCirAssignMap;

/* Map Format */

#define MAP_DS1         0x01

typedef struct _genName     /* Generic Name */
{
   ElmtHdr   eh;                   /* element header */
   TknU8     presRest;
   TknU8     spare;
   TknU8     availability;
   TknU8     type;
   TknStr    name;
} SiGenName;

/* Availability */

#define GNA_AVAIL           0x00
#define GNA_NOTAVAIL        0x01

/* Type of Name */
#define GNT_CALLING        0x01
#define GNT_ORIGCALLED     0x02
#define GNT_REDIRECTING    0x03
#define GNT_CONNECTED      0x04


typedef struct _hopCount     /* Hop Counter */
{
   ElmtHdr eh;                   /* element header */
   TknU8     hopCount;
   TknU8     spare;
} SiHopCount;

/* for NTTI */

typedef struct _msgAreaInfo     /* Message Area Information */
{
    ElmtHdr eh;
    TknU8   oddEven;
    TknU8   infoInd;
    TknStr  info;
} SiMsgAreaInfo;

typedef struct _chargeInfo      /* Charge Information */
{
    ElmtHdr eh;
    TknStr  chargeInfo;
} SiChargeInfo;

typedef struct _chargeInfoType  /* Charge Information Type */
{
    ElmtHdr eh;
    TknU8   chargeInfoType;
} SiChargeInfoType;

typedef struct _chargeInfoDly   /* Charge Information Delay */
{
    ElmtHdr eh;
    TknStr  chargeInfo;
} SiChargeInfoDly;

typedef struct _carrierInfoTrans /* Carrier Information Transfer*/
{
    ElmtHdr eh;
    TknU8   infoType;
    TknU8   spare;
    TknStr  carrierInfo;
} SiCarrierInfoTrans;

typedef struct _contractorNum   /* Contractor Number */
{
    ElmtHdr eh;                     /* element header */
    TknU8   natAddr;                /* nature of address indicator */
    TknU8   oddEven;                /* odd or even address signal */
    TknU8   spare1;                 /* spare bit 7, octet 2*/
    TknU8   numPlan;                /* numbering plan */
    TknU8   spare2;                 /* spare bits 1-4, octet 2 */
    TknStr  addrSig;                /* addressing signal */
} SiContractorNum;


typedef struct _cgNumNonNotRsn
{
    ElmtHdr eh;                     /* element header */
    TknU8   nonNotRsn;              /* non notification reason */
} SiCgNumNonNotRsn;

/*-----------------11/29/00 2:40PM------------------
 * New set of parameters added for 3.8
 * --------------------------------------------------*/
typedef struct _bckGVNS
{
    ElmtHdr eh;                     /* element header */
    TknU8   termAccInd;             /* Terminating access indicator */
    TknU8   spare1;                 /* bits C-G */
} SiBckGVNS;
/*termAccInd values*/
#define TERM_ACC_NO_INFO         0
#define TERM_ACC_DEDICATED       1
#define TERM_ACC_SWITCHED        2
#define TERM_ACC_SPARE           3

typedef struct _callDivTrtmnt       /* Call diversion Treatment Ind */
{
    ElmtHdr eh;                     /* element header */
    TknU8   callToBeDiv;            /* call to be diverted indicator */
    TknU8   spare1;                 /* bits C-G */
} SiCallDivTrtmnt;
/*callToBeDiv values*/
#define CALL_DIV_NO_INDICATION   0
#define CALL_DIV_ALLOWED         1
#define CALL_DIV_NOT_ALLOWED     2
#define CALL_DIV_SPARE           3

typedef struct _callOffTrtmnt       /* Call offering Treatment Ind */
{
    ElmtHdr eh;                     /* element header */
    TknU8   callToBeOff;            /* call to be offered indicator */
    TknU8   spare1;                 /* bits C-G */
} SiCallOffTrtmnt;
/*callToBeOff values*/
#define CALL_OFF_NO_INDICATION   0
#define CALL_OFF_ALLOWED         1
#define CALL_OFF_NOT_ALLOWED     2
#define CALL_OFF_SPARE           3

typedef struct _callXferNum         /* Call Transfer Number */
{
    ElmtHdr eh;                     /* element header */
    TknU8   natAddrInd;             /* nature of addresss indicator */
    TknU8   oddEven;                /* odd or even */
    TknU8   scrnInd;                /* screen indicator */
    TknU8   presRest;               /* Address presentation restricted ind. */
    TknU8   numPlan;                /* numbering plan */
    TknU8   spare;
    TknStr  addrSig;                /* Address Signal */
} SiCallXferNum;
/* see called/calling party number for values */

typedef struct _callXferRef         /* Call Transfer Reference */
{
    ElmtHdr eh;                     /* element header */
    TknU8   cllXferRef;             /* call transfer value 0-255 */
} SiCallXferRef;

typedef struct _cdINNum             /* Called IN Number */
{
    ElmtHdr eh;                     /* element header */
    TknU8   natAddr;                /* nature of addresss indicator */
    TknU8   oddEven;                /* odd or even */
    TknU8   spare1;                 /* spare */
    TknU8   presRest;               /* Address presentation restricted ind. */
    TknU8   numPlan;                /* numbering plan */
    TknU8   spare2;                 /* spare */
    TknStr  addrSig;                /* Address Signal */
} SiCdINNum;
/* see called/calling party number for values */

typedef struct _ccSS                /* CCSS (CCBS in ETSI v2) */
{
    ElmtHdr eh;                     /* element header */
    TknU8   ccssCallInd;            /* CCSS call indicator */
    TknU8   spare1;                 /* bits B-H */
} SiCCSS;
/*ccssCallInd values*/
#define CCSS_NO_INDICATION   0
#define CCSS_CALL            1

typedef struct _cirAssMap           /* Circuit assignment map */
{
    ElmtHdr eh;                     /* element header */
    TknU8   mapType;                /* map type */
    TknU8   spare1;                 /* bits G-H in first byte */
    TknU8   map1;                   /* bits A-H - a bit map of used circuits */
    TknU8   map2;                   /* bits A-H */
    TknU8   map3;                   /* bits A-H */
    TknU8   map4;                   /* bits A-G */
    TknU8   spare2;                 /* bits H in last byte */
} SiCirAssMap;
/*mapType values*/
#define MAPTYPE_1544     1
#define MAPTYPE_2048     2

/*map1, map2, map3, map4 bit values */
#define CIRCUIT_NOT_USED 0
#define CIRCUIT_USED     1

typedef struct _collCallReq         /* Collect Call Request */
{
    ElmtHdr eh;                     /* element header */
    TknU8   collCallReqInd;         /* Collect call Req indicator */
    TknU8   spare1;                 /* bits B-H */
} SiCollCallReq;
/*collCallReqInd values*/
#define COLLECT_NO_INDICATION   0
#define COLLECT_CALL_REQ        1

typedef struct _confTrtmnt          /* Conference Treatment Ind */
{
    ElmtHdr eh;                     /* element header */
    TknU8   confAccInd;             /* conference acceptance indicator */
    TknU8   spare1;                 /* bits C-G */
} SiConfTrtmnt;
/*confAccInd values*/
#define CONF_ACC_NO_INDICATION   0
#define CONF_ACC_ACCEPTED        1
#define CONF_ACC_REJECTED        2
#define CONF_ACC_SPARE           3

typedef struct _loopPrevInd         /* Loop Prevention Indicator */
{
    ElmtHdr eh;                     /* element header */
    TknU8   loopTypeInd;            /* Type indicator */
    TknU8   responseInd;            /* always 7 bits, B-H: all spare if loopType =0 */
} SiLoopPrevInd;
/*loopTypInd values*/
#define LOOP_TYPE_REQUEST       0
#define LOOP_TYPE_RESPONSE      1
/*responseInd, if loopType = 1 */
#define LOOP_RESP_INSUFF        0
#define LOOP_RESP_NO_LOOP       1
#define LOOP_RESP_SIMULTANEOUS  2
#define LOOP_RESP_SPARE         3

typedef struct _netMngmtCtrls       /* Network Management Controls */
{
    ElmtHdr eh;                     /* element header */
    TknU8   tarInd;                 /* Temporary Alternate Routing indicator */
    TknU8   spare1;                 /* bits B-G */
} SiNetMngmtCtrls;
/*tarInd values*/
#define TAR_IND_NO_INDICATION   0
#define TAR_IND_CONTROLLED_CALL 1

typedef struct _uidActionInd        /* UID action Indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   thruConnInd;            /* Through-connect instruction indicator */
    TknU8   t9Ind;                  /* T9 indicator */
    TknU8   spare1;                 /* bits C-G */
} SiUIDActionInd;
/*thruConnInd values*/
#define THRU_CONN_NO_INDICATION   0
#define THRU_CONN_BOTH_DIRS       1

/*t9Ind values*/
#define T9_NO_INDICATION   0
#define T9_STOP            1

typedef struct _uidCapInd           /* UID Capability Indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   thruConnInd;            /* Through-connect instruction indicator */
    TknU8   t9Ind;                  /* T9 indicator */
    TknU8   spare1;                 /* bits C-G */
} SiUIDCapInd;
/*thruConnInd values*/
#define THRU_CONN_IND_NO_INDICATION   0
#define THRU_CONN_IND_MOD_POSSIBLE    1

/*t9Ind values*/
#define T9_NO_INDICATION      0
#define T9_STOPPING_POSSIBLE  1

typedef struct _freePhnInd          /* Free Phone Indicators */
{
    ElmtHdr eh;                     /* element header */
    TknU8   freeInd;                /* Free phone indicator */
    TknU8   spare1;                 /* bits B-H */
} SiFreePhnInd;
/*freeInd values*/
#define FREE_PHN_NO_INDICATION   0
#define FREE_PHN_CALL            1

typedef struct _ccnr                /* CCNR possible indicator*/
{
    ElmtHdr eh;                     /* element header */
    TknU8   ccnrPossInd;            /* CCNR possible indicator */
    TknU8   spare1;                 /* bits B-H */
} SiCCNR;
/*ccnrPossInd values*/
#define CCNR_NOT_POSSIBLE    0
#define CCNR_POSSIBLE        1

typedef struct _scfID               /* SCF ID */
{
    ElmtHdr eh;                     /* element header */
    TknStr  data;                   /* status */
} SiScfID;
typedef struct _corrID              /* Correlation ID */
{
    ElmtHdr eh;                     /* element header */
    TknStr  digits;                 /* status */
} SiCorrelationID;

/*-----------------11/29/00 2:40PM------------------
 * End of New set of parameters added for 3.8
 * --------------------------------------------------*/

typedef struct _addUsrId
{
    ElmtHdr eh;                     /* element header */
    TknStr  usrId;
} SiAddUsrId;

/* Defines for new states that ISUPRawMsgReq can transition a circuit too */
#define RAWST_NOCHANGE  0x01
#define RAWST_IDLE      0x02
#define RAWST_BUSYIN    0x03
#define RAWST_BUSYOUT   0x04
#define RAWST_WAITACM   0x05

typedef struct _elementExt
{
   ElmtHdr eh;                  /* element header */
   TknExt  tknExt;              /* extended information */
} SiElementExt;

#ifdef UNIX
#pragma pack()
#endif


#endif

