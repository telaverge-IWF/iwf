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
//   ID: $Id: lmuconnectionrelease.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: lmuconnectionrelease.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_LMUCONNECTIONRELEASE_H
#define BSSAPLE_LMUCONNECTIONRELEASE_H 


#include <bssaple/message.h>


namespace bssaple	 {

/**
*    Class: LMUConnectionReleas
*	This message is sent to release a signaling connection
*	between an LMU and an SMLC. The message can be sent from
*	an SMLC to an MSC and from an MSC to an SMLC.
*/
class LMUConnectionRelease : public Message  
{

public:
    /**
    * Constructors 
    */
    LMUConnectionRelease():Message(LMU_CONNECTION_RELEASE)
    {}

    /**
    * Destructor 
    */
    virtual ~LMUConnectionRelease()
    {}

protected:

    /**
     *  Purpose:
     *      This method checks to see if all mandatory parameters
     *    have been included. This method is called as part of the
     *    Encode() procedure.
     *
     *  Input Paramenter:
     *
     *  Output parameters:
     *
     *  Throws Exception:
     *      Throws MissingParameterException in case unsuccessful
     *
     */
    virtual void CheckForMandatoryParams() const;

    /**
     *  Purpose:This constructor Decodes the buffer
     *
     *  Input Parameters:
     *      buf - encoded octet string
     *      len - length of octet string
     *
     *  Output parameters:
     *
     *
     *  Throws Exception:
     *      Throws DecodeException in case unsuccessful
     *
     */
    LMUConnectionRelease::LMUConnectionRelease(const ITS_OCTET *buf,int len);

    /**
    * Assignment Operation 
    */
    LMUConnectionRelease & operator=(const LMUConnectionRelease &right);

    typedef ParameterChecker<Message::ElementMap,
                                        ie::InfoElement,1,0> Checker;

    void GetMandatoryParams(ie::InfoElement::Type* mand,int &index) const
    {
        mand[0] = mandatory[0];
        index = 1;
    }
private:

    static Checker checker;
    static ie::InfoElement::Type mandatory[];

    friend class Message;

private: 

};


} // namespace bssaple	


#endif
