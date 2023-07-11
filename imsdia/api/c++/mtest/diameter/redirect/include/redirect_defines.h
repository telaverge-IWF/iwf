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
 *
 * ID: $Id: redirect_defines.h,v 1.1 2009/03/19 16:30:21 ssaxena Exp $
 ****************************************************************************/
#ident "$Id: redirect_defines.h,v 1.1 2009/03/19 16:30:21 ssaxena Exp $"

#ifndef _SAMPLE_CXDXAPP_DEFINE
#define _SAMPLE_CXDXAPP_DEFINE

#ifndef _SAMPLE_APP
#include <diameter/Command.h>
#endif

/**
 * Standard ApplicationId's defined by IANA
 **/
#define BASE_INTERFACE_APP_ID    0
#define BASE_ACCOUNTING_APP_ID   3
#define SH_INTERFACE_APP_ID      16777217
#define CXDX_INTERFACE_APP_ID    16777216
#define GQGQ_INTERFACE_APP_ID    16777222
#define RFRO_INTERFACE_APP_ID    4
#define REDIRECT_APP_ID          0xffffffff        // Only 8F


/**
 * The Application Worker Queue Id for Cx interface
 * (Worker: Thread with an associated TaskQueue)
 **/
#define REDIRECT_APP_TQ_INST      1


extern char subsProfile[2000];

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
 *      Utility functions to send the CxDx Protocol messages to
 *      the diameter stack. These will create the appropriate CxDx protocol
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


//extern int SendRedirectAnsMsg(const diameter::CommandImpl *impl);

#endif
