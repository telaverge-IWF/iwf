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
 * LOG: $Log: UserAuthorizationTest.cpp,v $
 * LOG: Revision 1.1.2.1  2015/05/18 05:15:10  kpnithin
 * LOG: cxdx v12 Test tool developed with new protocol file
 * LOG:
 * LOG: Revision 1.1.6.2  2015/01/07 07:28:52  ncshivakumar
 * LOG: Merged
 * LOG:
 * LOG: Revision 1.1.4.3  2014/11/18 10:08:57  ahemanth
 * LOG: Fix for bug 5277.
 * LOG:
 * LOG: Revision 1.1.4.2  2014/11/12 04:51:30  ncshivakumar
 * LOG: merged from Aicent branch
 * LOG:
 * LOG: Revision 1.1.2.1  2014/11/03 09:30:42  venkat
 * LOG: Added cxdx_v10
 * LOG:
 * LOG: Revision 1.1.2.1.2.1  2013/07/01 09:43:46  nazad
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
 * ID: $Id: UserAuthorizationTest.cpp,v 1.1.2.1 2015/05/18 05:15:10 kpnithin Exp $
 ****************************************************************************/
#ident "$Id: UserAuthorizationTest.cpp,v 1.1.2.1 2015/05/18 05:15:10 kpnithin Exp $"

#include <app.h>
#include <cxdx_defines.h>
#include <cxdx_stats.h>
#include <diameter/cxdx_v12/UserAuthorization.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::cxdx_v12;

// using namespace diameter::nasreq;

extern string sessIdString;
extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the  UserAuthorizationRequest to the
 *      diameter stack. Create the  UserAuthorizationRequest object,
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
int SendCxdxUserAuthorizationRequest()
{
    // 1. Create an instance of UserAuthorizationRequest class
    // The User-Authorization-Request command is sent by a Diameter
    // client to a Diameter Server in order to request authorization
    // of the registration of a multimedia user with
    // Command-Code = 300 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    UserAuthorizationRequest uar(false, false);

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
    AllocateSession(CXDX_INTERFACE_APP_ID, sIdx, sessIdString);
    uar.setSessionId(SessionId(sessIdString));

    uar.setSessionIndex(sIdx);

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
    AuthApplicationId authApplicationId(CXDX_INTERFACE_APP_ID);
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
    //AcctApplicationId acctApplicationId(2);
    //vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    //[2.1] Set the  Vendor-Specific-Application-Id AVP.
    uar.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

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
    AuthSessionState authSessionState(AuthSessionState::NO_STATE_MAINTAINED);
    uar.setAuthSessionState(authSessionState);

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
    uar.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    uar.setOriginRealm(originRealm);

    // [2.1] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    uar.setDestinationRealm(destinationRealm);

    // [2.1] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    uar.setUserName(userName);

    // [2.1] Set the Public-Identity AVP.
    // The Public-Identity AVP contains the public identity of a
    // user in the IMS.
    // The AVP Code of Public-Identity AVP is 601
    // The data type of Public-Identity AVP is UTF8String.
    PublicIdentity publicIdentity("sip:user@intellinet-tech.com");
    uar.setPublicIdentity(publicIdentity);

    // [2.1] Set the Visited-Network-Identifier AVP.
    // The AVP is used to identity a specific session and must appear
    // immediately following the Diameter header.
    // The AVP Code of Visited-Network-Identifier AVP is 600
    // The data type of Visited-Network-Identifier AVP is OctetString.
    VisitedNetworkIdentifier visitedNetworkIdentifier("Roaming");
    uar.setVisitedNetworkIdentifier(visitedNetworkIdentifier);

    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    if(GetDestinationHost())
    {
    	DestinationHost destinationHost(GetDestinationHost());
    	uar.setDestinationHost(destinationHost);
    }

    // [2.2] Set the User-Authorization-Type AVP.
    // The User-Authorization-Type AVP indicates the type of user
    // authorization being performed in a User Authorization
    // operation.
    // The AVP Code of User-Authorization-Type AVP is 623
    // The data type of User-Authorization-Type AVP is Enumerated with
    // the following values
    // {
    //  REGISTRATION (0),
    //  DE_REGISTRATION (1),
    //  REGISTRATION_AND_CAPABILITIES (2)
    // }
    UserAuthorizationType userAuthorizationType(UserAuthorizationType::
                                                REGISTRATION);
    uar.setUserAuthorizationType(userAuthorizationType);

    uar.setUARFlags(UARFlags(1u));    

    // Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //ProxyInfo proxyInfo1,proxyInfo2;

    // Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost proxyHost1("proxyHost1"),proxyHost2("proxyHost1");
    //proxyInfo1.setProxyHost(proxyHost1);
    //proxyInfo2.setProxyHost(proxyHost2);

    // Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState proxyState1("proxyState1"),proxyState2("proxyState2");
    //proxyInfo1.setProxyState(proxyState1);
    //proxyInfo2.setProxyState(proxyState2);

    // Add Extra AVP to Proxy-Info AVP
    //proxyInfo1.addExtra(AVP());
    //proxyInfo2.addExtra(ProxyState("proxyState3"));
    // [2.2] Set the Proxy-Info AVP.
    // Application should not set this AVP.
    // uar.addProxyInfo(proxyInfo1);
    // uar.addProxyInfo(proxyInfo2);

    // Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    // RouteRecord routeRecord1("routeRecord1"),routeRecord2("routeRecord2");

    // [2.2] Set the Route-Record AVP.
    // Application should not set this AVP.
    // uar.addRouteRecord(routeRecord2);

    // 3. Send the encoded UserAuthorizationRequest object to an output stream
    // buffer(Note: For test purpose, the object is being sent to ios::cout
    // output buffer.

    cout << uar;

    // Send object to stack.
    SendDiaAppMsg(uar, sIdx);

    CxdxStats::GetCxdxStats()->UpdateSendStats(uar.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends the Answer to the UserAuthorization request
 *      made by the diameter stack. Create the UserAuthorizationAnswer
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
int SendCxdxUserAuthorizationAnswer(const CommandImpl * impl)
{
    // 1. Create an instance of UserAuthorizationAnswer class
    // The User-Authorization-Answer command is sent by a server
    // in response to the User-Authorization-Request command with
    // Command-Code = 300 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    UserAuthorizationAnswer uaa(false, false);

    //Create an instance of UserAuthorizationRequest class
    UserAuthorizationRequest rreq(*impl);
    
    bool isNull;
    bool isAVPEnabled;
    bool isExpAVPEnabled;
    Json::Value l_jsonRoot = parseCxdxConfig();

    Json::Value* m_jsonRoot = &l_jsonRoot;
    Json::Value* m_jsonRoot1 = &(*m_jsonRoot)["cxdx_v12"];
    Json::Value* cfg = &(*m_jsonRoot1)["UserAuthorizationAnswer"];


    // Get some AVP values from Request Message and pass them to Answer
    const SessionId &sid1 = rreq.getSessionId();
    const OriginHost &oh1 = rreq.getOriginHost();
    const OriginRealm &or1 = rreq.getOriginRealm();
    const DestinationRealm &dr1 = rreq.getDestinationRealm();

    // 2. Create the instances of the classes describing the various
    // AVPs' present in an UserAuthorizationAnswer command and
    // pass them by value to the corresponding data members set
    // methods of the UserAuthorizationAnswer object created
    // in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    uaa.setSessionId(sid1);

    uaa.setSessionIndex(rreq.getSessionIndex());

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
    uaa.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

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
    AuthSessionState authSessionState(AuthSessionState::NO_STATE_MAINTAINED);
    uaa.setAuthSessionState(authSessionState);

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
    	uaa.setOriginHost(originHost);
    }
    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(dr1.value());
    uaa.setOriginRealm(originRealm);

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
    
    isAVPEnabled = (*cfg)["ResultCode"]["Enabled"].asBool();
    isNull = (*cfg)["ResultCode"]["Value"].isNull();
    if(!isNull && isAVPEnabled)
    {
        ResultCode resultCode((*cfg)["ResultCode"]["Value"].asInt());
        uaa.setResultCode(resultCode);
    }
    // Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // already ResultCode AVP is set, both should not be set
    isExpAVPEnabled = (*cfg)["Experimental-Result"]["Enabled"].asBool();
    if(isExpAVPEnabled)
    {
        ExperimentalResult experimentalResult;
        VendorId vendorId1(VENDOR_ID);
        experimentalResult.setVendorId(vendorId1);
        ExperimentalResultCode experimentalResultCode((*cfg)["Experimental-Result"]["Value"].asInt());
        experimentalResult.setExperimentalResultCode(experimentalResultCode);
        uaa.setExperimentalResult(experimentalResult);
    }
    // [2.2] Set the Server-Name AVP.
    // The Server-Name AVP contains a SIP-URL and used to
    // identify a SIP server (e.g. S-CSCF name)..
    // The AVP Code of AVP is .
    // The data type of AVP is UTF8String.
    ServerName serverName("sip:cscf@3gppnetwork.com");
    uaa.setServerName(serverName);

    // [2.2] Create the Server-Capabilities AVP.
    // This AVP contains information to assist the I-CSCF in the
    // selection of an S-CSCF.
    // The AVP Code of AVP is 603.
    // The data type of AVP is Grouped Type.
    ServerCapabilities serverCapabilities;

    // Set the Mandatory-Capability AVP.
    // The value included in this AVP can be used to represent a
    // single determined mandatory capability of an S-CSCF. Each
    // mandatory capability available in an individual operator’s
    // network shall be allocated a unique value.
    // The AVP Code of AVP is .
    // The data type of AVP is Unsigned32.
    MandatoryCapability mandatoryCapability(1u);
    serverCapabilities.addMandatoryCapability(mandatoryCapability);

    // Set the Optional-Capability AVP.
    // The value included in this AVP can be used to represent a
    // single determined optional capability of an S-CSCF.
    // Each optional capability available in an individual
    // operator’s network shall be allocated a unique value.
    // The AVP Code of Optional-Capability AVP is .
    // The data type of Optional-Capability AVP is Unsigned32.
    OptionalCapability optionalCapability(1u);
    serverCapabilities.addOptionalCapability(optionalCapability);

    // Add the Server-Name AVP to Server-Capabilities AVP..
    // The AVP Code of AVP is .
    // The data type of AVP is UTF8String.
    ServerName serverName1("sip:cscf@3gppnetwork.com");
    serverCapabilities.addServerName(serverName1);

    // [2.2] Set the Server-Capabilities AVP.
    uaa.setServerCapabilities(serverCapabilities);

    // Create the Failed-AVP AVP.
    // The Failed-AVP AVP provides debugging information in cases
    // where a request is rejected or not fully processed due to
    // erroneous information in a specific AVP.
    // The AVP Code of AVP is 279.
    // The data type of AVP is Grouped Type.

    //FailedAVP
    //    failedAVP;
    // [2.2] Set the Failed-AVP AVP.
    //uaa.addFailedAVP(failedAVP);

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
    // uaa.addProxyInfo(proxyInfo1);
    // uaa.addProxyInfo(proxyInfo2);

    // [2.2] Set the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the Capabilities
    // Exchange message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord routeRecord1("routeRecord1"),routeRecord2("routeRecord2");

    // Set Route Record
    // Application should not set this AVP.
    // uaa.addRouteRecord(routeRecord1);
    // uaa.addRouteRecord(routeRecord2);

    // 3. Send the encoded UserAuthorizationAnswer object to an output stream
    // buffer(Note: For test purpose, the object is being sent to ios::cout
    // output buffer.

    cout << uaa;

    // Send Object to stack.
    SendDiaAppMsg(uaa, sIdx);

    // Update stats.
    CxdxStats::GetCxdxStats()->UpdateSendStats(uaa.getCommandCode(),ITS_FALSE);
    return ITS_SUCCESS;
}

