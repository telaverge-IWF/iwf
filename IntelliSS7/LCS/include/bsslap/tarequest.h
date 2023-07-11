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
//  ID: $Id: tarequest.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//  LOG:$Log: tarequest.h,v $
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_TAREQUEST_H
#define BSSLAP_TAREQUEST_H

#include <bsslap/message.h>
#include <codec_param_checker.h>
#include <codec_trace.h>

namespace bsslap
{

class TARequest: public Message
{
    friend class Message;

    typedef ParameterChecker<InfoElementMap, 
                            ie::InfoElement, 0, 0> Checker;

public:
    /**
     * Constructor
     */
    TARequest()
    : Message(TA_REQUEST)
    {}

    virtual Message *Clone() const
    {
        return new TARequest(*this);
    }

    /**
     *
     */
    void GetMandatoryParams(ie::InfoElement::Type* mandatory,
                            int& size) const
    {
        mandatory = 0;
        size = 0;
    }

protected:
    /*
     * Decode constructor
     */
    TARequest(const ITS_OCTET *buffer, int& len);

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

    static Checker checker;
    static ie::InfoElement::Type margs[];
};

} // end of basslap namespace

#endif // !BSSLAP_TAREQUEST_H

