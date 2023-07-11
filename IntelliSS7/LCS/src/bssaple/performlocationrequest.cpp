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
//   ID: $Id: performlocationrequest.cpp,v 1.1.2.4 2010/05/17 13:19:54 rajeshak Exp $
//
//  LOG: $Log: performlocationrequest.cpp,v $
//  LOG: Revision 1.1.2.4  2010/05/17 13:19:54  rajeshak
//  LOG: Fix for IssueID-2793
//  LOG:
//  LOG: Revision 1.1.2.3  2010/04/21 06:30:57  rajeshak
//  LOG: Code Review comments
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

#include <bssaple/performlocationrequest.h>

namespace bssaple
{

ie::InfoElement::Type PerformLocationRequest::mandatory[] =
{
    ie::InfoElement::LOCATION_TYPE,
    ie::InfoElement::CELL_IDENTIFIER
};

ie::InfoElement::Type PerformLocationRequest::optional[] =
{
    ie::InfoElement::CLASSMARK_INFORMATION_TYPE3,
    ie::InfoElement::LCS_CLIENT_TYPE,
    ie::InfoElement::CHOSEN_CHANNEL,
    ie::InfoElement::LCS_PRIORITY,
    ie::InfoElement::LCS_QOS,
    ie::InfoElement::GPS_ASSISTANCE_DATA,
    ie::InfoElement::APDU,
    ie::InfoElement::LCS_CAPABILITY,
    ie::InfoElement::PACKET_MEASUREMENT_REPORT,
    ie::InfoElement::CELL_IDENTITY_LIST,
    ie::InfoElement::IMSI,
    ie::InfoElement::IMEI,
    //ie::InfoElement::GANSS_POSITIONING_DATA,
    ie::InfoElement::REQ_GANSS_ASSIST_DATA,
    ie::InfoElement::GANSS_LOCATION_TYPE,
};

PerformLocationRequest::Checker
    PerformLocationRequest::checker(mandatory,optional);  

PerformLocationRequest::PerformLocationRequest(const ITS_OCTET *buf, int len)
: Message(Message::PERFORM_LOCATION_REQUEST)
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

void PerformLocationRequest::CheckForMandatoryParams() const
{
    switch(PerformLocationRequest::checker.CheckParameters(ies))
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


