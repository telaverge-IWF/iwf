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
//   ID: $Id: cellidentifier.h,v 1.1.2.3 2010/03/26 11:48:05 rajeshak Exp $
//
//   LOG: $Log: cellidentifier.h,v $
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

#ifndef BSSAPLE_IE_CELLIDENTIFIER_H
#define BSSAPLE_IE_CELLIDENTIFIER_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{
namespace ie
{

static void TEST_CELL_IDENTITY();

struct CellIdentifierStruct
{
    enum Discriminator
    {
        GLOBAL_IDENTIFICATION = 0x00,
        LAC_AND_CI            = 0x01,
        CI                    = 0x02,
        NO_CELL               = 0x03
    };

    Discriminator discriminator;
    ITS_OCTET     mcc[2];
    ITS_OCTET     mnc;
    ITS_OCTET     lac[2];
    ITS_OCTET     ci[2];
};

/**
 * CellIdentifier is a variable length information element identifying a
 * particular cell.
 */
class CellIdentifier: public InfoElement, public CellIdentifierStruct
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
    CellIdentifier()
    : InfoElement(CELL_IDENTIFIER, 0)
    {
        discriminator = NO_CELL;
    }

    /**
     */
/**
    CellIdentifier(const CellIdentifier::Struct &cis)
    : InfoElement(CELL_IDENTIFIER, 0), _s(cis)
    {}
**/

    const CellIdentifierStruct &GetAsStruct() const
    {
        return *static_cast<const CellIdentifierStruct *>(this);
    }

    /**
     * Destructor
     */
    ~CellIdentifier(){ }

    /**
     *  Purpose:  Sets cell id discriminator
     *
     *  Input Parameters:
     *      val - is  cell discriminator value.
     *
     *  OutPut Parameters:
     *
     */
    void SetDiscriminator(Discriminator val)
    {
        discriminator = val;
    }

    /**
     *  Purpose:val Gets cell id discriminator
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *
     *  Returns:
     *      returns the cell Discriminator.
     *
     */
    Discriminator GetDiscriminator() const
    {
        return discriminator;
    }

    /**
     *  Purpose: Sets the MCC digits
     * 
     *  Input Parameters:
     *      dig1 - MCC digit1
     *      dig2 - MCC digit2
     *      dig3 - MCC digit3
     *
     *  OutPut Parameters:
     *
     */
    void SetMCC(ITS_OCTET dig1,ITS_OCTET dig2,ITS_OCTET dig3)
    {

        mcc[0] &= ~0x0FU;
        mcc[0] |= dig1 & 0x0FU;
        mcc[0] &= ~0xF0U;
        mcc[0] |= (dig2 << 4) & 0xF0U;

        mcc[1] = 0xF0; //all 1 1 1 1
        mcc[1] &= ~0x0FU;
        mcc[1] |= dig3 & 0x0FU;
    }

    /**
     *  Purpose: Get MCC 3 digits
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *      dig1 - MCC digit1
     *      dig2 - MCC digit2
     *      dig3 - MCC digit3
     *
     */
    void GetMCC(ITS_OCTET &dig1,ITS_OCTET &dig2,ITS_OCTET &dig3) const
    {
        dig1 = mcc[0] & 0x0FU;
        dig2 = mcc[0] >> 4 & 0x0FU;
        dig3 = mcc[1] & 0x0FU;
    }

    /**
     *  Purpose: Sets the MCC value
     *
     *  Input Parameters: 
     *          mcc - mcc value as ushort.
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
     *  Purpose: Get MCC value as ushort.
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *  Returns:
     *      mcc value as ushort.
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
     *  OutPut Parameters:
     *
     */
    void SetMNC(ITS_OCTET dig1,ITS_OCTET dig2)
    {

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
     */
    void GetMNC(ITS_OCTET& dig1,ITS_OCTET& dig2) const
    {
        dig1 = mnc & 0x0FU;
        dig2 = (mnc >> 4);
    }

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

    /**
     *  Purpose: Set CI value.
     *
     *  Input Parameters:
     *      val - CI value.
     *
     *  OutPut Parameters:
     *
     */
    void SetCI(ITS_USHORT val)
    {
        ci[0] = (val >> 8 ) & 0xFFU;
        ci[1] = val & 0xFFU;
    }

    /**
     *  Purpose: Get CI value
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *      
     *  Returns:
     *      CI value.
     *
     */
    ITS_USHORT GetCI () const
    {
        return ((ci[0] << 8) | ci[1] );
    }

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
     *
     *  Input Parameters:
     *      buf - is encoded bufer.
     *      len - is lenght of encoded bufer.
     *
     *  Output Parameters:
     *
     */
    CellIdentifier(const ITS_OCTET *buf, int len);

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
        return new CellIdentifier(*this);
    }

    virtual void PrintIE(std::ostream &) const;

private:
    ITS_OCTET hexBuff[25];

    friend class InfoElement;
    friend void TEST_CELL_IDENTITY();
};


} // namespace ie
} // namespace bssaple


#endif

