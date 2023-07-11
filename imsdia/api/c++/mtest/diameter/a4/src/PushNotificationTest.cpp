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
 * LOG: $Log: PushNotificationTest.cpp,v $
 * LOG: Revision 1.1  2011/06/29 06:39:46  vkumara
 * LOG: Baseline for a4 interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: PushNotificationTest.cpp,v 1.1 2011/06/29 06:39:46 vkumara Exp $
 ****************************************************************************/
#ident "$Id: PushNotificationTest.cpp,v 1.1 2011/06/29 06:39:46 vkumara Exp $"

#include <app.h>
#include <a4_defines.h>
#include <a4_stats.h>
#include <diameter/a4/PushNotification.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::a4;

extern string sessIdString;
extern ITS_UINT sIdx;

extern void PopulateIPFilterRule(IPFilterRule &ipFltRule);

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the PushNotificationRequest the
 *      diameter stack. Create the PushNotificationRequest object,
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
int SendA4PushNotificationRequest()
{
    // 1. Create an instance of PushNotificationRequest class
    // The Push-Notification-Request command is sent from a Diameter
    // multimedia client to a Diameter multimedia server in order to
    // pnReq it to store the name of the server that is currently
    // serving the user.
    // Command-Code = 309 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::a4::PushNotificationRequest pnReq;

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
    AllocateSession(A4_INTERFACE_APP_ID, sIdx, sessIdString);
    pnReq.setSessionId(diameter::base::SessionId(sessIdString));

    pnReq.setSessionIndex(sIdx);

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
    AuthApplicationId authApplicationId(A4_INTERFACE_APP_ID);
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
    pnReq.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

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
    pnReq.setAuthSessionState(authSessionState);

    // [2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP A4OULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    pnReq.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    pnReq.setOriginRealm(originRealm);

    // [2.1] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    pnReq.setDestinationRealm(destinationRealm);


    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP A4OULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    pnReq.setDestinationHost(destinationHost);

    // This information element contains:
    // The IP address of the user equipment used by the subscriber for which
    // profile information is being pushed.( i.e contains a Frame-IP-Address
    // or Frame-IPv6-Prefix AVP value, and an Address-Realm AVP).
    // The addressing domain in which the IP address is significant.(i.e Address-Realm AVP).
    //GloballyUniqueAddress gua ;
    //string ipAddress;

    //for unit test provide the values of IP Addresses for GlobalUniqueAddr based routing  
    //  cout << endl << "Please Enter the IP Address  " <<endl;
    //  cin >> ipAddress ;

    // [2.2.5.2] The Framed-IP-Address AVP (AVP Code 8) [RADIUS]
    // is of type OctetString and contains an IPv4 address
    //FramedIPAddress faddr(ipAddress);
    //gua.setFramedIPAddress(faddr);

    // [2.2.5.4] The Framed-IPv6-Prefix AVP (AVP Code 97) is
    // of type OctetString and contains the IPv6 prefix to be
    // configured for the user
    //FramedIPv6Prefix fpre("10.1.1.2");
    //gua.setFramedIPv6Prefix(fpre);

    //pnReq.setGloballyUniqueAddress(gua);

    // [2.1.2.6] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    pnReq.setUserName(userName);

    // The Logical-Access-ID AVP (AVP code 302 13019) is of type OctetString.
    // This AVP contains either a Circuit-ID (as defined in RFC 3046 [11]) or a
    // technology independent identifier.
    LogicalAccessId logAccId("abc@xyz");
    pnReq.setLogicalAccessId(logAccId);

    // The Physical-Access-ID AVP (AVP code 313 13019) is of type UTF8String and
    // identifies the physical access to which the user equipment is connected.
    // It includes a port identifier and the identity of the access node where
    // the port resides.
    PhysicalAccessId phyAccId("mno:1234");
    pnReq.setPhysicalAccessId(phyAccId);

    // The Access-Network-Type AVP (AVP code 306 13019) is of type Grouped,
    // and it indicates the type of port on which the user equipment is connected
    // and the type of aggregation network.
 //   AccessNetworkType accessNetworkType;



    // The Initial-Gate-Setting AVP (AVP code 303 13019) is of type Grouped.
    InitialGateSettingDescription initGatSet;

    // The NAS-Filter-Rule AVP (AVP Code 400) is of type IPFilterRule and provides
    // filter rules that need to be configured on the NAS for the user. One or more
    // of these AVPs MAY be present in an authorization response.
    IPFilterRule ipFltrule;
    PopulateIPFilterRule(ipFltrule);

    NASFilterRule nasFilterRule(ipFltrule);
    initGatSet.addNASFilterRule(nasFilterRule);

    // The Maximum-Allowed-Bandwidth-UL AVP (AVP code 308 13019) is of type
    // Unsigned32 and indicated the maximum uplink bandwidth that can be authorized
    // for a particular traffic class. The AVP value is expressed in kbits/s.
    // Absence of the Maximum-Allowed-Bandwidth-UL AVP indicates that no limitation
    // is placed by the subscription on the amount of bandwidth that can be used
    // on the uplink direction.
    MaximumAllowedBandwidthUL mabu(256u);
    initGatSet.setMaximumAllowedBandwidthUL(mabu);

    // The Maximum-Allowed-Bandwidth-DL AVP (AVP code 309 13019) is of type
    // Unsigned32 and indicated the maximum downlink bandwidth that can be
    // authorized for a particular traffic class. The AVP value is expressed in
    // kbits/s. Absence of the Maximum-Allowed-Bandwidth-DL AVP indicates that no
    // limitation is placed by the subscription on the amount of bandwidth that
    // can be used on the downlink direction.
    MaximumAllowedBandwidthDL mabd(1024u);
    initGatSet.setMaximumAllowedBandwidthDL(mabd);

    pnReq.setInitialGateSettingDescription(initGatSet);

    // The QoS-Profile AVP (AVP code 304 13019) represent of QoS-Profile element
    //  and is of type Grouped.
    QoSProfileDescription  qosProfile;

    // The Application-Class-ID AVP (AVP code 312 13019) is of type UTF8String
    //  and represents a class of applications that share the same QoS profile.
    ApplicationClassId  appClassId("ACID:1234");
    qosProfile.addApplicationClassId(appClassId);

    // The Media-Type AVP is defined in the Gq specification (TS 129 209 [5]) and
    // shall be used with the Vendor-Id header set to 3GPP (10415).
    MediaType mediaType(MediaType::DATA);
    qosProfile.addMediaType(mediaType);

    // The Reservation-Priority AVP (AVP code 310 13019) is of type Enumerated and
    // represent a priority level to serve resource reservation requests.
    ReservationPriority  resvPriority(ReservationPriority::PRIORITY_0);
    qosProfile.setReservationPriority(resvPriority);

    qosProfile.setMaximumAllowedBandwidthUL(mabu);

    qosProfile.setMaximumAllowedBandwidthDL(mabd);

    // The Transport-Class AVP (AVP code 311 13019) is of type Unsigned32 and
    // contains an integer used as an indexpointing to a class of transport
    // services to be applied (e.g. forwarding behaviour).
    TransportClass transClass(125u);
    qosProfile.setTransportClass(transClass);

    pnReq.addQoSProfileDescription(qosProfile);

    // The IP-Connectivity-Status AVP (AVP code 305 13019) is of type Enumerated.
    // IPConnectivityStatus ipConnStat(IPConnectivityStatus::IP_CONNECTIVITY_ON);
    //  pnReq.setIPConnectivityStatus(ipConnStat);

    // Application should not set this AVP.
    // pnReq.addProxyInfo(diameter::base::ProxyInfo(...));
    // pnReq.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values

    if (appMode == UNIT_TEST)
    cout<<endl<<" PNR : " << pnReq <<endl;

    SendDiaAppMsg(pnReq, sIdx);
    A4Stats::GetA4Stats()->UpdateSendStats(pnReq.getCommandCode(), ITS_TRUE);

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the PushNotification request
 *      made by the diameter stack. Create the PushNotificationAnswer
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
int SendA4PushNotificationAnswer(const CommandImpl * impl1)
{
    // 1. Create an instance of PushNotificationAnswer class
    // The Push-Notification-Answer command is sent by a server
    // in response to the Location-Info-Request command with
    // Command-Code = 309 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::a4::PushNotificationAnswer pnAns;

    // Create an instance of ServerAssignmentRequest class
    PushNotificationRequest pnreq(*impl1);

    // Get some AVP values from Request and set them to Answer Message
    const SessionId &sid1 = pnreq.getSessionId();
    const OriginHost &oh1 = pnreq.getOriginHost();
    const OriginRealm &or1 = pnreq.getOriginRealm();
    const AuthSessionState &authSessState = pnreq.getAuthSessionState();
    const VendorSpecificApplicationId
                          &vsAppId = pnreq.getVendorSpecificApplicationId();
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    pnAns.setSessionId(sid1);

    pnAns.setSessionIndex(pnreq.getSessionIndex());

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
    // [2.1.1] Set the  Vendor-Specific-Application-Id AVP.
    pnAns.setVendorSpecificApplicationId(vsAppId);

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
    pnAns.setResultCode(resultCode);

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
    // pnAns.setExperimentalResult(experimentalResult);

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
    pnAns.setAuthSessionState(authSessState);

    // [2.1.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP A4OULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    pnAns.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    pnAns.setOriginRealm(originRealm);

    if (appMode == UNIT_TEST)
    cout<<endl<<"PNA : " << pnAns <<endl;

    SendDiaAppMsg(pnAns, sIdx);
    A4Stats::GetA4Stats()->UpdateSendStats(pnAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}


