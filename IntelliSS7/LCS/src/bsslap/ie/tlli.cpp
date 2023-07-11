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
//   ID: $Id: tlli.cpp,v 1.1.2.2 2010/08/12 08:17:10 rajeshak Exp $
//
//  LOG: $Log: tlli.cpp,v $
//  LOG: Revision 1.1.2.2  2010/08/12 08:17:10  rajeshak
//  LOG: Fix Issue:3351
//  LOG:
//  LOG: Revision 1.1.2.1  2010/03/23 05:50:21  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: tlli.cpp,v 1.1.2.2 2010/08/12 08:17:10 rajeshak Exp $"

#include <bsslap/ie/tlli.h>

namespace bsslap {
namespace ie {

Tlli::Tlli(const ITS_OCTET* buf, int& len)
:InfoElement(TLLI)
{
    int ielen =0;
    if (len >= 4 * sizeof(ITS_OCTET))
    {
        ielen = 4;
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
Tlli::Encode(ITS_OCTET* buf, int& len) const
{
}

void 
Tlli:: Print(std::ostream& out) const
{
    out << "\tTlli " ;
    out << "\t[\n" ;
    out << "\t]\n" ;
}

} // end of namespace ie
} // end of namespace bsslap

