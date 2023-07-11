/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2010 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: Revision 1.3  2011/07/22 11:49:46  rajeshak
 * LOG: Proxy Changes for RX Interface
 * LOG:
 * LOG: Revision 1.2  2010/12/02 14:52:09  nvijikumar
 * LOG: Added IPFilterRule AVP
 * LOG:
 * LOG: Revision 1.1  2010/07/29 09:17:44  nvijikumar
 * LOG: RX sample app for TS29214 support
 * LOG:
 * LOG:
 *
 * ID: $Id: AATest.cpp,v 1.3 2011/07/22 11:49:46 rajeshak Exp $
 ****************************************************************************/
#include <app.h>
#include <rx_defines.h>
#include <rx_stats.h>
#include <diameter/rx_ts29214/AA.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::rx_ts29214;

string sessIdString;
ITS_UINT sIdx;

void PopulateIPFilterRule(IPFilterRule &ipFltRule)
{
    // [1] Populate "IPFilterRule" object fields.

    ipFltRule.action = IPFilterRule::PERMIT;
    ipFltRule.dir = IPFilterRule::IN;
    ipFltRule.proto = 0;
    // Value 0 means wildcard number that matches any IP protocol
    // If representation is exact only ipno is used
    IPFilterRule::SrcDst srcSam(IPFilterRule::SrcDst::MASK,"192.168.9.2",1);
    IPFilterRule::SrcDst dstSam(IPFilterRule::SrcDst::EXACT,"192.168.9.3",1);
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
int SendRxAARequest() 
{
    // [1]. Create an instance of AARequest class
    // The AA-Request command is sent by a Diameter
    // client to a Diameter Server in order to aaReq deregistration
    // Command-Code = 265 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::rx_ts29214::AARequest aaReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(RX_INTERFACE_APP_ID, sIdx, sessIdString);
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
    AuthApplicationId authid(RX_INTERFACE_APP_ID);
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
    IPFilterRule ipFltrule;
    PopulateIPFilterRule(ipFltrule);
    FlowDescription flowDescription(ipFltrule);
    mediaSubComponent.addFlowDescription(flowDescription);

    mediaComponentDescription.addMediaSubComponent(mediaSubComponent);

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

    // [2.2.3.1] The AF-Charging-Identifier AVP (AVP code 505)
    //  is of type OctetString, contains the AF Charging Identifier
    // that is sent by the AF.
    AFChargingIdentifier afcid("INT100");
    aaReq.setAFChargingIdentifier(afcid);

    // [2.2.3.2] The SIP_Forking AVP (AVP code 523) is of type Enumerated,
    // and describes if several SIP dialogues are related to one
    // SINGLE_DIALOGUE (default)
    // SEVERAL_DIALOGUES
    SIPForkingIndication sipin(SIPForkingIndication::SINGLE_DIALOGUE);
    aaReq.setSIPForkingIndication(sipin);

    // [2.2.3] The Specific-Action AVP (AVP code 513) is of type Enumerated.
    // The following values are defined for this AVP
    // SERVICE_INFORMATION_REQUEST
    // CHARGING_CORRELATION_EXCHANGE
    // INDICATION_OF_LOSS_OF_BEARER
    // INDICATION_OF_RECOVERY_OF_BEARER
    // INDICATION_OF_RELEASE_OF_BEARER
    // INDICATION_OF_ESTABLISHMENT_OF_BEARER
    SpecificAction specAction(SpecificAction::INDICATION_OF_RELEASE_OF_BEARER);
    aaReq.addSpecificAction(specAction);

    // Subscription-Id AVP (AVP Code 443) is of type Grouped 
    // and is used to identify the end user's subscription.
    SubscriptionId subscriptionId;

    // Subscription-Id-Type AVP (AVP Code 450) is of type 
    // Enumerated and it is used to determine which type of 
    // identifier is carried by the Subscription-Id AVP.
    //    END_USER_E164 = 0,
    //    END_USER_IMSI = 1,
    //    END_USER_SIP_URI = 2,
    //    END_USER_NAI = 3,
    //    END_USER_PRIVATE = 4
    SubscriptionIdType subscriptionIdType(SubscriptionIdType::END_USER_IMSI);
    subscriptionId.setSubscriptionIdType(subscriptionIdType);


    // Subscription-Id-Data AVP (AVP Code 444) is of type UTF8String 
    // and is used to identify the end user.
    SubscriptionIdData subscriptionIdData("SIP Data");
    subscriptionId.setSubscriptionIdData(subscriptionIdData);
    aaReq.addSubscriptionId(subscriptionId);

    // These two AVPs are set by the stack.
    // and application should not set those.
    // aaReq.addProxyInfo(ProxyInfo(...));
    // aaReq.addRouteRecord(RouteRecord(...));
    // add more AVP as ANY values

    if (appMode == UNIT_TEST)
    cout<<aaReq;

    // Send encoded message to stack.
    SendDiaAppMsg(aaReq, sIdx);
    RxStats::GetRxStats()->UpdateSendStats(aaReq.getCommandCode(), ITS_TRUE);

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
int SendRxAAAnswer(const CommandImpl *impl) 
{
    //[ 1] Create an instance of AAAnswer class
    // The AA-Answer command is sent by a Diameter
    // server to a Diameter client in order to request deregistration
    // Command-Code = 265 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::rx_ts29214::AAAnswer aaAns;

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
    //ExperimentalResult experimentResult;

    // [2.2.2.2] Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    //VendorId vid(VENDOR_ID);
    //experimentResult.setVendorId(vid);

    // [2.2.2.3] Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    //ExperimentalResultCode erc(100);
    //experimentResult.setExperimentalResultCode(erc);

    // [2.2.2]Set the ExperimentalResult AVP
    // aaAns.setExperimentalResult(experimentResult);

    // These AVPS should not be set by application.
    // aaAns.setErrorMessage(ErrorMessage(...));
    // aaAns.setErrorReportingHost(ErrorReportingHost(...));
    // aaAns.addFailedAVP(FailedAVP(...));
    // aaAns.addProxyInfo(ProxyInfo(...));
    // add more AVP as ANY values

    int pinfo_count = aareq.countProxyInfo();
    for(int i=0; i<pinfo_count; i++)
    {
        ProxyInfo pinfo;
        ProxyHost phost(aareq.getProxyInfo(i).getProxyHost());
        pinfo.setProxyHost(phost);

        ProxyState pstate(aareq.getProxyInfo(i).getProxyState());
        pinfo.setProxyState(pstate);

        aaAns.addProxyInfo(pinfo);
    }
 
    if (appMode == UNIT_TEST)
    cout<<aaAns; 

    // Send Encoded message to stack.
    SendDiaAppMsg(aaAns, sIdx);
    RxStats::GetRxStats()->UpdateSendStats(aaAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;


}
