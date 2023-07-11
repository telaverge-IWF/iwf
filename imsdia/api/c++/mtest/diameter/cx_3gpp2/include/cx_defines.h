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
 * LOG: $Log: cx_defines.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:07  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:47:03  kamakshilk
 * LOG: Cx 3GPP2 interface demo for static and distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: cx_defines.h,v 3.1 2008/03/31 10:33:07 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: cx_defines.h,v 3.1 2008/03/31 10:33:07 nvijikumar Exp $"

#ifndef _SAMPLE_CX3GPP2APP_DEFINE
#define _SAMPLE_CX3GPP2APP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID            0
#define CX_INTERFACE_APP_ID    	         16777216
#define VENDOR_ID    	 	         10415

/**
 * The Application Worker Queue Id for Cx interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define CX_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For Cx Interface
 **/
#define CX_UA_MSG_CMD_CODE        300
#define CX_SA_MSG_CMD_CODE        301
#define CX_LI_MSG_CMD_CODE        302
#define CX_MA_MSG_CMD_CODE        303
#define CX_RT_MSG_CMD_CODE        304
#define CX_PP_MSG_CMD_CODE        305

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
 *      Utility functions to send the Cx Protocol messages to
 *      the diameter stack. These will create the appropriate Cx protocol
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
extern int SendCxUserAuthorizationRequest();
extern int SendCxServerAssignmentRequest();
extern int SendCxLocationInfoRequest();
extern int SendCxMultimediaAuthRequest();
extern int SendCxRegistrationTerminationRequest();
extern int SendCxPushProfileRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Cx Protocol messages to
 *      the diameter stack. These will create the appropriate Cx protocol
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


extern int SendCxUserAuthorizationAnswer(const diameter::CommandImpl *impl);
extern int SendCxServerAssignmentAnswer(const diameter::CommandImpl *impl);
extern int SendCxLocationInfoAnswer(const diameter::CommandImpl *impl);
extern int SendCxMultimediaAuthAnswer(const diameter::CommandImpl *impl);
extern int SendCxRegistrationTerminationAnswer
                                     (const diameter::CommandImpl *impl);
extern int SendCxPushProfileAnswer(const diameter::CommandImpl *impl);

#endif

