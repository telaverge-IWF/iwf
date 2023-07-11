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
//  ID: $Id: cellidentity.h,v 1.1.2.4 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG:$Log: cellidentity.h,v $
//  LOG:Revision 1.1.2.4  2010/03/31 05:47:14  rajeshak
//  LOG:ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG:Revision 1.1.2.3  2010/03/26 11:48:05  rajeshak
//  LOG:GetHexBuff function signature changes
//  LOG:
//  LOG:Revision 1.1.2.2  2010/03/25 06:32:32  rajeshak
//  LOG:API to get the Hex dump after encode/decode (for TDR).
//  LOG:
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_IE_CELLIDENTITY_H
#define BSSLAP_IE_CELLIDENTITY_H

#include <bsslap/ie/infoelement.h>

namespace bsslap {
namespace ie {

class CellIdentity : public InfoElement
{
    friend class InfoElement;

public:

    enum CellIdType
    {
        SERVING    = 0x09U,
        TARGET     = 0x1CU
    };
	/**
	 * Constructor : Default
	 * @param cellIdentity
	 */
	CellIdentity(CellIdType type = SERVING, ITS_USHORT cellid = 0)
	:	InfoElement((InfoElement::Type)type), cellIdentity(cellid) 
	{
	}

	/**
	 * Set CellIdentity Value
	 * @param value 
	 */
	void
	SetCellIdentity(ITS_USHORT value)
	{
		cellIdentity = value;
	}

	/**
	 * Get CellIdentity Value
	 * @param: None
	 * @return: cellIdentity
	 */
	const ITS_USHORT
	GetCellIdentity() const
	{
		return cellIdentity;
	}

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
	 * Constructor : overloaded construtor performs decode
	 * @param buf - pointer of the decoded data buffer
	 * @param len - length of data buffer
	 */
	CellIdentity(const ITS_OCTET* buf, int& len);
	
	/**
	 * Encode CellIdentity Value
	 *
	 * @param buf The buffer that will contain the encoded data.
	 * @param len This parameter will contain the length of encodede data.
	 * @return CODEC_SUCCESS if the function succeeds.
	 */
	virtual void Encode(ITS_OCTET* buf, int& len) const;

	/**
	 * Clone
	 */
	InfoElement* 
	Clone() const
	{
		return new CellIdentity(*this);	
	}

    /**
     * Print function that print all IEs
     * @param: (std::ostream&) out
     */
    virtual void Print(std::ostream& out) const;

private :
    mutable ITS_OCTET hexBuff[15];
    ITS_USHORT cellIdentity;
};

} // end of namespace ie
} // end of namespace bsslap

#endif // !BSSLAP_IE_CELLIDENTITY_H

