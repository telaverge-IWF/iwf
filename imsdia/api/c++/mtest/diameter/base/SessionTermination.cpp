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
 * LOG: $Log: SessionTermination.cpp,v $
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
 * ID: $Id: SessionTermination.cpp,v 3.1 2008/03/31 10:33:07 nvijikumar Exp $
 *
 ***************************************************************************/
#ident "$Id: SessionTermination.cpp,v 3.1 2008/03/31 10:33:07 nvijikumar Exp $"
#include <SessionTermination.h>

using namespace diameter;
using namespace diameter::base;

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//   How to Build a Session Termination Request                            //
//                                                                         //
//  o   Create SessionTerminationRequest object.                           //
//                                                                         //
//  o   Insert data step by step in the created SessionTerminationRequest  //
//       object                                                            //
//      (i.e. populate various parameters of the SessionTerminationRequest //
//      operation argument).                                               //
//                                                                         //
//  o   Encode the SessionTerminationRequest object to produce an          //
//     SessionTerminationRequest encoded value.                            //
/////////////////////////////////////////////////////////////////////////////

int EncodeSessionTerminationReq() 
{
// [1] Create SessionTerminationRequest object. 

    SessionTerminationRequest str(false, false);

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
	SessionId sId("12345");
    str.setSessionId(sId);

// [2.1.2] Populate required Mandatories.

// [2.1.2.1] Populate required paramete "Origin-Host".
// Set the Origin-Host AVP.
// The data type of Origin-Host is DiameterIdentity
// This AVP identifies the endpoint that originated the Diameter message
// This AVP SHOULD be placed as close to the Diameter header
// The AVP Code of Origin-Host is 264.
	OriginHost origh("aaa.abc.com");
    str.setOriginHost(origh);

// [2.1.2.2] Populate required paramete "Origin-Realm".
// Set the Origin-Realm AVP.
// The data type of Origin-Realm is DiameterIdentity.
// This AVP contains the Realm of the originator of any Diameter message.
// This AVP SHOULD be placed as close to the Diameter header.
// The AVP Code of Origin-Realm is 296.
	OriginRealm origr("abc.com");
    str.setOriginRealm(origr);

// [2.1.2.3] Populate required paramete "Destination-Realm".
// Set the Destination-Realm AVP.
// The data type of Destination-Realm is DiameterIdentity.
// This AVP contains the Realm the message is to be routed to.
// This AVP SHOULD be placed as close to the Diameter header.
// The AVP Code of Destination-Realm is 283.
	DestinationRealm desr("xyz.com");
    str.setDestinationRealm(desr);

// [2.1.2.4] Populate required parameter "Auth-Application-Id".
// Set the Auth-Application-Id AVP.
// The data type of Auth-Application-Id is Unsigned32.
// This AVP is used in order to advertise support of the Authentication and
// Authorization portion of an application
// The AVP Code of Auth-Application-Id is 258.
	AuthApplicationId authid((Unsigned32)0);
    str.setAuthApplicationId(authid);

// [2.1.2.5] Populate required parameter "Termination-Cause".
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
	TerminationCause termc(TerminationCause::DIAMETER_BAD_ANSWER);
    str.setTerminationCause(termc);

// [2.2] Populate Optionals

// [2.2.1] Populate Optional paramete "User-Name".
// Set the User-Name AVP.
// The data type of User-Name is UTF8String.
// This AVP contains the User-Name.
// The AVP Code of User-Name is 1.
	UserName un("john.smith");
    str.setUserName(un);

// [2.2.2] Populate optional paramete "Destination-Host".
// Set the Destination-Host AVP.
// The data type of Destination-Host is DiameterIdentity
// This AVP identifies the endpoint where  the Diameter message is destinated
// This AVP SHOULD be placed as close to the Diameter header
// The AVP Code of Destination-Host is 293.
	DestinationHost desh("users.xyz.com");
    str.setDestinationHost(desh);

// [2.2.3] Populate optional parameter "Class".
// Set the Class AVP.
// The data type of Class is OctetString.
// This AVP is used to by Diameter servers to return state information to the
// access device.
// The AVP Code of Class is 25.
	Class class1("business");
    str.addClass(class1);
	Class class2("residential");
    str.addClass(class2);

// [2.2.4] Populate optional parameter "Origin-State-Id".
// Set the Origin-State-Id AVP.
// The data type of Origin-State-Id is Unsigned32.
// This is a monotonically increasing value that is advanced whenever a 
// Diameter entity restarts with loss of previous state
// The AVP Code of Origin-State-Id is 278.
	OriginStateId origsid(41);
    str.setOriginStateId(origsid);

// [2.2.5] Populate optional parameter "Proxy-Info".
// Set the Proxy-Info AVP.
// The data type of Proxy-Info is Grouped.
// This AVP gives information about proxy.
// The AVP Code of Proxy-Info is 284.

    ProxyInfo pi1;

// [2.2.5.1] Populate optional parameter "Proxy-Host".
// Set the Proxy-Host AVP.
// The data type of Proxy-Info is DiameterIdentity.
// This AVP contains the identity of the host that added the Proxy-Info AVP.
// The AVP Code of Proxy-Info is 280.
	ProxyHost ph1("proxy1.abc.com");
    pi1.setProxyHost(ph1);

// [2.2.5.2] Populate optional parameter "Proxy-State".
// Set the Proxy-State AVP.
// The data type of Proxy-State is OctetString.
// This AVP contains state local information, and MUST be treated as opaque 
//  data
// The AVP Code of Proxy-State is 33.
	ProxyState ps1("state0");
    pi1.setProxyState(ps1);

// [2.2.6] Populate optional parameter "Route-Record".
// Set the Route-Record AVP.
// The data type of Route-Record is DiameterIdentity.
// The identity added in this AVP MUST be the same as the one received in
// the Origin-Host of the Capabilities Exchange message.
// The AVP Code of Route-Record is 282.
	RouteRecord rrec("abcdef");
    str.addRouteRecord(rrec);

// [3] Use appropriate application specific logic to Send object

// To stop here in  console application.

    std::cout << str << std::endl;
}

