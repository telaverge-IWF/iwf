/*********************************-*-Dia-*-**********************************
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
 * LOG: $Log: rx_defines.h,v $
 * LOG: Revision 3.2  2010/08/04 10:31:08  nvijikumar
 * LOG: Load Capability for RX interface
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:12  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2006/12/19 09:10:07  kamakshilk
 * LOG: New architecture for static and distributed
 * LOG:
 * LOG: Revision 2.2  2006/10/18 04:56:15  tpanda
 * LOG: Signatures added for Send ASA and STA
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/07/24 15:18:20  nvijikumar
 * LOG: Baseline demo application for Rx Interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: rx_defines.h,v 3.2 2010/08/04 10:31:08 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: rx_defines.h,v 3.2 2010/08/04 10:31:08 nvijikumar Exp $"

#ifndef _SAMPLE_RXAPP_DEFINE
#define _SAMPLE_RXAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/** 
 * Standard ApplicationId's defined by IANA
 **/
#define BASE_INTERFACE_APP_ID    0
#define RX_INTERFACE_APP_ID    	 16777229
#define VENDOR_ID    	 	 10415

/** 
 * The Application Worker Queue Id for Rx interface
 * (Worker: Thread with an associated TaskQueue)
 **/
#define RX_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For Rx Interface
 **/
#define RX_AA_MSG_CMD_CODE        265
#define RX_RA_MSG_CMD_CODE        258
#define RX_ST_MSG_CMD_CODE        275
#define RX_AS_MSG_CMD_CODE        274

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
 *      Utility functions to send the Rx Protocol messages to 
 *      the diameter stack. These will create the appropriate Rx protocol 
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
extern int SendRxAARequest();
extern int SendRxRARequest();
extern int SendRxSTRequest(const SessionId* sessionId = NULL);
extern int SendRxASRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the Rx Protocol messages to 
 *      the diameter stack. These will create the appropriate Rx protocol 
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
extern int SendRxAAAnswer(const diameter::CommandImpl *impl);
extern int SendRxRAAnswer(const diameter::CommandImpl *impl);
extern int SendRxASAnswer(const diameter::CommandImpl *impl);
extern int SendRxSTAnswer(const diameter::CommandImpl *impl);

#endif

