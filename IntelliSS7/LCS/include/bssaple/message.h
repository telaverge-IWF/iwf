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
//   ID: $Id: message.h,v 1.1.2.3 2010/03/23 05:37:42 rajeshak Exp $
//
//   LOG: $Log: message.h,v $
//   LOG: Revision 1.1.2.3  2010/03/23 05:37:42  rajeshak
//   LOG: Release-8 Codec changes.
//   LOG:
//   LOG: Revision 1.1.2.2  2010/03/19 11:41:02  rajeshak
//   LOG: Removing IntelliSS7 dependency from Codec
//   LOG:
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_MESSAGE_H
#define BSSAPLE_MESSAGE_H 

#include <map>

#include <bssaple/ie/infoelement.h>
#include <codec_param_checker.h>
#include <codec_trace.h>


namespace bssaple
{

/**
 * Class Message defines the basic interface for BSSMAP-LE messages. All
 * BSSMAP-LE messages are derived from this class. This is an abstract class.
 */
class Message 
{
public:
    /**
     * BSSAPM-LE Protocol ID to be place in the SCCP User Data
     */
    enum BSSAPLEProtocolIdentity
    {
        BSSMAP_LE_ID = 0,
        DTAP_LE_ID = 1
    };

    /**
     * Message Types
     */
    enum Type
    {
        PERFORM_LOCATION_REQUEST        = 0x2B,
        PERFORM_LOCATION_RESPONSE       = 0x2D,
        PERFORM_LOCATION_ABORT          = 0x2E,
        PERFORM_LOCATION_INFORMATION    = 0x2F,

        LMU_CONNECTION_REQUEST          = 0x01,
        LMU_CONNECTION_ACCEPT           = 0X02,
        LMU_CONNECTION_REJECT           = 0x03,
        LMU_CONNECTION_RELEASE          = 0x04,

        CONNECTION_ORIENTED_INFORMATION = 0x2A,
        CONNECTIONLESS_INFORMATION      = 0x3A,

        RESET                           = 0x30,
        RESET_ACKNOWLEDGE               = 0x31

    };

    /**
     * Copy constructor
     */
    Message(const Message &right);

    /**
     * Virtual destructor
     */
    virtual ~Message();

    /**
     *  Operation: Encode
     *  Purpose:
     *      This method Encodes a single Message.  
     *
     *  Input Parameters:
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into.
     *      len - return the total length of ecoded IE.
     *
     *  Exception.
     *      Throws EncodeException in case unsuccessful.
     */
    void Encode(ITS_OCTET* buf, int &len) const;

    /**
     * Returns the type of this message.
     */
    Type GetType() const
    {
        return msgType;
    }

    /**
     *  Purpose:
     *      This method decodes an ITS_OCTET array and returns a dynamically 
     *      created Message object. The calling function is responsible for
     *      deleting this object after it no longer needs it.
     *
     *  Input Parameters:
     *      buf - a pointer to the buffer to encode into.
     *      len - the length of the encoded buffer.
     *
     *  Output Parameters:
     *
     *  Return Value:
     *      Message *,It returns decoded message object.
     *
     *  Exception:
     *      If decoding fails, a DecodeException is thrown.
     */
    static Message *Decode(const ITS_OCTET* buf, int len);

    /**
     *  Purpose:
     *      Adds an InfoElement into this message.
     *
     *  Input Parameters:
     *      ele -Information Element to add .
     *      clone -if its true it will create new cpoy and then add.
     *
     *  ReturnValue:
     *
     */
    void AddIE(const ie::InfoElement *ele, bool clone = false);

    /**
     *  Purpose:
     *      Searches for an InfoElement in this message that
     *      matches the given type.
     *
     *  Input Parameters:
     *      InfoElement::Type type of IE
     *
     *  RetrunValue:
     *      InfoElement *,returns IE object it present else 
     *      returns NULL.
     *
     */
    const ie::InfoElement *FindIE(ie::InfoElement::Type type) const;

protected:

    typedef std::map<ie::InfoElement::Type, const ie::InfoElement*> ElementMap;
    typedef ElementMap::const_iterator IE_iterator;

    /**
     * Constructor. The message type must be given by the derived class.
     */
    Message(Type type,BSSAPLEProtocolIdentity protId = BSSMAP_LE_ID)
    : msgType(type),protocolId(protId)
    {}

    /**
     *  Operation: CheckForMandatoryParams
     *
     *  Purpose:
     *    This method checks to see if all mandatory parameters
     *    have been included. This method is called as part of the
     *    Encode() procedure.
     *    This method throws exception incase of missing mandatory 
     *    parameters in the message.
     *
     *  Throws Exception:
     *      This method throws MissingMandatoryArgumnets,
     *      IllegalArgumentException Exception.
     *
     */
     virtual void CheckForMandatoryParams() const = 0;

     /**
      * Purpose:
      *     Returns the number of mandatory paramenter 
      * 
      * Input Parameters:
      *
      * Output Parameter:
      *     mand - mandatory parameter list.
      *     index - index of the array.
      *
      */
     virtual void GetMandatoryParams(ie::InfoElement::Type* mand,
                                                    int &index) const=0;

    /**
     *  Data member msgType
     */
     Type msgType;

    /**
     *  ElementMap is Hashtable to store all the IEs.
     *
     */
     ElementMap ies;

    /**
     *  Purpose:
     *      This method decodes a single Message.
     *      
     *  Input Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded buffer 
     *
     *  Output Parameters:
     *
     *  Return Value:
     *
     */
     void DecodeIE(const ITS_OCTET *buf, int len);

    /**
     *  Purpose:
     *      Prints all the IEs inside the message.
     */
     void PrintMsg(std::ostream &) const;

private:

    BSSAPLEProtocolIdentity protocolId;
    friend std::ostream &operator<<(std::ostream &, const Message &);
    Message &operator=(const Message &right);
};

inline std::ostream &operator<<(std::ostream &out, const Message &msg)
{
    msg.PrintMsg(out);
    return out;
}


} // namespace bssaple    



#endif

