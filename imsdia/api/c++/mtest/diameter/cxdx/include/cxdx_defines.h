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
 * LOG: $Log: cxdx_defines.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:08  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:21:14  kamakshilk
 * LOG: Demo program for Cxdx Interface
 * LOG:
 * LOG:
 *
 * ID: $Id: cxdx_defines.h,v 3.1 2008/03/31 10:33:08 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: cxdx_defines.h,v 3.1 2008/03/31 10:33:08 nvijikumar Exp $"

#ifndef _SAMPLE_CXDXAPP_DEFINE
#define _SAMPLE_CXDXAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID          0
#define CXDX_INTERFACE_APP_ID          16777216
#define VENDOR_ID                      10415

/**
 * The Application Worker Queue Id for Cx interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define CXDX_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For CxDx Interface
 **/
#define CXDX_UA_MSG_CMD_CODE        300
#define CXDX_SA_MSG_CMD_CODE        301
#define CXDX_LI_MSG_CMD_CODE        302
#define CXDX_MA_MSG_CMD_CODE        303
#define CXDX_RT_MSG_CMD_CODE        304
#define CXDX_PP_MSG_CMD_CODE        305

extern char subsProfile[2000];

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
 *      Utility functions to send the CxDx Protocol messages to
 *      the diameter stack. These will create the appropriate CxDx protocol
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
extern int SendCxdxUserAuthorizationRequest();
extern int SendCxdxServerAssignmentRequest();
extern int SendCxdxLocationInfoRequest();
extern int SendCxdxMultimediaAuthRequest();
extern int SendCxdxRegistrationTerminationRequest();
extern int SendCxdxPushProfileRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the CxDx Protocol messages to
 *      the diameter stack. These will create the appropriate CxDx protocol
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


extern int SendCxdxUserAuthorizationAnswer(const diameter::CommandImpl *impl);
extern int SendCxdxServerAssignmentAnswer(const diameter::CommandImpl *impl);
extern int SendCxdxLocationInfoAnswer(const diameter::CommandImpl *impl);
extern int SendCxdxMultimediaAuthAnswer(const diameter::CommandImpl *impl);
extern int SendCxdxRegistrationTerminationAnswer
                                     (const diameter::CommandImpl *impl);
extern int SendCxdxPushProfileAnswer(const diameter::CommandImpl *impl);

#endif
