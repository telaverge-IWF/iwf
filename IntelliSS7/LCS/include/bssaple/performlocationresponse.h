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
//   ID: $Id: performlocationresponse.h,v 1.1.2.2 2010/03/23 05:37:42 rajeshak Exp $
//
//   LOG: $Log: performlocationresponse.h,v $
//   LOG: Revision 1.1.2.2  2010/03/23 05:37:42  rajeshak
//   LOG: Release-8 Codec changes.
//   LOG:
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_PERFORMLOCATIONRESPONSE_H
#define BSSAPLE_PERFORMLOCATIONRESPONSE_H 

#include <bssaple/message.h>

namespace bssaple
{

/**
 * A PerformLocationResponse message is sent in response to a BSSMAP-LE Perform
 * Location Request to return a successful location estimate for a target MS or
 * to indicate some failure in obtaining this. The message is also sent in
 * response to a BSSMAP-LE Perform Location Request to return deciphering keys
 * or an indication that LCS assistance data has been successfully delivered to
 * an MS. The message can be sent from the SMLC to the BSC and from the SMLC to
 * the MSC.
 */
class PerformLocationResponse : public Message  
{
public:
    /**
    * Constructors 
    */
    PerformLocationResponse()
    :Message(PERFORM_LOCATION_RESPONSE)
    {}

    /**
    * Equality Operations 
    */
    int operator==(const PerformLocationResponse &right) const;

protected:
    typedef ParameterChecker<Message::ElementMap,
                                          ie::InfoElement,0,6> Checker ;

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
    PerformLocationResponse(const ITS_OCTET*,int);

    void GetMandatoryParams(ie::InfoElement::Type* mand,int &index) const
    {
        mand = 0;
        index = 0;
    }
private:

    static Checker checker;
    static ie::InfoElement::Type optional[];

    PerformLocationResponse & operator=(const PerformLocationResponse &right);

    friend class Message; 
};


} 


#endif

