/*****************************************************************************
 * NAME:  sccpapi.h
 * PURPOSE:
 *     This file contains macros and function prototypes that define the API
 *     for the SCCP service.
 *
 * Copyright (c)1997-2000 Natural MicroSystems Corporation. All rights reserved.
 *****************************************************************************/
#ifndef _SCCPAPI_H_
#define _SCCPAPI_H_
/*****************************************************************************/

#include "nmstypes.h"
#include "ctadef.h"
#include "ss7type.h"

/* Prevent C++ name mangling. */
#ifdef __cplusplus
extern "C"
{
#endif


/*-----------------------------------------------------------------------------
  SCCP Service ID.
    - These id's are allocated by NMS Developer Support.
    - Do not reuse an existing Service ID as processing conflicts will occur!
    - Shown here for clarity, really defined in the sccpparm.h file that is
      generated from the sccpparm.pf file via pf2src.
  ---------------------------------------------------------------------------*/
#define SCCP_SVCID                         0x26

/*-----------------------------------------------------------------------------
  SCCP Version Ids
    - These id's are used to identify the revision level of this service.
  ---------------------------------------------------------------------------*/
#define SCCP_MAJORREV                        1
#define SCCP_MINORREV                        0

/*-----------------------------------------------------------------------------
  SCCP API Compatibility Level Id
    - This id is used to determine runtime compatibility between the
      installed SCCP service and clients of the SCCP service. Clients can
      be a CT Access application which accesses SCCP functionality
      via the SCCP API.
    - Clients(CT Access application) #include this file into their code and,
      therefore, insert "hard coded" values for each SCCP compat level
      into their client code.
    - The API_COMPATLEVEL is used by CT Access application developers who
      want to check the "hard coded" value in their application against the
      "hard coded" value in the installed SCCP service (as determined
      via ctaGetServiceVersion() will be available in CT Access Version 2.1).
    - API compatibility level value should be incremented when the associated
      source module changes in a non-backwards compatible way. Refer to the CT
      Access Service Writer's Manual for more info.
  ---------------------------------------------------------------------------*/
#define SCCPAPI_COMPATLEVEL                  1

/*-----------------------------------------------------------------------------
 *  Event generated by SCCP Service and sent back to client.
 *
 *  CTA_CODE_EVENT = 0x2000
 *
 * Base value for reason codes ==
 *   (SCCP_SVCID << 16) | CTA_CODE_EVENT | <number> == 0x262000
 *-----------------------------------------------------------------------------*/
#define SCCPEVN_DATA        0x262001
#define SCCPEVN_CONGEST     0x262002

/* --------------------------------------------------------------------------
 * Return Status Values for SCCP API / SCCP Management API:
 *
 * CTA_CODE_ERROR = 0x0000
 *
 * Base value for reason codes ==
 *   (SCCP_SVCID << 16) | CTA_CODE_ERROR | <number> == 0x260000
 * -------------------------------------------------------------------------- */
#ifndef SCCP_SUCCESS
#define SCCP_SUCCESS        SUCCESS         /* API completed successfully; same as CT Access success */
#endif

#define SCCPERR_OVERRUN       0x260001      /* Data length too large to send            */
#define SCCPERR_UNDERRUN      0x260002      /* Received message too large               */
#define SCCPERR_UNBOUND       0x260003      /* Not bound to specified board             */
#define SCCPERR_BOARD         0x260004      /* Board number out of range                */
#define SCCPERR_DRIVER        0x260005      /* CPI driver reported an error             */
#define SCCPERR_NOMSG         0x260006      /* No event messages waiting                */
#define SCCPERR_NOTBOUND      0x260007      /* User failed to call SCCPBindTqst() first */
#define SCCPERR_RESOURCES     0x260008      /* Couldn't allocate msg buffer             */
#define SCCPERR_UNINIT        0x260009      /* User failed to call SccpMgmtInit() first */
#define SCCPERR_TOOMANY       0x26000A      /* Too many handles open for specified board*/
#define SCCPERR_INSTANCE      0x26000B      /* Instance ID out of range                 */
#define SCCPERR_TIMEOUT       0x26000C      /* No response from board                   */
#define SCCPERR_SWTYPE        0x26000D      /* Invalid switch type (i.e., protocol)     */
#define SCCPERR_PARAM         0x26000E      /* Invalid parameter                        */
#define SCCPERR_NOGENCFG      0x26000F      /* Board has not received SccpGenCfg yet    */
#define SCCPERR_NOTFOUND      0x260010      /* Specified address or route not found     */
#define SCCPERR_EXCEEDMAXCFG  0x260011      /* Insufficient resources allocated in gen  */
                                            /*   cfg for a USAP, NSAP, ROUTE or ADDRESS */
#define SCCPERR_INTERNAL      0x260012      /* An internal error occured.               */
#define SCCPERR_BUFLEN        0x260013      /* Address/mask too long to fit in buffer   */
                                            /*   or numConPc > conPcList array size     */
                                            /*   or numSsns > ssnList array size.       */
#define SCCPERR_BADDIGIT      0x260014      /* Address/mask contains an invalid digit   */
#define SCCPERR_MAXROUTES     0x260015      /* SccpGenCfg maxRtes is out of range       */
#define SCCPERR_NULLPTR       0x260016      /* A null pointer was passed as a parameter */
#define SCCPERR_TIMERVALUE    0x260017      /* An enabled timer has a value of 0        */
#define SCCPERR_HOPCOUNT      0x260018      /* Invalid hop count                        */
#define SCCPERR_POINTCODE     0x260019      /* Invalid point code                       */
#define SCCPERR_RANGE         0x26001A      /* An input field is out of range           */

/*-----------------------------------------------------------------------------
 * Reason codes generated by SCCP ctaOpenServices asynchronous completion
 * event; these codes indicate an unsuccessful bind attempt (a successful
 * bind is denoted by a reason of CTA_REASON_FINISHED)
 *
 * Base value for reason codes ==
 *   (SCCP_SVCID << 16) | CTA_CODE_REASON | <number> == 0x261000
 *-----------------------------------------------------------------------------*/
#define SCCP_REASON_SPID_RANGE  0x261001        /* requested SPID out of range */
#define SCCP_REASON_SPID_UNDEF  0x261002        /* requested SPID not configured */
#define SCCP_REASON_NO_NSAP     0x261003        /* NSAP not configured/bound for user's switch type */
#define SCCP_REASON_UNKNOWN     0x2610FF        /* unknown reason */


/* --------------------------------------------------------------------------
 * SCCPRetrieveMsg Indication types:
 * -------------------------------------------------------------------------- */
#define SCCPUDATIND         0xB1        /* Unitdata indication              */
#define SCCPSTAIND          0xB2        /* Unsolicited status indication    */
#define SCCPCOORDIND        0xB3        /* Coordinated OOS indication       */
#define SCCPCOORDCFM        0xB4        /* Coordinated OOS confirm          */
#define SCCPSTATEIND        0xB5        /* Subsystem state indication       */
#define SCCPPCSTIND         0xB6        /* Point code state indication      */
#define SCCPCONNIND         0xB7        /* Connect indication               */
#define SCCPCONNCFM         0xB8        /* Connect confirm                  */
#define SCCPDATIND          0xB9        /* Data (DT1 or DT2) indication     */
#define SCCPEDATIND         0xBA        /* Expedited data indication        */
#define SCCPRESETIND        0xBB        /* Connection reset indication      */
#define SCCPRESETCFM        0xBC        /* Connection reset confirm         */
#define SCCPDACKIND         0xBD        /* Data acknowledge indication      */
#define SCCPRELIND          0xBE        /* Connection release indication    */
#define SCCPCONNAUDCFM      0xBF        /* Connection audit confirm         */
#define SCCPINACTIND        0xE0        /* Connection inactivity indication */
#define SCCPRUNSTATEIND     0xEF        /* Run state indication             */
#define SCCPCONGIND         0xED        /* Congestion Indication            */

/* --------------------------------------------------------------------------
 * Event types for SCCPSTAIND indications (SccpRcvInfoBlk.evntType)
 * -------------------------------------------------------------------------*/
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

/* --------------------------------------------------------------------------
 * Event types for SCCPRUNSTATEIND indications (SccpRcvInfoBlk.evntType)
 * -------------------------------------------------------------------------*/
#define SPRS_BACKUP         0x30        /* sending SCCP now in backup mode  */
#define SPRS_PRIMARY        0x31        /* sending SCCP now in primary mode */
#define SPRS_STANDALONE     0x32        /* sending SCCP not redundant       */

/* --------------------------------------------------------------------------
 * Event types for SCCPCONNAUDCFM indications (SccpRcvInfoBlk.evntType)
 * -------------------------------------------------------------------------*/
#define SCCP_CONNAUDOK      0           /* OK, connection info returned     */
#define SCCP_CONNAUDEOF     8           /* No more connections to audit     */

/* --------------------------------------------------------------------------
 * SCCP Service API function prototypes:
 * -------------------------------------------------------------------------- */
DWORD NMSAPI SCCPConnectRqst( CTAHD ctahd, SccpConnId *connId, SccpConnRqst *connRqst );
DWORD NMSAPI SCCPConnectResp( CTAHD ctahd, SccpConnId *connId, SccpConnRqst *connRqst );
DWORD NMSAPI SCCPCoordRqst( CTAHD ctahd, S16 spId, SccpCoordRqst *coordRqst );
DWORD NMSAPI SCCPCoordResp( CTAHD ctahd, S16 spId, SccpCoordRqst *coordRqst );
DWORD NMSAPI SCCPDAckRqst( CTAHD ctahd, SccpConnId *connId, SccpDAckRqst *dackRqst );
DWORD NMSAPI SCCPDataRqst( CTAHD ctahd, SccpConnId *connId, SccpDataRqst *dataRqst );
DWORD NMSAPI SCCPEDataRqst( CTAHD ctahd, SccpConnId *connId, SccpDataRqst *dataRqst );
DWORD NMSAPI SCCPReleaseRqst( CTAHD ctahd, SccpConnId *connId, SccpReleased *relRqst );
DWORD NMSAPI SCCPResetRqst( CTAHD ctahd, SccpConnId *connId, SccpResetRqst *resetRqst );
DWORD NMSAPI SCCPResetResp( CTAHD ctahd, SccpConnId *connId );
DWORD NMSAPI SCCPRetrieveMessage( CTAHD ctahd, SccpAllMsgs *message, SccpRcvInfoBlk *infoBlk, Bool wait );
DWORD NMSAPI SCCPUDataRqst( CTAHD ctahd, S16 spId, SccpUdataRqst *dataRqst );
DWORD NMSAPI SCCPStateRqst( CTAHD ctahd, S16 spId, U8 aSsn, U8 status );
DWORD NMSAPI SCCPInactResp( CTAHD ctahd, SccpConnId *connId );
DWORD NMSAPI SCCPConnAuditRqst( CTAHD ctahd, SccpConnId *connId );
DWORD NMSAPI SCCPGetStats( CTAHD ctahd, SccpStats *stats, U8 bReset );

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
}
#endif

/*****************************************************************************/
#endif /* _SCCPAPI_H_ */

