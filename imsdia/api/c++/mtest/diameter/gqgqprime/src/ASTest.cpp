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
 * LOG: $Log: ASTest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:09  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:36:39  kamakshilk
 * LOG: GqGq' interface demo for static and distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: ASTest.cpp,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: ASTest.cpp,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $"
                                                                                
#include <diameter/gqgqprime/AS.h>
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
 *  Purpose: This function sends the ASRequest to the
 *      diameter stack. Create the ASRequest object,
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
int SendGqASRequest()
{
    // [1]. Create an instance of ASRequest class
    // The AS-Request command is sent by a Diameter
    // Command-Code = 274
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gqgqprime::ASRequest request;

    // [2.1.1.x ]Fixed AVP 

    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    // Get the user input to Abort the session.
    string sessIdString;
    cout<<"Please Enter the Session ID to Abort \n";
    cin>>sessIdString;

    request.setSessionId(SessionId(sessIdString));

    // [2.1.2.x] Required AVPs 

    // [2.1.2.1.] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
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
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
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

    // [2.2.1.5] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authid(GQGQ_INTERFACE_APP_ID);
    request.setAuthApplicationId(authid);

    // [2.2.1.6] The Session-Abort-Cause AVP (AVP code 500) is of type 
    // Enumerated,and determines the cause of a session abort request.
    //  The following values are defined:
    // BEARER_RELEASED
    // INSUFFICIENT_SERVER_RESOURCES
    // INSUFFICIENT_BEARER_RESOURCES
    AbortCause acause(AbortCause::INSUFFICIENT_SERVER_RESOURCES);
    request.setAbortCause(acause);

    // [2.2.x] Optional AVPs

    // [2.2.1] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId orgid(41);
    request.setOriginStateId(orgid);

    // [2.2.2.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //diameter::base::ProxyInfo pi1;
    // [2.2.2.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);        

    // [2.2.2.3] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);

    //[2.2.2] set ProxyInfo AVP
    // Application should not set this AVP.
    // request.addProxyInfo(pi1);

    // [2.2.3] Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the Capabilities
    // Exchange message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    //RouteRecord rrec("nemo");
    // Application should not set this AVP.
    //request.addRouteRecord(rrec);

    cout << "ASR" << request << endl;
    SendDiaAppMsg(request, sIdx);
    GqgqStats::GetGqgqStats()->UpdateSendStats(request.getCommandCode(), 
                                                              ITS_TRUE);
                                                                                
    return (ITS_SUCCESS);

}


/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the AS request
 *      made by the diameter stack. Create the ASAnswer
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
int SendGqASAnswer(const CommandImpl * impl)
{
    // [1]. Create an instance of  RA Answer class
    // The AS-Answer command is sent by a Diameter
    // server to a Diameter client in order to request deregistration
    // Command-Code = 274 
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gqgqprime::ASAnswer answer;

    // Create an instance of  AS Request class
    ASRequest asr(*impl);

    // Get the AVP values from AS Request Message
    const SessionId& sid = asr.getSessionId();
    const OriginHost& oh = asr.getOriginHost();
    const OriginRealm& or1 = asr.getOriginRealm();
    const DestinationHost& dh = asr.getDestinationHost();
    const DestinationRealm& dr = asr.getDestinationRealm();

    // [2.1.1.x] Fixed AVP

    // [2.1.1.1] The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    answer.setSessionId(sid);

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost origh(dh.value());
    answer.setOriginHost(origh);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origr(dr.value());
    answer.setOriginRealm(origr);

    // [2.2.x]Optional AVPs
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
    // Already ResultCode AVP is been test.
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

    // [2.2.3] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId osid(41);
    answer.setOriginStateId(osid);

    // [2.2.4] The Error-Message AVP (AVP Code 281) is of type UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message
    // Result code is successfull
    //ErrorMessage erm("Error sdf");
    //answer.setErrorMessage(erm);

    // [2.2.5] The Error-Reporting-Host AVP (AVP Code 294) is of type
    // DiameterIdentity.  This AVP contains the identity of the Diameter
    // host that sent the Result-Code AVP
    //ErrorReportingHost erh("host1.xyz.com");
    //answer.setErrorReportingHost(erh);

    // [2.2.6] The Failed-AVP AVP (AVP Code 279) is of type Grouped and provides
    // debugging information in cases where a request is rejected or not
    // fully processed due to erroneous information in a specific AVP
    //FailedAVP fa;
    //answer.addFailedAVP(fa);

    // [2.2.7.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //diameter::base::ProxyInfo pi2;

    // [2.2.7.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost ph1("proxy1.abc.com");
    //pi2.setProxyHost(ph1);

    // [2.2.7.3] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState ps1("state0");
    //pi2.setProxyState(ps1);

    // [2.2.7] set the ProxyInfo AVP.
    // answer.addProxyInfo(pi2);

    // Send AS Answer to diameter stack w.r.t AS Request.
    cout << "ASA" << answer <<endl;
    SendDiaAppMsg(answer, sIdx);
    GqgqStats::GetGqgqStats()->UpdateSendStats(answer.getCommandCode(), 
                                                            ITS_FALSE);
                                                                                
    return (ITS_SUCCESS);

}
