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
 * LOG: $Log: RATest.cpp,v $
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
 * LOG: Revision 1.1  2006/07/25 04:56:35  kamakshilk
 * LOG: Baseline demo application for Tx Interface.
 * LOG:
 * LOG:
 *
 * ID: $Id: RATest.cpp,v 3.1 2008/03/31 10:33:13 nvijikumar Exp $
 ****************************************************************************/
#include <diameter/tx/RA.h>
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
 *  Purpose: This function sends the RARequest to the
 *      diameter stack. Create the RARequest object,
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
int SendTxRARequest()
{
	// [1] Create an instance of RARequest.
    RARequest rareq(false,false);

    // [2] Insert data in the created RARequest object.

    // [2.1] Populate Mandatories.
    // [2.1.1] Populate Fixed Mandatories.

    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter
    // Header.The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    cout << "Please enter the Session ID to Re-Authorize" << endl;
    cin >> sessIdString;
    rareq.setSessionId(SessionId(sessIdString));

    rareq.setSessionIndex(sIdx);

    // [2.1.2] Populate Mandatories which can appear anywhere.

    // [2.1.2.1] Populate required parameter "Origin-Host".
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost originHost(GetOriginHost());
    rareq.setOriginHost(originHost);
                                                                                
    // [2.1.2.2] Populate required parameter "Origin-Realm".
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter
    // message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm originRealm(GetOriginRealm());
    rareq.setOriginRealm(originRealm);

    // [2.1.2.3] Populate required parameter "Destination-Realm".
    // The data type of Destination-Realm is DiameterIdentity.
    // This AVP contains the Realm the message is to be routed to.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Destination-Realm is 283.
    DestinationRealm destinationRealm(GetDestinationRealm());
    rareq.setDestinationRealm(destinationRealm);

    // [2.1.2.4] Populate required parameter "Destination-Host"
    // The data type for Destination-Host is DiameterIdentity.
    // This AVP MUST be present in all unsolicited agent initiated
    // messages, MAY be present in request messages and MUST NOT be
    // present in answers.
    // The AVP Code of Destination-Host is 293.
    DestinationHost destinationHost(GetDestinationHost());
    rareq.setDestinationHost(destinationHost);

    // [2.1.2.5] Populate required parameter "Auth-Application-Id".
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP shall contain the value of TBD as defined in X-S0013-013-0.
    // The AVP code of Auth-Application-Id is 258.
    AuthApplicationId authApplicationId(TX_INTERFACE_APP_ID);
    rareq.setAuthApplicationId(authApplicationId);

    // [2.1.2.6] Populate optional(multiple occurence) parameter 
    //           "Specific-Action".
    // The data type of Specific-Action is Enumerated.
    // Within a PCRF initiated Re-Authorization Request,the Specific-Action AVP
    // determines the type of the action.
    // Within an initial AA request the AF may use the Specific-Action AVP to
    // request specific actions from server at the bearer events and to limit 
    // the contact to such bearer events where specific action is required. If 
    // the Specific-Action AVP is omitted within the initial AA request,no 
    // notification of any of the events defined below is requested.
    // The AVP Code of Specific-Action is 513.
    SpecificAction spefcActn1(SpecificAction::CHARGING_CORRELATION_EXCHANGE);
    rareq.addSpecificAction(spefcActn1);

    // [2.2] Populate Optional AVPs.

    // [2.2.1] Populate optional(multiple occurence) parameter 
    //         Access-Network-Charging-Identifier.
    // The data type of Access-Network-Charging-Identifier is Grouped.
    // This contains a charging identifier within the Access-Network-Charging-
    // Identifier-Value AVP along with information about the flows transported
    // within the corresponding bearer within the Flows AVP. If no Flows AVP is
    // provided, the Access-Network-Charging-Identifier-Value applies for all
    // flows within the AF session.
    // The AVP Code of Access-Network-Charging-Identifier is 502.
    AccessNetworkChargingIdentifier accNwChargingId1; 
    
    // [2.2.1.1] Populate "Access-Network-Charging-Identifier" grouped AVPs.
    PopulateAccessNetworkChargingIdentifier(accNwChargingId1);
                                                                                
    // [2.2.1.2] Add "Access-Network-Charging-Identifier" AVP to AAA object.
    rareq.addAccessNetworkChargingIdentifier(accNwChargingId1);

    // [2.2.2] Populate optional parameter Access-Network-Charging-Address.
    // The data type of Access-Network-Charging-Address is Address.
    // This indicates the IP Address of the network entity within the access
    // network performing charging(e.g.PDSN IPaddress). The Access-Network-
    // Charging-Address AVP should not be forwarded over an inter-operator 
    // interface.
    // The AVP Code of Access-Network-Charging-Address is 501.
    Address addrChrg(Address::IPV4, "192.168.7.7");
    AccessNetworkChargingAddress accNwChargingAddr(addrChrg);
    rareq.setAccessNetworkChargingAddress(accNwChargingAddr);

    // [2.2.3] Populate optional(multiple occurence) parameter Flows.
    // The data type of Flows is Grouped.
    // This indicates IP flows via their flow identifiers. If no Flow-Number 
    // AVP(s) are supplied, the Flows AVP refers to all Flows matching the 
    // media component number.
    // The AVP Code of Flows is 510.
    Flows flows;

    // [2.2.3.1] Populate "Flows" grouped AVPs.
    PopulateFlows(flows);

    // [2.2.3.2] Set "Flows" AVP in Flow-Grouping object.
    rareq.addFlows(flows);

    // [2.2.4] Populate optional(multiple occurence) parameter 
    //         Subscription-Id.
    // The data type of Subscription-Id is Grouped.
    // This is used to identify the end user's subscription.
    // The AVP Code of Subscription-Id is 443.
    SubscriptionId subscrId1;
    PopulateSubscriptionId(subscrId1);
    rareq.addSubscriptionId(subscrId1);

    // [2.2.5] Populate optional parameter "Abort-Cause".
    // The data type of Session-Abort-Cause is Enumerated.
    // This determines the cause of a session abort request or of an RAR 
    // indicating a bearer context release.
    // The AVP code of Session-Abort-Cause AVP is 500.
    AbortCause abortCause(AbortCause::INSUFFICIENT_SERVER_RESOURCES);
    rareq.setAbortCause(abortCause);

    // [2.2.6] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type for Origin-State-Id is of type Unsigned32.
    // It is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state,eg upon reboot.
    // The AVP Code of Origin-State-Id is 278.
    OriginStateId originStateId(3);
          // API should be provided for getting the Origin-State-Id value.
    rareq.setOriginStateId(originStateId);
    
//    rareq.addProxyInfo(proxyInfo);
//    rareq.addRouteRecord(routeRecord);

    cout << "RAR" << rareq;
    SendDiaAppMsg(rareq, sIdx);
    TxStats::GetTxStats()->UpdateSendStats(rareq.getCommandCode(), ITS_TRUE);
                                                                                
    return (ITS_SUCCESS);

}


/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the Answer to the RA request
 *      made by the diameter stack. Create the RAAnswer
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
int SendTxRAAnswer(const CommandImpl * impl1)
{
    // [1] Create RAAnswer object.
    RAAnswer raans(false,false);
                                                                                
    // [1.1] Create an instance of RARequest class with recived event.
    RARequest rareq(*impl1);

    // [2.1] Populate Mandatories.

    // [2.1.1] Populate Fixed Mandatories.

    // [2.1.1.1] Populate Fixed parameter "Session-Id".
    // The data type of Session-Id is UTF8String.
    // This AVP is used to identify a specific session.
    // The Session-Id SHOULD appear immediately following the Diameter Header.
    // The Session-Id MUST be globally and eternally unique.
    // The AVP Code of Session-Id is 263.
    const SessionId& sessionId = rareq.getSessionId();
    raans.setSessionId(sessionId);

    raans.setSessionIndex(rareq.getSessionIndex());

    // [2.1.2] Populate Mandatories which can appear anywhere.

    // [2.1.2.1] Populate required parameter "Origin-Host".
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter
    // message.
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost originHost(GetOriginHost());
    raans.setOriginHost(originHost);
                                                                                
    // [2.1.2.2] Populate required parameter "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm originRealm(GetOriginRealm());
    raans.setOriginRealm(originRealm);

    // [2.2] Populate Optional AVPs.

    // [2.2.1] Populate optional parameter "Result-Code".
    // The data type of Result-Code is Unsigned32.
    // This AVP indicates whether a particular request was completed
    // successfully or whether an error occurred.
    // The AVP Code of Result-Code is 268.
    ResultCode resultCode(2001u);
    raans.setResultCode(resultCode);

    // [2.2.2] Create the Experimental-Result AVP
    // The Experimental-Result AVP indicates whether a particular
    // vendor specific request was completed successfully or whether
    // an error occurred.
    // The AVP Code of AVP is 297.
    // The data type of AVP is Grouped Type.
    // ResultCode AVP is already been set, we dont need to set this.
    //ExperimentalResult er1;
                                                                                
    // [2.2.2.1.1] Set the Vendor-Id AVP in Experimental-Result AVP.
    // The Vendor-Id AVP in the Experimental-Result AVP indicates
    // whether a particular vendor-specific request was completed
    // successfully or whether an error occurred.
    //VendorId vid(VENDOR_ID);
    //er1.setVendorId(vid);
                                                                                
    // [2.2.2.1.2] Set the Experimental-Result-Code AVP.
    // The Experimental-Result-Code AVP contains a vendor-assigned
    // value representing the result of processing the request.
    // The AVP Code of AVP is 298 .
    // The data type of AVP is Unsigned32.
    //ExperimentalResultCode erc(100);
    //er1.setExperimentalResultCode(erc);
                                                                                
    // [2.2.2.2]Set the ExperimentalResult AVP
    // raans.setExperimentalResult(er1);

    // [2.2.3] Populate optional(multiple occurence) parameter
    //         Media-Component-Description.
    // Set the Media-Component-Description AVP.
    // The data type of Media-Component-Description is Grouped.
    // This contains service information for a single media component within an
    // AF session.It may be based on the SDI exchanged between AF and AF client
    // in UE.
    // The AVP Code of Media-Component-Description is 517.
    MediaComponentDescription mediaCompDescrp1;

    // [2.2.3.1] Populate "Media-Component-Description" grouped AVPs.
    PopulateMediaComponentDescription(mediaCompDescrp1);
                                                                                
    // [2.2.3.2] Add "Media-Component-Description" AVP to AAR object.
    raans.addMediaComponentDescription(mediaCompDescrp1);

    // [2.2.4] Populate optional(multiple occurence) parameter
    //         Flow-Grouping.
    // The data type of Flow-Grouping is Grouped.
    // This  indicates that no other IP Flows shall be transported together 
    // with the listed IP Flows in the same bearer(s).
    // The AVP Code of Flow-Grouping is 508.
    FlowGrouping flowGrouping1;
    
    // [2.2.4.1] Populate "Flow-Grouping" grouped AVPs.
 
    // [2.2.4.1.1] Populate optional(multiple occurence) parameter Flows.
    // The data type of Flows is Grouped.
    // This indicates IP flows via their flow identifiers. If no Flow-Number 
    // AVP(s) are supplied, the Flows AVP refers to all Flows matching the 
    // media component number.
    // The AVP Code of Flows is 510.
    Flows flows;

    // [2.2.4.1.1.1] Populate "Flows" grouped AVPs.
    PopulateFlows(flows);

    // [2.2.4.1.1.2] Set "Flows" AVP in Flow-Grouping object.
    flowGrouping1.addFlows(flows);
    
    // [2.2.4.2] Set "Flow-Grouping" AVP in AAR object.
    raans.addFlowGrouping(flowGrouping1);

    // [2.2.5] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type for Origin-State-Id is of type Unsigned32.
    // It is a monotonically increasing value that is advanced whenever a
    // Diameter entity restarts with loss of previous state,eg upon reboot.
    // The AVP Code of Origin-State-Id is 278.
    OriginStateId originStateId(4);
          // API should be provided for getting the Origin-State-Id value.
    raans.setOriginStateId(originStateId);

    // [2.2.6] Populate optional parameter Error-Message.
    // The data type of Error-Message is UTF8String.
    // It MAY accompany a Result-Code AVP as a human readable error message. 
    // The Error-Message AVP is not intended to be useful in real-time, and
    // SHOULD NOT be expected to be parsed by network entities.
    // The AVP Code of Error-Message is 281.
    ErrorMessage errMsg("success");
    raans.setErrorMessage(errMsg);

    // [2.2.7] Populate optional parameter Error-Reporting-Host.
    // The data type of Error-Reporting-Host is DiameterIdentity.
    // This AVP contains the identity of the Diameter host that sent the 
    // Result-Code AVP to a value other than 2001(Success), only if the host 
    // setting the Result-Code is different from the one encoded in the 
    // Origin-Host AVP.  This AVP is intended to be used for troubleshooting 
    // purposes, and MUST be set when the Result-Code AVP indicates a failure.
    // The AVP Code of Error-Reporting-Host is 294.
//    ErrorReportingHost errRptHost();
//    raans.setErrorReportingHost(errRptHost);
    
//    raans.addFailedAVP(failedAVP);
//    raans.addProxyInfo(proxyInfo);

    cout << "RAA" << raans;
    SendDiaAppMsg(raans, sIdx);
    TxStats::GetTxStats()->UpdateSendStats(raans.getCommandCode(), ITS_FALSE);
                                                                                
    return (ITS_SUCCESS);
    
}
