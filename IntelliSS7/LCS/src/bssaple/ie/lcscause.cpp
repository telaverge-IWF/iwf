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
//   ID: $Id: lcscause.cpp,v 1.1.2.5 2010/05/10 13:05:03 rajeshak Exp $
//
//  LOG: $Log: lcscause.cpp,v $
//  LOG: Revision 1.1.2.5  2010/05/10 13:05:03  rajeshak
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

#include <bssaple/ie/lcscause.h>


namespace bssaple
{

namespace ie
{

LCSCause::LCSCause(const ITS_OCTET* buf, int len)
: InfoElement(InfoElement::LCS_CAUSE, len)
{
    causeValue = (Value)buf[0];

    if((len < sizeof(ITS_OCTET)*1) || (len > sizeof(ITS_OCTET)*2))
    {
        ITN_THROW(DecodeException,"Invalid IE length for LCS Cause IE");
    }
    else if (len == sizeof(ITS_OCTET)*1)
    {
        // Cause Value fine
    }
    else // len == sizeof(ITS_OCTET)*2
    {
        if(causeValue != LCSCause::POSITION_METHOD_FAILURE)
        {
            ITN_THROW(DecodeException,"Invalid IE length for this LCS Cause 'Position method failure'");
        }
        diagValue  = (PositionMethodDiagnostic)buf[1];
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

LCSCause::~LCSCause()
{
}

int LCSCause::Encode (ITS_OCTET* buf, int& len) const
{
    len = length + sizeof(ITS_OCTET)*2;

    buf[0] = id;
    buf[1] = length;

    buf[2] = (ITS_OCTET)causeValue;
    if(causeValue == LCSCause::POSITION_METHOD_FAILURE)
    {
        buf[3] = (ITS_OCTET)diagValue;
    }        

    ITS_OCTET * tmpPtr = (ITS_OCTET*)buf;
    int j=0;
    for(int i=0; i<len; i++)
    {
        snprintf((char*)&hexBuff[j], 2,"%X", ((tmpPtr[i]&0xF0)>>4));
        j++;
        snprintf((char*)&hexBuff[j], 2, "%X", (tmpPtr[i]&0x0F));
        j++;
    }
    hexBuff[j] = '\0';

    return CODEC_SUCCESS;
}

void LCSCause::SetDiagnostic(LCSCause::PositionMethodDiagnostic val)
{
    if(causeValue == LCSCause::POSITION_METHOD_FAILURE)
    {
        diagValue = val;
        length = sizeof(ITS_OCTET)*2;
    }
    else
    {
        ITN_THROW(InvalidData,"Invalid seting of values for LCS cause");
    }
}

void LCSCause::PrintIE(std::ostream &out) const
{
    out<<"      IE LCS Cause "<<std::endl;
    out<<"      ["<<std::endl;;
    out<<"\t\tcauseValue  0x"<<std::hex<<(int)causeValue<<" - "<<LCSCAUSE_VALUE_STRING((int)causeValue)<<std::endl;
    if(length == 2)
    {
        out<<"\t\tDiagnosticValue  0x"<<std::hex<<(int)diagValue<<std::endl;
    }
    out<<"      ]"<<std::endl<<std::endl;

}


} // namespace ie   
} // namespace bssaple   


