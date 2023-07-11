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
//   ID: $Id: chosenchannel.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG: $Log: chosenchannel.cpp,v $
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bssaple/ie/chosenchannel.h>

namespace bssaple
{
namespace ie
{

ChosenChannel::ChosenChannel(const ITS_OCTET * buf,int len)
: InfoElement(InfoElement::CHOSEN_CHANNEL,len)
{
    if(len > sizeof(ITS_OCTET))
    {
        ITN_THROW(DecodeException,"Length Exeeded for choosen channel");
    }
    //mode_channel = buf[0];
    mode = (Mode)(buf[0] >> 4);
    channel = (Channel)(buf[0] & 0x0F);
}

int ChosenChannel::Encode (ITS_OCTET* buf, int& len) const
{
    buf[0] = id;
    buf[1] = sizeof(ITS_OCTET);
    buf[2] = (ITS_OCTET)((mode << 4) | channel);
    len = sizeof(ITS_OCTET)*3;
    return CODEC_SUCCESS;
}

void ChosenChannel::PrintIE(std::ostream &out) const
{
    out<<"     IE ChosenChannel"<<std::endl;
    out<<"     ["<<std::endl;
    out<<"\t\tChannel_Mode  0x"<<std::hex<<(int)(GetChannelMode ())<<std::endl;
    out<<"\t\tChannel_Value  0x"<<std::hex<<(int)(GetChannel ())<<std::endl;
    out<<"     ]"<<std::endl<<std::endl;
}


} // namespace ie    

} // namespace bssaple    


