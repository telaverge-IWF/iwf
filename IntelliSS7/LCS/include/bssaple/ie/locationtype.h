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
//   ID: $Id: locationtype.h,v 1.1.2.4 2010/03/26 11:48:05 rajeshak Exp $
//
//   LOG: $Log: locationtype.h,v $
//   LOG: Revision 1.1.2.4  2010/03/26 11:48:05  rajeshak
//   LOG: GetHexBuff function signature changes
//   LOG:
//   LOG: Revision 1.1.2.3  2010/03/25 06:32:32  rajeshak
//   LOG: API to get the Hex dump after encode/decode (for TDR).
//   LOG:
//   LOG: Revision 1.1.2.2  2010/02/22 12:28:24  rajeshak
//   LOG: Fix for Issue 2520, 2521, 2513 & 2514 (Reserved Printed as "NOT_APPLICABLE")
//   LOG:
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_LOCATIONTYPE_H
#define BSSAPLE_IE_LOCATIONTYPE_H 

#include <bssaple/ie/infoelement.h>


namespace bssaple
{

namespace ie
{

static void TEST_LOCATIONTYPE(void);

#define LOCATION_INFO_STRING(l) \
        (((l) == LocationType::CURRENT_GEOGRAPHIC_LOCATION) ?      "CURRENT_GEOGRAPHIC_LOCATION" : \
         ((l) == LocationType::LOCATION_ASSISTANCE_INFORMATION) ?  "LOCATION_ASSISTANCE_INFORMATION" : \
         ((l) == LocationType::DECIPHERING_KEYS_FOR_BROADCAST) ?   "DECIPHERING_KEYS_FOR_BROADCAST" : \
                                                     "UNKNOWN")  

#define POSITIONING_METHOD_STRING(p) \
        (((p) == LocationType::NOT_APPLICABLE) ?        "RESERVED" : \
         ((p) == LocationType::MOBILE_ASSISTED_EOTD) ?  "MOBILE_ASSISTED_EOTD" : \
         ((p) == LocationType::MOBILE_BASED_EOTD) ?     "MOBILE_BASED_EOTD" : \
         ((p) == LocationType::ASSISTED_GPS) ?          "ASSISTED_GPS" : \
                                          "UNKNOWN")  

struct LocationTypeStruct
{
    enum LocationInformation
    {
        CURRENT_GEOGRAPHIC_LOCATION     = 0x00,
        LOCATION_ASSISTANCE_INFORMATION = 0x01,
        DECIPHERING_KEYS_FOR_BROADCAST  = 0x02
    };

    enum PositioningMethod
    {
        NOT_APPLICABLE       = 0x00,
        MOBILE_ASSISTED_EOTD = 0x01,
        MOBILE_BASED_EOTD    = 0x02,
        ASSISTED_GPS         = 0x03
    };

    LocationTypeStruct()
    : locationInfo(CURRENT_GEOGRAPHIC_LOCATION),
      positionMethod(NOT_APPLICABLE)
    {}

    LocationInformation locationInfo;
    PositioningMethod positionMethod;
};

/**
 * LocationType is a variable length information element defining the type of
 * location information being requested.
 */
class LocationType : public InfoElement, public LocationTypeStruct
{
public:
    /**
    *    Constructors 
    */

    LocationType()
    : InfoElement(InfoElement::LOCATION_TYPE, sizeof(ITS_OCTET))
    {}

    const LocationTypeStruct &GetAsStruct() const
    {
        return *static_cast<const LocationTypeStruct *>(this);
    }

    /**
    *    Equality Operations 
    */
    int operator==(const LocationType &right) const;

    /**
     *  Purpose: Set LocationInfo
     *
     *  Input Parameters:
     *      info - is the value of LocationInformation
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetLocationInfo (LocationInformation info)
    {
       locationInfo = info;
    }

    /**
     *  Purpose: retruns LocationInfo 
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      LocationInfo value
     *
     */
    LocationInformation GetLocationInfo () const
    {
        return locationInfo;
    }

    /**
     *  Purpose:  Set PositionMethod
     *
     *  Input Parameters:
     *      method - value of PositioningMethod
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetPositionMethod(PositioningMethod method);

    /**
     *  Purpose: Get PositionMethod value
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      PositionMethod value
     *
     */
    PositioningMethod GetPositionMethod() const;

    /**
     *  Purpose: Get Hex Buff (This can be used after IE decode only)
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      Hex Buff
     *
     */
    const ITS_OCTET* GetHexBuff() const
    {
        return hexBuff;
    }

protected:

    /**
     *  Purpose:
     *      This constructor can only be invoked by members and friends.
     *      This contructor decodes the buffer and creates object of its type.
     *
     *  Input Parameters:
     *      buf - is encoded bufer.
     *      len - is lenght of encoded bufer.
     *
     *  Output Parameters:
     *
     */
    LocationType(const ITS_OCTET *buf,int len);    

    /**
     *  Purpose:
     *      This method Enocde the IEs in to the buf argument.
     *
     *  Input Parameters:
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - returns the length of encoded buffer.
     *
     *  Throws Exception:
     *      Throws EncodingException in case unsuccessful
     */
     virtual int Encode (ITS_OCTET* buf, int& len) const;

    virtual InfoElement *Clone() const
    {
        return new LocationType(*this);
    }

    virtual void PrintIE(std::ostream &) const;

private: 
    ITS_OCTET hexBuff[10];
    friend class InfoElement;
    friend void TEST_LOCATIONTYPE(void);
    LocationType & operator=(const LocationType &right);
};

} // namespace ie
} // namespace bssaple



#endif

