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
 * LOG: Revision 3.1  2008/03/31 10:33:12  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:28:31  kamakshilk
 * LOG: Sh Interface demo for static and distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: UserDataTest.cpp,v 3.1 2008/03/31 10:33:12 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: UserDataTest.cpp,v 3.1 2008/03/31 10:33:12 nvijikumar Exp $"

#include <app.h>
#include <sh_defines.h>
#include <sh_stats.h>
#include <diameter/sh/UserData.h>

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
int SendShUserDataRequest()
{
    // [1] Create UserDataRequest object.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    UserDataRequest udr(false,false);

    // [2] Insert data in the created UserDataRequest object.
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
    udr.setSessionId(SessionId(sessIdString));

    udr.setSessionIndex(sIdx);

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

    // Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting
    // portion of an application.
    // The AVP Code of Acct-Application-Id is 259.
    vendorSpecificApplicationId1.setAcctApplicationId(AcctApplicationId(2));
    udr.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // [2.2.2] Populate required parameter "Auth-Session-State".
    // Set the Auth-Session-State AVP.
    // The data type of Vendor-Specific-Application-Id is Enumerated.
    // This AVP specifies whether state is maintained for a particular session
    // The AVP Code of Auth-Session-State is 277.
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    udr.setAuthSessionState(authSessionState);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    udr.setOriginHost(OriginHost(GetOriginHost()));

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    udr.setOriginRealm(OriginRealm(GetOriginRealm()));

    // [2.2.5] Populate required parameter "Destination-Realm".
    // Set the Destination-Realm AVP.
    // The data type of Destination-Realm is DiameterIdentity.
    // This AVP contains the Realm the message is to be routed to.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Destination-Realm is 283.
    udr.setDestinationRealm(DestinationRealm(GetDestinationRealm()));

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
    udr.setUserIdentity(userIdentity);

    // [2.2.7] Populate required parameter "Data-Reference".
    // Set the Data-Reference AVP.
    // The data type of Data-Reference is Enumerated.
    // This AVP indicates the type of the requested user data 
    // in the operation UDR and SNR.
    // The AVP Code of Data-Reference is 703.
    udr.setDataReference(DataReference(DataReference::Value(0)));

    // [2.2.8] Populate optional parameter "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of User-Data is DiameterIdentity.
    // This AVP contains the Host the message is to be routed to.
    // The absence of the Destination-Host AVP will cause a message to be
    // sent to any Diameter server supporting the application within the
    // realm specified in Destination-Realm AVP.
    // The AVP Code of Destination-Host is 293.
    udr.setDestinationHost(DestinationHost(GetDestinationHost()));

    // [2.2.9] Populate optional parameter "Supported-Features".
    // Set the Supported-Features AVP.
    // The data type of User-Data is Grouped.
    // If this AVP is present it may inform the destination host about
    // the features that the origin host supports.
    // The AVP Code of Supported-Features is 628.
    SupportedFeatures supportedFeatures;

    // [2.2.9.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    supportedFeatures.setVendorId(VendorId(VENDOR_ID));

    // [2.2.9.2] Populate required parameter "Feature-List-ID".
    // Set the Feature-List-ID AVP.
    // The data type of Feature-List-ID is Unsigned32.
    // This AVP contains the identity of a feature list
    // The AVP Code of Feature-List-ID is 629.
    supportedFeatures.setFeatureListID(FeatureListID(1u));

    // [2.2.9.3] Populate required parameter "Feature-List".
    // Set the Feature-List AVP.
    // The data type of Feature-List is Unsigned32.
    // This AVP contains a bit mask indicating the supported features
    // of an application.
    // The AVP Code of Feature-List is 630.
    supportedFeatures.setFeatureList(FeatureList(1u));
    udr.addSupportedFeatures(supportedFeatures);

    // [2.2.10] Populate required parameter "Server-Name".
    // Set the Server-Name AVP.
    // The data type of Server-Name is UTF8String.
    // If this AVP contains a SIP-URL (as defined in IETF RFC 3261 and IETF
    // RFC 2396), used to identify a SIP server (e.g. S-CSCF name).
    // The AVP Code of Server-Name is 602.
    udr.setServerName(ServerName("sip:cscf@3gppnetwork.com"));

    // [2.2.11] Populate required parameter "Service-Indication".
    // Set the Service-Indication AVP.
    // The data type of Service-Indication is OctateString.
    // If this AVP contains the Service Indication that identifies
    // a service in an AS.
    // The AVP Code of Service-Indication is 704.
    udr.setServiceIndication(ServiceIndication("Video Sharing"));

    // [2.2.12] Populate required parameter "Identity-Set".
    // Set the Identity-Set AVP.
    // The data type of Identity-Set is Enumerated.
    // If this AVP indicates the requested set of IMS Public Identities.
    // The following values are defined:
    // ALL_IDENTITIES (0)
    // REGISTERED_IDENTITIES (1)
    // IMPLICIT_IDENTITIES (2)
    // The AVP Code of Identity-Set is 708.
    udr.setIdentitySet(IdentitySet(IdentitySet::ALL_IDENTITIES));

    // [2.2.13] Populate required parameter "Requested-Domain".
    // Set the Requested-Domain AVP.
    // The data type of Requested-Domain is Enumerated.
    // If this AVP indicates the access domain for which certain data 
    // (e.g. user state) are requested. The following values are defined:
    // CS-Domain (0) -> The requested data apply to the CS domain.
    // PS-Domain (1) -> The requested data apply to the PS domain.
    // The AVP Code of Requested-Domain is 706.
    udr.setRequestedDomain(RequestedDomain(RequestedDomain::Value(0)));

    // [2.2.14] Populate required parameter "Current-Location".
    // Set the Current-Location AVP.
    // The data type of Current-Location is Enumerated.
    // If this AVP indicates whether an active location retrieval has 
    // to be initiated or not:
    // DoNotNeedInitiateActiveLocationRetrieval (0)
    // InitiateActiveLocationRetrieval (1)
    // The AVP Code of Current-Location is 707.
    udr.setCurrentLocation(CurrentLocation(CurrentLocation::
                          DoNotNeedInitiateActiveLocationRetrieval));

    // [2.2.15] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // [2.2.15.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info 
    // AVP.
    // The AVP Code of Proxy-Info is 280.
    //proxyInfo1.setProxyHost(ProxyHost("nemo"));
    //proxyInfo2.setProxyHost(ProxyHost("nemo"));

    // [2.2.15.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated
    // as opaque data
    // The AVP Code of Proxy-State is 33.
    //proxyInfo1.setProxyState(ProxyState("proxyState1"));
    //proxyInfo2.setProxyState(ProxyState("proxyState2"));

    // Stack sets this AVP.
    // Application should not set this AVP
    // udr.addProxyInfo(proxyInfo1);
    // udr.addProxyInfo(proxyInfo2);

    // [2.2.16] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the  message.
    // The AVP Code of Route-Record is 282.
    //RouteRecord routeRecord1("nemocl"), routeRecord2("jerry");

    // Stack sets this AVP.
    // Application should not set this AVP
    // udr.addRouteRecord(routeRecord1);
    // udr.addRouteRecord(routeRecord2);

    // [3] Use appropriate application specific logic to Send object

    if (appMode == UNIT_TEST)
        cout << udr;

    // Send object to stack.
    SendDiaAppMsg(udr, sIdx);

    ShStats::GetShStats()->UpdateSendStats(udr.getCommandCode(), ITS_TRUE);
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
int SendShUserDataAnswer(const CommandImpl * impl)
{
    // [1] Create UserDataAnswer object.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    UserDataAnswer uda(false,false);

    UserDataRequest udreq(*impl);

    //for (int i = 0; i < udreq.countRouteRecord(); i++)
    //{
    //    const RouteRecord& rr = udreq.getRouteRecord(i);
    //}

    // [2] Insert data in the created UserDataAnswer object.
    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.
    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // Set the Session-Id AVP.
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    const SessionId& sid = udreq.getSessionId();
    uda.setSessionId(sid);

    uda.setSessionIndex(udreq.getSessionIndex());

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
    uda.setVendorSpecificApplicationId( vendorSpecificApplicationId1);

    // [2.2.2] Populate required parameter "Auth-Session-State".
    // Set the Auth-Session-State AVP.
    // The data type of Vendor-Specific-Application-Id is Enumerated.
    // This AVP specifies whether state is maintained for a particular session
    // The AVP Code of Auth-Session-State is 277.
    const AuthSessionState& asessionstate = udreq.getAuthSessionState();
    uda.setAuthSessionState(asessionstate);

    // [2.2.3] Populate required parameter "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    const DestinationHost &dh1 = udreq.getDestinationHost();
    uda.setOriginHost(OriginHost(dh1.value()));

    // [2.2.4] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    const DestinationRealm &dr1 = udreq.getDestinationRealm();
    uda.setOriginRealm(OriginRealm(dr1.value()));

    // [2.2.5] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    uda.setResultCode(ResultCode(2001u));

    // [2.2.6] Populate required parameter "Experimental-Result".
    // Set the Experimental-Result AVP.
    // The data type of Experimental-Result is Grouped.
    // This AVP indicates whether a particular vendor-specific request 
    // was completed successfully or whether an error occurred.
    // The AVP Code of Experimental-Result is 297.
    // ResultCode AVP is already been set, it is not required to set.
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
    //ExperimentalResultCode experimentalResultCode(2001u);
    //experimentalResult.setExperimentalResultCode(experimentalResultCode);

    //uda.setExperimentalResult(experimentalResult);

    // [2.2.8] Populate required parameter "User-Data".
    // Set the User-Data AVP.
    // The data type of User-Data is OctateString.
    // This AVP contains the user data requested in the PUR and SNR 
    // operations and the data to be modified in the UPR operation
    // The AVP Code of User-data is 702.
    if (appMode == UNIT_TEST)
    {
        uda.setShUserData(ShUserData(subsProfile));
    }
    else
    {
        ShUserData userData(ShUserData("UserData"));
        uda.setShUserData(userData);
    }

    //SupportedFeatures supportedFeatures;

    //supportedFeatures.setVendorId(VendorId(VENDOR_ID));
    //supportedFeatures.setFeatureListID(FeatureListID(1u));
    //supportedFeatures.setFeatureList(FeatureList(1u));
    //uda.addSupportedFeatures(sf);

    //FailedAVP failedAVP;
    //uda.addFailedAVP(failedAVP);

    //ProxyInfo proxyInfo1,proxyInfo2;
    //proxyInfo1.setProxyHost(ProxyHost("proxyHost1"));
    //proxyInfo2.setProxyHost(ProxyHost("proxyHost2"));
    //proxyInfo1.setProxyState(ProxyState("proxyState1"));
    //proxyInfo2.setProxyState(ProxyState("proxyState2"));
    //uda.addProxyInfo(pInfo1);
    //uda.addProxyInfo(pInfo2);

    // Stack sets this AVP.
    // Application should not set this AVP
    //uda.addRouteRecord(rr1);
    //uda.addRouteRecord(rr2);

    // [3] Use appropriate application specific logic to Send object

    if (appMode == UNIT_TEST)
        cout << uda;

    // Send Object to stack.
    SendDiaAppMsg(uda, sIdx);

    // Update stats.
    ShStats::GetShStats()->UpdateSendStats(uda.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}

