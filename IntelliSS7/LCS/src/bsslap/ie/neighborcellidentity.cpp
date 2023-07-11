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
//   ID: $Id: neighborcellidentity.cpp,v 1.1.2.1 2009/12/22 10:41:43 rajeshak Exp $
//
//  LOG: $Log: neighborcellidentity.cpp,v $
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bsslap/ie/neighborcellidentity.h>

namespace bsslap {
namespace ie {

NeighborCellIdentity::NeighborCellIdentity(const ITS_OCTET* buf, int& len)
: InfoElement(NEIGHBOR_CELL_IDENTITY)
{
    int ielen = 1; // ie length byte
    if (len >= buf[0])
    {
        for (int i = 1 ; i <= buf[0]/2; ++i)
		{
			cellid.push_back((buf[2*i-1] << 8) | buf[2*i]);
            ielen += 2;
		}
    }
	else
    {
        ITN_THROW(IllegalArgumentException, "Invalid IE length");
    }
    len = ielen;
}

void 
NeighborCellIdentity::Encode(ITS_OCTET* buf, int& len) const
{
	len = 2 * sizeof(ITS_OCTET) + cellid.size() * 2;

	buf[0] = param_id;
	buf[1] = cellid.size() * 2; //param_length;

    CellidVector::const_iterator it;
    int offset = 2;
	for (it = cellid.begin(); it != cellid.end(); ++it)
	{
		buf[offset++] = *it >> 8;
        buf[offset++] = *it & 0xFFU;
	}
}


void NeighborCellIdentity::Print(std::ostream& out) const
{
    CellidVector::const_iterator it;
    int i;

    out << "\tNeighborCellIdentity = {\n";
    for(it = cellid.begin(), i = 0; 
        it != cellid.end(); ++it, ++i)
    {
        out << "\t\tNeighborCellId[" << i << "] ( 0x"
            << std::hex << *it << " )\n";
    }
    out << "\t}\n";
}


} // end of namespace ie
} // end of namespace bsslap

