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
 * LOG: $Log: AbortSessionTest.cpp,v $
 * LOG: Revision 1.1  2011/06/29 06:33:13  vkumara
 * LOG: Baseline for rr_requestmodel interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: AbortSessionTest.cpp,v 1.1 2011/06/29 06:33:13 vkumara Exp $
 ****************************************************************************/
#ident "$Id: AbortSessionTest.cpp,v 1.1 2011/06/29 06:33:13 vkumara Exp $"

#include <app.h>
#include <rr_requestmodel_defines.h>
#include <rr_requestmodel_stats.h>
#include <diameter/rr_requestmodel/AS.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::rr_requestmodel;

extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Rr_requestmodelAbortSessionRequest to the
 *      diameter stack. Create the WdAbortSessionRequest object,
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
int SendRr_requestmodelASRequest()
{
    // 1. Create an instance of Rr_requestmodelASRequest class
    // Command-Code = 274 and 'R' bit set
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::rr_requestmodel::ASRequest asReq;

    // 2. Create the instances of the classes describing the various
    // AVPs' present in an UserAuthorizationRequest command and
    // pass them by value to the corresponding data members set
    // methods of the UserAuthorizationRequest object created
    // in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    
    string sessIdString;
    cout<<"Please Enter the Session ID to Abort \n";
    cin>>sessIdString;
    
    asReq.setSessionId(SessionId(sessIdString));
    asReq.setSessionIndex(sIdx);

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
    asReq.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    asReq.setOriginRealm(originRealm);

    // [2.1] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    asReq.setDestinationRealm(destinationRealm);

    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    asReq.setDestinationHost(destinationHost);


    // Set the Auth-Application-Id AVP.
    // [2.2] The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authApplicationId(RR_REQUESTMODEL_INTERFACE_APP_ID);
    asReq.setAuthApplicationId(authApplicationId);

    /**
     * The Abort-Cause AVP (AVP code 500) is of type Enumerated, and it determines the cause of an ASR
     */
     AbortCause  ac(AbortCause::INSUFFICIENT_SERVER_RESOURCES);
     asReq.setAbortCause(ac);

    cout<<asReq;

    SendDiaAppMsg(asReq, sIdx);
    Rr_requestmodelStats::GetRr_requestmodelStats()->UpdateSendStats(asReq.getCommandCode(), ITS_TRUE);

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the Rr_requestmodelAbortSession request
 *      made by the diameter stack. Create the Rr_requestmodelAbortSession Answer
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
int SendRr_requestmodelASAnswer(const CommandImpl * impl1)
{
    // 1. Create an instance of ServerAssignmentAnswer class
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::rr_requestmodel::ASAnswer asAns;

    // Create an instance of Rr_requestmodelASRequest class
    ASRequest asreq(*impl1);

    // Get some AVP values from Request and set them to Answer Message
    const SessionId &sid1 = asreq.getSessionId();
    const OriginHost &oh1 = asreq.getOriginHost();
    const OriginRealm &or1 = asreq.getOriginRealm();

    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    asAns.setSessionId(sid1);

    asAns.setSessionIndex(asreq.getSessionIndex());

    // [2.2] Set the Result-Code AVP .
    // The Result-Code AVP indicates whether a particular request
    // rr_requestmodels completed successfully or whether an error occurred
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
    asAns.setResultCode(resultCode);

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
    asAns.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    asAns.setOriginRealm(originRealm);

    cout<<asAns;

    SendDiaAppMsg(asAns, sIdx);
    Rr_requestmodelStats::GetRr_requestmodelStats()->UpdateSendStats(asAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}
