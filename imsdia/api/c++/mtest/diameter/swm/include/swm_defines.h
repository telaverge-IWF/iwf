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
 * LOG: $Log: swm_defines.h,v $
 * LOG: Revision 1.1  2011/05/03 04:54:00  vkumara
 * LOG: SWm interface support.
 * LOG:
 * LOG:
 ****************************************************************************/
#ident "$Id: swm_defines.h,v 1.1 2011/05/03 04:54:00 vkumara Exp $"

#ifndef _SAMPLE_SWMAPP_DEFINE
#define _SAMPLE_SWMAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID            0
#define SWM_INTERFACE_APP_ID    	 16777264
#define VENDOR_ID                        10415

/**
 * The Application Worker Queue Id for Wd interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define SWM_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For SWM Interface
 **/
#define SWM_DE_MSG_CMD_CODE        268
#define SWM_AA_MSG_CMD_CODE        265
#define SWM_RA_MSG_CMD_CODE        258
#define SWM_ST_MSG_CMD_CODE        275
#define SWM_AS_MSG_CMD_CODE        274


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
 *      Utility functions to send the SWm Protocol messages to
 *      the diameter stack. These will create the appropriate SWm protocol
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
extern int SendSWmDiameterEAPRequest();
extern int SendSWmAARequest();
extern int SendSWmReAuthRequest();
extern int SendSWmSessionTerminationRequest();
extern int SendSWmAbortSessionRequest();


/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the SWm Protocol messages to
 *      the diameter stack. These will create the appropriate SWm protocol
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


extern int SendSWmDiameterEAPAnswer(const diameter::CommandImpl *impl);
extern int SendSWmAAAnswer(const diameter::CommandImpl *impl);
extern int SendSWmReAuthAnswer(const diameter::CommandImpl *impl);
extern int SendSWmSessionTerminationAnswer(const diameter::CommandImpl *impl);
extern int SendSWmAbortSessionAnswer(const diameter::CommandImpl *impl);

#endif

