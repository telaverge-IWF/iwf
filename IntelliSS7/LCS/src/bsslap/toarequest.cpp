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
//   ID: $Id: toarequest.cpp,v 1.1.2.2 2010/03/26 11:42:38 rajeshak Exp $
//
//  LOG: $Log: toarequest.cpp,v $
//  LOG: Revision 1.1.2.2  2010/03/26 11:42:38  rajeshak
//  LOG: Renaming IE code for SERVING_CELL_IDENTITY to CELL_IDENTITY
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#pragma warning(disable: 4786)

#include <bsslap/toarequest.h>

namespace bsslap
{

ie::InfoElement::Type TOARequest::margs[] =
{
    ie::InfoElement::DELTA_TIMER,
    ie::InfoElement::HANDOVER_TYPE,
    ie::InfoElement::CELL_IDENTITY,
    ie::InfoElement::STARTING_TIME,
};

ie::InfoElement::Type TOARequest::oargs[] =
{
    ie::InfoElement::NEIGHBOR_CELL_IDENTITY,
    ie::InfoElement::NEIGHBOR_STARTING_TIME
};

TOARequest::Checker TOARequest::checker(margs, oargs);

TOARequest::TOARequest(ITS_OCTET *buf, int& len)
:   Message(TOA_REQUEST)
{
    Message::DecodeIEs(buf, len);
    CheckForMandatoryParam();
}

} // end of namespace

