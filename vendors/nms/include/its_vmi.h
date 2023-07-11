/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: its_vmi.h,v 9.1 2005/03/23 12:55:43 cvsadmin Exp $
 *
 * LOG: $Log: its_vmi.h,v $
 * LOG: Revision 9.1  2005/03/23 12:55:43  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:55:04  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:51  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:54  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2001/10/06 23:30:33  mmiers
 * LOG: Finish the MTP2 API.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 20:35:47  mmiers
 * LOG: Consolidate the NMS libraries.  Only the root library so far.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:34  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:07  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:10:43  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.2  2000/06/16 15:20:54  hxing
 * LOG: Removed redefinition of VMI_ASYNCHRONOUS_SRC and VMI_SYNCHRONOUS_SRC
 * LOG:
 * LOG: Revision 1.1  2000/05/11 22:07:10  randresol
 * LOG: Creation of VMI Interface on top of NMS HMI library
 * LOG: to support redundancy.
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_VMI_H
#define _ITS_VMI_H

#include <its_ss7_trans.h>

#define VMI_MAX_INSTANCE       5

/********************************************  
 *******       HMI Primitive Tag   
 ********************************************/

#define VMI_BACKUP             (0x01U)
#define VMI_HALT_BOARD         (0x02U)
#define VMI_LOAD_BOARD         (0x03U)
#define VMI_PRIMARY            (0x04U)
#define VMI_RESET              (0x05U)
#define VMI_SHUTDOWN           (0x06U)
#define VMI_STANDALONE         (0x07U)
#define VMI_STATUS_REQUEST     (0x08U)

#define VMI_PRIMITIVE_FLAG     (0x0FU)  


/*********************************************
 *******     HMI Return Codes
 *********************************************/

#define VMI_SUCCESS           (0x11U)
#define VMI_ERR_CLOSED        (0x12U)
#define VMI_ERR_BADCMD        (0x13U)
#define VMI_ERR_TIMEOUT       (0x14U)
#define VMI_ERR_INVHANDLE     (0x15U)
#define VMI_ERR_NOMEM         (0x16U)
#define VMI_ERR_REFUSED       (0x17U)
#define VMI_ERR_INTERROR      (0x18U)

/**********************************************
 ************* HMI Events            
 **********************************************/

#define VMI_EVN_ISOLATED      (0x20U)
#define VMI_EVN_CONNECTED     (0x21U)
#define VMI_EVN_NOWPRIMARY    (0x22U)
#define VMI_EVN_BRDDEAD       (0x23U)
#define VMI_EVN_TASKDEAD      (0x24U)
#define VMI_EVN_HALTED        (0x25U)
#define VMI_EVN_LOADING       (0x26U)
#define VMI_EVN_NOWBACKUP     (0x27U)
#define VMI_EVN_NOWSTANDALONE (0x28U)
#define VMI_EVN_STARTING      (0x29U)
#define VMI_EVN_CONFLICT      (0x2AU)
#define VMI_EVN_SERVICE_DOWN  (0x2BU)

#ifdef __cplusplus
extern "C"
{
#endif
#if NMS_VERSION < 3000
extern int VMI_SendPrimitive(ITS_UINT mask, ITS_USHORT instance);
#endif
/* Asynchronous event are sent to all registered transports) */
extern int VMI_RegisterInstance(ITS_USHORT instance);
/* To deregister a transport */
extern int  VMI_DeregisterInstance(ITS_USHORT instance);
extern int  VMI_Initialize(ITS_Class newClass);
extern void VMI_Terminate(ITS_Class oldClass);

#ifdef __cplusplus
}
#endif


#endif
