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
//   ID: $Id: measurementreport.cpp,v 1.1.2.1 2009/12/22 10:41:43 rajeshak Exp $
//
//  LOG: $Log: measurementreport.cpp,v $
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bsslap/ie/measurementreport.h>

namespace bsslap {
namespace ie {

MeasurementReport::MeasurementReport(const ITS_OCTET* buf, int& len)
: InfoElement(MEASUREMENT_REPORT)
{
    int ielen = 0;
    if (len >= 17 * sizeof(ITS_OCTET))
	{
        param_length = buf[0];
        baUsed = buf[1] >> 7;
        dtxUsed= (buf[1] >> 6) & 0x01U;
        rxLevFullServingCell = buf[1] & 0x3FU;
        rxLevSubServingCell = buf[2] & 0x3FU;
        valid = ((buf[2] >> 6) | 0x01U) == 0;
        rxQualFullServingCell = buf[3] >> 4;
        rxQualSubServingCell = (buf[3] & 0x0EU) >> 1;
        count = ((buf[3] & 0x01) << 2 ) | (buf[4] >> 6);
        rxLevNcell[0] = (buf[4] & 0x3FU);
        bcchFreqNcell[0] = buf[5] >> 3;
        bsicNcell[0] = ((buf[5] & 0xF8U) << 3) | ((buf[6] & 0xE0U) >> 5);
        rxLevNcell[1] = ((buf[6] & 0x1FU) << 1) | (buf[7] >> 7);
        bcchFreqNcell[1] = (buf[7] & 0x7CU) >> 2;
        bsicNcell[1] =((buf[7] & 0x02U) << 4) | (buf[7] >> 4);
        rxLevNcell[2] =((buf[8] & 0x0FU) << 2) | (buf[8] >> 6);
        bcchFreqNcell[2] = ((buf[8] & 0x3EU) >> 1);
        bsicNcell[2] = ((buf[9] & 0x01U) << 6) | (buf[10] >> 3); 
        rxLevNcell[3] = ((buf[10] & 0x07U) << 3) | (buf[11] >> 5);
        bcchFreqNcell[3] = buf[11] & 0x1FU;
        bsicNcell[3] = buf[12] >> 2;
        rxLevNcell[4] = ((buf[12] & 0x02U) << 4) | (buf[13] >> 4);
        bcchFreqNcell[4] = ((buf[13] & 0x1FU) << 1) | (buf[14] >> 7);
        bsicNcell[4] = ((buf[14] & 0x7EU) >> 1); 
        rxLevNcell[5] = ((buf[14] & 0x01U) << 6) | (buf[15] >> 3);
        bcchFreqNcell[5] = ((buf[15] & 0x07U) << 2) | (buf[16] >> 6);
        bsicNcell[5] = buf[16] & 0x3FU;
        
        ielen +=  17;
	}
    else
    {
        ITN_THROW(IllegalArgumentException, "Invalid IE length");
    }
    len = ielen;
}

void MeasurementReport::Encode(ITS_OCTET *buf, int& len) const
{
    len = 18 * sizeof(ITS_OCTET);
 
    buf[0] = param_id;
    buf[1] = param_length;
    buf[2] = (baUsed << 7) | (dtxUsed<< 6) 
                | rxLevFullServingCell;
    //buf[3] = ( valid << 6) | rxLevSubServingCell;
    buf[3] = (valid ? 0x00 : 0x40) | rxLevSubServingCell;
    buf[4] = (rxQualFullServingCell << 4) |
                rxLevSubServingCell | (count >> 2);
    buf[5] = (count << 6) | rxLevNcell[0];
    buf[6] = (bcchFreqNcell[0] << 3) | bsicNcell[0];
    buf[7] = (bsicNcell[0] << 5) | (rxLevNcell[1] >> 1);
    buf[8] = (rxLevNcell[1] << 7) | bcchFreqNcell[1]
                | (bsicNcell[1] >> 4);
    buf[9] = (bsicNcell[1] << 4) | (rxLevNcell[2] >> 2);
    buf[10] = (rxLevNcell[2] << 6) | bcchFreqNcell[2]
                | (bsicNcell[2] >> 4);
    buf[11] = (bsicNcell[2] << 3) | (rxLevNcell[3] >> 3);
    buf[12] = (rxLevNcell[3] << 5) | bcchFreqNcell[3];
    buf[13] = bsicNcell[3] | (rxLevNcell[4] >> 4);
    buf[14] = (rxLevNcell[4] << 4) | (bcchFreqNcell[4] >>1);
    buf[15] = (bcchFreqNcell[4] << 7) | bsicNcell[4]
                | (rxLevNcell[5] >> 5);
    buf[16] = (rxLevNcell[5] << 3) | (bcchFreqNcell[5] >> 2);
    buf[17] = (bcchFreqNcell[5] << 6) | bsicNcell[5];
}

void MeasurementReport::Print(std::ostream& out) const
{  
    out << "\tMeasurementReport { " 
        << "\n\t\tBA Used ( 0x" << std::hex << baUsed << " )\n"; 
    out << " \t\tDTX Used ( 0x" << std::hex << dtxUsed<< " )\n"; 
    out << "\t\tFullServingCellRxPowerLevel ( 0x" << std::hex 
        << (int)rxLevFullServingCell << " )\n";
    out << "\t\tSubServingCellRXPowerLevel ( 0x" << std::hex
        << (int)rxLevSubServingCell << " )\n";
    out << "\t\tValid MEAS( 0x" << (valid ? '0' : '1') << " )\n";
    out << "\t\tFullServingCellReceiveQuality ( 0x" <<std::hex
        << (int)rxQualFullServingCell << " )\n"; 
    out << "\t\tSubServingCellReceiveQuality ( 0x" << std::hex 
        << (int)rxQualSubServingCell << " )\n";
    out << "\t\tcount ( 0x" << std::hex << (int)count << " )\n"; 
    for (int i = 0; i < 6; ++i)
    {
        out << "\t\tNeighborCellPowerLevel[" << i <<"] ( 0x" << std::hex
            << (int)rxLevNcell[i] << " )\n";
   
        out << "\t\tNeighborCellFrequency[" << i << "] ( 0x" << std::hex
            << (int)bcchFreqNcell[i] << " )\n";
    
        out << "\t\tNeighborCellBSIC[" << i << "] ( 0x" << std::hex
            << (int)bsicNcell[i] << " )\n";
    }
    out << "\n" << "\t}\n";
}

} // end of namespace ie
} // end of namespace bsslap

