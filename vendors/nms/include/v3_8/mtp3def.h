/*************************************************************************
**                                                                      **
**                         PROPRIETARY NOTICE                           **
**                                                                      **
**                         Copyright (c) 1997                           **
**                       by Natural MicroSystems                        **
**                                                                      **
**  The following is licensed program material and is considered        **
**  proprietary and confidential.  No part of this program may be       **
**  reproduced or used in any form or by any means without the express  **
**  written permission of Natural MicroSystems                          **
**                                                                      **
*************************************************************************/
#ifndef _MTP3DEF_H_
#define _MTP3DEF_H_

/**************************************************************************
             SS7 MTP Layer 3 Interface Specification

          File mtp3api.h : Definitions & Function Prototypes
**************************************************************************/

#include "nmstypes.h"
#include "ctadef.h"

#ifdef UNIX
#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif
#endif

/* define the calling conventions for the API functions for various
 * operating systems - NOTE: API callers should never define the
 * preprocessor constant "_TX_MTP3_SOURCE_"; this is only for use
 * by the MTP3 API source code itself.
 */

/* OS2: MTP3 API is a DLL */
#ifdef __OS2__
#ifdef _TX_MTP3_SOURCE_
	/* MTP3 API source definition */
#define     TXMTP3FUNC               extern _export _syscall
#else
	/* MTP3 API caller's definition */
#define     TXMTP3FUNC               _syscall
#endif	/* _TX_MTP3_SOURCE_ */

/* WIN32: MTP3 API is a DLL */
#elif  WIN32	                        /* WIN32 */
#ifdef _TX_MTP3_SOURCE_
	/* MTP3 API source definition */
#define     TXMTP3FUNC               __declspec( dllexport ) WINAPI
#else
	/* MTP3 API caller's definition */
#define     TXMTP3FUNC               WINAPI
#endif	/* _TX_MTP3_SOURCE_ */

/* all others: statically linked library */
#else
#define     TXMTP3FUNC
#endif

/* Miscellaneous values */
#define     MAXDATA         272     /* Max length of data to transmit */
#define     MTP3_PRESERVE   40

/* Values for Msg Indications */
#define MTP3_BIND_REQ       0x04
#define MTP3_BIND_CFM       0x05
#define MTP3_DATA_REQ       0x18
#define MTP3_FLOW_REQ       0x28
#define MTP3_XSTAT_REQ      0x38
#define MTP3_DATA_IND       0x1A
#define MTP3_XSTAT_IND      0x3A
#define MTP3_STAT_IND       0x7A

/* Values for the status field:                                     */
#define StatPaused              1    /* Paused                      */
#define StatResumed             2    /* Resumed                     */
#define StatCongested           3    /* Network Congestion          */
#define StatUsrUnavail          4    /* Remote User Unavailable     */
#define StatRestart             5    /* Restart Begins              */
#define StatRestartEnds         6    /* Restart Ends                */
#define StatCongestionEnds      7    /* Network Congestion Ends     */
#define StatPrimary             8    /* Now primary                 */
#define StatBackup              9    /* Now backup                  */
#define StatStandAlone         10    /* Now standalone              */
#define StatFlcStart           11    /* Flow control start          */
#define StatFlcEnd             12    /* Flow control end            */

/* Values for the extended status field:                            */
#define XStatLinkUp             1    /* Link up                     */
#define XStatLinkDown           2    /* Link down                   */
#define XStatLinkInhDen         3    /* Link inhibited and denied   */
#define XStatLinkInh            4    /* Link inhibited              */
#define XStatLinkUninh          5    /* Link uninhibited            */
#define XStatLinkUninhDen       6    /* Link uninhibited and denied */
#define XStatLinkRemBlock       7    /* Link remotely blocked       */
#define XStatLinkRemUnblock     8    /* Link remotely unblocked     */
#define XStatLinkLocBlock       9    /* Link locally blocked        */
#define XStatLinkLocUnblock    10    /* Link locally unblocked      */

/***** MTP3 structure definitions *****/

#ifdef __sun
#pragma pack(1)
#endif

typedef struct bind_req_s {
  U8      code;          /* bind request packet type 0x04           */
  U8      srvInfo;       /* value for the Service Information Octet */
  S16     sapId;         /* SAP identifier                          */
  S16     suId;          /* Service user identifier                 */
  U16     spare2;        /* Alignment                               */
} BIND_REQ;

typedef struct bind_cfm_s {
  U8      code;          /* bind request packet type 0x04           */
  U8      spare1;        /* Alignment                               */
  S16     suId;          /* SAP identifier                          */
  S16     spId;          /* Service user identifier                 */
  U16     spare2;        /* Alignment                               */
} BIND_CFM;

typedef struct data_req_s {
  U8      code;          /* data request packet type 0x18           */
  U8      spare1;        /* Alignment                               */
  S16     sapId;         /* SAP identifier                          */
  U32     opc;           /* the originating point code              */
  U32     dpc;           /* the destination point code              */
  U8      srvInfo;       /* value for the Service Information Octet */
  U8      lnkSel;        /* Signaling Link Selection field          */
  U8      priority;      /* Message priority                        */
  U8      spare2;        /* Alignment                               */
  U8      data[MAXDATA]; /* the data to be transmitted              */
} DATA_REQ;

typedef struct flow_req_s {
  U8      code;          /* flow control request packet type 0x28   */
  U8      spare1;        /* Alignment                               */
  S16     sapId;         /* SAP identifier                          */
  S16     action;        /* enable or disable flow control          */
  U16     spare2;        /* Alignment                               */
} FLOW_REQ;

typedef struct xstat_req_s {
  U8      code;          /* status indication packet type 0x38      */
  U8      on;            /* extended status indication flag (on/off)*/
  S16     sapId;         /* SAP identifier                          */
} XSTAT_REQ;

typedef struct data_ind_s {
  U8      code;          /* data indication packet type 0x1A        */
  U8      spare1;        /* Alignment                               */
  S16     sapId;         /* SAP identifier                          */
  U32     opc;           /* the originating point code              */
  U32     dpc;           /* the destination point code              */
  U8      srvInfo;       /* the Service Information Octet           */
  U8      lnkSel;        /* the Signaling Link Selector field       */

  U16     spare2;        /* Alignment                               */
  U8      data[MAXDATA]; /* the data received                       */
} DATA_IND;

#define     DATA_IND_HDR_SIZE   12      /* Don't count spares because they're not packed.  Don't count code either. */

typedef struct stat_ind_s {
  U8      code;          /* status indication packet type 0x7A      */
  U8      spare1;        /* Alignment                               */
  S16     sapId;         /* SAP identifier                          */
  U32     pc;            /* the Point Code this status is about     */
  S16     status;        /* status indicator value                  */
  U8      priority;      /* priority of the indication              */
  U8      spare2;        /* Alignment                               */
} STAT_IND;

typedef struct xstat_ind_s {
  U8      code;          /* status indication packet type 0x3A      */
  U8      spare1;        /* Alignment                               */
  S16     sapId;         /* SAP identifier                          */
  U16     status;        /* Extended status type                    */
  U16     link;          /* MTP3 link number                        */
  U16     spare2;        /* Spare for future use                    */
  U16     spare3;        /* Spare for future use                    */
} XSTAT_IND;

/****************************************************************************/
/* MTP3 API Statistics returned by MTP3GetApiStats()                        */
/****************************************************************************/
typedef struct
{
    U32 qCount;             /* number of API messages currently queued to MTP3 layer */
    U32 qPeak;              /* max number of API messages ever queued to MTP3 layer */
    U32 txPending;          /* current number of outstanding transmit rqsts to MTP3 layer */
    U32 txPendPeak;         /* max number of transmit rqsts ever outstanding to MTP3 layer */
    U32 txSuccess;          /* number of successful transmit requests completed */
    U32 txFailed;           /* number of failed transmit requests */
    U32 txLastErr;          /* error code from last failed transmit request */
    U32 rxSuccess;          /* number of events received from MTP3 layer */
    U32 rxFailed;           /* number of receive failure events from MTP3 layer */
    U8  apiQCongLvl;        /* current outbound queue congestion level [0..3] */
    U8  spare1;             /* spare for alignment */
    U16 spare2;             /* spare for alignment */
} MTP3APISTATS;

/* Bind flag states */
#define MTP3_BIND_FLAG_OFF  0
#define MTP3_BIND_FLAG_ON   1

#ifdef __sun
#pragma pack()
#endif

/*-----------------------------------------------------------------------------
  MTP3 Version Ids
    - These id's are used to identify the revision level of this service.
  ---------------------------------------------------------------------------*/
#define MTP3_MAJORREV                        1
#define MTP3_MINORREV                        0

/*-----------------------------------------------------------------------------
  MTP3 API Compatibility Level Id
    - This id is used to determine runtime compatibility between the
      installed MTP3 service and clients of the MTP3 service. Clients can
      be a CT Access application which accesses MTP3 functionality
      via the MTP3 API.
    - Clients(CT Access application) #include this file into their code and,
      therefore, insert "hard coded" values for each MTP3 compat level
      into their client code.
    - The API_COMPATLEVEL is used by CT Access application developers who
      want to check the "hard coded" value in their application against the
      "hard coded" value in the installed MTP3 service (as determined
      via ctaGetServiceVersion() will be available in CT Access Version 2.1).
    - API compatibility level value should be incremented when the associated
      source module changes in a non-backwards compatible way. Refer to the CT
      Access Service Writer's Manual for more info.
  ---------------------------------------------------------------------------*/
#define MTP3API_COMPATLEVEL                  1

/****************************************************************************/
/* important constants and common data structures                           */
/****************************************************************************/

/* Event generated by MTP3 Service and sent back to client for all strings  */
#define MTP3EVN_DATA    ((MTP3_SVCID << 16) | 0x2000 | 0x01)     /* 0x212001   */
#define MTP3EVN_CONGEST ((MTP3_SVCID << 16) | 0x2000 | 0x02)     /* 0x212002   */

/* MTP3 - return code definitions */
#define MTP3_SUCCESS    SUCCESS   /* API completed successfully; the same as CT Access success  */
#define MTP3_NO_MSG     ((MTP3_SVCID << 16) | 0x01)  /*0x210001 no message waiting                */
#define MTP3_NOT_BOUND  ((MTP3_SVCID << 16) | 0x02)  /*0x210002 MTP3 primitive called before bind */
#define MTP3_OSERROR    ((MTP3_SVCID << 16) | 0x03)  /*0x210003 OS-specific error                 */
#define MTP3_INVBOARD   ((MTP3_SVCID << 16) | 0x04)  /*0x210004 Board number invalid              */
#define MTP3_RESOURCE   ((MTP3_SVCID << 16) | 0x05)  /*0x210005 Out of resources                  */

/*-----------------------------------------------------------------------------
  MTP3 Reason Codes.
    - These codes are constructed using the MTP3_SVCID, the CT Access
      CTA_CODE_REASON id, and a 1-based sequence number. The formula is
        REASONCODE = ((MTP3_SVCID<<16) | (CTA_CODE_REASON | SEQUENCE))
  ---------------------------------------------------------------------------*/

#define MTP3_REASON_UNKNOWN      ((MTP3_SVCID << 16) | 0x1000 | 0xff)     /* 0x2110FF unknown reason */




#ifdef __cplusplus
extern "C" {
#endif


DWORD NMSAPI MTP3SendData       (CTAHD ctahd, S16 sapId, U32 opc, U32 dpc, U8 lnkSel, U8 priority,
                                   U8 *data, S16 length, U8 srvInfo );                                  /* Send data to a remote node */
DWORD NMSAPI MTP3Flow           (CTAHD ctahd, S16 sapId, S16 action );                                  /* Flow control the service access point */
DWORD NMSAPI MTP3RegXStaReq     (CTAHD ctahd, S16 sapId );                                              /* Register/Deregister for extended status indications */
DWORD NMSAPI MTP3DeregXStaReq   (CTAHD ctahd, S16 sapId );
DWORD NMSAPI MTP3RetrieveMessage(CTAHD ctahd, void *pMsgInd, U16 *Length);                              /* wait for a message to come in */
DWORD NMSAPI MTP3GetApiStats    (CTAHD ctahd, MTP3APISTATS *pStats, U8 reset);

#ifdef __cplusplus
}
#endif

#endif  /* _MTP3API_H_ */
