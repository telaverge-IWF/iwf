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
//  ID: $Id: neighborcellidentity.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//  LOG:$Log: neighborcellidentity.h,v $
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_IE_NEIGHBORCELLIDENTITY_H
#define BSSLAP_IE_NEIGHBORCELLIDENTITY_H

#include <bsslap/ie/infoelement.h>
#include <vector>

namespace bsslap {
namespace ie {


class NeighborCellIdentity : public InfoElement
{
    friend class InfoElement;
public :

    typedef std::vector<ITS_USHORT> CellidVector;
    /**
	 * Constructor
	 */
	NeighborCellIdentity()
	:	InfoElement(NEIGHBOR_CELL_IDENTITY)
	{
	}

	/**
	 * Add NeighborCellIdentity Value
	 * @param value - ITS_USHORT type
	 */
	void
	AddNeighborCellid(ITS_USHORT value)
	{
		cellid.push_back(value);
	}

	/**
	 * Get NeighborCellIdentity Value
	 * @param: None
	 */
    CellidVector&
	GetNeighborCellid()
	{ 
		return cellid;
	}

    /**
     * Get the size of CellidVector
     */
    int GetSizeOfNeighborCellid()
    {
        return ( cellid.size() * 2 );
    }

protected:
	/**
	 * Constructor: perform decode task
	 * @param buf - Input encode data
	 * @param len - Input data length
	 */
	NeighborCellIdentity(const ITS_OCTET* buf, int& len);
	
	/**
	 * Encode NeighborCellIdentity Value
	 */
	virtual void Encode(ITS_OCTET* buf, int& len) const;

	/**
	 * Clone
	 */
	InfoElement* 
	Clone() const
	{
		return new NeighborCellIdentity(*this);	
	}

    /**
     * Print function that print all IEs
     * @param: (std::ostream&) out
     */
    virtual void Print(std::ostream& out) const;


private :

    CellidVector        cellid;
};

} // end of namespace ie
} // end of namespace bsslap

#endif // !BSSLAP_IE_NEIGHBORCELLIDENTITY_H

