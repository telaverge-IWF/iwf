/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2011 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * CONTPICT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: PITest.cpp,v $
 * LOG: Revision 1.1  2011/07/14 11:51:38  vkumara
 * LOG: Baseline for Rw interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: PITest.cpp,v 1.1 2011/07/14 11:51:38 vkumara Exp $
 ****************************************************************************/
#ident "$Id: PITest.cpp,v 1.1 2011/07/14 11:51:38 vkumara Exp $"

#include <app.h>
#include <rw_defines.h>
#include <rw_stats.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::rw;

extern string sessIdString;
extern ITS_UINT sIdx;

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the PI piReq to the
 *      diameter stack. Creates the PI Request object,
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
int SendRwPIRequest()
{

    // [1] Create an instance of PIRequest class
    // The PI-Request command is sent by a Diameter
    // client to a Diameter Server in order to piReq deregistration
    // Command-Code = 315
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::rw::PIRequest piReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(RW_INTERFACE_APP_ID, sIdx, sessIdString);
    piReq.setSessionId(diameter::base::SessionId(sessIdString));

    piReq.setSessionIndex(sIdx);

    // [2.1.2.5] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authAppId(RW_INTERFACE_APP_ID);
    piReq.setAuthApplicationId(authAppId);

    // [2.1.2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter  messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost orighost(GetOriginHost());
    piReq.setOriginHost(orighost);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origrealm(GetOriginRealm());
    piReq.setOriginRealm(origrealm);

    // [2.1.2.3] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destRealm(GetDestinationRealm());
    piReq.setDestinationRealm(destRealm);
    
    // [2.1.2.4] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost destHost(GetDestinationHost());
    piReq.setDestinationHost(destHost);

    /**
     * The PI_Request_Type AVP (ITU-T AVP Code 1010) is of type Enumerated and contains the reason
     * for sending the Policy Install Request command. It MUST be present in all
     * Policy-Install-Request messages.
     * Here we are using 5056  AVP Code instead of 1010 (given in specs).
     * 1010 is using by Precedence  AVP .
     */
     PI_Request_Type piReqType(PI_Request_Type::INITIAL_REQUEST); 
     piReq.setPI_Request_Type(piReqType);


    /**
     * The PI-Request-Number AVP (ITU-T AVP Code 1011) is of type Unsigned32 and identifies
     * this request within one session.
     * Here we are using 5057  AVP Code instead of 1011 (given in specs).
     * 1011 is using by  Reporting-Level   AVP .
     */
     PIRequestNumber   piReqNum(1234);
     piReq.setPIRequestNumber(piReqNum);


    // [2.2.5] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     
    // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId originStateId(40);
    piReq.setOriginStateId(originStateId);

    // These AVP should not be set by the Application.
    // piReq.addProxyInfo(ProxyInfo(...));
    // piReq.addRouteRecord(RouteRecord(...));
    // add more AVP as ANY values

    cout<<endl<<"PIR : "<<piReq<<endl;
    SendDiaAppMsg(piReq, sIdx);
    RwStats::GetRwStats()->UpdateSendStats(piReq.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS; 
}

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the PI Answer to the
 *      diameter stack. Creates the PI Answer object,
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
int SendRwPIAnswer(const CommandImpl *impl)
{
    // [1]. Create an instance of  PI Answer class
    // The PI-Answer command is sent by a Diameter
    // server to a Diameter client in order to request deregistration
    // Command-Code = 315 
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::rw::PIAnswer piAns;

    // Create an instance of  PI Request class 
    PIRequest pireq(*impl);

    // Get AVP values from Request and set them to Answer Message
    const SessionId& sid = pireq.getSessionId();
    const OriginHost& oh = pireq.getOriginHost();
    const OriginRealm& or1 = pireq.getOriginRealm();
    const DestinationHost& dh = pireq.getDestinationHost();
    const DestinationRealm& dr = pireq.getDestinationRealm();
    const OriginStateId& osid = pireq.getOriginStateId();

    // [2.1.1.x] Fixed AVP

    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    piAns.setSessionId(sid);

    ITS_UINT sIdx = pireq.getSessionIndex();
    piAns.setSessionIndex(sIdx);

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
    piAns.setOriginHost(origHost);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origRealm(dr.value());
    piAns.setOriginRealm(origRealm);

    /**
     * The PI_Request_Type AVP (ITU-T AVP Code 1010) is of type Enumerated and contains the reason
     * for sending the Policy Install Request command. It MUST be present in all
     * Policy-Install-Request messages.
     * Here we are using 5056  AVP Code instead of 1010 (given in specs).
     * 1010 is using by Precedence  AVP .
     */
     PI_Request_Type piReqType(PI_Request_Type::INITIAL_REQUEST);
     piAns.setPI_Request_Type(piReqType);


    /**
     * The PI-Request-Number AVP (ITU-T AVP Code 1011) is of type Unsigned32 and identifies
     * this request within one session.
     * Here we are using 5057  AVP Code instead of 1011 (given in specs).
     * 1011 is using by  Reporting-Level   AVP .
     */
     PIRequestNumber   piReqNum(5678);
     piAns.setPIRequestNumber(piReqNum);

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
    piAns.setResultCode(resultCode);

    // [2.2.5] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     
    // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    piAns.setOriginStateId(osid);

    cout<<endl<<"PIA : "<<piAns<<endl;
    SendDiaAppMsg(piAns, sIdx);
    RwStats::GetRwStats()->UpdateSendStats(piAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS; 
}
