//////////////////////////////////-*-C++-*-///////////////////////////////////
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
//   ID: $Id: performlocationinformation.cpp,v 1.1.2.1 2010/03/23 05:41:53 rajeshak Exp $
//
//  LOG: $Log: performlocationinformation.cpp,v $
//  LOG: Revision 1.1.2.1  2010/03/23 05:41:53  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: performlocationinformation.cpp,v 1.1.2.1 2010/03/23 05:41:53 rajeshak Exp $"

#include <bssaple/performlocationinformation.h>

namespace bssaple
{

ie::InfoElement::Type PerformLocationInformation::mandatory[] =
{
    ie::InfoElement::CELL_IDENTIFIER
};

ie::InfoElement::Type PerformLocationInformation::optional[] =
{
    ie::InfoElement::APDU
};

PerformLocationInformation::Checker
    PerformLocationInformation::checker(mandatory,optional);  

PerformLocationInformation::PerformLocationInformation(const ITS_OCTET *buf, int len)
: Message(Message::PERFORM_LOCATION_INFORMATION)
{
    try
    {
        this->DecodeIE(buf,len);
        CheckForMandatoryParams();
    }
    catch(Exception &ex)
    {
        CODEC_TRACE_ERROR((_ITN_X_PARAMS(ex)));
        throw;
    }
}

void PerformLocationInformation::CheckForMandatoryParams() const
{
    switch(PerformLocationInformation::checker.CheckParameters(ies))
    {
    case Checker::SUCCESSFUL:
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


