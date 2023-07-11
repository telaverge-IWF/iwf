/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2010 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: RATest.cpp,v $
 * LOG: Revision 1.1  2010/04/22 11:12:53  nvijikumar
 * LOG: sample Application for S9 interface
 * LOG:
 * LOG:
 *
 * ID: $Id: RATest.cpp,v 1.1 2010/04/22 11:12:53 nvijikumar Exp $
 ****************************************************************************/
#include <app.h>
#include <s9_defines.h>
#include <s9_stats.h>
#include <diameter/s9/RA.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::s9;

extern string sessIdString;
extern ITS_UINT sIdx;

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the RA raReq to the
 *      diameter stack. Creates the RA Request object,
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
int SendS9RARequest()
{

    // [1] Create an instance of RARequest class
    // The RA-Request command is sent by a Diameter
    // client to a Diameter Server in order to raReq deregistration
    // Command-Code = 258
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::s9::RARequest raReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    cout << "Please enter the Session ID to Re-Authorize" << endl;
    cin >> sessIdString;
    raReq.setSessionId(SessionId(sessIdString));

    raReq.setSessionIndex(sIdx);

    // [2.1.2.5] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authAppId(S9_INTERFACE_APP_ID);
    raReq.setAuthApplicationId(authAppId);

    // [2.1.2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter  messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost orighost(GetOriginHost());
    raReq.setOriginHost(orighost);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origrealm(GetOriginRealm());
    raReq.setOriginRealm(origrealm);

    // [2.1.2.3] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destRealm(GetDestinationRealm());
    raReq.setDestinationRealm(destRealm);
    
    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destHost(GetDestinationHost());
    raReq.setDestinationHost(destHost);

    // The Re-Auth-Request-Type AVP (AVP Code 285) is of type Enumerated 
    // and is included in application-specific auth answers to inform the 
    // client of the action expected upon expiration of the 
    // Authorization-Lifetime. If the answer message contains an 
    // Authorization-Lifetime AVP with a positive value, the 
    // Re-Auth-Request-Type AVP MUST be present in an answer message.  
    // The following values are defined:
    //    AUTHORIZE_ONLY = 0,
    //    AUTHORIZE_AUTHENTICATE = 1
    ReAuthRequestType ReauthRequestType(ReAuthRequestType::AUTHORIZE_ONLY);
    raReq.setReAuthRequestType(ReauthRequestType);

    // [2.2.5] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId originStateId(40);
    raReq.setOriginStateId(originStateId);

    // These AVP should not be set by the Application.
    // raReq.addProxyInfo(ProxyInfo(...));
    // raReq.addRouteRecord(RouteRecord(...));
    // add more AVP as ANY values

    cout<<raReq;
    SendDiaAppMsg(raReq, sIdx);
    S9Stats::GetS9Stats()->UpdateSendStats(raReq.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS; 
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the RA Answer to the
 *      diameter stack. Creates the RA Answer object,
 *      populate the AVPs and send the message to the stack.
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
int SendS9RAAnswer(const CommandImpl *impl)
{
    // [1]. Create an instance of  RA Answer class
    // The RA-Answer command is sent by a Diameter
    // server to a Diameter client in order to request deregistration
    // Command-Code = 258 
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::s9::RAAnswer raAns;

    // Create an instance of  RA Request class 
    RARequest rareq(*impl);

    // Get AVP values from Request and set them to Answer Message
    const SessionId& sid = rareq.getSessionId();
    const OriginHost& oh = rareq.getOriginHost();
    const OriginRealm& or1 = rareq.getOriginRealm();
    const DestinationHost& dh = rareq.getDestinationHost();
    const DestinationRealm& dr = rareq.getDestinationRealm();
    const OriginStateId& osid = rareq.getOriginStateId();

    // [2.1.1.x] Fixed AVP

    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    raAns.setSessionId(sid);

    ITS_UINT sIdx = rareq.getSessionIndex();
    raAns.setSessionIndex(sIdx);

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
    raAns.setOriginHost(origHost);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origRealm(dr.value());
    raAns.setOriginRealm(origRealm);

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
    ResultCode resultCode(2001u);
    raAns.setResultCode(resultCode);

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
    // raAns.setExperimentalResult(er1);

    // [2.2.5] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    raAns.setOriginStateId(osid);

    // [2.2.6] The Error-Message AVP (AVP Code 281) is of type UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message
    // Application should not set this.
    // ErrorMessage erm("server problem");
    // raAns.setErrorMessage(erm);

    // [2.2.7] The Error-Reporting-Host AVP (AVP Code 294) is of type
    // DiameterIdentity.  This AVP contains the identity of the Diameter
    // host that sent the Result-Code AVP
    // Application should not set this.
    // ErrorReportingHost erh("abc.def.com");
    // raAns.setErrorReportingHost(erh);

    // [2.2.8] Set Failed AVP
    // Application should not set this.
    // FailedAVP fa;
    // raAns.addFailedAVP(fa);

    // ProxyInfo AVP should not be set by the Application.
    // answer.addProxyInfo(ProxyInfo(...));
    // add more AVP as ANY values

    cout<<raAns;
    SendDiaAppMsg(raAns, sIdx);
    S9Stats::GetS9Stats()->UpdateSendStats(raAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS; 

}
