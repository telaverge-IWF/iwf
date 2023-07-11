/*****************************************************************************
  NAME:  hmidef.h

  PURPOSE:

      This file contains macros and function prototypes that define the API
      for the HMI sample service.

      This API allows a CT Access application to ACT as a "tick client".
      A tick client requests a specific number of "tick" strings to be
      delivered from the "Tick Server" at a specified frequency.

      The HMI sample service, however, operates on behalf of the CT Access
      application as the "real" tick client. Once "tick" strings are received
      by the HMI Service, a CT Access event is generated and dispatched to
      the CT Access client.


  Copyright (c)1997,1998 Natural MicroSystems Corporation. All rights reserved.
  ****************************************************************************/

#ifndef HMDEF_INCLUDED
#define HMDEF_INCLUDED

/*#include "ss7type.h"*/

/* Prevent C++ name mangling. */
#ifdef __cplusplus
extern "C"
{
#endif

#ifdef UNIX
#pragma pack(1)
#endif

/*-----------------------------------------------------------------------------
  HM Service ID.
    - These id's are allocated by NMS Developer Support.
    - Do not reuse an existing Service ID as processing conflicts will occur!
    - Shown here for clarity, really defined in the tikparm.h file that is
      generated from the tikparm.pf file via pf2src.
  ---------------------------------------------------------------------------*/
/* #define HMI_SVCID                         0x2C */



/*-----------------------------------------------------------------------------
  HM Version Ids
    - These id's are used to identify the revision level of this service.
  ---------------------------------------------------------------------------*/
#define HMI_MAJORREV                        1
#define HMI_MINORREV                        0



/*-----------------------------------------------------------------------------
  HM API Compatibility Level Id
    - This id is used to determine runtime compatibility between the
      installed HMI service and clients of the HMI service. Clients can
      be a CT Access application which accesses HMI functionality
      via the HMI API.
    - Clients(CT Access application) #include this file into their code and,
      therefore, insert "hard coded" values for each HMI compat level
      into their client code.
    - The API_COMPATLEVEL is used by CT Access application developers who
      want to check the "hard coded" value in their application against the
      "hard coded" value in the installed HMI service (as determined
      via ctaGetServiceVersion() will be available in CT Access Version 2.1).
    - API compatibility level value should be incremented when the associated
      source module changes in a non-backwards compatible way. Refer to the CT
      Access Service Writer's Manual for more info.
  ---------------------------------------------------------------------------*/
#define HMIAPI_COMPATLEVEL                  1


/*-----------------------------------------------------------------------------
  HMI Event Codes.
    - These codes are constructed using the HMI_SVCID, the  CT Access
      CTA_CODE_EVENT id, and a 1-based sequence number. The formula is
        EVENTCODE = ((HMI_SVCID<<16) | (CTA_CODE_EVENT | SEQUENCE))
    - If an event declaration is a done event 0x100 must also be ORed into
      event code.
        EVENTCODE = ((HMI_SVCID<<16) | (CTA_CODE_EVENT | 0x100 | SEQUENCE)
    - The actual event codes are "hardcoded" for source browsing purposes.
  ---------------------------------------------------------------------------*/

/* Event generated by HM Service and sent back to client for all
 * tick strings
 */
#define HMI_EVN_CONNECTED           0x2C2001
#define HMI_EVN_ISOLATED            0x2C2002
#define HMI_EVN_NOWPRIMARY          0x2C2003
#define HMI_EVN_NOWBACKUP           0x2C2004
#define HMI_EVN_TASKDEAD            0x2C2005
#define HMI_EVN_BRDDEAD             0x2C2006
#define HMI_EVN_HALTED              0x2C2007
#define HMI_EVN_STARTING            0x2C2008
#define HMI_EVN_CONFLICT            0x2C2009
#define HMI_EVN_NOWSTANDALONE       0x2C200a
#define HMI_EVN_LOADING             0x2C200b
#define HMI_EVN_SERVICE_DOWN        0x2C200c
#define HMI_EVN_NO_BOARD            0x2C200d
#define HMI_EVN_INSERT              0x2C200e
#define HMI_EVN_EXTRACT             0x2C200f
#define HMI_EVN_STOP                0x2C2010
#define HMI_EVN_EXTRACT_READY       0x2C2011
#define HMI_EVN_START               0x2C2012

#define HMI_ERR_CLOSED      0x2C4000
#define HMI_ERR_BADCMD      0x2C4001
#define HMI_ERR_TIMEOUT     0x2C4002
#define HMI_ERR_INTERROR    0x2C4003
#define HMI_ERR_INVHANDLE   0x2C4004
#define HMI_ERR_REFUSED     0x2C4005
#define HMI_ERR_NOMEM       0x2C4006


#define HMI_RCV_EVENTS   'E'
#define HMI_DO_COMMANDS  'C'

#define HMI_EVENTS_ALL_BOARDS      0xff

/**/
/*-----------------------------------------------------------------------------
  Exported API Data Structures
    - Note that the HMI "parameter" structure (HMI_START_PARMS) is not defined
      here. Rather, this structure appears in HMIparm.h which is
      automatically generated by pf2src.
  ---------------------------------------------------------------------------*/
/* Status of open service. */
typedef struct
{
    U32 size;                         /* For compatibility.          */
    U32 calls;                        /* Successful API calls made.  */
} HMI_CHANNEL_INFO;

typedef struct hmLnkStats
{
    U32         txHB;                   /* number of link heartbeat messages transmitted */
    U32         rxHB;                   /* number of link heartbeat messages received */
    U8          linkState;
    U8          fill[3];
} HmLnkStats;

/* link state defines */
#define HMLS_CONNECTED      0x01
#define HMLS_ISOLATED       0x02
#define HMLS_STANDALONE     0x03

/* board state defines */
#define HMBS_EXTRACTED      0x01
#define HMBS_INSERTED       0x02

typedef struct hmTskStats
{
    U32         txLnkStInd;             /* number of link state change indications transmitted */
    U32         txRunStInd;             /* number of task state change indications transmitted */
    U32         rxHB;                   /* number of link heartbeat messages received */
    U8          runState;
    U8          rxSeq;
    U8          txSeq;
    U8          remRunState;
    U8          name[8];
} HmTskStats;

/* run state defines */
#define HMRS_UNKNOWN        0x0a
#define HMRS_STARTED        0x01
#define HMRS_BACKUP         0x02
#define HMRS_PRIMARY        0x03
#define HMRS_STANDALONE     0x04
#define HMRS_SHUTDOWN       0x05
#define HMRS_FAILED         0x06

#define HM_MAXTASKS     32

typedef struct hmStatsData
{
    HmLnkStats  linkStats;
    U8          numTsks;
    U8          fill[3];
    HmTskStats  taskStats[HM_MAXTASKS];
} HmStatsData;

#ifdef UNIX
#pragma pack()
#endif


#ifdef __cplusplus
}
#endif


#endif /* HMIDEF_INCLUDED */
