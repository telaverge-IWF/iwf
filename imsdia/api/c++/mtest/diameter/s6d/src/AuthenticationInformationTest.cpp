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
 * LOG: $Log: AuthenticationInformationTest.cpp,v $
 * LOG: Revision 1.1  2011/05/04 10:46:01  vkumara
 * LOG: Baseline for S6d interface.
 * LOG:
 * LOG:
 * ID: $Id: AuthenticationInformationTest.cpp,v 1.1 2011/05/04 10:46:01 vkumara Exp $
 ***************************************************************************/

#include <app.h>
#include <s6d_defines.h>
#include <s6d_stats.h>
#include <diameter/s6d/AuthenticationInformation.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::s6d;

extern string sessIdString;
extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the  AuthenticationInformation to the
 *      diameter stack. Create the  AuthenticationInformation object,
 *      populate the AVPs and send the message to the stack.
 *
 *  Input Parameters:
 *      Update choice.
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
int SendS6DAuthenticationInformationRequest()
{
    // [1]. Create an instance of AuthenticationInformationRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::s6d::AuthenticationInformationRequest AIReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(S6D_INTERFACE_APP_ID, sIdx, sessIdString);
    AIReq.setSessionId(diameter::base::SessionId(sessIdString));

    AIReq.setSessionIndex(sIdx);

    // [2.1.2.x] Required AVPs
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
    AIReq.setAuthSessionState(authSessionState);


    // [2.1.3] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    AIReq.setOriginHost(originHost);

    // [2.1.4] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    AIReq.setOriginRealm(originRealm);

    // [2.1.5] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    AIReq.setDestinationRealm(destinationRealm);

    // [2.1.6] Set the User-Name AVP.
    // [2.2.3]Populate parameter "User-Name"
    // The data type of User-Name is UTF8String.
    // This AVP contains the User-Name.
    // The AVP Code of User-Name is 1.
    UserName userName("sip:user@3gppnetwork.com");
    AIReq.setUserName(userName);

   // [2.1.7] Set Requested-EUTRAN-Authentication-Infos AVP
   // The Requested-EUTRAN-Authentication-Infos AVP code is 152.
    RequestedEUTRANAuthenticationInfo REAInfo; 
    NumberOfRequestedVectors nofreqvect1(10);
    REAInfo.setNumberOfRequestedVectors(nofreqvect1);
    ImmediateResponsePreferred	imrespref1(2);
    REAInfo.setImmediateResponsePreferred(imrespref1);
    ReSynchronizationInfo rsinfo1(" Resync info octetString");
    REAInfo.setReSynchronizationInfo(rsinfo1);
 
    AIReq.setRequestedEUTRANAuthenticationInfo(REAInfo);
  
   // [2.1.8] Set Requested-UTRAN-Authentication-Infos AVP
   // The Requested-EUTRAN-Authentication-Infos AVP code is 173.
    RequestedUTRANGERANAuthenticationInfo RUGAInfo;
    NumberOfRequestedVectors nofreqvect2(11);
    RUGAInfo.setNumberOfRequestedVectors(nofreqvect2);
    ImmediateResponsePreferred  imrespref2(3);
    RUGAInfo.setImmediateResponsePreferred(imrespref2);
    ReSynchronizationInfo rsinfo2(" Resync info");
    RUGAInfo.setReSynchronizationInfo(rsinfo2);

    AIReq.setRequestedUTRANGERANAuthenticationInfo(RUGAInfo);

   //[2.1.10] Set Visited-PLMN-Id AVP.
    VisitedPLMNId  visPLMNid("visitedPLMNID123");
    AIReq.setVisitedPLMNId(visPLMNid);
		 
   //[2.1.11] Set Requesting-Node-Type AVP 
   //Requesting-Node-Type AVP is of type Enumerated with code 156.
   //  MME (0), SGSN (1), MME/SGSN (2).
    //RequestingNodeType rntype(RequestingNodeType::SGSN);
    //AIReq.setRequestingNodeType(rntype);

    // Application should not set this AVP.
    // AIReq.addProxyInfo(diameter::base::ProxyInfo(...));
    // AIReq.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values

    if (appMode == UNIT_TEST)
    cout<<AIReq;

    // Send object to stack.
    SendDiaAppMsg(AIReq, sIdx);

    S6DStats::GetS6DStats()->UpdateSendStats(AIReq.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends the Answer to the AuthenticationInformation request
 *      made by the diameter stack. Create the AuthenticationInformationAnswer
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
int SendS6DAuthenticationInformationAnswer(const CommandImpl * impl)
{
    // 1. Create an instance of AuthenticationInformationAnswer class
    // The Update-Data-Answer command is sent by a server
    // in response to the Update-Data-Request command with
    // Command-Code = 306 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::s6d::AuthenticationInformationAnswer AIAns;

    // Create an instance of AuthenticationInformationRequest class to get host and
    // session details
    AuthenticationInformationRequest AIreq(*impl);

    // Get AVP values from requested message
    const SessionId &sid1 = AIreq.getSessionId();
    const OriginHost &oh1 = AIreq.getOriginHost();
    const OriginRealm &or1 = AIreq.getOriginRealm();
    const AuthSessionState &authSessState = AIreq.getAuthSessionState();

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
    AIAns.setSessionId(sid1);
    AIAns.setSessionIndex(AIreq.getSessionIndex());    
 
    // [2.1.2.x] Required AVPs
    AIAns.setAuthSessionState(authSessState); 

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
    AIAns.setResultCode(resultCode);

    // Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of Experimental-Result AVP is 297.
    // The data type of Experimental-Result AVP is Grouped Type.
    ExperimentalResult experimentalResult;

    // Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    VendorId vendorId1(VENDOR_ID);
    experimentalResult.setVendorId(vendorId1);

    // Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    ExperimentalResultCode experimentalResultCode(2001u);
    experimentalResult.setExperimentalResultCode(experimentalResultCode);

    // [2.2] Set the Experimental-Result AVP.

    // This AVP is required incase of Result-Code AVP is missing.
    AIAns.setExperimentalResult(experimentalResult);

    // [2.1.2] Set the Origin-Host AVP.
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
    AIAns.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    AIAns.setOriginRealm(originRealm);

    // The data type of Proxy-Info is Grouped Type.
    // This AVP should not be set by Application.
    // AIAns.setProxyInfo(diameter::base::ProxyInfo(...));

    // Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    // This AVP should not be set by Application.
    // AIAns.setRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values

    if (appMode == UNIT_TEST)
    cout<<AIAns;

    // Send Object to stack.
    SendDiaAppMsg(AIAns, sIdx);

    // Update stats.
    S6DStats::GetS6DStats()->UpdateSendStats(AIAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}


