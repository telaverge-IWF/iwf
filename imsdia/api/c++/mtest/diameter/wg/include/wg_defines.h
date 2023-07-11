/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: wg_defines.h,v $
 * LOG: Revision 1.1  2011/05/09 11:12:55  vkumara
 * LOG: Base line for Wg interface.
 * LOG:
 * LOG:
 * ID: $Id: wg_defines.h,v 1.1 2011/05/09 11:12:55 vkumara Exp $
 ****************************************************************************/
#ident "$Id: wg_defines.h,v 1.1 2011/05/09 11:12:55 vkumara Exp $"

#ifndef _SAMPLE_WGAPP_DEFINE
#define _SAMPLE_WGAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID            0
#define WG_INTERFACE_APP_ID    	         5
#define VENDOR_ID                        10415


/**
 * The Application Worker Queue Id for Wd interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define WG_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For WG Interface
 **/
#define WG_DE_MSG_CMD_CODE        268
#define WG_AA_MSG_CMD_CODE        265
#define WG_ST_MSG_CMD_CODE        275
#define WG_AS_MSG_CMD_CODE        274


/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to display the menu options for the
 *      respective protocol interface.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Returns the option selected.
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern int DisplayAppMenu();

/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Wd Protocol messages to
 *      the diameter stack. These will create the appropriate Wd protocol
 *      Request Command objects, populate the AVPs and sends the
 *      message to the stack.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern int SendWgDiameterEAPRequest();
extern int SendWgAARequest();
extern int SendWgSessionTerminationRequest();
extern int SendWgAbortSessionRequest();


/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Wg Protocol messages to
 *      the diameter stack. These will create the appropriate Wg protocol
 *      Answer Command objects, populate the AVPs and sends the
 *      message to the stack.
 *
 *  Input Parameters:
 *      const diameter::CommandImpl *impl: Pointer to the received Request
 *      Command, for which the Answer is to be sent.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/


extern int SendWgDiameterEAPAnswer(const diameter::CommandImpl *impl);
extern int SendWgAAAnswer(const diameter::CommandImpl *impl);
extern int SendWgSessionTerminationAnswer(const diameter::CommandImpl *impl);
extern int SendWgAbortSessionAnswer(const diameter::CommandImpl *impl);

#endif

