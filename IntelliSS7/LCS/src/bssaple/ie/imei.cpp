//////////////////////////////////-*-C++-*-///////////////////////////////////
//                                                                          //
//     Copyright 2010 IntelliNet Technologies, Inc. All Rights Reserved.    //
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
//   ID: $Id: imei.cpp,v 1.1.2.5 2010/05/10 13:05:03 rajeshak Exp $
//
//  LOG: $Log: imei.cpp,v $
//  LOG: Revision 1.1.2.5  2010/05/10 13:05:03  rajeshak
//  LOG: Fix for Issue-ID: 2803, 2802, 2800, 2791
//  LOG:
//  LOG: Revision 1.1.2.4  2010/05/03 04:23:42  rajeshak
//  LOG: Fix for Issue-2710
//  LOG:
//  LOG: Revision 1.1.2.3  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.2  2010/03/25 08:19:44  rajeshak
//  LOG: API to get the Hex dump after encode/decode (for TDR).
//  LOG:
//  LOG: Revision 1.1.2.1  2010/03/23 05:43:46  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: imei.cpp,v 1.1.2.5 2010/05/10 13:05:03 rajeshak Exp $"

#include <bssaple/ie/imei.h>


namespace bssaple
{

namespace ie
{

const int MAX_IMEI_DIGITS = 15;


IMEI::IMEI(const ITS_OCTET *buf,int len):InfoElement(InfoElement::IMEI,len)
{
    if(len < 1)
    {
        ITN_THROW(DecodeException,"Invalid IE length form IMEI. Must be at least 1");
    }
    else if((len * 2) <= (MAX_IMEI_DIGITS +1))
    {
        digit1_oddEven = buf[0];

        memcpy(digits,&buf[1],len-1);

        length = len;
    }
    else
    {
        ITN_THROW(DecodeException,"Length of buffer exeeded for IMEI");
    }

    ITS_OCTET * tmpPtr = (ITS_OCTET*)buf-2;
    int j=0;
    for(int i=0; i<len+2; i++)
    {
        snprintf((char*)&hexBuff[j], 2,"%X", ((tmpPtr[i]&0xF0)>>4));
        j++;
        snprintf((char*)&hexBuff[j], 2, "%X", (tmpPtr[i]&0x0F));
        j++;
    }
    hexBuff[j] = '\0';
}

void IMEI::SetDigits (ITS_OCTET* dig, int noDigits)
{
    if(noDigits <= MAX_IMEI_DIGITS)
    {
        length += noDigits / 2;
        if(noDigits%2 == 0)
        {
            digit1_oddEven &= 0xF0U;
        }
        else
        {
            digit1_oddEven &= ~0x0FU;
            digit1_oddEven |= 0x08U;
        }
         
        digit1_oddEven &= ~0xF0U;
        digit1_oddEven  |= ((dig[0] << 4) & 0xF0U);

        int i=1;
        int j=0;
        while(i < noDigits-1)
        {
            digits[j] &= ~0x0FU;
            digits[j] |= dig[i] & 0x0FU; 

            digits[j] &= ~0xF0U;
            digits[j] |= (dig[++i] << 4) & 0xF0U;

            i++;
            j++;

            if(((noDigits-1)%2) && (i == (noDigits-1)))
            {
                digits[j] &= ~0xF0U ;
                digits[j] = dig[i] & 0x0FU ;
                digits[j] |=  0xF0U ;
                break;
            }
            
        }
    }
    else
    {
        ITN_THROW(InvalidData,"maximum number digits exeeded for IMEI");
    }
}

void IMEI::GetDigits (ITS_OCTET* dig, int& noDigits) const
{
    if(GetOddEven ())
    {
        noDigits = length*2 -1;
    }
    else
    {
        noDigits = length*2 -2;
    }
    
    dig[0] = (digit1_oddEven >> 4) & 0x0FU;

    int i = 1;
    int j=0;
    while( i < noDigits)
    {
        dig[i] = digits[j] & 0x0FU;
        dig[++i] = (digits[j] >> 4) & 0x0FU ;

        i++;
        j++;
    
        if(((noDigits-1)%2) && (i == (noDigits-1)))
        {
            dig[i] = digits[j] & 0x0FU ;
            break;
        }
    }
}

int IMEI::Encode (ITS_OCTET* buf, int& len) const
{
    len = length + sizeof(ITS_OCTET)*2;

    buf[0] = id;
    buf[1] = length;

    buf[2] = digit1_oddEven;
    memcpy(&buf[3],digits,length-1);
    return CODEC_SUCCESS;
}

void IMEI::PrintIE(std::ostream &out) const
{
    ITS_OCTET  digt[16];
    int digLen;
    GetDigits(digt,digLen);
    out<<"     IE IMEI "<<std::endl;
    out<<"     [ ";
    for(int i=0;i<digLen;++i)
    {
        out<<"\t\tDigits  0x"<<std::hex<<(int)(digt[i])<<std::endl;
    }
    out<<"     ]"<<std::endl<<std::endl;
}

} // namespace ie    
} // namespace bssaple    


