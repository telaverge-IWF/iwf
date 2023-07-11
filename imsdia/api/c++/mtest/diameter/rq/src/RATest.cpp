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
 * LOG: $Log: RATest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:11  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/01/08 07:41:35  hbhatnagar
 * LOG: baseline demo application for rq interface for static and distributed mode.
 * LOG:
 *
 * ID: $Id: RATest.cpp,v 3.1 2008/03/31 10:33:11 nvijikumar Exp $
 ****************************************************************************/
#include <app.h>
#include <rq_defines.h>
#include <rq_stats.h>
#include <diameter/rq/RA.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::rq;

extern string sessIdString;
extern ITS_UINT sIdx;

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the RA raReq to the
 *      diameter stack. Creates the RA Request object,
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
int SendRqRARequest() 
{

    // [1] Create an instance of RARequest class
    // The RA-Request command is sent by a Diameter
    // client to a Diameter Server in order to raReq deregistration
    // Command-Code = 258
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::rq::RARequest raReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    cout << "Please enter the Session ID to Re-Authorize" << endl;
    cin >> sessIdString;
    raReq.setSessionId(SessionId(sessIdString));

    raReq.setSessionIndex(sIdx);

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter  messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost orighost(GetOriginHost());
    raReq.setOriginHost(orighost);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origrealm(GetOriginRealm());
    raReq.setOriginRealm(origrealm);

    // [2.1.2.3] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destRealm(GetDestinationRealm());
    raReq.setDestinationRealm(destRealm);

    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destHost(GetDestinationHost());
    raReq.setDestinationHost(destHost);

    // [2.1.2.5] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authAppId(RQ_INTERFACE_APP_ID);
    raReq.setAuthApplicationId(authAppId);

    // The Specific-Action AVP (AVP code 513) is of type Enumerated.
    // The following values are defined for this AVP
    // SERVICE_INFORMATION_REQUEST
    // CHARGING_CORRELATION_EXCHANGE
    // INDICATION_OF_LOSS_OF_BEARER
    // INDICATION_OF_RECOVERY_OF_BEARER
    // INDICATION_OF_RELEASE_OF_BEARER
    // INDICATION_OF_ESTABLISHMENT_OF_BEARER
    SpecificAction specAction(SpecificAction::INDICATION_OF_RELEASE_OF_BEARER);
    raReq.addSpecificAction(specAction);

    // [2.2.3.1] The Flows AVP (AVP code 510) is of type Grouped, 
    // and it indicates IP flows via their flow identifiers
    Flows flows;

    // [2.2.3.2] The Flow-Number AVP (AVP code 509) is of type Unsigned32,
    // and it contains the ordinal number of the IP flow(s),
    FlowNumber flowNumber(10);
    flows.addFlowNumber(flowNumber);

    //  [2.2.3.3] The Media-Component-Number AVP (AVP code 518) is of
    // type Unsigned32, and it contains the ordinal number of
    // the media component, assigned
    MediaComponentNumber mcn(10);
    flows.setMediaComponentNumber(mcn);

    // [2.2.3] Set the Flows AVP to RA Request Message
    raReq.addFlows(flows);

    // [2.2.4] The Session-Abort-Cause AVP (AVP code 500) is of type 
    // Enumerated, and determines the cause of a session abort request.
    //  The following values are defined:
    // BEARER_RELEASED
    // INSUFFICIENT_SERVER_RESOURCES
    // INSUFFICIENT_BEARER_RESOURCES
    AbortCause abortCause(AbortCause::INSUFFICIENT_SERVER_RESOURCES);
    raReq.setAbortCause(abortCause);

    // [2.2.5] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     
    // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId originStateId(40);
    raReq.setOriginStateId(originStateId);

    // These AVP should not be set by the Application.
    // raReq.addProxyInfo(ProxyInfo(...));
    // raReq.addRouteRecord(RouteRecord(...));
    // add more AVP as ANY values
   
    cout<<raReq;
    SendDiaAppMsg(raReq, sIdx);
    RqStats::GetRqStats()->UpdateSendStats(raReq.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the RA Answer to the
 *      diameter stack. Creates the RA Answer object,
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
int SendRqRAAnswer(const CommandImpl *impl) 
{
    // [1]. Create an instance of  RA Answer class
    // The RA-Answer command is sent by a Diameter
    // server to a Diameter client in order to request deregistration
    // Command-Code = 258 
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::rq::RAAnswer raAns;

    // Create an instance of  RA Request class 
    RARequest rareq(*impl);

    // Get AVP values from Request and set them to Answer Message
    const SessionId& sid = rareq.getSessionId();
    const OriginHost& oh = rareq.getOriginHost();
    const OriginRealm& or1 = rareq.getOriginRealm();
    const DestinationHost& dh = rareq.getDestinationHost();
    const DestinationRealm& dr = rareq.getDestinationRealm();
    const OriginStateId& osid = rareq.getOriginStateId();

    // [2.1.1.x] Fixed AVP

    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    raAns.setSessionId(sid);

    raAns.setSessionIndex(sIdx);

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost origHost(dh.value());
    raAns.setOriginHost(origHost);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origRealm(dr.value());
    raAns.setOriginRealm(origRealm);

    // [2.2.x] Optional AVPs

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
    raAns.setResultCode(resultCode);

    // [2.2.2.1] Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // ResultCode AVP is already been set.
    ExperimentalResult er1;

    // [2.2.2.2] Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    VendorId vid(VENDOR_ID);
    er1.setVendorId(vid);

    // [2.2.2.3] Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    ExperimentalResultCode erc(2001);
    er1.setExperimentalResultCode(erc);

    // [2.2.2] set ExperimentalResult AVP 
    // Already ResultCode AVP is set, not required to set
    // ExperimentalResult.
    raAns.setExperimentalResult(er1);

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
    raAns.addMediaComponentDescription(mediaComponentDescription);

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
    raAns.addFlowGrouping(flowGrouping);

    // [2.2.5] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     
    // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    raAns.setOriginStateId(osid);

    // [2.2.6] The Error-Message AVP (AVP Code 281) is of type UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message
    // Application should not set this.
    // ErrorMessage erm("server problem");
    // raAns.setErrorMessage(erm);

    // [2.2.7] The Error-Reporting-Host AVP (AVP Code 294) is of type
    // DiameterIdentity.  This AVP contains the identity of the Diameter
    // host that sent the Result-Code AVP
    // Application should not set this.
    // ErrorReportingHost erh("abc.def.com");
    // raAns.setErrorReportingHost(erh);

    // [2.2.8] Set Failed AVP
    // Application should not set this.
    // FailedAVP fa;
    // raAns.addFailedAVP(fa);

    // ProxyInfo AVP should not be set by the Application.
    // answer.addProxyInfo(ProxyInfo(...));
    // add more AVP as ANY values

    cout<<raAns;
    SendDiaAppMsg(raAns, sIdx);
    RqStats::GetRqStats()->UpdateSendStats(raAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;

}
