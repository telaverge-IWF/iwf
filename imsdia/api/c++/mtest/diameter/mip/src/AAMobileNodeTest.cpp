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
 * LOG: $Log: AAMobileNodeTest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:10  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.2  2007/01/08 14:14:10  hbhatnagar
 * LOG: Added few optional AVPs
 * LOG:
 * LOG: Revision 1.1  2007/01/01 15:18:49  hbhatnagar
 * LOG: adding the baseline demo application for the MobileIP
 * LOG:
 *
 * ID: $Id: AAMobileNodeTest.cpp,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $
 ****************************************************************************/

#include <app.h>
#include <mip_defines.h>
#include <mip_stats.h>
#include <diameter/mip/AAMobileNode.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::mip;

string sessIdString;
ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the MipAAMobileNodeRequest to the
 *      diameter stack. Create the MipAAMobileNodeRequest object,
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
int SendMipAAMobileNodeRequest()
{
    // [1]. create an instance of AAMobileNodeRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::mip::AAMobileNodeRequest amReq;

    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(MIP_INTERFACE_APP_ID, sIdx,sessIdString);
    amReq.setSessionId(diameter::base::SessionId(sessIdString));
    amReq.setSessionIndex(sIdx);

    // [2.1.2.1] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP shall contain the value of TBD as defined in X-S0013-013-0.
    // The AVP code of Auth-Application-Id is 258.
    const AuthApplicationId authApplicationId(MIP_INTERFACE_APP_ID);
    amReq.setAuthApplicationId(authApplicationId);

    // [2.1.2.6] Set the User-Name AVP.
    // The User-Name AVP is a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    const UserName userName("sip:user@3gppnetwork.com");
    amReq.setUserName(userName);

    // [2.1] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    const DestinationRealm destinationRealm(GetDestinationRealm());
    amReq.setDestinationRealm(destinationRealm);

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
    const OriginHost originHost(GetOriginHost());
    amReq.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    const OriginRealm originRealm(GetOriginRealm());
    amReq.setOriginRealm(originRealm);

    // The MIP-Reg-Request AVP (AVP Code 320) is of type OctetString and
    // contains the Mobile IPv4 Registration Request [MOBILEIP] sent by the
    // mobile node to the foreign agent.
    const MIPRegRequest mIPRegRequest("abcde"); 
    amReq.setMIPRegRequest(mIPRegRequest);

    // The MN-AAA-Auth AVP (AVP Code 322) is of type Grouped and contains
    // some ancillary data to simplify processing of the authentication data
    // in the Mobile IPv4 Registration Request [MOBILEIP, MIPCHAL] by the
    // target AAA server.
    MIPMNAAAAuth  mIPMNAAAAuth;

    const MIPMNAAASPI mIPMNAAASPI(1001u);
    mIPMNAAAAuth.setMIPMNAAASPI(mIPMNAAASPI);
   
    const MIPAuthInputDataLength  maidl(100u);
    mIPMNAAAAuth.setMIPAuthInputDataLength(maidl);
   
    const MIPAuthenticatorLength mal(50u);
    mIPMNAAAAuth.setMIPAuthenticatorLength(mal);

    const MIPAuthenticatorOffset mao(10u);
    mIPMNAAAAuth.setMIPAuthenticatorOffset(mao);
 
    amReq.setMIPMNAAAAuth(mIPMNAAAAuth);
        
    /**
     * Optional AVPs
     */

    // The Acct-Multi-Session-Id AVP (AVP Code 50) is of type UTF8String,
    // following the format specified in Section 8.8.  The Acct-Multi-
    // Session-Id AVP is used to link together multiple related accounting
    // sessions, where each session would have a unique Session-Id, but the
    // same Acct-Multi-Session-Id AVP.  This AVP MAY be returned by the
    // Diameter server in an authorization answer, and MUST be used in all
    // accounting messages for the given session.
    const AcctMultiSessionId acctMultiSessionId("xyz:123");
    amReq.setAcctMultiSessionId(acctMultiSessionId);

    DestinationHost destinationHost(GetDestinationHost());
    amReq.setDestinationHost(destinationHost);
    
    OriginStateId originStateId(123456u);
    amReq.setOriginStateId(originStateId);
   
    Address addrmn(Address::IPV4, "192.168.1.1");
    MIPMobileNodeAddress mmna(addrmn);
    amReq.setMIPMobileNodeAddress(mmna);

    Address addrha(Address::IPV4, "192.168.1.2");
    MIPHomeAgentAddress mhaa(addrha);
    amReq.setMIPHomeAgentAddress(mhaa); 
 
    MIPFeatureVector  mfv(6789u);
    amReq.setMIPFeatureVector(mfv);
    
    MIPOriginatingForeignAAA mofa;
    mofa.setOriginHost(originHost);
    mofa.setOriginRealm(originRealm);
    amReq.setMIPOriginatingForeignAAA(mofa);

    AuthorizationLifetime authlt(30u);
    amReq.setAuthorizationLifetime(authlt);

    AuthSessionState  authSessionState(AuthSessionState::STATE_MAINTAINED);
    amReq.setAuthSessionState(authSessionState);
        
    if (appMode == UNIT_TEST)
    cout<<amReq;

    SendDiaAppMsg(amReq, sIdx);
    MipStats::GetMipStats()->UpdateSendStats(amReq.getCommandCode(), ITS_TRUE);

    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the MipAAMobileNode request
 *      made by the diameter stack. Create the MipAAMobileNodeAnswer
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
int SendMipAAMobileNodeAnswer(const CommandImpl * impl1)
{

    diameter::mip::AAMobileNodeAnswer amAns;

    // Create an instance of AAMobileNodeRequest class
    AAMobileNodeRequest amreq(*impl1);

    // Get some AVP values from Request
    const SessionId &sid1       = amreq.getSessionId(); 
    const OriginHost &oh1       = amreq.getOriginHost();
    //const DestinationHost &dh1  = amreq.getDestinationHost();
    const OriginRealm &or1      = amreq.getOriginRealm();
    const DestinationRealm &dr1 = amreq.getDestinationRealm();

    // 2. Create the instances of the classes describing the various
    //    AVPs' present in an LocationInfoRequest command and
    //    pass them by value to the corresponding data members set
    //    methods of the LocationInfoRequest object created
    //    in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    amAns.setSessionId(sid1);
    amAns.setSessionIndex(amreq.getSessionIndex());

    const AuthApplicationId authApplicationId(MIP_INTERFACE_APP_ID);
    amAns.setAuthApplicationId(authApplicationId);

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
    amAns.setResultCode(resultCode);

    // [2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP MIPOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    amAns.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(dr1.value());
    amAns.setOriginRealm(originRealm);

    if (appMode == UNIT_TEST)
    cout<<amAns;

    SendDiaAppMsg(amAns, sIdx);
    MipStats::GetMipStats()->UpdateSendStats(amAns.getCommandCode(), ITS_FALSE);

    return (ITS_SUCCESS);
}
