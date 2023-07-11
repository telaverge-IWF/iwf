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
//   ID: $Id: velocitydata.h,v 1.1.2.1 2010/03/23 05:38:30 rajeshak Exp $
//
//  LOG: $Log: velocitydata.h,v $
//  LOG: Revision 1.1.2.1  2010/03/23 05:38:30  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: velocitydata.h,v 1.1.2.1 2010/03/23 05:38:30 rajeshak Exp $"

#ifndef BSSAPLE_IE_VELOCITY_DATA
#define BSSAPLE_IE_VELOCITY_DATA
 
#include <bssaple/ie/infoelement.h>

namespace bssaple
{
namespace ie
{

static void TEST_Velocity_Data();


class VelocityData: public InfoElement
{
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
    VelocityData()
    : InfoElement(VELOCITY_DATA, 0)
    {
    }

    /**
     * Destructor
     */
    ~VelocityData(){ }

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
    VelocityData(const ITS_OCTET *buf, int len);

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
        return new VelocityData(*this);
    }

    virtual void PrintIE(std::ostream &) const;

private:

    friend class InfoElement;
    friend void TEST_Velocity_Data();
};


} // namespace ie
} // namespace bssaple


#endif

