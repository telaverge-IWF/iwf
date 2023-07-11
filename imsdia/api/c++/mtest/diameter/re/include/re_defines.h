/*********************************-*-Dia-*-**********************************
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
 * LOG: $Log: re_defines.h,v $
 * LOG: Revision 1.1  2011/05/20 04:15:48  vkumara
 * LOG: Basline for Re interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: re_defines.h,v 1.1 2011/05/20 04:15:48 vkumara Exp $
 ****************************************************************************/
#ident "$Id: re_defines.h,v 1.1 2011/05/20 04:15:48 vkumara Exp $"

#ifndef _SAMPLE_REAPP_DEFINE
#define _SAMPLE_REAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/** 
 * Standard ApplicationId's defined by IANA
 **/
#define BASE_INTERFACE_APP_ID    0
#define RE_INTERFACE_APP_ID    	 16777218
#define VENDOR_ID    	 	 10415

/** 
 * The Application Worker Queue Id for Re interface
 * (Worker: Thread with an associated TaskQueue)
 **/
#define RE_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For Re Interface
 * Editors Note: The 3GPP Rating Application uses the value xxx (3GPP) as Vendor-Id.
 * Need to change Command Codes. Time being we are using 5052 as Command-Code.
 **/
#define RE_PRICE_MSG_CMD_CODE         5050      
#define RE_TARIFF_MSG_CMD_CODE        5051
#define RE_SERVICEUSAGE_MSG_CMD_CODE  5052

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
 *      Utility functions to send the Re Protocol messages to 
 *      the diameter stack. These will create the appropriate Re protocol 
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
extern int SendRePriceRequest();
extern int SendReTariffRequest();
extern int SendReServiceUsageRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the Re Protocol messages to 
 *      the diameter stack. These will create the appropriate Re protocol 
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
extern int SendRePriceResponse(const diameter::CommandImpl *impl);
extern int SendReTariffResponse(const diameter::CommandImpl *impl);
extern int SendReServiceUsageResponse(const diameter::CommandImpl *impl);

#endif
