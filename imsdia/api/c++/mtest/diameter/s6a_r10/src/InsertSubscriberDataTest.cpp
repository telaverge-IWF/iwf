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
 * LOG: Revision 1.1.6.2  2014/02/12 08:06:13  millayaraja
 * LOG:  added testapp s6a_r10 for IWF
 * LOG:
 * LOG: Revision 1.1.2.4.2.1  2013/09/20 13:07:37  jkchaitanya
 * LOG: changes for the bug 1674, supporting IDA-Flags and supported features in s6a json
 * LOG:
 * LOG: Revision 1.1.2.4  2013/05/22 15:30:39  jsarvesh
 * LOG: IWF Phase-II Changes
 * LOG:
 * LOG: Revision 1.1.2.3  2013/03/22 06:15:49  jsarvesh
 * LOG: changes done to configure resultcode from json file
 * LOG:
 * LOG: Revision 1.1.2.2  2013/01/24 19:22:49  lakshman
 * LOG: check in dia test changes.
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/19 22:17:18  brajappa
 * LOG: Added s6a and s13 Release 10 ABNF
 * LOG:
 * LOG: Revision 1.1.2.1.2.1  2012/09/06 11:23:51  jvikas
 * LOG: DTF Branch merge to B-DRE-0212-00 - Sept6.
 * LOG:
 * LOG: Revision 1.1.2.1.4.1  2012/09/04 05:42:33  ncshivakumar
 * LOG: Added AVPs within SubscriptionAPV
 * LOG:
 * LOG: Revision 1.1.2.1  2012/07/09 08:53:44  pramana
 * LOG: New test code added for S6a, S13 for Release 10 support (Bug 48).
 * LOG:
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
 * ID: $Id: InsertSubscriberDataTest.cpp,v 1.1.6.2 2014/02/12 08:06:13 millayaraja Exp $ 								    	
 ****************************************************************************/
#ident "$Id: InsertSubscriberDataTest.cpp,v 1.1.6.2 2014/02/12 08:06:13 millayaraja Exp $"

#include <app.h>
#include <s6a_defines.h>
#include <s6a_stats.h>
#include <diameter/s6a_r10/InsertSubscriberData.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::s6a_r10;

extern string sessIdString;
extern ITS_UINT sIdx;

enum IDRFlagsValue
{
    IDR_FLAG_UE_REACH_REQ       = (1 << 0), 
    IDR_FLAG_TADS_DATA_REQ      = (1 << 1), 
    IDR_FLAG_EPS_USER_STATE_REQ = (1 << 2), 
    IDR_FLAG_EPS_LOC_INFO_REQ   = (1 << 3), 
    IDR_FLAG_CUR_LOC_REQ        = (1 << 4), 
    IDR_FLAG_LOCAL_TZONE_REQ    = (1 << 5)
};

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
    diameter::s6a_r10::InsertSubscriberDataRequest IDReq;

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
    //UserName userName("sip:user@3gppnetwork.com");
    //IDReq.setUserName(userName);


    static long long imsi_number=singlton::arg[0];
        char temp[100]={'\0'},*end;
        char s[100]="@3gppntework.org";
        cout<<"IMSI BASED ROUTING"<<endl;
        sprintf(temp,"%lld%s",imsi_number,s);
        UserName userName((const char *)temp);
        IDReq.setUserName(userName);
        if(imsi_number!=singlton::arg[1])
                imsi_number++;
        else
                imsi_number=singlton::arg[0];

    // Set Subscription Data AVP. 
    //add avp MSISDN
    MSISDN msisdn("InsertMSISDN");
    SubscriberStatus subStatus(SubscriberStatus::SERVICEGRANTED); 
    SubscriptionData  subData;
    // add avp Access-Restriction-Data 
    //contains a bit mask where each bit when set to 1 
    //indicates a restriction.
    AccessRestrictionData ard(2);
    subData.setAccessRestrictionData(ard);
    subData.setMSISDN(msisdn);  
    subData.setSubscriberStatus(subStatus);  
    
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
    diameter::base::DestinationRealm destRealm1("intellinet.com");
    diameter::base::DestinationHost destHost1("serverA");
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

    apnConfigProf.addAPNConfiguration(const_cast<diameter::s6a_r10::APNConfiguration&>(apnConfig));
    apnConfigProf.setContextIdentifier(cid);

    diameter::s6a_r10::AllAPNConfigurationsIncludedIndicator apnConfigInd((diameter::s6a_r10::AllAPNConfigurationsIncludedIndicator::Value)0);
    apnConfigProf.setAllAPNConfigurationsIncludedIndicator(apnConfigInd);
    subData.setAPNConfigurationProfile(apnConfigProf);
    //End of Sub-Grouped AVP APN-Configuration-Profile
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
   
   diameter::s6a_r10::TraceReference traceRef("tr");
   traceData.setTraceReference(traceRef);
   diameter::s6a_r10::TraceDepth trDepth((diameter::s6a_r10::TraceDepth::Value)0);
   traceData.setTraceDepth(trDepth);
   diameter::s6a_r10::TraceNETypeList tNetTList("tl");
   traceData.setTraceNETypeList(tNetTList);
   diameter::s6a_r10::TraceEventList tEvtList("te");
   traceData.setTraceEventList(tEvtList);
   diameter::s6a_r10::TraceCollectionEntity tcEntity(addr1);
   traceData.setTraceCollectionEntity(tcEntity);

   subData.setTraceData(traceData);
   //End of sub-grouped AVP Trace-Data
   //
   //   //Start of sub-grouped AVP GPRS-Subscription-Data
 
   diameter::s6a_r10::GPRSSubscriptionData gprsSubData;

   //Start of sub-grouped AVP PDP-Context
   diameter::s6a_r10::PDPContext pdpContext;
   diameter::s6a_r10::ExtPDPType extPDPType("EP");
   pdpContext.setExtPDPType(extPDPType);

   diameter::Address addr((diameter::Address::Family)1, "1.1.1.1");

   diameter::s6a_r10::ExtPDPAddress extPDPAddr(addr);
   pdpContext.setExtPDPAddress(extPDPAddr);

   diameter::s6a_r10::SIPTOPermission sipToPermission1((diameter::s6a_r10::SIPTOPermission::Value)0);
   pdpContext.setSIPTOPermission(sipToPermission1);
   diameter::s6a_r10::LIPAPermission lipaPermission1((diameter::s6a_r10::LIPAPermission::Value)0);
   pdpContext.setLIPAPermission(lipaPermission1);


   pdpContext.setContextIdentifier(cid);
   diameter::s6a_r10::PDPType pdpType("PD");
   pdpContext.setPDPType(pdpType);

   diameter::s6a_r10::QoSSubscribed qos("QOS");
   pdpContext.setQoSSubscribed(qos);

   diameter::s6a_r10::ServiceSelection serviceSel("APN");
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
    AMBR ambr;
    MaxRequestedBandwidthUL maxReqBwUL(11);
    ambr.setMaxRequestedBandwidthUL(maxReqBwUL);
    MaxRequestedBandwidthDL maxReqBwDL(22);
    ambr.setMaxRequestedBandwidthDL(maxReqBwDL);
    //apnConf.setAMBR(ambr);
 
    //apnConProfile.addAPNConfiguration(apnConf);
 
    //sub.setAPNConfigurationProfile(apnConProfile);

    IDReq.setSubscriptionData(subData);

   //Set IDR Flags for Testing Provide Subscriber Info Req
    IDReq.setIDRFlags(IDRFlags(IDR_FLAG_UE_REACH_REQ));
    
     
		   
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
    bool isNull;
    bool isAVPEnabled;
    Json::Value l_jsonRoot = parseS6aConfig();

    Json::Value* m_jsonRoot = &l_jsonRoot;
    Json::Value* m_jsonRoot1 = &(*m_jsonRoot)["s6a_r10"];

    Json::Value* cfg = &(*m_jsonRoot1)["InsertSubscriberDataAnswer"];


    // 1. Create an instance of InsertSubDataAnswer class
    // The Update-Data-Answer command is sent by a server
    // in response to the Update-Data-Request command with
    // Command-Code = 666 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::s6a_r10::InsertSubscriberDataAnswer IDAns;

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

    isNull = (*cfg)["ResultCode"]["Value"].isNull();
    if(!isNull)
    {
        ResultCode resultCode((*cfg)["ResultCode"]["Value"].asInt());
        IDAns.setResultCode(resultCode);
    }

    // Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of Experimental-Result AVP is 297.
    // The data type of Experimental-Result AVP is Grouped Type.
    if(((*cfg)["ResultCode"]["Value"].asInt()) != 2001)
    {
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
        uint32_t gsmErr = 2001u; //ITS_DIA_INVALID_MSG_LENGTH;
        ExperimentalResultCode experimentalResultCode((*cfg)["ResultCode"]["Value"].asInt());
        experimentalResult.setExperimentalResultCode(experimentalResultCode);

        // [2.2] Set the Experimental-Result AVP.

        // This AVP is required incase of Result-Code AVP is missing.
        IDAns.setExperimentalResult(experimentalResult);
    }
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
   
    //NOTE: Setting Supported features.
    isNull = (*cfg)["Supported_Features"]["Enabled"].isNull();
    isAVPEnabled = (*cfg)["Supported_Features"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        SupportedFeatures suppfeatures;

        isNull = (*cfg)["Supported_Features"]["Vendor_Id"]["Value"].isNull();
        if(!isNull)
        {
            suppfeatures.setVendorId(VendorId((*cfg)["Supported_Features"]["Vendor_Id"]["Value"].asInt()));
        }
        isNull = (*cfg)["Supported_Features"]["Feature_List_ID"]["Value"].isNull();
        if(!isNull)
        {
            suppfeatures.setFeatureListID(FeatureListID((*cfg)["Supported_Features"]["Feature_List_ID"]["Value"].asInt()));
        }
        isNull = (*cfg)["Supported_Features"]["Feature_List"]["Value"].isNull();
        if(!isNull)
        {
            suppfeatures.setFeatureList(FeatureList((*cfg)["Supported_Features"]["Feature_List"]["Value"].asInt()));
        }
        IDAns.addSupportedFeatures(suppfeatures);
    }
    
    isNull = (*cfg)["IDA_Flags"]["Value"].isNull();
    isAVPEnabled = (*cfg)["IDA_Flags"]["Enabled"].asBool();
    if((!isNull) && isAVPEnabled)
    {
        IDAns.setIDAFlags(IDAFlags((*cfg)["IDA_Flags"]["Value"].asInt()));
    }
    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    IDAns.setOriginRealm(originRealm);

    // [2.1.2] set the RAT-type AVP.
    RATType ratType(RATType::EUTRAN);
    IDAns.setRATType(ratType);

    IDAns.setIMSVoiceOverPSSessionsSupported(IMSVoiceOverPSSessionsSupported(IMSVoiceOverPSSessionsSupported::SUPPORTED));
    IDAns.setLastUEActivityTime(LastUEActivityTime(1000));

    
    // [2.1.3] set the EPS User state AVP
    EPSUserState epsUserState;
    MMEUserState mmeUserState;
    UserState userState(UserState::DETACHED);
    mmeUserState.setUserState(userState);
    epsUserState.setMMEUserState(mmeUserState);
    
    SGSNUserState sgsnUserState;
    sgsnUserState.setUserState(userState);
    epsUserState.setSGSNUserState(sgsnUserState);
    IDAns.setEPSUserState(epsUserState);

    // [2.1.4] set the EPS Location Information
    EPSLocationInformation epsLocationInformation;
    MMELocationInformation mmeLocationInformation;
    SGSNLocationInformation sgsnLocationInformation;

    EUTRANCellGlobalIdentity eutranCellGlobalIdentity("1234567");
    mmeLocationInformation.setEUTRANCellGlobalIdentity(eutranCellGlobalIdentity);

    mmeLocationInformation.setTrackingAreaIdentity(TrackingAreaIdentity("12345"));
    mmeLocationInformation.setGeographicalInformation(GeographicalInformation("Geograph"));
    mmeLocationInformation.setGeodeticInformation(GeodeticInformation("GeodeticIn"));
    mmeLocationInformation.setCurrentLocationRetrieved(CurrentLocationRetrieved(CurrentLocationRetrieved::ACTIVE_LOCATION_RETRIEVAL));
    mmeLocationInformation.setAgeOfLocationInformation(AgeOfLocationInformation(250));
    epsLocationInformation.setMMELocationInformation(mmeLocationInformation);


    sgsnLocationInformation.setCellGlobalIdentity(CellGlobalIdentity("CellGlobalIdentity1"));
    sgsnLocationInformation.setLocationAreaIdentity(LocationAreaIdentity("LocationAreaIdentity1"));
    sgsnLocationInformation.setServiceAreaIdentity(ServiceAreaIdentity("ServiceAreaIdentity1"));
    sgsnLocationInformation.setRoutingAreaIdentity(RoutingAreaIdentity("RoutingAreaIdentity1"));
    sgsnLocationInformation.setGeographicalInformation(GeographicalInformation("Geograph"));
    sgsnLocationInformation.setGeodeticInformation(GeodeticInformation("GeodeticIn"));
    sgsnLocationInformation.setCurrentLocationRetrieved(CurrentLocationRetrieved(CurrentLocationRetrieved::ACTIVE_LOCATION_RETRIEVAL));
    sgsnLocationInformation.setAgeOfLocationInformation(AgeOfLocationInformation(250));

    IDAns.setEPSLocationInformation(epsLocationInformation);

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


