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
//   ID: $Id: lmucause.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: lmucause.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_LMUCAUSE_H
#define BSSAPLE_IE_LMUCAUSE_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{

namespace ie
{

void static TEST_LMUCause(void);

/**
 * LMUCause provides the reason for the release or rejection of an LMU
 * signaling connection between an MSC and an SMLC.
 */
class LMUCause : public InfoElement
{
public:

    enum LmuCauseValue
    {
        UNSPECIFIED              =    0x00,
        NORMAL_RELEASE           =    0x01,
        SYSTEM_FAILURE           =    0x02,
        PROTOCOL_ERROR           =    0x03,
        MISSING_DATA             =    0x04,
        UNEXPECTED_DATA          =    0x05,
        CONGESTION               =    0x06,
        LOSS_OF_RADIO_CHANNEL    =    0x07,
        RELEASE_BY_LMU           =    0x08,
        UNKNOWN_LMU              =    0x09,
        LMU_SIGNALING_ERROR      =    0x0A,
        LMU_NOT_AUTHENTICATED    =    0x0B,
        NO_RESPONSE_FROM_LMU     =    0x0C,
        LMU_IN_ERRONEOUS_STATE   =    0x0D,
        UNSPECIFIED_PROTOCOL     =    0x0E
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
    LMUCause():causeValue(0),InfoElement(InfoElement::LMU_CAUSE,0)
    {}

    /**
    *    Destructor 
    */
    ~LMUCause() 
    {}

    /**
    *   Operation: SetCauseValue
    */
    void SetCauseValue (LmuCauseValue val)
    {
        causeValue = val;
    }

    /**
    *    Operation: GetCauseValue
    *    Return Cause Value of LMU Cause
    */
    LmuCauseValue  GetCauseValue () const   
    {
        return (LmuCauseValue)causeValue;
    }
        


protected:
    /**
     *  Purpose:
     *      This method Enocde the IEs in to the buf argument.
     *
     *  Input Parameters:
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - returns the length of encoded buffer.
     *
     *  Throws Exception:
     *      Throws EncodingException in case unsuccessful
     */
     virtual int Encode (ITS_OCTET* buf, int& len) const;

    virtual InfoElement *Clone() const
    {
        return new LMUCause(*this);
    }

    /**
     *  Purpose:
     *      This constructor can only be invoked by members and friends.
     *      This contructor decodes the buffer and creates object of its type.
     *
     *  Input Parameters:
     *      buf - is encoded bufer
     *      len - is lenght of encoded bufer
     *
     *  Output Parameters:
     *
     */
    LMUCause(const ITS_OCTET *buf,int len );

    virtual void PrintIE(std::ostream &) const;

private:

    /**
    *    Assignment Operation 
    */
    LMUCause & operator=(const LMUCause &right);

    ITS_OCTET causeValue;

    friend class InfoElement;

    friend void TEST_LMUCause(void);
};


} // namespace ie
} // namespace bssaple 



#endif

