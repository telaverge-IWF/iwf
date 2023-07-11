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
 * LOG: $Log: testAccounting.cpp,v $
 * LOG: Revision 3.1  2008/03/31 10:33:07  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:41  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.2  2006/02/28 13:47:04  nvijikumar
 * LOG: Updates after code changes in val and api.
 * LOG:
 * LOG: Revision 1.1.1.1  2006/02/16 12:16:44  yranade
 * LOG: Create baseline imsdia project in CVS.
 * LOG:
 *
 * ID: $Id: testAccounting.cpp,v 3.1 2008/03/31 10:33:07 nvijikumar Exp $
 *
 ***************************************************************************/
#ident "$Id: testAccounting.cpp,v 3.1 2008/03/31 10:33:07 nvijikumar Exp $"
#include <iostream.h>
#include <Accounting.h>

using namespace std;
using namespace diameter;
using namespace diameter::base;

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//   How to Build a Accounting Request                                     //
//                                                                         //
//  o   Create AccountingRequest object.                                   //
//                                                                         //
//  o   Insert data step by step in the created AccountingRequest          //
//      object                                                             //
//      (i.e. populate various parameters of the AccountingRequest         //
//      operation argument).                                               //
//                                                                         //
//  o   Encode the AccountingRequest object to produce an                  //
//     AccountingRequest encoded value.                                    //
/////////////////////////////////////////////////////////////////////////////

int EncodeAccountingReq()
{

// [1] Create CapabilitiesExchangeRequest object.

    AccountingRequest acr(false, false);

// [2] Insert data in the created CapabilitiesExchangeRequest object.

// [2.1] Populate Mandatories.
                              
// [2.1.1] Populate Fixed Mandatories.

// [2.1.1.1] Populate Fixed paramete "Session-Id".
// Set the Session-Id AVP.
// The data type of Session-Id is UTF8String.
// This AVP is used to identify a specific session.
// The Session-Id SHOULD appear immediately following the Diameter Header.
// The Session-Id MUST be globally and eternally unique.
// The AVP Code of Session-Id is 263.
	SessionId sid("12345");
    acr.setSessionId(sid);

// [2.1.2] Populate required Mandatories.

// [2.1.2.1] Populate required paramete "Origin-Host".
// Set the Origin-Host AVP.
// The data type of Origin-Host is DiameterIdentity
// This AVP identifies the endpoint that originated the Diameter message
// This AVP SHOULD be placed as close to the Diameter header
// The AVP Code of Origin-Host is 264.
	OriginHost origh("aaa.abc.com");
    acr.setOriginHost(origh);

// [2.1.2.2] Populate required paramete "Origin-Realm".
// Set the Origin-Realm AVP.
// The data type of Origin-Realm is DiameterIdentity.
// This AVP contains the Realm of the originator of any Diameter message.
// This AVP SHOULD be placed as close to the Diameter header.
// The AVP Code of Origin-Realm is 296.
	OriginRealm origr("cdeabc.com");
    acr.setOriginRealm(origr);

// [2.1.2.3] Populate required paramete "Destination-Realm".
// Set the Destination-Realm AVP.
// The data type of Destination-Realm is DiameterIdentity.
// This AVP contains the Realm the message is to be routed to.
// This AVP SHOULD be placed as close to the Diameter header.
// The AVP Code of Destination-Realm is 283.
	DestinationRealm desr("xyz.com");
    acr.setDestinationRealm(desr);

// [2.1.2.4] Populate required paramete "Accounting-Record-Type".
// Set the Accounting-Record-Type AVP.
// The data type of Accounting-Record-Type is Enumerated.
// This Avp contains the type of accounting record being sent.
// The following values are currently defined
// EVENT_RECORD                    1
// START_RECORD                    2 
// The AVP Code of Accounting-Record-Type is 480.
	AccountingRecordType accr(AccountingRecordType::START_RECORD);
    acr.setAccountingRecordType(accr);
    
// [2.1.2.5] Populate required paramete "Accounting-Record-Number".
// Set the Accounting-Record-Number AVP.
// The data type of Accounting-Record-Number is Unsigned32.
// This AVP identifies this record within one session.
// The AVP Code of Accounting-Record-Number is 485.
	AccountingRecordNumber arn(1);
    acr.setAccountingRecordNumber(arn);


// [2.2] Populate Optionals

// [2.2.1] Populate optional parameter "Acct-Application-Id".
// Set the Auth-Application-Id AVP.
// The data type of Auth-Application-Id is Unsigned32.
// This AVP is used in order to advertise support of the Authentication and
// Authorization portion of an application
// The AVP Code of Auth-Application-Id is 258.
	AcctApplicationId accid(3);
    acr.setAcctApplicationId(accid);

// [2.2.2] Insert Vendor-Specific-Application-Id Data.
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

// [1.2.2.3] Populate required parameter "Acct-Application-Id".
// Set the Acct-Application-Id AVP.
// The data type of Acct-Application-Id is Unsigned32.
// This AVP is used in order to advertise support of the Accounting portion 
// of an application.
// The AVP Code of Acct-Application-Id is 259.
	AcctApplicationId acct(23);
   vsi.setAcctApplicationId(acct);

   //acr.addVendorSpecificApplicationId(vsi);

// [2.2.3]Populate optional parameter "User-Name"
// Set the User-Name AVP.
// The data type of User-Name is UTF8String.
// This AVP contains the User-Name.
// The AVP Code of User-Name is 1.
	UserName un("good.customer");
    acr.setUserName(un);

// [2.2.4]Populate optional parameter "Accounting-Sub-Session-Id".
// Set the Accounting-Sub-Session-Id AVP.
// The data type of Accounting-Sub-Session-Id is Unsigned64.
// This AVP contains the accounting sub-session identifier.
// The AVP Code of Accounting-Sub-Session-Id is 287.
	AccountingSubSessionId assid(923456);
    acr.setAccountingSubSessionId(assid);

// [2.2.5]Populate optional parameter "Acct-Session-Id".
// Set the Acct-Session-Id AVP.
// The data type of Acct-Session-Id is OctetString.
// This AVP is only used when RADIUS/Diameter translation occurs.
// The AVP Code of Acct-Session-Id is 44.
	AcctSessionId asid("ACCT-00343");
   acr.setAcctSessionId(asid);

// [2.2.6]Populate optional parameter "Acct-Multi-Session-Id".
// Set the Acct-Multi-Session-Id AVP.
// The data type of Acct-Multi-Session-Id is UTF8String.
// The Acct-Multi-Session-Id AVP is used to link together multiple related 
// accounting sessions, where each session would have a unique Session-Id,
// but the same Acct-Multi-Session-Id AVP.
// The AVP Code of Acct-Multi-Session-Id is 50.
	AcctMultiSessionId amsid("ACCT-MULTI-35334");
    acr.setAcctMultiSessionId(amsid);

// [2.2.7]Populate optional parameter "Acct-Interim-Interval".
// Set the Acct-Interim-Interval AVP.
// The data type of Acct-Interim-Interval is Unsigned32.
// The client uses information in this AVP to decide how and when to produce
// accounting records
// The AVP Code of Acct-Interim-Interval is 85.
	AcctInterimInterval aii(200);
    acr.setAcctInterimInterval(aii);

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
    acr.setAccountingRealtimeRequired(arr);
    
// [2.2.9] Populate optional parameter "Origin-State-Id".
// Set the Origin-State-Id AVP.
// The data type of Origin-State-Id is Unsigned32.
// This is a monotonically increasing value that is advanced whenever a 
// Diameter entity restarts with loss of previous state
// The AVP Code of Origin-State-Id is 278.
	OriginStateId origs(45);
    acr.setOriginStateId(origs);

// [2.2.10] Populate optional parameter "Event-Timestamp".
// Set the Event-Timestamp AVP.
// The data type of Event-Timestamp is Time.
// This AVP is used to record the time that the reported event occurred, in 
// seconds since January 1, 1900 00:00 UTC.
// The AVP Code of Event-Timestamp is 55.

    //acr.setEventTimestamp(EventTimestamp(999));
    
// [2.2.11] Populate optional parameter "Proxy-Info".
// Set the Proxy-Info AVP.
// The data type of Proxy-Info is Grouped.
// This AVP gives information about proxy.
// The AVP Code of Proxy-Info is 284.

    ProxyInfo pi1;

// [2.2.11.1] Populate optional parameter "Proxy-Host".
// Set the Proxy-Host AVP.
// The data type of Proxy-Info is DiameterIdentity.
// This AVP contains the identity of the host that added the Proxy-Info AVP.
// The AVP Code of Proxy-Info is 280.
	ProxyHost ph1("proxy1.abc.com");
    pi1.setProxyHost(ph1);

// [2.2.11.2] Populate optional parameter "Proxy-State".
// Set the Proxy-State AVP.
// The data type of Proxy-State is OctetString.
// This AVP contains state local information, and MUST be treated as opaque
//  data
// The AVP Code of Proxy-State is 33.
	ProxyState ps1("state0");
    pi1.setProxyState(ps1);
    acr.addProxyInfo(pi1);

// [2.2.12] Populate optional parameter "Route-Record".
// Set the Route-Record AVP.
// The data type of Route-Record is DiameterIdentity.
// The identity added in this AVP MUST be the same as the one received in
// the Origin-Host of the Capabilities Exchange message.
// The AVP Code of Route-Record is 282.
	RouteRecord rrec("abcdef");
    acr.addRouteRecord(rrec);

// [3] Use appropriate application specific logic to Send object

// To stop here in  console application.

    std::cout << acr << std::endl;
}

