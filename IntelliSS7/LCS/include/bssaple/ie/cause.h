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
//   ID: $Id: cause.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: cause.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSAPLE_IE_CAUSE_H
#define BSSAPLE_IE_CAUSE_H 


#include <bssaple/ie/infoelement.h>


namespace bssaple
{
namespace ie
{

static void TEST_CAUSE(void);


/**
 * Cause is a variable length information element indicating the reason for
 * sending a Reset message.
 */
class Cause: public InfoElement 
{
public:
    /**
     * if 1st ITS_OCTET is 1XXX 0000, then xxx is: 
     */
    enum CauseClass 
    {
        C_CLASS_NORMAL_EVENT1         =    0x00U,
        C_CLASS_NORMAL_EVENT2         =    0x01U,
        C_CLASS_RESRC_UNAVAILABLE     =    0x02U,
        C_CLASS_SERVICE_UNAVAILABLE   =    0x03U,
        C_CLASS_SERVICE_UNIMPLEMENTED =    0x04U,
        C_CLASS_INVALID_MESSAGE       =    0x05U,
        C_CLASS_PROTOCOL_ERROR        =    0x06U,
        C_CLASS_INTERWORKING          =    0x07U
    };

    /**
    * 'cause_val' ITS_OCTET coding of bits 6 - 0 
    */
    enum CauseValue 
    {
        C_RADIO_INTERFACE_MSG_FAIL = 0x00U,
        C_RADIO_INTERFACE_FAIL     = 0x01U,
        C_MISSING_ONE              = 0x02U,
        C_UPLINK_STRENGTH          = 0x03U,
        C_DOWNLINK_QUALITY         = 0x04U,
        C_DOWNLINK_STRENGTH        = 0x05U,
        C_DISTANCE                 = 0x06U,
        C_OAMP_INTERVANTION        = 0x07U,
        C_RESPONSE_MSC_INVOCATION  = 0x08U,
        C_CALL_CONTROL             = 0x09U,
        C_REVERT_TO_OLD_CHANNEL    = 0x0AU,
        C_HANDOFF_SUCCESSFUL       = 0x0BU,
        C_MS_NO_RESPONSE           = 0x0CU,
        C_TIMER_EXPIRED            = 0x0DU,
        C_MISSING_TWO              = 0x0EU,
        C_MISSING_THREE            = 0x0FU,
        C_RESERVED_INTERNATIONAL1  = 0x10U,
        C_RESERVED_INTERNATIONAL2  = 0x17U,
        C_RESERVED_NATIONAL1       = 0x1FU,
        C_EQUIPMENT_FAIL           = 0x20U,
        C_RADIO_RESRC_UNAVAILABLE  = 0x21U,
        C_LAND_RESRC_UNAVAILABLE   = 0x22U,
        C_CCCH_OVERLOAD            = 0x23U,
        C_PROCESSOR_OVERLOAD       = 0x24U,
        C_BS_NOT_EQUIPPED          = 0x25U,
        C_MS_NOT_EQUIPPED          = 0x26U,
        C_RESERVED_INTERNATIONAL3  = 0x27U,
        C_RESERVED_NATIONAL2       = 0x2AU,
        C_MOBILE_REDIRECTED1       = 0x2EU,
        C_MOBILE_REDIRECTED2       = 0x2FU,
        C_TRA_UNAVAILABLE          = 0x30U,
        C_RESERVED_INTERNATIONAL4  = 0x31U,
        C_CIPHER_ALGOL_UNSUPPORTED1= 0x3FU,
        C_CIPHER_ALGOL_UNSUPPORTED2= 0x40U,
        C_RESERVED_INTERNATIONAL5  = 0x41U,
        C_RESERVED_NATIONAL3       = 0x47U,
        C_LAND_CIRCUIT_ALLOCATED1  = 0x48U,
        C_LAND_CIRCUIT_ALLOCATED2  = 0x50U,
        C_RESERVED_INTERNATIONAL6  = 0x51U,
        C_RESERVED_NATIONAL4       = 0x57U,
        C_RESERVED_NATIONAL5       = 0x58U,
        C_BS_MSC_PROTOCOL_ERROR1   = 0x5FU,
        C_BS_MSC_PROTOCOL_ERROR2   = 0x60U,
        C_RESERVED_INTERNATIONAL7  = 0x61U,
        C_RESERVED_NATIONAL6       = 0x67U,
        C_RESERVED_NATIONAL7       = 0x68U,
        C_RESERVED_INTERNATIONAL8  = 0x6FU,
        C_RESERVED_INTERNATIONAL9  = 0x70U,
        C_RESERVED_NATIONAL8       = 0x77U,
        C_RESERVED_NATIONAL9       = 0x78U,
        C_HANDOFF_TIMEOUT          = 0x7FU,
        C_CELL_POWER_BUDGET        = 0x0EU,
        C_INTERFERENCE             = 0x0FU,
        C_HANDOFF_BLOCKED          = 0x2AU,
        C_RESERVED_PRIVATE_OPTS    = 0x18U,
        C_ALT_SIG_TYPE_REJECT      = 0x2BU,
        C_SCAN_FUNC_UNAVAILABLE    = 0x2CU,
        C_SOFT_HANDOFF             = 0x19U,
        C_INTER_BS_SOFT_HO_ADD     = 0x1AU,
        C_INTER_BS_SOFT_HO_DROP    = 0x1BU,
        C_INTRA_BS_SOFT_HO_ADD     = 0x1CU,
        C_INTRA_BS_SOFT_HO_DROP    = 0x1DU,
        C_SOFT_HANDOFF_DROP_SOURCE = 0x1EU
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
    Cause::Cause():InfoElement(InfoElement::CAUSE,sizeof(ITS_OCTET))
    {}

    ~Cause()
    {}

    /**
     * Operation: SetCauseValue
     *
     *  Input Parameters:
     *      isExt - extention for this cause.
     *      cause1 - cause in first octet.
     *      cause2 - cause in the second octet.
     *
     *  Output parameters:
     *
     *  Throws Exception:
     *      throws InvalidData exception incase unsuccessful
     *
     */
    void SetCauseValue (bool isExt,ITS_OCTET cause1, ITS_OCTET cause2);

    /**
     *  Operation:SetNationalCause
     *
     *  Purpose:
     *      National Cause ONLY incase of ext ==1 then octet 1 
     *      will look like 1 x x x 0 0 0 0 , x x x is class.
     *
     *  Input Parameters:
     *      classType - the type of class.
     *      value     - cause value.
     *
     *  Throws Exception:
     *      throws InvalidData exception incase unsuccessful
     *
     *  Note:
     *      This Set function must be used only if the cause is
     *      a National Cause type ,other wise use the SetCauseValue
     *      function.
     *
     */
    void SetNationalCause (CauseClass classType,CauseValue value);

    /**
     * Operation: GetCauseValue
     *
     *  Purpose:
     *      To get the cause values from the object
     *
     *  Input Parameters:
     *      
     *  Output parameters:
     *      isExt - returns true if cause has extention.
     *      isNat - returns true cause is National cause indicator.
     *      causORval - this could be a causeclass or cause value.
     *      cause     - returns cause(this is considered only if  
     *                  isExt == true).
     */
    void GetCauseValue (bool& isExt,bool& isNat,ITS_OCTET& causORval,
                                           ITS_OCTET&cause) const;

protected:

    virtual void PrintIE(std::ostream &) const;

    /**
     *  Purpose:
     *      This method Enocde the IEs in to the buf argument.
     *
     *  Input Parameters:
     *      buf - a pointer to the buffer to encode into.
     *
     *  Output Parameters:
     *      len - returns the length of encoded buffer.
     *
     *  Throws Exception:
     *      Throws EncodingException in case unsuccessful.
     */
     virtual int Encode (ITS_OCTET* buf,int& len) const;

    virtual InfoElement *Clone() const
    {
        return new Cause(*this);
    }

    /**
     *  Purpose:
     *      This constructor can only be invoked by members and friends.
     *      This constructor decodes the buffer.
     *
     *  Input Parameters:
     *      buf - is encoded bufer.
     *      len - is lenght of encoded bufer.
     *
     *  Output Parameters:
     *
     */
    Cause(const ITS_OCTET *buf,int len);

private: 

    bool ext;
    bool natFlag;
    ITS_OCTET cause[2];

    friend class InfoElement;
    friend  void TEST_CAUSE();
};

} // namespace ie
} // namespace bssaple


#endif

