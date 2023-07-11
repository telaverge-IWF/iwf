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
//  ID: $Id: mspositioncommand.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//  LOG:$Log: mspositioncommand.h,v $
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_MSPOSITIONCOMMAND_H
#define BSSLAP_MSPOSITIONCOMMAND_H

#include <bsslap/message.h>
#include <bsslap/ie/rrlpflag.h>
#include <bsslap/ie/rrlpie.h>
#include <codec_param_checker.h>

namespace bsslap {

/**
 * BSSLAP MS Position Command is a message from the SMLC
 * to BSS that contains the following ie
 * - RRLP flag  [Mandatory]
 * - RRLP Info  [Mandatory]
 */

class Message;

class MSPositionCommand : public Message
{
    friend class Message;
    typedef ParameterChecker<InfoElementMap,
                                ie::InfoElement, 2, 0> Checker;
public:
    
	/**
	 * Constructor
	 */
    MSPositionCommand()
		:Message(MS_POSITION_COMMAND)
	{
	}

    /**
	 * Get Flag  
	 */
    const ie:RRLPFlag* GetFlag() const
    {
        return static_cast<const ie::RRLPFlag*>(
                    FindIE(ie::InfoElement::RRLP_FLAG));
    }

    /**
	 * Get RRLP Info
	 */
    const ie::RRLPIe* GetRRLPIe() const
    {
        return static_cast<const ie::RRLPIe*>(
                    FindIE(ie::InfoElement::RRLP_IE));
    }

    virtual Message *Clone() const
    {
        return new MSPositionCommand(*this);
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

    MSPositionCommand(ITS_OCTET *buffer, int& len);

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
            ITN_THROW(IllegalArgumentException, "Illegal IE in message");
        }
    }

private:

    static ie::InfoElement::Type margs[];
    static Checker checker;
};

} // end of basslap namespace

#endif // !BSSLAP_MSPOSITIONCOMMAND_H

