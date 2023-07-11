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
//   ID: $Id: locationtype.cpp,v 1.1.2.5 2010/05/10 13:05:03 rajeshak Exp $
//
//  LOG: $Log: locationtype.cpp,v $
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


#include <bssaple/ie/locationtype.h>


namespace bssaple
{

namespace ie
{

LocationType::LocationType(const ITS_OCTET *buf,int len)
: InfoElement(InfoElement::LOCATION_TYPE,len)
{
    if(len > sizeof(ITS_OCTET)*2)
    {
        ITN_THROW(DecodeException,"Length Exeeded for LocationType");
    }
    locationInfo = (LocationInformation)buf[0];
    if(length >sizeof(ITS_OCTET))
    {
        if(locationInfo == LocationType::CURRENT_GEOGRAPHIC_LOCATION)
        {
             ITN_THROW(DecodeException,"Invalid data for LocationType");
        }
        else
        {
            positionMethod = (PositioningMethod)buf[1];
        }
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

int LocationType::Encode (ITS_OCTET* buf, int& len) const
{
    buf[0] = id;

    if(locationInfo == LocationType::CURRENT_GEOGRAPHIC_LOCATION )
    {
        len = sizeof(ITS_OCTET)*3;
        buf[1] = sizeof(ITS_OCTET);
        buf[2] = (ITS_OCTET)locationInfo;
    }
    else
    {
        len =  sizeof(ITS_OCTET)*4;
        buf[1] = sizeof(ITS_OCTET)*2;
        buf[2] = (ITS_OCTET)locationInfo;
        buf[3] = (ITS_OCTET)positionMethod;
    }
    return CODEC_SUCCESS;
}

void LocationType::SetPositionMethod(LocationType::PositioningMethod val)
{
    switch (locationInfo)
    {
    case LOCATION_ASSISTANCE_INFORMATION:
    case DECIPHERING_KEYS_FOR_BROADCAST:
        positionMethod = val;
        break;
    default:
        ITN_THROW(IllegalArgumentException, "LocationType not applicable");
    }
}

LocationType::PositioningMethod LocationType::GetPositionMethod() const
{
    switch (locationInfo)
    {
    case LOCATION_ASSISTANCE_INFORMATION:
    case DECIPHERING_KEYS_FOR_BROADCAST:
        return positionMethod;
    default:
        ITN_THROW(IllegalArgumentException, "LocationType not applicable");
    }            
}

void LocationType::PrintIE(std::ostream &out) const
{
    out<<"     IE LocationType"<<std::endl;
    out<<"     ["<<std::endl;
    if(locationInfo == LocationType::CURRENT_GEOGRAPHIC_LOCATION )
    {
        out<<"\t\tLocationInformatoin   0x"<<std::hex
                                    <<(int)(locationInfo)
									<<" - " <<LOCATION_INFO_STRING((int)(locationInfo))
									<<std::endl;
    }
    else
    {
        out<<"\t\tLocationInformatoin   0x"<<std::hex
                                    <<(int)(locationInfo)
									<<" - " <<LOCATION_INFO_STRING((int)(locationInfo))
									<<std::endl;
        out<<"\t\tPositionMethod   0x"<<std::hex
			                        <<(int)(positionMethod)
									<<" - " <<POSITIONING_METHOD_STRING((int)(positionMethod))
									<<std::endl;
    }
    out<<"     ]"<<std::endl<<std::endl;
}

} // namespace ie
} // namespace bssaple


