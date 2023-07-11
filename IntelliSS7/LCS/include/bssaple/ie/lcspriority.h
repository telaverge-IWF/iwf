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
//   ID: $Id: lcspriority.h,v 1.1.2.3 2010/03/26 11:48:05 rajeshak Exp $
//
//   LOG: $Log: lcspriority.h,v $
//   LOG: Revision 1.1.2.3  2010/03/26 11:48:05  rajeshak
//   LOG: GetHexBuff function signature changes
//   LOG:
//   LOG: Revision 1.1.2.2  2010/03/25 06:32:32  rajeshak
//   LOG: API to get the Hex dump after encode/decode (for TDR).
//   LOG:
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_LCSPRIORITY_H
#define BSSAPLE_IE_LCSPRIORITY_H 


#include <bssaple/ie/infoelement.h>


namespace bssaple
{

namespace ie
{

static void TEST_LCS_PRIORITY(void);

/**
 * LCSPriority defines the priority level of a location request.
 */
class LCSPriority : public InfoElement
{
public:
    enum Priority
    {
        HIGHEST_PRIORITY    =   0x00,
        NORMAL_PRIORITY     =   0x01
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
    LCSPriority():InfoElement(InfoElement::LCS_PRIORITY,sizeof(ITS_OCTET))
    {}

    /**
    * Destructor 
    */
    ~LCSPriority()
    {}

    /**
     *  Purpose: Set Priority value
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetPriority (Priority val)
    {
        priority &= ~0x01U;
        priority |= val & 0x01U;
    }

    /**
     *  Purpose: Get Priority value
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      Priority value
     *
     */
    Priority GetPriority () const
    {
        return (LCSPriority::Priority)priority;
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

    virtual void PrintIE(std::ostream &) const;

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
    LCSPriority(const ITS_OCTET *buf,int len);

    virtual InfoElement *Clone() const
    {
        return new LCSPriority(*this);
    }

private: 
    ITS_OCTET hexBuff[10];  
    ITS_OCTET priority;

    friend class InfoElement;
    friend  void TEST_LCS_PRIORITY(void);
};

} // namespace ie    
} // namespace bssaple    


#endif

