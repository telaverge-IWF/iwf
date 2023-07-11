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
//  ID: $Id: toarequest.h,v 1.1.2.2 2010/03/26 11:47:11 rajeshak Exp $
//
//  LOG:$Log: toarequest.h,v $
//  LOG:Revision 1.1.2.2  2010/03/26 11:47:11  rajeshak
//  LOG:Renaming IE code for SERVING_CELL_IDENTITY to CELL_IDENTITY
//  LOG:
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_TOAREQUEST_H
#define BSSLAP_TOAREQUEST_H

#include <bsslap/message.h>
#include <bsslap/ie/cellidentity.h>
#include <bsslap/ie/deltatimer.h>
#include <bsslap/ie/startingtime.h>
#include <bsslap/ie/neighborcellidentity.h>
#include <bsslap/ie/neighborstarttime.h>
#include <bsslap/ie/handovertype.h>
#include <codec_param_checker.h>
#include <codec_trace.h>

namespace bsslap {

class Message;

/**
 * The TOA Request is a message from SMLC to the BSC
 * It contains following IEs
 * - Delta Timer            [Mandatory]
 * - Handover Type          [Mandatory]
 * - Serving Cell ID        [Mandatory]
 * - Starting Time          [Mandatory]
 * - Neighbor Cell ID       [Optional]
 * - Neighbor Starting Time [Optional]
 */
class TOARequest : public Message
{
    typedef ParameterChecker<InfoElementMap,
                        ie::InfoElement, 4, 2> Checker;
    friend class Message;

public:
    
	/**
	 * Constructor
	 */
    TOARequest()
		:Message(TOA_REQUEST)
	{
	}
    
    /**
	 *
	 */
	const ie::DeltaTimer* GetDeltaTimer() const
	{
        return static_cast<const ie::DeltaTimer *>(
            FindIE(ie::InfoElement::DELTA_TIMER)); 
	}

    /**
	 *
	 */
	const ie::HandoverType* GetHandoverTypeIE() const
	{
        return static_cast<const ie::HandoverType *>(
            FindIE(ie::InfoElement::HANDOVER_TYPE));
	}

    /**
	 *
	 */
    const ie::CellIdentity* GetServingCellId() const
    {
        return static_cast<const ie::CellIdentity*>(
            FindIE(ie::InfoElement::CELL_IDENTITY));
    }

    /**
	 *
	 */
	const ie::StartingTime* GetStartingTime() const
	{
        return static_cast<const ie::StartingTime *>(
            FindIE(ie::InfoElement::STARTING_TIME));
	}

    /**
     *
     */
    ITS_BOOLEAN NeiborCellIdentityPresent()
    {
        return ITS_TRUE;
    }

    /**
     *
     */
    ITS_BOOLEAN NeiborCellStartTimePresent()
    {
        return ITS_TRUE;
    }
    /**
	 *
	 */
	const ie::NeighborCellIdentity* GetNeighborCellIdentity() const
	{
        return static_cast<const ie::NeighborCellIdentity*>(
            FindIE(ie::InfoElement::NEIGHBOR_CELL_IDENTITY));        
	}

    /**
	 *
	 */
	const ie::NeighborStartTime* GetNeighborStartingTime() const
	{
        return static_cast<const ie::NeighborStartTime *>(
            FindIE(ie::InfoElement::NEIGHBOR_STARTING_TIME));        
	}

    /**
     *
     */
    virtual Message *Clone() const
    {
        return new TOARequest(*this);
    }

    /**
     *
     */
    void GetMandatoryParams(ie::InfoElement::Type* mandatory,
                            int& size) const
    {
        memcpy(mandatory, margs, sizeof(ie::InfoElement::Type) * 4);
        size = 4;
    }

protected:

    /**
     * Constructor
     * @param buffer
     * @param len
     */
    TOARequest(ITS_OCTET *buffer, int& len);    

    /**
	 * Check for the Mandatory IEs of TOA Request
	 */
    virtual void CheckForMandatoryParam() const
	{
        switch (checker.CheckParameters(ies))
        {
        case Checker::SUCCESSFUL:
            break;
        case Checker::MISSING_MANDATORY:
            ITN_THROW(MissingParameterException, "Missing mandatory IE");
        case Checker::ILLEGAL_PARAMETER:
            ITN_THROW(IllegalArgumentException, "Illegal IE in message");
        }
	}
private:

    static ie::InfoElement::Type margs[];
    static ie::InfoElement::Type oargs[];
    static Checker checker;
    
};

} // end of basslap namespace

#endif // !BSSLAP_TOAREQUEST_H

