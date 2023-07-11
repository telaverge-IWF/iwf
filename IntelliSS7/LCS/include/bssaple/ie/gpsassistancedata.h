//////////////////////////////////-*-h-*-/////////////////////////////////////
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
//   ID: $Id: gpsassistancedata.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: gpsassistancedata.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_GPSASSISTANCEDATA_H
#define BSSAPLE_IE_GPSASSISTANCEDATA_H 

#include <bssaple/ie/infoelement.h>
#include <vector>

namespace bssaple     {

namespace ie     {

void static TEST_GPSAssistanceData(void);

/**
 * GPSAssistanceData is a variable length information element identifying the
 * GPS assistance data requested for an MS.
 */
class GPSAssistanceData : public InfoElement
{
public:
    struct SatID_IODE 
    {
        ITS_OCTET satid;
        ITS_OCTET iode;
    };

    typedef std::vector<SatID_IODE> Satid_Iode;

    /**
     *  Purpose:
     *      This is default contructor initailizes the type and
     *      default length.
     *
     *  Input Parameters:
     *
     *  Output parameters:
     *
     */
    GPSAssistanceData()
    :gpsweek(0),
    gpstoe(0),
    nsat_toelimit(0),
    InfoElement(InfoElement::GPS_ASSISTANCE_DATA,0)
    {
        AtoI[0] =0x0;
        AtoI[1]=0x0;

    }

    /**
     * Destructor 
     */
    ~GPSAssistanceData()
    {}


    /**
     *  Purpose: Set Alamanac
     *
     *  Input Parameters:
     *      Alamanac - flag for  Alamanac
     *
     *  OutPut Parameters:
     *
     *  Returns:
     *
     */
    void SetAlamanac (ITS_BOOLEAN Alamanac)
    {
        AtoI[0] |=  0x01U & (ITS_OCTET)Alamanac;
    }

    /**
     *  Purpose: Get Alamanac 
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *
     *  Returns:
     *      Alamanac flag
     *
     */
    ITS_BOOLEAN GetAlamanac () const
    {
        return (AtoI[0] & 0x01U);
    }

    /**
     *  Purpose: Set UTCModel flag
     *
     *  Input Parameters:
     *      UTCModel - flag for UTCModel
     *
     *  OutPut Parameters:
     *
     *  Returns:
     *
     */
    void SetUTCModel (ITS_BOOLEAN UTCModel)
    {
        AtoI[0] |= 0x02U & (ITS_OCTET)UTCModel;
    }

    /**
     *  Purpose: Get UTCModel 
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      UTCModel flag
     *
     */
    ITS_BOOLEAN GetUTCModel () const
    {
        return ((AtoI[0] >> 1) & 0x01U);
    }

    /**
     *  Purpose: Set IonosphericModel
     *
     *  Input Parameters:
     *      IonosphericModel - flag for IonosphericModel
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetIonosphericModel (ITS_BOOLEAN val)
    {
        AtoI[0] |= 0x04U & (ITS_OCTET)val;
    }

    /**
     *  Purpose: Get IonosphericModel
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      IonosphericModel flag
     *
     */
    ITS_BOOLEAN GetIonosphericModel () const
    {
        return ((AtoI[0] >> 2) & 0x01U);
    }

    /**
     *  Purpose: Set NavigationModel 
     *
     *  Input Parameters:
     *      val - boolean flag for NavigationModel
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetNavigationModel (ITS_BOOLEAN val)
    {
        AtoI[0] |= 0x08U & (ITS_OCTET)val;
    }

    /**
     *  Purpose:Get flag NavigationModel
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      NavigationModel boolean flag
     *
     */
    ITS_BOOLEAN GetNavigationModel () const
    {
        return ((AtoI[0] >> 3) & 0x01U);
    }

    /**
     *  Purpose: Set flag DGPSCorrectios 
     *
     *  Input Parameters:
     *      val - flag for DGPSCorrectios
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetDGPSCorrectios (ITS_BOOLEAN val)
    {
        AtoI[0] |= 0x10U & (ITS_OCTET)val;
    }

    /**
     *  Purpose:Get flag DGPSCorrections 
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      DGPSCorrections flag
     *
     */
    ITS_BOOLEAN GetDGPSCorrections () const
    {
        return ((AtoI[0] >> 4) & 0x01U);
    }


    /**
     *  Purpose: Set ReferenceLocation flag
     *
     *  Input Parameters:
     *      val - flag for ReferenceLocation
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetReferenceLocation (ITS_BOOLEAN val)
    {
        AtoI[0] |= 0x20U & (ITS_OCTET)val;
    }

    /**
     *  Purpose: Get ReferenceLocation flag
     *
     *  Input Parameters:
     *      
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      ReferenceLocation flag 
     *
     */
    ITS_BOOLEAN GetReferenceLocation () const
    {
        return ((AtoI[0] >> 5) & 0x01U);
    }

    /**
     *  Purpose: Set ReferenceTime flag
     *
     *  Input Parameters:
     *      val - flag for ReferenceTime
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetReferenceTime (ITS_BOOLEAN val)
    {
        AtoI[0] |= 0x40U & (ITS_OCTET)val;
    }

    /**
     *  Purpose: Get ReferenceTime flag
     *
     *  Input Parameters:
     *      
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      ReferenceTime flag
     *
     */
    ITS_BOOLEAN GetReferenceTime () const
    {
        return ((AtoI[0] >> 6) & 0x01U);
    }

    /**
     *  Purpose: Set AcquisitionAssistance
     *
     *  Input Parameters:
     *      val - flag for AcquisitionAssistance
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetAcquisitionAssistance (ITS_BOOLEAN val)
    {
        AtoI[0] |= 0x80U & (ITS_OCTET)val;
    }

    /**
     *  Purpose: Get AcquisitionAssistance flag
     *
     *  Input Parameters:
     *      
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      AcquisitionAssistance flag
     *
     */
    ITS_BOOLEAN GetAcquisitionAssistance () const
    {
        return ((AtoI[0] >> 7) & 0x01U);
    }

    /**
     *  Purpose: Set RealTimeIntegrity flag
     *
     *  Input Parameters:
     *      val - flag for RealTimeIntegrity
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetRealTimeIntegrity (ITS_BOOLEAN val)
    {
        AtoI[1] = (ITS_OCTET)val;
    }

    /**
     *  Purpose: Get RealTimeIntegrity flag
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      RealTimeIntegrity flag
     *
     */
    ITS_BOOLEAN GetRealTimeIntegrity () const
    {
        return (AtoI[1] & 0x01U);
    }

    /**
     *  Purpose: Set GPSWeek 
     *
     *  Input Parameters:
     *      GPS_Week - value for GPS_Week
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetGPSWeek (ITS_USHORT GPS_Week)
    {
        gpsweek = GPS_Week;
    }

    /**
     *  Purpose: Get GPSWeek
     *
     *  Input Parameters:
     *      
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      GPSWeek value
     *
     */
    ITS_USHORT GetGPSWeek () const
    {
        return gpsweek;
    }

    /**
     *  Purpose: Set GPS_TOE
     *
     *  Input Parameters:
     *      GPS_Toe - value for GPS_Toe
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetGPS_TOE (ITS_OCTET GPS_Toe)
    {
        gpstoe = GPS_Toe;
    }

    /**
     *  Purpose: Get GPS_TOE 
     *
     *  Input Parameters:
     *      
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      GPS_TOE value
     *
     */
    ITS_OCTET GetGPS_TOE () const
    {
        return gpstoe;
    }

    /**
     *  Purpose: Set NSAT value
     *
     *  Input Parameters:
     *      NSAT - value of NSAT
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetNSAT (ITS_OCTET NSAT)
    {
        nsat_toelimit |= ((NSAT << 4) & 0xF0U);
    }

    /**
     *  Purpose: Get NSAT value
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      NSAT value
     *
     */
    ITS_OCTET GetNSAT () const
    {
        return ((nsat_toelimit >> 4) & 0x0FU);
    }

    /**
     *  Purpose: Set T-ToeLimit value
     *
     *  Input Parameters:
     *      T_Toelimit - value of ToeLimit
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetT_ToeLimit (ITS_OCTET   T_Toelimit)
    {
        nsat_toelimit |= T_Toelimit & 0x0FU;
    }

    /**
     *  Purpose: Get T_ToeLimit value
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      value of T_ToeLimit
     *
     */
    ITS_OCTET GetT_ToeLimit () const
    {
        return (nsat_toelimit & 0x0FU);
    }

    /**
     *  Purpose: Add SatID_IODE values
     *
     *  Input Parameters:
     *      satid - instace of SatID_IODE
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     *  Note:
     *      SatID_IODE is structure contain attributes of SatID 
     *      and IODE.There can be any number of SatID_IODEs in 
     *      this information element.This function adds the SatID_IODE
     *      to a vector (satid_iode) at begining. 
     *
     */
    void AddSatID_IODE (SatID_IODE satid)
    {
        satid_iode.insert(satid_iode.begin(),satid);
    }
        

    /**
     *  Purpose: Returns the Satid_Iode vector
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      the Satid_Iode vector
     *
     */
    const Satid_Iode& GetSatID_IODE () const
    {
        return satid_iode;
    }

protected:

    /**
     *  Purpose:
     *      This method Enocde the IEs in to the buf argument.
     *
     *  Input Parameters:
     *      buf - a pointer to the buffer to encode into
     *
     *  Output Parameters:
     *      len - returns the length of encoded buffer.
     *
     *  Throws Exception:
     *      Throws EncodingException in case unsuccessful
     */
     virtual int Encode (ITS_OCTET* buf, int& len) const;

    virtual void PrintIE(std::ostream& out) const;

    /**
     * Operation Clone()
     */
    virtual InfoElement *Clone() const
    {
        return new GPSAssistanceData(*this);
    }

    /**
     *  Purpose:
     *      This constructor can only be invoked by members and friends.
     *      This constructor decodes the buffer.
     *
     *  Input Parameters:
     *      buf - is encoded bufer
     *      len - is lenght of encoded bufer
     *
     *  Output Parameters:
     *
     */
    GPSAssistanceData(const ITS_OCTET *buf,int len);

private:
    /**
     *    This attribute contains two octets (total 16 bits) that
     *    each bit stand for its particular inforamtion. At least
     *    one of bits A, B, C, D, E, F, G, H, I shall be set to
     *    "1".
     *    All bit has it own name corresponding to each bit, from
     *    A to H alphibetically
     *    This a field contains a 10 bits represent GPSWeek. The
     *    most sibnificant bit of the GPS Week is bit 8 in octet 5
     *    and the least significant bit is bit 1 in octet 6.
     */
    ITS_OCTET AtoI[2];
    ITS_USHORT gpsweek;
    ITS_OCTET gpstoe;
    ITS_OCTET nsat_toelimit;
    Satid_Iode satid_iode;

    /**
     * To check at least one of bit AtoI bits set to 1
     */
    /**
     *  Purpose:
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    ITS_BOOLEAN CheckAtoI(void) const;
            
    /**
     * Assignment Operation 
     */
    GPSAssistanceData & operator=(const GPSAssistanceData &right);

    friend class InfoElement;

    friend void TEST_GPSAssistanceData(void);

};

inline ITS_BOOLEAN GPSAssistanceData::CheckAtoI(void) const
{
    if( GetAlamanac() ==0 && 
        GetUTCModel() ==0 &&
        GetIonosphericModel() ==0 &&
        GetNavigationModel() ==0  &&
        GetDGPSCorrections() ==0  &&
        GetReferenceLocation() ==0  &&
        GetReferenceTime() ==0  &&
        GetAcquisitionAssistance() ==0  &&
        GetRealTimeIntegrity() ==0 )
    {
        return false;
    }
    else
    {
        return true;
    }
}


}

}

#endif

