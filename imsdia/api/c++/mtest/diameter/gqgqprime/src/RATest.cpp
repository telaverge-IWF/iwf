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
 * LOG: $Log: RATest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:09  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:36:39  kamakshilk
 * LOG: GqGq' interface demo for static and distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: RATest.cpp,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: RATest.cpp,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $"

#include <diameter/gqgqprime/RA.h>
#include <app.h>
#include <gq_defines.h>
#include <gq_stats.h>
                                                                                
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::gqgqprime;

extern string sessIdString;
extern ITS_UINT sIdx;


/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the RARequest to the
 *      diameter stack. Create the RARequest object,
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
int SendGqRARequest()
{
    // [1] Create an instance of AARequest class
    // The RA-Request command is sent by a Diameter
    // client to a Diameter Server in order to request deregistration
    // Command-Code = 258
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gqgqprime::RARequest request;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    // Fixed AVP 
    cout<<"Please enter the Session ID for ReAuthorization"<<endl;
    string sessIdString;
    cin>>sessIdString;
    request.setSessionId(SessionId(sessIdString));

    request.setSessionIndex(sIdx);

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter  messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost origh(GetOriginHost());
    request.setOriginHost(origh);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origr(GetOriginRealm());
    request.setOriginRealm(origr);

    // [2.1.2.3] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm desr(GetDestinationRealm());
    request.setDestinationRealm(desr);

    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost desh(GetDestinationHost());
    request.setDestinationHost(desh);

    // [2.1.2.5] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authid(GQGQ_INTERFACE_APP_ID);
    request.setAuthApplicationId(authid);

    // The Specific-Action AVP (AVP code 513) is of type Enumerated.
    // The following values are defined for this AVP
    // SERVICE_INFORMATION_REQUEST
    // CHARGING_CORRELATION_EXCHANGE
    // INDICATION_OF_LOSS_OF_BEARER
    // INDICATION_OF_RECOVERY_OF_BEARER
    // INDICATION_OF_RELEASE_OF_BEARER
    // INDICATION_OF_ESTABLISHMENT_OF_BEARER
    SpecificAction sp1(SpecificAction::INDICATION_OF_RELEASE_OF_BEARER);
    request.addSpecificAction(sp1);

    // [2.2.x] Optional AVPs

    // [2.2.1.1] The Access-Network-Charging-Identifier AVP 
    // (AVP code 502) is of type Grouped, and contains a 
    // charging identifier
    AccessNetworkChargingIdentifier ac1;

    // [2.2.1.2] The Access-Network-Charging-Identifier-Value 
    // AVP (AVP code 503) is of type OctetString, and contains 
    // a charging identifier
    AccessNetworkChargingIdentifierValue anciv("ABC");
    ac1.setAccessNetworkChargingIdentifierValue(anciv);

    // [2.2.1] set the AccessNetworkChargingIdentifier AVP 
    // to RA Request Message
    request.addAccessNetworkChargingIdentifier(ac1);

    // [2.2.2.1] Address AVP for each potential IP address that 
    // MAY be locally used when transmitting Diameter messages.
    Address f1(Address::IPV4,"11.1.1.2");

    // [2.2.2] The Access-Network-Charging-Address AVP (AVP code 501) is of
    // type Address, and it indicates the IP Address of the network
    // entity within the access network performing charging
    AccessNetworkChargingAddress anc(f1);
    request.setAccessNetworkChargingAddress(anc);

    // [2.2.3.1] The Flows AVP (AVP code 510) is of type Grouped, 
    // and it indicates IP flows via their flow identifiers
    Flows ff1;

    // [2.2.3.2] The Flow-Number AVP (AVP code 509) is of type Unsigned32,
    // and it contains the ordinal number of the IP flow(s),
    FlowNumber fn(10);
    ff1.addFlowNumber(fn);

    //  [2.2.3.3] The Media-Component-Number AVP (AVP code 518) is of
    // type Unsigned32, and it contains the ordinal number of
    // the media component, assigned
    MediaComponentNumber mcn(10);
    ff1.setMediaComponentNumber(mcn);

    // [2.2.3] Set the Flows AVP to RA Request Message
    request.addFlows(ff1);

    // [2.2.4] The Session-Abort-Cause AVP (AVP code 500) is of type 
    // Enumerated, and determines the cause of a session abort request.
    //  The following values are defined:
    // BEARER_RELEASED
    // INSUFFICIENT_SERVER_RESOURCES
    // INSUFFICIENT_BEARER_RESOURCES
    AbortCause v1(AbortCause::INSUFFICIENT_SERVER_RESOURCES);
    request.setAbortCause(v1);

    // [2.2.5] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId osid(40);
    request.setOriginStateId(osid);

    // [2.2.6.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //diameter::base::ProxyInfo pi1;
    // [2.2.6.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);

    // [2.2.6.3] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);

    // [2.2.6] set the ProxyInfo AVP to RA Request
    // Application should not set this AVP.
    // request.addProxyInfo(pi1);

    // [2.2.7] Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord rrec("nemo");
    // Application should not set this AVP.
    // request.addRouteRecord(rrec);

    cout << "RAR" << request << endl;
   
    // Send RA Request Message to Diameter stack 
    SendDiaAppMsg(request, sIdx);
    GqgqStats::GetGqgqStats()->UpdateSendStats(request.getCommandCode(), 
                                                               ITS_TRUE);
                                                                                
    return (ITS_SUCCESS);

}


/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the RA request
 *      made by the diameter stack. Create the RAAnswer
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
int SendGqRAAnswer(const CommandImpl * impl)
{
    // [1]. Create an instance of  RA Answer class
    // The RA-Answer command is sent by a Diameter
    // server to a Diameter client in order to request deregistration
    // Command-Code = 258 
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gqgqprime::RAAnswer answer;

    // Create an instance of  RA Request class 
    RARequest rar(*impl);

    // Get AVP values from Request and set them to Answer Message
    const SessionId& sid = rar.getSessionId();
    const OriginHost& oh = rar.getOriginHost();
    const OriginRealm& or1 = rar.getOriginRealm();
    const DestinationHost& dh = rar.getDestinationHost();
    const DestinationRealm& dr = rar.getDestinationRealm();
    const AuthApplicationId& aaid1 = rar.getAuthApplicationId();
    const OriginStateId& osid = rar.getOriginStateId();

    // [2.1.1.x] Fixed AVP

    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    answer.setSessionId(sid);

    answer.setSessionIndex(rar.getSessionIndex());

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost origh(dh.value());
    answer.setOriginHost(origh);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origr(dr.value());
    answer.setOriginRealm(origr);

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
    ResultCode rc(2001u);
    answer.setResultCode(rc);

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
    // answer.setExperimentalResult(er1);

    // [2.2.3.1] The Media-Component-Description AVP (AVP code 517)
    // is of type Grouped, and it contains service information
    // for a  single media component within an AF session.
    // It may be based on the SDI exchanged between the AF and the AF client
    diameter::gqgqprime::MediaComponentDescription m1;

    // [2.2.3.2] The Media-Component-Number AVP (AVP code 518) is of
    // type Unsigned32, and it contains the ordinal number of
    // the media component, assigned
    MediaComponentNumber mcn(10);
    m1.setMediaComponentNumber(mcn);

    // [2.2.3.3] The Media-Sub-Component AVP (AVP code 519) is 
    // of type Grouped, and it contains the requested QoS and 
    // filters for the set of IP
    // flows identified by their common Flow-Identifier.
    MediaSubComponent ms1;

    // [2.2.3.4]The Flow-Number AVP (AVP code 509) is of type Unsigned32,
    // and it contains the ordinal number of the IP flow(s)
    FlowNumber fn(10);
    ms1.setFlowNumber(fn);
    m1.addMediaSubComponent(ms1);

    // [2.2.3] set MediaComponentDescription to AA Request
    answer.addMediaComponentDescription(m1);

    // [2.2.4.1]The Flows AVP (AVP code 510) is of type Grouped, 
    // and it indicates IP flows via their flow identifiers
    Flows f1;

    // [2.2.4.2] The Flow-Number AVP (AVP code 509) is of type 
    // Unsigned32, and it contains the ordinal number of the IP flow(s)
    FlowNumber fn2(10);
    f1.addFlowNumber(fn2);    

    // [2.2.4.3] The Media-Component-Number AVP (AVP code 518) is of
    // type Unsigned32, and it contains the ordinal number of
    // the media component, assigned
    MediaComponentNumber mcn1(10);
    f1.setMediaComponentNumber(mcn1);

    //  [2.2.4.4] The Flow-Grouping AVP (AVP code 508) is of 
    // type Grouped, and it indicates that no other IP Flows 
    // shall be transported together with the listed IP Flows 
    // in the same PDP context(s).
    FlowGrouping F1;
    F1.addFlows(f1);

    // [2.2.4] set the FlowGrouping AVP 
    answer.addFlowGrouping(F1);

    // [2.2.5] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    answer.setOriginStateId(osid);

    // [2.2.6] The Error-Message AVP (AVP Code 281) is of type UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message
    // ErrorMessage erm("server problem");
    // answer.setErrorMessage(erm);

    // [2.2.7] The Error-Reporting-Host AVP (AVP Code 294) is of type
    // DiameterIdentity.  This AVP contains the identity of the Diameter
    // host that sent the Result-Code AVP
    // ErrorReportingHost erh("abc.def.com");
    // answer.setErrorReportingHost(erh);

    // [2.2.8] Set Failed AVP
    // FailedAVP fa;
    // answer.addFailedAVP(fa);


    // [2.2.9.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //diameter::base::ProxyInfo pi2;

    // [2.2.9.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost ph1("proxy1.abc.com");
    //pi2.setProxyHost(ph1);

    // [2.2.9.3] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState ps1("state0");
    //pi2.setProxyState(ps1);

    // [2.2.9] set the ProxyInfo AVP
    // Application should not set this AVP.
    // answer.addProxyInfo(pi2);

    cout << "RAA" << answer << endl;
    SendDiaAppMsg(answer, sIdx);
    GqgqStats::GetGqgqStats()->UpdateSendStats(answer.getCommandCode(), 
                                                             ITS_FALSE);
                                                                                
    return (ITS_SUCCESS);
    
}

