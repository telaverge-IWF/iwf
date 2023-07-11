/*****************************************************************************
******************************************************************************
*-----------------------------------------------------------------------------
*-----------------------------------------------------------------------------
**
**   tcapdef.h
**
**      Constants, Structures, and Function prototype necessary for utilization
**      of the TCAP API.
**
*-----------------------------------------------------------------------------
* $Log: tcapdef.h,v $
* Revision 9.1  2005/03/23 12:55:57  cvsadmin
* Begin PR6.5
*
* Revision 8.2  2005/03/21 13:55:21  cvsadmin
* PR6.4.2 Source Propagated to Current
*
* Revision 7.1  2002/08/26 22:10:59  mmiers
* Begin PR6.2
*
* Revision 1.2  2002/05/16 15:53:32  hcho
* Modifications for v3_6.
*
* Revision 1.1.2.1  2001/12/21 21:25:25  hcho
* Initialize v3.6 build.
*
* Revision 3.1  2000/09/06 22:12:21  hxing
* Add more NMS SS7 3.5 header files.
* $NoKeywords: $
*
* 6     8/24/98 2:19p Marcn
* Added pragmas
*
* 5     1/15/98 1:43p Tedd
* Added comment for new PC State indication SP_INACC_NODROP, which was
* added by SCCP.
*
* 4     10/14/97 5:06p Tedd
* Changed TCAP_MSG_SIZE from 512 to 668. This is the minimum buffer size
* that a user must pass.
*
* 3     10/01/97 1:06p Maf
* Added newline to end of file
*
* 2     8/13/97 5:58p Jeffd
* Fix interface problem where applications were not notified correctly
* when an invoke timed out; a new transaction type of "TCAP_LOC_IND" is
* created to carry the reject component sent to application on invoke
* timeout.
*
* 1     5/16/97 2:56p Tedd
* Initial Check-in
*-----------------------------------------------------------------------------
******************************************************************************
*****************************************************************************/

/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1997                           **
**                      by Natural MicroSystems, Inc.                   **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of Natural MicroSystems, Inc.                    **
**                                                                      **
*************************************************************************/

#ifndef _TCAPDEF_H_
#define _TCAPDEF_H_

/*#include "ss7type.h" */

/* define the calling conventions for the API functions for various
 * operating systems - NOTE: API callers should never define the
 * preprocessor constant "_TX_TCAP_SOURCE_"; this is only for use
 * by the TCAP API source code itself.
 */



#include "nmstypes.h"
#include "ctadef.h"

#ifdef __cplusplus
extern "C" {
#endif


/* OS2: TCAP API is a DLL */
#ifdef __OS2__
#ifdef _TX_TCAP_SOURCE_
    /* TCAP API source definition */
#define     TXTCAPFUNC               extern _export _syscall
#else
    /* TCAP API caller's definition */
#define     TXTCAPFUNC               _syscall
#endif  /* _TX_TCAP_SOURCE_ */

/* WIN32: TCAP API is a DLL */
#elif  WIN32	                        /* WIN32 */
#ifdef _TX_TCAP_SOURCE_
    /* TCAP API source definition */
#define     TXTCAPFUNC               __declspec( dllexport ) WINAPI
#else
    /* TCAP API caller's definition */
#define     TXTCAPFUNC               WINAPI
#endif  /* _TX_TCAP_SOURCE_ */

/* all others: statically linked library */
#else
#define     TX  TCAPFUNC
#endif

/* Turn on structure packing for Solaris */
#ifdef __sun
#pragma pack(1)
#endif

/*-----------------------------------------------------------------------------
  TCAP Version Ids
    - These id's are used to identify the revision level of this service.
  ---------------------------------------------------------------------------*/
#define TCAP_MAJORREV                        1
#define TCAP_MINORREV                        0

/*-----------------------------------------------------------------------------
  TCAP API Compatibility Level Id
    - This id is used to determine runtime compatibility between the
      installed TCAP service and clients of the TCAP service. Clients can
      be a CT Access application which accesses TCAP functionality
      via the TCAP API.
    - Clients(CT Access application) #include this file into their code and,
      therefore, insert "hard coded" values for each TCAP compat level
      into their client code.
    - The API_COMPATLEVEL is used by CT Access application developers who
      want to check the "hard coded" value in their application against the
      "hard coded" value in the installed TCAP service (as determined
      via ctaGetServiceVersion() will be available in CT Access Version 2.1).
    - API compatibility level value should be incremented when the associated
      source module changes in a non-backwards compatible way. Refer to the CT
      Access Service Writer's Manual for more info.
  ---------------------------------------------------------------------------*/
#define TCAPAPI_COMPATLEVEL                  1

/****************************************************************************/
/* important constants and common data structures                           */
/****************************************************************************/

/* Event generated by TCAP Service and sent back to client for all strings  */
#define TCAPEVN_DATA   (TCAP_SVCID << 16) | 0x2000 | 0x01     /* 0x252001   */

/* TCAP - return code definitions */
#define TCAP_SUCCESS    SUCCESS   /* API completed successfully; the same as CT Access success  */
#define TCAP_BOARD     (TCAP_SVCID << 16) | 0x01  /*0x250001 Board number out of range          */
#define TCAP_DRIVER    (TCAP_SVCID << 16) | 0x02  /*0x250002 CPI driver reported an error       */
#define TCAP_UNINIT    (TCAP_SVCID << 16) | 0x03  /*0x250003 Failed to call TcapInit()    1-st  */
#define TCAP_INDEX     (TCAP_SVCID << 16) | 0x04  /*0x250004 Component index does not exist     */
#define TCAP_NOMSG     (TCAP_SVCID << 16) | 0x05  /*0x250005 No event messages waiting          */
#define TCAP_OVERFLOW  (TCAP_SVCID << 16) | 0x06  /*0x250006 User info is too big for TCAP msg  */
#define TCAP_PARAM     (TCAP_SVCID << 16) | 0x07  /*0x250007 Invalid parameter                  */
/* #define TCAP_NO_BIND   (TCAP_SVCID << 16) | 0x08  0x250008 No binr confirm                    */

/*-----------------------------------------------------------------------------
  TCAP Reason Codes.
    - These codes are constructed using the TCAP_SVCID, the CT Access
      CTA_CODE_REASON id, and a 1-based sequence number. The formula is
        REASONCODE = ((TCAP_SVCID<<16) | (CTA_CODE_REASON | SEQUENCE))
  ---------------------------------------------------------------------------*/

#define TCAP_REASON_SPID_RANGE   (TCAP_SVCID << 16) | 0x1000 | 0x01     /* 0x251001 SpId out of range */
#define TCAP_REASON_SPID_UNDEF   (TCAP_SVCID << 16) | 0x1000 | 0x02     /* 0x251002 SpId not configured */
#define TCAP_REASON_SCCP_SPID_RANGE   (TCAP_SVCID << 16) | 0x1000 | 0x03   /* 0x251001 SCCP SpId out of range */
#define TCAP_REASON_SCCP_SPID_UNDEF   (TCAP_SVCID << 16) | 0x1000 | 0x04   /* 0x251002 SCCP SpId not configured */
#define TCAP_REASON_SCCP_NO_NSAP      (TCAP_SVCID << 16) | 0x1000 | 0x05   /* 0x251002 SCCP NSAP not configured or not bound */
#define TCAP_REASON_UNKNOWN      (TCAP_SVCID << 16) | 0x1000 | 0xff     /* 0x2510FF unknown reason */


/* this is the minimum size buffer that calling application must allocate in
 * order to receive TCAP message events
 */
/* TRP modified MSG_SIZE from 512 to 668 */
#define TCAP_MSG_SIZE       668

/* Maximum size (bytes) of a global title */
#define TCAP_MAX_GLT_SZ     32

/* this is the maximum length of variable length octet strings used for
 * application context names, etc.
 */
#define TCAP_MAX_OCTSTR     64      /* max size of TCAP octet strings */

/* Bind flag states */
#define TCAP_BIND_FLAG_OFF  0
#define TCAP_BIND_FLAG_ON   1

/* basic data structure for a variable length octet string, consists of
 * a length followed by the content.  For optional octet strings, a length
 * value of zero is used to indicate that the element is "not present".
 */
typedef struct Tcap_Octet_Str
{
    U16 length;
    U8  fill;                   /* fill for alignment */
    U8  fill2;                  /* fill for alignment */
    U8  octStr[TCAP_MAX_OCTSTR];
} TcapOctetStr;

/* Component ID structure used in the component definitions; consists of a flag to
 * indicate if the ID is present/populated (i.e., for optional IDs) or not and, if
 * present, an ID value.  For the present flag, use the PRESENT/NOT_PRESENT
 * identifiers defined in <sccpdef.h>
 */
typedef struct Tcap_CompId
{
    U8 present;                 /* This component ID present/not present */
    U8 compId;                  /* component ID value */
    U8 fill;                    /* fill for alignment */
    U8 fill2;                   /* fill for alignment */
} TcapCompId;

/* This structure defines the SCCP quality of service parameters */
typedef struct Tcap_Sccp_Qos
{
    U8  priority;               /* message priority: (lowest) 0..3 (highest) */

    U8  retOpt;                 /* return options for undeliverable messages... */
/* use one of following values from <sccpdef.h>:
 * #define MSG_DISCARD  0x00  discard message on error
 * #define MSG_RETURN   0x08  return message on error
 */
    U8  seqDlvy;                /* sequential delivery required?... */
#define TCAP_QOS_NORMAL     0   /* normal delivery, use SCCP class 0 */
#define TCAP_QOS_SEQDEL     1   /* sequential delivery required, use SCCP class 1 */

    U8  spare;                  /* spare for alignment */

} TcapSccpQos;

/* SCCP Address Structure, TCAP-specific variant */

typedef struct Tcap_Sp_Addr             /* Called/Calling Party Address     */
{
    U8       presInd;                    /* presence indicator               */
    U8       spare1;                     /* spare for alignment              */
    S16      swType;                     /* address type (ANSI/ITU-T)        */
    U8       subsystemInd;               /* subsystem indicator              */
    U8       pointCodeInd;               /* point code indicator             */
    U8       glTitleInd;                 /* global title indicator           */
    U8       routingInd;                 /* routing indicator                */
    U32      pointCode;                  /* point code                       */
    U8       natIntInd;                  /* national/international ind.      */
    U8       subsystem;                  /* subsystem number                 */
    U8       glTransType;                /* global title translation type    */
    U8       encoding;                   /* address encoding scheme          */
    U8       numPlan;                    /* numbering plan                   */
    U8       natAddrInd;                 /* nature of address indicator      */
    U8       spare2;                     /* spare for structure alignment    */
    U8       glTitleLen;                 /* length of global title           */
    U8       glTitle[TCAP_MAX_GLT_SZ];   /* Global Title                     */
} TcapSpAddr;

/****************************************************************************/
/* General Transaction Info Section                                         */
/****************************************************************************/

/* This is the transaction information block which carries general transaction-level
 * info about the transaction message being sent or received
 */
typedef struct Tcap_Trans_Info
{
    U8          msgType;        /* transaction message (or package) type... */
#define TCAP_BEGIN        1     /* begin message */
#define TCAP_CONTINUE     2     /* continue message */
#define TCAP_END          3     /* end message */
#define TCAP_U_ABORT      4     /* ITU-T user abort message */
#define TCAP_ABORT        TCAP_U_ABORT
#define TCAP_UNI          5     /* ITU-T unidirectional */
#define TCAP_QRY_PRM      6     /* query with permission message */
#define TCAP_QRY_NO_PRM   7     /* query without permission message */
#define TCAP_RESPONSE     8     /* response message */
#define TCAP_CNV_PRM      9     /* conversation with permission message */
#define TCAP_CNV_NO_PRM  10     /* conversation without permission message */
#define TCAP_ANSI_UABORT 11     /* TCAP ANSI User abort message */
#define TCAP_ANSI_ABORT  TCAP_ANSI_UABORT
#define TCAP_ANSI_PABORT 12     /* TCAP ANSI Protocol abort message */
#define TCAP_P_ABORT     13     /* ITU-T protocol abort message */
#define TCAP_ANSI_UNI    14     /* ANSI unidirectional */
#define TCAP_LOC_IND     15     /* Special locally generated component indication */
#define TCAP_XACTION_TIMEOUT 16 /* Locally generated transaction timeout indication */

    U8          abortCause;     /* cause of an abort initiated by TCAP layer, valid
                                 * only if msgType is TCAP_ANSI_PABORT or TCAP_P_ABORT ...*/
/* P-Abort ITU-T Causes */
#define TCAP_ABORT_UNREC_MSG 0x00  /* unrecognized message */
#define TCAP_ABORT_UNREC_TRS 0x01  /* unrecognized transaction id */
#define TCAP_ABORT_BAD_FRMT  0x02  /* badly formatted transaction part */
#define TCAP_ABORT_INC_TRANS 0x03  /* incorrect transaction part */
#define TCAP_ABORT_RESOURCE  0x04  /* insufficient resources */
#define TCAP_ABORT_ABNML_DLG  0x05 /* incorrect dialog portion */
#define TCAP_ABORT_NO_CMN_DLG 0x06 /* unsupported protocol version in dialog portion */
 /* P-Abort ANSI Causes */
#define TCAP_ANSI_ABORT_UP    0x01  /* unrecognized package type */
#define TCAP_ANSI_ABORT_IN    0x02  /* incorrect transaction portion */
#define TCAP_ANSI_ABORT_BD    0x03  /* badly structured transaction portion */
#define TCAP_ANSI_ABORT_UT    0x04  /* unrecognized transaction ID */
#define TCAP_ANSI_ABORT_PR    0x05  /* Permission to release problem */
#define TCAP_ANSI_ABORT_RN    0x06  /* resource not available */

    U8          preArgEnd;      /* pre-arranged end? 0=no, 1=yes */
    U8          chkpt;          /* Checkpoint              */
#define TCAP_NO_CHKPT         0
#define TCAP_CHKPT            1
#define TCAP_CHKPT_DEFAULT    2
    U16         inactvTimer;    /* Inactivity timer */
    U16         spare;          /* spare for structure alignment */
    U32         suDlgId;        /* service user dialog ID */
    U32         spDlgId;        /* service provider (TCAP) dialog ID */
    TcapSpAddr  cdAddr;         /* called party (destination) address */
    TcapSpAddr  cgAddr;         /* calling party (originator) address */
    TcapSccpQos qos;            /* SCCP quality of service requested */
} TcapTransInfo;

/****************************************************************************/
/* ITU-T Dialog Section                                                     */
/****************************************************************************/

/* TCAP ITU-92 Dialog Portion - this structure is used for setting (or
 * retrieving, for incoming messages), the values to be used in the
 * optional dialog section of the transaction message; it is used only
 * for ITU-92 mode
 */
typedef struct Tcap_Dlg_Sect
{
    U8 dlgType;                 /* type of message this dialog is for... */
#define TCAP_DLGP_UNK    0      /* unknown dialog portion type */
#define TCAP_DLGP_UNI    1      /* unidirectional dialog portion type */
#define TCAP_DLGP_REQ    2      /* request dialog portion type */
#define TCAP_DLGP_RSP    3      /* response dialog portion type */
#define TCAP_DLGP_ABT    4      /* abort dialog portion type */
#define TCAP_DLGP_NONE   0xFF   /* dialog portion not present */

    U8 resPres;                 /* result field present?  */
    U8  fill;                   /* fill for alignment */
    U8  fill2;                  /* fill for alignment */
    TcapOctetStr apConName;     /* application context name */

    U8 result;                  /* dialog result: accepted/rejected perm... */
#define TCAP_DLG_ACCEPTED   0   /* dialog has been accepted */
#define TCAP_DLG_REJ_PERM   1   /* dialog was rejected permanently */

    U8 resSrc;                  /* result source: user or provider (TCAP)... */
#define TCAP_DLG_SU_TAG 0x21    /* dialog service user tag */
#define TCAP_DLG_SP_TAG 0x22    /* dialog service provider tag */

    U8 resDiag;                 /* result diagnostic... */
#define TCAP_DLG_RSD_NULL   0   /* result source diagnostic: null */
#define TCAP_DLG_RSD_NORSN  1   /* result source diagnostic: no reason */
#define TCAP_DLG_RSD_NOACN  2   /* result source diagnostic: user: no acn*/
#define TCAP_DLG_RSD_NCDLG  2   /* result source diagnostic: provider:
                                 * no common dialog portion */
    U8 abrtSrc;                 /* source of abort */
#define TCAP_DLG_USR_ABRT   0   /* Service user */
#define TCAP_DLG_PRV_ABRT   1   /* Service provider */

} TcapDlgSect;

/****************************************************************************/
/* Component Section - ANSI specific structures - Operation Code            */
/****************************************************************************/

/* structure used to define ANSI invoke operation codes */
typedef struct Tcap_Ansi_Opcode
{
    U8  opCodeId;               /* operation code identifier: National TCAP or private */
#define TCAP_NATIONAL    3      /* National TCAP */
#define TCAP_PRIVATE     4      /* Private TCAP */

    U8  opFamily;               /* operation code family, national values below... */
#define TCAP_ANSI_NOF_NU     0x00   /* not used */
#define TCAP_ANSI_NOF_PARAM  0x01   /* parameter */
#define TCAP_ANSI_NOF_CHGING 0x02   /* charging */
#define TCAP_ANSI_NOF_PR_INS 0x03   /* provide instructions */
#define TCAP_ANSI_NOF_CN_CTL 0x04   /* connection control */
#define TCAP_ANSI_NOF_CL_INT 0x05   /* caller interaction */
#define TCAP_ANSI_NOF_SND_NO 0x06   /* send notification */
#define TCAP_ANSI_NOF_NET_MN 0x07   /* network management */
#define TCAP_ANSI_NOF_PROC   0x08   /* procedural */
#define TCAP_ANSI_NOF_OP_CTL 0x09   /* Operation Control Family (ANSI-92) */
#define TCAP_ANSI_NOF_RP_EVT 0x0A   /* Report Event Family (ANSI-92) */
#define TCAP_ANSI_NOF_MISC   0x7E   /* miscellaneous */
#define TCAP_ANSI_NOF_RSRVD  0x7F   /* reserved */
#define TCAP_ANSI_NOF_RP_REQ 0x80   /* reply required - OR in with above values */

    U8  opSpec;                 /* operation code specifier, national values below... */
#define TCAP_ANSI_OS_RSRVD   0xFF   /* all families - reserved */
#define TCAP_ANSI_OS_NU      0x00   /* all families - not used */
#define TCAP_ANSI_OS_PRV_VAL 0x01   /* parameter - provide value */
#define TCAP_ANSI_OS_SET_VAL 0x02   /* parameter - set value */
#define TCAP_ANSI_OS_BL_CALL 0x01   /* charging - bill call */
#define TCAP_ANSI_OS_START   0x01   /* provide instruction - start */
#define TCAP_ANSI_OS_ASSIST  0x02   /* provide instruction - assist */
#define TCAP_ANSI_OS_CONNECT 0x01   /* connection control - connect */
#define TCAP_ANSI_OS_TMP_CON 0x02   /* connection control - temporary connect */
#define TCAP_ANSI_OS_DISC    0x03   /* connection control - disconnect */
#define TCAP_ANSI_OS_FWD_DIS 0x04   /* connection control - forward disconnect */
#define TCAP_ANSI_OS_PLY_ANN 0x01   /* caller interaction - play announcement */
#define TCAP_ANSI_OS_COL_DIG 0x02   /* cllr intrctn - play ann & coll digits */
#define TCAP_ANSI_OS_INF_WTG 0x03   /* caller interaction - info. waiting */
#define TCAP_ANSI_OS_INF_PVD 0x03   /* caller interaction - info. provided */
#define TCAP_ANSI_OS_PTY_FRE 0x01   /* send notification - when party free */
#define TCAP_ANSI_OS_RAS_TRM 0x01   /* procedural - report assist termination */
#define TCAP_ANSI_OS_CANCEL  0x01   /* Operation Control - Cancel */
#define TCAP_ANSI_OS_VM_AVL  0x01   /* Report Event - Voice Message Available */
#define TCAP_ANSI_OS_VM_RTVD 0x02   /* Report Event - Voice Message Retrieved */
#define TCAP_ANSI_OS_Q_CALL  0x02   /* Miscellaneous - Queue Call */
#define TCAP_ANSI_OS_DQ_CALL 0x02   /* Miscellaneous - Dequeue Call */
#define TCAP_ANSI_OS_CAL_GAP 0x01   /* network management - call gap */
#define TCAP_ANSI_OS_TMP_HDN 0x01   /* procedural - temporary handover */

    U8  spare;                  /* spare for alignment */
} TcapAnsiOpcode;

/****************************************************************************/
/* Component Section - ANSI specific structures - Error Code                */
/****************************************************************************/

/* structure used to define ANSI return error component error codes */
typedef struct Tcap_Ansi_Errcode
{
    U8  errCodeId;              /* error code identifier: National TCAP or private...  */
/* use one of following values, defined above for opCodeId.
 * #define TCAP_NATIONAL    3
 * #define TCAP_PRIVATE     4
 */
    U8  errCode;                /* error code */
#define TCAP_ANSI_ERR_NU     0x00   /* not used */
#define TCAP_ANSI_ERR_UX_CMP 0x01   /* unexpected component sequence */
#define TCAP_ANSI_ERR_UX_DAT 0x02   /* unexpected data value */
#define TCAP_ANSI_ERR_UA_NET 0x03   /* unavailable network resource */
#define TCAP_ANSI_ERR_MSG_RC 0x04   /* missing customer record */
#define TCAP_ANSI_ERR_REP_OD 0x05   /* reply overdue (ANSI-88)*/
#define TCAP_ANSI_ERR_REP_SC 0x05   /* spare code (ANSI-92)*/
#define TCAP_ANSI_ERR_DAT_UA 0x06   /* data unavailable */
#define TCAP_ANSI_ERR_TSK_RE 0x07   /* Task refused (ANSI-92)*/
#define TCAP_ANSI_ERR_Q_FULL 0x08   /* Queue Full (ANSI-92)*/
#define TCAP_ANSI_ERR_NO_Q   0x09   /* No Queue (ANSI-92)*/
#define TCAP_ANSI_ERR_TMR_EX 0x0A   /* Timer Expired (ANSI-92)*/
#define TCAP_ANSI_ERR_DAT_EX 0x0B   /* Data already exists (ANSI-92)*/
#define TCAP_ANSI_ERR_UNAUTH 0x0C   /* Unauthorized Request (ANSI-92)*/
#define TCAP_ANSI_ERR_NOT_QD 0x0D   /* Not Queued (ANSI-92)*/
#define TCAP_ANSI_ERR_UAS_DN 0x0E   /* Unassigned DN (ANSI-92)*/
#define TCAP_ANSI_ERR_SPARE  0x0F   /* Spare (ANSI-92)*/
#define TCAP_ANSI_ERR_NOT_AV 0x10   /* Notification Available on dest DN (ANSI-92)*/
#define TCAP_ANSI_ERR_VMSR_E 0x11   /* VMSR sys. ID does not match user prof. (ANSI-92)*/
    U8  fill;                   /* fill for alignment */
    U8  fill2;                  /* fill for alignment */

} TcapAnsiErrcode;

/****************************************************************************/
/* Component Section - ANSI specific structures - Reject Problem Code       */
/****************************************************************************/

/* structure used to define ANSI reject component problem codes */
typedef struct Tcap_Ansi_Prbcode
{
    U8  probType;               /* problem type... */
#define TCAP_ANSI_PRB_NU     0x00   /* not used */
#define TCAP_ANSI_PRB_GEN    0x01   /* general */
#define TCAP_ANSI_PRB_INV    0x02   /* invoke */
#define TCAP_ANSI_PRB_RR     0x03   /* return result */
#define TCAP_ANSI_PRB_RE     0x04   /* return error */
#define TCAP_ANSI_PRB_TRANS  0x05   /* transaction portion */
#define TCAP_ANSI_PRB_RSRVD  0xFF   /* all families - reserved */

    U8  probSpec;               /* problem specifier... */
#define TCAP_ANSI_PRB_UR_CMP 0x01   /* general - unrecognized component */
#define TCAP_ANSI_PRB_IN_CMP 0x02   /* general - incorrect component portion */
#define TCAP_ANSI_PRB_BD_CMP 0x03   /* general - badly structured component portion */
#define TCAP_ANSI_PRB_DUP_ID 0x01   /* invoke - duplicate invoke ID */
#define TCAP_ANSI_PRB_UR_OP  0x02   /* invoke - unrecognized operation code */
#define TCAP_ANSI_PRB_IN_PRM 0x03   /* invoke - incorrect parameter  */
#define TCAP_ANSI_PRB_IUR_ID 0x04   /* invoke - unrecognized correlation ID */
#define TCAP_ANSI_PRB_RUR_ID 0x01   /* return result - unrecognized correlation ID */
#define TCAP_ANSI_PRB_UX_RES 0x02   /* return result - unexpected return result */
#define TCAP_ANSI_PRB_EUR_ID 0x01   /* return error - unrecognized correlation ID */
#define TCAP_ANSI_PRB_UX_RER 0x02   /* return error - unexpected return error */
#define TCAP_ANSI_PRB_UR_ERR 0x03   /* return error - unrecognized error */
#define TCAP_ANSI_PRB_UX_ERR 0x04   /* return error - unexpected error */
#define TCAP_ANSI_PRB_EN_PRM 0x05   /* return error - incorrect parameter */
#define TCAP_ANSI_PRB_UR_PKG 0x01   /* transaction portion - unrecognized package type */
#define TCAP_ANSI_PRB_IN_TRN 0x02   /* transaction portion - incorrect transaction portion */
#define TCAP_ANSI_PRB_BD_TRN 0x03   /* transaction portion - badly structured transaction portion */
#define TCAP_ANSI_PRB_UR_TRN 0x04   /* transaction portion - unrecognized transaction ID */
#define TCAP_ANSI_PRB_PR_TRN 0x05   /* transaction portion - permission to release */
#define TCAP_ANSI_PRB_RU_TRN 0x06   /* transaction portion - resource unavailable */
    U8  fill;                   /* fill for alignment */
    U8  fill2;                  /* fill for alignment */

} TcapAnsiPrbcode;

/****************************************************************************/
/* Component Section - ANSI specific structures - Component Structure       */
/****************************************************************************/

/* The following structure is used to describe a single ANSI component */
typedef struct Tcap_Ansi_Comp
{
   TcapCompId   invokeId;       /* invoke id */
   TcapCompId   corrId;         /* correlation id */
   U16          invokeTimer;    /* Invoke Timer */
   U8           paramFlg;       /* Set or Sequence... */
#define TCAP_NO_SET_SEQ  0      /* no parameters */
#define TCAP_SEQUENCE    1      /* parameter is a sequence */
#define TCAP_SET         2      /* parameter is a set */

    U8          spare;          /* spare for alignment */

   union                        /* component type-specfic fields */
   {
        TcapAnsiOpcode  opcode;     /* operation code for invoke components */
        TcapAnsiErrcode errcode;    /* error code for return error components */
        TcapAnsiPrbcode prbcode;    /* problem code for abort components */
   } uComp;

} TcapAnsiComp;

/****************************************************************************/
/* Component Section - ITU-T specific structures - Opcode, Errcode, Prbcode */
/****************************************************************************/

/* structure used to define ITU-T invoke operation codes */
typedef struct Tcap_Itu_Opcode
{
    U8          opCodeType;     /* operation code type: National TCAP or private */
#define TCAP_NONE       0       /* opcode omitted (return result only) */
#define TCAP_LOCAL      1       /* local error/operation code */
#define TCAP_GLOBAL     2       /* global error/operation code */

    U8          spare;          /* spare for alignment */
    U8          fill;           /* fill for alignment */
    U8          fill2;          /* fill for alignment */
    TcapOctetStr opCode;        /* opcode length/value */
} TcapItuOpcode;


/* structure used to define ITU-T return error component error codes */
typedef struct Tcap_Itu_Errcode
{
    U8           errCodeId;     /* error code identifier: National TCAP or private...  */
/* use one of following values, defined above for opCodeId.
 * #define TCAP_LOCAL      1
 * #define TCAP_GLOBAL     2
 */
    U8           spare;         /* spare for alignment */
    U8           fill;          /* fill for alignment */
    U8           fill2;         /* fill for alignment */
    TcapOctetStr errCode;       /* error code length/value */

} TcapItuErrcode;

/* structure used to define ITU-T reject component problem codes */
typedef struct Tcap_Itu_Prbcode
{
    U8  probType;               /* problem type... */
#define TCAP_PROB_NONE    0x00  /* no problem code flag */
#define TCAP_PROB_GENERAL 0x80  /* general problem code flag */
#define TCAP_PROB_INVOKE  0x81  /* invoke problem code flag */
#define TCAP_PROB_RET_RES 0x82  /* return result problem code flag */
#define TCAP_PROB_RET_ERR 0x83  /* return error problem code flag */

    U8  spare;                  /* spare for alignment */
    U8  fill;                   /* fill for alignment */
    U8  fill2;                  /* fill for alignment */
    TcapOctetStr prbCode;       /* error code length/value ...*/
/* General Problems */
#define TCAP_UNREC_COMP      0   /* Unrecognized component */
#define TCAP_MISTYPED_COMP   1   /* Mistyped parameter */
#define TCAP_BAD_STRUC_COMP  2   /* Badly structured component */
/* Invoke problems */
#define TCAP_DUP_INVOKE      0   /* Duplicate Invoke Id */
#define TCAP_UNREC_OPR       1   /* Unrecognized invoke Id */
#define TCAP_MISTYPED_PARAM  2   /* Mistyped parameter */
#define TCAP_RESOURCE_LIMIT  3   /* Resource limitation */
#define TCAP_INIT_RELEASE    4   /* Initiating Release */
#define TCAP_UNREC_LINKED_ID 5   /* Unrecognized linked Id */
#define TCAP_LINKED_RESP_UNX 6   /* Linked response unexpected */
#define TCAP_UNX_LINKED_OP   7   /* Unexpected linked operation */
/* Return result problem */
#define TCAP_RR_UNREC_INVKID 0   /* Unrecognized invoke Id */
#define TCAP_UNX_RETRSLT     1   /* Return result unexpected */
#define TCAP_RR_MISTYPED_PAR 2   /* Return result mistyped parameter */
/* Return Error problems */
#define TCAP_RE_UNREC_INVKID 0   /* return error unerecognized invoke id */
#define TCAP_RE_UNX_RETERR   1   /* Unexpected return error */
#define TCAP_UNREC_ERROR     2   /* Unrecgnized error */
#define TCAP_UNX_ERR         3   /* Unexpected error */
#define TCAP_RE_MISTYPED_PAR 4   /* Mistyped parameter */

} TcapItuPrbcode;

/****************************************************************************/
/* Component Section - ITU-T specific structures - Component Structure       */
/****************************************************************************/

/* The following structure is used to describe a single ANSI component */
typedef struct Tcap_Itu_Comp
{
    TcapCompId  invokeId;       /* invoke id */
    TcapCompId  linkedId;       /* linked id */
    U16         invokeTimer;    /* Invoke Timer */
    U8          opClass;        /* operation class - invoke only, 1..4 */
    U8          spare;          /* spare for alignment */

   union                        /* component type-specfic fields */
   {
        TcapItuOpcode   opcode;     /* operation code for invoke/ret reslt components */
        TcapItuErrcode  errcode;    /* error code for return error components */
        TcapItuPrbcode  prbcode;    /* problem code for abort components */
   } uComp;

} TcapItuComp;

/****************************************************************************/
/* Component Section - General Component Structure                          */
/****************************************************************************/

/* The following structure is used to describe a single TCAP component */
typedef struct Tcap_Comp
{
    U8          compType;       /* Component type... */
#define TCAP_UNKNOWN     0      /* unknown component */
#define TCAP_INVOKE      1      /* invoke */
#define TCAP_RET_RES_L   2      /* return result last */
#define TCAP_RET_ERR     3      /* return error */
#define TCAP_REJECT      4      /* reject */
#define TCAP_RET_RES_NL  5      /* return result not last */
#define TCAP_INVOKE_L    6      /* invoke last */
#define TCAP_INVOKE_NL   7      /* invoke not last */
#define TCAP_CANCEL      8      /* cancel outstanding invoke (local only) */

    U8          rejSrc;         /* source of reject/cancel component... */
#define TCAP_COMP_NONE        0   /* no additional status */
#define TCAP_COMP_CANCEL      5   /* invoke component timed out */
#define TCAP_COMP_REJ_USR     6   /* TC user reject component */
#define TCAP_COMP_REJ_LOCAL   7   /* local TCAP reject component */
#define TCAP_COMP_REJ_REMOTE  8   /* remote TCAP reject component */

    U8          fill;               /* fill for alignment */
    U8          fill2;              /* fill for alignment */

   union                            /*  ANSI or ITU-T component */
   {
        TcapItuComp     ituComp;    /* ITU-T component */
        TcapAnsiComp    ansiComp;   /* ITU-T component */
   } uProt;

} TcapComp;

/****************************************************************************/
/* Incoming Event Structures  - Individual Events                           */
/****************************************************************************/

/* Incoming coordinated status change indication or confirm event
 * (eventType == TCAP_EVENT_COORD_IND or TCAP_EVENT_COORD_CFM)
 */
typedef struct Tcap_Coord_Event
{
    U8          aSsn;           /* affected subsystem number */

    U8          smi;            /* subsystem multiplicity indicator... */
/* one of following values from <sccpdef.h>: */
/* #define SMI_UNKNOWN         0x00      unknown                          */
/* #define SMI_SOLO            0x01      subsystem is not replicated      */
/* #define SMI_DUP             0x02      subsystem is replicated          */
/* #define SMI_DENIED          0x10      Indicate denial of coordinate    */
/*                                       state change  (TCAP_EVENT_COORD_CFM only) */
    U8          fill;           /* fill for alignment */
    U8          fill2;          /* fill for alignment */

} TcapCoordEvent;


/* Incoming signaling point status change indication
 * (eventType == TCAP_EVENT_PC_STATE)
 */
typedef struct Tcap_PCState_Event
{
    U32         aPc;            /* affected point code */

    U8          status;         /* new signaling point status... */
/* one of following values from <sccpdef.h>: */
/* #define SP_ACC       0x00    Signalling Point Accessible      */
/* #define SP_INACC     0x01    Signalling Point Inaccessible    */
/* #define SP_INACC_NODROP 0x06 Signalling Point Inaccessible, Connections not dropped    */

    U8          spare;          /* spare for alignment */
    U8          fill;           /* fill for alignment */
    U8          fill2;          /* fill for alignment */
} TcapPCStateEvent;


/* Incoming subsystem status change indication (eventType == TCAP_EVENT_SSN_STATE) */
typedef struct Tcap_SsnState_Event
{

    U8          aSsn;           /* affected subsystem number */

    U8          status;         /* new signaling point status... */
/* one of following values from <sccpdef.h>: */
/* #define SS_OOS   0x03        Subsystem out of service         */
/* #define SS_IS    0x04        Subsystem in service             */

    U8          smi;            /* subsystem multiplicity indicator... */
/* one of following values from <sccpdef.h>: */
/* #define SMI_UNKNOWN         0x00      unknown                          */
/* #define SMI_SOLO            0x01      subsystem is not replicated      */
/* #define SMI_DUP             0x02      subsystem is replicated          */
/* #define SMI_DENIED          0x10      Indicate denial of coordinate    */
/*                                       state change  (TCAP_EVENT_COORD_CFM only) */

    U8          spare;          /* spare for alignment */
    U32         aPc;            /* affected point code - for future use */
} TcapSsnStateEvent;

/* Incoming run state indication
 * (eventType == TCAP_EVENT_RUN_STATE)
 */
typedef struct Tcap_RunState_Event
{
    U8          status;         /* Run State status... */
#define TCAP_BACKUP     0x30
#define TCAP_PRIMARY    0x31
#define TCAP_STANDALONE 0x32
#define TCAP_BACKUP_READY 0x50
    U8          spare;          /* spare for alignment */
    U8          fill;           /* fill for alignment */
    U8          fill2;          /* fill for alignment */
} TcapRunStateEvent;

/* Incoming notification (message undeliverable by SCCP) event
 * (eventType == TCAP_EVENT_NOT_IND)
 */
typedef struct Tcap_Notif_Event
{
    TcapTransInfo   transInfo;  /* transaction info block from failed Trans Req */

    U8              retcause;   /* cause for return of undeliverable message */
/* one of following values from <sccpdef.h>: */
/* #define RETCGENTRANS     0x00        no translation for address of this nature */
/* #define RETCNOTRANS      0x01        no translation for this address  */
/* #define RETCSUBSCONG     0x02        Subsystem congestion             */
/* #define RETCSUBSFAIL     0x03        Subsystem failure                */
/* #define RETCUNQUIP       0x04        unequipped user                  */
/* #define RETCNETFAIL      0x05        network failure                  */
/* #define RETCNETCONG      0x06        Network congestion               */
/* #define RETCUNQUALIFIED  0x07        unqualified                      */
/* #define RETCHOPCNT       0x08        hop counter violation            */
/* #define RETCMSGXPORT     0x09        error in message transport       */
/* #define RETCLOCALPROC    0x0A        error in local processing        */
/* #define RETCREASSEMBLY   0x0B        dest can't do reassembly         */
/* #define RETCBADISNI      0xF9        invalid ISNI routing rqst        */
/* #define RETCAUTH         0xFA        unauthorized message             */
/* #define RETCINCOMPAT     0xFB        message incompatibility          */
/* #define RETCNOISNI       0xFC        can't do ISNI constrained routing*/
/* #define RETCREDISNI      0xFD        redundant ISNI constrained       */
/*                                      routing info                     */
/* #define RETCISNIID       0xFE        can't do ISNI indentification    */

    U8          spare;          /* spare for alignment */
    U8          fill;           /* fill for alignment */
    U8          fill2;          /* fill for alignment */

} TcapNotifEvent;


/* Incoming status (error) indication (eventType == TCAP_EVENT_STA_IND) */
typedef struct Tcap_Status_Event
{
    S16         status;         /* error cause... */
#define TCAP_R_EVT_INAPP   1    /* received event in inappropriate state */
#define TCAP_MSNG_ELE      2    /* missing mandatory element */
#define TCAP_DUP_INV_ID    3    /* duplicate invoke ID  */
#define TCAP_INV_REJ       4    /* received REJECT with syntax error */

    S16         suId;           /* caller's service user ID */
} TcapStatusEvent;

/* Incoming data (transaction) indication (eventType == TCAP_EVENT_DAT_IND) */
typedef struct Tcap_Trans_Event
{
    U32             opc;        /* originating point code from routing label */
    TcapTransInfo   transInfo;  /* transaction information block */
    TcapDlgSect     dlgPart;    /* ITU-92 dialog section */
    U16             numComps;   /* number of components present in this message */
    U16             userInfoLen;/* byte length user info, (0->none) (ITU-92 only) */
    U8             *pUserInfo;  /* pointer to user info, if any (ITU-92 only) */

} TcapTransEvent;

/****************************************************************************/
/* TCAP Receive Event Info Structure - General                              */
/****************************************************************************/

/* The following structure is returned by TCAPRetrieveMsg() to
 * describe the received event
 */
typedef struct Tcap_Recv_Info
{
    U8          eventType;      /* Event type... */
#define TCAP_EVENT_DAT_IND      0xB1  /* Data (transaction) indication */
#define TCAP_EVENT_STA_IND      0xB2  /* Status indication */
#define TCAP_EVENT_COORD_IND    0xB3  /* coordinated state change indication */
#define TCAP_EVENT_COORD_CFM    0xB4  /* coordinated state change confirmation */
#define TCAP_EVENT_SSN_STATE    0xB5  /* Subsystem state change indication */
#define TCAP_EVENT_PC_STATE     0xB6  /* Signaling point state change indication */
#define TCAP_EVENT_RUN_STATE    0xB7  /* Run state indication */
#define TCAP_EVENT_NOT_IND      0xBF  /* Notice (sccp undeliverable) indication */

    U8          spare;          /* spare for alignment */
    /* TRP changed next parameter from spId to suId.*/
    S16         suId;           /* TCAP SAP ID that this event belongs to */

   union                                /*  event-specific info */
   {
        TcapCoordEvent      coord;      /* eventType == TCAP_EVENT_COORD_IND [or CFM]*/
        TcapPCStateEvent    pcstate;    /* eventType == TCAP_EVENT_PC_STATE */
        TcapSsnStateEvent   ssnstate;   /* eventType == TCAP_EVENT_SSN_STATE */
        TcapRunStateEvent   runstate;   /* eventType == TCAP_EVENT_RUN_STATE */
        TcapNotifEvent      notif;      /* eventType == TCAP_EVENT_NOT_IND */
        TcapStatusEvent     status;     /* eventType == TCAP_EVENT_STA_IND */
        TcapTransEvent      data;       /* eventType == TCAP_EVENT_DAT_IND */
   } event;

} TcapRecvInfo;


#ifdef __sun
#pragma pack()
#endif

DWORD NMSAPI TCAPCoordReq       (CTAHD ctahd, S16 spId, U8 aSsn);
DWORD NMSAPI TCAPCoordResp      (CTAHD ctahd, S16 spId, U8 aSsn);
DWORD NMSAPI TCAPRetrieveMessage(CTAHD ctahd, U8 *pMessage, TcapRecvInfo *pInfoBlk);
DWORD NMSAPI TCAPStateReq       (CTAHD ctahd, S16 spId, U8 aSsn, U8 status);
DWORD NMSAPI TCAPTransRqst      (CTAHD ctahd, S16 spId, U8 *pMessage);
DWORD NMSAPI TCAPRetainTrans    (CTAHD ctahd, S16 spId, TcapTransInfo *pTinfo);
DWORD NMSAPI TCAPAddComp        (U8 *pMessage, TcapComp *pComp, U16 paramLen, U8 *pParamBuf);
DWORD NMSAPI TCAPGetComp        (U8 *pMessage, U8 index, TcapComp *pComp, U16 *pParamLen, U8 *pParamBuf);
DWORD NMSAPI TCAPInitTrans      (U8 *pMessage, TcapTransInfo *pTinfo, TcapDlgSect *pDlgPart, U16 userInfoLen, U8 *pUserInfo);

#ifdef __cplusplus
}
#endif

#endif /* _TCAPDEF_H_ */
