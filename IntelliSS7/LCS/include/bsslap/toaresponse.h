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
//  ID: $Id: toaresponse.h,v 1.1.2.2 2010/03/26 11:47:11 rajeshak Exp $
//
//  LOG:$Log: toaresponse.h,v $
//  LOG:Revision 1.1.2.2  2010/03/26 11:47:11  rajeshak
//  LOG:Renaming IE code for SERVING_CELL_IDENTITY to CELL_IDENTITY
//  LOG:
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_TOARESPONSE_H
#define BSSLAP_TOARESPONSE_H

#include <bsslap/message.h>
#include <bsslap/ie/channeldescription.h>
#include <bsslap/ie/cellidentity.h>
#include <bsslap/ie/timingadvance.h>
#include <bsslap/ie/measurementreport.h>
#include <bsslap/ie/handoverreference.h>
#include <bsslap/ie/frequencylist.h>
#include <bsslap/ie/mspower.h>
#include <bsslap/ie/cellidentitylist.h>
#include <codec_param_checker.h>
#include <codec_trace.h>

namespace bsslap {

class Message;

/**
 * The TOA Response message is from BSS to SMLC
 * It contains following ie components
 * - Channel Description    [Mandatory]
 * - Frequency List         [Mandatory]
 * - Handover Reference     [Mandatory]
 * - Target Cell Identity   [Mandatory]
 * - Serving Cell Identity  [Mandatory]
 * - Timing Advance         [Mandatory]
 * - MS Power               [Mandatory]
 * - Measurement Report     [Optional]
 */
class TOAResponse : public Message
{
    friend class Message;
    typedef ParameterChecker<InfoElementMap,
                                ie::InfoElement, 7, 1> Checker;
public:
    
	/**
	 * Constructor
	 */
    TOAResponse()
		:Message(TOA_RESPONSE)
	{
	}  
    /**
	 *
	 */
    ~TOAResponse()
	{
	}

    /**
	 *
	 */
	const ie::MSPower* GetMSPower() const
	{
		return static_cast<const ie::MSPower*>(
                FindIE(ie::InfoElement::MS_POWER));
	}

    /**
	 *
	 */
	const ie::ChannelDescription* GetChannelDescription() const
	{
        return static_cast<const ie::ChannelDescription*>(
                 FindIE(ie::InfoElement::CHANNEL_DESCRIPTION));
	}

	/**
	 *	Phase 2
	 */
	const ie::FrequencyList* GetFrequencyList() const
	{
        return static_cast<const ie::FrequencyList*>(
                FindIE(ie::InfoElement::FREQUENCY_LIST));
	}

	/**
	 *
	 */
	const ie::HandoverReference* GetHandoverReference() const
	{
        return static_cast<const ie::HandoverReference*>(
                FindIE(ie::InfoElement::HANDOVER_REFERENCE));
	}

	/**
	 *
	 */
	const ie::CellIdentityList* GetTargetCellIdentity() const
	{
        return static_cast<const ie::CellIdentityList*>(
                FindIE(ie::InfoElement::CELL_IDENTITY_LIST));
	}

    /**
     *
     */
    const ie::CellIdentity* GetServingCellIdentity() const
    {
        return static_cast<const ie::CellIdentity*>(
                FindIE(ie::InfoElement::CELL_IDENTITY));
    }

	/**
	 *
	 */
	const ie::TimingAdvance* GetTimingAdvance() const
	{
        return static_cast<const ie::TimingAdvance*>(
                FindIE(ie::InfoElement::TIMING_ADVANCE));
	}

	/**
	 *
	 */
    const ie::MeasurementReport* GetMeasurementReport() const
    {
        return static_cast<const ie::MeasurementReport*>(
            FindIE(ie::InfoElement::MEASUREMENT_REPORT));
    }

    /**
     * Checks whether the measurement report is present.
     */
    ITS_BOOLEAN MeasurementReportPresent() const
    {
        return ITS_TRUE;
    }

    /**
     *
     */
    virtual Message *Clone() const
    {
        return new TOAResponse(*this);
    }

    /**
     *
     */
    void GetMandatoryParams(ie::InfoElement::Type* mandatory,
                            int& size) const
    {
        memcpy(mandatory, margs, sizeof(ie::InfoElement::Type) * 7);
        size = 7;
    }

protected:

    /**
     * Constructor (perform as decoder)
     * @param buffer
     * @param len
     */
    TOAResponse(ITS_OCTET *buffer, int& len);

	/**
	 *
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

#endif // !BSSLAP_TOARESPONSE_H

