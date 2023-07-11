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
 * LOG: $Log: wa_defines.h,v $
 * LOG: Revision 1.1  2011/04/18 10:38:09  vkumara
 * LOG: Wa interface support.
 * LOG:
 * LOG: Revision 1.1  2011/04/18 09:44:11  vkumara
 * LOG: Wa Interface Support added.
 * LOG:
 * LOG:
 ****************************************************************************/
#ident "$Id: wa_defines.h,v 1.1 2011/04/18 10:38:09 vkumara Exp $"

#ifndef _SAMPLE_WDAPP_DEFINE
#define _SAMPLE_WDAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID            0
#define WA_INTERFACE_APP_ID    	         5
#define VENDOR_ID                        10415

/* Defines for ACR */
#define START          1
#define INTERIM        2
#define STOP           3
#define EVENT          4
#define START_AUTHSESS 5
#define EVENT_AUTHSESS 6

/**
 * The Application Worker Queue Id for Wd interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define WA_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For WA Interface
 **/
#define WA_DE_MSG_CMD_CODE        268
#define WA_AA_MSG_CMD_CODE        265
#define WA_AC_MSG_CMD_CODE        271
#define WA_RA_MSG_CMD_CODE        258
#define WA_ST_MSG_CMD_CODE        275
#define WA_AS_MSG_CMD_CODE        274


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
extern int SendWaDiameterEAPRequest();
extern int SendWaAARequest();
extern int SendWaACRequest(int reqType, const diameter::CommandImpl* impl = NULL);
extern int SendWaReAuthRequest();
extern int SendWaSessionTerminationRequest();
extern int SendWaAbortSessionRequest();


/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Wa Protocol messages to
 *      the diameter stack. These will create the appropriate Wa protocol
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


extern int SendWaDiameterEAPAnswer(const diameter::CommandImpl *impl);
extern int SendWaAAAnswer(const diameter::CommandImpl *impl);
extern int SendWaACAnswer(const diameter::CommandImpl *impl);
extern int SendWaReAuthAnswer(const diameter::CommandImpl *impl);
extern int SendWaSessionTerminationAnswer(const diameter::CommandImpl *impl);
extern int SendWaAbortSessionAnswer(const diameter::CommandImpl *impl);

#endif

