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
//  ID: $Id: mspower.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//  LOG:$Log: mspower.h,v $
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////



#ifndef BSSLAP_IE_MSPOWER_H
#define BSSLAP_IE_MSPOWER_H

#include <bsslap/ie/infoelement.h>

namespace bsslap {
namespace ie {

//const ITS_OCTET MSPOWER_MASK = 0X1FU;

class MSPower : public InfoElement
{
    friend class InfoElement;
public :
    
	/**
	 * Constructor
	 * 
	 */
	MSPower(ITS_OCTET power = 0)
	:	InfoElement(MS_POWER), powerLevel(power)
	{
	}

	/**
	 * Set MSPower Value: This value fromat is bit(8)~bit(6) 
	 * is spare. So the mask is set as 0x1FU (MSPOWER_MASK)
	 * @param value 
	 */
	void
	SetMSPowerLevel(ITS_OCTET value)
	{
		//value &= MSPOWER_MASK;
		powerLevel = value;
	}

	/**
	 * Get MSPower Value
	 * 
	 * @return powerLevel
	 */
	ITS_OCTET
	GetMSPowerLevel()
	{
		return powerLevel;
	}

protected:
	/**
	 * Constructor: performs decode task
	 * @param buf - Input data buffer to decode
	 * @param len - Input data buffer length
	 */
	MSPower(const ITS_OCTET* buf, int& len);
	
	/**
	 * Encode MSPower Value
	 * @param buf - Input data buffer to decode
	 * @param len - Input data buffer length
	 */
	virtual void Encode(ITS_OCTET* buf, int& len) const;
	
	/**
	 * Clone
	 */
	InfoElement* 
	Clone() const
	{
		return new MSPower(*this);	
	}

    /**
     * Print function that print all IEs
     * @param: (std::ostream&) out
     */
    virtual void Print(std::ostream& out) const;

private :

    ITS_OCTET powerLevel; // range from 0 ~ 31

};

} // end of namespace ie
} // end of namespace bsslap

#endif // !BSSLAP_IE_MSPOWER_H

