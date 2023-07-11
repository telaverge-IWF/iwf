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
 ****************************************************************************
 * LOG: $Log: InsertSubscriberDataTest.cpp,v $
 * LOG: Revision 1.8  2009/06/10 12:17:39  sureshj
 * LOG: Support for march release(3GPP TS 29.272 V8.2.0 (2009-03)) app changes.
 * LOG:
 * LOG: Revision 1.7  2009/04/17 05:09:02  sureshj
 * LOG: reverted back changes to support TS29272v8.2.0
 * LOG:
 * LOG: Revision 1.6  2009/04/08 05:49:32  sureshj
 * LOG: Demo changes to support 3GPP TS 29272 v8.2.0.
 * LOG:
 * LOG: Revision 1.5  2009/03/04 12:44:06  sureshj
 * LOG: Demo changes for Motorola specific part changes.TS 29272 v8.1.0.
 * LOG:
 * LOG: Revision 1.4  2008/12/18 10:38:48  sureshj
 * LOG: Access-Restriction-Data avp added to Data avp.
 * LOG:
 * LOG: Revision 1.3  2008/11/25 09:10:27  sureshj
 * LOG: iissueID:none
 * LOG: FeatureID:none
 * LOG: Description: support for C4-083420 (motorola).
 * LOG:
 * LOG: Revision 1.2  2008/11/12 09:08:09  sureshj
 * LOG: New command IDR/IDA added for demo.
 * LOG: 
 * ID: $Id: InsertSubscriberDataTest.cpp,v 1.8 2009/06/10 12:17:39 sureshj Exp $ 								    	
 ****************************************************************************/
#ident "$Id: InsertSubscriberDataTest.cpp,v 1.8 2009/06/10 12:17:39 sureshj Exp $"

#include <app.h>
#include <s6a_defines.h>
#include <s6a_stats.h>
#include <diameter/s6a/InsertSubscriberData.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::s6a;

extern string sessIdString;
extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the  InsertSubscriberData to the
 *      diameter stack. Create the  InsertSubscriberData object,
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
int SendS6AInsertSubDataRequest()
{
    // [1]. Create an instance of InsertSubscriberDataRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::s6a::InsertSubscriberDataRequest IDReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(S6A_INTERFACE_APP_ID, sIdx, sessIdString);
    IDReq.setSessionId(diameter::base::SessionId(sessIdString));

    IDReq.setSessionIndex(sIdx);

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
    AuthSessionState authSessionState(AuthSessionState::NO_STATE_MAINTAINED);
    IDReq.setAuthSessionState(authSessionState);

    // [2.1.2.3] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    IDReq.setOriginHost(originHost);

    // [2.1.2.4] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    IDReq.setOriginRealm(originRealm);


    // [2.1.2.5] Set the Destination-Host AVP.
    // [2.2.2] Populate optional paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    // This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost DestinationHost(GetDestinationHost());
    IDReq.setDestinationHost(DestinationHost);

    // [2.1.2.6] Set the Desti
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    IDReq.setDestinationRealm(destinationRealm);

    // [2.1.2.7] Set the User-Name AVP.
    // Set the User-Name AVP.
    // The data type of User-Name is UTF8String.
    // This AVP contains the User-Name.
    // The AVP Code of User-Name is 1.
    UserName userName("sip:user@3gppnetwork.com");
    IDReq.setUserName(userName);

    // Set Subscription Data AVP. 
    //add avp MSISDN
    MSISDN msisdn("InsertMSISDN");
    SubscriberStatus subStatus(SubscriberStatus::SERVICEGRANTED); 
    SubscriptionData  sub;
    // add avp Access-Restriction-Data 
    //contains a bit mask where each bit when set to 1 
    //indicates a restriction.
    AccessRestrictionData ard(10);
    sub.setAccessRestrictionData(ard);
    sub.setMSISDN(msisdn);  
    sub.setSubscriberStatus(subStatus);  
    
    // APN-Configuration-Profile
    //APNConfigurationProfile  apnConProfile;
    //ContextIdentifier contxId(123);
    //apnConProfile.setContextIdentifier(contxId);
    //AllAPNConfigurationsIncludedIndicator  allAPNConfIncluInd(
    //  AllAPNConfigurationsIncludedIndicator::All_APN_CONFIGURATIONS_INCLUDED);
    //apnConProfile.setAllAPNConfigurationsIncludedIndicator(allAPNConfIncluInd);
 
    //APNConfiguration apnConf;
    //apnConf.setContextIdentifier(contxId);
    //PDNType pdnType(PDNType::IPv4);
    //apnConf.setPDNType(pdnType);
    //CalledStationId   calStationId("CalledStationID");
    //apnConf.setCalledStationId(calStationId);

     
    AMBR ambr;
    MaxRequestedBandwidthUL maxReqBwUL(11);
    ambr.setMaxRequestedBandwidthUL(maxReqBwUL);
    MaxRequestedBandwidthDL maxReqBwDL(22);
    ambr.setMaxRequestedBandwidthDL(maxReqBwDL);
    //apnConf.setAMBR(ambr);
 
    //apnConProfile.addAPNConfiguration(apnConf);
 
    //sub.setAPNConfigurationProfile(apnConProfile);

    IDReq.setSubscriptionData(sub);
    
     
		   
    // Application should not set this AVP.
    // IDReq.addProxyInfo(diameter::base::ProxyInfo(...));
    // IDReq.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values

    if (appMode == UNIT_TEST)
    cout<<IDReq;

    // Send object to stack.
    SendDiaAppMsg(IDReq, sIdx);

    S6AStats::GetS6AStats()->UpdateSendStats(IDReq.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends the Answer to the InsertSubscriberData request
 *      made by the diameter stack. Create the InsertSubscriberDataAnswer
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
int SendS6AInsertSubDataAnswer(const CommandImpl * impl)
{
    // 1. Create an instance of InsertSubDataAnswer class
    // The Update-Data-Answer command is sent by a server
    // in response to the Update-Data-Request command with
    // Command-Code = 666 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::s6a::InsertSubscriberDataAnswer IDAns;

    // Create an instance of InsertSubDataRequest class to get host and
    // session details
    InsertSubscriberDataRequest IDreq(*impl);

    // Get AVP values from requested message
    const SessionId &sid1 = IDreq.getSessionId();
    const OriginHost &oh1 = IDreq.getOriginHost();
    const OriginRealm &or1 = IDreq.getOriginRealm();
    const AuthSessionState &authSessState = IDreq.getAuthSessionState();

    // 2. Create the instances of the classes describing the various
    // AVPs' present in an InsertSubDataAnswer command and
    // pass them by value to the corresponding data members set
    // methods of the InsertSubDataAnswer object created
    // in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    IDAns.setSessionId(sid1);
    IDAns.setSessionIndex(IDreq.getSessionIndex());    
 
    // [2.1.2.x] Required AVPs
    IDAns.setAuthSessionState(authSessState);
 
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
    IDAns.setResultCode(resultCode);

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
    IDAns.setExperimentalResult(experimentalResult);

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
    IDAns.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    IDAns.setOriginRealm(originRealm);

    // The data type of Proxy-Info is Grouped Type.
    // This AVP should not be set by Application.
    // IDAns.setProxyInfo(diameter::base::ProxyInfo(...));

    // Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    // This AVP should not be set by Application.
    // IDAns.setRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values

    if (appMode == UNIT_TEST)
    cout<<IDAns;

    // Send Object to stack.
    SendDiaAppMsg(IDAns, sIdx);

    // Update stats.
    S6AStats::GetS6AStats()->UpdateSendStats(IDAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}


