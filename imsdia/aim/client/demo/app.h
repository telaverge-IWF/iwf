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
 * LOG: $Log: app.h,v $
 * LOG: Revision 3.1.28.1  2012/02/06 06:28:46  brajappa
 * LOG: Resolved compilation errors caused in g++ 4.4.x
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:00  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.7  2008/03/27 11:18:28  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.5.4.1  2007/04/19 10:52:56  nvijikumar
 * LOG: Give message to BaseApplication if appId in the header is  3.
 * LOG:
 * LOG: Revision 2.5  2007/01/04 11:44:07  nvijikumar
 * LOG: Changes to send defferent types of Accounting Req.
 * LOG:
 * LOG: Revision 2.4  2006/11/08 15:02:39  hbhatnagar
 * LOG: Changes to work with DCCA state Machine
 * LOG:
 * LOG: Revision 2.3  2006/10/26 05:40:43  kamakshilk
 * LOG: Added DisplayBaseMenuToApp() in the menu.
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:23:57  kamakshilk
 * LOG: Changes to work with ITS-Diameter APIs
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:38  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.4  2006/06/21 10:09:50  kamakshilk
 * LOG: Modification for Copyright info.
 * LOG:
 * LOG: Revision 1.3  2006/06/09 13:40:54  kamakshilk
 * LOG: RfRo menu addition
 * LOG:
 * LOG: Revision 1.2  2006/04/28 06:59:24  nvijikumar
 * LOG: Code Enhancement (Documentation).
 * LOG:
 * LOG: Revision 1.1  2006/04/13 11:08:06  nvijikumar
 * LOG: Baseline demo programs
 * LOG:
 * LOG:
 *
 * ID: $Id: app.h,v 3.1.28.1 2012/02/06 06:28:46 brajappa Exp $
 ****************************************************************************/

#ifndef _SAMPLE_IDC_APP
#define _SAMPLE_IDC_APP

#include <iostream>

#include <its++.h>

#include <diameter/Command.h>

#define BASE_INTERFACE_APP_ID    0
#define BASE_ACCOUNTING_APP_ID   3
#define SH_INTERFACE_APP_ID      16777217
#define CXDX_INTERFACE_APP_ID    16777216
#define GQGQ_INTERFACE_APP_ID    16777222
#define RFRO_INTERFACE_APP_ID    4

#define BASE_APP_THREAD_INST      1
#define SH_APP_THREAD_INST        2
#define CXDX_APP_THREAD_INST      3
#define GQGQ_APP_THREAD_INST      4
#define RFRO_APP_THREAD_INST      5

/* Defines for ACR */
#define START          1
#define INTERIM        2
#define STOP           3
#define EVENT          4
#define START_AUTHSESS 5
#define EVENT_AUTHSESS 6

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
extern int BaseMenu();
extern int CxdxMenu();
extern int ShMenu();
extern int GqMenu();
extern int RfRoMenu();
extern int DisplayBaseMenuToApp();

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
extern int BaseMessage(const diameter::CommandImpl *impl, unsigned int &);
extern int CxdxMessage(const diameter::CommandImpl *impl, unsigned int &);
extern int ShMessage(const diameter::CommandImpl *impl, unsigned int &);
extern int GqMessage(const diameter::CommandImpl *impl, unsigned int &);
extern int RfRoMessage(const diameter::CommandImpl *impl, unsigned int &);

/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Base Protocol messages to
 *      the diameter stack. These will create the appropriate Base protocol
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
 *      On success returns ITS_SUCCESS.
 *
 *  Notes:
 *
 *  See Also:
 *      SendToStack()
 ****************************************************************************/
extern int SendAccountingRequest(int requestType = START,
                                 const diameter::CommandImpl* impl = NULL);
extern int SendCapabilitiesExchangeRequest();
extern int SendDeviceWatchdogRequest();
extern int SendDisconnectPeerRequest();
extern int SendReAuthRequest();
extern int SendSessionTerminationRequest();
extern int SendAbortSessionRequest();


/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Base Protocol messages to
 *      the diameter stack. These will create the appropriate Base protocol
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
 *      On success returns ITS_SUCCESS.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern int SendAccountingAnswer(const diameter::CommandImpl *impl);
extern int SendCapabilitiesExchangeAnswer(const diameter::CommandImpl *impl);
extern int SendDeviceWatchdogAnswer(const diameter::CommandImpl *impl);
extern int SendDisconnectPeerAnswer(const diameter::CommandImpl *impl);
extern int SendReAuthAnswer(const diameter::CommandImpl *impl);
extern int SendSessionTerminationAnswer(const diameter::CommandImpl *impl);
extern int SendAbortSessionAnswer(const diameter::CommandImpl *impl);

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
extern int SendLocationInfoRequest();
extern int SendPushProfileRequest();
extern int SendServerAssignmentRequest();
extern int SendMultimediaAuthRequest();
extern int SendRegistrationTerminationRequest();
extern int SendUserAuthorizationRequest();

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
extern int SendLocationInfoAnswer(const diameter::CommandImpl *impl);
extern int SendPushProfileAnswer(const diameter::CommandImpl *impl);
extern int SendServerAssignmentAnswer(const diameter::CommandImpl *impl);
extern int SendMultimediaAuthAnswer(const diameter::CommandImpl *impl);
extern int SendRegistrationTerminationAnswer(const diameter::CommandImpl *impl);
extern int SendUserAuthorizationAnswer(const diameter::CommandImpl *impl);


/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Sh Protocol messages to
 *      the diameter stack. These will create the appropriate Sh protocol
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
extern int SendProfileUpdateRequest();
extern int SendPushNotificationRequest();
extern int SendSubscribeNotificationsRequest();
extern int SendUserDataRequest();

/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the Sh Protocol messages to
 *      the diameter stack. These will create the appropriate Sh protocol
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
extern int SendUserDataAnswer(const diameter::CommandImpl* impl);
extern int SendProfileUpdateAnswer(const diameter::CommandImpl* impl);
extern int SendSubscribeNotificationsAnswer(const diameter::CommandImpl*
                                            impl);
extern int SendPushNotificationAnswer(const diameter::CommandImpl* impl);

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
extern int SendAARequest();
extern int SendRARequest();
extern int SendSTRequest();
extern int SendASRequest();

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
extern int SendAAAnswer(const diameter::CommandImpl *impl);
extern int SendRAAnswer(const diameter::CommandImpl *impl);
extern int SendSTAnswer(const diameter::CommandImpl *impl);
extern int SendASAnswer(const diameter::CommandImpl *impl);

/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the RfRo Protocol messages to
 *      the diameter stack. These will create the appropriate RfRo protocol
 *      Request Command objects, populate the AVPs and send the
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
//extern int SendCreditControlRequest();
extern int SendCreditControlRequest(int);

/*  implementation: public
 ****************************************************************************
 *  Purpose:
 *      Utility functions to send the RfRo Protocol messages to
 *      the diameter stack. These will create the appropriate RfRo protocol
 *      Answer Command objects, populate the AVPs and send the
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
extern int SendCreditControlAnswer(const diameter::CommandImpl *impl);

#endif
