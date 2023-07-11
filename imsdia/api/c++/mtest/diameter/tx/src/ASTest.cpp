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
 * LOG: $Log: ASTest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:13  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.3  2006/12/19 08:54:50  kamakshilk
 * LOG: New architecture to work with static and distributed.
 * LOG:
 * LOG: Revision 2.2  2006/10/16 15:08:01  kamakshilk
 * LOG: Merging with ITSDiameter
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.2  2006/08/04 17:52:51  nvijikumar
 * LOG: 1. Changes to update the stats for all messgaes.
 * LOG: 2. Fix for solaris compilation issue.
 * LOG:
 * LOG: Revision 1.1  2006/07/25 04:56:35  kamakshilk
 * LOG: Baseline demo application for Tx Interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: ASTest.cpp,v 3.1 2008/03/31 10:33:13 nvijikumar Exp $
 ****************************************************************************/
                                                                                
#include <diameter/tx/AS.h>
#include <app.h>
#include <tx_defines.h>
#include <tx_stats.h>
                                                                                
using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::tx;

extern string sessIdString;
extern ITS_UINT sIdx;


/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the ASRequest to the
 *      diameter stack. Create the ASRequest object,
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
int SendTxASRequest()
{
	// [1] Create an instance of ASRequest.
    ASRequest asreq(false,false);

    // [2] Insert data in the created ASRequest object.
    // [2.1] Populate Mandatories.

    // [2.1.1] Populate Fixed Mandatories.

    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter
    // Header.The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    cout<<"Please Enter the Session ID to Abort \n";
    cin>>sessIdString;
    asreq.setSessionId(SessionId(sessIdString));

    asreq.setSessionIndex(sIdx);

    // [2.1.2] Populate Mandatories which can appear anywhere.

    // [2.1.2.1] Populate required parameter "Origin-Host".
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost originHost(GetOriginHost());
    asreq.setOriginHost(originHost);
                                                                                
    // [2.1.2.2] Populate required parameter "Origin-Realm".
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter
    // message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm originRealm(GetOriginRealm());
    asreq.setOriginRealm(originRealm);

    // [2.1.2.3] Populate required parameter "Destination-Realm".
    // The data type of Destination-Realm is DiameterIdentity.
    // This AVP contains the Realm the message is to be routed to.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Destination-Realm is 283.
    DestinationRealm destinationRealm(GetDestinationRealm());
    asreq.setDestinationRealm(destinationRealm);

    // [2.1.2.4] Populate required parameter "Destination-Host"
    // The data type for Destination-Host is DiameterIdentity.
    // This AVP MUST be present in all unsolicited agent initiated
    // messages, MAY be present in request messages and MUST NOT be
    // present in answers.
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    asreq.setDestinationHost(destinationHost);

    // [2.1.2.5] Populate required parameter "Auth-Application-Id".
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP shall contain the value of TBD as defined in X-S0013-013-0.
    // The AVP code of Auth-Application-Id is 258.
    AuthApplicationId authApplicationId(TX_INTERFACE_APP_ID);
    asreq.setAuthApplicationId(authApplicationId);

    // [2.1.2.6] Populate required parameter "Abort-Cause".
    // The data type of Session-Abort-Cause is Enumerated.
    // This determines the cause of a session abort request or of an RAR 
    // indicating a bearer context release.
    // The AVP code of Session-Abort-Cause AVP is 500.
    AbortCause abortCause(AbortCause::INSUFFICIENT_SERVER_RESOURCES);
    asreq.setAbortCause(abortCause);

    // [2.2] Populate Optional AVPs.

    // [2.2.1] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type for Origin-State-Id is of type Unsigned32.
    // It is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state,eg upon reboot.
    // The AVP Code of Origin-State-Id is 278.
    OriginStateId originStateId(1);
          // API should be provided for getting the Origin-State-Id value.
    asreq.setOriginStateId(originStateId);

//    asreq.addProxyInfo(proxyInfo);
//    asreq.addRouteRecord(routeRecord);

    cout << "ASR" << asreq;
    SendDiaAppMsg(asreq, sIdx);
    TxStats::GetTxStats()->UpdateSendStats(asreq.getCommandCode(), ITS_TRUE);
                                                                                
    return (ITS_SUCCESS);

}


/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the AS request
 *      made by the diameter stack. Create the ASAnswer
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
int SendTxASAnswer(const CommandImpl * impl1)
{
	// [1] Create ASAnswer object.
    ASAnswer asans(false,false);
                                                                                
    // [1.1] Create an instance of ASRequest class with recived event.
    ASRequest asreq(*impl1);

    // [2.1] Populate Mandatories.

    // [2.1.1] Populate Fixed Mandatories.

    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    const SessionId& sessionId = asreq.getSessionId();
    asans.setSessionId(sessionId);

    asans.setSessionIndex(asreq.getSessionIndex());

    // [2.1.2] Populate Mandatories which can appear anywhere.

    // [2.1.2.1] Populate required parameter "Origin-Host".
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter
    // message.
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost originHost(GetOriginHost());
    asans.setOriginHost(originHost);
                                                                                
    // [2.1.2.2] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm originRealm(GetOriginRealm());
    asans.setOriginRealm(originRealm);

    // [2.2] Populate Optional AVPs.

    // [2.2.1] Populate optional parameter "Result-Code".
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    ResultCode resultCode(2001u);
    asans.setResultCode(resultCode);

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
    // asans.setExperimentalResult(er1);

    // [2.2.3] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type for Origin-State-Id is of type Unsigned32.
    // It is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state,eg upon reboot.
    // The AVP Code of Origin-State-Id is 278.
    OriginStateId originStateId(2);
          // API should be provided for getting the Origin-State-Id value.
    asans.setOriginStateId(originStateId);

    // [2.2.4] Populate optional parameter Error-Message.
    // The data type of Error-Message is UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message. 
    // The Error-Message AVP is not intended to be useful in real-time, and
    // SHOULD NOT be expected to be parsed by network entities.
    // The AVP Code of Error-Message is 281.
    ErrorMessage errMsg("success");
    asans.setErrorMessage(errMsg);

    // [2.2.5] Populate optional parameter Error-Reporting-Host.
    // The data type of Error-Reporting-Host is DiameterIdentity.
    // This AVP contains the identity of the Diameter host that sent the 
    // Result-Code AVP to a value other than 2001(Success), only if the host 
    // setting the Result-Code is different from the one encoded in the 
    // Origin-Host AVP.  This AVP is intended to be used for troubleshooting 
    // purposes, and MUST be set when the Result-Code AVP indicates a failure.
    // The AVP Code of Error-Reporting-Host is 294.
//    ErrorReportingHost errRptHost();
//    asans.setErrorReportingHost(errRptHost);

//    FailedAVP failedAVP;
//    asans.addFailedAVP(failedAVP);

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
//    asans.setRedirectHostUsage(redirectHostUsage);

    // [2.2.8] Populate optional parameter "Redirect-Max-Cache-Time"
    // Set the Redirect-Max-Cache-Time AVP.
    // The data type Redirect-Max-Cache-Time is Unsigned32.
    // This AVP must be present if the answer message's 'E' bit is set
    // and Result-Code is DIMETER_REDIRECT_INDICATION and the
    // Redirect-Host-Usage AVP is set to a non zero value.
    // The AVP Code of Redirect-Max-Cache-Time is 262.
//    RedirectMaxCacheTime redirectMaxCacheTime(20);
//    asans.setRedirectMaxCacheTime(redirectMaxCacheTime);

//	asans.addProxyInfo(proxyInfo);

    cout << "ASA" << asans;
    SendDiaAppMsg(asans, sIdx);
    TxStats::GetTxStats()->UpdateSendStats(asans.getCommandCode(), ITS_FALSE);
                                                                                
    return (ITS_SUCCESS);

}
