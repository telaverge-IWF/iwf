/******************************************************************************  
* 
* Module Name:
*
*     cdidef.h
*
* Abstract:
*
*     This file contains macros and function prototypes that define the API
*     for the CDI sample service.
*
* Author:
*
*     Ning Ji
*
* Environment:
*
*     User mode
*
* Revision History:
*
* 10/28/99  Christophe J Gerard:
*				- moving CDI_RING_PARMS and CDI_SIGNALDETECTOR_PARMS to cdiparm.pf
*
* 11/12/99  Christophe J Gerard:
*				- removing unused CDI_DATA_STRUCTURE
*				- defining LED states
*
* 11/17/99  Christophe J Gerard:
*				- removing CDIERR_NO_RESOURCES, CDIERR_INVALID_CALL_STATE, CDIERR_INVALID_OFF_HOOK_STATE and using CTA error codes
*
*  Copyright (c) 1994-2002 NMS Communications.  All rights reserved.
*
*******************************************************************************/


#ifndef CDIDEF_INCLUDED
#define CDIDEF_INCLUDED 


/* Standard CT Access include files. */
#include "nmstypes.h"
#include "ctadef.h"
#include "cdiparm.h"

/* Prevent C++ name mangling. */
#ifdef __cplusplus
extern "C"
{
#endif

/*-----------------------------------------------------------------------------
  CDI Service ID.  
    - These id's are allocated by NMS Developer Support. 
    - Do not reuse an existing Service ID as processing conflicts will occur!
    - Shown here for clarity, really defined in the cdiparm.h file that is 
      generated from the cdiparm.pf file via pf2src.
  ---------------------------------------------------------------------------*/
//#define CDI_SVCID                0x1f


/*-----------------------------------------------------------------------------
  CDI Version Ids  
    - These id's are used to identify the revision level of this service. 
  ---------------------------------------------------------------------------*/
#define CDI_MAJORREV             1
#define CDI_MINORREV             12

/* CDI Specific definations */
#define MAX_PORT_NUM			 48
// #define MAX_BOARD_NUM            32 Moved definition to cxddef.h
#define CDI_BASEID               0x001f0000L
#define MAX_LIBRARY_LEN          40
#define SUPERVISOR_CHANNEL       0x8000
#define MAX_TRACE_BUFFER         300
#define MAX_TMP_BUFFER           10

#define BOARD_MON_UNREGISTERED	 0
#define BOARD_MON_REGISTERED	 1

#ifdef CDIDBG
    #define CDIDEBUG(a)	printf a
#else
    #define CDIDEBUG(a)	
#endif

/*-----------------------------------------------------------------------------
  CDI API Compatibility Level Id
    - This id is used to determine runtime compatibility between the
      installed CDI service and clients of the CDI service. Clients can
      be a CT Access application which accesses CDI functionality
      via the CDI API.
    - Clients(CT Access application) #include this file into their code and, 
      therefore, insert "hard coded" values for each CDI compat level
      into their client code.
    - The API_COMPATLEVEL is used by CT Access application developers who
      want to check the "hard coded" value in their application against the
      "hard coded" value in the installed CDI service (as determined
      via ctaGetServiceVersion() will be available in CT Access Version 2.1).
    - API compatibility level value should be incremented when the associated
      source module changes in a non-backwards compatible way. Refer to the CT 
      Access Service Writer's Manual for more info.
  ---------------------------------------------------------------------------*/
#define CDIAPI_COMPATLEVEL                  1


/*-----------------------------------------------------------------------------
  CDI Command Codes.
    - These codes are constructed using the CDI_SVCID, the CT Access
      CTA_CODE_COMMAND id, and a 1-based sequence number. The formula is
          COMMANDCODE = ((CDI_SVCID<<16) | (CTA_CODE_COMMAND | SEQUENCE))
    - The actual command codes are "hardcoded" for source browsing purposes. 
  ---------------------------------------------------------------------------*/

#define CDICMD_START_DTMF_DETECTOR      0x1f3001	
#define CDICMD_STOP_DTMF_DETECTOR       0x1f3002
#define CDICMD_ENABLE_BATTERY           0x1f3003
#define CDICMD_DISABLE_BATTERY          0x1f3004
#define CDICMD_START_RING               0x1f3005
#define CDICMD_STOP_RING                0x1f3006
#define CDICMD_START_TONES              0x1f3007
#define CDICMD_STOP_TONES               0x1f3008
#define CDICMD_START_SIGNAL_DETECTOR    0x1f3009
#define CDICMD_STOP_SIGNAL_DETECTOR     0x1f300a
#define CDICMD_ASSERT_SIGNAL            0x1f300b
#define CDICMD_GET_SIGNAL_STATE         0x1f300c
#define CDICMD_START_STATUS_MONITORING  0x1f300d
#define CDICMD_STOP_STATUS_MONITORING   0x1f300e
#define CDICMD_READ_THERMOMETER         0x1f300f
#define CDICMD_START_TIMER              0x1f3010
#define CDICMD_STOP_TIMER               0x1f3011
#define CDICMD_GET_BOARD_STATUS         0x1f3012
#define CDICMD_USER_LED                 0x1f3013 
#define CDICMD_SEND_MESSAGE             0x1f3014
#define CDICMD_RECEIVE_MESSAGE          0x1f3015

/*-----------------------------------------------------------------------------
  CDI Event Codes.
    - These codes are constructed using the CDI_SVCID, the  CT Access
      CTA_CODE_EVENT typecode, and a sequence number. The formula is
        EVENTCODE = ((CDI_SVCID<<16) | (CTA_CODE_EVENT | SEQUENCE))
    - If an event declaration is a done event 0x100 must also be ORed into
      event code.
        EVENTCODE = ((CDI_SVCID<<16) | (CTA_CODE_EVENT | 0x100 | SEQUENCE)
    - Note that the CDI Service also generates CT Access events as well; 
      therefore this is not an exhaustive list of all, CDI generated, 
      event codes.
  ---------------------------------------------------------------------------*/

#define CDIEVN_TONE_DONE                0x1f2001
#define CDIEVN_DTMF_STARTED             0x1f2002
#define CDIEVN_DTMF_ENDED               0x1f2003
#define CDIEVN_ON_HOOK                  0x1f2004
#define CDIEVN_OFF_HOOK                 0x1f2005
#define CDIEVN_FLASH_HOOK               0x1f2006
#define CDIEVN_A_CHANGE_OFF             0x1f2007
#define CDIEVN_A_CHANGE_ON              0x1f2008
#define CDIEVN_BOARD_STATUS_CHANGE      0x1f2009
#define CDIEVN_TIMER_TICK               0x1f200a
#define CDIEVN_TIMER_DONE               0x1f200b
#define CDIEVN_CX_HEART_BEAT_LOST       0x1f200c
#define CDIEVN_CX_HEART_BEAT_BACK       0x1f200d
#define CDIEVN_TIMER_START              0x1f200e
#define CDIEVN_RING_IS_ON               0x1f200f
#define CDIEVN_RING_IS_OFF              0x1f2010

                                 /* ((CDI_SVCID<<16)|(CTA_CODE_EVENT|0x01)) */

/*-----------------------------------------------------------------------------
  CDI Reason Codes. 
    - CDI reason codes for events defined above.  These values are to be 
      utilized in the "value" member of the event structure, so that an 
      application can determine why an event occurred.
  
    - These codes are constructed using the CDI_SVCID, the CT Access
      CTA_CODE_REASON typecode, and a sequence number. The formula is
        REASONCODE = ((CDI_SVCID<<16) | (CTA_CODE_REASON | SEQUENCE))
  ---------------------------------------------------------------------------*/
/* Event occurred because of reason one. */
#define CDIREASON_ONE ((CDI_SVCID<<16)|(CTA_CODE_REASON|0x1)) 
#define CDIREASON_TWO ((CDI_SVCID<<16)|(CTA_CODE_REASON|0x2)) 

/*-----------------------------------------------------------------------------
  CDI Trace Tag Codes.
    - These codes are constructed using the cdi_SVCID, the CT Access
      CTA_CODE_TRACETAG typecode, and a sequence number. The formula is
         TRACETAGCODE = ((CDI_SVCID<<16) | (CTA_CODE_TRACETAG | SEQUENCE))
    - Tracetag definitions are utilized in cdiFormatTraceBuffer to assist
      ctdaemon utility with tracing information to debug service/application.
  ---------------------------------------------------------------------------*/
#define CDI_TRACETAG_ZERO       0x1f4000
#define CDI_TRACETAG_ONE        0x1f4001
#define CDI_TRACETAG_BITX       0x1f4002

/*-----------------------------------------------------------------------------
  CDI Error codes. 
    -   Error codes are the return values for API calls for error events
        peculiar to this service.  You may wish to check ctaerr.h to see if a 
        generic CT Access error code is good enough to suite your debugging
        needs.
    - These codes are constructed using the CDI_SVCID, the CT Access
      CTA_CODE_ERROR typecode, and a sequence number. The formula is
         ERRORCODE = ((CDI_SVCID<<16) | (CTA_CODE_ERROR | SEQUENCE))  
  ---------------------------------------------------------------------------*/
#define CDIERR_XXX          ((CDI_SVCID<<16)|(CTA_CODE_ERROR|0x1)) 

/*-----------------------------------------------------------------------------
 Command / event message format definition
 ---------------------------------------------------------------------------*/

#define MAX_CHANNEL_CMD 0x20
#define SIZE_CHANNEL_CMD 40

extern char supervisor_cmd[MAX_CHANNEL_CMD][SIZE_CHANNEL_CMD];
extern char channel_cmd[MAX_CHANNEL_CMD][SIZE_CHANNEL_CMD];


/*-----------------------------------------------------------------------------
 cdiGetText() Macros.
    - These macros convert CDI Service command, event, error, and reason codes
      to their corresponding ASCII macro identifier.
 ---------------------------------------------------------------------------*/

#define TEXTCASE(e) case e: return #e 

#define CDI_COMMANDS() \
TEXTCASE (CDICMD_START_DTMF_DETECTOR); \
TEXTCASE (CDICMD_STOP_DTMF_DETECTOR); \
TEXTCASE (CDICMD_ENABLE_BATTERY); \
TEXTCASE (CDICMD_DISABLE_BATTERY); \
TEXTCASE (CDICMD_START_RING); \
TEXTCASE (CDICMD_STOP_RING); \
TEXTCASE (CDICMD_START_TONES); \
TEXTCASE (CDICMD_STOP_TONES); \
TEXTCASE (CDICMD_START_SIGNAL_DETECTOR); \
TEXTCASE (CDICMD_STOP_SIGNAL_DETECTOR); \
TEXTCASE (CDICMD_ASSERT_SIGNAL); \
TEXTCASE (CDICMD_GET_SIGNAL_STATE); \
TEXTCASE (CDICMD_START_STATUS_MONITORING); \
TEXTCASE (CDICMD_STOP_STATUS_MONITORING); \
TEXTCASE (CDICMD_READ_THERMOMETER); \
TEXTCASE (CDICMD_START_TIMER); \
TEXTCASE (CDICMD_STOP_TIMER); \
TEXTCASE (CDICMD_GET_BOARD_STATUS); \
TEXTCASE (CDICMD_USER_LED); 

#define CDI_EVENTS() \
TEXTCASE (CDIEVN_TONE_DONE); \
TEXTCASE (CDIEVN_ON_HOOK); \
TEXTCASE (CDIEVN_OFF_HOOK); \
TEXTCASE (CDIEVN_FLASH_HOOK); \
TEXTCASE (CDIEVN_A_CHANGE_OFF); \
TEXTCASE (CDIEVN_A_CHANGE_ON); \
TEXTCASE (CDIEVN_BOARD_STATUS_CHANGE); \
TEXTCASE (CDIEVN_TIMER_TICK); \
TEXTCASE (CDIEVN_TIMER_DONE); \
TEXTCASE (CDIEVN_DTMF_STARTED); \
TEXTCASE (CDIEVN_DTMF_ENDED); \
TEXTCASE (CDIEVN_CX_HEART_BEAT_LOST);\
TEXTCASE (CDIEVN_CX_HEART_BEAT_BACK);\
TEXTCASE (CDIEVN_TIMER_START);\
TEXTCASE (CDIEVN_RING_IS_ON);\
TEXTCASE (CDIEVN_RING_IS_OFF)

#define CDI_ERRORS() \
TEXTCASE (CDIERR_XXX);

#define CDI_REASONS() \
TEXTCASE (CDIREASON_ONE); \
TEXTCASE (CDIREASON_TWO); 



/*-----------------------------------------------------------------------------
  Exported API Data Structures
  - Definition of data structures exposed via API
  - constants
  ---------------------------------------------------------------------------*/

typedef struct
{
	DWORD size;
	DWORD voltage_presence;
	DWORD board_presence;
	DWORD thermometer_presence;
	DWORD thermal_state;
	DWORD hmic_error;
	DWORD slic_error[3];
}	CDI_BOARD_STATUS;


#define CDI_VOLTAGE_LOW_BATTERY      0x0001
#define CDI_VOLTAGE_HIGH_BATTERY     0x0002
#define CDI_VOLTAGE_RING_VOLTAGE     0x0004
#define CDI_VOLTAGE_EXT_RINGER       0x0008

#define CDI_BOARD_FIRST_STATION_GROUP   0x0001
#define CDI_BOARD_SECOND_STATION_GROUP  0x0002
#define CDI_BOARD_THIRD_STATION_GROUP   0x0004
#define CDI_BOARD_REAR_BOARD            0x0008

#define CDI_THERMOMETER_0_POPULATED     0x0001
#define CDI_THERMOMETER_1_POPULATED     0x0002
#define CDI_THERMOMETER_2_POPULATED     0x0004
#define CDI_THERMOMETER_3_POPULATED     0x0008
#define CDI_THERMOMETER_4_POPULATED     0x0010

#define CDI_HMIC_ERROR_SYSTEM        0x0001
#define CDI_HMIC_ERROR_CLOCK         0x0002
#define CDI_BSP_SYNC_ERROR           0x0004

#define CDI_THERMAL_IDLE             0x0000
#define CDI_THERMAL_NORMAL           0x0001
#define CDI_THERMAL_WARNING          0x0002
#define CDI_THERMAL_PROTECTION       0x0003

/*-----------------------------------------------------------------------------
  CDI Service API function prototypes.
  ---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
    ctahd:    Handle for CT Access context to start.
    arg1:     Some DWORD argument.  May be modified to any type of pass
              argument.
    arg2:     Some structure argument.  May be modified to any type of pass
              argument.

  Returns SUCCESS on successful execution, otherwise returns a CT Access
  or Service specific error code on failure.
  ---------------------------------------------------------------------------*/
DWORD NMSAPI cdiStartTones( CTAHD ctahd, CDI_TONE_PARMS *parms );
DWORD NMSAPI cdiStartDTMFDetector( CTAHD ctahd, CDI_DTMFDETECTOR_PARMS *parms	);
DWORD NMSAPI cdiStopDTMFDetector( CTAHD ctahd );
DWORD NMSAPI cdiEnableBattery( CTAHD ctahd );
DWORD NMSAPI cdiDisableBattery( CTAHD ctahd );
DWORD NMSAPI cdiStartRing( CTAHD ctahd, CDI_RING_PARMS *parms );
DWORD NMSAPI cdiStopRing( CTAHD ctahd );
DWORD NMSAPI cdiStopTones( CTAHD ctahd );
DWORD NMSAPI cdiStartSignalDetector( CTAHD ctahd, CDI_SIGNALDETECTOR_PARMS *parms );
DWORD NMSAPI cdiStopSignalDetector( CTAHD ctahd );
DWORD NMSAPI cdiAssertSignal( CTAHD ctahd, DWORD pattern );
DWORD NMSAPI cdiGetSignalState( CTAHD ctahd, DWORD *pattern );
DWORD NMSAPI cdiStartStatusMonitoring( CTAHD ctahd );
DWORD NMSAPI cdiStopStatusMonitoring( CTAHD ctahd );
DWORD NMSAPI cdiReadThermometer( CTAHD ctahd, DWORD tid, DWORD *temp );
DWORD NMSAPI cdiStartTimer( CTAHD ctahd, DWORD timeout, DWORD count );
DWORD NMSAPI cdiStopTimer( CTAHD ctahd );
DWORD NMSAPI cdiGetBoardStatus( CTAHD ctahd, CDI_BOARD_STATUS *board_status );
DWORD NMSAPI cdiUserLed( CTAHD ctahd, DWORD value );


/* values for CdiUserLed() */
#define RESET_USER_LED	0
#define SET_USER_LED	1
#define TOGGLE_USER_LED	2

/*-----------------------------------------------------------------------------
	masks for EnhancedMode
 bit0 is the global enhancedmode bit. When set, all functions are used in this mode.

 When bit is reset, each function can choose to use enhanced mode using a dedicated bit
 For simplicity reason, we recommend using the global approach as much as possible 
  ---------------------------------------------------------------------------*/
#define GLOBAL_ENHANCEDMODE_MASK	0x01

#define TONES_ENHANCEDMODE_MASK		( 0x02 | GLOBAL_ENHANCEDMODE_MASK )
#define DTMF_ENHANCEDMODE_MASK		( 0x04 | GLOBAL_ENHANCEDMODE_MASK )
#define SIGNAL_ENHANCEDMODE_MASK	( 0x08 | GLOBAL_ENHANCEDMODE_MASK ) 
#define RING_ENHANCEDMODE_MASK		( 0x10 | GLOBAL_ENHANCEDMODE_MASK )

#define RING_CYCLE_EVENTS_MASK    0x1000


#ifdef __cplusplus
}
#endif


#endif /* CDIDEF_INCLUDED */
