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
//   ID: $Id: decipheringkeys.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG: $Log: decipheringkeys.cpp,v $
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#include <bssaple/ie/decipheringkeys.h>


namespace bssaple
{

namespace ie
{

// Class bssaple    ::ie    ::DecipheringKeys 

DecipheringKeys::DecipheringKeys(const ITS_OCTET* buf, int len)
:InfoElement(InfoElement::DECIPHERING_KEYS,sizeof(ITS_OCTET)*15)
{
    if(len != sizeof(ITS_OCTET) *15)
    {
        ITN_THROW(DecodeException,"Invalid length for DecipheringKeys");
    }
    keyFlag = buf[0];
    memcpy(currentKey,&buf[1],sizeof(ITS_OCTET) *7);
    memcpy(nextKey,&buf[8],sizeof(ITS_OCTET) *7);
}

int DecipheringKeys::Encode (ITS_OCTET* buf, int& len) const
{
    len = sizeof(ITS_OCTET) * 17;
    buf[0] = id;
    buf[1] = length;
    buf[2] = keyFlag;
    memcpy(&buf[3],currentKey,sizeof(ITS_OCTET) *7);
    memcpy(&buf[10],nextKey,sizeof(ITS_OCTET) *7);

    return CODEC_SUCCESS;
}

void DecipheringKeys::PrintIE(std::ostream &out) const
{
    out<<"      IE DecipheringKeys"<<std::endl;
    out<<"      ["<<std::endl;
    out<<"\t\tKeyFlag     0x"<<std::hex<<(int)keyFlag<<std::endl;
    out<<"\t\tCurrentKey  0x"<<std::hex<<(int)currentKey[0]
                             <<std::hex<<(int)currentKey[1]
                             <<std::hex<<(int)currentKey[2]
                             <<std::hex<<(int)currentKey[3]
                             <<std::hex<<(int)currentKey[4]
                             <<std::hex<<(int)currentKey[5]
                             <<std::hex<<(int)currentKey[6]<<std::endl;

    out<<"\t\tNextKey     0x"<<std::hex<<(int)nextKey[0]
                             <<std::hex<<(int)nextKey[1]
                             <<std::hex<<(int)nextKey[2]
                             <<std::hex<<(int)nextKey[3]
                             <<std::hex<<(int)nextKey[4]
                             <<std::hex<<(int)nextKey[5]
                             <<std::hex<<(int)nextKey[6]<<std::endl;
    
    out<<"      ]"<<std::endl<<std::endl;

}


} // namespace ie    
} // namespace bssaple    


