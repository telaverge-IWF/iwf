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
//   ID: $Id: positioningdata.cpp,v 1.1.2.5 2010/05/10 13:05:03 rajeshak Exp $
//
//  LOG: $Log: positioningdata.cpp,v $
//  LOG: Revision 1.1.2.5  2010/05/10 13:05:03  rajeshak
//  LOG: Fix for Issue-ID: 2803, 2802, 2800, 2791
//  LOG:
//  LOG: Revision 1.1.2.4  2010/05/03 04:23:42  rajeshak
//  LOG: Fix for Issue-2710
//  LOG:
//  LOG: Revision 1.1.2.3  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.2  2010/03/25 06:31:29  rajeshak
//  LOG: API to get the Hex dump after encode/decode (for TDR).
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bssaple/ie/positioningdata.h>


namespace bssaple
{

namespace ie
{

PositioningData::PositioningData(const ITS_OCTET* buf, int len)
: InfoElement(InfoElement::POSITIONING_DATA,len)
{
    if(len > MAX_POSITIONING_METHODS)
    {
        ITN_THROW(DecodeException,"Length exeeded for PositioningData");
    }
    positioningDisc = buf[0];

    memcpy(postioningMethod_usage,&buf[1],len-1);

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

int PositioningData::Encode (ITS_OCTET* buf, int& len) const
{
    len = length + sizeof(ITS_OCTET)*2;
    buf[0] = id;
    buf[1] = length;
    buf[2] = positioningDisc;
    memcpy(&buf[3],postioningMethod_usage,length-sizeof(ITS_OCTET));

    ITS_OCTET * tmpPtr = (ITS_OCTET*)buf;
    int j=0;
    for(int i=0; i<len; i++)
    {
        snprintf((char*)&hexBuff[j], 2,"%X", ((tmpPtr[i]&0xF0)>>4));
        j++;
        snprintf((char*)&hexBuff[j], 2, "%X", (tmpPtr[i]&0x0F));
        j++;
    }
    hexBuff[j] = '\0';

    return CODEC_SUCCESS;
}

void PositioningData::SetPositioningMethodAndUsage(
                                PositioningData::MethodAndUsage *method,int len)
{
    if(len < MAX_POSITIONING_METHODS)
    {
        for(int i =0;i<len ;i++)
        {
            postioningMethod_usage[i] &= ~0xF8U;
            postioningMethod_usage[i] |= (method[i]._type << 3) & 0xF8U;

            postioningMethod_usage[i] &= ~0x07U;
            postioningMethod_usage[i] |= method[i]._usage & 0x07U;
        }
        length += len;
    }
    else
    {
        ITN_THROW(InvalidData,"Invalid seting of data PositioningData");
    }
}

void PositioningData::GetPositioningMethodAndUsage (
                            PositioningData::MethodAndUsage *method,int &len) const
{
    for(int i =0;i<=length-sizeof(ITS_OCTET) ;i++)
    {
        method[i]._type = (PositioningMethod)((postioningMethod_usage[i] >>
                                                                 3) & 0x1FU);
        method[i]._usage = (Usage)(postioningMethod_usage[i] & 0x07);
    }
    len = length-sizeof(ITS_OCTET);
                
}

void PositioningData::PrintIE(std::ostream &out) const
{
    out<<"     IE PositioningData "<<std::endl;
    out<<"     ["<<std::endl;
    out<<"\t\tPositioningDiscriminator    0x"<<std::hex<<(int)(positioningDisc)<<std::endl;
   
    out<<"\t\tPositioningMethod                 "<<"PositioningMethodUsage"
                                                           <<std::endl<<std::endl; 

    for(int i=0;i<length-1;i++)
    {
        out<<"\t\t0x"<<std::hex<<(int)((postioningMethod_usage[i] >> 3) & 0x1FU)<<"                                0x"<<std::hex<<(int)(postioningMethod_usage[i] & 0x07)<<std::endl;
    }
    out<<"     ]"<<std::endl<<std::endl;

}

} // namespace ie
} // namespace bssaple


