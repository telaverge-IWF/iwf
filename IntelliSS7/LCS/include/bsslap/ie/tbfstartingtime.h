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
//  ID: $Id: tbfstartingtime.h,v 1.1.2.1 2010/03/23 05:41:53 rajeshak Exp $
//
//  LOG:$Log: tbfstartingtime.h,v $
//  LOG:Revision 1.1.2.1  2010/03/23 05:41:53  rajeshak
//  LOG:Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: tbfstartingtime.h,v 1.1.2.1 2010/03/23 05:41:53 rajeshak Exp $"

#ifndef BSSLAP_IE_TBF_STARTING_TIME_H
#define BSSLAP_IE_TBF_STARTING_TIME_H

#include <bsslap/ie/infoelement.h>

namespace bsslap {
namespace ie {

class TbfStartingTime : public InfoElement
{
    friend class InfoElement;
public :    

    /**
     * Constructor
     * @param st1
     * @param st2
     * @param st3
     */
    TbfStartingTime(ITS_OCTET st1 = 0, 
                 ITS_OCTET st2 = 0,
                 ITS_OCTET st3 = 0)
    :    InfoElement(TFB_STARTING_TIME), t1(st1),t2(st2),t3(st3)
    {
    }

    /**
     * Set t1 Value
     */
    void
    SetT1(ITS_OCTET value)
    {
        t1 = value;
    }

    /**
     * Get t1 Value
     */
    ITS_OCTET
    GetT1()
    {
        return t1;
    }

    /**
     * Set t2 Value
     */
    void
    SetT2(ITS_OCTET value)
    {
        t2 = value;
    }

    /**
     * Get t2 Value
     */
    ITS_OCTET
    GetT2()
    {
        return t2;
    }

    /**
     * Set t3 Value
     */
    void
    SetT3(ITS_OCTET value)
    {
        t3 = value ;
    }

    /**
     * Get t3 Value
     */
    ITS_OCTET
    GetT3()
    {
        return t3;
    }

protected:
    /**
     * Constructor
     * @param buf
     * @param len
     */
    TbfStartingTime(const ITS_OCTET* buf, int& len);

    /**
     * Encode StartingTime Value
     */
    virtual void Encode(ITS_OCTET* buf, int& len) const;

    /**
     * Clone
     */
    InfoElement* 
    Clone() const
    {
        return new TbfStartingTime(*this);    
    }

    /**
     * Print function that print all IEs
     * @param: (std::ostream&) out
     */
    virtual void Print(std::ostream& out) const;

private :

    ITS_OCTET t1, t2, t3;

};

} // end of namespace ie
} // end of namespace bsslap

#endif // !BSSLAP_IE_TBF_STARTING_TIME_H

