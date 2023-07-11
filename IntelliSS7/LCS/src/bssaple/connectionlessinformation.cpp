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
//   ID: $Id: connectionlessinformation.cpp,v 1.1.2.1 2009/12/22 10:41:43 rajeshak Exp $
//
//  LOG: $Log: connectionlessinformation.cpp,v $
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#include <bssaple/connectionlessinformation.h>


namespace bssaple
{

ie::InfoElement::Type ConnectionlessInformation::mandatory[]=
{
    ie::InfoElement::SRC_NETWORK_ELEMENT_ID,
    ie::InfoElement::DEST_NETWORK_ELEMENT_ID
};

ie::InfoElement::Type ConnectionlessInformation::optional[] =
{
    ie::InfoElement::APDU,
    ie::InfoElement::SEGMENTATION,
    ie::InfoElement::RETURN_ERROR_REQUEST,
    ie::InfoElement::RETURN_ERROR_CAUSE
};

ConnectionlessInformation::Checker
    ConnectionlessInformation::checker(mandatory,optional);


ConnectionlessInformation::ConnectionlessInformation(const ITS_OCTET* buf,
                                                           int len)
:Message(Message::CONNECTIONLESS_INFORMATION)
{
    try
    {
        (const_cast<ITS_OCTET*>(buf))[0] = 
                        bssaple::ie::InfoElement::SRC_NETWORK_ELEMENT_ID;
        this->DecodeIE(buf,len);
        CheckForMandatoryParams();
    }
    catch(Exception &ex)
    {
        CODEC_TRACE_ERROR((_ITN_X_PARAMS(ex)));
        throw;
    }
}

void ConnectionlessInformation::CheckForMandatoryParams () const
{
    switch(ConnectionlessInformation::checker.CheckParameters(ies))
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

