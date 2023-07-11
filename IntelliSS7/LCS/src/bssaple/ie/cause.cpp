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
//   ID: $Id: cause.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG: $Log: cause.cpp,v $
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bssaple/ie/cause.h>

#define C_EXT_BIT                0x80U
#define C_CAUSE_VAL_WITH_0_BIT   0x7FU
#define C_CAUSE_VAL_WITH_1_BIT   0x70U

namespace bssaple  {     
namespace ie   {     

// Class bssaple    ::ie    ::Cause 


Cause::Cause(const ITS_OCTET* buf,int len):InfoElement(InfoElement::CAUSE,len)
{

   if(len == sizeof(ITS_OCTET)*2)
   {
        ext =1;
        if((buf[0] & 0x0FU )== 0x00)
        {
            natFlag =1;
        }
        else
        {
            natFlag =0;
        }
        memcpy(cause,buf,sizeof(ITS_OCTET)*len);
    }
    else if(len == sizeof(ITS_OCTET))
    {
        cause[0] = buf[0];
    }
    else
    {
        ITN_THROW(DecodeException,"length exeeded than max size");
    }

}

int Cause::Encode (ITS_OCTET* buf, int& len) const
{
    buf[0] = id;
    buf[1] = length;
    memcpy(&buf[2],cause,(sizeof(ITS_OCTET)*length)); 
    len = length + sizeof(ITS_OCTET)*2;
    return (CODEC_SUCCESS);
}

void Cause::SetCauseValue(bool isExt,ITS_OCTET cause1,ITS_OCTET cause2) 
{
    ext = isExt;
    cause[0] &= ~C_EXT_BIT;
    cause[0] |= (isExt << 7) & C_EXT_BIT;

    cause[0] &= ~C_CAUSE_VAL_WITH_0_BIT;
    cause[0] |= cause1 & C_CAUSE_VAL_WITH_0_BIT;


    if (isExt) //two Octets
    {
        if ((cause1 & 0x0F) == 0)   //cause1 = xxx 0000
        {
            ITN_THROW(InvalidData,"Inapropriate seting of data");        
        }
        else
        {
            cause[1] = cause2 & 0xFFU;
        }
        length += sizeof(ITS_OCTET);
    }
}

void  Cause::SetNationalCause(Cause::CauseClass natclass,CauseValue causeVal)
{
    ext = 1;
    natFlag = 1;
    if(natclass & 0x07 != 0x00)
    {
        ITN_THROW(InvalidData,"Inapropriate seting of data");
    }
    else //if ext(bit 7) is 1, the cause value is a 2 octet field
        //if 1st octet is 1XXX 0000, the 2nd is reserved for national app
    {
        cause[0] &= ~C_CAUSE_VAL_WITH_1_BIT;
        cause[0] |= (natclass << 4) & C_CAUSE_VAL_WITH_1_BIT;    
        cause[1] = causeVal & 0xFF;
    }

    length +=sizeof(ITS_OCTET);
}

void Cause::GetCauseValue (bool& isExt,bool &isNat,
                            ITS_OCTET& causeORclass1,ITS_OCTET&cause2) const
{
    isExt = ext;
    isNat = natFlag;

    if(!isExt)  //one Octet
    {
        causeORclass1 = cause[0];    
    }
    else  //two Octets, 1st contains the cause(or)class, 2nd cause
    {
        if(!natFlag)
        {
            causeORclass1 = cause[0]; 
        }
        else
        {
            causeORclass1 = (cause[0] & C_CAUSE_VAL_WITH_1_BIT) >> 4;
        }
        cause2 = cause[1];
    }
}

void Cause::PrintIE(std::ostream &out) const
{
    char buf[100];

    out<<"     IE Cause"<<std::endl;
    out<<"     ["<<std::endl;
    if(!ext)
    {
        out<<"Cause "<<std::hex<<(int)(cause[0])<<std::endl;
    }
    else
    {
        if(!natFlag)
        {
            out<<"\t\tCause OR Value  0x"<<std::hex<<(int)( cause[0])<<std::endl;
            out<<"\t\tCause  0x"<<std::hex<<(int)( cause[1])<<std::endl;
        }
        else
        {
            out<<"\t\tClass   0x"<<std::hex<<(int)(cause[0]>>4)<<std::endl;
            out<<"\t\tCause   0x"<<std::hex<<(int)(cause[1])<<std::endl;
        }
    }
    out<<"     ]"<<std::endl<<std::endl;

}


}//ie namespace

}//le namespace


