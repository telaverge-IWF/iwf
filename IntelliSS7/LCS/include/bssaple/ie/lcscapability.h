//////////////////////////////////-*-h-*-/////////////////////////////////////
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
//   ID: $Id: lcscapability.h,v 1.1.2.1 2010/03/23 05:38:30 rajeshak Exp $
//
//  LOG: $Log: lcscapability.h,v $
//  LOG: Revision 1.1.2.1  2010/03/23 05:38:30  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: lcscapability.h,v 1.1.2.1 2010/03/23 05:38:30 rajeshak Exp $"

#ifndef BSSAPLE_IE_LCS_CAPABILITY_H
#define BSSAPLE_IE_LCS_CAPABILITY_H_

#include <bssaple/ie/infoelement.h>


namespace bssaple
{

namespace ie
{

#define CONVENTIONAL_GPS_BIT        0x01
#define MS_BASED_GPS_BIT            0x02
#define MS_ASSISTED_GPS_BIT         0x04
#define MS_BASED_E_OTD_BIT          0x08
#define MS_ASSISTED_E_OTD_BIT       0x10

#define LCS_CAPABILITY_BITMASK      0x1F


/**
 */
class LcsCapability : public InfoElement
{
public:
    /**
    *    Constructors 
    */

    LcsCapability()
    : InfoElement(InfoElement::LCS_CAPABILITY, sizeof(ITS_OCTET))
    {
        gps_c = false;
        gps_b = false;
        gps_a = false;
        otd_b = false;
        otd_a = false;
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
    LcsCapability(const ITS_OCTET *buf,int len);    

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
        return new LcsCapability(*this);
    }

    virtual void PrintIE(std::ostream &) const;

private: 

    friend class InfoElement;
    bool gps_c;
    bool gps_b;
    bool gps_a;
    bool otd_b;
    bool otd_a;
};

} // namespace ie
} // namespace bssaple



#endif

