///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//          Copyright (c) 1999 - 2002 IntelliNet Technologies, Inc.          //
//                            All Rights Reserved.                           //
//              Manufactured in the United States of America.                //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
//                                                                           //
//   This product and related documentation is protected by copyright and    //
//   distributed under licenses restricting its use, copying, distribution   //
//   and decompilation.  No part of this product or related documentation    //
//   may be reproduced in any form by any means without prior written        //
//   authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                           //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//   government is subject to restrictions as set forth in subparagraph      //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Contract: Internal                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: AsnRelativeOid.cpp,v $
// LOG: Revision 9.2  2007/01/10 11:15:06  yranade
// LOG: Merge changes from 6.5.3 and Lucent branches
// LOG:
// LOG: Revision 9.1.10.1  2005/09/06 09:17:20  mmanikandan
// LOG: Support for ASN.1 PER.
// LOG:
// LOG: Revision 9.1  2005/03/23 12:53:06  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:20  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 1.1  2002/01/16 22:14:48  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: AsnRelativeOid.cpp,v 9.2 2007/01/10 11:15:06 yranade Exp $"

//
// ASN.1 runtime AsnRelativeOid class implementation.
//

#include <Asn.h>
#include <AsnXml.h>
#include <AsnRelativeOid.h>
#include <AsnException.h>

using namespace std;

namespace its {


AsnDescObject* 
AsnRelativeOid::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescRelativeOid staticDesc;

    if (initialized)
    {
        ITS_ENSURE(result != NULL);
        return result;
    }

    Asn::Lock();

    if (initialized)
    {
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
    else
    {
        ITS_ASSERT(result == NULL);
        staticDesc.SetCloneForFactory(new AsnRelativeOid(&staticDesc));
        staticDesc.TagAddLevel(GetUniversalTag());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

void 
AsnRelativeOid::EncodeCheck(const AsnOptions& asnOptions)
{
    bool not_implemented = false;
    ITS_ASSERT(not_implemented);
}

Octets* 
AsnRelativeOid::InternalEncodeBer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);
    bool not_implemented = false;
    ITS_ASSERT(not_implemented);
    return NULL;
}

void 
AsnRelativeOid::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    bool not_implemented = false;
    ITS_ASSERT(not_implemented);
}

void 
AsnRelativeOid::InternalDecodeBer(
                Octets& octets, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeRemoveExtraTagLength(octets, asnOptions);

    bool not_implemented = false;
    ITS_ASSERT(not_implemented);
    DecodeCheck(octets, asnOptions);
}

int
AsnRelativeOid::EncodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description)
{
    return ITS_SUCCESS;
}

int 
AsnRelativeOid::DecodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description)
{
    return ITS_SUCCESS;
}

Characters* 
AsnRelativeOid::InternalEncodeToXml(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    string str;

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementStartTag(str, asnOptions, level, description);

    bool not_implemented = false;
    ITS_ASSERT(not_implemented);

    EncodeXmlElementEndTag(str, asnOptions, level, description);

    return new Characters(str);
}

void 
AsnRelativeOid::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    bool not_implemented = false;
    ITS_ASSERT(not_implemented);
}

void 
AsnRelativeOid::InternalDecodeFromXml(
                Characters& characters, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeXmlElementStartTag(characters, asnOptions, level, description);

    XmlContent content(*this);   

    bool not_implemented = false;
    ITS_ASSERT(not_implemented);

    DecodeXmlElementEndTag(characters, asnOptions, level, description);

    DecodeCheck(characters, asnOptions);
}

bool 
AsnRelativeOid::Equals(const AsnObject& rhs) const
{ 
    const AsnRelativeOid* other = 
        static_cast<const AsnRelativeOid*>(&rhs);
    // Useful only if dynamic cast is used.    
    if (other == NULL)
    {
        return false;
    }

    if (GetName() != rhs.GetName())
    {
        return false;
    }

    if (_data == other->_data)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void 
AsnRelativeOid::Print(ostream& os, size_t level) const
{
    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << GetName();
    os << " (";
    os << GetBaseName();
    os << ")" << endl;
    os << levelShift;
    os << "[ ";

    // TODO: To be improved (30 chararcters max per line).

    for (size_t i = 0; i < GetSize(); i++)
    {
        os << _data[i];
        
        if (i != GetSize() - 1)
        {
            os << ", ";
        }
    }

    os << " ]" << endl;
}

} // namespace its.


