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
//   ID: $Id: releasecompletecause.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG: $Log: releasecompletecause.cpp,v $
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#include <bssaple/ie/releasecompletecause.h>

namespace bssaple
{

namespace ie
{

ReleaseCompleteCause::ReleaseCompleteCause(const ITS_OCTET *buf,int len)
:InfoElement(RELEASE_COMPLETE_CAUSE,len)
{
    standard_location = buf[0];
    if(GetStandard() != GSM_PLMNS && (buf[0] >> 7 != 0x01))
    {
        recommendation = buf[1];
        causeValue = buf[2];
        memcpy(diagnosticData,&buf[3],len -3);
    }
    else
    {
        causeValue = buf[1];
        memcpy(diagnosticData,&buf[3],len -2);
    }
}

int ReleaseCompleteCause::Encode (ITS_OCTET* buf, int& len) const
{
    len = dataLen + sizeof(ITS_OCTET)*4;
    buf[0] = id;
    buf[1] = dataLen + sizeof(ITS_OCTET)*2;
    buf[2] = standard_location;
    buf[3] = causeValue;
    memcpy(&buf[4],diagnosticData,dataLen);
    return CODEC_SUCCESS;
}

void ReleaseCompleteCause::PrintIE(std::ostream &out) const
{

}

}

}

