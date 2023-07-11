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
//   ID: $Id: segmentation.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG: $Log: segmentation.cpp,v $
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bssaple/ie/segmentation.h>


namespace bssaple
{

namespace ie
{


Segmentation::Segmentation(const ITS_OCTET* buf, int len)
: InfoElement(InfoElement::SEGMENTATION,len)
{
    length = len;
    segInfo = buf[0];
    if(len > 1 )
    {
        if(len <= 3)
        {
            msgId = ((buf[1] << 8) | buf[2] );
        }
        else
        {
            ITN_THROW(DecodeException,"Length exeeded for Segmentation");
        }
    }
}

int Segmentation::Encode (ITS_OCTET* buf, int& len) const
{
    len = length+sizeof(ITS_OCTET)*2;

    buf[0] = id;
    buf[1] = length;
    buf[2] = segInfo;

    if(length > 3)
    {
        buf[3] = (msgId >> 8) & 0xFF;
        buf[4] = (msgId & 0xFF);
    }
    return CODEC_SUCCESS;
}

void Segmentation::PrintIE(std::ostream &out) const
{
    out<<"     IE Segmentation "<<std::endl;
    out<<"     ["<<std::endl;
    out<<"\t\tSegmentation Bit  0x"<<std::hex<<(int)(GetSegmentationBit())
                                                                <<std::endl;
    out<<"\t\tSetSegmentation Number  0x"<<std::hex
                        <<(int)(GetSegmentationNumber())<<std::endl;
    if(length > 1)
    {
        out<<"\t\tMessageID   0x"<<std::hex<<(int)(GetMessageID())<<std::endl;;
                                                                
    }

    out<<"     ]"<<std::endl<<std::endl;

}

} // namespace ie
} // namespace bssaple


