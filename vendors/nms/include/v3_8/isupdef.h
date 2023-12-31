/*****************************************************************************
  NAME:  isupdef.h

  PURPOSE:

      This file contains macros and function prototypes that define the API
      for the TIK sample service.

      This API allows a CT Access application to ACT as a "tick client".
      A tick client requests a specific number of "tick" strings to be
      delivered from the "Tick Server" at a specified frequency.

      The TIK sample service, however, operates on behalf of the CT Access
      application as the "real" tick client. Once "tick" strings are received
      by the TIK Service, a CT Access event is generated and dispatched to
      the CT Access client.


  Copyright (c)1997,1998 Natural MicroSystems Corporation. All rights reserved.
  ****************************************************************************/

#ifndef ISUPDEF_INCLUDED
#define ISUPDEF_INCLUDED


#include "nmstypes.h"
#include "ctadef.h"
#pragma pack(1)
#include "isuptype.h"
#include "isupmsgs.h"
#pragma pack()

/* Prevent C++ name mangling. */
#ifdef __cplusplus
extern "C"
{
#endif

/*-----------------------------------------------------------------------------
  ISUP Service ID.
    - These id's are allocated by NMS Developer Support.
    - Do not reuse an existing Service ID as processing conflicts will occur!
    - Shown here for clarity, really defined in the tikparm.h file that is
      generated from the tikparm.pf file via pf2src.
  ---------------------------------------------------------------------------*/
/*#define ISUP_SVCID                         0x24*/



/*-----------------------------------------------------------------------------
  TIK Version Ids
    - These id's are used to identify the revision level of this service.
  ---------------------------------------------------------------------------*/
#define ISUP_MAJORREV                        1
#define ISUP_MINORREV                        0



/*-----------------------------------------------------------------------------
  TIK API Compatibility Level Id
    - This id is used to determine runtime compatibility between the
      installed TIK service and clients of the TIK service. Clients can
      be a CT Access application which accesses TIK functionality
      via the TIK API.
    - Clients(CT Access application) #include this file into their code and,
      therefore, insert "hard coded" values for each TIK compat level
      into their client code.
    - The API_COMPATLEVEL is used by CT Access application developers who
      want to check the "hard coded" value in their application against the
      "hard coded" value in the installed TIK service (as determined
      via ctaGetServiceVersion() will be available in CT Access Version 2.1).
    - API compatibility level value should be incremented when the associated
      source module changes in a non-backwards compatible way. Refer to the CT
      Access Service Writer's Manual for more info.
  ---------------------------------------------------------------------------*/
#define ISUPAPI_COMPATLEVEL                  1


/*-----------------------------------------------------------------------------
  TIK Event Codes.
    - These codes are constructed using the TIK_SVCID, the  CT Access
      CTA_CODE_EVENT id, and a 1-based sequence number. The formula is
        EVENTCODE = ((TIK_SVCID<<16) | (CTA_CODE_EVENT | SEQUENCE))
    - If an event declaration is a done event 0x100 must also be ORed into
      event code.
        EVENTCODE = ((TIK_SVCID<<16) | (CTA_CODE_EVENT | 0x100 | SEQUENCE)
    - The actual event codes are "hardcoded" for source browsing purposes.
    - Note that the TIK Service also generates CT Access events as well;
      therefore this is not an exhaustive list of all, TIK generated,
      event codes.
  ---------------------------------------------------------------------------*/

/* Event generated by TIK Service and sent back to client for all
 * tick strings
 */
#define ISUPEVN_DATA                 0x242001
#define ISUPEVN_CONG                 0x242002

/* return codes */

#define ISUP_SUCCESS    SUCCESS       /* same as CT Access success */
#define ISUP_NOMSG      0x240001      /* no message waiting */
#define ISUP_NOTBOUND   0x240002      /* ISUP primitive called before bind */
#define ISUP_UNKEVENT   0x240003      /* unknown event type passed to primitive */
#define ISUP_OSERROR    0x240004      /* OS-specific error */
#define ISUP_RESOURCES  0x240005      /* unable to allocate resources (buffer) */
#define ISUP_BADMSG     0x240006      /* unrecognized msg rec'd from ISUP */
#define ISUP_INVBOARD   0x240007      /* Board number invalid */


/* Indication/confirmation types for received messages */

#define EVTSITBNDREQ      0x04  /* Bind request */
#define EVTSITBNDCFM      0x08  /* Bind confirm */

#define EVTSITCONREQ      0x0C  /* Connct request */
#define EVTSITCONCFM      0x0D  /* Connct confirm */
#define EVTSITCONRSP      0x0F  /* Connect response */
#define EVTSITCONIND      0x0E  /* Connect indication */

#define EVTSITCNSTREQ     0x58  /* Connection progress status request */
#define EVTSITCNSTIND     0x5A  /* Connection progress status indication */

#define EVTSITDATREQ      0x14  /* Data request */
#define EVTSITDATIND      0x16  /* Data indication */

#define EVTSITFACREQ      0x68  /* Call facility request */
#define EVTSITFACIND      0x6A  /* Call facility indication */

#define EVTSITRELREQ      0x5C  /* Connection release request */
#define EVTSITRELRSP      0x5F  /* Connection release response */
#define EVTSITRELIND      0x5E  /* Connection release indication */
#define EVTSITRELCFM      0x5D  /* Connection release confirmation */

#define EVTSITSUSPREQ     0x38  /* Call suspend request */
#define EVTSITSUSPIND     0x3A  /* Call suspend indication */

#define EVTSITRESMREQ     0x34  /* Call resume request */
#define EVTSITRESMIND     0x36  /* Call resume indication */

#define EVTSITSTAREQ      0x78  /* Status request */
#define EVTSITSTAIND      0x7A  /* Status indication */

#define EVTSITRAWREQ      0x2C  /* Raw event request */
#define EVTSITRAWIND      0x2D  /* Raw event indication */

/* events for Connect Status Request/Indication */

#define ADDRCMPLT         0     /* address complete */
#define MODIFY            1     /* modify */
#define MODCMPLT          2     /* modify complete */
#define MODREJ            3     /* modify reject */
#define PROGRESS          4     /* progress */
#define FRWDTRSFR         5     /* forward transfer */
#define INFORMATION       6     /* information */
#define INFORMATREQ       7     /* information request */
#define SUBSADDR          8     /* subsequent address */
#define EXIT              9     /* exit */
#define NETRESMGT         10    /* network resource management  */
#define IDENTREQ          11    /* identification request  */
#define IDENTRSP          12    /* identification response  */
#define MALCLLPRNT        13    /* Malicious call print  */
#define CHARGE            14    /* Charge Info  */
#define TRFFCHGE          15    /* Tariff Change  */
#define CHARGEACK         16    /* Charge Acknowledge  */
#define CALLOFFMSG        17    /* Call Offering  */
#define SEGMENTATION      18    /* Segmentation  */

/* events for status request/indication primitives */

#define   REATTEMPT        1      /* reattemp indication */
#define   ERRORIND         2      /* error indication */
#define   CONTCHK          3      /* continuity check */
#define   CONTREP          4      /* continuity report */
#define   STPCONTIN        5      /* stop continuity */
#define   CIRGRPQRYRSP     6      /* circuit group query response */
#define   CONFUSION        7      /* confusion */
#define   LOOPBCKACK       8      /* loop-back acknowledge */
#define   CIRRESERVE       9      /* circuit reservation request */
#define   CIRRESERVEACK    0x0a   /* circuit reservation acknowledge  */
#define   CIRBLOSTOPRSC    0x0b   /* circuit block, stop retrying RSC  */
#define   CIRBLKREQ        0x14   /* circuit block request */
#define   CIRBLKRSP        0x15   /* circuit block response */
#define   CIRUNBLKREQ      0x16   /* circuit unblock request */
#define   CIRUNBLKRSP      0x17   /* circuit unblock response */
#define   CIRRESREQ        0x18   /* circuit reset request */

#define   PRERELEASE       0x19
#define   LOOPPREVENTION   0x1a
#define   APPTRANSPORT     0x1b

#define   CIRGRPBLKREQ     0x1c   /* circuit group block request */
#define   CIRGRPUNBLKREQ   0x1d   /* circuit group unblock request */
#define   CIRGRPQRYREQ     0x1e   /* circuit group query request */
#define   CIRGRPBLKRSP     0x1f   /* circuit group block response */
#define   CIRGRPUNBLKRSP   0x20   /* circuit group unblock response */
#define   CIRGRPRESREQ     0x21   /* circuit group reset request */

#define   CIRGRPSET        0x22   /* circuit group set status */
#define   CIRGRPGET        0x23   /* circuit group get status */

#define   CIRUNEQPD        0x24   /* circuit unequipped */
#define   CIRGRPRESACK     0x25   /* circuit group reset acknowledge */
#define   CIRRESREQLOC     0x26   /* reset initiated locally by the software */

#define   MTPPAUSE         0x27   /* pause received from MTP */
#define   MTPRESUME        0x28   /* resume received from MTP */

#define   RMTUSRUNAVAIL    0x29   /* remote user unavailable */
#define   RMTUSRAVAIL      0x2a   /* remote user available */
#define   MTPCONGEST       0x2b   /* congestion received from MTP */
#define   MTPSTOPCONGEST   0x2c   /* stop congestion received from MTP */

#define   MTPBACKUP        0x30   /* BACKUP received from MTP */
#define   MTPPRIMARY       0x31   /* PRIMARY received from MTP */
#define   MTPSTANDALONE    0x32   /* STANDALONE received from MTP */

#define   INVRUNSTATE      0x33   /* invalid running state */

/* events for general facility request */

#define FACILITY            0x00
#define FACILITYACC         0x01
#define FACILITYREJ         0x02
#define FACILITYINFO        0x03
#define FACILITYDEACT       0x04
#define FACILITYREQ         0x05


/* switchType values for buffer initialization functions */

#define ST_ITU      1
#define ST_ITUWHITE 1
#define ST_ANS88    2
#define ST_ANS92    3
#define ST_ITUBLUE  4
#define ST_ANS95    5
#define ST_Q767     6
#define ST_JNTT     7
#define ST_ITU97    8               /* switch - ITU 1997 */
#define ST_ETSIV2   9               /* switch - ETSI V2 */
#define ST_ETSIV3  10               /* switch - ETSI V3 */
#define ST_JTTC    11               /* switch - Japan TTC */

/****************************************************************************/
/* TCAP API Statistics returned by TCAPGetApiStats()                        */
/****************************************************************************/
typedef struct
{
    U32 qCount;             /* number of API messages currently queued to ISUP layer */
    U32 qPeak;              /* max number of API messages ever queued to ISUP layer */
    U32 txPending;          /* current number of outstanding transmit rqsts to ISUP layer */
    U32 txPendPeak;         /* max number of transmit rqsts ever outstanding to ISUP layer */
    U32 txSuccess;          /* number of successful transmit requests completed */
    U32 txFailed;           /* number of failed transmit requests */
    U32 txLastErr;          /* error code from last failed transmit request */
    U32 rxSuccess;          /* number of events received from ISUP layer */
    U8  apiQCongLvl;        /* current outbound queue congestion level [0..3] */
    U8  isupCongLvl;        /* current ISUP layer congestion level [0..3] */
    U8  isupCongSrc;        /* reason for ISUP layer congestion */
    U8  spare1;             /* spare for alignment */
} ISUPAPISTATS;

/* ISUP layer congestion source values */
#define ISUP_CONG_LOWMEM    1           /* low memory in ISUP layer */
#define ISUP_CONG_QTHRESH   2           /* ISUP outbound queue threshold exceeded */
/**/
/*-----------------------------------------------------------------------------
  ISUP Service API function prototypes.
  ---------------------------------------------------------------------------*/
DWORD NMSAPI  ISUPRetrieveMessage(CTAHD ctahd, SiAllSdus *event, IsupRcvInfoBlk *infoBlk, Bool wait);

DWORD NMSAPI  ISUPConnectReq( CTAHD ctahd, SuId suId, SiInstId suInstId, SiInstId spInstId,
                      Bool cirSelFlg, CirId circuit, SiConEvnt *conEvnt);
DWORD NMSAPI  ISUPConnectResp( CTAHD ctahd, SuId suId, SiInstId suInstId, SiInstId spInstId,
                      CirId circuit, SiConEvnt *conEvnt);
DWORD NMSAPI  ISUPConnectStatusReq( CTAHD ctahd, SuId suId, SiInstId suInstId, SiInstId spInstId,
                            CirId circuit, SiCnStEvnt *conStEvnt, U8 eventType);
DWORD NMSAPI  ISUPReleaseReq( CTAHD ctahd, SuId suId, SiInstId suInstId, SiInstId spInstId,
                      CirId circuit, SiRelEvnt *relEvnt);
DWORD NMSAPI  ISUPReleaseResp( CTAHD ctahd, SuId suId, SiInstId suInstId, SiInstId spInstId,
                       CirId circuit, SiRelEvnt *relEvnt);
DWORD NMSAPI  ISUPDataReq( CTAHD ctahd, SuId suId, SiInstId suInstId, SiInstId spInstId,
                      CirId circuit, SiInfoEvnt *infoEvnt);
DWORD NMSAPI  ISUPSuspendReq( CTAHD ctahd, SuId suId, SiInstId suInstId, SiInstId spInstId,
                      CirId circuit, SiSuspEvnt *suspEvnt);
DWORD NMSAPI  ISUPResumeReq( CTAHD ctahd, SuId suId, SiInstId suInstId, SiInstId spInstId,
                     CirId circuit, SiResmEvnt *resmEvnt);
DWORD NMSAPI  ISUPStatusReq( CTAHD ctahd, SuId suId, SiInstId suInstId, SiInstId spInstId,
					 Bool globalFlg, CirId circuit, U8 eventType,
                     SiStaEvnt *statEvnt);
DWORD NMSAPI  ISUPFacilityReq( CTAHD ctahd, SuId suId, SiInstId suInstId, SiInstId spInstId,
                      CirId circuit, SiFacEvnt *facEvnt, U8 eventType);
DWORD NMSAPI  ISUPRawReq( CTAHD ctahd, SuId suId, SiInstId suInstId, SiInstId spInstId,
                      Bool cirSelFlg, CirId circuit, SiRawEvnt *rawEvnt, U8 newState);

DWORD NMSAPI  ISUPInitACM(S16 switchType, SiCnStEvnt *event);
DWORD NMSAPI  ISUPInitANM(S16 switchType, SiConEvnt *event);
DWORD NMSAPI  ISUPInitCON(S16 switchType, SiConEvnt *event);
DWORD NMSAPI  ISUPInitCOT (S16 switchType, SiStaEvnt *event, U8 contInd);
DWORD NMSAPI  ISUPInitCPG(S16 switchType, SiCnStEvnt *event);
DWORD NMSAPI  ISUPInitCRM(S16 switchType, SiStaEvnt *event);
DWORD NMSAPI  ISUPInitFAA(S16 switchType, SiFacEvnt *event);
DWORD NMSAPI  ISUPInitFAC(S16 switchType, SiFacEvnt *event);
DWORD NMSAPI  ISUPInitFAD(S16 switchType, SiFacEvnt *event);
DWORD NMSAPI  ISUPInitFAI(S16 switchType, SiFacEvnt *event);
DWORD NMSAPI  ISUPInitFAR(S16 switchType, SiFacEvnt *event);
DWORD NMSAPI  ISUPInitFRJ(S16 switchType, SiFacEvnt *event, U8 cause);
DWORD NMSAPI  ISUPInitFOT(S16 switchType, SiCnStEvnt *event);
DWORD NMSAPI  ISUPInitIAM(S16 switchType, SiConEvnt *event,
                                          U8 *cdPty, U8 cdPtyLen, U8 *cgPty, U8 cgPtyLen);
DWORD NMSAPI  ISUPInitINF(S16 switchType, SiCnStEvnt *event);
DWORD NMSAPI  ISUPInitINR(S16 switchType, SiCnStEvnt *event);
DWORD NMSAPI  ISUPInitREL(S16 switchType, SiRelEvnt *event, U8 cause);
DWORD NMSAPI  ISUPInitSAM(S16 switchType, SiCnStEvnt *event,
                                              U8 *subAddr, U8 subAddrLen);
DWORD NMSAPI  ISUPInitSUS (S16 switchType, SiSuspEvnt *event);
DWORD NMSAPI  ISUPInitRES (S16 switchType, SiResmEvnt *event);
U8 NMSAPI  ISUPASCIItoBCD( U8 *ascii, U8 *bcd, U8 length);
U8 NMSAPI  ISUPBCDtoASCII( U8 *bcd, U8 bcdLen, U8 *ascii, U8 asciiLen);

DWORD NMSAPI ISUPGetApiStats    (CTAHD ctahd, ISUPAPISTATS *pStats, U8 reset);

#ifdef __cplusplus
}
#endif


#endif /* ISUPDEF_INCLUDED */
