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
//   ID: $Id: cause.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG: $Log: cause.cpp,v $
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bsslap/ie/cause.h>

namespace bsslap {
namespace ie {

Cause::Cause(const ITS_OCTET* buf, int& len)
: InfoElement(CAUSE)
{
    int ielen = 0;
    if (len >= 1* sizeof(ITS_OCTET))
	{
        causeValue = (Cause::Type)buf[0];
        ++ielen;
	}
    else
    {
        ITN_THROW(IllegalArgumentException, "Cause Value Missing");
    }
    len = ielen;
}

/**
 * Encode Cause Value
 *
 * @param:buf - The buffer that will contain the encoded data.
 * @param:len - This parameter will contain the length of encodede data.
 * @return: CODEC_SUCCESS - if the function succeeds.
 */
void 
Cause::Encode(ITS_OCTET* buf, int& len) const
{
	len = 2 * sizeof(ITS_OCTET);

	buf[0] = param_id;
	buf[1] = causeValue;
}

void Cause::Print(std::ostream& out) const
{
    out << "\tCause Value ( 0x" << std::hex << (int)causeValue << " ) - "<<BSSLAPCAUSE_VALUE_STRING((int)causeValue)<<"\n";
}

} // end of namespace ie
} // end of namespace bsslap

