/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: AATest.cpp,v $
 * LOG: Revision 1.1  2011/07/14 11:53:20  vkumara
 * LOG: Baseline for Rs interface.
 * LOG:
 * LOG:
 * ID: $Id: AATest.cpp,v 1.1 2011/07/14 11:53:20 vkumara Exp $
 ****************************************************************************/
#ident "$Id: AATest.cpp,v 1.1 2011/07/14 11:53:20 vkumara Exp $"


#include <app.h>
#include <rs_defines.h>
#include <rs_stats.h>
#include <diameter/rs/AA.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::nasreq;
using namespace diameter::rs;

string sessIdString;
ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the RsAARequest to the
 *      diameter stack. Create the  RsAARequest object,
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
int SendRsAARequest()
{
    // [1]. Create an instance of RsAARequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::rs::AARequest aaReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(RS_INTERFACE_APP_ID, sIdx, sessIdString);
    aaReq.setSessionId(diameter::base::SessionId(sessIdString));

    aaReq.setSessionIndex(sIdx);

    // Set the Auth-Application-Id AVP.
    // [2.1.2.1.3] The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(RS_INTERFACE_APP_ID);
    aaReq.setAuthApplicationId(authApplicationId);

    // [2.1.2.3] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    aaReq.setOriginHost(originHost);

    // [2.1.2.4] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    aaReq.setOriginRealm(originRealm);

    // [2.1.2.5] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    aaReq.setDestinationRealm(destinationRealm);

    AuthRequestType  authRequestType(AuthRequestType::AUTHORIZE_AUTHENTICATE);
    aaReq.setAuthRequestType(authRequestType);


    // [2.1.2.6] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("sip:user@3gppnetwork.com");
    aaReq.setUserName(userName);


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
    AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    aaReq.setAuthSessionState(authSessionState);
    

    // Application should not set this AVP.
    // aaReq.addProxyInfo(diameter::base::ProxyInfo(...));
    // aaReq.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values

    if (appMode == UNIT_TEST)
    cout<<aaReq;

    // Send object to stack.
    SendDiaAppMsg(aaReq, sIdx);

    RsStats::GetRsStats()->UpdateSendStats(aaReq.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends the Answer to the Rs AA request
 *      made by the diameter stack. Create the WdAAAnswer
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
int SendRsAAAnswer(const CommandImpl * impl)
{
    // 1. Create an instance of RsAAAnswer class
    // The Multimedia-Auth-Answer command is sent by a server
    // in response to the Multimedia-Auth-Request command with
    // Command-Code = 265 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::rs::AAAnswer aaAns;

    // Create an instance of MultimediaAuthRequest class to get host and
    // session details
    AARequest aareq(*impl);

    // Get AVP values from requested message
    const SessionId &sid1 = aareq.getSessionId();
    const OriginHost &oh1 = aareq.getOriginHost();
    const OriginRealm &or1 = aareq.getOriginRealm();

    const AuthApplicationId &aaid = aareq.getAuthApplicationId();
    const AuthRequestType &authRequestType = aareq.getAuthRequestType();

    const AuthSessionState &authSessState = aareq.getAuthSessionState();
    const UserName &uname = aareq.getUserName();

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
    aaAns.setSessionId(sid1);

    aaAns.setSessionIndex(aareq.getSessionIndex());

    // [2.1.2.x] Required AVPs

    aaAns.setAuthApplicationId(aaid);

    aaAns.setAuthRequestType(authRequestType);

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
    ResultCode resultCode(2001u);
    aaAns.setResultCode(resultCode);

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
    aaAns.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    aaAns.setOriginRealm(originRealm);

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
    aaAns.setAuthSessionState(authSessState);


    if (appMode == UNIT_TEST)
    cout<<aaAns;

    // Send Object to stack.
    SendDiaAppMsg(aaAns, sIdx);

    // Update stats.
    RsStats::GetRsStats()->UpdateSendStats(aaAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}

