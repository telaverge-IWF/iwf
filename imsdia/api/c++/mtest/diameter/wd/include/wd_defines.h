/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2007 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: wd_defines.h,v $
 * LOG: Revision 3.3  2011/04/18 11:37:03  vkumara
 * LOG: Wd interface
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:13  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/04/26 09:32:26  hbhatnagar
 * LOG: Baseline Demo Application for Wd Interface.
 * LOG:
 * ID: $Id: wd_defines.h,v 3.3 2011/04/18 11:37:03 vkumara Exp $
 ****************************************************************************/
#ident "$Id: wd_defines.h,v 3.3 2011/04/18 11:37:03 vkumara Exp $"

#ifndef _SAMPLE_WDAPP_DEFINE
#define _SAMPLE_WDAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID            0
#define WD_INTERFACE_APP_ID    	         1

/**
 * The Application Worker Queue Id for Wd interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define WD_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For WD Interface
 **/
#define WD_DE_MSG_CMD_CODE        268
#define WD_AA_MSG_CMD_CODE        265
#define WD_RA_MSG_CMD_CODE        258
#define WD_ST_MSG_CMD_CODE        275
#define WD_AS_MSG_CMD_CODE        274


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
extern int SendWdDiameterEAPRequest();
extern int SendWdAARequest();
extern int SendWdReAuthRequest();
extern int SendWdSessionTerminationRequest();
extern int SendWdAbortSessionRequest();


/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Wd Protocol messages to
 *      the diameter stack. These will create the appropriate Wd protocol
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


extern int SendWdDiameterEAPAnswer(const diameter::CommandImpl *impl);
extern int SendWdAAAnswer(const diameter::CommandImpl *impl);
extern int SendWdReAuthAnswer(const diameter::CommandImpl *impl);
extern int SendWdSessionTerminationAnswer(const diameter::CommandImpl *impl);
extern int SendWdAbortSessionAnswer(const diameter::CommandImpl *impl);

#endif

