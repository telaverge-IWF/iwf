/********************************-*-CPP-*-***********************************
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
 * LOG: $Log: sample_cxdx.cpp,v $
 * LOG: Revision 3.2  2009/03/09 09:22:31  rajeshak
 * LOG: Changed LIR/LIA as stateless
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:26  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.4  2006/10/23 06:42:12  nvijikumar
 * LOG: Menu to send Base Protocol Messages from Application.
 * LOG:
 * LOG: Revision 1.3  2006/10/17 17:22:01  tpanda
 * LOG: SetSessionIndex changed to setSessionIndex
 * LOG:
 * LOG: Revision 1.2  2006/10/17 09:20:39  yranade
 * LOG: ITS-Diameter specifics.
 * LOG:
 * LOG: Revision 1.1  2006/10/17 06:28:20  tpanda
 * LOG: Baseline ITS Demo.
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:42  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.20  2006/08/19 11:17:27  sumag
 * LOG: deleted the STR menu item
 * LOG:
 * LOG: Revision 1.19  2006/06/30 14:20:03  nvijikumar
 * LOG: Small changes for menu exit function.
 * LOG:
 * LOG: Revision 1.18  2006/06/30 10:28:13  nvijikumar
 * LOG: Changes for Exit function.
 * LOG:
 * LOG: Revision 1.17  2006/06/07 15:00:20  tpanda
 * LOG: Code added for load testing
 * LOG:
 * LOG: Revision 1.16  2006/06/07 11:07:54  tpanda
 * LOG: Handling of error responses
 * LOG:
 * LOG: Revision 1.15  2006/05/26 14:10:59  yranade
 * LOG: Support for CC Compiler.
 * LOG:
 * LOG: Revision 1.14  2006/05/24 04:45:55  nvijikumar
 * LOG: defines for Commandcodes and correcting the code comments.
 * LOG:
 * LOG: Revision 1.13  2006/05/08 16:46:07  yranade
 * LOG: Minor updates to menu.
 * LOG:
 * LOG: Revision 1.12  2006/05/08 10:04:16  nvijikumar
 * LOG: Changes according to Tushar's input(Proxy,RouteRcord,Originstate,..etc).
 * LOG:
 * LOG: Revision 1.11  2006/04/26 21:38:57  ahanda
 * LOG: Cleaner data. Added support for sending Subscriber Profile
 * LOG:
 * LOG: Revision 1.10  2006/04/25 15:31:02  nvijikumar
 * LOG: Code Enhancement, Documentation (viji)
 * LOG:
 * LOG: Revision 1.9  2006/04/22 00:07:16  ahanda
 * LOG: Entered some sane data and cleaned up menus
 * LOG:
 * LOG: Revision 1.8  2006/04/17 16:27:35  yranade
 * LOG: Hooks for statistics.
 * LOG:
 * LOG: Revision 1.7  2006/03/22 14:25:34  nvijikumar
 * LOG: Redefining the Menu
 * LOG:
 * LOG: Revision 1.6  2006/03/22 08:34:58  nvijikumar
 * LOG: Chages for auto response
 * LOG:
 * LOG: Revision 1.5  2006/03/20 06:37:56  yranade
 * LOG: Updates to use new AllocateSessionIndex API.
 * LOG:
 * LOG: Revision 1.4  2006/03/18 12:16:56  nvijikumar
 * LOG: Set Host (Origin/Dest) and Realm (Origin/Dest) based on User Input.
 * LOG:
 * LOG: Revision 1.3  2006/03/13 16:52:33  yranade
 * LOG: Updates based on changes in dframe.
 * LOG:
 * LOG: Revision 1.2  2006/03/09 11:47:32  tpanda
 * LOG: Encode/Decode feature provided by wei's api replaced our encode/decode function.Hence dia_codec.* files are redundant
 * LOG:
 * LOG: Revision 1.1  2006/03/03 14:17:08  sumag
 * LOG: First Version of Demo Application.
 * LOG:
 *
 * ID: $Id: sample_cxdx.cpp,v 3.2 2009/03/09 09:22:31 rajeshak Exp $
 ****************************************************************************/
#include <dia_defines.h>
#include <dia_frame.h>
#include <app_trace.h>

#include <diameter/cxdx/LocationInfo.h>
#include <diameter/cxdx/PushProfile.h>
#include <diameter/cxdx/ServerAssignment.h>
#include <diameter/cxdx/MultimediaAuth.h>
#include <diameter/cxdx/RegistrationTermination.h>
#include <diameter/cxdx/UserAuthorization.h>

#include <app.h>
#include <app_defines.h>
#include <app_stats.h>

using namespace std;
using namespace its;
using namespace engine;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::cxdx;

int HandleCxdxDiaMessage(its::ITS_Event & ev);

/*  implementation: public
 ****************************************************************************
 *  Purpose: Thread Function that handles messages received from the
 *      stack with AppId = CXDX_INTERFACE_APP_ID
 *
 *  Input Parameters:
 *      ThreadPoolThread* thr: ThreadPoolThread
 *      void* arg: Arguments(if any)
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
extern "C"
void CxDxThreadFunc(ThreadPoolThread * thr, void *arg)
{
    int ret;
    engine::Worker * work = (engine::Worker *) thr;

    ITS_HANDLE handle = NULL;

    ITS_USHORT inst = work->GetInstance();
    Event evt;

    while (!work->GetExit())
    {
        /*
         * Wait For Event from the event queue.
         * GetNextEvent is a BlockingCall that returns
         * when an Event is posted onto the associated worker
         * taskqueue
         */
        if (work->GetNextEvent(evt) == ITS_SUCCESS)
        {
            APP_TRACE_DEBUG(("CxDx:Received an event on Instance %d",inst));

            // If the event source is from the diameter stack,
            // handle that event. 
            switch (evt.GetSource())
            {
                case ITS_DIA_SRC:
                    APP_TRACE_DEBUG(("Received Event from ITS DiameterStack "));
                    HandleCxdxDiaMessage(evt);
                    break;
                default:
                    APP_TRACE_ERROR(("Unknown Event Received"));
                    break;
            }
        }
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function processes the message received from the base
 *      diameter stack. It identifies the commands and processes that command.
 *
 *  Input Parameters:
 *     ITS_Event& ev: Event Received from the Queue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On success returns ITS_SUCCESS
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int HandleCxdxDiaMessage(ITS_Event & ev)
{
    /*
     * Access the diameter stack HANDLE
     * via the DiaFrame Singleton Object Pointer
     */
    DiaFrame * diaFrame = DiaFrame::GetDiaFrame();

    if (diaFrame)
    {
        // Create an instance DiaMsg to handle the  Received Message
        DiaMsg * dMsg;

        // Receive the message from the event received
        if (diaFrame->Receive(ev, &dMsg) != ITS_SUCCESS)
        {
            APP_TRACE_ERROR(("Failed to Receive Diameter Message"));
            return -1;
        }


        // If the message is the indication from the stack,
        // Handle the Indication. In this case, we simply update
        // the indication statistics.
        
        if(dMsg->IsIndication())
        {
            APP_TRACE_DEBUG(("Received Indication from Stack %d\n",
                             dMsg->GetIndication()));

             APPStats::GetAPPStats()->UpdateRecvIndications(
                                      dMsg->GetIndication());
        }
        // If not an indication, then it is a Command Message
        else
        {
            // Get the command instance from the message.

            const diameter::CommandImpl* impl = dMsg->GetCommandImpl();
            ITS_BOOLEAN isReq = impl->isRequest() ? ITS_TRUE:ITS_FALSE;

            // Update the receive statistics
            APPStats::GetAPPStats()->UpdateRecvStats(impl->getCommandCode(), 
                                                     isReq);
            try
            {
                // Process the commands based on the command code.
                if(impl->isError())
                {
                   HandleErrorResponse(impl);
                }
                else if(impl->getApplicationId() == 0)//Base protocol
                {
                   HandleBaseMessages(impl);
                }
                else
                {
                   switch (impl->getCommandCode())
                   {
                     case CXDX_UA_MSG_CMD_CODE:
                          if (impl->isRequest())
                          {
                            UserAuthorizationRequest
                            uareq(*impl);
                            cout <<"UserAuthorizationRequest "<< uareq << endl;
                            SendUserAuthorizationAnswer(impl);
                          }
                          else
                          {
                            UserAuthorizationAnswer
                            uaans(*impl);
                            cout << "UserAuthorizationAnswer " << uaans << endl;
                          }
                          break;
                     case CXDX_SA_MSG_CMD_CODE:
                         if (impl->isRequest())
                         {
                            ServerAssignmentRequest
                               sareq(*impl);
                            cout << "ServerAssignmentRequest" << sareq << endl;
                            SendServerAssignmentAnswer(impl);
                         }
                         else
                         {
                            ServerAssignmentAnswer
                              saans(*impl);
                            cout << "ServerAssignmentAnswer" << saans << endl;
                         }
                         break;

                     case CXDX_LI_MSG_CMD_CODE:
                        if (impl->isRequest())
                        {
                           LocationInfoRequest
                             lireq(*impl);
                           if (appMode == UNIT_TEST)
                           cout << "LocationInfoRequest" << lireq << endl;
                           SendLocationInfoAnswer(impl);
                        }
                        else
                        {
                           LocationInfoAnswer
                              lians(*impl);
                           if (appMode == UNIT_TEST)
                           cout << "LocationInfoAnswer" << lians << endl;
                        }
                        break;

                     case CXDX_MA_MSG_CMD_CODE:
                        if (impl->isRequest())
                        {
                           MultimediaAuthRequest
                             mareq(*impl);
                           cout << "MultimediaAuthRequest" << mareq << endl;
                           SendMultimediaAuthAnswer(impl);
                        }
                        else
                        {
                           MultimediaAuthAnswer
                              maans(*impl);
                           cout << "MultimediaAuthAnswer" << maans << endl;
                        }
                        break;
           
                    case CXDX_RT_MSG_CMD_CODE:
                       if (impl->isRequest())
                       {
                          RegistrationTerminationRequest
                            rtreq(*impl);
                          cout << "RegistrationTerminationRequest" << rtreq 
                             <<endl;
                          SendRegistrationTerminationAnswer(impl);
                       }
                       else
                       {
                          RegistrationTerminationAnswer
                            rtans(*impl);
                          cout << "RegistrationTerminationAnswer" << rtans 
                             <<endl;
                       }
                       break;

                    case CXDX_PP_MSG_CMD_CODE:
                       if (impl->isRequest())
                       {
                          PushProfileRequest
                            ppreq(*impl);
                          cout << "PushProfileRequest" << ppreq << endl;
                          SendPushProfileAnswer(impl);
                       }
                       else
                       {
                          PushProfileAnswer
                            ppans(*impl);
                          cout << "PushProfileAnswer" << ppans << endl;
                       }
                       break;
                      default:
                       break;
                    }
                }
            }
            catch (NoSuchAttributeException e)
            {
                APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ", 
                                 e.name(), e.what()));
            }
            catch (WrongCommandTypeException e)
            {
                APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ", 
                                 e.name(), e.what()));
            }
            catch (UnknownTypeException e)
            {
                APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ", 
                                 e.name(), e.what()));
            }
            catch (CodecException e)
            {
                APP_TRACE_ERROR(("Exception Caught: %s , Error Cause: %s ", 
                                 e.name(), e.what()));
            }
            catch (...)
            {
                APP_TRACE_ERROR(("Unknown Exception Caught"));
            }

        }
        if (dMsg)
            delete dMsg;
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: 
 *      This function displays the menu options for the Cxdx interface
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
 *      input - User choice of type integer.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int DisplayCxdxMenu()
{
    string input;
    int ret = 0;

    do
    {
        cout << endl << "Select Cx/Dx Command" <<endl << endl;
        cout << "1: LIR - Location Info Request" << endl;
        cout << "2: MAR - Multimedia Auth Request" << endl;
        cout << "3: PPR - Push Profile Request" << endl;
        cout << "4: RTR - Registration Termination Request" << endl;
        cout << "5: SAR - Server Assignment Request" << endl;
        cout << "6: UAR - User Authorization Request" << endl;
        cout << "7: To Send Base Protocol Messages " << endl;
        cout << "99: To Exit" << endl;

        cin >> input;

        ret=atoi(input.c_str());

    } while ((ret < 1 || ret > 7) && ret!=99);
    
    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the request to the diameter
 *      stack based on the option selected in the menu.
 *
 *  Input Parameters:
 *      int input: User choice.
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
int SendCxdxMessage(int input)
{
    switch (input)
    {
        case 1:
            SendLocationInfoRequest();
            break;
        case 2:
            SendMultimediaAuthRequest();
            break;
        case 3:
            SendPushProfileRequest();
            break;
        case 4:
            SendRegistrationTerminationRequest();
            break;
        case 5:
            SendServerAssignmentRequest();
            break;
        case 6:
            SendUserAuthorizationRequest();
            break;
        case 7:
            DisplayBaseMenuToApp();
            break;
        case 99:
            {
                DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
                if (diaFrame)
                {
                    diaFrame->Terminate();
                }
                exit(EXIT_SUCCESS);
            }
        default:
            cout << endl << "please enter the correct choice";
            break;
    }
    return 0;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the LocationInfo request to the
 *      diameter stack. Create the LocationInfo Request object,
 *      populate the AVPs and send the message to the stack.
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
int SendLocationInfoRequest()
{
    // [1] The Location-Info-Request command is sent by a Diameter
    // Multimedia Client to a Diameter Multimedia Server in order to
    // request the name of the server that is currently serving the user
    // Command-Code = 302 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.

    LocationInfoRequest lir(false, false);

    // [2.1.1.x] Populate fixed AVPs.

    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    DiaFrame *diaFrame = DiaFrame::GetDiaFrame();
    string sessIdString;
    ITS_UINT sIdx;
    if (diaFrame->AllocateSessionIndex(CXDX_INTERFACE_APP_ID, sIdx,
                                       sessIdString) == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("Succesfull Session Allocation"));
        APP_TRACE_DEBUG(("SessionIdx = %d, SessionId = %s", sIdx,
                         sessIdString.c_str()));
    }
    else
    {
        APP_TRACE_ERROR(("Failure in Session Allocation"));
        return (ITS_ESENDFAIL);
    }

    lir.setSessionId(SessionId(sessIdString));
    lir.setSessionIndex(sIdx);

    // [2.1.2.x] Required AVPS

    // [2.1.2.1.1] Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter
    // application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as
    // possible.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.1.2.1.2] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(VENDOR_ID);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // [2.1.2.1.3] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(CXDX_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // [2.1.2.1.4] Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting
    // messages.
    // Exactly one of the Auth-Application-Id AVP and Acct-Application-Id
    // may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    //[2.1.2.1] Set the  Vendor-Specific-Application-Id AVP.
    lir.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // Create a Auth-Session-State AVP object.
    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    // [2.1.2.2] Set the Auth-Session-State AVP.
    AuthSessionState authSessionState(AuthSessionState::NO_STATE_MAINTAINED);
    lir.setAuthSessionState(authSessionState);

    // [2.1.2.3] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    lir.setOriginHost(originHost);

    // [2.1.2.4] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    lir.setOriginRealm(originRealm);

    // [2.1.2.5] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    lir.setDestinationRealm(destinationRealm);

    // [2.1.2.6] Set the Public-Identity AVP.
    // The Public-Identity AVP contains the public identity of a
    // user in the IMS.
    // The AVP Code of Public-Identity AVP is 601
    // The data type of Public-Identity AVP is UTF8String.

    PublicIdentity publicIdentity("sip:user@intellinet-tech.com");

    lir.setPublicIdentity(publicIdentity);

    // [2.2.x] optional AVPS

    // [2.2.1] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    lir.setDestinationHost(destinationHost);

    // [2.2.2.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1, proxyInfo2;

    // [2.2.2.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"), proxyHost2("proxyHost1");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // [2.2.2.3] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState proxyState1("proxyState1"), proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // [2.2.2] Set the Proxy-Info AVP.
    // Application should not set this AVP.
    // lir.addProxyInfo(proxyInfo2);

    // [2.2.3] Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord routeRecord1("nemo"), routeRecord2("nemocl");

    // [2.2] Set the Route-Record AVP.
    // Application should not set this AVP.
    // lir.addRouteRecord(routeRecord1);

    // lir.addRouteRecord(routeRecord2);

    // 3. Send the encoded LocationInfoRequest object to an output stream
    //    buffer(Note: For test purpose, the object is being sent to ios::cout
    //    output buffer.
    if (appMode == UNIT_TEST)
    cout << lir;

    SendToStack(&lir);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the  MultimediaAuthRequest to the
 *      diameter stack. Create the  MultimediaAuthRequest object,
 *      populate the AVPs and send the message to the stack.
 *
 *  Input Parameters:
 *      User choice.
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
int SendMultimediaAuthRequest()
{
    // [1]. Create an instance of MultimediaAuthRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    MultimediaAuthRequest mar(false, false);

    // [2.1.1.x] Fixed AVP    
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    DiaFrame* diaFrame = DiaFrame::GetDiaFrame();
    string sessIdString;
    ITS_UINT sIdx;
    if (diaFrame->AllocateSessionIndex(CXDX_INTERFACE_APP_ID, 
                                        sIdx,sessIdString) 
                                        == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("Succesfull Session Allocation"));
        APP_TRACE_DEBUG(("SessionIdx = %d, SessionId = %s", sIdx, 
                         sessIdString.c_str()));
    }
    else
    {
        APP_TRACE_ERROR(("Failure in Session Allocation"));
        return (ITS_ESENDFAIL);
    }

    mar.setSessionId(SessionId(sessIdString));
    mar.setSessionIndex(sIdx);

    // [2.1.2.x] Required AVPs

    // [2.1.2.1.1]Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as possible.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.1.2.1.2] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(VENDOR_ID);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // Set the Auth-Application-Id AVP.
    // [2.1.2.1.3] The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.

    AuthApplicationId authApplicationId(CXDX_INTERFACE_APP_ID);

    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // [2.1.2.1.4] Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting 
    // messages.Exactly one of the Auth-Application-Id AVP and Acct-
    // Application-Id may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    //[2.1.2.1] Set the  Vendor-Specific-Application-Id AVP.
    mar.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // [2.1.2.2]Create a Auth-Session-State AVP object.
    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    mar.setAuthSessionState(authSessionState);

    // [2.1.2.3] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    mar.setOriginHost(originHost);

    // [2.1.2.4] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    mar.setOriginRealm(originRealm);

    // [2.1.2.5] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    mar.setDestinationRealm(destinationRealm);

    // [2.1.2.6] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    mar.setUserName(userName);

    // [2.1.2.7] Set the Public-Identity AVP.
    //The Public-Identity AVP contains the public identity of a user in the IMS.
    // The AVP Code of Public-Identity AVP is 601
    // The data type of Public-Identity AVP is UTF8String.
    PublicIdentity publicIdentity("sip:user@intellinet-tech.com");
    mar.setPublicIdentity(publicIdentity);

    // [2.1.2.8] Set the Server-Name AVP.
    // The Server-Name AVP contains a SIP-URL and used to
    // identify a SIP server (e.g. S-CSCF name).
    // The AVP Code of AVP is 602.
    // The data type of AVP is UTF8String.
    ServerName serverName("sip:cscf@3gppnetwork.com");
    mar.setServerName(serverName);

    // [2.2.x] Optional AVPS

    // [2.2.1] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    mar.setDestinationHost(destinationHost);

    // [2.2.2] Set the SIP-Number-Auth-Items AVP.
    // The SIP-Number-Auth-Items AVP indicates the number of
    // The AVP Code of SIP-Number-Auth-Items AVP is 607
    // The Data Type of SIP-Number-Auth-Items AVP is Unsigned32
    SIPNumberAuthItems sIPNumberAuthItems(1u);
    mar.setSIPNumberAuthItems(sIPNumberAuthItems);

    // Create a SIP-Auth-Data-Item AVP object
    SIPAuthDataItem sIPAuthDataItem;

    // [2.2.3.1] Set the SIP-Item-Number AVP.
    // The SIP-Item-Number AVPs indicate the order in which the
    // multiple occurrences of SIP-Auth-Data-Item AVP has to be processed.
    // The SIP-Item-Number AVP Code of AVP is 613
    // The Data Type of SIP-Item-Number AVP is Unsigned32
    SIPItemNumber sIPItemNumber(1u);
    sIPAuthDataItem.setSIPItemNumber(sIPItemNumber);

    // [2.2.3.2] Set the SIP-Authentication-Scheme AVP.
    // The SIP-Authentication-Scheme AVP indicates the authentication
    // scheme used in the authentication of SIP messages.
    // The AVP Code of SIP-Authentication-Scheme AVP is 608
    // The Data Type of SIP-Authentication-Scheme AVP is UTF8String
    SIPAuthenticationScheme sIPAuthenticationScheme("127");
    sIPAuthDataItem.setSIPAuthenticationScheme(sIPAuthenticationScheme);

    // [2.2.3.3] Set the SIP-Authenticate AVP.
    // The SIP-Authenticate AVP.
    // The AVP Code of SIP-Authenticate AVP is 609
    // The Data Type of SIP-Authenticate AVP is OctetString
    SIPAuthenticate sIPAuthenticate("1234567");
    sIPAuthDataItem.setSIPAuthenticate(sIPAuthenticate);

    // [2.2.3.4] Set the SIP-Authorization AVP.
    // The SIP-Authorization AVP contains authentication-related
    // information relevant for performing the authentication but
    // that is not part of the SIP authentication headers.
    // The AVP Code of AVP is 610
    // The Data Type of AVP is OctetString
    SIPAuthorization sIPAuthorization("1234567");
    sIPAuthDataItem.setSIPAuthorization(sIPAuthorization);

    // [2.2.3.5] Set the SIP-Authentication-Context AVP.
    // SIP-Authentication-Context AVP contains authentication-
    // related information relevant for performing the authentication
    // but that is not part of the SIP authentication headers.
    // The AVP Code of AVP is 611
    // The Data Type of AVP is OctetString
    SIPAuthenticationContext sIPAuthenticationContext("1234567");
    sIPAuthDataItem.setSIPAuthenticationContext(sIPAuthenticationContext);

    // [2.2.3.6] Set the Confidentiality-Key AVP.
    // The Confidentiality-Key AVP contains the Confidentiality Key.
    // The AVP Code of AVP is 625
    // The Data Type of AVP is OctetString
    ConfidentialityKey confidentialityKey("1234567");
    sIPAuthDataItem.setConfidentialityKey(confidentialityKey);

    // [2.2.3.7] Set the Integrity-Key AVP.
    // The Integrity-Key AVP contains the Integrity Key.
    // The AVP Code of AVP is 626
    // The Data Type of AVP is OctetString
    IntegrityKey integrityKey("1234567");
    sIPAuthDataItem.setIntegrityKey(integrityKey);

    // [2.2.3] Set the SIP-Auth-Data-Item AVP.
    // The SIP-Auth-Data-Item AVP contains the authentication and/or
    // the authorization for the Diameter client.
    // The AVP Code of SIP-Auth-Data-Item AVP is 612
    // The Data Type of SIP-Auth-Data-Item AVP is Grouped
    mar.setSIPAuthDataItem(sIPAuthDataItem);

    // [2.2.4.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // [2.2.4.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"), proxyHost2("proxyHost2");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // [2.2.4.3] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState proxyState1("proxyState1"), proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // [2.2.4] Set the Proxy-Info AVP.
    // Application should not set this AVP.
    // mar.addProxyInfo(proxyInfo2);

    // [2.2.5] Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord routeRecord1("nemo"), routeRecord2("nemocl");

    // [2.2.5] Set the Route-Record AVP.
    // Application should not set this AVP.
    // mar.addRouteRecord(routeRecord1);
    // mar.addRouteRecord(routeRecord2);

    // 3. Send the encoded MultimediaAuthRequest object to an output stream
    // buffer(Note: For test purpose, the object is being sent to ios::cout
    // output buffer.

    cout << mar;

    // Send Message to stack
    SendToStack(&mar);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the PushProfileRequest to the
 *      diameter stack. Create the PushProfileRequest object,
 *      populate the AVPs and send the message to the stack.
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
int SendPushProfileRequest()
{
    // [1]. create an instance of PushProfileRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    PushProfileRequest ppr(false, false);

    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    DiaFrame* diaFrame = DiaFrame::GetDiaFrame();
    string sessIdString;
    ITS_UINT sIdx;
    if (diaFrame->AllocateSessionIndex(CXDX_INTERFACE_APP_ID, sIdx,
                                       sessIdString) == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("Succesfull Session Allocation"));
        APP_TRACE_DEBUG(("SessionIdx = %d, SessionId = %s", sIdx,
                         sessIdString.c_str()));
    }
    else
    {
        APP_TRACE_ERROR(("Failure in Session Allocation"));
        return (ITS_ESENDFAIL);
    }

    ppr.setSessionId(SessionId(sessIdString));
    ppr.setSessionIndex(sIdx);

    // Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter
    // application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as
    // possible.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.2.5] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(VENDOR_ID);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // [2.2] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(CXDX_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // [2.2] Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting
    // messages.
    // Exactly one of the Auth-Application-Id AVP and Acct-Application-Id
    // may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    //[2.1] Set the  Vendor-Specific-Application-Id AVP.
    ppr.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // Create a Auth-Session-State AVP object.
    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    // [2.1] Set the Auth-Session-State AVP.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    ppr.setAuthSessionState(authSessionState);

    // [2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    ppr.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    ppr.setOriginRealm(originRealm);

    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    ppr.setDestinationHost(destinationHost);

    // [2.1] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    ppr.setDestinationRealm(destinationRealm);

    // [2.1] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    ppr.setUserName(userName);

    CxDxUserData userData(subsProfile);
    ppr.setCxDxUserData(userData);

    /*
    ChargingInformation cInfo;

    URI uri1("PrimaryEventChargingFunction.com", URI::AAA,3880, URI::SCTP, 
             URI::DIAMETER);

    URI uri2("SecondaryEventChargingFunction.com", URI::AAAS,3880, URI::TCP, 
             URI::DIAMETER);

    URI uri3("PrimaryEventCollectionFunction.com", URI::AAAS,3880, URI::TCP, 
             URI::DIAMETER);

    URI uri4("SecondaryEventCollectionFunction.com", URI::AAA,3880, URI::TCP, 
             URI::DIAMETER);

    cInfo.setPrimaryEventChargingFunctionName(
          PrimaryEventChargingFunctionName(uri1));

    cInfo.setSecondaryEventChargingFunctionName(
          SecondaryEventChargingFunctionName(uri2));

    cInfo.setPrimaryChargingCollectionFunctionName(
          PrimaryChargingCollectionFunctionName(uri3));

    cInfo.setSecondaryChargingCollectionFunctionName(
          SecondaryChargingCollectionFunctionName(uri4));

    ppr.setChargingInformation(cInfo); */

    // Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"),proxyHost2("proxyHost2");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState proxyState1("proxyState1"),proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // [2.2] Set the Proxy-Info AVP.
    // Application should not set this AVP.
    //ppr.addProxyInfo(proxyInfo1);
    //ppr.addProxyInfo(proxyInfo2);
    //ppr.addExtra(proxyInfo2);

    // [2.2] Set the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    // Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    // RouteRecord routeRecord1("nemo"),routeRecord2("nemocl");

    // [2.2] Set the Route-Record AVP.
    // Application should not set this AVP.
    //ppr.addRouteRecord(routeRecord1);
    //ppr.addRouteRecord(routeRecord2);

    //ppr.addExtra(routeRecord2);

    cout << ppr;

    SendToStack(&ppr);

}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the RegistrationTerminationRequest to the
 *      diameter stack. Create the RegistrationTerminationRequest object,
 *      populate the AVPs and send the message to the stack.
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
int SendRegistrationTerminationRequest()
{
    // 1. Create an instance of RegistrationTerminationRequest class
    // The Registration-Termination-Request command is sent by a Diameter
    // client to a Diameter Server in order to request deregistration
    // of a multimedia user.
    // Command-Code = 304 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    RegistrationTerminationRequest rtr(false, false);

    // 2. Create the instances of the classes describing the various
    // AVPs' present in an RegistrationTerminationRequest command and
    // pass them by value to the corresponding data members set
    // methods of the RegistrationTerminationRequest object created
    // in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    DiaFrame* diaFrame = DiaFrame::GetDiaFrame();
    string sessIdString;
    ITS_UINT sIdx;
    if (diaFrame->AllocateSessionIndex(CXDX_INTERFACE_APP_ID, sIdx,
                                       sessIdString) == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("Succesfull Session Allocation"));
        APP_TRACE_DEBUG(("SessionIdx = %d, SessionId = %s", sIdx,
                         sessIdString.c_str()));
    }
    else
    {
        APP_TRACE_ERROR(("Failure in Session Allocation"));
        return (ITS_ESENDFAIL);
    }

    rtr.setSessionId(SessionId(sessIdString));
    rtr.setSessionIndex(sIdx);

    // Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter
    // application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as
    // possible.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.2.5] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(VENDOR_ID);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // Set the Auth-Application-Id AVP.
    // [2.2] The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(CXDX_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // [2.2] Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting
    // messages.
    // Exactly one of the Auth-Application-Id AVP and Acct-Application-Id
    // may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    //[2.1] Set the  Vendor-Specific-Application-Id AVP.
    rtr.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // Create a Auth-Session-State AVP object.
    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    // [2.1] Set the Auth-Session-State AVP.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    rtr.setAuthSessionState(authSessionState);

    // [2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    rtr.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    rtr.setOriginRealm(originRealm);

    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    rtr.setDestinationHost(destinationHost);

    // [2.1] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    rtr.setDestinationRealm(destinationRealm);

    // [2.1] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    rtr.setUserName(userName);

    // for a de-registration operation.
    // The AVP Code of Degistration-Reason AVP is 615.
    // The data type of User-Name AVP is Grouped.
    DeregistrationReason deregistrationReason;

    // [2.1] Set the Reason-Code AVP.
    // The Reason-Code AVP defines the reason for the network
    // initiated de-registration.
    // The AVP Code of Reason-Code AVP is 616 .
    // The data type of Reason-Code AVP is Enumerated{0,1,2,3}.
    ReasonCode reasonCode(ReasonCode::NEW_SERVER_ASSIGNED);
    deregistrationReason.setReasonCode(reasonCode);

    // [2.2] Set the Reason-Info AVP.
    // The Reason-Info AVP contains textual information to inform
    // the user about the reason for a de-registration
    // The AVP Code of Reason-Info AVP is 617.
    // The data type of Reason-Info AVP is UTF8String.
    ReasonInfo reasonInfo("1234567");
    deregistrationReason.setReasonInfo(reasonInfo);

    // [2.1] Set the De-Registration-Reason AVP.
    rtr.setDeregistrationReason(deregistrationReason);

    // [2.1] Set the Public-Identity AVP.
    // The Public-Identity AVP contains the public identity of a
    // user in the IMS.
    // The AVP Code of Public-Identity AVP is 601
    // The data type of Public-Identity AVP is UTF8String.
    PublicIdentity publicIdentity("sip:user@intellinet-tech.com");
    rtr.addPublicIdentity(publicIdentity);

    // Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"),proxyHost2("proxyHost2");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState proxyState1("proxyState1"),proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // [2.2] Set the Proxy-Info AVP.
    // Application should not set this AVP.
    // rtr.addProxyInfo(proxyInfo1);
    // rtr.addProxyInfo(proxyInfo2);

    // [2.2] Set the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    // Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    // RouteRecord routeRecord1("routeRecord1"),routeRecord2("routeRecord2");

    // [2.2] Set the Route-Record AVP.
    // Application should not set this AVP.
    // rtr.addRouteRecord(routeRecord1);
    // rtr.addRouteRecord(routeRecord2);

    // 3. Send the encoded RegistrationTerminationRequest object to an 
    // output stream
    // buffer(Note: For test purpose, the object is being sent to ios::cout
    // output buffer.

    cout << rtr;

    SendToStack(&rtr);

}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the ServerAssignmentRequestto the
 *      diameter stack. Create the ServerAssignmentRequest object,
 *      populate the AVPs and send the message to the stack.
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

int SendServerAssignmentRequest()
{
    // 1. Create an instance of ServerAssignmentRequest class
    // The Server-Assignment-Request command is sent from a Diameter
    // multimedia client to a Diameter multimedia server in order to
    // request it to store the name of the server that is currently
    // serving the user.
    // Command-Code = 301 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    ServerAssignmentRequest sar(false, false);

    // 2. Create the instances of the classes describing the various
    // AVPs' present in an UserAuthorizationRequest command and
    // pass them by value to the corresponding data members set
    // methods of the UserAuthorizationRequest object created
    // in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    DiaFrame* diaFrame = DiaFrame::GetDiaFrame();
    string sessIdString;
    ITS_UINT sIdx;
    if (diaFrame->AllocateSessionIndex(CXDX_INTERFACE_APP_ID, sIdx,
                                       sessIdString) == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("Succesfull Session Allocation"));
        APP_TRACE_DEBUG(("SessionIdx = %d, SessionId = %s", sIdx,
                         sessIdString.c_str()));
    }
    else
    {
        APP_TRACE_ERROR(("Failure in Session Allocation"));
        return (ITS_ESENDFAIL);
    }

    sar.setSessionId(SessionId(sessIdString));
    sar.setSessionIndex(sIdx);

    // Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter
    // application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as
    // possible.
    VendorSpecificApplicationId        vendorSpecificApplicationId1;

    // [2.2.5] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(VENDOR_ID);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // Set the Auth-Application-Id AVP.
    // [2.2] The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(CXDX_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // [2.2] Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting
    // messages.
    // Exactly one of the Auth-Application-Id AVP and Acct-Application-Id
    // may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    //AcctApplicationId acctApplicationId(12);
    //vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    //[2.1] Set the  Vendor-Specific-Application-Id AVP.
    sar.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // Create a Auth-Session-State AVP object.
    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    // [2.1] Set the Auth-Session-State AVP.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    sar.setAuthSessionState(authSessionState);

    // [2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    sar.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    sar.setOriginRealm(originRealm);

    // [2.2] Set the Server-Name AVP.
    // The Server-Name AVP contains a SIP-URL and used to
    // identify a SIP server (e.g. S-CSCF name)..
    // The AVP Code of AVP is .
    // The data type of AVP is UTF8String.
    ServerName serverName("sip:cscf@3gppnetwork.com");
    sar.setServerName(serverName);

    ServerAssignmentType serverAssignmentType(ServerAssignmentType::
                                              NO_ASSIGNMENT);
    sar.setServerAssignmentType(serverAssignmentType);

    UserDataAlreadyAvailable userDataAlreadyAvailable(UserDataAlreadyAvailable
                                                   ::USER_DATA_NOT_AVAILABLE);
    sar.setUserDataAlreadyAvailable(userDataAlreadyAvailable);

    // [2.1] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    sar.setDestinationRealm(destinationRealm);

    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    sar.setDestinationHost(destinationHost);

    // [2.1] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    sar.setUserName(userName);

    // [2.1] Set the Public-Identity AVP.
    // The Public-Identity AVP contains the public identity of a
    // user in the IMS.
    // The AVP Code of Public-Identity AVP is 601
    // The data type of Public-Identity AVP is UTF8String.
    PublicIdentity publicIdentity("sip:user@intellinet-tech.com");
    sar.addPublicIdentity(publicIdentity);

    // Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1, proxyInfo2;

    // Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"),proxyHost2("proxyHost1");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // The data type of is OctetString.
    //ProxyState proxyState1("proxyState1"),proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // [2.2] Set the Proxy-Info AVP.
    // Application should not set this AVP.
    // sar.addProxyInfo(proxyInfo1);
    // sar.addProxyInfo(proxyInfo2);
    //ppr.addExtra(proxyInfo2);

    // Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord routeRecord1("routeRecord1"),
    //routeRecord2("routeRecord2");

    // [2.2] Set the Route-Record AVP.
    // Application should not set this AVP.
    //sar.addRouteRecord(routeRecord1);
    //sar.addRouteRecord(routeRecord2);

    cout << sar;

    SendToStack(&sar);

}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the UserAuthorizationRequest to the
 *      diameter stack. Create the UserAuthorizationRequest object,
 *      populate the AVPs and send the message to the stack.
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
int SendUserAuthorizationRequest()
{

    // 1. Create an instance of UserAuthorizationRequest class
    // The User-Authorization-Request command is sent by a Diameter
    // client to a Diameter Server in order to request authorization
    // of the registration of a multimedia user with
    // Command-Code = 300 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    UserAuthorizationRequest uar(false, false);

    // 2. Create the instances of the classes describing the various
    // AVPs' present in an UserAuthorizationRequest command and
    // pass them by value to the corresponding data members set
    // methods of the UserAuthorizationRequest object created
    // in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    DiaFrame* diaFrame = DiaFrame::GetDiaFrame();
    string sessIdString;
    ITS_UINT sIdx;
    if (diaFrame->AllocateSessionIndex(CXDX_INTERFACE_APP_ID, sIdx,
                                       sessIdString) == ITS_SUCCESS)
    {
        APP_TRACE_DEBUG(("Succesfull Session Allocation"));
        APP_TRACE_DEBUG(("SessionIdx = %d, SessionId = %s", sIdx,
                         sessIdString.c_str()));
    }
    else
    {
        APP_TRACE_ERROR(("Failure in Session Allocation"));
        return (ITS_ESENDFAIL);
    }

    uar.setSessionId(SessionId(sessIdString));
    uar.setSessionIndex(sIdx);

    // Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter
    // application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as
    // possible.
    VendorSpecificApplicationId        vendorSpecificApplicationId1;

    // [2.2.5] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(VENDOR_ID);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // Set the Auth-Application-Id AVP.
    // [2.2] The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(CXDX_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // [2.2] Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting
    // messages.
    // Exactly one of the Auth-Application-Id AVP and Acct-Application-Id
    // may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    //AcctApplicationId acctApplicationId(2);
    //vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    //[2.1] Set the  Vendor-Specific-Application-Id AVP.
    uar.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // Create a Auth-Session-State AVP object.
    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    // [2.1] Set the Auth-Session-State AVP.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    uar.setAuthSessionState(authSessionState);

    // [2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    uar.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    uar.setOriginRealm(originRealm);

    // [2.1] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    uar.setDestinationRealm(destinationRealm);

    // [2.1] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    uar.setUserName(userName);

    // [2.1] Set the Public-Identity AVP.
    // The Public-Identity AVP contains the public identity of a
    // user in the IMS.
    // The AVP Code of Public-Identity AVP is 601
    // The data type of Public-Identity AVP is UTF8String.
    PublicIdentity publicIdentity("sip:user@intellinet-tech.com");
    uar.setPublicIdentity(publicIdentity);

    // [2.1] Set the Visited-Network-Identifier AVP.
    // The AVP is used to identity a specific session and must appear
    // immediately following the Diameter header.
    // The AVP Code of Visited-Network-Identifier AVP is 600
    // The data type of Visited-Network-Identifier AVP is OctetString.
    VisitedNetworkIdentifier visitedNetworkIdentifier("Roaming");
    uar.setVisitedNetworkIdentifier(visitedNetworkIdentifier);

    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    uar.setDestinationHost(destinationHost);

    // [2.2] Set the User-Authorization-Type AVP.
    // The User-Authorization-Type AVP indicates the type of user
    // authorization being performed in a User Authorization
    // operation.
    // The AVP Code of User-Authorization-Type AVP is 623
    // The data type of User-Authorization-Type AVP is Enumerated with
    // the following values
    // {
    //  REGISTRATION (0),
    //  DE_REGISTRATION (1),
    //  REGISTRATION_AND_CAPABILITIES (2)
    // }
    UserAuthorizationType userAuthorizationType(UserAuthorizationType::
                                                REGISTRATION);
    uar.setUserAuthorizationType(userAuthorizationType);

    // Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"),proxyHost2("proxyHost1");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState proxyState1("proxyState1"),proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // Add Extra AVP to Proxy-Info AVP
    //proxyInfo1.addExtra(AVP());
    //proxyInfo2.addExtra(ProxyState("proxyState3"));
    // [2.2] Set the Proxy-Info AVP.
    // Application should not set this AVP.
    // uar.addProxyInfo(proxyInfo1);
    // uar.addProxyInfo(proxyInfo2);

    // Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    // RouteRecord routeRecord1("routeRecord1"),routeRecord2("routeRecord2");

    // [2.2] Set the Route-Record AVP.
    // Application should not set this AVP.
    // uar.addRouteRecord(routeRecord2);

    // 3. Send the encoded UserAuthorizationRequest object to an output stream
    // buffer(Note: For test purpose, the object is being sent to ios::cout
    // output buffer.

    cout << uar;

    SendToStack(&uar);

}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the LocationInfo request
 *      made by the diameter stack. Create the LocationInfoAnswer
 *      object, populate the AVPs and send the message to the stack.
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
int SendLocationInfoAnswer(const CommandImpl * impl1)
{
    // 1. Create an instance of LocationInfoAnswer class
    // The Location-Info-Answer command is sent by a server
    // in response to the Location-Info-Request command with
    // Command-Code = 302 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    LocationInfoAnswer lia(false, false);
    
    // Create an instance of LocationInfoRequest class with recived event
    LocationInfoRequest rreq(*impl1);

    // Get AVP values from Request MesSage to set it to the Answer
    const SessionId &sid1 = rreq.getSessionId();
    const OriginHost &oh1 = rreq.getOriginHost();
    const OriginRealm &or1 = rreq.getOriginRealm();
    const DestinationHost &dh1 = rreq.getDestinationHost();
    const DestinationRealm &dr1 = rreq.getDestinationRealm();


    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    lia.setSessionId(sid1);

    // Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter
    // application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as
    // possible.
    VendorSpecificApplicationId        vendorSpecificApplicationId1;

    // [2.2.5] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(VENDOR_ID);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(CXDX_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting
    // messages.
    // Exactly one of the Auth-Application-Id AVP and Acct-Application-Id
    // may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    // [2.1.1] Set the  Vendor-Specific-Application-Id AVP.
    lia.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // Create a Auth-Session-State AVP object.
    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    // [2.1.1] Set the Auth-Session-State AVP.
    AuthSessionState authSessionState(AuthSessionState::NO_STATE_MAINTAINED);
    lia.setAuthSessionState(authSessionState);

    // [2.1.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(dh1.value());
    lia.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(dr1.value());
    lia.setOriginRealm(originRealm);

    // [2.2] Set the Result-Code AVP .
    // The Result-Code AVP indicates whether a particular request
    // was completed successfully or whether an error occurred
    // All Diameter answer messages must contain one Result-Code AVP
    // Diameter provides the following classes of error which
    // is represented by the Result-Code AVP:
    // 1xxx - Informational
    // 2xxx - Success
    // 3xxx - Protocol Errors
    // 4xxx - Transient Failures
    // 5xxx - Permanent Failure
    // The AVP Code of AVP is 268.
    // The data type of AVP is Unsigned32.
    ResultCode resultCode(2001u);
    lia.setResultCode(resultCode);

    // Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // Any one result code sholud be set, but not both
    //ExperimentalResult experimentalResult;

    // Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    //VendorId vendorId1(VENDOR_ID);
    //experimentalResult.setVendorId(vendorId1);

    // Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    //ExperimentalResultCode experimentalResultCode(2001u);
    //experimentalResult.setExperimentalResultCode(experimentalResultCode);

    // [2.2] Set the Experimental-Result AVP.
    // lia.setExperimentalResult(experimentalResult);

    // [2.2] Set the Server-Name AVP.
    // The Server-Name AVP contains a SIP-URL and used to
    // identify a SIP server (e.g. S-CSCF name)..
    // The AVP Code of AVP is .
    // The data type of AVP is UTF8String.
    ServerName serverName("sip:SCSCR-Server@3gppnetwork.com");
    lia.setServerName(serverName);

    // [2.2] Create the Server-Capabilities AVP.
    // This AVP contains information to assist the I-CSCF in the
    // selection of an S-CSCF.
    // The AVP Code of AVP is 603.
    // The data type of AVP is Grouped Type.
    ServerCapabilities serverCapabilities;

    // Set the Mandatory-Capability AVP.
    // The value included in this AVP can be used to represent a
    // single determined mandatory capability of an S-CSCF. Each
    // mandatory capability available in an individual operator’s
    // network shall be allocated a unique value.
    // The AVP Code of AVP is .
    // The data type of AVP is Unsigned32.
    MandatoryCapability mandatoryCapability(1u);
    serverCapabilities.addMandatoryCapability(mandatoryCapability);

    // Set the Optional-Capability AVP.
    // The value included in this AVP can be used to represent a
    // single determined optional capability of an S-CSCF.
    // Each optional capability available in an individual
    // operator’s network shall be allocated a unique value.
    // The AVP Code of Optional-Capability AVP is .
    // The data type of Optional-Capability AVP is Unsigned32.
    OptionalCapability optionalCapability(1u);
    serverCapabilities.addOptionalCapability(optionalCapability);

    // Add the Server-Name AVP to Server-Capabilities AVP..
    // The AVP Code of AVP is .
    // The data type of AVP is UTF8String.
    ServerName serverName1("sip:SCSCF-Server@3gppnetwork.com");
    serverCapabilities.addServerName(serverName1);

    // [2.2] Set the Server-Capabilities AVP.
    lia.setServerCapabilities(serverCapabilities);

    // Create the Failed-AVP AVP.
    // The Failed-AVP AVP provides debugging information in cases
    // where a request is rejected or not fully processed due to
    // erroneous information in a specific AVP.
    // The AVP Code of AVP is 279.
    // The data type of AVP is Grouped Type.

    // FailedAVP failedAVP;

    // [2.2] Set the Failed-AVP AVP.
    // lia.addFailedAVP(failedAVP);

    // Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"),proxyHost2("proxyHost2");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // The data type of is OctetString.
    //ProxyState proxyState1("proxyState1"),proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // [2.2] Set the Proxy-Info AVP.
    // Application should not set this AVP.
    // lia.addProxyInfo(proxyInfo1);
    // lia.addProxyInfo(proxyInfo2);

    // [2.2] Set the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord routeRecord1("routeRecord1"),routeRecord2("routeRecord2");

    // Set Route Record values
    // Application should not set this AVP.
    // lia.addRouteRecord(routeRecord1);
    // lia.addRouteRecord(routeRecord2);

    // 3. Send the encoded LocationInfoAnswer object to an output stream
    // buffer(Note: For test purpose, the object is being sent to ios::cout
    // output buffer.
    if (appMode == UNIT_TEST)
    cout << lia;

    SendToStack(&lia);

    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the PushProfile request
 *      made by the diameter stack. Create the PushProfileAnswer
 *      object, populate the AVPs and send the message to the stack.
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
int SendPushProfileAnswer(const CommandImpl * impl1)
{
    // 1. Create an instance of PushProfileAnswer class
    // The PushProfileAnswer command is sent by a server
    // in response to the Multimedia-Auth-Request command with
    // Command-Code = 305 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator
    // Optional param retrans - whether this is a retransmission
    PushProfileAnswer ppa(false, false);
 
    // Create an instance of PushProfileRequest class
    PushProfileRequest rreq(*impl1);

    // Get some AVP values from Request
    const SessionId &sid1 = rreq.getSessionId();
    const OriginHost &oh1 = rreq.getOriginHost();
    const OriginRealm &or1 = rreq.getOriginRealm();
    const DestinationHost &dh1 = rreq.getDestinationHost();
    const DestinationRealm &dr1 = rreq.getDestinationRealm();

    // 2. Create the instances of the classes describing the various
    //    AVPs' present in an LocationInfoRequest command and
    //    pass them by value to the corresponding data members set
    //    methods of the LocationInfoRequest object created
    //    in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    ppa.setSessionId(sid1);

    // Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter
    // application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as
    // possible.
    VendorSpecificApplicationId        vendorSpecificApplicationId1;

    // [2.2.5] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(VENDOR_ID);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // [2.2] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(CXDX_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // [2.2] Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting
    // messages.
    // Exactly one of the Auth-Application-Id AVP and Acct-Application-Id
    // may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    //[2.1] Set the  Vendor-Specific-Application-Id AVP.
    ppa.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // Create a Auth-Session-State AVP object.
    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    // [2.1] Set the Auth-Session-State AVP.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    ppa.setAuthSessionState(authSessionState);

    // [2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(dh1.value());
    ppa.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(dr1.value());
    ppa.setOriginRealm(originRealm);

    // [2.2] Set the Result-Code AVP .
    // The Result-Code AVP indicates whether a particular request
    // was completed successfully or whether an error occurred
    // All Diameter answer messages must contain one Result-Code AVP
    // Diameter provides the following classes of error which
    // is represented by the Result-Code AVP:
    // 1xxx - Informational
    // 2xxx - Success
    // 3xxx - Protocol Errors
    // 4xxx - Transient Failures
    // 5xxx - Permanent Failure
    // The AVP Code of AVP is 268.
    // The data type of AVP is Unsigned32.
    ResultCode resultCode(2001u);
    ppa.setResultCode(resultCode);

    // Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // ResultCode or ExperimentalResult any one should be set,but not 
    // both 
    //ExperimentalResult experimentalResult;

    // Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    //VendorId vendorId1(VENDOR_ID);
    //experimentalResult.setVendorId(vendorId1);

    // Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    //ExperimentalResultCode experimentalResultCode(2001u);
    //experimentalResult.setExperimentalResultCode(experimentalResultCode);

    // [2.2] Set the Experimental-Result AVP.
    // ppa.setExperimentalResult(experimentalResult);

    //FailedAVP
    //     failedAVP;
    // ppa.addFailedAVP(failedAVP);


    // Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"),proxyHost2("proxyHost2");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // The data type of is OctetString.
    //ProxyState proxyState1("proxyState1"),proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // [2.2] Set the Proxy-Info AVP.
    // Application should not set this AVP.
    // ppa.addProxyInfo(proxyInfo1);
    // ppa.addProxyInfo(proxyInfo2);

    //  ppr.addExtra(proxyInfo2);

    // [2.2] Set the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the  message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord routeRecord1("routeRecord1"),routeRecord2("routeRecord2");

    // Set Route Records
    // Application should not set this AVP.
    // ppa.addRouteRecord(routeRecord1);
    // ppa.addRouteRecord(routeRecord2);

    //  ppr.addExtra(routeRecord2);

    cout << ppa;

    SendToStack(&ppa);

    return (ITS_SUCCESS);

}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the ServerAssignment request
 *      made by the diameter stack. Create the ServerAssignmentAnswer
 *      object, populate the AVPs and send the message to the stack.
 *     send message to Diameter Stack
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
int SendServerAssignmentAnswer(const CommandImpl * impl1)
{
    // 1. Create an instance of ServerAssignmentAnswer class
    // The SendServer-Assignment-Answer command is sent by a server
    // in response to the Location-Info-Request command with
    // Command-Code = 301 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    ServerAssignmentAnswer saa(false, false);

    // Create an instance of ServerAssignmentRequest class
    ServerAssignmentRequest rreq(*impl1);

    // Get some AVP values from Request and set them to Answer Message
    const SessionId &sid1 = rreq.getSessionId();
    const OriginHost &oh1 = rreq.getOriginHost();
    const OriginRealm &or1 = rreq.getOriginRealm();
    const DestinationHost &dh1 = rreq.getDestinationHost();
    const DestinationRealm &dr1 = rreq.getDestinationRealm();

    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    saa.setSessionId(sid1);

    // Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter
    // application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as
    // possible.
    VendorSpecificApplicationId        vendorSpecificApplicationId1;

    // [2.2.5] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(VENDOR_ID);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(CXDX_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting
    // messages.
    // Exactly one of the Auth-Application-Id AVP and Acct-Application-Id
    // may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    // [2.1.1] Set the  Vendor-Specific-Application-Id AVP.
    saa.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // Create a Auth-Session-State AVP object.
    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    // [2.1.1] Set the Auth-Session-State AVP.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    saa.setAuthSessionState(authSessionState);

    // [2.1.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(dh1.value());
    saa.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(dr1.value());
    saa.setOriginRealm(originRealm);

    // [2.2] Set the Result-Code AVP .
    // The Result-Code AVP indicates whether a particular request
    // was completed successfully or whether an error occurred
    // All Diameter answer messages must contain one Result-Code AVP
    // Diameter provides the following classes of error which
    // is represented by the Result-Code AVP:
    // 1xxx - Informational
    // 2xxx - Success
    // 3xxx - Protocol Errors
    // 4xxx - Transient Failures
    // 5xxx - Permanent Failure
    // The AVP Code of AVP is 268.
    // The data type of AVP is Unsigned32.
    ResultCode resultCode(2001u);
    saa.setResultCode(resultCode);

    // Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // Result Code already been set
    //ExperimentalResult experimentalResult;

    // Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    //VendorId vendorId1(VENDOR_ID);
    //experimentalResult.setVendorId(vendorId1);

    // Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    //ExperimentalResultCode experimentalResultCode(2001u);
    //experimentalResult.setExperimentalResultCode(experimentalResultCode);

    // [2.2] Set the Experimental-Result AVP.
    // saa.setExperimentalResult(experimentalResult);

    // [2.1] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    saa.setUserName(userName);

    CxDxUserData userData(subsProfile);
    saa.setCxDxUserData(userData);

/*    ChargingInformation cInfo;
                                                                                
    URI uri1("PrimaryEventChargingFunction.com", URI::AAA,
                  3880, URI::SCTP, URI::DIAMETER);
                                                                                
    URI uri2("SecondaryEventChargingFunction.com", URI::AAAS,
                  3880, URI::TCP, URI::DIAMETER);
                                                                                
    URI uri3("PrimaryEventCollectionFunction.com", URI::AAAS,
                  3880, URI::TCP, URI::DIAMETER);
                                                                                
    URI uri4("SecondaryEventCollectionFunction.com", URI::AAA,
                  3880, URI::TCP, URI::DIAMETER);
                                                                                
    cInfo.setPrimaryEventChargingFunctionName(
          PrimaryEventChargingFunctionName(uri1));
                                                                                
    cInfo.setSecondaryEventChargingFunctionName(
          SecondaryEventChargingFunctionName(uri2));
                                                                                
    cInfo.setPrimaryChargingCollectionFunctionName(
          PrimaryChargingCollectionFunctionName(uri3));
                                                                                
    cInfo.setSecondaryChargingCollectionFunctionName(
          SecondaryChargingCollectionFunctionName(uri4));
                                                                                
        saa.setChargingInformation(cInfo);
*/

    // FailedAVP
    //    failedAVP;
    // saa.addFailedAVP(failedAVP);

    // Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"),proxyHost2("proxyHost2");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // The data type of is OctetString.
    //ProxyState proxyState1("proxyState1"),proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // [2.2] Set the Proxy-Info AVP.
    // Application should not set this AVP.
    // saa.addProxyInfo(proxyInfo1);
    // saa.addProxyInfo(proxyInfo2);
    //  ppr.addExtra(proxyInfo2);

    // Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.

    // [2.2] Set the Route-Record AVP.
    // Application should not set this AVP.
    // saa.addRouteRecord(routeRecord1);
    // saa.addRouteRecord(routeRecord2);

    //  ppr.addExtra(routeRecord2);

    cout << saa;

    SendToStack(&saa);

    return (ITS_SUCCESS);

}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the MultimediaAuth request
 *      made by the diameter stack. Create the MultimediaAuthAnswer
 *      object, populate the AVPs and send the message to the stack.
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
int SendMultimediaAuthAnswer(const CommandImpl * impl1)
{
    // 1. Create an instance of MultimediaAuthAnswer class
    // The Multimedia-Auth-Answer command is sent by a server
    // in response to the Multimedia-Auth-Request command with
    // Command-Code = 303 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    MultimediaAuthAnswer maa(false, false);

    // Create an instance of MultimediaAuthRequest class to get host and 
    // session details
    MultimediaAuthRequest rreq(*impl1);

    // Get AVP values from requested message
    const SessionId &sid1 = rreq.getSessionId();
    const OriginHost &oh1 = rreq.getOriginHost();
    const OriginRealm &or1 = rreq.getOriginRealm();
    const DestinationHost &dh1 = rreq.getDestinationHost();
    const DestinationRealm &dr1 = rreq.getDestinationRealm();

    // 2. Create the instances of the classes describing the various
    // AVPs' present in an MultimediaAuthAnswer command and
    // pass them by value to the corresponding data members set
    // methods of the MultimediaAuthAnswer object created
    // in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    maa.setSessionId(sid1);

    // Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter
    // application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as
    // possible.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.2.5] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(VENDOR_ID);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(CXDX_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting
    // messages.
    // Exactly one of the Auth-Application-Id AVP and Acct-Application-Id
    // may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    // [2.1.1] Set the  Vendor-Specific-Application-Id AVP.
    maa.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    // [2.1.1] Set the Auth-Session-State AVP.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    maa.setAuthSessionState(authSessionState);

    // [2.1.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(dh1.value());
    maa.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(dr1.value());
    maa.setOriginRealm(originRealm);

    // [2.2] Set the Result-Code AVP .
    // The Result-Code AVP indicates whether a particular request
    // was completed successfully or whether an error occurred
    // All Diameter answer messages must contain one Result-Code AVP
    // Diameter provides the following classes of error which
    // is represented by the Result-Code AVP:
    // 1xxx - Informational
    // 2xxx - Success
    // 3xxx - Protocol Errors
    // 4xxx - Transient Failures
    // 5xxx - Permanent Failure
    // The AVP Code of Result-Code AVP is 268.
    // The data type of Result-Code AVP is Unsigned32.
    // already ExperimentalResult is been set
    //ResultCode resultCode(2001u);
    //maa.setResultCode(resultCode);

    // Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of Experimental-Result AVP is 297.
    // The data type of Experimental-Result AVP is Grouped Type.
    ExperimentalResult experimentalResult;

    // Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    VendorId vendorId1(VENDOR_ID);
    experimentalResult.setVendorId(vendorId1);

    // Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    ExperimentalResultCode experimentalResultCode(2001u);
    experimentalResult.setExperimentalResultCode(experimentalResultCode);

    // [2.2] Set the Experimental-Result AVP.
    maa.setExperimentalResult(experimentalResult);

    // [2.1] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    maa.setUserName(userName);

    // [2.1] Set the Public-Identity AVP.
    // The Public-Identity AVP contains the public identity of a
    // user in the IMS.
    // The AVP Code of Public-Identity AVP is 601
    // The data type of Public-Identity AVP is UTF8String.
    PublicIdentity publicIdentity("sip:user@intellinet-tech.com");
    maa.setPublicIdentity(publicIdentity);

    // [2.2] Set the SIP-Number-Auth-Items AVP.
    // The SIP-Number-Auth-Items AVP indicates the number of
    // authentication vectors the S-CSCF is requesting.                             // The AVP Code of SIP-Number-Auth-Items AVP is 607
    // The Data Type of SIP-Number-Auth-Items AVP is Unsigned32
    SIPNumberAuthItems sIPNumberAuthItems(1u);
    maa.setSIPNumberAuthItems(sIPNumberAuthItems);

    // Create a SIP-Auth-Data-Item AVP object
    SIPAuthDataItem sIPAuthDataItem;
    SIPItemNumber sIPItemNumber(1u);
    sIPAuthDataItem.setSIPItemNumber(sIPItemNumber);

    SIPAuthenticationScheme sIPAuthenticationScheme("127");
    sIPAuthDataItem.setSIPAuthenticationScheme(sIPAuthenticationScheme);

    SIPAuthenticate sIPAuthenticate("1234567");
    sIPAuthDataItem.setSIPAuthenticate(sIPAuthenticate);

    SIPAuthorization sIPAuthorization("1234567");
    sIPAuthDataItem.setSIPAuthorization(sIPAuthorization);

    SIPAuthenticationContext sIPAuthenticationContext("1234567");
    sIPAuthDataItem.setSIPAuthenticationContext(sIPAuthenticationContext);

    ConfidentialityKey confidentialityKey("1234567");
    sIPAuthDataItem.setConfidentialityKey(confidentialityKey);

    IntegrityKey integrityKey("1234567");
    sIPAuthDataItem.setIntegrityKey(integrityKey);

    // [2.2] Set the SIP-Auth-Data-Item AVP.
    // The SIP-Auth-Data-Item AVP contains the authentication and/or
    // the authorization for the Diameter client.
    // The AVP Code of SIP-Auth-Data-Item AVP is 612
    // The Data Type of SIP-Auth-Data-Item AVP is Grouped
    maa.addSIPAuthDataItem(sIPAuthDataItem);

    // Create the Failed-AVP AVP.
    // The Failed-AVP AVP provides debugging information in cases
    // where a request is rejected or not fully processed due to
    // erroneous information in a specific AVP.
    // The AVP Code of AVP is 279.
    // The data type of AVP is Grouped Type.

    // FailedAVP
    //    failedAVP;
    // [2.2] Set the Failed-AVP AVP.
    // maa.addFailedAVP(failedAVP);

    // Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"),proxyHost2("proxyHost2");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // The data type of is OctetString.
    //ProxyState proxyState1("proxyState1"),proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // [2.2] Set the Proxy-Info AVP.
    // Application should not set this AVP.
    // maa.addProxyInfo(proxyInfo1);
    // maa.addProxyInfo(proxyInfo2);

    // Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord routeRecord1("routeRecord1"),
    //routeRecord2("routeRecord2");

    // [2.2] Set the Route-Record AVP.
    // Application should not set this AVP.
    // maa.addRouteRecord(routeRecord2);

    // 3. Send the encoded MultimediaAuthAnswer object to an output stream
    //    buffer(Note: For test purpose, the object is being sent to ios::cout
    //    output buffer.

    cout << maa;

    SendToStack(&maa);

    return (ITS_SUCCESS);

}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the RegistrationTermination
 *      request made by the diameter stack. Create the Registration
 *      TerminationAnswer object, populate the AVPs and send the message 
 *      to the stack.
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
int SendRegistrationTerminationAnswer(const CommandImpl * impl1)
{
    // 1. Create an instance of RegistrationTerminationAnswer class
    // The Registration-Termination-Answer command is sent by a server
    // in response to the Registration-Termination-Request command with
    // Command-Code = 304 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    RegistrationTerminationAnswer rta(false, false);

   // Create an instance of RegistrationTerminationrequest class
    RegistrationTerminationRequest rreq(*impl1);

    // Get some AVP values from requested Message and set them to Answer
    const SessionId &sid1 = rreq.getSessionId();
    const OriginHost &oh1 = rreq.getOriginHost();
    const OriginRealm &or1 = rreq.getOriginRealm();
    const DestinationHost &dh1 = rreq.getDestinationHost();
    const DestinationRealm &dr1 = rreq.getDestinationRealm();

    // 2. Create the instances of the classes describing the various
    // AVPs' present in an RegistrationTerminationAnswer command and
    // pass them by value to the corresponding data members set
    // methods of the RegistrationTerminationAnswer object created
    // in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    rta.setSessionId(sid1);

    // Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter
    // application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as
    // possible.
    VendorSpecificApplicationId        vendorSpecificApplicationId1;

    // [2.2.5] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(VENDOR_ID);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(CXDX_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting
    // messages.
    // Exactly one of the Auth-Application-Id AVP and Acct-Application-Id
    // may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    // [2.1.1] Set the  Vendor-Specific-Application-Id AVP.
    rta.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    // [2.1.1] Set the Auth-Session-State AVP.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    rta.setAuthSessionState(authSessionState);

    // [2.1.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(dh1.value());
    rta.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(dr1.value());
    rta.setOriginRealm(originRealm);

    // [2.2] Set the Result-Code AVP .
    // The Result-Code AVP indicates whether a particular request
    // was completed successfully or whether an error occurred
    // All Diameter answer messages must contain one Result-Code AVP
    // Diameter provides the following classes of error which
    // is represented by the Result-Code AVP:
    // 1xxx - Informational
    // 2xxx - Success
    // 3xxx - Protocol Errors
    // 4xxx - Transient Failures
    // 5xxx - Permanent Failure
    // The AVP Code of AVP is 268.
    // The data type of AVP is Unsigned32.
    ResultCode resultCode(2001u);
    rta.setResultCode(resultCode);

    // Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // already ResultCode is set, both should not be set
    //ExperimentalResult experimentalResult;

    // Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    //VendorId vendorId1(VENDOR_ID);
    //experimentalResult.setVendorId(vendorId1);

    // Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    //ExperimentalResultCode experimentalResultCode(2001u);
    //experimentalResult.setExperimentalResultCode(experimentalResultCode);

    // [2.2] Set the Experimental-Result AVP.
    // rta.setExperimentalResult(experimentalResult);

    // Create the Failed-AVP AVP.
    // The Failed-AVP AVP provides debugging information in cases
    // where a request is rejected or not fully processed due to
    // erroneous information in a specific AVP.
    // The AVP Code of AVP is 279.
    // The data type of AVP is Grouped Type.

    // FailedAVP
    //    failedAVP;
    // [2.2] Set the Failed-AVP.
    // rta.addFailedAVP(failedAVP);

    // Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"),proxyHost2("proxyHost2");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // The data type of is OctetString.
    //ProxyState proxyState1("proxyState1"),proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // [2.2] Set the Proxy-Info AVP.
    // Application should not set this AVP.
    // rta.addProxyInfo(proxyInfo1);
    // rta.addProxyInfo(proxyInfo2);

    // [2.2] Set the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord routeRecord1("routeRecord1"),
    //routeRecord2("routeRecord2");

    // Set Route Record
    // rta.addRouteRecord(routeRecord1);
    // rta.addRouteRecord(routeRecord2);

    // 3. Send the encoded RegistrationTerminationAnswer object to an output 
    // stream
    // buffer(Note: For test purpose, the object is being sent to ios::cout
    // output buffer.

    cout << rta;

    SendToStack(&rta);

    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the  UserAuthorization request
 *      made by the diameter stack. Create the  UserAuthorizationAnswer
 *      object, populate the AVPs and send the message to the stack.
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
int SendUserAuthorizationAnswer(const CommandImpl * impl1)
{
    // 1. Create an instance of UserAuthorizationAnswer class
    // The User-Authorization-Answer command is sent by a server
    // in response to the User-Authorization-Request command with
    // Command-Code = 300 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    UserAuthorizationAnswer uaa(false, false);

    //Create an instance of UserAuthorizationRequest class
    UserAuthorizationRequest rreq(*impl1);

    // Get some AVP values from Request Message and pass them to Answer
    const SessionId &sid1 = rreq.getSessionId();
    const OriginHost &oh1 = rreq.getOriginHost();
    const OriginRealm &or1 = rreq.getOriginRealm();
    const DestinationHost &dh1 = rreq.getDestinationHost();
    const DestinationRealm &dr1 = rreq.getDestinationRealm();

    // 2. Create the instances of the classes describing the various
    // AVPs' present in an UserAuthorizationAnswer command and
    // pass them by value to the corresponding data members set
    // methods of the UserAuthorizationAnswer object created
    // in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    uaa.setSessionId(sid1);

    // Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter
    // application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as
    // possible.
    VendorSpecificApplicationId        vendorSpecificApplicationId1;

    // [2.2.5] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may
    // be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(VENDOR_ID);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(CXDX_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting
    // messages.
    // Exactly one of the Auth-Application-Id AVP and Acct-Application-Id
    // may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    // [2.1.1] Set the  Vendor-Specific-Application-Id AVP.
    uaa.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // Create a Auth-Session-State AVP object.
    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    // [2.1.1] Set the Auth-Session-State AVP.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    uaa.setAuthSessionState(authSessionState);

    // [2.1.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(dh1.value());
    uaa.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(dr1.value());
    uaa.setOriginRealm(originRealm);

    // [2.2] Set the Result-Code AVP .
    // The Result-Code AVP indicates whether a particular request
    // was completed successfully or whether an error occurred
    // All Diameter answer messages must contain one Result-Code AVP
    // Diameter provides the following classes of error which
    // is represented by the Result-Code AVP:
    // 1xxx - Informational
    // 2xxx - Success
    // 3xxx - Protocol Errors
    // 4xxx - Transient Failures
    // 5xxx - Permanent Failure
    // The AVP Code of AVP is 268.
    // The data type of AVP is Unsigned32.
    ResultCode resultCode(2001u);
    uaa.setResultCode(resultCode);

    // Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // already ResultCode AVP is set, both should not be set
    //ExperimentalResult experimentalResult;

    // Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    //VendorId vendorId1(VENDOR_ID);
    //experimentalResult.setVendorId(vendorId1);

    // Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    //ExperimentalResultCode experimentalResultCode(2001u);
    //experimentalResult.setExperimentalResultCode(experimentalResultCode);

    // [2.2] Set the Experimental-Result AVP.
    //uaa.setExperimentalResult(experimentalResult);

    // [2.2] Set the Server-Name AVP.
    // The Server-Name AVP contains a SIP-URL and used to
    // identify a SIP server (e.g. S-CSCF name)..
    // The AVP Code of AVP is .
    // The data type of AVP is UTF8String.
    ServerName serverName("sip:cscf@3gppnetwork.com");
    uaa.setServerName(serverName);

    // [2.2] Create the Server-Capabilities AVP.
    // This AVP contains information to assist the I-CSCF in the
    // selection of an S-CSCF.
    // The AVP Code of AVP is 603.
    // The data type of AVP is Grouped Type.
    ServerCapabilities serverCapabilities;

    // Set the Mandatory-Capability AVP.
    // The value included in this AVP can be used to represent a
    // single determined mandatory capability of an S-CSCF. Each
    // mandatory capability available in an individual operator’s
    // network shall be allocated a unique value.
    // The AVP Code of AVP is .
    // The data type of AVP is Unsigned32.
    MandatoryCapability mandatoryCapability(1u);
    serverCapabilities.addMandatoryCapability(mandatoryCapability);

    // Set the Optional-Capability AVP.
    // The value included in this AVP can be used to represent a
    // single determined optional capability of an S-CSCF.
    // Each optional capability available in an individual
    // operator’s network shall be allocated a unique value.
    // The AVP Code of Optional-Capability AVP is .
    // The data type of Optional-Capability AVP is Unsigned32.
    OptionalCapability optionalCapability(1u);
    serverCapabilities.addOptionalCapability(optionalCapability);

    // Add the Server-Name AVP to Server-Capabilities AVP..
    // The AVP Code of AVP is .
    // The data type of AVP is UTF8String.
    ServerName serverName1("sip:cscf@3gppnetwork.com");
    serverCapabilities.addServerName(serverName1);

    // [2.2] Set the Server-Capabilities AVP.
    // [2.2] Set the Server-Capabilities AVP.
    uaa.setServerCapabilities(serverCapabilities);

    // Create the Failed-AVP AVP.
    // The Failed-AVP AVP provides debugging information in cases
    // where a request is rejected or not fully processed due to
    // erroneous information in a specific AVP.
    // The AVP Code of AVP is 279.
    // The data type of AVP is Grouped Type.

    //FailedAVP
    //    failedAVP;
    // [2.2] Set the Failed-AVP AVP.
    //uaa.addFailedAVP(failedAVP);

    // Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"),proxyHost2("proxyHost2");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // The data type of is OctetString.
    //ProxyState proxyState1("proxyState1"),proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // [2.2] Set the Proxy-Info AVP.
    // uaa.addProxyInfo(proxyInfo1);
    // uaa.addProxyInfo(proxyInfo2);

    // [2.2] Set the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the Capabilities
    // Exchange message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord routeRecord1("routeRecord1"),routeRecord2("routeRecord2");

    // Set Route Record
    // Application should not set this AVP.
    // uaa.addRouteRecord(routeRecord1);
    // uaa.addRouteRecord(routeRecord2);

    // 3. Send the encoded UserAuthorizationAnswer object to an output stream
    // buffer(Note: For test purpose, the object is being sent to ios::cout
    // output buffer.

    cout << uaa;

    SendToStack(&uaa);

    return (ITS_SUCCESS);
}
