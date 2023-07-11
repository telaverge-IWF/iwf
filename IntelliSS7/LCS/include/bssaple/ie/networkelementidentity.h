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
//   ID: $Id: networkelementidentity.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: networkelementidentity.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_NETWORKELEMENTIDENTITY_H
#define BSSAPLE_IE_NETWORKELEMENTIDENTITY_H 

#include <bssaple/ie/infoelement.h>


namespace bssaple
{

namespace ie
{

void static TEST_NetworkElementIdentity(void);

/**
*    Class: NetworkElementIdentity
*    This is a variable length information element
*    identifying a network element. by association with
*    either a designated cell
*    site or a designated location area.
*/
class NetworkElementIdentity : public InfoElement 
{

public:

    enum Discriminator
    {
        GLOBAL_IDENTIFICATION = 0x00,
        LAC_AND_CI            = 0x01,
        CI                    = 0x02,
        NO_CELL               = 0x03
    };

    /**
     *  Purpose:
     *      This is default contructor initailizes the type and
     *      default length.
     *
     *  Input Parameters:
     *      type - is type of identity(SRC_NETWORK_ID or DEST_NETWORK_ID).
     *
     *  Output parameters:
     *
     */
    NetworkElementIdentity(InfoElement::Type type)
    :InfoElement(type,0)
    {
        discriminator = NO_CELL;
    }


    /**
    *    Destructor 
    */
    ~NetworkElementIdentity()
    {}


    /**
     *  Purpose: Sets Discriminator
     *
     *  Input Parameters:
     *      disc - Discriminator value
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetDiscriminator (Discriminator disc)
    {
        discriminator = disc;
    }

    /**
     *  Purpose: Returns the Discriminator
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      Discriminator value
     *
     */
    Discriminator GetDiscriminator () const
    {
        return discriminator;
    }

    /**
     *  Purpose:Sets MCC digits
     *
     *  Input Parameters:
     *      dig1 - MCC digit1.
     *      dig2 - MCC digit2.
     *      dig3 - MCC digit3.
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetMCC (ITS_OCTET dit1,ITS_OCTET dig2,ITS_OCTET dig3)
    {
        if(discriminator != GLOBAL_IDENTIFICATION)
        {
            ITN_THROW(InvalidData,
                        "Invalid data for this Network discriminator");
        }

        mcc[0] &= ~0x0FU;
        mcc[0] |= dit1 & 0x0FU;
        mcc[0] &= ~0xF0U;
        mcc[0] |= (dig2 << 4) & 0xF0U;

        mcc[1] = 0xF0; //all 1 1 1 1
        mcc[1] &= ~0x0FU;
        mcc[1] |= dig3 & 0x0FU;
    }

    /**
     *  Purpose: Get MCC digits
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *      dig1 - MCC digit1.
     *      dig2 - MCC digit2.
     *      dig3 - MCC digit3.
     *
     *  Returns:
     *
     *
     */
    void GetMCC (ITS_OCTET& dig1,ITS_OCTET& dig2,ITS_OCTET &dig3) const
    {
        dig1 = mcc[0] & 0x0FU;
        dig2 = mcc[0] >> 4 & 0x0FU;
        dig3 = mcc[1] & 0x0FU;
    }

    /**
     *  Purpose: Sets the MCC value
     *
     *  Input Parameters:
     *          mcc - mcc value as ushort
     *
     *  OutPut Parameters:
     *
     */
    void SetMCC(ITS_USHORT mccVal)
    {
        mcc[0] = (mccVal >> 8) & 0xFFU;
        mcc[1] = mccVal & 0xFFU;
    }

    /**
     *  Purpose: Get MCC value as ushort
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *  Returns:
     *      mcc value as ushort
     *
     */
    ITS_USHORT GetMCC()
    {
        return ((mcc[0] << 8) | mcc[1]);
    }


    /**
     *  Purpose: Set MNC digits.
     *
     *  Input Parameters:
     *      dig1 - MNC digit1.
     *      dig2 -  MNC digit2.
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetMNC (ITS_OCTET dig1,ITS_OCTET dig2)
    {
        if (discriminator != GLOBAL_IDENTIFICATION)
        {
            ITN_THROW(IllegalArgumentException,
                      "MCC not allowd for non-global Network identifier");
        }

        mnc &= ~0x0FU;
        mnc |= dig1 & 0x0FU;
        mnc &= ~0xF0U;
        mnc |= (dig2 << 4) & 0xF0U;
    }


    /**
     *  Purpose: Get MNC digits
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *      dig1 - MNC digit1.
     *      dig2 -  MNC digit2.
     *
     *  Returns:
     *
     */
    void GetMNC (ITS_OCTET& dig1,ITS_OCTET& dig2) const
    {
        dig1 = mnc & 0x0FU;
        dig2 = (mnc >> 4);
    }


    /**
     *  Purpose: Set LAC value
     *
     *  Input Parameters:
     *       val - LAC value
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetLAC (ITS_USHORT val)
    {
        if (discriminator != GLOBAL_IDENTIFICATION &&
                                      discriminator != LAC_AND_CI)
        {
            ITN_THROW(IllegalArgumentException,
                      "LAC not allowd for non-global Network identifier");
        }

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
     *
     *  Returns:
     *      LAC value
     *
     */
    ITS_USHORT GetLAC () const
    {
        return ((lac[0] << 8) | lac[1] );
    }


    /**
     *  Purpose: Set CI value
     *
     *  Input Parameters:
     *      val - CI value
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetCI (ITS_USHORT val)
    {
        ci[0] = (val >> 8 ) & 0xFFU;
        ci[1] = val & 0xFFU;
    }

    /**
     *  Purpose: Get CI value
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *       CI value.
     *
     */
    ITS_USHORT GetCI () const
    {
        return ((ci[0] << 8) | ci[1] );
    }


protected:

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
        return new NetworkElementIdentity(*this);
    }

    /**
     *  Purpose:
     *      This constructor can only be invoked by members and friends.
     *      This contructor decodes the buffer and creates object of its type.
     *
     *  Input Parameters:
     *      buf - is encoded bufer
     *      len - is lenght of encoded bufer
     *
     *  Output Parameters:
     *
     */
    NetworkElementIdentity(const ITS_OCTET* buf,int len);

    virtual void PrintIE(std::ostream&) const;

private: 

    Discriminator discriminator;
    ITS_OCTET     mcc[2];
    ITS_OCTET     mnc;
    ITS_OCTET     lac[2];
    ITS_OCTET     ci[2];

    /**
    *    Assignment Operation 
    */
    NetworkElementIdentity & operator=(const NetworkElementIdentity &right);

    friend class InfoElement;
    friend void TEST_NetworkElementIdentity(void);
};


} // namespace ie
} // namespace bssaple


#endif

