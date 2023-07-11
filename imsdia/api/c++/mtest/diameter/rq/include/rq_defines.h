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
 * LOG: $Log: rq_defines.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:11  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/01/08 07:41:35  hbhatnagar
 * LOG: baseline demo application for rq interface for static and distributed mode.
 * LOG:
 *
 * ID: $Id: rq_defines.h,v 3.1 2008/03/31 10:33:11 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: rq_defines.h,v 3.1 2008/03/31 10:33:11 nvijikumar Exp $"

#ifndef _SAMPLE_RQAPP_DEFINE
#define _SAMPLE_RQAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/** 
 * Standard ApplicationId's defined by IANA
 **/
#define BASE_INTERFACE_APP_ID    0
#define RQ_INTERFACE_APP_ID    	 16777222
#define VENDOR_ID    	 	 13019

/** 
 * The Application Worker Queue Id for Rq interface
 * (Worker: Thread with an associated TaskQueue)
 **/
#define RQ_APP_TQ_INST           1

/**
 * Standard CommandCode's defined by IANA
 * For Rq Interface
 **/
#define RQ_AA_MSG_CMD_CODE        265
#define RQ_RA_MSG_CMD_CODE        258
#define RQ_ST_MSG_CMD_CODE        275
#define RQ_AS_MSG_CMD_CODE        274

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
 *      Utility functions to send the Rq Protocol messages to 
 *      the diameter stack. These will create the appropriate Rq protocol 
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
extern int SendRqAARequest();
extern int SendRqRARequest();
extern int SendRqSTRequest();
extern int SendRqASRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the Rq Protocol messages to 
 *      the diameter stack. These will create the appropriate Rq protocol 
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
extern int SendRqAAAnswer(const diameter::CommandImpl *impl);
extern int SendRqRAAnswer(const diameter::CommandImpl *impl);
extern int SendRqASAnswer(const diameter::CommandImpl *impl);
extern int SendRqSTAnswer(const diameter::CommandImpl *impl);

#endif

