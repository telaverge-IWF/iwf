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
//   ID: $Id: apdu.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: apdu.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSAPLE_IE_APDU_H
#define BSSAPLE_IE_APDU_H 


#include <bssaple/ie/infoelement.h>

#define MAX_APDU_LEN  251

namespace bssaple
{
namespace ie
{

static void TEST_APDU(void);

/**
 * APDU is a variable length information element that conveys an embedded
 * message or message segment associated with a higher level protocol.
 */
class APDU : public InfoElement  
{
public:
    /**
     * Protocol declarations
     */
    enum ProtocolId
    {
        PROTOCOL_ID_BSSLAP = 0x01,
        PROTOCOL_ID_LLP    = 0x02,
        PROTOCOL_ID_SMLCPP = 0x03
    }; 

    /**
     * This Constructor initializes the length,for fixed length fields
     */
    APDU():InfoElement(InfoElement::APDU,sizeof(ITS_OCTET))
    {}
    

    /**
     * Destructor
     */
    ~APDU()
    {}

    /**
     *  Purpose:
     *      To set the ProtocolId of embeded message.
     *
     *  Input Parameters:
     *         val - ProtocolId
     *
     *  Output parameters
     *
     */
    void SetProtocolID (ProtocolId val)
    {
        protocolID = val & 0x7F;
    }

   /**
     *  Purpose:
     *      To get the protocol Id of embeded message.
     *
     *  Input Parameters:
     *      
     *
     *  Output parameters
     *
     *  Returns:
     *      value of ProtocolId
     *
     */
    ProtocolId GetProtocolID () const
    {
        return (ProtocolId)protocolID;
    }

   /**
     *  Purpose:
     *      To set the data(embeded message)
     *
     *   Input Parameters:
     *      lapdata - data is octet string.
     *      len     - length of octet string.
     *   
     *
     *  Output parameters
     *
     */
    void SetData (ITS_OCTET* lapdata, int len)
    {
        length = sizeof(ITS_OCTET);//protocolID
        length += len;
        memcpy(data,lapdata,len);
    }

   /**
     *  Purpose:
     *      To get the data(embeded message)
     *
     *  Input Parameters:
     *
     *  Output parameters:
     *      lapdata  - data in octet string.
     *      len     - length of octet string.
     */
    void GetData (ITS_OCTET* lapdata, int& len) const
    {
        len = length - sizeof(ITS_OCTET);
        memcpy(lapdata,data,len);
    }


protected:

    virtual void PrintIE(std::ostream &) const;

    /**
     *  Purpose:
     *      This method Enocde the IEs in to the buf argument.
     * 
     *  Input Parameters:
     *      buf - a pointer to the buffer to encode into
     *  
     *  Output Parameters:
     *      len - returns the length of encoded buffer. 
     *  
     *  Throws Exception:
     *      Throws EncodingException in case unsuccessful.
     */
    virtual int Encode(ITS_OCTET* buf,int& len) const;

    /**
     *  Purpose:
     *      returns a new copy
     */
    virtual InfoElement *Clone() const
    {
        return new APDU(*this);
    }

    /**
     *  Purpose:
     *      This constructor can only be invoked by members and friends.
     *      This constructor decodes the buffer.
     *
     *  Input Parameters:
     *      buf - is encoded bufer. 
     *      len - is lenght of encoded bufer.
     *
     *  Output Parameters:
     *
     */
    explicit APDU(const ITS_OCTET *buf,int len);

private:

    ITS_OCTET protocolID;
    mutable ITS_OCTET data[MAX_APDU_LEN];

    friend class InfoElement;
    friend void TEST_APDU(void);
};


} // namespace ie    
} // namespace bssaple    


#endif

