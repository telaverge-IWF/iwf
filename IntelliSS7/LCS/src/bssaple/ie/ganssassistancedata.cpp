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
//   ID: $Id: ganssassistancedata.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG: $Log: ganssassistancedata.cpp,v $
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2010/03/23 05:42:45  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: ganssassistancedata.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $"

#include <bssaple/ie/ganssassistancedata.h>

namespace bssaple
{

namespace ie
{

GANSSAssistanceData::GANSSAssistanceData(const ITS_OCTET* buf, int len)
: InfoElement(InfoElement::REQ_GANSS_ASSIST_DATA,len)
{
}

int GANSSAssistanceData::Encode (ITS_OCTET* buf, int& len) const
{
    ITN_THROW(InvalidData, "This is not Unsupported in this version");    
    return CODEC_SUCCESS;
}

void GANSSAssistanceData::PrintIE(std::ostream &out) const
{
    out<<"      IE GANSSAssistanceData "<<std::endl;  
    out<<"      ["<<std::endl;
    out<<"      ]"<<std::endl<<std::endl;
}

} // namespace ie
} // namespace bssaple


