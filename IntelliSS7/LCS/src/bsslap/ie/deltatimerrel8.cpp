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
//   ID: $Id: deltatimerrel8.cpp,v 1.1.2.1 2010/03/23 05:44:52 rajeshak Exp $
//
//  LOG: $Log: deltatimerrel8.cpp,v $
//  LOG: Revision 1.1.2.1  2010/03/23 05:44:52  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: deltatimerrel8.cpp,v 1.1.2.1 2010/03/23 05:44:52 rajeshak Exp $"

#include <bsslap/ie/deltatimerrel8.h>

namespace bsslap {
namespace ie{

DeltaTimerRel8::DeltaTimerRel8(const ITS_OCTET* buf, int& len)
:	InfoElement(DELTA_TIMER_REL8)
{
    int ielen = 0;
	if (len >= 1 * sizeof(ITS_OCTET))
	{
		timerValue = buf[0];
        ++ielen;
	}
    else
    {
        ITN_THROW(IllegalArgumentException, "Invalid IE length");
    }
    len = ielen;
}

/**
 * Encode DeltaTimer Value
 * @param: buf - Input data buffer to decode
 * @param: len - Input/Output data buffer length
 */
void 
DeltaTimerRel8::Encode(ITS_OCTET* buf, int& len) const
{
	len = 2 * sizeof(ITS_OCTET);

	buf[0] = param_id;
	buf[1] = timerValue;
}

void DeltaTimerRel8::Print(std::ostream& out) const
{
    out << "\tDelta Timer Value ( 0x" << std::hex << (int)timerValue << " )\n";
}

} // end of namespace ie
} // end of namespace bsslap

