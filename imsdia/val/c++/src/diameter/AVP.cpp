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
 *
 * LOG: $Log: AVP.cpp,v $
 * LOG: Revision 3.1.30.1  2012/10/01 09:01:08  rsanjay
 * LOG:  opendiameter code removal changes:bugzilla-id 300
 * LOG:
 * LOG: Revision 3.1  2008/03/31 10:33:29  nvijikumar
 * LOG: Start GA 3.0
 * LOG:
 * LOG: Revision 2.4  2008/03/27 12:12:01  hbhatnagar
 * LOG: Converting 2.1 branch to CURRENT
 * LOG:
 * LOG: Revision 2.2.10.1  2008/01/24 10:35:21  avinashks
 * LOG: Added generic support for Float32 and Float64 data types.
 * LOG:
 * LOG: Revision 2.2  2006/10/16 15:53:10  kamakshilk
 * LOG: Merging the itsval with val
 * LOG:
 * LOG: Revision 2.5  2006/10/05 05:54:02  tpanda
 * LOG: Changes related to Dictionary AVPs parsing and decoding
 * LOG:
 * LOG: Revision 2.4  2006/09/19 06:04:51  tpanda
 * LOG: Val is splitted. Encoding/Decoding functionality moved to vendor
 * LOG:
 * LOG: Revision 2.3  2006/09/14 15:23:53  tpanda
 * LOG: Optimising the code.. still a lot of things to do
 * LOG:
 * LOG: Revision 2.2  2006/09/13 16:01:04  tpanda
 * LOG: Changes made to make application decoding working
 * LOG:
 * LOG: Revision 2.1  2006/09/13 09:22:43  yranade
 * LOG: Start GA 1.1
 * LOG:
 * LOG: Revision 1.1  2006/09/12 15:56:17  tpanda
 * LOG: First baseline code for val supporting IntelliNet encoding/decoding
 * LOG:
 * LOG: Revision 1.4  2006/08/13 09:53:09  brianhu
 * LOG: New DEBUG_VERBOSE flag and lib initializer to control debugging logs
 * LOG:
 * LOG: Revision 1.3  2006/06/21 10:22:24  kamakshilk
 * LOG: Modification for Copyright info.
 * LOG:
 * LOG: Revision 1.2  2006/06/21 10:12:32  kamakshilk
 * LOG: included Copyright info.
 * LOG:
 * LOG:
 * ID: $Id: AVP.cpp,v 3.1.30.1 2012/10/01 09:01:08 rsanjay Exp $
 ****************************************************************************/
#ident "$Id: AVP.cpp,v 3.1.30.1 2012/10/01 09:01:08 rsanjay Exp $"

#include <diameter/AVP.h>
#include <diameter/Exceptions.h>

namespace diameter {

/*
AnyParser          AttributeName::_AnyParser;
Integer32Parser    AttributeName::_Integer32Parser;
Integer64Parser    AttributeName::_Integer64Parser;
Utf8stringParser   AttributeName::_Utf8stringParser;
OctetstringParser  AttributeName::_OctetstringParser;
DiamidentParser    AttributeName::_DiamidentParser;
DiamuriParser      AttributeName::_DiamuriParser;
IPFilterRuleParser AttributeName::_IpfilterRuleParser;
GroupedParser      AttributeName::_GroupedParser;
AddressParser      AttributeName::_AddressParser;
*/

std::map<unsigned int, AttributeName*> AttributeCodeMap::AttributeMap;
std::map<unsigned long long,  CommandAttribute::CommandAttributePair> CommandAttribute::_CommandAttributeMap;

struct AnyAvpBuilder: public AvpBuilder {
    virtual AVP *build(const AVPImpl *entry) const {
        throw UnknownTypeException(__FILE__, __LINE__, "Can't build AVP of unknown type");
    }
} _AnyAvpBuilder;

const AvpBuilder &AttributeName::AnyAvpBuilder = _AnyAvpBuilder;

//
// Implementation must define
//
//	const ImpBuilder &AttributeName::AnyImpBuilder;
//      const ImpBuilder &AttributeName::OctetStringImpBuilder;
//      const ImpBuilder &AttributeName::Integer32ImpBuilder;
//      const ImpBuilder &AttributeName::Integer64ImpBuilder;
//      const ImpBuilder &AttributeName::Unsigned32ImpBuilder;
//      const ImpBuilder &AttributeName::Unsigned64ImpBuilder;
//      const ImpBuilder &AttributeName::AddressImpBuilder;
//      const ImpBuilder &AttributeName::TimeImpBuilder;
//      const ImpBuilder &AttributeName::UTF8StringImpBuilder;
//      const ImpBuilder &AttributeName::IdentityImpBuilder;
//      const ImpBuilder &AttributeName::URIImpBuilder;
//      const ImpBuilder &AttributeName::IPFilterRuleImpBuilder;
//      const ImpBuilder &AttributeName::EnumeratedImpBuilder;
//      const ImpBuilder &AttributeName::GroupedImpBuilder;
//

const AttributeName AttributeName::AVP("AVP", AttributeName::AnyAvpBuilder, AttributeName::AnyImpBuilder);

class ImpBuilder{};
typedef ImpBuilder OctetStringImpBuilder;
typedef ImpBuilder Integer32ImpBuilder;
typedef ImpBuilder Integer64ImpBuilder;
typedef ImpBuilder Unsigned32ImpBuilder;
typedef ImpBuilder Unsigned64ImpBuilder;

/**
 * Added Typedefs for Float32 and Float64 ImpBuilder.
 */
typedef ImpBuilder Float32ImpBuilder;
typedef ImpBuilder Float64ImpBuilder;

typedef ImpBuilder AddressImpBuilder;
typedef ImpBuilder TimeImpBuilder;
typedef ImpBuilder UTF8StringImpBuilder;
typedef ImpBuilder IdentityImpBuilder;
typedef ImpBuilder URIImpBuilder;
typedef ImpBuilder IPFilterRuleImpBuilder;
typedef ImpBuilder EnumeratedImpBuilder;
typedef ImpBuilder GroupedImpBuilder;

ImpBuilder _AnyImpBuilder;
OctetStringImpBuilder _OctetStringImpBuilder;
Integer32ImpBuilder  _Integer32ImpBuilder;
Integer64ImpBuilder  _Integer64ImpBuilder; 
Unsigned32ImpBuilder _Unsigned32ImpBuilder;
Unsigned64ImpBuilder _Unsigned64ImpBuilder;

/**
 * Added Float32 and Float64 ImplBuilder
 */
Float32ImpBuilder _Float32ImpBuilder;
Float64ImpBuilder _Float64ImpBuilder;

AddressImpBuilder    _AddressImpBuilder;
TimeImpBuilder       _TimeImpBuilder;
UTF8StringImpBuilder _UTF8StringImpBuilder;
IdentityImpBuilder   _IdentityImpBuilder;
URIImpBuilder        _URIImpBuilder;
IPFilterRuleImpBuilder _IPFilterRuleImpBuilder;
EnumeratedImpBuilder   _EnumeratedImpBuilder;
GroupedImpBuilder      _GroupedImpBuilder;






const ImpBuilder &AttributeName::AnyImpBuilder          = _AnyImpBuilder;

const ImpBuilder &AttributeName::OctetStringImpBuilder  = _OctetStringImpBuilder;
const ImpBuilder &AttributeName::Integer32ImpBuilder    = _Integer32ImpBuilder;
const ImpBuilder &AttributeName::Integer64ImpBuilder    = _Integer64ImpBuilder;
const ImpBuilder &AttributeName::Unsigned32ImpBuilder   = _Unsigned32ImpBuilder;
const ImpBuilder &AttributeName::Unsigned64ImpBuilder   = _Unsigned64ImpBuilder;

/**
 * Initializing the Float32 and Float64 ImplBuilder.
 */
const ImpBuilder &AttributeName::Float32ImpBuilder   = _Float32ImpBuilder;
const ImpBuilder &AttributeName::Float64ImpBuilder   = _Float64ImpBuilder;

const ImpBuilder &AttributeName::AddressImpBuilder      = _AddressImpBuilder;
const ImpBuilder &AttributeName::TimeImpBuilder         = _TimeImpBuilder;
const ImpBuilder &AttributeName::UTF8StringImpBuilder   = _UTF8StringImpBuilder;
const ImpBuilder &AttributeName::IdentityImpBuilder     = _IdentityImpBuilder;
const ImpBuilder &AttributeName::URIImpBuilder          = _URIImpBuilder;
const ImpBuilder &AttributeName::IPFilterRuleImpBuilder = _IPFilterRuleImpBuilder;
const ImpBuilder &AttributeName::EnumeratedImpBuilder   = _EnumeratedImpBuilder;
const ImpBuilder &AttributeName::GroupedImpBuilder      = _GroupedImpBuilder;



/////////////////////////
// Library Initializer //
// ------------------- //
//  * init logging     //
/////////////////////////
 
 
class LibraryInitializer {
public:
    LibraryInitializer() {
#ifdef DEBUG
#ifdef DEBUG_VERBOSE
    if (std::getenv("DEBUG_VALCPP") != 0) {
        DBG_SET(VALCPP, std::cerr);
    }
#endif
#endif
    }
};
 
static LibraryInitializer _initializer;

}
