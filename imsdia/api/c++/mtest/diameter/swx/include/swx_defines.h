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
 * LOG: $Log: swx_defines.h,v $
 * LOG: Revision 1.1  2011/05/03 04:58:33  vkumara
 * LOG: SWx interface support.
 * LOG:
 * LOG:
 *
 * ID: $Id: swx_defines.h,v 1.1 2011/05/03 04:58:33 vkumara Exp $
 ****************************************************************************/
#ident "$Id: swx_defines.h,v 1.1 2011/05/03 04:58:33 vkumara Exp $"

#ifndef _SAMPLE_SWXAPP_DEFINE
#define _SAMPLE_SWXAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/** 
 * Standard ApplicationId's defined by IANA
 **/
#define BASE_INTERFACE_APP_ID    0
#define SWX_INTERFACE_APP_ID    	 16777265
#define VENDOR_ID    	 	 10415

/** 
 * The Application Worker Queue Id for SWx interface
 * (Worker: Thread with an associated TaskQueue)
 **/
#define SWX_APP_TQ_INST           1

/** 
 * Standard CommandCode's defined by IANA
 * For SWx Interface
 **/
#define SWX_MA_MSG_CMD_CODE        303
#define SWX_PP_MSG_CMD_CODE        305
#define SWX_SA_MSG_CMD_CODE        301
#define SWX_RT_MSG_CMD_CODE        304

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
 *      Utility functions to send the SWx Protocol messages to 
 *      the diameter stack. These will create the appropriate SWx protocol 
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
extern int SendSWxPushProfileRequest();
extern int SendSWxServerAssignmentRequest();
extern int SendSWxMultimediaAuthenticationRequest();
extern int SendSWxRegistrationTerminationRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the SWx Protocol messages to 
 *      the diameter stack. These will create the appropriate SWx protocol 
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
extern int SendSWxPushProfileAnswer(const diameter::CommandImpl *impl);
extern int SendSWxServerAssignmentAnswer(const diameter::CommandImpl *impl);
extern int SendSWxMultimediaAuthenticationAnswer
                                       (const diameter::CommandImpl *impl);
extern int SendSWxRegistrationTerminationAnswer
                                       (const diameter::CommandImpl *impl);

#endif

