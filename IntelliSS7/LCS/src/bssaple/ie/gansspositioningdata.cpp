//////////////////////////////////-*-C++-*-///////////////////////////////////
//                                                                          //
//     Copyright 2009 IntelliNet Technologies, Inc. All Rights Reserved.    //
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
//   ID: $Id: gansspositioningdata.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG: $Log: gansspositioningdata.cpp,v $
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2010/03/23 05:43:46  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: gansspositioningdata.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $"

#include <bssaple/ie/gansspositioningdata.h>

namespace bssaple
{

namespace ie
{

GANSSPositioningData::GANSSPositioningData(const ITS_OCTET* buf, int len)
: InfoElement(InfoElement::GANSS_POSITIONING_DATA,len)
{
    ITS_OCTET temp  = buf[0];

    if(len >= sizeof(ITS_OCTET)*1)
    {
        posMethod  = (Method)((temp & 0xC0)>> 6);
        posGanssId = (GanssID)((temp & 0x38)>> 3);
        posUsage   = (Usage)(temp & 0x07);
    }
    else
    {
        ITN_THROW(DecodeException,"Invalid IE length for GANSSPositioningData IE");
    }
}

int GANSSPositioningData::Encode (ITS_OCTET* buf, int& len) const
{
    len = length + sizeof(ITS_OCTET)*3;

    buf[0] = id;
    buf[1] = length + sizeof(ITS_OCTET);

    ITS_OCTET temp = (ITS_OCTET)(posMethod<<6);
    buf[2] = temp;
    temp = (ITS_OCTET)(posGanssId<<3);
    buf[2] = buf[2] | temp;
    temp = (ITS_OCTET)posUsage;
    buf[2] = buf[2] | temp;

    return CODEC_SUCCESS;
}

void GANSSPositioningData::PrintIE(std::ostream &out) const
{
    ITS_OCTET temp = (ITS_OCTET)(posMethod<<6);
    ITS_OCTET buf = temp;
    temp = (ITS_OCTET)(posGanssId<<3);
    buf = buf | temp;
    temp = (ITS_OCTET)posUsage;
    buf = buf | temp;

    out<<"      IE GANSSPositioningData "<<std::endl;  
    out<<"      ["<<std::endl;
    out<<"      \t\tvalue = 0x" << std::hex << (int)buf << std::endl; 
    out<<"      ]"<<std::endl<<std::endl;
}

} // namespace ie
} // namespace bssaple


