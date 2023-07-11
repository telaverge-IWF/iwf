/*****************************************************************************
*                                  CNFDEF.H
*
*  Header for CT Access Conferencing service. 
*
*      This file contains macros and function prototypes that define the API
*      for the CNF service.
*
*  Copyright (c) 1999  Natural MicroSystems Corp.  All rights reserved.
*****************************************************************************/
#if !defined( CNFDEF_INCLUDED )
#define CNFDEF_INCLUDED 

#include "nmstypes.h"
#include "ctadef.h"

/* Prevent C++ name mangling. */
#if defined( __cplusplus )
extern "C"
{
#endif	/* defined( __cplusplus ) */


/*-----------------------------------------------------------------------------
  CNF Service ID.  
  ---------------------------------------------------------------------------*/
#define	CNF_SVCID			           0x1A
#define CNF_BASEID			     0x001A0000L /* base number for defining other keys */


/*-----------------------------------------------------------------------------
  CNF Version Ids  
    - These id's are used to identify the revision level of this service. 
  ---------------------------------------------------------------------------*/
#define CNF_MAJORREV                      2
#define CNF_MINORREV                      0


/*-----------------------------------------------------------------------------
  CNF API Compatibility Level Id
    - This id is used to determine runtime compatibility between the
      installed CNF service and clients of the CNF service. Clients can
      be a CT Access application which accesses CNF functionality
      via the CNF API.
    - Customers(CT Access application) #include this file into their code and, 
      therefore, insert "hard coded" values for each CNF compat level
      into their client code.
    - The API_COMPATLEVEL is used by CT Access application developers who
      want to check the "hard coded" value in their application against the
      "hard coded" value in the installed CNF service as determined
      via ctaGetServiceVersion().
    - API compatibility level value should be incremented when the associated
      source module changes in a non-backwards compatible way. Refer to the CT 
      Access Service Writer's Manual for more info.
  ---------------------------------------------------------------------------*/
#define CNF_API_COMPATLEVEL               1
#define CNF_SPI_COMPATLEVEL               1



/*-----------------------------------------------------------------------------
  CNF Event Codes.
    - These codes are constructed using the CNF_SVCID and a sequence number.
	  The formula is
        EVENTCODE = ((CNF_SVCID<<16) | (CTA_CODE_EVENT | SEQUENCE))
  ---------------------------------------------------------------------------*/
#define CNF_EVENTBASECODE                   ((CNF_SVCID << 16) | CTA_CODE_EVENT)

#define CNFEVN_OPEN_RESOURCE_DONE           (CNF_EVENTBASECODE | 0x1) 
#define CNFEVN_CLOSE_RESOURCE_DONE          (CNF_EVENTBASECODE | 0x2)
#define CNFEVN_ACTIVE_TALKERS_CHANGE        (CNF_EVENTBASECODE | 0x3) /* A change is occuring in the active talkers list */
#define CNFEVN_TONE_DONE                    (CNF_EVENTBASECODE | 0x4) /* A tone has finished playing */


/*-----------------------------------------------------------------------------
  CNF Error codes. 
    -   Error codes are the return values for API calls for error events
        peculiar to this service.  You may wish to check ctaerr.h to see if a 
        generic CT Access error code is good enough to suite your debugging
        needs.
    - These codes are constructed using the CNF_SVCID, the CT Access
      CTA_CODE_ERROR typecode, and a sequence number. The formula is
         ERRORCODE = ((CNF_SVCID<<16) | (CTA_CODE_ERROR | SEQUENCE))  
  ---------------------------------------------------------------------------*/
#define CNF_ERRBASECODE                     ((CNF_SVCID << 16) | CTA_CODE_ERROR)

/* Conferencing specific errors */
#define CNFERR_INVALID_IDENTIFIER           (CNF_ERRBASECODE | 0x1) /* The conference or member identifier in invalid */
#define CNFERR_INVALID_ATTRIBUTE            (CNF_ERRBASECODE | 0x2) /* The attribute is invalid  */
#define CNFERR_INVALID_PARAMETER            (CNF_ERRBASECODE | 0x3) /* One of the parameter is inconsistent or out of range  */
#define CNFERR_RESOURCE_NOT_DEFINED         (CNF_ERRBASECODE | 0x4) /* The conferencing resource isn't defined in the configuration file  */
#define CNFERR_RESOURCE_NOT_AVAILABLE       (CNF_ERRBASECODE | 0x5) /* The conferencing resource has been locked by another process */
#define CNFERR_NOT_ENOUGH_RESOURCE_SPACE    (CNF_ERRBASECODE | 0x6) /* Conferencing resource out of space */
#define CNFERR_BOARD_TIMEOUT                (CNF_ERRBASECODE | 0x7) /* The board timeout while waiting for rsp message */
#define CNFERR_CANNOT_CREATE_CHANNEL        (CNF_ERRBASECODE | 0x8) /* Unable to create a communication channel with the board correponding to the resource*/
#define CNFERR_CONFERENCE_EMPTY             (CNF_ERRBASECODE | 0x9) /* Unable to generate a tone on this conference; there is no member */



/* Event mask bits */
#define	CNF_EVNMSK_ACTIVE_TALKERS_CHANGE  0x1
#define	CNF_EVNMSK_TONE_DONE              0x2

/* Miscellaneous definitions */


/* Resizing mode to be used with cnfResizeConference */
#define	CNF_REDUCE_ALLOCATED            0x0
#define	CNF_INCREASE_ALLOCATED          0x1
#define	CNF_RESIZE_ALLOCATED            0x2

/* Board type returned by cnfGetResourceInfo */
#define CNF_BOARDTYPE_AG                0x1    /* Alliance Generation                   */ 
#define CNF_BOARDTYPE_CG                0x5    /* Convergence Generation                */

/* Available Capability bits */
#define	CNF_RESCAP_ECHO_CANCELER        0x0001 /* Echo Canceller 10ms window size and 200ms convergence 
                                                  time supported (legacy)               */	
#define CNF_RESCAP_COACHING             0x0002 /* Coaching mode supported               */
#define	CNF_RESCAP_DTMF_CLAMPING        0x0004 /* DTMF Clamping                         */	
#define	CNF_RESCAP_TONE_CLAMPING        0x0008 /* Tone Clamping supported               */	
#define	CNF_RESCAP_AUTO_GAIN_CONTROL    0x0010 /* Auto Gain Control supported           */	
#define	CNF_RESCAP_TALKER_PRIVILEGE     0x0020 /* Talker privilege supported            */	
#define	CNF_RESCAP_ACTIVE_TALKER        0x0040 /* Active Talker detection supported     */	
#define CNF_RESCAP_EC_10_MS_WINDOW      0x0080 /* Echo canceller with 10 ms window size */
#define CNF_RESCAP_EC_20_MS_WINDOW      0x0100 /*                with 20 ms window size */
#define CNF_RESCAP_EC_30_MS_WINDOW      0x0200 /*                with 30 ms window size */
#define CNF_RESCAP_EC_100_MS_CV         0x1000 /* Echo canceller with 100 ms convergence time */
#define CNF_RESCAP_EC_200_MS_CV         0x2000 /* Echo canceller with 200 ms convergence time */

/* Not used Capability flags */
#define	CNF_NO_ECHO_CANCEL              0x0001 /* All Echo Cancellation disabled         */	
#define CNF_NO_COACHING                 0x0002 /* Conference Coaching/Mapping mode disabled  */
#define	CNF_NO_DTMF_CLAMPING            0x0004 /* DTMF Clamping disabled                 */	
#define	CNF_NO_TONE_CLAMPING            0x0008 /* Tone Clamping disabled                 */

/* G711 Law set via MEMBER_ATTR_XXXX_G711_LAW */
#define CNF_G711_DEFAULT                0x0    /* Firmware Default                       */
#define CNF_G711_ALAW                   0x1    /* A-Law                                  */
#define CNF_G711_MULAW                  0x2    /* Mu-Law                                 */

/* Coaching flag define */
#define CNF_COACHING_HEAR               0x1
#define CNF_COACHING_SILENT             0x0

/* Conference attributes */ 
#define	CNF_CONFATTR_BASECODE           0x10000

#define	CONF_ATTR_NUM_LOUDEST_SPEAKERS       (CNF_CONFATTR_BASECODE | 0x01)	
#define	CONF_ATTR_EVENT_MASK                 (CNF_CONFATTR_BASECODE | 0x02)
#define	CONF_ATTR_ACTIVE_TALKERS             (CNF_CONFATTR_BASECODE | 0x03)
#define	CONF_ATTR_ACTIVE_TALKERS_TIMER       (CNF_CONFATTR_BASECODE | 0x04)


/* Member attributes */
#define CNF_MEMBERATTR_BASECODE         0x20000

#define MEMBER_ATTR_EC_ENABLE                (CNF_MEMBERATTR_BASECODE | 0x01)
#define MEMBER_ATTR_EC_GAIN                  (CNF_MEMBERATTR_BASECODE | 0x02)
#define MEMBER_ATTR_EC_PREDELAY              (CNF_MEMBERATTR_BASECODE | 0x03)

#define MEMBER_ATTR_INPUT_AGC_ENABLE         (CNF_MEMBERATTR_BASECODE | 0x10)
#define MEMBER_ATTR_INPUT_AGC_TARGETAMPL     (CNF_MEMBERATTR_BASECODE | 0x11)
#define MEMBER_ATTR_INPUT_AGC_SILENCEAMPL    (CNF_MEMBERATTR_BASECODE | 0x12)

#define MEMBER_ATTR_OUTPUT_AGC_ENABLE        (CNF_MEMBERATTR_BASECODE | 0x20) 
#define MEMBER_ATTR_OUTPUT_AGC_TARGETAMPL    (CNF_MEMBERATTR_BASECODE | 0x21)
#define MEMBER_ATTR_OUTPUT_AGC_SILENCEAMPL   (CNF_MEMBERATTR_BASECODE | 0x22)

#define MEMBER_ATTR_INPUT_GAIN               (CNF_MEMBERATTR_BASECODE | 0x30)
#define MEMBER_ATTR_OUTPUT_GAIN              (CNF_MEMBERATTR_BASECODE | 0x31)

#define MEMBER_ATTR_TALKER_ENABLE            (CNF_MEMBERATTR_BASECODE | 0x40)
#define MEMBER_ATTR_LISTENER_ENABLE          (CNF_MEMBERATTR_BASECODE | 0x41)
#define MEMBER_ATTR_TALKER_PRIVILEGE         (CNF_MEMBERATTR_BASECODE | 0x42)
#define MEMBER_ATTR_DTMF_CLAMPING_ENABLE     (CNF_MEMBERATTR_BASECODE | 0x43)
#define MEMBER_ATTR_TONE_CLAMPING_ENABLE     (CNF_MEMBERATTR_BASECODE | 0x44)
#define MEMBER_ATTR_SELF_ECHO_ENABLE         (CNF_MEMBERATTR_BASECODE | 0x45)

#define MEMBER_ATTR_INPUT_G711_LAW           (CNF_MEMBERATTR_BASECODE | 0x50)
#define MEMBER_ATTR_OUTPUT_G711_LAW          (CNF_MEMBERATTR_BASECODE | 0x51)

#define MEMBER_ATTR_DTMF_CLAMPING_DELAYLINE  (CNF_MEMBERATTR_BASECODE | 0x60)


/*-----------------------------------------------------------------------------
  Exported API Data Structures
  - Definition of data structures exposed via API
  ---------------------------------------------------------------------------*/

/* CNF_RESOURCE_INFO structure */
typedef struct
{
    DWORD   size;              /* size of the structure */
    DWORD   board;             /* AG board number */
    DWORD  	boardtype;         /* type of AG board */
    DWORD   capabilities;      /* capabilities currently available */
    DWORD 	conference;        /* number of conference currently running */
    DWORD 	max_members;       /* maximum number of members*/
    DWORD   available_members; /* number of members currently available */
} CNF_RESOURCE_INFO; 


/* CNF_CONFERENCE_INFO structure */
typedef struct
{
    DWORD 	size;               /* size of the structure */
    DWORD   allocated_members;  /* number of member allocated for this conference */
    DWORD   joined_members;     /* number of member allocated for this conference */
    DWORD 	flags;              /* capabilities not used flags */
    DWORD   capabilities;       /* actual capabilities of the conference */
    DWORD 	user_value;         /* application provided value */
} CNF_CONFERENCE_INFO; 


/* CNF_MEMBER_INFO structure */
typedef struct
{
    DWORD 	size;               /* size of the structure */
    DWORD 	stream;             /* MVIP address */
    DWORD   timeslot;           /* MVIP address */
    DWORD 	user_value;         /* application provided value */
} CNF_MEMBER_INFO; 


/* Parameter ID */

#define	CNF_CONFERENCE_PARMID           0x1A0001
#define	CNF_CONFERENCE_ATTR_PARMID      0x1A0002
#define	CNF_MEMBER_PARMID               0x1A0003
#define	CNF_MEMBER_ATTR_PARMID          0x1A0004
#define	CNF_TONE_PARMID	                0x1A0005

/*
 * Parameter structures 
 */


/* Conference parameters (used in cnfCreateConference) */
typedef struct
{
	DWORD	size;
	DWORD	flags;
	DWORD	allocated_members;
	DWORD	user_value;
} CNF_CONFERENCE_PARMS;

/* Conference attributes */
typedef struct
{
	DWORD	size;
	DWORD	num_loudest;
	DWORD	event_mask;
	DWORD	active_talkers;
	DWORD	active_talkers_timer;
} CNF_CONFERENCE_ATTR_PARMS;

/* Member parameters (used in cnfJoinConference) */
typedef struct
{
	DWORD	size;
	DWORD	user_value;
} CNF_MEMBER_PARMS;


/* Member attributes */
typedef struct
{
	DWORD	size;
	DWORD	ec_enable;
	INT32	ec_gain;
	DWORD	ec_predelay;
	DWORD	input_agc_enable;
	INT32	input_agc_targetampl;
	INT32	input_agc_silenceampl;
	INT32	input_gain;
	DWORD	output_agc_enable;
	INT32	output_agc_targetampl;
	INT32	output_agc_silenceampl;
	INT32	output_gain;
	DWORD	talker_enable;
	DWORD	listener_enable;
	DWORD	talker_privilege;
	DWORD	dtmf_clamping_enable;
	DWORD	tone_clamping_enable;
	DWORD	self_echo_enable;
	DWORD	input_law;
	DWORD	output_law;
	DWORD	dtmf_clamping_delay_line;
} CNF_MEMBER_ATTR_PARMS;

/* Tone parameters (used in cnfStartTone) */
typedef struct
{
	DWORD	size;
	DWORD	freq1;
	INT32	ampl1;
	DWORD	freq2;
	INT32	ampl2;
	DWORD	ontime;
	DWORD	offtime;
	INT32	iterations;
} CNF_TONE_PARMS;



/*-----------------------------------------------------------------------------
  CNF Service API function prototypes.
  ---------------------------------------------------------------------------*/
typedef DWORD CNFRESOURCEHD;

#define NULL_CNFRESOURCEHD NULL_CTAHD

DWORD NMSAPI cnfGetResourceList (CTAHD ctahd,
						  unsigned maxresources,
						  unsigned *resourcelist,
						  unsigned *numresources);

DWORD NMSAPI cnfOpenResource (CTAHD ctahd,
	                      unsigned resourcenum,
	                      CNFRESOURCEHD *cnfresourcehd);

DWORD NMSAPI cnfGetResourceInfo (CNFRESOURCEHD cnfresourcehd,
	                      CNF_RESOURCE_INFO *resourceinfo,
	                      unsigned size); 

DWORD NMSAPI cnfGetConferenceList (CNFRESOURCEHD cnfresourcehd,
						  unsigned maxconfids,
	                      DWORD *confidlist,
	                      unsigned *numconfids);

DWORD NMSAPI cnfCreateConference (CNFRESOURCEHD cnfresourcehd,
						  CNF_CONFERENCE_PARMS *parms,
	                      DWORD *confid);

DWORD NMSAPI cnfGetConferenceInfo (CNFRESOURCEHD cnfresourcehd,
					      DWORD confid,
						  CNF_CONFERENCE_INFO *confinfo,
	                      unsigned size);

DWORD NMSAPI cnfResizeConference (CNFRESOURCEHD cnfresourcehd,
						  DWORD confid,
	                      DWORD mode,
	                      unsigned number); 

DWORD NMSAPI cnfGetConferenceAttribute (CNFRESOURCEHD cnfresourcehd,
						  DWORD confid,
						  DWORD attribute,
						  INT32 *value);

DWORD NMSAPI cnfSetConferenceAttribute (CNFRESOURCEHD cnfresourcehd,
						  DWORD confid,
				   		  DWORD attribute,
				   		  INT32 value);

DWORD NMSAPI cnfGetMemberList (CNFRESOURCEHD cnfresourcehd,
	                      DWORD confid,
						  unsigned maxmemberids,
					      DWORD *memberidlist,
	                      unsigned *nummemberids);

DWORD NMSAPI cnfGetActiveTalkersList (CNFRESOURCEHD cnfresourcehd,
						  DWORD confid,
						  unsigned maxmemberids,
						  DWORD *memberidlist,
						  unsigned *nummemberids);

DWORD NMSAPI cnfJoinConference (CNFRESOURCEHD cnfresourcehd,
						  DWORD confid,
						  CNF_MEMBER_PARMS *parms,
						  DWORD *memberid); 

DWORD NMSAPI cnfGetMemberInfo (CNFRESOURCEHD cnfresourcehd,
						  DWORD memberid,
						  CNF_MEMBER_INFO *memberinfo,
						  unsigned size);

DWORD NMSAPI cnfGetMemberAttribute (CNFRESOURCEHD cnfresourcehd,
						  DWORD memberid,
						  DWORD attribute,
					      INT32 *value);

DWORD NMSAPI cnfGetMemberAttributeList (CNFRESOURCEHD cnfresourcehd,
						  DWORD memberid,
						  DWORD *attributes,
						  INT32 *values,
						  unsigned count); 

DWORD NMSAPI cnfSetMemberAttribute (CNFRESOURCEHD cnfresourcehd,
						  DWORD memberid,
						  DWORD attribute,
						  INT32 value);

DWORD NMSAPI cnfSetMemberAttributeList (CNFRESOURCEHD cnfresourcehd,
						  DWORD memberid,
						  DWORD *attributes,
						  INT32 *values,
						  unsigned count);

DWORD NMSAPI cnfStartTone (CNFRESOURCEHD cnfresourcehd,
						  DWORD confid,
						  CNF_TONE_PARMS *parms);

DWORD NMSAPI cnfStopTone (CNFRESOURCEHD cnfresourcehd,
						  DWORD confid);

DWORD NMSAPI cnfSetCoaching (CNFRESOURCEHD cnfresourcehd,
						  DWORD memberid,
                          BYTE flag,
                          DWORD *listeneridlist,
                          unsigned numlistenerids);

DWORD NMSAPI cnfGetCoaching (CNFRESOURCEHD cnfresourcehd,
						  DWORD memberid,
                          BYTE flag,
                          unsigned maxlistenerids,
                          DWORD *listeneridlist,
                          unsigned *numlistenerids);

DWORD NMSAPI cnfLeaveConference (CNFRESOURCEHD cnfresourcehd,
						  DWORD memberid);

DWORD NMSAPI cnfCloseConference (CNFRESOURCEHD cnfresourcehd,
						  DWORD confid);

DWORD NMSAPI cnfCloseResource (CNFRESOURCEHD cnfresourcehd);
 

/* The following macros may be used for tracing facilities */

#if !defined( _TEXTCASE_ )
	#define _TEXTCASE_(e) case e: return #e
#endif	/* !defined( _TEXTCASE_ ) */


#ifdef __cplusplus
}
#endif	/* defined( __cplusplus ) */

#endif /* !defined( CNFDEF_INCLUDED ) */



