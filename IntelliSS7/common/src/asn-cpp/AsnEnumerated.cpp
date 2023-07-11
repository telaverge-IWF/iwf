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
// LOG: $Log: AsnEnumerated.cpp,v $
// LOG: Revision 9.2.64.1  2014/09/16 09:34:53  jsarvesh
// LOG: Changes done for removing warnings
// LOG:
// LOG: Revision 9.2.60.1  2014/09/15 07:20:41  jsarvesh
// LOG: Changes done for removing Warnings
// LOG:
// LOG: Revision 9.2  2007/01/10 11:15:06  yranade
// LOG: Merge changes from 6.5.3 and Lucent branches
// LOG:
// LOG: Revision 9.1.10.4  2005/10/24 13:04:27  dsatish
// LOG: Choice index problem fix (Althaf)
// LOG:
// LOG: Revision 9.1.10.3  2005/10/06 12:12:56  mmanikandan
// LOG: Exception Handling in PER and Code Review Changes.
// LOG:
// LOG: Revision 9.1.10.2  2005/09/14 09:48:27  mmanikandan
// LOG: Unit Test Bugs.
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
// LOG: Revision 5.9  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.8  2002/01/11 22:20:00  hdivoux
// LOG: First shot at XER decoding.
// LOG:
// LOG: Revision 5.7  2002/01/10 00:09:56  hdivoux
// LOG: Update for first working XER encoding.
// LOG:
// LOG: Revision 5.6  2002/01/07 22:58:37  hdivoux
// LOG: First shot at XER encoding.
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

#ident "$Id: AsnEnumerated.cpp,v 9.2.64.1 2014/09/16 09:34:53 jsarvesh Exp $"

//
// ASN.1 runtime AsnEnumerated class implementation.
//

#include <Asn.h>
#include <AsnXml.h>
#include <AsnEnumerated.h>
#include <AsnException.h>
#include <AsnWholeNumber.h>

using namespace std;

namespace its {

AsnDescObject* 
AsnEnumerated::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescEnumerated staticDesc;

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
        staticDesc.SetCloneForFactory(new AsnEnumerated(&staticDesc));
        staticDesc.TagAddLevel(GetUniversalTag());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

void 
AsnEnumerated::EncodeCheck(const AsnOptions& asnOptions)
{
    if (!GetDescription().Contains(_value) &&
        !asnOptions.IsEncodeSkipInvalidEnumeratedValue())
    {
        ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_ENUMERATED_VALUE);
    }
}

Octets* 
AsnEnumerated::InternalEncodeBer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    vector<byte> array(ASN_BYTES_PER_LONG, 0x00U);

    int inc = 0;
    bool maxShrink = false;
    int j = 0;

    for (j = 0; j < ASN_BYTES_PER_LONG; j++)
    {
        if (!maxShrink && j < ASN_BYTES_PER_LONG - 1)
        {
            byte curr    = (byte)((_value >> ((ASN_BYTES_PER_LONG - j - 1) *
                                   ASN_BITS_PER_BYTE)) & ASN_ALL_BITS_SET);

            byte next    = (byte)((_value >> ((ASN_BYTES_PER_LONG - j - 2) *
                                   ASN_BITS_PER_BYTE)) & ASN_ALL_BITS_SET);

            if ((curr == 0 && (next & ASN_SIGN_BIT) == 0) ||
                (curr == ASN_ALL_BITS_SET && (next & ASN_SIGN_BIT) != 0 ))
            {
                continue;
            }
            else
            {
                maxShrink = true;
            }
        }

        array[inc] = (byte)((_value >> ((ASN_BYTES_PER_LONG - j - 1) *
                             ASN_BITS_PER_BYTE)) & ASN_ALL_BITS_SET);

        inc++;
    }

    Octets valOctets(array, (size_t)inc);
    Octets* result = EncodeTagLengthValue(valOctets, asnOptions);
    ITS_ENSURE(result != NULL);
    return result; 
}

void 
AsnEnumerated::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    if (!GetDescription().Contains(_value) &&
        !asnOptions.IsDecodeSkipInvalidEnumeratedValue() &&
        !GetDescription().IsClauseExtensible())
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INVALID_ENUMERATED_VALUE, octets);
    }
}

void 
AsnEnumerated::InternalDecodeBer(
                Octets& octets, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeRemoveExtraTagLength(octets, asnOptions);

    Tag tag(octets, asnOptions);

    Length length(octets, asnOptions);
    if (length.IsIndefinite())
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INDEFINITE_ENUMERATED_LENGTH, octets);
    }
    else if (length.GetLength() == 0)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_NULL_ENUMERATED_LENGTH, octets);
    }
    else if (length.GetLength() > ASN_BYTES_PER_LONG)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_ENUMERATED_LENGTH_TOO_LARGE, octets);
    }
    else
    {
        int i = 0;

        if (!octets.IsIndexWithOffsetValid(0))
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_ENUMERATED_LENGTH, octets);
        }

        byte b = octets.GetOctetAtWithOffset(0);

        if ((b & ASN_SIGN_BIT) != 0)
        {
            _value = -1;
        }
        else
        {
            _value = 0;
        }

        for (i = 0; i < length.GetLength(); i++)
        {
            if (!octets.IsIndexWithOffsetValid((size_t)i))
            {
                ASN_THROW_DECODE_ERROR(
                    ASN_E_INVALID_ENUMERATED_LENGTH,
                    octets);
            }

            _value <<= ASN_BITS_PER_BYTE;
            _value &= ~ASN_ALL_BITS_SET | ~ASN_BYTE_MASK_IN_LONG;
            _value |= octets.GetOctetAtWithOffset(i) & ASN_BYTE_MASK_IN_LONG;
        }

        octets.IncrementOffset((size_t)length.GetLength());
    }

    if (GetDescription().IsClauseExtensible() && 
        !GetDescription().Contains(_value))
    {
        SetExtension(true);
    }

    DecodeCheck(octets, asnOptions);
}

int
AsnEnumerated::EncodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description)
{
    bool extBit = IsExtension();

    if (GetDescription().IsClauseExtensible())
    {
        octs.SetBit(extBit);
    }

    int index = -1;

    const AsnDescEnumerated::NamedNumber* numList = 
                 GetDescription().GetNamedNumberList();

    for (unsigned int i = 0; i < GetDescription().GetSize(); i++)
    {
        if (numList[i]._number == _value)
        {
            index = i;
            break;
        }
    }

    if ((index == -1) && extBit)
    {
        const AsnDescEnumerated::NamedNumber* numExtList = 
                GetDescription().GetNamedNumberExtList();

        // Enumeration index >= 64 is unlikely to happen for outside the root
        if((_value >= 64) || (GetDescription().GetExtSize() >= 64))
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_ENUMERATED_VALUE);
        }
        for (unsigned int i = 0; i < GetDescription().GetExtSize(); i++)
        {
            if (numExtList[i]._number == _value)
            {
                index = i;
                break;
            }
        }
    }

    if (index == -1)
    {
        ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_ENUMERATED_VALUE);
    }

    if (!extBit)
    {
        AsnWN::EncodeCWN(octs, 0, GetDescription().GetSize() - 1, 
                              index, asnOptions);
    }
    else
    {
        AsnWN::EncodeNSNNWN(octs, index, asnOptions);
    }

    return ITS_SUCCESS;
}

int 
AsnEnumerated::DecodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description)
{
    bool extBit = false;
    int index = 0;

    if (GetDescription().IsClauseExtensible())
    {
        extBit = octs.GetNextBit();
        SetExtension(extBit);
    }

    if (!extBit)
    {
        index = AsnWN::DecodeCWN(octs, 0, 
                      GetDescription().GetSize() - 1, asnOptions);
    }
    else
    {
        index = AsnWN::DecodeNSNNWN(octs, asnOptions);
        //EnumerationIndex shouldn't be >= 64 for outside the root
        if(index >= 64)
        {
            ASN_THROW_DECODE_ERROR(ASN_E_UNEXPECTED_LARGE_LENGTH, octs);
        }
    }

    if (!extBit)
    {
        const AsnDescEnumerated::NamedNumber* numList = 
                 GetDescription().GetNamedNumberList();
        _value = numList[index]._number;
    }
    else
    {
        const AsnDescEnumerated::NamedNumber* numList = 
                 GetDescription().GetNamedNumberExtList();
        _value = numList[index]._number;
    }

    return ITS_SUCCESS;
}

Characters* 
AsnEnumerated::InternalEncodeToXml(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    string str;

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementStartTag(str, asnOptions, level, description);

    const AsnDescEnumerated::NamedNumber* 
        namedNumberList = 
            GetDescription().GetNamedNumberList();

    bool found = false;

    while ((*namedNumberList)._name != NULL)
    {
        if ((*namedNumberList)._number == _value)
        {
            found = true;
            break;
        }

        namedNumberList++;
    }

    if (found)
    {
        XmlWriteEmptyElementTag(str, (*namedNumberList)._name, asnOptions);
    }
    else
    {
        bool must_not_be_reached = false;
        ITS_ASSERT(must_not_be_reached);
        XmlWriteEmptyElementTag(str, "invalid enumerated value", asnOptions);
    }

    EncodeXmlElementEndTag(str, asnOptions, level, description);

    return new Characters(str);
}

void 
AsnEnumerated::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    if (!GetDescription().Contains(_value) &&
        !asnOptions.IsDecodeSkipInvalidEnumeratedValue() &&
        !GetDescription().IsClauseExtensible())
    {
        ASN_THROW_CHARACTERS_DECODE_ERROR(
            ASN_E_INVALID_ENUMERATED_VALUE,
            characters);
    }
}

void 
AsnEnumerated::InternalDecodeFromXml(
                Characters& characters, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeXmlElementStartTag(characters, asnOptions, level, description);

    XmlContent content(*this);   

    content.DecodeAsEnumerated(characters, asnOptions);

    string str = content.GetString();

    const AsnDescEnumerated::NamedNumber*
        namedNumberList = 
            GetDescription().GetNamedNumberList();

    bool found = false;

    while ((*namedNumberList)._name != NULL)
    {
        if ((*namedNumberList)._name == str)
        {
            _value = (*namedNumberList)._number;

            found = true;
            break;
        }

        namedNumberList++;
    }

    if (!found)
    {
        ASN_THROW_CHARACTERS_DECODE_ERROR(
            ASN_E_INVALID_ENUMERATED_VALUE,
            characters);
    }

    DecodeXmlElementEndTag(characters, asnOptions, level, description);

    DecodeCheck(characters, asnOptions);
}

bool 
AsnEnumerated::Equals(const AsnObject& rhs) const
{ 
    const AsnEnumerated* other = static_cast<const AsnEnumerated*>(&rhs);
    // Useful only if dynamic cast is used.
    if (other == NULL)
    {
        return false;
    }

    if (GetName() != rhs.GetName())
    {
        return false;
    }

    if (_value == other->_value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void 
AsnEnumerated::Print(ostream& os, size_t level) const
{
    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << GetName();
    os << " (";
    os << GetBaseName();
    os << ")" << endl;
    os << levelShift;
    os << "[ ";
    
    if (!_extBit && GetDescription().Contains(_value))
    {
        os << GetDescription().Get(_value);
    }
    else if (_extBit && GetDescription().ContainsExt(_value))
    {
        os << GetDescription().GetExt(_value);
    }

    os << "(";
    os << _value;
    os << ") ]" << endl;
}

} // namespace its.

