/*****************************************************************************
*                                  HSCommon.h
*
*  This header contains common Hot Swap stuff
*
*
* Copyright (c) 1997, 1998  Natural MicroSystems Corp.  All rights reserved.
*****************************************************************************/

#ifndef __HS_COMMON_H__
#define __HS_COMMON_H__

#include "nmstypes.h"

#define  DRIVER_NAME_SIZE  256
#define  DEVICE_NAME_SIZE  256

typedef struct
{
    DWORD  dw_param;
    char   driver_name [DRIVER_NAME_SIZE];
    char   device_name [DEVICE_NAME_SIZE];
} IDENT_DATA;

typedef struct
{   /* device identification structure */
    DWORD       vendor_id;               /* vendor id                         */
    DWORD       device_id;               /* device id                         */
    DWORD       subsys_vendor_id;        /* subsystem vendor id               */
    DWORD       subsys_id;               /* subsystem id                      */
    DWORD       hs_csr;                  /* hot swap control register         */
                                         /* according to hot swap spec        */
                                         /* HS_CSR is byte                    */
    IDENT_DATA  ident_data;              /* Driver specific data for the slot */
} HS_BOARD_INFO;


/* HS_EVENT_HANDLE must be defined for different operating systems */

#ifndef HS_EVENT_HANDLE
  #ifdef _Solaris64_
    #define HS_EVENT_HANDLE             unsigned long
  #else
    #define HS_EVENT_HANDLE             MUX_HANDLE
  #endif /* _Solaris64_ */
#endif

/* extract PCI bus, device and function number from PCI_SLOT structure */
#define HS_GET_PCI_BUS(pci_slot)        (((unsigned short)pci_slot)>>8)
#define HS_GET_PCI_DEVICE(pci_slot)     ((pci_slot & 0x0f8)>>3)
#define HS_GET_PCI_FUNCTION(pci_slot)   (pci_slot & 0x07)
#define HS_GET_PCI_SLOT(bus, device, function) (((bus&0xFF)<<8)|((device&0x1F)<<3)|(function&0x07))


typedef DWORD PCI_SLOT;         /* pci slot structure */

#endif /* __HS_COMMON_H__ */

