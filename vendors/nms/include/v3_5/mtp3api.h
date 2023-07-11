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
#ifndef _MTP3API_H_
#define _MTP3API_H_

/**************************************************************************
             SS7 MTP Layer 3 Interface Specification

          File mtp3api.h : Definitions & Function Prototypes
**************************************************************************/

#include "ss7type.h"

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

/* MTP3 API error codes */
#define MTP3_SUCCESS            0    /* request successful */
#define MTP3_NO_MSG             1    /* no message waiting */
#define MTP3_NOT_BOUND          -1   /* MTP3 primitive called before bind */
#define MTP3_OSERROR            -2   /* OS-specific error */
#define MTP3_INVBOARD           -3   /* Board number invalid */

/***** MTP3 structure definitions *****/
typedef struct boardInfo
{
    TX_HANDLE   fd;
    Bool        boardState;
    U8          dprChan;
} BoardInfo;

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

#define     DATA_IND_HDR_SIZE   13      /* Don't count spares because they're not packed */

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


#ifdef __sun
#pragma pack()
#endif

#ifdef __cplusplus
extern "C" {
#endif

OS_HSYNC TXMTP3FUNC MTP3SyncObj( U8 board, S16 *errval );

/* Establish a connection to the MTP3 process */
short TXMTP3FUNC MTP3Bind(U8 board, U8 srvInfo, S16 sapId, U8 srcEnt,
                          U8 srcInst, S16 suId);

/* Break a connection to the MTP3 process */
short TXMTP3FUNC MTP3Unbind(U8 board);

/* Send data to a remote node */
short TXMTP3FUNC MTP3SendData( U8 board, S16 sapId, U32 opc, U32 dpc,
                               U8 lnkSel, U8 priority,
                               U8 *data, S16 length, U8 srvInfo );

/* Flow control the service access point */
short TXMTP3FUNC MTP3Flow( U8 board, S16 sapId, S16 action );

/* Register/Deregister for extended status indications */
short TXMTP3FUNC MTP3RegXStaReq( U8 board, S16 sapId );
short TXMTP3FUNC MTP3DeregXStaReq( U8 board, S16 sapId );

/* wait for a message to come in */
short TXMTP3FUNC MTP3RetrieveMessage(U8 board, void *pMsgInd, U16 *Length);

#ifdef __cplusplus
}
#endif

#endif  /* _MTP3API_H_ */
