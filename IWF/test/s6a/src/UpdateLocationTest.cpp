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
 * LOG: $Log: UpdateLocationTest.cpp,v $
 * LOG: Revision 1.1.2.2  2013/03/19 10:04:53  jvikas
 * LOG: Fixes to Display Diameter Message Details.
 * LOG:
 * LOG: Revision 1.1.2.1  2013/02/08 10:52:30  jvikas
 * LOG: Diameter Simulator Changes for IWF
 * LOG:
 * LOG: Revision 1.1.2.1  2013/01/28 11:31:39  pramana
 * LOG: Initial check-in for simulator code
 * LOG:
 * LOG: Revision 1.1.2.1.2.3  2012/09/06 11:23:51  jvikas
 * LOG: DTF Branch merge to B-DRE-0212-00 - Sept6.
 * LOG:
 * LOG: Revision 1.1.2.1.2.2  2012/08/18 13:15:21  pramana
 * LOG: Checkin after changing the auth state maintained to no state maintained
 * LOG:
 * LOG: Revision 1.1.2.1.2.1.2.1  2012/08/30 11:50:43  jvikas
 * LOG: Added All AVPs for ULR and ULA for Release10
 * LOG:
 * LOG: Revision 1.1.2.1.2.1  2012/08/07 01:44:59  ncshivakumar
 * LOG: Updated VisitedPLMN value
 * LOG:
 * LOG: Revision 1.1.2.1  2012/07/09 08:53:44  pramana
 * LOG: New test code added for S6a, S13 for Release 10 support (Bug 48).
 * LOG:
 * LOG: Revision 1.4  2010/09/07 12:26:21  vkumara
 * LOG: Updated with V 8.5.0
 * LOG:
 * LOG: Revision 1.3  2009/03/04 12:45:13  sureshj
 * LOG: Demo changes for Motorola specific part changes.TS 29272 v8.1.0.
 * LOG:
 * LOG: Revision 1.2  2008/11/12 05:38:32  sureshj
 * LOG: Updates for supporting v8.0.0. part of release 3.1.1.
 * LOG:
 * LOG: Revision 1.1  2008/08/19 06:09:24  sureshj
 * LOG: Initial commit.
 * LOG:
 * ID: $Id: UpdateLocationTest.cpp,v 1.1.2.2 2013/03/19 10:04:53 jvikas Exp $
 ***************************************************************************/

#include <app.h>
#include <s6a_defines.h>
#include <s6a_stats.h>
#include <diameter/s6a_r10/UpdateLocation.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::s6a_r10;

extern ApplicationStats appStats;
string sessIdString;
ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the  UpdateLocationRequest to the
 *      diameter stack. Create the  UpdateLocationRequest object,
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
int SendS6AUpdateLocationRequest()
{
    // [1]. Create an instance of UpdateLocationRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::s6a_r10::UpdateLocationRequest ulReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(S6A_INTERFACE_APP_ID, sIdx, sessIdString);
    ulReq.setSessionId(diameter::base::SessionId(sessIdString));

    ulReq.setSessionIndex(sIdx);

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
    //Previously: AuthSessionState authSessionState(AuthSessionState::STATE_MAINTAINED);
    AuthSessionState authSessionState(AuthSessionState::NO_STATE_MAINTAINED);
    ulReq.setAuthSessionState(authSessionState);

    // [2.1.2.2] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
     OriginHost originHost(GetOriginHost());
     ulReq.setOriginHost(originHost);

    // [2.1.2.3] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    ulReq.setOriginRealm(originRealm);

    // [2.1.2.4] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    ulReq.setDestinationRealm(destinationRealm);

    // [2.1.2.5] Set the User-Name AVP.
    // The User-Name AVP (AVP Code 1) [RADIUS] is of type UTF8String,
    // which contains the User-Name, in a format consistent with the NAI
    // specification [NAI]. The AVP Code of User-Name AVP is 1.
    // The data type of Usere-Name AVP is UTF8String.
    //UserName userName("sip:user@3gppnetwork.com");
    //ulReq.setUserName(userName);

    static long long imsi_number=singlton::arg[0];
        char temp[100]={'\0'},*end;
        char s[100]="@3gppntework.org";
        //cout<<"IMSI BASED ROUTING"<<endl;
        sprintf(temp,"%lld%s",imsi_number,s);
        UserName userName((const char *)temp);
        ulReq.setUserName(userName);
        if(imsi_number!=singlton::arg[1])
                imsi_number++;
        else
                imsi_number=singlton::arg[0];
        char imsi_to_print[100] = {0};
        sprintf(imsi_to_print, "Sent ULR with IMSI: %s", userName.value().c_str());
	int recent_msg_idx = appStats.recent_msg_idx++ % MAX_MSGS_TO_DISPLAY;
	appStats.last_processed_msgs[recent_msg_idx] = imsi_to_print;
	appStats.recent_msg_idx = recent_msg_idx+1;


   // [2.1.2.6] Set the ULR-Flags AVP.
    ULRFlags ulrflags(10);
    ulReq.setULRFlags(ulrflags);

   // [2.1.2.7] Set  Visited-PLMN-Id
    //VisitedPLMNId  visPLMNid("visitedPLMNID123");
    VisitedPLMNId  visPLMNid("31026");
    ulReq.setVisitedPLMNId(visPLMNid);

    imsi_to_print[100] = {0};
    sprintf(imsi_to_print, "Visited-PLMN-ID AVP: %s", visPLMNid.value().c_str());
	recent_msg_idx = appStats.recent_msg_idx++ % MAX_MSGS_TO_DISPLAY;
	appStats.last_processed_msgs[recent_msg_idx] = imsi_to_print;
	appStats.recent_msg_idx = recent_msg_idx+1;

   // [2.1.2.8] Set the RAT-Type AVP
   // The RAT-Type AVP is of type Enumerated and is used to identify the
   // radio access technology that is serving the UE.
    RATType  ratType(RATType::HSPA_EVOLUTION);
    ulReq.setRATType(ratType);

    imsi_to_print[100] = {0};
    sprintf(imsi_to_print, "RAT-Type AVP : %d", RATType::HSPA_EVOLUTION);
	recent_msg_idx = appStats.recent_msg_idx++ % MAX_MSGS_TO_DISPLAY;
	appStats.last_processed_msgs[recent_msg_idx] = imsi_to_print;
	appStats.recent_msg_idx = recent_msg_idx+1;

    // [2.1.3.x] set Optional AVPs.
    // [2.1.3.1] Set the Destination-Host AVP.
    // The Destination-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Destination-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
#if 0
    DestinationHost DestinationHost(GetDestinationHost());
    ulReq.setDestinationHost(DestinationHost);
#endif

   // [2.1.3.2] Set the UE SRVCC Capability
   UESRVCCCapability ueSrvccCapability(UESRVCCCapability::UE_SRVCC_NOT_SUPPORTED);
   ulReq.setUESRVCCCapability(ueSrvccCapability);

   // [2.1.3.3] Set the Homogeneous Support of IMS Voice Over PS Sessions
   HomogeneousSupportofIMSVoiceOverPSSessions homogeneousSuppOfIMSVoPSSessions(HomogeneousSupportofIMSVoiceOverPSSessions::NOT_SUPPORTED);
   ulReq.setHomogeneousSupportofIMSVoiceOverPSSessions(homogeneousSuppOfIMSVoPSSessions);

   diameter::Address addr((diameter::Address::Family)1, "5.5.5.5");
   diameter::s6a_r10::GMLCAddress glmcAddr(addr);
   ulReq.setGMLCAddress(glmcAddr);

   ActiveAPN activeApn;
   diameter::s6a_r10::ContextIdentifier cid(10);
   activeApn.setContextIdentifier(cid);

   diameter::s6a_r10::ServiceSelection serviceSelection1("Service_Selection1");
   activeApn.setServiceSelection(const_cast<diameter::s6a_r10::ServiceSelection&>(serviceSelection1));

   diameter::s6a_r10::MIP6AgentInfo mip6AgentInfo;
   diameter::Address addr1((diameter::Address::Family)1, "1.1.1.1");
   diameter::s6a_r10::MIPHomeAgentAddress mipHAgentAddr(addr1);
   mip6AgentInfo.addMIPHomeAgentAddress(mipHAgentAddr);

   diameter::s6a_r10::MIPHomeAgentHost mipHAHost;
   diameter::base::DestinationRealm destRealm("intellinet.com");
   diameter::base::DestinationHost destHost("serverA");
   mipHAHost.setDestinationRealm(destRealm);
   mipHAHost.setDestinationHost(destHost);
   mip6AgentInfo.setMIPHomeAgentHost(mipHAHost);

   diameter::s6a_r10::MIP6HomeLinkPrefix mip6HLPrefix("MIP6_Home_Link_Prefix");
   mip6AgentInfo.setMIP6HomeLinkPrefix(mip6HLPrefix);

   activeApn.setMIP6AgentInfo(mip6AgentInfo);

   diameter::s6a_r10::VisitedNetworkIdentifier visitedNetId("Visited_Network_Identifier");
   activeApn.setVisitedNetworkIdentifier(visitedNetId);

   diameter::s6a_r10::SpecificAPNInfo specificAPNInfo;
   specificAPNInfo.setServiceSelection(const_cast<diameter::s6a_r10::ServiceSelection&>(serviceSelection1));
   specificAPNInfo.setMIP6AgentInfo(mip6AgentInfo);
   specificAPNInfo.setVisitedNetworkIdentifier(visitedNetId);
   activeApn.addSpecificAPNInfo(specificAPNInfo);

   ulReq.addActiveAPN(activeApn);

    //VendorSpecificApplicationId vendorSpecificApplicationId();
    // [2.2] Populate required Mandatories.
    // [2.2.1] Populate required parameter "Vendor-Specific-Application-Id".
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP identifies the supported application identifiers
    // of a Diameter node.
    // The AVP Code of Vendor-Specific-Application-Id is 631.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.2.1.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(10415);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // [2.2.1.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication
    // and Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AuthApplicationId authApplicationId(S6A_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // [2.2.1.3] Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting
    // portion of an application.
    // The AVP Code of Acct-Application-Id is 259.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    ulReq.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

#if 0
    if (appMode == UNIT_TEST)
    cout<<ulReq;
#endif

    // Send object to stack.
    SendDiaAppMsg(ulReq, sIdx);

    S6AStats::GetS6AStats()->UpdateSendStats(ulReq.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends the Answer to the UpdateLocation request
 *      made by the diameter stack. Create the UpdateLocationAnswer
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
int SendS6AUpdateLocationAnswer(const CommandImpl * impl)
{
    // 1. Create an instance of UpdateLocationAnswer class
    // The Update-Data-Answer command is sent by a server
    // in response to the Update-Data-Request command with
    // Command-Code = 306 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::s6a_r10::UpdateLocationAnswer ulAns;

    // Create an instance of UpdateLocationRequest class to get host and
    // session details
    UpdateLocationRequest ulreq(*impl);

    // Get AVP values from requested message
    const SessionId &sid1 = ulreq.getSessionId();
    const OriginHost &oh1 = ulreq.getOriginHost();
    const OriginRealm &or1 = ulreq.getOriginRealm();
    const AuthSessionState &authSessState = ulreq.getAuthSessionState();

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
    ulAns.setSessionId(sid1);
    ulAns.setSessionIndex(ulreq.getSessionIndex());

    // [2.1.2.x] Required AVPs
    ulAns.setAuthSessionState(authSessState);

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
    ulAns.setResultCode(resultCode);

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
    ulAns.setExperimentalResult(experimentalResult);

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
    //ulAns.setAuthSessionState(authSessState);

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
    ulAns.setOriginHost(originHost);

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    ulAns.setOriginRealm(originRealm);

    // [2.1] Set the ULA-Flags AVP.
    // The AVP Code of ULA-Flags AVP is .
    // The data type of ULA-Flagse AVP is Unsigned32.
     ULAFlags ulaflag(11);
     ulAns.setULAFlags(ulaflag);

    // The data type of Proxy-Info is Grouped Type.
    // This AVP should not be set by Application.
    // ulAns.setProxyInfo(diameter::base::ProxyInfo(...));

    // Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    // This AVP should not be set by Application.
    // ulAns.setRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values

    //VendorSpecificApplicationId vendorSpecificApplicationId();
    // [2.2] Populate required Mandatories.
    // [2.2.1] Populate required parameter "Vendor-Specific-Application-Id".
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP identifies the supported application identifiers
    // of a Diameter node.
    // The AVP Code of Vendor-Specific-Application-Id is 631.
    VendorSpecificApplicationId vendorSpecificApplicationId1;

    // [2.2.1.1] Populate required parameter "Vendor-Id".
    // Set the Vendor-Id AVP.
    // The data type of Vendor-Id is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes
    // may be sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates
    // that this field is ignored.
    // The AVP Code of Vendor-Id is 266.
    VendorId vendorId(10415);
    vendorSpecificApplicationId1.addVendorId(vendorId);

    // [2.2.1.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication
    // and Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AuthApplicationId authApplicationId(S6A_INTERFACE_APP_ID);
    vendorSpecificApplicationId1.setAuthApplicationId(authApplicationId);

    // [2.2.1.3] Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting
    // portion of an application.
    // The AVP Code of Acct-Application-Id is 259.
    // AcctApplicationId acctApplicationId(2);
    // vendorSpecificApplicationId1.setAcctApplicationId(acctApplicationId);

    ulAns.setVendorSpecificApplicationId(vendorSpecificApplicationId1);

    /*New AVP*/
    const ErrorDiagnostic errorDiagnostic(0);
    ulAns.setErrorDiagnostic(errorDiagnostic);


    /*Modifying existing Grouped AVP*/
    SubscriptionData subData;
    diameter::s6a_r10::ICSIndicator icsIndicator((diameter::s6a_r10::ICSIndicator::Value)0);
    subData.setICSIndicator(icsIndicator);

    diameter::s6a_r10::SubscribedPeriodicRAUTAUTimer subscribedPeriodicRAUTAUTimer(1);
    subData.setSubscribedPeriodicRAUTAUTimer(subscribedPeriodicRAUTAUTimer);

    diameter::s6a_r10::MPSPriority mpsPriority(10);
    subData.setMPSPriority(mpsPriority);

    diameter::s6a_r10::VPLMNLIPAAllowed vplmnLipaAllowed((diameter::s6a_r10::VPLMNLIPAAllowed::Value)0);
    subData.setVPLMNLIPAAllowed(vplmnLipaAllowed);

    diameter::s6a_r10::RelayNodeIndicator relayNodeInd((diameter::s6a_r10::RelayNodeIndicator::Value)0);
    subData.setRelayNodeIndicator(relayNodeInd);

    diameter::s6a_r10::MDTUserConsent MDTuserCont((diameter::s6a_r10::MDTUserConsent::Value)0);
    subData.setMDTUserConsent(MDTuserCont);


    /*New Grouped AVP Added in ULA*/
    diameter::s6a_r10::APNConfigurationProfile apnConfigProf;
    diameter::s6a_r10::APNConfiguration apnConfig;

    //Start of Sub-Grouped
    diameter::s6a_r10::MIP6AgentInfo mip6AgentInfo;
    diameter::Address addr1((diameter::Address::Family)1, "1.1.1.1");
    diameter::s6a_r10::MIPHomeAgentAddress mipHAgentAddr(addr1);
    mip6AgentInfo.addMIPHomeAgentAddress(mipHAgentAddr);

    diameter::s6a_r10::MIPHomeAgentHost mipHAHost;
    diameter::base::DestinationRealm destRealm("intellinet.com");
    diameter::base::DestinationHost destHost("serverA");
    mipHAHost.setDestinationRealm(destRealm);
    mipHAHost.setDestinationHost(destHost);
    mip6AgentInfo.setMIPHomeAgentHost(mipHAHost);

    diameter::s6a_r10::MIP6HomeLinkPrefix mip6HLPrefix("MIP6_Home_Link_Prefix");
    mip6AgentInfo.setMIP6HomeLinkPrefix(mip6HLPrefix);

    apnConfig.setMIP6AgentInfo(mip6AgentInfo);

    diameter::s6a_r10::ServiceSelection serviceSelection1("Service_Selection1");
    apnConfig.setServiceSelection(const_cast<diameter::s6a_r10::ServiceSelection&>(serviceSelection1));
    diameter::s6a_r10::ContextIdentifier cid(10);
    diameter::s6a_r10::PDNType pdnType((diameter::s6a_r10::PDNType::Value)0);
    apnConfig.setPDNType(pdnType);
    apnConfig.setContextIdentifier(cid);

    diameter::s6a_r10::APNOIReplacement apnOIReplacement("APN_OI_Replacement");
    apnConfig.setAPNOIReplacement(apnOIReplacement);

    diameter::s6a_r10::SIPTOPermission sipToPermission((diameter::s6a_r10::SIPTOPermission::Value)0);
    apnConfig.setSIPTOPermission(sipToPermission);

    diameter::s6a_r10::LIPAPermission lipaPermission((diameter::s6a_r10::LIPAPermission::Value)0);
    apnConfig.setLIPAPermission(lipaPermission);

    diameter::s6a_r10::VisitedNetworkIdentifier visitedNetId("Visited_Network_Identifier");
    apnConfig.setVisitedNetworkIdentifier(visitedNetId);

    //Start of sub-grouped AVP Specific-APN-Info
    diameter::s6a_r10::SpecificAPNInfo specificAPNInfo;

    //Start of Sub-Grouped
    diameter::s6a_r10::MIP6AgentInfo mip6AgentInfo1;
    diameter::Address addr2((diameter::Address::Family)1, "1.1.1.1");
    diameter::s6a_r10::MIPHomeAgentAddress mipHAgentAddr1(addr2);
    mip6AgentInfo.addMIPHomeAgentAddress(mipHAgentAddr1);

    diameter::s6a_r10::MIPHomeAgentHost mipHAHost1;
    diameter::base::DestinationRealm destRealm1("diametriq.com");
    diameter::base::DestinationHost destHost1("mme");
    mipHAHost1.setDestinationRealm(destRealm1);
    mipHAHost1.setDestinationHost(destHost1);
    mip6AgentInfo1.setMIPHomeAgentHost(mipHAHost1);

    diameter::s6a_r10::MIP6HomeLinkPrefix mip6HLPrefix1("MIP6_Home_Link_Prefix");
    mip6AgentInfo1.setMIP6HomeLinkPrefix(mip6HLPrefix1);

    specificAPNInfo.setMIP6AgentInfo(mip6AgentInfo1);

    diameter::s6a_r10::ServiceSelection serviceSelection2("Service_Selection1");
    specificAPNInfo.setServiceSelection(const_cast<diameter::s6a_r10::ServiceSelection&>(serviceSelection1));

    diameter::s6a_r10::VisitedNetworkIdentifier visitedNetId1("Visited_Network_Identifier");
    specificAPNInfo.setVisitedNetworkIdentifier(visitedNetId1);
    apnConfig.addSpecificAPNInfo(specificAPNInfo);
    //End of Sub-Grouped AVP Specific-APN-Info
    //
    apnConfigProf.addAPNConfiguration(const_cast<diameter::s6a_r10::APNConfiguration&>(apnConfig));
     apnConfigProf.setContextIdentifier(cid);

    diameter::s6a_r10::AllAPNConfigurationsIncludedIndicator apnConfigInd((diameter::s6a_r10::AllAPNConfigurationsIncludedIndicator::Value)0);
    apnConfigProf.setAllAPNConfigurationsIncludedIndicator(apnConfigInd);
    subData.setAPNConfigurationProfile(apnConfigProf);
    //End of Sub-Grouped AVP APN-Configuration-Profile
    //
    //Start of sub-grouped AVP Trace-Data
    diameter::s6a_r10::TraceData traceData;
    diameter::s6a_r10::MDTConfiguration mdtConfig;
    	diameter::s6a_r10::JobType jobType((diameter::s6a_r10::JobType::Value)0);
	mdtConfig.setJobType(jobType);
	diameter::s6a_r10::AreaScope areaScope;
	diameter::s6a_r10::CellGlobalIdentity cellGlobalId("Cell_Global_Identity");
	areaScope.addCellGlobalIdentity(cellGlobalId);
	diameter::s6a_r10::EUTRANCellGlobalIdentity eutranGlobalId("E_UTRAN_Cell_Global_Identity");
	areaScope.addEUTRANCellGlobalIdentity(eutranGlobalId);
     	diameter::s6a_r10::RoutingAreaIdentity routingAreaId("Routing_Area_Identity");
   	areaScope.addRoutingAreaIdentity(routingAreaId);
	diameter::s6a_r10::LocationAreaIdentity locAreaId("Location_Area_Identity");
        areaScope.addLocationAreaIdentity(locAreaId);
  	diameter::s6a_r10::TrackingAreaIdentity trackingAreaId("Tracking_Area_Identity");
	areaScope.addTrackingAreaIdentity(trackingAreaId);

   mdtConfig.setAreaScope(areaScope);
	diameter::s6a_r10::ListOfMeasurements listofMeasurements(10);
	mdtConfig.setListOfMeasurements(listofMeasurements);
	diameter::s6a_r10::ReportingTrigger reportingTrigger(10);
	mdtConfig.setReportingTrigger(reportingTrigger);
	diameter::s6a_r10::ReportInterval reportInt((diameter::s6a_r10::ReportInterval::Value)0);
 	mdtConfig.setReportInterval(reportInt);
	diameter::s6a_r10::ReportAmount reportAmt((diameter::s6a_r10::ReportAmount::Value)0);
	mdtConfig.setReportAmount(reportAmt);
 	diameter::s6a_r10::EventThresholdRSRP eventThrRSRP(10);
	mdtConfig.setEventThresholdRSRP(eventThrRSRP);
	diameter::s6a_r10::EventThresholdRSRQ eventThrRSRQ(10);
	mdtConfig.setEventThresholdRSRQ(eventThrRSRQ);
	diameter::s6a_r10::LoggingInterval logInterval((diameter::s6a_r10::LoggingInterval::Value)0);
	mdtConfig.setLoggingInterval(logInterval);
	diameter::s6a_r10::LoggingDuration logDuration((diameter::s6a_r10::LoggingDuration::Value)0);
	mdtConfig.setLoggingDuration(logDuration);

   traceData.setMDTConfiguration(mdtConfig);
   //End of sub-grouped AVP MDT-Configuration
   //
   diameter::s6a_r10::TraceReference traceRef("");
                traceData.setTraceReference(traceRef);
                diameter::s6a_r10::TraceDepth trDepth((diameter::s6a_r10::TraceDepth::Value)0);
                traceData.setTraceDepth(trDepth);
                diameter::s6a_r10::TraceNETypeList tNetTList("");
                traceData.setTraceNETypeList(tNetTList);
                diameter::s6a_r10::TraceEventList tEvtList("");
                traceData.setTraceEventList(tEvtList);
                //diameter::Address addr1((diameter::Address::Family)0,"0");
                diameter::s6a_r10::TraceCollectionEntity tcEntity(addr1);
                traceData.setTraceCollectionEntity(tcEntity);

   subData.setTraceData(traceData);
   //End of sub-grouped AVP Trace-Data

   //Start of sub-grouped AVP GPRS-Subscription-Data
   diameter::s6a_r10::GPRSSubscriptionData gprsSubData;

   //Start of sub-grouped AVP PDP-Context
   diameter::s6a_r10::PDPContext pdpContext;
	diameter::s6a_r10::ExtPDPType extPDPType("Ext_PDP_Type");
	pdpContext.setExtPDPType(extPDPType);
        //const diameter::AddressImpl& addrImpl = 1.1.1.1;
	diameter::Address addr((diameter::Address::Family)1, "1.1.1.1");
	//diameter::Address addr(addrImpl);
	diameter::s6a_r10::ExtPDPAddress extPDPAddr(addr);
        pdpContext.setExtPDPAddress(extPDPAddr);

	diameter::s6a_r10::AMBR ambr;
	diameter::s6a_r10::MaxRequestedBandwidthUL maxBwUL(1);
	diameter::s6a_r10::MaxRequestedBandwidthDL maxBwDL(1);
	ambr.setMaxRequestedBandwidthUL(maxBwUL);
	ambr.setMaxRequestedBandwidthDL(maxBwDL);
        pdpContext.setAMBR(ambr);
	diameter::s6a_r10::SIPTOPermission sipToPermission1((diameter::s6a_r10::SIPTOPermission::Value)0);
	pdpContext.setSIPTOPermission(sipToPermission1);
	diameter::s6a_r10::LIPAPermission lipaPermission1((diameter::s6a_r10::LIPAPermission::Value)0);
	pdpContext.setLIPAPermission(lipaPermission1);

        //diameter::s6a_r10::ContextIdentifier cid(10);
        pdpContext.setContextIdentifier(cid);
        diameter::s6a_r10::PDPType pdpType("");
        pdpContext.setPDPType(pdpType);
        diameter::s6a_r10::QoSSubscribed qos("");
        pdpContext.setQoSSubscribed(qos);
        diameter::s6a_r10::ServiceSelection serviceSel("");
        pdpContext.setServiceSelection(serviceSel);

   gprsSubData.addPDPContext(pdpContext);

   diameter::s6a_r10::CompleteDataListIncludedIndicator comDLInd((diameter::s6a_r10::CompleteDataListIncludedIndicator::Value)0);
                gprsSubData.setCompleteDataListIncludedIndicator(comDLInd);

   subData.setGPRSSubscriptionData(gprsSubData);

   //Start of sub-grouped AVP CSG-Subscription-Data
   diameter::s6a_r10::CSGSubscriptionData csgSubData;
	diameter::s6a_r10::ServiceSelection serviceSelection("Service_Selection");

   diameter::s6a_r10::CSGId csgId(1);
                csgSubData.setCSGId(csgId);
   subData.addCSGSubscriptionData(csgSubData);
   //End of sub-grouped AVP CSG-Subscription-Data
   ulAns.setSubscriptionData(const_cast<SubscriptionData&>(subData));

#if 0
    if (appMode == UNIT_TEST)
    cout<<ulAns;
#endif

    // Send Object to stack.
    SendDiaAppMsg(ulAns, sIdx);

    // Update stats.
    S6AStats::GetS6AStats()->UpdateSendStats(ulAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}


