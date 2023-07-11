/*****************************************************************************
*                                  SWIDEF.H
*
*  This is the include file for the Switching Manager (SWI) API.
*
*
* Copyright (c) 1996-2002 NMS Communications.  All rights reserved.
*****************************************************************************/

#ifndef SWIDEF_INCLUDED
#define SWIDEF_INCLUDED 1

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef NMSTYPES_INCLUDED
#include "nmstypes.h"
#endif

#ifndef CTADEF_INCLUDED
#include "ctadef.h"
#endif

#include "mvip95.h"

/*====== COMMON DEFINES AND STRUCTURES =====================================*/

#define SWI_SVCID 4
typedef DWORD SWIHD;

/* Other useful constants */
#define SWI_A_BIT_ON  0x0008
#define SWI_A_BIT_OFF 0x0080
#define SWI_B_BIT_ON  0x0004
#define SWI_B_BIT_OFF 0x0040

#define SWI_DT_D4     0     /* Values for CONFIG_DT 'frame' parameter */
#define SWI_DT_ESF    1
#define SWI_DT_CEPT   2

#define SWI_DT_AMI     0    /* Values for CONFIG_DT 'code' parameter */
#define SWI_DT_B8ZS    1
#define SWI_DT_AMI_ZCS 2
#define SWI_DT_HDB3    3    /* E1 Only */


typedef struct
{
    DWORD bus;
    DWORD stream;
    DWORD timeslot;
} SWI_TERMINUS;

/*-----------------------------------------------------------------------------
 Opening and closing switch handles
-----------------------------------------------------------------------------*/
#define SWI_MVIP90 0x1
#define SWI_ENABLE_RESTORE  0x4
DWORD NMSAPI swiOpenSwitch( CTAHD ctahd,
                            const char *devname,
                            unsigned swno,
                            unsigned flags,
                            SWIHD *swihd );

DWORD NMSAPI swiCloseSwitch( SWIHD swihd );

/*-----------------------------------------------------------------------------
 Switching Functions
-----------------------------------------------------------------------------*/

DWORD NMSAPI swiDisableOutput( SWIHD swihd,
                               SWI_TERMINUS output[],
                               unsigned count );

DWORD NMSAPI swiGetOutputState( SWIHD swihd,
                                SWI_TERMINUS output[],
                                unsigned mode[],
                                BYTE pattern[],
                                SWI_TERMINUS input[],
                                unsigned count );

DWORD NMSAPI swiMakeConnection( SWIHD swihd,
                                SWI_TERMINUS input[],
                                SWI_TERMINUS output[],
                                unsigned count );

DWORD NMSAPI swiMakeFramedConnection( SWIHD swihd,
                                      SWI_TERMINUS input[],
                                      SWI_TERMINUS output[],
                                      unsigned count );

typedef struct
{
    DWORD timeslots;
    DWORD deviceid;
} SWI_LOCALDEV_DESC;

typedef struct
{
    DWORD dvrrevision;
    DWORD domain;
    DWORD routing;
    DWORD blocking;
    DWORD swstandard;
    DWORD swstdrevision;
    DWORD hwstandard;
    DWORD hwstdrevision;
    DWORD numlocalstreams;
} SWI_SWITCHCAPS_ARGS;

DWORD NMSAPI swiGetSwitchCaps( SWIHD swihd,
                               SWI_SWITCHCAPS_ARGS *args,
                               SWI_LOCALDEV_DESC localdevs[],
                               unsigned count);

DWORD NMSAPI swiResetSwitch( SWIHD swihd );

DWORD NMSAPI swiSampleInput( SWIHD swihd,
                             SWI_TERMINUS input[],
                             BYTE data[],
                             unsigned count );

DWORD NMSAPI swiSendPattern( SWIHD swihd,
                             BYTE pattern[],
                             SWI_TERMINUS output[],
                             unsigned count );

/*----------------------------------------------------------------------------
 Clock Configuration functions
----------------------------------------------------------------------------*/
typedef struct
{
    DWORD size;
    DWORD clocktype;
    DWORD clocksource;
    DWORD network;
    union
    {
        struct
        {
            DWORD mc1clockmode;
            DWORD autofallback;
        } mc1;  /* only for MC1 */

        /* Added for H.110 */
        struct
        {
            DWORD clockmode;
            DWORD autofallback;
            DWORD netrefclockspeed;
            DWORD fallbackclocksource;
            DWORD fallbacknetwork;
        }h100; /* only for h100 */

    } ext; /* extension, specific parts for each board, based on
              clocktype */
} SWI_CLOCK_ARGS;
/****************************************************
    Added for clock query
*****************************************************/

typedef struct
{
    DWORD size;
    DWORD clocktype;
    DWORD clocksource;
    DWORD network;
    union
    {
        struct
        {
            DWORD mc1clockmode;
            DWORD autofallback;
            DWORD fallbackoccurred;
        } mc1;  /* only for MC1 */

        struct
        {
            DWORD clockmode;
            DWORD autofallback;
            DWORD fallbackoccurred;
            DWORD clockstatus_a;
            DWORD clockstatus_b;
            DWORD clockstatus_netref1;
            DWORD clockstatus_netref2;
        } h100; /* only for h100 */

    } ext; /* extension, specific parts for each board, based on
              clocktype */
} SWI_QUERY_CLOCK_ARGS;

typedef struct
{
    DWORD size;
    DWORD network;
    DWORD netrefclockmode;
    DWORD netrefclockspeed;

} SWI_NETREF_CLOCK_ARGS;


typedef struct
{
    DWORD size;
    DWORD referencesource;
    DWORD network;
    DWORD status;
    DWORD statusinfo;

} SWI_QUERY_TIMING_REFERENCE_ARGS ;


DWORD NMSAPI swiConfigNetrefClock( SWIHD swihd,
                                   SWI_NETREF_CLOCK_ARGS *args );

DWORD NMSAPI swiGetBoardClock( SWIHD swihd,
                               DWORD clocktype,
                               SWI_QUERY_CLOCK_ARGS *args,
                               unsigned size );

DWORD NMSAPI swiGetTimingReference( SWIHD swihd,
                                    DWORD referencesource,
                                    DWORD network,
                                    SWI_QUERY_TIMING_REFERENCE_ARGS *args,
                                    unsigned size );

DWORD NMSAPI swiConfigBoardClock( SWIHD swihd,
                                  SWI_CLOCK_ARGS *args );

DWORD NMSAPI swiConfigSec8KClock( SWIHD swihd,
                                  DWORD source,
                                  DWORD network );

DWORD NMSAPI swiConfig8KRefClock( SWIHD swihd,
                                  DWORD source,
                                  DWORD network );

/*----------------------------------------------------------------------------
 Diagnostic functions
----------------------------------------------------------------------------*/
DWORD NMSAPI swiDisableSwitch( SWIHD swihd );

DWORD NMSAPI swiEnableSwitch( SWIHD swihd );

DWORD NMSAPI swiSetVerify( SWIHD swihd,
                           unsigned verify );

/*-----------------------------------------------------------------------------
 Stream Configuration functions
-----------------------------------------------------------------------------*/
DWORD NMSAPI swiConfigStreamSpeed( SWIHD swihd,
                                   DWORD speed,
                                   DWORD streams[],
                                   DWORD count );

DWORD NMSAPI swiGetStreamsBySpeed( SWIHD swihd,
                                   DWORD speed,
                                   DWORD streams[],
                                   unsigned max_count,
                                   unsigned *count );

/*----------------------------------------------------------------------------
 Configuration functions
----------------------------------------------------------------------------*/
typedef struct
{
    DWORD localstream;
    DWORD deviceid;
    DWORD parameterid;
} SWI_LOCALSTREAM_ARGS;

DWORD NMSAPI swiConfigLocalStream( SWIHD swihd,
                                   SWI_LOCALSTREAM_ARGS *args,
                                   void *buffer,
                                   unsigned size );

DWORD NMSAPI swiGetLocalStreamInfo( SWIHD swihd,
                                    SWI_LOCALSTREAM_ARGS *args,
                                    void *buffer,
                                    unsigned size );

typedef struct
{
    DWORD localstream;
    DWORD localtimeslot;
    DWORD deviceid;
    DWORD parameterid;
} SWI_LOCALTIMESLOT_ARGS;

DWORD NMSAPI swiConfigLocalTimeslot( SWIHD swihd,
                                     SWI_LOCALTIMESLOT_ARGS *args,
                                     void *buffer,
                                     unsigned size );

DWORD NMSAPI swiGetLocalTimeslotInfo( SWIHD swihd,
                                      SWI_LOCALTIMESLOT_ARGS *args,
                                      void *buffer,
                                      unsigned size );

typedef struct
{
    DWORD size;
    BYTE description [80];
    BYTE revision [16];
    BYTE date [12];
    BYTE vendor [80];
    BYTE serialnumber [80];
    DWORD boardid;
    DWORD base_port_address;
} SWI_BOARDINFO_ARGS;

DWORD NMSAPI swiGetBoardInfo( SWIHD swihd,
                              SWI_BOARDINFO_ARGS *args,
                              unsigned size);

typedef struct
{
    DWORD size;
    BYTE description [80];
    BYTE revision [16];
    BYTE date [12];
    BYTE vendor [80];
} SWI_DRIVERINFO_ARGS;

DWORD NMSAPI swiGetDriverInfo( SWIHD swihd,
                               SWI_DRIVERINFO_ARGS *args,
                               unsigned size);

/*-----------------------------------------------------------------------------
 Utility functions
-----------------------------------------------------------------------------*/
DWORD NMSAPI swiCallDriver( SWIHD swihd,
                            DWORD command,
                            DWORD *args,
                            DWORD size,
                            DWORD *errorcode );

DWORD NMSAPI swiGetLastError( SWIHD swihd, DWORD *errorcode );

/*----------------------------------------------------------------------------
 Switching Manager Error Codes
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 General Errors
----------------------------------------------------------------------------*/
#define SWIERR_INVALID_COMMAND           0x40000
#define SWIERR_DLL_INVALID_DEVICE        0x40001
#define SWIERR_DEVICE_ERROR              0x40002
#define SWIERR_NO_RESOURCES              0x40003

/*-----------------------------------------------------------------------------
 Parameter Errors
-----------------------------------------------------------------------------*/
#define SWIERR_INVALID_STREAM            0x40004
#define SWIERR_INVALID_TIMESLOT          0x40005
#define SWIERR_MISSING_PARAMETER         0x40006
#define SWIERR_INVALID_CLOCK_PARM        0x40007
#define SWIERR_INVALID_SPEED             0x40008
#define SWIERR_NOT_CONFIGURABLE          0x40009
#define SWIERR_INVALID_MODE              0x4000A
#define SWIERR_INVALID_MINOR_SWITCH      0x4000B
#define SWIERR_INVALID_PARAMETER         0x4000C
#define SWIERR_UNSUPPORTED_MODE          0x4000D

/*-----------------------------------------------------------------------------
 Switch Errors
-----------------------------------------------------------------------------*/
#define SWIERR_NO_PATH                   0x4000E
#define SWIERR_SWITCH_VERIFY_ERROR       0x4000F
#define SWIERR_INTERNAL_CONFLICT         0x40010
#define SWIERR_CONNECTION_NOT_SUPPORTED  0x40011
#define SWIERR_MVIP_BUS_NOT_ENABLED      0x40012

/*-----------------------------------------------------------------------------
 Generic Errors
-----------------------------------------------------------------------------*/
#define SWIERR_UNKNOWN_ERROR             0x40013


#ifdef __cplusplus
    }
#endif

#endif

