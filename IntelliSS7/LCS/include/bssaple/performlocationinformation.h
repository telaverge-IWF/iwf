//////////////////////////////////-*-h-*-/////////////////////////////////////
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
//   ID: $Id: performlocationinformation.h,v 1.1.2.1 2010/03/23 05:37:42 rajeshak Exp $
//
//  LOG: $Log: performlocationinformation.h,v $
//  LOG: Revision 1.1.2.1  2010/03/23 05:37:42  rajeshak
//  LOG: Release-8 Codec changes.
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////
#ident "$Id: performlocationinformation.h,v 1.1.2.1 2010/03/23 05:37:42 rajeshak Exp $"

#ifndef BSSAPLE_PERFORMLOCATIONINFORMATION_H
#define BSSAPLE_PERFORMLOCATIONINFORMATION_H 

#include <bssaple/message.h>

namespace bssaple
{

/**
 * The Perform Location Information procedure is applicable to the Lb interface. It enables an SMLC to be informed by
 * the BSS when a target MS in the PS domain (A/Gb-mode) has changed serving cell. The procedure is only valid while a
 *location request procedure for the target MS is ongoing. The procedure makes use of SCCP connection oriented
 * signaling on the Lb interface and uses the same SCCP connection as the location request procedure for the particular
 * target MS.
 */
class PerformLocationInformation : public Message  
{
    friend class Message; 

public:
    /**
     * Constructors 
     */
    PerformLocationInformation()
    : Message(PERFORM_LOCATION_INFORMATION)
    {}

protected:

    typedef ParameterChecker<Message::ElementMap,
                                        ie::InfoElement,1,1> Checker;

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
    PerformLocationInformation(const ITS_OCTET *buf, int len);

    void GetMandatoryParams(ie::InfoElement::Type* mand,int &index) const
    {
        memcpy(mand,mandatory,sizeof(ie::InfoElement::Type)*1);
        index = 1;
    }
private: 

    static Checker checker;
    static ie::InfoElement::Type mandatory[];
    static ie::InfoElement::Type optional[];

    PerformLocationInformation & operator=(const PerformLocationInformation &right);
};

} // namespace bssaple


#endif

