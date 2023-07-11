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
 * LOG: $Log: DeleteSubscriberTest.cpp,v $
 * LOG: Revision 1.1.6.2  2014/02/12 08:06:13  millayaraja
 * LOG:  added testapp s6a_r10 for IWF
 * LOG:
 * LOG: Revision 1.1.2.2  2013/03/22 06:15:49  jsarvesh
 * LOG: changes done to configure resultcode from json file
 * LOG:
 * LOG: Revision 1.1.2.1  2012/12/19 22:17:18  brajappa
 * LOG: Added s6a and s13 Release 10 ABNF
 * LOG:
 * LOG: Revision 1.1.2.1  2012/07/09 08:53:44  pramana
 * LOG: New test code added for S6a, S13 for Release 10 support (Bug 48).
 * LOG:
 * LOG: Revision 1.3  2009/03/04 12:43:31  sureshj
 * LOG: Demo changes for Motorola specific part changes.TS 29272 v8.1.0.
 * LOG:
 * LOG: Revision 1.2  2008/11/12 09:06:43  sureshj
 * LOG: New command DSR/DSA added for demo. part of 3.1.1 release.
 * LOG: 
 * ID: $Id: DeleteSubscriberTest.cpp,v 1.1.6.2 2014/02/12 08:06:13 millayaraja Exp $ 
 ***************************************************************************/
#ident "$Id: DeleteSubscriberTest.cpp,v 1.1.6.2 2014/02/12 08:06:13 millayaraja Exp $"

#include <app.h>
#include <s6a_defines.h>
#include <s6a_stats.h>
#include <diameter/s6a_r10/DeleteSubscriberData.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::s6a_r10;

extern string sessIdString;
extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the  DeleteSubscriberDataRequest to the
 *      diameter stack. Create the  DeleteSubscriberDataRequest object,
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
int SendS6ADeleteSubDataRequest()
{
    // [1]. Create an instance of DeleteSubscriberDataRequest.
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::s6a_r10::DeleteSubscriberDataRequest dsdReq;

    // [2.1.1.x] Fixed AVP
    // [2.1.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(S6A_INTERFACE_APP_ID, sIdx, sessIdString);
    dsdReq.setSessionId(diameter::base::SessionId(sessIdString));

    dsdReq.setSessionIndex(sIdx);

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
    dsdReq.setAuthSessionState(authSessionState);

    // [2.1.2.2] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
     OriginHost originHost(GetOriginHost());
     dsdReq.setOriginHost(originHost);

    // [2.1.2.3] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    dsdReq.setOriginRealm(originRealm);

    // [2.1.2.4] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message has
    // to be routed to.
    // The Destination-Realm AVP is used to perform message routing decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destinationRealm(GetDestinationRealm());
    dsdReq.setDestinationRealm(destinationRealm);

    // [2.1.2.5] Set the User-Name AVP.
    // The Update-Name AVP ia a RADIUS AVP and contains the user name.
    // The AVP Code of Update-Name AVP is 1.
    // The data type of Update-Name AVP is UTF8String.
    //UserName userName("sip:user@3gppnetwork.com");
    //dsdReq.setUserName(userName);


    static long long imsi_number=singlton::arg[0];
        char temp[100]={'\0'},*end;
        char s[100]="@3gppntework.org";
        cout<<"IMSI BASED ROUTING"<<endl;
        sprintf(temp,"%lld%s",imsi_number,s);
        UserName userName((const char *)temp);
        dsdReq.setUserName(userName);
        if(imsi_number!=singlton::arg[1])
                imsi_number++;
        else
                imsi_number=singlton::arg[0];

    // [2.1.2.6] Set the DSR-Flags AVP.
    DSRFlags dsrflags(10);
    dsdReq.setDSRFlags(dsrflags);
	 		
    // [2.1.3.x] set Optional AVPs.
    // [2.1.3.1] Set the Destination-Host AVP.
    // The Destination-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Destination-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    DestinationHost DestinationHost(GetDestinationHost());
    dsdReq.setDestinationHost(DestinationHost);

    // Application should not set this AVP.
    // dsdReq.addProxyInfo(diameter::base::ProxyInfo(...));
    // dsdReq.addRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values

    if (appMode == UNIT_TEST)
    cout<<dsdReq;

    // Send object to stack.
    SendDiaAppMsg(dsdReq, sIdx);

    S6AStats::GetS6AStats()->UpdateSendStats(dsdReq.getCommandCode(), ITS_TRUE);
    return ITS_SUCCESS;
}
/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends the Answer to the DeleteSubscriberData request
 *      made by the diameter stack. Create the DeleteSubscriberDataAnswer
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
int SendS6ADeleteSubDataAnswer(const CommandImpl * impl)
{
    bool isNull;
    bool isAVPEnabled;
    Json::Value l_jsonRoot = parseS6aConfig();

    Json::Value* m_jsonRoot = &l_jsonRoot;
    Json::Value* m_jsonRoot1 = &(*m_jsonRoot)["s6a_r10"];

    Json::Value* cfg = &(*m_jsonRoot1)["DeleteSubscriberAnswer"];


    // 1. Create an instance of DeleteSubscriberDataAnswer class
    // The Update-Data-Answer command is sent by a server
    // in response to the Update-Data-Request command with
    // Command-Code = 306 and 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::s6a_r10::DeleteSubscriberDataAnswer dsdAns;

    // Create an instance of DeleteSubscriberDataRequest class to get host and
    // session details
    DeleteSubscriberDataRequest dsdreq(*impl);

    // Get AVP values from requested message
    const SessionId &sid1 = dsdreq.getSessionId();
    const OriginHost &oh1 = dsdreq.getOriginHost();
    const OriginRealm &or1 = dsdreq.getOriginRealm();
    const AuthSessionState &authSessState = dsdreq.getAuthSessionState();

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
    dsdAns.setSessionId(sid1);
    dsdAns.setSessionIndex(dsdreq.getSessionIndex());    
 
    // [2.1.2.x] Required AVPs

    dsdAns.setAuthSessionState(authSessState);

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
        dsdAns.setResultCode(resultCode);
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
        dsdAns.setExperimentalResult(experimentalResult);
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
    //dsdAns.setAuthSessionState(authSessState);

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
    dsdAns.setOriginHost(originHost);

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
        dsdAns.addSupportedFeatures(suppfeatures);
    }

    // [2.1.1] set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(GetOriginRealm());
    dsdAns.setOriginRealm(originRealm);


    // The data type of Proxy-Info is Grouped Type.
    // This AVP should not be set by Application.
    // dsdAns.setProxyInfo(diameter::base::ProxyInfo(...));

    // Create the Route-Record AVP.
    // The identity added in the Route-Record AVP must be the same as
    // the one received in the Origin-Host AVP of the message.
    // The AVP Code of Route-Record AVP is 282
    // The data type of Route-Record is DiameterIdentity.
    // This AVP should not be set by Application.
    // dsdAns.setRouteRecord(diameter::base::RouteRecord(...));
    // add more AVP as ANY values
    
     
    if (appMode == UNIT_TEST)
    cout<<dsdAns;

    // Send Object to stack.
    SendDiaAppMsg(dsdAns, sIdx);

    // Update stats.
    S6AStats::GetS6AStats()->UpdateSendStats(dsdAns.getCommandCode(), ITS_FALSE);
    return ITS_SUCCESS;
}


