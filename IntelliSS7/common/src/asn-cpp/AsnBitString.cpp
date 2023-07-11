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
// LOG: $Log: AsnBitString.cpp,v $
// LOG: Revision 9.2.64.1  2014/09/16 09:34:53  jsarvesh
// LOG: Changes done for removing warnings
// LOG:
// LOG: Revision 9.2.60.1  2014/09/15 07:20:41  jsarvesh
// LOG: Changes done for removing Warnings
// LOG:
// LOG: Revision 9.2  2007/01/10 11:15:06  yranade
// LOG: Merge changes from 6.5.3 and Lucent branches
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
// LOG: Revision 8.2  2005/03/21 13:51:18  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:45  mmiers
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

#ident "$Id: AsnBitString.cpp,v 9.2.64.1 2014/09/16 09:34:53 jsarvesh Exp $"

//
// ASN.1 runtime BitString class implementation.
//

#include <Asn.h>
#include <AsnXml.h>
#include <AsnBitString.h>
#include <AsnException.h>
#include <AsnWholeNumber.h>

using namespace std;

namespace its {

AsnDescObject* 
AsnBitString::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescBitString staticDesc;

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
        staticDesc.SetCloneForFactory(new AsnBitString(&staticDesc));
        staticDesc.TagAddLevel(GetUniversalTag());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

void 
AsnBitString::EncodeCheck(const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsEncodeIgnoreBitStringSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_BIT_STRING_SIZE);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_BIT_STRING_SIZE);
        }
    }
}

Octets* 
AsnBitString::InternalEncodeBer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    long numberOfBits = 0;
    vector<byte> arrayBits;
    VectorBoolToBits(_data, numberOfBits, arrayBits);
    long finalOctetUnusedBits = 0;

    if (numberOfBits % ASN_BITS_PER_BYTE != 0)
    {
        finalOctetUnusedBits =
            ASN_BITS_PER_BYTE -
                (numberOfBits %
                    ASN_BITS_PER_BYTE);
    }

    ITS_ASSERT(finalOctetUnusedBits >= 0);
    ITS_ASSERT(finalOctetUnusedBits < ASN_BITS_PER_BYTE);

    vector<byte> array;
    array.reserve(arrayBits.size() + 1);
    array.push_back((byte)finalOctetUnusedBits);
    array.insert(array.end(), arrayBits.begin(), arrayBits.end());
    ITS_ASSERT(array.size() == arrayBits.size() + 1);

    Octets valOctets(array);
    Octets* result = EncodeTagLengthValue(valOctets, asnOptions);
    ITS_ENSURE(result != NULL);
    return result;
}

void 
AsnBitString::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsDecodeIgnoreBitStringSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_BIT_STRING_SIZE, octets);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_BIT_STRING_SIZE, octets);
        }
    }
}

void 
AsnBitString::InternalDecodeBer(
                Octets& octets, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeRemoveExtraTagLength(octets, asnOptions);

    Tag tag(octets, asnOptions);
    if (tag.GetType() == Tag::ASN_CONSTRUCTED)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_CONSTRUCTED_BIT_STRING, octets);
    }

    Length length(octets, asnOptions);
    if (length.IsIndefinite())
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INDEFINITE_BIT_STRING_LENGTH, octets);
    }
    else if (length.GetLength() == 0)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_NULL_BIT_STRING_LENGTH, octets);
    }
    else
    {
        _data.erase(_data.begin(), _data.end());

        if (!octets.IsIndexWithOffsetValid(0))
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_BIT_STRING_LENGTH, octets);
        }

        byte b = octets.GetOctetAtWithOffset(0);
        long finalOctetUnusedBits = (long)b;
        ITS_ASSERT(finalOctetUnusedBits >= 0);

        if (finalOctetUnusedBits >= ASN_BITS_PER_BYTE)
        {
            ASN_THROW_DECODE_ERROR(
                ASN_E_INVALID_BIT_STRING_UNUSED_BITS_NUMBER,
                octets);
        }

        vector<byte> arrayBits;
        arrayBits.reserve(length.GetLength() - 1);

        for (int i = 1; i < length.GetLength(); i++)
        {
            if (!octets.IsIndexWithOffsetValid(i))
            {
                ASN_THROW_DECODE_ERROR(
                    ASN_E_INVALID_BIT_STRING_LENGTH, 
                    octets);
            }

            arrayBits.push_back(octets.GetOctetAtWithOffset(i));
        }

        if (arrayBits.size() == 0 && finalOctetUnusedBits != 0)
        {
            ASN_THROW_DECODE_ERROR(
                ASN_E_INVALID_BIT_STRING_UNUSED_BITS_NUMBER,
                octets);
        }

        long numberOfBits = 
                arrayBits.size() *
                    ASN_BITS_PER_BYTE -
                        finalOctetUnusedBits;
        ITS_ASSERT(numberOfBits >= 0);
        BitsToVectorBool(numberOfBits, arrayBits, _data);
        octets.IncrementOffset((size_t)length.GetLength());
    }

    DecodeCheck(octets, asnOptions);
}

int
AsnBitString::EncodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description)
{
    bool extBit = false;
    int len = 0;
    unsigned long lb = 0;
    unsigned long ub = 0;

    lb = GetDescription().GetMinSize();
    ub = GetDescription().GetMaxSize();

    if (GetDescription().IsClauseExtensible())
    {
	extBit = (ub !=0 && (_data.size() > ub)) ? true : false;
	octs.SetBit(extBit);
    }
    //16K is reasonably good no of bit strings, more than this is unexpected
    if((_data.size() < lb) || ((ub !=0) && (extBit == false) && (_data.size() > ub)))
    {
	ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_BIT_STRING_LENGTH);
    }

    if (!extBit)
    {

        if ((lb == ub) && (ub != 0) && 
            (ub <= 16))
        {
            if (ub == _data.size())
            {
                len = ub;
            }
            else
            {
                return !ITS_SUCCESS;
            }
        }
        else if ((lb == ub) && (ub != 0))
        {
            if (ub == _data.size())
            {
                octs.AddPaddingBits();
                len = ub;
            }
            else
            {
                return !ITS_SUCCESS;
            }
        }
        else
        {
            len = _data.size();

            if (ub != 0)
            {
                AsnWN::EncodeCWN(octs, lb, ub, len, asnOptions);
                octs.AddPaddingBits();
            }
            else
            {
                Length leng(len-lb);
                Octets* lenocts = leng.Encode(asnOptions);
                std::vector<ITS_OCTET> oarr = lenocts->GetArray();
                for (unsigned int i = 0; i < oarr.size(); i++)
                {
                    octs.SetOctet(oarr[i]);
                }
                if(lenocts)
                {
                    delete lenocts;
                }
               
            }
        }
    }
    else
    {
        Length leng(_data.size());
                
        Octets* lenocts = leng.Encode(asnOptions);
        len = leng.GetLength();

        std::vector<ITS_OCTET> oarr = lenocts->GetArray();
        for (unsigned int i = 0; i < oarr.size(); i++)
        {
            octs.SetOctet(oarr[i]);
        } 

        if (lenocts)
        {
            delete lenocts;
        }
    }

    if (len != 0)
    {
        for (int i = 0; i < len; i++)
        {
            octs.SetBit(_data[i]);
        }
    }
    return ITS_SUCCESS;
}

int 
AsnBitString::DecodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description)
{
    bool extBit = false;
    int len = 0;
    long lb = 0;
    long ub = 0;

    if (GetDescription().IsClauseExtensible())
    {
        extBit = octs.GetNextBit();
        SetExtension(extBit);
    }

    if (!extBit)
    {
        lb = GetDescription().GetMinSize();
        ub = GetDescription().GetMaxSize();

        if ((lb == ub) && (ub != 0) && (ub <= 16))
        {
            len = ub;
        }
        else if ((lb == ub) && (ub != 0) && (ub < K64))
        {
            octs.SkipPaddingBits();
            len = ub;
        }
        else
        {
            if ((lb != 0) && (ub != 0) && (ub < K64))
            {
                len = AsnWN::DecodeCWN(octs, lb, ub, asnOptions);
                octs.SkipPaddingBits();
		if(len > ub)
		{
		    ASN_THROW_DECODE_ERROR(ASN_E_INVALID_BIT_STRING_LENGTH, octs);
		}
								    
            }
            else
            {
                Length leng(octs, asnOptions);
                len = leng.GetLength();
		//for semi constraint type when lb !=0
		len +=lb;
            }
        }
    }
    else
    {
        Length leng(octs, asnOptions);
        len = leng.GetLength();
    }
    if(len >= K16)
    {
	ASN_THROW_DECODE_ERROR(ASN_E_INVALID_BIT_STRING_LENGTH, octs);
    }
    if (len != 0)
    {
        _data.clear();
        for (int i = 0; i < len; i++)
        {
            _data.push_back(octs.GetNextBit());
        }
    }
    return ITS_SUCCESS;
}

Characters* 
AsnBitString::InternalEncodeToXml(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    string str;

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementStartTag(str, asnOptions, level, description);

    for (size_t i = 0; i < _data.size(); i++)
    {
        if (_data[i])
        {
            str += '1';
        }
        else
        {
            str += '0';
        }
    }

    EncodeXmlElementEndTag(str, asnOptions, level, description);

    return new Characters(str);
}

void 
AsnBitString::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsDecodeIgnoreBitStringSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_INVALID_BIT_STRING_SIZE, 
                characters);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_INVALID_BIT_STRING_SIZE, 
                characters);
        }
    }
}

void 
AsnBitString::InternalDecodeFromXml(
                Characters& characters, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeXmlElementStartTag(characters, asnOptions, level, description);

    XmlContent content(*this);   

    content.DecodeAsBitString(characters, asnOptions);

    string str = content.GetString();

    _data.erase(_data.begin(), _data.end());
    _data.reserve(str.size());

    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == '1')
        {
            _data.push_back(true);
        }
        else
        {
            ITS_ASSERT(str[i] == '0');
            _data.push_back(false);
        }
    }

    DecodeXmlElementEndTag(characters, asnOptions, level, description);

    DecodeCheck(characters, asnOptions);
}

bool 
AsnBitString::Equals(const AsnObject& rhs) const
{ 
    const AsnBitString* other = static_cast<const AsnBitString*>(&rhs);
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
AsnBitString::Print(ostream& os, size_t level) const
{
    static const int ROW_LENGTH = 30;

    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << GetName();
    os << " (";
    os << GetBaseName();
    os << ")" << endl;
    os << levelShift;
    os << "[ ";

    int divisor = ROW_LENGTH;

    ITS_ASSERT(divisor > 1);

    int quotient  = GetSize() / divisor;
    int remainder = GetSize() % divisor;

    int i = 0;
        
    for (i = 0; i < quotient; i++)
    {
        for (int j = 0; j < divisor; j++)
        {
            if (_data[i * divisor + j])
            {
                os << "1";
            }
            else
            {
                os << "0";
            }
        }

        if (!(remainder == 0) || i != quotient - 1)
        {
            os << endl;
            os << levelShift;
        }

        if (i < quotient - 1)
        {
            os << "  ";
        }
    }

    if (quotient != 0 && !(remainder == 0))
    {
        os << "  ";
    }

    for (int j = 0; j < remainder; j++)
    {
        if (_data[i * divisor + j])
        {
            os << "1";
        }
        else
        {
            os << "0";
        }
    }

    if (remainder != 0 && quotient != 0)
    {
        for (int j = 0; j < divisor - remainder; j++)
        {
            os << " ";
        }
    }

    os << " ]" << endl;
}

void 
AsnBitString::VectorBoolToBits(
                            const vector<bool>& boolVect,
                            long& numberOfBits,
                            vector<byte>& byteVect)
{
    byteVect.erase(byteVect.begin(), byteVect.end());
    numberOfBits = boolVect.size();

    int numberOfBytes = numberOfBits / ASN_BITS_PER_BYTE;
    if (numberOfBits % ASN_BITS_PER_BYTE > 0)
    {
        numberOfBytes += 1;
    }

    byteVect.reserve(numberOfBytes);

    int n = 0;  // Bit number starting from zero.
    for (int i = 0; i < numberOfBytes; i++)
    {
        byte b = 0x00U;

        for (int j = ASN_BITS_PER_BYTE - 1; j >= 0; j--)
        {
            if (boolVect[n])
            {
                b |= 0x01U << j;
            }

            n++;

            if (n >= numberOfBits)
            {
                break;
            }
        }

        byteVect.push_back(b);
    }
}

void 
AsnBitString::BitsToVectorBool(
                            long numberOfBits,
                            const vector<byte>& byteVect,
                            vector<bool>& boolVect)
{
    ITS_REQUIRE(numberOfBits >= 0);

    unsigned int requiredNumberOfBytes = numberOfBits / ASN_BITS_PER_BYTE;
    if (numberOfBits % ASN_BITS_PER_BYTE > 0)
    {
        requiredNumberOfBytes += 1;
    }

    ITS_REQUIRE(byteVect.size() == requiredNumberOfBytes);

    boolVect.erase(boolVect.begin(), boolVect.end());
    boolVect.reserve(numberOfBits);

    int n = 0;  // Bit number starting from zero.
    for (size_t i = 0; i < byteVect.size(); i++)
    {
        byte b = byteVect[i];

        for (int j = ASN_BITS_PER_BYTE - 1; j >= 0; j--)
        {
            if ((b & (0x01U << j)) != 0x00U)
            {
                boolVect.push_back(true);
            }
            else
            {
                boolVect.push_back(false);
            }

            n++;

            if (n >= numberOfBits)
            {
                break;
            }
        }
    }
}

} // namespace its.


