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
 * LOG: $Log: AccountingTest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:10  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/01/01 14:31:42  nanaparthi
 * LOG: NASREQ Demo for Static and Distributed
 * LOG:
 * LOG:
 *
 * ID: $Id: AccountingTest.cpp,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: AccountingTest.cpp,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $"

#include <app.h>
#include <nasreq_defines.h>
#include <nasreq_stats.h>
#include <diameter/nasreq/AC.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::nasreq;

// using namespace diameter::nasreq;

extern string sessIdString;
extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the  UserAuthorizationRequest to the
 *      diameter stack. Create the  UserAuthorizationRequest object,
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
int SendNasreqAccountingRequest()
{
    // [1]. Create an instance of UserAuthorizationRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::nasreq::ACRequest acReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(NASREQ_INTERFACE_APP_ID, sIdx, sessIdString);
    acReq.setSessionId(diameter::base::SessionId(sessIdString));

    acReq.setSessionIndex(sIdx);


    // [2.1.2.3] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    acReq.setOriginHost(originHost);

    // [2.1.2.4] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    acReq.setOriginRealm(originRealm);

    // [2.1.2.5] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    acReq.setDestinationRealm(destinationRealm);


    // [2.1.2.4] Populate required paramete "Accounting-Record-Type".
    // Set the Accounting-Record-Type AVP.
    // The data type of Accounting-Record-Type is Enumerated.
    // This Avp contains the type of accounting record being sent.
    // The following values are currently defined
    // EVENT_RECORD                    1
    // START_RECORD                    2
    // The AVP Code of Accounting-Record-Type is 480.
    AccountingRecordType accountingRecordType(AccountingRecordType::START_RECORD);
    acReq.setAccountingRecordType(accountingRecordType);

    // [2.1.2.5] Populate required paramete "Accounting-Record-Number".
    // Set the Accounting-Record-Number AVP.
    // The data type of Accounting-Record-Number is Unsigned32.
    // This AVP identifies this record within one session.
    // The AVP Code of Accounting-Record-Number is 485.
    AccountingRecordNumber accountingRecordNumber(1);
    acReq.setAccountingRecordNumber(accountingRecordNumber);

    // [2.1.2.6] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    UserName userName("user@nasreq-network.com");
    acReq.setUserName(userName);

    // [2.2.1] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    acReq.setDestinationHost(destinationHost);

    // Application should not set this AVP.
    // acReq.addProxyInfo(diameter::base::ProxyInfo(...));
    // acReq.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values

    if (appMode == UNIT_TEST)
    cout<<acReq;

    // Send object to stack.
    SendDiaAppMsg(acReq, sIdx);

    NasreqStats::GetNasreqStats()->UpdateSendStats(acReq.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends the Answer to the UserAuthorization request
 *      made by the diameter stack. Create the UserAuthorizationAnswer
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
int SendNasreqAccountingAnswer(const CommandImpl * impl)
{
    // 1. Create an instance of UserAuthorizationAnswer class
    // The User-Authorization-Answer command is sent by a server
    // in response to the User-Authorization-Request command with
    // Command-Code = 303 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::nasreq::ACAnswer acAns;

    // Create an instance of UserAuthorizationRequest class to get host and
    // session details
    ACRequest acReq(*impl);

    // Get AVP values from requested message
    const SessionId &sid1 = acReq.getSessionId();
    const OriginHost &oh1 = acReq.getOriginHost();
    const OriginRealm &or1 = acReq.getOriginRealm();

    const AccountingRecordType &acrtype = acReq.getAccountingRecordType();
    const AccountingRecordNumber &acrno = acReq.getAccountingRecordNumber();

    const UserName &uname = acReq.getUserName();


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
    acAns.setSessionId(sid1);

    acAns.setSessionIndex(acReq.getSessionIndex());

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
    acAns.setResultCode(resultCode);

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
    acAns.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    acAns.setOriginRealm(originRealm);


    acAns.setAccountingRecordType(acrtype);

    acAns.setAccountingRecordNumber(acrno);



    // [2.1] Set the User-Name AVP.
    // The User-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of User-Name AVP is 1.
    // The data type of User-Name AVP is UTF8String.
    acAns.setUserName(uname);

    // It is an Geouped AVP.
    // The AVP Code of Proxy-Info AVP is 284
    // The data type of Proxy-Info is Grouped Type.
    // This AVP should not be set by Application.
    // acAns.setProxyInfo(diameter::base::ProxyInfo(...));

    // Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    // This AVP should not be set by Application.
    // acAns.setRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values


    if (appMode == UNIT_TEST)
    cout<<acAns;

    // Send Object to stack.
    SendDiaAppMsg(acAns, sIdx);

    // Update stats.
    NasreqStats::GetNasreqStats()->UpdateSendStats(acAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}
