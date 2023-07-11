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
//   ID: $Id: geographiclocation.cpp,v 1.1.2.3 2010/06/29 12:49:17 chandrashekharbs Exp $
//
//  LOG: $Log: geographiclocation.cpp,v $
//  LOG: Revision 1.1.2.3  2010/06/29 12:49:17  chandrashekharbs
//  LOG: Fix for Issue ID-3163
//  LOG:
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bssaple/ie/geographiclocation.h>


namespace bssaple
{

namespace ie
{

GeographicLocation::GeographicLocation(const ITS_OCTET *buf,int len)
: InfoElement(InfoElement::GEOGRAPHIC_LOCATION,len)
{
    type = (ShapeType)(buf[0] >> 4 & 0x0FU);
    latSign |= buf[1] & 0x80U;

    degreeLatitude = ((buf[1]  << 16) & 0x007F0000U) |
                     ((buf[2]  << 8) & 0x0000FF00U) |
                     ((buf[3] ) & 0x000000FFU);

    degreeLongitude = ((buf[4]  << 16) & 0x00FF0000U) |
                      ((buf[5]  << 8) & 0x0000FF00U) |
                      ((buf[6] ) & 0x000000FFU);

    if(type == 
            GeographicLocation::ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE)
    {
        uncertaintyCode = buf[7];
    }

    else if(type ==
            GeographicLocation::ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE)
    {
        semiMajor = buf[7];
        semiMinor = buf[8];
        angleOfMajoraxis = buf[9];
        confidence = buf[10];
    }

    else if(type ==
    GeographicLocation::ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID)    {
        altSign = buf[7] & 0x80U;

        altitude = ((buf[7] << 8) & 0x7F00U) | buf[8] ;

        semiMajor = buf[9];
        semiMinor = buf[10];
        angleOfMajoraxis = buf[11];
        uncertaintyAltitude =  buf[12];
        confidence = buf[13];
    }

    else if(type == GeographicLocation::ELLIPSOID_ARC)
    {   
        innerRadius = buf[7] << 8 | buf[8];
        uncertaintyRadius = buf[9]; 
        offsetAngle = buf[10];
        includedAngle = buf[11];
        confidence = buf[12];
    }
    else
    {
        ITN_THROW(DecodeException,
                    "Unsupported Positioning shape in GeographicLocation");
    }
}


void GeographicLocation::SetLogitudeAndLatitude(
        GeographicLocation::LatitudeSign sign,
        ITS_UINT lat,
        ITS_UINT longitude)
{
    latSign &= ~0x80U;
    latSign |= ((sign << 7) & 0x80U);

    degreeLatitude = lat;
    degreeLongitude = longitude;
}


void GeographicLocation::GetLogitudeAndLatitude(
                                     GeographicLocation::LatitudeSign &sign,
                                     ITS_UINT &lat,ITS_UINT &longitude) const
{
    sign = (GeographicLocation::LatitudeSign)(latSign >> 7) ;
    lat = degreeLatitude;
    longitude = degreeLongitude;
     
}


void GeographicLocation::SetGeographicalCircleCode(ITS_OCTET uncercode)
{
    type = GeographicLocation::ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE;
    length = sizeof(ITS_OCTET)*8;
    uncertaintyCode = uncercode;
}

ITS_OCTET GeographicLocation::GetGeographicalCircleCode() const
{
    return uncertaintyCode;
}


void GeographicLocation::SetGeographicalEllipse(ITS_OCTET major,
                                                ITS_OCTET minor,
                                                ITS_OCTET angle,
                                                ITS_OCTET conf)
{
    type = GeographicLocation::ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE;
    length = sizeof(ITS_OCTET)*11;

    semiMajor &= ~0xFFU; 
    semiMajor |= major & 0x7FU;

    semiMinor &= ~0xFFU;
    semiMinor |= minor & 0x7FU;

    angleOfMajoraxis = angle;

    confidence &= ~0xFFU;
    confidence |= conf & 0x7FU;
}

void GeographicLocation::GetGeographicalEllipse(ITS_OCTET &major,
                                                ITS_OCTET &minor,
                                                ITS_OCTET &angle,
                                                ITS_OCTET &conf) const 
{
    major = semiMajor;
    minor = semiMinor;
    angle = angleOfMajoraxis;
    conf = confidence;
}


void GeographicLocation::SetGeographicalEllipsoid(
        GeographicLocation::AltitudeSign sign,
        ITS_USHORT alt,
        ITS_OCTET major,
        ITS_OCTET minor,
        ITS_OCTET angle,
        ITS_OCTET unceralt,
        ITS_OCTET conf)
{
    type = GeographicLocation::ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID;
    length = sizeof(ITS_OCTET)*14;
    altSign &= ~0x80U;
    altSign |= ((alt << 7) & 0x80U);

    altitude = alt;
    
    semiMajor &= ~0xFFU;
    semiMajor |= major & 0x7FU;

    semiMinor &= ~0xFFU;
    semiMinor |= minor & 0x7FU;

    angleOfMajoraxis = angle;

    uncertaintyAltitude &= ~0xFFU;
    uncertaintyAltitude |= unceralt & 0x7FU;

    confidence &= ~0xFFU;
    confidence |= conf & 0x7FU;
}


void GeographicLocation::GetGeographicalEllipsoid(
        GeographicLocation::AltitudeSign &sign,
        ITS_USHORT &alt,
        ITS_OCTET &major,
        ITS_OCTET &minor,
        ITS_OCTET &angle,
        ITS_OCTET &unceralt,
        ITS_OCTET &conf) const
{
    sign  = (GeographicLocation::AltitudeSign)(altSign >> 7);
    alt = altitude;
    major = semiMajor;
    minor = semiMinor;
    angle = angleOfMajoraxis;
    unceralt = uncertaintyAltitude;
    conf = confidence;
}

void GeographicLocation::SetGeographicalArc(
        ITS_USHORT innerrad,
        ITS_OCTET uncertaintyrad,
        ITS_OCTET offangle,
        ITS_OCTET incangle,
        ITS_OCTET conf)
{
    type = GeographicLocation::ELLIPSOID_ARC;
    length = sizeof(ITS_OCTET)*13; 

    innerRadius = innerrad;

    uncertaintyRadius &= ~0xFF;
    uncertaintyRadius |= uncertaintyrad & 0x7FU;

    offsetAngle = offangle;
    
    includedAngle = incangle;

    confidence &= ~0xFF;
    confidence |= conf & 0x7FU;
}

void GeographicLocation::GetGeographicalArc(
        ITS_USHORT &innerrad,
        ITS_OCTET &uncertaintyrad,
        ITS_OCTET &offangle,
        ITS_OCTET &incangle,
        ITS_OCTET &conf) const
{
    innerrad = innerRadius;

    uncertaintyrad = uncertaintyRadius;

    offangle = offsetAngle;

    incangle = includedAngle;

    conf = confidence;
}


int GeographicLocation::Encode (ITS_OCTET *buf, int &len) const
{
    len = length + sizeof(ITS_OCTET)*2;

    buf[0] = id;
    buf[1] = length;
    buf[2] = (ITS_OCTET)(type << 4 & 0xF0U);

    buf[3] = latSign;

    buf[3] &= ~0x7FU;
    buf[3] |= (degreeLatitude >> 16) & 0x7FU;
    buf[4] = (degreeLatitude >> 8) & 0xFFU;
    buf[5] = degreeLatitude & 0xFFU;

    buf[6] = (degreeLongitude >> 16) & 0xFFU;
    buf[7] = (degreeLongitude >> 8) & 0xFFU;
    buf[8] = degreeLongitude & 0xFFU;

    if(type == GeographicLocation::ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE)
    {
        buf[9] = uncertaintyCode;
    }

    if(type == GeographicLocation::ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE)
    {
        buf[9] = semiMajor;
        buf[10] = semiMinor;
        buf[11] = angleOfMajoraxis;
        buf[12] = confidence;
    }

    if(type == 
    GeographicLocation::ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID)
    {
        buf[9] = altSign & 0x80U;
        buf[9] |= (altitude >> 8) & ~0x80;
        buf[10] = altitude & 0xFFU;;
        buf[11] = semiMajor;
        buf[12] = semiMinor;
        buf[13] = angleOfMajoraxis;
        buf[14] = uncertaintyAltitude;
        buf[15] = confidence;
    }

    if(type == GeographicLocation::ELLIPSOID_ARC)
    {
        buf[9] = ((innerRadius >> 8) & 0xFFU);
        buf[10] = (innerRadius & 0xFFU);
        buf[11] = uncertaintyRadius;
        buf[12] = offsetAngle;
        buf[13] = includedAngle;
        buf[14] = confidence;
    }
    return CODEC_SUCCESS;   

}

void GeographicLocation::PrintIE(std::ostream &out) const
{
    out<<"     IE GeographicLocation "<<std::endl;
    out<<"     [ "<<std::endl;
    out<<"\t\tTypeOfShape  0x"<<std::hex<<(int)(GetShapeType())<<std::endl;
    
    GeographicLocation::LatitudeSign sign;
    ITS_UINT log,lat;
    GetLogitudeAndLatitude(sign,log,lat);
    out<<"\t\tLatitudeSign  0x"<<std::hex<<(int)(sign)<<std::endl;
    out<<"\t\tDegreeLatitude  0x"<<std::hex<<(int)(log)<<std::endl;
    out<<"\t\tDegreeLongitude  0x"<<std::hex<<(int)(lat)<<std::endl;

    if(GetShapeType() == 
            GeographicLocation::ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE)
    {
        out<<"\t\tCircleCode  0x"<<std::hex<<(int)(GetGeographicalCircleCode())<<std::endl;
    }
    else if(GetShapeType() == 
            GeographicLocation::ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE)
    {
        ITS_OCTET maj,min,axis,conf;
        GetGeographicalEllipse(maj,min,axis,conf);
        out<<"\t\tSemiMajorAxis  0x"<<std::hex<<(int)(maj)<<std::endl;
        out<<"\t\tSemiMinorAxis  0x"<<std::hex<<(int)(min)<<std::endl;
        out<<"\t\tAngleOfMajoraxis  0x"<<std::hex<<(int)(axis)<<std::endl;
        out<<"\t\tConfidence   0x"<<std::hex<<(int)(conf)<<std::endl;
    }
    else if(GetShapeType() == 
  GeographicLocation::ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID)
    {
        GeographicLocation::AltitudeSign sign;
        ITS_OCTET maj,min,axis,unalt,conf;
        ITS_USHORT alt;
        GetGeographicalEllipsoid(sign,alt,maj,min,axis,unalt,conf);
        
        out<<"\t\tAltitudeSign  0x"<<std::hex<<(int)(sign)<<std::endl;
        out<<"\t\tAltitude  0x"<<std::hex<<(int)(alt)<<std::endl;
        out<<"\t\tSemimajorAxis  0x"<<std::hex<<(int)(maj)<<std::endl;
        out<<"\t\tSemiminorAxis  0x"<<std::hex<<(int)(min)<<std::endl;
        out<<"\t\tAngleOfmajoraxis  0x"<<std::hex<<(int)(axis)<<std::endl;
        out<<"\t\tUncertaintyAltitude  0x"<<std::hex<<(int)(unalt)<<std::endl;
        out<<"\t\tConfidence  0x"<<std::hex<<(int)(conf)<<std::endl;
    }
    else if(GetShapeType() == GeographicLocation::ELLIPSOID_ARC)
    {
        ITS_USHORT innrad;
        ITS_OCTET unrad,offang,incang,conf;
        GetGeographicalArc(innrad,unrad,offang,incang,conf);

        out<<"\t\tInnerRadius  0x"<<std::hex<<(int)(innrad)<<std::endl;
        out<<"\t\tUncertaintyRadius  0x"<<std::hex<<(int)(unrad)<<std::endl;
        out<<"\t\tOffsetAngle  0x"<<std::hex<<(int)(offang)<<std::endl;
        out<<"\t\tIncludedAngle  0x"<<std::hex<<(int)(incang)<<std::endl;
        out<<"\t\tConfidence  0x"<<std::hex<<(int)(conf)<<std::endl;
    }
    out<<"     ]"<<std::endl<<std::endl;
}

} // namespace ie
} // namespace bssaple


