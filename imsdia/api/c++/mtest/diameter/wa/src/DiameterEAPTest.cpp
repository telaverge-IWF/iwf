/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: DiameterEAPTest.cpp,v 1.1 2011/04/18 09:44:11 vkumara Exp $"

#include <app.h>
#include <wa_defines.h>
#include <wa_stats.h>
#include <diameter/wa/DiameterEAP.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::eap;
using namespace diameter::wa;

extern string sessIdString;
extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the  WaDiameterEAPRequest to the
 *      diameter stack. Create the  WaDiameterEAPRequest object,
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
int SendWaDiameterEAPRequest()
{
    // [1]. Create an instance of MultimediaAuthenticationRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::wa::DiameterEAPRequest waDerReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(WA_INTERFACE_APP_ID, sIdx, sessIdString);
    waDerReq.setSessionId(diameter::base::SessionId(sessIdString));

    waDerReq.setSessionIndex(sIdx);

    // [2.1.2.x] Required AVPs
    // Set the Auth-Application-Id AVP.
    // [2.1.2.1.3] The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(WA_INTERFACE_APP_ID);
    waDerReq.setAuthApplicationId(authApplicationId);


    // [2.1.2.3] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    waDerReq.setOriginHost(originHost);

    // [2.1.2.4] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    waDerReq.setOriginRealm(originRealm);

    // [2.1.2.5] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    waDerReq.setDestinationRealm(destinationRealm);


    // [2.2.1] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    waDerReq.setDestinationHost(destinationHost);


    AuthRequestType  authRequestType(AuthRequestType::AUTHORIZE_AUTHENTICATE);
    waDerReq.setAuthRequestType(authRequestType);

    diameter::eap::EAPPayload eAPPayload("Encapsulate EAP Packet Information");
    waDerReq.setEAPPayload(eAPPayload);

  /**
   * The Location-Information Attribute MAY be sent in the Access-Request
   * message, the Accounting-Request message, both of these messages, or
   * no message.  For the Accounting-Request message, the Acc-Status-Type
   * may be set to Start, Interim, or Stop.
   */
    LocationInformation lI("vkumara@intellinet");
    waDerReq.addLocationInformation(lI);

    if (appMode == UNIT_TEST)
    cout<<waDerReq;

    // Send object to stack.
    SendDiaAppMsg(waDerReq, sIdx);

    WaStats::GetWaStats()->UpdateSendStats(waDerReq.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends the Answer to the WaDiameterEAPRequest 
 *      made by the diameter stack. Create the WaDiameterEAPAnswer
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
int SendWaDiameterEAPAnswer(const CommandImpl * impl)
{
    // 1. Create an instance of MultimediaAuthAnswer class
    // The Multimedia-Auth-Answer command is sent by a server
    // in response to the Multimedia-Auth-Request command with
    // Command-Code = 303 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::wa::DiameterEAPAnswer waDerAns;

    // Create an instance of MultimediaAuthRequest class to get host and
    // session details
    DiameterEAPRequest waDerreq(*impl);

    // Get AVP values from requested message
    const SessionId &sid1 = waDerreq.getSessionId();
    const AuthApplicationId &aaid = waDerreq.getAuthApplicationId();
    const AuthRequestType &authRequestType = waDerreq.getAuthRequestType();

    const OriginHost &oh1 = waDerreq.getOriginHost();
    const OriginRealm &or1 = waDerreq.getOriginRealm();
    if (waDerreq.containsDestinationHost())
        const DestinationHost &dh1 = waDerreq.getDestinationHost();

    const DestinationRealm &dr1 = waDerreq.getDestinationRealm();


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
    waDerAns.setSessionId(sid1);

    waDerAns.setSessionIndex(waDerreq.getSessionIndex());


    waDerAns.setAuthApplicationId(aaid);

    waDerAns.setAuthRequestType(authRequestType);


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
    OriginHost originHost(GetOriginHost());
    waDerAns.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    waDerAns.setOriginRealm(originRealm);

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
    ResultCode resultCode(2001u);
    waDerAns.setResultCode(resultCode);

    // Subscription-Id AVP(AVP Code 443) is of type Grouped and
    // is used to identity the end user's subscription.
    SubscriptionId subscriptionId;

    // Subscription-Id-Type AVP (AVP Code 450) is of type Enumerated
    // and it is used to determine which type of identifier is carried
    // by the Subscription-Id AVP.
    //    END_USER_E164 = 0,
    //    END_USER_IMSI = 1,
    //    END_USER_SIP_URI = 2,
    //    END_USER_NAI = 3,
    //    END_USER_PRIVATE = 4
    SubscriptionIdType subscriptionIdType(SubscriptionIdType::END_USER_E164);
    subscriptionId.setSubscriptionIdType(subscriptionIdType);

    // Subscription-Id-Data AVP (AVP Code 444) is of type UTF8String
    // and is used to identify the end user.
    SubscriptionIdData SubscriptionIdData("IMSSUBSCRIPTDATA");
    subscriptionId.setSubscriptionIdData(SubscriptionIdData);
    // Set the SubscriptionId AVP.
    waDerAns.addSubscriptionId(subscriptionId);

   //QoS-Resources Grouped AVP
    QoSResources qos; 
    FilterRule fr;
    Classifier cl;
    ClassifierID cid("VKUMARA@WA-INTERFACE");
    cl.setClassifierID(cid);
    fr.setClassifier(cl);
    qos.addFilterRule(fr);
    waDerAns.setQoSResources(qos);

    if (appMode == UNIT_TEST)
    cout<<waDerAns;

    // Send Object to stack.
    SendDiaAppMsg(waDerAns, sIdx);

    // Update stats.
    WaStats::GetWaStats()->UpdateSendStats(waDerAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}
