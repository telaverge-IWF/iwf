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
// LOG: $Log: Octets.cpp,v $
// LOG: Revision 9.2.64.1  2014/09/16 09:34:53  jsarvesh
// LOG: Changes done for removing warnings
// LOG:
// LOG: Revision 9.2.60.1  2014/09/15 07:20:41  jsarvesh
// LOG: Changes done for removing Warnings
// LOG:
// LOG: Revision 9.2  2007/01/10 11:15:07  yranade
// LOG: Merge changes from 6.5.3 and Lucent branches
// LOG:
// LOG: Revision 9.1.10.4  2005/10/27 08:58:00  dsatish
// LOG: Fix to throw exception(haltaf)
// LOG:
// LOG: Revision 9.1.10.3  2005/10/24 13:06:13  dsatish
// LOG: Choice index problem fix(Althaf)
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
// LOG: Revision 8.2  2005/03/21 13:51:21  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:46  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:18  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.4  2002/01/17 17:21:21  hdivoux
// LOG: Update for missing level argument in print.
// LOG:
// LOG: Revision 5.3  2002/01/16 22:13:42  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:27  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: Octets.cpp,v 9.2.64.1 2014/09/16 09:34:53 jsarvesh Exp $"

//
// ASN.1 runtime Octets class implementation.
//

#include <stdio.h>

#include <Octets.h>

#include <Asn.h>
#include <AsnException.h>

using namespace std;

namespace its
{

bool 
Octets::Equals(const Octets& rhs) const
{
    if (_offset != rhs._offset || GetSize() != rhs.GetSize())
    {
        return false;
    }

    for (size_t i = 0; i < GetSize(); i++)
    {
        if (_data[i] != rhs._data[i])
        {
            return false;
        }
    }

    return true;
}

void 
Octets::Print(ostream& os, size_t level) const
{
    PrintArray(_data, os, level);
}

void 
Octets::PrintWithOffset(ostream& os, size_t level) const
{
    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << "[ offset = ";
    os << _offset;
    os << " ]";
    os << endl;

    PrintArray(_data, os, level);
}

static string 
ByteToHexString(byte b)
{
    char strBuf[4];
    memset(strBuf, 0, 4);

    sprintf(strBuf, "%02X", b);

    string result = strBuf;

    return result;
}

void 
Octets::PrintArray(const vector<byte>& array, ostream& os, size_t level)
{
    static const int ROW_LENGTH = 10;

    string levelShift = GetLevelShift(level);

    os << levelShift;
    os << "[ ";

    int divisor = ROW_LENGTH;

    ITS_THROW_ASSERT(divisor > 1);

    int quotient  = array.size() / divisor;
    int remainder = array.size() % divisor;

    int i = 0;
        
    for (i = 0; i < quotient; i++)
    {
        for (int j = 0; j < divisor; j++)
        {
            os << ByteToHexString(array[i * divisor + j]);
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
        os << ByteToHexString(array[i * divisor + j]);
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

// Helper function to get level shift string (four spaces multiplied by level).

string 
Octets::GetLevelShift(size_t level)
{
#if defined(__SUNPRO_CC)

    string result = "    "; // Require by Sun CC 5.2 C++ runtime (bug).

#else // !defined(__SUNPRO_CC)

    string result;

#endif // defined(__SUNPRO_CC)

    result.reserve((level + 1) * 4);

    result.append(level * 4, ' ');

    return result;
}

void 
Octets::SkipPaddingBits()
{
    if (_bitPos != 0)
    {
        _offset++;
        _bitPos = 0;
    }
}

void 
Octets::AddPaddingBits()
{
    if (_bitPos != 0)
    {
        _data.push_back(_value);
        _value = 0;
        _bitPos = 0;
    }
}

void
Octets::SetBit(bool val)
{
    if (val)
    {
        _value = _value | (0x80 >> _bitPos);
    }

    _bitPos++;

    if ((_bitPos % 8) == 0)
    {
        _data.push_back(_value);
        _value = 0;
        _bitPos = 0;
    }
}

void
Octets::SetBits(ITS_OCTET val, int len)
{
    if (len > 8)
        return;

    for (int i = 0; i < len; i++)
    {
        SetBit ((val & (0x80 >> (8 - len + i)))?true:false);
    }
}

bool
Octets::GetNextBit()
{
    bool ret = false;

    if ((_offset < _data.size()) &&
        (_data[_offset] & (0x80 >> _bitPos)))
    {
        ret = true;
    }

    _bitPos++;

    if (!(_bitPos % 8))
    {
        _offset++;
        _bitPos = 0;

    }

    return ret;
}

ITS_UINT
Octets::GetBits(int len)
{
    int tmpLen = len;
    ITS_UINT val = 0;

    while (tmpLen > 8)
    {
        val = (val << 8) | GetNextOctet();
        tmpLen -= 8;
    }

    for (int i = 0; i < tmpLen; i++)
    {
        val = (val << 1) | ((GetNextBit())?1:0);
    }

    return val;
}


ITS_OCTET 
Octets::GetNextOctet()
{
    ITS_OCTET ret = 0;

    if (_offset < _data.size())
    {
        ret = _data[_offset];
        _offset++;
        _bitPos = 0;
    }
    else
    {
        throw AsnDecodeError(ASN_E_INVALID_OCTET_POS, "invalid octet position", *this);
    }

    return ret;
}

void 
Octets::SetOctet(ITS_OCTET oct)
{
    if (_value != 0)
    {
        _data.push_back(_value);
        _value = 0;
        _bitPos = 0;
    }

    _data.push_back(oct);
}

void 
Octets::GetOctetArray (ITS_OCTET* octet, ITS_UINT len)
{
    unsigned int i = 0;
    if (!octet)
        return;

    for (i = 0; i < len; i++)
    {
        octet[i] = _data[_offset];
        _offset++;
    }
}

void 
Octets::SetOctetArray (ITS_OCTET* octet, ITS_UINT len)
{
    unsigned int i = 0;
    if (!octet)
        return;

    if (_value != 0)
    {
        _data.push_back(_value);
        _value = 0;
        _bitPos = 0;
    }

    for (i = 0; i < len; i++)
    {
        _data.push_back(octet[i]);
    }
}

ostream& 
operator<<(ostream& os, Octets& octets)
{
    octets.Print(os);
    return os;
}

} // namespace its.


