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
//   ID: $Id: tbfstartingtime.cpp,v 1.1.2.1 2010/03/23 05:50:21 rajeshak Exp $
//
//  LOG: $Log: tbfstartingtime.cpp,v $
//  LOG: Revision 1.1.2.1  2010/03/23 05:50:21  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: tbfstartingtime.cpp,v 1.1.2.1 2010/03/23 05:50:21 rajeshak Exp $"

#include <bsslap/ie/tbfstartingtime.h>

namespace bsslap {
namespace ie {

TbfStartingTime::TbfStartingTime(const ITS_OCTET* buf, int& len)
:InfoElement(TFB_STARTING_TIME)
{
    int ielen = 0;
    if (len >= 2 * sizeof(ITS_OCTET))
    {
        t1 = buf[0] >> 3;
        t2 = buf[1] & 0x1FU;
        t3 = ((buf[0] & 0x07U) << 3) | (buf[1] >> 5);
        ielen += 2;
    }
    else
    {
        ITN_THROW(IllegalArgumentException, "Invalid IE length");
    }
    len = ielen;
}

/**
 * Encode StartingTime Value
 */
void 
TbfStartingTime::Encode(ITS_OCTET* buf, int& len) const
{
    len = 3 * sizeof(ITS_OCTET); 
            
    buf[0] = param_id;
    buf[1] = (t1 << 3) | (t3 >> 3);
    buf[2] = (t3 << 5) | t2;
}

void 
TbfStartingTime::Print(std::ostream& out) const
{
    out << "\tTbfStartingTime = {\n";
    out << "\t\tT1 ( 0x" << std::hex << (int)t1 << " )\n";
    out << "\t\tT2 ( 0x" << std::hex << (int)t2 << " )\n";
    out << "\t\tT3 ( 0x" << std::hex << (int)t3 << " )\n";
    out << "\t}\n";
}

} // end of namespace ie
} // end of namespace bsslap

