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
//   ID: $Id: facility.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG: $Log: facility.cpp,v $
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#include <bssaple/ie/facility.h>

namespace bssaple
{

namespace ie
{

Facility::Facility(const ITS_OCTET *buf,int len)
:InfoElement(FACILITY,len)
{
    if(len > MAX_LAYER3_LEN)
    {
        ITN_THROW(DecodeException,"Facility length exeeded");
    }

    memcpy(component,buf,len);
}

int Facility::Encode (ITS_OCTET* buf, int& len) const
{
    if(!optionalFlag)
    {
        len = length + sizeof(ITS_OCTET);
        buf[0] = length;
        memcpy(&buf[1],component,length);
    }
    else
    {
        len = length + sizeof(ITS_OCTET)*2;
        buf[0] = id;
        buf[1] = length;
        memcpy(&buf[2],component,length);
    }
    return CODEC_SUCCESS;
}

void Facility::PrintIE(std::ostream &out) const
{

}


}

}

