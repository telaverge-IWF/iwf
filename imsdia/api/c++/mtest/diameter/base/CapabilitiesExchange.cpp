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
 * LOG: $Log: CapabilitiesExchange.cpp,v $
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
 * ID: $Id: CapabilitiesExchange.cpp,v 3.1 2008/03/31 10:33:07 nvijikumar Exp $
 *
 ***************************************************************************/
#ident "$Id: CapabilitiesExchange.cpp,v 3.1 2008/03/31 10:33:07 nvijikumar Exp $"
#include <CapabilitiesExchange.h>

using namespace diameter;
using namespace diameter::base;

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  How to Build a Capabilities Exchange Request                           //
//                                                                         //
//  o   Create CapabilitiesExchangeRequest object.                         //
//                                                                         //
//  o   Insert data step by step in the created CapabilitiesExchangeRequest//
//       object.                                                           //
//     (i.e. populate various parameters of the CapabilitiesExchangeRequest//
//      operation argument).                                               //
//                                                                         //
//  o   Encode the CapabilitiesExchangeRequest object to produce an        //
//    CapabilitiesExchangeRequest encoded value.                           //
/////////////////////////////////////////////////////////////////////////////

int EncodeCapabilitiesExchangeReq()
{
// [1] Create CapabilitiesExchangeRequest object.
    CapabilitiesExchangeRequest cer(false, false);
   
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
	OriginHost origh("456.abc.com");
   cer.setOriginHost(origh);

// [2.1.2.2] Populate required paramete "Origin-Realm".
// Set the Origin-Realm AVP.
// The data type of Origin-Realm is DiameterIdentity.
// This AVP contains the Realm of the originator of any Diameter message.
// This AVP SHOULD be placed as close to the Diameter header.
// The AVP Code of Origin-Realm is 296.
	OriginRealm origr("abc.com"); 
   cer.setOriginRealm(origr);


// [2.1.2.3] Populate required paramete "Host-IP-Address".
// Set the Host-IP-Address AVP.
// The data type of Host-IP-Address is Address.
// This AVP is used to inform a Diameter peer of the sender's IP address.
// The AVP Code of Host-IP-Address is 257.
	Address addr(Address::IPV4, "123.456.7.89");
	HostIPAddress hip(addr);
    cer.addHostIPAddress(hip);

// [2.1.2.4] Populate required paramete "Vendor-ID".
// Set the Vendor-ID AVP.
// The data type of Vendor-ID is Unsigned32.
// This AVP is used in order to know which vendor specific attributes may be
// sent to the peer.
// A Vendor-Id value of zero in this messages is reserved and indicates that
// this field is ignored.	 
// The AVP Code of Vendor-ID is 266.
	VendorId vid(10);
    cer.setVendorId(vid);

// [2.1.2.5] Populate required paramete "Product-Name".
// Set the Product-Name AVP.
// The data type of Product-Name is UTF8String.
// This AVP contains the vendor assigned name for the product.
// The Product-Name AVP SHOULD remain constant across firmware revisions for
// the same product.
// The AVP Code of Product-Name is 269.
	ProductName pname("AAA-Router");
    cer.setProductName(pname);
                 
// [2.2] Populate Optionals

// [2.2.1] Populate optional parameter "Origin-State-Id".
// Set the Origin-State-Id AVP.
// The data type of Origin-State-Id is Unsigned32.
// This is a monotonically increasing value that is advanced whenever a 
// Diameter entity restarts with loss of previous state
// The AVP Code of Origin-State-Id is 278.
	OriginStateId orgid(41);
    cer.setOriginStateId(orgid);

// [2.2.2] Populate optional parameter "Supported-Vendor-Id".
// Set the Supported-Vendor-Id AVP.
// The data type of Supported-Vendor-Id isUnsigned32.
// This AVP is used in order to inform the peer that the sender supports the
// vendor-specific AVPs defined by the vendor identified in This AVP.
// The AVP Code of Supported-Vendor-Id is 265.
	SupportedVendorId svid(53);
    cer.addSupportedVendorId(svid);

// [2.2.3] Populate optional parameter "Auth-Application-Id".
// Set the Auth-Application-Id AVP.
// The data type of Auth-Application-Id is Unsigned32.
// This AVP is used in order to advertise support of the Authentication and
// Authorization portion of an application
// The AVP Code of Auth-Application-Id is 258.
	AuthApplicationId aaid((Unsigned32)0);
    cer.addAuthApplicationId(aaid);

// [2.2.4] Populate optional parameter "Inband-Security-Id".
// Set the Inband-Security-Id AVP.
// The data type of Inband-Security-Id is Unsigned32.
// This AVP is used in order to advertise support of the Security portion of
// the application.
// Currently, the following values are supported: 
// NO_INBAND_SECURITY                0
// TLS                               1
// The AVP Code of Inband-Security-Id is 299.
	InbandSecurityId isid(2);
    cer.addInbandSecurityId(isid);

// [2.2.4] Populate optional parameter "Acct-Application-Id".
// Set the Acct-Application-Id AVP.
// The data type of Acct-Application-Id is Unsigned32.
// This AVP is used in order to advertise support of the Accounting portion 
// of an application.
// The AVP Code of Acct-Application-Id is 259.
	AcctApplicationId actid(5);
    cer.addAcctApplicationId(actid);

// [2.2.5] Populate optional parameter "Vendor-Specific-Application-Id".
// Set the Vendor-Specific-Application-Id AVP.
// The data type of Vendor-Specific-Application-Id is Grouped.
// This AVP is used to advertise support of a vendor-specific Diameter
// Application
// This AVP SHOULD be placed as close to the Diameter header
// The AVP Code of Vendor-Specific-Application-Id is 260.

    VendorSpecificApplicationId vsi;

// [2.2.5.1] Popolate optional parameter "Vendor-Id".
// Set the Vendor-ID AVP.
// The data type of Vendor-ID is Unsigned32.
// This AVP is used in order to know which vendor specific attributes may be
// sent to the peer.
// A Vendor-Id value of zero in this messages is reserved and indicates that 
// this field is ignored.
// The AVP Code of Vendor-ID is 266.
	VendorId venid(237);
    vsi.addVendorId(venid);

// [2.2.5.2] Populate required parameter "Auth-Application-Id".
// Set the Auth-Application-Id AVP.
// The data type of Auth-Application-Id is Unsigned32.
// This AVP is used in order to advertise support of the Authentication and
// Authorization portion of an application
// The AVP Code of Auth-Application-Id is 258.
	AuthApplicationId aapid(25);
    vsi.setAuthApplicationId(aapid);

// [2.2.5.3] Populate required parameter "Acct-Application-Id".
// Set the Acct-Application-Id AVP.
// The data type of Acct-Application-Id is Unsigned32.
// This AVP is used in order to advertise support of the Accounting portion 
// of an application.
// The AVP Code of Acct-Application-Id is 259.
	AcctApplicationId accid(23);
   vsi.setAcctApplicationId(accid);

    cer.addVendorSpecificApplicationId(vsi);

// [2.2.6] Populate optional parameter "Firmware-Revision".
// Set the Firmware-Revision AVP.
// The data type of Firmware-Revision is Unsigned32.
// This Avp is used to inform a Diameter peer of the firmware revision of the
// issuing device
// The AVP Code of Firmware-Revision is 267.
	FirmwareRevision frev(1);
    cer.setFirmwareRevision(frev);

// [3] Use appropriate application specific logic to Send object

// To stop here in  console application
    std::cout << cer << std::endl;

}



