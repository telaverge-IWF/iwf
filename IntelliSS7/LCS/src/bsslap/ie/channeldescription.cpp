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
//   ID: $Id: channeldescription.cpp,v 1.1.2.1 2009/12/22 10:41:43 rajeshak Exp $
//
//  LOG: $Log: channeldescription.cpp,v $
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bsslap/ie/channeldescription.h>

namespace bsslap {
namespace ie {

ChannelDescription::ChannelDescription(const ITS_OCTET* buf, int& len)
:	InfoElement(CHANNEL_DESCRIPTION)
{
    int ielen = 0;
	if (len >= 3 * sizeof(ITS_OCTET))
	{
	    // oct 2 contains channel_type .. & tn values
		//channelTypeTdmaOffset = buf[1] >> 3;
        //tn = buf[1] & TN_MASK;
        //tsc = buf[2] >> 5;
        //hop = (buf[2] & H_MASK) >> 4;
        
        channelTypeTdmaOffset = buf[0] >> 3;
        tn = buf[0] & TN_MASK;
        tsc = buf[1] >> 5;
        hop = (buf[1] & H_MASK) >> 4;
       
        //oct 3 contains three part tsc, h, (maio or arfcn)
        //depend on hop value to determine maio or arfcn
        if (hop == 1) 
        {
           ITS_OCTET high_maio = buf[1] &  MAIO_HIGH_PART_MASK;
           ITS_OCTET low_maio = buf[2] >> 6;
           maio = ((high_maio << 2) | low_maio);
           hsn = buf[2] & HSN_MASK;
        }
        else
        {
            ITS_OCTET high_arfcn = buf[1] & ARFCN_HIGH_PART_MASK;
            ITS_OCTET low_arfcn = buf[2];
            arfcn = ((high_arfcn << 8) | low_arfcn);
        }
        ielen += 3;

	}
    else
    { 
        ITN_THROW(IllegalArgumentException, "Invalid IE length");
    }
    len = ielen;  
}

void 
ChannelDescription::Encode(ITS_OCTET* buf, int& len) const
{
	len = 4 * sizeof(ITS_OCTET);

	buf[0] = param_id;
	buf[1] = ((channelTypeTdmaOffset << 3) | tn);
    if (hop == 1)
    {
		buf[2] = ((tsc <<5) | (hop << 4) | (maio >> 2));
        buf[3] = ((maio << 6) | (hsn));
    }
    else
    {
        buf[2] = ((tsc << 5)| (hop << 4) | (arfcn >> 8));
        buf[3] = ((arfcn | 0xFF) << 8 );
    }
}

void ChannelDescription::Print(std::ostream& out) const
{
    out << "\tChannel Descrption {\n";
    
    out << "\n\t\tChannel Type and TDMA offset ( 0x" << std::hex 
        <<  (int)channelTypeTdmaOffset << " )";
    out << "\n\t\tH ( 0x" << (int)hop << std::hex << " )"; 
    if (hop)
    {
        out << "\n\t\tMAIO ( 0x" << std::hex << (int)maio << " )";     
    }
    else
    {
        out << "\n\t\tARFCN ( 0x" << std::hex << (int)arfcn << " )"; 
    }
    out << "\n\t\tTN ( 0x" << (int)tn << std::hex << " )"; 
    out << "\n\t\tTSC ( 0x" << (int)tsc << std::hex << " )"; 
    out << "\n\t\tHSN ( 0x" << (int)hsn << std::hex << " )";
    out << "\n" << "\t}\n";
}

} // end of namespace ie
} // end of namespace bsslap

