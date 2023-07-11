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
 * LOG: $Log: gmb_defines.h,v $
 * LOG: Revision 1.1  2011/06/14 05:25:38  vkumara
 * LOG: Baseline for Gmb interface.
 * LOG:
 * LOG:
 ****************************************************************************/
#ident "$Id: gmb_defines.h,v 1.1 2011/06/14 05:25:38 vkumara Exp $"

#ifndef _SAMPLE_GMBAPP_DEFINE
#define _SAMPLE_GMBAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID            0
#define GMB_INTERFACE_APP_ID    	 16777223
#define VENDOR_ID                        10415

/**
 * The Application Worker Queue Id for Gmb interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define GMB_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For GMB Interface
 **/
#define GMB_AA_MSG_CMD_CODE        265
#define GMB_RA_MSG_CMD_CODE        258
#define GMB_ST_MSG_CMD_CODE        275
#define GMB_AS_MSG_CMD_CODE        274


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
 *      Utility functions to send the Gmb Protocol messages to
 *      the diameter stack. These will create the appropriate Gmb protocol
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
extern int SendGmbAARequest();
extern int SendGmbReAuthRequest();
extern int SendGmbSessionTerminationRequest();
extern int SendGmbAbortSessionRequest();


/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Gmb Protocol messages to
 *      the diameter stack. These will create the appropriate Gmb protocol
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
extern int SendGmbAAAnswer(const diameter::CommandImpl *impl);
extern int SendGmbReAuthAnswer(const diameter::CommandImpl *impl);
extern int SendGmbSessionTerminationAnswer(const diameter::CommandImpl *impl);
extern int SendGmbAbortSessionAnswer(const diameter::CommandImpl *impl);

#endif
