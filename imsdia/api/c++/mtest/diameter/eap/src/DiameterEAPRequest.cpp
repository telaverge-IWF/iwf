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
 * LOG: $Log: DiameterEAPRequest.cpp,v $
 * LOG: Revision 3.3  2008/04/16 10:47:35  avinashks
 * LOG: Changes done as enhancement for EAP application against Bug id 843 logged by
 * LOG: lakshmys during validation.
 * LOG:
 * LOG: Revision 3.2  2008/04/07 09:44:18  avinashks
 * LOG: Changes made for Implementation of Proxy client.
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:09  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/01/01 14:52:17  nanaparthi
 * LOG: EAP Demo for Static and Distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: DiameterEAPRequest.cpp,v 3.3 2008/04/16 10:47:35 avinashks Exp $
 ****************************************************************************/
#ident "$Id: DiameterEAPRequest.cpp,v 3.3 2008/04/16 10:47:35 avinashks Exp $"

#include <app.h>
#include <eap_defines.h>
#include <eap_stats.h>
#include <diameter/eap/DiameterEAP.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::nasreq;
using namespace diameter::eap;

string sessIdString;
ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the  EapDiameterEAPRequest to the
 *      diameter stack. Create the  EapDiameterEAPRequest object,
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
int SendEapDiameterEAPRequest()
{
    // [1]. Create an instance of MultimediaAuthenticationRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::eap::DiameterEAPRequest eapReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(EAP_INTERFACE_APP_ID, sIdx, sessIdString);
    eapReq.setSessionId(diameter::base::SessionId(sessIdString));

    eapReq.setSessionIndex(sIdx);

    // [2.1.2.x] Required AVPs
    // Set the Auth-Application-Id AVP.
    // [2.1.2.1.3] The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(EAP_INTERFACE_APP_ID);
    eapReq.setAuthApplicationId(authApplicationId);

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
    //    eapReq.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

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
    eapReq.setAuthSessionState(authSessionState);

    // [2.1.2.3] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    eapReq.setOriginHost(originHost);

    // [2.1.2.4] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    eapReq.setOriginRealm(originRealm);

    // [2.1.2.5] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    eapReq.setDestinationRealm(destinationRealm);


    // [2.2.1] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    eapReq.setDestinationHost(destinationHost);


    AuthRequestType  authRequestType(AuthRequestType::AUTHORIZE_AUTHENTICATE);
    eapReq.setAuthRequestType(authRequestType);


    EAPPayload eAPPayload("Encapsulate EAP Packet Information");
    eapReq.setEAPPayload(eAPPayload);




    // Application should not set this AVP.
    // eapReq.addProxyInfo(diameter::base::ProxyInfo(...));
    // eapReq.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values

    if (appMode == UNIT_TEST)
    cout<<eapReq;

    // Send object to stack.
    SendDiaAppMsg(eapReq, sIdx);

    EapStats::GetEapStats()->UpdateSendStats(eapReq.getCommandCode(), ITS_TRUE);
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
int SendEapDiameterEAPAnswer(const CommandImpl * impl)
{
    // 1. Create an instance of MultimediaAuthAnswer class
    // The Multimedia-Auth-Answer command is sent by a server
    // in response to the Multimedia-Auth-Request command with
    // Command-Code = 303 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::eap::DiameterEAPAnswer eapAns;

    // Create an instance of MultimediaAuthRequest class to get host and
    // session details
    DiameterEAPRequest eapreq(*impl);

    // Get AVP values from requested message
    const SessionId &sid1 = eapreq.getSessionId();
    const AuthApplicationId &aaid = eapreq.getAuthApplicationId();
    const AuthRequestType &authRequestType = eapreq.getAuthRequestType();

    const OriginHost &oh1 = eapreq.getOriginHost();
    const OriginRealm &or1 = eapreq.getOriginRealm();
    const DestinationRealm &dr1 = eapreq.getDestinationRealm();

    const AuthSessionState &authSessState = eapreq.getAuthSessionState();



    //  const SIPAuthDataItem &sipAuthData = eapreq.getSIPAuthDataItem();

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
    eapAns.setSessionId(sid1);

    eapAns.setSessionIndex(eapreq.getSessionIndex());


    eapAns.setAuthApplicationId(aaid);

    eapAns.setAuthRequestType(authRequestType);

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
    eapAns.setAuthSessionState(authSessState);

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
    eapAns.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    eapAns.setOriginRealm(originRealm);



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
    eapAns.setResultCode(resultCode);

    int pinfo_count = eapreq.countProxyInfo();
    for(int i=0; i<pinfo_count; i++)
    {
        ProxyInfo pinfo;
        ProxyHost phost(eapreq.getProxyInfo(i).getProxyHost());
        pinfo.setProxyHost(phost);

        ProxyState pstate(eapreq.getProxyInfo(i).getProxyState());
        pinfo.setProxyState(pstate);

        eapAns.addProxyInfo(pinfo);
    }

    if (appMode == UNIT_TEST)
    cout<<eapAns;

    // Send Object to stack.
    SendDiaAppMsg(eapAns, sIdx);

    // Update stats.
    EapStats::GetEapStats()->UpdateSendStats(eapAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}


