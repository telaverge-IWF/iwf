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
//  ID: $Id: reset.h,v 1.1.2.4 2010/09/03 10:21:12 rajeshak Exp $
//
//  LOG:$Log: reset.h,v $
//  LOG:Revision 1.1.2.4  2010/09/03 10:21:12  rajeshak
//  LOG:Issue 3400 Codec changes
//  LOG:
//  LOG:Revision 1.1.2.3  2010/03/26 11:47:11  rajeshak
//  LOG:Renaming IE code for SERVING_CELL_IDENTITY to CELL_IDENTITY
//  LOG:
//  LOG:Revision 1.1.2.2  2010/03/23 05:38:30  rajeshak
//  LOG:Release-8 Codec changes.
//  LOG:
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_RESET_H
#define BSSLAP_RESET_H

#include <bsslap/message.h>
#include <bsslap/ie/cellidentity.h>
#include <bsslap/ie/timingadvance.h>
#include <bsslap/ie/measurementreport.h>
#include <bsslap/ie/cause.h>
#include <bsslap/ie/channeldescription.h>
#include <bsslap/ie/locationareacode.h>
#include <bsslap/ie/cellidentitylist.h>
#include <codec_param_checker.h>
#include <codec_trace.h>

namespace bsslap {

class Message;

/**
 * The Reset message may either from BSS to SMLC or SMLC to BSS. Upon receiving
 * this signal, either SMLC or BSS shall abort ongoing positioning procedure
 */
class Reset : public Message
{
    typedef ParameterChecker<InfoElementMap, 
                            ie::InfoElement, 4, 13> Checker;
    friend class Message;

public:
    
	/**
	 * Constructor
	 */
    Reset()
		:Message(RESET)
	{		
	}
    
    /**
	 *
	 */
    const ie::Cause* GetCause() const
	{
        return static_cast<const ie::Cause*>(
            FindIE(ie::InfoElement::CAUSE));
	}

    /**
	 *
	 */
    const ie::CellIdentity* GetCellId() const
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

    const ie::ChannelDescription* GetChannelDescription() const
	{
        return static_cast<const ie::ChannelDescription*>(
            FindIE(ie::InfoElement::CHANNEL_DESCRIPTION));
	}

    /**
	 *
	 */
    const ie::MeasurementReport* GetMeasurementReport() const
	{
		return static_cast<const ie::MeasurementReport*>(
            FindIE(ie::InfoElement::MEASUREMENT_REPORT));
	}

    const ie::LocationAreaCode* GetLocationAreaCode() const
	{
		return static_cast<const ie::LocationAreaCode*>(
            FindIE(ie::InfoElement::LOCATION_AREA_CODE));
	}
    const ie::CellIdentityList* GetCellIdentityList() const
	{
		return static_cast<const ie::CellIdentityList*>(
            FindIE(ie::InfoElement::CELL_IDENTITY_LIST));
	}

    /**
	 *
	 */
	ITS_BOOLEAN MeasurementReportPresent()
	{
		return ITS_TRUE;
	}

    virtual Message *Clone() const
    {
        return new Reset(*this);
    }

    /**
     *
     */
    void GetMandatoryParams(ie::InfoElement::Type* mandatory,
                            int& size) const
    {
        //mandatory = margs;
        memcpy(mandatory, margs, sizeof(ie::InfoElement::Type) * 4);
        size = 4;
    }

protected:

    /**
     * Constructor 
     * @param buffer
     * @param len
     */
    Reset(ITS_OCTET *buffer, int& len);

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
            /* unrecognised IEs are ignored */
            //ITN_THROW(IllegalArgumentException, "Illegal IE in message");
            break;
        }
	}

private:

    static ie::InfoElement::Type margs[]; 
    static ie::InfoElement::Type oargs[]; 
    static Checker checker;
    
};

} // end of basslap namespace

#endif // !BSSLAP_RESET_H

