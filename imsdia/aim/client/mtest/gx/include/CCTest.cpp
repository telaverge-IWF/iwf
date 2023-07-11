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
 * LOG: $Log: CCTest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:00  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2008/03/27 11:18:29  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 1.4  2006/11/29 12:31:08  kamakshilk
 * LOG: Send App Id changed to GX_APP_ID
 * LOG:
 * LOG: Revision 1.3  2006/11/17 07:07:26  kamakshilk
 * LOG: ReleaseSesion Added
 * LOG:
 * LOG: Revision 1.2  2006/11/07 13:12:37  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1  2006/10/03 09:21:28  rrath
 * LOG: Baseline distributed demo for new IMS Interfaces.
 * LOG:
 * LOG:
 * ID: $Id: CCTest.cpp,v 3.1 2008/03/31 10:33:00 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: CCTest.cpp,v 3.1 2008/03/31 10:33:00 nvijikumar Exp $"

#include <app.h>
#include <idc_api.h>

#include <gx_defines.h>
#include <diameter/gx/CC.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::nasreq;
using namespace diameter::gx;

extern unsigned int sIdxGx;
string sessIdStringGxCc;
extern IDSCLApi apiGx;

void PopulateChargingInformation(ChargingInformation &chargingInformation);
void PopulateIPFilterRule(IPFilterRule &ipFltRule);
void
PopulateChargingRuleDefinition(ChargingRuleDefinition &chargingRuleDefinition);

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Credit Control Req to the
 *      diameter stack. Creates the CC Request object,
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
int SendGxCCRequest() 
{
    // [1] Create CreditControlRequest object.
    // The RA-Request command is sent by a Diameter
    // client to a Diameter Server in order to raReq deregistration
    // Command-Code = 272
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gx::CCRequest ccReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    apiGx.AllocateSessionIndex(10000,sIdxGx,sessIdStringGxCc);
    ccReq.setSessionId(SessionId(sessIdStringGxCc));

    // [2.1.2.5] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authAppId(GX_INTERFACE_APP_ID);
    ccReq.setAuthApplicationId(authAppId);

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
    ccReq.setOriginHost(orighost);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origrealm(GetOriginRealm());
    ccReq.setOriginRealm(origrealm);

    // [2.1.2.3] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destRealm(GetDestinationRealm());
    ccReq.setDestinationRealm(destRealm);

    // [2.1.2.6] Populate required parameter "CC-Request-Type".
    // Set the CC-Request-Type AVP.
    // The data type of CC-Request-Type is Enumerated.
    // This AVP contains the reason for sending the credit-control request
    // message. 
    // The AVP Code of CC-Request-Type is 416.
    CCRequestType ccRequestType(CCRequestType::INITIAL_REQUEST);
    ccReq.setCCRequestType(ccRequestType);

    // [2.1.2.7] Populate required parameter "CC-Request-Number".
    // Set the CC-Request-Number AVP.
    // The data type of CC-Request-Number is Unsigned32.
    // This AVP identifies the request within one session. The 
    // combination of Session-Id and CC-Request-Number is globally unique.
    // An easy way to produce unique numbers is to set the value to 0 for 
    // credit-control request of type INITIAL_REQUEST and EVENT_REQUEST. 
    // Set value to 1 for UPDATE_REQUEST, to 2 for second  until the value
    // for TERMINATE_REQUEST is one more than the last UPDATE_REQUEST.
    // The AVP Code of CC-Request-Number is 415.
    CCRequestNumber ccRequestNumber(0u);
    ccReq.setCCRequestNumber(ccRequestNumber);

    // [2.2] Populate Optionals.

    // [2.2.1] Populate optional parameter "Destination-Host"
    // Set the Destination-Host AVP.
    // The data type for Destination-Host is DiameterIdentity.
    // This AVP MUST be present in all unsolicited agent initiated 
    // messages, MAY be present in request messages and MUST NOT be 
    // present in ccAnss. 
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    ccReq.setDestinationHost(destinationHost);

    // [2.2.3] Populate optional parameter "Origin-State-Id"
    // Set the Origin-State-Id AVP.
    // The data type for Origin-State-Id is of type Unsigned32.
    // It is a monotonically increasing value that is advanced whenever a 
    // Diameter entity restarts with loss of previous state,eg upon reboot.
    // The AVP Code of Origin-State-Id is 278.
    OriginStateId originStateId(1);
    // API should be provided for getting the Origin-State-Id value.
    ccReq.setOriginStateId(originStateId);

    // [2.2.5] Populate optional(multiple occurence) parameter
    //          "Subscription-Id"
    // Set the Subscription-Id AVP.
    // The data type Subscription-Id is Grouped.
    // This is used to identify the end user's subscription.
    // The AVP Code of Subscription-Id is 443.
    SubscriptionId subscriptionId1;

    // [2.2.5.1] Populate "Subscription-Id" grouped AVPs.
    // [2.2.5.1.1] Populate optional parameter "Subscription-Id-Type"
    // Set the Subscription-Id-Type AVP.
    // The data type Subscription-Id-Type is Enumerated.
    // This is used to determine which type of identifier is carried by the
    // subscription-Id avp. 
    // The AVP Code of Subscription-Id-Type is 450.
    SubscriptionIdType subscriptionIdType
                          (SubscriptionIdType::END_USER_SIP_URI);
    subscriptionId1.setSubscriptionIdType(subscriptionIdType);

    // [2.2.5.1.2] Populate optional parameter "Subscription-Id-Data"
    // Set the Subscription-Id-Data AVP.
    // The data type Subscription-Id-Data is UTF8String.
    // This is used to identify the end user.
    // The AVP Code of Subscription-Id-Data is 444.
    SubscriptionIdData subscriptionIdData("sip:alice@atlanta.com");
    subscriptionId1.setSubscriptionIdData(subscriptionIdData);
    ccReq.addSubscriptionId(subscriptionId1);

    // [2.2.5.2] The Framed-IP-Address AVP (AVP Code 8) [RADIUS] 
    // is of type OctetString and contains an IPv4 address
    FramedIPAddress framedIPaddr("10.1.1.1");
    ccReq.setFramedIPAddress(framedIPaddr);

    // [2.2.5.4] The Framed-IPv6-Prefix AVP (AVP Code 97) is 
    // of type OctetString and contains the IPv6 prefix to be 
    // configured for the user
    FramedIPv6Prefix framedIPv6prefix("10.10");
    ccReq.setFramedIPv6Prefix(framedIPv6prefix);

    // 3GPP-RAT-Type AVP is of type OctetString. 
    // It indicates which Radio Access Technology is 
    // currently serving the UE.
    Gx3GPPRATType gx3GPPRATType("Business");
    ccReq.setGx3GPPRATType(gx3GPPRATType);

    // [2.1.2.4] Populate required parameter "Termination-Cause".
    // Set the Termination-Cause AVP.
    // The data type of Termination-Cause is Enumerated.
    // This AVP  is used to indicate the reason why a session was terminated on
    // the access device.
    // The following values are defined:
    // DIAMETER_LOGOUT                   1
    // DIAMETER_SERVICE_NOT_PROVIDED     2
    // DIAMETER_BAD_ANSWER               3
    // DIAMETER_ADMINISTRATIVE           4
    // DIAMETER_LINK_BROKEN              5
    // DIAMETER_AUTH_EXPIRED             6
    // DIAMETER_USER_MOVED               7
    // DIAMETER_SESSION_TIMEOUT          8
    // The AVP Code of Termination-Cause is 295.
    TerminationCause termcause(TerminationCause::DIAMETER_BAD_ANSWER);
    ccReq.setTerminationCause(termcause);

    // The User-Equipment-Info AVP (AVP Code 458) is of 
    // type Grouped and allows the credit-control client to 
    // indicate the identity and capability of the terminal 
    // the subscriber is using for the connection to network.
    UserEquipmentInfo userEquipmentInfo;

    // The User-Equipment-Info-Type AVP (AVP Code 459) is of type 
    // Enumerated and defines the type of user equipment information 
    // contained in the User-Equipment-Info-Value AVP.
    //         IMEISV = 0,
    //         MAC = 1,
    //         EUI64 = 2,
    //         MODIFIED_EUI64 = 3
    UserEquipmentInfoType userEquipmentInfoType(UserEquipmentInfoType::MAC);
    userEquipmentInfo.setUserEquipmentInfoType(userEquipmentInfoType);

    // The User-Equipment-Info-Value AVP (AVP Code 460) is of 
    // type OctetString. The User-Equipment-Info-Type AVP defines 
    // which type of identifier is used.
    UserEquipmentInfoValue userEquipmentInfoValue("A100");
    userEquipmentInfo.setUserEquipmentInfoValue(userEquipmentInfoValue);

    // Set the userEquipmentInfo AVP
    ccReq.setUserEquipmentInfo(userEquipmentInfo);

    // 3GPP-GPRS-Negotiated-QoS-Profile AVP is of type UTF8String. 
    // It is the QoS Profile applied by GGSN.
    Gx3GPPGPRSNegotiatedQoSProfile gx3GPPGPRSNegotiatedQoSProfile(" GGSN ");
    ccReq.setGx3GPPGPRSNegotiatedQoSProfile(gx3GPPGPRSNegotiatedQoSProfile);

    // 3GPP-SGSN-MCC-MNC AVP is of type UTF8String. 
    // It contains the MCC and MNC extracted from the RAI within the 
    // Create PDP Context Request or Update PDP Context Request message.
    Gx3GPPSGSNMCCMNC gx3GPPSGSNMCCMNC("New PDP");
    ccReq.setGx3GPPSGSNMCCMNC(gx3GPPSGSNMCCMNC);

    // 3GPP-SGSN-Address AVP (AVP Code 6) is of type UTF8String and 
    // contains the SGSN IP address that is used by the GTP control 
    // plane for the handling of control messages. It may be used to 
    // identify the PLMN to which the user is attached.
    Gx3GPPSGSNAddress gx3GPPSGSNAddress("10.1.2.1");
    ccReq.setGx3GPPSGSNAddress(gx3GPPSGSNAddress);

    // 3GPP-SGSN-IPv6-Address AVP (AVP Code 15) is of type 
    // UTF8String and contains the SGSN IPv6 address that is used 
    // by the GTP control plane for the handling of control messages. 
    // It may be used to identify the PLMN to which the user is attached.
    Gx3GPPSGSNIPv6Address gx3GPPSGSNIPv6Address("10.1.5.4.1.2");
    ccReq.setGx3GPPSGSNIPv6Address(gx3GPPSGSNIPv6Address);

    // The Called-Station-Id AVP (AVP Code 30) is of type UTF8String 
    // and allows the NAS to send the ASCII string describing the 
    // layer 2 address the user contacted in the request. For dialup 
    // access,this can be a phone number, obtained using Dialed Number 
    // identification (DNIS) or a similar technology. Note that this may 
    // be different from the phone number the call comes in on. For the use 
    // with IEEE 802 access, the Called-Station-Id MAY contain a MAC address 
    // formatted as described in RAD802.1X.
    ccReq.setCalledStationId(CalledStationId("A1500"));

    // The Bearer-Usage AVP (AVP code 1000) is of type Enumerated, 
    // and it shall indicate how the bearer is being used. If the Bearer-Usage 
    // AVP has not been previously provided, its absence shall indicate 
    // that no specific information is available. If the Bearer-Usage AVP 
    // has been provided, its value shall remain valid until it 
    // is provided the next time.
    //         GENERAL = 0,
    //        IMS_SIGNALLING = 1
    BearerUsage bearerUsage(BearerUsage::GENERAL);
    ccReq.setBearerUsage(bearerUsage);

    // The PDP-Session-Operation AVP (AVP Code 1015) is of type Enumerated. 
    // It is only applicable for GPRS.
    //  PDP_SESSION_TERMINATION = 0
    PDPSessionOperation PDPsessionOperation(PDPSessionOperation::
                                              PDP_SESSION_TERMINATION);
    ccReq.setPDPSessionOperation(PDPsessionOperation);

    // The TFT-Packet-Filter-Information AVP (AVP code 1013) is of 
    // type Grouped,and it contains the information from a single 
    // TFT packet filter including the evaluation precedence, 
    // the filter and the Type-of-Service/Traffic Class sent from the 
    // TPF to the CRF
    TFTPacketFilterInformation TFTpacketFilterInformation;

    // The Precedence AVP (AVP code 1010) is of type Unsigned32, 
    // and it defines the precedence of a charging rule in case 
    // of overlapping charging rules. A charging rule with the Precedence 
    // AVP with lower value shall take the priority over a charging rule 
    // with the Precedence AVP with higher value
    Precedence precedence(10);
    TFTpacketFilterInformation.setPrecedence(precedence);

    // The TFT-Filter AVP (AVP code 1012) is of type IPFilterRule, 
    // and it contains the flow filter for one TFT packet filter.
    // The TFT-Filter AVP is derived from the Traffic Flow Template (TFT) 
    // defined in 3GPP TS 24.008. 
    IPFilterRule ipFltRule;
    PopulateIPFilterRule(ipFltRule);
    TFTFilter TFTfilter(ipFltRule);
    TFTpacketFilterInformation.setTFTFilter(TFTfilter);

    // The ToS-Traffic-Class AVP (AVP code 1014) is of type OctetString, 
    // and it contains the Type-of-Service/Traffic-Class of a TFT packet 
    // filter as defined in 3GPP TS 24.008.
    ToSTrafficClass tosTrafficClass("Prefessional");
    TFTpacketFilterInformation.setToSTrafficClass(tosTrafficClass);
    // Set the TFTPacketFilterInformation AVP.
    ccReq.addTFTPacketFilterInformation(TFTpacketFilterInformation);

    // These AVPs should not be set by the Application.
    // ccReq.addProxyInfo(ProxyInfo(...));
    //  ccReq.addRouteRecord(RouteRecord(...));
    // add more AVP as ANY values

    // Send encoded Message to IDS.
    std::cout << ccReq << std::endl;

    apiGx.Send(ccReq, sIdxGx, GX_INTERFACE_APP_ID);

    return ITS_SUCCESS;

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Answer to Credit Control request 
 *      sent by the application. This creates the CreditControlAnswer
 *      object, populate the AVPs and sends the message to the app.
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
int SendGxCCAnswer(const diameter::CommandImpl* impl)
{
    // [1] Create CreditControlAnswer object.
    CCAnswer ccAns(false,false);

    // [1.1] Create an instance of CreditControlRequest class with
    //        recived event
    CCRequest ccreq(*impl);

    // Get AVP values from Request and set them to Answer Message
    const SessionId& sid = ccreq.getSessionId();
    const AuthApplicationId& authid  = ccreq.getAuthApplicationId();
    const OriginHost& oh = ccreq.getOriginHost();
    const OriginRealm& or1 = ccreq.getOriginRealm();
    const DestinationHost& dh = ccreq.getDestinationHost();
    const DestinationRealm& dr = ccreq.getDestinationRealm();
    const OriginStateId& osid = ccreq.getOriginStateId();
    const CCRequestNumber& ccreqnumber = ccreq.getCCRequestNumber();
    const CCRequestType& ccreqtype = ccreq.getCCRequestType();

    // [2.1.1.x] Fixed AVP
    
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    ccAns.setSessionId(sid);

    // [2.1.2.5] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    ccAns.setAuthApplicationId(authid);

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
    ccAns.setOriginHost(origHost);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origRealm(dr.value());
    ccAns.setOriginRealm(origRealm);

    // [2.1.2.6] Populate required parameter "CC-Request-Type".
    // Set the CC-Request-Type AVP.
    // The data type of CC-Request-Type is Enumerated.
    // This AVP contains the reason for sending the credit-control request
    // message. 
    // The AVP Code of CC-Request-Type is 416.
    ccAns.setCCRequestType(ccreqtype);

    // [2.1.2.7] Populate required parameter "CC-Request-Number".
    // Set the CC-Request-Number AVP.
    // The data type of CC-Request-Number is Unsigned32.
    // This AVP identifies the request within one session. The 
    // combination of Session-Id and CC-Request-Number is globally unique.
    // An easy way to produce unique numbers is to set the value to 0 for 
    // credit-control request of type INITIAL_REQUEST and EVENT_REQUEST. 
    // Set value to 1 for UPDATE_REQUEST, to 2 for second  until the value
    // for TERMINATE_REQUEST is one more than the last UPDATE_REQUEST.
    // The AVP Code of CC-Request-Number is 415.
    ccAns.setCCRequestNumber(ccreqnumber);

    
    // [2.1.2] Populate Mandatories which can appear anywhere.

    // [2.1.2.1] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    // 1xxx - Informational
    // 2xxx - Success
    // 3xxx - Protocol Errors
    // 4xxx - Transient Failures
    // 5xxx - Permanent Failure
    // The AVP Code of AVP is 268.
    // The data type of AVP is Unsigned32.
    ResultCode resultCode(2001u);
    ccAns.setResultCode(resultCode);

    // [2.2.2.1] Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // ResultCode AVP is already been set.
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
    //ExperimentalResultCode erc(2001);
    //er1.setExperimentalResultCode(erc);

    // [2.2.2] set ExperimentalResult AVP 
    // Already ResultCode AVP is set, not required to set
    // ExperimentalResult.
    // ccAns.setExperimentalResult(er1);

    // The Event-Trigger AVP (AVP code 1006) is of type Enumerated,
    // and it indicates an event that shall cause a re-request of 
    // charging rules.
    //         SGSN_CHANGE = 0,
    //         QOS_CHANGE = 1,
    //         RAT_CHANGE = 2,
    //         TFT_CHANGE = 3,
    //         PLMN_CHANGE = 4
    ccAns.addEventTrigger(EventTrigger(EventTrigger::SGSN_CHANGE));

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
    ccAns.setOriginStateId(osid);

    // he Charging-Rule-Remove AVP (AVP code 1002) is of type Grouped, 
    // and it is used to deactivate or remove charging rules from a bearer.
    // Charging-Rule-Name AVP is a reference for a specific charging rule 
    // at the TPF to be removed or for a specific charging rule predefined 
    // at the TPF to be deactivated. The Charging-Rule-Base-Name AVP is a 
    // reference for a group of charging rules predefined at the TPF 
    // to be deactivated
    ChargingRuleRemove chargingRuleRemove;

    // The Charging-Rule-Name AVP (AVP code 1005) is of type OctetString.  
    // For charging rules provided by the CRF it uniquely identifies a 
    // charging rule for a bearer. For charging rules pre-defined at the 
    // TPF it uniquely identifies a charging rule within the TPF.
    ChargingRuleName chargingRuleName("RuleA1");
    chargingRuleRemove.addChargingRuleName(chargingRuleName);

    // The Charging-Rule-Base-Name AVP (AVP code 1004) is of type OctetString, 
    // and it indicates the name of a preâfined group of charging rules r
    // esiding at the TPF.
    ChargingRuleBaseName chargingRuleBaseName("BaseRule");
    chargingRuleRemove.addChargingRuleBaseName(chargingRuleBaseName);

    // Set the ChargingRuleRemove AVP.
    ccAns.addChargingRuleRemove(chargingRuleRemove);

    // The Charging-Rule-Install AVP (AVP code 1001) is of type Grouped, 
    // and it is used to activate,install or modify charging rules for 
    // a bearer as instructed from the CRF to TPF.
    ChargingRuleInstall chargingRuleInstall;

    // The Charging-Rule-Definition AVP (AVP code 1003) is of type Grouped, 
    // and it defines the charging rule for a service flow sent by the 
    // CRF to the TPF.The Charging-Rule-Name AVP uniquely identifies 
    // the charging rule for a bearer and it is used to reference to a 
    // charging rule in communication between the TPF and the CRF. 
    // The Flow-Description AVP(s) determines the traffic that 
    //  belongs to the service flow.
    ChargingRuleDefinition chargingRuleDefinition;
    PopulateChargingRuleDefinition(chargingRuleDefinition);
    chargingRuleInstall.addChargingRuleDefinition(chargingRuleDefinition);

    // The Charging-Rule-Name AVP (AVP code 1005) is of type OctetString.  
    // For charging rules provided by the CRF it uniquely identifies a 
    // charging rule for a bearer. For charging rules pre-defined at the 
    // TPF it uniquely identifies a charging rule within the TPF.
    ChargingRuleName chargingruleName("RuleA1");
    chargingRuleInstall.addChargingRuleName(chargingruleName);

    // The Charging-Rule-Base-Name AVP (AVP code 1004) is of type OctetString, 
    // and it indicates the name of a preâfined group of charging rules r
    // esiding at the TPF.
    ChargingRuleBaseName chargingruleBaseName("BaseRule");
    chargingRuleInstall.addChargingRuleBaseName(chargingruleBaseName);

    // Set the ChargingRuleInstall AVP.
    ccAns.addChargingRuleInstall(chargingRuleInstall);

    // The Charging-Information AVP (AVP Code 618) is of type Grouped, 
    // and contains the addresses of the charging function.
    ChargingInformation chargingInformation;
    PopulateChargingInformation(chargingInformation);

    // Set the ChargingInformation AVP.
    ccAns.setChargingInformation(chargingInformation);

    // [2.2.8] The Error-Message AVP (AVP Code 281) is of type UTF8String.  
    // It MAY accompany a Result-Code AVP as a human readable error message
    // ErrorMessage err("Authentication error");
    // ccAns.setErrorMessage(err);

    // [2.2.9] The Error-Reporting-Host AVP (AVP Code 294) is of type
    // DiameterIdentity.  This AVP contains the identity of the Diameter
    // host that sent the Result-Code AVP
    // ErrorReportingHost errh("dia.xyz.com");
    // ccAns.setErrorReportingHost(errh);
    std::cout << ccAns << std::endl;

    apiGx.Send(ccAns, sIdxGx, GX_INTERFACE_APP_ID);

    /* Release session context */
    if (!apiGx.IsDccaEnabled())
    {
        switch(ccAns.getCCRequestType().value())
        {
           case CCRequestType::EVENT_REQUEST:
           case CCRequestType::TERMINATION_REQUEST:
               std::string rlsStr =
                           ccAns.getSessionId().value();
               apiGx.ReleaseSession(rlsStr, sIdxGx);
               break;
        }
    }

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
//    ByteRange icmpRng(3,13);
//    ipFltRule.icmpTypeRangeList.push_front(icmpRng);

}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the ChargingRuleDefinition AVP.
 *      This sets the values in the ChargingRuleDefinition AVP passed as a 
 *      reference to this function.
 *
 *  Input Parameters:
 *      ChargingRuleDefinition &chargingRuleDefinition
 *      Reference to the ChargingRuleDefinition AVP.
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
void 
PopulateChargingRuleDefinition(ChargingRuleDefinition &chargingRuleDefinition)
{
    // The Charging-Rule-Name AVP (AVP code 1005) is of type OctetString.  
    // For charging rules provided by the CRF it uniquely identifies a 
    // charging rule for a bearer. For charging rules pre-defined at the 
    // TPF it uniquely identifies a charging rule within the TPF.
    ChargingRuleName chargingrulename("RuleA1");
    chargingRuleDefinition.setChargingRuleName(chargingrulename);

    // The ServiceIdentifier is of type OctetString.
    ServiceIdentifier serviceIdentifier("A100Z0");
    chargingRuleDefinition.setServiceIdentifier(serviceIdentifier);

    // The RatingGroup is of type Unsigned Int.
    RatingGroup ratingGroup(100);
    chargingRuleDefinition.setRatingGroup(ratingGroup);


    // The Flow-Description AVP (AVP code 507) is of type IPFilterRule, 
    // and defines a packet filter for an IP flow with the following 
    // information: Direction (in or out). Source and destination IP address 
    // (possibly masked). Protocol.
    IPFilterRule ipFltrule;
    PopulateIPFilterRule(ipFltrule);
    FlowDescription flowDescription(ipFltrule);
    chargingRuleDefinition.addFlowDescription(flowDescription);

    // The Reporting-Level AVP (AVP code 1011) is of type Enumerated,
    // and it defines on what level the TPF reports the usage for the 
    // related charging rule.
    //    CHARGING_RULE_LEVEL = 0,
    //    RATING_GROUP_LEVEL = 1
    ReportingLevel reportingLevel(ReportingLevel::CHARGING_RULE_LEVEL);
    chargingRuleDefinition.setReportingLevel(reportingLevel);

    // The Online AVP (AVP code 1009) is of type Enumerated, 
    // and it defines whether the online charging interface from 
    // the TPF for the associated charging rule  shall be enabled. 
    // The absence of this AVP indicates that the default 
    // configuration shall be used.
    //    DISABLE_ONLINE = 0,
    //    ENABLE_ONLINE = 1
    Online online(Online::DISABLE_ONLINE);
    chargingRuleDefinition.setOnline(online);

    // The Offline AVP (AVP code 1008) is of type Enumerated,
    // and it defines whether the offline charging interface from 
    // the TPF for the associated charging rule shall be enabled. 
    // The absence of this AVP indicates that the default 
    // configuration shall be used.
    //    DISABLE_OFFLINE = 0,
    //    ENABLE_OFFLINE = 1
    Offline offline(Offline::ENABLE_OFFLINE);
    chargingRuleDefinition.setOffline(offline);

    // The Metering-Method AVP (AVP code 1007) is of type Enumerated, and 
    // it defines what parameters shall be metered for offline charging.
    //    DURATION = 0,
    //    VOLUME = 1,
    //    DURATION_VOLUME = 2
    MeteringMethod meteringMethod(MeteringMethod::DURATION);
    chargingRuleDefinition.setMeteringMethod(meteringMethod);

    // The Precedence AVP (AVP code 1010) is of type Unsigned32, 
    // and it defines the precedence of a charging rule in case 
    // of overlapping charging rules. A charging rule with the Precedence 
    // AVP with lower value shall take the priority over a charging rule 
    // with the Precedence AVP with higher value
    Precedence precedence(10);
    chargingRuleDefinition.setPrecedence(precedence);

    // The AF-Charging-Identifier AVP (AVP code 505)is of type OctetString,
    // contains the AF Charging Identifier that is sent by the AF. 
    // This information may be used for charging correlation with bearer layer.
    AFChargingIdentifier AFchargingIdentifier("A100D");
    chargingRuleDefinition.setAFChargingIdentifier(AFchargingIdentifier);

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
    chargingRuleDefinition.addFlows(flows);
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function populates the ChargingInformation AVP.
 *      This sets the values in the ChargingInformation AVP passed as a 
 *      reference to this function.
 *
 *  Input Parameters:
 *      ChargingInformation &chargingInformation
 *      : Reference to the IPFilterRule object
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
void PopulateChargingInformation(ChargingInformation &chargingInformation)
{
    // The Primary-Charging-Collection-Function-Name AVP is of type 
    // DiameterURI. This AVP contains the address of the Primary 
    // Charging Collection Function.
    URI uri("PrimaryEventChargingFunction.com", URI::AAA,3880, URI::SCTP,
             URI::DIAMETER);

    // The Primary-Event-Charging-Function-Name AVP (AVP Code 619) is of 
    // type DiameterURI. This AVP contains the address of the Primary 
    // Online Charging Function.
    PrimaryEventChargingFunctionName pecfName(uri);
    chargingInformation.setPrimaryEventChargingFunctionName(pecfName);

    // The Secondary-Event-Charging-Function-Name AVP (AVP Code 620) is of 
    // type DiameterURI. This AVP contains the address of the Secondary 
    // Online Charging Function.
    SecondaryEventChargingFunctionName secfName(uri);
    chargingInformation.setSecondaryEventChargingFunctionName(secfName);

    // The Primary-Charging-Collection-Function-Name AVP is of type 
    // DiameterURI. This AVP contains the address of the Primary 
    // Charging Collection Function.
    URI uri1("PrimaryEventChargingFunction.com", URI::AAA,3880, URI::SCTP,
             URI::DIAMETER);

    // The Primary-Charging-Collection-Function-Name AVP (AVP Code 621) 
    // is of type DiameterURI. This AVP contains the address of the 
    // Primary Charging Data Function. 
    PrimaryChargingCollectionFunctionName pccfn(uri1);
    chargingInformation.setPrimaryChargingCollectionFunctionName(pccfn);
    
    // The Secondary-Charging-Collection-Function-Name AVP (AVP Code 622) 
    // is of type DiameterURI. This AVP contains the address of the Secondary 
    // Charging Data Function.
    SecondaryChargingCollectionFunctionName sccfName(uri1);
    chargingInformation.setSecondaryChargingCollectionFunctionName(sccfName);
}
