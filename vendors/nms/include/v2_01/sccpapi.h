/*****************************************************************************
******************************************************************************
**
**   sccpapi.h
**
**      Constants, Structures, and Function prototype necessary for utilization
**      of the SCCP API.
**
*****************************************************************************/

/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1996                           **
**                          by TEKnique, Inc.                           **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of TEKnique, Inc.                                **
**                                                                      **
*************************************************************************/
#ifndef _SCCPAPI_H_
#define _SCCPAPI_H_

#include "sccpdefs.h"
#include "ss7type.h"

/* define the calling conventions for the API functions for various
 * operating systems - NOTE: API callers should never define the
 * preprocessor constant "_TX_SCCP_SOURCE_"; this is only for use
 * by the SCCP API source code itself.
 */

/* OS2: SCCP API is a DLL */
#ifdef __OS2__
#ifdef _TX_SCCP_SOURCE_
	/* SCCP API source definition */
#define     TXSCCPFUNC               extern _export _syscall
#else
	/* SCCP API caller's definition */
#define     TXSCCPFUNC               _syscall
#endif	/* _TX_SCCP_SOURCE_ */

/* WIN32: SCCP API is a DLL */
#elif  WIN32	                        /* WIN32 */
#ifdef _TX_SCCP_SOURCE_
	/* SCCP API source definition */
#define     TXSCCPFUNC               __declspec( dllexport ) WINAPI
#else
	/* SCCP API caller's definition */
#define     TXSCCPFUNC               WINAPI
#endif	/* _TX_SCCP_SOURCE_ */

/* all others: statically linked library */
#else
#define     TXSCCPFUNC
#endif

#define MAX_GLT_SZ          32
#define MAX_DATA_SZ         1200
#define EXTADDRLEN          16

#define ORGNETWORK         0x00         /* network originatied              */
#define ORGENDUSER         0x01         /* user originatied                 */

/* Obsolete API return values maintained for backwards compatibility        */

#define API_SUCCESS        SCCP_SUCCESS
#define API_OVERRUN        SCCP_OVERRUN
#define API_UNDERRUN       SCCP_UNDERRUN
#define API_UNBOUND        SCCP_UNBOUND
#define API_BOARD          SCCP_BOARD
#define API_DRIVER         SCCP_DRIVER


/* Set compiler structure packing option */
#ifdef __sun
#pragma pack(1)
#endif /* __sun */

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
   U32      pointCode;                  /* point code                       */
   U8       glTransType;                /* global title translation type    */
   U8       encoding;                   /* encoding scheme: ENC_UNKNOWN |   */
                                        /*   ENC_BCD_ODD | ENC_BCD_EVEN     */
   U8       numPlan;                    /* numbering plan: NP_TEL, etc.     */
   U8       natAddrInd;                 /* nature of address indicator:     */
                                        /*   NATIND_[SUBS | NATL | INTNATL] */
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
#define RETCHOPCNT          0x08        /* hop counter violation            */
#define RETCMSGXPORT        0x09        /* error in message transport       */
#define RETCLOCALPROC       0x0A        /* error in local processing        */
#define RETCREASSEMBLY      0x0B        /* dest can't do reassembly         */
#define RETCBADISNI         0xF9        /* invalid ISNI routing rqst        */
#define RETCAUTH            0xFA        /* unauthorized message             */
#define RETCINCOMPAT        0xFB        /* message incompatibility          */
#define RETCNOISNI          0xFC        /* can't do ISNI constrained        */
                                        /* routing                          */
#define RETCREDISNI         0xFD        /* redundant ISNI constrained       */
                                        /* routing info                     */
#define RETCISNIID          0xFE        /* can't do ISNI indentification    */

typedef U8 SccpCredit;

typedef struct sccpData
{
    U8      presInd;                    /* presence indicator               */
    S16     dataLen;                    /* length of data                   */
    U8      data[MAX_DATA_SZ];          /* user data                        */

} SccpData;


typedef U8 SccpEOS;

#define EOS_NO              0x00        /* not end of sequence              */
#define EOS_YES             0x01        /* end of sequence                  */

typedef U8 SccpExpDatSel;

#define EDS_NONE            0x00        /* no expedited data                */
#define EDS_REQ             0x01        /* expedited data requested         */

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

} SccpProtoClass;

typedef U8 SccpRecConfSel;

#define RCS_NONE            0x00        /* no receipt confirmation          */
#define RCS_REQ             0x01        /* receipt confirmation requested   */

typedef U8 SccpNextRS;

typedef U8 SccpSmi;

#define SMI_UNKNOWN         0x00        /* unknown                          */
#define SMI_SOLO            0x01        /* subsystem is not replicated      */
#define SMI_DUP             0x02        /* subsystem is replicated          */
#define SMI_DENIED          0x10        /* Indicate denial of coordinate    */
                                        /* state change                     */
typedef U8 SccpSsn;

typedef U8 SccpStatus;

#define SP_ACC              0x00        /* Signalling Point Accessible      */
#define SP_INACC            0x01        /* Signalling Point Inaccessible    */
#define SS_OOS              0x03        /* Subsystem out of service         */
#define SS_IS               0x04        /* Subsystem in service             */
#define SP_INACC_NODROP     0x06        /* Signalling Point Inaccessible, but connections not dropped */

/************************************************/
/*                 Messages                     */
/************************************************/

typedef struct sccpConnRqst             /* Connection Request Message       */
{
    SccpProtoClass  protoClass;         /* protocol class (M)               */
    SccpAddr        calledPty;          /* called party address (M)         */
    SccpCredit      credit;             /* proposed window size (M)         */
    SccpAddr        callingPty;         /* calling party address (O)        */
    SccpRecConfSel  rcs;                /* receipt conf. selected (M)       */
    SccpExpDatSel   eds;                /* expedited data selector (M)      */
    SccpData        data;               /* data (O)                         */

} SccpConnRqst;

typedef struct sccpCoordRqst            /* Coordination Request Message     */
{
    SccpSsn         aSsn;               /* affected subsystem (M)           */
    SccpSmi         smi;                /* subsystem multiplicity ind(M -   */
                                        /* Indication/Confirm only          */
    SccpStatus      status;             /* New status (M - subsystem & SP   */
                                        /* state change indications only    */
} SccpCoordRqst;

typedef struct sccpDAckRqst             /* Data Acknowledge Message         */
{
    SccpNextRS      rsn;                /* rcv seq. # (M-normal data only-  */
                                        /* not used for expedited)          */
    SccpCredit      credit;             /* window size (M-normal data only- */
                                        /* not used for expedited)          */
} SccpDAckRqst;

typedef struct sccpDataRqst             /* Data Request Message             */
{
    SccpData        data;               /* data (M)                         */

} SccpDataRqst;

typedef struct sccpReleased             /* Released Message                 */
{
    U8              relOrig;            /* originator of release            */
    SccpCauseVal    relCause;           /* release cause (M)                */
    SccpAddr        rspPty;             /* Rel indication only - addr       */
                                        /* of responding party when         */
                                        /* outgoing conn. refused (O)       */
    SccpData        data;               /* data (O)                         */

} SccpReleased;

typedef struct sccpResetRqst            /* Reset Request Message            */
{
    SccpCauseVal    resCause;           /* release cause (M-Rqst &          */
                                        /* Indication only)                 */
    U8              resOrig;            /* origin of reset                  */
#define ORIGNETWORK        0x00         /* network originatied              */
#define ORIGENDUSER        0x01         /* user originatied                 */

} SccpResetRqst;

typedef struct sccpUdataRqst            /* Unitdata Request Message         */
{
    SccpProtoClass  protoClass;         /* protocol class (M)               */
    SccpAddr        calledPty;          /* called party address (M)         */
    SccpAddr        callingPty;         /* calling party address (M)        */
    SccpEOS         eos;                /* end-of-sequence flag (M - class  */
                                        /* 1 only                           */
    SccpData        data;               /* data (M)                         */

} SccpUdataRqst;

typedef union sccpAllMsgs
{

    SccpConnRqst    connRqst;
    SccpCoordRqst   coordRqst;
    SccpDAckRqst    dackRqst;
    SccpDataRqst    dataRqst;
    SccpReleased    released;
    SccpResetRqst   resetRqst;
    SccpUdataRqst   udataRqst;
} SccpAllMsgs;


/* Structures */

typedef struct sccpConnId
{
   S16      suId;                       /* service user ID                  */
   S16      spId;                       /* service provider ID              */
   U32      suConnId;                   /* user's connection ref number     */
   U32      spConnId;                   /* SCCP's connection ref number     */

} SccpConnId;

typedef struct sccpRcvInfoBlk
{
    U8          board;                  /* sending TX2000 board             */
    U8          indType;                /* indication/confirm. type         */
    U8          evntType;               /* event type for status            */
                                        /* indications                      */
    S16         suId;                   /* service user id -                */
                                        /* connectionless msgs only         */
    struct sccpConnId connId;                  /* connection ID - connection-      */
                                        /* oriented messages only           */
    U32         opc;                    /* originating point code           */

} SccpRcvInfoBlk;

#ifdef __sun
#pragma pack()
#endif


#ifndef _NEW_SCCP_

typedef SccpRcvInfoBlk RcvInfoBlk;

#endif

/************************************************/
/*              Function Prototpes              */
/************************************************/
#ifdef __cplusplus
extern "C" {
#endif

OS_FD TXSCCPFUNC SCCPInitAPI( U8 board, U8 srcEnt, U8 srcInst );
S16 TXSCCPFUNC SCCPBindRqst( U8 board, U8 srcEnt, U8 srcInst, S16 suId, S16 spId, U8 ssn, U8 type );
S16 TXSCCPFUNC SCCPConnectRqst( U8 board, SccpConnId *connId, SccpConnRqst *connRqst );
S16 TXSCCPFUNC SCCPConnectResp( U8 board, SccpConnId *connId, SccpConnRqst *connRqst );
S16 TXSCCPFUNC SCCPCoordRqst( U8 board, S16 spId, SccpCoordRqst *coordRqst );
S16 TXSCCPFUNC SCCPCoordResp( U8 board, S16 spId, SccpCoordRqst *coordRqst );
S16 TXSCCPFUNC SCCPDAckRqst( U8 board, SccpConnId *connId, SccpDAckRqst *dackRqst );
S16 TXSCCPFUNC SCCPDataRqst( U8 board, SccpConnId *connId, SccpDataRqst *dataRqst );
S16 TXSCCPFUNC SCCPEDataRqst( U8 board, SccpConnId *connId, SccpDataRqst *dataRqst );
S16 TXSCCPFUNC SCCPReleaseRqst( U8 board, SccpConnId *connId, SccpReleased *relRqst );
S16 TXSCCPFUNC SCCPResetRqst( U8 board, SccpConnId *connId, SccpResetRqst *resetRqst );
S16 TXSCCPFUNC SCCPResetResp( U8 board, SccpConnId *connId );
S16 TXSCCPFUNC SCCPRetrieveMessage( OS_FD fd, SccpAllMsgs *message, SccpRcvInfoBlk *infoBlk, Bool wait );
S16 TXSCCPFUNC SCCPUDataRqst( U8 board, S16 spId, SccpUdataRqst *dataRqst );
S16 TXSCCPFUNC SCCPUnbindRqst( U8 board, U8 srcEnt, U8 srcInst, S16 spId, U8 reason );
S16 TXSCCPFUNC SCCPStateRqst( U8 board, S16 spId, U8 aSsn, U8 status );
S16 TXSCCPFUNC SCCPTermAPI( S16 handle );
OS_HSYNC TXSCCPFUNC SCCPSyncObj( OS_FD fd, S16 *errval );

#ifdef __cplusplus
}
#endif

#define SCCPCONNCFM         0xB8        /* Connect confirm                  */
#define SCCPCONNIND         0xB7        /* Connect indication               */
#define SCCPRELIND          0xBE        /* Connection release indication    */
#define SCCPDATIND          0xB9        /* Data (DT1 or DT2) indication     */
#define SCCPUDATIND         0xB1        /* Unitdata indication              */
#define SCCPEDATIND         0xBA        /* Expedited data indication        */
#define SCCPDACKIND         0xBD        /* Data acknowledge indication      */
#define SCCPRESETCFM        0xBC        /* Connection reset confirm         */
#define SCCPRESETIND        0xBB        /* Connection reset indication      */
#define SCCPSTAIND          0xB2        /* Unsolicited status indication    */
#define SCCPCOORDIND        0xB3        /* Coordinated OOS indication       */
#define SCCPCOORDCFM        0xB4        /* Coordinated OOS confirm          */
#define SCCPSTATEIND        0xB5        /* Subsystem state indication       */
#define SCCPPCSTIND         0xB6        /* Point code state indication      */



#define SCCP_NTBADADDR      0x00        /* No translation, address of       */
                                        /* such nature                      */
#define SCCP_NTSPECADDR     0x01        /* No translation, specific         */
                                        /* address                          */
#define SCCP_SSCONG         0x02        /* subsystem congestion             */
#define SCCP_SSFAIL         0x03        /* subsystem failure                */
#define SCCP_UNEQUIP        0x04        /* Unequiped User                   */
#define SCCP_NETFAIL        0x05        /* Network Failure                  */
#define SCCP_NETCONG        0x06        /* Network Congestion               */
#define SCCP_UNQUAL         0x07        /* Unqualified                      */
#define SCCP_HOPVIOLATE     0x08        /* Hop count violation(ANSI)        */
#define SCCP_ERRMSGTPRT     0x08        /* Error in message transport       */
                                        /*(CCITT92)                         */
#define SCCP_ERRLCLPROC     0x09        /* Error in local processing        */
                                        /* (CCITT92)                        */
#define SCCP_NOREASSEMB     0x0A        /* Destination cannot perform       */
                                        /* reassembly (CCITT92)             */
#define SCCP_FAIL           0x0B        /* SCCP failure (CCITT92)           */


#define SS_OOS              0x03        /* Subsystem out of service         */
#define SS_IS               0x04        /* Subsystem in service             */

#endif		/* _SCCPAPI_H_ */
