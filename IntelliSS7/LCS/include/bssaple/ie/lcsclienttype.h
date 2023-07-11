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
//   ID: $Id: lcsclienttype.h,v 1.1.2.3 2010/03/26 11:48:05 rajeshak Exp $
//
//   LOG: $Log: lcsclienttype.h,v $
//   LOG: Revision 1.1.2.3  2010/03/26 11:48:05  rajeshak
//   LOG: GetHexBuff function signature changes
//   LOG:
//   LOG: Revision 1.1.2.2  2010/03/25 06:32:32  rajeshak
//   LOG: API to get the Hex dump after encode/decode (for TDR).
//   LOG:
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_LCSCLIENTTYPE_H
#define BSSAPLE_IE_LCSCLIENTTYPE_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{
namespace ie
{

static void TEST_CLIENT_TYPE(void);

struct LCSClientTypeStruct
{
    enum Category
    {
        VALUE_ADDED_CLIENT          =   0x00,
        PLMN_OPERATOR               =   0x02,
        EMERGENCY_SERVICES          =   0x03,
        LAWFUL_INTERCEPT_SERVICES   =   0x04
    };

    enum SubType
    {
        UNSPECIFIED                 =   0x00,
        BROADCAST_SERVICE           =   0x01,
        O_AND_M                     =   0x02,
        ANONYMOUS_STATISTICS        =   0x03,
        TARGET_MS_SERVICE_SUPPORT   =   0x04
    };

    Category category;
    SubType subtype;
};

/**
 * LCSClientType identifies the type of LCS Client.
 */
class LCSClientType: public InfoElement, public LCSClientTypeStruct
{
public:

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
    LCSClientType()
    : InfoElement(InfoElement::LCS_CLIENT_TYPE, sizeof(ITS_OCTET))
    {}

    const LCSClientTypeStruct &GetAsStruct() const
    {
        return *static_cast<const LCSClientTypeStruct *>(this);
    }

    /**
     *  Purpose: Set Client Subtype
     *
     *  Input Parameters:
     *      val - value of Client Subtype
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetClientSubtype(SubType val)
    {
        subtype = val;
    }

    /**
     *  Purpose: Return the Clinet Subtype of the LCS Client Type
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      Clinet Subtype of the LCS Client Type
     *
     */
    SubType GetClientSubtype() const
    {
        return subtype;
    }

    /**
     *  Purpose: Set Client Category
     *
     *  Input Parameters:
     *      val - value of client Category
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetClientCategory (Category val)
    {
        category = val;
    }

    /**
     *  Purpose: Returns the Clinet Category of the LCS Client Type
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      the Clinet Category of the LCS Client Type
     *
     */
    Category GetClientCategory () const
    {
        return category;
    }

    /**
     *  Purpose: Get Hex Buff (This can be used after IE decode only)
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      Hex Buff
     *
     */
    const ITS_OCTET* GetHexBuff() const
    {
        return hexBuff;
    }

protected:

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
    LCSClientType(const ITS_OCTET *buf,int len);

    virtual void PrintIE(std::ostream &) const;

    virtual InfoElement *Clone() const
    {
        return new LCSClientType(*this);
    }

    /**
     *  Purpose:
     *      This method Enocde the IEs in to the buf argument.
     *
     *  Input Parameters:
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - returns the length of encoded buffer.
     *
     *  Throws Exception:
     *      Throws EncodingException in case unsuccessful
     */
     virtual int Encode (ITS_OCTET* buf, int& len) const;

private: 
    ITS_OCTET hexBuff[10];

    friend class InfoElement;
    friend void TEST_CLIENT_TYPE(void);
    LCSClientType & operator=(const LCSClientType &right);
};

} // namespace ie
} // namespace bssaple


#endif

