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
//   ID: $Id: networkelementidentity.cpp,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG: $Log: networkelementidentity.cpp,v $
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#include <bssaple/ie/networkelementidentity.h>


namespace bssaple
{

namespace ie
{

const int SIZE_OF_NETWORK_GLOBAL_IDENTIFICATION = sizeof(ITS_OCTET) * 8;
const int SIZE_OF_NETWORK_LAC_AND_CI = sizeof(ITS_OCTET) * 5;
const int SIZE_OF_NETWORK_CI = sizeof(ITS_OCTET) * 3;
const int SIZE_OF_NETWORK_NO_CELL = 0;


NetworkElementIdentity::NetworkElementIdentity(const ITS_OCTET* fullbuf,int len)
:InfoElement((InfoElement::Type)fullbuf[0],len)
{
    const ITS_OCTET *buf = &fullbuf[2];
    discriminator = (Discriminator)buf[0];

    if(discriminator == GLOBAL_IDENTIFICATION)
    {
        if (len != SIZE_OF_NETWORK_GLOBAL_IDENTIFICATION)
        {
            ITN_THROW(DecodeException,
                "Network identifier size exeeded for its Discriminator");
        }

        memcpy(mcc,&buf[1],sizeof(ITS_OCTET)*2);

        mnc = buf[3];

        memcpy(lac,&buf[4],sizeof(ITS_OCTET)*2);

        memcpy(ci,&buf[6],sizeof(ITS_OCTET)*2);

    }
    else
    {
        ITN_THROW(DecodeException,"Invalid Network Identifier");
    }

}


int NetworkElementIdentity::Encode (ITS_OCTET* buf, int& len) const
{
    if(discriminator == GLOBAL_IDENTIFICATION)
    {
        buf[0] = InfoElement::DEST_NETWORK_ELEMENT_ID;
        buf[1] = SIZE_OF_NETWORK_GLOBAL_IDENTIFICATION;
        buf[2] = (ITS_OCTET)discriminator;
        memcpy(&buf[3],mcc,sizeof(ITS_OCTET)*2);
        buf[5] = mnc;
        memcpy(&buf[6],lac,sizeof(ITS_OCTET)*2);
        memcpy(&buf[8],ci,sizeof(ITS_OCTET)*2);

        len = SIZE_OF_NETWORK_GLOBAL_IDENTIFICATION + sizeof(ITS_OCTET)*2;
    }
    else
    {
        ITN_THROW(EncodeException,"Invalid Network Identifier");
    }
    return CODEC_SUCCESS;   

}

void NetworkElementIdentity::PrintIE(std::ostream &out) const
{
    ITS_OCTET dig1,dig2,dig3,dig4,dig5;
    GetMCC(dig1,dig2,dig3);
    GetMNC(dig4,dig5);

    out<<"     IE NetworkIdentifier "<<std::endl;
    out<<"     [ "<<std::endl;
    out<<"\t\tNetworkDisc  0x"<<std::hex<<(int)(GetDiscriminator())<<std::endl;
    if(GetDiscriminator()== GLOBAL_IDENTIFICATION)
    {
        out<<"\t\tMCC_DIG1  0x"<<std::hex<<(int)(dig1)<<std::endl;
        out<<"\t\tMCC_DIG2  0x"<<std::hex<<(int)(dig2)<<std::endl;
        out<<"\t\tMCC_DIG3  0x"<<std::hex<<(int)(dig3)<<std::endl;
        out<<"\t\tMNC_DIG1  0x"<<std::hex<<(int)(dig4)<<std::endl;
        out<<"\t\tMNC_DIG2  0x"<<std::hex<<(int)(dig5)<<std::endl;
    }
    out<<"\t\tLAC  0x"<<std::hex<<(int)(GetLAC ())<<std::endl;
    out<<"\t\tCI  0x"<<std::hex<<(int)(GetCI ())<<std::endl;
    out<<"     ]"<<std::endl<<std::endl;
}


} // namespace ie
} // namespace bssaple


