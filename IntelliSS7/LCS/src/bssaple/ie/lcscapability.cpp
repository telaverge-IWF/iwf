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
//   ID: $Id: lcscapability.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG: $Log: lcscapability.cpp,v $
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2010/03/23 05:43:46  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: lcscapability.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $"

#include <bssaple/ie/lcscapability.h>


namespace bssaple
{

namespace ie
{

LcsCapability::LcsCapability(const ITS_OCTET* buf, int len)
: InfoElement(InfoElement::LCS_CAPABILITY, len)
,gps_c(false)
, gps_b(false)
, gps_a(false)
, otd_b(false)
, otd_a(false)
{
    if((len < sizeof(ITS_OCTET)*1) || (len >= sizeof(ITS_OCTET)*2))
    {
        ITN_THROW(DecodeException,"Invalid IE length for LCS Capability IE");
    }
    else if (len == sizeof(ITS_OCTET)*1)
    {
        if ((buf[0] && CONVENTIONAL_GPS_BIT) == CONVENTIONAL_GPS_BIT)
        {
            gps_c = true;
        }
        if ((buf[0] && MS_BASED_GPS_BIT) == MS_BASED_GPS_BIT)
        {
            gps_b = true;
        }
        if ((buf[0] && MS_ASSISTED_GPS_BIT) == MS_ASSISTED_GPS_BIT)
        {
            gps_a = true;
        }
        if ((buf[0] && MS_BASED_E_OTD_BIT) == MS_BASED_E_OTD_BIT)
        {
            otd_b = true;
        }
        if ((buf[0] && MS_ASSISTED_E_OTD_BIT) == MS_ASSISTED_E_OTD_BIT)
        {
            otd_a = true;
        }
    }
}

int LcsCapability::Encode (ITS_OCTET* buf, int& len) const
{
    ITS_OCTET value = 0;
    len = length + sizeof(ITS_OCTET)*2;

    buf[0] = id;
    buf[1] = length;

    if (gps_c)
    {
        value |= CONVENTIONAL_GPS_BIT;
    }

    if (gps_b)
    {
        value |= MS_BASED_GPS_BIT;
    }
    if (gps_a)
    {
        value |= MS_ASSISTED_GPS_BIT;
    }
    if (otd_b)
    {
        value |= MS_BASED_E_OTD_BIT;
    }
    if (otd_a)
    {
        value |= MS_ASSISTED_E_OTD_BIT;
    }

    buf[2] = (ITS_OCTET)value;

    return CODEC_SUCCESS;
}

void LcsCapability::PrintIE(std::ostream &out) const
{
    int value = 0;

    if (gps_c)
    {
        value |= CONVENTIONAL_GPS_BIT;
    }
    if (gps_b)
    {
        value |= MS_BASED_GPS_BIT;
    }
    if (gps_a)
    {
        value |= MS_ASSISTED_GPS_BIT;
    }
    if (otd_b)
    {
        value |= MS_BASED_E_OTD_BIT;
    }
    if (otd_a)
    {
        value |= MS_ASSISTED_E_OTD_BIT;
    }

    out<<"      IE LCS Capability "<<std::endl;
    out<<"      ["<<std::endl;;
    out<<"\t\tValue  0x"<<std::hex<<(int)value<<std::endl;
    out<<"      ]"<<std::endl<<std::endl;

}


} // namespace ie   
} // namespace bssaple   


