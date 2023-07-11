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
//  ID: $Id: cause.h,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG:$Log: cause.h,v $
//  LOG:Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG:ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_IE_CAUSE_H
#define BSSLAP_IE_CAUSE_H

#include <bsslap/ie/infoelement.h>

namespace bsslap {
namespace ie {
#define BSSLAPCAUSE_VALUE_STRING(c) \
        (((c) == CONGESTION) ?                               "CONGESTION" : \
		 ((c) == CHANNEL_MODE_NOT_SUPPORT) ?                 "CHANNEL_MODE_NOT_SUPPORT" : \
		 ((c) == POSITION_PORCEDURE_NOT_SUPPORT) ?           "POSITION_PORCEDURE_NOT_SUPPORT" : \
		 ((c) == FAILURE_FOR_OTHER_RADIO_RELATED_EVENT) ?    "FAILURE_FOR_OTHER_RADIO_RELATED_EVENT" : \
		 ((c) == INTRA_BSS_HANDOVER) ?                       "INTRA_BSS_HANDOVER" : \
		 ((c) == SUPERVISION_TIMER_EXPIRED) ?                "SUPERVISION_TIMER_EXPIRED" : \
		 ((c) == INTER_BSS_HANDOVER) ?                       "INTER_BSS_HANDOVER" : \
		 ((c) == LOSS_OF_SIGNALING_CONNECTION_TO_MS) ?       "LOSS_OF_SIGNALING_CONNECTION_TO_MS" : \
		 ((c) == INCORRECT_SERVING_CELL_IDENTITY) ?          "INCORRECT_SERVING_CELL_IDENTITY" : \
         ((c) == BSSAP_LE_SEGMENTATION_ERROR) ?              "BSSAP_LE_SEGMENTATION_ERROR" : \
		                                                     "ERROR")


class Cause : public InfoElement
{
    friend class InfoElement;
public :
	/**
	 * The cause field is ooded as follows
	 */
	enum Type
	{
		CONGESTION								= 0x00, 
		CHANNEL_MODE_NOT_SUPPORT				= 0x01,
		POSITION_PORCEDURE_NOT_SUPPORT			= 0x02,
		FAILURE_FOR_OTHER_RADIO_RELATED_EVENT	= 0x03,
		INTRA_BSS_HANDOVER						= 0x04,
		SUPERVISION_TIMER_EXPIRED				= 0x05,
		INTER_BSS_HANDOVER						= 0x06,
		LOSS_OF_SIGNALING_CONNECTION_TO_MS		= 0x07,
		INCORRECT_SERVING_CELL_IDENTITY			= 0x08,
		BSSAP_LE_SEGMENTATION_ERROR             = 0x09
	};

	/**
	 * Constructor:
	 */
	Cause(Type cause)
	: InfoElement(CAUSE), causeValue(cause)
	{
        if (cause > 0x09)
            ITN_THROW(NumberFormatException, "Invalid IE value");
	}

    
	/**
	 * Set Cause Value
	 *
	 * @param value - contains Cause value,
	 *		   
	 */
	void
	SetCauseValue(Type value)
	{
        if (value <= 0x09)
            causeValue = value;
        else
            ITN_THROW(NumberFormatException, "Invalid IE value");
	}

	/**
	 * Get Cause Value
	 *
	 * @return causeValue 
	 */
	const Type
	GetCauseValue() const
	{
		return causeValue;
	}

protected :
	/**
	 * Constructor: this contructor will perform decode the ie 
	 *
	 * @param buf - buffer contains data
	 *		  len - length of contained data
	 */
	Cause(const ITS_OCTET* buf, int& len);

    
	/**
	 * Encode Cause Value
	 *
	 * @param:buf - The buffer that will contain the encoded data.
	 * @param:len - This parameter will contain the length of encodede data.
	 * @return: CODEC_SUCCESS - if the function succeeds.
	 */ 
	virtual void Encode(ITS_OCTET* buf, int& len) const;

    /**
	 * Clone : get concrete type ie copy
	 * 
	 * @return new Cause
	 */
	InfoElement* 
	Clone() const
	{
		return new Cause(*this);	
	}
    
    /**
     * Print function that print all IEs
     * @param: (std::ostream&) out
     */
    virtual void Print(std::ostream& out) const;


private :

    Type causeValue;

};

} // end of namespace ie
} // end of namespace bsslap

#endif // !BSSLAP_IE_CAUSE_H

