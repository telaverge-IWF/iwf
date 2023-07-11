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
//   ID: $Id: neighborstarttime.cpp,v 1.1.2.1 2009/12/22 10:41:43 rajeshak Exp $
//
//  LOG: $Log: neighborstarttime.cpp,v $
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bsslap/ie/neighborstarttime.h>

namespace bsslap {
namespace ie {

NeighborStartTime::NeighborStartTime(const ITS_OCTET* buf, int& len)
:	InfoElement(NEIGHBOR_STARTING_TIME)
{
    int ielen = 1; // ie length byte
    if (len >= buf[0])
    {
        for (int i = 1 ; i <= buf[0]/2; ++i)
		{
            t1.push_back(buf[2*i-1] >> 3);
			t2.push_back( buf[2*i] & 0x1FU);
			t3.push_back( ((buf[2*i-1] & 0x07U) << 3) | (buf[2*i] >> 5) );
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
NeighborStartTime::Encode(ITS_OCTET *buf, int& len) const
{
    len = 2 * sizeof(ITS_OCTET) + 2 * t1.size();

    buf[0] = param_id;
	buf[1] = 2 * t1.size();
	int j = 2; 

    for ( int k = 0; k < t1.size() ; ++k)
    {
        buf[j++] = (t1[k] << 3) | (t3[k] >> 3);
        buf[j++] = (t3[k] << 5) | t2[k];
    }
}


void NeighborStartTime::Print(std::ostream& out) const
{
    TimeVector::const_iterator it1, it2, it3;
    int i,j,k;

    out << "\tNeighborStartTime = {\n";
    for (it1 = t1.begin(),i=0; it1 != t1.end(); ++it1, ++i)
    {
        out << "\t\tT1[" <<i<< "] ( 0x" << std::hex << (int)*it1 <<" )\n";
    }
    for (it2 = t2.begin(),j=0; it2 != t2.end(); ++it2,++j)
    {
        out << "\t\tT2["<<j<<"] ( 0x" << std::hex << (int)(*it2) <<" )\n";
    }
    for (it3 = t3.begin(),k=0; it3 != t3.end(); ++it3,++k)
    {
        out << "\t\tT3["<<k<<"] ( 0x" << std::hex << (int)*it3 <<" )\n";
    }
    out << "\t}\n";
}


} // end of namespace ie
} // end of namespace bsslap

