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
//   ID: $Id: isdnaddress.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG: $Log: isdnaddress.cpp,v $
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#include <bssaple/ie/isdnaddress.h>


namespace bssaple
{

namespace ie
{

const int MAX_ISDNADDRESS_SIZE = sizeof(ITS_OCTET)*9;


ISDNAddress::ISDNAddress(const ITS_OCTET *buf,int len)
: InfoElement(InfoElement::ISDN_ADDRESS,len)
{
	if(len < 1)
	{
        ITN_THROW(DecodeException,"Invalid IE Length for ISDN Address IE. Must at least be 1");
	}
	else if(len <= MAX_ISDNADDRESS_SIZE)
    {
        ext &= ~0x80U;
        ext |= buf[0] & 0x80U; 

        natureAddress &= ~0x70U;
        natureAddress |= buf[0] & 0x70U;

        numberPlan &= ~0xFFU;
        numberPlan |= buf[0] & 0x0FU;

        memcpy(digits,&buf[1],sizeof(ITS_OCTET)*(len-1));
    }
    else
    {
        ITN_THROW(DecodeException,"Length exeeded for ISDN Address");
    } 
}


int ISDNAddress::Encode (ITS_OCTET* buf, int& len) const
{
    len = length+sizeof(ITS_OCTET)*2;

    buf[0] = id;
    buf[1] = length;

    buf[2] &= ~0x80U;
    buf[2] |= ext & 0x80U;

    buf[2] &= ~0x70U;
    buf[2] |= natureAddress & 0x70U;

    buf[2] &= ~0x0FU;
    buf[2] |= numberPlan & 0x0FU;
    
    memcpy(&buf[3],digits,length * sizeof(ITS_OCTET));

    return CODEC_SUCCESS;

}

void ISDNAddress::SetDigits (ITS_OCTET* dig, int len)
{
    if(((double)len)/2 > MAX_ISDNADDRESS_SIZE -1)
    {
        ITN_THROW(InvalidData,"Invalid data seting for ISDN Address");
    }

    int j=0;
    length += ((len%2 ==0) ? len/2 : ((len/2)+1)); 
    for(int i=0; i < len; ++i)
    {
        digits[j] &= ~0x0FU;
        digits[j] |= dig[i] & 0x0FU;

        digits[j] &= ~0xF0U;
        digits[j] |= (dig[++i] << 4) & 0xF0U;

        ++j;
        if(  (i+2 == len) )
        {
            digits[j] &= ~0x0FU;
            digits[j] |= dig[i+1] & 0x0FU;

            digits[j] &= ~0xF0U; //Set these bit as 1111
            digits[j]  |= 0xF0U; //this is just fill.
            break;
        }
    }
}

void ISDNAddress::GetDigits (ITS_OCTET* dig, int& len) const
{
    len = (length-1) *2;
    int j=0;   
    for(int i=0; i < (length-1) *2; ++i)
    {
        dig[i] = digits[j] & 0x0FU; 

        dig[++i] = (digits[j] >> 4) & 0x0FU;

        if(j == (length-2)) 
        {
            if(dig[i] == 0x0F)
            {
                --len;
                break;
            }
        }
        j++;
    } 
}


void ISDNAddress::PrintIE(std::ostream &out) const
{
    out<<"     IE ISDN Adrress "<<std::endl;
    out<<"     [ "<<std::endl;
    out<<"\tEXT  0x"<<std::hex<<(int)GetExt()<<std::endl;
    out<<"\tnatureAddress  0x"<<std::hex<<(int)((natureAddress >> 4) & 0x07)
                                                                <<std::endl;
    out<<"\tnumberPlan   0x"<<std::hex<<(int)(numberPlan & 0x0FU)<<std::endl;

    int nodits;
    ITS_OCTET buf[16];

    GetDigits(buf,nodits);

    for(int i=0;i < nodits;++i)
    {
        out<<"\tDigits   0x"<<std::hex<<(int)(buf[i])<<std::endl;
    }

    out<<"     ]"<<std::endl<<std::endl;

}

} // namespace ie    
} // namespace bssaple    


