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
//  ID: $Id: neighborstarttime.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//  LOG:$Log: neighborstarttime.h,v $
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_IE_NEIGHBORSTARTTIME_H
#define BSSLAP_IE_NEIGHBORSTARTTIME_H

#include <bsslap/ie/infoelement.h>
#include<vector>

namespace bsslap {
namespace ie {

class NeighborStartTime : public InfoElement
{
    friend class InfoElement;

public :
    
    typedef std::vector<ITS_OCTET> TimeVector;

    /**
     * Constructor
     */
    NeighborStartTime()
		:InfoElement(NEIGHBOR_STARTING_TIME)
	{
	}

    /**
     *  Add T1 value
     * @param value
     */
	void 
    AddT1(ITS_OCTET value)
    {
        t1.push_back(value);
    }

    /**
     * Get T1 value 
     */
    TimeVector& 
    GetT1()
    {
        return t1;
    }

    /**
     * Add T2 value
     * @param value
     */
    void 
    AddT2(ITS_OCTET value)
    {
        t2.push_back(value);
    }

    /**
     *  Get T1 value
     */
    TimeVector& 
    GetT2()
    {
        return t2;
    }

    /**
     *  Add T3 value
     *  @param value
     */
	void 
    AddT3(ITS_OCTET value)
    {
        t3.push_back(value);
    }

    /**
     *  Get T3 value
     */
    TimeVector& 
    GetT3()
    {
        return t3;
    } 

    /**
     * Get the NeighborStartTime length of T1, T2, or T3
     */
    int GetSizeOfNeighborStartTime()
    {
        return ( t1.size() * 2 );
    }
protected :

    /**
	 * Constructor: perform decode task
	 * @param buf - Input encode data
	 * @param len - Input data length
	 */
	NeighborStartTime(const ITS_OCTET* buf, int& len);
	
	/**
     *
     */
    virtual void Encode(ITS_OCTET *buf, int& len) const;
 
    /**
	 * Clone
	 */
	InfoElement* 
	Clone() const
	{
		return new NeighborStartTime(*this);	
	}

    /**
     * Print function that print all IEs
     * @param: (std::ostream&) out
     */
    virtual void Print(std::ostream& out) const;


private :
   
    TimeVector	    t1;
    TimeVector      t3;
    TimeVector  	t2;
};

} // end of namespace ie
} // end of namespace bsslap

#endif // !BSSLAP_IE_NEIGHBORSTARTTIME_H

