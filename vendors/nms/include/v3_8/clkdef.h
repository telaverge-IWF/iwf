/*****************************************************************************
*                                  CLKDEF.H
*
*  This is the include file for the Clock Manager.
*
*****************************************************************************/
#ifndef __CLKDEF_H__
#define __CLKDEF_H__

#ifndef NMSTYPES_INCLUDED
#include <nmstypes.h>
#endif

#ifndef CTADEF_INCLUDED
#include <ctadef.h>
#endif

#ifndef OAMDEF_INCLUDED
#include <oamdef.h>
#endif

#ifdef __cplusplus
    extern "C"
    {
#endif

/*====== COMMON DEFINES AND STRUCTURES =====================================*/
#define  CLK_SVCID   (OAM_SVCID | 0x01)

/*-----------------------------------------------------------------------------
 Events
-----------------------------------------------------------------------------*/

/* ((CLK_SVCID<<16)|CTA_CODE_EVENT|0x01) */
#define  CLKEVN_CONFIGURED           0x40012001
#define  CLKEVN_INVALID_CONFIG_DATA  0x40012002
#define  CLKEVN_CONFIG_FAILED        0x40012003
#define  CLKEVN_OPEN_OAM_FAILED      0x40012004
#define  CLKEVN_OPEN_SWITCH_FAILED   0x40012005
#define  CLKEVN_INFO                 0x40012006
#define  CLKEVN_NETREF_CONFIG_FAILED 0x40012007

/*-----------------------------------------------------------------------------
 Errors
-----------------------------------------------------------------------------*/
#define CLKERR_NO_RESOURCES   (0x0000|(CLK_SVCID<<16))
#define CLKERR_NOT_FOUND      (0x0001|(CLK_SVCID<<16))
#define CLKERR_FAILURE        (0x0002|(CLK_SVCID<<16))

#ifdef __cplusplus
    }
#endif

#endif /* __CLKDEF_H__ */

