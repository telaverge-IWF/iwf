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
//   ID: $Id: infoelement.h,v 1.1.2.4 2010/03/31 05:47:14 rajeshak Exp $
//
//   LOG: $Log: infoelement.h,v $
//   LOG: Revision 1.1.2.4  2010/03/31 05:47:14  rajeshak
//   LOG: ITS_SUCCESS to CODEC_SUCCESS to remove compilation warning
//   LOG:
//   LOG: Revision 1.1.2.3  2010/03/23 05:38:30  rajeshak
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

#ifndef BSSAPLE_IE_INFOELEMENT_H
#define BSSAPLE_IE_INFOELEMENT_H 

#include <codec_trace.h>
#include <codec_exception.h>
#include <iostream>
#include <cstdio>

namespace bssaple
{

class Message;
class DTAPMessage;

namespace ie
{

/**
 * InfoElement defines the basic interface for BSSMAP-LE information elements.
 * All BSSMAP-LE information elements are derived from this class. This is an
 * abstract class.
 */
class InfoElement 
{
public:
    enum Type
    {
        LCS_QOS                      =  0x3E,
        LCS_PRIORITY                 =  0x43,
        LOCATION_TYPE                =  0x44,
        GEOGRAPHIC_LOCATION          =  0x45,
        POSITIONING_DATA             =  0x46,
        LCS_CAUSE                    =  0x47,
        LCS_CLIENT_TYPE              =  0x48,
        APDU                         =  0x49,
        SRC_NETWORK_ELEMENT_ID       =  0x5A,
        DEST_NETWORK_ELEMENT_ID      =  0x4A,
        GPS_ASSISTANCE_DATA          =  0x4B,
        DECIPHERING_KEYS             =  0x4C,
        RETURN_ERROR_REQUEST         =  0x4D,
        RETURN_ERROR_CAUSE           =  0x4E,
        SEGMENTATION                 =  0x4F,

        LCS_CAPABILITY               =  0x50,
        PACKET_MEASUREMENT_REPORT    =  0x51,
        CELL_IDENTITY_LIST           =  0x52,
        IMEI                         =  0x80,
        GANSS_LOCATION_TYPE          =  0x82,
        GANSS_POSITIONING_DATA       =  0x83,
        VELOCITY_DATA                =  0x55,
        REQ_GANSS_ASSIST_DATA        =  0x41,

        CLASSMARK_INFORMATION_TYPE3  =  0x13,
        CAUSE                        =  0x04,
        CELL_IDENTIFIER              =  0x05,
        CHOSEN_CHANNEL               =  0x21,
        IMSI                         =  0x00,
        ISDN_ADDRESS                 =  0x01,
        SECURITY                     =  0x02,
        SIGNALING_POINT_CODE         =  0x03,
        LMU_CAUSE                    =  0x04,

        FACILITY                     =  0xF1, 
        RELEASE_COMPLETE_CAUSE       =  0xF2,
        RELEASE_FORBIDDEN            =  0xF3
    };

    
    /**
     *  ~InfoElement
     */
    virtual ~InfoElement()
    {}

    /**
     *  Purpose: Returns the information element identifier
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      the Id of information element.
     *
     */
    Type GetId() const
    { 
        return id;
    }

    /**
     *  Purpose: Returns the length of octets of IE
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      the length of information element
     *
     */
    int GetLength() const
    { 
        return length;
    }

    /**
     *  Operation:Clone
     *
     *  Purpose:
     *      Pure virtual functin Clone,shuold be implemented by
     *      derived class.This function returns new copy.
     *
     *  RetrunValue:
     *      returns new copy of IE.
     */
    virtual InfoElement *Clone() const = 0;

protected:

    /**
     * Proteced Printing function which is overriden by 
     * derived classes
     */
    virtual void PrintIE(std::ostream &) const = 0;

    /**
     * Protected copy Constructors 
     */
    InfoElement(const InfoElement &right)
    {
        id = right.id;
        length = right.length;
    }

    /**
     *  Operation: Encode
     *  Purpose:
     *      This method Encodes a single IE.  All IE types must implement
     *      this method.If the buffer is successfully Encoded,
     *      CODEC_SUCCESS will be returned,Other wise it throws Encoding
     *      exception.
     *
     *  Input Parameters:
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into.
     *      len - return the total length of ecoded IE.
     *  
     *  Throws Exception.
     *      Throws EncodingException in case unsuccessful.
     */
    virtual int Encode (ITS_OCTET* buf, int& len) const = 0;

    /**
     *  Operation: InfoElement()
     *  Purpose:
     *
     *      Constructor. This method constructs a Info
     *      Element. It requires that the IE identifier be set. This
     *      is the only public constructor for the base class, which
     *      forces all derived classes to set the IE identifier for
     *      this parameter.
     *
     *  Input Parameters:
     *      _id Information Element Id.
     *      len length if the IE.
     */
    InfoElement(Type _id,int len):id(_id),length(len)
    {}

    /**
     *  Purpose:
     *      This method decodes a single IE.  
     *  
     *  Input Parameters:
     *      buf - a pointer to the buffer to encode into.
     *      len - the length of the encoded buffer.
     *
     *  Output Parameters:
     *
     *  Return Value:
     *      InfoElement *,It returns decoded Information Element object.
     *
     *  Exception.
     *      Throws DecodingException in case unsuccessful.
     */
    static InfoElement *Decode(const ITS_OCTET *buf, int &len);

    Type id;
    int length;

private:
    friend class bssaple::Message;
    friend class bssaple::DTAPMessage;
    friend std::ostream & operator<<(std::ostream &, const InfoElement &);
    InfoElement &operator=(const InfoElement &right);
};

inline std::ostream &operator<<(std::ostream &out, const InfoElement &ie)
{
    ie.PrintIE(out);
    return out;
}

} // namespace ie
} // namespace bssaple


#endif

