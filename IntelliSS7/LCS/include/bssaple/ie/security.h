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
//   ID: $Id: security.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: security.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_SECURITY_H
#define BSSAPLE_IE_SECURITY_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{

namespace ie
{

static void TEST_SECURITY(void);

/**
 * Security defines what security measures are needed for signaling to an LMU.
 */
class Security : public InfoElement
{
public:

    enum AuthenticationIndicator
    {
        AUTHENTICATION_OF_LMU_NOT_REQUIRED     =   0x00,
        AUTHENTICATION_OF_LMU_REQUIRED         =   0x01
    };
    
    enum CipheringIndicator
    {
        CIPHERING_OF_LMU_SIGNALING_DATA_NOT_REQUIRED    =   0x00,
        CIPHERING_OF_LMU_SIGNALING_DATA_REQUIRED        =   0x01
    };

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
    Security()
    :InfoElement(InfoElement::SECURITY,sizeof(ITS_OCTET))
    {}

    /**
    *     Destructor 
    */
    ~Security()
    {}

    /**
     *  Purpose: Set attribute CIPH
     *
     *  Input Parameters:
     *          val - value of CipheringIndicator
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetCIPH (CipheringIndicator val)
    {
        ciph_auth &= ~0x02U;
        ciph_auth |= (val << 1) & 0x02U;
    }


    /**
     *  Purpose: Return CIPH of Security
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *      CIPH attribute of Security
     *
     */
    CipheringIndicator  GetCIPH () const
    {
        return (Security::CipheringIndicator)((ciph_auth >> 1) & 0x01U);
    }


    /**
     *  Purpose: Set AUTH attribute
     *
     *  Input Parameters:
     *      val - value of AuthenticationIndicator
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *
     *
     */
    void SetAUTH (AuthenticationIndicator val)
    {
        ciph_auth &= ~0x01U;
        ciph_auth |= val & 0x01U;
    }

    /**
     *  Purpose: Return AUTH of Security
     *
     *  Input Parameters:
     *
     *
     *  OutPut Parameters:
     *
     *
     *  Returns:
     *       AUTH attribute of Security 
     *
     */
    AuthenticationIndicator GetAUTH () const
    {
        return (Security::AuthenticationIndicator)(ciph_auth & 0x01U);
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
        return new Security(*this);
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
    Security(const ITS_OCTET *buf,int len);

    virtual void PrintIE(std::ostream &) const;

private: 

    ITS_OCTET ciph_auth;

    /**
    *     Assignment Operation 
    */
    Security & operator=(const Security &right);
    friend class InfoElement;
    friend void TEST_SECURITY(void);

};


} // namespace ie
} // namespace bssaple

#endif

