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
//   ID: $Id: signalingpointcode.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: signalingpointcode.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_SIGNALINGPOINTCODE_H
#define BSSAPLE_IE_SIGNALINGPOINTCODE_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{

namespace ie
{

void static TEST_SignalingPointCode(void);

/**
 * SignalingPointCode is a variable length information element providing that
 * provides the signaling point code of a network element.
 */
class SignalingPointCode : public InfoElement 
{
public:

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
    SignalingPointCode()
    :sigpc(0),InfoElement(InfoElement::SIGNALING_POINT_CODE,0)
    {}

    /**
    * Destructor 
    */
    ~SignalingPointCode()
    {}

    /**
     *  Purpose: Set the signaling point code
     *
     *  Input Parameters:
     *      pc - value of 14 bit signaling point code
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *  Note:
     *      Use this Set function to set 14 bit ITU code,
     *
     */
    void SetPointCode14Bit (ITS_USHORT pc)
    {
        sigpc = pc;
        length = sizeof(ITS_USHORT);
    }

    /**
     *  Purpose: Set the signaling point code
     *
     *  Input Parameters:
     *      pc - value of 24 bit signaling point code
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *  Note:
     *      Use this Set function to set 24 bit ANSI structured code.
     *
     */
    void SetPointCode24Bit (ITS_UINT pc)
    {
        sigpc = pc;
        length = sizeof(ITS_OCTET) * 3;
    }

    /**
     *  Purpose: Get the signaling point code
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *       the signaling point code
     *
     */
    ITS_UINT GetPointCode () const
    {
        return sigpc;
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
        return new SignalingPointCode(*this);
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
    SignalingPointCode(const ITS_OCTET *buf,int len);

private: 
    ITS_UINT sigpc;

    /**
     * Assignment operator
     */
    SignalingPointCode & operator=(const SignalingPointCode &right);

    friend class InfoElement;
    friend void TEST_SignalingPointCode(void);
};




} // namespace ie    
} // namespace bssaple    



#endif

