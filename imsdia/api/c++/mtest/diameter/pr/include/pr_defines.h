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
 * LOG: $Log: pr_defines.h,v $
 * LOG: Revision 1.1  2011/05/09 11:14:50  vkumara
 * LOG: Base line for Pr interface.
 * LOG:
 * LOG:
 * ID: $Id: pr_defines.h,v 1.1 2011/05/09 11:14:50 vkumara Exp $
 ****************************************************************************/
#ident "$Id: pr_defines.h,v 1.1 2011/05/09 11:14:50 vkumara Exp $"

#ifndef _SAMPLE_PRAPP_DEFINE
#define _SAMPLE_PRAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID            0
#define PR_INTERFACE_APP_ID    	         16777230
#define VENDOR_ID                        10415

/**
 * The Application Worker Queue Id for Wd interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define PR_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For PR Interface
 **/
#define PR_AA_MSG_CMD_CODE        265
#define PR_AS_MSG_CMD_CODE        274
#define PR_SA_MSG_CMD_CODE        301


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
extern int SendPrDiameterEAPRequest();
extern int SendPrAARequest();
extern int SendPrServerAssignmentRequest();
extern int SendPrAbortSessionRequest();


/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Pr Protocol messages to
 *      the diameter stack. These will create the appropriate Pr protocol
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


extern int SendPrDiameterEAPAnswer(const diameter::CommandImpl *impl);
extern int SendPrAAAnswer(const diameter::CommandImpl *impl);
extern int SendPrServerAssignmentAnswer(const diameter::CommandImpl *impl);
extern int SendPrAbortSessionAnswer(const diameter::CommandImpl *impl);

#endif

