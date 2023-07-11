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
 * LOG: $Log: wx_defines.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:14  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.2  2006/12/19 09:02:14  kamakshilk
 * LOG: New architecture to work with static and distributed
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.2  2006/07/31 07:07:57  kamakshilk
 * LOG: Added new Message ( Registration Termination).
 * LOG:
 * LOG:
 *
 * ID: $Id: wx_defines.h,v 3.1 2008/03/31 10:33:14 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: wx_defines.h,v 3.1 2008/03/31 10:33:14 nvijikumar Exp $"

#ifndef _SAMPLE_WXAPP_DEFINE
#define _SAMPLE_WXAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/** 
 * Standard ApplicationId's defined by IANA
 **/
#define BASE_INTERFACE_APP_ID    0
#define WX_INTERFACE_APP_ID    	 16777219
#define VENDOR_ID    	 	 10415

/** 
 * The Application Worker Queue Id for Wx interface
 * (Worker: Thread with an associated TaskQueue)
 **/
#define WX_APP_TQ_INST           1

/** 
 * Standard CommandCode's defined by IANA
 * For Wx Interface
 **/
#define WX_MA_MSG_CMD_CODE        303
#define WX_PP_MSG_CMD_CODE        305
#define WX_SA_MSG_CMD_CODE        301
#define WX_RT_MSG_CMD_CODE        304

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
 *      Utility functions to send the Wx Protocol messages to 
 *      the diameter stack. These will create the appropriate Wx protocol 
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
extern int SendWxPushProfileRequest();
extern int SendWxServerAssignmentRequest();
extern int SendWxMultimediaAuthenticationRequest();
extern int SendWxRegistrationTerminationRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the Wx Protocol messages to 
 *      the diameter stack. These will create the appropriate Wx protocol 
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
extern int SendWxPushProfileAnswer(const diameter::CommandImpl *impl);
extern int SendWxServerAssignmentAnswer(const diameter::CommandImpl *impl);
extern int SendWxMultimediaAuthenticationAnswer
                                       (const diameter::CommandImpl *impl);
extern int SendWxRegistrationTerminationAnswer
                                       (const diameter::CommandImpl *impl);

#endif

