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
//   ID: $Id: cellidentity.cpp,v 1.1.2.6 2010/05/17 14:16:44 rajeshak Exp $
//
//  LOG: $Log: cellidentity.cpp,v $
//  LOG: Revision 1.1.2.6  2010/05/17 14:16:44  rajeshak
//  LOG: Fix for Issue Id-2822
//  LOG:
//  LOG: Revision 1.1.2.5  2010/05/10 13:05:03  rajeshak
//  LOG: Fix for Issue-ID: 2803, 2802, 2800, 2791
//  LOG:
//  LOG: Revision 1.1.2.4  2010/05/03 04:23:42  rajeshak
//  LOG: Fix for Issue-2710
//  LOG:
//  LOG: Revision 1.1.2.3  2010/03/26 11:42:38  rajeshak
//  LOG: Renaming IE code for SERVING_CELL_IDENTITY to CELL_IDENTITY
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

#include <bsslap/ie/cellidentity.h>

namespace bsslap {
namespace ie {

CellIdentity::CellIdentity(const ITS_OCTET* buf, int& len)
:    InfoElement((InfoElement::Type)buf[0])
{
    param_id = static_cast<InfoElement::Type>(buf[0]);
    int ielen = 0;
    if (len >= 2 * sizeof(ITS_OCTET))
    {
        cellIdentity = (buf[1] << 8 | buf[2]);
        ielen += 2;
    }
    else
    {
        ITN_THROW(DecodeException, "Invalid IE length");
    }
    len = ielen;

    ITS_OCTET * tmpPtr = (ITS_OCTET*)buf;
    int j=0;
    for(int i=0; i<len+1; i++)
    {
        snprintf((char*)&hexBuff[j], 2,"%X", ((tmpPtr[i]&0xF0)>>4));
        j++;
        snprintf((char*)&hexBuff[j], 2, "%X", (tmpPtr[i]&0x0F));
        j++;
    }
    hexBuff[j] = '\0';
}


void CellIdentity::Encode(ITS_OCTET* buf, int& len) const
{
    len = 3 * sizeof(ITS_OCTET);

    buf[0] = CELL_IDENTITY;
    buf[1] = cellIdentity >> 8;
    buf[2] = cellIdentity & 0xFFU;

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
}

void CellIdentity::Print(std::ostream& out) const
{
    out << "\tCellIdentity ( 0x" << std::hex << cellIdentity << " )\n";
}

} // end of namespace ie
} // end of namespace bsslap

