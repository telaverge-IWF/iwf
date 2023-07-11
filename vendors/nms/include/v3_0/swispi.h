/*****************************************************************************
*                                  SWISPI.H
*
*  This is the include file for the Switching Manager (SWI) SPI functions
*
*  File revision: "14"
*
* Copyright (c)1996 Natural MicroSystems Corporation. All rights reserved.
*****************************************************************************/

#ifndef SWISPI_INCLUDED
#define SWISPI_INCLUDED 1

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef NMSTYPES_INCLUDED
#include <nmstypes.h>
#endif

#ifndef CTADEF_INCLUDED
#include <ctadef.h>
#endif

#ifndef SWIDEF_INCLUDED
#include <swidef.h>
#endif

typedef DWORD SWIHDX; /* Server Side Handle */

/*****************************************************************************
 SWI SPI Functions
*****************************************************************************/
DWORD NMSAPI swispiOpenSwitch( CTAHD ctahd,
                               unsigned source_svcid,
                               const char *devname,
                               unsigned swno,
                               unsigned flags,
                               SWIHDX *shx);

DWORD NMSAPI swispiCloseSwitch( CTAHD ctahd, 
                                unsigned source_svcid, 
                                SWIHDX shx );

DWORD NMSAPI swispiDisableOutput( CTAHD ctahd,
                                  unsigned source_svcid,
                                  SWIHDX shx,
                                  SWI_TERMINUS output[],
                                  unsigned count);

DWORD NMSAPI swispiGetOutputState( CTAHD ctahd,
                                   unsigned source_svcid,
                                   SWIHDX shx,
                                   SWI_TERMINUS output[],
                                   unsigned mode[],
                                   BYTE pattern[],
                                   SWI_TERMINUS input[],
                                   unsigned count);
DWORD NMSAPI swispiMakeConnection( CTAHD ctahd,
                                   unsigned source_svcid,
                                   SWIHDX shx,
                                   SWI_TERMINUS input[],
                                   SWI_TERMINUS output[],
                                   unsigned count);

DWORD NMSAPI swispiMakeFramedConnection( CTAHD ctahd,
                                         unsigned source_svcid,
                                         SWIHDX shx,
                                         SWI_TERMINUS input[],
                                         SWI_TERMINUS output[],
                                         unsigned count);

DWORD NMSAPI swispiGetSwitchCaps( CTAHD ctahd,
                                  unsigned source_svcid,
                                  SWIHDX shx,
                                  SWI_SWITCHCAPS_ARGS *args,
                                  SWI_LOCALDEV_DESC localdevs[],
                                  unsigned count);

DWORD NMSAPI swispiResetSwitch( CTAHD ctahd,
                                unsigned source_svcid,
                                SWIHDX shx);

DWORD NMSAPI swispiSampleInput( CTAHD ctahd,
                                unsigned source_svcid,
                                SWIHDX shx,
                                SWI_TERMINUS input[],
                                BYTE data[],
                                unsigned count);

DWORD NMSAPI swispiSendPattern( CTAHD ctahd,
                                unsigned source_svcid,
                                SWIHDX shx,
                                BYTE pattern[],
                                SWI_TERMINUS output[],
                                unsigned count);

/*****************************************************************************/
/* Clock Commands                                                            */
/*****************************************************************************/
DWORD NMSAPI swispiConfigBoardClock( CTAHD ctahd,
                                     unsigned source_svcid,
                                     SWIHDX shx,
                                     SWI_CLOCK_ARGS *args);

DWORD NMSAPI swispiConfigSec8KClock( CTAHD ctahd,
                                     unsigned source_svcid,
                                     SWIHDX shx,
                                     DWORD source,
                                     DWORD network );

DWORD NMSAPI swispiConfig8KRefClock( CTAHD ctahd,
                                     unsigned source_svcid,
                                     SWIHDX shx,
                                     DWORD source,
                                     DWORD network );

/*****************************************************************************/
/* Diagnostic Commands                                                       */
/*****************************************************************************/
DWORD NMSAPI swispiDisableSwitch( CTAHD ctahd,
                                  unsigned source_svcid,
                                  SWIHDX shx);

DWORD NMSAPI swispiEnableSwitch( CTAHD ctahd,
                                 unsigned source_svcid,
                                 SWIHDX shx);

DWORD NMSAPI swispiSetVerify( CTAHD ctahd,
                              unsigned source_svcid,
                              SWIHDX shx,
                              unsigned verify);

/*****************************************************************************/
/* Stream Configuration Commands                                             */
/*****************************************************************************/
DWORD NMSAPI swispiConfigStreamSpeed( CTAHD ctahd,
                                      unsigned source_svcid,
                                      SWIHDX shx,
                                      DWORD speed,
                                      DWORD streams[],
                                      DWORD count );

DWORD NMSAPI swispiGetStreamsBySpeed( CTAHD ctahd,
                                      unsigned source_svcid,
                                      SWIHDX shx,
                                      DWORD speed,
                                      DWORD streams[],
                                      unsigned max_count,
                                      unsigned *count );

/*****************************************************************************/
/* Configuration Commands                                                    */
/*****************************************************************************/
DWORD NMSAPI swispiConfigLocalStream( CTAHD ctahd,
                                      unsigned source_svcid,
                                      SWIHDX shx,
                                      SWI_LOCALSTREAM_ARGS *args,
                                      void *buffer,
                                      unsigned size );

DWORD NMSAPI swispiConfigLocalTimeslot( CTAHD ctahd,
                                        unsigned source_svcid,
                                        SWIHDX shx,
                                        SWI_LOCALTIMESLOT_ARGS *args,
                                        void *buffer,
                                        unsigned size );

DWORD NMSAPI swispiGetBoardInfo( CTAHD ctahd,
                                 unsigned source_svcid,
                                 SWIHDX shx,
                                 SWI_BOARDINFO_ARGS *args);

DWORD NMSAPI swispiGetDriverInfo( CTAHD ctahd,
                                  unsigned source_svcid,
                                  SWIHDX shx,
                                  SWI_DRIVERINFO_ARGS *args);


DWORD NMSAPI swispiGetLocalStreamInfo( CTAHD ctahd,
                                       unsigned source_svcid,
                                       SWIHDX shx,
                                       SWI_LOCALSTREAM_ARGS *args,
                                       void *buffer,
                                       unsigned size );

DWORD NMSAPI swispiGetLocalTimeslotInfo( CTAHD ctahd,
                                         unsigned source_svcid,
                                         SWIHDX shx,
                                         SWI_LOCALTIMESLOT_ARGS *args,
                                         void *buffer,
                                         unsigned size );

/*****************************************************************************/
/* Utility Commands                                                          */
/*****************************************************************************/
DWORD NMSAPI swispiCallDriver( CTAHD ctahd,
                               unsigned source_svcid,
                               SWIHDX shx,
                               DWORD command,
                               DWORD *args,
                               DWORD size,
                               DWORD *errorcode);

DWORD NMSAPI swispiGetLastError( CTAHD ctahd,
                                 unsigned source_svcid,
                                 SWIHDX shx,
                                 DWORD *errorcode);

#ifdef __cplusplus
    }
#endif

#endif
