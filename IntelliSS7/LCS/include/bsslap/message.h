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
//  ID: $Id: message.h,v 1.1.2.3 2010/03/31 05:47:14 rajeshak Exp $
//
//  LOG:$Log: message.h,v $
//  LOG:Revision 1.1.2.3  2010/03/31 05:47:14  rajeshak
//  LOG:ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
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

#ifndef BSSLAP_MESSAGE_H
#define BSSLAP_MESSAGE_H

#include <map>			// STL header
#include <iostream>
#include <bsslap/ie/infoelement.h> // BSSLAP IE API header

namespace bsslap
{

/**
 * This abstract class defines the basic interface for BSSLAP Messages. 
 * All BSSLAP Message types are derived from this class
 */
class Message
{
public:
	/**
	 * Define the Message Type ID
	 */
	enum Type
	{
		TA_REQUEST				= 0x01U,	
		TA_RESPONSE				= 0x02U,
		TOA_REQUEST				= 0x03U,
		TOA_RESPONSE			= 0x04U,
		REJECT					= 0x0AU,
		RESET					= 0x0BU,
		ABORT					= 0x0CU,
		TA_LAYER3				= 0x0DU,
		MS_POSITION_COMMAND		= 0x0FU,
		MS_POSITION_RESPONSE	= 0x10U
	};

    /**
     * Copy Constructor
     */
    Message(const Message& msg);

    /**
	 * Destructor for destroy object
	 */
    virtual ~Message();
    
    /**
     * This pure virtual function encodes a BSSLAP_Message into an octet 
	 * array. If the buffer is successfully encoded, CODEC_SUCCESS is 
	 * returned, any other return value indicates an error.
	 * 
	 * @param:	buf - buffer contains data
	 * @param:	len - length of the data
     */
    virtual void Encode(ITS_OCTET * buf, int& len) const;

    /**
     * This method returns the Message type for this Message object.
     * @return msgType
     */
    const Type GetType() const 
	{ 
		return _msgType; 
	}

    /**
     * This method add the specified information element
     * which is used in the Messages
     * @param ieID
     * @param ie
     * @param clone(default as false)
     */
    void AddIE (ie::InfoElement * ie, bool clone  = false );
	
    /**
     * This method find the InfoElement in the map
     * @param ieID
     * @return pointer of the tha map second element
     */
    const ie::InfoElement* FindIE(ie::InfoElement::Type ieID) const;    

	/**
     * This static functin decodes a BSSLAP Message into an octet array. 
     * If the buffer is successfully decoded, CODEC_SUCCESS is returned, 
     * any other return value indicates an error.
     * This is a static method
	 *
	 * @param buf
	 * @param len
	 * @return pointer of the message
     */
    static Message *Decode( ITS_OCTET* buf, int& len);

    /**
     * Creates a duplicate of this message.
     */
    virtual Message *Clone() const = 0;	

protected :

	/**
	 * Constructor
	 *
	 * @param: msgType - input Message type
	 *
	 */
    Message(Type msgType)
    : _msgType(msgType)
    {}

    /**
     * This function is to call concrete IE decode
     * function
     * @param buf
     * @param len
     */
    void DecodeIEs(const ITS_OCTET* buf, int& len);
    
    /**
     * This is utility function provide service for destructor
     * Assignment operator function and decode function
     * for clear garbage IEs 
     */
    void cleanup()
    {
        Message::InfoElementMap::const_iterator it;

        for (it = ies.begin(); it != ies.end(); ++it)
        {
            delete it->second;
        }
        ies.clear();
    }

    /**
     * This pure virtual function, which is specific for ever Message, 
	 * checks to see if all mandatory parameters have been included. 
	 * This method is called as part of the Encode() procedure.
	 * 
	 * @param: None
     */
    virtual void CheckForMandatoryParam() const = 0;

    /**
     * This function will get 
     * mandatory info elements and its size
     */
    virtual void GetMandatoryParams(ie::InfoElement::Type*,
                                           int& ) const = 0;

	/**
	 * Print function to print out messages
	 */
    friend std::ostream &operator<<(std::ostream &out, const Message &);

protected :
    typedef std::map<ie::InfoElement::Type, ie::InfoElement*> InfoElementMap;
    InfoElementMap 	ies;

private:
    Type _msgType;
    Message &operator=(const Message& msg);
};

std::ostream &operator<<(std::ostream &out, const Message &);

} // end of bsslap namespace

#endif // !BSSLAP_MESSAGE_H

