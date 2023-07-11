/////////////////////////////////-/-C++-/-////////////////////////////////////
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
//  ID: $Id: locationareacode.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//  LOG:$Log: locationareacode.h,v $
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSLAP_IE_LAC_H 
#define BSSLAP_IE_LAC_H

#include <bsslap/ie/infoelement.h>

namespace bsslap
{
namespace ie
{


/*
 * LAC information element defines the cell identity of the MS serving cell.
 */

class LocationAreaCode: public InfoElement
{
    friend class InfoElement;
public:

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
    LocationAreaCode()
    : InfoElement(LOCATION_AREA_CODE)
    {
    }


    /**
     * Destructor
     */
    ~LocationAreaCode(){ }

    /**
     *  Purpose: Set LAC value
     *
     *  Input Parameters:
     *      val - LAC value.
     *
     *  OutPut Parameters:
     *
     *
     *
     */
    void SetLAC(ITS_USHORT val)
    {
        lac[0] = (val >> 8 ) & 0xFFU;
        lac[1] = val & 0xFFU;
    }

    /**
     *  Purpose: Get LAC value
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *  Returns:
     *      LAC value.
     *
     */
    ITS_USHORT GetLAC() const
    {
        return ((lac[0] << 8) | lac[1] );
    }

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
    LocationAreaCode(const ITS_OCTET *buf, int& len);

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
    virtual void Encode (ITS_OCTET* buf, int& len) const;

    InfoElement *Clone() const
    {
        return new LocationAreaCode(*this);
    }

    virtual void Print(std::ostream &) const;

private:
    ITS_OCTET     lac[2];
};


} // namespace ie
} // namespace bsslap


#endif //BSSLAP_IE_LAC_H

