/////////////////////////////////-/-H-/-//////////////////////////////////////
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
//  ID: $Id: enhancedmeasurementreport.h,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG:$Log: enhancedmeasurementreport.h,v $
//  LOG:Revision 1.1.2.2  2010/03/31 05:47:14  rajeshak
//  LOG:ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//  LOG:
//  LOG:Revision 1.1.2.1  2010/03/23 05:39:43  rajeshak
//  LOG:Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: enhancedmeasurementreport.h,v 1.1.2.2 2010/03/31 05:47:14 rajeshak Exp $"

#ifndef BSSLAP_IE_ENHANCED_MEASUREMENTREPORT_H
#define BSSLAP_IE_ENHANCED_MEASUREMENTREPORT_H

#include <bsslap/ie/infoelement.h>

namespace bsslap
{
namespace ie
{

class EnhancedMeasurementReport: public InfoElement
{
    friend class InfoElement;

public :
    EnhancedMeasurementReport()
    : InfoElement(ENHANCED_MEASUREMENT_REPORT)
    {
    }
 
    /**
     * Returns a copy of this measurement report.
     */
    InfoElement *Clone() const
    {
        return new EnhancedMeasurementReport(*this);    
    }

protected :
    /**
     * Constructor: this contructor will perform decode the ie 
     *
     * @param buf - buffer contains data
     *          len - length of contained data
     */
    EnhancedMeasurementReport(const ITS_OCTET* buf, int& len);     
    
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

#endif // 

