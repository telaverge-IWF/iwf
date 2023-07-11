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
//  ID: $Id: rrlpflag.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//  LOG:$Log: rrlpflag.h,v $
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_IE_RRLPFLAG_H
#define BSSLAP_IE_RRLPFLAG_H

#include <bsslap/ie/infoelement.h>

namespace bsslap 
{
namespace ie 
{

class RRLPFlag : public InfoElement
{
    friend class InfoElement;
public:

    /**
     * Constructor
     * @param 
     */
    RRLPFlag(ITS_BOOLEAN f = ITS_FALSE)
    : InfoElement(RRLP_FLAG), flag(f)
    {
    }

    /**
     * Set  RRLPFlag
     * @param value
     */
    void SetRRLPFlag(ITS_BOOLEAN value)
    {
         flag = value;
    }

    /**
     * Get RRLPFlag
     * @return flag
     */
    ITS_BOOLEAN GetRRLPFlag() const
    {
        return flag;
    }

    /**
     * Print function that print all IEs
     * @param: (std::ostream&) out
     */
    virtual void Print(std::ostream& out) const;

protected:

    /**
     * Constructor : performs as decoder
     * @param buf
     * @param len
     */
    RRLPFlag(const ITS_OCTET* buf, int& len);

    /**
     * Encode RRLP flag ie
     * @param buf
     * @param len
     */
    virtual void Encode(ITS_OCTET* buf, int& len) const;

    /**
     * Clone
     */
    InfoElement* Clone() const
    {
        return new RRLPFlag(*this);
    }

private:

    ITS_BOOLEAN flag;
};

} // ie namespace
} // bsslap namespace

#endif // !BSSLAP_IE_RRLPFLAG_H

