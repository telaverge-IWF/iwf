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
 * LOG: $Log: UserDataTest.cpp,v $
 * LOG: Revision 3.3  2010/09/22 05:44:48  vkumara
 * LOG: Read IP addr for GlobalUniueAddr-IPV4 AVP
 * LOG:
 * LOG: Revision 3.2  2010/09/09 03:38:29  nvijikumar
 * LOG: ETSI ES 283 034 V2.2.0 (2008-07)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:09  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/01/04 16:05:47  hbhatnagar
 * LOG: Baseline demo application for e4 interface for static and distributed.
 * LOG:
 * LOG:
 * ID: $Id: UserDataTest.cpp,v 3.3 2010/09/22 05:44:48 vkumara Exp $
 ****************************************************************************/
#ident "$Id: UserDataTest.cpp,v 3.3 2010/09/22 05:44:48 vkumara Exp $"

#include <app.h>
#include <e4_defines.h>
#include <e4_stats.h>
#include <diameter/e4/UserData.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::e4;

string sessIdString;
ITS_UINT sIdx;

void PopulateIPFilterRule(IPFilterRule &ipFltRule);

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the  UserDataRequest to the
 *      diameter stack. Create the  UserDataRequest object,
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
int SendE4UserDataRequest()
{
    // [1]. Create an instance of UserDataRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::e4::UserDataRequest udReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(E4_INTERFACE_APP_ID, sIdx, sessIdString);
    udReq.setSessionId(diameter::base::SessionId(sessIdString));

    udReq.setSessionIndex(sIdx);

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
    AuthApplicationId authApplicationId(E4_INTERFACE_APP_ID);
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
    udReq.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

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
    udReq.setAuthSessionState(authSessionState);

    // [2.1.2.3] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP E4OULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    udReq.setOriginHost(originHost);

    // [2.1.2.4] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    udReq.setOriginRealm(originRealm);

    // [2.1.2.5] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    udReq.setDestinationRealm(destinationRealm);


    // [2.2.1] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP E4OULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    udReq.setDestinationHost(destinationHost);

    // This information element contains:
    // The IP address of the user equipment used by the subscriber for which
    // profile information is being pushed.( i.e contains a Frame-IP-Address
    // or Frame-IPv6-Prefix AVP value, and an Address-Realm AVP).
    // The addressing domain in which the IP address is significant.(i.e Address-Realm AVP).
    GloballyUniqueAddress gua ;
    string ipAddress;

    //for unit test provide the values of IP Addresses for GlobalUniqueAddr based routing  
      cout << endl << "Please Enter the IP Address  " <<endl;
      cin >> ipAddress ;

    // [2.2.5.2] The Framed-IP-Address AVP (AVP Code 8) [RADIUS]
    // is of type OctetString and contains an IPv4 address
    FramedIPAddress faddr(ipAddress);
    gua.setFramedIPAddress(faddr);

    // [2.2.5.4] The Framed-IPv6-Prefix AVP (AVP Code 97) is
    // of type OctetString and contains the IPv6 prefix to be
    // configured for the user
    FramedIPv6Prefix fpre("10.1.1.2");
    gua.setFramedIPv6Prefix(fpre);

    udReq.setGloballyUniqueAddress(gua);

    // The AF-Application-identifier AVP (AVP code 504) is of type OctetString,
    // and it contains information that identifies the particular service that
    // the AF service session belongs to. This information may be used by the
    // PDF to differentiate
    AFApplicationIdentifier afai("abc@xyz");
    udReq.setAFApplicationIdentifier(afai);

    // [2.1.2.6] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    udReq.setUserName(userName);


    if (appMode == UNIT_TEST)
    cout<<udReq;

    // Send object to stack.
    SendDiaAppMsg(udReq, sIdx);

    E4Stats::GetE4Stats()->UpdateSendStats(udReq.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends the Answer to the UserDataRequest request
 *      made by the diameter stack. Create the UserDataAnswer
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
int SendE4UserDataAnswer(const CommandImpl * impl)
{
    // 1. Create an instance of UserDataAnswer class
    // The User-Data-Answer command is sent by a server
    // in response to the User-Data-Request command with
    // Command-Code = 303 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::e4::UserDataAnswer udAns;

    // Create an instance of MultimediaAuthRequest class to get host and
    // session details
    UserDataRequest udreq(*impl);

    // Get AVP values from requested message
    const SessionId &sid1 = udreq.getSessionId();
    const OriginHost &oh1 = udreq.getOriginHost();
    const OriginRealm &or1 = udreq.getOriginRealm();
    if (udreq.containsDestinationHost())
        const DestinationHost &dh1 = udreq.getDestinationHost();
    const DestinationRealm &dr1 = udreq.getDestinationRealm();
    const VendorSpecificApplicationId &vsAppId =
                              udreq.getVendorSpecificApplicationId();
    const AuthSessionState &authSessState = udreq.getAuthSessionState();
    const UserName &uname = udreq.getUserName();


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
    udAns.setSessionId(sid1);

    udAns.setSessionIndex(udreq.getSessionIndex());

    // [2.1.2.x] Required AVPs

    // [2.1.2.1.1]Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as possibl
    //[2.1.2.1] Set the  Vendor-Specific-Application-Id AVP.
    udAns.setVendorSpecificApplicationId(vsAppId);

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
    udAns.setResultCode(resultCode);

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

    // This AVP is required incase of Result-Code AVP is missing.
    udAns.setExperimentalResult(experimentalResult);

    // [2.1.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP E4OULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    udAns.setAuthSessionState(authSessState);

    // [2.1.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP E4OULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    udAns.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    udAns.setOriginRealm(originRealm);

    // [2.1] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    udAns.setUserName(uname);

    // The Logical-Access-ID AVP (AVP code 302 13019) is of type OctetString.
    // This AVP contains either a Circuit-ID (as defined in RFC 3046 [11]) or a
    // technology independent identifier.
    LogicalAccessId logAccId("abc@xyz");
    udAns.setLogicalAccessId(logAccId);

    // The Physical-Access-ID AVP (AVP code 313 13019) is of type UTF8String and
    // identifies the physical access to which the user equipment is connected.
    // It includes a port identifier and the identity of the access node where
    // the port resides.
    PhysicalAccessId phyAccId("mno:1234");
    udAns.setPhysicalAccessId(phyAccId);

    // The Access-Network-Type AVP (AVP code 306 13019) is of type Grouped,
    // and it indicates the type of port on which the user equipment is connected
    // and the type of aggregation network.
    AccessNetworkType accessNetworkType;

    // The NAS-Port-Type AVP (AVP Code 61) is of type Enumerated and contains the
    // type of the port on which the NAS is authenticating the user. This AVP
    // SHOULD be present if the NAS uses the same NAS-Port number ranges for
    // different service types concurrently. The supported values are defined in
    // [RADIUSTypes].
    NASPortType  nasPortType(NASPortType::SYNC);
    accessNetworkType.setNASPortType(nasPortType);

    // The Aggregation-Network-Type AVP (AVP code 307 13019)
    // and is of type Enumerated.
    AggregationNetworkType  aggNetType(AggregationNetworkType::ETHERNET);
    accessNetworkType.setAggregationNetworkType(aggNetType);
    udAns.setAccessNetworkType(accessNetworkType);

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

    udAns.setInitialGateSettingDescription(initGatSet);

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

    udAns.addQoSProfileDescription(qosProfile);

    // The IP-Connectivity-Status AVP (AVP code 305 13019) is of type Enumerated.
    IPConnectivityStatus ipConnStat(IPConnectivityStatus::IP_CONNECTIVITY_ON);
    udAns.setIPConnectivityStatus(ipConnStat);

    // This information element contains:
    // The IP address of the user equipment used by the subscriber for which
    // profile information is being pushed.( i.e contains a Frame-IP-Address
    // or Frame-IPv6-Prefix AVP value, and an Address-Realm AVP).
    // The addressing domain in which the IP address is significant.(i.e Address-Realm AVP).
    GloballyUniqueAddress gua ;
    string ipAddress;

    //for unit test provide the values of IP Addresses for GlobalUniqueAddr based routing  
    cout << endl << "Please Enter the IP Address  " <<endl;
    cin >> ipAddress ;

    // [2.2.5.2] The Framed-IP-Address AVP (AVP Code 8) [RADIUS]
    // is of type OctetString and contains an IPv4 address
    FramedIPAddress faddr(ipAddress);
    gua.setFramedIPAddress(faddr);

    udAns.setGloballyUniqueAddress(gua);
  
    // It is an Geouped AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    // This AVP should not be set by Application.
    // udAns.setProxyInfo(diameter::base::ProxyInfo(...));

    // Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    // This AVP should not be set by Application.
    // udAns.setRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values

    if (appMode == UNIT_TEST)
    cout<<udAns;

    // Send Object to stack.
    SendDiaAppMsg(udAns, sIdx);

    // Update stats.
    E4Stats::GetE4Stats()->UpdateSendStats(udAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
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

