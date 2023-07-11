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
//   ID: $Id: connectionorientedinformation.cpp,v 1.1.2.1 2009/12/22 10:41:43 rajeshak Exp $
//
//  LOG: $Log: connectionorientedinformation.cpp,v $
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bssaple/connectionorientedinformation.h>

namespace bssaple
{

ie::InfoElement::Type ConnectionOrientedInformation::mandatory[] =
{
    ie::InfoElement::APDU
};

ie::InfoElement::Type ConnectionOrientedInformation::optional[] =
{
    ie::InfoElement::SEGMENTATION
};

ConnectionOrientedInformation::Checker
    ConnectionOrientedInformation::checker(mandatory,optional);


ConnectionOrientedInformation::
ConnectionOrientedInformation(const ITS_OCTET *buf, int len)
: Message(CONNECTION_ORIENTED_INFORMATION)
{
    try
    {
        this->DecodeIE(buf,len);
        CheckForMandatoryParams();
    }
    catch(DecodeException &ex)
    {
        CODEC_TRACE_ERROR((_ITN_X_PARAMS(ex)));
        throw;
    }
}

void ConnectionOrientedInformation::CheckForMandatoryParams () const
{
    switch(ConnectionOrientedInformation::checker.CheckParameters(ies))
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


