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
//   ID: $Id: cellidentifier.cpp,v 1.1.2.7 2010/06/04 03:41:37 rajeshak Exp $
//
//  LOG: $Log: cellidentifier.cpp,v $
//  LOG: Revision 1.1.2.7  2010/06/04 03:41:37  rajeshak
//  LOG: Same response for all unsupported CellDiscriminators
//  LOG:
//  LOG: Revision 1.1.2.6  2010/05/26 13:01:15  rajeshak
//  LOG: Fix for Issue ID:2917
//  LOG:
//  LOG: Revision 1.1.2.5  2010/05/10 13:05:02  rajeshak
//  LOG: Fix for Issue-ID: 2803, 2802, 2800, 2791
//  LOG:
//  LOG: Revision 1.1.2.4  2010/05/03 04:23:42  rajeshak
//  LOG: Fix for Issue-2710
//  LOG:
//  LOG: Revision 1.1.2.3  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.2  2010/03/25 06:31:29  rajeshak
//  LOG: API to get the Hex dump after encode/decode (for TDR).
//  LOG:
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#include <bssaple/ie/cellidentifier.h>


namespace bssaple
{
namespace ie
{


const int SIZE_OF_CELL_GLOBAL_IDENTIFICATION = sizeof(ITS_OCTET) * 8;
const int SIZE_OF_CELL_LAC_AND_CI = sizeof(ITS_OCTET) * 5;
const int SIZE_OF_CELL_CI = sizeof(ITS_OCTET) * 3;
const int SIZE_OF_CELL_NO_CELL = 0;


CellIdentifier::CellIdentifier(const ITS_OCTET *buf, int len)
: InfoElement(InfoElement::CELL_IDENTIFIER, len)
{
    discriminator = (Discriminator)buf[0];

    if(discriminator == GLOBAL_IDENTIFICATION)
    {
        if (len != SIZE_OF_CELL_GLOBAL_IDENTIFICATION)
        {
            ITN_THROW(DecodeException,
                "cell identifier size exeeded for its Discriminator");
        }
        
        memcpy(mcc,&buf[1],sizeof(ITS_OCTET)*2);

        mnc = buf[3];

        memcpy(lac,&buf[4],sizeof(ITS_OCTET)*2);

        memcpy(ci,&buf[6],sizeof(ITS_OCTET)*2);
        
    }
    else if(discriminator == LAC_AND_CI)
    {
        if(len != SIZE_OF_CELL_LAC_AND_CI)
        {
            ITN_THROW(DecodeException,
                "cell identifier size exeeded for its Discriminator");
        }

        memcpy(lac,&buf[1],sizeof(ITS_OCTET)*2);

        memcpy(ci,&buf[3],sizeof(ITS_OCTET)*2);

    }
    else if(discriminator == CI)
    {
        memcpy(ci,&buf[1],sizeof(ITS_OCTET)*2);
    }
    else if(discriminator == NO_CELL)
    {
    }
    else if (discriminator == 0x08)
    {
    }
    else if (discriminator == 0x09)
    {
    }
    else if (discriminator == 0x0A)
    {
    }
    else if (discriminator == 0x0B)
    {
    }
    else if (discriminator == 0x0C)
    {
    }
    else
    {
        ITN_THROW(DecodeException,"Invalid Cell Identifier");
    }

    ITS_OCTET * tmpPtr = (ITS_OCTET*)buf-2;
    int j=0;
    for(int i=0; i<len+2; i++)
    {
        snprintf((char*)&hexBuff[j], 2,"%X", ((tmpPtr[i]&0xF0)>>4));
        j++;
        snprintf((char*)&hexBuff[j], 2, "%X", (tmpPtr[i]&0x0F));
        j++;
    }
    hexBuff[j] = '\0';
}

int CellIdentifier::Encode (ITS_OCTET* buf, int& len) const
{
    if(discriminator == GLOBAL_IDENTIFICATION)
    {
        buf[0] = id;
        buf[1] = SIZE_OF_CELL_GLOBAL_IDENTIFICATION; 
        buf[2] = (ITS_OCTET)discriminator;
        memcpy(&buf[3],mcc,sizeof(ITS_OCTET)*2);
        buf[5] = mnc;
        memcpy(&buf[6],lac,sizeof(ITS_OCTET)*2);
        memcpy(&buf[8],ci,sizeof(ITS_OCTET)*2);

        len = SIZE_OF_CELL_GLOBAL_IDENTIFICATION + sizeof(ITS_OCTET)*2;
    }    
    else if(discriminator == LAC_AND_CI)
    {
        buf[0] = id;
        buf[1] = SIZE_OF_CELL_LAC_AND_CI;
        buf[2] = (ITS_OCTET)discriminator;
        memcpy(&buf[3],lac,sizeof(ITS_OCTET)*2);
        memcpy(&buf[5],ci,sizeof(ITS_OCTET)*2);

        len = SIZE_OF_CELL_LAC_AND_CI + sizeof(ITS_OCTET)*2;
    }
    else
    {
        buf[0] = id;
        buf[1] = SIZE_OF_CELL_CI;
        buf[2] = (ITS_OCTET)discriminator;
        memcpy(&buf[3],ci,sizeof(ITS_OCTET)*2); 

        len = SIZE_OF_CELL_CI + sizeof(ITS_OCTET)*2;
    }

    return CODEC_SUCCESS;
}

void CellIdentifier::PrintIE(std::ostream &out) const
{
    ITS_OCTET dig1,dig2,dig3,dig4,dig5;
    GetMCC(dig1,dig2,dig3);

    GetMNC(dig4,dig5);


    out<<"     IE CellIdentifier "<<std::endl;
    out<<"     [ "<<std::endl;
    out<<"\t\tCellDisc  0x"<<std::hex<<(int)(GetDiscriminator())<<std::endl;
    if(GetDiscriminator()== GLOBAL_IDENTIFICATION)
    {
        out<<"\t\tMCC_DIG1  0x"<<std::hex<<(int)(dig1)<<std::endl;
        out<<"\t\tMCC_DIG2  0x"<<std::hex<<(int)(dig2)<<std::endl;
        out<<"\t\tMCC_DIG3  0x"<<std::hex<<(int)(dig3)<<std::endl;
        out<<"\t\tMNC_DIG1  0x"<<std::hex<<(int)(dig4)<<std::endl;
        out<<"\t\tMNC_DIG2  0x"<<std::hex<<(int)(dig5)<<std::endl;
        out<<"\t\tLAC  0x"<<std::hex<<(int)(GetLAC ())<<std::endl;
    }
    if(GetDiscriminator()== LAC_AND_CI)
    {
        out<<"\t\tLAC  0x"<<std::hex<<(int)(GetLAC ())<<std::endl;
    }

    if ((GetDiscriminator()== GLOBAL_IDENTIFICATION) ||
                   (GetDiscriminator()== LAC_AND_CI) ||
                   (GetDiscriminator()== CI))
    {
        out<<"\t\tCI  0x"<<std::hex<<(int)(GetCI ())<<std::endl;
    }
    out<<"     ]"<<std::endl<<std::endl;
}    


} // namespace ie    
} // namespace bssaple    


