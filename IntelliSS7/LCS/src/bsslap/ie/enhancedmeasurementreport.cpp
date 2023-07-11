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
//   ID: $Id: enhancedmeasurementreport.cpp,v 1.1.2.3 2010/08/12 08:17:10 rajeshak Exp $
//
//  LOG: $Log: enhancedmeasurementreport.cpp,v $
//  LOG: Revision 1.1.2.3  2010/08/12 08:17:10  rajeshak
//  LOG: Fix Issue:3351
//  LOG:
//  LOG: Revision 1.1.2.2  2010/08/06 05:20:05  rajeshak
//  LOG: Fix for Issue:3351
//  LOG:
//  LOG: Revision 1.1.2.1  2010/03/23 05:44:52  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: enhancedmeasurementreport.cpp,v 1.1.2.3 2010/08/12 08:17:10 rajeshak Exp $"

#include <bsslap/ie/enhancedmeasurementreport.h>

namespace bsslap {
namespace ie {

EnhancedMeasurementReport::EnhancedMeasurementReport(const ITS_OCTET* buf, int& len)
: InfoElement(ENHANCED_MEASUREMENT_REPORT)
{
    len = buf[0] + 1; /* IE length + 1 bye for Length Field */
}

void EnhancedMeasurementReport::Encode(ITS_OCTET *buf, int& len) const
{
}

void EnhancedMeasurementReport::Print(std::ostream& out) const
{  
    out << "\tEnhancedMeasurementReport \n";
    out << "\t[\n";
    out << "\t]\n";
}

} // end of namespace ie
} // end of namespace bsslap

