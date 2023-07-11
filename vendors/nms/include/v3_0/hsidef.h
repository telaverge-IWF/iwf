/*****************************************************************************
*                                  HSIDEF.H
*
*  This is the include file for the Hot Swap Manager (HSI) API.
*
*****************************************************************************/

#ifndef __HSIDEF_H__
#define __HSIDEF_H__

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

/*====== COMMON DEFINES AND STRUCTURES =====================================*/

#define HSI_SVCID                        0x11

/*-----------------------------------------------------------------------------
 Events                                                                  
-----------------------------------------------------------------------------*/

#define HSIEVN_BOARD_READY               (0x2001|(HSI_SVCID<<16))
#define HSIEVN_REMOVAL_REQUESTED         (0x2002|(HSI_SVCID<<16))

/*-----------------------------------------------------------------------------
 General Errors
-----------------------------------------------------------------------------*/
#define HSIERR_INVALID_COMMAND           (0x0000|(HSI_SVCID<<16))
#define HSIERR_DLL_INVALID_DEVICE        (0x0001|(HSI_SVCID<<16))
#define HSIERR_DEVICE_ERROR              (0x0002|(HSI_SVCID<<16))
#define HSIERR_NO_RESOURCES              (0x0003|(HSI_SVCID<<16))

/*-----------------------------------------------------------------------------
 Generic Errors
-----------------------------------------------------------------------------*/
#define HSIERR_UNKNOWN_ERROR             (0x0013|(HSI_SVCID<<16))

#define HSI_EVENTS()\
    _TEXTCASE_ (HSIEVN_BOARD_READY);            \
    _TEXTCASE_ (HSIEVN_REMOVAL_REQUESTED)

#define HSI_ERRORS()\
    _TEXTCASE_ (HSIERR_INVALID_COMMAND    );    \
    _TEXTCASE_ (HSIERR_DLL_INVALID_DEVICE );    \
    _TEXTCASE_ (HSIERR_DEVICE_ERROR       );    \
    _TEXTCASE_ (HSIERR_NO_RESOURCES       );    \
    _TEXTCASE_ (HSIERR_UNKNOWN_ERROR      )


#ifdef __cplusplus
    }
#endif

#endif
