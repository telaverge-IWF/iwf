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
 * LOG: Revision 3.1  2008/03/31 10:33:13  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.4  2006/12/22 10:15:05  nvijikumar
 * LOG: Passing correct appId for AllocateSession API.
 * LOG:
 * LOG: Revision 2.3  2006/12/19 08:54:50  kamakshilk
 * LOG: New architecture to work with static and distributed.
 * LOG:
 * LOG: Revision 2.2  2006/10/16 15:08:01  kamakshilk
 * LOG: Merging with ITSDiameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/07/25 04:56:35  kamakshilk
 * LOG: Baseline demo application for Tx Interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: AATest.cpp,v 3.1 2008/03/31 10:33:13 nvijikumar Exp $
 ****************************************************************************/
#include <app.h>
#include <tx_defines.h>
#include <tx_stats.h>
#include <diameter/tx/AA.h>
                                                                                
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::tx;

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
int SendTxAARequest()
{
    // [1] Create an instance of AARequest.
    AARequest aareq(false,false);

    // [2] Insert data in the created AARequest object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter
    // Header.The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    AllocateSession(TX_INTERFACE_APP_ID, sIdx, sessIdString);
    aareq.setSessionId(SessionId(sessIdString));

    aareq.setSessionIndex(sIdx);

    // [2.1.2] Populate Mandatories which can appear anywhere.

    // [2.1.2.1] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP shall contain the value of TBD as defined in X-S0013-013-0.
    // The AVP code of Auth-Application-Id is 258.
    AuthApplicationId authApplicationId(TX_INTERFACE_APP_ID);
    aareq.setAuthApplicationId(authApplicationId);

    // [2.1.2.2] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost originHost(GetOriginHost());
    aareq.setOriginHost(originHost);
                                                                                
    // [2.1.2.3] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter
    // message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm originRealm(GetOriginRealm());
    aareq.setOriginRealm(originRealm);

    // [2.1.2.4] Populate required parameter "Destination-Realm".
    // Set the Destination-Realm AVP.
    // The data type of Destination-Realm is DiameterIdentity.
    // This AVP contains the Realm the message is to be routed to.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Destination-Realm is 283.
    DestinationRealm destinationRealm(GetDestinationRealm());
    aareq.setDestinationRealm(destinationRealm);
    
    // [2.2] Populate Optionals.

    // [2.2.1] Populate optional(multiple occurence) parameter
    //         Media-Component-Description.
    // Set the Media-Component-Description AVP.
    // The data type of Media-Component-Description is Grouped.
    // This contains service information for a single media component within an
    // AF session.It may be based on the SDI exchanged between AF and AF client
    // in UE.
    // The AVP Code of Media-Component-Description is 517.
    MediaComponentDescription mediaCompDescrp1;

    // [2.2.1.1] Populate "Media-Component-Description" grouped AVPs.
    PopulateMediaComponentDescription(mediaCompDescrp1);
                                                                                
    // [2.2.1.2] Add "Media-Component-Description" AVP to AAR object.
    aareq.addMediaComponentDescription(mediaCompDescrp1);

    // [2.2.2] Populate optional(multiple occurence) parameter
    //         Flow-Grouping.
    // The data type of Flow-Grouping is Grouped.
    // This  indicates that no other IP Flows shall be transported together 
    // with the listed IP Flows in the same bearer(s).
    // The AVP Code of Flow-Grouping is 508.
    FlowGrouping flowGrouping1;
    
    // [2.2.2.1] Populate "Flow-Grouping" grouped AVPs.
 
    // [2.2.2.1.1] Populate optional(multiple occurence) parameter
    //         Flows.
    // The data type of Flows is Grouped.
    // This indicates IP flows via their flow identifiers. If no Flow-Number 
    // AVP(s) are supplied, the Flows AVP refers to all Flows matching the 
    // media component number.
    // The AVP Code of Flows is 510.
    Flows flows;

    // [2.2.2.1.1.1] Populate "Flows" grouped AVPs.
    PopulateFlows(flows);

    // [2.2.2.1.1.2] Set "Flows" AVP in Flow-Grouping object.
    flowGrouping1.addFlows(flows);
    
    // [2.2.2.2] Set "Flow-Grouping" AVP in AAR object.
    aareq.addFlowGrouping(flowGrouping1);

    // [2.2.3] Populate optional parameter AF-Charging-Identifier.
    // The data type of AF-Charging-Identifier is OctetString.
    // This contains the AF Charging Identifier that is sent by the AF. This
    // information may be used for charging correlation with bearer layer.
    // The AVP Code of AF-Charging-Identifier is 505.
    AFChargingIdentifier afChargingId("54");
    aareq.setAFChargingIdentifier(afChargingId);

    // [2.2.4] Populate optional parameter SIP-Forking-Indication.
    // The data type of SIP-Forking-Indication is Enumerated.
    // This describes if several SIP dialogues are related to one Diameter 
    // session.
    // The AVP Code of SIP-Forking-Indication is 523.
    SIPForkingIndication sipForkInd(SIPForkingIndication::SINGLE_DIALOGUE);
    aareq.setSIPForkingIndication(sipForkInd);

    // [2.2.5] Populate optional(multiple occurence) parameter Specific-Action.
    // The data type of Specific-Action is Enumerated.
    // Within a PCRF initiated Re-Authorization Request,the Specific-Action AVP
    // determines the type of the action.
    // Within an initial AA request the AF may use the Specific-Action AVP to
    // request specific actions from server at the bearer events and to limit 
    // the contact to such bearer events where specific action is required. If 
    // the Specific-Action AVP is omitted within the initial AA request,no 
    // notification of any of the events defined below is requested.
    // The AVP Code of Specific-Action is 513.
    SpecificAction spefcActn1(SpecificAction::CHARGING_CORRELATION_EXCHANGE);
    aareq.addSpecificAction(spefcActn1);

    // [2.2.5] Populate optional parameter Subscription-Id.
    // The data type of Subscription-Id is Grouped.
    // This is used to identify the end user's subscription.
    // The AVP Code of Subscription-Id is 443.
    SubscriptionId subscrId1;
    PopulateSubscriptionId(subscrId1);
    aareq.addSubscriptionId(subscrId1);

    //    aareq.addProxyInfo(proxyInfo)
    //    aareq.addRouteRecord(routeRecord);

#if 0
    //Creating AVP of OctetString Type
    OctetStringAvp extAvpOct(1200, "My OctetString");
    aareq.addExtra(extAvpOct);
                                                                             
    //Creating AVP of Integer32 Type
    Integer32Avp extAvpInt32(1201, 1986030359);
    aareq.addExtra(extAvpInt32);
                                                                                
    //Creating AVP of Integer64 Type
    Integer64Avp extAvpInt64(1202, 12233708);
    aareq.addExtra(extAvpInt64);
#endif
    
    if (appMode == UNIT_TEST)
    cout << "AAR" << aareq;

    // Send Encoded Message to the Stack.
    SendDiaAppMsg(aareq, sIdx);
    TxStats::GetTxStats()->UpdateSendStats(aareq.getCommandCode(), ITS_TRUE);
                                                                                
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
int SendTxAAAnswer(const CommandImpl * impl1)
{
    // [1] Create AAAnswer object.
    AAAnswer aaans(false,false);
                                                                                
    // [1.1] Create an instance of AARequest class with recived event.
    AARequest aareq(*impl1);

    // [2.1] Populate Mandatories.

    // [2.1.1] Populate Fixed Mandatories.

    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    const SessionId& sessionId = aareq.getSessionId();
    aaans.setSessionId(sessionId);

    aaans.setSessionIndex(aareq.getSessionIndex());

    // [2.1.2] Populate Mandatories which can appear anywhere.

    // [2.1.2.1] Populate required parameter "Auth-Application-Id".
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP shall contain the value of TBD as defined in X-S0013-013-0.
    // The AVP code of Auth-Application-Id is 258.
    AuthApplicationId authApplicationId(TX_INTERFACE_APP_ID);
    aaans.setAuthApplicationId(authApplicationId);

    // [2.1.2.2] Populate required parameter "Origin-Host".
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter
    // message.
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost originHost(GetOriginHost());
    aaans.setOriginHost(originHost);
                                                                                
    // [2.1.2.3] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm originRealm(GetOriginRealm());
    aaans.setOriginRealm(originRealm);

    // [2.2] Populate Optional AVPs.

    // [2.2.1] Populate optional parameter "Result-Code".
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    ResultCode resultCode(2001u);
    aaans.setResultCode(resultCode);

    // [2.2.2] Create the Experimental-Result AVP
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

    // [2.2.3] Populate optional parameter Authorization-Token.
    // The data type of Authorization-Token is OctetString.
    // This contains the Authorization Token defined in the RFC 3520.
    // The AVP Code of Authorization-Token is 506.
    // This AVP is not used in this release, Version 1.0
//    AuthorizationToken authToken("abcd");
//    aaans.setAuthorizationToken(authToken);

    // [2.2.4] Populate optional(multiple occurence) parameter 
    //         Access-Network-Charging-Identifier.
    // The data type of Access-Network-Charging-Identifier is Grouped.
    // This contains a charging identifier within the Access-Network-Charging-
    // Identifier-Value AVP along with information about the flows transported
    // within the corresponding bearer within the Flows AVP. If no Flows AVP is
    // provided, the Access-Network-Charging-Identifier-Value applies for all
    // flows within the AF session.
    // The AVP Code of Access-Network-Charging-Identifier is 502.
    AccessNetworkChargingIdentifier accNwChargingId1; 
    
    // [2.2.4.1] Populate "Access-Network-Charging-Identifier" grouped AVPs.
    PopulateAccessNetworkChargingIdentifier(accNwChargingId1);
                                                                                
    // [2.2.4.2] Add "Access-Network-Charging-Identifier" AVP to AAA object.
    aaans.addAccessNetworkChargingIdentifier(accNwChargingId1);

    // [2.2.5] Populate optional parameter Access-Network-Charging-Address.
    // The data type of Access-Network-Charging-Address is Address.
    // This indicates the IP Address of the network entity within the access
    // network performing charging(e.g.PDSN IPaddress). The Access-Network-
    // Charging-Address AVP should not be forwarded over an inter-operator 
    // interface.
    // The AVP Code of Access-Network-Charging-Address is 501.
    Address addrChrg(Address::IPV4, "192.168.7.6");
    AccessNetworkChargingAddress accNwChargingAddr(addrChrg);
    aaans.setAccessNetworkChargingAddress(accNwChargingAddr);

    // [2.2.6] Populate optional parameter Error-Message.
    // The data type of Error-Message is UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message. 
    // The Error-Message AVP is not intended to be useful in real-time, and
    // SHOULD NOT be expected to be parsed by network entities.
    // The AVP Code of Error-Message is 281.
    ErrorMessage errMsg("success");
    aaans.setErrorMessage(errMsg);

    // [2.2.7] Populate optional parameter Error-Reporting-Host.
    // The data type of Error-Reporting-Host is DiameterIdentity.
    // This AVP contains the identity of the Diameter host that sent the 
    // Result-Code AVP to a value other than 2001(Success), only if the host 
    // setting the Result-Code is different from the one encoded in the 
    // Origin-Host AVP.  This AVP is intended to be used for troubleshooting 
    // purposes, and MUST be set when the Result-Code AVP indicates a failure.
    // The AVP Code of Error-Reporting-Host is 294.
    //    ErrorReportingHost errRptHost();
    //    aaans.setErrorReportingHost(errRptHost);

    //    FailedAVP
    //    aaans.addFailedAVP();

    //aaans.addProxyInfo(proxyInfo);

    if (appMode == UNIT_TEST)                                                   
    cout << "AAA" << aaans;

    // Send encoded message to stack.
    SendDiaAppMsg(aaans, sIdx);
    TxStats::GetTxStats()->UpdateSendStats(aaans.getCommandCode(), ITS_FALSE);
                                                                                
    return (ITS_SUCCESS);
}


/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Media-Component-Description
 *      grouped AVP.
 *      This populate the grouped AVPs and sets the values in the
 *      MediaComponentDescription object passed as a reference to this
 *      function.
 *
 *  Input Parameters:
 *      MediaComponentDescription &mediaCompDescrp: Refernce to the 
 *      MediaComponentDescription object, the grouped AVP of which needs to 
 *      be set.
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
void PopulateMediaComponentDescription(MediaComponentDescription 
                                        &mediaCompDescrp)
{
    // [1] Populate "Media-Component-Description" grouped AVPs.
                                                                                
    // [1.1] Populate mandatory AVPs.

    // [1.1.1] Populate required parameter Media-Component-Number.
    // The data type of Media-Component-Number is Unsigned32.
    // This contains the ordinal number of the media component, assigned 
    // according to the rules in annex A of 3GPP2 X.S0013-013-0.
    // The AVP Code for Media-Component-Number is 518.
    MediaComponentNumber mediaCompNum(5);
    mediaCompDescrp.setMediaComponentNumber(mediaCompNum);

    // [1.2] Populate optional AVPs.

    // [1.2.1] Populate optional parameter(multiple occurence) 
    //         Media-Sub-Component.
    // The data type of Media-Sub-Component is Grouped.
    // This contains the requested QoS and filters for the set of IP flows 
    // identified by their common Flow-Identifier.
    // The AVP Code for Media-Sub-Component is 519.
    MediaSubComponent mediaSubComp1;

    // [1.2.1.1] Populate "Media-Sub-Component" grouped AVPs.
    PopulateMediaSubComponent(mediaSubComp1);
                                                                                
    // [1.2.1.2] Add "Media-Sub-Component" AVP to Media-Component-Description 
    //                object
    mediaCompDescrp.addMediaSubComponent(mediaSubComp1);

    // [1.2.2] Populate optional parameter AF-Application-Identifier.
    // The data type of AF-Application-Identifier is OctetString.
    // This contains information that identifies the particular service that 
    // the AF service session belongs to. This information may be used by the 
    // PCRF to differentiate QoS for different application services.
    // The AVP Code for AF-Application-Identifier is 504.
    AFApplicationIdentifier afAppId("234");
    mediaCompDescrp.setAFApplicationIdentifier(afAppId);

    // [1.2.3] Populate optional parameter Media-Type.
    // The data type of Media-Type is Enumerated.
    // This determines the media type of a session component.
    // The AVP Code for Media-Type is 520.
    MediaType mediaType(MediaType::VIDEO);
    mediaCompDescrp.setMediaType(mediaType);

    // [1.2.4] Populate optional parameter Max-Requested-Bandwidth-UL.
    // The data type of Max-Requested-Bandwidth-UL is Unsigned32.
    // This indicates the maximum requested bandwidth in bits per second for an
    // uplink IP flow. The bandwidth contains all the overhead coming from the
    // IP-layer and the layers above, e.g. IP, UDP, RTP and RTP payload
    // The AVP Code for Max-Requested-Bandwidth-UL is 516.
    MaxRequestedBandwidthUL maxBwUL(64);
    mediaCompDescrp.setMaxRequestedBandwidthUL(maxBwUL);

    // [1.2.5] Populate optional parameter Max-Requested-Bandwidth-DL.
    // The data type of Max-Requested-Bandwidth-DL is Unsigned32.
    // This indicates the maximum requested bandwidth in bits per second for a
    // downlink IP flow.The bandwidth contains all the overhead coming from the
    // IP-layer and the layers above, e.g. IP, UDP, RTP and RTP payload
    // The AVP Code for Max-Requested-Bandwidth-DL is 515.
    MaxRequestedBandwidthDL maxBwDL(64);
    mediaCompDescrp.setMaxRequestedBandwidthDL(maxBwDL);

    // [1.2.6] Populate optional parameter Flow-Status.
    // The data type of Flow-Status is Enumerated.
    // This describes whether the IP flow(s) are enabled or disabled.
    // The AVP Code for Flow-Status is 511.
    FlowStatus flowStatus(FlowStatus::ENABLED_UPLINK);
    mediaCompDescrp.setFlowStatus(flowStatus);

    // [1.2.7] Populate optional parameter RS-Bandwidth.
    // The data type of RS-Bandwidth is Unsigned32.
    // This indicates the maximum required bandwidth in bits per second for 
    // RTCP sender reports within the session component, as specified in RFC
    // 3556. The bandwidth contains all the overhead coming from the IP-layer
    // and the layers above, i.e. IP, UDP and RTCP.
    // The AVP Code for RS-Bandwidth is 522.
    RSBandwidth rsBw(8000);
    mediaCompDescrp.setRSBandwidth(rsBw);
    
    // [1.2.8] Populate optional parameter RR-Bandwidth.
    // The data type of RR-Bandwidth is Unsigned32.
    // This indicates the maximum required bandwidth in bits per second for 
    // RTCP receiver reports within the session component, as specified in RFC
    // 3556. The bandwidth contains all the overhead coming from the IP-layer 
    // and the layers above, i.e.IP, UDP and RTCP.
    // The AVP Code for RR-Bandwidth is 521.
    RRBandwidth rrBw(8000);
    mediaCompDescrp.setRRBandwidth(rrBw);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Media-Sub-Component grouped AVP.
 *      This populate the grouped AVPs and sets the values in the
 *      MediaSubComponent object passed as a reference to this
 *      function.
 *
 *  Input Parameters:
 *      MediaSubComponent &mediaSubComp: Refernce to the MediaSubComponent 
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
void PopulateMediaSubComponent(MediaSubComponent &mediaSubComp)
{
    // [1] Populate "Media-Sub-Component" grouped AVPs.
                                                                                
    // [1.1] Populate mandatory AVPs.

    // [1.1.1] Populate required parameter Flow-Number.
    // The data type of Flow-Number is Unsigned32.
    // This contains the ordinal number of the IP flow(s), assigned according 
    // to the rules in annex A of 3GPP2 X.S0013-013-0.
    // The AVP Code for Flow-Number is 509.
    FlowNumber flowNum(5);
    mediaSubComp.setFlowNumber(flowNum);

    // [1.2] Populate optional AVPs.
                                                                                
    // [1.2.1] Populate optional parameter Flow-Description.
    // The data type of Flow-Description is IPFilterRule.
    // This defines a packet filter for an IP flow with the following 
    // information:
    // --Direction (in or out).
    // --Source and destination IP address (possibly masked).
    // --Protocol.
    // --Source and destination port (list or ranges).
    // The AVP Code for Flow-Description is 507.
    IPFilterRule ipFltRule;
    PopulateIPFilterRule(ipFltRule);
    FlowDescription flowDescrp1(ipFltRule);
    mediaSubComp.addFlowDescription(flowDescrp1);

    // [1.2.2] Populate optional parameter Flow-Status.
    // The data type of Flow-Status is Enumerated.
    // This describes whether the IP flow(s) are enabled or disabled.
    // The AVP Code for Flow-Status is 511.
    FlowStatus flowStatus(FlowStatus::ENABLED_UPLINK);
    mediaSubComp.setFlowStatus(flowStatus);

    // [1.2.3] Populate optional parameter Flow-Usage.
    // The data type of Flow-Usage is Enumerated.
    // This provides information about the usage of IP Flows.
    // NO_INFORMATION is the default value.
    // NOTE: An AF may choose not to identify RTCP flows, e.g. in order to 
    // avoid that RTCP flows are always enabled by the server.
    // The AVP Code for Flow-Usage is 512.
    FlowUsage flowUsage(FlowUsage::RTCP);
    mediaSubComp.setFlowUsage(flowUsage);

    // [1.2.4] Populate optional parameter Max-Requested-Bandwidth-UL.
    // The data type of Max-Requested-Bandwidth-UL is Unsigned32.
    // This indicates the maximum requested bandwidth in bits per second for an
    // uplink IP flow. The bandwidth contains all the overhead coming from the
    // IP-layer and the layers above, e.g. IP, UDP, RTP and RTP payload
    // The AVP Code for Max-Requested-Bandwidth-UL is 516.
    MaxRequestedBandwidthUL maxBwUL(64);
    mediaSubComp.setMaxRequestedBandwidthUL(maxBwUL);

    // [1.2.5] Populate optional parameter Max-Requested-Bandwidth-DL.
    // The data type of Max-Requested-Bandwidth-DL is Unsigned32.
    // This indicates the maximum requested bandwidth in bits per second for a
    // downlink IP flow.The bandwidth contains all the overhead coming from the
    // IP-layer and the layers above, e.g. IP, UDP, RTP and RTP payload
    // The AVP Code for Max-Requested-Bandwidth-DL is 515.
    MaxRequestedBandwidthDL maxBwDL(64);
    mediaSubComp.setMaxRequestedBandwidthDL(maxBwDL);

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
    ByteRange icmpRng(3,13);
    ipFltRule.icmpTypeRangeList.push_front(icmpRng);
                                                                                
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Flows grouped AVP.
 *      This populate the grouped AVPs and sets the values in the
 *      Flows object passed as a reference to this
 *      function.
 *
 *  Input Parameters:
 *      Flows &flows: Refernce to the Flows object, the grouped AVP of which 
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
void PopulateFlows(Flows &flows)
{
    // [1] Populate "Flows" grouped AVPs.
                                                                                
    // [1.1] Populate mandatory AVPs.
    
    // [1.1.1] Populate required parameter Media-Component-Number.
    // The data type of Media-Component-Number is Unsigned32.
    // This contains the ordinal number of the media component, assigned 
    // according to the rules in annex A of 3GPP2 X.S0013-013-0.
    // The AVP Code for Media-Component-Number is 518.
    MediaComponentNumber mediaCompNum(3);
    flows.setMediaComponentNumber(mediaCompNum);

    // [1.2] Populate optional AVPs.

    // [1.2.1] Populate optional (multiple occurence) parameter Flow-Number.
    // The data type of Flow-Number is Unsigned32.
    // This contains the ordinal number of the IP flow(s), assigned according 
    // to the rules in annex A of 3GPP2 X.S0013-013-0.
    // The AVP Code for Flow-Number is 509.
    FlowNumber flowNum1(3);
    flows.addFlowNumber(flowNum1);

}


/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Subscription-Id grouped AVP.
 *      This populate the grouped AVPs and sets the values in the
 *      Flows object passed as a reference to this
 *      function.
 *
 *  Input Parameters:
 *      SubscriptionId &subscriptionId: Refernce to the Subscription-Id object,
 *      the grouped AVP of which needs to be set.
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
void PopulateSubscriptionId(SubscriptionId &subscriptionId)
{
    // [1] Populate "Subscription-Id" grouped AVPs.
                                                                                
    // [1.1] Populate mandatory AVPs.

    // [1.1.1] Populate required parameter Subscription-Id-Type.
    // The data type of Subscription-Id-Type is Enumerated.
    // This is used to determine which type of identifier is carried by the 
    // Subscription-Id AVP.
    // The AVP Code for Subscription-Id-Type is 450.
    SubscriptionIdType subsType(SubscriptionIdType::END_USER_IMSI);
    subscriptionId.setSubscriptionIdType(subsType);

    // [1.1.2] Populate required parameter Subscription-Id-Data.
    // The data type of Subscription-Id-Data is Enumerated.
    // This is used to identify the end user. 
    // The AVP Code for Subscription-Id-Data is 444.
    SubscriptionIdData subsData("09108025211852");
    subscriptionId.setSubscriptionIdData(subsData);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the Access-Network-Charging-Identifier
 *           grouped AVP.
 *      This populate the grouped AVPs and sets the values in the
 *      AccessNetworkChargingIdentifier object passed as a reference to this
 *      function.
 *
 *  Input Parameters:
 *      AccessNetworkChargingIdentifier &accNwChargingId: Refernce to the 
 *      Access-Network-Charging-Identifier object,the grouped AVP of which 
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
void PopulateAccessNetworkChargingIdentifier(AccessNetworkChargingIdentifier 
                                              &accNwChargingId)
{
    // [1] Populate "Access-Network-Charging-Identifier" grouped AVPs.
                                                                                
    // [1.1] Populate mandatory AVPs.

    // [1.1.1] Populate required parameter 
    //         Access-Network-Charging-Identifier-Value.
    // The data type of Access-Network-Charging-Identifier-Value is OctetString.
    // This contains a charging identifier.
    // The AVP Code for Access-Network-Charging-Identifier-Value is 503.
    AccessNetworkChargingIdentifierValue accNwChIdVal("55");
    accNwChargingId.setAccessNetworkChargingIdentifierValue(accNwChIdVal);
    
    // [1.2] Populate optional AVPs.

    // [1.2.1] Populate optional(multiple occurence) parameter
    //         Flows.
    // The data type of Flows is Grouped.
    // This indicates IP flows via their flow identifiers. If no Flow-Number 
    // AVP(s) are supplied, the Flows AVP refers to all Flows matching the 
    // media component number.
    // The AVP Code of Flows is 510.
    Flows flows;

    // [1.2.1.1] Populate "Flows" grouped AVPs.
    PopulateFlows(flows);

    // [1.2.1.2] Set "Flows" AVP in Access-Network-Charging-Identifier object. 
    accNwChargingId.addFlows(flows);

}
