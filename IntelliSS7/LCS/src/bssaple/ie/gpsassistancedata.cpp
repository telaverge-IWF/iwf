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
//   ID: $Id: gpsassistancedata.cpp,v 1.1.2.3 2010/11/04 01:49:50 rajeshak Exp $
//
//  LOG: $Log: gpsassistancedata.cpp,v $
//  LOG: Revision 1.1.2.3  2010/11/04 01:49:50  rajeshak
//  LOG: Fix for Issue 3553
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

#include <bssaple/ie/gpsassistancedata.h>


namespace bssaple
{

namespace ie
{


GPSAssistanceData::GPSAssistanceData(const ITS_OCTET *buf,int len)
:InfoElement(InfoElement::GPS_ASSISTANCE_DATA,len)
{
    AtoI[0] = buf[0];
    AtoI[1] = buf[1] ;

    if(!CheckAtoI()) 
    {
        ITN_THROW(IllegalArgumentException,
             "At least one of bits A to I, shall be set to the value 1");
    }

    if (len > 5)
    {
        gpsweek = (buf[2] << 8) |  buf[3];
        gpstoe = buf[4];
        nsat_toelimit = buf[5];

        for(int i=0;(i+1)<(len - (sizeof(ITS_OCTET)*6));++i)
        {
            GPSAssistanceData::SatID_IODE sat_iode;
            sat_iode.satid = buf[6+i];
            sat_iode.iode = buf[6+ ++i];

            AddSatID_IODE(sat_iode);
        }
    }
}

int GPSAssistanceData::Encode (ITS_OCTET* buf, int& len) const
{
    len = sizeof(ITS_OCTET)*8 + satid_iode.size()*2; 

    buf[0] = id;
    buf[1] = sizeof(ITS_OCTET)*6 + satid_iode.size()*2;

    buf[2] = AtoI[0]; 
    buf[3] = AtoI[1];

    if(!CheckAtoI())
    {
        ITN_THROW(IllegalArgumentException,
             "At least one of bits A to I, shall be set to the value 1");
    }

    buf[4] = gpsweek >> 8 & 0xFFU;
    buf[5] = gpsweek & 0xFFU;
    buf[6] = gpstoe;
    
    buf[7] = nsat_toelimit;

    int j=0;
    for(int i=0;i<(satid_iode.size()*2);++i)
    {
        buf[8+i] = satid_iode[j].satid;
        buf[8+ ++i] = satid_iode[j].iode;
        ++j;
    }

    return CODEC_SUCCESS;
}

void GPSAssistanceData::PrintIE(std::ostream &out) const
{
    out<<"      IE GPSAssistanceData"<<std::endl;
    out<<"      ["<<std::endl;
    out<<"\t\tAlamanac   0x"<<std::hex<<(int)GetAlamanac()<<std::endl;
    out<<"\t\tUTCModel   0x"<<std::hex<<(int)GetUTCModel()<<std::endl;
    out<<"\t\tIonosphericModel   0x"
                        <<std::hex<<(int)GetIonosphericModel()<<std::endl;
    out<<"\t\tNavigationModel   0x"<<
                        std::hex<<(int)GetNavigationModel()<<std::endl;
    out<<"\t\tDGPSCorrections   0x"<<
                        std::hex<<(int)GetDGPSCorrections()<<std::endl;
    out<<"\t\tReferenceLocation   0x"<<
                        std::hex<<(int)GetReferenceLocation()<<std::endl;
    out<<"\t\tReferenceTime   0x"<<
                        std::hex<<(int)GetReferenceTime()<<std::endl;
    out<<"\t\tAcquisitionAssistance   0x"<<
                        std::hex<<(int)GetAcquisitionAssistance()<<std::endl;
    out<<"\t\tRealTimeIntegrity   0x"<<
                        std::hex<<(int)GetRealTimeIntegrity()<<std::endl;
    out<<"\t\tGPS_Week   0x"<<
                        std::hex<<(int)gpsweek<<std::endl;
    out<<"\t\tGPS_Toe   0x"<<
                        std::hex<<(int)gpstoe<<std::endl;
    out<<"\t\tNSAT   0x"<<
                        std::hex<<(int)GetNSAT()<<std::endl;
    out<<"\t\tT_ToeLimit   0x"<<
                        std::hex<<(int)GetT_ToeLimit()<<std::endl<<std::endl;

    out<<"\t\tNo.of SatID_IODE  0x"<<
                        std::hex<<GetSatID_IODE().size()<<std::endl;

    for(int i=0;i<GetSatID_IODE().size();++i)
    {
        out<<"\t\tSatID_IODE["<<i<<"].SatID  0x"<<
                        std::hex<<(int)GetSatID_IODE()[i].satid<<"      "
           <<"SatID_IODE["<<i<<"].IODE  0x"<<
                        std::hex<<(int)GetSatID_IODE()[i].iode<<std::endl;
    }
    out<<"      ]"<<std::endl<<std::endl;
    
}

} // namespace ie    
} // namespace bssaple    


