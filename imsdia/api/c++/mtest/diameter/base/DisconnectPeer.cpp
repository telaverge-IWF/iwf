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
 * LOG: $Log: DisconnectPeer.cpp,v $
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
 * ID: $Id: DisconnectPeer.cpp,v 3.1 2008/03/31 10:33:07 nvijikumar Exp $
 *
 ***************************************************************************/
#ident "$Id: DisconnectPeer.cpp,v 3.1 2008/03/31 10:33:07 nvijikumar Exp $"
#include <DisconnectPeer.h>

using namespace diameter;
using namespace diameter::base;

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//   How to Build a Disconnect Peer Request.                               //
//                                                                         //
//  o   Create  DisconnectPeerRequest object.                              //
//                                                                         //
//  o   Insert data step by step in the created DisconnectPeerRequest      //
//       object                                                            //
//      (i.e. populate various parameters of the DisconnectPeerRequest     //
//      operation argument).                                               //
//                                                                         //
//  o   Encode the DisconnectPeerRequest object to produce an              //
//     DisconnectPeerRequest encoded value.                                //
/////////////////////////////////////////////////////////////////////////////

int EncodeDisconnectPeerReq()
{
// [1] Create Disconnect Peer Request object.

    DisconnectPeerRequest dpr(false, false);

// [2] Insert data in the created CapabilitiesExchangeRequest object.

// [2.1] Populate Mandatories.

// [2.1.1] Populate Fixed Mandatories.

// [2.1.2] Populate required Mandatories.

// [2.1.2.1] Populate required paramete "Origin-Host".
// Set the Origin-Host AVP.
// The data type of Origin-Host is DiameterIdentity
// This AVP identifies the endpoint that originated the Diameter message
// This AVP SHOULD be placed as close to the Diameter header
// The AVP Code of Origin-Host is 264.
	OriginHost origh("aaa.abc.com");
    dpr.setOriginHost(origh);

// [2.1.2.2] Populate required paramete "Origin-Realm".
// Set the Origin-Realm AVP.
// The data type of Origin-Realm is DiameterIdentity.
// This AVP contains the Realm of the originator of any Diameter message.
// This AVP SHOULD be placed as close to the Diameter header.
// The AVP Code of Origin-Realm is 296.
	OriginRealm origr("abc.com");
    dpr.setOriginRealm(origr);

// [2.1.2.3] Populate required parameter "Disconnect-Cause".
// Set the Disconnect-Cause AVP.
// The data type of Disconnect-Cause is Enumerated.
// This AVP to inform the peer of the reason for its intention to shutdown 
// the transport connection.
// The following values are supported:
// REBOOTING                         0
// BUSY                              1
// DO_NOT_WANT_TO_TALK_TO_YOU        2
// The AVP Code of Disconnect-Cause is 273.
	DisconnectCause discause(DisconnectCause::REBOOTING);
    dpr.setDisconnectCause(discause);


// [2.2] Populate Optionals

// [3] Use appropriate application specific logic to Send object
   
// To stop here in  console application
 
    std::cout << dpr << std::endl;
}
