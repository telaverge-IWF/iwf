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
// LOG: $Log: AsnWholeNumber.cpp,v $
// LOG: Revision 9.1.64.1  2014/09/16 09:34:53  jsarvesh
// LOG: Changes done for removing warnings
// LOG:
// LOG: Revision 9.1.60.1  2014/09/15 07:20:41  jsarvesh
// LOG: Changes done for removing Warnings
// LOG:
// LOG: Revision 9.1  2007/01/10 11:15:07  yranade
// LOG: Merge changes from 6.5.3 and Lucent branches
// LOG:
// LOG: Revision 1.1.2.2  2005/10/06 12:12:56  mmanikandan
// LOG: Exception Handling in PER and Code Review Changes.
// LOG:
// LOG: Revision 1.1.2.1  2005/09/06 09:19:08  mmanikandan
// LOG: Initial commit for ASN.1 PER.
// LOG:
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: AsnWholeNumber.cpp,v 9.1.64.1 2014/09/16 09:34:53 jsarvesh Exp $"

#include <AsnWholeNumber.h>

namespace its {

const std::string errorStr="ASN Whole Number Encoding";
int
AsnWN::EncodeNSNNWN(Octets& octs, ITS_UINT val, const AsnOptions& asnOptions)
{
    if (val < 64)
    {
        octs.SetBit(false);
        octs.SetBits(val, 6);
    }
    else
    {
        octs.SetBit(true);
        EncodeSCWN(octs, val, asnOptions);
    }

    return ITS_SUCCESS;
}

ITS_UINT 
AsnWN::DecodeNSNNWN(Octets& octs, const AsnOptions& asnOptions)
{
    ITS_UINT val = 0;

    if (octs.GetNextBit())
    {
        val = DecodeSCWN(octs, asnOptions);
    }
    else
    {
        val = octs.GetBits(6);
    }

    return val;
}

int 
AsnWN::EncodeSCWN(Octets& octs, unsigned int val, const AsnOptions& asnOptions)
{
    std::vector<ITS_OCTET> arr;

    octs.AddPaddingBits();
    union
    {
        unsigned int value;
        unsigned char valArr[4];
    }intVal;
    intVal.value = val;
    int i;
    for(i =0; i < 4 && intVal.valArr[3-i]==0; ++i);
    //set length first
    octs.SetOctet(4-i);
    for(int j=3-i; j>=0; j--)
    {
       octs.SetOctet(intVal.valArr[j]);
    }
    return ITS_SUCCESS;
}

unsigned int 
AsnWN::DecodeSCWN(Octets& octs, const AsnOptions& asnOptions)
{
    unsigned int val = 0;
    std::vector<ITS_OCTET> arr;

    octs.SkipPaddingBits();
    int len = octs.GetNextOctet();
    if(len > 4)
    {
	throw AsnDecodeError(ASN_E_UNEXPECTED_LARGE_LENGTH, errorStr, octs);
    }
    for(int i = 0; i < len; i++)
    {
        val = (val << 8) | octs.GetNextOctet();
    }
    return val;
}

int
AsnWN::EncodeCWN(Octets& octs, int lb, int ub, int eval, const AsnOptions& asnOptions, bool _signedInt)
{
    unsigned int range;
    ITS_UINT val;
    if(_signedInt)
    {
        range = ub - lb;
        val = eval - lb;
    }
    else
    {   
        range = (ITS_UINT)ub - (ITS_UINT)lb;
        val = (ITS_UINT)eval - (ITS_UINT)lb;
    }
    int len = 0;
    if (val > range)
    {
        return !ITS_SUCCESS;
    }
    if(range < 0xFFFFFFFF)
    {
       range++;
    }
    if (range < 256)
    {
        std::vector<bool> arr;

        if (range <= 2)
        {
            len = 1;
        }
        else if (range <= 4)
        {
            len = 2;
        }
        else if (range <= 8)
        {
            len = 3;
        }
        else if (range <= 16)
        {
            len = 4;
        }
        else if (range <= 32)
        {
            len = 5;
        }
        else if (range <= 64)
        {
            len = 6;
        }
        else if (range <= 128)
        {
            len = 7;
        }
        else
        {
            len = 8;
        }

        octs.SetBits(val, len);
    }
    else if (range == 256)
    {
        octs.AddPaddingBits();
        octs.SetOctet(val);
    }
    else if (range <= K64)
    {
        octs.AddPaddingBits();
        octs.SetOctet((val & 0xff00) >> 8);
        octs.SetOctet(val & 0xff);
    }
    else
    {   
        Octets dummyOcts;
        EncodeSCWN(dummyOcts, val, asnOptions);
        //parsing EncodeSCWN adds one length octet at the begining, should be ignored
        size_t contentOctsSize = dummyOcts.GetSize()-1;
        switch(contentOctsSize)
        {
           case 1:
                 octs.SetBit(false);
                 octs.SetBit(false);
                 break;
           case 2:
                 octs.SetBit(false);
                 octs.SetBit(true);
                 break;
           case 3:
                 octs.SetBit(true);
                 octs.SetBit(false);
                 break;
           case 4:
                 octs.SetBit(true);
                 octs.SetBit(true);
                 break;
        }
        octs.AddPaddingBits();
        //i should start at 1, 0 refers to length, only contents to be considered here
        for(size_t i=1; i<=contentOctsSize; ++i)
        {
           octs.SetOctet(dummyOcts.GetOctetAt(i));
        }
    }

    return ITS_SUCCESS;
}

ITS_UINT
AsnWN::DecodeCWN(Octets& octs, int lb, int ub, const AsnOptions& asnOptions)
{
    int range = ub - lb + 1;
    ITS_UINT val = 0;
    int len = 0;

    if (range < 256)
    {
        if (range <= 2)
        {
            len = 1;
        }
        else if (range <= 4)
        {
            len = 2;
        }
        else if (range <= 8)
        {
            len = 3;
         }
        else if (range <= 16)
        {
            len = 4;
        }
        else if (range <= 32)
        {
            len = 5;
        }
        else if (range <= 64)
        {
            len = 6;
        }
        else if (range <= 128)
        {
            len = 7;
        }
        else
        {
            len = 8;
        }

        val = octs.GetBits(len);
    }
    else if (range == 256)
    {
        octs.SkipPaddingBits();
        val = octs.GetNextOctet();
    }
    else if (range <= K64)
    {
        octs.SkipPaddingBits();
        val = octs.GetNextOctet();
        val = (val << 8) | octs.GetNextOctet();
    }
    else
    {
        int numOct = 0;
         numOct = (numOct << 1) | (octs.GetNextBit()?1:0);
        numOct = (numOct << 1) | (octs.GetNextBit()?1:0);
        numOct++;

        octs.SkipPaddingBits();

        for (int i = 0; i < numOct; i++)
        {
            val = (val << 8) | octs.GetNextOctet();
        }
    }

    val += lb;

    return val;
}



ITS_UINT 
AsnWN::DecodeCWN(Octets& octs, int lb, int ub, const AsnOptions& asnOptions, bool& signedInt)
{
    unsigned int range;
    ITS_UINT val = 0;
    int len = 0;
    if(signedInt)
    {
        range = ub - lb;
    }
    else
    {
        range = (ITS_UINT)ub - (ITS_UINT)lb;
    }
    if(range < 0xFFFFFFFF)
    {
       range++;
    }
    if (range < 256)
    {
        if (range <= 2)
        {
            len = 1;
        }
        else if (range <= 4)
        {
            len = 2;
        }
        else if (range <= 8)
        {
            len = 3;
        }
        else if (range <= 16)
        {
            len = 4;
        }
        else if (range <= 32)
        {
            len = 5;
        }
        else if (range <= 64)
        {
            len = 6;
        }
        else if (range <= 128)
        {
            len = 7;
        }
        else
        {
            len = 8;
        }

        val = octs.GetBits(len);
    }
    else if (range == 256)
    {
        octs.SkipPaddingBits();
        val = octs.GetNextOctet();
    }
    else if (range <= K64)
    {
        octs.SkipPaddingBits();
        val = octs.GetNextOctet();
        val = (val << 8) | octs.GetNextOctet();
    }
    else
    {
        int numOct = 0;
        numOct = (numOct << 1) | (octs.GetNextBit()?1:0);
        numOct = (numOct << 1) | (octs.GetNextBit()?1:0);
        numOct++;
 
        octs.SkipPaddingBits();
 
        for (int i = 0; i < numOct; i++)
        {
            val = (val << 8) | octs.GetNextOctet();
        }
    }
    val += (signedInt ? lb : (ITS_UINT)lb);
    return val;
}

int 
AsnWN::EncodeUCWN(Octets& octs, int eval, const AsnOptions& asnOptions)
{
    std::vector<ITS_OCTET> arr;

    octs.AddPaddingBits();
    Encode2sComp(eval, arr);

    octs.SetOctet(arr.size());

    for (int i = arr.size(); i > 0; i--)
    {
        octs.SetOctet(arr[i-1]);
    }

    return ITS_SUCCESS;
}

int 
AsnWN::DecodeUCWN(Octets& octs, const AsnOptions& asnOptions)
{
    int val = 0;
    std::vector<ITS_OCTET> arr;

    octs.SkipPaddingBits();

    int len = octs.GetNextOctet();

    while (len)
    {
        arr.push_back(octs.GetNextOctet());
        len--;
    }

    val = Decode2sComp(arr);

    return val;
}

int
AsnWN::Encode2sComp(int val, std::vector<ITS_OCTET>& arr)
{
    int tmpVal = val;

    if (val < 0)
    {
        while (tmpVal != 0)
        {
            if ((tmpVal & 0xff) != 0xff)
            {
                arr.push_back(tmpVal & 0xff);
                tmpVal = (tmpVal >> 8) & 0x00ffffff;
            }
            else
            {
                tmpVal = 0;
            }
        }
    }
    else
    {
        while (tmpVal)
        {
            arr.push_back(tmpVal & 0xff);
            tmpVal = (tmpVal >> 8) & 0x00ffffff;
        }

        int size = arr.size();

        if (arr[size - 1] & 0x80)
        {
            arr.push_back(0x00);
        }
    }

    return ITS_SUCCESS;
}

int
AsnWN::Decode2sComp(std::vector<ITS_OCTET>& arr)
{
    int val = 0;
    unsigned int i = 0;

    if (arr.size() > 0)
    {
        if (arr[0] & 0x80)
        {
            val = arr[0] & 0x7f;
            i = 1;
        }

        for (; i < arr.size(); i++)
        {
            val = (val << 8) | arr[i];
        }

        if (arr[0] & 0x80)
        {
            val = 0 - ((0x01 << (arr.size() * 8 - 1)) - val);
        }
    }

    return val;
}
}
