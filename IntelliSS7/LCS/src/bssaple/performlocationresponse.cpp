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
//   ID: $Id: performlocationresponse.cpp,v 1.1.2.3 2010/03/23 08:09:43 rajeshak Exp $
//
//  LOG: $Log: performlocationresponse.cpp,v $
//  LOG: Revision 1.1.2.3  2010/03/23 08:09:43  rajeshak
//  LOG: Increasing the optional array size to 6
//  LOG:
//  LOG: Revision 1.1.2.2  2010/03/23 05:42:45  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bssaple/performlocationresponse.h>

namespace bssaple
{

ie::InfoElement::Type PerformLocationResponse::optional[6] =
{
   ie::InfoElement::GEOGRAPHIC_LOCATION,
   ie::InfoElement::POSITIONING_DATA,
   ie::InfoElement::DECIPHERING_KEYS,
   ie::InfoElement::LCS_CAUSE,
   ie::InfoElement::VELOCITY_DATA,
   ie::InfoElement::GANSS_POSITIONING_DATA
};

PerformLocationResponse::Checker
    PerformLocationResponse::checker(0, optional);


PerformLocationResponse::PerformLocationResponse(const ITS_OCTET *buf, int len)
: Message(PERFORM_LOCATION_RESPONSE)
{
    try
    {
        DecodeIE(buf,len);
        CheckForMandatoryParams();
    }
    catch(DecodeException &ex)
    {
        CODEC_TRACE_ERROR((_ITN_X_PARAMS(ex)));
        throw;
    }

}

void  PerformLocationResponse::CheckForMandatoryParams () const
{
    switch(PerformLocationResponse::checker.CheckParameters(ies))
    {
    case Checker::SUCCESSFUL:
        //itn::Trace::log(itn::Trace::debug) << "Passed" << itn::Trace::end;
        break;
    case Checker::MISSING_MANDATORY:
        ITN_THROW(MissingParameterException, "Missing mandatory.");
        break;
    case Checker::ILLEGAL_PARAMETER:
        ITN_THROW(IllegalArgumentException, "Illegal parameter.");
        break;
    }
}


} // namespace bssaple


