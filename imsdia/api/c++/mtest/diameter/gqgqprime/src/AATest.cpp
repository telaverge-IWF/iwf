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
 * LOG: $Log: AATest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:09  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:36:39  kamakshilk
 * LOG: GqGq' interface demo for static and distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: AATest.cpp,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: AATest.cpp,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $"

#include <app.h>
#include <gq_defines.h>
#include <gq_stats.h>
#include <diameter/gqgqprime/AA.h>
                                                                                
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::nasreq;
using namespace diameter::gqgqprime;

string sessIdString;
ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the AARequest to the
 *      diameter stack. Create the AARequest object,
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
int SendGqAARequest()
{
    // [1]. Create an instance of AARequest class
    // The AA-Request command is sent by a Diameter
    // client to a Diameter Server in order to request deregistration
    // Command-Code = 265 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    AARequest request(false,false);

    // [2.1.1.1] Fixed AVP.
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(GQGQ_INTERFACE_APP_ID, sIdx, sessIdString);
    request.setSessionId(SessionId(sessIdString));

    request.setSessionIndex(sIdx);

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authid(GQGQ_INTERFACE_APP_ID);
    request.setAuthApplicationId(authid);
    
    // [2.1.2.2] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost origh(GetOriginHost());
    request.setOriginHost(origh);

    // [2.1.2.3] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origr(GetOriginRealm());
    request.setOriginRealm(origr);

    // [2.1.2.4] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm desr(GetDestinationRealm());
    request.setDestinationRealm(desr);

    // [2.2.x] Optional AVPS
    
    // [2.2.1.1] The Media-Component-Description AVP (AVP code 517) 
    // is of type Grouped, and it contains service information 
    // for a  single media component within an AF session. 
    // It may be based on the SDI exchanged between the AF and the AF client
    MediaComponentDescription m1;

    // [2.2.1.2] The Media-Component-Number AVP (AVP code 518) is of 
    // type Unsigned32, and it contains the ordinal number of 
    // the media component, assigned 
    MediaComponentNumber mcn(10);
    m1.setMediaComponentNumber(mcn);

    // [2.2.1.3] The Media-Sub-Component AVP (AVP code 519) 
    // is of type Grouped, and it contains the requested QoS 
    // and filters for the set of IP flows identified by their i
    // common Flow-Identifier. 
    MediaSubComponent ms1;

    // [2.2.1.4] The Flow-Number AVP (AVP code 509) is of type Unsigned32, 
    // and it contains the ordinal number of the IP flow(s),
    FlowNumber fn(10);
    ms1.setFlowNumber(fn);
  
    m1.addMediaSubComponent(ms1);
   
    // [2.2.1] set MediaComponentDescription to AA Request
    request.addMediaComponentDescription(m1);

    // [2.2.2.1] The Flows AVP (AVP code 510) is of type Grouped, 
    // and it indicates IP flows via their flow identifiers
    Flows f1;

    // [2.2.2.2] The Flow-Number AVP (AVP code 509) is of type Unsigned32,
    // and it contains the ordinal number of the IP flow(s),
    FlowNumber fn2(10);
    f1.addFlowNumber(fn2);

    //  [2.2.2.3] The Media-Component-Number AVP (AVP code 518) is of
    // type Unsigned32, and it contains the ordinal number of
    // the media component, assigned
    MediaComponentNumber mcn2(10);
    f1.setMediaComponentNumber(mcn2);

    // [2.2.2.4] The Flow-Grouping AVP (AVP code 508) is of type Grouped, 
    // and it indicates that no other IP Flows shall be transported together 
    // with the listed IP Flows in the same PDP context(s).
    FlowGrouping F1;
    F1.addFlows(f1);

    // [2.2.2] set FlowGrouping to AA Request object
    request.addFlowGrouping(F1);

    // [2.2.3.1] The AF-Charging-Identifier AVP (AVP code 505)
    //  is of type OctetString, contains the AF Charging Identifier 
    // that is sent by the AF.
    AFChargingIdentifier afcid("INT100");
    request.setAFChargingIdentifier(afcid);

    // [2.2.3.2] The SIP_Forking AVP (AVP code 523) is of type Enumerated, 
    // and describes if several SIP dialogues are related to one
    // SINGLE_DIALOGUE (default)
    // SEVERAL_DIALOGUES
    SIPForkingIndication sipin(SIPForkingIndication::SINGLE_DIALOGUE);
    request.setSIPForkingIndication(sipin);

    // [2.2.3] The Specific-Action AVP (AVP code 513) is of type Enumerated.
    // The following values are defined for this AVP
    // SERVICE_INFORMATION_REQUEST
    // CHARGING_CORRELATION_EXCHANGE
    // INDICATION_OF_LOSS_OF_BEARER
    // INDICATION_OF_RECOVERY_OF_BEARER
    // INDICATION_OF_RELEASE_OF_BEARER
    // INDICATION_OF_ESTABLISHMENT_OF_BEARER
    SpecificAction sp1(SpecificAction::INDICATION_OF_RELEASE_OF_BEARER);
    request.addSpecificAction(sp1);

    // [2.2.4] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName un("sip:Smith@3gppnetwork.com");
    request.setUserName(un);

    // [2.2.5.1] The V4-Transport-Address AVP (AVP code 454) 
    // is of type Grouped and contains a single IPv4 address and 
    // a single port number.
    V4TransportAddress addv4;

    // [2.2.5.2] The Framed-IP-Address AVP (AVP Code 8) [RADIUS] 
    // is of type OctetString and contains an IPv4 address
    FramedIPAddress faddr("10.1.1.1");
    addv4.setFramedIPAddress(faddr);

    // [2.2.5.3] The Port-Number AVP (AVP code 455) is of type 
    // Unsigned32 and contains the end point port number.
    PortNumber pno(1811);
    addv4.setPortNumber(pno);

    // [2.2.5.4] The V6-Transport-Address AVP (AVP code 453) 
    // is of type Grouped and contains a single IPv6 address 
    // and a single port number.
    V6TransportAddress addv6;


    // [2.2.5.4] The Framed-IPv6-Prefix AVP (AVP Code 97) is 
    // of type OctetString and contains the IPv6 prefix to be 
    // configured for the user
    FramedIPv6Prefix fpre("10.1.1.2");
    addv6.setFramedIPv6Prefix(fpre);

    // [2.2.5.5] The Port-Number AVP (AVP code 455) is of type 
    // Unsigned32 and contains the end point port number.
    PortNumber pno1(1812);
    addv6.setPortNumber(pno1);

    // [2.2.5.6] The Binding-Input-List AVP (AVP code 451) is 
    // of type Grouped and contains a list transport addresses 
    // for which a binding is requested.
    BindingInputList bil;
    bil.addV4TransportAddress(addv4);
    bil.addV6TransportAddress(addv6);
    // [2.2.5.7] The Binding-Information AVP (AVP code 450) is 
    // of type Grouped and is sent between the AF and the SPDF
    BindingInformation b1;
    b1.setBindingInputList(bil);

    // [2.2.5] set BindingInformation to AA Request object
    request.setBindingInformation(b1); 

    // [2.2.6] Reservation-Priority AVP (AVP code 458) is of type Enumerated. 
    // The following values are specified:
    // PRIORITY-ONE
    // PRIORITY-TWO
    // PRIORITY-THREE
    // PRIORITY-FOUR
    // PRIORITY-FIVE
    // PRIORITY-SIX
    // PRIORITY-SEVEN
    ReservationPriority rprty(ReservationPriority::PRIORITY_ONE);
    request.setReservationPriority(rprty);

    // [2.2.7.1] The Globally-Unique-Address AVP (AVP code 300) 
    // is of type Grouped
    GloballyUniqueAddress gua;

    // [2.2.7.2] The Framed-IP-Address AVP (AVP Code 8) [RADIUS] 
    // is of type OctetString and contains an IPv4 address
    FramedIPAddress fip("11.1.2.1");
    gua.setFramedIPAddress(fip);

    // [2.2.7.3] The Framed-IPv6-Prefix AVP (AVP Code 97) is 
    // of type OctetString and contains the IPv6 prefix
    FramedIPv6Prefix fpre1("x.y");
    gua.setFramedIPv6Prefix(fpre1);

    // [2.2.7.4] The Address-Realm AVP (AVP code 301) is of 
    // type Octet String
    AddressRealm addrr("dia.net");
    gua.setAddressRealm(addrr);

    // [2.2.7] set GloballyUniqueAddress to the AA Request Object
    request.setGloballyUniqueAddress(gua);

    // [2.2.8] The Authorization-Lifetime AVP (AVP Code 291) 
    // is of type Unsigned32
    AuthorizationLifetime authlt(24);
    request.setAuthorizationLifetime(authlt);

    // [2.2.9.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //diameter::base::ProxyInfo pi1;

    // [2.2.9.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);

    // [2.2.9.2] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);

    // [2.2.9] set the ProxyInfo AVP
    // Application should not set this AVP.
    // request.addProxyInfo(pi1);

    // [2.2.10] Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord rrec("nemo");
    // Application should not set this AVP.
    // request.addRouteRecord(rrec);
    
    if (appMode == UNIT_TEST)
    cout << "AAR" << request << endl;

    // Send Encoded Message to the Stack.
    SendDiaAppMsg(request, sIdx);
    GqgqStats::GetGqgqStats()->UpdateSendStats(request.getCommandCode(),
                                                                ITS_TRUE);
                                                                                
    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the AA request
 *      made by the diameter stack. Create the AAAnswer
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
int SendGqAAAnswer(const CommandImpl * impl)
{
    //[ 1] Create an instance of AAAnswer class
    // The AA-Answer command is sent by a Diameter
    // server to a Diameter client in order to request deregistration
    // Command-Code = 265 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gqgqprime::AAAnswer answer;

    // Create an instance of AARequest class 
    AARequest aar1(*impl);

    // Get the some AVP values and set them to Answer Message
    const SessionId& sid = aar1.getSessionId();
    const OriginHost& oh = aar1.getOriginHost();
    const OriginRealm& or1 = aar1.getOriginRealm();
    const DestinationRealm& dr = aar1.getDestinationRealm();
    const AuthApplicationId& aaid1 = aar1.getAuthApplicationId();
   
    // Fixed AVP

    // [2] Insert data in the created AAAnswer object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed paramete "Session-Id".
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    answer.setSessionId(sid);

    // Required AVPs

    // [2.1.2] Populate required Manatories.
    // [2.1.2.1] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    answer.setAuthApplicationId(aaid1);

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
    answer.setOriginHost(origh);


    // [2.1.2.3] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origr(dr.value());
    answer.setOriginRealm(origr);

    // Optional AVPS

    // [2.2] Populate Optionals
    // [2.2.1] Set the Result-Code AVP .
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
    ResultCode rc(2001u);
    answer.setResultCode(rc);

    // [2.2.2.1] Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // ResultCode AVP is already been set, we dont need to set this.
    //ExperimentalResult er1;

    // [2.2.2.2] Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    //VendorId vid(VENDOR_ID);
    //er1.setVendorId(vid);
    // [2.2.2.3] Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    //ExperimentalResultCode erc(100);
    //er1.setExperimentalResultCode(erc);

    // [2.2.2]Set the ExperimentalResult AVP
    // answer.setExperimentalResult(er1);
   
    // [2.2.3.1] The V4-Transport-Address AVP (AVP code 454) 
    // is of type Grouped and contains a single IPv4 address 
    // and a single port number.
    V4TransportAddress addv4;

    // [2.2.3.2] The Framed-IP-Address AVP (AVP Code 8) [RADIUS] 
    // is of type OctetString and contains an IPv4 address
    FramedIPAddress fip1("10.1.1.1");
    addv4.setFramedIPAddress(fip1);

    // [2.2.3.3] The Port-Number AVP (AVP code 455) is of 
    // type Unsigned32 and contains the end point port number.
    PortNumber pn1(1811);
    addv4.setPortNumber(pn1);

    // [2.2.3.4] The V6-Transport-Address AVP (AVP code 453) 
    // is of type Grouped and contains a single IPv6 address 
    // and a single port number.
    V6TransportAddress addv6;

    // [2.2.3.5] The Framed-IPv6-Prefix AVP (AVP Code 97) 
    // is of type OctetString and contains the IPv6 prefix 
    // to be configured for the user
    FramedIPv6Prefix fpre("10.1.1.2");
    addv6.setFramedIPv6Prefix(fpre);

    // [2.2.3.6] The Port-Number AVP (AVP code 455) is of 
    // type Unsigned32 and contains the end point port number.
    PortNumber pno1(1824);
    addv6.setPortNumber(pno1);

    // [2.2.3.7] The Binding-Input-List AVP (AVP code 451) 
    // is of type Grouped and contains a list transport 
    // addresses for which a binding is requested.
    BindingInputList bil;
    bil.addV4TransportAddress(addv4);
    bil.addV6TransportAddress(addv6);

    // [2.2.3.8] The Binding-Information AVP (AVP code 450) is 
    // of type Grouped and is sent between the AF and the SPDF
    BindingInformation b1;
    b1.setBindingInputList(bil);

    // [2.2.3 ] set the BindingInformation AVP
    answer.setBindingInformation(b1); 

    // [2.2.4] Reservation-Priority AVP (AVP code 458) is of type Enumerated.
    // The following values are specified:
    // PRIORITY-ONE
    // PRIORITY-TWO
    // PRIORITY-THREE
    // PRIORITY-FOUR
    // PRIORITY-FIVE
    // PRIORITY-SIX
    // PRIORITY-SEVEN
    ReservationPriority v1(ReservationPriority::PRIORITY_ONE);
    answer.setReservationPriority(v1);

    // [2.2.5] The Authorization-Token AVP (AVP code 506) is of type 
    // OctetString, and contains the Authorization Token
    AuthorizationToken atoken("ABC");
    answer.setAuthorizationToken(atoken);

    // [2.2.6.1] The Access-Network-Charging-Identifier AVP 
    // (AVP code 502) is of type Grouped, and contains a 
    // charging identifier
    AccessNetworkChargingIdentifier ac1;

    //[2.2.6.2]The Access-Network-Charging-Identifier-Value 
    // AVP (AVP code 503) is of type OctetString, and contains 
    // a charging identifier
    AccessNetworkChargingIdentifierValue aciv("ABC");
    ac1.setAccessNetworkChargingIdentifierValue(aciv);

    // [2.2.6] set the AccessNetworkChargingIdentifier 
    // AVP to AAAnswer Message
    answer.addAccessNetworkChargingIdentifier(ac1);

    // [2.2.7.1] Address AVP for each potential IP address 
    // that MAY be locally used when transmitting Diameter messages.
    Address f1(Address::IPV4,"11.1.1.1");

    // [2.2.7] The Access-Network-Charging-Address AVP 
    // (AVP code 501) is of type Address, and it indicates 
    // the IP Address of the network entity within the access 
    // network performing charging
    AccessNetworkChargingAddress anc(f1);
    answer.setAccessNetworkChargingAddress(anc);

    // [2.2.8] The Error-Message AVP (AVP Code 281) is of type UTF8String.  
    // It MAY accompany a Result-Code AVP as a human readable error message
    // ErrorMessage err("Authentication error");
    // answer.setErrorMessage(err);

    // [2.2.9] The Error-Reporting-Host AVP (AVP Code 294) is of type
    // DiameterIdentity.  This AVP contains the identity of the Diameter
    // host that sent the Result-Code AVP
    // ErrorReportingHost errh("dia.xyz.com");
    // answer.setErrorReportingHost(errh);

    // [2.2.10] The Authorization-Lifetime AVP (AVP Code 291) 
    // is of type Unsigned32
    AuthorizationLifetime alt1(24);
    answer.setAuthorizationLifetime(alt1);

    // [2.2.11] The Auth-Grace-Period AVP (AVP Code 276) 
    // is of type Unsigned32 and contains the number of 
    // seconds the Diameter server to wait
    AuthGracePeriod authp(10);
    answer.setAuthGracePeriod(authp);

    // [2.2.12.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    // diameter::base::ProxyInfo pi2;

    // [2.2.12.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost ph1("proxy2.abc.com");
    //pi2.setProxyHost(ph1);

    // [2.2.12.3] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState ps1("state0");
    //pi2.setProxyState(ps1);

    // [2.2.12] Set the ProxyInfo AVP to AAAnswer Message
    // Application should not set this AVP.
    // answer.addProxyInfo(pi2);

    cout << "AAA" << answer << endl;

    // Send encoded message to stack.
    SendDiaAppMsg(answer, sIdx);
    GqgqStats::GetGqgqStats()->UpdateSendStats(answer.getCommandCode(),
                                                            ITS_FALSE);
                                                                                
    return (ITS_SUCCESS);
}

