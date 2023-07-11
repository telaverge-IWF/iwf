/*****************************************************************************
*                                  HSIDEF.H
*
*  This is the include file for the Hot Swap Manager (HSI) API.
*
*****************************************************************************/
#ifndef __HSIDEF_H__
#define __HSIDEF_H__

#ifndef NMSTYPES_INCLUDED
#include <nmstypes.h>
#endif

#ifndef CTADEF_INCLUDED
#include <ctadef.h>
#endif

#include "hscommon.h"

#ifdef __cplusplus
    extern "C"
    {
#endif

/*====== COMMON DEFINES AND STRUCTURES =====================================*/
#define  HSI_SVCID   0x11

/*-----------------------------------------------------------------------------
 Events
-----------------------------------------------------------------------------*/
#define  HSIEVN_BOARD_READY         (0x2001|(HSI_SVCID<<16))
#define  HSIEVN_REMOVAL_REQUESTED   (0x2002|(HSI_SVCID<<16))
#define  HSIEVN_BOARD_OFFLINE       (0x2003|(HSI_SVCID<<16))
#define  HSIEVN_BOARD_REMOVED       (0x2004|(HSI_SVCID<<16))
#define  HSIEVN_BOARD_INSERTED      (0x2005|(HSI_SVCID<<16))
#define  HSIEVN_ONLINE_PENDING      (0x2006|(HSI_SVCID<<16))
#define  HSIEVN_PCI_CONFIG_FAILED   (0x2007|(HSI_SVCID<<16))
#define  HSIEVN_PREPARATION_FAILED  (0x2008|(HSI_SVCID<<16))

/*-----------------------------------------------------------------------------
 General Errors
-----------------------------------------------------------------------------*/
#define HSIERR_NO_RESOURCES   (0x0000|(HSI_SVCID<<16))
#define HSIERR_INVALID_BUS    (0x0001|(HSI_SVCID<<16))
#define HSIERR_NOT_FOUND      (0x0002|(HSI_SVCID<<16))

/*-----------------------------------------------------------------------------
 Generic Errors
-----------------------------------------------------------------------------*/
#define HSIERR_FAILURE        (0x0013|(HSI_SVCID<<16))

/*-----------------------------------------------------------------------------
 * HSI states
 *---------------------------------------------------------------------------*/
#define HSI_STATE_NOT_PRESENT          0
#define HSI_STATE_OFFLINE              1
#define HSI_STATE_PREPARATION          2
#define HSI_STATE_PREPARATION_FAILED   3
#define HSI_STATE_RUNNING              4
#define HSI_STATE_DOWNING              5

/*-----------------------------------------------------------------------------
 * Board info structure
 *---------------------------------------------------------------------------*/
#define  BOARD_FAMILY_SIZE  DRIVER_NAME_SIZE
typedef struct
{
    DWORD   pci_slot;

    DWORD   vendor_id;        /* PCI vendor id            */
    DWORD   device_id;        /* PCI device id            */
    DWORD   subsys_vendor_id; /* PCI subsystem vendor id  */
    DWORD   subsys_id;        /* PCI subsystem id         */

    DWORD   state;            /* board state (refer to HSI state diagram)    */
    DWORD   board_id;         /* logical board number or board specific info */
    char    board_family [BOARD_FAMILY_SIZE]; /* identification string for 
                                                 board's family */
} HSI_BOARDINFO;

/*-----------------------------------------------------------------------------
  HSI Service API function prototypes.
  ---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
  Gets board's information by board's PCI location.
    Operation of this API call is synchronous.

    ctahd   :  Handle for context with running Hot Swap service.
    pci_slot:  PCI Board location returned in CTA_EVENT->value
    p_info  :  Defined HSI_BOARDINFO structure(above).
  ---------------------------------------------------------------------------*/
DWORD NMSAPI hsiGetBoardInfo (CTAHD           ctahd,
                              DWORD           pci_slot, 
                              HSI_BOARDINFO * p_info);

/*-----------------------------------------------------------------------------
  Gets board's information by board's logical number
    Operation of this API call is synchronous.

    ctahd         :  Handle for context with running Hot Swap service.
    p_board_family:  pointer to a buffer that holds board family name
    board_id      :  board's logical identification
    p_info        :  Defined HSI_BOARDINFO structure(above).
  ---------------------------------------------------------------------------*/
DWORD NMSAPI hsiGetLogicalBoardInfo (CTAHD           ctahd,
                                     char           * p_board_family, 
                                     DWORD            board_id, 
                                     HSI_BOARDINFO  * p_info);
#ifdef __cplusplus
    }
#endif

#endif /* __HSIDEF_H__ */

