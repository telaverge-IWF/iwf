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
//  ID: $Id: deltatimerrel8.h,v 1.1.2.1 2010/03/23 05:39:43 rajeshak Exp $
//
//  LOG:$Log: deltatimerrel8.h,v $
//  LOG:Revision 1.1.2.1  2010/03/23 05:39:43  rajeshak
//  LOG:Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: deltatimerrel8.h,v 1.1.2.1 2010/03/23 05:39:43 rajeshak Exp $"

#ifndef BSSLAP_IE_DELTATIMER_REL8_H
#define BSSLAP_IE_DELTATIMER_REL8_H

#include <bsslap/ie/infoelement.h>

namespace bsslap {
namespace ie {

class DeltaTimerRel8 : public InfoElement
{
    friend class InfoElement;

public:

    DeltaTimerRel8(const ITS_OCTET timer = 0)
    :InfoElement(DELTA_TIMER_REL8), timerValue(timer)
    {
    }

    /**
     * Set DeltaTimer Value
     * @param value 
     */
    void
    SetTimerValue(ITS_OCTET value)
    {
        timerValue = value;
    }

    /**
     * Get DeltaTimer Value
     * @return timerValue 
     */
    ITS_OCTET
    GetTimerValue()
    {
        return timerValue;
    }

protected:
    /**
     * Constructor: perform decode the data buffer
     * @param buf 
     * @param len 
     */
    DeltaTimerRel8(const ITS_OCTET* buf, int& len);

    /**
     * Encode DeltaTimer Value
     * @param: buf - Input data buffer to decode
     * @param: len - Input/Output data buffer length
     */
    virtual void Encode(ITS_OCTET* buf, int& len) const;
    
    /**
     * Clone
     */
    InfoElement* 
    Clone() const
    {
        return new DeltaTimerRel8(*this);	
    }

    /**
     * Print function that print all IEs
     * @param: (std::ostream&) out
     */
    virtual void Print(std::ostream& out) const;

private :

    ITS_OCTET timerValue;

};

} // end of namespace ie
} // end of namespace bsslap

#endif // !BSSLAP_IE_DELTATIMER_REL8_H

