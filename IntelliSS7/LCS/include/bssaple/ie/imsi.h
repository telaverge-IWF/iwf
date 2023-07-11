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
//   ID: $Id: imsi.h,v 1.1.2.3 2010/03/26 11:48:05 rajeshak Exp $
//
//   LOG: $Log: imsi.h,v $
//   LOG: Revision 1.1.2.3  2010/03/26 11:48:05  rajeshak
//   LOG: GetHexBuff function signature changes
//   LOG:
//   LOG: Revision 1.1.2.2  2010/03/25 06:32:32  rajeshak
//   LOG: API to get the Hex dump after encode/decode (for TDR).
//   LOG:
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_IMSI_H
#define BSSAPLE_IE_IMSI_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{

namespace ie
{

static void TEST_IMSI(void);

/**
 * The IMSI is of variable length and is coded as a sequence of BCD digits,
 * compressed two into each octet.  This is a variable length element, and
 * includes a length indicator. The IMSI is defined in GSM 03.03. It shall
 * not exceed 15 digits (see GSM 03.03).
 */
class IMSI : public InfoElement
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
    IMSI():InfoElement(InfoElement::IMSI,sizeof(ITS_OCTET))
    {}

    /**
    *    Destructor 
    */
    virtual ~IMSI()
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
     *  Purpose: Set the IMSI digits.
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
     *  Purpose: Get the IMSI digits.
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
        return new IMSI(*this);
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
    IMSI(const ITS_OCTET *buf,int len);

private:
    ITS_OCTET hexBuff[25];
    /*
     *    Attribute: digit1_oddEven
     *    octet 3
     *    Ref: GSM 09.31 Fig. 10.11
     */
    ITS_OCTET digit1_oddEven;

    /*
     *    Attribute: digits
     *    IMSI digits excluding digit1.
     */
    ITS_OCTET digits[7];

    friend class InfoElement;
    friend void  TEST_IMSI(void);
};

} // namespace ie
} // namespace bssaple


#endif

