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
//  ID: $Id: cellidentitylist.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//  LOG:$Log: cellidentitylist.h,v $
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_IE_CELLIDENTITY_LIST_H
#define BSSLAP_IE_CELLIDENTITY_LIST_H 

#include <bsslap/ie/infoelement.h>
#include <vector>


namespace bsslap
{
namespace ie
{
struct CellIdDiscriminatorStruct
{
    enum Discriminator
    {
        GLOBAL_IDENTIFICATION = 0x00,
        LAC_AND_CI            = 0x01,
        TARGET_ID_2           = 0x02,
        TARGET_ID_3           = 0x03
    };
    Discriminator discriminator;

    ITS_OCTET     mcc[2];
    ITS_OCTET     mnc;
    ITS_OCTET     lac[2];
    ITS_OCTET     ci[2];
    ITS_OCTET     targetId2[9]; //To be ignored while decoding.
    ITS_OCTET     targetId3[6]; //To be ignored while decoding.
};

/**
 * CellIdentityList is a variable length information element identifying a
 * neighbouring  cells.
 */
class CellIdDiscriminator: public CellIdDiscriminatorStruct
{
public:

     CellIdDiscriminator()
	{
	}
    const CellIdDiscriminatorStruct &GetAsStruct() const
    {
        return *static_cast<const CellIdDiscriminatorStruct *>(this);
    }

    /**
     * Destructor
     */
    ~CellIdDiscriminator(){ }

    /**
     *  Purpose:  Sets cell id discriminator
     *
     *  Input Parameters:
     *      val - is  cell discriminator value.
     *
     *  OutPut Parameters:
     *
     */
    //void SetDiscriminator(Discriminator val)
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


protected: 
        /**
	 * Clone
	 */

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
    //virtual void Encode (ITS_OCTET* buf, int& len) const;

    virtual CellIdDiscriminator *Clone() const
    {
        return new CellIdDiscriminator(*this);
    }

    //virtual void Print(std::ostream &) const;

};

class CellIdentityList: public InfoElement 
{
public:
    typedef std::vector<CellIdDiscriminator > cellIdVector;

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

    /*
	 * Add CellId into vector
	 */
	 void
	 AddCellId(CellIdDiscriminator cid)
	 {
		 cellVector.push_back(cid);
	 }

    /*
	 * Get CellId from vector
	 cellIdVector& 
	 GetCellId()
	 {
		 return cellVector;
	 }
	 */
    CellIdentityList()
    : InfoElement(CELL_IDENTITY_LIST)
    {
    }


    /**
     * Destructor
     */
    ~CellIdentityList(){ }


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
    CellIdentityList(const ITS_OCTET *buf, int& len);

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

    virtual InfoElement*
	Clone() const
    {
        return new CellIdentityList(*this);
    }

    virtual void Print(std::ostream &) const;

private:

	friend class CellIdDiscriminator;
    cellIdVector cellVector ;
    friend class InfoElement;
};


} // namespace ie
} // namespace bsslap


#endif

