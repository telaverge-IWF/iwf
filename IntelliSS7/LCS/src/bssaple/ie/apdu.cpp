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
//   ID: $Id: apdu.cpp,v 1.1.2.3 2010/09/03 10:21:12 rajeshak Exp $
//
//  LOG: $Log: apdu.cpp,v $
//  LOG: Revision 1.1.2.3  2010/09/03 10:21:12  rajeshak
//  LOG: Issue 3400 Codec changes
//  LOG:
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#include <bssaple/ie/apdu.h>
#include <bsslap/message.h>
#include <iostream>



namespace bssaple
{

namespace ie
{

APDU::APDU(const ITS_OCTET* buf,int len):InfoElement(InfoElement::APDU,len)
{
    if(len > MAX_APDU_LEN)
    {
        ITN_THROW(DecodeException,"APDU length exeeded");
    }

    protocolID = buf[0];
    memcpy(data,&buf[1],len-sizeof(ITS_OCTET));
}

int APDU::Encode (ITS_OCTET* buf, int& len) const
{
    if(length > MAX_APDU_LEN)
    {
        ITN_THROW(EncodeException,"APDU length exeeded");
    }
    len = length+sizeof(ITS_OCTET)*3; 
    
    buf[0] = id;
    buf[1] = length >> 8 & 0xFFU;
    buf[2] = length & 0xFFU;    
    buf[3] = protocolID;
    memcpy(&buf[4],data,length-1);

    return CODEC_SUCCESS;
}

void APDU::PrintIE(std::ostream &out) const
{
    char buf[20];
    
    sprintf(buf,"PROTOCOL_ID      %02X",protocolID);

    out<<"     IE APDU"<<std::endl;
    out<<"     [ "<<std::endl;
    out<<"\tProtocolID   0x"<<std::hex<<(int)protocolID<<std::endl<<std::endl;
    //int len = length-sizeof(ITS_OCTET);
    //const bsslap::Message *ptr = bsslap::Message::Decode(data,len);
    //out<<"\t"<<*ptr<<std::endl;
    out<<"     ]"<<std::endl<<std::endl;
}



} // namespace ie
} // namespace bssaple

