//////////////////////////////////-*-h-*-/////////////////////////////////////
//                                                                          //
//     Copyright 2010 IntelliNet Technologies, Inc. All Rights Reserved.    //
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
//   ID: $Id: imei.h,v 1.1.2.3 2010/03/26 11:48:05 rajeshak Exp $
//
//  LOG: $Log: imei.h,v $
//  LOG: Revision 1.1.2.3  2010/03/26 11:48:05  rajeshak
//  LOG: GetHexBuff function signature changes
//  LOG:
//  LOG: Revision 1.1.2.2  2010/03/25 08:30:30  rajeshak
//  LOG: API to get the Hex dump after encode/decode (for TDR).
//  LOG:
//  LOG: Revision 1.1.2.1  2010/03/23 05:38:30  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: imei.h,v 1.1.2.3 2010/03/26 11:48:05 rajeshak Exp $"

#ifndef BSSAPLE_IE_IMEI_H
#define BSSAPLE_IE_IMEI_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{

namespace ie
{

static void TEST_IMEI(void);

/**
 */
class IMEI : public InfoElement
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
    IMEI():InfoElement(InfoElement::IMEI,sizeof(ITS_OCTET))
    {}

    /**
    *    Destructor 
    */
    virtual ~IMEI()
    {}

    /**
     *  Purpose: Get flag OddEven
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      flag the odd or Even
     *
     */
    ITS_OCTET GetOddEven () const
    {
        return  (digit1_oddEven >> 3) & 0x01;
    }

    /**
     *  Purpose: Set the IMEI digits.
     *
     *  Input Parameters:
     *      dig - octet string.
     *      len - length of octet string.
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetDigits (ITS_OCTET* dig,int len);

    /**
     *  Purpose: Get the IMEI digits.
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *      dig - octet string.
     *      len - length of octet string.
     *
     *  Returns:
     *
     *
     */
    void GetDigits(ITS_OCTET* dig, int& len) const;

    /**
     *  Purpose: Get Hex Buff (This can be used after IE decode only)
     *
     *  Input Parameters:
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
        return new IMEI(*this);
    }

    virtual void PrintIE(std::ostream &) const;

    /**
     *  Purpose:
     *      This constructor can only be invoked by members and friends.
     *      This contructor decodes the buffer and creates object of its type.
     *  Input Parameters:
     *      buf - is encoded bufer.
     *      len - is lenght of encoded bufer.
     *
     *  Output Parameters:
     *
     */
    IMEI(const ITS_OCTET *buf,int len);

private:
    ITS_OCTET hexBuff[25];

    /*
     */
    ITS_OCTET digit1_oddEven;

    /*
     *    Attribute: digits
     *    IMEI digits excluding digit1.
     */
    ITS_OCTET digits[7];

    friend class InfoElement;
    friend void  TEST_IMEI(void);
};

} // namespace ie
} // namespace bssaple


#endif

