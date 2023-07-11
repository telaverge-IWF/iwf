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
 * LOG: $Log: STTest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:09  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2006/12/19 08:36:39  kamakshilk
 * LOG: GqGq' interface demo for static and distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: STTest.cpp,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: STTest.cpp,v 3.1 2008/03/31 10:33:09 nvijikumar Exp $"

#include <app.h>
#include <gq_defines.h>
#include <gq_stats.h>
#include <diameter/gqgqprime/ST.h>
                                                                                
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::gqgqprime;

extern string sessIdString;
extern ITS_UINT sIdx;


/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the STRequest to the
 *      diameter stack. Create the STRequest object,
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
int SendGqSTRequest()
{
    // [1]. Create an instance of STRequest class
    // The ST-Request command is sent by a Diameter
    // client to a Diameter Server in order to request deregistration
    // Command-Code = 275 with 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gqgqprime::STRequest request(false,false);

    
    // [2.1.1.x] Fixed AVP 

    // [2.1.1.1] The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    // Provide Session Id to terminate
    cout<<"Please enter the Session ID to Terminate"<<endl;
    string sessIdString;
    cin>>sessIdString;
    request.setSessionId(SessionId(sessIdString));

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] Set the Origin-Host AVP.
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
    // The Destination-Realm AVP contains the realm, the message routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm desr(GetDestinationRealm());
    request.setDestinationRealm(desr);

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
    TerminationCause termc(TerminationCause::DIAMETER_BAD_ANSWER);
    request.setTerminationCause(termc);

    // [2.1.2.5] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authid(GQGQ_INTERFACE_APP_ID);
    request.setAuthApplicationId(authid);

    // [2.2.x] Optional AVPs

    // [2.2.1] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost desh(GetDestinationHost());
    request.setDestinationHost(desh);

    // [2.2.2] The Class AVP (AVP Code 25) is of type OctetString and is used 
    // to be Diameter servers to return state information to the access device.
    Class class1("Business");
    request.addClass(class1);

    // [2.2.3] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE:This is a monotonically increasing value that is advanced whenever
    // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId origsid(41);
    request.setOriginStateId(origsid);

    // [2.2.4] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284.
    //diameter::base::ProxyInfo pi1;

    // [2.2.5.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info AVP.    
    // The AVP Code of Proxy-Info is 280.
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);

    // [2.2.5.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated as opaque
    //  data
    // The AVP Code of Proxy-State is 33.
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);

    // [2.2.5] set the ProxyInfo AVP 
    // request.addProxyInfo(pi1);

    // [2.2.6] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the message.
    // The AVP Code of Route-Record is 282.
    //RouteRecord rrec("nemo");
    // Application should not set this AVP.
    // request.addRouteRecord(rrec);

    // Send STRequest Message to Diameter stack 

    cout << "STR" << request <<endl;
    SendDiaAppMsg(request, sIdx);
    GqgqStats::GetGqgqStats()->UpdateSendStats(request.getCommandCode(), 
                                                             ITS_TRUE);
                                                                                
    return (ITS_SUCCESS);
    
}


/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the ST request
 *      made by the diameter stack. Create the STAnswer
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
int SendGqSTAnswer(const CommandImpl * impl)
{
    // [1]. Create an instance of STAnswer class
    // The ST Answer command is sent by a Diameter
    // client to a Diameter Server in order to request deregistration
    // Command-Code = 275
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gqgqprime::STAnswer answer;

    // Create an instance of STRequest class
    STRequest str1(*impl);

    // Get the AVP values from Request and set them to Answer
    const SessionId& sid = str1.getSessionId();
    const OriginHost& oh = str1.getOriginHost();
    const OriginRealm& or1 = str1.getOriginRealm();
    //const DestinationHost& dh = str1.getDestinationHost();
    const DestinationRealm& dr = str1.getDestinationRealm();
    const AuthApplicationId& aaid1 = str1.getAuthApplicationId();

    // [2.1.1.x] Fixed AVP 

    //[2.1.1.1] set the session Id that is taken from Request
    answer.setSessionId(sid);

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    // Vaule taken from the Requested Message
    OriginHost origh(GetOriginHost());
    answer.setOriginHost(origh);

    // [2.1.2.2] The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    // Values taken from the Requested Message
    OriginRealm origr(dr.value());
    answer.setOriginRealm(origr);

    // [2.2.x] Optional AVPs

    // [2.2.1] Populate required parameter "Result-Code".
    // Set the Result-Code AVP.
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
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

    // [2.2.2] set the ExperimentalResult AVP
    // answer.setExperimentalResult(er1);

    // [2.2.3] The Error-Message AVP (AVP Code 281) is of type UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message
    // ErrorMessage erm("Server problem");
    // answer.setErrorMessage(erm);

    // [2.2.4] The Error-Reporting-Host AVP (AVP Code 294) is of type
    // DiameterIdentity.  This AVP contains the identity of the Diameter
    // host that sent the Result-Code AVP
    // ErrorReportingHost erh("xyz.dia.com");
    // answer.setErrorReportingHost(erh);

    // [2.2.5] The Failed-AVP AVP (AVP Code 279) is of type Grouped and provides
    // debugging information in cases where a request is rejected or not
    // fully processed due to erroneous information in a specific AVP
    // FailedAVP fh1;
    // answer.addFailedAVP(fh1);


    // [2.2.6] Populate optional parameter "Origin-State-Id".
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

    // [2.2.7.1]
    //URI uri1("SecondaryEventCollectionFunction.com", URI::AAA,
    //       3880, URI::TCP, URI::DIAMETER);

    // [2.2.7] Upon receiving Result-Code AVP is set to 
    // DIAMETER_REDIRECT_INDICATION Diameter node forwards the request 
    // directly to one of the hosts identified in these AVPs (AVP Code 292).
    // Application need not to set this.
    //RedirectHost rh(uri1);
    //answer.addRedirectHost(rh);

    // [2.2.8] The Redirect-Host-Usage AVP (AVP Code 261) is of type Enumerated.
    // This AVP MAY be present in answer messages whose 'E' bit is set and
    //  the Result-Code AVP is set to DIAMETER_REDIRECT_INDICATION.
    // The following values are supported.
    // DONT_CACHE             0
    // ALL_SESSION            1
    // ALL_REALM              2
    // REALM_AND_APPLICATION  3
    // ALL_APPLICATION        4
    // ALL_HOST               5
    // ALL_USER               6
    //RedirectHostUsage rhu(RedirectHostUsage::ALL_SESSION);
    //answer.setRedirectHostUsage(rhu);


    // [2.2.9] The Redirect-Max-Cache-Time AVP (AVP Code 262) is of type 
    // Unsigned32. This AVP contains the maximum number of seconds the peer 
    // and route table entries, created as a result of the Redirect-Host,
    // to cache
    //RedirectMaxCacheTime rmct(500);
    //answer.setRedirectMaxCacheTime(rmct);

    // [2.2.10.1] Create the Proxy-Info AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    //diameter::base::ProxyInfo pi1;

    // [2.2.10.2] Set the Proxy-Host AVP.
    // The Proxy-Host AVP contains the identity of the host that
    //  added the Proxy-Info AVP
    // The AVP Code of Proxy-Host is 280
    // The data type of Proxy-Host is DiameterIdentity
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);

    // [2.2.10.3] Set the Proxy-State AVP.
    // The Proxy-State AVP contains the state local information
    // and must be treated as opaque data
    // The AVP Code of is 33
    // the data type of is OctetString.
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);

    //[2.2.10] set the ProxyInfo AVP
    // Application should not set this AVP.
    // answer.addProxyInfo(pi1);

    cout << "STA" << answer << endl;
    SendDiaAppMsg(answer, sIdx);
    GqgqStats::GetGqgqStats()->UpdateSendStats(answer.getCommandCode(), 
                                                            ITS_FALSE);
                                                                                
    return (ITS_SUCCESS);

}
