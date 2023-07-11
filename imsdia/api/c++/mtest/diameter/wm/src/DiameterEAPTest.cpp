/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2007 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: DiameterEAPTest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:14  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/02/28 11:03:09  hbhatnagar
 * LOG: Baseline Demo Application for Wm Interface.
 * LOG:
 *
 * ID: $Id: DiameterEAPTest.cpp,v 3.1 2008/03/31 10:33:14 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: DiameterEAPTest.cpp,v 3.1 2008/03/31 10:33:14 nvijikumar Exp $"

#include <app.h>
#include <wm_defines.h>
#include <wm_stats.h>
#include <diameter/wm/DiameterEAP.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::eap;
using namespace diameter::wm;

extern string sessIdString;
extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the  WmDiameterEAPRequest to the
 *      diameter stack. Create the  WmDiameterEAPRequest object,
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
int SendWmDiameterEAPRequest()
{
    // [1]. Create an instance of MultimediaAuthenticationRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::wm::DiameterEAPRequest wmDerReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(WM_INTERFACE_APP_ID, sIdx, sessIdString);
    wmDerReq.setSessionId(diameter::base::SessionId(sessIdString));

    wmDerReq.setSessionIndex(sIdx);

    // [2.1.2.x] Required AVPs
    // Set the Auth-Application-Id AVP.
    // [2.1.2.1.3] The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(WM_INTERFACE_APP_ID);
    wmDerReq.setAuthApplicationId(authApplicationId);


    // [2.1.2.3] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    wmDerReq.setOriginHost(originHost);

    // [2.1.2.4] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    wmDerReq.setOriginRealm(originRealm);

    // [2.1.2.5] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    wmDerReq.setDestinationRealm(destinationRealm);


    // [2.2.1] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    wmDerReq.setDestinationHost(destinationHost);


    AuthRequestType  authRequestType(AuthRequestType::AUTHORIZE_AUTHENTICATE);
    wmDerReq.setAuthRequestType(authRequestType);

    diameter::eap::EAPPayload eAPPayload("Encapsulate EAP Packet Information");
    wmDerReq.setEAPPayload(eAPPayload);

    // Application should not set this AVP.
    // wmDerReq.addProxyInfo(diameter::base::ProxyInfo(...));
    // wmDerReq.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values

    if (appMode == UNIT_TEST)
    cout<<wmDerReq;

    // Send object to stack.
    SendDiaAppMsg(wmDerReq, sIdx);

    WmStats::GetWmStats()->UpdateSendStats(wmDerReq.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends the Answer to the WmDiameterEAPRequest 
 *      made by the diameter stack. Create the WmDiameterEAPAnswer
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
int SendWmDiameterEAPAnswer(const CommandImpl * impl)
{
    // 1. Create an instance of MultimediaAuthAnswer class
    // The Multimedia-Auth-Answer command is sent by a server
    // in response to the Multimedia-Auth-Request command with
    // Command-Code = 303 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::wm::DiameterEAPAnswer wmDerAns;

    // Create an instance of MultimediaAuthRequest class to get host and
    // session details
    DiameterEAPRequest wmDerreq(*impl);

    // Get AVP values from requested message
    const SessionId &sid1 = wmDerreq.getSessionId();
    const AuthApplicationId &aaid = wmDerreq.getAuthApplicationId();
    const AuthRequestType &authRequestType = wmDerreq.getAuthRequestType();

    const OriginHost &oh1 = wmDerreq.getOriginHost();
    const OriginRealm &or1 = wmDerreq.getOriginRealm();
    if (wmDerreq.containsDestinationHost())
        const DestinationHost &dh1 = wmDerreq.getDestinationHost();

    const DestinationRealm &dr1 = wmDerreq.getDestinationRealm();


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
    wmDerAns.setSessionId(sid1);

    wmDerAns.setSessionIndex(wmDerreq.getSessionIndex());


    wmDerAns.setAuthApplicationId(aaid);

    wmDerAns.setAuthRequestType(authRequestType);


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
    wmDerAns.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    wmDerAns.setOriginRealm(originRealm);

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
    wmDerAns.setResultCode(resultCode);


    if (appMode == UNIT_TEST)
    cout<<wmDerAns;

    // Send Object to stack.
    SendDiaAppMsg(wmDerAns, sIdx);

    // Update stats.
    WmStats::GetWmStats()->UpdateSendStats(wmDerAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}
