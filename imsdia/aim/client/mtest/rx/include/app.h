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
 * LOG: $Log: app.h,v $
 * LOG: Revision 3.1  2008/03/31 10:33:02  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.2  2006/11/07 13:22:30  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1  2006/10/03 09:21:28  rrath
 * LOG: Baseline distributed demo for new IMS Interfaces.
 * LOG:
 * LOG:
 * ID: $Id: app.h,v 3.1 2008/03/31 10:33:02 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: app.h,v 3.1 2008/03/31 10:33:02 nvijikumar Exp $"

#ifndef _SAMPLE_IDC_APP
#define _SAMPLE_IDC_APP

#include <iostream.h>

#include <its++.h>

#include <diameter/Command.h>

#define BASE_INTERFACE_APP_ID    0
#define RX_INTERFACE_APP_ID      16777229
#define VENDOR_ID                10415

#define BASE_APP_THREAD_INST      1
#define RX_APP_THREAD_INST        2

/* Macro to log/display the error messages
*/
#define APP_TRACE_ERROR(x) \
              printf x

extern int mode;
extern int choice;

extern const char* orHost;
extern const char* orRealm;
extern const char* dhHost;
extern const char* drRealm;

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Utility methods that are used to get the user configured values
 *     that are passed as commandLine options to the sample program
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
 *     Appropriate (OriginHost, OriginRealm, DestinationHost, DestinationRealm)
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
const char* GetOriginHost();
const char* GetOriginRealm();
const char* GetDestinationHost();
const char* GetDestinationRealm();

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *     Utility methods that are used to set the user configured values
 *     that are passed as commandLine options to the sample program
 *
 *  Input Parameters:
 *     Appropriate (OriginHost, OriginRealm, DestinationHost, DestinationRealm)
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
void SetOriginHost(const char* OriginHost);
void SetOriginRealm(const char* OriginRealm);
void SetDestinationHost(const char* DestinationHost);
void SetDestinationRealm(const char* DestinationRealm);

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
extern int RxMenu();

/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to handle the incomming message 
 *      based on the respective protocol interface.
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
 *      SendToStack()
 ****************************************************************************/
extern int RxMessage(const diameter::CommandImpl *impl, unsigned int &);

/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the CxDx Protocol messages to
 *      the diameter stack. These will create the appropriate CxDx protocol
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
extern int SendRxASRequest();
extern int SendRxRARequest();
extern int SendRxSTRequest();

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
extern int SendRxAAAnswer(const diameter::CommandImpl *impl);
extern int SendRxASAnswer(const diameter::CommandImpl *impl);
extern int SendRxRAAnswer(const diameter::CommandImpl *impl);
extern int SendRxSTAnswer(const diameter::CommandImpl *impl);

#endif
