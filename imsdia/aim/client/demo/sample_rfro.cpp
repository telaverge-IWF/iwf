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
 * LOG: $Log: sample_rfro.cpp,v $
 * LOG: Revision 3.2  2010/06/25 08:25:15  nvijikumar
 * LOG: Updates for release 8
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:00  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.10  2006/11/24 05:45:05  kamakshilk
 * LOG: SessionId input for Update and Terminate
 * LOG:
 * LOG: Revision 2.9  2006/11/17 06:51:25  kamakshilk
 * LOG: getSessionIndex added for release
 * LOG:
 * LOG: Revision 2.8  2006/11/17 06:16:55  kamakshilk
 * LOG: ReleaseSession API called
 * LOG:
 * LOG: Revision 2.7  2006/11/15 13:26:23  kamakshilk
 * LOG: AppID changed to 4 in Send API
 * LOG:
 * LOG: Revision 2.6  2006/11/08 15:02:39  hbhatnagar
 * LOG: Changes to work with DCCA state Machine
 * LOG:
 * LOG: Revision 2.5  2006/10/29 07:30:45  kamakshilk
 * LOG: Re-Auth received handed to BaseMessage()
 * LOG:
 * LOG: Revision 2.4  2006/10/26 05:40:43  kamakshilk
 * LOG: Added DisplayBaseMenuToApp() in the menu.
 * LOG:
 * LOG: Revision 2.3  2006/10/24 11:45:50  kamakshilk
 * LOG: Fix for Bug ID 4588. Handle Base messages
 * LOG:
 * LOG: Revision 2.2  2006/10/16 14:23:57  kamakshilk
 * LOG: Changes to work with ITS-Diameter APIs
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:38  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.3  2006/09/07 06:15:35  kamakshilk
 * LOG: Removed the icmptypes set in IPFilterRule
 * LOG:
 * LOG: Revision 1.2  2006/06/14 09:17:09  kamakshilk
 * LOG: AVP Values correction.
 * LOG:
 * LOG: Revision 1.1  2006/06/09 13:38:54  kamakshilk
 * LOG: RfRo Demo Application
 * LOG:
 * ID: $Id: sample_rfro.cpp,v 3.2 2010/06/25 08:25:15 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: sample_rfro.cpp,v 3.2 2010/06/25 08:25:15 nvijikumar Exp $"

#include <diameter/rfro/CreditControl.h>

#include <app.h>
#include <app_rfro.h>
#include <idc_api.h>

using namespace std;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::rfro;
using namespace diameter::nasreq;
//using namespace diameter::rfro::ims;

IDSCLApi apiRfRo;
unsigned int sIdxRfRo = 0;
string sessIdString;


/*  implementation: public
 ****************************************************************************
 *  Purpose: This function handles the message received from the
 *      stack with AppId = RFRO_INTERFACE_APP_ID.
 *
 *  Input Parameters:
 *      ITS_Event& ev: ITS_Event
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
int RfRoMessage(const diameter::CommandImpl *impl, unsigned int &sIdxrfro)
{
    sIdxRfRo=sIdxrfro;
    try
    {
        switch (impl->getCommandCode())
        {
            case 272: /*Credit Control*/
                if(impl->isRequest())
                {
                    CreditControlRequest ccreq(*impl);
                        cout << "ccreq" << ccreq << endl;
                        SendCreditControlAnswer(impl);
                }
                else
                {
                    CreditControlAnswer ccans(*impl);
                    cout << "ccrsp" << ccans << endl;
                    /* Release session context */
                    switch(ccans.getCCRequestType().value())
                    {
                        case CCRequestType::EVENT_REQUEST:
                            if (!apiRfRo.IsDccaEnabled())
                            {
                               std::string rlsStr = 
                                             ccans.getSessionId().value();
                               apiRfRo.ReleaseSession(rlsStr, 
                                             ccans.getSessionIndex());
                            }
                            break;

                        case CCRequestType::TERMINATION_REQUEST:
                            std::string rlsStr = 
                                           ccans.getSessionId().value();
                            apiRfRo.ReleaseSession(rlsStr, 
                                               ccans.getSessionIndex());
                            break;
                    }
                }
                break;

            case 274:
            case 275:
            case 258:
                BaseMessage(impl,sIdxrfro);
                break;
     
            default:
                break;
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

    return ITS_SUCCESS;
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function displays the menu options for the
 *      RfRo interface.
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
int RfRoMenu()
{
    string input;
    int ret = 0;
    int k=1;
    while(k)
    {
        do
        {
            cout << endl << "Select RfRo Command"<<endl<<endl;
            //cout << "1: CCR - Credit Control Request"<<endl;
            cout <<" 1: CCR - Credit Control Request with  Initial "<<endl;
            cout <<" 2: CCR - Credit Control Request with  Update"<<endl;
            cout <<" 3: CCR - Credit Control Request with  Terminate"<<endl;
            cout <<" 4: CCR - Credit Control Request Event Based "<<endl;
            cout << "5: To Send Base protocol Messages"<<endl;
            cout << "99: To Previous Menu"<<endl;
                                                                                
            cin >> input;
                                                                                
            ret = atoi(input.c_str());
        }while ((ret < 1 || ret > 5) && ret!=99 );

        switch(ret)
        {
        case 1:
        case 2:
        case 3:
        case 4:
            //SendCreditControlRequest(); break;
            SendCreditControlRequest(ret); break;
        case 5:
            DisplayBaseMenuToApp(); break;
        case 99:
            k=0; break;
        default:
            cout << endl << "please enter the correct choice";
            break;
        } //end switch
    } // end while
    return 0;
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Credit Control Request to the
 *      diameter stack. This creates the CreditControlRequest object,
 *      populate the AVPs and sends the message to the stack.
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
//int SendCreditControlRequest()
int 
SendCreditControlRequest(int requestType )
{
    // [1] Create CreditControlRequest object.
    CreditControlRequest ccr(false,false);
    static int num = 0;

   try
   {
        // [2] Insert data in the created CapabilitiesExchangeRequest object.
        // [2.1] Populate Mandatories.
        // [2.1.1] Populate Fixed Mandatories.
        // [2.1.1.1] Populate Fixed parameter "Session-Id".
        // Set the Session-Id AVP.
        // The data type of Session-Id is UTF8String.
        // This AVP is used to identify a specific session.
        // The Session-Id SHOULD appear immediately following the Diameter 
        // Header.The Session-Id MUST be globally and eternally unique.
        // The AVP Code of Session-Id is 263.

        // [2.1.2] Populate Mandatories which can appear anywhere.
        // [2.1.2.1] Populate required parameter "Origin-Host".
        // Set the Origin-Host AVP.
        // The data type of Origin-Host is DiameterIdentity
        // This AVP identifies the endpoint that originated Diameter message.
        // This AVP SHOULD be placed as close to the Diameter header
        // The AVP Code of Origin-Host is 264.
        OriginHost originHost(GetOriginHost());
        ccr.setOriginHost(originHost);

        // [2.1.2.2] Populate required parameter "Origin-Realm".
        // Set the Origin-Realm AVP.
        // The data type of Origin-Realm is DiameterIdentity.
        // This AVP contains the Realm of the originator of any Diameter
        // message.
        // This AVP SHOULD be placed as close to the Diameter header.
        // The AVP Code of Origin-Realm is 296.
        OriginRealm originRealm(GetOriginRealm());
        ccr.setOriginRealm(originRealm);

        // [2.1.2.3] Populate required parameter "Destination-Realm".
        // Set the Destination-Realm AVP.
        // The data type of Destination-Realm is DiameterIdentity.
        // This AVP contains the Realm the message is to be routed to.
        // This AVP SHOULD be placed as close to the Diameter header.
        // The AVP Code of Destination-Realm is 283.
        DestinationRealm destinationRealm(GetDestinationRealm());
        ccr.setDestinationRealm(destinationRealm);

        // [2.1.2.4] Populate required parameter "Auth-Application-Id".
        // Set the Auth-Application-Id AVP.
        // The data type of Auth-Application-Id is Unsigned32.
        // This AVP shall contain the value of 4 as defined in IETF RFC 4006 
        // according 3GPP TS 29.230.
        // The AVP code of Auth-Application-Id is 258.
        AuthApplicationId authApplicationId(RFRO_INTERFACE_APP_ID);
        ccr.setAuthApplicationId(authApplicationId);

        // [2.1.2.5] Populate required parameter "Service-context-Id".
        // Set the Service-context-Id AVP.
        // The data type of Service-context-Id is UTF8String.
        // This AVP contains a unique identifier to Diameter Credit Control 
        // service specific document that applies to the request. This is an 
        // identifier allocated by the service provider/operator, by the 
        // service element manufacturer or by a stadardization body. The 
        // format is
        // "extensions".MCC.MNC."Release"."service-context' @" "domain"
        // The AVP Code of Service-context-Id is 461.
        ServiceContextId serviceContextId("123.0.91.7.32260@3gpp.org");
        ccr.setServiceContextId(serviceContextId);

        // [2.1.2.6] Populate required parameter "CC-Request-Type".
        // Set the CC-Request-Type AVP.
        // The data type of CC-Request-Type is Enumerated.
        // This AVP contains the reason for sending the credit-control request
        // message. 
        // The AVP Code of CC-Request-Type is 416.
        
        //CCRequestType ccRequestType(CCRequestType::INITIAL_REQUEST);
        //ccr.setCCRequestType(ccRequestType);

         switch ( requestType )
        {
            case INITIAL:
            {
                num =0;
                apiRfRo.AllocateSessionIndex(10000, sIdxRfRo, sessIdString);
       
                ccr.setSessionId(SessionId(sessIdString));

                CCRequestType ccRequestType(CCRequestType::INITIAL_REQUEST);
                ccr.setCCRequestType(ccRequestType);
            }
            break;
            case UPDATE:
            {
                cout<<"Please Enter Session Id to Update"<<endl;
                cin>>sessIdString;
                ccr.setSessionId(SessionId(sessIdString));

                cout << "Please enter Session Index" << endl;
                string sId;
                cin >> sId;
                sIdxRfRo = atoi(sId.c_str()); 

                CCRequestType ccRequestType(CCRequestType::UPDATE_REQUEST);
                ccr.setCCRequestType(ccRequestType);
            }
            break;
            case TERMINATION:
            {
                cout<<"Please Enter Session Id to Terminate"<<endl;
                cin>>sessIdString;
                ccr.setSessionId(SessionId(sessIdString));

                cout << "Please enter Session Index" << endl;
                string sId;
                cin >> sId;
                sIdxRfRo = atoi(sId.c_str()); 

                CCRequestType ccRequestType(CCRequestType::TERMINATION_REQUEST);
                ccr.setCCRequestType(ccRequestType);
            }
            break;
            case EVENT:
            {
                num =0;
                apiRfRo.AllocateSessionIndex(10000, sIdxRfRo, sessIdString);
       
                ccr.setSessionId(SessionId(sessIdString));

                CCRequestType ccRequestType(CCRequestType::EVENT_REQUEST);
                ccr.setCCRequestType(ccRequestType);
            }
            break;
            default:
            cout << endl << "Invalid Request Type" << endl;

     }
 

        // [2.1.2.7] Populate required parameter "CC-Request-Number".
        // Set the CC-Request-Number AVP.
        // The data type of CC-Request-Number is Unsigned32.
        // This AVP identifies the request within one session. The 
        // combination of Session-Id and CC-Request-Number is globally unique.
        // An easy way to produce unique numbers is to set the value to 0 for 
        // credit-control request of type INITIAL_REQUEST and EVENT_REQUEST. 
        // Set value to 1 for UPDATE_REQUEST, to 2 for second  until the value
        // for TERMINATE_REQUEST is one more than the last UPDATE_REQUEST.
        // The AVP Code of CC-Request-Number is 415.
        
        //CCRequestNumber ccRequestNumber(0u);
        CCRequestNumber ccRequestNumber(num++);
        ccr.setCCRequestNumber(ccRequestNumber);

        // [2.2] Populate Optionals.

        // [2.2.1] Populate optional parameter "Destination-Host"
        // Set the Destination-Host AVP.
        // The data type for Destination-Host is DiameterIdentity.
        // This AVP MUST be present in all unsolicited agent initiated 
        // messages, MAY be present in request messages and MUST NOT be 
        // present in answers. 
        // The AVP Code of Destination-Host is 293.
        DestinationHost destinationHost(GetDestinationHost());
        ccr.setDestinationHost(destinationHost);

        // [2.2.2] Populate optional parameter "User-Name"
        // Set the User-Name AVP.
        // the data type for User-Name os UTF8String.
        // This contains username in a format consistent with the NAI 
        // specification.
        // The AVP Code of User-Name is 1.
        UserName userName("sip:user@3gppnetwork.com");
        ccr.setUserName(userName);

        // [2.2.3] Populate optional parameter "Origin-State-Id"
        // Set the Origin-State-Id AVP.
        // The data type for Origin-State-Id is of type Unsigned32.
        // It is a monotonically increasing value that is advanced whenever a 
        // Diameter entity restarts with loss of previous state,eg upon reboot.
        // The AVP Code of Origin-State-Id is 278.
        OriginStateId originStateId(1); 
              // API should be provided for getting the Origin-State-Id value.
        ccr.setOriginStateId(originStateId);

        // [2.2.4] Populate optional parameter "Event-Timestamp"
        // Set the Event-Timestamp AVP.
        // The data type Event-Timestamp is Time.
        // This may be included to record the time that the reported event 
        // occured,in seconds since January 1, 1900 00:00 UTC
        // The AVP Code of Event-Timestamp is 55.
        EventTimestamp eventTimestamp(2006);
        ccr.setEventTimestamp(eventTimestamp);

        // [2.2.5] Populate optional(multiple occurence) parameter
        //          "Subscription-Id"
        // Set the Subscription-Id AVP.
        // The data type Subscription-Id is Grouped.
        // This is used to identify the end user's subscription.
        // The AVP Code of Subscription-Id is 443.
        SubscriptionId subscriptionId1;

        // [2.2.5.1] Populate "Subscription-Id" grouped AVPs.
        // [2.2.5.1.1] Populate optional parameter "Subscription-Id-Type"
        // Set the Subscription-Id-Type AVP.
        // The data type Subscription-Id-Type is Enumerated.
        // This is used to determine which type of identifier is carried by the
        // subscription-Id avp. 
        // The AVP Code of Subscription-Id-Type is 450.
        SubscriptionIdType subscriptionIdType
                          (SubscriptionIdType::END_USER_SIP_URI);
        subscriptionId1.setSubscriptionIdType(subscriptionIdType);

        // [2.2.5.1.2] Populate optional parameter "Subscription-Id-Data"
        // Set the Subscription-Id-Data AVP.
        // The data type Subscription-Id-Data is UTF8String.
        // This is used to identify the end user.
        // The AVP Code of Subscription-Id-Data is 444.
        SubscriptionIdData subscriptionIdData("sip:alice@atlanta.com");
        subscriptionId1.setSubscriptionIdData(subscriptionIdData);

        ccr.addSubscriptionId(subscriptionId1);
    
        // [2.2.6] Populate optional parameter "Termination-Cause"
        // Set the Termination-Cause AVP.
        // The data type Termination-Cause is Enumerated.
        // This is used to indicate the reason why a session was terminated on
        // the access device.
        // The AVP Code of Termination-Cause is 295.
        TerminationCause terminationCause(
                          TerminationCause::DIAMETER_USER_MOVED);
        ccr.setTerminationCause(terminationCause);

        // [2.2.7] Populate optional parameter "Requested-Action"
        // Set the Requested-Action AVP.
        // The data type Requested-Action is Enumerated.
        // This contains the requested action being sent by CCR command 
        // where the CC-Request-Type is set to EVENT_REQUEST
        // The AVP Code of Requested-Action is 436.
//        RequestedAction requestedAction(RequestedAction::CHECK_BALANCE);
//        ccr.setRequestedAction(requestedAction);

        // [2.2.8] Populate optional parameter "Multiple-Services-Indicator"
        // Set the Multiple-Services-Indicator AVP.
        // The data type Multiple-Services-Indicator is Enumerated.
        // This indicates whether the Diameter credit-control client is 
        // capable of handling multiple services independently within 
        // a (sub-) session.
        // The AVP Code of Multiple-Services-Indicator is 455.
        MultipleServicesIndicator  multipleServicesIndicator(
                 MultipleServicesIndicator::MULTIPLE_SERVICES_SUPPORTED);
        ccr.setMultipleServicesIndicator(multipleServicesIndicator);

        // [2.2.9] Populate optional(multiple occurence) parameter 
        //         "Multiple-Services-Credit-Control"
        // Set the Multiple-Services-Credit-Control AVP.
        // The data type Multiple-Services-Credit-Control is Grouped.
        // This contains AVPs related to independent credit-control of 
        // multiple services.
        // The AVP Code of Multiple-Services-Credit-Control is 456.
        MultipleServicesCreditControl  multipleServicesCC1;

        // [2.2.9.1] Populate "Multiple-Services-Credit-Control" grouped AVPs.
        PopulateMultipleServicesCreditControl(multipleServicesCC1,true);

        // [2.2.9.2] Add "Multiple-Services-Credit-Control" AVP to CCR object. 
        ccr.addMultipleServicesCreditControl(multipleServicesCC1);

        // [2.2.10] Populate optional parameter "User-Equipment-Info"
        // Set the User-Equipment-Info AVP.
        // The data type User-Equipment-Info is Grouped.
        // This allows the credit-control client to indicate teh identity and
        // capability of the terminal the subscriber is using for the 
        // connection to network.
        // The AVP Code of User-Equipment-Info is 458.
        UserEquipmentInfo userEquipInfo;

        // [2.2.10.1] Populate "User-Equipment-Info" grouped AVPs

        // [2.2.10.1.1] Populate mandatory parameter "User-Equipment-Info-Type"
        // Set the User-Equipment-Info-Type AVP.
        // The data type User-Equipment-Info-Type is Enumerated.
        // This defines teh type of user equipment information contained in the
        // User-Equipment-Info-Value AVP.
        // The AVP Code of User-Equipment-Info-Type is 459.
        UserEquipmentInfoType userEquipInfoType(UserEquipmentInfoType::IMEISV);
        userEquipInfo.setUserEquipmentInfoType(userEquipInfoType);

        // [2.2.10.1.2] Populate mandatory parameter "User-Equipment-Info-Value"
        // Set the User-Equipment-Info-Value AVP.
        // The data type User-Equipment-Info-Value is OctetString.
        // IMEISV format refer 3GPP TS 23.003, MAC refer RAD802.1X
        // <-----8 digits-----><--6 digits--><-------2 digits------>
        // <TypeAllocationCode><SerialNumber><SoftwareVersionNumber>
        // The AVP Code of User-Equipment-Info-Value is 460.
        UserEquipmentInfoValue userEquipInfoValue("123400001111222201");
        userEquipInfo.setUserEquipmentInfoValue(userEquipInfoValue);

        // [2.2.10.2] Set "User-Equipment-Info" AVP in CCR object.
        ccr.setUserEquipmentInfo(userEquipInfo);

        // [2.2.11] Populate optional parameter "Service-Information"
        // Set the Service-Information AVP.
        // The data type Service-Information is Grouped.
        // Its purpose is to allow transmission of additional 3GPP
        // service specific information elements
        // The AVP Code of Service-Information is 873.
        ServiceInformation  serviceInfo;

        // [2.2.11.1] Populate "Service-Information" grouped AVPs.
        PopulateServiceInformation(serviceInfo);

        // [2.2.11.2] Add "Service-Information" AVP to CCR object. 
        ccr.setServiceInformation(serviceInfo);

        //ProxyInfo
        //RouteRecord

        // [3] Send object to stack
        cout << ccr;
 
        apiRfRo.Send(ccr, sIdxRfRo, RFRO_INTERFACE_APP_ID);
     
    } //end try block
    catch(...)
    {
        cout << "Exception ,setting CCR AVP values." << endl;
    }// end catch block    

    return ITS_SUCCESS;
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Answer to Credit Control request 
 *      sent by the application. This creates the CreditControlAnswer
 *      object, populate the AVPs and sends the message to the app.
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
int SendCreditControlAnswer(const diameter::CommandImpl* impl) 
{
    // [1] Create CreditControlAnswer object.
    CreditControlAnswer cca(false,false);

    // [1.1] Create an instance of CreditControlRequest class with
    //        recived event
    CreditControlRequest ccr(*impl);

    try
    {
        // [2] Insert data in the created CreditControlAnswer object.
        // [2.1] Populate Mandatories.
        // [2.1.1] Populate Fixed Mandatories.
        // [2.1.1.1] Populate Fixed paramete "Session-Id".
        // Set the Session-Id AVP.
        // The data type of Session-Id is UTF8String.
        // This AVP is used to identify a specific session.
        // The Session-Id SHOULD appear immediately following the Diameter Header.
        // The Session-Id MUST be globally and eternally unique.
        // The AVP Code of Session-Id is 263.
        const SessionId& sessionId = ccr.getSessionId();
        cca.setSessionId(sessionId);
        
    
        // [2.1.2] Populate Mandatories which can appear anywhere.

        // [2.1.2.1] Populate required parameter "Result-Code".
        // Set the Result-Code AVP.
        // The data type of Result-Code is Unsigned32.
        // This AVP indicates whether a particular request was completed
        // successfully or whether an error occurred.
        // The AVP Code of Result-Code is 268.
        ResultCode resultCode(2001u);
        cca.setResultCode(resultCode);

        // [2.1.2.2] Populate required parameter "Origin-Host".
        // Set the Origin-Host AVP.
        // The data type of Origin-Host is DiameterIdentity
        // This AVP identifies the endpoint that originated the Diameter message
        // This AVP SHOULD be placed as close to the Diameter header
        // The AVP Code of Origin-Host is 264.
        OriginHost originHost(GetOriginHost());
        cca.setOriginHost(originHost);

        // [2.1.2.3] Populate required parameter "Origin-Realm".
        // Set the Origin-Realm AVP.
        // The data type of Origin-Realm is DiameterIdentity.
        // This AVP contains the Realm of the originator of any Diameter 
        // message.
        // This AVP SHOULD be placed as close to the Diameter header.
        // The AVP Code of Origin-Realm is 296.
        OriginRealm originRealm(GetOriginRealm());
        cca.setOriginRealm(originRealm);

        // [2.1.2.4] Populate required parameter "Auth-Application-Id".
        // Set the Auth-Application-Id AVP.
        // The data type of Auth-Application-Id is Unsigned32.
        // This AVP is used in order to advertise support of the Authentication
        // and Authorization portion of an application
        // The AVP Code of Auth-Application-Id is 258.
        AuthApplicationId authApplicationId(RFRO_INTERFACE_APP_ID);
        cca.setAuthApplicationId(authApplicationId);

        // [2.1.2.5] Populate required parameter "CC-Request-Type".
        // Set the CC-Request-Type AVP.
        // The data type of CC-Request-Type is Enumerated.
        // This AVP contains the reason for sending the credit-control request
        // message.
        // The AVP Code of CC-Request-Type is 416.
        //CCRequestType ccRequestType(CCRequestType::TERMINATION_REQUEST);
        //cca.setCCRequestType(ccRequestType);

        const CCRequestType&  ccRequestType = ccr.getCCRequestType();
        cca.setCCRequestType(ccRequestType);
                                                                                                                             
        // [2.1.2.6] Populate required parameter "CC-Request-Number".
        // Set the CC-Request-Number AVP.
        // The data type of CC-Request-Number is Unsigned32.
        // This AVP identifies the request within one session. The
        // combination of Session-Id and CC-Request-Number is globally unique.
        // An easy way to produce unique numbers is to set the value to 0 for
        // credit-control request of type INITIAL_REQUEST and EVENT_REQUEST.
        // Set value to 1 for UPDATE_REQUEST, to 2 for second  until the value
        // for TERMINATE_REQUEST is one more than the last UPDATE_REQUEST.
        // The AVP Code of CC-Request-Number is 415.
        CCRequestNumber ccRequestNumber(1);
        cca.setCCRequestNumber(ccRequestNumber);

        // [2.2] Populate Optionals.

        // [2.2.1] Populate optional parameter "CC-Session-Failover"
        // Set the CC-Session-Failover AVP.
        // The data type of CC-Session-Failover is Enumerated.
        // This contains information as to whether moving the credit-control
        // message stream to a backup server during an ongoing credit-control
        // session is suported.
        // The AVP Code of CC-Session-Failover is 418.
        CCSessionFailover ccSessionFailover(
                           CCSessionFailover::FAILOVER_NOT_SUPPORTED);
        cca.setCCSessionFailover(ccSessionFailover);

        // [2.2.2] Populate optional(multiple occurence) parameter "
        //         Multiple-Services-Credit-Control"
        // Set the Multiple-Services-Credit-Control AVP.
        // The data type Multiple-Services-Credit-Control is Grouped.
        // This contains AVPs related to independent credit-control of
        // multiple services.
        // The AVP Code of Multiple-Services-Credit-Control is 456.
        MultipleServicesCreditControl multipleServicesCC1;

        // [2.2.2.1] Populate "Multiple-Services-Credit-Control" grouped AVPs.
        PopulateMultipleServicesCreditControl(multipleServicesCC1,false);
                                                                                                                             
        // [2.2.2.2] Add "Multiple-Services-Credit-Control" AVP to CCA object.
        cca.addMultipleServicesCreditControl(multipleServicesCC1);
                                                                                                                             
        // [2.2.3] Populate optional parameter "Cost-Information"
        // Set the ontrol AVP.
        // The data type ontrol is Grouped.
        // This is used to return the cost information of a service,which the
        // credit-control client can transfer transparently to the end user.
        // The AVP Code of ontrol is 423.
        CostInformation costInfo;

        // [2.2.3.1] Populate "Cost-Information" grouped AVPs.
        PopulateCostInformation(costInfo);
                                                                                                                             
        // [2.2.3.2] Add "Cost-Information" AVP to CCA object.
        cca.setCostInformation(costInfo);

        // [2.2.4] Populate optional parameter 
        //          "Credit-Control-Failure-Handling"
        // Set the Credit-Control-Failure-Handling AVP.
        // The data type Credit-Control-Failure-Handling is Enumerated.
        // The credit-control client uses information in this AVP to decide
        // what to do if sending credit control messages to the server, has 
        // been ,for instance, temporarily prevented due to network problem.
        // The AVP Code of Credit-Control-Failure-Handling is 427.
        CreditControlFailureHandling ccFailureHandling(
                          CreditControlFailureHandling::TERMINATE);
        cca.setCreditControlFailureHandling(ccFailureHandling);

        // [2.2.5] Populate optional(multiple occurence) parameter 
        //             "Redirect-Host"
        // Set the Redirect-Host AVP.
        // The data type Redirect-Host is DiamURI.
        // This AVP must be present if the answer message's 'E' bit is set 
        // and Result-Code is DIMETER_REDIRECT_INDICATION.
        // The AVP Code of Redirect-Host is 292.
//        RedirectHost redirectHost1; // not clear

        // [2.2.6] Populate optional parameter "Redirect-Host-Usage"
        // Set the Reditect-Host-Usage AVP.
        // The data type Reditect-Host-Usage is Enumerated.
        // This AVP must be present if the answer message's 'E' bit is set 
        // and Result-Code is DIMETER_REDIRECT_INDICATION.
        // The AVP Code of Reditect-Host-Usage is 261.
//        RedirectHostUsage redirectHostUsage(RedirectHostUsage::ALL_SESSION);
//        cca.setRedirectHostUsage(redirectHostUsage);

        // [2.2.7] Populate optional parameter "Redirect-Max-Cache-Time"
        // Set the Redirect-Max-Cache-Time AVP.
        // The data type Redirect-Max-Cache-Time is Unsigned32.
        // This AVP must be present if the answer message's 'E' bit is set 
        // and Result-Code is DIMETER_REDIRECT_INDICATION and the
        // Redirect-Host-Usage AVP is set to a non zero value.
        // The AVP Code of Redirect-Max-Cache-Time is 262.
//        RedirectMaxCacheTime redirectMaxCacheTime(20);
//        cca.setRedirectMaxCacheTime(redirectMaxCacheTime);

        // [2.2.8] Populate optional parameter "Service-Information"
        // Set the Service-Information AVP.
        // The data type Service-Information is Grouped.
        // Its purpose is to allow transmission of additional 3GPP
        // service specific information elements
        // The AVP Code of Service-Information is 873.
        ServiceInformation serviceInfo;

        // [2.2.11.1] Populate "Service-Information" grouped AVPs.
        PopulateServiceInformation(serviceInfo);
                                                                                                                             
        // [2.2.11.2] Add "Service-Information" AVP to CCR object.
        cca.setServiceInformation(serviceInfo);

        // [3] Send object to stack
        cout << endl << cca;

        apiRfRo.Send(cca, sIdxRfRo, RFRO_INTERFACE_APP_ID);

    }// end try block
    catch(...)
    { 
        cout << " Exception, setting CCA AVP values" << endl;
    } // end catch block

    /* Release session context */
    switch(cca.getCCRequestType().value())
    {
       case CCRequestType::EVENT_REQUEST:
           if (!apiRfRo.IsDccaEnabled())
           {
               std::string rlsStr = cca.getSessionId().value();
               apiRfRo.ReleaseSession(rlsStr, sIdxRfRo);
           }
           break;
       case CCRequestType::TERMINATION_REQUEST:
           std::string rlsStr = cca.getSessionId().value();
           apiRfRo.ReleaseSession(rlsStr, sIdxRfRo);
           break;
    }

    return (ITS_SUCCESS);
}


/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Multiple-Services-Credit-Control
 *      grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      MultipleServicesCreditControl object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      MultipleServicesCreditControl &multipleServicesCC: Reference to the 
 *      MultipleServicesCreditControl object, grouped AVPs of which needs 
 *      to be set.
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
void PopulateMultipleServicesCreditControl(MultipleServicesCreditControl 
        &multipleServicesCC , bool isRequest=true)
{
    // [1] Populate "Multiple-Services-Credit-Control" grouped AVPs. 

    if(isRequest)
    {
        // [1.1] Populate optional parameter Requested-Service-Unit 
        // Set the Requested-Service-Unit AVP.
        // The data type Requested-Service-Unit is Grouped.
        // This contains amount of requested units specified by the Diameter
        // credit-control client. The server si not required to implement all
        // the unit types, and it must treat unknown or unsupported unit 
        // types as invalid AVPs. 
        // The AVP Code of Requested-Service-Unit is 437.
        RequestedServiceUnit requestedServiceUnit;

        // [1.1.1] Populate "Requested-Service-Unit" grouped AVPs. 
        PopulateRequestedServiceUnit(requestedServiceUnit);

        // [1.1.2] Set "Requested-Service-Unit" AVP in
        //                  Multiple-Services-Credit-Control object. 
        multipleServicesCC.setRequestedServiceUnit(requestedServiceUnit);
    } // end if(isRequest)
    else
    {
        // [1.1] Populate optional parameter Granted-Service-Unit 
        // Set the Granted-Service-Unit AVP.
        // The data type Granted-Service-Unit is Grouped.
        // This contains amount of requested units specified by the Diameter
        // credit-control client. The server si not required to implement all
        // the unit types, and it must treat unknown or unsupported unit 
        // types as invalid AVPs. 
        // The AVP Code of Granted-Service-Unit is 437.
        GrantedServiceUnit grantedServiceUnit;

        // [1.1.1] Populate "Granted-Service-Unit" grouped AVPs. 
        PopulateGrantedServiceUnit(grantedServiceUnit);

        // [1.1.2] Set "Granted-Service-Unit" AVP in
        //                  Multiple-Services-Credit-Control object. 
        multipleServicesCC.setGrantedServiceUnit(grantedServiceUnit);
    } // end else (answer)

    // [1.2] Populate optional(multiple occurence) parameter 
    //                Used-Service-Unit 
    // Set the Used-Service-Unit AVP.
    // The data type Used-Service-Unit is Grouped.
    // This contains the amount of used units measured from the point when 
    // the service became active or, if interim interrogations are used during
    // the session, from the point when the previous measurement ended.
    // The AVP Code of Used-Service-Unit is 446.
    UsedServiceUnit usedServiceUnit1;

    // [1.2.1] Populate "Used-Service-Unit" grouped AVPs. 
    PopulateUsedServiceUnit(usedServiceUnit1);

    // [1.2.2] Add "Used-Service-Unit" AVP to Multiple-Services-Credit
    //                   -Control object. 
    multipleServicesCC.addUsedServiceUnit(usedServiceUnit1);

    // [1.3] Populate optional parameter Rating-Group 
    // Set the Rating-Group AVP.
    // The data type Rating-Group is Unsigned32.
    // This contains the identifer of a rating group.
    // The AVP Code of Rating-Group is 432.
    RatingGroup ratingGroup(3);
    multipleServicesCC.setRatingGroup(ratingGroup);

    if(isRequest)
    {
        // [1.4] Populate optional parameter Reporting-Reason 
        // Set the Reporting-Reason AVP.
        // The data type Reporting-Reason is Enumerated.
        // This specifies the reason for usage reporting for one or more
        // types of quota for a particular category. It ca directly occur
        // in Multiple-Services-Credit-Control or in Used-Service-Units.
        // The AVP Code of Reporting-Reason is 872.
        ReportingReason reportingReason1(ReportingReason::FINAL);
        multipleServicesCC.addReportingReason(reportingReason1);

        // [1.5] Populate optional parameter Trigger-Type 
        // Set the Trigger-Type AVP.
        // The data type Trigger-Type is Enumerated.
        // This shall be included inthe request only when the Reporting-Reason
        // AVP value is RATING_CONDITION_CHANGE
        // The AVP Code of Trigger-Type is 870.
//        TriggerType triggerType1(TriggerType::CHANGE_IN_QOS);
//        multipleServicesCC.addTriggerType(triggerType1);
    } // end if(isRequest)
    else
    {
        // [1.4] Populate optional parameter Validity-Time
        // Set the Validity-Time AVP.
        // The data type Validity-Time is Unsigned32.
        // This is sent from the credit-control server to the credit-control
        // client. The AVP contains the validity time of the granted service
        // units. The measurement of the Validity-Time is started upon receipt
        // of the Credit-Control-Answer Message containing this AVP.If the 
        // granted service units have not been consumed within the validity 
        // time specified in this AVP, the credit-control client MUST send a 
        // CCR message to server,with CC-Request-Type set to UPDATE_REQUEST. 
        // The value field of the Validity-Time AVP is given in seconds.
        // The AVP Code of Validity-Time is 448.
        ValidityTime validityTime(100);
        multipleServicesCC.setValidityTime(validityTime);

        // [1.5] Populate optional parameter Final-Unit-Indication
        // Set the Final-Unit-Indication AVP.
        // The data type Final-Unit-Indication is Grouped.
        // This indicates that the Granted-Service-Unit AVP in the CCA, or in
        // the AA answer,contains the final units for the service. After these
        // units have expired, the Diameter credit-control client is 
        // responsible for executing the action indicated in the
        // Final-Unit-Action AVP.
        // The AVP Code of Final-Unit-Indication is 430.
        FinalUnitIndication finalUnitInd;
        PopulateFinalUnitIndication(finalUnitInd); 
        multipleServicesCC.setFinalUnitIndication(finalUnitInd);

        // [1.6] Populate optional parameter Time-Quota-Threshold
        // Set the Time-Quota-Threshold AVP.
        // The data type Time-Quota-Threshold is Unsigned32.
        // This contains a threshold value in seconds.
        // The AVP Code of Time-Quota-Threshold is 868.
        TimeQuotaThreshold timeQuotaThrs(100);
        multipleServicesCC.setTimeQuotaThreshold(timeQuotaThrs);

        // [1.7] Populate optional parameter Volume-Quota-Threshold
        // Set the Volume-Quota-Threshold AVP.
        // The data type Volume-Quota-Threshold is Unsigned32.
        // This contains a threshold value in octets.
        // The AVP Code of Volume-Quota-Threshold is 869.
        VolumeQuotaThreshold volumeQuotaThrs(800);
        multipleServicesCC.setVolumeQuotaThreshold(volumeQuotaThrs);

        // [1.8] Populate optional parameter Quota-Holding-Time
        // Set the Quota-Holding-Time AVP.
        // The data type Quota-Holding-Time is Unsigned32.
        // This contains quota holding time in seconds.
        // The AVP Code of Quota-Holding-Time is 871.
        QuotaHoldingTime quotaHoldingTime(100);
        multipleServicesCC.setQuotaHoldingTime(quotaHoldingTime);

        // [1.9] Populate optional parameter Quota-Consumption-Time
        // Set the Quota-Consumption-Time AVP.
        // The data type Quota-Consumption-Time is Unsigned32.
        // This contains idle traffic threshold time in seconds.
        // The AVP Code of Quota-Consumption-Time is 881.
        QuotaConsumptionTime quotaConsumptionTime(100);
        multipleServicesCC.setQuotaConsumptionTime(quotaConsumptionTime);

        // [1.10] Populate optional parameter Reporting-Reason
        // Set the Reporting-Reason AVP.
        // The data type Reporting-Reason is Enumerated.
        // This specifies the reason for usage reporting for one or more
        // types of quota for a particular category. It ca directly occur
        // in Multiple-Services-Credit-Control or in Used-Service-Units.
        // The AVP Code of Reporting-Reason is 872.
        ReportingReason reportingReason1
            (ReportingReason::RATING_CONDITION_CHANGE);
        multipleServicesCC.addReportingReason(reportingReason1);
                                                                                
        // [1.12] Populate optional parameter PS-Furnish-Charging-Information
        // Set the PS-Furnish-Charging-Information AVP.
        // The data type of PS-Furnish-Charging-Information is Grouped.
        // The purpose is to add online charging session specific information,
        // received via the Ro Reference point onto the Rf reference point in 
        // order to facilitate its inclusion in CDRs.This information element 
        // may be received in CCA message via the Ro reference point. In 
        // situations where online and offline charging are active in parallel,
        // the information element is transparently copied into ACR to be sent
        // on the Rf reference point.
        // The AVP Code for PS-Furnish-Charging-Information is 865.
        PSFurnishChargingInformation psFurnishChrgInfo;
        PopulatePSFurnishChargingInformation(psFurnishChrgInfo);
        multipleServicesCC.setPSFurnishChargingInformation(psFurnishChrgInfo);

    } // end else(answer)

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the PS-Furnish-Charging-Information 
 *           grouped AVP.
 *      This populate the grouped AVPs and sets the values in the
 *      PSFurnishChargingInformation object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      PSFurnishChargingInformation &psFurnishChrgInfo: Reference to the
 *      PSFurnishChargingInformation object, grouped AVPs of which needs 
 *      to be set.
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
void PopulatePSFurnishChargingInformation
          (PSFurnishChargingInformation &psFurnishChrgInfo)
{
    // [1] Populate PS-Furnish-Charging-Information grouped AVPs.

    // [1.1] Populate optional AVPs.

    // [1.1.1] Populate optional parameter 3GPP-Charging-Id.
    // Set 3GPP-Charging-Id AVP.
    // The data type of 3GPP-Charging-Id is Unsigned32.
    // This contains the Charging ID for this PDP context (this together with
    // GGSN-Address constitutes a unique identifier for the PDP context).
    // The AVP Code for 3GPP-Charging-Id is 2.
    RfRo3GPPChargingId ps3gppChargingId(1500u);
    psFurnishChrgInfo.setRfRo3GPPChargingId(ps3gppChargingId);
  
    // [1.1.2] Populate optional parameter PS-Free-Format-Data.
    // Set PS-Free-Format-Data AVP.
    // The data type of PS-Free-Format-Data is OctetString.
    // The holds online charging session specific data.
    // The AVP Code for PS-Free-Format-Data is 866.
    PSFreeFormatData psFreeFormatData("psinformation"); //not clear
    psFurnishChrgInfo.setPSFreeFormatData(psFreeFormatData);

    // [1.1.3] Populate optional parameter PS-Append-Free-Format-Data.
    // Set PS-Append-Free-Format-Data AVP.
    // The data type of PS-Append-Free-Format-Data is Enumerated.
    // The indicates if the information sent in the PS-Free-Format-Data AVP
    //  must be appended to the PS-Free-Format-Data stored for the
    // online-session.
    // The AVP Code for PS-Append-Free-Format-Data is 867.
    PSAppendFreeFormatData psAppndFreeFrmtData(PSAppendFreeFormatData::Append);
    psFurnishChrgInfo.setPSAppendFreeFormatData(psAppndFreeFrmtData);

}


/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Requested-Service-Unit grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      RequestedServiceUnit object passed as a reference to this function.
 *
 *  Input Parameters:
 *      RequestedServiceUnit &requestedServiceUnit: Reference to the
 *      RequestedServiceUnit object, grouped AVPs of which needs to be set.
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
void PopulateRequestedServiceUnit(RequestedServiceUnit &requestedServiceUnit)
{
    // [1] Populate "Requested-Service-Unit" grouped AVPs. 

    // [1.1] Populate optional parameter CC-Time 
    // Set the CC-Time AVP.
    // The data type CC-Time is Unsigned32.
    // This indicates the length of requested,granted or used time in seconds.
    // The AVP Code of CC-Time is 420.
    CCTime ccTime(3600);
    requestedServiceUnit.setCCTime(ccTime);

    // [1.2] Populate optional parameter CC-Money 
    // Set the CC-Money AVP.
    // The data type CC-Money is Grouped.
    // This contains amount of requested units specified by the Diameter
    // The AVP Code of CC-Money is 413.
    CCMoney ccMoney;

    // [1.2.1] Populate "CC-Money" grouped AVPs. 

    // [1.2.1.1] Populate mandatory parameter Unit-Value 
    // Set the Unit-Value AVP.
    // The data type Unit-Value is Grouped.
    // This specifies the units as decimal value.
    // The AVP Code of Unit-Value is 445.
    UnitValue unitValue;

    // [1.2.1.1.1] Populate "Unit-Value" grouped AVPs. 

    // [1.2.1.1.1.1] Populate mandatory parameter Value-Digits 
    // Set the Value-Digits AVP.
    // The data type Value-Digits is Integer64.
    // This contains the significant digits of the number.
    // Eg: for the monetary amount $0.05, the value of Value-Digits is 5 and
    // Exponent AVP must be set to -2.
    // The AVP Code of Value-Digits is 447.
    ValueDigits valueDigits(5);
    unitValue.setValueDigits(valueDigits);

    // [1.2.1.1.1.2] Populate optional parameter Exponent 
    // Set the Exponent AVP.
    // The data type Exponent is Grouped.
    // This contains the exponent value to be applied for the Value-Digits AVP.
    // The AVP Code of Exponent is 429.
    Exponent exponent(-2);
    unitValue.setExponent(exponent);

    // [1.2.1.1.2] Set "Unit-Value" AVP in CC-Money. 
    ccMoney.setUnitValue(unitValue);

    // [1.2.1.2] Populate optional parameter Currency-Code 
    // Set the Currency-Code AVP.
    // The data type Currency-Code is Unsigned32.
    // This contains currency code that specifies in which currency the values
    // of AVPs containing monetary units were given. It is specified by using
    // numeric values defined in ISO 4217 standard.
    // The AVP Code of Currency-Code is 425.
    CurrencyCode currencyCode(840);
    ccMoney.setCurrencyCode(currencyCode);

    // [1.2.2] Set "CC-Money" AVP in Requested-Service-Unit. 
    requestedServiceUnit.setCCMoney(ccMoney);

    // [1.3] Populate optional parameter CC-Total-Octets 
    // Set the CC-Total-Octets AVP.
    // The data type CC-Total-Octets is Unsigned64.
    // This contains total number of requested,granted or used octets 
    // regardless of direction sent or received.
    // The AVP Code of CC-Total-Octets is 421.
    CCTotalOctets ccTotalOctets(6000);
    requestedServiceUnit.setCCTotalOctets(ccTotalOctets);

    // [1.4] Populate optional parameter CC-Input-Octets 
    // Set the CC-Input-Octets AVP.
    // The data type CC-Input-Octets is Unsigned64.
    // This contains number of requested,granted or used octets that can be
    // received from end user.
    // The AVP Code of CC-Input-Octets is 412.
    CCInputOctets ccInputOctets(6000);
    requestedServiceUnit.setCCInputOctets(ccInputOctets);

    // [1.5] Populate optional parameter CC-Output-Octets 
    // Set the CC-Output-Octets AVP.
    // The data type CC-Output-Octets is Unsigned64.
    // This contains number of requested,granted or used octets that can be
    // sent to end user.
    // The AVP Code of CC-Output-Octets is 414.
    CCOutputOctets ccOutputOctets(6000);
    requestedServiceUnit.setCCOutputOctets(ccOutputOctets);

    // [1.6] Populate optional parameter CC-Service-Specific-Units 
    // Set the CC-Service-Specific-Units AVP.
    // The data type CC-Service-Specific-Units is Unsigned64.
    // This contains number of service specific units (eg: number of events,
    // points) given in a selected service.
    // The AVP Code of CC-Service-Specific-Units is 417.
    CCServiceSpecificUnits ccServiceSpecificUnits(20);
    requestedServiceUnit.setCCServiceSpecificUnits(ccServiceSpecificUnits);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Granted-Service-Unit grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      RequestedServiceUnit object passed as a reference to this function.
 *
 *  Input Parameters:
 *      GrantedServiceUnit &grantedServiceUnit: Reference to the
 *      GrantedServiceUnit object, grouped AVPs of which needs to be set
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
void PopulateGrantedServiceUnit(GrantedServiceUnit &grantedServiceUnit)
{
    // [1] Populate "Granted-Service-Unit" grouped AVPs. 

    // [1.1] Populate optional parameter CC-Time 
    // Set the CC-Time AVP.
    // The data type CC-Time is Unsigned32.
    // This indicates the length of requested,granted or used time in seconds.
    // The AVP Code of CC-Time is 420.
    CCTime ccTime(3600);
    grantedServiceUnit.setCCTime(ccTime);

    // [1.2] Populate optional parameter CC-Money 
    // Set the CC-Money AVP.
    // The data type CC-Money is Grouped.
    // This contains amount of requested units specified by the Diameter
    // The AVP Code of CC-Money is 413.
    CCMoney ccMoney;

    // [1.2.1] Populate "CC-Money" grouped AVPs. 

    // [1.2.1.1] Populate mandatory parameter Unit-Value 
    // Set the Unit-Value AVP.
    // The data type Unit-Value is Grouped.
    // This specifies the units as decimal value.
    // The AVP Code of Unit-Value is 445.
    UnitValue unitValue;

    // [1.2.1.1.1] Populate "Unit-Value" grouped AVPs. 

    // [1.2.1.1.1.1] Populate mandatory parameter Value-Digits 
    // Set the Value-Digits AVP.
    // The data type Value-Digits is Integer64.
    // This contains the significant digits of the number.
    // Eg: for the monetary amount $0.05, the value of Value-Digits is 5 and
    // Exponent AVP must be set to -2.
    // The AVP Code of Value-Digits is 447.
    ValueDigits valueDigits(5);
    unitValue.setValueDigits(valueDigits);

    // [1.2.1.1.1.2] Populate optional parameter Exponent 
    // Set the Exponent AVP.
    // The data type Exponent is Grouped.
    // This contains the exponent value to be applied for the Value-Digits AVP.
    // The AVP Code of Exponent is 429.
    Exponent exponent(-2);
    unitValue.setExponent(exponent);

    // [1.2.1.1.2] Set "Unit-Value" AVP in CC-Money. 
    ccMoney.setUnitValue(unitValue);

    // [1.2.1.2] Populate optional parameter Currency-Code 
    // Set the Currency-Code AVP.
    // The data type Currency-Code is Unsigned32.
    // This contains currency code that specifies in which currency the values
    // of AVPs containing monetary units were given. It is specified by using
    // numeric values defined in ISO 4217 standard.
    // The AVP Code of Currency-Code is 425.
    CurrencyCode currencyCode(840);
    ccMoney.setCurrencyCode(currencyCode);

    // [1.2.2] Set "CC-Money" AVP in Requested-Service-Unit. 
    grantedServiceUnit.setCCMoney(ccMoney);

    // [1.3] Populate optional parameter CC-Total-Octets 
    // Set the CC-Total-Octets AVP.
    // The data type CC-Total-Octets is Unsigned64.
    // This contains total number of requested,granted or used octets 
    // regardless of direction sent or received.
    // The AVP Code of CC-Total-Octets is 421.
    CCTotalOctets ccTotalOctets(6000);
    grantedServiceUnit.setCCTotalOctets(ccTotalOctets);

    // [1.4] Populate optional parameter CC-Input-Octets 
    // Set the CC-Input-Octets AVP.
    // The data type CC-Input-Octets is Unsigned64.
    // This contains number of requested,granted or used octets that can be
    // received from end user.
    // The AVP Code of CC-Input-Octets is 412.
    CCInputOctets ccInputOctets(6000);
    grantedServiceUnit.setCCInputOctets(ccInputOctets);

    // [1.5] Populate optional parameter CC-Output-Octets 
    // Set the CC-Output-Octets AVP.
    // The data type CC-Output-Octets is Unsigned64.
    // This contains number of requested,granted or used octets that can be
    // sent to end user.
    // The AVP Code of CC-Output-Octets is 414.
    CCOutputOctets ccOutputOctets(6000);
    grantedServiceUnit.setCCOutputOctets(ccOutputOctets);

    // [1.6] Populate optional parameter CC-Service-Specific-Units 
    // Set the CC-Service-Specific-Units AVP.
    // The data type CC-Service-Specific-Units is Unsigned64.
    // This contains number of service specific units (eg: number of events,
    // points) given in a selected service.
    // The AVP Code of CC-Service-Specific-Units is 417.
    CCServiceSpecificUnits ccServiceSpecificUnits(20);
    grantedServiceUnit.setCCServiceSpecificUnits(ccServiceSpecificUnits);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Used-Service-Unit grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      UsedServiceUnit object passed as a reference to this function.
 *
 *  Input Parameters:
 *      UsedServiceUnit &usedServiceUnit: Reference to the
 *      UsedServiceUnit object, grouped AVPs of which needs to be set
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
void PopulateUsedServiceUnit(UsedServiceUnit &usedServiceUnit)
{
    // [1] Populate "Used-Service-Unit" grouped AVPs. 

    // [1.1] Populate optional parameter CC-Time 
    // Set the CC-Time AVP.
    // The data type CC-Time is Unsigned32.
    // This indicates the length of requested,granted or used time in seconds.
    // The AVP Code of CC-Time is 420.
    CCTime ccTime(3600);
    usedServiceUnit.setCCTime(ccTime);

    // [1.2] Populate optional parameter CC-Money 
    // Set the CC-Money AVP.
    // The data type CC-Money is Grouped.
    // This contains amount of requested units specified by the Diameter
    // The AVP Code of CC-Money is 413.
    CCMoney ccMoney;

    // [1.2.1] Populate "CC-Money" grouped AVPs. 

    // [1.2.1.1] Populate mandatory parameter Unit-Value 
    // Set the Unit-Value AVP.
    // The data type Unit-Value is Grouped.
    // This specifies the units as decimal value.
    // The AVP Code of Unit-Value is 445.
    UnitValue unitValue;

    // [1.2.1.1.1] Populate "Unit-Value" grouped AVPs. 

    // [1.2.1.1.1.1] Populate mandatory parameter Value-Digits 
    // Set the Value-Digits AVP.
    // The data type Value-Digits is Integer64.
    // This contains the significant digits of the number.
    // Eg: for the monetary amount $0.05, the value of Value-Digits is 5 and
    // Exponent AVP must be set to -2.
    // The AVP Code of Value-Digits is 447.
    ValueDigits valueDigits(5);
    unitValue.setValueDigits(valueDigits);

    // [1.2.1.1.1.2] Populate optional parameter Exponent 
    // Set the Exponent AVP.
    // The data type Exponent is Grouped.
    // This contains the exponent value to be applied for the Value-Digits AVP.
    // The AVP Code of Exponent is 429.
    Exponent exponent(-2);
    unitValue.setExponent(exponent);

    // [1.2.1.1.2] Set "Unit-Value" AVP in CC-Money. 
    ccMoney.setUnitValue(unitValue);

    // [1.2.1.2] Populate optional parameter Currency-Code 
    // Set the Currency-Code AVP.
    // The data type Currency-Code is Unsigned32.
    // This contains currency code that specifies in which currency the values
    // of AVPs containing monetary units were given. It is specified by using
    // numeric values defined in ISO 4217 standard.
    // The AVP Code of Currency-Code is 425.
    CurrencyCode currencyCode(840);
    ccMoney.setCurrencyCode(currencyCode);

    // [1.2.2] Set "CC-Money" AVP in Requested-Service-Unit. 
    //usedServiceUnit.setCCMoney(ccMoney);

    // [1.3] Populate optional parameter CC-Total-Octets 
    // Set the CC-Total-Octets AVP.
    // The data type CC-Total-Octets is Unsigned64.
    // This contains total number of requested,granted or used octets 
    // regardless of direction sent or received.
    // The AVP Code of CC-Total-Octets is 421.
    CCTotalOctets ccTotalOctets(6000);
    usedServiceUnit.setCCTotalOctets(ccTotalOctets);

    // [1.4] Populate optional parameter CC-Input-Octets 
    // Set the CC-Input-Octets AVP.
    // The data type CC-Input-Octets is Unsigned64.
    // This contains number of requested,granted or used octets that can be
    // received from end user.
    // The AVP Code of CC-Input-Octets is 412.
    CCInputOctets ccInputOctets(6000);
    usedServiceUnit.setCCInputOctets(ccInputOctets);

    // [1.5] Populate optional parameter CC-Output-Octets 
    // Set the CC-Output-Octets AVP.
    // The data type CC-Output-Octets is Unsigned64.
    // This contains number of requested,granted or used octets that can be
    // sent to end user.
    // The AVP Code of CC-Output-Octets is 414.
    CCOutputOctets ccOutputOctets(6000);
    usedServiceUnit.setCCOutputOctets(ccOutputOctets);

    // [1.6] Populate optional parameter CC-Service-Specific-Units 
    // Set the CC-Service-Specific-Units AVP.
    // The data type CC-Service-Specific-Units is Unsigned64.
    // This contains number of service specific units (eg: number of events,
    // points) given in a selected service.
    // The AVP Code of CC-Service-Specific-Units is 417.
    CCServiceSpecificUnits ccServiceSpecificUnits(20);
    usedServiceUnit.setCCServiceSpecificUnits(ccServiceSpecificUnits);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Cost-Information grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      CostInformation object passed as a reference to this function.
 *
 *  Input Parameters:
 *      CostInformation &costInfo: Reference to the CostInformation 
 *      object, grouped AVPs of which needs to be set.
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
void PopulateCostInformation(CostInformation &costInfo)
{
    // [1] Populate "Cost-Information" grouped AVPs. 

    // [1.1] Populate mandatory parameter Unit-Value
    // Set the Unit-Value AVP.
    // The data type Unit-Value is Grouped.
    // This specifies the units as decimal value.
    // The AVP Code of Unit-Value is 445.
    UnitValue unitValue;
                                                                                                                             
    // [1.1.1] Populate "Unit-Value" grouped AVPs.
                                                                                                                             
    // [1.1.1.1] Populate mandatory parameter Value-Digits
    // Set the Value-Digits AVP.
    // The data type Value-Digits is Integer64.
    // This contains the significant digits of the number.
    // Eg: for the monetary amount $0.05, the value of Value-Digits is 5 and
    // Exponent AVP must be set to -2.
    // The AVP Code of Value-Digits is 447.
    ValueDigits valueDigits(3);
    unitValue.setValueDigits(valueDigits);
                                                                                                                             
    // [1.1.1.2] Populate optional parameter Exponent
    // Set the Exponent AVP.
    // The data type Exponent is Grouped.
    // This contains the exponent value to be applied for the Value-Digits AVP.
    // The AVP Code of Exponent is 429.
    Exponent exponent(-2);
    unitValue.setExponent(exponent);
                                                                                                                             
    // [1.1.2] Set "Unit-Value" AVP in Cost-Information object.
    costInfo.setUnitValue(unitValue);

    // [1.2] Populate mandatory parameter Currency-Code
    // Set the Currency-Code AVP.
    // The data type Currency-Code is Unsigned32.
    // This contains currency code that specifies in which currency the values
    // of AVPs containing monetary units were given. It is specified by using
    // numeric values defined in ISO 4217 standard.
    // The AVP Code of Currency-Code is 425.
    CurrencyCode currencyCode(840);
    costInfo.setCurrencyCode(currencyCode);
                                                                                                                             
    // [1.3] Populate optional parameter Cost-Unit
    // Set the Cost-Unit AVP.
    // The data type Cost-Unit is UTF8String.
    // This specifies the applicable unit to Cost-Information when the service
    // cost is a cost per unit.Eg: cost of service is $1 per minute.
    // The AVP Code of Cost-Unit is 424.
    CostUnit costUnit("hours");
    costInfo.setCostUnit(costUnit);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Final-Unit-Indication grouped AVP.
 *      This populate the grouped AVPs and sets the values in the
 *      RequestedServiceUnit object passed as a reference to this function.
 *
 *  Input Parameters:
 *      FinalUnitIndication &finalUnitInd: Reference to the
 *      FinalUnitIndication object, grouped AVPs of which needs to be set.
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
void PopulateFinalUnitIndication(FinalUnitIndication &finalUnitInd)
{
    // [1] Populate "Final-Unit-Indication" grouped AVPs.
                                                                                                                             
    // [1.1] Populate mandatory AVPs

    // [1.1.1] Populate mandatory parameter Final-Unit-Action
    // Set the Final-Unit-Action AVP.
    // The data type Final-Unit-Action is Enumerated.
    // This indicates to the credit-control client the action to be taken when
    // the user's account cannot cover the service cost.
    // The AVP Code of Final-Unit-Action is 449.
    FinalUnitAction finalUnitAction(FinalUnitAction::REDIRECT);
    finalUnitInd.setFinalUnitAction(finalUnitAction);

    // [1.2] Populate optional AVPs

    // [1.2.1] Populate optional(multiple occurence) parameter 
    //         Restriction-Filter-Rule
    // Set the Restriction-Filter-Rule AVP.
    // The data type Restriction-Filter-Rule is IpFilterRule.
    // This provides filter rules corresponding to services that are to remain
    // accessible even if there are no more service units granted. The access 
    // device has to configure the specified filter rules for the subscriber
    // and MUST drop all the packets not matching these filter.
    // The AVP Code of Restriction-Filter-Rule is 438.
    IPFilterRule ipFltRule;
    PopulateIPFilterRule(ipFltRule);
    RestrictionFilterRule restrictFltrRule(ipFltRule);
    finalUnitInd.addRestrictionFilterRule(restrictFltrRule);

    // [1.2.2] Populate optional(multiple occurence) parameter 
    //         Filter-Id
    // Set the Filter-Id AVP.
    // The data type Filter-Id is UTF8String.
    // This contains the name of the filter list for this user.
    // Zero or more Filter-Id AVPs MAY be sent in an authorisation answer.
    // The AVP Code of Filter-Id is 11.
    FilterId filterId("filterlist1"); // not clear
    finalUnitInd.addFilterId(filterId);

    // [1.2.3] Populate optional parameter Redirect-Server
    // Set the Redirect-Server AVP.
    // The data type Redirect-Server is Grouped.
    // This contains the address information of the redirect server 
    // (e.g., HTTP redirect server, SIP Server) with which the end user is to
    // be connected when the account cannot cover the service cost.It MUST be
    // present when the Final-Unit-Action AVP is set to REDIRECT.
    // The AVP Code of Redirect-Server is 434.
    RedirectServer redirectServer; 

    // [1.2.3.1] Populate Redirect-Server grouped AVPs

    // [1.2.3.1.1] Populate optional parameter Redirect-Address-Type
    // Set the Redirect-Address-Type AVP.
    // The data type Redirect-Address-Type is Enumerated.
    // This defines the address type of the address given in the 
    // Redirect-Server-Address AVP.
    // The AVP Code of Redirect-Address-Type is 433.
    RedirectAddressType redirectAddrType(RedirectAddressType::IPv4_Address); 
    redirectServer.setRedirectAddressType(redirectAddrType);

    // [1.2.3.1.2] Populate optional parameter Redirect-Server-Address
    // Set the Redirect-Server-Address AVP.
    // The data type Redirect-Server-Address is UTF8String.
    // This defines the address of the redirect server (eg: HTTP redirect 
    // server,SIP server) wih which the end user is to be connected when the 
    // account cannot cover the service cost.
    // The AVP Code of Redirect-Server-Address is 435.
    RedirectServerAddress redirectSvrAddr("192.168.4.2");
    redirectServer.setRedirectServerAddress(redirectSvrAddr);

    // [1.2.3.2] Set Redirect-Server in Final-Unit-Indication object 
    finalUnitInd.setRedirectServer(redirectServer);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the IPFilterRule object.
 *      This sets the values in the IPFilterRule object passed as a
 *      reference to this function.
 *
 *  Input Parameters:
 *      IPFilterRule &ipFltRule: Reference to the IPFilterRule object
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
 *
 * Revision History:
 *  ---------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ---------------------------------------------------------------------------
 *  Kamakshi     07-09-06    Bug Id 4265     Removed the icmptypes set in
                                             IPFilterRule.
 *
 ****************************************************************************/
void PopulateIPFilterRule(IPFilterRule &ipFltRule)
{
    // [1] Populate "IPFilterRule" object fields.
                                                                                                    
    ipFltRule.action = IPFilterRule::PERMIT;
    ipFltRule.dir = IPFilterRule::IN;
    ipFltRule.proto = 0;
        // Value 0 means wildcard number that matches any IP protocol
        // If representation is exact only ipno is used
    IPFilterRule::SrcDst srcSam(IPFilterRule::SrcDst::EXACT,"192.168.9.2",0);
    IPFilterRule::SrcDst dstSam(IPFilterRule::SrcDst::EXACT,"192.168.9.3",0);
    ShortRange srcPortRng(5000,5005), dstPortRng(5006,5010);
    srcSam.portRangeList.push_front(srcPortRng);
    dstSam.portRangeList.push_front(dstPortRng);
    ipFltRule.src = srcSam;
    ipFltRule.dst = dstSam;
    ipFltRule.frag = false;
    ipFltRule.established = false;
    ipFltRule.setup = false;
    ipFltRule.ipOptionList.push_front(4);
    ipFltRule.tcpOptionList.push_front(1);
    ipFltRule.tcpOptionList.push_front(3);
    ipFltRule.tcpOptionList.push_front(4);
    ipFltRule.tcpFlagList.push_front(2);
    ipFltRule.tcpFlagList.push_front(3);
    ipFltRule.tcpFlagList.push_front(4);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Service-Information
 *      grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      ServiceInformation object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      ServiceInformation &serviceInfo: Refernce to the ServiceInformation
 *      object, the grouped AVP of which needs to be set.
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
void PopulateServiceInformation(ServiceInformation &serviceInfo) 
{
    // [1] Populate "Service-Information" grouped AVPs. 

    // [1.1] Populate optional parameter "PS-Information"
    // Set the PS-Information AVP.
    // The data type PS-Information is Grouped.
    // Its purpose is to allow transmission of additional PS
    // service specific information elements
    // The AVP Code of PS-Information is 873.
    PSInformation psInfo;

    // [1.1.1] Populate "PS-Information" grouped AVPs.
    PopulatePSInformation(psInfo);

    // [1.1.2] Add "PS-Information" AVP to Service-Information object.
    serviceInfo.setPSInformation(psInfo);

    // [1.2] Populate optional parameter "WLAN-Information"
    // Set the WLAN-Information AVP.
    // The data type WLAN-Information is Grouped.
    // Its purpose is to allow transmission of additional WLAN
    // service specific information elements
    // The AVP Code of WLAN-Information is 873.
    WLANInformation wlanInfo;

    // [1.2.1] Populate "WLAN-Information" grouped AVPs.
    PopulateWLANInformation(wlanInfo);

    // [1.2.2] Add "WLAN-Information" AVP to Service-Information object.
    serviceInfo.setWLANInformation(wlanInfo);

    // [1.3] Populate optional parameter "IMS-Information"
    // Set the IMS-Information AVP.
    // The data type IMS-Information is Grouped.
    // Its purpose is to allow transmission of additional IMS
    // service specific information elements
    // The AVP Code of IMS-Information is 873.
    IMSInformation imsInfo;

    // [1.3.1] Populate "IMS-Information" grouped AVPs.
    PopulateIMSInformation(imsInfo);

    // [1.3.2] Add "IMS-Information" AVP to Service-Information object.
    serviceInfo.setIMSInformation(imsInfo);

    // [1.4] Populate optional parameter "MMS-Information"
    // Set the MMS-Information AVP.
    // The data type MMS-Information is Grouped.
    // Its purpose is to allow transmission of additional MMS
    // service specific information elements
    // The AVP Code of MMS-Information is 873.
    MMSInformation mmsInfo;

    // [1.4.1] Populate "MMS-Information" grouped AVPs.
    PopulateMMSInformation(mmsInfo);

    // [1.4.2] Add "MMS-Information" AVP to Service-Information object.
    serviceInfo.setMMSInformation(mmsInfo);

    // [1.5] Populate optional parameter "LCS-Information"
    // Set the LCS-Information AVP.
    // The data type LCS-Information is Grouped.
    // Its purpose is to allow transmission of additional LCS
    // service specific information elements
    // The AVP Code of LCS-Information is 873.
    LCSInformation lcsInfo;

    // [1.5.1] Populate "LCS-Information" grouped AVPs.
    PopulateLCSInformation(lcsInfo);

    // [1.5.2] Add "LCS-Information" AVP to Service-Information object.
    serviceInfo.setLCSInformation(lcsInfo);

    // [1.6] Populate optional parameter "PoC-Information"
    // Set the PoC-Information AVP.
    // The data type PoC-Information is Grouped.
    // Its purpose is to allow transmission of additional PoC
    // service specific information elements
    // The AVP Code of PoC-Information is 873.
    PoCInformation pocInfo;

    // [1.6.1] Populate "PoC-Information" grouped AVPs.
    PopulatePoCInformation(pocInfo);

    // [1.6.2] Add "PoC-Information" AVP to Service-Information object.
    serviceInfo.setPoCInformation(pocInfo);

    // [1.7] Populate optional parameter "MBMS-Information"
    // Set the MBMS-Information AVP.
    // The data type MBMS-Information is Grouped.
    // Its purpose is to allow transmission of additional MBMS
    // service specific information elements
    // The AVP Code of MBMS-Information is 873.
    MBMSInformation mbmsInfo;

    // [1.7.1] Populate "MBMS-Information" grouped AVPs.
    PopulateMBMSInformation(mbmsInfo);

    // [1.7.2] Add "MBMS-Information" AVP to Service-Information object.
    serviceInfo.setMBMSInformation(mbmsInfo);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the PS-Information
 *      grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      PS-Information object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      PSInformation &psInfo: Refernce to the ServiceInformation
 *      object, the grouped AVP of which needs to be set.
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
void PopulatePSInformation(PSInformation &psInfo) 
{
    // [1] Populate "PS-Information" grouped AVPs. 

    // [1.1] Populate optional AVPs. 

    // [1.1.1] Populate optional parameter 3GPP-Charging-Id.
    // Set 3GPP-Charging-Id AVP.
    // The data type of 3GPP-Charging-Id is Unsigned32.
    // This contains the Charging ID for this PDP context (this together with
    // GGSN-Address constitutes a unique identifier for the PDP context).
    // The AVP Code for 3GPP-Charging-Id is 2
    RfRo3GPPChargingId ims3gppChargingId(1500u); 
    psInfo.setRfRo3GPPChargingId(ims3gppChargingId);

    // [1.1.2] Populate optional parameter 3GPP-PDP-Type. 
    // Set 3GPP-PDP-Type AVP.
    // The data type of 3GPP-PDP-Type is Unsigned32.
    // This it denotes the type of PDP context e.g IP or PPP.
    // The AVP Code for 3GPP-PDP-Type is 3.
    RfRo3GPPPDPType ims3gppPdpType(1);
    psInfo.setRfRo3GPPPDPType(ims3gppPdpType);

    // [1.1.3] Populate optional parameter PDP-Address. 
    // Set PDP-Address AVP.
    // The data type of PDP-Address is Address.
    // This holds the IP-Address associated with the PDP session.
    // The AVP Code for PDP-Address is 1227.
    Address addr1(Address::IPV4, "192.168.5.1");
    PDPAddress pdpAddr(addr1);
    psInfo.setPDPAddress(pdpAddr);

    // [1.1.5] Populate optional parameter SGSN-Address. 
    // Set SGSN-Address AVP.
    // The data type of SGSN-Address is Address.
    // This holds the IP-Address of SGSN that was used during a report.
    // The AVP Code for SGSN-Address is 1228.
    Address addr2(Address::IPV4, "192.168.5.2");
    SGSNAddress sgsnAddr(addr2);
    psInfo.setSGSNAddress(sgsnAddr);

    // [1.1.6] Populate optional parameter GGSN-Address. 
    // Set GGSN-Address AVP.
    // The data type of GGSN-Address is Address.
    // This holds the IP-Address of the GGSN that generated the GPRS 
    // Charging ID.
    // The AVP Code for GGSN-Address is 847.
    Address addr3(Address::IPV4, "192.168.4.1");
    GGSNAddress ggsnAddr(addr3);
    psInfo.setGGSNAddress(ggsnAddr);

    // [1.1.7] Populate optional parameter CG-Address. 
    // Set CG-Address AVP.
    // The data type of CG-Address is Address.
    // This holds the IP-address of the charging gateway.
    // The AVP Code for CG-Address is 846.
    Address addr4(Address::IPV4, "192.168.6.1");
    CGAddress cgAddr(addr4);
    psInfo.setCGAddress(cgAddr);

    // [1.1.8] Populate optional parameter 3GPP-IMSI-MCC-MNC.
    // Set 3GPP-IMSI-MCC-MNC AVP.
    // The data type of 3GPP-IMSI-MCC-MNC is UFT8String.
    // This contains MCC and MNC extracted from the user's IMSI
    // (first 5 or 6 digits, as applicable from the presented IMSI)
    // The AVP Code for 3GPP-IMSI-MCC-MNC is 8.
    RfRo3GPPIMSIMCCMNC imsiMccMnc("091080");
    psInfo.setRfRo3GPPIMSIMCCMNC(imsiMccMnc);

    // [1.1.9] Populate optional parameter 3GPP-GGSN-MCC-MNC.
    // Set 3GPP-GGSN-MCC-MNC AVP.
    // The data type of 3GPP-GGSN-MCC-MNC is UFT8String.
    // This contains MCC and MNC of the network the GGSN belongs to.
    // The AVP Code for 3GPP-GGSN-MCC-MNC is 9.
    RfRo3GPPGGSNMCCMNC ggsnMccMnc("091040");
    psInfo.setRfRo3GPPGGSNMCCMNC(ggsnMccMnc);

    // [1.1.10] Populate optional parameter 3GPP-NSAPI.
    // Set 3GPP-NSAPI AVP.
    // The data type of 3GPP-NSAPI is UFT8String.
    // This identifies a particular PDP.
    // The AVP Code for 3GPP-NSAPI is 10.
    RfRo3GPPNSAPI imsNSAPI("34"); // not clear
    psInfo.setRfRo3GPPNSAPI(imsNSAPI);

    // [1.1.11] Populate optional parameter Called-Station-Id.
    // Set Called-Station-Id AVP.
    // The data type of Called-Station-Id is UFT8String.
    // This allows the NAS to send in the request,the ASCII string describing
    // the layer 2 address that the user contacted to. For dialup access,this
    // can be a phone number,obtained using Dialed Number identification(DNIS)
    // or a similar technology. For the use with IEEE 802 access,the Called-
    // Station-Id MAY contain MAC address formatted as described in RAD802.1X.
    // [IEEE 802.1X Remote Authentication Dial In User Service (RADIUS)
    //  Usage Guidelines].
    // The AVP Code for Called-Station-Id is 30.
    CalledStationId calledStnId("00-10-A4-23-19-C0:AP1");
    psInfo.setCalledStationId(calledStnId);

    // [1.1.12] Populate optional parameter 3GPP-Session-Stop-Indicator.
    // Set 3GPP-Session-Stop-Indicator AVP.
    // The data type of 3GPP-Session-Stop-Indicator is OctetString.
    // This indicates to the AAA server that the last PDP context of a session
    // is released and that the PDP session has been terminated.
    // Its value is set to all 1. 1111,1111
    // The AVP Code for 3GPP-Session-Stop-Indicator is 2001.
    RfRo3GPPSessionStopIndicator sessStopInd("FF"); // not clear
    psInfo.setRfRo3GPPSessionStopIndicator(sessStopInd);

    // [1.1.13] Populate optional parameter 3GPP-Selection-Mode.
    // Set 3GPP-Selection-Mode AVP.
    // The data type of 3GPP-Selection-Mode is UTF8String.
    // This contains the selection mode for this PDP context received in the 
    // create PDP context request message.
    // Refer- 3GPP TS 29.060 (7.7.12)
    // The AVP Code for 3GPP-Selection-Mode is 12.
    RfRo3GPPSelectionMode selectMode("FC"); // not clear
    psInfo.setRfRo3GPPSelectionMode(selectMode);

    // [1.1.14] Populate optional parameter 3GPP-Charging-Characteristics.
    // Set 3GPP-Charging-Characteristics AVP.
    // The data type of 3GPP-Charging-Characteristics is UTF8String.
    // This contains the charging characteristics for this PDP context 
    // received in the Create PDP Context Request Message (only available in 
    // R99 and later releases) 
    // Refer TS 32.251 and 32.298. This consists of a string os 16 bits
    // designated as Profile(P) and Behaviour(B).
    // P3(N)flag - normal charging, P2(P)flag - prepaid charging, 
    // P1(F)flag - flat rate charging,P0(H)flag - charging by hot billing
    // The AVP Code for 3GPP-Charging-Characteristics is 13.
    RfRo3GPPChargingCharacteristics chargingCharacter("F40F"); // not clear
    psInfo.setRfRo3GPPChargingCharacteristics(chargingCharacter);

    // [1.1.15] Populate optional parameter 3GPP-SGSN-MCC-MNC.
    // Set 3GPP-SGSN-MCC-MNC AVP.
    // The data type of 3GPP-SGSN-MCC-MNC is UFT8String.
    // This contains MCC and MNC extracted from the RAI within the Create PDP 
    // Context Request or Update PDP Context Request message.
    // The AVP Code for 3GPP-SGSN-MCC-MNC is 18.
    RfRo3GPPSGSNMCCMNC sgsnMccMnc("091044");
    psInfo.setRfRo3GPPSGSNMCCMNC(sgsnMccMnc);

    // [1.1.16] Populate optional parameter 3GPP-MS-TimeZone. 
    // Set 3GPP-MS-TimeZone AVP.
    // The data type of 3GPP-MS-TimeZone is OctetString.
    // This indicates the offset between universal time and local time in 
    // steps of 15 minutes of where the MS currently resides.
    // The AVP Code for 3GPP-MS-TimeZone is 23.
    RfRo3GPPMSTimeZone msTimeZone("10");
    psInfo.setRfRo3GPPMSTimeZone(msTimeZone);

    // [1.1.19] Populate optional parameter 3GPP-User-Location-Info. 
    // Set 3GPP-User-Location-Info AVP.
    // The data type of 3GPP-User-Location-Info is OctetString.
    // This indicates details of where the UE is currenly located 
    // (e.g SAI or CGI)
    // The AVP Code for 3GPP-User-Location-Info is 22.
    RfRo3GPPUserLocationInfo userLocation("CGI");
    psInfo.setRfRo3GPPUserLocationInfo(userLocation);

    // [1.1.20] Populate optional parameter 3GPP-RAT-Type. 
    // Set 3GPP-RAT-Type AVP.
    // The data type of 3GPP-RAT-Type is OctetString.
    // This indicates which Radio AccessTechnology is currently serving the UE.
    // The AVP Code for 3GPP-RAT-Type is 21.
    RfRo3GPPRATType ratType("WLAN"); 
    psInfo.setRfRo3GPPRATType(ratType);

    // [1.1.21] Populate optional parameter PS-Furnish-Charging-Information. 
    // Set PS-Furnish-Charging-Information AVP.
    // The data type of PS-Furnish-Charging-Information is Grouped.
    // The purpose is to add online charging session specific information, 
    // received via the Ro Reference point onto the Rf reference point in order
    // to facilitate its inclusion in CDRs.This information element may be 
    // received in CCA message via the Ro reference point. In situations where
    // online and offline charging are active in parallel, the information
    // element is transparently copied into ACR to be sent on the Rf reference 
    // point.
    // The AVP Code for PS-Furnish-Charging-Information is 865.
    PSFurnishChargingInformation psFurnishChrgInfo;
    PopulatePSFurnishChargingInformation(psFurnishChrgInfo)  ;
    psInfo.setPSFurnishChargingInformation(psFurnishChrgInfo);
   
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the WLAN-Information
 *      grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      WLANInformation object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      WLANInformation &wlanInfo: Refernce to the WLANInformation
 *      object, the grouped AVP of which needs to be set.
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
void PopulateWLANInformation(WLANInformation &wlanInfo) 
{
    // [1] Populate "WLAN-Information" grouped AVPs. 

    // [1.1] Populate optional AVPs. 

    // [1.1.1] Populate optional parameter WLAN-Session-Id. 
    // Set WLAN-Session-Id AVP.
    // The data type of WLAN-Session-Id is Unsigned32.
    // This contains the charging id generated by the AAA server for the 
    // session.
    // The AVP Code for WLAN-Session-Id is 2000.
    // not clear. Added by Kamakshi. The AVP type is specified as UTF8String
    // in TS 32.299, Table 7.2 but in AVP description its specified as
    // Unsigned32.
    WLANSessionId wlanSessId(1520u); 
    wlanInfo.setWLANSessionId(wlanSessId);

    // [1.1.2] Populate optional parameter PDG-Address. 
    // Set PDG-Address AVP.
    // The data type of PDG-Address is Address.
    // This contains the PDG IP address.
    // The AVP Code for PDG-Address is 895.
    Address addrp(Address::IPV4, "192.168.7.5");
    PDGAddress pdgAddr(addrp); 
    wlanInfo.setPDGAddress(pdgAddr);

    // [1.1.3] Populate optional parameter PDG-Charging-Id. 
    // Set PDG-Charging-Id AVP.
    // The data type of PDG-Charging-Id is Unsigned32.
    // This contains the charging identifier generated by the PDG for the 
    // tunnel. Charging identifier is generated at tunnel establishment and 
    // transferred to 3GPP AAA server.
    // The AVP Code for PDG-Charging-Id is 896.
    PDGChargingId pdgChargingId(22); 
    wlanInfo.setPDGChargingId(pdgChargingId);

    // [1.1.4] Populate optional parameter WAG-Address. 
    // Set WAG-Address AVP.
    // The data type of WAG-Address is Address.
    // This contains the WAG IP address.
    // The AVP Code for WAG-Address is 890.
    Address addrw(Address::IPV4, "192.168.7.6");
    WAGAddress wagAddr(addrw); 
    wlanInfo.setWAGAddress(wagAddr);

    // [1.1.5] Populate optional parameter WAG-PLMN-Id. 
    // Set WAG-PLMN-Id AVP.
    // The data type of WAG-PLMN-Id is OctetString.
    // This contains the WAG PLMN Id( MCC and MNC). Coding of this AVP is 
    // same as 3GPP-MCC-MNC coding described in 3GPP TS 29.061 .
    // The AVP Code for WAG-PLMN-Id is 891.
    WAGPLMNId wagPlmnId("09144"); 
    wlanInfo.setWAGPLMNId(wagPlmnId);

    // [1.1.6] Populate optional parameter WLAN-Radio-Container. 
    // Set WLAN-Radio-Container AVP.
    // The data type of WLAN-Radio-Container is Grouped.
    // The AVP Code for WLAN-Radio-Container is 892.
//    WLANRadioContainer wlanRadioContainer;

    // [1.1.6.1] Populate WLAN-Technology grouped AVPs. 

    // [1.1.6.1.1] Populate optional parameter WLAN-Technology. 
    // Set WLAN-Technology AVP.
    // The data type of WLAN-Technology is Unsigned32.
    // The contents of this AVP is tbd.
    // The AVP Code for WLAN-Technology is 893.
//    WLANTechnology wlanTechnology(25); 
//    wlanRadioContainer.setWLANTechnology(wlanTechnology);

//    wlanInfo.setWLANRadioContainer(wlanRadioContainer);
    // Added by Kamakshi 
    // The WLAN-Radio-Container AVP contents are not defined
    // so this AVP need not be set.

    // [1.1.7] Populate optional parameter WLAN-UE-Local-IPAddress. 
    // Set WLAN-UE-Local-IPAddress AVP.
    // The data type of WLAN-UE-Local-IPAddress is Address.
    // The AVP Code for WLAN-UE-Local-IPAddress is 894.
    Address addru(Address::IPV4, "192.168.7.7");
    WLANUELocalIPAddress wlanUELclAddr(addru);
    wlanInfo.setWLANUELocalIPAddress(wlanUELclAddr);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the IMS-Information
 *      grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      IMSInformation object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      IMSInformation &imsInfo: Refernce to the IMSInformation
 *      object, the grouped AVP of which needs to be set.
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
void PopulateIMSInformation(IMSInformation &imsInfo) 
{
    // [1] Populate "IMS-Information" grouped AVPs. 

    // [1.1] Populate optional AVPs. 

    // [1.1.1] Populate optional parameter Event-Type. 
    // Set Event-Type AVP.
    // The data type of Event-Type is Grouped.
    // This specifies the role of the PoC server.
    // The AVP Code for Event-Type is 823.
    EventType eventType;
    PopulateEventType(eventType);
    imsInfo.setEventType(eventType);

    // [1.1.3] Populate optional parameter Node-Functionality. 
    // Set Node-Functionality AVP.
    // The data type of Node-Functionality is enumerated.
    // This includes the functionality identifier of the node.
    // The AVP Code for Node-Functionality is 862.
    NodeFunctionality nodeFunct(NodeFunctionality::P_CSCF); 
    imsInfo.setNodeFunctionality(nodeFunct);

    // [1.1.4] Populate optional parameter User-Session-ID. 
    // Set User-Session-ID AVP.
    // The data type of User-Session-ID is UTF8String.
    // This holds the session identifier. For a SIP session the
    // User-Session-ID contains the SIP Call ID 
    // The AVP Code for User-Session-ID is 830.
    UserSessionID userSessId("a84b4c76e66710"); // not clear
    imsInfo.setUserSessionID(userSessId);

    // [1.1.6] Populate optional parameter Called-Party-Address. 
    // Set Called-Party-Address AVP.
    // The data type of Called-Party-Address is UTF8String.
    // This holds the address (Public User ID,SIP URL,E.164 etc.)
    // of the party to whom a session is established.
    // The AVP Code for Called-Party-Address is 832.
    CalledPartyAddress calledPartyAddr("sip:alice@Atlanta.com"); 
    imsInfo.setCalledPartyAddress(calledPartyAddr); 

    // [1.1.7] Populate optional parameter Time-Stamps. 
    // Set Time-Stamps AVP.
    // The data type of Time-Stamps is Grouped.
    // This holds the time of the initial SIP request and the time
    // of response to the initial SIP request.
    // The AVP Code for Time-Stamps is 833.
    TimeStamps timeStamps;

    // [1.1.7.1] Populate Time-Stamps grouped AVPs.
                                                                               
    // [1.1.7.1.1] Populate optional parameter SIP-Request-Timestamp
    // Set SIP-Request-Timestamp AVP.
    // The data type of SIP-Request-Timestamp is time.
    // This holds the time in UTC format of the SIP request
    // (e.g. Invite, Update)
    // The AVP Code for SIP-Request-Timestamp is 834.
    SIPRequestTimestamp sipReqTimestamp(50);
    timeStamps.setSIPRequestTimestamp(sipReqTimestamp);
 
    // [1.1.7.1.2] Populate optional parameter SIP-Response-Timestamp
    // Set SIP-Response-Timestamp AVP.
    // The data type of SIP-Response-Timestamp is time.
    // This holds the time in UTC format of the SIP response (eg 200OK)
    // The AVP Code for SIP-Response-Timestamp is 835.
    SIPResponseTimestamp sipRspTimestamp(70);
    timeStamps.setSIPResponseTimestamp(sipRspTimestamp);
 
    imsInfo.setTimeStamps(timeStamps); 

    // [1.1.8] Populate optional(multiple occurence) parameter 
    //          Application-Server-Information. 
    // Set Application-Server-Information AVP.
    // The data type of Application-Server-Information is Grouped.
    // This specifies the role of the PoC server.
    // The AVP Code for Application-Server-Information is 850.
    ApplicationServerInformation appServerInfo;
    PopulateApplicationServerInformation(appServerInfo);
    imsInfo.addApplicationServerInformation(appServerInfo);

    // [1.1.9] Populate optional(multiple occurence) parameter 
    //          Inter-Operator-Identifier.
    // Set Inter-Operator-Identifier AVP.
    // The data type of Inter-Operator-Identifier is Grouped.
    // This holds the identification of the network neighbours 
    // (originating and terminating) as exchanged via SIP signalling.
    // The AVP Code for Inter-Operator-Identifier is 838.
    InterOperatorIdentifier interOperId;

    // [1.1.9.1] Populate Inter-Operator-Identifier grouped AVPs.

    // [1.1.9.1.1] Populate optional parameter Origination-IOI 
    // Set Originating-IOI AVP.
    // The data type of Originating-IOI is UTF8String.
    // This holds the Inter Operator Identifier (IOI) for the originating 
    // network as generated by the IMS network element which takes
    // responsibility for populating this parameter in a SIP request.
    // The AVP Code for Originating-IOI is 839.
    OriginatingIOI originatingIOI("142333"); // not clear
    interOperId.setOriginatingIOI(originatingIOI);

    // [1.1.9.1.2] Populate optional parameter Terminating-IOI 
    // Set Terminating-IOI AVP.
    // The data type of Terminating-IOI is UTF8String.
    // This holds the Inter Operator Identifier (IOI) for the Terminating 
    // network as generated by the IMS network element which takes
    // responsibility for populating this parameter in a SIP response.
    // The AVP Code for Terminating-IOI is 840.
    TerminatingIOI terminatingIOI("132434"); // not clear
    interOperId.setTerminatingIOI(terminatingIOI);

    imsInfo.addInterOperatorIdentifier(interOperId); 

    // [1.1.10] Populate optional parameter IMS-Charging-Identifier. 
    // Set IMS-Charging-Identifier AVP.
    // The data type of IMS-Charging-Identifier is UTF8String.
    // This holds the IMS Charging Identifier as generated by a IMS node
    // for a SIP session..
    // The AVP Code for IMS-Charging-Identifier is 841.
    IMSChargingIdentifier imsChargingId("56"); // not clear
    imsInfo.setIMSChargingIdentifier(imsChargingId);

    // [1.1.11] Populate optional(multiple occurence) parameter 
    //          SDP-Session-Description. 
    // Set SDP-Session-Description AVP.
    // The data type of SDP-Session-Description is UTF8String.
    // This holds the content of a "attribute-line" (i=,c=,b=,k=,a=,etc.)
    // related to a session.
    // The AVP Code for SDP-Session-Description is 842.
    SDPSessionDescription sdpDescrpt("a=rtpmap:0 PCMU/8000"); // not clear
    imsInfo.addSDPSessionDescription(sdpDescrpt);

    // [1.1.12] Populate optional(multiple occurence) parameter 
    //          SDP-Media-Component. 
    // Set SDP-Media-Component AVP.
    // The data type of SDP-Media-Component is Grouped.
    // This specifies the role of the PoC server.
    // The AVP Code for SDP-Media-Component is 843.
    SDPMediaComponent sdpMediaCompo;
    PopulateSDPMediaComponent(sdpMediaCompo);
    imsInfo.addSDPMediaComponent(sdpMediaCompo);

    // [1.1.13] Populate optional parameter Served-Party-IP-Address. 
    // Set Served-Party-IP-Address AVP.
    // The data type of Served-Party-IP-Address is Address.
    // This holds the IP address of either the calling or called party,
    // depending on whether the P-CSCF is in touch with the calling or 
    // the called party.
    // The AVP Code for Served-Party-IP-Address is 848.
    Address addr(Address::IPV4, "192.168.4.5");
    ServedPartyIPAddress servedPartyIPAddr(addr); 
    imsInfo.setServedPartyIPAddress(servedPartyIPAddr);

    // [1.1.14] Populate optional parameter Server-Capabilities. 
    // Set Server-Capabilities AVP.
    // The data type of Server-Capabilities is Grouped.
    // This contains information to assist the I-CSCF in the selection
    // of an S-CSCF.
    // The AVP Code for Server-Capabilities is 603.
    ServerCapabilities serverCapb;
    PopulateServerCapabilities(serverCapb);
    imsInfo.setServerCapabilities(serverCapb);

    // [1.1.15] Populate optional parameter Trunk-Group-ID. 
    // Set Trunk-Group-ID AVP.
    // The data type of Trunk-Group-ID is Grouped.
    // This identifies the incoming and out going PSTN legs.
    // The AVP Code for Trunk-Group-ID is 851.
    TrunkGroupID trunkGrpId;

    // [1.1.15.1] Populate Trunk-Group-ID grouped AVPs. 

    // [1.1.15.1.1] Populate optional parameter Incoming-Trunk-Group-ID. 
    // Set Incoming-Trunk-Group-ID AVP.
    // The data type of Incoming-Trunk-Group-ID is UTF8String.
    // This identifies the incoming PSTN legs.
    // The AVP Code for Incoming-Trunk-Group-ID is 852.
    IncomingTrunkGroupID incomingTrunkGrpId("105"); 
    trunkGrpId.setIncomingTrunkGroupID(incomingTrunkGrpId);
   
    // [1.1.15.1.2] Populate optional parameter Outgoing-Trunk-Group-ID. 
    // Set Outgoing-Trunk-Group-ID AVP.
    // The data type of Outgoing-Trunk-Group-ID is UTF8String.
    // This identifies the Outgoing PSTN legs.
    // The AVP Code for Outgoing-Trunk-Group-ID is 853.
    OutgoingTrunkGroupID outgoingTrunkGrpId("106"); 
    trunkGrpId.setOutgoingTrunkGroupID(outgoingTrunkGrpId);
   
    imsInfo.setTrunkGroupID(trunkGrpId);

    // [1.1.16] Populate optional parameter Bearer-Service. 
    // Set Bearer-Service AVP.
    // The data type of Bearer-Service is OctetString.
    // This holds the used bearer service for the PSTN leg.
    // The AVP Code for Bearer-Service is 854.
    BearerService bearerService("mms"); // not clear
    imsInfo.setBearerService(bearerService);

    // [1.1.17] Populate optional parameter Service-Id. 
    // Set Service-Id AVP.
    // The data type of Service-Id is UTF8String.
    // This  identifies the service the MRFC is hosting. For conferences
    // the conference ID is used as the value of this parameter.
    // The AVP Code for Service-Id is 855.
    ServiceId serviceId("45"); // --not clear
    imsInfo.setServiceId(serviceId);

    // [1.1.19] Populate optional(multiple occurence) parameter Message-Body. 
    // Set Message-Body AVP.
    // The data type of Message-Body is Grouped.
    // This holds information about the message bodies including
    // user-to-user data.
    // The AVP Code for Message-Body is 889.
    MessageBody msgBody1;
    PopulateMessageBody(msgBody1);
    imsInfo.addMessageBody(msgBody1);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Event-Type
 *      grouped AVP.
 *      This populate the grouped AVPs and sets the values in the
 *      EventType object passed as a reference to this
 *      function.
 *
 *  Input Parameters:
 *      EventType &eventType: Refernce to the EventType
 *      object, the grouped AVP of which needs to be set.
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
void PopulateEventType(EventType &eventType)
{
    // [1] Populate "Event-Type" grouped AVPs.

    // [1.1] Populate optional AVPs.

    // [1.1.1] Populate optional parameter SIP-Method.
    // Set SIP-Method AVP.
    // The data type of SIP-Method is UTF8String.
    // This holds the name of the SIP Method (INVITE,UPDATE,etc) causing an
    // accounting request to be sent to the CDF.
    // The AVP Code for SIP-Method is 824.
//    SIPMethod sipMethod("INV");
    SIPMethod sipMethod("INVITE");
    eventType.setSIPMethod(sipMethod); 

    // [1.1.2] Populate optional parameter Event.
    // Set Event AVP.
    // The data type of Event is UTF8String.
    // This holds the content of the "Event" header.
    // The AVP Code for Event is 825.
    IMSEvent event("Event:foo;param=abcd;id=1234");
    eventType.setIMSEvent(event);

    // [1.1.3] Populate optional parameter Expires.
    // Set Expires AVP.
    // The data type of Expires is UTF8String.
    // This holds the content of the "Expires" header.
    // The AVP Code for Expires is 888.
    Expires expires(40);
    eventType.setExpires(expires);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Application-Server-Information
 *      grouped AVP.
 *      This populate the grouped AVPs and sets the values in the
 *      ApplicationServerInformation object passed as a reference to this
 *      function.
 *
 *  Input Parameters:
 *      ApplicationServerInformation &appSvrInfo: Refernce to the 
 *      ApplicationServerInformation object,the grouped AVP of which 
 *      needs to be set.
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
void PopulateApplicationServerInformation
             (ApplicationServerInformation &appSvrInfo)
{
    // [1] Populate "Application-Server-Information" grouped AVPs.

    // [1.1] Populate optional AVPs.

    // [1.1.1] Populate optional parameter Application-Server.
    // Set Application-Server AVP.
    // The data type of Application-Server is UTF8String.
    // This holds the SIP URL of the AS addressed during the session.
    // The AVP Code for Application-Server is 836.
   ApplicationServer appServer("myappl.com"); 
   appSvrInfo.setApplicationServer(appServer);

    // [1.1.2] Populate optional(multiple occurence) parameter 
    //            Application-Provided-Called-Party-Address.
    // Set Application-Provided-Called-Party-Address AVP.
    // The data type of Application-Provided-Called-Party-Address isUTF8String.
    // This holds the called party number (SIP URI, E.164),if it is determined
    // by an application server.
    // The AVP Code for Application-Provided-Called-Party-Address is 837.
    ApplicationProvidedCalledPartyAddress appCalledAddr("sip:bob@example.com");
    appSvrInfo.addApplicationProvidedCalledPartyAddress(appCalledAddr);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the SDP-Media-Component
 *      grouped AVP.
 *      This populate the grouped AVPs and sets the values in the
 *      EventType object passed as a reference to this
 *      function.
 *
 *  Input Parameters:
 *      SDPMediaComponent &sdpMediaCompo: Refernce to the SDPMediaComponent
 *      object, the grouped AVP of which needs to be set.
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
void PopulateSDPMediaComponent(SDPMediaComponent &sdpMediaCompo)
{
    // [1] Populate "SDP-Media-Component" grouped AVPs.

    // [1.1] Populate optional AVPs.

    // [1.1.1] Populate optional parameter SDP-Media-Name.
    // Set SDP-Media-Name AVP.
    // The data type of SDP-Media-Name is UTF8String.
    // This holds the content of a "m=" line in the SDP data.
    // The AVP Code for SDP-Media-Name is 844.
    SDPMediaName sdpMediaName("audio 49172 RTP/AVP 0");
    sdpMediaCompo.setSDPMediaName(sdpMediaName);

    // [1.1.2] Populate optional(multiple occurence) parameter 
    //         SDP-Media-Description.
    // Set SDP-Media-Description AVP.
    // The data type of SDP-Media-Description is UTF8String.
    // This holds the content of a "attribute-line" (i=,c=,b=,k=,a=,etc.) 
    // related to a media component. The attributes are specifying the media
    // described in the SDP-Media-Name AVP.
    // The AVP Code for SDP-Media-Description is 845.
    SDPMediaDescription sdpMediaDescri("a=rtpmap:0 PCMU/8000"); 
    sdpMediaCompo.addSDPMediaDescription(sdpMediaDescri);
    
    // [1.1.3] Populate optional parameter Media-Initiator-Flag.
    // Set Media-Initiator-Flag AVP.
    // The data type of Media-Initiator-Flag is enumerated.
    // This indicates which party has requested the session modification.The
    // default value is '0' indicating the called party initiated the 
    // modification.
    // The AVP Code for Media-Initiator-Flag is 882.
    MediaInitiatorFlag mediaIniFlag(MediaInitiatorFlag::called_party);
    sdpMediaCompo.setMediaInitiatorFlag(mediaIniFlag);

    // [1.1.4] Populate optional parameter Authorized-QoS.
    // Set Authorized-QoS AVP.
    // The data type of Authorized-QoS is UTF8String.
    // This holds the Authorised QoS as defined in TS 23.207/TS 29.207 
    // and applied via the Go reference points.
    // The AVP Code for Authorized-QoS is 849.
    AuthorizedQoS authQoS("040c3f571feaff4040fffd3f3f11"); // not clear
    sdpMediaCompo.setAuthorizedQoS(authQoS);

    // [1.1.5] Populate optional parameter 3GPP-Charging-Id.
    // Set 3GPP-Charging-Id AVP.
    // The data type of 3GPP-Charging-Id is Unsigned32.
    // This contains the Charging ID for this PDP context (this together with
    // GGSN-Address constitutes a unique identifier for the PDP context).
    // The AVP Code for 3GPP-Charging-Id is 2.
    RfRo3GPPChargingId ims3gppChargingId(1500u); 
    sdpMediaCompo.setRfRo3GPPChargingId(ims3gppChargingId);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Server-Capabilities
 *      grouped AVP.
 *      This populate the grouped AVPs and sets the values in the
 *      ServerCapabilities object passed as a reference to this
 *      function.
 *
 *  Input Parameters:
 *      ServerCapabilities &serverCapabilities: Refernce to the 
        ServerCapabilities object, the grouped AVP of which needs to be set.
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
void PopulateServerCapabilities(ServerCapabilities &serverCapabilities)
{
    // [1] Populate "Server-Capabilities" grouped AVPs.

    // [1.1] Populate optional AVPs.

    // [1.1.1] Populate optional(multiple occurence) parameter 
    //          Mandatory-Capability.
    // Set Mandatory-Capability AVP.
    // The data type of Mandatory-Capability is Unsigned32.
    // The value included in this AVP can be used to represent a single 
    // determined mandatory capability of an S-CSCF. Each mandatory capability
    // available in an individual operator's network shall be allocated a 
    // unique value. The allocation of these values to individual capabilities 
    // is an operator issue.
    // The AVP Code for Mandatory-Capability is 604.
    MandatoryCapability mandatoryCapability(1u);
    serverCapabilities.addMandatoryCapability(mandatoryCapability);

    // [1.1.2] Populate optional(multiple occurence) parameter 
    //          Optional-Capability.
    // Set the Optional-Capability AVP.
    // The data type of Optional-Capability AVP is Unsigned32.
    // The value included in this AVP can be used to represent a single
    // determined optional capability of an S-CSCF. Each optional capability
    // available in an individual operator's network shall be allocated a
    // unique value. The allocation of these values to individual capabilities
    // is an operator issue.
    // The AVP Code of Optional-Capability AVP is 605.
    OptionalCapability optionalCapability(1u);
    serverCapabilities.addOptionalCapability(optionalCapability);

    // [1.1.3] Populate optional(multiple occurence) parameter 
    //          Server-Name.
    // Set Server-Name AVP.
    // The data type of AVP is UTF8String.
    // Add the Server-Name AVP to Server-Capabilities AVP..
    // The AVP Code of Server-Name AVP is 602.
    ServerName serverName1("sip:SCSCF-Server@3gppnetwork.com");
    serverCapabilities.addServerName(serverName1);

}


/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Message-Body
 *      grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      MessageBody object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      MessageBody &msgBody: Refernce to the MessageBody
 *      object, the grouped AVP of which needs to be set.
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
void PopulateMessageBody(MessageBody &msgBody) 
{
    // [1] Populate "Message-Body" grouped AVPs. 

    // [1.1] Populate optional AVPs. 

    // [1.1.1] Populate optional parameter Content-Type. 
    // Set Content-Type AVP.
    // The data type of Content-Type is UTF8String.
    // This holds the media type(e.g application/sdp, text/html) of the 
    // message-body.
    // The AVP Code for Content-Type is 826.
    ContentType contentType("application/sdp");
    msgBody.setContentType(contentType);

    // [1.1.2] Populate optional parameter Content-Length. 
    // Set Content-Length AVP.
    // The data type of Content-Length is Unsigned32.
    // This holds the size of the message-body.
    // The AVP Code for Content-Length is 827.
    ContentLength contentLen(20);
    msgBody.setContentLength(contentLen);

    // [1.1.3] Populate optional parameter Content-Disposition. 
    // Set Content-Disposition AVP.
    // The data type of Content-Disposition is UTF8String.
    // This indicates how the message bosy or a message body part is to be 
    // interpreted (e.g session,render)
    // The AVP Code for Content-Disposition is 828.
    ContentDisposition contentDispo("session"); 
    msgBody.setContentDisposition(contentDispo);

    // [1.1.4] Populate optional parameter Originator. 
    // Set Originator AVP.
    // The data type of Originator is Enumerated.
    // This indicates the originating party of the message body.
    // The AVP Code for Originator is 864.
   Originator originator(Originator::Called_Party); 
   msgBody.setOriginator(originator);

}


/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the MMS-Information
 *      grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      MMSInformation object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      MMSInformation &mmsInfo: Refernce to the MMSInformation
 *      object, the grouped AVP of which needs to be set.
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
void PopulateMMSInformation(MMSInformation &mmsInfo) 
{
    // [1] Populate "MMS-Information" grouped AVPs. 

    // [1.1] Populate optional AVPs. 

    // [1.1.1] Populate optional parameter Originator-Address. 
    // Set Originator-Address AVP.
    // The data type of Originator-Address is Grouped.
    // This specifies the role of the PoC server.
    // The AVP Code for Originator-Address is 886.
    OriginatorAddress originatorAddr;
    PopulateOriginatorAddress(originatorAddr);
    mmsInfo.setOriginatorAddress(originatorAddr);
    
    // [1.1.2] Populate optional(multiple occurence) parameter 
    //          Recipient-Address. 
    // Set Recipient-Address AVP.
    // The data type of Recipient-Address is Grouped.
    // This specifies the role of the PoC server.
    // The AVP Code for Recipient-Address is 1201.
    RecipientAddress recipientAddr;
    PopulateRecipientAddress(recipientAddr);
    mmsInfo.addRecipientAddress(recipientAddr);
    
    // [1.1.3] Populate optional parameter Submission-Time. 
    // Set Submission-Time AVP.
    // The data type of Submission-Time is Time.
    // This indicates the time at which the MM was submitted or forwarded 
    // as specified in the corresponding MMI message.
    // The AVP Code for Submission-Time is 1202.
    SubmissionTime submsTime(300);
    mmsInfo.setSubmissionTime(submsTime);

    // [1.1.4] Populate optional parameter MM-Content-Type. 
    // Set MM-Content-Type AVP.
    // The data type of MM-Content-Type is Grouped.
    // This specifies the role of the PoC server.
    // The AVP Code for MM-Content-Type is 1203.
    MMContentType mmContentType;
    PopulateMMContentType(mmContentType);
    mmsInfo.setMMContentType(mmContentType);

    // [1.1.5] Populate optional parameter Priority. 
    // Set Priority AVP.
    // The data type of Priority is Enumerated.
    // The priority of the message is specified by the originator
    // MMs User Agent.
    // The AVP Code for Priority is 1209.
    Priority priority(Priority::Low);
    mmsInfo.setPriority(priority);

    // [1.1.6] Populate optional parameter Message-ID. 
    // Set Message-ID AVP.
    // The data type of Message-ID is UTF8String.
    // This holds the MM identification provided by the originating
    // MMS Relay/Server.
    // This value is same as the Xmms-Message-Id.
    // The AVP Code for Message-ID is 1210.
    MessageID msgId("18569-0.18569.mminject@intersec.fr"); 
    mmsInfo.setMessageID(msgId);

    // [1.1.7] Populate optional parameter Message-Type. 
    // Set Message-Type AVP.
    // The data type of Message-Type is Enumerated.
    // This holds the type of message according to the MMs transaction
    // * e.g sunmission,delivery..
    // The AVP Code for Message-Type is 1211.
    MessageType msgType(MessageType::m_send_req);
    mmsInfo.setMessageType(msgType);

    // [1.1.8] Populate optional parameter Message-Size. 
    // Set Message-Size AVP.
    // The data type of Message-Size is Unsigned32.
    // This holds the total size in bytes of the MM calculated according
    // to TS 23.140..
    // The AVP Code for Message-Size is 1212.
    MessageSize msgSize(120u);
    mmsInfo.setMessageSize(msgSize);

    // [1.1.9] Populate optional parameter Message-Class. 
    // Set Message-Class AVP.
    // The data type of Message-Class is Grouped.
    // This specifies the role of the PoC server.
    // The AVP Code for Message-Class is 1213.
    MessageClass msgClass;

    // [1.1.9.1] Populate Message-Class grouped AVPs. 

    // [1.1.9.1.1] Populate optional parameter Class-Identifier. 
    // Set Class-Identifier AVP.
    // The data type of Class-Identifier is Enumerated.
    // The AVP Code for Class-Identifier is 1214.
    ClassIdentifier classId(ClassIdentifier::Personal);
    msgClass.setClassIdentifier(classId);
   
    // [1.1.9.1.2] Populate optional parameter Token-Text. 
    // Set Token-Text AVP.
    // The data type of Token-Text is UTF8String.
    // This contains extension information for the Message-Class AVP.
    // The AVP Code for Token-Text is 1215.
    TokenText tokenText("notclear"); // --not clear
    msgClass.setTokenText(tokenText);

    mmsInfo.setMessageClass(msgClass);

    // [1.1.10] Populate optional parameter Delivery-Report-Requested. 
    // Set Delivery-Report-Requested AVP.
    // The data type of Delivery-Report-Requested is enumerated.
    // This indicates whether a delivery report has been requested by 
    // the originator MMS User Agent or not.
    // The AVP Code for Delivery-Report-Requested is 1216.
    DeliveryReportRequested deliveryRqstd(DeliveryReportRequested::No);
    mmsInfo.setDeliveryReportRequested(deliveryRqstd);

    // [1.1.11] Populate optional parameter Read-Reply-Report-Requested. 
    // Set Read-Reply-Report-Requested AVP.
    // The data type of Read-Reply-Report-Requested is enumerated.
    // This indicates whether a read reply report has been requested by 
    // the originator MMS User Agent or not.
    // The AVP Code for Read-Reply-Report-Requested is 1222.
    ReadReplyReportRequested readReplyRqstd(ReadReplyReportRequested::No);
    mmsInfo.setReadReplyReportRequested(readReplyRqstd);

    // [1.1.12] Populate optional parameter Applic-ID. 
    // Set Applic-ID AVP.
    // The data type of Applic-ID is UTF8String.
    // This holds the identification of the destination application that
    // the underlying MMS abstract message was addressed to.
    // 16777226 - 3GPP MM10 application
    // The AVP Code for Applic-ID is 1218.
    ApplicID ApplicId("16777226"); // --not clear
    mmsInfo.setApplicID(ApplicId);

    // [1.1.13] Populate optional parameter Reply-Applic-ID. 
    // Set Reply-Applic-ID AVP.
    // The data type of Reply-Applic-ID is UTF8String.
    // This holds the identifier of a "reply path", i.e the identifier
    // of the application to which delivery reports, read-reply reports 
    // and reply-MMs are addressed.
    // The AVP Code for Reply-Applic-ID is 1223.
    ReplyApplicID replyApplicId("16777226"); // --not clear
    mmsInfo.setReplyApplicID(replyApplicId);

    // [1.1.14] Populate optional parameter Aux-Applic-Info. 
    // Set Aux-Applic-Info AVP.
    // The data type of Aux-Applic-Info is UTF8String.
    // This holds additional application/implementation specific
    // control information.
    // The AVP Code for Aux-Applic-Info is 1219.
    AuxApplicInfo auxApplicInfo("notclear"); // --not clear
    mmsInfo.setAuxApplicInfo(auxApplicInfo);

    // [1.1.15] Populate optional parameter Content-Class. 
    // Set Content-Class AVP.
    // The data type of Content-Class is Enumerated.
    // This classifies the content of the MM to the highest content
    // class to which the MM belongs, as defined in MMS Encapsulation.
    // The AVP Code for Content-Class is 1220.
    ContentClass contentClass(ContentClass::text);
    mmsInfo.setContentClass(contentClass);

    // [1.1.16] Populate optional parameter DRM-Content. 
    // Set DRM-Content AVP.
    // The data type of DRM-Content is Enumerated.
    // This indicates if the MM contains DRM-protected content.
    // The AVP Code for DRM-Content is 1221.
    DRMContent drmContent(DRMContent::No);
    mmsInfo.setDRMContent(drmContent);

    // [1.1.17] Populate optional parameter Adaptations. 
    // Set Adaptations AVP.
    // The data type of Adaptations is Enumerated.
    // This indicates whether the originator allows adaptation of the
    // content (default Yes)
    // The AVP Code for Adaptations is 1217.
    Adaptations adapts(Adaptations::No);
    mmsInfo.setAdaptations(adapts);

    // [1.1.18] Populate optional parameter VASP-Id. 
    // Set VASP-Id AVP.
    // The data type of VASP-Id is UTF8String.
    // This contains the identification of a Value Added Service Provider.
    // The AVP Code for VASP-Id is 1101.
    VASPId vaspId("airtel");
    mmsInfo.setVASPId(vaspId);

    // [1.1.19] Populate optional parameter VAS-Id. 
    // Set VAS-Id AVP.
    // The data type of VAS-Id is UTF8String.
    // This contains the identification of a Value Added Service.
    // The AVP Code for VAS-Id is 1102.
    VASId vasId("mms"); //- not clear
    mmsInfo.setVASId(vasId);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the MM-Content-Type
 *      grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      MMContentType object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      MMContentType &mmContentType: Refernce to the MMContentType
 *      object, the grouped AVP of which needs to be set.
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
void PopulateMMContentType(MMContentType &mmContentType) 
{
    // [1] Populate "MM-Content-Type" grouped AVPs. 

    // [1.1] Populate optional AVPs. 

    // [1.1.1] Populate optional parameter Type-Number. 
    // Set Type-Number AVP.
    // The data type of Type-Number is Integer32.
    // This identifies the well-known media types. The values taken from 
    // OMNA WSP Content type codes database
    // The AVP Code for Type-Number is 1204.
    TypeNumber typeNumber(3); // text/plain
    mmContentType.setTypeNumber(typeNumber);

    // [1.1.2] Populate optional parameter Additional-Type-Information. 
    // Set Additional-Type-Information AVP.
    // The data type of Additional-Type-Information is UTF8String.
    // This identifies any additional information beyond well-known media 
    // type or non-well-known media types.
    // The AVP Code for Additional-Type-Information is 1205.
    AdditionalTypeInformation addTypeInfo("codec24"); // not clear
    mmContentType.setAdditionalTypeInformation(addTypeInfo);

    // [1.1.3] Populate optional parameter Content-Size. 
    // Set Content-Size AVP.
    // The data type of Content-Size is Unsigned32.
    // This indicates the size in bytes of the specified content type. 
    // The AVP Code for Content-Size is 1206.
    ContentSize contentSize(70);
    mmContentType.setContentSize(contentSize);

    // [1.1.4] Populate optional(multiple occurence) parameter 
    //         Additional-Content-Information
    // Set Additional-Content-Information AVP.
    // The data type of Additional-Content-Information is Grouped.
    // This identifies any subsequent content types. 
    // The AVP Code for Additional-Content-Information is 1207.
    AdditionalContentInformation addContentInfo;

    // [1.1.4.1] Populate Additional-Content-Information grouped AVPs.

    // [1.1.4.1.1] Populate optional parameter Type-Number. 
    // Set Type-Number AVP.
    // The data type of Type-Number is Integer32.
    // This identifies the well-known media types. The values taken from 
    // OMNA WSP Content type codes database
    // The AVP Code for Type-Number is 1204.
    TypeNumber typeNumber1(2); // text/html
    addContentInfo.setTypeNumber(typeNumber1);

    // [1.1.4.1.2] Populate optional parameter Additional-Type-Information. 
    // Set Additional-Type-Information AVP.
    // The data type of Additional-Type-Information is UTF8String.
    // This identifies any additional information beyond well-known media 
    // type or non-well-known media types.
    // The AVP Code for Additional-Type-Information is 1205.
    AdditionalTypeInformation addTypeInfo1("codec25"); // not clear
    addContentInfo.setAdditionalTypeInformation(addTypeInfo1);

    // [1.1.4.1.3] Populate optional parameter Content-Size. 
    // Set Content-Size AVP.
    // The data type of Content-Size is Unsigned32.
    // This indicates the size in bytes of the specified content type. 
    // The AVP Code for Content-Size is 1206.
    ContentSize contentSize1(50);
    addContentInfo.setContentSize(contentSize1);

    // [1.1.4.2] Set Additional-Content-Information in MM-Content-Type object.
    mmContentType.addAdditionalContentInformation(addContentInfo);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Originator-Address 
 *      grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      OriginatorAddress object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      OriginatorAddress &origAddr: Refernce to the OriginatorAddress
 *      object, the grouped AVP of which needs to be set.
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
void PopulateOriginatorAddress(OriginatorAddress &origAddr) 
{
    // [1] Populate "Originator-Address" grouped AVPs. 

    // [1.1] Populate optional AVPs. 

    // [1.1.1] Populate optional parameter Address-Type. 
    // Set Address-Type AVP.
    // The data type of Address-Type is Enumerated.
    // This indicates the type of address carried within the 
    // Address-Information AVP.
    // The AVP Code for Address-Type is 899.
    IMSAddressType addrType(IMSAddressType::e_mail_address);
    origAddr.setIMSAddressType(addrType);

    // [1.1.2] Populate optional parameter Address-Data. 
    // Set Address-Data AVP.
    // The data type of Address-Data is UTF8String.
    // This indicates the address information and formatted according type of 
    // address indicated in Address-Type and according to MMS encapsulation.
    // The AVP Code for Address-Data is 897.
    AddressData addrData("dummy@example.com");
    origAddr.setAddressData(addrData);

    // [1.1.3] Populate optional parameter Address-Domain. 
    // Set Address-Domain AVP.
    // The data type of Address-Domain is Grouped.
    // This indicates the domain/network to which the associated address 
    // resides. If this AVP is present, at least one of the AVPs in the 
    // grouping must be included.
    // The AVP Code for Address-Domain is 898.
    AddressDomain addrDomain;

    // [1.1.3.1] Populate Address-Domain grouped AVPs. 

    // [1.1.3.1.1] Populate optional parameter Domain-Name. 
    // Set Domain-Name AVP.
    // The data type of Domain-Name is UFT8String.
    // This represents a fully qualified domain name. 
    // The AVP Code for Domain-Name is 1200.
    DomainName domainName("example"); 
    addrDomain.setDomainName(domainName);

    // [1.1.3.1.2] Populate optional parameter 3GPP-IMSI-MCC-MNC. 
    // Set 3GPP-IMSI-MCC-MNC AVP.
    // The data type of 3GPP-IMSI-MCC-MNC is UFT8String.
    // This contains MCC and MNC extracted from the user's IMSI 
    // (first 5 or 6 digits, as applicable from the presented IMSI) 
    // The AVP Code for 3GPP-IMSI-MCC-MNC is 8.
    RfRo3GPPIMSIMCCMNC imsiMccMnc("091080"); 
    addrDomain.setRfRo3GPPIMSIMCCMNC(imsiMccMnc);

    // [1.1.3.2] Set Address-Domain in Originator-Address object. 
    origAddr.setAddressDomain(addrDomain);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Recipient-Address
 *      grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      RecipientAddress object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      RecipientAddress &recipientAddr: Refernce to the RecipientAddress
 *      object, the grouped AVP of which needs to be set.
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
void PopulateRecipientAddress(RecipientAddress &recipientAddr) 
{
    // [1] Populate "Recipient-Address" grouped AVPs. 

    // [1.1] Populate optional AVPs. 

    // [1.1.1] Populate optional parameter Address-Type. 
    // Set Address-Type AVP.
    // The data type of Address-Type is Enumerated.
    // This indicates the type of address carried within the 
    // Address-Information AVP.
    // The AVP Code for Address-Type is 899.
    IMSAddressType addrType(IMSAddressType::e_mail_address);
    recipientAddr.setIMSAddressType(addrType);

    // [1.1.2] Populate optional parameter Address-Data. 
    // Set Address-Data AVP.
    // The data type of Address-Data is UTF8String.
    // This indicates the address information and formatted according type of 
    // address indicated in Address-Type and according to MMS encapsulation.
    // The AVP Code for Address-Data is 897.
    AddressData addrData("dummy@example.com");
    recipientAddr.setAddressData(addrData);

    // [1.1.3] Populate optional parameter Address-Domain. 
    // Set Address-Domain AVP.
    // The data type of Address-Domain is Grouped.
    // This indicates the domain/network to which the associated address 
    // resides. If this AVP is present, at least one of the AVPs in the 
    // grouping must be included.
    // The AVP Code for Address-Domain is 898.
    AddressDomain addrDomain;

    // [1.1.3.1] Populate Address-Domain grouped AVPs. 

    // [1.1.3.1.1] Populate optional parameter Domain-Name. 
    // Set Domain-Name AVP.
    // The data type of Domain-Name is UFT8String.
    // This represents a fully qualified domain name. 
    // The AVP Code for Domain-Name is 1200.
    DomainName domainName("example"); 
    addrDomain.setDomainName(domainName);

    // [1.1.3.1.2] Populate optional parameter 3GPP-IMSI-MC-MNC. 
    // Set 3GPP-IMSI-MC-MNC AVP.
    // The data type of 3GPP-IMSI-MC-MNC is UFT8String.
    // This contains MCC and MNC extracted from the user's IMSI 
    // (first 5 or 6 digits, as applicable from the presented IMSI) 
    // The AVP Code for 3GPP-IMSI-MC-MNC is 8.
    RfRo3GPPIMSIMCCMNC imsiMccMnc("091080"); 
    addrDomain.setRfRo3GPPIMSIMCCMNC(imsiMccMnc);

    // [1.1.3.2] Set Address-Domain in Recipient-Address object. 
    recipientAddr.setAddressDomain(addrDomain);

    // [1.1.4] Populate optional parameter Addressee-Type. 
    // Set Addressee-Type AVP.
    // The data type of Addressee-Type is Enumerated.
    // This identifies how the recipient is addressed in the header of an MM.
    // The AVP Code for Addressee-Type is 1208.
    AddresseeType addresseeType(AddresseeType::TO);
    recipientAddr.setAddresseeType(addresseeType);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the LCS-Information
 *      grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      LCSInformation object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      LCSInformation &lcsInfo: Refernce to the LCSInformation
 *      object, the grouped AVP of which needs to be set.
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
void PopulateLCSInformation(LCSInformation &lcsInfo) 
{
    // [1] Populate "LCS-Information" grouped AVPs. 

    // [1.1] Populate optional AVPs. 

    // [1.1.1] Populate optional parameter LCS-Client-ID. 
    // Set LCS-Client-ID AVP.
    // The data type of LCS-Client-ID is Grouped.
    // This specifies the role of the PoC server.
    // The AVP Code for LCS-Client-ID is 1232.
    LCSClientID lcsClientId;
    PopulateLCSClientID(lcsClientId);
    lcsInfo.setLCSClientID(lcsClientId);

    // [1.1.2] Populate optional parameter Location-Type. 
    // Set Location-Type AVP.
    // The data type of Location-Type is Grouped.
    // This indicates the type of location estimate required by the LCS Client.
    // The AVP Code for Location-Type is 1244.
    LocationType locationType;
   
    // [1.1.2.1] Populate Location-Type grouped AVPs. 

    // [1.1.2.1.1] Populate optional parameter Location-Estimate-Type. 
    // Set Location-Estimate-Type AVP.
    // The data type of Location-Estimate-Type is Enumerated.
    // The AVP Code for Location-Estimate-Type is 1243.
    LocationEstimateType locEstmType(LocationEstimateType::CURRENT_LOCATION);
    locationType.setLocationEstimateType(locEstmType);
    
    // [1.1.2.1.2] Populate optional parameter Deferred-Location-Event-Type. 
    // Set Deferred-Location-Event-Type AVP.
    // The data type of Deferred-Location-Event-Type is UTF8String.
    // This holds information related to a deferred location request.
    // Refer N4-021260
    // The AVP Code for Deferred-Location-Event-Type is 1230.
    DeferredLocationEventType defLocEvtType("UE Available"); // not clear
    locationType.setDeferredLocationEventType(defLocEvtType);

    // [1.1.2.2] Set Location-Type in LCS-Information object. 
    lcsInfo.setLocationType(locationType);

    // [1.1.3] Populate optional parameter Location-Estimate. 
    // Set Location-Estimate AVP.
    // The data type of Location-Estimate is UTF8String.
    // This contains an estimate of the location of an MS in the universal 
    // coordinates and the accuracy of the estimate.
    // The AVP Code for Location-Estimate is 1242.
    LocationEstimate locationEstimate("20x50y"); // not clear
    lcsInfo.setLocationEstimate(locationEstimate);

    // [1.1.4] Populate optional parameter Positioning-Data. 
    // Set Positioning-Data AVP.
    // The data type of Positioning-Data is UTF8String.
    // This indicates the usage of each positioning method that was attempted 
    // to determine location estimate either successfully or unsuccessfully.
    // The AVP Code for Positioning-Data is 1245.
    PositioningData positionData("correct"); // not clear
    lcsInfo.setPositioningData(positionData);


    // [1.1.5] Populate optional parameter MSISDN. 
    // Set MSISDN AVP.
    // The data type of MSISDN is OctetString.
    // This This AVP contains an MSISDN, in international number format as 
    // described in ITU-T Rec E.164, encoded as a TBCD-string.
    // The AVP Code for MSISDN is 701.
    MSISDN msIsdn("234567");
    lcsInfo.setMSISDN(msIsdn);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the LCS-Client-ID
 *      grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      LCSClientID object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      LCSClientID &lcsClientId: Refernce to the LCSClientID
 *      object, the grouped AVP of which needs to be set.
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
void PopulateLCSClientID(LCSClientID &lcsClientId) 
{
    // [1] Populate "LCS-Client-ID" grouped AVPs. 

    // [1.1] Populate optional AVPs. 

    // [1.1.1] Populate optional parameter LCS-Client-Type. 
    // Set LCS-Client-Type AVP.
    // The data type of LCS-Client-Type is Enumerated.
    // The AVP Code for LCS-Client-Type is 1241.
    LCSClientType lcsClientType(LCSClientType::VALUE_ADDED_SERVICES);
    lcsClientId.setLCSClientType(lcsClientType); 

    // [1.1.2] Populate optional parameter LCS-Client-External-ID. 
    // Set LCS-Client-External-ID AVP.
    // The data type of LCS-Client-External-ID is UTF8String.
    // This holds identification of the external LCS Client.
    // The AVP Code for LCS-Client-External-ID is 1234.
    LCSClientExternalID lcsClientExternalId("66"); // not clear
    lcsClientId.setLCSClientExternalID(lcsClientExternalId);

    // [1.1.3] Populate optional parameter LCS-Client-Dialed-By-MS. 
    // Set LCS-Client-Dialed-By-MS AVP.
    // The data type of LCS-Client-Dialed-By-MS is UTF8String.
    // This holds the number of the LCS Client dialled by MS.
    // The AVP Code for LCS-Client-Dialed-By-MS is 1233.
    LCSClientDialedByMS lcsDialedbyMS("9845098450");
    lcsClientId.setLCSClientDialedByMS(lcsDialedbyMS);

    // [1.1.4] Populate optional parameter LCS-Client-Name. 
    // Set LCS-Client-Name AVP.
    // The data type of LCS-Client-Name is Grouped.
    // This holds the information realted to the name of the LCS Client.
    // The AVP Code for LCS-Client-Name is 1235.
    LCSClientName lcsClientName;

    // [1.1.4.1] Populate LCS-Client-Name grouped AVPs. 
  
    // [1.1.4.1.1] Populate optional parameter LCS-Data-Coding-Scheme. 
    // Set LCS-Data-Coding-Scheme AVP.
    // The data type of LCS-Data-Coding-Scheme is UTF8String.
    // This contains information of the alphabet and language used.
    // The AVP Code for LCS-Data-Coding-Scheme is 1236.
    LCSDataCodingScheme lcsDataCodeSchm("bcd");  // not clear
    lcsClientName.setLCSDataCodingScheme(lcsDataCodeSchm);

    // [1.1.4.1.2] Populate optional parameter LCS-Name-String. 
    // Set LCS-Name-String AVP.
    // The data type of LCS-Name-String is UTF8String.
    // This contains LCS Client Name.
    // The AVP Code for LCS-Name-String is 1238.
    LCSNameString lcsNameString("sip:Alice@atlanta.com"); 
    lcsClientName.setLCSNameString(lcsNameString);

    // [1.1.4.1.2] Populate optional parameter LCS-Format-Indicator. 
    // Set LCS-Format-Indicator AVP.
    // The data type of LCS-Format-Indicator is Enumerated.
    // This contains the format of the LCS Client Name.
    // The AVP Code for LCS-Format-Indicator is 1237.
    LCSFormatIndicator lcsFormatIndicator(LCSFormatIndicator::EMAIL_ADDRESS);
    lcsClientName.setLCSFormatIndicator(lcsFormatIndicator);
   
    // [1.1.4.2] Set LCS-Client-Name AVP in LCS-Client-Id object
    lcsClientId.setLCSClientName(lcsClientName);

    // [1.1.5] Populate optional parameter LCS-APN. 
    // Set LCS-APN AVP.
    // The data type of LCS-APN is UTF8String.
    // This contains the APN of the LCS Client.
    // The AVP Code for LCS-APN is 1231.
    LCSAPN lcsAPN("482364234"); // not clear
    lcsClientId.setLCSAPN(lcsAPN);

    // [1.1.6] Populate optional parameter LCS-Requestor-ID. 
    // Set LCS-Requestor-ID AVP.
    // The data type of LCS-Requestor-ID is Grouped.
    // This contains information related to the identification of requestor.
    // The AVP Code for LCS-Requestor-ID is 1239.
    LCSRequestorID lcsReqId;

    // [1.1.6.1] Populate LCS-Requestor-ID grouped AVPs. 
   
    // [1.1.6.1.1] Populate optional parameter LCS-Data-Coding-Scheme. 
    // Set LCS-Data-Coding-Scheme AVP.
    // The data type of LCS-Data-Coding-Scheme is UTF8String.
    // This contains information of the alphabet and language used.
    // The AVP Code for LCS-Data-Coding-Scheme is 1236.
    LCSDataCodingScheme lcsDataCodeSchm1("bcd");  // not clear
    lcsReqId.setLCSDataCodingScheme(lcsDataCodeSchm1);

    // [1.1.6.1.2] Populate optional parameter LCS-Requestor-ID-String. 
    // Set LCS-Requestor-ID-String AVP.
    // The data type of LCS-Requestor-ID-String is UTF8String.
    // This contains the identification of the Requestor Eg MSISDN or 
    // logical name.
    // The AVP Code for LCS-Requestor-ID-String is 1240.
    LCSRequestorIDString lcsReqIdStr("Bob");
    lcsReqId.setLCSRequestorIDString(lcsReqIdStr);

    // [1.1.6.2] Set LCS-Requestor-ID AVP in LCS-Client-Id object. 
    lcsClientId.setLCSRequestorID(lcsReqId);

}


/*  implementation: public
 ****************************************************************************
 *  purpose: This function populates the PoC-Information
 *      grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      PoCInformation object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      PoCInformation &pocInfo: Refernce to the PoCInformation
 *      object, the grouped AVP of which needs to be set.
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
void PopulatePoCInformation(PoCInformation &pocInfo) 
{
    // [1] Populate "PoC-Information" grouped AVPs. 

    // [1.1] Populate optional AVPs. 

    // [1.1.1] Populate optional parameter PoC-Server-Role. 
    // Set PoC-Server-Role AVP.
    // The data type of PoC-Server-Role is Enumerated.
    // This specifies the role of the PoC server.
    // The AVP Code for PoC-Server-Role is 883.
    PoCServerRole pocServerRole(PoCServerRole::Participating_PoC_Server);
    pocInfo.setPoCServerRole(pocServerRole);

    // [1.1.2] Populate optional parameter PoC-Session-Type. 
    // Set PoC-Session-Type AVP.
    // The data type of PoC-Session-Type is Enumerated.
    // This specifies the type of PoC session.
    // The AVP Code for PoC-Session-Type is 884.
    PoCSessionType pocSessionType(PoCSessionType::One_to_one_PoC_session);
    pocInfo.setPoCSessionType(pocSessionType);

    // [1.1.3] Populate optional parameter Number-Of-Participants. 
    // Set Number-Of-Participants AVP.
    // The data type of Number-Of-Participants is Integer32.
    // This holds the number of invited parties of the PoC session.
    // The AVP Code for Number-Of-Participants is 885.
    NumberOfParticipants numParticipants(2);
    pocInfo.setNumberOfParticipants(numParticipants);

    // [1.1.4] Populate optional parameter(multiple occurence) 
    //            Participants-Involved. 
    // Set Participants-Involved AVP.
    // The data type of Participants-Involved is UTF8String.
    // This holds the list of address (Public User ID,SIP URI,TEL URI,MSISDN)
    // of the parties who are involved into PoC session.
    // The AVP Code for Participants-Involved is 887.
    ParticipantsInvolved participant1("sip:alice@atlanta.com");
    pocInfo.addParticipantsInvolved(participant1);

    ParticipantsInvolved participant2("sip:bob@biloxi.com");
    pocInfo.addParticipantsInvolved(participant2);

    // [1.1.5] Populate optional(multiple occurence) parameter 
    //          Talk-Burst-Exchange. 
    // Set Talk-Burst-Exchange AVP.
    // The data type of Talk-Burst-Exchange is Grouped.
    // The AVP Code for Talk-Burst-Exchange is 860.
//    --not clear

    // [1.1.6] Populate optional parameter PoC-Controlling-Address. 
    // Set PoC-Controlling-Address AVP.
    // The data type of PoC-Controlling-Address is UTF8String.
    // This identifies the PoC server performing the controlling
    // function for the associated PoC session.
    // The AVP Code for PoC-Controlling-Address is 858.
    PoCControllingAddress pocControlAddr("kphone.com"); // -- not clear
    pocInfo.setPoCControllingAddress(pocControlAddr);

    // [1.1.7] Populate optional parameter PoC-Group-Name. 
    // Set PoC-Group-Name AVP.
    // The data type of PoC-Group-Name is UTF8String.
    // This identifies a pre-arranged group.Included if the session is a 
    // pre-arranged group session.
    // The AVP Code for PoC-Group-Name is 859.
//    PoCGroupName pocGroupName("Friends");
//    pocInfo.setPoCGroupName(pocGroupName);

    // [1.1.8] Populate optional parameter PoC-Session-Id. 
    // Set PoC-Session-Id AVP.
    // The data type of PoC-Session-Id is UTF8String.
    // It uniquely identifies an end-to-end PoC session and may be used for 
    // correlation between charging information generated by participating 
    // and controlling PoC functions. This information is obtained from the
    // "contact" header of the SIP message received from the controlling 
    // PoC function.
    // The AVP Code for PoC-Session-Id is 1229.
    PoCSessionId pocSessionId("Lee<sip:lee@example.com>"); // --not clear
    pocInfo.setPoCSessionId(pocSessionId);

}

/*  implementation: public
 ****************************************************************************
 *  purpose: This function populates the MBMS-Information
 *      grouped AVP.  
 *      This populate the grouped AVPs and sets the values in the 
 *      MBMSInformation object passed as a reference to this 
 *      function.
 *
 *  Input Parameters:
 *      MBMSInformation &mbmsInfo: Refernce to the MBMSInformation
 *      object, the grouped AVP of which needs to be set.
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
void PopulateMBMSInformation(MBMSInformation &mbmsInfo) 
{
    // [1] Populate "MBMS-Information" grouped AVPs. 

    // [1.1] Populate mandatory AVPs. 

    // [1.1.1] Populate mandatory parameter TMGI. 
    // Set TMGI AVP.
    // The data type of TMGI is OctetString.
    // This contains the Temorary Mobile Group Identity allocated to a
    // particular MBMS bearer service.
    // <MBMS Service Id(3octets)><MCC(3octets)><MNC(2or3octets)>
    // The AVP Code for TMGI is 900.
    TMGI tmgi("101091044"); // not clear
    mbmsInfo.setTMGI(tmgi);

    // [1.1.2] Populate mandatory parameter MBMS-Service-Type. 
    // Set MBMS-Service-Type AVP.
    // The data type of MBMS-Service-Type is Enumerated.
    // This contains explicit information about type of service
    // BM-SC Start Procedure is about to start.
    // that is being delievered.
    // The AVP Code for MBMS-Service-Type is 906.
    MBMSServiceType mbmsServiceType(MBMSServiceType::BROADCAST);
    mbmsInfo.setMBMSServiceType(mbmsServiceType);

    // [1.1.3] Populate mandatory parameter MBMS-User-Service-Type. 
    // Set MBMS-User-Service-Type AVP.
    // The data type of MBMS-User-Service-Type is Enumerated.
    // This indicates the type of service the MBMS user service
    // that is being delievered.
    // The AVP Code for MBMS-User-Service-Type is 1225.
    MBMSUserServiceType mbmsUserServiceType(
                        MBMSUserServiceType::DOWNLOAD);
    mbmsInfo.setMBMSUserServiceType(mbmsUserServiceType);

    // [1.2] Populate optional AVPs. 

    // [1.2.1] Populate optional parameter File-Repair-Supported. 
    // Set File-Repair-Supported AVP.
    // The data type of File-Repair-Supported is Enumerated.
    // This indicates the whether the MBMS user service supports
    // point-to-point file repair.
    // The AVP Code for File-Repair-Supported is 1224.
    FileRepairSupported fileRepairSuprt(FileRepairSupported::SUPPORTED);
    mbmsInfo.setFileRepairSupported(fileRepairSuprt);

    // [1.2.2] Populate optional parameter Required-MBMS-Bearer-Capabilities. 
    // Set Required-MBMS-Bearer-Capabilities AVP.
    // The data type of Required-MBMS-Bearer-Capabilities is UTF8String.
    // This contains the minimum bearer capabilities the UE need to support.
    // The information contained in this AVP is UTF8 encoded QoS Profile
    // as described in 3GPP TS 24.008.
    // It indicate the maximum bit rate for downlink supported by the MS for 
    // an MBMS context.
    // The AVP Code for Required-MBMS-Bearer-Capabilities is 901.
    RequiredMBMSBearerCapabilities 
                 reqMBMSBearerCapb("4040");
//                 reqMBMSBearerCapb("3,1 kHz audio ex PLMN"); // -- not clear
    mbmsInfo.setRequiredMBMSBearerCapabilities(reqMBMSBearerCapb);

    // [1.2.3] Populate optional parameter MBMS-2G-3G-Indicator. 
    // Set MBMS-2G-3G-Indicator AVP.
    // The data type of MBMS-2G-3G-Indicator is Enumerated.
    // This indicates the whether the MBMS bearer service will be delievered
    // in 2G only,3G only or both coverage areas.
    // The AVP Code for MBMS-2G-3G-Indicator is 907.
    MBMS2G3GIndicator mbms2g3gInd(MBMS2G3GIndicator::BOTH_2G_AND_3G);
    mbmsInfo.setMBMS2G3GIndicator(mbms2g3gInd);

    // [1.2.4] Populate optional parameter RAI. 
    // Set RAI AVP.
    // The data type of RAI is UTF8String.
    // This contains the Routing area Identity of the SGSN where the UE
    // is registered.
    //  |LAI=MCC,MNC,LAC(2octets)| |RAC=1 octet|
    // The AVP Code for RAI is 909.
    RAI rai("09180042"); //  -- not clear
    mbmsInfo.setRAI(rai);

    // [1.2.5] Populate optional(multiple occurence) parameter 
    //         MBMS-Service-Area. 
    // Set MBMS-Service-Area AVP.
    // The data type of MBMS-Service-Area is OctetString.
    // This indicates area over which MBMS bearer service has to 
    // be distrubuted.
    // The AVP Code for MBMS-Service-Area is 903.
    MBMSServiceArea mbmsServiceArea1("MBMS");  //-- not clear
    mbmsInfo.addMBMSServiceArea(mbmsServiceArea1);

    // [1.2.6] Populate optional parameter MBMS-Session-Identity. 
    // Set MBMS-Session-Identity AVP.
    // The data type of MBMS-Session-Identity is OctetString.
    // Its length is one octet and it is allocated by BM-SC
    // The AVP Code for MBMS-Session-Identity is 908.
    MBMSSessionIdentity mbmsSessionIdentity("15"); // -- not clear
    mbmsInfo.setMBMSSessionIdentity(mbmsSessionIdentity);

}

