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
 * LOG: $Log: wm_defines.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:14  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/02/28 11:03:09  hbhatnagar
 * LOG: Baseline Demo Application for Wm Interface.
 * LOG:
 *
 * ID: $Id: wm_defines.h,v 3.1 2008/03/31 10:33:14 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: wm_defines.h,v 3.1 2008/03/31 10:33:14 nvijikumar Exp $"

#ifndef _SAMPLE_WMAPP_DEFINE
#define _SAMPLE_WMAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID            0
#define WM_INTERFACE_APP_ID    	         1

/**
 * The Application Worker Queue Id for Wm interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define WM_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For WM Interface
 **/
#define WM_DE_MSG_CMD_CODE        268
#define WM_AA_MSG_CMD_CODE        265
#define WM_RA_MSG_CMD_CODE        258
#define WM_ST_MSG_CMD_CODE        275
#define WM_AS_MSG_CMD_CODE        274


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
 *      Utility functions to send the Wm Protocol messages to
 *      the diameter stack. These will create the appropriate Wm protocol
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
extern int SendWmDiameterEAPRequest();
extern int SendWmAARequest();
extern int SendWmReAuthRequest();
extern int SendWmSessionTerminationRequest();
extern int SendWmAbortSessionRequest();


/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Wm Protocol messages to
 *      the diameter stack. These will create the appropriate Wm protocol
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


extern int SendWmDiameterEAPAnswer(const diameter::CommandImpl *impl);
extern int SendWmAAAnswer(const diameter::CommandImpl *impl);
extern int SendWmReAuthAnswer(const diameter::CommandImpl *impl);
extern int SendWmSessionTerminationAnswer(const diameter::CommandImpl *impl);
extern int SendWmAbortSessionAnswer(const diameter::CommandImpl *impl);

#endif

