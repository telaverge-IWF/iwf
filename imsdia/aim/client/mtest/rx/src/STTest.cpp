/********************************-*-CPP-*-***********************************
 *                                                                          *
 *     Copyright 2006 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 * LOG: $Log: STTest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:02  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.3  2006/11/29 12:35:57  kamakshilk
 * LOG: Send App Id changed to RX app Id
 * LOG:
 * LOG: Revision 1.2  2006/11/07 13:22:30  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1  2006/10/03 09:21:28  rrath
 * LOG: Baseline distributed demo for new IMS Interfaces.
 * LOG:
 * LOG:
 * ID: $Id: STTest.cpp,v 3.1 2008/03/31 10:33:02 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: STTest.cpp,v 3.1 2008/03/31 10:33:02 nvijikumar Exp $"

#include <app.h>
#include <idc_api.h>

#include <rx_defines.h>
#include <diameter/rx/ST.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::rx;

unsigned int sIdxRxSt = 0;
string sessIdStringRxSt;
IDSCLApi apiRxSt;

/*  implementation: public
 ****************************************************************************
 *  Purpose: This function sends the Session termination stReq to the
 *      diameter stack. Creates the SessionTerminationRequest
 *      object, populate the AVPs and send the message to the stack.
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
int SendRxSTRequest() 
{
    // [1]. Create an instance of STRequest class
    // The ST-Request command is sent by a Diameter
    // client to a Diameter Server in order to stReq deregistration
    // Command-Code = 275 with 'R' bit reset
    // Optional param error - whether this command carries an error indicator.
    // Optional param retrans - whether this is a retransmission.
    diameter::rx::STRequest stReq;

    // [2.1.1.x] Fixed AVP 

    // [2.1.1.1] The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    // Provide Session Id to terminate
    cout<<"Please enter the Session ID to Terminate"<<endl;
    string sessIdString;
    cin>>sessIdString;
    stReq.setSessionId(SessionId(sessIdString));

    cout << "Please enter Session Index" << endl;
    string sId;
    cin >> sId;
    sIdxRxSt = atoi(sId.c_str());

    // [2.1.2.x] Required AVPs

    // [2.1.2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter messages.
    // This AVP SHOULD be placed as close to the Diameter header as possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost orighost(GetOriginHost());
    stReq.setOriginHost(orighost);

    // [2.1.2.2] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm origrealm(GetOriginRealm());
    stReq.setOriginRealm(origrealm);

    // [2.1.2.3] Set the Destination-Realm AVP.
    // The Destination-Realm AVP contains the realm, the message routed to.
    // The Destination-Realm AVP is used to perform message routing
    // decisions.
    // The AVP Code of Destination-Realm AVP is 283
    // The data type of Destination-Realm AVP is DiameterIdentity.
    DestinationRealm destrealm(GetDestinationRealm());
    stReq.setDestinationRealm(destrealm);

    // [2.1.2.4] Populate required parameter "Termination-Cause".
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
    TerminationCause termcause(TerminationCause::DIAMETER_BAD_ANSWER);
    stReq.setTerminationCause(termcause);

    // [2.1.2.5] Set the Auth-Application-Id AVP.
    // The Auth-Application-Id AVP is used to advertise support of
    // Authorization and/or Authentication portion of an application
    // The Auth-Application-Id AVP must be present in all the
    // Authorization and/or Authentication messages.
    // The AVP Code of is 258
    // The data type of Auth-Application-Id is Unsigned32.
    AuthApplicationId authid(RX_INTERFACE_APP_ID);
    stReq.setAuthApplicationId(authid);

    // [2.2.x] Optional AVPs

    // [2.2.1] Populate required paramete "Destination-Host".
    // Set the Destination-Host AVP.
    // The data type of Destination-Host is DiameterIdentity
    //This AVP identifies the endpoint where  the Diameter message is destinated
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Destination-Host is 293.
    DestinationHost desthost(GetDestinationHost());
    stReq.setDestinationHost(desthost);

    // [2.2.2] The Class AVP (AVP Code 25) is of type OctetString and is used 
    // to be Diameter servers to return state information to the access device.
    Class class1("Business");
    stReq.addClass(class1);

    // [2.2.3] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    // NOTE: This is a monotonically increasing value that is advanced whenever     
    // a Diameter entity restarts with loss of previous state,
    // for example upon reboot. This Logic is to be implemented
    // by the application developers
    OriginStateId origsid(41);
    stReq.setOriginStateId(origsid);

    // These two APVs set by the stack
    // stReq.addProxyInfo(ProxyInfo(...));
    // stReq.addRouteRecord(RouteRecord(...));
    // add more AVP as ANY values

    std::cout << stReq << std::endl;

    apiRxSt.Send(stReq, sIdxRxSt, RX_INTERFACE_APP_ID);

    return ITS_SUCCESS;

}

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the ST request
 *      made by the diameter stack. Create the STAnswer
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
int SendRxSTAnswer(const CommandImpl * impl1)
{
        // [1] Create STAnswer object.
    STAnswer stans(false,false);
                                                                                
    // [1.1] Create an instance of STRequest class with recived event.
    STRequest streq(*impl1);
                                                                                
    // [2.1] Populate Mandatories.
                                                                                
    // [2.1.1] Populate Fixed Mandatories.
                                                                                
    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    const SessionId& sessionId = streq.getSessionId();
    stans.setSessionId(sessionId);
                                                                                
    // [2.1.2] Populate Mandatories which can appear anywhere.
                                                                                
    // [2.1.2.1] Populate required parameter "Origin-Host".
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter
    // message.
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost originHost(GetOriginHost());
    stans.setOriginHost(originHost);
                                                                                
    // [2.1.2.2] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm originRealm(GetOriginRealm());
    stans.setOriginRealm(originRealm);
                                                                                
    // [2.2] Populate Optional AVPs.
                                                                                
    // [2.2.1] Populate optional parameter "Result-Code".
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    ResultCode resultCode(2001u);
    stans.setResultCode(resultCode);
                                                                                
    // [2.2.2] Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // ResultCode AVP is already been set, we dont need to set this.
    //ExperimentalResult er1;
                                                                                
    // [2.2.2.2] Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    //VendorId vid(VENDOR_ID);
    //er1.setVendorId(vid);
                                                                                
    // [2.2.2.3] Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    //ExperimentalResultCode erc(100);
    //er1.setExperimentalResultCode(erc);
                                                                                
    // [2.2.2]Set the ExperimentalResult AVP
    // stans.setExperimentalResult(er1);
                                                                                
    // [2.2.3] Populate optional parameter Error-Message.
    // The data type of Error-Message is UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message.
    // The Error-Message AVP is not intended to be useful in real-time, and
    // SHOULD NOT be expected to be parsed by network entities.
    // The AVP Code of Error-Message is 281.
    ErrorMessage errMsg("success");
    stans.setErrorMessage(errMsg);
                                                                                
    // [2.2.4] Populate optional parameter Error-Reporting-Host.
    // The data type of Error-Reporting-Host is DiameterIdentity.
    // This AVP contains the identity of the Diameter host that sent the
    // Result-Code AVP to a value other than 2001(Success), only if the host
    // setting the Result-Code is different from the one encoded in the
    // Origin-Host AVP.  This AVP is intended to be used for troubleshooting
    // purposes, and MUST be set when the Result-Code AVP indicates a failure.
    // The AVP Code of Error-Reporting-Host is 294.
//    ErrorReportingHost errRptHost();
//    stans.setErrorReportingHost(errRptHost);
                                                                                
//    FailedAVP failedAVP;
//    stans.addFailedAVP(failedAVP);
                                                                                
    // [2.2.5] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type for Origin-State-Id is of type Unsigned32.
    // It is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state,eg upon reboot.
    // The AVP Code of Origin-State-Id is 278.
    OriginStateId originStateId(2);
          // API should be provided for getting the Origin-State-Id value.
    stans.setOriginStateId(originStateId);
                                                                                
    // [2.2.6] Populate optional(multiple occurence) parameter
    //             "Redirect-Host"
    // Set the Redirect-Host AVP.
    // The data type Redirect-Host is DiamURI.
    // This AVP must be present if the answer message's 'E' bit is set
    // and Result-Code is DIMETER_REDIRECT_INDICATION.
    // The AVP Code of Redirect-Host is 292.
//        RedirectHost redirectHost1; // not clear
                                                                                
    // [2.2.7] Populate optional parameter "Redirect-Host-Usage"
    // Set the Reditect-Host-Usage AVP.
    // The data type Reditect-Host-Usage is Enumerated.
    // This AVP must be present if the answer message's 'E' bit is set
    // and Result-Code is DIMETER_REDIRECT_INDICATION.
    // The AVP Code of Reditect-Host-Usage is 261.
//    RedirectHostUsage redirectHostUsage(RedirectHostUsage::ALL_SESSION);
//    stans.setRedirectHostUsage(redirectHostUsage);
                                                                                
    // [2.2.8] Populate optional parameter "Redirect-Max-Cache-Time"
    // Set the Redirect-Max-Cache-Time AVP.
    // The data type Redirect-Max-Cache-Time is Unsigned32.
    // This AVP must be present if the answer message's 'E' bit is set
    // and Result-Code is DIMETER_REDIRECT_INDICATION and the
    // Redirect-Host-Usage AVP is set to a non zero value.
    // The AVP Code of Redirect-Max-Cache-Time is 262.
//    RedirectMaxCacheTime redirectMaxCacheTime(20);
//    stans.setRedirectMaxCacheTime(redirectMaxCacheTime);
                                                                                
//      stans.addProxyInfo(proxyInfo);
                                                                                
    std::cout << stans << std::endl;

    apiRxSt.Send(stans, sIdxRxSt, RX_INTERFACE_APP_ID);

    return ITS_SUCCESS;
 
}

