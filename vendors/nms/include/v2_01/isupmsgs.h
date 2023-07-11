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

/* Turn on structure packing for Solaris */
#ifdef __sun
#pragma pack(1)
#endif


#ifndef _TX_ISUPAPI_SOURCE_
/* The following defines are required for compatibility with
 * this version of the ISUP process; do not remove them.
 */
#define MF_SIZE_TKNSTR  132		  /* token string size - regular */


/* coding for "pres" indicators - type Bool or type U8 */
#define	NOT_PRESENT		0
#define PRESENT			1

/*
** token typedefs
*/
typedef struct _si_tknHdr             /* token header */
{
   Bool pres;                     /* present */
} TknHdr;

typedef struct _elmtHdr            /* element header */
{
   Bool pres;                     /* present */
   U8   spare1;                   /* for alignment */
   U16  spare2;                   /* for alignment */
} ElmtHdr;

typedef struct _tknU8              /* token U8 */
{
   U8   pres;                     /* present flag */
   U8   val;                      /* value */
   U16  spare1;                   /* for alignment */
} TknU8;

typedef struct _tknU16             /* token U16 */
{
   U8   pres;                     /* present flag */
   U8   spare1;                   /* for alignment */
   U16  val;                      /* value */
} TknU16;

typedef struct _tknU32             /* token U32 */
{
   U8   pres;                     /* present flag */
   U8   spare1;                   /* for alignment */
   U16  spare2;                   /* for alignment */
   U32  val;                      /* value */
} TknU32;

typedef struct _tknStr             /* token string */
{
   U8   pres;                     /* present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
   U8   val[(MF_SIZE_TKNSTR + 4) & 0xffc]; /* string value */
} TknStr;


#endif /* _TX_ISUPAPI_SOURCE_ */

#include "iedefs.h"

#define usrServInfoA    usrServInfo
#define callRefA        callRef
#define connReqA        connReq
#define opFwdCalIndA    opFwdCalInd
#define cugIntCodeA     cugIntCode
#define usr2UsrInfoA    usr2UsrInfo
#define redirInf        redirInfo
#define redirInfoA      redirInfo
#define infoIndA        infoInd
#define infoReqIndA     infoReqInd
#define sigPointCodeA   sigPointCode

/* Events */

typedef struct _siConEvnt         /* ISUP Connect Event */
{
    SiNatConInd         natConInd;          /* Nature of connection indicators */
    SiFwdCallInd        fwdCallInd;         /* forward call indicators */
    SiCgPtyCat          cgPtyCat;           /* calling party category */
    SiTxMedReq          txMedReq;           /* transmission medium requirement */
    SiTxMedReq          txMedReqPr;         /* transmission medium requirement prime */
    SiCdPtyNum          cdPtyNum;           /* called party number */
    SiTranNetSel        tranNetSel;         /* transit network selection */
    SiCallRef           callRef;            /* call reference */
    SiCgPtyNum          cgPtyNum;           /* calling party number */
    SiOpFwdCalInd       opFwdCalInd;        /* optional forward call indicators */
    SiRedirgNum         redirgNum;          /* redirecting number */
    SiRedirInfo         redirInfo;          /* redirection information */
    SiCugIntCode        cugIntCode;         /* closed group interlock code */
    SiConnReq           connReq;            /* connection request */
    SiOrigCdNum         origCdNum;          /* original called number */
    SiUsr2UsrInfo       usr2UsrInfo;        /* user to user information */
    SiAccTrnspt         accTrnspt;          /* access transport */
    SiChargeNum         chargeNum;          /* charge number */
    SiOrigLineInf       origLineInf;        /* originating line information */
    SiUsrServInfo       usrServInfo;        /* user service infiormation */
    SiUsr2UsrInd        usr2UsrInd;         /* user to user indicators */
    SiPropDly           propDly;            /* propagation delay counter */
    SiUsrServInfo       usrServInfo1;       /* user service info prime */
    SiNetSpecFacil      netFac;             /* network specific facility */
    SiSigPointCode      orgPteCde;          /* originating ISC point code */
    SiGenDigits         genDigits;          /* generic digits */
    SiGenNum            genNmb;             /* generic number */
    SiRemotOper         remotOper;          /* remote operations */
    SiParmCompInfo      parmCom;            /* parameter compatibility information */
    SiNotifInd          notifInd;           /* notification indicator */
    SiInfoInd           infoInd;            /* information indicator */
    SiServiceAct        serviceAct;         /* service activation */
    SiMlppPrec          mlppPrec;           /* MLPP precedence */
    SiTxMedReq          txMedUsed;          /* transmission medium used */
    SiBckCalInd         bckCallInd;         /* backward call indicators */
    SiOptBckCalInd      optBckCalInd;       /* optional backward call indicators */
    SiConnectedNum      connNum;            /* connected number */
    SiAccDelInfo        accDelInfo;         /* access delivery information */
    SiPropDly           cllHstry;           /* call history information */
    SiRedirNum          redirNum;           /* redirection number */
    SiRedirRestr        redirRstr;          /* redirection restriction */
    SiBusinessGrp       businessGrp;        /* business group */
    SiCarrierId         carrierId;          /* carrier identification */
    SiCarrierSelInf     carSelInf;          /* carrier selection information */
    SiEgress            egress;             /* ergress service */
    SiGenAddr           genAddr;            /* generic address */
    SiInfoReqInd        infoReqInd;         /* information request indicators */
    SiJurisInf          jurisInf;           /* jurisdiction information */
    SiNetTransport      netTransport;       /* network transport */
    SiSpecProcReq       specProcReq;        /* special processing request */
    SiTransReq          transReq;           /* transaction request */
    SiEchoCtl           echoControl;        /* echo control */
    SiCirAssignMap      cirAssignMap;       /* circuit assignment map */
    SiGenName           genName;            /* generic name */
    SiHopCount          hopCount;           /* hop counter */
    SiOpServInfo        opServInfo;         /* operator services information */
    SiServiceCode       serviceCode;        /* service code */
    SiLocNum            locNum;             /* location number */
    SiMsgAreaInfo       msgAreaInfo;        /* message area information */
    SiContractorNum     contractorNum;      /* conttractor number */
    SiCgNumNonNotRsn    cgNumNonNotRsn;     /* calling number non-notification reason */
    SiAddUsrId          addUsrId;           /* additional user identification */
    SiCarrierInfoTrans  carrierInfoTrans;   /* carrier information transfer */
} SiConEvnt;

typedef struct _siCnStEvnt       /* Connect Status Event */
{
   SiSubNum             subNum;             /* subsequent number */
   SiBckCalInd          bckCallInd;         /* backward call indicators */
   SiChargeNum          chargeNum;          /* connected number */
   SiOptBckCalInd       optBckCalInd;       /* optional backward call indicators */
   SiCauseDgn           causeDgn;           /* cause indicators */
   SiConnectedNum       connNum;            /* connected number */
   SiUsr2UsrInd         usr2UsrInd;         /* user to user indicators */
   SiUsr2UsrInfo        usr2UsrInfo;        /* user to user information */
   SiRedirInfo          redirInfo;          /* redirection information */
   SiAccTrnspt          accTrnspt;          /* access transport */
   SiCalModInd          calModInd;          /* call modification indicators */
   SiEvntInfo           evntInfo;           /* event information */
   SiRedirNum           redirNum;           /* redirection number */
   SiInfoInd            infoInd;            /* information indicators */
   SiInfoReqInd         infoReqInd;         /* information request indicators */
   SiRedirgNum          redirgNum;          /* redirecting number */
   SiCgPtyCat           cgPtyCat;           /* calling party category */
   SiCgPtyNum           cgPtyNum;           /* calling party number */
   SiIndex              index;              /* index */
   SiConnReq            connReq;            /* connection request */
   SiCallRef            callRef;            /* call reference */
   SiNotifInd           notifInd;           /* notification indicator */
   SiTxMedReq           txMedUsed;          /* transmission medium used */
   SiEchoCtl            echoControl;        /* echo control */
   SiAccDelInfo         accDelInfo;         /* access delivery information */
   SiGenNum             genNmb;             /* generic number */
   SiParmCompInfo       parmCom;            /* parameter compatibility information */
   SiCllDiverInfo       cllDivr;            /* call Diversion information */
   SiNetSpecFacil       netFac;             /* network specific facility */
   SiRemotOper          remotOper;          /* remote operations */
   SiServiceAct         serviceAct;         /* service activation */
   SiRedirRestr         redirRstr;          /* redirection restriction */
   SiMcidReqInd         mcidReq;            /* MCID request indicators */
   SiMcidRspInd         mcidRsp;            /* MCID response indicators */
   SiMsgCompInfo        msgCom;             /* message compatibility information */
   SiOrigLineInf        origLineInf;        /* originating line information */
   SiBusinessGrp        businessGrp;        /* business group */
   SiNetTransport       netTransport;       /* network transport */
   SiMsgAreaInfo        msgAreaInfo;        /* message area information */
   SiChargeInfo         chargeInfo;         /* charge information */
   SiChargeInfoType     chargeInfoType;     /* charge information type */
   SiChargeInfoDly      chargeInfoDly;      /* charge information delay */
   SiCarrierInfoTrans   carrierInfoTrans;   /* carrier information transfer */
} SiCnStEvnt;

typedef struct _siInfoEvnt        /* Information Event */
{
   SiCallRef        callRef;        /* call reference */
   SiPassAlng       passAlng;       /* pass along */
   SiUsr2UsrInfo    usr2UsrInfo;    /* user to user information */
   SiAccTrnspt      accTrnspt;      /* access transport */
} SiInfoEvnt;

typedef struct _siResmEvnt        /* resume event */
{
   SiSusResInd      susResInd;      /* Suspend/Resume indicators */
   SiCallRef        callRef;        /* call reference */
} SiResmEvnt;

typedef struct _siStaEvnt         /* Status Event */
{
   SiRangStat           rangStat;           /* range and status */
   SiCirGrpSupMTypInd   cgsmti;             /* circuit grp. supervision msg. type ind. */
   SiCirStateInd        cirStateInd;        /* circuit state indicators */
   SiContInd            contInd;            /* continuity indicator */
   SiCauseDgn           causeDgn;           /* cause indicators */
   SiParmCompInfo       parmCom;            /* parameter compatibility information */
   SiNatConInd          natConInd;          /* Nature of connection indicators */
   SiCirAssignMap       cirAssignMap;       /* circuit assignment map */
} SiStaEvnt;

typedef struct _siRelEvnt         /* Release Event */
{
   SiCauseDgn       causeDgn;       /* cause indicators */
   SiRedirInfo      redirInfo;      /* redirection information */
   SiRedirNum       redirNum;       /* redirection number */
   SiRedirgNum      redirgNum;      /* redirection number */
   SiCallRef        callRef;        /* call reference */
   SiCugIntCode     cugIntCode;     /* closed group interlock code */
   SiSigPointCode   sigPointCode;   /* signalling point code */
   SiAccTrnspt      accTrnspt;      /* access transport */
   SiUsr2UsrInfo    usr2UsrInfo;    /* user to user information */
   SiAutoCongLvl    autoCongLvl;    /* automatic congestion level */
   SiAccDelInfo     accDelInfo;     /* access delivery information */
   SiParmCompInfo   parmCom;        /* parameter compatibility information */
   SiNetSpecFacil   netFac;         /* network specific facility */
   SiRedirRestr     redirRstr;      /* redirection restriction */
   SiUsr2UsrInd     usr2UsrInd;     /* user to user indicators */
   SiChargeNum      chargeNum;      /* charge number */
   SiGenAddr        genAddr;        /* generic address */
   SiServiceAct     serviceAct;     /* service activation */
   SiCdPtyNum       cdPtyNum;       /* called party number */
} SiRelEvnt;

typedef struct _siSuspEvnt        /* suspend event */
{
   SiSusResInd      susResInd;      /* suspend/resume indicators */
   SiCallRef        callRef;        /* call reference */
} SiSuspEvnt;

typedef struct _siFacEvnt         /* facility event */
{
   SiFacInd         facInd;         /* facility indicator */
   SiFacInfInd      facInfInd;      /* facility information indicator */
   SiCdPtyNum       cdPtyNum;       /* called party number */
   SiCgPtyNum       cgPtyNum;       /* calling party number */
   SiCallRef        callRef;        /* call reference */
   SiConnReq        connReq;        /* connection request */
   SiUsr2UsrInd     usr2UsrInd;     /* user to user indicator */
   SiCauseDgn       causeDgn;       /* cause indicator */
   SiMsgCompInfo    msgCom;         /* message compatibility information */
   SiParmCompInfo   parmCom;        /* parameter compatibility information */
   SiRemotOper      remotOper;      /* remote operations */
   SiServiceAct     serviceAct;     /* service activation */
} SiFacEvnt;







typedef struct _siAllSdus         /* all sdu messages */
{
   union
   {
      SiConEvnt     siConEvnt;      /* ISUP Connect Event */
      SiCnStEvnt    siCnStEvnt;     /* Connect Status Event */
      SiFacEvnt     siFacEvnt;      /* facility event */
      SiInfoEvnt    siInfoEvnt;     /* Information Event */
      SiResmEvnt    siResmEvnt;     /* resume event */
      SiStaEvnt     siStaEvnt;      /* Status Event */
      SiRelEvnt     siRelEvnt;      /* Release Event */
      SiSuspEvnt    siSuspEvnt;     /* suspend event */
   } m;
} SiAllSdus;

#ifdef __sun
#pragma pack()
#endif


#endif
