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
 * LOG: $Log: a4_defines.h,v $
 * LOG: Revision 1.1  2011/06/29 06:39:46  vkumara
 * LOG: Baseline for a4 interface.
 * LOG:
 * LOG:
 * ID: $Id: a4_defines.h,v 1.1 2011/06/29 06:39:46 vkumara Exp $
 ****************************************************************************/
 #ident "$Id: a4_defines.h,v 1.1 2011/06/29 06:39:46 vkumara Exp $"


#ifndef _SAMPLE_A4APP_DEFINE
#define _SAMPLE_A4APP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID            0
#define A4_INTERFACE_APP_ID    	         16777257
#define VENDOR_ID    	 	         13019

/**
 * The Application Worker Queue Id for A4 interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define A4_APP_TQ_INST             1

/**
 * Standard CommandCode's defined by IANA
 * For A4 Interface
 **/
#define A4_UD_MSG_CMD_CODE        306
#define A4_PN_MSG_CMD_CODE        309

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
 *      Utility functions to send the A4 Protocol messages to
 *      the diameter stack. These will create the appropriate A4 protocol
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
extern int SendA4UserDataRequest();
extern int SendA4PushNotificationRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the A4 Protocol messages to
 *      the diameter stack. These will create the appropriate A4 protocol
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
extern int SendA4UserDataAnswer(const diameter::CommandImpl *impl);
extern int SendA4PushNotificationAnswer(const diameter::CommandImpl *impl);


#endif
