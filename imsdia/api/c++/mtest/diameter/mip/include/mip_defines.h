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
 * LOG: $Log: mip_defines.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:10  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.2  2007/01/08 14:12:41  hbhatnagar
 * LOG: made changes for the Accounting Request and Answer
 * LOG:
 * LOG: Revision 1.1  2007/01/01 15:18:49  hbhatnagar
 * LOG: adding the baseline demo application for the MobileIP
 * LOG:
 *
 * ID: $Id: mip_defines.h,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $
 * 
 ****************************************************************************/


#ifndef _SAMPLE_MIPAPP_DEFINE
#define _SAMPLE_MIPAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/

#define BASE_INTERFACE_APP_ID        0
#define MIP_INTERFACE_APP_ID         2
//#define VENDOR_ID                    10415

/**
 * The Application Worker Queue Id for Mip interface
 * (Worker: Thread with an associated TaskQueue)
 **/

#define MIP_APP_TQ_INST             1

/**
 * Standard CommandCode's defined by IANA
 * For Mip Interface
 **/
#define MIP_AM_MSG_CMD_CODE        260
#define MIP_HA_MSG_CMD_CODE        262
#define MIP_AC_MSG_CMD_CODE        271

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
 *      Utility functions to send the Mip Protocol messages to
 *      the diameter stack. These will create the appropriate Mip protocol
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
extern int SendMipAAMobileNodeRequest();
extern int SendMipHomeAgentMIPRequest();
extern int SendMipAccountingRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Mip Protocol messages to
 *      the diameter stack. These will create the appropriate Mip protocol
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
extern int SendMipAAMobileNodeAnswer(const diameter::CommandImpl *impl);
extern int SendMipHomeAgentMIPAnswer(const diameter::CommandImpl *impl);
extern int SendMipAccountingAnswer(const diameter::CommandImpl *impl);

#endif
