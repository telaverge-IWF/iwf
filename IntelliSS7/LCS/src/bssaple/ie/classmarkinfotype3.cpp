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
//   ID: $Id: classmarkinfotype3.cpp,v 1.1.2.1 2009/12/22 10:41:43 rajeshak Exp $
//
//  LOG: $Log: classmarkinfotype3.cpp,v $
//  LOG: Revision 1.1.2.1  2009/12/22 10:41:43  rajeshak
//  LOG: Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////

#include <bssaple/ie/classmarkinfotype3.h>

namespace bssaple
{

namespace ie
{
    ClassmarkInfoType3::ClassmarkInfoType3(const ITS_OCTET *buf,int len)
    {
    }

    ClassmarkInfoType3::~ClassmarkInfoType3()
    {
    }

    int ClassmarkInfoType3::Encode (ITS_OCTET* buf, int& len) const
    {
    }

    void ClassmarkInfoType3::SetP_GSMSupported (ITS_BOOLEAN val)
    {
    }

    void ClassmarkInfoType3::SetEorR_GSMSupported (ITS_BOOLEAN val)
    {
    }

    void ClassmarkInfoType3::SetDCS1800Supported (ITS_BOOLEAN val)
    {
    }

    void ClassmarkInfoType3::SetA5_4 (ITS_BOOLEAN val)
    {
    }

    void ClassmarkInfoType3::SetA5_5 (ITS_BOOLEAN val)
    {
    }

    void ClassmarkInfoType3::SetA5_6 (ITS_BOOLEAN val)
    {
    }

    void ClassmarkInfoType3::SetA5_7 (ITS_BOOLEAN val)
    {
    }

    void ClassmarkInfoType3::SetRadioCapability1 (ITS_OCTET val)
    {
    }

    void ClassmarkInfoType3::SetRadioCapability2 (ITS_OCTET val)
    {
    }

    void ClassmarkInfoType3::SetR_Support (ITS_OCTET val)
    {
    }

    void ClassmarkInfoType3::SetMultiSlotCapability (ITS_OCTET val)
    {
    }

    void ClassmarkInfoType3::SetUCS2Treatment (ITS_BOOLEAN val)
    {
    }

    void ClassmarkInfoType3::SetExtMeasurement (ITS_BOOLEAN val)
    {
    }

    void ClassmarkInfoType3::SetSMSValue (ITS_OCTET val)
    {
    }

    void ClassmarkInfoType3::SetSMValue (ITS_OCTET val)
    {
    }

    void ClassmarkInfoType3::SetMSAssistedE_OTD (ITS_BOOLEAN val)
    {
    }

    void ClassmarkInfoType3::SetMSBasedE_OTD (ITS_BOOLEAN val)
    {
    }

    void ClassmarkInfoType3::SetMSAssistedGPS (ITS_BOOLEAN val)
    {
    }

    void ClassmarkInfoType3::SetMSBasedGPS (ITS_BOOLEAN val)
    {
    }

    void ClassmarkInfoType3::SetMSConventionalGPS (ITS_BOOLEAN val)
    {
    }

    ITS_BOOLEAN ClassmarkInfoType3::GetP_GSMSupported ()
    {
    }

    ITS_BOOLEAN ClassmarkInfoType3::GetEorR_GSMSupported ()
    {
    }

    ITS_BOOLEAN ClassmarkInfoType3::GetDCS1800Supported ()
    {
    }

    ITS_BOOLEAN ClassmarkInfoType3::GetA5_4 ()
    {
    }

    ITS_BOOLEAN ClassmarkInfoType3::GetA5_5 ()
    {
    }

    ITS_BOOLEAN ClassmarkInfoType3::GetA5_6 ()
    {
    }

    ITS_BOOLEAN ClassmarkInfoType3::GetA5_7 ()
    {
    }

    ITS_OCTET ClassmarkInfoType3::GetRadioCapability1 ()
    {
    }

    ITS_OCTET ClassmarkInfoType3::GetRadioCapability2 ()
    {
    }

    ITS_OCTET ClassmarkInfoType3::GetR_Support ()
    {
    }

    ITS_OCTET ClassmarkInfoType3::GetMultiSlotCapability ()
    {
    }

    ITS_BOOLEAN ClassmarkInfoType3::GetUCS2Treatment ()
    {
    }

    ITS_BOOLEAN ClassmarkInfoType3::GetExtMeasurement ()
    {
    }

    ITS_OCTET ClassmarkInfoType3::GetSMSValue ()
    {
    }

    ITS_OCTET ClassmarkInfoType3::GetSMValue ()
    {
    }

    ITS_BOOLEAN ClassmarkInfoType3::GetMSAssistedE_OTD ()
    {
    }

    ITS_BOOLEAN ClassmarkInfoType3::GetMSBasedE_OTD ()
    {
    }

    ITS_BOOLEAN ClassmarkInfoType3::GetMSAssistedGPS ()
    {
    }

    ITS_BOOLEAN ClassmarkInfoType3::GetMSBasedGPS ()
    {
    }

    ITS_BOOLEAN ClassmarkInfoType3::GetMSConventionalGPS ()
    {
    }


    ostream & operator<<(ostream &out,const ClassmarkInfoType3 &obj);
    {

    }


} // namespace ie    
} // namespace bssaple    


