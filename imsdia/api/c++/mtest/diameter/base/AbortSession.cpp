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
 * LOG: $Log: AbortSession.cpp,v $
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
 * ID: $Id: AbortSession.cpp,v 3.1 2008/03/31 10:33:07 nvijikumar Exp $
 *
 ***************************************************************************/
#ident "$Id: AbortSession.cpp,v 3.1 2008/03/31 10:33:07 nvijikumar Exp $"

#include <time.h>
#include <sys/timeb.h>

#include <AbortSession.h>

using namespace diameter;
using namespace diameter::base;
using namespace std;

string 
GetUniqueSessionId(string sender)
{
     // Create a Unique Session-Id.
    string sessionId;
    char tbuff[256];
    char tct[20];
    struct timeb now;
    ftime(&now);
    static int cnt = 0;

    sprintf(tbuff, "%d", (now.time + now.millitm));
    sprintf(tct, "%d", cnt);
    sessionId = sender + ";" + tbuff + ";" + tct;

    cout << "sessionId = " << sessionId << endl;
    cnt++;

    return sessionId;

} 

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  How to Build a Abort Session Request                                   //
//                                                                         //
//  o   Create AbortSessionRequest object.                                 //
//                                                                         //
//  o   Insert data step by step in the created AbortSessionRequest object //
//      (i.e. populate various parameters of the AbortSessionRequest       //
//      operation argument).                                               //
//                                                                         //
//  o   Encode the AbortSessionRequest object to produce an                //
//     AbortSessionRequest encoded value.                                  //
/////////////////////////////////////////////////////////////////////////////

int EncodeAbortSessionReq()
{

// [1] Create AbortSessionRequest object.

    AbortSessionRequest asr(false, false);

// [2] Insert data in the created CapabilitiesExchangeRequest object
    
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
    asr.setSessionId(sid);

// [2.1.2] Populate required Mandatories.

// [2.1.2.1] Populate required paramete "Origin-Host".
// Set the Origin-Host AVP.
// The data type of Origin-Host is DiameterIdentity
// This AVP identifies the endpoint that originated the Diameter message
// This AVP SHOULD be placed as close to the Diameter header
// The AVP Code of Origin-Host is 264.
	OriginHost orig("aaa.abc.com");
    asr.setOriginHost(orig);

// [2.1.2.2] Populate required paramete "Origin-Realm".
// Set the Origin-Realm AVP.
// The data type of Origin-Realm is DiameterIdentity.
// This AVP contains the Realm of the originator of any Diameter message.
// This AVP SHOULD be placed as close to the Diameter header.
// The AVP Code of Origin-Realm is 296.
	OriginRealm origr("abc.com");
    asr.setOriginRealm(origr);

// [2.1.2.3] Populate required paramete "Destination-Realm".
// Set the Destination-Realm AVP.
// The data type of Destination-Realm is DiameterIdentity.
// This AVP contains the Realm the message is to be routed to.
// This AVP SHOULD be placed as close to the Diameter header.
// The AVP Code of Destination-Realm is 283.
	DestinationRealm destr("xyz.com");
    asr.setDestinationRealm(destr);

// [2.1.2.4] Populate required paramete "Destination-Host".
// Set the Destination-Host AVP.
// The data type of Destination-Host is DiameterIdentity
// This AVP identifies the endpoint where  the Diameter message is destinated
// This AVP SHOULD be placed as close to the Diameter header
// The AVP Code of Destination-Host is 293.
	DestinationHost desth("users.xyz.com");
    asr.setDestinationHost(desth);

// [2.1.2.5] Populate required parameter "Auth-Application-Id".
// Set the Auth-Application-Id AVP.
// The data type of Auth-Application-Id is Unsigned32.
// This AVP is used in order to advertise support of the Authentication and
// Authorization portion of an application
// The AVP Code of Auth-Application-Id is 258.
	AuthApplicationId authid((Unsigned32)41);
    asr.setAuthApplicationId(authid);
      
// [2.2] Populate Optionals

// [2.2.1] Populate Optional paramete "User-Name".
// Set the User-Name AVP.
// The data type of User-Name is UTF8String.
// This AVP contains the User-Name.
// The AVP Code of User-Name is 1.
	UserName un("john.smith");
    asr.setUserName(un);

// [2.2.2] Populate optional parameter "Origin-State-Id".
// Set the Origin-State-Id AVP.
// The data type of Origin-State-Id is Unsigned32.
// This is a monotonically increasing value that is advanced whenever a
// Diameter entity restarts with loss of previous state
// The AVP Code of Origin-State-Id is 278.
	OriginStateId org(41);
    asr.setOriginStateId(org);

// [2.2.3] Populate optional parameter "Proxy-Info". 
// Set the Proxy-Info AVP.
// The data type of Proxy-Info is Grouped.
// This AVP gives information about proxy.
// The AVP Code of Proxy-Info is 284.

    ProxyInfo pi1;

// [2.2.3.1] Populate optional parameter "Proxy-Host".
// Set the Proxy-Host AVP.
// The data type of Proxy-Info is DiameterIdentity.
// This AVP contains the identity of the host that added the Proxy-Info AVP.
// The AVP Code of Proxy-Info is 280.
	ProxyHost ph1("proxy1.abc.com");
    pi1.setProxyHost(ph1);

// [2.2.3.2] Populate optional parameter "Proxy-State".
// Set the Proxy-State AVP.
// The data type of Proxy-State is OctetString.
// This AVP contains state local information, and MUST be treated as opaque
//  data
// The AVP Code of Proxy-State is 33.
	ProxyState ps1("state0");
    pi1.setProxyState(ps1);
    asr.addProxyInfo(pi1);

// [2.2.4] Populate optional parameter "Route-Record".
// Set the Route-Record AVP.
// The data type of Route-Record is DiameterIdentity.
// The identity added in this AVP MUST be the same as the one received in
// the Origin-Host of the Capabilities Exchange message.
// The AVP Code of Route-Record is 282.
	RouteRecord rrec("123.abc.com");
    asr.addRouteRecord(rrec);
  
// [3] Use appropriate application specific logic to Send object

// To stop here in  console application.

    std::cout << asr << std::endl;

   
}

