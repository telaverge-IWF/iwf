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
 * LOG: $Log: SessionTerminationTest.cpp,v $
 * LOG: Revision 1.1  2011/06/14 05:25:38  vkumara
 * LOG: Baseline for Gmb interface.
 * LOG:
 * LOG:
 * 
 * ID: $Id: SessionTerminationTest.cpp,v 1.1 2011/06/14 05:25:38 vkumara Exp $
 ****************************************************************************/
#ident "$Id: SessionTerminationTest.cpp,v 1.1 2011/06/14 05:25:38 vkumara Exp $"

#include <app.h>
#include <gmb_defines.h>
#include <gmb_stats.h>
#include <diameter/gmb/ST.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::gmb;

extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the SessionTerminationRequestto the
 *      diameter stack. Create the SessionTerminationRequest object,
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
int SendGmbSessionTerminationRequest()
{
    // 1. Create an instance of RegistrationTerminationRequest class
    // The Registration-Termination-Request command is sent from a Diameter
    // multimedia client to a Diameter multimedia server in order to
    // saReq it to store the name of the server that is currently
    // serving the user.
    // Command-Code = 301 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gmb::STRequest stReq(false,false);

    // 2. Create the instances of the classes describing the various
    // AVPs' present in an RegistrationTerminationRequest command and
    // pass them by value to the corresponding data members set
    // methods of the RegistrationTerminationRequest object created
    // in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
         
    cout<<"Please enter the Session ID to Terminate"<<endl;
    string sessIdString;
    cin>>sessIdString;

    stReq.setSessionId(SessionId(sessIdString));
    stReq.setSessionIndex(sIdx);

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
    stReq.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    stReq.setOriginRealm(originRealm);

    // [2.1] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    stReq.setDestinationRealm(destinationRealm);

    // Set the Auth-Application-Id AVP.
    // [2.2] The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(GMB_INTERFACE_APP_ID);
    stReq.setAuthApplicationId(authApplicationId);


    // [2.1.2.5] Populate required parameter "Termination-Cause".
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
    TerminationCause terminationCause(TerminationCause::DIAMETER_BAD_ANSWER);
    stReq.setTerminationCause(terminationCause);


    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    // This AVP identifies the endpoint where Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    stReq.setDestinationHost(destinationHost);

    cout<<stReq;

    SendDiaAppMsg(stReq, sIdx);
    GmbStats::GetGmbStats()->UpdateSendStats(stReq.getCommandCode(),
                                                                ITS_TRUE);
    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the SessionTermination
 *      request made by the diameter stack. Create the
 *      SessionTerminationAnswer object, populate the AVPs and send the
 *      message to the stack. send message to Diameter Stack
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

int SendGmbSessionTerminationAnswer(const CommandImpl * impl1)
{
    // 1. Create an instance of RegistrationTerminationAnswer class
    // The Registration-Termination-Answer command is sent by a server
    // in response to the Registration-Termination-Request command with
    // Command-Code = 304 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::gmb::STAnswer sta(false,false);

    // Create an instance of RegistrationTerminationrequest class
    STRequest streq(*impl1);

    // Get some AVP values from requested Message and set them to Answer
    const SessionId &sid1 = streq.getSessionId();
    const OriginHost &oh1 = streq.getOriginHost();
    const OriginRealm &or1 = streq.getOriginRealm();

    // 2. Create the instances of the classes describing the various
    // AVPs' present in an RegistrationTerminationAnswer command and
    // pass them by value to the corresponding data members set
    // methods of the RegistrationTerminationAnswer object created
    // in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    sta.setSessionId(sid1);

    sta.setSessionIndex(streq.getSessionIndex());

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
    sta.setResultCode(resultCode);

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
    sta.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    sta.setOriginRealm(originRealm);

    cout << sta;

    SendDiaAppMsg(sta, sIdx);
    GmbStats::GetGmbStats()->UpdateSendStats(sta.getCommandCode(), ITS_FALSE);
    return (ITS_SUCCESS);
}
