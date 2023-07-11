/*****************************************************************************
*                                  HSWDEF.H
*
*  This is the include file for the HotSwap OAM EMC.
*
*****************************************************************************/
#ifndef __HSWDEF_H__
#define __HSWDEF_H__

#ifndef CTADEF_INCLUDED
#include <ctadef.h>
#endif

#ifdef __cplusplus
    extern "C"
    {
#endif

#define  HSW_SVCID   0x4011

/*-----------------------------------------------------------------------------
  HSW Event Codes.
    - These codes are constructed using the HSW_SVCID, the CT Access
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

#define HSWEVN_BOARD_READY          0x40112001
#define HSWEVN_REMOVAL_REQUESTED    0x40112002
#define HSWEVN_BOARD_OFFLINE        0x40112003
#define HSWEVN_BOARD_REMOVED        0x40112004
#define HSWEVN_BOARD_INSERTED       0x40112005
#define HSWEVN_ONLINE_PENDING       0x40112006
#define HSWEVN_PCI_CONFIG_FAILED    0x40112007
#define HSWEVN_PREPARATION_FAILED   0x40112008

/*-----------------------------------------------------------------------------
  HSW Reason Codes. 
    - HSW reason codes for events defined above.  These values are to be 
      utilized in the "value" member of the event structure, so that an 
      application can determine why an event occurred.
    - These codes are constructed using the HSW_SVCID, the CT Access
      CTA_CODE_REASON id, and a 1-based sequence number. The formula is
        REASONCODE = ((HSW_SVCID<<16) | (CTA_CODE_REASON | SEQUENCE))
    - The actual reason codes are "hardcoded" for source browsing purposes.
  ---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
  HSW Error codes. 
    - These codes are constructed using the HSW_SVCID, the CT Access
      CTA_CODE_ERROR id, and a 1-based sequence number. The formula is
         ERRORCODE = ((HSW_SVCID<<16) | (CTA_CODE_ERROR | SEQUENCE))  
    - The actual error codes are "hardcoded" for source browsing purposes.
  ---------------------------------------------------------------------------*/

#define HSWERR_FAILURE              0x40110001
#define HSWERR_NO_RESOURCES         0x40110002
#define HSWERR_INVALID_BUS          0x40110003
#define HSWERR_NOT_FOUND            0x40110004

#ifdef __cplusplus
    }
#endif

#endif /* __HSWDEF_H__ */

