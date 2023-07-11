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
 ****************************************************************************
 * LOG: $Log: s6a_defines.h,v $
 * LOG: Revision 1.5  2009/04/08 05:48:23  sureshj
 * LOG: Demo changes to support 3GPP TS 29272 v8.2.0, commands codes updated.
 * LOG:
 * LOG: Revision 1.4  2009/03/04 12:51:08  sureshj
 * LOG: command code changes motorola specific.
 * LOG:
 * LOG: Revision 1.3  2008/11/25 09:06:03  sureshj
 * LOG: issueID:none
 * LOG: FeatureID:none
 * LOG: Description: support for C4-083420 (motorola). Updated command codes.
 * LOG:
 * LOG: Revision 1.2  2008/11/12 06:20:29  sureshj
 * LOG: Added new commands. part of 3.1.1 release.
 * LOG:
 * LOG: Revision 1.1  2008/08/19 06:59:32  sureshj
 * LOG: Baseline demo application for s6a interface.
 * LOG:
 * ID: $Id: s6a_defines.h,v 1.5 2009/04/08 05:48:23 sureshj Exp $
 ****************************************************************************/

#ifndef _SAMPLE_S6AAPP_DEFINE
#define _SAMPLE_S6AAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID            0
#define S6A_INTERFACE_APP_ID   	         16777251
#define VENDOR_ID    	 	         10415

/**
 * The Application Worker Queue Id for S6A interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define S6A_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For S6A Interface
 **/
#define S6A_UL_MSG_CMD_CODE        316 
#define S6A_CL_MSG_CMD_CODE        317
#define S6A_PU_MSG_CMD_CODE        321
#define S6A_ID_MSG_CMD_CODE        319
#define S6A_DS_MSG_CMD_CODE        320
#define S6A_AI_MSG_CMD_CODE        318


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
 *      Utility functions to send the S6A Protocol messages to
 *      the diameter stack. These will create the appropriate S6A protocol
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
extern int SendS6AUpdateLocationRequest();

extern int SendS6AAuthenticationInformationRequest();

extern int SendS6ACancelLocationRequest();

extern int SendS6APurgeUERequest();

extern int SendS6ADeleteSubDataRequest();

extern int SendS6AInsertSubDataRequest();
 


/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the S6A Protocol messages to
 *      the diameter stack. These will create the appropriate S6A protocol
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


extern int SendS6AUpdateLocationAnswer(const diameter::CommandImpl *impl);

extern int SendS6AAuthenticationInformationAnswer(const diameter::CommandImpl *impl);

extern int SendS6ACancelLocationAnswer(const diameter::CommandImpl *impl);

extern int SendS6APurgeUEAnswer(const diameter::CommandImpl *impl);

extern int SendS6ADeleteSubDataAnswer(const diameter::CommandImpl *impl);

extern int SendS6AInsertSubDataAnswer(const diameter::CommandImpl *impl);

#endif
