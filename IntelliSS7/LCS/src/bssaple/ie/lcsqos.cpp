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
//   ID: $Id: lcsqos.cpp,v 1.1.2.6 2010/05/10 13:05:03 rajeshak Exp $
//
//  LOG: $Log: lcsqos.cpp,v $
//  LOG: Revision 1.1.2.6  2010/05/10 13:05:03  rajeshak
//  LOG: Fix for Issue-ID: 2803, 2802, 2800, 2791
//  LOG:
//  LOG: Revision 1.1.2.5  2010/05/03 04:23:42  rajeshak
//  LOG: Fix for Issue-2710
//  LOG:
//  LOG: Revision 1.1.2.4  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.3  2010/03/25 06:31:29  rajeshak
//  LOG: API to get the Hex dump after encode/decode (for TDR).
//  LOG:
//  LOG: Revision 1.1.2.2  2010/02/22 12:24:02  rajeshak
//  LOG: Fix for Whizible Issue 2518 (HA missing in QOS)
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bssaple/ie/lcsqos.h>


namespace bssaple
{

namespace ie
{

LCSQoS::LCSQoS(const ITS_OCTET* buf, int len)
: InfoElement(InfoElement::LCS_QOS, len)
{
    if (len == sizeof(ITS_OCTET)*4)
    {
        verticalIndicator     = buf[0];
        ha_horizontalAccuracy = buf[1];
        va_verticalAccuracy   = buf[2];
        responseTime          = buf[3];
    }
    else
    {
        ITN_THROW(DecodeException,"Invalid Length for LCSQoS");
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

int LCSQoS::Encode (ITS_OCTET* buf, int& len) const
{
    buf[0] = id;
    buf[1] = sizeof(ITS_OCTET)*4;
    buf[2] = verticalIndicator;
    buf[3] = ha_horizontalAccuracy;
    buf[4] = va_verticalAccuracy;
    buf[5] = responseTime;
    len = sizeof(ITS_OCTET)*6;
    return CODEC_SUCCESS;
}

void LCSQoS::PrintIE(std::ostream &out) const
{
    out<<"     IE LCSQoS "<<std::endl;
    out<<"     ["<<std::endl;   
    out<<"\t\tverticalIndicator  0x"<<std::hex<<(int)(verticalIndicator)<<std::endl;
    out<<"\t\thorizontalIndicator  0x"<<std::hex
       <<(int)((ha_horizontalAccuracy & 0x80) >> 7) << std::endl;
    out<<"\t\thorizontalAccuracy  0x"<<std::hex<<
                          (int)(ha_horizontalAccuracy & 0x7FU)<<std::endl;
    out<<"\t\tVerticalAccuracy  0x"<<std::hex<<
                            (int)(va_verticalAccuracy & 0x7FU)<<std::endl;
    out<<"\t\tresponseTime  0x"<<std::hex
                                    <<(int)(responseTime >> 6)<<std::endl;
    out<<"     ]"<<std::endl<<std::endl;
}

} // namespace ie    
} // namespace bssaple    


