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
//  ID: $Id: abort.h,v 1.1.2.2 2010/09/03 10:21:12 rajeshak Exp $
//
//  LOG:$Log: abort.h,v $
//  LOG:Revision 1.1.2.2  2010/09/03 10:21:12  rajeshak
//  LOG:Issue 3400 Codec changes
//  LOG:
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_ABORT_H
#define BSSLAP_ABORT_H

#include <bsslap/message.h>
#include <bsslap/ie/cause.h>
#include <codec_param_checker.h>
#include <codec_trace.h>		

namespace bsslap {

/**
 * The Abort message may either from BSS to SMLC or SMLC to BSS. Upon receiving
 * this signal, either SMLC or BSS shall abort ongoing positioning procedure
 */
class Message;

class Abort : public Message
{
    typedef ParameterChecker<InfoElementMap, ie::InfoElement, 1, 0> Checker;
    friend class Message;

public:
    
	/**
	 * Constructor
	 */
    Abort()
	: Message(ABORT)
	{
	}

    /**
	 *
	 */
    const ie::Cause *GetCause() const
	{
        return static_cast<const ie::Cause *>
            (FindIE(ie::InfoElement::CAUSE));
	}

    virtual Message *Clone() const
    {
        return new Abort(*this);
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
     * Constructor
     * @param: buffer
     * @param: len
     */   
    Abort(ITS_OCTET *buffer, int& len);

    /**
	 * This function is to check for mandatory IEs inside message
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
    static Checker checker;
};

} // end of basslap namespace

#endif // !BSSLAP_ABORT_H

