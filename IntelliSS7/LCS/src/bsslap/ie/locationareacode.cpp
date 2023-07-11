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
//   ID: $Id: locationareacode.cpp,v 1.1.2.1 2009/12/22 10:41:43 rajeshak Exp $
//
//  LOG: $Log: locationareacode.cpp,v $
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bsslap/ie/locationareacode.h>


namespace bsslap
{
namespace ie
{

const int SIZE_OF_LAC = sizeof(ITS_OCTET) * 3;


LocationAreaCode::LocationAreaCode(const ITS_OCTET *buf, int& len)
: InfoElement(InfoElement::LOCATION_AREA_CODE)
{
    int ielen = 0;
	if (len >= 2 * sizeof(ITS_OCTET))
	{
        memcpy(lac,&buf[0],sizeof(ITS_OCTET)*2);
        ielen += 2;
    }
	else
    {
        ITN_THROW(IllegalArgumentException, "Invalid IE length");
    }
	len = ielen;

}

void LocationAreaCode::Encode (ITS_OCTET* buf, int& len) const
{
	len = SIZE_OF_LAC;
	buf[0] = param_id;
    memcpy(&buf[1],lac,sizeof(ITS_OCTET)*2);
}

void LocationAreaCode::Print(std::ostream &out) const
{
    out<<"         IE Location Area Code "<<std::endl;
    out<<"         ( "<<std::endl;
    out<<"\t\t\tLAC  0x"<<std::hex<<(int)GetLAC()<<std::endl;
    out<<"         )"<<std::endl<<std::endl;
}    


} // namespace ie    
} // namespace bsslap    

