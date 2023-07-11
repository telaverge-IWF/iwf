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
//   ID: $Id: dtapmessage.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: dtapmessage.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_DTAPMESSAGE_H
#define BSSAPLE_DTAPMESSAGE_H

#include <bssaple/message.h>


namespace bssaple
{


/**
 * Class DTAPMessage defines the basic interface for DTAP-LE messages. All
 * DTAP-LE messages are derived from this class. This is an abstract class.
 */
class DTAPMessage : public Message
{

public:

    enum Type
    {
        RELEASE_COMPLETE                = 0x21,
        FACILITY                        = 0x31,
        REGISTER                        = 0x32
    };

    enum ControlChannelId 
    {
        NOT_SPECIFIED       =   0x00,
        FACCH_OR_SDCCH      =   0x10,
        SACCH               =   0x11
    };

    enum SAPI
    {
        SIGNALLING_INFORMATION  =   0x00,
        SHORT_MESSAGES          =   0x11
    };
    
    enum ProtocolDiscriminator
    {
        LOCATION_SERVICES = 0xC
    };

    enum TransactionFlag 
    {
        ORIGINATOR      = 0x00,
        NOT_ORIGINATOR  = 0x01
    };
    
        
        
    DTAPMessage(Type type)
    :Message((Message::Type)type,Message::DTAP_LE_ID),tId_protDisc(0)
    {}

    ~DTAPMessage()
    {}

    /**
     * Copy constructor
     */
    DTAPMessage(const DTAPMessage &right);

    /**
     *  Purpose: Sets the ProtocolDiscriminator
     *
     *  Input Parameters:
     *      type - is type of ProtocolDiscriminator
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetProtocolDiscriminator(ProtocolDiscriminator type)
    {
        tId_protDisc |= ((ITS_OCTET)type) & 0x0FU;
    }
    
    /**
     *  Purpose: Get the ProtocolDiscriminator
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      ProtocolDiscriminator
     *
     */
    ProtocolDiscriminator GetProtocolDiscriminator(void) const
    {
        return (ProtocolDiscriminator)(tId_protDisc & 0x0FU );
    }

    /**
     *  Purpose: Sets the TransactionFlag 
     *
     *  Input Parameters:
     *      flag - is TransactionFlag
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */ 
    void SetTransactionFlag(TransactionFlag flag)
    {
        tId_protDisc |= ((ITS_OCTET)flag << 7) & 0x80;
    }

    /**
     *  Purpose: Get the TransactionFlag
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      TransactionFlag
     *
     */
    TransactionFlag GetTransactionFlag(void) const
    {
        return (TransactionFlag)((tId_protDisc >> 7) & 0x01U);
    }

    /**
     *  Purpose: Sets TransactionId
     *
     *  Input Parameters:
     *      tid - is TransactionId
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetTransactionId(int tid)
    {
        tId_protDisc |= (tid << 4 ) & 0xF0U;
    }

    /**
     *  Purpose: Get the TransactionId
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      TransactionId
     *
     */    
    int GetTransactionId(void) const
    {
        return (tId_protDisc >> 4 ) & 0x07U;
    }

    /**
     *  Purpose: Sets the ControlChannelId
     *
     *  Input Parameters:
     *      id - is ControlChannelId
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetControlChannelId(ControlChannelId id)
    {
        channelId = id;
    }

    /**
     *  Purpose: Get ControlChannelId
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      ControlChannelId
     *
     */
    ControlChannelId GetControlChannelId(void) const
    {
        return channelId;
    }

    /**
     *  Purpose: Sets the SAPI
     *
     *  Input Parameters:
     *      _sapi - is SAPI
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetSAPI(SAPI _sapi)
    {
        sapi = _sapi;
    }

    /**
     *  Purpose: Get the SAPI
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      SAPI
     *
     */
    SAPI GetSAPI(void) const
    {
        return sapi;
    }
    

protected:

    ITS_OCTET tId_protDisc;
    ControlChannelId channelId;
    SAPI sapi;

    /**
     *  Purpose: is to Decode the DTAP-LE message
     *
     *  Input Parameters:
     *      buf -  is encoded message.
     *      len -  is length of buf.
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      decoded DTAP-LE message object
     *
     */
    static DTAPMessage *DecodeDTAPMessage(const ITS_OCTET *buf,int len);

    /**
     *  Purpose: Encode the DTAP-Le message.
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *      buf -  is the buffer the message is encoded into.
     *      len -  is length of the encoded buf.
     *
     *  Returns:
     *
     *
     */
    void EncodeDTAPMessage(ITS_OCTET *buf,int& len) const;

    /**
     *  Purpose: prints the contents of the of message.
     *
     *
     *
     */
     void PrintMsg(std::ostream &) const ;

private:

    DTAPMessage &operator=(const DTAPMessage &right);
    friend class Message;
};

}

#endif

