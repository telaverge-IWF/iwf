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
 *  ID: $Id: itu-wait_out_rlc_itu_99.c,v 1.2 2006/01/09 06:44:52 omayor Exp $
 *
 *  LOG: $Log: itu-wait_out_rlc_itu_99.c,v $
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
 * Functions for handling messages in the Wait_Outgoing_RLC state for ITU_99.
 */



/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an PRI received in the WAIT_OUTGOING_RLC state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name           Date          Reference               Description
 *  ----------------------------------------------------------------------------
 *  Ramesh KV   01-05-2005   AUD-ETS-SDS-01-v1.0.doc    Support for ITU 99. 
 *
 ****************************************************************************/
static void
__ISUP_Received_PRI(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                          ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward PRI  appropriately */
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received PRI in WAIT_OUT_RLC from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Send to app */
        SPRC_SendIsupToApp_CCITT(cic_rec->vcic, msg);
    }
    else 
    {
        /* App sent REL instead of RLC: error condition. */
        ISUP_ERROR(("Received PRI in WAIT_OUT_RLC from APP, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        /* Send Error Indication to APP about dropping of Msg. */
        SPRC_SendErrorToApp_CCITT(ISUP_MSG_PRI,
                                  ITS_ISUP_UNEXP_APPMSG_WAITOUT_RLC_ERR,
                                  cic_rec);
    }
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a valid pointer to a message handler function
 *      for the WAIT_OUTGOING_RLC state, based on the msgType received.
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
 *   Name           Date          Reference               Description
 *  ----------------------------------------------------------------------------
 *  Ramesh KV   01-05-2005   AUD-ETS-SDS-01-v1.0.doc    Support for ITU 99.
 *
 ****************************************************************************/
__ISUP_MsgHandlerProc
__ISUP_GetMsgProc_WaitOutgoingRlc_ITU_99(ITS_OCTET msgType)
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

