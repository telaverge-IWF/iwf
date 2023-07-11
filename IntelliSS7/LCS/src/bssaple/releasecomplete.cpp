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
//   ID: $Id: releasecomplete.cpp,v 1.1.2.1 2009/12/22 10:41:43 rajeshak Exp $
//
//  LOG: $Log: releasecomplete.cpp,v $
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bssaple/releasecomplete.h>

namespace bssaple
{

ie::InfoElement::Type ReleaseComplete::optional[]=
{
    ie::InfoElement::RELEASE_COMPLETE_CAUSE,
    ie::InfoElement::FACILITY
};


ReleaseComplete::Checker ReleaseComplete::checker(0,optional);

ReleaseComplete::ReleaseComplete(const ITS_OCTET* buf,int len)
:DTAPMessage(DTAPMessage::RELEASE_COMPLETE)
{
    try
    {
        channelId = (ControlChannelId)(buf[0] >> 6);
        sapi = (SAPI)(buf[0] & 0x07U);
        tId_protDisc = buf[1];

        //buf[2] is Message ID;

        this->DecodeIE(&buf[3],len -3);
        CheckForMandatoryParams();
    }
    catch(Exception &ex)
    {
        CODEC_TRACE_ERROR((_ITN_X_PARAMS(ex)));
        throw;
    }
}


void ReleaseComplete::CheckForMandatoryParams () const
{
    switch(ReleaseComplete::checker.CheckParameters(ies))
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

}


