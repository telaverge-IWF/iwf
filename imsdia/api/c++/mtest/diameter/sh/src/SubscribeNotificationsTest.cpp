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
 * LOG: $Log: SubscribeNotificationsTest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:12  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:28:31  kamakshilk
 * LOG: Sh Interface demo for static and distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: SubscribeNotificationsTest.cpp,v 3.1 2008/03/31 10:33:12 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: SubscribeNotificationsTest.cpp,v 3.1 2008/03/31 10:33:12 nvijikumar Exp $"

#include <app.h>
#include <sh_defines.h>
#include <sh_stats.h>
#include <diameter/sh/SubscribeNotifications.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::cxdx;
using namespace diameter::sh;

extern string sessIdString;
extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the SubscribeNotificationsRequest the
 *      diameter stack. Create the SubscribeNotificationsRequest object,
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
int SendShSubscribeNotificationsRequest()
{
    // [1] Create SubscribeNotificationsRequest object.
    // Optional param error - whether this command carries an error indicator
    // Optional param retrans - whether this is a retransmission
    SubscribeNotificationsRequest snr(false,false);

    // [2] Insert data in the created SubscribeNotificationsRequest object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    AllocateSession(SH_INTERFACE_APP_ID, sIdx, sessIdString);
    snr.setSessionId(SessionId(sessIdString));

    snr.setSessionIndex(sIdx);

    // [2.2] Populate required Mandatories.
    // [2.2.1] Populate required parameter "Vendor-Specific-Application-Id".
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP identifies the supported application identifiers
    // of a Diameter node.
    // The AVP Code of Vendor-Specific-Application-Id is 631.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.2.1.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    vendorSpecificApplicationId1.addVendorId(VendorId(VENDOR_ID));

    // [2.2.1.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication
    // and Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    vendorSpecificApplicationId1.
        setAuthApplicationId(AuthApplicationId(SH_INTERFACE_APP_ID));

    // [2.2.1.3] Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting
    // portion of an application.
    // The AVP Code of Acct-Application-Id is 259.
    // vendorSpecificApplicationId1.setAcctApplicationId(AcctApplicationId(2));
    snr.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // [2.2.2] Populate required parameter "Auth-Session-State".
    // Set the Auth-Session-State AVP.
    // The data type of Vendor-Specific-Application-Id is Enumerated.
    // This AVP specifies whether state is maintained for a particular session
    // The AVP Code of Auth-Session-State is 277.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    snr.setAuthSessionState(authSessionState);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    snr.setOriginHost(OriginHost(GetOriginHost()));

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    snr.setOriginRealm(OriginRealm(GetOriginRealm()));

    // [2.2.5] Populate required parameter "Destination-Realm".
    // Set the Destination-Realm AVP.
    // The data type of Destination-Realm is DiameterIdentity.
    // This AVP contains the Realm the message is to be routed to.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Destination-Realm is 283.
    snr.setDestinationRealm(DestinationRealm(GetDestinationRealm()));

    // [2.2.6] Populate required parameter "User-Identity".
    // Set the User-Identity AVP.
    // The data type of Destination-Realm is Grouped.
    // This AVP contains either Public Identity or an MSISDN AVP.
    // The AVP Code of User-Identity is 700.
    UserIdentity userIdentity;

    // [2.2.6.1] Populate required parameter "Public-Identity".
    // Set the Public-Identity AVP.
    // The data type of Public-Identity is UTF8String.
    // This AVP contains the public identity of a user in the IMS
    // The AVP Code of Public-Identity is 601.
    userIdentity.setPublicIdentity(PublicIdentity("sip:user@3gppnetwork.com"));

    // [2.2.6.2] Populate required parameter "MSISDN".
    // Set the MSISDN AVP.
    // The data type of MSISDN is OctetString.
    // This AVP contains an MSISDN, in international number format as 
    // described in ITU-T Rec E.164, encoded as a TBCD-string, i.e. 
    // digits from 0 through 9 are encoded 0000 to 1001; 1111 is used
    // as a filler when there is an odd number of digits; bits 8 to 5 
    // of octet n encode digit 2n; bits 4 to 1 of octet n encode digit
    // 2(n-1)+1.
    // The AVP Code of MSISDN is 701.
    userIdentity.setMSISDN(MSISDN("3217260686"));
    snr.setUserIdentity(userIdentity);

    // [2.2.7] Populate required parameter "Subs-Req-Type".
    // Set the Subs-Req-Type AVP.
    // The data type of Subs-Req-Type is Enumerated.
    // This AVP indicates the type of the subscription-to-notifications
    // request. The following values are defined:
    // 1) Subscribe
    // 2) Unsubscribe
    // The AVP Code of Subs-Req-Type is 705.
    snr.setSubsReqType(SubsReqType(SubsReqType::Subscribe));

    // [2.2.8] Populate required parameter "Data-Reference".
    // Set the Data-Reference AVP.
    // The data type of Data-Reference is Enumerated.
    // This AVP indicates the type of the requested user data 
    // in the operation UDR and SNR.
    // The AVP Code of Data-Reference is 703.
    snr.setDataReference(DataReference(DataReference::RepositoryData));

    // [2.2.9] Populate optional parameter "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of User-Data is DiameterIdentity.
    // This AVP contains the Host the message is to be routed to.
    // The absence of the Destination-Host AVP will cause a message to be
    // sent to any Diameter server supporting the application within the
    // realm specified in Destination-Realm AVP.
    // The AVP Code of Destination-Host is 293.
    snr.setDestinationHost(DestinationHost(GetDestinationHost()));

    // [2.2.10] Populate optional parameter "Supported-Features".
    // Set the Supported-Features AVP.
    // The data type of User-Data is Grouped.
    // If this AVP is present it may inform the destination host about
    // the features that the origin host supports.
    // The AVP Code of Supported-Features is 628.
    SupportedFeatures supportedFeatures;

    // [2.2.10.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    supportedFeatures.setVendorId(VendorId(VENDOR_ID));

    // [2.2.10.2] Populate required parameter "Feature-List-ID".
    // Set the Feature-List-ID AVP.
    // The data type of Feature-List-ID is Unsigned32.
    // This AVP contains the identity of a feature list
    // The AVP Code of Feature-List-ID is 629.
    supportedFeatures.setFeatureListID(FeatureListID(1u));

    // [2.2.10.3] Populate required parameter "Feature-List".
    // Set the Feature-List AVP.
    // The data type of Feature-List is Unsigned32.
    // This AVP contains a bit mask indicating the supported features
    // of an application.
    // The AVP Code of Feature-List is 630.
    supportedFeatures.setFeatureList(FeatureList(1u));

    snr.addSupportedFeatures(supportedFeatures);

    // [2.2.11] Populate required parameter "Service-Indication".
    // Set the Service-Indication AVP.
    // The data type of Service-Indication is OctateString.
    // If this AVP contains the Service Indication that identifies
    // a service in an AS.
    // The AVP Code of Service-Indication is 704.
    snr.setServiceIndication(ServiceIndication("Video Sharing"));

    // [2.2.12] Populate required parameter "Server-Name".
    // Set the Server-Name AVP.
    // The data type of Server-Name is UTF8String.
    // If this AVP contains a SIP-URL (as defined in IETF RFC 3261 and IETF
    // RFC 2396), used to identify a SIP server (e.g. S-CSCF name).
    // The AVP Code of Server-Name is 602.
    snr.setServerName(ServerName("sip:cscf@3gppnetwork.com"));

    // [2.2.13] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // [2.2.13.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info 
    // AVP.
    // The AVP Code of Proxy-Info is 280.
    //proxyInfo1.setProxyHost(ProxyHost("proxyHost1"));
    //proxyInfo2.setProxyHost(ProxyHost("proxyHost2"));

    // [2.2.13.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated
    // as opaque data
    // The AVP Code of Proxy-State is 33.
    //proxyInfo1.setProxyState(ProxyState("proxyState1"));
    //proxyInfo2.setProxyState(ProxyState("proxyState2"));

    // Stack sets this AVP.
    // Application should not set this AVP
    // snr.addProxyInfo(proxyInfo1);
    // snr.addProxyInfo(proxyInfo2);

    // [2.2.14] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the  message.
    // The AVP Code of Route-Record is 282.
    //RouteRecord routeRecord1("routeRecord1"),routeRecord2("routeRecord2");

    // Stack sets this AVP.
    // Application should not set this AVP
    // snr.addRouteRecord(routeRecord1);
    // snr.addRouteRecord(routeRecord2);

    // [3] Use appropriate application specific logic to Send object

    if (appMode == UNIT_TEST)
        cout << snr;

    SendDiaAppMsg(snr, sIdx);
    ShStats::GetShStats()->UpdateSendStats(snr.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the SubscribeNotifications
 *      request made by the diameter stack. Create the
 *      SubscribeNotificationsAnswer object, populate the AVPs and send the
 *      message to the stack. send message to Diameter Stack
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
int SendShSubscribeNotificationsAnswer(const CommandImpl * impl)
{
    // [1] Create SubscribeNotificationsAnswer object.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    SubscribeNotificationsAnswer sna(false,false);

    SubscribeNotificationsRequest snreq(*impl);

    const AuthSessionState& authSessSt = snreq.getAuthSessionState();
    //const VendorSpecificApplicationId & vsid = snreq.
    //    getVendorSpecificApplicationId();
    //const SupportedFeatures& sf = snreq.getSupportedFeatures(1);
    //const ProxyInfo &proxyInfo11 = snreq.getProxyInfo(1);
    //const ProxyInfo& proxyInfo12 = snreq.getProxyInfo(2);

    // [2] Insert data in the created SubscribeNotificationsAnswer object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    const SessionId& sid = snreq.getSessionId();
    sna.setSessionId(sid);

    // [2.2] Populate required Mandatories.
    // [2.2.1] Populate required parameter "Vendor-Specific-Application-Id".
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP identifies the supported application identifiers
    // of a Diameter node.
    // The AVP Code of Vendor-Specific-Application-Id is 631.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.2.1.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    vendorSpecificApplicationId1.addVendorId(VendorId(VENDOR_ID));

    // [2.2.1.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication
    // and Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    vendorSpecificApplicationId1.
        setAuthApplicationId(AuthApplicationId(SH_INTERFACE_APP_ID));

    // [2.2.1.3] Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting
    // portion of an application.
    // The AVP Code of Acct-Application-Id is 259.
    // vendorSpecificApplicationId1.setAcctApplicationId(AcctApplicationId(2));
    sna.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // [2.2.2] Populate required parameter "Auth-Session-State".
    // Set the Auth-Session-State AVP.
    // The data type of Vendor-Specific-Application-Id is Enumerated.
    // This AVP specifies whether state is maintained for a particular session
    // The AVP Code of Auth-Session-State is 277.
    sna.setAuthSessionState(authSessSt);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    const DestinationHost &dh1 = snreq.getDestinationHost();
    sna.setOriginHost(OriginHost(dh1.value()));

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    const DestinationRealm &dr1 = snreq.getDestinationRealm();
    sna.setOriginRealm(OriginRealm(dr1.value()));

    // [2.2.5] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    sna.setResultCode(ResultCode(2001u));

    // [2.2.6] Populate required parameter "Experimental-Result".
    // Set the Experimental-Result AVP.
    // The data type of Experimental-Result is Grouped.
    // This AVP indicates whether a particular vendor-specific request 
    // was completed successfully or whether an error occurred.
    // The AVP Code of Experimental-Result is 297.
    // ResultCode and ExperimentalResult both shouldnot be set.
    //ExperimentalResult experimentalResult;

    // [2.2.6.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    //experimentalResult.setVendorId(VendorId(VENDOR_ID));

    // [2.2.6.2] Populate required parameter "Experimental-Result-Code".
    // Set the Experimental-Result-Code AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP contains a vendor-assigned value representing the result of
    // processing the request.
    // The AVP Code of Experimental-Result-Code is 298.
    //ExperimentalResultCode experimentalResultCode(100u);
    //experimentalResult.setExperimentalResultCode(experimentalResultCode);

    //sna.setExperimentalResult(experimentalResult);

    // [2.2.7] Populate optional parameter "Supported-Features".
    // Set the Supported-Features AVP.
    // The data type of User-Data is Grouped.
    // If this AVP is present it may inform the destination host about
    // the features that the origin host supports.
    // The AVP Code of Supported-Features is 628.
    SupportedFeatures supportedFeatures;

    // [2.2.7.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    supportedFeatures.setVendorId(VendorId(VENDOR_ID));

    // [2.2.7.2] Populate required parameter "Feature-List-ID".
    // Set the Feature-List-ID AVP.
    // The data type of Feature-List-ID is Unsigned32.
    // This AVP contains the identity of a feature list
    // The AVP Code of Feature-List-ID is 629.
    supportedFeatures.setFeatureListID(FeatureListID(1u));

    // [2.2.7.3] Populate required parameter "Feature-List".
    // Set the Feature-List AVP.
    // The data type of Feature-List is Unsigned32.
    // This AVP contains a bit mask indicating the supported features
    // of an application.
    // The AVP Code of Feature-List is 630.
    supportedFeatures.setFeatureList(FeatureList(1u));
    sna.addSupportedFeatures(supportedFeatures);

    // [2.2.8] Populate required parameter "Failed-AVP".
    // Set the Failed-AVP AVP.
    // The data type of Feature-List is Grouped.
    // This AVP provides debugging information in cases where a request is
    // rejected or not fully processed due to erroneous information in a
    // specific AVP. The value of the Result-Code AVP will provide 
    // information on the reason for the Failed-AVP AVP.
    // The AVP Code of Feature-List is 297.
    // FailedAVP failedAVP;
    // sna.addFailedAVP(failedAVP);

    // [2.2.9] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo proxyInfo1;
    //ProxyInfo proxyInfo2;

    // [2.2.9.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info 
    // AVP.
    // The AVP Code of Proxy-Info is 280.
    //proxyInfo1.setProxyHost(ProxyHost("proxyHost1"));
    //proxyInfo2.setProxyHost(ProxyHost("proxyHost2"));

    // [2.2.9.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated as
    // opaque data
    // The AVP Code of Proxy-State is 33.
    //proxyInfo1.setProxyState(ProxyState("proxyState1"));
    //proxyInfo2.setProxyState(ProxyState("proxyState2"));

    // Stack sets this AVP.
    // Application should not set this AVP
    // sna.addProxyInfo(proxyInfo1);
    // sna.addProxyInfo(proxyInfo2);

    // [2.2.10] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the  message.
    // The AVP Code of Route-Record is 282.
    for(int i =0; i < snreq.countRouteRecord(); i++)
    {
       const RouteRecord & rRec = snreq.getRouteRecord(i);

       // Stack sets this AVP.
      // Application should not set this AVP
      // sna.addRouteRecord(rRec);
    }

    // [3] Use appropriate application specific logic to Send object

    if (appMode == UNIT_TEST)
        cout << sna;

    SendDiaAppMsg(sna, sIdx);
    ShStats::GetShStats()->UpdateSendStats(sna.getCommandCode(), ITS_FALSE);
    return (ITS_SUCCESS);
}

