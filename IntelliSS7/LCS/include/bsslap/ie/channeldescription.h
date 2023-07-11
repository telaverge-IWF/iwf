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
//  ID: $Id: channeldescription.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//  LOG:$Log: channeldescription.h,v $
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_IE_CHANNELDESCRIPTION_H
#define BSSLAP_IE_CHANNELDESCRIPTION_H

#include <bsslap/ie/infoelement.h>

namespace bsslap {
namespace ie {

class ChannelDescription: public InfoElement
{
    friend class InfoElement;

	enum ChannelMask {

		ARFCN_HIGH_PART_MASK	= 0x03U,
		TN_MASK					= 0x07U,
		MAIO_HIGH_PART_MASK		= 0x0FU,
		H_MASK					= 0x10U,
		HSN_MASK				= 0x3FU,
		MAIO_LOW_PART_MASK		= 0xC0U,
		TSC_MASK				= 0xE0U,
		CHANNEL_TYPE_TDMA_OFFSET_MASK = 0xF8U,
		ARFCN_LOW_PART_MASK	= 0xFFU		
	};

public :

    /**
	 * Constructor: default
	 */
	ChannelDescription(const ITS_OCTET _maio =0, ITS_USHORT _arfcn = 0,
                       ITS_OCTET _channel_tdma =0, ITS_OCTET _hop = 0,
                       ITS_OCTET _tn = 0, ITS_OCTET _tsc = 0,
                       ITS_OCTET _hsn = 0)
	:	InfoElement(CHANNEL_DESCRIPTION),maio(_maio),arfcn(_arfcn),
        channelTypeTdmaOffset(_channel_tdma), hop(_hop),
        tn(_tn), tsc(_tsc), hsn(_hsn)
	{
	}

	/**
	 * Set channelType_TDMAoffset Value
	 * @param value
	 */
	void
	SetChannelType_TDMAoffset(ITS_OCTET value)
	{
        if (value <= 0x1F) 
            channelTypeTdmaOffset = value;
        else
            ITN_THROW(NumberFormatException, "Invalid IE value");
	}

	/**
	 * Get channelType_TDMAoffset Value
	 * @return channelType_TDMAoffset
	 */
	ITS_OCTET
	GetChannelType_TDMAoffset()
	{
        return channelTypeTdmaOffset;
	}
	
	/**
	 * Set TN value
	 * @param value
	 */
	void
	SetTN(ITS_OCTET value)
	{
        if (value <= 0x07)
            tn = value;
        else
            ITN_THROW(NumberFormatException, "Invalid IE value");
	}

	/**
	 * Get TN value
	 * @return TN value
	 */
	ITS_OCTET
	ChannelDescription::GetTN()
	{
		return tn;
	}
	
	/**
	 * Set TSC value
	 * @param value
	 */
	void
	SetTSC(ITS_OCTET value)
	{
        if (value <= 0x07)
            tsc = value;
        else
            ITN_THROW(NumberFormatException, "Invalid IE value");
	}

	/**
	 * Get TSC value
	 * @return TSC
	 */
	ITS_OCTET
	GetTSC()
	{
		return tsc;
	}

	/**
	 * Set H(Hopping Channel) value
	 * @param value
	 */
	void
	SetH(ITS_BOOLEAN value)
	{
        if (value <= 0x01)
            hop = value;
        else
            ITN_THROW(NumberFormatException, "Invalid IE value"); 
	}

	/**
	 * Get H(Hopping Channel) value
	 */
	ITS_BOOLEAN
	GetH()
	{
        return hop;
	}

	/**
	 * Set MAIO value
	 */
	void
	SetMAIO(ITS_OCTET value)
	{
        if ((value <= 0x33) && (hop == 0x01 ))
            maio = value;
        else
            ITN_THROW(NumberFormatException, "Invalid IE value");
	}

	/**
	 * Get MAIO value
	 */
	ITS_OCTET
	GetMAIO()
	{
        return maio;
	}

	/**
	 * Set HSN value
	 * @param value
	 */
	void
	SetHSN(ITS_OCTET value)
	{
        if (value <= 0x3F)
            hsn = value;
        else
            ITN_THROW(NumberFormatException, "Invalid IE value");
	}

	/**
	 * Get HSN value
	 */
	ITS_OCTET
	GetHSN()
	{
        return hsn;
	}

	/**
	 * Set ARFCN value
	 * @param value
	 */
	void
	SetARFCN(ITS_USHORT value)
	{
        if ((value <= 0x3FF) && (hop == 0x00))
            arfcn = value;
        else
            ITN_THROW(NumberFormatException, "Invalid IE value");
	}

	/**
	 * Get ARFCN value
	 */
	ITS_USHORT
	GetARFCN()
	{
        return arfcn;
	}

protected:
	/**
	 * Constructor - performs as decoder
	 * @param buf
	 * @param len
	 */
	ChannelDescription(const ITS_OCTET* buf, int& len);
	
	/**
	 * Encode ChannelDescription Value
	 * @param buf
	 * @param len
	 */
	virtual void Encode(ITS_OCTET* buf, int& len) const;
	
	/**
	 * Clone
	 */
	InfoElement* 
	ChannelDescription::Clone() const
	{
		return new ChannelDescription(*this);	
	}

    /**
     * Print function that print all IEs
     * @param: (std::ostream&) out
     */
    virtual void Print(std::ostream& out) const;
 
private :
  
    ITS_OCTET   maio;		
    ITS_USHORT  arfcn;      
    ITS_OCTET   channelTypeTdmaOffset;
    ITS_BOOLEAN hop;
    ITS_OCTET   tn;
    ITS_OCTET   tsc;
    ITS_OCTET   hsn;
    
};

} // end of namespace ie
} // end of namespace bsslap

#endif // !BSSLAP_IE_CHANNELDESCRIPTION_H

