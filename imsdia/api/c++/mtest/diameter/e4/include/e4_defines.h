/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: e4_defines.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:09  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/01/04 16:05:47  hbhatnagar
 * LOG: Baseline demo application for e4 interface for static and distributed.
 * LOG:
 *
 * ID: $Id: e4_defines.h,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $
 ****************************************************************************/
 #ident "$Id: e4_defines.h,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $"


#ifndef _SAMPLE_E4APP_DEFINE
#define _SAMPLE_E4APP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID            0
#define E4_INTERFACE_APP_ID    	         16777231
#define VENDOR_ID    	 	         13019

/**
 * The Application Worker Queue Id for E4 interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define E4_APP_TQ_INST             1

/**
 * Standard CommandCode's defined by IANA
 * For E4 Interface
 **/
#define E4_UD_MSG_CMD_CODE        306
#define E4_PN_MSG_CMD_CODE        309

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
 *      Utility functions to send the E4 Protocol messages to
 *      the diameter stack. These will create the appropriate E4 protocol
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
extern int SendE4UserDataRequest();
extern int SendE4PushNotificationRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the E4 Protocol messages to
 *      the diameter stack. These will create the appropriate E4 protocol
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
extern int SendE4UserDataAnswer(const diameter::CommandImpl *impl);
extern int SendE4PushNotificationAnswer(const diameter::CommandImpl *impl);


#endif
