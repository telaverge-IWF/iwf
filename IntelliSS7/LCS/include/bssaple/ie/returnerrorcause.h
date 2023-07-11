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
//   ID: $Id: returnerrorcause.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: returnerrorcause.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_RETURNERRORCAUSE_H
#define BSSAPLE_IE_RETURNERRORCAUSE_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{

namespace ie
{

void TEST_RETURN_ERROR_CAUSE(void);

/**
 * ReturnErrorCause provides the reason for unsuccessful delivery of a
 * BSSMAP-LE Connectionless Information message to its final destination.
 */
class ReturnErrorCause: public InfoElement
{
public:
    enum Value
    {
        UNSPECIFIED                 =   0x00,             
        SYSTEMFAILURE               =   0x01,
        PROTOCOLERROR               =   0x02,
        DESTINATIONUNKNOWN          =   0x03,
        DESTINATIONUNREACHABLE      =   0x04,
        CONGESTION                  =   0x05,
        UNSPECIFIC_TO_PROTOCOL      =   0xFF
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
    ReturnErrorCause()
    : InfoElement(InfoElement::RETURN_ERROR_CAUSE,sizeof(ITS_OCTET))
    {}

    /**
    *     Destructor 
    */
    ~ReturnErrorCause()
    {}

    /**
     *  Purpose: Set  CauseValue 
     *
     *  Input Parameters:
     *      val - Value type
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
        cause = val;
    }

    /**
     *  Purpose: Return the Cause Value of Return Error Casue
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      Cause Value of Return Error Casue
     *
     */
    Value  GetCauseValue () const
    {
        return (ReturnErrorCause::Value)cause;
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
     *      buf - a pointer to the buffer to encode into.
     *      len - returns the length of encoded buffer.
     *
     *  Throws Exception:
     *      Throws EncodingException in case unsuccessful
     */
     virtual int Encode (ITS_OCTET* buf, int& len) const;

    virtual InfoElement *Clone() const
    {
        return new ReturnErrorCause(*this);
    }

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

    ReturnErrorCause(const ITS_OCTET *buf,int len);

private: 

    ITS_OCTET cause;

    /**
    *     Assignment Operation 
    */
    ReturnErrorCause & operator=(const ReturnErrorCause &right);

    friend class InfoElement;
    friend void TEST_RETURN_ERROR_CAUSE(void);
};


} // namespace ie
} // namespace bssaple


#endif

