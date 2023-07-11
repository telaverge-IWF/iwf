//////////////////////////////////-*-h-*-/////////////////////////////////////
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
//   ID: $Id: geographiclocation.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: geographiclocation.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSAPLE_IE_GEOGRAPHICLOCATION_H
#define BSSAPLE_IE_GEOGRAPHICLOCATION_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{

namespace ie
{

static void TEST_GEOGRAPHICLOCATION(void);

/**
 * GeographicLocation is a variable length information element providing an
 * estimate of a geographic location.  The content of this IE is:
 *   -- Type of Shape
 *   -- Shape description
 * Based on different shape type, the shape description is different; it has a
 * variable length from 7 to 13.
 */
class GeographicLocation : public InfoElement 
{
public:
    enum ShapeType
    {
        ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE                    =   0x01,
        ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE                   =   0x03,
        ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID    =   0x09,
        ELLIPSOID_ARC                                              =   0x0A
    };

    enum LatitudeSign
    {
        NORTH   =   0x00,
        SOUTH   =   0x01
    };

    enum AltitudeSign
    {
        HIGHT = 0x00,
        DEPTH = 0x01
    };

    /**
     *  Purpose:
     *      This is default contructor initailizes the type and
     *      default length.
     *
     *  Input Parameters:
     *
     *  Output parameters:
     *
     */
    GeographicLocation()
    : InfoElement(InfoElement::GEOGRAPHIC_LOCATION, sizeof(ITS_OCTET)*7),
      type(ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE),
      latSign(0),
      degreeLatitude(0),
      degreeLongitude(0),
      uncertaintyCode(0),
      altSign(0),
      altitude(0),
      semiMajor(0),
      semiMinor(0),
      angleOfMajoraxis(0),
      uncertaintyAltitude(0),
      innerRadius(0),
      uncertaintyRadius(0),
      offsetAngle(0),
      includedAngle(0),
      confidence(0)
    {}


    /**
    * Constructors
    */
    GeographicLocation(ShapeType type);

    /**
    * Destructor 
    */
    ~GeographicLocation()
    {}

    /**
    * Equality Operations 
    */
    int operator==(const GeographicLocation &right) const;

    /**
     *  Purpose: Set ShapeType
     *
     *  Input Parameters:
     *      val - is a type of ShapeType
     *
     *  OutPut Parameters:
     *
     *  Returns:
     *
     */
    void SetShapeType(ShapeType val)
    {
       type = val;
    }
    
    /**
     *  Purpose: Get ShapeType
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *
     *  Returns:
     *      ShapeType 
     *  
     */
    ShapeType GetShapeType() const
    {
        return type;
    }


    /**
     *  Purpose: Set Logitude and Latitude.
     *
     *  Input Parameters:
     *      sign - is Latitude sign(NORTH or SOUTH).
     *      longitude -  logitude value.
     *      latitude - latitude value.
     *
     *  OutPut Parameters:
     *
     *  Returns:
     *
     */
    void SetLogitudeAndLatitude(LatitudeSign sign,ITS_UINT longitude,
                                                            ITS_UINT latitude);

    /**
     *  Purpose: Get Logitude and Latitude
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *      sign - is Latitude sign(NORTH or SOUTH).
     *      longitude -  logitude value.
     *      latitude - latitude value.
     *
     *  Returns:
     *
     */
    void GetLogitudeAndLatitude(LatitudeSign &sign,ITS_UINT &Longitude,
                                                      ITS_UINT &lat) const;


    /**
     *  Purpose: Set GeographicalCircleCode
     *
     *  Input Parameters:
     *      uncertaintyCode - is the value of uncertainty code 
     *                        for a GeographicalCircle.
     *  OutPut Parameters:
     *
     *  Returns:
     *
     */
    void SetGeographicalCircleCode(ITS_OCTET uncertaintyCode);

    /**
    *   Operation:GetGeographicalCircle
    */
    /**
     *  Purpose: Get GeographicalCircleCode
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *
     *  Returns:
     *      value of uncertainty code.
     *
     */
    ITS_OCTET GetGeographicalCircleCode() const;

    /**
     *  Purpose: Set Geographical Ellipse.
     *
     *  Input Parameters:
     *      semimajor - semimajor axis of Ellipse.
     *      semiminor - semiminor axis of Ellipse.
     *      angleMajoraxis - angle of major axis of Ellipse.
     *      conf -  is confidence.
     *
     *  OutPut Parameters:
     *
     *  Returns:
     *
     */
    void SetGeographicalEllipse(ITS_OCTET semimajor,
                                                ITS_OCTET semiminor,
                                                ITS_OCTET angleMajoraxis,
                                                ITS_OCTET conf);

    /**
     *  Purpose: Get Geographical Ellipse.
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *      semimajor - semimajor axis of Ellipse.
     *      semiminor - semiminor axis of Ellipse.
     *      angleMajoraxis - angle of major axis of Ellipse.
     *      conf -  is confidence.
     *
     *  Returns:
     *
     */
    void GetGeographicalEllipse(ITS_OCTET &semimajor,
                                            ITS_OCTET &semiminor,
                                            ITS_OCTET &angleOfmajoraxis,
                                            ITS_OCTET &conf) const;

    /**
     *  Purpose:  Set Geographical Ellipsoid.
     *
     *  Input Parameters:
     *      sign - altitude sign(HIGTH or DEPTH).
     *      altitude - altitude of Geographical Ellipsoid.
     *      semimajor - semimajor axis of Ellipsoid.
     *      semiminor - semiminor axis of Ellipsoid.
     *      angleMajoraxis - angle of major axis of Ellipsoid.
     *      uncertaintyaltitude - uncertain altitude of Ellipsoid.
     *      conf -  is confidence. 
     *
     *  OutPut Parameters:
     *
     *  Returns:
     *
     */
    void SetGeographicalEllipsoid(AltitudeSign sign,ITS_USHORT altitude,
                                            ITS_OCTET semimajor,
                                            ITS_OCTET semiminor,
                                            ITS_OCTET angleOfmajoraxis,
                                            ITS_OCTET uncertaintyaltitude,
                                            ITS_OCTET conf);

    /**
     *  Purpose:Get Geographical Ellipsoid.
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *      sign - altitude sign(HIGTH or DEPTH).
     *      alt - altitude of Geographical Ellipsoid.
     *      major - semimajor axis of Ellipsoid.
     *      minor - semiminor axis of Ellipsoid.
     *      angle - angle of major axis of Ellipsoid.
     *      unceralt - uncertain altitude of Ellipsoid
     *      conf -  is confidence.
     *
     *  Returns:
     *
     */
    void GeographicLocation::GetGeographicalEllipsoid(
                                      GeographicLocation::AltitudeSign &sign,
                                                      ITS_USHORT &alt,
                                                      ITS_OCTET &major,
                                                      ITS_OCTET &minor,
                                                      ITS_OCTET &angle,
                                                      ITS_OCTET &unceralt,
                                                      ITS_OCTET &conf) const;
    /**
     *  Purpose: Set Geographical Arc.
     *
     *  Input Parameters:
     *      innerRadius - inner radius of Geographical Arc.
     *      uncertaintyradius - uncertainty radius of Geographical Arc.
     *      offsetangle - off set angle of Geographical Arc.
     *      includedangle - include angle of Geographical Arc.
     *      conf - confidence.
     *
     *  OutPut Parameters:
     *
     *  Returns:
     *
     */
    void SetGeographicalArc(ITS_USHORT innerRadius,
                                        ITS_OCTET uncertaintyradius,
                                        ITS_OCTET offsetangle,
                                        ITS_OCTET includedangle,
                                        ITS_OCTET conf);

    /**
     *  Purpose:Get Geographical Arc.
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *      innerRadius - inner radius of Geographical Arc.
     *      uncertaintyradius - uncertainty radius of Geographical Arc.
     *      offsetangle - off set angle of Geographical Arc.
     *      includedangle - include angle of Geographical Arc.
     *      conf - confidence.
     *
     *  Returns:
     *
     */
    void GetGeographicalArc(ITS_USHORT &inneradius,
                                            ITS_OCTET &uncertaintyadius,
                                            ITS_OCTET &offsetngle,
                                            ITS_OCTET &includedngle,
                                            ITS_OCTET &conf) const;

protected:

    virtual void PrintIE(std::ostream &) const;

    /**
     *  Purpose:
     *      This method Enocde the IEs in to the buf argument.
     *
     *  Input Parameters:
     *      buf - a pointer to the buffer to encode into.
     *
     *  Output Parameters:
     *      len - returns the length of encoded buffer.
     *
     *  Throws Exception:
     *      Throws EncodingException in case unsuccessful.
     */
     virtual int Encode (ITS_OCTET* buf, int& len) const;

    /**
     *  Purpose:
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     */
    virtual InfoElement *Clone() const
    {
        return new GeographicLocation(*this);
    }

    /**
     *  Purpose:
     *      This constructor can only be invoked by members and friends.
     *
     *  Input Parameters:
     *      buf - is encoded bufer.
     *      len - is lenght of encoded bufer.
     *
     *  Output Parameters:
     *
     */
    GeographicLocation(const ITS_OCTET *buf,int len);

private:

    /**
    * Attribute: type
    *   This field occupies bits 6-8 of octet 1. Only the
    *   following types are allowed:
    *   0001: Ellipsoid point with uncertainty Circle
    *   0011: Ellipsoid point with uncertainty Ellipse.
    *   1001: Ellipsoid point with altitude and uncertainty
    *   Ellipsoid.
    *   1010: Ellipsoid Arc.
    *   This field exists for all types.
    */
    ShapeType type;
    ITS_OCTET latSign;
    ITS_UINT degreeLatitude;
    ITS_UINT degreeLongitude;
    ITS_OCTET uncertaintyCode;
    ITS_OCTET altSign;
    ITS_USHORT altitude;
    ITS_OCTET semiMajor;
    ITS_OCTET semiMinor;
    ITS_OCTET angleOfMajoraxis;
    ITS_OCTET uncertaintyAltitude;
    ITS_USHORT innerRadius;
    ITS_OCTET uncertaintyRadius;
    ITS_OCTET offsetAngle;
    ITS_OCTET includedAngle;
    ITS_OCTET confidence;

    GeographicLocation & operator=(const GeographicLocation &right);
    friend void TEST_GEOGRAPHICLOCATION(void);
    friend class InfoElement;
};

}

}

#endif


