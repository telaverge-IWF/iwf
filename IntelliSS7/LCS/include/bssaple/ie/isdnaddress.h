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
//   ID: $Id: isdnaddress.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: isdnaddress.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_ISDNADDRESS_H
#define BSSAPLE_IE_ISDNADDRESS_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{

namespace ie
{

static void TEST_ISDN_ADDRESS(void);

/**
 * ISDNAddress contains an ISDN address.
 */
class ISDNAddress: public InfoElement 
{
public:
    enum ExtensionIndicator
    {
        EXTENSION       =   0x00,
        NO_EXTENSION    =   0x01
    };

    enum NatureAddressIndicator
    {
        NATURE_UNKNOWN                  = 0x00,
        INTERNATIONAL_NUMBER            = 0x01,
        NATIONAL_SIGNIFICANT_NUMBER     = 0x02,
        NETWORK_SPECIFIC_NUMBER         = 0x03,
        SUBSCRIBER_NUMBER               = 0x04,
        RESERVED                        = 0x05,
        ABBREVIATED_NUMBER              = 0x06,
        IESERVED_FOR_EXTENSION          = 0x07   
    };


    enum NumberPlan
    {
        NUMBER_UNKNOWN                      =   0x00,    
        ISDN_OR_TELEPHONY_NUMBERING_PLAN    =   0x01,      
        SPARE_1                             =   0x02,   
        DATA_NUMBERING_PLAN                 =   0x03,
        TELEX_NUMBERING_PLAN                =   0x04,
        SPARE_2                             =   0x05,
        LAND_MOBILE_NUMBERING_PLAN          =   0x06,
        SPARE_3                             =   0x07,
        NATIONAL_NUMBERING_PLAN             =   0x08,
        PRIVATE_NUMBERING_PLAN              =   0x09,
        RESERVED_FOR_EXTENSION              =   0x15
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
    ISDNAddress():InfoElement(InfoElement::ISDN_ADDRESS,sizeof(ITS_OCTET))
    {}

    /**
    * Destructor 
    */
    ~ISDNAddress()
    {}

    /**
    * Equality Operations 
    */
    int operator==(const ISDNAddress &right) const;

    /**
     *  Purpose: Set the isdnaddress digits
     *
     *  Input Parameters:
     *      digits - octet string of isdnaddress digits.
     *      len - lenght of octet string.
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetDigits (ITS_OCTET* digits,int len);

    /**
     *  Purpose: Get the isdnaddress digits
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *      digits - returns octet string of isdnaddress digits.
     *      len - lenght of octet string.
     *
     *  Returns:
     *
     *
     */
    void GetDigits (ITS_OCTET* digits, int& len) const;

    /**
     *  Purpose: Set the Extension Indicator for isdnaddress
     *
     *  Input Parameters:
     *      val - is a ExtensionIndicator (NO_EXTENSION or EXTENSION).
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetExt (ExtensionIndicator val)
    {
        ext = val << 7;
    }

    /**
     *  Purpose: Get the Extension Indicator for isdnaddress.
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      the Extension Indicator(NO_EXTENSION or EXTENSION).
     *
     */
    ExtensionIndicator GetExt () const
    {
        return (ExtensionIndicator)(ext >> 7 & 0x01);
    }

    /**
     *  Purpose: Set NatureAddress for isdnaddress
     *
     *  Input Parameters:
     *      val - is NatureAddressIndicator.
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetNatureAddress (NatureAddressIndicator val)
    {
        natureAddress &= ~0x70U;
        natureAddress |= (val << 4) & 0x70U;
    }

    /**
     *  Purpose: Get NatureAddress for isdnaddress
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      NatureAddressIndicator.
     *
     */
    NatureAddressIndicator GetNatureAddress () const
    {
        return (NatureAddressIndicator)(natureAddress >> 4 & 0x07U);
    }

    /**
     *  Purpose:  Set NumberPlan for isdnaddress.
     *
     *  Input Parameters:
     *      val - is value for NumberPlan.
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetNumberPlan (NumberPlan val)
    {
        numberPlan = val & 0x0FU;
    }

    /**
     *  Purpose: Get NumberPlan
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      value of NumberPlan.
     *
     */
    NumberPlan GetNumberPlan () const
    {
        return (NumberPlan)numberPlan;
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
        return new ISDNAddress(*this);
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
    ISDNAddress(const ITS_OCTET* buf,int len);

private:

    ITS_OCTET ext;
    ITS_OCTET natureAddress;
    ITS_OCTET numberPlan;
    ITS_OCTET digits[8];

    friend class InfoElement;
    friend void TEST_ISDN_ADDRESS(void);
};


} // namespace ie
} // namespace bssaple


#endif

