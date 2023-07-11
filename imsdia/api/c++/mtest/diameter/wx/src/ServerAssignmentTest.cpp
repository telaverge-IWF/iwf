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
 * LOG: $Log: ServerAssignmentTest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:14  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.4  2006/12/19 09:02:14  kamakshilk
 * LOG: New architecture to work with static and distributed
 * LOG:
 * LOG: Revision 2.3  2006/11/02 12:44:49  kamakshilk
 * LOG: Added containsDestinationHost() before doing get
 * LOG:
 * LOG: Revision 2.2  2006/10/18 05:02:01  tpanda
 * LOG: Changes to work with ITS-Diameter APIs
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.2  2006/08/04 17:43:48  nvijikumar
 * LOG: Changes to update the stats for all Wx Interface Messages.
 * LOG:
 * LOG: Revision 1.1  2006/07/24 15:40:06  nvijikumar
 * LOG: Baseline commit for demo application ( Wx Interface).
 * LOG:
 * LOG:
 *
 * ID: $Id: ServerAssignmentTest.cpp,v 3.1 2008/03/31 10:33:14 nvijikumar Exp $
 ****************************************************************************/
#include <app.h>
#include <wx_defines.h>
#include <wx_stats.h>
#include <diameter/wx/ServerAssignment.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::wx;

extern string sessIdString;
extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the ServerAssignmentRequestto the
 *      diameter stack. Create the ServerAssignmentRequest object,
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
int SendWxServerAssignmentRequest() 
{
    // 1. Create an instance of ServerAssignmentRequest class
    // The Server-Assignment-Request command is sent from a Diameter
    // multimedia client to a Diameter multimedia server in order to
    // saReq it to store the name of the server that is currently
    // serving the user.
    // Command-Code = 301 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::wx::ServerAssignmentRequest saReq;

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
    AllocateSession(WX_INTERFACE_APP_ID, sIdx, sessIdString);
    saReq.setSessionId(diameter::base::SessionId(sessIdString));

    saReq.setSessionIndex(sIdx);

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
    AuthApplicationId authApplicationId(WX_INTERFACE_APP_ID);
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
    saReq.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

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
    saReq.setAuthSessionState(authSessionState);

    // [2.1] Set the Origin-Host AVP.
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
    saReq.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    saReq.setOriginRealm(originRealm);

    // [2.1] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    saReq.setDestinationRealm(destinationRealm);

    // [2.1] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    saReq.setUserName(userName);

    // Set the ServerAssignmentType AVP.
    ServerAssignmentType serverAssignmentType(ServerAssignmentType::
                                              NO_ASSIGNMENT);
    saReq.setServerAssignmentType(serverAssignmentType);

    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    saReq.setDestinationHost(destinationHost);

    // Application should not set this AVP.
    // saReq.addProxyInfo(diameter::base::ProxyInfo(...));
    // saReq.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values

    cout<<saReq;
    SendDiaAppMsg(saReq, sIdx);
    WxStats::GetWxStats()->UpdateSendStats(saReq.getCommandCode(), ITS_TRUE);

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the ServerAssignment request
 *      made by the diameter stack. Create the ServerAssignmentAnswer
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

int SendWxServerAssignmentAnswer(const CommandImpl * impl1) 
{
    // 1. Create an instance of ServerAssignmentAnswer class
    // The SendServer-Assignment-Answer command is sent by a server
    // in response to the Location-Info-Request command with
    // Command-Code = 301 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::wx::ServerAssignmentAnswer saAns;

    // Create an instance of ServerAssignmentRequest class
    ServerAssignmentRequest sareq(*impl1);

    // Get some AVP values from Request and set them to Answer Message
    const SessionId &sid1 = sareq.getSessionId();
    const OriginHost &oh1 = sareq.getOriginHost();
    const OriginRealm &or1 = sareq.getOriginRealm();
    if (sareq.containsDestinationHost())
        const DestinationHost &dh1 = sareq.getDestinationHost();
    const DestinationRealm &dr1 = sareq.getDestinationRealm();
    const AuthSessionState &authSessState = sareq.getAuthSessionState();
    const UserName &uname = sareq.getUserName();
    const VendorSpecificApplicationId 
                          &vsAppId = sareq.getVendorSpecificApplicationId();
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    saAns.setSessionId(sid1);

    saAns.setSessionIndex(sareq.getSessionIndex());

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
    saAns.setVendorSpecificApplicationId(vsAppId);

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
    saAns.setAuthSessionState(authSessState);

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
    saAns.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    saAns.setOriginRealm(originRealm);

    // [2.1] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    saAns.setUserName(uname);

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
    saAns.setResultCode(resultCode);

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
    // saAns.setExperimentalResult(experimentalResult);

    // The WLAN-User-Data AVP is of type Grouped. 
    // This AVP contains the WLAN User Profile information for 
    // the 3GPP AAA Server to authorize the service.
    WLANUserData wlanUserData;

    // The WLAN-Access AVP is of type Enumerated, and allows 
    // operators to determine barring of 3GPP-WLAN interworking subscription.
    //         WLAN_SUBSCRIPTION_ALLOWED = 0,
    //         WLAN_SUBSCRIPTION_BARRED = 1
    WLANAccess wlanAccess(WLANAccess::WLAN_SUBSCRIPTION_ALLOWED);
    wlanUserData.setWLANAccess(wlanAccess);

    //  The WLAN-3GPP-IP-Access AVP is of type Enumerated, and 
    // allows operator to disable all W-APNs for a subscriber at one time. 
    // If there is a conflict between this item and the "APN-Barring-type" 
    // flag of any W-APN, the most restrictive will prevail.
    //    WLAN_APNS_ENABLE = 0,
    //    WLAN_APNS_DISABLE = 1
    WLAN3GPPIPAccess wlan3gppIpAccess(WLAN3GPPIPAccess::WLAN_APNS_ENABLE);
    wlanUserData.setWLAN3GPPIPAccess(wlan3gppIpAccess);

    // The WLAN-Direct-IP-Access AVP is of type Enumerated, 
    // and indicate whether the user has direct access to external 
    // IP networks, e.g. Internet, from the WLAN Access Network or not.
    //     WLAN_DIRECT_IP_ACCESS = 0,
    //     WLAN_NO_DIRECT_IP_ACCESS = 1
    WLANDirectIPAccess wlanDirect(WLANDirectIPAccess::WLAN_DIRECT_IP_ACCESS);
    wlanUserData.setWLANDirectIPAccess(wlanDirect);

    // The Charging-Data AVP is of type Grouped, and contains 
    // the addresses of the charging functions.
    ChargingData chargingData;
  
    //  The Charging-Characteristics AVP is of type Integer, and contains 
    // the charging mode to be applied as described in 3GPP TS 32.215.
    ChargingCharacteristics chargingchar(20);
    chargingData.setChargingCharacteristics(chargingchar);

    // The Charging-Nodes AVP is of type Grouped, and contains the 
    // addresses of the charging functions, as described in 3GPP TS 32.240.
    ChargingNodes cnodes;

    // The Primary-Charging-Collection-Function-Name AVP is of type 
    // DiameterURI. This AVP contains the address of the Primary 
    // Charging Collection Function.
    URI uri1("PrimaryEventChargingFunction.com", URI::AAA,3880, URI::SCTP,
             URI::DIAMETER);
    PrimaryChargingCollectionFunctionName pccfn(uri1);
    cnodes.setPrimaryChargingCollectionFunctionName(pccfn);

    chargingData.setChargingNodes(cnodes);
    wlanUserData.addChargingData(chargingData);

    // Subscription-Id AVP(code 443) is of type Grouped and is used to     
    // identity the end user's subscription.
    SubscriptionId subId;

    // Subscription-Id-Type AVP(code 450) is of type Enumerated 
    // and it is used to determine which type of identifier is 
    // carried by the Subscription-Id AVP.
    //         END_USER_E164 = 0,
    //         END_USER_IMSI = 1,
    //         END_USER_SIP_URI = 2,
    //         END_USER_NAI = 3,
    //         END_USER_PRIVATE = 4
    SubscriptionIdType subIdType(SubscriptionIdType::END_USER_IMSI);
    subId.setSubscriptionIdType(subIdType);

    // Subscription-Id-Data AVP(code 444) is of type UTF8String and 
    // is used to identify the end user.
    SubscriptionIdData subIdData("John:AAAA");
    subId.setSubscriptionIdData(subIdData);
    wlanUserData.setSubscriptionId(subId);

    // Set the WLAN User Data.
    saAns.setWLANUserData(wlanUserData);

    // Set the Charging DATA grouped AVP.
    //saAns.setChargingData(chargingData);

    // These two AVPs can be set by Stack.
    // answer.addProxyInfo(diameter::base::ProxyInfo(...));
    // answer.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
  
    cout<<saAns;
    SendDiaAppMsg(saAns, sIdx);
    WxStats::GetWxStats()->UpdateSendStats(saAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}
