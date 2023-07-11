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
// LOG: $Log: AsnNull.cpp,v $
// LOG: Revision 9.2  2007/01/10 11:15:06  yranade
// LOG: Merge changes from 6.5.3 and Lucent branches
// LOG:
// LOG: Revision 9.1.10.1  2005/09/06 09:17:20  mmanikandan
// LOG: Support for ASN.1 PER.
// LOG:
// LOG: Revision 9.1  2005/03/23 12:53:05  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:19  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.8  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.7  2002/01/11 22:20:00  hdivoux
// LOG: First shot at XER decoding.
// LOG:
// LOG: Revision 5.6  2002/01/10 00:09:56  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 5.5  2002/01/04 15:58:32  hdivoux
// LOG: More update for XER support.
// LOG:
// LOG: Revision 5.4  2002/01/02 23:23:03  hdivoux
// LOG: Start update for XER support.
// LOG:
// LOG: Revision 5.3  2001/12/24 21:05:03  hdivoux
// LOG: General update for options.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:27  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: AsnNull.cpp,v 9.2 2007/01/10 11:15:06 yranade Exp $"

//
// ASN.1 runtime AsnNull class implementation.
//

#include <Asn.h>
#include <AsnXml.h>
#include <AsnNull.h>
#include <AsnException.h>

using namespace std;

namespace its {

AsnDescObject* 
AsnNull::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescNull staticDesc;

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
        staticDesc.SetCloneForFactory(new AsnNull(&staticDesc));
        staticDesc.TagAddLevel(GetUniversalTag());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

void 
AsnNull::EncodeCheck(const AsnOptions& asnOptions)
{
    // Nothing to do.
}

Octets* 
AsnNull::InternalEncodeBer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    Octets valOctets; // Default constructor => valOctets.GetLength() == 0.
    Octets* result = EncodeTagLengthValue(valOctets, asnOptions);
    ITS_ENSURE(result != NULL);
    return result;
}

void 
AsnNull::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    // Nothing to do.
}

void 
AsnNull::InternalDecodeBer(
                Octets& octets, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeRemoveExtraTagLength(octets, asnOptions);

    Tag tag(octets, asnOptions);

    Length length(octets, asnOptions);
    if (length.GetLength() != 0)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INVALID_NULL_LENGTH, octets);
    }

    DecodeCheck(octets, asnOptions);
}

int
AsnNull::EncodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description)
{
    return ITS_SUCCESS;
}

int 
AsnNull::DecodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description)
{
    return ITS_SUCCESS;
}

Characters* 
AsnNull::InternalEncodeToXml(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    string str;
    XmlWriteLevelShift(str, asnOptions, level);

    if (level == 0 || !description.IsNamedType())
    {
        if (description.HasTypeName())
        {
            XmlWriteEmptyElementTag(
                str,
                description.GetTypeName(),
                asnOptions);
        }
        else
        {
            XmlWriteEmptyElementTag(
                str, 
                XmlReplaceUnderscoreByDash(GetName()), 
                asnOptions);
        }
    }
    else if (description.IsNamedType())
    {
        XmlWriteEmptyElementTag(
            str, 
            description.GetNamedTypeName(), 
            asnOptions);
    }
    else
    {
        if (description.HasTypeName())
        {
            XmlWriteEmptyElementTag(
                str,
                description.GetTypeName(),
                asnOptions);
        }
        else
        {
            XmlWriteEmptyElementTag(
                str, 
                XmlReplaceUnderscoreByDash(GetName()),
                asnOptions);
        }
    }

    return new Characters(str);
}

void 
AsnNull::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    // Nothing to do.
}

void 
AsnNull::InternalDecodeFromXml(
                Characters& characters, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    string expectedTagName;

    if (level == 0 || !description.IsNamedType())
    {
        if (description.HasTypeName())
        {
            expectedTagName = description.GetTypeName();
        }
        else
        {
            expectedTagName = XmlReplaceUnderscoreByDash(GetName());
        }
    }
    else if (description.IsNamedType())
    {
            expectedTagName = description.GetNamedTypeName();
    }
    else
    {
        if (description.HasTypeName())
        {
            expectedTagName = description.GetTypeName();
        }
        else
        {
            expectedTagName = XmlReplaceUnderscoreByDash(GetName());
        }
    }

    XmlEmptyElementTag emptyElementTag(*this);

    emptyElementTag.Decode(characters, asnOptions);

    if (expectedTagName != emptyElementTag.GetName())
    {
        ASN_THROW_CHARACTERS_DECODE_ERROR(
            ASN_E_XML_INVALID_EMPTY_ELEMENT_TAG,
            characters);
    }

    DecodeCheck(characters, asnOptions);
}

bool 
AsnNull::Equals(const AsnObject& rhs) const
{ 
    const AsnNull* other = static_cast<const AsnNull*>(&rhs);
    // Useful only if dynamic cast is used.
    if (other == NULL)
    {
        return false;
    }

    if (GetName() != rhs.GetName())
    {
        return false;
    }

    return true;
}

void 
AsnNull::Print(ostream& os, size_t level) const
{
    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << GetName();
    os << " (";
    os << GetBaseName();
    os << ")" << endl;
    os << levelShift;
    os << "[ ]" << endl;
}

} // namespace its.
