/**************************************************************************
 **
 **                         PROPRIETARY NOTICE
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
 **  This product also contains software that is protected by the
 **  following copyrights.
 **
 **        (c) Copyright 1989-1995, Trillium Digital Systems, Inc.
 *************************************************************************/

#ifndef _TUPMSGS_H
#define _TUPMSGS_H

/* Turn on structure packing for UNIX env. */
#ifndef TUP_TASK
#ifdef UNIX
#pragma pack(1)
#endif
#endif

#define TUP_MF_SIZE_TKNSTR  32       /* token string size - regular */

typedef struct _tupelmtHdr            /* element header */
{
   Bool pres;                     /* present */
   U8   spare1;                   /* for alignment */
   U16  spare2;                   /* for alignment */
} TupElmtHdr;

/* coding for "pres" indicators - type Bool or type U8 */
#ifndef NOT_PRESENT
#define NOT_PRESENT        0
#endif
#ifndef PRESENT
#define PRESENT            1
#endif

/* token typedefs */
typedef struct _tuptknStr             /* token string */
{
   U8   spare0;                   /* used to be the present flag */
   U8   len;                      /* length */
   U16  spare1;                   /* for alignment */
   U8   val[(TUP_MF_SIZE_TKNSTR + 4) & 0xffc]; /* string value */
} TupTknStr;



/* This structure is included in IAM and IAI messages */
typedef struct callPartyCategory
{
    TupElmtHdr eh;
    U8  callPartyCat;
    U8  spare2;
    U16 spare1;
} CallPartyCat;
/******************************************************************************
* TUP calling party categories
******************************************************************************/
#define UNKNOWN_SOURCE          0
#define OPERATOR_FRENCH         0x01
#define OPERATOR_ENGLISH        0x02
#define OPERATOR_GERMAN         0x03
#define OPERATOR_RUSSIAN        0x04
#define OPERATOR_SPANISH        0x05
#define MUT_AGREE_CHINESE       0x06
#define MUT_AGREEMENT           0x07
#define MUT_AGREE_JAPANESE      0x08
#define NATIONAL_OPERATOR       0x09
#define ORDINARY_TOLL_CALLER    0x0A
#define PRIORITY_TOLL_CALLER    0x0B
#define DATA_CALL               0x0C
#define TEST_CALL               0x0D
#define PAY_PHONE               0x1F    /* not China */
#define ORDINARY_NO_CHG         0x10    /* China only */
#define ORDINARY_PERIODIC       0x11    /* China only */
#define ORDINARY_METER_IMMED    0x12    /* China only */
#define ORDINARY_PRINTER_IMMED  0x13    /* China only */
#define PRIORITY_NO_CHG         0x14    /* China only */
#define PRIORITY_PERIODIC       0x15    /* China only */
#define ORDINARY_LOCAL          0x18    /* China only */


/* This is a 16 bit indocator that is in IAM and IAI messages */
typedef struct iamMessageInd
{
    TupElmtHdr eh;
    U16  msgInd;
    U16 spare;
} IAMMessageInd;
/******************************************************************************
* TUP IAM/IAI Message indicator bits
******************************************************************************/
#define IAM_MI_LOCAL_SUBSCRIBER                 0x000
#define IAM_MI_NATIONAL                         0x002
#define IAM_MI_INTERNATIONAL                    0x003

#define IAM_MI_NO_SATELLITE                     0x000
#define IAM_MI_ONE_SATELLITE                    0x004

#define IAM_MI_CONT_CHECK_NOT_REQ               0x000
#define IAM_MI_CONT_CHECK_REQ                   0x010
#define IAM_MI_CONT_CHECK_PERFORMED_PREVIOUS    0x020

#define IAM_MI_OUT_ECHO_SUPP_INCLUDED           0x040
#define IAM_MI_IN_CALL_INTERNATIONAL            0x080
#define IAM_MI_REDIRECTED_CALL                  0x100
#define IAM_MI_DIGITAL_PATH_REQUIRED            0x200
#define IAM_MI_ALL_SS7_PATH                     0x400


/* This is the address (phone number) array, filled with the constants
    after its definition.

    The multi address structure is used in IAM, SAO, and SAM
    called addresses. */
typedef struct addrSignals
{
    TupElmtHdr eh;
    TupTknStr  addrSigs;
} AddrSigs;

/******************************************************************************
* TUP Address signals
******************************************************************************/
#define DIGIT_0         0
#define DIGIT_1         1
#define DIGIT_2         2
#define DIGIT_3         3
#define DIGIT_4         4
#define DIGIT_5         5
#define DIGIT_6         6
#define DIGIT_7         7
#define DIGIT_8         8
#define DIGIT_9         9

#define SPARE_0         10
#define CODE_11         11
#define CODE_12         12
#define SPARE_1         13
#define SPARE_2         14
#define CODE_ST         15


/* This structure is used in a GSM and IAI for caller Id and called ID */
typedef struct lineid
{
    TupElmtHdr eh;
    U8  addrInd;
    U8  spare2;
    U16 spare1;
    TupTknStr  addrSigs;
} LineID;
/******************************************************************************
* TUP address Indicator
******************************************************************************/
#define TUPSUBSNUM                  0x00
#define TUPNATNUM                   0x02
#define TUPINTNATNUM                0x03

#define TUPNOTRES                   0x00
#define TUPRESTRICTED               0x04
#define TUPNOTINC                   0x00
#define TUPINCOMPLETE               0x08


/** This structure is not USED yet */
typedef struct clsedUserGrp
{
    TupElmtHdr eh;
    U8      grpInd;
    U8      spare2;
    U16     spare1;
    U32     interlockCode;
} ClosedUserGroup;
/******************************************************************************
* TUP Closed User Group call indicators
******************************************************************************/
#define CUG_ORDINARY_CALL               0x00
#define CUG_SUCCESSFUL_CHECK            0x01
#define CUG_ACCESS_ALLOWED              0x02
#define CUG_ACCESS_NOT_ALLOWED          0x03


/* This is a GSM structure for the Trunk ID if it is requested in a GRQ */
typedef struct trunkid
{
    TupElmtHdr eh;
    U8      idType;
    U8      spare2;
    U16     spare1;
    TupTknStr  exchID;
    TupTknStr  trunkID;
} TrunkID;
/******************************************************************************
* TUP GRM trunk ID id type
******************************************************************************/
#define GSM_ID_TYPE_IND_POINT_CODE          0x01
#define GSM_ID_TYPE_IND_AVAIL_LINE_ID       0x02


/* The GRQ uses this structure to generate a request for info ! */
typedef struct respInd
{
    TupElmtHdr eh;
    U8      indicator;
    U8      spare2;
    U16     spare1;
} RespInd;
/******************************************************************************
* TUP response Indicator  -  different values for GSM and GRQ
******************************************************************************/
#define GSM_CALLING_PARTY_CATEGORY          0x01
#define GSM_CALLING_LINE_ID                 0x02
#define GSM_INCOMING_EXCH_ID                0x04
#define GSM_ORIG_CALLED_ADDRESS             0x08
#define GSM_OUTGOING_ECHO_SUPPRESSOR        0x10
#define GSM_MALICIOUS_CALL_ID               0x20
#define GSM_HOLD_INDICATOR                  0x40

#define GRQ_CALLING_PARTY_CATEGORY          0x01
#define GRQ_CALLING_LINE_ID                 0x02
#define GRQ_ORIG_CALLED_ADDRESS             0x04
#define GRQ_MALICIOUS_CALL_ID               0x08
#define GRQ_HOLD_INDICATOR                  0x10
#define GRQ_OUTGOING_ECHO_SUPPRESSOR        0x20


/* This is an 8 bit indicator used in a couple spots.

    An ACM uses it to indicate what kind of address was completed.

    An EUM uses it to indicate if a subscriber is busy.

    An ACC uses it to indicate what level of congestion has been reached.
*/
typedef struct mesgInd
{
    TupElmtHdr eh;
    U8      indicator;
    U8      spare2;
    U16     spare1;
} MsgInd;
/******************************************************************************
* TUP address complete indicators
******************************************************************************/
#define ACM_COMPLETE                        0x00
#define ACM_COMPLETE_CHARGE                 0x01
#define ACM_COMPLETE_NO_CHARGE              0x02
#define ACM_COMPLETE_COINBOX                0x03

#define ACM_SUBSCRIBER_FREE                 0x04
#define ACM_INCOMING_ECHO_SUPPRESSED        0x08
#define ACM_CALL_FORWARDED                  0x10    /* not used */
#define ACM_ALL_SS7_PATH                    0x20    /* not used */

/******************************************************************************
* TUP EUM octet indicator
******************************************************************************/
#define EUM_SUBSCRIBER_BUSY                 0x01

/* This is an 8 bit indicator for answer type. */
typedef struct ansType
{
    TupElmtHdr eh;
    U8      answerType;
    U8      spare2;
    U16     spare1;
} AnswerType;
/******************************************************************************
*  answer type indicators
******************************************************************************/
#define ANU_NO_CHARGE                       0x00
#define ANU_CHARGE                          0x01
#define ANU_UNQUALIFIED                     0x02

typedef struct _auCongLvl
{
    TupElmtHdr eh;
    U8      auCongLvl;
    U8      spare2;
    U16     spare1;
} TupAutoCongLvl;
/******************************************************************************
* TUP ACC congestion level message indicators
******************************************************************************/
#define TUPACLVL_LVL1          0x01
#define TUPACLVL_LVL2          0x02


/* This structure holds the SS7 Point Code */
typedef struct pointcode
{
    TupElmtHdr eh;
    U32     pointCode;
} PointCode;


/* This value is in a GRM message and indicates the number of circuits
    The current message has status information for.  It should be between
    1 and 255.

    If it is zero, it is for a predetermined circuit group.
*/
/* This structure is for GRM messages when the Range (above) is non-zero.

    The first bit is for the circuit in the CIC of the label.  The rest of
    the bits are for the "range" number of circuits, consecutively after
    the CIC of the label.
*/
typedef struct grmRange
{
    TupElmtHdr eh;
    U8      range;
    U8      spare2;
    U16     spare1;
    U8      statusMap[256];
} Range;

/******************************************************************************
* TUP GRM status bits
******************************************************************************/
#define GRM_NO_BLOCKING                 0x00
#define GRM_BLOCKING                    0x01

#define GRM_NO_BLOCKING_ACK             0x00
#define GRM_BLOCKING_ACK                0x01

#define GRM_NO_UNBLOCKING               0x00
#define GRM_UNBLOCKING                  0x01

#define GRM_NO_UNBLOCKING_ACK           0x00
#define GRM_UNBLOCKING_ACK              0x01

#define GRM_NO_GROUP_RESET_ACK          0x00
#define GRM_GROUP_RESET_ACK             0x01

/** This structure will hold why a ReleaseReq was sent by either side! */
typedef struct ubm_cause
{
    TupElmtHdr eh;
    U8      cause;
    U8      spare2;
    U16     spare1;
} TupCause;

/** This meesage holds a binary 16 bit piece of info for charging units. */
typedef struct chgInfo
{
    TupElmtHdr eh;
    U16     info;
    U16     spare1;
} ChargeInfo;


/************ E V E N T    S T R U C T U R E S ****************/

/* This struct is passed to the TUPConnectReq routine */
typedef struct tupConEvnt            /* IAM, IAI */
{
    CallPartyCat    cgPtyCat;       /* IAM, IAI */
    IAMMessageInd   msgInd;         /* IAM, IAI */
    AddrSigs        addrSigs;       /* IAM, IAI */
    LineID          cgPtyNum;       /* IAI */
    LineID          origCdNum;      /* IAI */
    ClosedUserGroup clUsrGrp;       /* IAI */
} TupConEvnt;

/* This struct is passed to the TUPConnectResp routine */
typedef struct tupConRspEvnt        /* ANN, ANC, ANU */
{
    AnswerType      answerType;     /* ANN, ANC, ANU */
} TupConRspEvnt;


/* This struct is passed to the TUPConnectStatusReq routines */
typedef struct tupCnStEvnt          /* ACM, ACC, FOT, GSM, GRQ, SAM, SAO, MAL */
{                                   /* MPM, RAN, CCL, OPR */
    RespInd         respInd;        /* GRQ */
    MsgInd          msgInd;         /* ACM, ACC */
    TupAutoCongLvl  congLvl;        /* ACC */
    AddrSigs        addrSigs;       /* SAM, SAO */
    CallPartyCat    cgPtyCat;       /* GSM */
    LineID          cgPtyNum;       /* GSM */
    LineID          origCdNum;      /* GSM */
    TrunkID         trunkID;        /* GSM */
    ChargeInfo      chargeInfo;     /* MPM */
} TupCnStEvnt;

/* This struct is passed to the TUPReleaseReq and TUPReleaseResp routines */
typedef struct tupRelEvnt           /* SEC, CGC, NNC, ADI, CFL, SSB, UNN */
{                                   /* LOS, SST, ACB, DPN, EUM */
    TupCause        cause;          /* all of them SHOULD fill this */
} TupRelEvnt;

/* This struct is passed to the TUPStatusReq routines */
typedef struct tupStaEvnt           /* all GRM's */
{
    MsgInd          msgInd;         /* EUM */
    PointCode       pointCode;      /* EUM */
    Range           range;          /* all GRM's */
    U8              mtpCongestionLvl;   /* indicates MTP3 congestion level */
    U8              tupTaskcongestionLvl;/* contains tup task memory congestion level */
    U16             spare2;             /* Spare for alignment */
} TupStaEvnt;

/* This struct is passed to the app if there was an error to report */
typedef struct tupErrInfo
{
    U8      origIndType;
    U8      origEvntType;
    U32     errorCode;
} TupErrInfo;

/* This union is the returned structure to TUPReceiveMessage in the
    Event paramter
*/
typedef struct tupAllSdus         /* all sdu messages */
{
    union
    {
      TupConEvnt      conEvnt;
      TupConRspEvnt   conRspEvnt;
      TupCnStEvnt     conStEvnt;
      TupRelEvnt      relEvnt;
      TupStaEvnt      staEvnt;
    } m;
    TupErrInfo      errInfo;
} TupAllSdus;

#ifndef TUP_TASK
#ifdef UNIX
#pragma pack()
#endif
#endif

#endif   /* #ifndef _TUPUSER_H_ */
