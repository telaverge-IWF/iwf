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
 * LOG: $Log: STTest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:03  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.3  2006/11/29 12:38:05  kamakshilk
 * LOG: Send app Id changed to TX app Id
 * LOG:
 * LOG: Revision 1.2  2006/11/07 13:25:36  kamakshilk
 * LOG: Changes to work with ITS-Diameter
 * LOG:
 * LOG: Revision 1.1  2006/10/03 09:21:28  rrath
 * LOG: Baseline distributed demo for new IMS Interfaces.
 * LOG:
 * LOG:
 * ID: $Id: STTest.cpp,v 3.1 2008/03/31 10:33:03 nvijikumar Exp $
 ****************************************************************************/
#ident "$Id: STTest.cpp,v 3.1 2008/03/31 10:33:03 nvijikumar Exp $"

#include <app.h>
#include <idc_api.h>

#include <tx_defines.h>
#include <diameter/tx/ST.h>
                                                                                
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::tx;

unsigned int sIdxTxSt = 0;
string sessIdStringTxSt;
IDSCLApi apiTxSt;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the STRequest to the
 *      diameter stack. Create the STRequest object,
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
int SendTxSTRequest()
{
    // [1] Create an instance of STRequest.
    STRequest streq(false,false);

    // [2] Insert data in the created STRequest object.

    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.

    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter
    // Header.The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    cout<<"Please enter the Session ID to Terminate"<<endl;
    string sessIdString;
    cin>>sessIdString;
    streq.setSessionId(SessionId(sessIdString));
    
    cout << "Please enter Session Index" << endl;
    string sId;
    cin >> sId;
    sIdxTxSt = atoi(sId.c_str());

    // [2.1.2] Populate Mandatories which can appear anywhere.

    // [2.1.2.1] Populate required parameter "Origin-Host".
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost originHost(GetOriginHost());
    streq.setOriginHost(originHost);
                                                                                
    // [2.1.2.2] Populate required parameter "Origin-Realm".
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter
    // message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm originRealm(GetOriginRealm());
    streq.setOriginRealm(originRealm);

    // [2.1.2.3] Populate required parameter "Destination-Realm".
    // The data type of Destination-Realm is DiameterIdentity.
    // This AVP contains the Realm the message is to be routed to.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Destination-Realm is 283.
    DestinationRealm destinationRealm(GetDestinationRealm());
    streq.setDestinationRealm(destinationRealm);

    // [2.1.2.4] Populate required parameter "Termination-Cause".
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
    TerminationCause termc(TerminationCause::DIAMETER_LOGOUT);
    streq.setTerminationCause(termc);

    // [2.1.2.5] Populate required parameter "Auth-Application-Id".
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP shall contain the value of TBD as defined in X-S0013-013-0.
    // The AVP code of Auth-Application-Id is 258.
    AuthApplicationId authApplicationId(TX_INTERFACE_APP_ID);
    streq.setAuthApplicationId(authApplicationId);

    // [2.2] Populate Optional AVPs.
 
    // [2.2.1] Populate optional parameter "Destination-Host"
    // The data type for Destination-Host is DiameterIdentity.
    // This AVP MUST be present in all unsolicited agent initiated
    // messages, MAY be present in request messages and MUST NOT be
    // present in answers.
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    streq.setDestinationHost(destinationHost);

    // [2.2.2] Populate optional(multiple occurence) parameter "Class".
    // The data type for Class AVP is OctetString.
    // This is used to by Diameter servers to return state information 
    // to the access device.
    // The AVP Code of Class is 25.
    Class class1("Business");
    streq.addClass(class1);
   
    // [2.2.3] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type for Origin-State-Id is of type Unsigned32.
    // It is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state,eg upon reboot.
    // The AVP Code of Origin-State-Id is 278.
    OriginStateId originStateId(3);
          // API should be provided for getting the Origin-State-Id value.
    streq.setOriginStateId(originStateId);

//    streq.addProxyInfo(proxyInfo);
//    streq.addRouteRecord(routeRecord);

                                                                                
    std::cout << streq << std::endl;

    apiTxSt.Send(streq, sIdxTxSt, TX_INTERFACE_APP_ID);
    return (ITS_SUCCESS);
    
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
int SendTxSTAnswer(const CommandImpl * impl1)
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

//	stans.addProxyInfo(proxyInfo);

                                                                                
    std::cout << stans << std::endl;

    apiTxSt.Send(stans, sIdxTxSt, TX_INTERFACE_APP_ID);
    return (ITS_SUCCESS);

}
