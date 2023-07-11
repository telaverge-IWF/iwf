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
 * ID: $Id: gq_defines.h,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $
 *
 * LOG: $Log: gq_defines.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:09  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:36:39  kamakshilk
 * LOG: GqGq' interface demo for static and distributed
 * LOG:
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: gq_defines.h,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $"

#ifndef _SAMPLE_TXAPP_DEFINE
#define _SAMPLE_TXAPP_DEFINE

#include <diameter/gqgqprime/AA.h>
#include <diameter/gqgqprime/AS.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::gqgqprime;

/** 
 * Standard ApplicationId's defined by IANA
 **/
#define BASE_INTERFACE_APP_ID    0
#define GQGQ_INTERFACE_APP_ID    16777222
#define VENDOR_ID    	 	 10415

/** 
 * The Application Worker Queue Id for GqGq' interface
 * (Worker: Thread with an associated TaskQueue)
 **/
#define GQGQ_APP_TQ_INST           1

/** 
 * Standard CommandCode's defined by IANA
 * For GqGq' Interface
 **/
#define GQGQ_AA_MSG_CMD_CODE        265
#define GQGQ_RA_MSG_CMD_CODE        258
#define GQGQ_ST_MSG_CMD_CODE        275
#define GQGQ_AS_MSG_CMD_CODE        274

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
 *      Utility functions to send the GqGq' Protocol messages to 
 *      the diameter stack. These will create the appropriate GqGq' protocol 
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
extern int SendGqAARequest();
extern int SendGqRARequest();
extern int SendGqSTRequest();
extern int SendGqASRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the GqGq' Protocol messages to 
 *      the diameter stack. These will create the appropriate GqGq' protocol 
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
extern int SendGqAAAnswer(const diameter::CommandImpl *impl);
extern int SendGqRAAnswer(const diameter::CommandImpl *impl);
extern int SendGqSTAnswer(const diameter::CommandImpl *impl);
extern int SendGqASAnswer(const diameter::CommandImpl *impl);


#endif

