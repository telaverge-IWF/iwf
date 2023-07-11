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
//   ID: $Id: cellidentitylist.cpp,v 1.1.2.5 2010/05/26 05:30:10 rajeshak Exp $
//
//  LOG: $Log: cellidentitylist.cpp,v $
//  LOG: Revision 1.1.2.5  2010/05/26 05:30:10  rajeshak
//  LOG: Fix for IssueId-2901(CellIdentityList Decoding Error Fix)
//  LOG:
//  LOG: Revision 1.1.2.4  2010/04/26 12:29:10  rajeshak
//  LOG: Fix for Issue 2676(Remove Set/Get API for 2 digit MNC)
//  LOG:
//  LOG: Revision 1.1.2.3  2010/04/21 06:30:57  rajeshak
//  LOG: Code Review comments
//  LOG:
//  LOG: Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG: Revision 1.1.2.1  2010/03/23 05:42:45  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: cellidentitylist.cpp,v 1.1.2.5 2010/05/26 05:30:10 rajeshak Exp $"

#include <bssaple/ie/cellidentitylist.h>
#include<vector>

namespace bssaple
{
namespace ie
{


const int SIZE_OF_CELL_GLOBAL_IDENTIFICATION = sizeof(ITS_OCTET) * 7;
const int SIZE_OF_CELL_LAC_AND_CI = sizeof(ITS_OCTET) * 4;
const int SIZE_OF_TARGET_ID_2 =  sizeof(ITS_OCTET) * 9;
const int SIZE_OF_TARGET_ID_3 =  sizeof(ITS_OCTET) * 6;


CellIdentityList::CellIdentityList(const ITS_OCTET *buf, int len)
: InfoElement(InfoElement::CELL_IDENTITY_LIST, 0)
{
    ITS_UINT index = 0,temp_len; //buf[0] is the lenth
    ITS_OCTET param_length = len;
    temp_len = param_length;
    while(temp_len > 0)
    {
        //Create a CellId object. Fill it with Buf then Add to Vector
        CellIdDiscriminator cellid ; 	

        cellid.discriminator = (CellIdDiscriminator::Discriminator)buf[index++];
        temp_len = temp_len - 1 ;
        if(cellid.discriminator == CellIdDiscriminator::GLOBAL_IDENTIFICATION)
        {
            //memcpy(cellid.mcc,&buf[index],sizeof(ITS_OCTET)*2);
            cellid.mcc[0] = buf[index++];
            cellid.mcc[1] = buf[index] & 0x0F;
            cellid.mnc[1] = ((buf[index++] & 0xF0) >> 4); 
            cellid.mnc[0] = buf[index++];

            memcpy(cellid.lac,&buf[index],sizeof(ITS_OCTET)*2);
            index += 2;
            memcpy(cellid.ci,&buf[index],sizeof(ITS_OCTET)*2);
            index += 2;
            //Update the len
            temp_len = temp_len - SIZE_OF_CELL_GLOBAL_IDENTIFICATION ;
        }
        else if(cellid.discriminator == CellIdDiscriminator::LAC_AND_CI)
        {
            memcpy(cellid.lac,&buf[index],sizeof(ITS_OCTET)*2);
            index += 2;
            memcpy(cellid.ci,&buf[index],sizeof(ITS_OCTET)*2);
            index += 2;
            //Update the len
            temp_len = temp_len - SIZE_OF_CELL_LAC_AND_CI;
        }
        else if(cellid.discriminator == CellIdDiscriminator::TARGET_ID_2)
        {
			//Ignore sizeof(ITS_OCTET) * 9 from the input buffer 
            memcpy(cellid.targetId2,&buf[index],sizeof(ITS_OCTET)*9);
			index += 9;
            temp_len = temp_len - SIZE_OF_TARGET_ID_2;
        }
        else if(cellid.discriminator == CellIdDiscriminator::TARGET_ID_3)
        {
			//Ignore sizeof(ITS_OCTET) * 6 from the input buffer 
            memcpy(cellid.targetId3,&buf[index],sizeof(ITS_OCTET)*6);
			index += 6;

            temp_len = temp_len - SIZE_OF_TARGET_ID_3;
        }
        else
        {
            ITN_THROW(DecodeException,"Invalid Cell Identifier");
        }

        //Add the cellid to the vector
        AddCellId(cellid);
     }//While
     len = index ;
}

int CellIdentityList::Encode (ITS_OCTET* buf, int& len) const 
{
    ITS_UINT index =2;
    ITS_UINT i = 0;
	
    buf[0] = id;
    //Get the vector elements and Encode one by one
    for(i = 0; i< cellVector.size();i++)
    {
        if(cellVector[i].discriminator == CellIdDiscriminator::GLOBAL_IDENTIFICATION)
        {
            buf[index++] = (CellIdDiscriminator::Discriminator)cellVector[i].discriminator;
            memcpy(&buf[index],cellVector[i].mcc,sizeof(ITS_OCTET)*2);
            index += 2;
            //buf[index++] = cellVector[i].mnc;
            memcpy(&buf[index++],cellVector[i].mnc,sizeof(ITS_OCTET)*2);
            memcpy(&buf[index],cellVector[i].lac,sizeof(ITS_OCTET)*2);
            index += 2;
            memcpy(&buf[index],cellVector[i].ci,sizeof(ITS_OCTET)*2);
            index += 2;
        }    
        else if(cellVector[i].discriminator == CellIdDiscriminator::LAC_AND_CI)
        {
            buf[index++] = (CellIdDiscriminator::Discriminator)cellVector[i].discriminator;
            memcpy(&buf[index],cellVector[i].lac,sizeof(ITS_OCTET)*2);
            index += 2;
            memcpy(&buf[index],cellVector[i].ci,sizeof(ITS_OCTET)*2);
            index += 2;
        }
        else if(cellVector[i].discriminator == CellIdDiscriminator::TARGET_ID_2)
        {
            buf[index++] = (CellIdDiscriminator::Discriminator)cellVector[i].discriminator;
            memcpy(&buf[index],cellVector[i].targetId2,sizeof(ITS_OCTET)*9);
            index += 9;
        }
        else if(cellVector[i].discriminator == CellIdDiscriminator::TARGET_ID_3)
        {
            buf[index++] = (CellIdDiscriminator::Discriminator)cellVector[i].discriminator;
            memcpy(&buf[index],cellVector[i].targetId3,sizeof(ITS_OCTET)*6);
            index += 6;
        }
    }
    len = index ; 
    buf[1] = index - 2;
    return CODEC_SUCCESS;
}
void CellIdentityList::PrintIE(std::ostream &out) const
{
    ITS_OCTET dig1,dig2,dig3,dig4,dig5,dig6;

    out<<"     IE CellIdentityList "<<std::endl;
    out<<"     [ "<<std::endl;

    for(int i = 0; i< cellVector.size();i++)
    {
        cellVector[i].GetMCC(dig1,dig2,dig3);
        cellVector[i].GetMNC(dig4,dig5,dig6);

        if(cellVector[i].discriminator == CellIdDiscriminator::GLOBAL_IDENTIFICATION)
        {
            out<<"\tCellId "<<std::endl;
            out<<"\t[ "<<std::endl;
            out<<"\t\tCellDisc  0x"<<std::hex<<(int)(cellVector[i].discriminator)<<std::endl;
            out<<"\t\tMCC_DIG1  0x"<<std::hex<<(int)(dig1)<<std::endl;
            out<<"\t\tMCC_DIG2  0x"<<std::hex<<(int)(dig2)<<std::endl;
            out<<"\t\tMCC_DIG3  0x"<<std::hex<<(int)(dig3)<<std::endl;
            out<<"\t\tMNC_DIG1  0x"<<std::hex<<(int)(dig4)<<std::endl;
            out<<"\t\tMNC_DIG2  0x"<<std::hex<<(int)(dig5)<<std::endl;
            out<<"\t\tMNC_DIG3  0x"<<std::hex<<(int)(dig6)<<std::endl;
            out<<"\t\tLAC[0][1]  0x"<<std::hex<<(int)(cellVector[i].GetLAC())<<std::endl;
            out<<"\t\tCI[0][1]  0x"<<std::hex<<(int)(cellVector[i].GetCI())<<std::endl;
            out<<"\t]"<<std::endl<<std::endl;
        }
        else if(cellVector[i].discriminator ==CellIdDiscriminator::LAC_AND_CI)
        {
            out<<"\tCellId "<<std::endl;
            out<<"\t[ "<<std::endl;
            out<<"\t\tCellDisc  0x"<<std::hex<<(int)(cellVector[i].discriminator)<<std::endl;

            out<<"\t\tLAC[0][1]  0x"<<std::hex<<(int)(cellVector[i].GetLAC())<<std::endl;
            out<<"\t\tCI[0][1]  0x"<<std::hex<<(int)(cellVector[i].GetCI())<<std::endl;
            out<<"\t]"<<std::endl<<std::endl;
        }
    }
}    

} // namespace ie    
} // namespace bssaple    


