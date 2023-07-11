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
 * LOG: $Log: nasreq_defines.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:10  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.2  2007/01/11 11:29:41  kamakshilk
 * LOG: AppId 1 added to commands
 * LOG:
 * LOG: Revision 1.1  2007/01/01 14:31:42  nanaparthi
 * LOG: NASREQ Demo for Static and Distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: nasreq_defines.h,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: nasreq_defines.h,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $"



#ifndef _SAMPLE_NASREQAPP_DEFINE
#define _SAMPLE_NASREQAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID            0
#define NASREQ_INTERFACE_APP_ID    	 1

/**
 * The Application Worker Queue Id for Nasreq interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define NASREQ_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For NASREQ Interface
 **/
#define NASREQ_AA_MSG_CMD_CODE        265
#define NASREQ_RA_MSG_CMD_CODE        258
#define NASREQ_ST_MSG_CMD_CODE        275
#define NASREQ_AS_MSG_CMD_CODE        274
#define NASREQ_AC_MSG_CMD_CODE        271


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
 *      Utility functions to send the Nasreq Protocol messages to
 *      the diameter stack. These will create the appropriate Nasreq protocol
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
extern int SendNasreqAARequest();
extern int SendNasreqReAuthRequest();
extern int SendNasreqSessionTerminationRequest();
extern int SendNasreqAbortSessionRequest();
extern int SendNasreqAccountingRequest();


/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Nasreq Protocol messages to
 *      the diameter stack. These will create the appropriate Nasreq protocol
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


extern int SendNasreqAAAnswer(const diameter::CommandImpl *impl);
extern int SendNasreqReAuthAnswer(const diameter::CommandImpl *impl);
extern int SendNasreqSessionTerminationAnswer(const diameter::CommandImpl *impl);
extern int SendNasreqAbortSessionAnswer(const diameter::CommandImpl *impl);
extern int SendNasreqAccountingAnswer
                                     (const diameter::CommandImpl *impl);


#endif

