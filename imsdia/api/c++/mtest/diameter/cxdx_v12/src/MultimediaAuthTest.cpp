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
 * LOG: $Log: MultimediaAuthTest.cpp,v $
 * LOG: Revision 1.1.2.1  2015/05/18 05:15:10  kpnithin
 * LOG: cxdx v12 Test tool developed with new protocol file
 * LOG:
 * LOG: Revision 1.1.6.2  2015/01/07 07:28:52  ncshivakumar
 * LOG: Merged
 * LOG:
 * LOG: Revision 1.1.4.3  2014/11/18 10:08:57  ahemanth
 * LOG: Fix for bug 5277.
 * LOG:
 * LOG: Revision 1.1.4.2  2014/11/12 04:51:29  ncshivakumar
 * LOG: merged from Aicent branch
 * LOG:
 * LOG: Revision 1.1.2.1  2014/11/03 09:30:42  venkat
 * LOG: Added cxdx_v10
 * LOG:
 * LOG: Revision 1.1.2.1.2.1  2013/07/01 09:40:50  nazad
 * LOG: changes done as mentioned by malli
 * LOG:
 * LOG: Revision 1.1.2.1  2013/04/05 13:11:47  jvikram
 * LOG: Include cx/dx and sh interface test code
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:08  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:21:14  kamakshilk
 * LOG: Demo program for Cxdx Interface
 * LOG:
 * LOG:
 *
 * ID: $Id: MultimediaAuthTest.cpp,v 1.1.2.1 2015/05/18 05:15:10 kpnithin Exp $
 ****************************************************************************/
#ident "$Id: MultimediaAuthTest.cpp,v 1.1.2.1 2015/05/18 05:15:10 kpnithin Exp $"

#include <app.h>
#include <cxdx_defines.h>
#include <cxdx_stats.h>
#include <diameter/cxdx_v12/MultimediaAuth.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::cxdx_v12;

extern string sessIdString;
extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the  MultimediaAuthenticationRequest to the
 *      diameter stack. Create the  MultimediaAuthenticationRequest object,
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
int SendCxdxMultimediaAuthRequest()
{
    // [1]. Create an instance of MultimediaAuthRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    MultimediaAuthRequest mar(false, false);

    // [2.1.1.x] Fixed AVP    
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(CXDX_INTERFACE_APP_ID, sIdx, sessIdString);
    mar.setSessionId(SessionId(sessIdString));

    mar.setSessionIndex(sIdx);

    // [2.1.2.x] Required AVPs

    // [2.1.2.1.1]Create a Vendor-Specific-Application-Id AVP object
    // Vendor-Specific-Application-Id AVP is a Grouped type AVP and
    // is used to advertise support of a vendor-specific Diameter application.
    // Exactly one of the Auth-Application-Id and Acct-Application-Id
    // AVPs may be present.
    // This AVP must also be present as the first AVP in all experimental
    // commands defined in the vendor-specific application.
    // This AVP should be placed as close to the Diameter header as possible.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.1.2.1.2] Populate required parameter "Vendor-Id".
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
    // [2.1.2.1.3] The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.

    AuthApplicationId authApplicationId(CXDX_INTERFACE_APP_ID);

    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // [2.1.2.1.4] Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting 
    // messages.Exactly one of the Auth-Application-Id AVP and Acct-
    // Application-Id may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    //[2.1.2.1] Set the  Vendor-Specific-Application-Id AVP.
    mar.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    // [2.1.2.2]Create a Auth-Session-State AVP object.
    // The Auth-Session-State AVP is specifies whether state is
    // maintained for a particular session.
    // The AVP Code of Auth-Session-State AVP is 277
    // The data type of Auth-Session-State AVP is Enumerated with
    // the following values
    // {
    //  STATE_MAINTAINED(0),
    //  NO_STATE_MAINTAINED(1)
    // }
    AuthSessionState authSessionState(AuthSessionState::NO_STATE_MAINTAINED);
    mar.setAuthSessionState(authSessionState);

    // [2.1.2.3] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    mar.setOriginHost(originHost);

    // [2.1.2.4] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    mar.setOriginRealm(originRealm);

    // [2.1.2.5] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    mar.setDestinationRealm(destinationRealm);

    // [2.1.2.6] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    mar.setUserName(userName);

    // [2.1.2.7] Set the Public-Identity AVP.
    //The Public-Identity AVP contains the public identity of a user in the IMS.
    // The AVP Code of Public-Identity AVP is 601
    // The data type of Public-Identity AVP is UTF8String.
    PublicIdentity publicIdentity("sip:user@intellinet-tech.com");
    mar.setPublicIdentity(publicIdentity);

    // [2.1.2.8] Set the Server-Name AVP.
    // The Server-Name AVP contains a SIP-URL and used to
    // identify a SIP server (e.g. S-CSCF name).
    // The AVP Code of AVP is 602.
    // The data type of AVP is UTF8String.
    ServerName serverName("sip:cscf@3gppnetwork.com");
    mar.setServerName(serverName);

    // [2.2.x] Optional AVPS

    // [2.2.1] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    if(GetDestinationHost())
    {
    	DestinationHost destinationHost(GetDestinationHost());
    	mar.setDestinationHost(destinationHost);
    }

    SupportedFeatures supportedFeatures;
    supportedFeatures.setVendorId(VendorId(1u));
    supportedFeatures.setFeatureListID(FeatureListID(1u));
    supportedFeatures.setFeatureList(FeatureList(1u));

    mar.addSupportedFeatures(supportedFeatures);

    // [2.2.2] Set the SIP-Number-Auth-Items AVP.
    // The SIP-Number-Auth-Items AVP indicates the number of
    // The AVP Code of SIP-Number-Auth-Items AVP is 607
    // The Data Type of SIP-Number-Auth-Items AVP is Unsigned32
    SIPNumberAuthItems sIPNumberAuthItems(1u);
    mar.setSIPNumberAuthItems(sIPNumberAuthItems);

    // Create a SIP-Auth-Data-Item AVP object
    SIPAuthDataItem sIPAuthDataItem;

    // [2.2.3.1] Set the SIP-Item-Number AVP.
    // The SIP-Item-Number AVPs indicate the order in which the
    // multiple occurrences of SIP-Auth-Data-Item AVP has to be processed.
    // The SIP-Item-Number AVP Code of AVP is 613
    // The Data Type of SIP-Item-Number AVP is Unsigned32
    SIPItemNumber sIPItemNumber(1u);
    sIPAuthDataItem.setSIPItemNumber(sIPItemNumber);

    // [2.2.3.2] Set the SIP-Authentication-Scheme AVP.
    // The SIP-Authentication-Scheme AVP indicates the authentication
    // scheme used in the authentication of SIP messages.
    // The AVP Code of SIP-Authentication-Scheme AVP is 608
    // The Data Type of SIP-Authentication-Scheme AVP is UTF8String
    SIPAuthenticationScheme sIPAuthenticationScheme("127");
    sIPAuthDataItem.setSIPAuthenticationScheme(sIPAuthenticationScheme);

    // [2.2.3.3] Set the SIP-Authenticate AVP.
    // The SIP-Authenticate AVP.
    // The AVP Code of SIP-Authenticate AVP is 609
    // The Data Type of SIP-Authenticate AVP is OctetString
    SIPAuthenticate sIPAuthenticate("1234567");
    sIPAuthDataItem.setSIPAuthenticate(sIPAuthenticate);

    // [2.2.3.4] Set the SIP-Authorization AVP.
    // The SIP-Authorization AVP contains authentication-related
    // information relevant for performing the authentication but
    // that is not part of the SIP authentication headers.
    // The AVP Code of AVP is 610
    // The Data Type of AVP is OctetString
    SIPAuthorization sIPAuthorization("1234567");
    sIPAuthDataItem.setSIPAuthorization(sIPAuthorization);

    // [2.2.3.5] Set the SIP-Authentication-Context AVP.
    // SIP-Authentication-Context AVP contains authentication-
    // related information relevant for performing the authentication
    // but that is not part of the SIP authentication headers.
    // The AVP Code of AVP is 611
    // The Data Type of AVP is OctetString
    SIPAuthenticationContext sIPAuthenticationContext("1234567");
    sIPAuthDataItem.setSIPAuthenticationContext(sIPAuthenticationContext);

    // [2.2.3.6] Set the Confidentiality-Key AVP.
    // The Confidentiality-Key AVP contains the Confidentiality Key.
    // The AVP Code of AVP is 625
    // The Data Type of AVP is OctetString
    ConfidentialityKey confidentialityKey("1234567");
    sIPAuthDataItem.setConfidentialityKey(confidentialityKey);

    // [2.2.3.7] Set the Integrity-Key AVP.
    // The Integrity-Key AVP contains the Integrity Key.
    // The AVP Code of AVP is 626
    // The Data Type of AVP is OctetString
    IntegrityKey integrityKey("1234567");
    sIPAuthDataItem.setIntegrityKey(integrityKey);
    
    FramedIPAddress framedIpAddress("172.16.12.221");
    sIPAuthDataItem.setFramedIPAddress(framedIpAddress);

    FramedIPv6Prefix framedIpv6Prefix("fe80::ea40:f2ff:fe3c:9001");
    sIPAuthDataItem.setFramedIPv6Prefix(framedIpv6Prefix);

    FramedInterfaceId framedInterfaceId(1u);
    sIPAuthDataItem.setFramedInterfaceId(framedInterfaceId);


    // [2.2.3] Set the SIP-Auth-Data-Item AVP.
    // The SIP-Auth-Data-Item AVP contains the authentication and/or
    // the authorization for the Diameter client.
    // The AVP Code of SIP-Auth-Data-Item AVP is 612
    // The Data Type of SIP-Auth-Data-Item AVP is Grouped
    mar.setSIPAuthDataItem(sIPAuthDataItem);

    // [2.2.4.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // [2.2.4.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"), proxyHost2("proxyHost2");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // [2.2.4.3] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState proxyState1("proxyState1"), proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // [2.2.4] Set the Proxy-Info AVP.
    // Application should not set this AVP.
    // mar.addProxyInfo(proxyInfo2);

    // [2.2.5] Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord routeRecord1("nemo"), routeRecord2("nemocl");

    // [2.2.5] Set the Route-Record AVP.
    // Application should not set this AVP.
    // mar.addRouteRecord(routeRecord1);
    // mar.addRouteRecord(routeRecord2);

    // 3. Send the encoded MultimediaAuthRequest object to an output stream
    // buffer(Note: For test purpose, the object is being sent to ios::cout
    // output buffer.

    cout << mar;

    // Send object to stack.
    SendDiaAppMsg(mar, sIdx);

    CxdxStats::GetCxdxStats()->UpdateSendStats(mar.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends the Answer to the MultimediaAuthentication request
 *      made by the diameter stack. Create the MultimediaAuthAnswer
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
int SendCxdxMultimediaAuthAnswer(const CommandImpl * impl)
{
    // 1. Create an instance of MultimediaAuthAnswer class
    // The Multimedia-Auth-Answer command is sent by a server
    // in response to the Multimedia-Auth-Request command with
    // Command-Code = 303 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    MultimediaAuthAnswer maa(false, false);

    // Create an instance of MultimediaAuthRequest class to get host and 
    // session details
    MultimediaAuthRequest rreq(*impl);
    
    bool isNull;
    bool isAVPEnabled;
    bool isExpAVPEnabled;
    Json::Value l_jsonRoot = parseCxdxConfig();

    Json::Value* m_jsonRoot = &l_jsonRoot;
    Json::Value* m_jsonRoot1 = &(*m_jsonRoot)["cxdx_v12"];
    Json::Value* cfg = &(*m_jsonRoot1)["MultimediaAuthTestAnswer"];


    // Get AVP values from requested message
    const SessionId &sid1 = rreq.getSessionId();
    const OriginHost &oh1 = rreq.getOriginHost();
    const OriginRealm &or1 = rreq.getOriginRealm();
    const DestinationRealm &dr1 = rreq.getDestinationRealm();

    // 2. Create the instances of the classes describing the various
    // AVPs' present in an MultimediaAuthAnswer command and
    // pass them by value to the corresponding data members set
    // methods of the MultimediaAuthAnswer object created
    // in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    maa.setSessionId(sid1);

    maa.setSessionIndex(rreq.getSessionIndex());

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
    VendorSpecificApplicationId vendorSpecificApplicationId1;

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
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(CXDX_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // Set the Acct-Application-Id AVP.
    // The Acct-Application-Id AVP is used in order to advertise support
    // of Accounting portion of an application.
    // The Acct-Application-Id AVP must be present in all the Accounting
    // messages.
    // Exactly one of the Auth-Application-Id AVP and Acct-Application-Id
    // may be present.
    // The AVP Code of is 259
    // The data type of is Unsigned32.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    // [2.1.1] Set the  Vendor-Specific-Application-Id AVP.
    maa.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

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
    AuthSessionState authSessionState(AuthSessionState::NO_STATE_MAINTAINED);
    maa.setAuthSessionState(authSessionState);

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
    
    if(GetOriginHost()){
         OriginHost originHost(GetOriginHost());
         maa.setOriginHost(originHost);
    }
    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(dr1.value());
    maa.setOriginRealm(originRealm);

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
    // The AVP Code of Result-Code AVP is 268.
    // The data type of Result-Code AVP is Unsigned32.
    // already ExperimentalResult is been set

    isAVPEnabled = (*cfg)["ResultCode"]["Enabled"].asBool();
    isNull = (*cfg)["ResultCode"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        ResultCode resultCode((*cfg)["ResultCode"]["Value"].asInt());
        maa.setResultCode(resultCode);
    }

    // Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of Experimental-Result AVP is 297.
    // The data type of Experimental-Result AVP is Grouped Type.
    isExpAVPEnabled = (*cfg)["Experimental-Result"]["Enabled"].asBool();
    if(isExpAVPEnabled)
    {
        ExperimentalResult experimentalResult;

        // Set the Vendor-Id AVP in Experimental-Result AVP.
        // The Vendor-Id AVP in the Experimental-Result AVP indicates
        // whether a particular vendor-specific request was completed
        // successfully or whether an error occurred.
        VendorId vendorId1(VENDOR_ID);
        experimentalResult.setVendorId(vendorId1);

        // Set the Experimental-Result-Code AVP.
        // The Experimental-Result-Code AVP contains a vendor-assigned
        // value representing the result of processing the request.
        // The AVP Code of AVP is 298 .
        // The data type of AVP is Unsigned32.
        //ExperimentalResultCode experimentalResultCode(2001u);
        //experimentalResult.setExperimentalResultCode(experimentalResultCode);

        // [2.2] Set the Experimental-Result AVP.
        maa.setExperimentalResult(experimentalResult);
    }

    // [2.1] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    maa.setUserName(userName);
    
    SupportedFeatures supportedFeatures;
    supportedFeatures.setVendorId(VendorId(1u));
    supportedFeatures.setFeatureListID(FeatureListID(1u));
    supportedFeatures.setFeatureList(FeatureList(1u));

    maa.addSupportedFeatures(supportedFeatures);

    // [2.1] Set the Public-Identity AVP.
    // The Public-Identity AVP contains the public identity of a
    // user in the IMS.
    // The AVP Code of Public-Identity AVP is 601
    // The data type of Public-Identity AVP is UTF8String.
    PublicIdentity publicIdentity("sip:user@intellinet-tech.com");
    maa.setPublicIdentity(publicIdentity);

    // [2.2] Set the SIP-Number-Auth-Items AVP.
    // The SIP-Number-Auth-Items AVP indicates the number of
    // authentication vectors the S-CSCF is requesting.                             // The AVP Code of SIP-Number-Auth-Items AVP is 607
    // The Data Type of SIP-Number-Auth-Items AVP is Unsigned32
    SIPNumberAuthItems sIPNumberAuthItems(1u);
    maa.setSIPNumberAuthItems(sIPNumberAuthItems);

    // Create a SIP-Auth-Data-Item AVP object
    SIPAuthDataItem sIPAuthDataItem;
    SIPItemNumber sIPItemNumber(1u);
    sIPAuthDataItem.setSIPItemNumber(sIPItemNumber);

    SIPAuthenticationScheme sIPAuthenticationScheme("127");
    sIPAuthDataItem.setSIPAuthenticationScheme(sIPAuthenticationScheme);

    SIPAuthenticate sIPAuthenticate("1234567");
    sIPAuthDataItem.setSIPAuthenticate(sIPAuthenticate);

    SIPAuthorization sIPAuthorization("1234567");
    sIPAuthDataItem.setSIPAuthorization(sIPAuthorization);

    SIPAuthenticationContext sIPAuthenticationContext("1234567");
    sIPAuthDataItem.setSIPAuthenticationContext(sIPAuthenticationContext);

    ConfidentialityKey confidentialityKey("1234567");
    sIPAuthDataItem.setConfidentialityKey(confidentialityKey);

    IntegrityKey integrityKey("1234567");
    sIPAuthDataItem.setIntegrityKey(integrityKey);

    FramedIPAddress framedIpAddress("172.16.12.221");
    sIPAuthDataItem.setFramedIPAddress(framedIpAddress);

    FramedIPv6Prefix framedIpv6Prefix("fe80::ea40:f2ff:fe3c:9001");
    sIPAuthDataItem.setFramedIPv6Prefix(framedIpv6Prefix);

    FramedInterfaceId framedInterfaceId(1u);
    sIPAuthDataItem.setFramedInterfaceId(framedInterfaceId);

    // [2.2] Set the SIP-Auth-Data-Item AVP.
    // The SIP-Auth-Data-Item AVP contains the authentication and/or
    // the authorization for the Diameter client.
    // The AVP Code of SIP-Auth-Data-Item AVP is 612
    // The Data Type of SIP-Auth-Data-Item AVP is Grouped
    maa.addSIPAuthDataItem(sIPAuthDataItem);

    // Create the Failed-AVP AVP.
    // The Failed-AVP AVP provides debugging information in cases
    // where a request is rejected or not fully processed due to
    // erroneous information in a specific AVP.
    // The AVP Code of AVP is 279.
    // The data type of AVP is Grouped Type.

    // FailedAVP
    //    failedAVP;
    // [2.2] Set the Failed-AVP AVP.
    // maa.addFailedAVP(failedAVP);

    // Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"),proxyHost2("proxyHost2");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // The data type of is OctetString.
    //ProxyState proxyState1("proxyState1"),proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // [2.2] Set the Proxy-Info AVP.
    // Application should not set this AVP.
    // maa.addProxyInfo(proxyInfo1);
    // maa.addProxyInfo(proxyInfo2);

    // Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord routeRecord1("routeRecord1"),
    //routeRecord2("routeRecord2");

    // [2.2] Set the Route-Record AVP.
    // Application should not set this AVP.
    // maa.addRouteRecord(routeRecord2);

    // 3. Send the encoded MultimediaAuthAnswer object to an output stream
    //    buffer(Note: For test purpose, the object is being sent to ios::cout
    //    output buffer.

    cout << maa;

    // Send Object to stack.
    SendDiaAppMsg(maa, sIdx);

    // Update stats.
    CxdxStats::GetCxdxStats()->UpdateSendStats(maa.getCommandCode(),ITS_FALSE);
    return ITS_SUCCESS;
}



