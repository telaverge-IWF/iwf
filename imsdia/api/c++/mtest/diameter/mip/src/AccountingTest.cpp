/****************************************************************************
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
 * LOG: $Log: AccountingTest.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:10  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 1.1  2007/01/08 14:16:37  hbhatnagar
 * LOG: added the Accounting Request and Answer with Mip specific AVPs
 * LOG:
 *
 * ID: $Id: AccountingTest.cpp,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $
 *
 ***************************************************************************/
#ident "$Id: AccountingTest.cpp,v 3.1 2008/03/31 10:33:10 nvijikumar Exp $"

#include <app.h>
#include <mip_defines.h>
#include <mip_stats.h>
#include <diameter/mip/Accounting.h>

using namespace std;
using namespace its;
using namespace diameter;
using namespace diameter::base;
using namespace diameter::mip;

extern string sessIdString;
extern ITS_UINT sIdx;

/*.implementation:public
 ****************************************************************************
 *  Purpose: This function sends the MipAccountingRequest to the
 *      diameter stack. Create the MipAccountingRequest object,
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

int SendMipAccountingRequest()
{
    // [1] Create CapabilitiesExchangeRequest object.
    AccountingRequest acReq(false, false);

    // [2.1] Populate Mandatories.
                              
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    AllocateSession(MIP_INTERFACE_APP_ID, sIdx,sessIdString);
    acReq.setSessionId(diameter::base::SessionId(sessIdString));
    acReq.setSessionIndex(sIdx);

    // [2.1.2] Populate required Mandatories.

    // [2.1.2.1] Populate required paramete "Origin-Host".
    // Set the Origin-Host AVP.
    // The data type of Origin-Host is DiameterIdentity
    // This AVP identifies the endpoint that originated the Diameter message
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Origin-Host is 264.
    OriginHost originHost(GetOriginHost());
    acReq.setOriginHost(originHost);

    // [2.1.2.2] Populate required paramete "Origin-Realm".
    // Set the Origin-Realm AVP.
    // The data type of Origin-Realm is DiameterIdentity.
    // This AVP contains the Realm of the originator of any Diameter message.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Origin-Realm is 296.
    OriginRealm origRealm(GetOriginRealm());
    acReq.setOriginRealm(origRealm);

    // [2.1.2.3] Populate required paramete "Destination-Realm".
    // Set the Destination-Realm AVP.
    // The data type of Destination-Realm is DiameterIdentity.
    // This AVP contains the Realm the message is to be routed to.
    // This AVP SHOULD be placed as close to the Diameter header.
    // The AVP Code of Destination-Realm is 283.
    DestinationRealm destinationRealm(GetDestinationRealm());
    acReq.setDestinationRealm(destinationRealm);

    // [2.1.2.4] Populate required paramete "Accounting-Record-Type".
    // Set the Accounting-Record-Type AVP.
    // The data type of Accounting-Record-Type is Enumerated.
    // This Avp contains the type of accounting record being sent.
    // The following values are currently defined
    // EVENT_RECORD                    1
    // START_RECORD                    2 
    // The AVP Code of Accounting-Record-Type is 480.
    AccountingRecordType accr(AccountingRecordType::START_RECORD);
    acReq.setAccountingRecordType(accr);
    
    // [2.1.2.5] Populate required paramete "Accounting-Record-Number".
    // Set the Accounting-Record-Number AVP.
    // The data type of Accounting-Record-Number is Unsigned32.
    // This AVP identifies this record within one session.
    // The AVP Code of Accounting-Record-Number is 485.
    AccountingRecordNumber arn(1u);
    acReq.setAccountingRecordNumber(arn);

    // The Accounting-Input-Octets AVP (AVP Code 363) is of type Unsigned64,
    // and contains the number of octets in IP packets received from the
    // user.  This AVP MUST be included in all Accounting-Request messages
    // and MAY be present in the corresponding Accounting-Answer messages as
    // well.
    AccountingInputOctets accInpOct(25u);
    acReq.setAccountingInputOctets(accInpOct);

    // The Accounting-Input-Packets (AVP Code 365) is of type Unsigned64 and
    // contains the number of IP packets received from the user.  This AVP
    // MUST be included in all Accounting-Request messages and MAY be
    // present in the corresponding Accounting-Answer messages as well.
    AccountingInputPackets accInpPac(5u);
    acReq.setAccountingInputPackets(accInpPac);

    // The Accounting-Output-Octets AVP (AVP Code 364) is of type Unsigned64
    // and contains the number of octets in IP packets sent to the user.
    // This AVP MUST be included in all Accounting-Request messages and MAY
    // be present in the corresponding Accounting-Answer messages as well.
    AccountingOutputOctets accOutOct(10u);
    acReq.setAccountingOutputOctets(accOutOct);

    // The Accounting-Output-Packets (AVP Code 366) is of type Unsigned64
    // and contains the number of IP packets sent to the user.  This AVP
    // MUST be included in all Accounting-Request messages and MAY be
    // present in the corresponding Accounting-Answer messages as well.
    AccountingOutputPackets accOutPac(2u);
    acReq.setAccountingOutputPackets(accOutPac);

    // The Acct-Multi-Session-Id AVP (AVP Code 50) is of type UTF8String,
    // following the format specified in Section 8.8.  The Acct-Multi-
    // Session-Id AVP is used to link together multiple related accounting
    // sessions, where each session would have a unique Session-Id, but the
    // same Acct-Multi-Session-Id AVP.  This AVP MAY be returned by the
    // Diameter server in an authorization answer, and MUST be used in all
    // accounting messages for the given session.
    AcctMultiSessionId acctMultiSessionId("xbz:143");
    acReq.setAcctMultiSessionId(acctMultiSessionId);

    // The Acct-Session-Time AVP (AVP Code 46) is of type Unsigned32 and indicates
    // the length of the current session in seconds.  This AVP MUST be
    // included in all Accounting-Request messages and MAY be present in the
    // corresponding Accounting-Answer messages as well.
    AcctSessionTime accSessionTime(555u);
    acReq.setAcctSessionTime(accSessionTime);

    // The MIP-Feature-Vector AVP (AVP Code 337) is of type Unsigned32 and
    // is added with flag values set by the foreign agent or by the AAAF
    // owned by the same administrative domain as the foreign agent.
    MIPFeatureVector  mfv(6789u);
    acReq.setMIPFeatureVector(mfv);

    // The MIP-Home-Agent-Address AVP (AVP Code 334) is of type Address and
    // contains the mobile node's home agent IP address.
    Address addrha(Address::IPV4, "192.168.1.2");
    MIPHomeAgentAddress mhaa(addrha);
    acReq.setMIPHomeAgentAddress(mhaa);

    // The MIP-Mobile-Node-Address AVP (AVP Code 333) is of type Address and
    // contains the mobile node's home IP address.
    Address addrmn(Address::IPV4, "192.168.1.1");
    MIPMobileNodeAddress mmna(addrmn);
    acReq.setMIPMobileNodeAddress(mmna);

    // Populate Optionals

    // Populate optional parameter "Acct-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication and
    // Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AcctApplicationId accid(3);
    acReq.setAcctApplicationId(accid);

    // Insert Vendor-Specific-Application-Id Data.
    // Set the Vendor-Specific-Application-Id AVP.
    // The data type of Vendor-Specific-Application-Id is Grouped.
    // This AVP is used to advertise support of a vendor-specific Diameter 
    // Application.
    // This AVP SHOULD be placed as close to the Diameter header
    // The AVP Code of Vendor-Specific-Application-Id is 260.
    VendorSpecificApplicationId vsi;

    // [2.2.2.1] Populate optional parameter "Vendor-Id".
    // Set the Vendor-ID AVP.
    // The data type of Vendor-ID is Unsigned32.
    // This AVP is used in order to know which vendor specific attributes may be
    // sent to the peer.
    // A Vendor-Id value of zero in this messages is reserved and indicates that 
    // this field is ignored.
    // The AVP Code of Vendor-ID is 266.
    VendorId vid(237);
    vsi.addVendorId(vid);

    // [2.2.2.2] Populate required parameter "Auth-Application-Id".
    // Set the Auth-Application-Id AVP.
    // The data type of Auth-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Authentication and
    // Authorization portion of an application
    // The AVP Code of Auth-Application-Id is 258.
    AuthApplicationId auth(25);
    vsi.setAuthApplicationId(auth);

    // [b1.2.2.3] Populate required parameter "Acct-Application-Id".
    // Set the Acct-Application-Id AVP.
    // The data type of Acct-Application-Id is Unsigned32.
    // This AVP is used in order to advertise support of the Accounting portion 
    // of an application.
    // The AVP Code of Acct-Application-Id is 259.
    AcctApplicationId acct(23);
    vsi.setAcctApplicationId(acct);

    acReq.setVendorSpecificApplicationId(vsi);

    // [2.2.3]Populate optional parameter "User-Name"
    // Set the User-Name AVP.
    // The data type of User-Name is UTF8String.
    // This AVP contains the User-Name.
    // The AVP Code of User-Name is 1.
    UserName un("good.customer");
    acReq.setUserName(un);

    // [2.2.4]Populate optional parameter "Accounting-Sub-Session-Id".
    // Set the Accounting-Sub-Session-Id AVP.
    // The data type of Accounting-Sub-Session-Id is Unsigned64.
    // This AVP contains the accounting sub-session identifier.
    // The AVP Code of Accounting-Sub-Session-Id is 287.
    AccountingSubSessionId assid(923456);
    acReq.setAccountingSubSessionId(assid);

    // [2.2.5]Populate optional parameter "Acct-Session-Id".
    // Set the Acct-Session-Id AVP.
    // The data type of Acct-Session-Id is OctetString.
    // This AVP is only used when RADIUS/Diameter translation occurs.
    // The AVP Code of Acct-Session-Id is 44.
    AcctSessionId asid("ACCT-00343");
    acReq.setAcctSessionId(asid);

    // [2.2.6]Populate optional parameter "Acct-Multi-Session-Id".
    // Set the Acct-Multi-Session-Id AVP.
    // The data type of Acct-Multi-Session-Id is UTF8String.
    // The Acct-Multi-Session-Id AVP is used to link together multiple related 
    // accounting sessions, where each session would have a unique Session-Id,
    // but the same Acct-Multi-Session-Id AVP.
    // The AVP Code of Acct-Multi-Session-Id is 50.
    AcctMultiSessionId amsid("ACCT-MULTI-35334");
    acReq.setAcctMultiSessionId(amsid);

    // [2.2.7]Populate optional parameter "Acct-Interim-Interval".
    // Set the Acct-Interim-Interval AVP.
    // The data type of Acct-Interim-Interval is Unsigned32.
    // The client uses information in this AVP to decide how and when to produce
    // accounting records
    // The AVP Code of Acct-Interim-Interval is 85.
    AcctInterimInterval aii(200);
    acReq.setAcctInterimInterval(aii);

    // [2.2.8]Populate optional parameter "Accounting-Realtime-Required"
    // Set the Accounting-Realtime-Required AVP.
    // The data type of Accounting-Realtime-Required is Enumerated.
    // The client uses information in this AVP to decide what to do if the     
    // sending of accounting records to the accounting server has been        
    // temporarily prevented .
    // The following values are supported
    // DELIVER_AND_GRANT                           1
    // GRANT_AND_STORE                             2
    // GRANT_AND_LOSE                              3 
    // The AVP Code of Accounting-Realtime-Required is 483.
    AccountingRealtimeRequired arr(AccountingRealtimeRequired::GRANT_AND_STORE);
    acReq.setAccountingRealtimeRequired(arr);
    
    // [2.2.9] Populate optional parameter "Origin-State-Id".
    // Set the Origin-State-Id AVP.
    // The data type of Origin-State-Id is Unsigned32.
    // This is a monotonically increasing value that is advanced whenever a 
    // Diameter entity restarts with loss of previous state
    // The AVP Code of Origin-State-Id is 278.
    OriginStateId origs(45);
    acReq.setOriginStateId(origs);

    // [2.2.10] Populate optional parameter "Event-Timestamp".
    // Set the Event-Timestamp AVP.
    // The data type of Event-Timestamp is Time.
    // This AVP is used to record the time that the reported event occurred, in 
    // seconds since January 1, 1900 00:00 UTC.
    // The AVP Code of Event-Timestamp is 55.

    acReq.setEventTimestamp(EventTimestamp(999));
    
    // [2.2.11] Populate optional parameter "Proxy-Info".
    // Set the Proxy-Info AVP.
    // The data type of Proxy-Info is Grouped.
    // This AVP gives information about proxy.
    // The AVP Code of Proxy-Info is 284    .

    //ProxyInfo pi1;

    // [2.2.11.1] Populate optional parameter "Proxy-Host".
    // Set the Proxy-Host AVP.
    // The data type of Proxy-Info is DiameterIdentity.
    // This AVP contains the identity of the host that added the Proxy-Info AVP.
    // The AVP Code of Proxy-Info is 280.
    //ProxyHost ph1("proxy1.abc.com");
    //pi1.setProxyHost(ph1);

    // [2.2.11.2] Populate optional parameter "Proxy-State".
    // Set the Proxy-State AVP.
    // The data type of Proxy-State is OctetString.
    // This AVP contains state local information, and MUST be treated as opaque
    //  data
    // The AVP Code of Proxy-State is 33.
    //ProxyState ps1("state0");
    //pi1.setProxyState(ps1);
    //acReq.addProxyInfo(pi1);

    // [2.2.12] Populate optional parameter "Route-Record".
    // Set the Route-Record AVP.
    // The data type of Route-Record is DiameterIdentity.
    // The identity added in this AVP MUST be the same as the one received in
    // the Origin-Host of the Capabilities Exchange message.
    // The AVP Code of Route-Record is 282.
    //RouteRecord rrec("abcdef");
    //acReq.addRouteRecord(rrec);

    // [3] Use appropriate application specific logic to Send object

    // To stop here in  console application.
    
    if (appMode == UNIT_TEST)
    cout << acReq << endl;
   
    SendDiaAppMsg(acReq, sIdx);
    MipStats::GetMipStats()->UpdateSendStats(acReq.getCommandCode(), ITS_TRUE);

    return (ITS_SUCCESS);
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends the Answer to the MipAccountingRequest
 *      made by the diameter stack. Create the MipAccountingAnswer
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
int SendMipAccountingAnswer(const CommandImpl * impl1)
{

    diameter::mip::AccountingAnswer acAns;

    // Create an instance of AAMobileNodeRequest class
    AccountingRequest acreq(*impl1);

    // Get some AVP values from Request
    const SessionId &sid1       = acreq.getSessionId();
    const OriginHost &oh1       = acreq.getOriginHost();
    const OriginRealm &or1      = acreq.getOriginRealm();
    const DestinationRealm &dr1 = acreq.getDestinationRealm();

    // 2. Create the instances of the classes describing the various
    //    AVPs' present in an LocationInfoRequest command and
    //    pass them by value to the corresponding data members set
    //    methods of the LocationInfoRequest object created
    //    in step 1.
    // [2.1.1] Set the Session-Id AVP.
    // The Session-Id AVP is used to identity a specific session
    // and must appear immediately following the Diameter header.
    // The AVP Code of Session-Id is 263
    // The data type of Session-Id is UTF8String.
    acAns.setSessionId(sid1);
    acAns.setSessionIndex(acreq.getSessionIndex());

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
    // The AVP Code of AVP is 268.
    // The data type of AVP is Unsigned32.
    ResultCode resultCode(2001u);
    acAns.setResultCode(resultCode);

    // [2.1] Set the Origin-Host AVP.
    // The Origin-Host AVP identifies the end-point that originated
    // the Diameter message.
    // The Origin-Host AVP must be present in all the Diameter
    // messages.
    // This AVP MIPOULD be placed as close to the Diameter header as
    // possible.
    // The relay agents must not modify this AVP.
    // The AVP Code of Origin-Host AVP is 264
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginHost originHost(GetOriginHost());
    acAns.setOriginHost(originHost);

    // [2.1] Set the Origin-Realm AVP.
    // The Origin-Realm AVP contains the realm of the originator of
    // any Diameter message and must be present in all the Diameter
    // messages.
    // The AVP Code of Origin-Host AVP is 296.
    // The data type of Origin-Host AVP is DiameterIdentity.
    OriginRealm originRealm(dr1.value());
    acAns.setOriginRealm(originRealm);

    // [2.1.2.4] Populate required paramete "Accounting-Record-Type".
    // Set the Accounting-Record-Type AVP.
    // The data type of Accounting-Record-Type is Enumerated.
    // This Avp contains the type of accounting record being sent.
    // The following values are currently defined
    // EVENT_RECORD                    1
    // START_RECORD                    2
    // The AVP Code of Accounting-Record-Type is 480.
    AccountingRecordType accr(AccountingRecordType::START_RECORD);
    acAns.setAccountingRecordType(accr);

    // [2.1.2.5] Populate required paramete "Accounting-Record-Number".
    // Set the Accounting-Record-Number AVP.
    // The data type of Accounting-Record-Number is Unsigned32.
    // This AVP identifies this record within one session.
    // The AVP Code of Accounting-Record-Number is 485.
    AccountingRecordNumber accrn(acreq.getAccountingRecordNumber());
    acAns.setAccountingRecordNumber(accrn);

   // OPTIONALS

    if (appMode == UNIT_TEST)
    cout<<acAns;

    SendDiaAppMsg(acAns, sIdx);
    MipStats::GetMipStats()->UpdateSendStats(acAns.getCommandCode(), ITS_FALSE);

    return (ITS_SUCCESS);
}

