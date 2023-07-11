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
 * LOG: Revision 3.1  2008/03/31 10:33:09  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/01/04 12:54:27  hbhatnagar
 * LOG: baseline demo application for e2 interface
 * LOG:
 * LOG:
 * ID: $Id: UserDataTest.cpp,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: UserDataTest.cpp,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $"

#include <app.h>
#include <e2_defines.h>
#include <e2_stats.h>
#include <diameter/e2/UserData.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::e2;

string sessIdString;
ITS_UINT sIdx;

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
int SendE2UserDataRequest()
{
    // [1]. Create an instance of UserDataRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::e2::UserDataRequest udReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(E2_INTERFACE_APP_ID, sIdx, sessIdString);
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
    AuthApplicationId authApplicationId(E2_INTERFACE_APP_ID);
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
    // This AVP SHOULD be placed as close to the Diameter header as possible.
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


    // [2.2.1] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    udReq.setDestinationHost(destinationHost);

    // [2.1.2.5] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    udReq.setDestinationRealm(destinationRealm);

    
    // This information element contains:
    // The IP address of the user equipment used by the subscriber for which
    // profile information is being pushed.( i.e contains a Frame-IP-Address
    // or Frame-IPv6-Prefix AVP value, and an Address-Realm AVP).
    // The addressing domain in which the IP address is significant.(i.e Address-Realm AVP).
    GloballyUniqueAddress gua ;
    
    // [2.2.5.2] The Framed-IP-Address AVP (AVP Code 8) [RADIUS]
    // is of type OctetString and contains an IPv4 address
    FramedIPAddress faddr("10.1.1.1");
    gua.setFramedIPAddress(faddr);

    // [2.2.5.4] The Framed-IPv6-Prefix AVP (AVP Code 97) is
    // of type OctetString and contains the IPv6 prefix to be
    // configured for the user
    FramedIPv6Prefix fpre("10.1.1.2");
    gua.setFramedIPv6Prefix(fpre);

    udReq.setGloballyUniqueAddress(gua);

    // [2.1.2.6] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    udReq.setUserName(userName);

    // The AF-Application-identifier AVP (AVP code 504) is of type OctetString, 
    // and it contains information that identifies the particular service that
    // the AF service session belongs to. This information may be used by the
    // PDF to differentiate
    AFApplicationIdentifier afai("abc@xyz");
    udReq.setAFApplicationIdentifier(afai); 

    // The Requested-Information AVP shall be present if specific information is
    // requested and shall be absent if all available information is requested.
    // It contains  list of items requested by the AF.The Requested-Information AVP
    // (AVP code 353 13019) is of type Enumerated.
    RequestedInformation reqinfo(RequestedInformation::LOCATION_INFORMATION);
    udReq.setRequestedInformation(reqinfo);

    // Application should not set this AVP.
    // udReq.addProxyInfo(diameter::base::ProxyInfo(...));
    // udReq.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values

    if (appMode == UNIT_TEST)
    cout<<udReq;

    // Send object to stack.
    SendDiaAppMsg(udReq, sIdx);

    E2Stats::GetE2Stats()->UpdateSendStats(udReq.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends the Answer to the UserData request
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
int SendE2UserDataAnswer(const CommandImpl * impl)
{
    // 1. Create an instance of UserDataAnswer class
    // The User-Data-Answer command is sent by a server
    // in response to the User-Data-Request command with
    // Command-Code = 306 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::e2::UserDataAnswer udAns;

    // Create an instance of UserDataRequest class to get host and
    // session details
    UserDataRequest udreq(*impl);

    // Get AVP values from requested message
    const SessionId &sid1 = udreq.getSessionId();
    const OriginHost &oh1 = udreq.getOriginHost();
    const OriginRealm &or1 = udreq.getOriginRealm();
  //  if (mareq.containsDestinationHost())
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
    // This AVP SHOULD be placed as close to the Diameter header as
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
    // This AVP SHOULD be placed as close to the Diameter header as
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

    // Location information has AVP code 350 and  in a form that is
    // suitable for the requesting application.It is grouped AVP 
    LocationInformation locationInformation;

    // The Line-Identifier AVP has AVP code 500 is of type OctetString. This AVP
    // contains a fixed broadband access line identifier associated to the user.
    // This information element contains the line identifier of the user's network
    // termination.
    LineIdentifier lineIdentifier("lineID1");
    locationInformation.setLineIdentifier(lineIdentifier);
    
    udAns.setLocationInformation(locationInformation);
    
    // The RACS-Contact-Point AVP (AVP code 351 13019) is of type DiameterIdentity
    // and identifies the RACS element to which resource reservation requests shall be sent.
    // It is FQDN or IP address of the RACS entity where resource request
    // shall be sent (i.e. SPDF address). 
    RACSContactPoint racsContactPoint("192.1.1.1");
    udAns.setRACSContactPoint(racsContactPoint);

    // The Terminal-Type AVP (AVP code 352 13019) is of type OctetString and
    // contains a value of the User Class DHCP Option. It denotes type of user
    // equipment to which the IP address was allocated.
    TerminalType terminalType("Ethernet");
    udAns.setTerminalType(terminalType);
   
    // It is an Grouped AVP.
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
    E2Stats::GetE2Stats()->UpdateSendStats(udAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}


