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
//   ID: $Id: lcsclienttype.cpp,v 1.1.2.5 2010/05/10 13:05:03 rajeshak Exp $
//
//  LOG: $Log: lcsclienttype.cpp,v $
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


#include <bssaple/ie/lcsclienttype.h>


namespace bssaple
{

namespace ie
{


LCSClientType::LCSClientType(const ITS_OCTET* buf, int len)
: InfoElement(InfoElement::LCS_CLIENT_TYPE,len)
{
    if(len != sizeof(ITS_OCTET))
    {
        ITN_THROW(DecodeException,"Invalid length for LCSClientType");
    }
    category = (Category)(buf[0] >> 4);
    subtype = (SubType)(buf[0] & 0x0F);

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

int  LCSClientType::Encode (ITS_OCTET* buf, int& len) const
{
    len = length + sizeof(ITS_OCTET)*2;

    buf[0] = id;
    buf[1] = length;
    buf[2] = (category << 4) | subtype;
    return CODEC_SUCCESS;
}

void LCSClientType::PrintIE(std::ostream &out) const
{
    out<<"      IE LCSClientType "<<std::endl;  
    out<<"      ["<<std::endl;
    out<<"\t\tClientCategory   0x"<<std::hex<<(int)(category) << std::endl;
    out<<"\t\tClientSubtype    0x"<<std::hex<<(int)(subtype) << std::endl;
    out<<"      ]"<<std::endl<<std::endl;
}

} // namespace ie
} // namespace bssaple


