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
 * LOG: $Log: s6b_defines.h,v $
 * LOG: Revision 1.1  2011/04/27 12:14:11  vkumara
 * LOG: Draft for S6b interface.
 * LOG:
 * LOG:
 ****************************************************************************/
#ident "$Id: s6b_defines.h,v 1.1 2011/04/27 12:14:11 vkumara Exp $"

#ifndef _SAMPLE_S6BAPP_DEFINE
#define _SAMPLE_S6BAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID            0
#define S6B_INTERFACE_APP_ID    	 16777272
#define VENDOR_ID                        10415

/**
 * The Application Worker Queue Id for S6b interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define S6B_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For WA Interface
 **/
#define S6B_DE_MSG_CMD_CODE        268
#define S6B_AA_MSG_CMD_CODE        265
#define S6B_RA_MSG_CMD_CODE        258
#define S6B_ST_MSG_CMD_CODE        275
#define S6B_AS_MSG_CMD_CODE        274


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
 *      Utility functions to send the S6b Protocol messages to
 *      the diameter stack. These will create the appropriate S6b protocol
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
extern int SendS6bDiameterEAPRequest();
extern int SendS6bAARequest();
extern int SendS6bReAuthRequest();
extern int SendS6bSessionTerminationRequest();
extern int SendS6bAbortSessionRequest();


/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the S6b Protocol messages to
 *      the diameter stack. These will create the appropriate S6b protocol
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


extern int SendS6bDiameterEAPAnswer(const diameter::CommandImpl *impl);
extern int SendS6bAAAnswer(const diameter::CommandImpl *impl);
extern int SendS6bReAuthAnswer(const diameter::CommandImpl *impl);
extern int SendS6bSessionTerminationAnswer(const diameter::CommandImpl *impl);
extern int SendS6bAbortSessionAnswer(const diameter::CommandImpl *impl);

#endif

