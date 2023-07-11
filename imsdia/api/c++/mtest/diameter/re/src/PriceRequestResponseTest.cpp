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
 * LOG: $Log: PriceRequestResponseTest.cpp,v $
 * LOG: Revision 1.1  2011/05/20 04:15:48  vkumara
 * LOG: Basline for Re interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: PriceRequestResponseTest.cpp,v 1.1 2011/05/20 04:15:48 vkumara Exp $
 ****************************************************************************/
#ident "$Id: PriceRequestResponseTest.cpp,v 1.1 2011/05/20 04:15:48 vkumara Exp $"

#include <app.h>
#include <re_defines.h>
#include <re_stats.h>
#include <diameter/re/PriceRequest.h>
#include <diameter/re/PriceResponse.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::re;

string sessIdString;
ITS_UINT sIdx;

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Price Request to the
 *      diameter stack. Creates the Price Request object,
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
int SendRePriceRequest() 
{
    // [1]. Create an instance of PriceRequest class
    // The Price-Request command is sent by a Diameter
    // client to a Diameter Server in order to priceRequest deregistration
    //  Editors Note: The 3GPP Rating Application uses the value xxx (3GPP) as Vendor-Id.
    //  Need to change Command Codes. Time being we are using 10415 as Command-Code.
    // Command-Code = 10415 and 'R' bit set

    diameter::re::PriceRequest  priceReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.

    AllocateSession(RE_INTERFACE_APP_ID, sIdx, sessIdString);
    priceReq.setSessionId(SessionId(sessIdString));

    priceReq.setSessionIndex(sIdx);

    // [2.1.2.2] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost origh(GetOriginHost());
    priceReq.setOriginHost(origh);

    // [2.1.2.3] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origr(GetOriginRealm());
    priceReq.setOriginRealm(origr);

    // [2.1.2.4] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm desr(GetDestinationRealm());
    priceReq.setDestinationRealm(desr);


   /**
    * The ActualTime AVP is of type Time. It contains the actual timestamp of the current
    * rating request message (i.e. PRQ or TRQ).
    * Here we are using 5042  AVP Code instead of TBD(To Be Decided)
    */
    ActualTime atime(70);
    priceReq.setActualTime(atime);


    // [2.2.5] Populate optional(multiple occurence) parameter
    //          "Subscription-Id"
    // Set the Subscription-Id AVP.
    // The data type Subscription-Id is Grouped.
    // This is used to identify the end user's subscription.
    // The AVP Code of Subscription-Id is 443.

    //SubscriptionId subscriptionId1;
    SubscriptionId subscriptionId1;

    // [2.2.5.1] Populate "Subscription-Id" grouped AVPs.
    // [2.2.5.1.1] Populate optional parameter "Subscription-Id-Type"
    // Set the Subscription-Id-Type AVP.
    // The data type Subscription-Id-Type is Enumerated.
    // This is used to determine which type of identifier is carried by the
    // subscription-Id avp. 
    // The AVP Code of Subscription-Id-Type is 450.

    //SubscriptionIdType subscriptionIdType
   SubscriptionIdType subscriptionIdType
                           (SubscriptionIdType::END_USER_SIP_URI);
    subscriptionId1.setSubscriptionIdType(subscriptionIdType);
    
    // [2.2.5.1.2] Populate optional parameter "Subscription-Id-Data"
    // Set the Subscription-Id-Data AVP.
    // The data type Subscription-Id-Data is UTF8String.
    // This is used to identify the end user.
    // The AVP Code of Subscription-Id-Data is 444.

    SubscriptionIdData subscriptionIdData("sip:vkumara@atlanta.com");
    subscriptionId1.setSubscriptionIdData(subscriptionIdData);

    //priceReq.addSubscriptionId(subscriptionId1);
    priceReq.setSubscriptionId(subscriptionId1);

   /**
    * The Service-Rating AVP is of type Grouped. It is used in the all messages once
    * if single service is rated or multiple times if several services are rated in
    * a single transaction.
    */

    ServiceRating sR;

    ServiceIdentifier sI(20);
    sR.setServiceIdentifier(sI);
    MonetaryTariff mT("HELLO IN");
    sR.setMonetaryTariff(mT); 

    priceReq.addServiceRating(sR);

    // [2.2.x] Optional AVPS

    // [2.2.9] Populate optional parameter "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of User-Data is DiameterIdentity.
    // This AVP contains the Host the message is to be routed to.
    // The absence of the Destination-Host AVP will cause a message to be
    // sent to any Diameter server supporting the application within the
    // realm specified in Destination-Realm AVP.
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    priceReq.setDestinationHost(destinationHost);

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
    AuthApplicationId authApplicationId(RE_INTERFACE_APP_ID);
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
    priceReq.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:vkumara@3gppnetwork.com");
    priceReq.setUserName(userName);

    if (appMode == UNIT_TEST)
    cout<<priceReq;

    // Send encoded message to stack.
    SendDiaAppMsg(priceReq, sIdx);
    ReStats::GetReStats()->UpdateSendStats(priceReq.getCommandCode(), ITS_TRUE);

    return ITS_SUCCESS;

}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Price Response to the
 *      diameter stack. Creates the Price Response object,
 *      populate the AVPs and send the message to the stack.
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
int SendRePriceResponse(const CommandImpl *impl) 
{
    //[ 1] Create an instance of PriceResponse class
    // The Price-Response  command is sent by a Diameter
    // server to a Diameter client in order to request deregistration
    // Command-Code = 265 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::re::PriceResponse priceResponse;

    // Create an instance of PriceRequest class 
    PriceRequest prreq(*impl);

    // Get the some AVP values and set them to Answer Message
    const SessionId& sid = prreq.getSessionId();
    const OriginHost& oh = prreq.getOriginHost();
    const OriginRealm& or1 = prreq.getOriginRealm();
    const DestinationRealm& dr = prreq.getDestinationRealm();

    // Fixed AVP

    // [2] Insert data in the created PriceResponse object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed paramete "Session-Id".
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    priceResponse.setSessionId(sid);

    priceResponse.setSessionIndex(prreq.getSessionIndex());

    // Required AVPs

    // [2.1.2.2] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost origh(GetOriginHost());
    priceResponse.setOriginHost(origh);

    // [2.1.2.3] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origrealm(dr.value());
    priceResponse.setOriginRealm(origrealm);

   /**
    * The Service-Rating AVP is of type Grouped. It is used in the all messages once
    * if single service is rated or multiple times if several services are rated in
    * a single transaction.
    */

    ServiceRating sR;

    ServiceIdentifier sI(20);
    sR.setServiceIdentifier(sI);
    MonetaryTariff mT(" Hello VK");
    sR.setMonetaryTariff(mT);

    priceResponse.addServiceRating(sR);

    // [2.2.x] Optional AVPS

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
    AuthApplicationId authApplicationId(RE_INTERFACE_APP_ID);
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
    priceResponse.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:vkumara@3gppnetwork.com");
    priceResponse.setUserName(userName);

 
    if (appMode == UNIT_TEST)
    cout<<priceResponse; 

    // Send Encoded message to stack.
    SendDiaAppMsg(priceResponse, sIdx);
    ReStats::GetReStats()->UpdateSendStats(priceResponse.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;

}
