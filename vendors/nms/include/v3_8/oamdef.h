/*****************************************************************************
  NAME:  oamdef.h

  PURPOSE:

      This file contains macros and function prototypes that define the API
      for the OAM sample service.

      Your service will be specified by the prefix 'oam' throughout all
      related template service source files.
  ****************************************************************************/

#ifndef OAMDEF_INCLUDED
#define OAMDEF_INCLUDED


/* Standard CT Access include files. */
#include "nmstypes.h"
#include "ctadef.h"
#include <time.h>


/* Prevent C++ name mangling. */
#ifdef __cplusplus
extern "C"
{
#endif

/*-----------------------------------------------------------------------------
  OAM Service ID.
    - These id's are allocated by NMS Developer Support.
    - Do not reuse an existing Service ID as processing conflicts will occur!
  ---------------------------------------------------------------------------*/

#define OAM_SVCID                           0x4000

/*-----------------------------------------------------------------------------
  OAM Version Ids
    - These id's are used to identify the revision level of this service.
  ---------------------------------------------------------------------------*/

#define OAM_MAJORREV                        1
/* Please note, that minor 1 means 01, for example  - 1.01; 10 means 1.10. */
#define OAM_MINORREV                        3

/*-----------------------------------------------------------------------------
  OAM API Compatibility Level Id
    - This id is used to determine runtime compatibility between the
      installed OAM service and clients of the OAM service. Clients can
      be a CT Access application which accesses OAM functionality
      via the OAM API.
    - Clients(CT Access application) #include this file into their code and,


      therefore, insert "hard coded" values for each OAM compat level
      into their client code.
    - The API_COMPATLEVEL is used by CT Access application developers who
      want to check the "hard coded" value in their application against the
      "hard coded" value in the installed OAM service (as determined
      via ctaGetServiceVersion() will be available in CT Access Version 2.1).
    - API compatibility level value should be incremented when the associated
      source module changes in a non-backwards compatible way. Refer to the CT
      Access Service Writer's Manual for more info.
  ---------------------------------------------------------------------------*/

#define OAMAPI_COMPATLEVEL                  1

/*-----------------------------------------------------------------------------
  OAM Event Codes.
    - These codes are constructed using the OAM_SVCID, the CT Access
      CTA_CODE_EVENT id, and a 1-based sequence number. The formula is
        EVENTCODE = ((OAM_SVCID<<16) | (CTA_CODE_EVENT | SEQUENCE))
    - If an event declaration is a "done" event 0x100 must also be ORed into
      event code.
        EVENTCODE = ((OAM_SVCID<<16) | (CTA_CODE_EVENT | 0x100 | SEQUENCE)
    - The actual event codes are "hardcoded" for source browsing purposes.
    - Note that the OAM Service also generates CT Access events as well;
      therefore this is not an exhaustive list of all, OAM generated,
      event codes.
  ---------------------------------------------------------------------------*/

#define OAMEVN_BASE             0x40002000  // ((OAM_SVCID << 16) | CTA_CODE_EVENT)
#define OAM_IS_OAM_EVENT(x) ((x & 0xF000F000) == OAMEVN_BASE) // within reserved bank of OAM event codes

// Normal events.
#define OAMEVN_ALERT            0x40002001  // catch-all (use this till you add a new specific code)
#define OAMEVN_REPORT           0x40002002  // special internal code used to log report info
#define OAMEVN_CREATED          0x40002003  // object was created
#define OAMEVN_DELETED          0x40002004  // object was deleted
#define OAMEVN_RENAMED          0x40002005  // object was renamed (text = new name)
#define OAMEVN_TRACE            0x40002006  // indicates trace info (potentially high-speed)
#define OAMEVN_MODIFIED         0x40002007  // object was modified (closed after write access)
#define OAMEVN_BOARD_DEAD       0x40002008  // object representing this board
                                            // is dead
 
// "Done" events indicating completion of asynchronous function calls.
#define OAMEVN_STARTBOARD_DONE  0x40002101
#define OAMEVN_STOPBOARD_DONE   0x40002102
#define OAMEVN_TESTBOARD_DONE   0x40002103

/*-----------------------------------------------------------------------------
  OAM Reason Codes.
    - OAM reason codes for events defined above.  These values are to be
      utilized in the "value" member of the event structure, so that an
      application can determine why an event occurred.
    - These codes are constructed using the OAM_SVCID, the CT Access
      CTA_CODE_REASON id, and a 1-based sequence number. The formula is
        REASONCODE = ((OAM_SVCID<<16) | (CTA_CODE_REASON | SEQUENCE))
    - The actual reason codes are "hardcoded" for source browsing purposes.
  ---------------------------------------------------------------------------*/

#define OAM_REASON_BASE         0x40001000  // ((OAM_SVCID << 16) | CTA_CODE_REASON)

#define OAM_REASON_FINISHED     CTA_REASON_FINISHED // ran to completion
#define OAM_REASON_FAILED       0x40001001  // general failure

/*-----------------------------------------------------------------------------
  OAM Error codes.
    - These codes are constructed using the OAM_SVCID, the CT Access
      CTA_CODE_ERROR id, and a 1-based sequence number. The formula is
         ERRORCODE = ((OAM_SVCID<<16) | (CTA_CODE_ERROR | SEQUENCE))
    - The actual error codes are "hardcoded" for source browsing purposes.
  ---------------------------------------------------------------------------*/

#define OAMERR_BASE                 0x40000000  // ((OAM_SVCID << 16) | CTA_CODE_ERROR)

// Normal error codes.
#define OAMERR_SERVER_NOT_FOUND     0x40000001
#define OAMERR_SERVER_NOT_RUNNING   0x40000002
#define OAMERR_NOT_ENOUGH_MEMORY    0x40000003
#define OAMERR_NOT_FOUND            0x40000004
#define OAMERR_ALREADY_EXISTS       0x40000005
#define OAMERR_ACCESS_DENIED        0x40000006
#define OAMERR_FILE_READ_ERROR      0x40000007
#define OAMERR_FILE_WRITE_ERROR     0x40000008
#define OAMERR_CANT_CREATE_THREAD   0x40000009

// Generic error codes used by plug-ins.
#define OAMERR_PLUGIN_INIT_FAIL                     0x40000101
#define OAMERR_PLUGIN_EXIT_FAIL                     0x40000102
#define OAMERR_NOT_SUPPORTED_WARNING                0x40000103
#define OAMERR_AUTO_DETECT_BOARD_FAIL               0x40000104
#define OAMERR_CREATE_BOARD_FAIL                    0x40000105
#define OAMERR_DESTORY_BOARD_FAIL                   0x40000106
#define OAMERR_GET_BOARD_KEYWORD_FAIL               0x40000107
#define OAMERR_SET_BOARD_KEYWORD_FAIL               0x40000108
#define OAMERR_GET_QUALIFIER_FAIL                   0x40000109
#define OAMERR_OPEN_OBJECT_FAIL                     0x4000010A
#define OAMERR_CLOSE_OBJECT_FAIL                    0x4000010B
#define OAMERR_START_BOARD_FAIL                     0x4000010C
#define OAMERR_STOP_BOARD_FAIL                      0x4000010D
#define OAMERR_BOARD_SELFTEST_FAIL                  0x4000010E
#define OAMERR_BOARD_SELFTEST_INVALID               0x4000010F
#define OAMERR_SEND_BUFFER_FAIL                     0x40000110
#define OAMERR_OPEN_DRIVER_FAIL                     0x40000111

/*-----------------------------------------------------------------------------
  Data type definitions.
  ---------------------------------------------------------------------------*/

typedef UINTPTR HMOBJ;        // handle to a managed object
typedef UINTPTR HOAMCLIENT;   // handle to an OAM client (caller-defined DWORD)

// OAM message structure used for asynchronous notifications.
typedef struct oam_msg_tag
{
    DWORD dwMsgLen;         // message length, including appended name & message strings
    DWORD dwCode;           // message event code (use OAMEVN_xxx)
    DWORD dwSeverity;       // message severity
    DWORD dwOfsSzName;      // offset to name string of source managed object
    DWORD dwOfsSzMessage;   // offset to text message string
    DWORD dwValue;          // possible additional event-specific data
    // string data is appended here
} OAM_MSG;

/*-----------------------------------------------------------------------------
  Constant values
  ---------------------------------------------------------------------------*/

// Object open mode flags.
#define OAM_READONLY    0x0
#define OAM_READWRITE   0x1
#define OAM_PROVIDER    0x2
static const char NAME_SUPERVISOR[] = "Supervisor";

// Board start/stop option flags.
#define OAM_AUTOONLY    0x1
#define OAM_SYNCHRONOUS 0x2

/**/
/*-----------------------------------------------------------------------------
  OAM Service API function prototypes.
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

DWORD NMSAPI oamSendBuffer( CTAHD ctahd, const char *szName, const BYTE *pbBuf, DWORD dwBufLen );

DWORD NMSAPI oamRestart( CTAHD ctahd );
DWORD NMSAPI oamShutdown( CTAHD ctahd );

DWORD NMSAPI oamAlertRegister( CTAHD ctahd );
DWORD NMSAPI oamAlertUnregister( CTAHD ctahd );
DWORD NMSAPI oamAlertNotify( CTAHD ctahd, const OAM_MSG *pMsg );

DWORD NMSAPI oamConfigExport( CTAHD ctahd, const char *szFile );
DWORD NMSAPI oamConfigImport( CTAHD ctahd, const char *szFile );
DWORD NMSAPI oamCreateBoard( CTAHD ctahd, const char *szProduct, char *szName, DWORD dwNameSize );
DWORD NMSAPI oamDeleteBoard( CTAHD ctahd, const char *szName );
DWORD NMSAPI oamAddDetectedBoard( CTAHD ctahd, const char *szName );
DWORD NMSAPI oamOpenObject( CTAHD ctahd, const char *szName, HMOBJ *phObject, DWORD dwMode );
DWORD NMSAPI oamCloseObject( HMOBJ hObject );
DWORD NMSAPI oamSetKeyword( HMOBJ hObject, const char *szKeyword, const char *szValue );
DWORD NMSAPI oamGetKeyword( HMOBJ hObject, const char *szKeyword, char *szValue, DWORD dwValueSize );
DWORD NMSAPI oamGetQualifier( HMOBJ hObject, const char *szKeyword, const char *szQualifier, char *szValue, DWORD dwValueSize );

DWORD NMSAPI oamDetectBoards( CTAHD ctahd );
DWORD NMSAPI oamStartBoard( CTAHD ctahd, const char *szName );
DWORD NMSAPI oamStopBoard( CTAHD ctahd, const char *szName );
DWORD NMSAPI oamTestBoard( CTAHD ctahd, const char *szName, DWORD dwOptions );

DWORD NMSAPI oamBoardEnum( CTAHD ctahd, int ixBoard, char *szName, DWORD dwNameSize );
DWORD NMSAPI oamBoardLookupByNumber( CTAHD ctahd, DWORD dwNumber, char *szName, DWORD dwNameSize );
DWORD NMSAPI oamBoardLookupByDriverIDs( CTAHD ctahd, const char *szDriverName, const char *szDriverBoardID, char *szName, DWORD dwNameSize );
DWORD NMSAPI oamBoardLookupByBusSlot( CTAHD ctahd, DWORD dwBus, DWORD dwSlot, char *szName, DWORD dwNameSize );
DWORD NMSAPI oamBoardLookupByIOAddress( CTAHD ctahd, DWORD dwIOAddress, char *szName, DWORD dwNameSize );
DWORD NMSAPI oamBoardLookupBySerialNumber( CTAHD ctahd, const char *szSerialNumber, char *szName, DWORD dwNameSize );
DWORD NMSAPI oamBoardLookupByProduct( CTAHD ctahd, const char *szProduct, char *szName, DWORD dwNameSize );
DWORD NMSAPI oamBoardGetNumber( CTAHD ctahd, const char *szName, DWORD *pdwNumber );
DWORD NMSAPI oamBoardGetDriverIDs( CTAHD ctahd, const char *szName, char *szDriverName, DWORD dwDriverNameSize, char *szDriverBoardID, DWORD dwDriverBoardIDSize );
DWORD NMSAPI oamBoardGetBusSlot( CTAHD ctahd, const char *szName, DWORD *pdwBus, DWORD *pdwSlot );
DWORD NMSAPI oamBoardGetIOAddress( CTAHD ctahd, const char *szName, DWORD *pdwIOAddress );
DWORD NMSAPI oamBoardGetSerialNumber( CTAHD ctahd, const char *szName, char *szSerialNumber, DWORD dwSerialNumberSize );
DWORD NMSAPI oamBoardGetProduct( CTAHD ctahd, const char *szName, char *szProduct, DWORD dwProductSize );

#ifdef __cplusplus
}
#endif


#endif /* OAMDEF_INCLUDED */

