/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID: $Id: mab_isup_client.h,v 1.1 2005/05/25 10:13:58 mmanikandan Exp $
 *
 * LOG: $Log: mab_isup_client.h,v $
 * LOG: Revision 1.1  2005/05/25 10:13:58  mmanikandan
 * LOG: Initial Commit Multiple Application Binding.
 * LOG:
 *
 ****************************************************************************/

#ifndef MABCL_ISUP_H 
#define MABCL_ISUP_H 

#include <mab_client.h>

/* Event types between client and server */
#define MABCL_ISUP_RESERVE_CIC_REQ     0x05
#define MABCL_ISUP_UNRESERVE_CIC_REQ   0x09

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method handles reserve cic response
 *
 *  Input Parameters:
 *      handle  - ITS_HANDLE  
 *      ev    - ITS_EVENT * 
 *      reserveCic - ReserveCIC entry
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns the return value ReserveCIC Api
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
ISUP_ReceiveReserveCICIndication(ITS_HANDLE handle, ITS_EVENT *ev,
                                  MABCL_ISUP_RSV_CIC_ENTRY *reserveCic);

/*implemt: public
 ****************************************************************************
 *  Purpose:
 *      This method handles unreserveCic response
 *
 *  Input Parameters:
 *      handle  - ITS_HANDLE  
 *      ev    - ITS_EVENT * 
 *      unreserveCic - UnreserveCic Entry
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns the return value UnReserveCIC Api
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
MABCL_DLLAPI ITS_INT
ISUP_ReceiveUnReserveCICIndication(ITS_HANDLE handle, ITS_EVENT *ev,
                                   MABCL_ISUP_UNRSV_CIC_ENTRY *entry);
#endif
