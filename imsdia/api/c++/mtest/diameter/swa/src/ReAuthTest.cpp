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
 * LOG: $Log: ReAuthTest.cpp,v $
 * LOG: Revision 1.1  2011/04/27 12:24:40  vkumara
 * LOG: Draft for SWa interface.
 * LOG:
 * LOG:
 ****************************************************************************/
#ident "$Id: ReAuthTest.cpp,v 1.1 2011/04/27 12:24:40 vkumara Exp $"

#include <app.h>
#include <swa_defines.h>
#include <swa_stats.h>
#include <diameter/swa/ReAuth.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::swa;

extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the ReAuthRequest to the
 *      diameter swack. Create the ReAuthRequest object,
 *      populate the AVPs and send the message to the swack.
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
int SendSWaReAuthRequest()
{
    // [1]. create an inswance of ReAuthRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::swa::ReAuthRequest swaReq;
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.


    cout<<"Please enter the Session ID for ReAuthorization"<<endl;
    string sessIdString;
    cin>>sessIdString;
    swaReq.setSessionId(SessionId(sessIdString));
 
    swaReq.setSessionIndex(sIdx);

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
    swaReq.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    swaReq.setOriginRealm(originRealm);

     // [2.1] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    swaReq.setDestinationRealm(destinationRealm);

    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    swaReq.setDestinationHost(destinationHost);


    // [2.2] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(SWA_INTERFACE_APP_ID);
    swaReq.setAuthApplicationId(authApplicationId);

    ReAuthRequestType reAuthRequestType(ReAuthRequestType::AUTHORIZE_ONLY);
    swaReq.setReAuthRequestType(reAuthRequestType);

    // [2.1] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("user@swa-network.com");
    swaReq.setUserName(userName);

    cout<<swaReq;

    SendDiaAppMsg(swaReq, sIdx);
    SWaStats::GetSWaStats()->UpdateSendStats(swaReq.getCommandCode(), ITS_TRUE);

    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the ReAuth request
 *      made by the diameter swack. Create the ReAuthAnswer
 *      object, populate the AVPs and send the message to the swack.
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
int SendSWaReAuthAnswer(const CommandImpl * impl1)
{

    // 1. Create an inswance of ReAuthAnswer class
    // The PushProfileAnswer command is sent by a server
    // in response to the Re-Auth-Request command with
    // Command-Code = 305 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator
    // Optional param retrans - whether this is a retransmission
    diameter::swa::ReAuthAnswer swaAns;

    // Create an inswance of PushProfileRequest class
    ReAuthRequest swareq(*impl1);

    // Get some AVP values from Request
    const SessionId &sid1 = swareq.getSessionId();
    const OriginHost &oh1 = swareq.getOriginHost();
    const OriginRealm &or1 = swareq.getOriginRealm();

    const UserName &uname = swareq.getUserName();


    // 2. Create the inswances of the classes describing the various
    //    AVPs' present in an LocationInfoRequest command and
    //    pass them by value to the corresponding data members set
    //    methods of the LocationInfoRequest object created
    //    in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    swaAns.setSessionId(sid1);

    swaAns.setSessionIndex(swareq.getSessionIndex());

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
    swaAns.setResultCode(resultCode);

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
    swaAns.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    swaAns.setOriginRealm(originRealm);

    cout<<swaAns;

    SendDiaAppMsg(swaAns, sIdx);
    SWaStats::GetSWaStats()->UpdateSendStats(swaAns.getCommandCode(), ITS_FALSE);

    return (ITS_SUCCESS);
}
