//////////////////////////////////-*-C++-*-///////////////////////////////////
//                                                                          //
//     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    //
//             Manufactured in the United States of America.                //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
//                                                                          //
//   This product and related documentation is protected by copyright and   //
//   distributed under licenses restricting its use, copying, distribution  //
//   and decompilation.  No part of this product or related documentation   //
//   may be reproduced in any form by any means without prior written       //
//   authorization of IntelliNet Technologies and its licensors, if any.    //
//                                                                          //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      //
//   government is subject to restrictions as set forth in subparagraph     //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software       //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                        //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// CONTRACT: INTERNAL                                                       //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////
//
//   ID: $Id: frequencylist.cpp,v 1.1.2.2 2010/08/12 08:17:10 rajeshak Exp $
//
//  LOG: $Log: frequencylist.cpp,v $
//  LOG: Revision 1.1.2.2  2010/08/12 08:17:10  rajeshak
//  LOG: Fix Issue:3351
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bsslap/ie/frequencylist.h>
#include <math.h>

namespace bsslap
{
namespace ie
{
///////////////////////////////////////////////////////////////////////
// Constructor: call corresponding decode utilitis
///////////////////////////////////////////////////////////////////////

FrequencyList::FrequencyList(const ITS_OCTET* buf, int &len)
    :InfoElement(FREQUENCY_LIST)
{
    if (len >= buf[0])
    {
        param_length = buf[0];
        highpart_formatID = buf[1] >> 6;
        lowpart_formatID = (buf[1] & 0x0EU) >> 1;  

        if (highpart_formatID == BITMAP)
        {
            DecodeBitMapFormat(buf, len);            
        }
        else if (highpart_formatID == NON_BITMAP)
        {
            if (lowpart_formatID < 0x04U)
            {
                DecodeRange1024Format(buf, len);
            }
            else
            {
                switch(lowpart_formatID)
                {
                case RANGE512:
                    DecodeRange512Format(buf, len);
                    break;
                case RANGE256:
                    DecodeRange256Format(buf, len);
                    break;
                case RANGE128:
                    DecodeRange128Format(buf, len);
                    break;
                case VARIABLE_BITMAP:
                    DecodeVariableBitMapFormat(buf, len);
                default:
                    ITN_THROW(IllegalArgumentException, 
                                "Not Valid Low Part Format ID");
                    break;
                }
            }
            
            //ielen += buf[0];
        }
        else
        {        
            ITN_THROW(IllegalArgumentException, 
                                "Not Valid High Part Format ID!");
        }
    }
    else
    {
        ITN_THROW(IllegalArgumentException, "Invalid IE length");
    }
    //len = ielen;
}

//////////////////////////////////////////////////////////////////////
// Utility function for decode Bit Map format
//////////////////////////////////////////////////////////////////////

void FrequencyList::DecodeBitMapFormat(const ITS_OCTET* buf, int& len)
{
    bool arfcn_bitmap[124];
    int i, j;
    int ielen = 1;

    arfcn_bitmap[124] = (buf[1] & 0x08U) >> 3;
    arfcn_bitmap[123] = (buf[1] & 0x04U) >> 2;
    arfcn_bitmap[122] = (buf[1] & 0x02U) >> 1;
    arfcn_bitmap[121] = buf[1] & 0x01;

    for ( j = 16; j > 1; --j )
    {
        for (i = 1; i <= 15; ++i)
        {
            arfcn_bitmap[8*i - 7] = (buf[j] & 0x01);
            arfcn_bitmap[8*i - 6] = (buf[j] & 0x02) >> 1;
            arfcn_bitmap[8*i - 5] = (buf[j] & 0x04) >> 2;
            arfcn_bitmap[8*i - 4] = (buf[j] & 0x08) >> 3;
            arfcn_bitmap[8*i - 3] = (buf[j] & 0x10) >> 4;
            arfcn_bitmap[8*i - 2] = (buf[j] & 0x20) >> 5;
            arfcn_bitmap[8*i - 1] = (buf[j] & 0x40) >> 6;
            arfcn_bitmap[8*i] = buf[j]  >> 7;
        }
    }
    ielen += 16;
    for (int freqlist = 1; freqlist < 125; ++freqlist)
    {
        if (arfcn_bitmap[freqlist])
        {
            arfcn.push_back(freqlist);
        }
    }
    len = ielen;
}

//////////////////////////////////////////////////////////////////////
// Decode range 1024 format
//////////////////////////////////////////////////////////////////////

void FrequencyList::DecodeRange1024Format(const ITS_OCTET* buf, int& len)
{
    int index = 1023;
    int M = 10;
    int ielen = 1;
    ITS_USHORT W[1024];

    int bit_offset = 6;
    for ( int i = 1 ; i < 256; ++i )
    {
        if (buf[i] != NULL)
            RetreiveValueOfW (W, buf, M, bit_offset);
        else
            buf[++i] == NULL;
    }
    ielen += buf[0];
    len = ielen;
}

//////////////////////////////////////////////////////////////////////
//  Retrieve all of W(i) for F(i)
//  from 1024 and 512 format
//////////////////////////////////////////////////////////////////////

void FrequencyList::RetreiveValueOfW (ITS_USHORT* W, 
                                      const ITS_OCTET* byte_offset,
                                      int M, 
                                      int& bit_offset)
{
    int i = 0;

    for ( int k = 0; k < M; ++k )
    {
        for ( i = pow((double)2, k); i < pow((double)2, k + 1); ++i )
        {
            W[i] = GetCalculationOfW(M - k, byte_offset, bit_offset);

        }
    }
    
    ComputeFrequency(i, W, M);
}

/////////////////////////////////////////////////////////////////////
// Algorithm for each W computation
/////////////////////////////////////////////////////////////////////

ITS_USHORT FrequencyList::GetCalculationOfW (int bits, 
                                       const ITS_OCTET* byte_offset, 
                                       int& bit_offset)
{
    ITS_USHORT  value;

    value = (*byte_offset << 8) | *(byte_offset + 1);
    value = value << bit_offset;
    value = value >> 16 - bits;
    bit_offset += bits;

    while ( bit_offset > 7 ) 
    {
        *byte_offset++;
        bit_offset -= 8;
    }

    return value;
}
 
//////////////////////////////////////////////////////////////////////
// Frequency computation algorithm for range 1024 format ~ 128 format
// a little complicate according to 3GPP GSM 04.08 specification
//////////////////////////////////////////////////////////////////////

void FrequencyList::ComputeFrequency (int size,
                                      ITS_USHORT* W,
                                      int indicator )
{
    ITS_USHORT N;           // temp varible for calculation

    int rangeOfFormat;      // numerator

    switch (indicator)      
    {
    case 10:
        rangeOfFormat = 1024;
        break;
    case 9:
        rangeOfFormat = 512;
        break;
    case 8:
        rangeOfFormat = 256;
        break;
    case 7:
        rangeOfFormat = 128;
        break;
    }

    int j ;      // denominator

    int exponent = 0 ;  //

    for (int index = 1; index <= size; ++index)
    {
        j = pow((double)2, exponent);

        if ( index - j < j )  // check if j value is the greatest 
                              // power of 2 less or eq to index
        {
            N = W[index];

            while ( index > 1 )
            {
                if ( (2 * index) < (3 * j) )
                {
                    index = index - j / 2;

                    N = (N + W[index] - rangeOfFormat / j - 1) %
                            (rangeOfFormat * 2 / j - 1) + 1;
                }
                else
                {
                    index = index - j;

                    N = (N + W[index] - 1) % 
                            ((rangeOfFormat * 2 / j) - 1) + 1;
                }

                j = j / 2;

            }   // end of while loop

           frequencyList.push_back(N);    // get frequency finally

        }   // end of if

        else    // increase j value close to i by exponent increment
        {
            ++exponent;
        }

    } // end of for loop
}

//////////////////////////////////////////////////////////////////////
// Decode range 512 format
//////////////////////////////////////////////////////////////////////

void FrequencyList::DecodeRange512Format(const ITS_OCTET* buf, int& len)
{
    int index = 512;
    int M = 9;
    int ielen = 1;
    ITS_USHORT W[512];

    ITS_USHORT orig_arfcn;
    
    orig_arfcn = ((((buf[1] << 8) | buf[2]) << 7) | (buf[3] >> 1)) >> 6;
    arfcn.push_back(orig_arfcn);

    int bit_offset = 1;

    for ( int i = 3 ; i < 256; ++i )
    {
        if (buf[i] != NULL)
            RetreiveValueOfW (W, buf, M, bit_offset);
        else
            buf[++i] == NULL;
    }
    ielen += buf[0];
    len =ielen;

}

//////////////////////////////////////////////////////////////////////
// Decode range 256 format
//////////////////////////////////////////////////////////////////////

void FrequencyList::DecodeRange256Format(const ITS_OCTET* buf, int& len)
{
    int index = 256;
    int M = 8;
    int ielen = 1;
    ITS_USHORT W[256];

    ITS_USHORT orig_arfcn;

    //orig_arfcn = ((buf[1] << 8 | buf[2]) << 7) | (buf[3] << 7);
    //orig_arfcn = orig_arfcn >> 7;

    orig_arfcn = ((((buf[1] << 8) | buf[2]) << 7) | (buf[3] >> 1)) >> 6;
    arfcn.push_back(orig_arfcn);

    int bit_offset = 1;
    for ( int i = 3; i < 256; ++i )
    {
        if (buf[i] != NULL)
            RetreiveValueOfW(W, buf, M, bit_offset);
        else
            buf[++i] == NULL;
    } 
    ielen += buf[0];
    len =ielen;
}

//////////////////////////////////////////////////////////////////////
// Decode range 128 format
//////////////////////////////////////////////////////////////////////

void FrequencyList::DecodeRange128Format(const ITS_OCTET* buf, int& len)
{
    int index = 128;
    int M = 7;
    int ielen = 1;
    ITS_USHORT W[128];

    ITS_USHORT orig_arfcn;

    orig_arfcn = ((((buf[1] << 8) | buf[2]) << 7) | (buf[3] >> 1)) >> 6; 
    arfcn.push_back(orig_arfcn);

    int bit_offset = 1;
    for (int i = 3; i < 256; ++i)
    {
        if (buf[i] != NULL)
            RetreiveValueOfW(W, buf, M, bit_offset);    
        else
            buf[++i] == NULL;
    }
    ielen += buf[0];
    len =ielen;
}

//////////////////////////////////////////////////////////////////////
// Decode variable bit map format
//////////////////////////////////////////////////////////////////////

void FrequencyList::DecodeVariableBitMapFormat(const ITS_OCTET* buf, int& len)
{
    ITS_USHORT orig_arfcn;
    int ielen = 1;
    orig_arfcn = ((((buf[1] << 8) | buf[2]) << 7) | (buf[3] >> 1)) >> 6;
    arfcn.push_back(orig_arfcn);
    
    int M = 127;
    bool rrfcn_bitmap[1023];

    for (int i = 1; i < 8; ++i)
    {
        rrfcn_bitmap[i] = (buf [1] << i) >> 7;
    }

    for (int k = 2; k < 256; ++k)
    {
        for (int j = 0; j < 128; ++j)
        {
            for (int m = 0; m < 8; ++m)
            {
                rrfcn_bitmap[8 * j + m] = (buf[k] << m) >> 7;
            }
        }
    }
    ielen += buf[0];
    len = ielen;

    for (int freqlist = 1; freqlist <= 1023; ++freqlist)
    {
        if (rrfcn_bitmap[freqlist])
        {
            rrfcn.push_back(freqlist);
        }
    }
    
}

/////////////////////////////////////////////////////////////////////
//  Encode function
/////////////////////////////////////////////////////////////////////

void FrequencyList::Encode(ITS_OCTET *buf, int& len) const
{
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
    buf[0] = param_id;

    if (buf[1] == 0x10)
        // bitmap 0 encode
    {
        len = 16 + 2 * sizeof(ITS_OCTET);
        EncodeBitMapFormat(buf, len);   
    }
    else if (highpart_formatID == NON_BITMAP)
    {
        // len = ;
        lowpart_formatID = (buf[1] & 0x0EU) >> 1;

        if (((buf[2] & 0x0EU) >> 1) < 0x04U)
        {
            EncodeRange1024Format(buf, len);
        }
        else
        {
        }
    }
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/        
}

//////////////////////////////////////////////////////////////////////
//  Print function
//////////////////////////////////////////////////////////////////////

void FrequencyList::Print(std::ostream& out) const
{
    ArfcnVector::const_iterator ait;
    RrfcnVector::const_iterator rit;

    int i,j;
    out << "\tFrequencyList\n[\n" ;

    for (ait = arfcn.begin(),i = 0; ait !=arfcn.end(); ++ait, ++i)
    {
    	out << "\tarfcn[" <<i<<"] ( 0x" << std::hex << (int)*ait <<" )\n";
    }
    for (rit = rrfcn.begin(),j = 0; rit !=rrfcn.end(); ++rit, ++j)
    {
        out << "\trrfcn[" <<j<<"] ( 0x" << std::hex << (int)*rit <<" )\n";
    }
    out << "\t]\n" ;
}

} //ie namespace
} //bsslap namespace

