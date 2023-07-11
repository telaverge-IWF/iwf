/******************************************************************************\
* File: super.h
* Author:   Phil Sours
* Project:  OA&M Server - Supervisor
*
* Description:
*       Public header file for client of Supervisor.
*
* Revision History:
*       (see source code control)
*
*	(c)   1999 Natural MicroSystems Inc.   All rights reserved.
\******************************************************************************/

#ifndef __super_h__
#define __super_h__

#include "oamdef.h"   // OAM Service include file, contains most of what we need

//******************************************************************************
// Constant values
//******************************************************************************

#define NULL_HOAMCLIENT (HOAMCLIENT)NULL_CTAHD  // NULL OA&M client handle

// Severity levels for alert notification messages.
#define OAM_SEVERITY_INFO       CTA_TRACE_SEVERITY_INFO
#define OAM_SEVERITY_WARNING    CTA_TRACE_SEVERITY_WARNING
#define OAM_SEVERITY_ERROR      CTA_TRACE_SEVERITY_ERROR

//******************************************************************************
// Data type definitions.
//******************************************************************************

typedef DWORD OAM_ERRCODE;

//******************************************************************************
// Exported functions.
//******************************************************************************

// Use extern "C" to prevent C++ name decoration.
// Use NMSSTDCALL since it's the standard language-independent function
// calling convention.
#ifdef __cplusplus
extern "C" {
#endif

// Debug functions.

void NMSSTDCALL _oamHello( const char *sz );
OAM_ERRCODE NMSSTDCALL _oamSendBuffer( const char *szName, const BYTE *pbBuf, DWORD dwBufLen );

// UMI functions.

OAM_ERRCODE NMSSTDCALL _oamInit();
OAM_ERRCODE NMSSTDCALL _oamExit();
OAM_ERRCODE NMSSTDCALL _oamRestart();
OAM_ERRCODE NMSSTDCALL _oamShutdown();

// - These functions will not be exposed to clients, just to the CT Access
//   Service Manager.
OAM_ERRCODE NMSSTDCALL _oamClientInit( HOAMCLIENT hClient );
OAM_ERRCODE NMSSTDCALL _oamClientExit( HOAMCLIENT hClient );
const char * NMSSTDCALL _oamGetText( DWORD dwCode );

// - Only the CT Access Service Manager will use _oamAlertRegisterCallback().
// - Client versions of _oamAlertRegister() & _oamAlertUnregister() have no args.
OAM_ERRCODE NMSSTDCALL _oamAlertRegisterCallback( OAM_ERRCODE (*fnAlertCallback)( HOAMCLIENT hClient, const OAM_MSG *pMsg ) );
OAM_ERRCODE NMSSTDCALL _oamAlertRegister( HOAMCLIENT hClient );
OAM_ERRCODE NMSSTDCALL _oamAlertUnregister( HOAMCLIENT hClient );
OAM_ERRCODE NMSSTDCALL _oamAlertNotify( const OAM_MSG *pMsg );

OAM_ERRCODE NMSSTDCALL _oamConfigExport( const char *szFile );
OAM_ERRCODE NMSSTDCALL _oamConfigImport( const char *szFile );
OAM_ERRCODE NMSSTDCALL _oamCreateBoard( const char *szProduct, char *szName, DWORD dwNameSize );
OAM_ERRCODE NMSSTDCALL _oamDeleteBoard( const char *szName );
OAM_ERRCODE NMSSTDCALL _oamAddDetectedBoard( const char *szName );
OAM_ERRCODE NMSSTDCALL _oamOpenObject( HOAMCLIENT hClient, const char *szName, HMOBJ *phObject, DWORD dwMode );
OAM_ERRCODE NMSSTDCALL _oamCloseObject( HMOBJ hObject );
OAM_ERRCODE NMSSTDCALL _oamSetKeyword( HMOBJ hObject, const char *szKeyword, const char *szValue );
OAM_ERRCODE NMSSTDCALL _oamGetKeyword( HMOBJ hObject, const char *szKeyword, char *szValue, DWORD dwValueSize );
OAM_ERRCODE NMSSTDCALL _oamGetQualifier( HMOBJ hObject, const char *szKeyword, const char *szQualifier, char *szValue, DWORD dwValueSize );

OAM_ERRCODE NMSSTDCALL _oamDetectBoards();
OAM_ERRCODE NMSSTDCALL _oamStartBoard( const char *szName, DWORD dwOptions );
OAM_ERRCODE NMSSTDCALL _oamStopBoard( const char *szName, DWORD dwOptions );
OAM_ERRCODE NMSSTDCALL _oamTestBoard( const char *szName, DWORD dwOptions );

OAM_ERRCODE NMSSTDCALL _oamBoardEnum( int ixBoard, char *szName, DWORD dwNameSize );
OAM_ERRCODE NMSSTDCALL _oamBoardLookupByNumber( DWORD dwNumber, char *szName, DWORD dwNameSize );
OAM_ERRCODE NMSSTDCALL _oamBoardLookupByDriverIDs( const char *szDriverName, const char *szDriverBoardID, char *szName, DWORD dwNameSize );
OAM_ERRCODE NMSSTDCALL _oamBoardLookupByBusSlot( DWORD dwBus, DWORD dwSlot, char *szName, DWORD dwNameSize );
OAM_ERRCODE NMSSTDCALL _oamBoardLookupByIOAddress( DWORD dwIOAddress, char *szName, DWORD dwNameSize );
OAM_ERRCODE NMSSTDCALL _oamBoardLookupBySerialNumber( const char *szSerialNumber, char *szName, DWORD dwNameSize );
OAM_ERRCODE NMSSTDCALL _oamBoardLookupByProduct( const char *szProduct, char *szName, DWORD dwNameSize );
OAM_ERRCODE NMSSTDCALL _oamBoardGetNumber( const char *szName, DWORD *pdwNumber );
OAM_ERRCODE NMSSTDCALL _oamBoardGetDriverIDs( const char *szName, char *szDriverName, DWORD dwDriverNameSize, char *szDriverBoardID, DWORD dwDriverBoardIDSize );
OAM_ERRCODE NMSSTDCALL _oamBoardGetBusSlot( const char *szName, DWORD *pdwBus, DWORD *pdwSlot );
OAM_ERRCODE NMSSTDCALL _oamBoardGetIOAddress( const char *szName, DWORD *pdwIOAddress );
OAM_ERRCODE NMSSTDCALL _oamBoardGetSerialNumber( const char *szName, char *szSerialNumber, DWORD dwSerialNumberSize );
OAM_ERRCODE NMSSTDCALL _oamBoardGetProduct( const char *szName, char *szProduct, DWORD dwProductSize );

// Provider functions - hidden Board ID Database calls.

OAM_ERRCODE NMSSTDCALL _oamBoardGetAutoStartEnabled( const char *szName, DWORD *pdwAutoStartEnabled );
OAM_ERRCODE NMSSTDCALL _oamBoardGetAutoStopEnabled( const char *szName, DWORD *pdwAutoStopEnabled );

// Provider functions - lower level database direct access.

OAM_ERRCODE NMSSTDCALL _oamDbOpenObject( const char *szName, HMOBJ *phObject, DWORD dwOpenMode );
OAM_ERRCODE NMSSTDCALL _oamDbCloseObject( HMOBJ hObject );
OAM_ERRCODE NMSSTDCALL _oamDbGetProviderMode( HMOBJ hObject, int *pbOn );
OAM_ERRCODE NMSSTDCALL _oamDbSetProviderMode( HMOBJ hObject, int bOn );
OAM_ERRCODE NMSSTDCALL _oamDbSetKeyword( HMOBJ hObject, const char *szKeyword, const char *szValue );
OAM_ERRCODE NMSSTDCALL _oamDbGetKeyword( HMOBJ hObject, const char *szKeyword, char *szValue, DWORD dwValueSize );
OAM_ERRCODE NMSSTDCALL _oamDbRemoveKeyword( HMOBJ hObject, const char *szKeyword );
OAM_ERRCODE NMSSTDCALL _oamDbSetQualifier( HMOBJ hObject, const char *szKeyword, const char *szQualifier, const char *szValue );
OAM_ERRCODE NMSSTDCALL _oamDbGetQualifier( HMOBJ hObject, const char *szKeyword, const char *szQualifier, char *szValue, DWORD dwValueSize );
OAM_ERRCODE NMSSTDCALL _oamDbRemoveQualifier( HMOBJ hObject, const char *szKeyword, const char *szQualifier );
OAM_ERRCODE NMSSTDCALL _oamDbEnumObjects( int ixObject, char *szName, DWORD dwNameSize );
OAM_ERRCODE NMSSTDCALL _oamDbEnumKeywords( HMOBJ hObject, int ixKeyword, char *szKeyword, DWORD dwKeywordSize );

#ifdef __cplusplus
} // extern "C"
#endif

#endif // __super_h__

