/////////////////////////////////-/-C++-/-////////////////////////////////////
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
//  ID: $Id: measurementreport.h,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG:$Log: measurementreport.h,v $
//  LOG:Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG:ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_IE_MEASUREMENTREPORT_H
#define BSSLAP_IE_MEASUREMENTREPORT_H

#include <bsslap/ie/infoelement.h>

namespace bsslap
{
namespace ie
{

struct MeasurementReportStruct
{
    MeasurementReportStruct(ITS_OCTET rxLevFull = 0, ITS_OCTET rxLevSub = 0,
                            ITS_OCTET rxQualFull = 0, ITS_OCTET  rxQualSub = 0,
                            bool ba = 0, bool dtx = 0)
    : rxLevFullServingCell(rxLevFull), rxLevSubServingCell(rxLevSub),
      rxQualFullServingCell(rxQualFull), rxQualSubServingCell(rxQualSub),
      baUsed(ba), dtxUsed(dtx), count(0), valid(true)
    {}

    ITS_OCTET rxLevFullServingCell;
    ITS_OCTET rxLevSubServingCell;
    ITS_OCTET rxQualFullServingCell;
    ITS_OCTET rxQualSubServingCell;
    bool      valid;
    bool      baUsed;
    bool      dtxUsed;
    int       count;
    ITS_OCTET rxLevNcell[6];
    ITS_OCTET bcchFreqNcell[6];
    ITS_OCTET bsicNcell[6];
};

class MeasurementReport: public InfoElement, public MeasurementReportStruct
{
    friend class InfoElement;

public :
    enum Type
    {
        NO_NEIGHBOUR_CELL_MEASUREMENT_RESULT = 0x00U,
        NEIGHBOUR_CELL_INFORMATION_NOT_AVAILABLE = 0x07U
    };

    MeasurementReport(ITS_OCTET rxLevFull = 0, ITS_OCTET rxLevSub = 0, 
                      ITS_OCTET rxQualFull = 0, ITS_OCTET  rxQualSub = 0,
                      bool ba = 0, bool dtx = 0)
    : InfoElement(MEASUREMENT_REPORT),
      MeasurementReportStruct(rxLevFull,rxLevSub,rxQualFull,rxQualSub,ba,dtx)
    {
        for (int i = 0; i < 6; ++i)
        {
            rxLevNcell[i] = 0;
            bcchFreqNcell[i] = 0;
            bsicNcell[i] = 0;
        }
        param_length = 0x10;

    }
 
    const MeasurementReportStruct &GetAsStruct() const
    {
        return *static_cast<const MeasurementReportStruct *>(this);
    }

    /**
     *
     */
    void 
    SetBAUsed(bool value)
    {
        baUsed = value;
    }

    /**
     *
     */
    bool
    IsBAUsed()
    {
        return baUsed;
    }

    /**
     *
     */
    void 
    SetDTXUsed(bool value)
    {
        dtxUsed = value;
    }

    /**
     *
     */
    bool 
    IsDTXUsed()
    {
        return dtxUsed;
    }

    /**
     *
     */
    void
    SetValid(bool val)
    {
        valid = val;
    }

    /**
     *
     */
    bool
    IsValid()
    {
        return valid;
    }

    /**
     *
     */
    void 
    SetFullServingCellRxPowerLevel(ITS_OCTET value)
    {
        rxLevFullServingCell = value;
    }

    /**
     *
     */
    ITS_OCTET 
    GetFullServingCellRxPowerLevel()
    {
        return rxLevFullServingCell;
    }

    /**
     *
     */
    void 
    SetSubServingCellRxPowerLevel(ITS_OCTET value)
    {
        rxLevSubServingCell = value;
    }

    /**
     *
     */
    ITS_OCTET 
    GetSubServingCellRxPowerLevel()
    {
        return rxLevSubServingCell;
    }

    /**
     *
     */
    void 
    SetFullServingCellRxQuality(ITS_OCTET value)
    {
        rxQualFullServingCell = value;
    }

    /**
     *
     */
    ITS_OCTET 
    GetFullServingCellRxQuality()
    {
        return rxQualFullServingCell;
    }

    /**
     *
     */
	void 
    SetSubServingCellRxQuality(ITS_OCTET value)
    {
        rxQualSubServingCell = value;
    }

    /**
     *
     */
    ITS_OCTET 
    GetSubServingCellRxQuality()
    {
        return rxQualSubServingCell;
    }

    /**
     *
     */
    void 
    AddNeighborCellMeasurement(ITS_OCTET bsic, ITS_OCTET powerLevel, 
                               ITS_OCTET frequency)
    {
        if ( count < 6 )
        {
            rxLevNcell[count] = powerLevel;
            bcchFreqNcell[count] = frequency;
            bsicNcell[count] = bsic;
            ++count;
        }
        else
        {
            ITN_THROW(BufferOverflowException, "Too many neighbor cells");
        }
    }

    int GetNeighborCellCount()
    {
        return count;
    }

    /**
     *
     */
    ITS_OCTET GetNeighborCellBSIC(int index)
    {
        return bsicNcell[index];
    }

    /**
     *
     */
    ITS_OCTET GetNeighborCellPowerLevel(int index)
    {
        return rxLevNcell[index];
    }

    /**
     *
     */
    ITS_OCTET GetNeighborCellFrequency(int index)
    {
        return bcchFreqNcell[index];
    }

	/**
	 * Returns a copy of this measurement report.
	 */
	InfoElement *Clone() const
	{
		return new MeasurementReport(*this);	
	}

protected :
    /**
	 * Constructor: this contructor will perform decode the ie 
	 *
	 * @param buf - buffer contains data
	 *		  len - length of contained data
	 */
	MeasurementReport(const ITS_OCTET* buf, int& len);     
    
	/*
	 * Encode MeasurementReport
	 * @param buf - The buffer that will contain the encoded data.
	 * @param len - This parameter will contain the length of encodede data.
	 * @return CODEC_SUCCESS - if the function succeeds.
	 */
    virtual void Encode(ITS_OCTET *buf, int& len) const;
    
    /*
     * Print function that print all IEs
     * @param: (std::ostream&) out
     */
    virtual void Print(std::ostream& out) const;
};

} // end of namespace ie
} // end of namespace bsslap

#endif // !BSSLAP_IE_MEASUREMENTREPORT_H

