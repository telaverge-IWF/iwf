/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *    This product and related documentation is protected by copyright and  *
 *    distributed under licenses restricting its use, copying, distribution *
 *    and decompilation.  No part of this product or related documentation  *
 *    may be reproduced in any form by any means without prior written      *
 *    authorization of IntelliNet Technologies and its licensors, if any.   *
 *                                                                          *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the     *
 *    government is subject to restrictions as set forth in subparagraph    *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software      *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                       *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: CCTest.cpp,v $
 * LOG: Revision 1.1  2011/07/14 11:51:38  vkumara
 * LOG: Baseline for Rw interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: CCTest.cpp,v 1.1 2011/07/14 11:51:38 vkumara Exp $
 ****************************************************************************/
#ident "$Id: CCTest.cpp,v 1.1 2011/07/14 11:51:38 vkumara Exp $"

#include <app.h>

#include <diameter/rw/CC.h>
#include <rw_defines.h>
#include <rw_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::nasreq;
using namespace diameter::rw;

string sessIdString;
ITS_UINT sIdx;

  int
  SendCCRequestInitial()
  {
     return SendRwCCRequest(INITIAL);
  }

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Credit Control Req to the
 *      diameter stack. Creates the CC Request object,
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
int SendRwCCRequest(int requestType,
                               const diameter::CommandImpl* impl)
{
    // [1] Create CCRequest object.
    CCRequest ccr(false,false);
    static int num = 0;
    string sessIdString;
    ITS_UINT sIdx = 0;

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

    if(requestType == INITIAL || requestType == EVENT )
    {
        num =0;
        AllocateSession(RW_INTERFACE_APP_ID,sIdx,sessIdString);
        ccr.setSessionId(SessionId(sessIdString));

        ccr.setSessionIndex(sIdx);
    }
    else if (impl != NULL)
    {
        //formatting next ccr message based on recieved CCA
        CCAnswer cca(*impl);

        ccr.setSessionId(cca.getSessionId());
        ccr.setSessionIndex(cca.getSessionIndex());
    }
    else
    {
        //for unit test provide the values of Session Id and Index
        cout << endl << "Please Enter the SessionId:" <<endl;
        cin >> sessIdString ;
        ccr.setSessionId(SessionId(sessIdString));
    }

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
    AuthApplicationId authApplicationId(RW_INTERFACE_APP_ID);
    ccr.setAuthApplicationId(authApplicationId);

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
            CCRequestType ccRequestType(CCRequestType::INITIAL_REQUEST);
            ccr.setCCRequestType(ccRequestType);
        }
        break;
        case UPDATE:
        {
            CCRequestType ccRequestType(CCRequestType::UPDATE_REQUEST);
            ccr.setCCRequestType(ccRequestType);
        }
        break;
        case TERMINATION:
        {
            CCRequestType ccRequestType(CCRequestType::TERMINATION_REQUEST);
            ccr.setCCRequestType(ccRequestType);
        }
        break;
        case EVENT:
        {
            CCRequestType ccRequestType(CCRequestType::EVENT_REQUEST);
            ccr.setCCRequestType(ccRequestType);
        }
        break;
        default:
            cout << endl << "Invalid Request Type" << endl;
        break;

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
    CCRequestNumber ccRequestNumber(222);
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

    // Set Optional AVPs.
    if (appMode == UNIT_TEST)
    {
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


    }
        cout <<endl<<"CCR : "<< ccr << endl;

    // Send encoded Message to stack.
    SendDiaAppMsg(ccr, sIdx);
    RwStats::GetRwStats()->UpdateSendStats(ccr.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Answer to Credit Control request 
 *      sent by the application. This creates the CCAnswer
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
int SendRwCCAnswer(const diameter::CommandImpl* impl ) 
{
    // [1] Create CCAnswer object.
    CCAnswer cca(false,false);

    // [1.1] Create an instance of CCRequest class with
    //        recived event
    CCRequest ccr(*impl);

    // [2] Insert data in the created CCAnswer object.
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

    ITS_UINT sIdx = ccr.getSessionIndex();
    cca.setSessionIndex(sIdx);

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
    // This AVP identifies the endpoint that originated the Diameter 
    // message.
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost originHost(GetOriginHost());
    cca.setOriginHost(originHost);

    // [2.1.2.3] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
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
    AuthApplicationId authApplicationId(RW_INTERFACE_APP_ID);
    cca.setAuthApplicationId(authApplicationId);

    // [2.1.2.5] Populate required parameter "CC-Request-Type".
    // Set the CC-Request-Type AVP.
    // The data type of CC-Request-Type is Enumerated.
    // This AVP contains the reason for sending the credit-control request
    // message.
    // The AVP Code of CC-Request-Type is 416.
    CCRequestType ccRequestType(CCRequestType::TERMINATION_REQUEST);
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
    CCRequestNumber ccRequestNumber(111);
    cca.setCCRequestNumber(ccRequestNumber);

    // For loadtest dont set optional AVPs.
    if (appMode == UNIT_TEST)
    cout <<endl<<"CCA : "<< cca << endl;

    SendDiaAppMsg(cca, sIdx);
    RwStats::GetRwStats()->UpdateSendStats(cca.getCommandCode(),
                                                            ITS_FALSE);

    return ITS_SUCCESS;

}
