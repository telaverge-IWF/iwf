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
//   ID: $Id: returnerrorrequest.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: returnerrorrequest.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_RETURNERRORREQUEST_H
#define BSSAPLE_IE_RETURNERRORREQUEST_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{

namespace ie
{

static void  TEST_RETURN_ERROR_REQUEST(void);

/**
 * ReturnErrorRequest indicates a request from the source of a BSSMAP-LE
 * connectionless information message for an error response if the message
 * cannot be delivered to its final destination.
 */
class ReturnErrorRequest : public InfoElement 
{

public:

    enum ReturnErrorType
    {
        RETURN_APDU_OR_FIRST_SEGMENT_OF_APDU    =   0x00
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
    ReturnErrorRequest()
    : InfoElement(InfoElement::RETURN_ERROR_REQUEST, sizeof(ITS_OCTET))
    {}

    /**
    *     Destructor 
    */
    ~ReturnErrorRequest()
    {}

    /**
     *  Purpose: Set ReturnErrorType
     *
     *  Input Parameters:
     *      errorType - ReturnErrorType type
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetReturnErrorType (ReturnErrorType errorType)
    {
        returnErrorType = errorType;
    }


    /**
     *  Purpose: Return the Return error type of Return Error Request
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      error type of Return Error Request
     *
     */
    ReturnErrorType  GetReturnErrorType () const
    {
        return (ReturnErrorType)returnErrorType;
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
    ReturnErrorRequest(const ITS_OCTET *buf,int len);

    virtual InfoElement *Clone() const
    {
        return new ReturnErrorRequest(*this);
    }

private: 

    ITS_OCTET returnErrorType;

    /**
    *     Assignment Operation 
    */
    ReturnErrorRequest & operator=(const ReturnErrorRequest &right);
    friend class InfoElement;
    friend void  TEST_RETURN_ERROR_REQUEST(void);
};

}
}

#endif

