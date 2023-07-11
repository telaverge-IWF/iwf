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
//  ID: $Id: mspositionresponse.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//  LOG:$Log: mspositionresponse.h,v $
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_MSPOSITIONRESPONSE_H
#define BSSLAP_MSPOSITIONRESPONSE_H

#include <bsslap/message.h>
#include <bsslap/ie/rrlpflag.h>
#include <bsslap/ie/rrlpie.h>
#include <bsslap/ie/timingadvance.h>
#include <bsslap/ie/measurementreport.h>
#include <codec_param_checker.h>

namespace bsslap {

/**
 * BSSLAP MS Position Response is a message from the BSS
 * to SMLC that contains the following ie:
 * - flag               [Mandatory]
 * - RRLP info          [Mandatory]
 * - Timing Advance     [Optinal]
 * - Measurementreport  [Optinal]
 */
class Message;

class MSPositionResponse : public Message
{
    friend class Message;
    typedef ParameterChecker<InfoElementMap,
                                ie::InfoElement, 2, 2> Checker;
public:
    
	/**
	 * Constructor
	 */
    MSPositionResponse()
		:Message(MS_POSITION_RESPONSE)
	{
		
	}

    /**
	 *  Get RRLP Flag
	 */
	const ie:RRLPFlag* GetFlag() const
    {
        return static_cast<const ie::RRLPFlag*>(
                    FindIE(ie::InfoElement::RRLP_FLAG));
    }
    /**
	 * Get RRLP info
	 */
	const ie::RRLPIe* GetRRLPIe() const
    {
        return static_cast<const ie::RRLPIe*>(
                    FindIE(ie::InfoElement::RRLP_IE));

    /**
     * Get Timing Advance 
     */
	const ie::TimingAdvance* GetTimingAdvance() const
    {
        return static_cast<const ie::TimingAdvance*>(
                    FindIE(ie::InfoElement::TIMING_ADVANCE));
    }

    /**
     * Get Measurement Report
     */
	const ie::MeasurementReport* GetMeasurementReport() const
    {
        return static_cast<const ie::MeasurementReport*>(
                    FindIE(ie::InfoElement::MEASUREMENT_REPORT));

    /**
     *
     */
    ITS_BOOLEAN MeasurementReportPresent()
    {
        return ITS_TRUE;
    }

    virtual Message *Clone() const
    {
        return new MSPositionResponse(*this);
    }

    /**
     *
     */
    void GetMandatoryParams(ie::InfoElement::Type* mandatory,
                            int& size) const
    {
        mandatory = margs;
        size = 2;
    }

protected:

    /**
     * Constructor
     * @param buffer
     * @param len
     */
    MSPositionResponse(ITS_OCTET *buffer, int& len);

    /**
     * This function is to check the mandatory parameter of the IE
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

#endif // !BSSLAP_MSPOSITIONRESPONSE_H

