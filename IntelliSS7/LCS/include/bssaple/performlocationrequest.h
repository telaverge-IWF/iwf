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
//   ID: $Id: performlocationrequest.h,v 1.1.2.3 2010/04/21 06:30:56 rajeshak Exp $
//
//   LOG: $Log: performlocationrequest.h,v $
//   LOG: Revision 1.1.2.3  2010/04/21 06:30:56  rajeshak
//   LOG: Code Review comments
//   LOG:
//   LOG: Revision 1.1.2.2  2010/03/23 05:37:42  rajeshak
//   LOG: Release-8 Codec changes.
//   LOG:
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_PERFORMLOCATIONREQUEST_H
#define BSSAPLE_PERFORMLOCATIONREQUEST_H 

#include <bssaple/message.h>

namespace bssaple
{

/**
 * A PerformLocationRequest message is sent to request a location estimate for
 * a target MS and contains sufficient information to enable location according
 * to the required QoS using any positioning method supported by the PLMN and,
 * where necessary, MS. The message is also used to request LCS assistance data
 * transfer to an MS or request a deciphering keys for LCS broadcast assistance
 * data The message can be sent from the BSC to the SMLC and from the MSC to
 * the SMLC.
 */
class PerformLocationRequest : public Message  
{
    friend class Message; 

public:
    /**
     * Constructors 
     */
    PerformLocationRequest()
    : Message(PERFORM_LOCATION_REQUEST)
    {}

protected:

    typedef ParameterChecker<Message::ElementMap,
                                        ie::InfoElement,2,14> Checker;

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
    PerformLocationRequest(const ITS_OCTET *buf, int len);

    void GetMandatoryParams(ie::InfoElement::Type* mand,int &index) const
    {
        memcpy(mand,mandatory,sizeof(ie::InfoElement::Type)*2);
        index = 2;
    }
private: 

    static Checker checker;
    static ie::InfoElement::Type mandatory[];
    static ie::InfoElement::Type optional[];

    PerformLocationRequest & operator=(const PerformLocationRequest &right);
};

} // namespace bssaple


#endif

