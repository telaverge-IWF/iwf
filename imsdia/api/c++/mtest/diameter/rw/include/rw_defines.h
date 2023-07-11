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
 * LOG: $Log: rw_defines.h,v $
 * LOG: Revision 1.1  2011/07/14 11:51:38  vkumara
 * LOG: Baseline for Rw interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: rw_defines.h,v 1.1 2011/07/14 11:51:38 vkumara Exp $
 ****************************************************************************/
 #ident "$Id: rw_defines.h,v 1.1 2011/07/14 11:51:38 vkumara Exp $"


#ifndef _SAMPLE_RWAPP_DEFINE
#define _SAMPLE_RWAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

#include <diameter/rw/CC.h>
#include <diameter/rw/RA.h>
#include <diameter/rw/PI.h>
#include <diameter/rw/AS.h>


/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID                           0
#define RW_INTERFACE_APP_ID    	         		16777256
#define VENDOR_ID    	 	         		11502

/**
 * The Application Worker Queue Id for Rw interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define RW_APP_TQ_INST             1

/**
 * Standard CommandCode's defined by IANA
 * For Rw Interface
 **/
#define RW_PI_MSG_CMD_CODE        315
#define RW_AS_MSG_CMD_CODE        274
#define RW_RA_MSG_CMD_CODE        258
#define RW_CC_MSG_CMD_CODE        272

#define INITIAL       1
#define UPDATE        2
#define TERMINATION   3
#define EVENT         4

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
 *      Utility functions to send the Rw Protocol messages to
 *      the diameter stack. These will create the appropriate Rw protocol
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
extern int SendRwPIRequest();
extern int SendRwRARequest();
extern int SendRwCCRequest(int requestType,const diameter::CommandImpl* impl = NULL);
extern int SendRwAbortSessionRequest();
/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Rw Protocol messages to
 *      the diameter stack. These will create the appropriate Rw protocol
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
extern int SendRwPIAnswer(const diameter::CommandImpl *impl);
extern int SendRwRAAnswer(const diameter::CommandImpl *impl);
extern int SendRwCCAnswer(const diameter::CommandImpl *impl);
extern int SendRwAbortSessionAnswer(const diameter::CommandImpl *impl);

#endif

