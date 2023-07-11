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
//   ID: $Id: reset.cpp,v 1.1.2.4 2010/08/12 08:17:10 rajeshak Exp $
//
//  LOG: $Log: reset.cpp,v $
//  LOG: Revision 1.1.2.4  2010/08/12 08:17:10  rajeshak
//  LOG: Fix Issue:3351
//  LOG:
//  LOG: Revision 1.1.2.3  2010/03/26 11:42:38  rajeshak
//  LOG: Renaming IE code for SERVING_CELL_IDENTITY to CELL_IDENTITY
//  LOG:
//  LOG: Revision 1.1.2.2  2010/03/23 05:44:52  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#pragma warning(disable: 4786)

#include <bsslap/reset.h>

namespace bsslap
{
ie::InfoElement::Type Reset::margs[] = { ie::InfoElement::CELL_IDENTITY,
                                         ie::InfoElement::TIMING_ADVANCE,
                                         ie::InfoElement::CHANNEL_DESCRIPTION,
                                         ie::InfoElement::CAUSE
                                        };

ie::InfoElement::Type Reset::oargs[] = { ie::InfoElement::MEASUREMENT_REPORT,
                                         ie::InfoElement::LOCATION_AREA_CODE, 
                                         ie::InfoElement::CELL_IDENTITY_LIST, 
                                         ie::InfoElement::FREQUENCY_LIST_REL8,
                                         ie::InfoElement::CHANNEL_MODE,
                                         ie::InfoElement::MULTIRATE_CONFIG,
                                         ie::InfoElement::PACKET_CHANNEL_DESC,
                                         ie::InfoElement::TLLI,
                                         ie::InfoElement::TFI,
                                         ie::InfoElement::TFB_STARTING_TIME,
                                         ie::InfoElement::ENCRYPTION_KEY,
                                         ie::InfoElement::CIPHER_MODE_SETTING,
                                         ie::InfoElement::ENHANCED_MEASUREMENT_REPORT
                                       };

Reset::Checker Reset::checker(margs, oargs);


Reset::Reset(ITS_OCTET *buf, int& len)
: Message(RESET)
{
    Message::DecodeIEs(buf, len);
    //std::cout<<*this<<std::endl;
    CheckForMandatoryParam();
}

} // end of namespace

