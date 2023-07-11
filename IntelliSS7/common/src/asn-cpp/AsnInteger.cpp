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
// LOG: $Log: AsnInteger.cpp,v $
// LOG: Revision 9.2  2007/01/10 11:15:06  yranade
// LOG: Merge changes from 6.5.3 and Lucent branches
// LOG:
// LOG: Revision 9.1.10.2  2005/10/06 12:12:56  mmanikandan
// LOG: Exception Handling in PER and Code Review Changes.
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

#ident "$Id: AsnInteger.cpp,v 9.2 2007/01/10 11:15:06 yranade Exp $"

//
// ASN.1 runtime AsnInteger class implementation.
//

#include <Asn.h>
#include <AsnXml.h>
#include <AsnInteger.h>
#include <AsnException.h>
#include <AsnWholeNumber.h>

using namespace std;

namespace its {

AsnDescObject* 
AsnInteger::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescInteger staticDesc;

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
        staticDesc.SetCloneForFactory(new AsnInteger(&staticDesc));
        staticDesc.TagAddLevel(GetUniversalTag());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

void 
AsnInteger::EncodeCheck(const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseRange())
    {
        if (_value > GetDescription().GetMaxValue())
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INTEGER_VALUE_OUT_OF_RANGE);
        }

        if (_value < GetDescription().GetMinValue())
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INTEGER_VALUE_OUT_OF_RANGE);
        }
    }
}

Octets* 
AsnInteger::InternalEncodeBer(
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

    Octets valOctets(array, inc);
    Octets* result = EncodeTagLengthValue(valOctets, asnOptions);
    ITS_ENSURE(result != NULL);
    return result;
}

void 
AsnInteger::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseRange())
    {
        if (_value > GetDescription().GetMaxValue())
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INTEGER_VALUE_OUT_OF_RANGE, octets);
        }

        if (_value < GetDescription().GetMinValue())
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INTEGER_VALUE_OUT_OF_RANGE, octets);
        }
    }
}

void 
AsnInteger::InternalDecodeBer(
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
        ASN_THROW_DECODE_ERROR(ASN_E_INDEFINITE_INTEGER_LENGTH, octets);
    }
    else if (length.GetLength() == 0)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_NULL_INTEGER_LENGTH, octets);
    }
    else if (length.GetLength() > ASN_BYTES_PER_LONG)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INTEGER_LENGTH_TOO_LARGE, octets);
    }
    else
    {
        int i = 0;

        if (!octets.IsIndexWithOffsetValid(0))
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_INTEGER_LENGTH, octets);
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
            if (!octets.IsIndexWithOffsetValid(i))
            {
                ASN_THROW_DECODE_ERROR(ASN_E_INVALID_INTEGER_LENGTH, octets);
            }

            _value <<= ASN_BITS_PER_BYTE;
            _value &= ~ASN_ALL_BITS_SET | ~ASN_BYTE_MASK_IN_LONG;
            _value |= octets.GetOctetAtWithOffset(i) & ASN_BYTE_MASK_IN_LONG;
        }

        octets.IncrementOffset((size_t)length.GetLength());
    }

    DecodeCheck(octets, asnOptions);
}

int 
AsnInteger::EncodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description)
{
    bool extBit = false;
    long lb = 0;
    long ub = 0;
    lb = GetDescription().GetMinValue();
    ub = GetDescription().GetMaxValue();
    if(_signedInt)
    {
	if(GetDescription().IsClauseRange() && (_value < lb))
	{
	    ASN_THROW_ENCODE_ERROR(ASN_E_INTEGER_VALUE_OUT_OF_RANGE);
	}
	if (GetDescription().IsClauseRange() && (ub > lb) && (_value > ub))
	{
	    if(GetDescription().IsClauseExtensible()== false)
	    {
		ASN_THROW_ENCODE_ERROR(ASN_E_INTEGER_VALUE_OUT_OF_RANGE);
	    }
	    extBit = true;
	}
    }
    else
    {
	if(GetDescription().IsClauseRange() && ((ITS_UINT)_value < (ITS_UINT)lb))
	{
	    ASN_THROW_ENCODE_ERROR(ASN_E_INTEGER_VALUE_OUT_OF_RANGE);
	}
	if (GetDescription().IsClauseRange() && ((ITS_UINT)ub > (ITS_UINT)lb) 
	   && ((ITS_UINT)_value > (ITS_UINT)ub))
	{
	    if(GetDescription().IsClauseExtensible()== false)
	    {
		ASN_THROW_ENCODE_ERROR(ASN_E_INTEGER_VALUE_OUT_OF_RANGE);
	    }
	    extBit = true;
	}
    }
    if (GetDescription().IsClauseExtensible())
    {
        octs.SetBit(extBit);
    }
    
    if((extBit == false) && (_signedInt ? (ub > lb): ((ITS_UINT)ub > (ITS_UINT)lb)))
    {
        return AsnWN::EncodeCWN(octs, lb, ub, _value, asnOptions, _signedInt);
    }
    else if(extBit == false && GetDescription().IsClauseRange())
    {
        ITS_UINT val;
        if(_signedInt)
        {
            val = _value - lb;
        }
        else
        {
            val = (ITS_UINT)_value - (ITS_UINT)lb;
        }
        return AsnWN::EncodeSCWN(octs, val, asnOptions);
    }
    else
    {
        //Integer is always signed
        _signedInt = true;
        return AsnWN::EncodeUCWN(octs, _value, asnOptions);
    }
}

int 
AsnInteger::DecodeAPER(Octets& octs,
                      const AsnOptions& asnOptions,
                      const AsnDescObject& description)
{
    bool extBit = false;
    long lb = 0;
    long ub = 0;

    if (GetDescription().IsClauseExtensible())
    {
        extBit = octs.GetNextBit();
        SetExtension(extBit);
    }
    lb = GetDescription().GetMinValue();
    ub = GetDescription().GetMaxValue();
    if(extBit == false && (_signedInt ? (ub > lb): ((ITS_UINT)ub > (ITS_UINT)lb)))
    {
        _value = AsnWN::DecodeCWN(octs, lb, ub, asnOptions, _signedInt);
        if((_signedInt && _value > ub) ||
	  (_signedInt == false && ((ITS_UINT)_value > (ITS_UINT)ub)))
        {
	    ASN_THROW_DECODE_ERROR(ASN_E_INTEGER_VALUE_OUT_OF_RANGE, octs);
	}
    }
    else if(extBit == false && GetDescription().IsClauseRange())
    {
        _value = AsnWN::DecodeSCWN(octs, asnOptions);
        _value = (ITS_UINT)_value+lb;
    }
    else
    {
        //Integer is always signed
        _signedInt=true;
        _value = AsnWN::DecodeUCWN(octs, asnOptions);
    }

    return ITS_SUCCESS;
}

Characters* 
AsnInteger::InternalEncodeToXml(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    string str;

    XmlWriteLevelShift(str, asnOptions, level);
    EncodeXmlElementStartTag(str, asnOptions, level, description);

    char buffer[16];
    memset(buffer, 0, 16);
    sprintf(buffer, "%ld", _value);
    str += buffer;

    EncodeXmlElementEndTag(str, asnOptions, level, description);

    return new Characters(str);
}

void 
AsnInteger::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseRange())
    {
        if (_value > GetDescription().GetMaxValue())
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_INTEGER_VALUE_OUT_OF_RANGE,
                characters);
        }

        if (_value < GetDescription().GetMinValue())
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_INTEGER_VALUE_OUT_OF_RANGE, 
                characters);
        }
    }
}

void 
AsnInteger::InternalDecodeFromXml(
                Characters& characters, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeXmlElementStartTag(characters, asnOptions, level, description);

    XmlContent content(*this);   

    content.DecodeAsInteger(characters, asnOptions);

    string str = content.GetString();

    int numFields = sscanf(str.c_str(), "%ld", &_value);
    ITS_ASSERT(numFields == 1);

    DecodeXmlElementEndTag(characters, asnOptions, level, description);

    DecodeCheck(characters, asnOptions);
}

bool 
AsnInteger::Equals(const AsnObject& rhs) const
{ 
    const AsnInteger* other = static_cast<const AsnInteger*>(&rhs);
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
AsnInteger::Print(ostream& os, size_t level) const
{
    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << GetName();
    os << " (";
    os << GetBaseName();
    os << ")" << endl;
    os << levelShift;
    os << "[ ";
    if(_signedInt)
    {
        os << _value;
    }
    else
    {
        os << (ITS_UINT)_value;
    }
    os << " ]" << endl;
}

} // namespace its.


