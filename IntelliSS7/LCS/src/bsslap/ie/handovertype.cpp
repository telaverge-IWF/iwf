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
//   ID: $Id: handovertype.cpp,v 1.1.2.1 2009/12/22 10:41:43 rajeshak Exp $
//
//  LOG: $Log: handovertype.cpp,v $
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bsslap/ie/handovertype.h>

namespace bsslap {
namespace ie {

HandoverType::HandoverType(const ITS_OCTET* buf, int& len)
:	InfoElement(HANDOVER_TYPE)
{
    int ielen = 0;
	if (len >= 1 * sizeof(ITS_OCTET))
	{
        handoverType = (HandoverType::Type)buf[0];
        ++ielen;
    }
	else
	{
		ITN_THROW(IllegalArgumentException, "Invalid IE length");
    }
    len = ielen;
}

/**
 * Encode HandoverType Value
 */
void 
HandoverType::Encode(ITS_OCTET* buf, int& len) const
{
	len = 2 * sizeof(ITS_OCTET);

	buf[0] = param_id;
	buf[1] = handoverType;
}

void HandoverType::Print(std::ostream& out) const
{
    out << "\tHandover Type ( 0x" <<
        std::hex << (int)handoverType << " )\n";
}


} // end of namespace ie
} // end of namespace bsslap

