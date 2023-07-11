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
 * LOG: $Log: AuthenticationInformationTest.cpp,v $
 * LOG: Revision 1.1.6.2.2.1  2014/08/06 15:52:08  jsarvesh
 * LOG: Encoding VplmnId in AIR and ULR
 * LOG:
 * LOG: Revision 1.1.6.2  2014/02/12 08:06:13  millayaraja
 * LOG:  added testapp s6a_r10 for IWF
 * LOG:
 * LOG: Revision 1.1.2.3  2013/05/22 15:30:39  jsarvesh
 * LOG: IWF Phase-II Changes
 * LOG:
 * LOG: Revision 1.1.2.2  2013/02/04 04:03:45  brajappa
 * LOG: Meaningful values for ResyncInfo and VPLMNId
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/19 22:17:18  brajappa
 * LOG: Added s6a and s13 Release 10 ABNF
 * LOG:
 * LOG: Revision 1.1.2.1  2012/07/09 08:53:44  pramana
 * LOG: New test code added for S6a, S13 for Release 10 support (Bug 48).
 * LOG:
 * LOG: Revision 1.5  2010/09/07 12:26:21  vkumara
 * LOG: Updated with V 8.5.0
 * LOG:
 * LOG: Revision 1.4  2009/03/04 12:42:16  sureshj
 * LOG: Demo changes for Motorola specific part changes.TS 29272 v8.1.0.
 * LOG:
 * LOG: Revision 1.3  2008/11/12 06:17:50  sureshj
 * LOG: Updates for supporting v8.0.0. part of 3.1.1 release.
 * LOG:
 * LOG: Revision 1.2  2008/08/19 06:06:01  sureshj
 * LOG: Changes for AVP type changes in abnf.
 * LOG:
 * LOG: Revision 1.1  2008/08/18 06:47:13  sureshj
 * LOG: Initial commits.
 * LOG:
 * ID: $Id: AuthenticationInformationTest.cpp,v 1.1.6.2.2.1 2014/08/06 15:52:08 jsarvesh Exp $
 ***************************************************************************/

#include <app.h>
#include <s6a_defines.h>
#include <s6a_stats.h>
#include <diameter/s6a_r10/AuthenticationInformation.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::s6a_r10;

extern string sessIdString;
extern ITS_UINT sIdx;
extern void CreatePlmn(unsigned char* plmn, std::string& mcc, std::string& mnc);
extern void ExtractMncMcc(const std::string& imsi, std::string& strMcc, std::string& strMnc);

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
int SendS6AAuthenticationInformationRequest()
{
    // [1]. Create an instance of AuthenticationInformationRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::s6a_r10::AuthenticationInformationRequest AIReq;

    bool isNull;
    bool isAVPEnabled;
    Json::Value l_jsonRoot = parseS6aConfig();

    Json::Value* m_jsonRoot = &l_jsonRoot;
    Json::Value* m_jsonRoot1 = &(*m_jsonRoot)["s6a_r10"];

    Json::Value* cfg = &(*m_jsonRoot1)["AuthenticationInformationRequest"];


    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(S6A_INTERFACE_APP_ID, sIdx, sessIdString);
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
    //UserName userName("sip:user@3gppnetwork.com");
    //AIReq.setUserName(userName);

    static long long imsi_number=singlton::arg[0];
        char temp[100]={'\0'},*end;
        char s[100]="@3gppntework.org";
        cout<<"IMSI BASED ROUTING"<<endl;
        sprintf(temp,"%lld%s",imsi_number,s);
        UserName userName((const char *)temp);
        AIReq.setUserName(userName);
        if(imsi_number!=singlton::arg[1])
                imsi_number++;
        else
                imsi_number=singlton::arg[0];

   // [2.1.7] Set Requested-EUTRAN-Authentication-Infos AVP
   // The Requested-EUTRAN-Authentication-Infos AVP code is 152.
    RequestedEUTRANAuthenticationInfo REAInfo; 
    NumberOfRequestedVectors nofreqvect1(10);
    REAInfo.setNumberOfRequestedVectors(nofreqvect1);
    ImmediateResponsePreferred	imrespref1(2);
    REAInfo.setImmediateResponsePreferred(imrespref1);
    
    // TODO: To compute the value, an array of bytes must be converted to string
    // "123456789012345678901234567890" is not the intended representation
    ReSynchronizationInfo rsinfo1("123456789012345678901234567890");
    REAInfo.setReSynchronizationInfo(rsinfo1);
 
    AIReq.setRequestedEUTRANAuthenticationInfo(REAInfo);
  
    // [2.1.8] Set Requested-UTRAN-Authentication-Infos AVP
    // The Requested-EUTRAN-Authentication-Infos AVP code is 173.
    RequestedUTRANGERANAuthenticationInfo RUGAInfo;
    NumberOfRequestedVectors nofreqvect2(11);
    RUGAInfo.setNumberOfRequestedVectors(nofreqvect2);
    ImmediateResponsePreferred  imrespref2(3);
    RUGAInfo.setImmediateResponsePreferred(imrespref2);

    AIReq.setRequestedUTRANGERANAuthenticationInfo(RUGAInfo);

    //[2.1.10] Set Visited-PLMN-Id AVP.
    // TODO: To compute the value, an array of bytes must be converted to string
    // This must be based on the specification for the construction of PLMN
    // "310150" is not the intended representation
    std::string vplmnId = (*cfg)["VPLMN_Id"]["Value"].asString();

    std::string mcc = "";
    std::string mnc = "";
    ExtractMncMcc(vplmnId , mcc, mnc);
    unsigned char plmn[4] = {0};

    CreatePlmn(plmn, mcc, mnc);
 
    VisitedPLMNId  visPLMNid((const char*)plmn);
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

    S6AStats::GetS6AStats()->UpdateSendStats(AIReq.getCommandCode(), ITS_TRUE);
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
int SendS6AAuthenticationInformationAnswer(const CommandImpl * impl)
{

    bool isNull;
    bool isAVPEnabled;
    Json::Value l_jsonRoot = parseS6aConfig();

    Json::Value* m_jsonRoot = &l_jsonRoot;
    Json::Value* m_jsonRoot1 = &(*m_jsonRoot)["s6a_r10"];

    Json::Value* cfg = &(*m_jsonRoot1)["AuthenticationInformationAnswer"];


    // 1. Create an instance of AuthenticationInformationAnswer class
    // The Update-Data-Answer command is sent by a server
    // in response to the Update-Data-Request command with
    // Command-Code = 306 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::s6a_r10::AuthenticationInformationAnswer AIAns;

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
    //ResultCode resultCode(2001u);
    //AIAns.setResultCode(resultCode);

    isNull = (*cfg)["ResultCode"]["Value"].isNull();
    if(!isNull)
    {
        ResultCode resultCode((*cfg)["ResultCode"]["Value"].asInt());
        AIAns.setResultCode(resultCode);
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
        ExperimentalResultCode experimentalResultCode((*cfg)["ResultCode"]["Value"].asInt());
        experimentalResult.setExperimentalResultCode(experimentalResultCode);

        // [2.2] Set the Experimental-Result AVP.

        // This AVP is required incase of Result-Code AVP is missing.
        AIAns.setExperimentalResult(experimentalResult);
    }

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
    S6AStats::GetS6AStats()->UpdateSendStats(AIAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}


