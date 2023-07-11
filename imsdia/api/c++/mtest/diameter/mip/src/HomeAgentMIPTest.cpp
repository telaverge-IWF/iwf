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
 * LOG: $Log: HomeAgentMIPTest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:10  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.2  2007/01/08 14:15:24  hbhatnagar
 * LOG: made changes for the Accounting and clean up
 * LOG:
 * LOG: Revision 1.1  2007/01/01 15:18:49  hbhatnagar
 * LOG: adding the baseline demo application for the MobileIP
 * LOG:
 *
 * ID: $Id: HomeAgentMIPTest.cpp,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $
 ****************************************************************************/

#include <app.h>
#include <mip_defines.h>
#include <mip_stats.h>
#include <diameter/mip/HomeAgentMIP.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::mip;

extern string sessIdString;
extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the HomeAgentMIPRequest the
 *      diameter stack. Create the HomeAgentMIPRequest object,
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
int SendMipHomeAgentMIPRequest()
{
    // 1. Create an instance of HomeAgentMIPRequest class
    // The AAA sends the Home-Agent-MIP-Request (HAR), indicated by the
    // Command-Code field set to 262 and the 'R' bit set in the Command
    // Flags field, to the Home Agent.
    diameter::mip::HomeAgentMIPRequest haReq;

    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(MIP_INTERFACE_APP_ID, sIdx, sessIdString);
    haReq.setSessionId(diameter::base::SessionId(sessIdString));

    haReq.setSessionIndex(sIdx);


    // Set the Auth-Application-Id AVP.
    // [2.2] The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(MIP_INTERFACE_APP_ID);
    haReq.setAuthApplicationId(authApplicationId);

    // The Authorization-Lifetime AVP (AVP Code 291) is of type Unsigned32
    // and contains the maximum number of seconds of service to be provided
    // to the user before the user is to be re-authenticated and/or re-
    // authorized.
    const AuthorizationLifetime authorizationLifetime(30u);
    haReq.setAuthorizationLifetime(authorizationLifetime);

    // The Auth-Session-State AVP (AVP Code 277) is of type Enumerated and
    // specifies whether state is maintained for a particular session.  The
    // client MAY include this AVP in requests as a hint to the server, but
    // the value in the server's answer message is binding. The values are
    // enum Value {
    //     STATE_MAINTAINED = 0,
    //     NO_STATE_MAINTAINED = 1
    // };
    AuthSessionState  authSessionState(AuthSessionState::STATE_MAINTAINED);
    haReq.setAuthSessionState(authSessionState);

    // The MIP-Reg-Request AVP (AVP Code 320) is of type OctetString and
    // contains the Mobile IPv4 Registration Request [MOBILEIP] sent by the
    // mobile node to the foreign agent.
    MIPRegRequest mIPRegRequest("abcde");
    haReq.setMIPRegRequest(mIPRegRequest);

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
    haReq.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    haReq.setOriginRealm(originRealm);
    
    // [2.1.2.6] Set the User-Name AVP.
    // The User-Name AVP is a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    haReq.setUserName(userName);

    // [2.1] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    haReq.setDestinationRealm(destinationRealm);

    // The MIP-Feature-Vector AVP (AVP Code 337) is of type Unsigned32 and
    // is added with flag values set by the foreign agent or by the AAAF
    // owned by the same administrative domain as the foreign agent.
    MIPFeatureVector mIPFeatureVector(15u);
    haReq.setMIPFeatureVector( mIPFeatureVector);

    /**
     * Optional AVPs
     */
    if (appMode == UNIT_TEST) 
    cout<<haReq;

    SendDiaAppMsg(haReq, sIdx);
    MipStats::GetMipStats()->UpdateSendStats(haReq.getCommandCode(), ITS_TRUE);

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the HomeAgentMIP request
 *      made by the diameter stack. Create the HomeAgentMIPAnswer
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

int SendMipHomeAgentMIPAnswer(const CommandImpl * impl1)
{
    // 1. Create an instance of HomeAgentMIPAnswer class
    // The Push-Notification-Answer command is sent by a server
    // in response to the Location-Info-Request command with
    // Command-Code = 301 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::mip::HomeAgentMIPAnswer haAns;

    // Create an instance of HomeAgentMIPRequest class
    HomeAgentMIPRequest hareq(*impl1);

    // Get some AVP values from Request and set them to Answer Message
    const SessionId &sid1 = hareq.getSessionId();
    const OriginHost &oh1 = hareq.getOriginHost();
    const OriginRealm &or1 = hareq.getOriginRealm();
    
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    haAns.setSessionId(sid1);

    haAns.setSessionIndex(hareq.getSessionIndex());

    // Set the Auth-Application-Id AVP.
    // [2.2] The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(MIP_INTERFACE_APP_ID);
    haAns.setAuthApplicationId(authApplicationId);

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
    haAns.setResultCode(resultCode);

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
    haAns.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    haAns.setOriginRealm(originRealm);
  
   /**
    * Optional AVPs
    */ 
    if (appMode == UNIT_TEST)
    cout<<haAns;
    SendDiaAppMsg(haAns, sIdx);
    MipStats::GetMipStats()->UpdateSendStats(haAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}
