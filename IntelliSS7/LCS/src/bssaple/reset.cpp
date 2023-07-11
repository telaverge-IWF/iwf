//////////////////////////////////-*-C++-*-///////////////////////////////////
//                                                                          //
//     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    //
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
//   ID: $Id: reset.cpp,v 1.1.2.1 2009/12/22 10:41:43 rajeshak Exp $
//
//  LOG: $Log: reset.cpp,v $
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bssaple/reset.h>

namespace bssaple
{

ie::InfoElement::Type Reset::mandatory[] =
{
    ie::InfoElement::CAUSE
};

Reset::Checker Reset::checker(mandatory, 0);

Reset::Reset(const ITS_OCTET *buf, int len)
: Message(RESET)
{
    try
    {
        this->DecodeIE(buf,len);
        CheckForMandatoryParams ();
    }
    catch(Exception &ex)
    {
        CODEC_TRACE_ERROR((_ITN_X_PARAMS(ex)));
        throw;
    }
}

void Reset::CheckForMandatoryParams() const
{
    switch(Reset::checker.CheckParameters(ies))
    {
    case Reset::Checker::SUCCESSFUL:
        //itn::Trace::log(itn::Trace::debug) << "Passed" << itn::Trace::end;
        break;
    case Reset::Checker::MISSING_MANDATORY:
        //itn::Trace::log(itn::Trace::debug) << "Failed" << itn::Trace::end;
        ITN_THROW(MissingParameterException, "Missing mandatory.");
        break;
    case Reset::Checker::ILLEGAL_PARAMETER:
        //itn::Trace::log(itn::Trace::debug) << "Failed" << itn::Trace::end;
        ITN_THROW(IllegalArgumentException, "Illegal parameter.");
        break;
    }

}

} // namespace bssaple


