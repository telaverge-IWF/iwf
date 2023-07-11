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
//   ID: $Id: gansspositioningdata.h,v 1.1.2.1 2010/03/23 05:38:30 rajeshak Exp $
//
//  LOG: $Log: gansspositioningdata.h,v $
//  LOG: Revision 1.1.2.1  2010/03/23 05:38:30  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: gansspositioningdata.h,v 1.1.2.1 2010/03/23 05:38:30 rajeshak Exp $"

#ifndef BSSAPLE_IE_GANSS_POSITIONING_DATA_H
#define BSSAPLE_IE_GANSS_POSITIONING_DATA_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{
namespace ie
{

static void TEST_GANSS_Positioning_Data();


class GANSSPositioningData: public InfoElement
{
public:
    enum Method
    {
        MS_BASED      = 0x00,
        MS_ASSISTED   = 0x01,
        CONVENTIONAL  = 0x02
    };

    enum GanssID
    {
        GALILEO         =  0x00,
        SBAS            =  0x01,
        MODERNIZED_GPS  =  0x02,
        QZSS            =  0x03,
        GLONASS         =  0x04
    };
 
    enum Usage
    {
        ATTEMPT_UNSUCCESS                       = 0x00,
        ATTEMPT_SUCCESS_RESULT_NOT_USED         = 0x01,
        ATTEMPT_SUCCESS_RESULT_USED_TO_VERIFY   = 0x02,
        ATTEMPT_SUCCESS_RESULT_USED             = 0x03,
        ATTEMPT_SUCCESS_MS_SUPP_MULT_POS_METHOD = 0x04
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
    GANSSPositioningData()
    : InfoElement(GANSS_POSITIONING_DATA, sizeof(ITS_OCTET))
    {
        length = sizeof(ITS_OCTET);
    }

    /**
     * Destructor
     */
    ~GANSSPositioningData(){ }

protected:

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
    GANSSPositioningData(const ITS_OCTET *buf, int len);

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

    virtual InfoElement *Clone() const
    {
        return new GANSSPositioningData(*this);
    }

    virtual void PrintIE(std::ostream &) const;

private:
    Method posMethod;
    GanssID posGanssId;
    Usage  posUsage;

    friend class InfoElement;
    friend void TEST_GANSS_Positioning_Data();
};


} // namespace ie
} // namespace bssaple


#endif

