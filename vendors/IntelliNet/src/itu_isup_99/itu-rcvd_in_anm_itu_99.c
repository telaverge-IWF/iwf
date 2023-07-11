/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 *  ID: $Id: itu-rcvd_in_anm_itu_99.c,v 1.2 2006/01/09 06:44:52 omayor Exp $
 *
 *  LOG: $Log: itu-rcvd_in_anm_itu_99.c,v $
 *  LOG: Revision 1.2  2006/01/09 06:44:52  omayor
 *  LOG: Added support for ITU ISUP 99.(skatta)
 *  LOG:
 *    
 *****************************************************************************/

#undef ANSI
#undef CCITT
#define CCITT

#include <stdlib.h>
#include <string.h>

#include <its.h>

#include <itu/isup.h>
#include <isup_variants.h>

#include "isup_intern.h"
#include "itu-isup_99_intern.h"

/*
 * Functions for handling messages in the Rcvd_Incoming_ANM state for ITU93 
 * variant. 
 */


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a valid pointer to a message handler function
 *      for the RCVD_INCOMING_ANM state, based on the msgType received.
 *
 *  Input Parameters:
 *      msgType: the type of the message received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Pointer to a message handler function.
 *   
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name           Date         Reference                 Description
 *  ----------------------------------------------------------------------------
 *  Ramesh KV   01-05-2005    AUD-ETS-SDS-01-v1.0.doc   Support for ITU 99
 *
 ****************************************************************************/
__ISUP_MsgHandlerProc
__ISUP_GetMsgProc_RcvdIncomingAnm_ITU_99(ITS_OCTET msgType)
{
    switch(msgType)
    {
    case ISUP_MSG_APM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_APM;
    case ISUP_MSG_PRI:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_PRI;
    case ISUP_MSG_SDM:
    default:
        return (__ISUP_MsgHandlerProc)(NULL);
    }
}



