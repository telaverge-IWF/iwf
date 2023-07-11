/*****************************************************************************
 * NAME:  sccpdef.h
 * PURPOSE:
 *     This file contains macros and constants common to the SCCP API service,
 *     management API, and TCAP API sevice.
 *
 * Copyright (c)1997-1999 Natural MicroSystems Corporation. All rights reserved.
 *****************************************************************************/
#ifndef _SCCPDEF_H_
#define _SCCPDEF_H_
/*****************************************************************************/

#include "ss7type.h"

/* Prevent C++ name mangling. */
#ifdef __cplusplus
extern "C"
{
#endif

/* --------------------------------------------------------------------------
 * SCCP Routing Type Values for Adresss Map Tables:
 * -------------------------------------------------------------------------- */
#define ROUTE_GLT       0x00    /* Route using global title only              */
#define ROUTE_PC_SN     0x01    /* Route usint point code + SSN               */

/* --------------------------------------------------------------------------
 * National/International Address Indicator Values for Address Translations:
 * -------------------------------------------------------------------------- */
#define ADDRIND_INT     0x00    /* International address indicator            */
#define ADDRIND_NAT     0x01    /* National address indicator                 */

/* --------------------------------------------------------------------------
 * Address Encoding Scheme Values:
 * -------------------------------------------------------------------------- */
#define ENC_UNKNOWN     0x00    /* Encoding unknown                           */
#define ENC_BCD_ODD     0x01    /* BCD, odd number of digits                  */
#define ENC_BCD_EVEN    0x02    /* BCD, even number of digits                 */

/* --------------------------------------------------------------------------
 * Numbering Plan Values:
 * -------------------------------------------------------------------------- */
#define NP_UNK          0x00    /* Unknown                                    */
#define NP_ISDN         0x01    /* ISDN/telephony - E.164/E.163               */
#define NP_TEL          0x02    /* Telephony numbering - E.163                */
#define NP_DATA         0x03    /* Data numbering - X.121                     */
#define NP_TELEX        0x04    /* Telex numbering - Recomm. F.69             */
#define NP_MARITIME     0x05    /* Maritime mobile numbering                  */
#define NP_LANDMOB      0x06    /* Land mobile numbering                      */
#define NP_ISDNMOB      0x07    /* ISDN/mobile numbering                      */
#define NP_NATIONAL     0x08    /* National standard numbering                */
#define NP_PRIVATE      0x09    /* Private numbering                          */
#define NP_EXT          0x0F    /* Reserved for extension                     */

/* --------------------------------------------------------------------------
 * Nature of Address Indicator Values:
 * -------------------------------------------------------------------------- */
#define NATIND_SUBS     0x01    /* Subscriber number                          */
#define NATIND_NATL     0x03    /* National number                            */
#define NATIND_INTNATL  0x04    /* International number                       */

/* --------------------------------------------------------------------------
 * Constants:
 * -------------------------------------------------------------------------- */
#define MAX_GLT_SZ      32
#define MAX_DATA_SZ     1200
#define EXTADDRLEN      16

#define ORGNETWORK      0x00    /* network originatied              */
#define ORGENDUSER      0x01    /* user originatied                 */


/******* Set compiler structure packing option */
#pragma pack(1)

/* Address Parameter */
typedef struct sccpAddr                 /* Called/Calling Party Address     */
{
   U8       presInd;                    /* presence indicator               */
#define NOT_PRESENT         0x00        /* field not present in incoming    */
                                        /* msg or not to be populated in    */
                                        /* outgoing msg                     */
#define PRESENT             0x01        /* field is present in incoming msg */
                                        /* or should be included in         */
                                        /* outgoing msg                     */
   U8       spare1;                     /* spare for alignment              */

   S16      swType;                     /* switch type (ANSI/ITU-T)         */
#define SW_ITU              0x01        /* ITU operation                    */
#define SW_ANSI             0x02        /* ANSI operation                   */

   U8       subsystemInd;               /* subsystem indicator              */
#define SUBSYS_NONE         0x00        /* No subsystem number in address   */
#define SUBSYS_INC          0x01        /* Addr contains subsystem number   */

   U8       pointCodeInd;               /* point code indicator             */
#define PTCODE_NONE         0x00        /* No point code in address         */
#define PTCODE_INC          0x01        /* Addr contains point code         */

   U8       glTitleInd;                 /* global title indicator           */
#define GLT_NONE            0x00        /* No global title in address       */
#define GLT_TT_NP_E         0x01        /* ANSI only - Global title includes*/
                                        /* translation type, numbering plan */
                                        /* & encoding                       */
#define GLT_TT              0x02        /* ANSI only - Global title includes*/
                                        /* translation type only            */
#define GLT_ITU_FMT1        0x01        /* ITU only - Global title includes */
                                        /* encoding and nature of address   */
                                        /* only                             */
#define GLT_ITU_FMT2        0x02        /* ITU only - Global title includes */
                                        /* translation type only            */
#define GLT_ITU_FMT3        0x03        /* ITU only - Global title includes */
                                        /* translation type, numbering plan */
                                        /*  & encoding                      */
#define GLT_ITU_FMT4        0x04        /* ITU only - Global title includes */
                                        /* translation type, numbering plan,*/
                                        /* encoding, and nature of address  */
   U8       routingInd;                 /* routing indicator:               */
                                        /*   ROUTE_GLT | ROUTE_PC_SN        */
   U32      pointCode;                  /* point code                       */
   U8       natIntInd;                  /* national/international indicator:*/
                                        /*   ADDRIND_NAT | ADDRIND_INT      */
   U8       subsystem;                  /* subsystem number                 */
#define SUBSYS_NONE         0x00        /* subsystem unknown or not used    */
#define SUBSYS_SCCPMGMT     0x01        /* SCCP management subsystem        */
#define SUBSYS_ISUP         0x03        /* ISUP subsystem                   */
#define SUBSYS_OMAP         0x04        /* operations, maint., admin.       */
#define SUBSYS_MAP          0x05        /* mobile application part          */
#define SUBSYS_HLR          0x06        /* home location register           */
#define SUBSYS_VLR          0x07        /* visitor location register        */
#define SUBSYS_MSC          0x08        /* mobile switching center          */
#define SUBSYS_EIR          0x09        /* equipment ident. register        */
#define SUBSYS_AUTH         0x0A        /* authentication center            */

   U8       glTransType;                /* global title translation type    */
   U8       encoding;                   /* encoding scheme: ENC_UNKNOWN |   */
                                        /*   ENC_BCD_ODD | ENC_BCD_EVEN     */
   U8       numPlan;                    /* numbering plan: NP_TEL, etc.     */
   U8       natAddrInd;                 /* nature of address indicator:     */
                                        /*   NATIND_[SUBS | NATL | INTNATL] */
   U8       spare2;                     /* spare for alignment              */
   U8       glTitleLen;                 /* length of global title           */
   U8       glTitle[MAX_GLT_SZ];        /* Global Title                     */
} SccpAddr;

typedef U8 SccpCauseVal;
/*
The cause value has different meanings depending on the message it is
included in.  Pre-defined values for various messages are shown below.
Application-specific values are also allowed.
*/
/* Error Cause Values (Error Message) */
#define ECDESTLRN           0x00        /* unassigned dest local ref. nbr   */
#define ECSRCLRN            0x01        /* inconsistant src local ref. nbr  */
#define ECPOINTCODE         0x02        /* point code mismatch              */
#define ECSERVCLASS         0x03        /* service class mismatch           */
#define ECUNQUALIFIED       0x04        /* unqualified                      */

/* Refusal Cause Values (Connection Refused Message) */
#define REFCENDUSER         0x00        /* end user originated              */
#define REFCUSERCONG        0x01        /* end user congested               */
#define REFCUSERFAIL        0x02        /* end user failed                  */
#define REFCSCCPUSER        0x03        /* SCCP user originated             */
#define REFCDESTUNK         0x04        /* destination unknown              */
#define REFCDESTINACC       0x05        /* destination inaccessible         */
#define REFCQOSPERM         0x06        /* QOS not avail (permanent)        */
#define REFCQOSTRANS        0x07        /* QOS not avail (transient)        */
#define REFCACCFAIL         0x08        /* Access failure                   */
#define REFCACCCONG         0x09        /* Access congestion                */
#define REFCSUBSFAIL        0x0A        /* Subsystem failure                */
#define REFCSUBSCONG        0x0B        /* Subsystem congestion             */
#define REFCCONNTIMER       0x0C        /* Connection timer expired         */
#define REFCBADDATA         0x0D        /* Inconsistant user data           */
#define REFCNOTOBTAIN       0x0E        /* Not obtainable                   */
#define REFCUNQUALIFIED     0x0F        /* unqualified                      */
#define REFCHOPCNT          0x10        /* Hop counter failure              */
#define REFCSCCPFAIL        0x11        /* SCCP failure                     */
#define REFCNOTRANS         0x12        /* No translation for address       */
#define REFCUNEQUSER        0x13        /* unequipped user                  */

/* Release Cause Values (Released Message) */
#define RELCENDUSER         0x00        /* end user originated              */
#define RELCUSERBUSY        0x01        /* end user busy                    */
#define RELCUSERFAIL        0x02        /* end user failed                  */
#define RELCSCCPUSER        0x03        /* SCCP user originated             */
#define RELCREMPROC         0x04        /* remote procedure error           */
#define RELCCONNDATA        0x05        /* inconsistant connection data     */
#define RELCACCFAIL         0x06        /* Access failure                   */
#define RELCACCCONG         0x07        /* Access congestion                */
#define RELCSUBSFAIL        0x08        /* Subsystem failure                */
#define RELCSUBSCONG        0x09        /* Subsystem congestion             */
#define RELCNETFAIL         0x0A        /* Network failure                  */
#define RELCNETCONG         0x0B        /* Network congestion               */
#define RELCRESETTIMER      0x0C        /* Reset timer expired              */
#define RELCINACT           0x0D        /* Inactivity timer expired         */
#define RELCNOTOBTAIN       0x0E        /* Not obtainable                   */
#define RELCUNQUALIFIED     0x0F        /* unqualified                      */
#define RELCSCCPFAIL        0x10        /* SCCP failure                     */

/* Reset Cause Values (Reset Request Message) */
#define RESCENDUSER         0x00        /* end user originated              */
#define RESCSCCPUSER        0x01        /* SCCP user originated             */
#define RESCPSERR           0x02        /* sequence error - bad P(s)        */
#define RESCPRERR           0x03        /* sequence error - bad P(r)        */
#define RESCREMWIN          0x04        /* message out of window            */
#define RESCREMPSERR        0x05        /* bad P(s) after reinit            */
#define RESCREMGEN          0x06        /* general remote proc error        */
#define RESCREMUSER         0x07        /* remote end user operational      */
#define RESCNETWORK         0x08        /* network operational              */
#define RESCACCESS          0x09        /* Access operational               */
#define RESCNETCONG         0x0A        /* Network congestion               */
#define RESCNOTOBTAIN       0x0B        /* Not obtainable                   */
#define RESCUNQUALIFIED     0x0C        /* unqualified                      */

/* Return Cause Values (Class 0 & 1 Returned Messages) */
#define RETCGENTRANS        0x00        /* no translation for address of    */
                                        /* this nature                      */
#define RETCNOTRANS         0x01        /* no translation for this address  */
#define RETCSUBSCONG        0x02        /* Subsystem congestion             */
#define RETCSUBSFAIL        0x03        /* Subsystem failure                */
#define RETCUNQUIP          0x04        /* unequipped user                  */
#define RETCNETFAIL         0x05        /* network failure                  */
#define RETCNETCONG         0x06        /* Network congestion               */
#define RETCUNQUALIFIED     0x07        /* unqualified                      */
#define RETCHOPCNT_ANS92    0x08        /* hop counter violation  (ANS92)   */
#define RETCMSGXPORT        0x08        /* error in message transport       */
#define RETCLOCALPROC       0x09        /* error in local processing        */
#define RETCREASSEMBLY      0x0A        /* Dest. cannot perform reassembly  */
#define RETCSCCPFAIL        0x0B        /* SCCP failure                     */
#define RETCHOPCNT          0x0C        /* hop counter violation (ITU&ANS96)*/
#define RETCSEGMNOTSUPP     0x0D        /* error in message transport       */
#define RETCSEGMFAIL        0x0E        /* error in local processing        */
#define RETCBADISNI         0xF9        /* invalid ISNI routing rqst        */
#define RETCAUTH            0xFA        /* unauthorized message             */
#define RETCINCOMPAT        0xFB        /* message incompatibility          */
#define RETCNOISNI          0xFC        /* can't do ISNI constrained        */
                                        /* routing                          */
#define RETCREDISNI         0xFD        /* redundant ISNI constrained       */
                                        /* routing info                     */
#define RETCISNIID          0xFE        /* can't do ISNI indentification    */

typedef struct  _SCCP_STAT
{
    U32               succTx;      /* Success transmit       */
    U32               succRx;      /* Success receive        */
    U32               failTx;      /* Transmit failure       */
    U32               failTxErr;   /* Transmit failure error */
    U32               failRx;      /* Receive failure        */
    U32               outStTx;     /* Msg sent queue         */
    U32               maxOutStTx;  /* Max on msg sent queue  */
    U32               quTx;        /* Queued msg             */
    U32               maxQuTx;     /* Max queued msg         */
    U8                currCongState;   /* Current outbound congestion state       */
    U8                svcCongState;    /* service congestion state       */
    U8                taskCongState;   /* last task congestion state       */
} SccpStats;

/* Proposed window size for class 3 connection-oriented traffic */
typedef U8 SccpCredit;

/* data information element for messages that can hold user data */
typedef struct sccpData
{
    U8      presInd;                    /* presence indicator               */
    U8      spare1;                     /* spare for alignment              */
    S16     dataLen;                    /* length of data                   */
    U8      data[MAX_DATA_SZ];          /* user data                        */
} SccpData;

/* End-of-sequence indicator for sequenced connectionless (class 1) traffic */
typedef U8 SccpEOS;

#define EOS_NO              0x00        /* not end of sequence              */
#define EOS_YES             0x01        /* end of sequence                  */

/* expedited data selector for connection set-up */
typedef U8 SccpExpDatSel;

#define EDS_NONE            0x00        /* no expedited data                */
#define EDS_REQ             0x01        /* expedited data requested         */

/* protocol and message handling options for connectionless unitdata and
 * connection set-up
 */
typedef struct sccpProtoClass
{
   U8       classInd;                   /* class indicator                  */
#define SCCP_CLASS0         0x00         /* 0 - basic connectionless         */
#define SCCP_CLASS1         0x01        /* 1 - sequenced connectionless     */
#define SCCP_CLASS2         0x02        /* 2 - basic connection-oriented    */
#define SCCP_CLASS3         0x03        /* 3 - connection-oriented w/flow   */
   U8       msgHandling;                /* message handling indicator       */
#define MSG_DISCARD         0x00        /* discard message on error         */
#define MSG_RETURN          0x08        /* return message on error          */
   U16      spare1;                     /* spare for alignment              */
} SccpProtoClass;

/* receipt confirmation selector for class 3 connection set-up */
typedef U8 SccpRecConfSel;

#define RCS_NONE            0x00        /* no receipt confirmation          */
#define RCS_REQ             0x01        /* receipt confirmation requested   */

/* receive sequence number for class 3 acknowledgements */
typedef U8 SccpNextRS;

/* Subsystem multiplicity indicator data type */
typedef U8 SccpSmi;

#define SMI_UNKNOWN         0x00        /* unknown                          */
#define SMI_SOLO            0x01        /* subsystem is not replicated      */
#define SMI_DUP             0x02        /* subsystem is replicated          */
#define SMI_DENIED          0x10        /* Indicate denial of coordinate    */
                                        /* state change                     */
/* Affected subsystem number data type */
typedef U8 SccpSsn;

/* Signaling point and subsystem status data type */
typedef U8 SccpStatus;

#define SP_ACC              0x00        /* Signalling Point Accessible      */
#define SP_INACC            0x01        /* Signalling Point Inaccessible    */
#define SP_CONG             0x02        /* Signalling point is congested */
#define SS_OOS              0x03        /* Subsystem out of service         */
#define SS_IS               0x04        /* Subsystem in service             */
#define SP_INACC_NODROP     0x06        /* Signalling Point Inaccessible, but connections not dropped */
#define SP_CONG_OFF         0x07        /* Congestion ended on affected SP */
#define SP_CONG1            0x10        /* TRP - Congestion Level 1 */
#define SP_CONG2            0x11        /* TRP - Congestion Level 2 */
#define SP_CONG3            0x12        /* TRP - Congestion Level 3 */

/*-
 * Ansi-96 Intermediate signaling network identification element
 */
typedef struct sccpIsni
{
   U8       presInd;                    /* presence indicator                   */
   U8       markInd;                    /* mark for identification indicator    */
   U8       iri;                        /* ISNI routing indicator               */
   U8       typeInd;                    /* ISNI type (0 or 1)                   */
   U8       counter;                    /* # of entries in netids array (0..7)  */
   U8       rcext;                      /* routing control extension (type 1)   */
   U16      netids[7];                  /* network IDs                          */
} SccpIsni;

/*-
 * ITU-96 message importance element
 */
typedef struct sccpImportance
{
   U8       presInd;                    /* presence indicator                   */
   U8       impvalue;                   /* message importance (0..7)            */
   U8       spare1;                     /* spare for alignment                  */
   U8       spare2;                     /* spare for alignment                  */
} SccpImportance;

/* --------------------------------------------------------------------------
 * Messages:
 * -------------------------------------------------------------------------- */
typedef struct sccpConnRqst             /* Connection Request Message       */
{
    SccpProtoClass  protoClass;         /* protocol class (M)               */
    SccpAddr        calledPty;          /* called party address (M)         */
    SccpAddr        callingPty;         /* calling party address (O)        */
    SccpCredit      credit;             /* proposed window size (M)         */
    SccpRecConfSel  rcs;                /* receipt conf. selected (M)       */
    SccpExpDatSel   eds;                /* expedited data selector (M)      */
    U8              spare1;             /* spare for alignment              */
    SccpImportance  importance;         /* reserved for ITU-96 importance   */
    SccpData        data;               /* data (O)                         */
} SccpConnRqst;

typedef struct sccpCoordRqst            /* Coordination Request Message     */
{
    SccpSsn         aSsn;               /* affected subsystem (M)           */
    SccpSmi         smi;                /* subsystem multiplicity ind(M -   */
                                        /*  Indication/Confirm only)        */
    SccpStatus      status;             /* New status (M - subsystem & SP   */
                                        /*  state change indications only)  */
    U8              spare1;             /* spare for alignment              */
} SccpCoordRqst;

typedef struct sccpDAckRqst             /* Data Acknowledge Message         */
{
    SccpNextRS      rsn;                /* rcv seq. # (M-normal data only-  */
                                        /*  not used for expedited)         */
    SccpCredit      credit;             /* window size (M-normal data only- */
                                        /*  not used for expedited)         */
    U16             spare1;             /* spare for alignment              */
} SccpDAckRqst;

typedef struct sccpDataRqst             /* Data Request Message             */
{
    SccpData        data;               /* data (M)                         */
} SccpDataRqst;

typedef struct sccpReleased             /* Released Message                 */
{
    U8              relOrig;            /* originator of release            */
    SccpCauseVal    relCause;           /* release cause (M)                */
    U16             spare1;             /* spare for alignment              */
    SccpAddr        rspPty;             /* Rel indication only - addr       */
                                        /* of responding party when         */
                                        /* outgoing conn. refused (O)       */
    SccpImportance  importance;         /* reserved for ITU-96 importance(O)*/
    SccpData        data;               /* data (O)                         */
} SccpReleased;

typedef struct sccpResetRqst            /* Reset Request Message            */
{
    SccpCauseVal    resCause;           /* release cause (M-Rqst &          */
                                        /* Indication only)                 */
    U8              resOrig;            /* origin of reset                  */
#define ORIGNETWORK        0x00         /* network originatied              */
#define ORIGENDUSER        0x01         /* user originatied                 */
    U16             spare1;             /* spare for alignment              */
} SccpResetRqst;

typedef struct sccpUdataRqst            /* Unitdata Request Message         */
{
    SccpProtoClass  protoClass;         /* protocol class (M)               */
    SccpAddr        calledPty;          /* called party address (M)         */
    SccpAddr        callingPty;         /* calling party address (M)        */
    SccpEOS         eos;                /* end-of-sequence flag (M - class  */
                                        /*   1 only)                        */
    U8              spare1;             /* spare for alignment              */
    U8              spare2;             /* spare for alignment              */
    U8              spare3;             /* spare for alignment              */
    SccpImportance  importance;         /* reserved for ITU-96 importance(O)*/
    SccpIsni        isni;               /* reserved for Ansi-96 ISNI (O)    */
    SccpData        data;               /* data (M)                         */
} SccpUdataRqst;

typedef struct sccpConnInfo             /* Connection Info (audit confirm)  */
{
    SccpProtoClass  protoClass;         /* protocol class                   */
    SccpAddr        calledPty;          /* called party address             */
    SccpAddr        callingPty;         /* calling party address            */
    U8              reason;             /* reserved for future use          */
    U8              connState;          /* connection state                 */
#define SCCP_CONN_RDY_ST 0x00           /*      ready (idle) state          */
#define SCCP_CONN_CON_ST 0x01           /*      connecting state            */
#define SCCP_CONN_DTX_ST 0x02           /*      data Transfer state         */
#define SCCP_CONN_RCG_ST 0x03           /*      reset (calling side) state  */
#define SCCP_CONN_RCD_ST 0x04           /*      reset (called side) state   */
#define SCCP_CONN_RBT_ST 0x05           /*      reset (both sides) state    */
#define SCCP_CONN_RLS_ST 0x06           /*      releasing state             */
    U8              connType;           /* connection type                  */
#define SCCP_CONN_ORIG   0x01           /*      originating node            */
#define SCCP_CONN_DEST   0x02           /*      destination node            */
#define SCCP_CONN_INTR   0x04           /*      intermediate node           */
    SccpCredit      credit;             /* proposed window size             */
} SccpConnInfo;

typedef union sccpAllMsgs
{
    SccpConnRqst    connRqst;
    SccpCoordRqst   coordRqst;
    SccpDAckRqst    dackRqst;
    SccpDataRqst    dataRqst;
    SccpReleased    released;
    SccpResetRqst   resetRqst;
    SccpUdataRqst   udataRqst;
    SccpConnInfo    connInfo;
} SccpAllMsgs;

/* Structures */
typedef struct sccpConnId
{
   S16      suId;                       /* service user ID                  */
   S16      spId;                       /* service provider ID              */
   U32      suConnId;                   /* user's connection ref number     */
   U32      spConnId;                   /* SCCP's connection ref number     */
} SccpConnId;

#define INSTID_UNKNOWN  0xFFFFFFFF      /* instance id unknown  */

typedef struct sccpRcvInfoBlk
{
    U8          board;                  /* sending board number             */
    U8          indType;                /* indication/confirm. type         */
    U8          evntType;               /* event type for status indications*/
    U8          spare1;                 /* spare for alignment              */
    S16         suId;                   /* service user id -                */
                                        /*   connectionless msgs only       */
    U16         spare2;                 /* spare for alignment              */
    SccpConnId  connId;                 /* connection ID - connection-      */
                                        /*   oriented messages only         */
    U32         opc;                    /* originating point code           */
    U32         mopc;                   /* orig point code for PC state and
                                        /*  SSN state for Multiple OPC supt.*/
} SccpRcvInfoBlk;

#pragma pack()

#ifndef _NEW_SCCP_
typedef SccpRcvInfoBlk RcvInfoBlk;
#endif


/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif

/*****************************************************************************/
#endif /* _SCCPDEF_H_ */

