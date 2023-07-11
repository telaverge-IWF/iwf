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
//   ID: $Id: pollingrepetition.cpp,v 1.1.2.1 2010/03/23 05:50:21 rajeshak Exp $
//
//  LOG: $Log: pollingrepetition.cpp,v $
//  LOG: Revision 1.1.2.1  2010/03/23 05:50:21  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: pollingrepetition.cpp,v 1.1.2.1 2010/03/23 05:50:21 rajeshak Exp $"

#include <bsslap/ie/pollingrepetition.h>

namespace bsslap {
namespace ie {

PollingRepetition::PollingRepetition(const ITS_OCTET* buf, int& len)
:InfoElement(POLLING_REPETITION)
{
    int ielen =0;
    if (len == 1 * sizeof(ITS_OCTET))
    {
        ++ielen;
    }
    else
    {
        ITN_THROW(IllegalArgumentException, "Invalid IE length");
    }
    len = ielen;
}
/**
 * Encode 
 * @param buf - Input data buffer to decode
 * @param len - Input data buffer length
 */
void 
PollingRepetition::Encode(ITS_OCTET* buf, int& len) const
{
    len = 2 * sizeof(ITS_OCTET);

    buf[0] = param_id;
    buf[1] = 0x00;
}

void 
PollingRepetition:: Print(std::ostream& out) const
{
    out << "\tPollingRepetition " ; 
}

} // end of namespace ie
} // end of namespace bsslap

