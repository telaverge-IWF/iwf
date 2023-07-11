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
//   ID: $Id: signalingpointcode.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG: $Log: signalingpointcode.cpp,v $
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#include <bssaple/ie/signalingpointcode.h>


namespace bssaple
{

namespace ie
{

SignalingPointCode::SignalingPointCode(const ITS_OCTET *buf,int len)
:InfoElement(InfoElement::SIGNALING_POINT_CODE,len)
{
    if(len == sizeof(ITS_OCTET) *2)
    {
        sigpc = buf[0] << 8 | buf[1];
    }
    else
    {
        sigpc = ((buf[0]  << 16) & 0x00FF0000U) |
                 ((buf[1]  << 8) & 0x0000FF00U) |
                      ((buf[2] ) & 0x000000FFU);
    }
}

int SignalingPointCode::Encode (ITS_OCTET* buf, int& len) const
{
    len = length + sizeof(ITS_OCTET)*2;
    buf[0] = id;
    buf[1] = length;
    
    if(length == sizeof(ITS_OCTET) *2)
    {
        buf[2] = sigpc >> 8 & 0xFFU;
        buf[3] = sigpc & 0xFFU;
    }
    else
    {
        buf[2] = sigpc >> 16 & 0xFFU;
        buf[3] = sigpc >> 8 & 0xFFU;
        buf[4] = sigpc & 0xFFU;
    }
    return CODEC_SUCCESS;
}

void SignalingPointCode::PrintIE(std::ostream & out) const
{
    out<<"      IE SignalingPointCode "<<std::endl;
    out<<"      [ "<<std::endl;
    out<<"\t\tSignalPointCode  0x"<<std::hex<<(int)sigpc<<std::endl;
    out<<"      ]"<<std::endl<<std::endl;
}

} // namespace ie
} // namespace bssaple


