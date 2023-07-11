/*******************************************************************************
*                                  HSFDEF.H
*
*  Header for API to functional device driver (AG native interface).
*
*
* Copyright (c) 1998  Natural MicroSystems Corp.  All rights reserved.
*******************************************************************************/
#ifndef __HSFDEF_H__
#define __HSFDEF_H__

#include "hscommon.h"

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE (!SUCCESS)
#endif

/* Indexed by physical slot */

typedef void *HSF_HANDLE;


#define HSFERR_FATAL                   -100
#define HSFERR_BAD_PARAMETERS          -101
#define HSFERR_OUT_OF_MEMORY           -102
#define HSFERR_OUT_OF_RESOURCES        -103
#define HSFERR_DRIVER_OPEN_FAILED      -104
#define HSFERR_DRIVER_CLOSE_FAILED     -105
#define HSFERR_WRONG_DRIVER_VERSION    -106
#define HSFERR_INVALID_STATE           -107
#define HSFERR_DEVICE_ERROR            -108
#define HSFERR_RELEASE_MUX_HANDLE      -109
#define HSFERR_CREATE_MUX_HANDLE       -110
#define HSFERR_STRUCTURE_MISMATCH      -111
#define HSFERR_INCONSISTENT_PARMS      -112
#define HSFERR_NULL_BUFADDR            -114
#define HSFERR_BAD_HANDLE              -115

/* Hot swap service primitives */

#ifdef __cplusplus
extern "C" {
#endif

extern DWORD hsfInitialize      ( HSF_HANDLE   *hsf_handle );
extern DWORD hsfClose           ( HSF_HANDLE   hsf_handle );

extern DWORD hsfGetDriverName   (char * psz_driverName);

extern DWORD hsfRegisterEvent   ( HSF_HANDLE   hsf_handle,
                                  PCI_SLOT     slot_number,  
                                  MUX_HANDLE   event );

extern DWORD hsfStopDeviceInstance  ( HSF_HANDLE hsf_handle,
                                      PCI_SLOT   slot_number );

extern DWORD hsfStartDeviceInstance ( HSF_HANDLE hsf_handle,
                                      PCI_SLOT   slot_number );

extern DWORD hsfEnableOpeningChannels ( HSF_HANDLE hsf_handle,
                                        PCI_SLOT   slot_number );
 
extern DWORD hsfDisableOpeningChannels ( HSF_HANDLE hsf_handle,
                                         PCI_SLOT   slot_number );

extern DWORD hsfQueryDeviceState ( HSF_HANDLE hsf_handle,
                                   PCI_SLOT   slot_number,
                                   DWORD * state ); 

extern DWORD hsfQueryIdentDataBySlot ( HSF_HANDLE   hsf_handle,
                                       PCI_SLOT     pci_bus_device,
                                       IDENT_DATA  *ident_data_ptr);

extern DWORD hsfQuerySlotByIdentData ( HSF_HANDLE   hsf_handle,
                                       IDENT_DATA  *p_identData,
                                       PCI_SLOT    *pci_bus_device_ptr);


#ifdef __cplusplus
}
#endif


#endif /* __HSFDEF_H__ */

