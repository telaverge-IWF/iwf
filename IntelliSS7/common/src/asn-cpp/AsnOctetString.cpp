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
// LOG: $Log: AsnOctetString.cpp,v $
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

#ident "$Id: AsnOctetString.cpp,v 9.2.64.1 2014/09/16 09:34:53 jsarvesh Exp $"

//
// ASN.1 runtime AsnOctetString class implementation.
//

#include <stdio.h>

#include <Asn.h>
#include <AsnXml.h>
#include <AsnOctetString.h>
#include <AsnException.h>
#include <AsnWholeNumber.h>

using namespace std;

namespace its {

// Helper function to convert a byte to hexadecimal string.
static string 
ByteToHexString(byte b)
{
    char strBuf[4];
    memset(strBuf, 0, 4);
    sprintf(strBuf, "%02X", b);
    string result = strBuf;
    return result;
}

AsnDescObject* 
AsnOctetString::GetStaticDescription()
{
    static volatile bool initialized = false;
    static AsnDescObject* result = NULL;
    static AsnDescOctetString staticDesc;

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
        staticDesc.SetCloneForFactory(new AsnOctetString(&staticDesc));
        staticDesc.TagAddLevel(GetUniversalTag());
        result = &staticDesc;
        initialized = true;
        Asn::Unlock();
        ITS_ENSURE(result != NULL);
        return result;
    }
}

void 
AsnOctetString::EncodeCheck(const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsEncodeIgnoreOctetStringSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_OCTET_STRING_SIZE);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_OCTET_STRING_SIZE);
        }
    }
}

Octets* 
AsnOctetString::InternalEncodeBer(
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    EncodeCheck(asnOptions);

    Octets valOctets(_data);
    Octets* result = EncodeTagLengthValue(valOctets, asnOptions);
    ITS_ENSURE(result != NULL);
    return result;
}

void 
AsnOctetString::DecodeCheck(Octets& octets, const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsDecodeIgnoreOctetStringSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_OCTET_STRING_SIZE, octets);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_DECODE_ERROR(ASN_E_INVALID_OCTET_STRING_SIZE, octets);
        }
    }
}

void 
AsnOctetString::InternalDecodeBer(
                Octets& octets, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeRemoveExtraTagLength(octets, asnOptions);

    Tag tag(octets, asnOptions);
    if (tag.GetType() == Tag::ASN_CONSTRUCTED)
    {
        ASN_THROW_DECODE_ERROR(ASN_E_CONSTRUCTED_OCTET_STRING, octets);
    }

    Length length(octets, asnOptions);
    if (length.IsIndefinite())
    {
        ASN_THROW_DECODE_ERROR(ASN_E_INDEFINITE_OCTET_STRING_LENGTH, octets);
    }
    else
    {
        _data.erase(_data.begin(), _data.end());
        _data.reserve((size_t)length.GetLength());

        for (int i = 0; i < length.GetLength(); i++)
        {
            if (!octets.IsIndexWithOffsetValid(i))
            {
                ASN_THROW_DECODE_ERROR(
                    ASN_E_INVALID_OCTET_STRING_LENGTH,
                    octets);
            }

            byte b = octets.GetOctetAtWithOffset(i);
            _data.push_back(b);
        }

        octets.IncrementOffset((size_t)length.GetLength());
    }

    DecodeCheck(octets, asnOptions);
}

int
AsnOctetString::EncodeAPER(Octets& octs,
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
    if((_data.size() < lb) || (ub !=0 && extBit == false && (_data.size() > ub)))
    {
	ASN_THROW_ENCODE_ERROR(ASN_E_INVALID_OCTET_STRING_LENGTH);
    }

    if (!extBit)
    {

        if ((lb == ub) && (ub != 0) && (ub <= 2))
        {
            ITS_OCTET val = 0;

            for (unsigned int i = 0; i < ub; i++)
            {
                val = _data[i];
                octs.SetBits(val, 8);
            }

            len = 0;
        }
        else if ((lb == ub) && (ub != 0))
        {
            octs.AddPaddingBits();
            len = ub;
        }
        else
        {
            if ((lb != 0) && (ub != 0))
            {
                AsnWN::EncodeCWN(octs, lb, ub, 
                                    _data.size(), asnOptions);
                len = _data.size();
            }
            else
            {
	        len = _data.size();
                Length leng(len-lb);
                
                Octets* lenocts = leng.Encode(asnOptions);

                std::vector<ITS_OCTET> oarr = lenocts->GetArray();

                if (lenocts)
                {
                    delete lenocts;
                    lenocts = NULL; 
                }

                for (unsigned int i = 0; i < oarr.size(); i++)
                {
                    octs.SetOctet(oarr[i]);
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

        if (lenocts)
        {
            delete lenocts;
            lenocts = NULL;
        }

        for (unsigned int i = 0; i < oarr.size(); i++)
        {
            octs.SetOctet(oarr[i]);
        }
    }

    for (int i = 0; i < len; i++)
    {
        octs.SetOctet(_data[i]);
    }
    return ITS_SUCCESS;
}

int 
AsnOctetString::DecodeAPER(Octets& octs,
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

        if ((lb == ub) && (ub != 0) && (ub <= 2))
        {
            int bitSize = ub * 8;
            ITS_OCTET val = 0;

            for (int i = 0; i < bitSize; i++)
            {
                val = (val << 1) | (octs.GetNextBit()?1:0);

                if ((i+1) % 8 == 0)
                {
                    _data.push_back(val);
                    val = 0;
                }
            }

            len = 0;
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
		if(len > ub)
		{
		    ASN_THROW_DECODE_ERROR(ASN_E_INVALID_OCTET_STRING_LENGTH, octs);
		}
								    
            }
            else
            {
                octs.SkipPaddingBits();
                Length leng(octs, asnOptions);
                len = leng.GetLength();
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
	ASN_THROW_DECODE_ERROR(ASN_E_INVALID_OCTET_STRING_LENGTH, octs);
    }
    if (len)
    {
        octs.SkipPaddingBits();
        for (int i = 0; i < len; i++)
        {
            _data.push_back(octs.GetNextOctet());
        }
    }
    return ITS_SUCCESS;
}

Characters* 
AsnOctetString::InternalEncodeToXml(
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
        str += ByteToHexString(_data[i]);
    }

    EncodeXmlElementEndTag(str, asnOptions, level, description);

    return new Characters(str);
}

void 
AsnOctetString::DecodeCheck(
                Characters& characters, 
                const AsnOptions& asnOptions)
{
    if (GetDescription().IsClauseSize() &&
        !asnOptions.IsDecodeIgnoreOctetStringSizeConstraint())
    {
        if (GetSize() > GetDescription().GetMaxSize())
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_INVALID_OCTET_STRING_SIZE, 
                characters);
        }

        if (GetSize() < GetDescription().GetMinSize())
        {
            ASN_THROW_CHARACTERS_DECODE_ERROR(
                ASN_E_INVALID_OCTET_STRING_SIZE, 
                characters);
        }
    }
}

void 
AsnOctetString::InternalDecodeFromXml(
                Characters& characters, 
                const AsnOptions& asnOptions,
                size_t level,
                const AsnDescObject& description)
{
    DecodeXmlElementStartTag(characters, asnOptions, level, description);

    XmlContent content(*this);   

    content.DecodeAsOctetString(characters, asnOptions);

    string str = content.GetString();

    ITS_ASSERT(str.size() % 2 == 0);

    _data.erase(_data.begin(), _data.end());
    _data.reserve(str.size() / 2);

    char    byteStr[3];
    int     byteVal;

    byteStr[2] = '\0';

    for (size_t i = 0; i < str.size(); i++)
    {
        if (i % 2 == 0)
        {
            byteStr[0] = str[i];
        }
        else
        {
            byteStr[1] = str[i];
            int numFields = sscanf(byteStr, "%02X", &byteVal);
            ITS_ASSERT(numFields == 1);
            _data.push_back((byte)byteVal);
        }
    }

    DecodeXmlElementEndTag(characters, asnOptions, level, description);

    DecodeCheck(characters, asnOptions);
}

bool 
AsnOctetString::Equals(const AsnObject& rhs) const
{ 
    const AsnOctetString* other = static_cast<const AsnOctetString*>(&rhs);
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
AsnOctetString::Print(ostream& os, size_t level) const
{
    static const int ROW_LENGTH = 10;

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
            os << ByteToHexString(_data[i * divisor + j]);
            os << " ";
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
        os << ByteToHexString(_data[i * divisor + j]);
        os << " ";
    }

    if (remainder != 0 && quotient != 0)
    {
        for (int j = 0; j < divisor - remainder; j++)
        {
            os << "   ";
        }
    }

    os << "]" << endl;
}

} // namespace its.
