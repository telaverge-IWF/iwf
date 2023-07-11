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
//   ID: $Id: segmentation.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: segmentation.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_SEGMENTATION_H
#define BSSAPLE_IE_SEGMENTATION_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{

namespace ie
{

static void TEST_SEGMENTATION(void);

/**
 * Segmentation is a variable length information element that carries
 * information for a segmented APDU.
 */
class Segmentation : public InfoElement
{
public:
    enum SegmentationBit
    {
        FINAL_SEGMENT         =   0x00, 
        NON_FINAL_SEGMENT     =   0x01
    };

    /**
     *  Purpose:
     *      This is default contructor initailizes the type and
     *      default length.
     *
     *  Input Parameters:
     *
     *  Output parameters:
     *
     */
    Segmentation()
    :segInfo(0),
     msgId(0),
     InfoElement(InfoElement::SEGMENTATION, sizeof(ITS_OCTET))
    {} 

    /**
    * Destructor 
    */
    virtual ~Segmentation()
    {}

    /**
     *  Purpose: Set SegmentationBit info
     *
     *  Input Parameters:
     *      val - value of SegmentationBit
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetSegmentationBit (SegmentationBit val)
    {
        segInfo &= ~0x10U;
        segInfo |= (val << 4) & 0x10U;
    }

    /**
     *  Purpose: Get value of SegmentationBit
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      value of SegmentationBit
     *
     */
    SegmentationBit GetSegmentationBit () const
    {
        return (Segmentation::SegmentationBit)((segInfo >> 4) & 0x01U);
    }

    /**
     *  Purpose: Set SegmentationNumber 
     *
     *  Input Parameters:
     *      val - value of SegmentationNumber
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void  SetSegmentationNumber (ITS_OCTET val)
    {
        segInfo &= ~0x0FU;
        segInfo |= (val & 0x0FU);
    }

    /**
     *  Purpose: Get SegmentationNumber value
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      SegmentationNumber value
     *
     */
    ITS_OCTET GetSegmentationNumber () const
    {
        return (segInfo & 0x0F);
    }

    /**
     *  Purpose: Set MessageID value
     *
     *  Input Parameters:
     *      val - MessageID value
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetMessageID (ITS_USHORT val)
    {
        if(length == sizeof(ITS_OCTET))
        {
            length += sizeof(ITS_USHORT);
        }
        msgId = val;
    }

    /**
     *  Purpose: Get MessageID value
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      MessageID 
     *
     *  Note: 
     *      MessageID is optional attribute
     *      it return 0 if not presnt
     */
    ITS_USHORT GetMessageID () const
    {
        return msgId;
    }

protected:

    /**
     *  Purpose:
     *      This method Enocde the IEs in to the buf argument.
     *
     *  Input Parameters:
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into.
     *      len - returns the length of encoded buffer.
     *
     *  Throws Exception:
     *      Throws EncodingException in case unsuccessful
     */
     virtual int Encode (ITS_OCTET* buf, int& len) const;

    virtual InfoElement *Clone() const
    {
        return new Segmentation(*this);
    }

    /**
     *  Purpose:
     *      This constructor can only be invoked by members and friends.
     *      This contructor decodes the buffer and creates object of its type.
     *
     *  Input Parameters:
     *      buf - is encoded bufer.
     *      len - is lenght of encoded bufer.
     *
     *  Output Parameters:
     *
     */
    Segmentation(const ITS_OCTET* buf, int len);   

    virtual void PrintIE(std::ostream &) const;

private: 

    ITS_OCTET segInfo;
    ITS_USHORT msgId;

    /**
    * Assignment Operation 
    */
    Segmentation & operator=(const Segmentation &right);

    friend class InfoElement;
    friend void TEST_SEGMENTATION(void);

};


} // namespace ie   
} // namespace bssaple   


#endif

