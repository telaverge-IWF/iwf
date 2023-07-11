/*****************************************************************************
*                                  DTMDEF.H
*
*  This is the include file for the Monitor (DTM) API.
*
*
* Copyright (c) 1997 Natural MicroSystems Corporation. All rights reserved.
*****************************************************************************/

#ifndef DTMDEF_INCLUDED
#define DTMDEF_INCLUDED 1

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NMSTYPES_INCLUDED
  #include "nmstypes.h"
#endif

#ifndef CTADEF_INCLUDED
  #include "ctadef.h"
#endif


/*-----------------------------------------------------------------------------
  DTM Version Ids
    - These id's are used to identify the revision level of this service.
  ---------------------------------------------------------------------------*/
#define DTM_MAJORREV                        1
#define DTM_MINORREV                        0



/*-----------------------------------------------------------------------------
  DTM API Compatibility Level Id
    - This id is used to determine runtime compatibility between the
      installed DTM service and clients of the DTM service. Clients can
      be a CT Access application which accesses DTM functionality
      via the DTM API.
    - Clients(CT Access application) #include this file into their code and,
      therefore, insert "hard coded" values for each DTM compat level
      into their client code.
    - The API_COMPATLEVEL is used by CT Access application developers who
      want to check the "hard coded" value in their application against the
      "hard coded" value in the installed DTM service (as determined
      via ctaGetServiceVersion() will be available in CT Access Version 2.1).
    - API compatibility level value should be incremented when the associated
      source module changes in a non-backwards compatible way. Refer to the CT
      Access Service Writer's Manual for more info.
  ---------------------------------------------------------------------------*/
#define DTMAPI_COMPATLEVEL                  0


/*====== COMMON DEFINES AND STRUCTURES =====================================*/

#define DTM_SVCID 0xc

typedef DWORD DTMHD ;


/*====== TRUNK STATUS STRUCTURE ============================================*/

typedef struct {
    BYTE alarms ;
        #define DTM_ALARM_FAR_END      1   /* yellow */
        #define DTM_ALARM_AIS          2   /* blue   */
        #define DTM_ALARM_LOF          4   /* red    */
        #define DTM_ALARM_FAR_LOMF     8   /* far end loss of MF (E1 CAS)  */
        #define DTM_ALARM_TS16AIS   0x10   /* All 1's in slot 16 (E1)      */

    BYTE sync ;
        #define DTM_SYNC_NO_SIGNAL     1
        #define DTM_SYNC_NO_FRAME      2
        #define DTM_SYNC_NO_MULTIFRAME 4
        #define DTM_SYNC_NO_CRC_MF     8  /* No CRC multi-frame sync (E1 only)*/

    BYTE alarmsent ;
        #define DTM_SENDING_LOF        1  /* sent yellow */
        #define DTM_SENDING_AIS        2  /* sent blue */
        #define DTM_SENDING_LOMF       4  /* sent loss of multiframe (E1 CAS) */
        #define DTM_SENDING_TS16AIS    8  /* sent all 1's in slot 16 (E1)     */

    BYTE  spare ;
} DTM_TRUNK_STATE ;


typedef struct
{
    DWORD size ;                       /* size of this structure      */
    DWORD board ;                      /* board number                */
    DWORD trunk ;                      /* trunk number                */
    DTM_TRUNK_STATE state ;            /* alarms and sync status      */
    DWORD starttime;                   /* when counts started (time_t)*/
    DWORD slips;                       /* slips accumulator           */
    DWORD lineerrors;                  /* line code violations (BPVs) */
    DWORD frameerrors;                 /* frame bit errors+ CRC errors*/
    DWORD es;                          /* errored seconds accumulator */
    DWORD ses;                         /* severely errored seconds    */
    DWORD uas;                         /* unavailable seconds         */
} DTM_TRUNK_STATUS ;


#define DTM_START_PARMID 0xc0001

typedef struct
{
    DWORD size ;
    DWORD maxevents ;             /* Maximum number of events per second */
    DWORD reportmask ;
} DTM_START_PARMS ;

#define  DTM_REPORT_GO_NOGO       1    /* only when going in or out of */
                                       /* alarm                        */
#define  DTM_REPORT_ALARMS        2    /* any change in received alarms*/
#define  DTM_REPORT_STATUS        4    /* any status/sync change       */
#define  DTM_REPORT_SLIPS         8    /* any slip                     */
#define  DTM_REPORT_ES            0x10 /* change in errored seconds    */
#define  DTM_REPORT_SES           0x20 /* change in severe error secs  */
#define  DTM_REPORT_UAS           0x40 /* change in failed seconds     */

#define  DTM_REPORT_REPORT_STATUS DTM_REPORT_STATUS

DWORD NMSAPI dtmStartTrunkMonitor  (CTAHD ctahd, unsigned board, unsigned trunk,
                                     DTMHD *dtmhd, DTM_START_PARMS *parms);
DWORD NMSAPI dtmStopTrunkMonitor   (DTMHD dtmhd);
DWORD NMSAPI dtmGetTrunkStatus     (DTMHD dtmhd, DTM_TRUNK_STATUS *status,
                                     unsigned size);
DWORD NMSAPI dtmRefreshTrunkStatus (DTMHD dtmhd);
DWORD NMSAPI dtmResetCounters      (DTMHD dtmhd);
DWORD NMSAPI dtmSendAlarm          (DTMHD dtmhd, unsigned alarm);


#define DTM_SEND_NO_ALARMS 0
#define DTM_SEND_AIS       1
#define DTM_SEND_LOF       2
#define DTM_SEND_TS16AIS   3


/*-----------------------------------------------------------------------------
 Monitor Service EVENTS
-----------------------------------------------------------------------------*/
#define DTMEVN_MONITOR_STARTED      0xc2001
#define DTMEVN_TRUNK_STATUS         0xc2002
 /* value = DTM_TRUNK_STATE structure (4 bytes) */
 /* size: dtmhd */

#define DTMEVN_MONITOR_DONE         0xc2101


#ifdef __cplusplus
}
#endif
#endif /* ifndef DTMDEF_INCLUDED  */

