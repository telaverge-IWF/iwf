/***********************************************************************
*  File - piinterface.h
*
*  Description -  interface to OAM Supervisor
*
*  History
*
*  Copyright (c) 1999  Natural MicroSystems Corp.  All rights reserved.
***********************************************************************/
#ifndef __PiInterface_H__
#define __PiInterface_H__
  
#include "nmstypes.h"

#define OAMEVN_REPORT           0x40002002
#define OAMEVN_ALERT            0x40002001


// Plug In error code has format 0x400001xx
#define PLUGIN_INIT_FAIL        0x40000101
#define PLUGIN_EXIT_FAIL        0x40000102
#define NOT_SUPPORTED_WARNING   0x40000103
#define AUTO_DETECT_BOARD_FAIL  0x40000104
#define CREATE_BOARD_FAIL       0x40000105
#define DESTORY_BOARD_FAIL      0x40000106
#define GET_BOARD_KEYWORD_FAIL  0x40000107
#define SET_BOARD_KEYWORD_FAIL  0x40000108
#define GET_QUALIFIER_FAIL      0x40000109
#define OPEN_OBJECT_FAIL        0x4000010A
#define CLOSE_OBJECT_FAIL       0x4000010B
#define START_BOARD_FAIL        0x4000010C
#define STOP_BOARD_FAIL         0x4000010D
#define BOARD_SELFTEST_FAIL     0x4000010E
#define BOARD_SELFTEST_INVALID  0x4000010F
#define SEND_BUFFER_FAIL        0x40000110
  
// the strings of Name and Message will be cascaded to the end of
// OAM_MSG, the MsgSize = sizeof(OAM_MSG) + sizeof(Name) + sizeof(Message)
  
// This will be defined in super.h
/******************************
typedef struct oam_msg_tag
{
    DWORD MsgSize;
    DWORD Code;
    DWORD Severity;
    DWORD NameOffset;
    DWORD MsgOffset;
} OAM_MSG;
********************************/
extern "C"
{
    DWORD Init( const char *szName);
    DWORD Exit();
    DWORD DetectBoards();
    DWORD CreateBoard( const char *szName, const char *szProduct );
    DWORD DestroyBoard( const char *szName );
    DWORD OpenObject( UINTPTR h, DWORD dwOpenMode );
    DWORD CloseObject( UINTPTR h );
    DWORD SetKeyword( UINTPTR h, const char *szKeyword, const char *szValue );
    DWORD GetKeyword( UINTPTR h, const char *szKeyword,
    char *szValue, DWORD dwValueSize );
    DWORD GetQualifier( UINTPTR h, const char *szKeyword, const char *szQualifier,
    char *szValue, DWORD dwValueSize );
    DWORD StartBoard( const char *szName );
    DWORD StopBoard( const char *szName );
    DWORD TestBoard( const char *szName, DWORD dwOptions );
    DWORD SendBuffer( const char *szName, const BYTE *pbBuf, DWORD dwBufSize );
};
  
  
  
#endif

