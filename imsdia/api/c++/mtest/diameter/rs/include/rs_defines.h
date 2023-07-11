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
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Softrsre       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: rs_defines.h,v $
 * LOG: Revision 1.1  2011/07/14 11:53:20  vkumara
 * LOG: Baseline for Rs interface.
 * LOG:
 * LOG:
 * ID: $Id: rs_defines.h,v 1.1 2011/07/14 11:53:20 vkumara Exp $
 ****************************************************************************/
#ident "$Id: rs_defines.h,v 1.1 2011/07/14 11:53:20 vkumara Exp $"

#ifndef _SAMPLE_RSAPP_DEFINE
#define _SAMPLE_RSAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID            0
#define RS_INTERFACE_APP_ID    	         16777235
#define VENDOR_ID                        11502

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

#define RS_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For RS Interface
 **/
#define RS_AA_MSG_CMD_CODE        265
#define RS_RA_MSG_CMD_CODE        258
#define RS_ST_MSG_CMD_CODE        275
#define RS_AS_MSG_CMD_CODE        274
#define RS_PN_MSG_CMD_CODE        309

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
extern int SendRsAARequest();
extern int SendRsRARequest();
extern int SendRsSTRequest();
extern int SendRsASRequest();
extern int SendRsPNRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Rs Protocol messages to
 *      the diameter stack. These will create the appropriate Rs protocol
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


extern int SendRsAAAnswer(const diameter::CommandImpl *impl);
extern int SendRsRAAnswer(const diameter::CommandImpl *impl);
extern int SendRsSTAnswer(const diameter::CommandImpl *impl);
extern int SendRsASAnswer(const diameter::CommandImpl *impl);
extern int SendRsPNAnswer(const diameter::CommandImpl *impl);
#endif

