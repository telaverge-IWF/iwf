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
//  ID: $Id: talayer3.h,v 1.1.2.3 2010/09/03 10:21:12 rajeshak Exp $
//
//  LOG:$Log: talayer3.h,v $
//  LOG:Revision 1.1.2.3  2010/09/03 10:21:12  rajeshak
//  LOG:Issue 3400 Codec changes
//  LOG:
//  LOG:Revision 1.1.2.2  2010/08/06 05:20:05  rajeshak
//  LOG:Fix for Issue:3351
//  LOG:
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_TALAYER3_H
#define BSSLAP_TALAYER3_H

#include <bsslap/message.h>
#include <bsslap/ie/timingadvance.h>
#include <bsslap/ie/measurementreport.h>
#include <bsslap/ie/cellidentitylist.h>
#include <codec_param_checker.h>
#include <codec_trace.h>

namespace bsslap {

class Message;

class TALayer3 : public Message
{
    typedef ParameterChecker<Message::InfoElementMap,
                            ie::InfoElement, 1, 3> Checker;
    friend class Message;

public:
    
	/**
	 * Constructor
	 */
    TALayer3()
		:Message(TA_LAYER3)
	{	
	}
 
    /**
	 * Get Timig Advance IE
	 */
    const ie::TimingAdvance* GetTimingAdvance() const
	{
        return static_cast<const ie::TimingAdvance*>(
            FindIE(ie::InfoElement::TIMING_ADVANCE));
	}

    /**
	 * Get Measurement Report IE
	 */
    const ie::MeasurementReport* GetMeasurementReport() const
	{
        return static_cast<const ie::MeasurementReport*>(
            FindIE(ie::InfoElement::MEASUREMENT_REPORT));
	}

    /**
	 *
	 */
	ITS_BOOLEAN MeasurementReportPresent()
	{
		return ITS_TRUE;
	}
    /**
     * Gets CellIdentityList report.
     */
    const ie::CellIdentityList* GetCellIdentityList() const
    {
        return static_cast<const ie::CellIdentityList*>(
            FindIE(ie::InfoElement::CELL_IDENTITY_LIST));
    }

    /**
     * Clone TA layer 3 Message
     */
    Message *Clone() const
    {
        return new TALayer3(*this);
    }

    /**
     *
     */
    void GetMandatoryParams(ie::InfoElement::Type* mandatory,
                            int& size) const
    {
        mandatory[0] = margs[0];
        size = 1;
    }

protected:
    
    /**
     *
     */
    TALayer3(ITS_OCTET *buffer, int& len);
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
            /* unrecognised IEs are ignored */
            //ITN_THROW(IllegalArgumentException, "Illegal IE in message");
            break;
        }
	}

private:

    static ie::InfoElement::Type margs[]; // = { CAUSE };
    static ie::InfoElement::Type oargs[]; // = MArgs;
    static Checker checker;
};

} // end of basslap namespace

#endif // !BSSLAP_TALAYER3_H

