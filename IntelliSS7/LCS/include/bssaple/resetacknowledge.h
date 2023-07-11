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
//   ID: $Id: resetacknowledge.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: resetacknowledge.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_RESETACKNOWLEDGE_H
#define BSSAPLE_RESETACKNOWLEDGE_H 

#include <bssaple/message.h>

namespace bssaple
{

/**
 * A ResetAcknowledge message is sent in response to a Reset message to
 * indicate that references and resources associated with LMU connections and
 * location service transactions towards the entity sending the Reset have been
 * released. The message may be sent from an SMLC to an MSC or BSC and from an
 * MSC or BSC to an SMLC.
 *
 * This message is sent as a connectionless SCCP message.
 */
class ResetAcknowledge : public Message  
{
public:
    /**
     * Constructors 
     */
    ResetAcknowledge()
    : Message(RESET_ACKNOWLEDGE)
    {}

    /**
     * Equality Operations 
     */
    int operator==(const ResetAcknowledge &right) const;

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

    void GetMandatoryParams(ie::InfoElement::Type* mand,int &index) const
    {
        mand = 0;
        index = 0;
    }
private:
    ResetAcknowledge & operator=(const ResetAcknowledge &right);

    friend class Message;
};

} // namespace bssaple

#endif

