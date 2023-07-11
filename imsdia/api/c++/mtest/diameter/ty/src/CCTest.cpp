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
 * LOG: $Log: CCTest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:13  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.6  2007/02/21 07:01:39  hbhatnagar
 * LOG: changed the value passed to Service-Identifier from string to unsigned int
 * LOG:
 * LOG: Revision 2.5  2006/12/22 10:17:01  nvijikumar
 * LOG: Passing correct appId for AllocateSession API.
 * LOG:
 * LOG: Revision 2.4  2006/12/19 08:58:48  kamakshilk
 * LOG: New architecture to work with static and distributed
 * LOG:
 * LOG: Revision 2.3  2006/11/02 12:15:32  kamakshilk
 * LOG: Added containsDestinationHost() before doing get
 * LOG:
 * LOG: Revision 2.2  2006/10/16 15:45:03  kamakshilk
 * LOG: Merging with ITS-Diameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.2  2006/09/12 09:56:44  kamakshilk
 * LOG: Removed the icmptypes option set in IPFilterRule
 * LOG:
 * LOG: Revision 1.1  2006/07/24 15:59:29  nvijikumar
 * LOG: Baseline demo application for Ty Interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: CCTest.cpp,v 3.1 2008/03/31 10:33:13 nvijikumar Exp $
 ****************************************************************************/
#include <app.h>
#include <ty_defines.h>
#include <ty_stats.h>
#include <diameter/ty/CC.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::nasreq;
using namespace diameter::ty;

void PopulateIPFilterRule(IPFilterRule &ipFltRule);
void
PopulateChargingRuleDefinition(ChargingRuleDefinition &chargingRuleDefinition);

string sessIdString;
ITS_UINT sIdx;

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
int SendTyCCRequest()
{
    // [1] Create CreditControlRequest object.
    // The RA-Request command is sent by a Diameter
    // client to a Diameter Server in order to raReq deregistration
    // Command-Code = 272
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::ty::CCRequest ccReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    if (appMode == LOAD_TEST)
    {
    AllocateSession(TY_INTERFACE_APP_ID,sIdx,sessIdString);
    ccReq.setSessionId(SessionId(sessIdString));

    ccReq.setSessionIndex(sIdx);
    }

    // [2.1.2.5] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authAppId(TY_INTERFACE_APP_ID);
    ccReq.setAuthApplicationId(authAppId);

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
    if (appMode == LOAD_TEST)
    {
    CCRequestType ccRequestType(CCRequestType::INITIAL_REQUEST);
    ccReq.setCCRequestType(ccRequestType);
    }

    else if (appMode == UNIT_TEST)
    {
        string inStr;
        cout << "Please enter the request Type" << endl
             << "1. Initial" << endl
             << "2. Update" << endl
             << "3. Terminate" << endl
             << "4. Event" << endl ;
        cin >> inStr; 
        int inReqType = atoi(inStr.c_str());
        switch(inReqType)
        {
            case 1:
            {
                CCRequestType ccRequestType(CCRequestType::INITIAL_REQUEST);
                ccReq.setCCRequestType(ccRequestType);
                AllocateSession(TY_INTERFACE_APP_ID,sIdx,sessIdString);
                break;
            }
            case 2:
            {
                cout << "Please enter the Session ID to Update" << endl;
                cin >> sessIdString;
                CCRequestType ccRequestType(CCRequestType::UPDATE_REQUEST);
                ccReq.setCCRequestType(ccRequestType);
                break;
            }
            case 3:
            {
                cout << "Please enter the Session ID to Terminate" << endl;
                cin >> sessIdString;
                CCRequestType ccRequestType(CCRequestType::TERMINATION_REQUEST);
                ccReq.setCCRequestType(ccRequestType);
                break;
            }
            case 4:
            {
                CCRequestType ccRequestType(CCRequestType::EVENT_REQUEST);
                ccReq.setCCRequestType(ccRequestType);
                AllocateSession(TY_INTERFACE_APP_ID,sIdx,sessIdString);
                break;
            }
            default:
                cout << "Invalid Request Type" <<endl;    
                break;
        }
        ccReq.setSessionId(SessionId(sessIdString));

        ccReq.setSessionIndex(sIdx);
    }

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

    //The CCSubSessionId is of type unsigned int.
    CCSubSessionId ccSubSessionId(42);
    ccReq.setCCSubSessionId(ccSubSessionId);

    // [2.2.3] Populate optional parameter "Origin-State-Id"
    // Set the Origin-State-Id AVP.
    // The data type for Origin-State-Id is of type Unsigned32.
    // It is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state,eg upon reboot.
    // The AVP Code of Origin-State-Id is 278.
    OriginStateId originStateId(1);
    // API should be provided for getting the Origin-State-Id value.
    ccReq.setOriginStateId(originStateId);

    // ubscription-Id AVP(AVP Code 443) is of type Grouped and 
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
    ccReq.addSubscriptionId(subscriptionId);

    //  The Framed-IP-Address AVP (AVP Code 8) is of type OctetString 
    // and contains an IPv4 address of the type specified in attribute 
    // value to be configured for the user. It MAY be used in an 
    // authorization request as a hint to server that a specific address 
    // is desired, but the server is not required to honor the hint in 
    // the corresponding response.
    FramedIPAddress framedIPAddress("10.1.10.1");
    ccReq.setFramedIPAddress(framedIPAddress);

    // The Framed-IPv6-Prefix AVP (AVP Code 97) is of type OctetString 
    // and contains the IPv6 prefix to be configured for the user. 
    // One or more AVPs MAY be used in authorization requests as hint 
    // to the server that specific IPv6 prefixes are desired, but the 
    // server is not required to honor the hint in the corresponding response.
    FramedIPv6Prefix framedIPv6Prefix("10.10");
    ccReq.setFramedIPv6Prefix(framedIPv6Prefix);

    // [2.1.2.4] Populate required parameter "Termination-Cause".
    // Set the Termination-Cause AVP.
    // The data type of Termination-Cause is Enumerated.
    // This AVP  is used to indicate the reason why a session was terminated on    // the access device.
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

    // 3GPP-GPRS-Negotiated-QoS-Profile AVP (AVP Code 5) is of type 
    // UTF8String. It is the QoS Profile applied by GGSN.
    NegotiatedQoSProfile negotiatedQoSProfile("GGSN");
    ccReq.setNegotiatedQoSProfile(negotiatedQoSProfile);

    // The Called-Station-Id AVP (AVP Code 30) is of type UTF8String and 
    // allows the NAS to send the ASCII string describing the layer 2 
    // address the user contacted in the request. For dialup access,
    // this can be a phone number, obtained using Dialed Number 
    // identification (DNIS) or a similar technology.
    CalledStationId calledStationId("A100D");
    ccReq.setCalledStationId(calledStationId);

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

    if (appMode == UNIT_TEST)
    cout<<ccReq;

    // Send encoded msg to Stack.
    SendDiaAppMsg(ccReq, sIdx);

    // Update stats.
    TyStats::GetTyStats()->UpdateSendStats(ccReq.getCommandCode(), ITS_TRUE);
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
int SendTyCCAnswer(const diameter::CommandImpl* impl)
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
    if (ccreq.containsDestinationHost())
        const DestinationHost& dh = ccreq.getDestinationHost();
    const DestinationRealm& dr = ccreq.getDestinationRealm();
    const OriginStateId& osid = ccreq.getOriginStateId();
    const CCRequestNumber& ccreqnumber = ccreq.getCCRequestNumber();
    const CCRequestType& ccreqtype = ccreq.getCCRequestType();
    const CCSubSessionId& ccsubId = ccreq.getCCSubSessionId();

    // [2.1.1.x] Fixed AVP

    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    ccAns.setSessionId(sid);

    ccAns.setSessionIndex(ccreq.getSessionIndex());

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
    OriginHost origHost(GetOriginHost());
    ccAns.setOriginHost(origHost);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origRealm(GetOriginRealm());
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

    //The CCSubSessionId is of type unsigned int.
    ccAns.setCCSubSessionId(ccsubId);

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
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
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

    // The Primary-CCF-Address AVP (AVP code 1011) is of type DiameterURI, 
    // and it defines the address of the primary offline charging system 
    // for the bearer. The absence of the protocol definition in the 
    // DiameterURI shall indicate the default protocol defined for the 
    // XX interface for offline charging data collection.
    URI uri("3gpp.com", URI::AAA,3880, URI::SCTP,URI::DIAMETER);
    PrimaryCCFAddress primaryCCFAddress(uri);
    ccAns.setPrimaryCCFAddress(primaryCCFAddress);

    // The Secondary-CCF-Address AVP (AVP code 1015) is of type DiameterURI, 
    // and it defines the address of the secondary offline charging system 
    // for the bearer. The absence of the protocol definition in the 
    // DiameterURI shall indicate the default protocol defined for the 
    // XX interface for offline charging data collection.
    URI uri1("3gpp.com", URI::AAA,3880, URI::SCTP,URI::DIAMETER);
    SecondaryCCFAddress secondaryCCFAddress(uri1);
    ccAns.setSecondaryCCFAddress(secondaryCCFAddress);

    // The Primary-OCS-Address AVP (AVP code 1012) is of type DiameterURI, 
    // and it defines the address of the primary online charging system 
    // for the bearer. The absence of the protocol definition in the 
    // DiameterURI shall indicate the default protocol defined for the 
    // XX interface for online charging control.
    URI uri2("3gpp.com", URI::AAA,3880, URI::SCTP,
             URI::DIAMETER);
    PrimaryOCSAddress primaryOCSAddress(uri2);
    ccAns.setPrimaryOCSAddress(primaryOCSAddress);

    // The Secondary-OCS-Address AVP (AVP code 1016) is of type DiameterURI, 
    // and it defines the address of the secondary online charging system 
    // for the bearer. The absence of the protocol definition in the 
    // DiameterURI shall indicate the default protocol defined for the 
    // XX interface for online charging control.
    URI uri3("3gpp.com", URI::AAA,3880, URI::SCTP,
             URI::DIAMETER);
    SecondaryOCSAddress secondaryOCSAddress(uri3);
    ccAns.setSecondaryOCSAddress(secondaryOCSAddress);

    // [2.2.8] The Error-Message AVP (AVP Code 281) is of type UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message
    // ErrorMessage err("Authentication error");
    // ccAns.setErrorMessage(err);

    // [2.2.9] The Error-Reporting-Host AVP (AVP Code 294) is of type
    // DiameterIdentity.  This AVP contains the identity of the Diameter
    // host that sent the Result-Code AVP
    // ErrorReportingHost errh("dia.xyz.com");
    // ccAns.setErrorReportingHost(errh);

    if (appMode == UNIT_TEST)
    cout<<ccAns;

    // Send encoded message to stack.
    SendDiaAppMsg(ccAns, sIdx);

    // Update stats.
    TyStats::GetTyStats()->UpdateSendStats(ccAns.getCommandCode(), ITS_FALSE);

    /* Release session context */
    switch(ccAns.getCCRequestType().value())
    {
        case CCRequestType::EVENT_REQUEST:
            if (!IsDccaEnabled())
            {
               std::string rlsStr = ccAns.getSessionId().value();
               ReleaseSession(rlsStr, sIdx);
            }
            break;
        case CCRequestType::TERMINATION_REQUEST:
            std::string rlsStr = ccAns.getSessionId().value();
            ReleaseSession(rlsStr, sIdx);
            break;
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

    // The Type of ServiceIdentifier was OctetString previously
    // now changed to Unsigned32 .
    ServiceIdentifier serviceIdentifier(1501u);
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

