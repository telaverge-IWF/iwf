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
//   ID: $Id: classmarkinfotype3.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: classmarkinfotype3.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_CLASSMARKINFOTYPE3_H
#define BSSAPLE_IE_CLASSMARKINFOTYPE3_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{

namespace ie
{

/**
 * ClassmarkInfoType3 contains classmark information for a target MS obtained
 * from the MS Classmark 3 defined in GSM 04.08.
 *
 * The length of the Classmark is between 1 and 12.
 */
class ClassmarkInfoType3: public InfoElement
{
public:
    /**
    * Constructors 
    */
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
    ClassmarkInfoType3();

    /**
    *    Destructor 
    *
    */
    ~ClassmarkInfoType3();

    /**
    *    Operation: SetP_GSMSupported
    */
    void SetP_GSMSupported (bool val    // array of octets.
    );

    /**
    *    Operation: SetEorR_GSMSupported
    */

    void SetEorR_GSMSupported (bool val);

    /**
    *    Operation: SetDCS1800Supported
    */
    void SetDCS1800Supported (bool val);

    /**
    *    Operation: SetA5_4
    */
    void SetA5_4 (bool val);

    /**
    *    Operation: SetA5_5
    */
    void SetA5_5 (bool val);

    /**
    *    Operation: SetA5_6
    */
    void SetA5_6 (bool val);

    /**
    *    Operation: SetA5_7
    */
    void SetA5_7 (bool val);

    /**
    *    Operation: SetRadioCapability1
    */
    void SetRadioCapability1 (ITS_OCTET val);

    /**
    *    Operation: SetRadioCapability2
    */
    void SetRadioCapability2 (ITS_OCTET val);

    /**
    *    Operation: SetR_Support
    */
    void SetR_Support (ITS_OCTET val);

    /**
    *    Operation: SetMultiSlotCapability
    */
    void SetMultiSlotCapability (ITS_OCTET val);

    /**
    *    Operation: SetUCS2Treatment
    */
    void SetUCS2Treatment (bool val);

    /**
    *    Operation: SetExtMeasurement
    */
    void SetExtMeasurement (bool val);

    /**
    *    Operation: SetSMSValue
    */
    void SetSMSValue (ITS_OCTET val);

    /**
    *    Operation: SetSMValue
    */
    void SetSMValue (ITS_OCTET val);

    /**
    *    Operation: SetMSAssistedE_OTD
    */
    void SetMSAssistedE_OTD (bool val);

    /**
    *    Operation: SetMSBasedE_OTD
    */
    void SetMSBasedE_OTD (bool val);

    /**
    *    Operation: SetMSAssistedGPS
    */
    void SetMSAssistedGPS (bool val);

    /**
    *    Operation: SetMSBasedGPS
    */
    void SetMSBasedGPS (bool val);

    /**
    *    Operation: SetMSConventionalGPS
    */
    void SetMSConventionalGPS (bool val);

    /**
    *    Operation: GetP_GSMSupported
    */
    bool GetP_GSMSupported ();

    /**
    *    Operation: GetEorR_GSMSupported
    */
    bool GetEorR_GSMSupported ();

    /**
    *    Operation: GetDCS1800Supported
    */
    bool GetDCS1800Supported ();

    /**
    *    Operation: GetA5_4
    */
    bool GetA5_4 ();

    /**
    *    Operation: GetA5_5
    */
    bool GetA5_5 ();

    /**
    *    Operation: GetA5_6
    */
    bool GetA5_6 ();

    /**
    *    Operation: GetA5_7
    */
    bool GetA5_7 ();

    /**
    *    Operation: GetRadioCapability1
    */
    ITS_OCTET GetRadioCapability1 ();

    /**
    *    Operation: GetRadioCapability2
    */
    ITS_OCTET GetRadioCapability2 ();

    /**
    *    Operation: GetR_Support
    */
    ITS_OCTET GetR_Support ();

    /**
    *    Operation: GetMultiSlotCapability
    */
    ITS_OCTET GetMultiSlotCapability ();

    /**
    *    Operation: GetUCS2Treatment
    */
    bool GetUCS2Treatment ();

    /**
    *    Operation: GetExtMeasurement
    */
    bool GetExtMeasurement ();

    /**
    *    Operation: GetSMSValue
    */
    ITS_OCTET GetSMSValue ();

    /**
    *    Operation: GetSMValue
    */
    ITS_OCTET GetSMValue ();

    /**
    *    Operation: GetMSAssistedE_OTD
    */
    bool GetMSAssistedE_OTD ();

    /**
    *    Operation: GetMSBasedE_OTD
    */
    bool GetMSBasedE_OTD ();

    /**
    *    Operation: GetMSAssistedGPS
    */
    bool GetMSAssistedGPS ();

    /**
    *    Operation: GetMSBasedGPS
    */
    bool GetMSBasedGPS ();

    /**
    *    Operation: GetMSConventionalGPS
    */
    bool GetMSConventionalGPS();

protected:

    virtual void PrintIE(std::ostream &); 

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

    virtual InfoElement *Clone() const
    {       
        return new ClassmarkInfoType3(*this);
    }

    /**
     *  Purpose:
     *      This constructor can only be invoked by members and friends.
     *
     *  Input Parameters:
     *      buf - is encoded bufer
     *      len - is lenght of encoded bufer
     *
     *  Output Parameters:
     *
     */
    ClassmarkInfoType3(ITS_OCTET *buf,int len);

private: 

    friend class InfoElement;

};



} // namespace ie
} // namespace bssaple


#endif

