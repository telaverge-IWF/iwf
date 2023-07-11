/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: AATest.cpp,v $
 * LOG: Revision 3.3  2010/09/23 08:09:54  vkumara
 * LOG: Globally-Unique-Address input reading from keyboard
 * LOG:
 * LOG: Revision 3.2  2010/09/09 03:37:28  nvijikumar
 * LOG: Updates with ETSI ES 283 026 V2.4.1 (2008-11)
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:11  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/01/08 07:41:35  hbhatnagar
 * LOG: baseline demo application for rq interface for static and distributed mode.
 * LOG:
 *
 * ID: $Id: AATest.cpp,v 3.3 2010/09/23 08:09:54 vkumara Exp $
 ****************************************************************************/
#include <app.h>
#include <rq_defines.h>
#include <rq_stats.h>
#include <diameter/rq/AA.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::rq;

string sessIdString;
ITS_UINT sIdx;

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the AA aaReq to the
 *      diameter stack. Creates the Accounting Request object,
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
int SendRqAARequest() 
{
    // [1]. Create an instance of AARequest class
    // The AA-Request command is sent by a Diameter
    // client to a Diameter Server in order to aaReq deregistration
    // Command-Code = 265 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::rq::AARequest aaReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(RQ_INTERFACE_APP_ID, sIdx, sessIdString);
    aaReq.setSessionId(SessionId(sessIdString));

    aaReq.setSessionIndex(sIdx);

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authid(RQ_INTERFACE_APP_ID);
    aaReq.setAuthApplicationId(authid);

    // [2.1.2.2] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost origh(GetOriginHost());
    aaReq.setOriginHost(origh);

    // [2.1.2.3] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origr(GetOriginRealm());
    aaReq.setOriginRealm(origr);

    // [2.1.2.4] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm desr(GetDestinationRealm());
    aaReq.setDestinationRealm(desr);

    // [2.2.x] Optional AVPS


    // The AF-Charging-Identifier AVP (AVP code 505)is of type OctetString,contains
    // the AF Charging Identifier that is sent by the AF. This information may be
    // used for charging correlation  between AF and RACS functional entities.
    AFChargingIdentifier afci("asdf@jkl");
    aaReq.setAFChargingIdentifier(afci);
       
    // [2.2.1.1] The Media-Component-Description AVP (AVP code 517)
    // is of type Grouped, and it contains service information
    // for a  single media component within an AF session.
    // It may be based on the SDI exchanged between the AF and the AF client
    MediaComponentDescription mediaComponentDescription;

    // [2.2.1.2] The Media-Component-Number AVP (AVP code 518) is of
    // type Unsigned32, and it contains the ordinal number of
    // the media component, assigned
    MediaComponentNumber mcn(10);
    mediaComponentDescription.setMediaComponentNumber(mcn);

    // [2.2.1.3] The Media-Sub-Component AVP (AVP code 519)
    // is of type Grouped, and it contains the requested QoS
    // and filters for the set of IP flows identified by their i
    // common Flow-Identifier.
    MediaSubComponent mediaSubComponent;

    // [2.2.1.4] The Flow-Number AVP (AVP code 509) is of type Unsigned32,
    // and it contains the ordinal number of the IP flow(s),
    FlowNumber flowNum(10);
    mediaSubComponent.setFlowNumber(flowNum);

    mediaComponentDescription.addMediaSubComponent(mediaSubComponent);


    // The AF-Application-identifier AVP (AVP code 504) is of type OctetString, and
    // it contains information that identifies the RACS client requesting the 
    // resources.
    AFApplicationIdentifier afai("abc@xyz");
    mediaComponentDescription.setAFApplicationIdentifier(afai);

    // The Media-Type AVP (AVP code 520) is of type Enumerated, and it determines
    // the media type of a session component.
    MediaType mediaType(MediaType::DATA);
    mediaComponentDescription.setMediaType(mediaType);
  
    // The Max-Requested-Bandwidth-UL AVP (AVP code 516) is of type Unsigned32, and
    // it indicates the maximum requested bandwidth in bits per second for an
    // uplink IP flow. The bandwidth contains all the overhead coming from the
    // IP-layer and the layers above, e.g. IP, UDP, RTP and RTP payload.
    MaxRequestedBandwidthUL mrbu(1024u);
    mediaComponentDescription.setMaxRequestedBandwidthUL(mrbu);

    // The Max-Requested-Bandwidth-DL AVP (AVP code 515) is of type Unsigned32, and
    // it indicates the maximum requested bandwidth in bits per second for a
    // downlink IP flow. The bandwidth contains all the overhead coming from the
    // IP-layer and the layers above, e.g. IP, UDP, RTP and RTP payload.
    MaxRequestedBandwidthDL mrbd(256u);
    mediaComponentDescription.setMaxRequestedBandwidthDL(mrbd);

    // The Flow-Status AVP (AVP code 511) is of type Enumerated, and describes
    // whether the IP flow(s) are enabled or disabled. The Flow-Status AVP may
    // be present in the Media-Description-Component AVP and/or in the Media-Sub
    // -Component AVP.
    
    FlowStatus flowStatus(FlowStatus::ENABLED_UPLINK);
    mediaComponentDescription.setFlowStatus(flowStatus);

    // The RS-Bandwidth AVP (AVP code 522) is of type Unsigned32, and it indicates
    // the maximum required bandwidth in bits per second for RTCP sender reports
    // within the session component, as specified in RFC 3556. The bandwidth
    // contains all the overhead coming from the IP-layer and the layers above,
    // i.e. IP, UDP and RTCP.
    RSBandwidth rsBandwidth(512u);
    mediaComponentDescription.setRSBandwidth(rsBandwidth);
  
    // The RR-Bandwidth AVP (AVP code 521) is of type Unsigned32, and it indicates
    // the maximum required bandwidth in bits per second for RTCP receiver reports
    // within the session component, as specified in RFC 3556. The bandwidth
    // contains all the overhead coming from the IP-layer and the layers above,
    // i.e.IP, UDP and RTCP.
    RRBandwidth rrBandwidth(512u);
    mediaComponentDescription.setRRBandwidth(rrBandwidth);

    // The Reservation-Priority AVP (AVP code 458) is of type Enumerated. It may
    // be specified in an AA-Request as a main AVP in order to associate a priority
    // with a resource reservation or modification request. It may also be specified
    // as part of a Media-Component AVP in order to associate a priority with
    // resource reservations requested for the media flows identified by the Media-
    // Sub-Component AVP(s) in a Media-Component AVP.  
    ReservationPriority reservationPriority(ReservationPriority::DEFAULT);
    mediaComponentDescription.setReservationPriority(reservationPriority);

    // The Reservation-Class AVP (AVP code 456) is of type Unsigned32, and it
    // contains an integer used as an index pointing to the traffic characteristics
    // of the flow (e.g. burstiness and packet size).  
    ReservationClass reservationClass(5u);
    mediaComponentDescription.setReservationClass(reservationClass);

    // The Transport-Class AVP (AVP code 311) is of type Unsigned32, and it
    // contains an integer used as an index pointing to a class of transport
    // services to be applied (e.g. forwarding behaviour).
    TransportClass transportClass(10u);
    mediaComponentDescription.setTransportClass(transportClass); 

    // [2.2.1] set MediaComponentDescription to AA Request
    aaReq.addMediaComponentDescription(mediaComponentDescription);

    // [2.2.2.1] The Flows AVP (AVP code 510) is of type Grouped,
    // and it indicates IP flows via their flow identifiers
    Flows flows;

    // [2.2.2.2] The Flow-Number AVP (AVP code 509) is of type Unsigned32,
    // and it contains the ordinal number of the IP flow(s),
    FlowNumber flowNumber(10);
    flows.addFlowNumber(flowNumber);

    //  [2.2.2.3] The Media-Component-Number AVP (AVP code 518) is of
    // type Unsigned32, and it contains the ordinal number of
    // the media component, assigned
    MediaComponentNumber mcn2(10);
    flows.setMediaComponentNumber(mcn2);

    // [2.2.2.4] The Flow-Grouping AVP (AVP code 508) is of type Grouped,
    // and it indicates that no other IP Flows shall be transported together
    // with the listed IP Flows in the same PDP context(s).
    FlowGrouping flowGrouping;
    flowGrouping.addFlows(flows);

    // [2.2.2] set FlowGrouping to AA Request object
    aaReq.addFlowGrouping(flowGrouping);

    aaReq.setReservationPriority(reservationPriority);

       // [2.1.2.6] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    aaReq.setUserName(userName);

    // This information element contains:
    // The IP address of the user equipment used by the subscriber for which
    // profile information is being pushed.( i.e contains a Frame-IP-Address
    // or Frame-IPv6-Prefix AVP value, and an Address-Realm AVP).
    // The addressing domain in which the IP address is significant.(i.e Address-Realm AVP).
    GloballyUniqueAddress gua ;
    string ipAddress;

    // [2.2.5.2] The Framed-IP-Address AVP (AVP Code 8) [RADIUS]
    // is of type OctetString and contains an IPv4 address
    cout<<"Please enter IP Address "<<endl;
    cin>>ipAddress; 
    FramedIPAddress faddr(ipAddress);
    gua.setFramedIPAddress(faddr);

    // [2.2.5.4] The Framed-IPv6-Prefix AVP (AVP Code 97) is
    // of type OctetString and contains the IPv6 prefix to be
    // configured for the user
    FramedIPv6Prefix fpre("10.1.1.2");
    gua.setFramedIPv6Prefix(fpre);

    // The Address-Realm AVP (AVP code 301) is of type OctetString.
    AddressRealm addressRealm("india.internal.net");
    gua.setAddressRealm(addressRealm);

    aaReq.setGloballyUniqueAddress(gua);

    // The Authorization-Lifetime AVP (AVP Code 291) is of type Unsigned32
    // and contains the maximum number of seconds of service to be provided
    // to the user before the user is to be re-authenticated and/or re-
    // authorized.  Great care should be taken when the Authorization-
    // Lifetime value is determined, since a low, non-zero, value could
    // create significant Diameter traffic, which could congest both the
    // network and the agents.
    AuthorizationLifetime  authorizationLifetime(40u);
    aaReq.setAuthorizationLifetime(authorizationLifetime);

    // These two AVPs are set by the stack.
    // and application should not set those.
    // aaReq.addProxyInfo(ProxyInfo(...));
    // aaReq.addRouteRecord(RouteRecord(...));
    // add more AVP as ANY values

    if (appMode == UNIT_TEST)
    cout<<aaReq;

    // Send encoded message to stack.
    SendDiaAppMsg(aaReq, sIdx);
    RqStats::GetRqStats()->UpdateSendStats(aaReq.getCommandCode(), ITS_TRUE);

    return ITS_SUCCESS;

}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the AA Answer to the
 *      diameter stack. Creates the AA Answer object,
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
int SendRqAAAnswer(const CommandImpl *impl) 
{
    //[ 1] Create an instance of AAAnswer class
    // The AA-Answer command is sent by a Diameter
    // server to a Diameter client in order to request deregistration
    // Command-Code = 265 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::rq::AAAnswer aaAns;

    // Create an instance of AARequest class 
    AARequest aareq(*impl);

    // Get the some AVP values and set them to Answer Message
    const SessionId& sid = aareq.getSessionId();
    const OriginHost& oh = aareq.getOriginHost();
    const OriginRealm& or1 = aareq.getOriginRealm();
    const DestinationRealm& dr = aareq.getDestinationRealm();
    const AuthApplicationId& aaid1 = aareq.getAuthApplicationId();

    // Fixed AVP

    // [2] Insert data in the created AAAnswer object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed paramete "Session-Id".
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    aaAns.setSessionId(sid);

    aaAns.setSessionIndex(aareq.getSessionIndex());

    // Required AVPs

    // [2.1.2] Populate required Manatories.
    // [2.1.2.1] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    aaAns.setAuthApplicationId(aaid1);

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
    aaAns.setOriginHost(origh);

    // [2.1.2.3] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origrealm(dr.value());
    aaAns.setOriginRealm(origrealm);

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
    ResultCode resultCode(2001u);
    aaAns.setResultCode(resultCode);

    // [2.2.2.1] Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // ResultCode AVP is already been set, we dont need to set this.
    ExperimentalResult experimentResult;

    // [2.2.2.2] Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    VendorId vid(VENDOR_ID);
    experimentResult.setVendorId(vid);

    // [2.2.2.3] Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    ExperimentalResultCode erc(100);
    experimentResult.setExperimentalResultCode(erc);

    // [2.2.2]Set the ExperimentalResult AVP
    aaAns.setExperimentalResult(experimentResult);

    // The Auth-Grace-Period AVP (AVP Code 276) is of type Unsigned32 and
    // contains the number of seconds the Diameter server will wait
    // following the expiration of the Authorization-Lifetime AVP before
    // cleaning up resources for the session.
    AuthGracePeriod authGracePeriod(10u);
    aaAns.setAuthGracePeriod(authGracePeriod);

    // The Session-Bundle-Id (AVP code 400) is of type Unsigned32. It may be
    // specified by the A-RACF in the AA-Answer, when the initial reservation
    // is granted, in order to identify the group of sessions to which the session
    // of the AA-Answer belongs. The value of the Session-Bundle-Id AVP is
    // meaningful for the A-RACF only. It may be included by the A-RACF in
    // subsequent Abort-Session-Request (ASR) messages sent to the SPDF. 
    SessionBundleId sessionBundleId(12345u);
    aaAns.addSessionBundleId(sessionBundleId);

    // The Reservation-Priority AVP (AVP code 458) is of type Enumerated. It may
    // be specified in an AA-Request as a main AVP in order to associate a priority
    // with a resource reservation or modification request. It may also be specified
    // as part of a Media-Component AVP in order to associate a priority with
    // resource reservations requested for the media flows identified by the Media-
    // Sub-Component AVP(s) in a Media-Component AVP.
    ReservationPriority reservationPriority(ReservationPriority::DEFAULT);
    aaAns.setReservationPriority(reservationPriority);
 
    // The Authorization-Lifetime AVP (AVP Code 291) is of type Unsigned32
    // and contains the maximum number of seconds of service to be provided
    // to the user before the user is to be re-authenticated and/or re-
    // authorized.  Great care should be taken when the Authorization-
    // Lifetime value is determined, since a low, non-zero, value could
    // create significant Diameter traffic, which could congest both the
    // network and the agents.
    AuthorizationLifetime  authorizationLifetime(50u);
    aaAns.setAuthorizationLifetime(authorizationLifetime);

    // These AVPS should not be set by application.
    // aaAns.setErrorMessage(ErrorMessage(...));
    // aaAns.setErrorReportingHost(ErrorReportingHost(...));
    // aaAns.addFailedAVP(FailedAVP(...));
    // aaAns.addProxyInfo(ProxyInfo(...));
    // add more AVP as ANY values
 
    if (appMode == UNIT_TEST)
    cout<<aaAns; 

    // Send Encoded message to stack.
    SendDiaAppMsg(aaAns, sIdx);
    RqStats::GetRqStats()->UpdateSendStats(aaAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;


}
