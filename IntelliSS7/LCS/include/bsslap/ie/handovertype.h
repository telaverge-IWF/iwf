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
//  ID: $Id: handovertype.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//  LOG:$Log: handovertype.h,v $
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_IE_HANDOVERTYPE_H
#define BSSLAP_IE_HANDOVERTYPE_H

#include <bsslap/ie/infoelement.h>

namespace bsslap {
namespace ie {

class HandoverType : public InfoElement
{
    friend class InfoElement;
public:
	/**
	 * The coding of the handover type field
	 */
	enum Type {

		INTRA_CELL_HANDOVER_TO_SMALL_CHANNEL = 0x00,
		INTRA_CELL_HANDOVER_TO_NEW_CHANNEL	 = 0x01,
		INTER_CELL_HANDOVER					 = 0x02,
		BSS_SELECTS_HANDOVER				 = 0x03
	};

	/**
	 * Constructor: default
	 * 
	 */
	HandoverType(ITS_OCTET type = 0)
	:	InfoElement(HANDOVER_TYPE), handoverType(type)
	{
		//handoverType = 0x00U;
	}

	/**
	 * Set HandoverType Value
	 * @param value
	 */
	void
	SetHandoverType(Type value)
	{
		handoverType = value;
	}

	/**
	 * Get HandoverType Value
	 * @return handoverType;
	 */
	Type
	GetHandoverType()
	{
		return (Type)handoverType;
	}

protected:
	/**
	 * Constructor: performs decode task
	 * @param buf - Input decode data
	 * @param len - Input data length
	 */
	HandoverType(const ITS_OCTET* buf, int& len);
	
	/**
	 * Encode HandoverType Value
	 */
	virtual void Encode(ITS_OCTET* buf, int& len) const;

	/**
	 * Clone
	 */
	InfoElement* 
	Clone() const
	{
		return new HandoverType(*this);	
	}

    /**
     * Print function that print all IEs
     * @param: (std::ostream&) out
     */
    virtual void Print(std::ostream& out) const;

private :

    ITS_OCTET handoverType;

};

} // end of namespace ie
} // end of namespace bsslap

#endif // !BSSLAP_IE_HANDOVERTYPE_H

