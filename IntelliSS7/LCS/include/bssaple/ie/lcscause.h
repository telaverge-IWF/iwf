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
//   ID: $Id: lcscause.h,v 1.1.2.7 2010/06/01 10:29:36 rajeshak Exp $
//
//   LOG: $Log: lcscause.h,v $
//   LOG: Revision 1.1.2.7  2010/06/01 10:29:36  rajeshak
//   LOG: Partial Fix for IssueID#2792
//   LOG:
//   LOG: Revision 1.1.2.6  2010/05/23 13:04:19  rajeshak
//   LOG: Fix for Issue Id:2889(Exception while decoding LCS Cause)
//   LOG:
//   LOG: Revision 1.1.2.5  2010/05/17 05:58:14  rajeshak
//   LOG: Diagnostic cause not getting added.(Issue ID: 2815 Fix)
//   LOG:
//   LOG: Revision 1.1.2.4  2010/03/26 11:48:05  rajeshak
//   LOG: GetHexBuff function signature changes
//   LOG:
//   LOG: Revision 1.1.2.3  2010/03/25 06:32:32  rajeshak
//   LOG: API to get the Hex dump after encode/decode (for TDR).
//   LOG:
//   LOG: Revision 1.1.2.2  2010/02/22 12:29:46  rajeshak
//   LOG: Added Diagnostic cause values as per new requirement.
//   LOG:
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_LCSCAUSE_H
#define BSSAPLE_IE_LCSCAUSE_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{

namespace ie
{

static void TEST_LCSCAUSE(void);

#define LCSCAUSE_VALUE_STRING(c) \
        (((c) == UNSPECIFIED ) ?                        "UNSPECIFIED" : \
		 ((c) == SYSTEM_FAILURE) ?                      "SYSTEM_FAILURE" : \
		 ((c) == PROTOCOL_ERROR) ?                      "PROTOCOL_ERROR" : \
		 ((c) == DATA_MISSINGIN_IN_POSITION_REQUEST) ?  "DATA_MISSINGIN_IN_POSITION_REQUEST" : \
		 ((c) == UNEXPECTED_DATA_IN_POSITION_REQUEST) ? "UNEXPECTED_DATA_VALUE_IN_POSITION_REQUEST" : \
		 ((c) == POSITION_METHOD_FAILURE) ?             "POSITION_METHOD_FAILURE" : \
		 ((c) == TARGET_MS_UNREACHABLE) ?               "TARGET_MS_UNREACHABLE" : \
		 ((c) == LOCATION_REQUEST_ABORTED) ?            "LOCATION_REQUEST_ABORTED" : \
		 ((c) == FACILITY_NOT_SUPPORTED) ?              "FACILITY_NOT_SUPPORTED" : \
		 ((c) == INTER_BSC_HANDOVER_ONGOING) ?          "INTER_BSC_HANDOVER_ONGOING" : \
		 ((c) == INTRA_BSC_HANDOVER_COMPLETE) ?         "INTRA_BSC_HANDOVER_COMPLETE" : \
		 ((c) == CONGESTION) ?                          "CONGESTION" : \
		                                                "ERROR")  

/**
 * LCSCause is of variable length IE and provides the reason for an
 * unsuccessful location request.
 */
class LCSCause: public InfoElement
{
public:
    enum Value
    {
        UNSPECIFIED                         = 0x00,
        SYSTEM_FAILURE                      = 0x01,
        PROTOCOL_ERROR                      = 0x02,
        DATA_MISSINGIN_IN_POSITION_REQUEST  = 0x03,
        UNEXPECTED_DATA_IN_POSITION_REQUEST = 0x04,
        POSITION_METHOD_FAILURE             = 0x05,
        TARGET_MS_UNREACHABLE               = 0x06,
        LOCATION_REQUEST_ABORTED            = 0x07,
        FACILITY_NOT_SUPPORTED              = 0x08,
        INTER_BSC_HANDOVER_ONGOING          = 0x09,
        INTRA_BSC_HANDOVER_COMPLETE         = 0x0A,
        CONGESTION                          = 0x0B
    };
    

    enum PositionMethodDiagnostic
    {
        DIAGNOSTIC_CONGESTION                 = 0x00,
        INSUFFICIENT_RESOURCES                = 0x01,
        INSUFFICIENT_MEASUREMENT_DATA         = 0x02,
        INCONSISTENT_MEASUREMENT_DATA         = 0x03,
        PROCEDURE_NOT_COMPLETED               = 0x04,
        PROCEDURE_NOT_SUPPORTED_BY_TARGET_MS  = 0x05,
        QOS_NOT_ATTAINABLE                    = 0x06,
        METHOD_NOT_AVAILABLE_IN_NETWORK       = 0x07,
        METHOD_NOT_AVAILABLE_IN_LOCATION_AREA = 0x08,
        CHANNEL_NOT_SUPPORTED                 = 0x0B,
        POSITIONING_PROC_NOT_SUPPORTED        = 0x0C,
        OTHER_RADIO_RELATED_FAILURE           = 0x0D,
        SUPERVISION_TIMER_EXPIRED             = 0x0F,
        INCORRECT_SERVING_CELL_ID             = 0x12,
        LE_SEGMENTATION_ERROR                 = 0x13,
        NO_DIAGNOSTIC                         = 0xFF  // not used in encoding
    };

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
    LCSCause(Value value = UNSPECIFIED,
             PositionMethodDiagnostic diagnostic = NO_DIAGNOSTIC)
    : InfoElement(InfoElement::LCS_CAUSE, sizeof(ITS_OCTET)),
      causeValue(value),
      diagValue(diagnostic)
    {}

    /**
     * Destructor 
     */
    ~LCSCause();

    /**
     *  Purpose: Set CauseValue
     *
     *  Input Parameters:
     *      val - is cause value
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetCauseValue (Value val)
    {
        causeValue = val;
    }

    /**
     *  Purpose: Get CauseValue
     *
     *  Input Parameters:
     *      
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      cause value
     *
     */
    Value GetCauseValue () const
    {
        return causeValue;
    }

    /**
     *  Purpose: Set Diagnostic value
     *
     *  Input Parameters:
     *      val - is  PositionMethodDiagnostic value
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *  Note:
     *      LCSCause contains Diagnostic value in case only if  
     *      the cause value is POSITION_METHOD_FAILURE
     *
     */
    void SetDiagnostic(PositionMethodDiagnostic val);

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
     *      value of PositionMethodDiagnostic
     *
     */
    PositionMethodDiagnostic GetDiagnostic() const
    {
        return diagValue;
    }

    /**
     *  Purpose: Get Hex Buff (This can be used after IE decode only)
     *
     *  Input Parameters:
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      Hex Buff
     *
     */
    const ITS_OCTET* GetHexBuff() const
    {
        return hexBuff;
    }

protected:

    /**
     *  Purpose:
     *      This method Enocde the IEs in to the buf argument.
     *
     *  Input Parameters:
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into.
     *      len - returns the length of encoded buffer.
     *
     *  Throws Exception:
     *      Throws EncodingException in case unsuccessful
     */
     virtual int Encode (ITS_OCTET* buf, int& len) const;

    /**
     *  Purpose:
     *      This constructor can only be invoked by members and friends.
     *      This contructor decodes the buffer and creates object of its type.
     *
     *  Input Parameters:
     *      buf - is encoded bufer.
     *      len - is lenght of encoded bufer.
     *
     *  Output Parameters:
     *
     */
    LCSCause(const ITS_OCTET* buf,int len);

    InfoElement *Clone() const
    {
        return new LCSCause(*this);
    }

    virtual void PrintIE(std::ostream &) const;

private: 
    mutable ITS_OCTET hexBuff[15];
    Value causeValue;
    PositionMethodDiagnostic diagValue;

    friend class InfoElement;
    friend void TEST_LCSCAUSE(void);
};


} // namespace ie    
} // namespace bssaple    



#endif

