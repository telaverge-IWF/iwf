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
//   ID: $Id: connectionorientedinformation.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: connectionorientedinformation.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_CONNECTIONORIENTEDINFORMATION_H
#define BSSAPLE_CONNECTIONORIENTEDINFORMATION_H

#include <bssaple/message.h>


namespace bssaple
{

/**
 * A ConnectionOrientedInformation message is sent in association with an
 * existing signaling connection between an SMLC and another enity to transfer
 * information between the SMLC and other entity belonging to a higher level
 * protocol. The message can be sent from an SMLC to an MSC, from an MSC to an
 * SMLC, from a BSC to an SMLC and from an SMLC to a BSC.
 */
class ConnectionOrientedInformation : public Message
{
public:
    /**
     * Constructs an empty ConnectionOrientedInformation message.
     */
    ConnectionOrientedInformation()
    : Message(CONNECTION_ORIENTED_INFORMATION)
    {}

    /**
     * Equality Operations
     */
    int operator==(const ConnectionOrientedInformation &right) const;

protected:
    typedef ParameterChecker<Message::ElementMap,
                                   ie::InfoElement,1,1> Checker;

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
    ConnectionOrientedInformation(const ITS_OCTET *, int);

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


    virtual void GetMandatoryParams(ie::InfoElement::Type* mand,
                                                        int &index) const
    {
        mand[0] = mandatory[0];
        index = 1;
    }

private:
    static Checker checker;
    static ie::InfoElement::Type mandatory[];
    static ie::InfoElement::Type optional[];

    friend class Message;
ConnectionOrientedInformation &operator=(const ConnectionOrientedInformation &);
};


} // namespace bssaple

#endif

