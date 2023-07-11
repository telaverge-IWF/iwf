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
 * LOG: Revision 3.1  2008/03/31 10:33:22  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.13  2006/06/07 15:02:02  tpanda
 * LOG: Code added for Load test
 * LOG:
 * LOG: Revision 1.12  2006/06/06 14:33:44  tpanda
 * LOG: Handle Error Response
 * LOG:
 * LOG: Revision 1.11  2006/06/02 04:44:19  kamakshilk
 * LOG: RfRo prototypes added
 * LOG:
 * LOG: Revision 1.10  2006/05/24 04:59:29  nvijikumar
 * LOG: Seperating the defines to app_defines file.
 * LOG:
 * LOG: Revision 1.9  2006/04/26 21:39:22  ahanda
 * LOG: Added subsProfile
 * LOG:
 * LOG: Revision 1.8  2006/04/25 13:47:00  yranade
 * LOG: 1. Code Enhancements (Added Comments, Flowerboxes)
 * LOG: 2. Method to Inject Hex Dumps
 * LOG:
 * LOG: Revision 1.7  2006/04/22 00:11:12  ahanda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.6  2006/04/17 16:03:08  yranade
 * LOG: Load Generator Functionality.
 * LOG:
 * LOG: Revision 1.5  2006/03/22 08:35:39  nvijikumar
 * LOG: Changes for auto response
 * LOG:
 * LOG: Revision 1.4  2006/03/20 06:36:35  yranade
 * LOG: Cleanups.
 * LOG:
 * LOG: Revision 1.3  2006/03/20 04:30:11  nvijikumar
 * LOG: Added Get functions for(Origin/Dest) Host and (Origin/Dest) Realm
 * LOG:
 * LOG: Revision 1.2  2006/03/08 08:48:58  nvijikumar
 * LOG: app.h updation with respect to GqGq prime
 * LOG:
 * LOG: Revision 1.1  2006/03/03 14:17:08  sumag
 * LOG: First Version of Demo Application.
 * LOG:
 *
 * ID: $Id: app.h,v 3.1 2008/03/31 10:33:22 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: app.h,v 3.1 2008/03/31 10:33:22 nvijikumar Exp $"

#ifndef _SAMPLE_APP
#define _SAMPLE_APP

#include <iostream.h>

#include <its++.h>
#include <engine++.h>

#include <diameter/Command.h>
#include <diameter/base/BaseAVP.h>

extern char subsProfile[];

/* 
 * Application Specific Variables
 */

extern int commandSet;

enum ApplicationMode
{
    UNIT_TEST = 1,
    LOAD_TEST = 2
};

/* Used only for UnitTest */
enum RunMode
{
    INITIATOR = 1,
    RECEIVER  = 2
};

extern ApplicationMode appMode;
extern RunMode runMode;

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
 *      Application Interface Specific Thread Functions
 *      This demo simulates 4 Application specific workers
 *      1. Worker that processes Base Protocol Messages
 *      2. Worker that processes Sh Interface Messages
 *      3. Worker that processes CxDx Interface Messages
 *      4. Worker that processes GqGq' Interface Messages
 *      The following are the individual thread functions.
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
 *      None
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern "C"
void BaseThreadFunc(its::ThreadPoolThread* thr, void* arg);

extern "C"
void ShThreadFunc(its::ThreadPoolThread* thr, void* arg);

extern "C"
void CxDxThreadFunc(its::ThreadPoolThread* thr, void* arg);

extern "C"
void GqThreadFunc(its::ThreadPoolThread* thr, void* arg);

extern "C"
void RfRoThreadFunc(its::ThreadPoolThread* thr, void* arg);

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Sender Thread Function
 *
 *  Input Parameters:
 *      thr - type ThreadPoolThread. arg - type void..
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

extern "C"
void SenderThreadFunc(its::ThreadPoolThread* thr, void* arg);

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility function to send a Command(Request/Answer) to Base Diameter
 *      Stack.
 *
 *  Input Parameters:
 *      diameter::Command* impl: Pointer to the Command Object. 
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
extern int
SendToStack(diameter::Command* impl);

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
extern int DisplayBaseMenu();
extern int DisplayCxdxMenu();
extern int DisplayShMenu();
extern int DisplayGqMenu();
extern int DisplayRfRoMenu();
extern int DisplayAllDiaMenu();

/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *      Utility functions to send the command to the diameter
 *      stack based on the option selected in the menu.
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
extern int SendDiameterMessage(int input);
extern int SendBaseMessage(int input);
extern int SendShMessage(int input);
extern int SendCxdxMessage(int input);
extern int SendGqMessage(int input);
extern int SendRfRoMessage(int input);

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
extern int SendAccountingRequest();
extern int SendCapabilitiesExchangeRequest();
extern int SendDeviceWatchdogRequest();
extern int SendDisconnectPeerRequest();
extern int SendReAuthRequest();
extern int SendSessionTerminationRequest(const diameter::base::SessionId *sesId=0);
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
extern int SendCreditControlRequest();
extern int SendCreditControlAnswer(const diameter::CommandImpl* impl);

/* Load Generator Specific */
typedef int (*LoadGenFunc)();
extern
LoadGenFunc TrafficGeneratorFunc;
extern int GenerateLoad();

extern void InjectDump(ITS_USHORT inst);
/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *       
 *         Utility function to handle error responses
 *
 *  Input Parameters:
 *      const diameter::CommandImpl *impl: Pointer to the received Error response 
 *      Command 
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
extern int HandleErrorResponse(const diameter::CommandImpl *impl);
/*  implementation: public
 ****************************************************************************
 *  Purpose: 
 *       
 *         Utility function to handle base messages from other application
 *
 *  Input Parameters:
 *      const diameter::CommandImpl *impl: Pointer to the received Error response 
 *      Command 
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
extern int HandleBaseMessages(const diameter::CommandImpl *impl);
#endif
