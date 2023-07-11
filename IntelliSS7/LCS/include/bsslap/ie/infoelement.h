/////////////////////////////////-/-C++-/-////////////////////////////////////
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
//  ID: $Id: infoelement.h,v 1.1.2.4 2010/03/26 11:47:11 rajeshak Exp $
//
//  LOG:$Log: infoelement.h,v $
//  LOG:Revision 1.1.2.4  2010/03/26 11:47:11  rajeshak
//  LOG:Renaming IE code for SERVING_CELL_IDENTITY to CELL_IDENTITY
//  LOG:
//  LOG:Revision 1.1.2.3  2010/03/23 05:40:44  rajeshak
//  LOG:Release-8 Codec changes.
//  LOG:
//  LOG:Revision 1.1.2.2  2010/03/19 11:41:02  rajeshak
//  LOG:Removing IntelliSS7 dependency from Codec
//  LOG:
//  LOG:Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//  LOG:Adding Codec files to LCS folder
//  LOG:
//  LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSLAP_IE_INFOELEMENT_H
#define BSSLAP_IE_INFOELEMENT_H

#include <iostream>
#include <codec_trace.h>
#include <codec_exception.h>

namespace bsslap
{

class Message;

namespace ie
{

/**
 * This abstract class defines the basic interface for BSSLAP
 * message's information elenments. All BSSLAP information elements 
 * are derived from this class.
 */
class InfoElement
{
    friend class bsslap::Message;

    /**
      * Print function to print out messages
      */
    friend std::ostream &operator<<(std::ostream &out, const InfoElement &);

public :
   /**
     * The following are BSSLAP message signaling elements code
     */
    enum Type
    {
        TIMING_ADVANCE          = 0x01U,
        HANDOVER_TYPE           = 0x08U,
        CELL_IDENTITY           = 0x09U,
       	STARTING_TIME           = 0x0AU,
        NEIGHBOR_CELL_IDENTITY  = 0x0BU,
        NEIGHBOR_STARTING_TIME  = 0x0CU,
        CHANNEL_DESCRIPTION     = 0x10U,
       	FREQUENCY_LIST          = 0x11U,
        HANDOVER_REFERENCE      = 0x12U,
        MS_POWER                = 0x13U,
        MEASUREMENT_REPORT      = 0x14U,
        DELTA_TIMER             = 0x15U,
        CAUSE                   = 0x18U,
        RRLP_FLAG               = 0x19U,
        RRLP_IE                 = 0x1BU,
        //TARGET_CELL_IDENTITY    = 0x1CU,
        LOCATION_AREA_CODE      = 0X1EU,
        CELL_IDENTITY_LIST      = 0X1CU,

        ENHANCED_MEASUREMENT_REPORT = 0x1DU,
        FREQUENCY_LIST_REL8     = 0x21U,
        MS_POWER_REL8           = 0x22U,
        DELTA_TIMER_REL8        = 0x23U,
        SERVING_CELL_IDENTITY_REL8 = 0x24U,
        ENCRYPTION_KEY          = 0x25U,
        CIPHER_MODE_SETTING     = 0x26U,
        CHANNEL_MODE            = 0x27U, 
        MULTIRATE_CONFIG        = 0x28U,
        POLLING_REPETITION      = 0x29U,
        PACKET_CHANNEL_DESC     = 0x2AU,
        TLLI                    = 0x2BU,
        TFI                     = 0x2CU,
        TFB_STARTING_TIME       = 0x2DU,
        POWERUP_STARTING_TIME   = 0x2EU
    };
    
    virtual ~InfoElement() {}

    Type GetID() const { return param_id; }

    virtual InfoElement* Clone() const = 0;
    
protected :

    /**
     * Constructor that determine the type of the IE.
     * @param id (Type)
     */
    InfoElement(Type id) 
    {
        param_id = id;
    }

    /**
     * Pure virtual function, all subclass will override
     * this function
     * @param buf
     * @param len
     */
    virtual void Encode(ITS_OCTET* buf, int& len) const = 0;

    /**
     * This Decode function is static function
     * @param buf
     * @param len
     * @return InfoElement pointer
     */
    static InfoElement* Decode(const ITS_OCTET* buf, int& len);

    /**
     * Print function that print all IEs
     * @param: (std::ostream&) out
     */
    virtual void Print(std::ostream&) const = 0;

protected :
    
    Type  param_id;
    ITS_OCTET	param_length;
};


std::ostream &operator<<(std::ostream &out, const InfoElement &);

} // end of namespace ie
} // end of namespcae bsslap


#endif //!BSSLAP_IE_INFOELEMENT_H




