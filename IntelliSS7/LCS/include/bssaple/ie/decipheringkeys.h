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
//   ID: $Id: decipheringkeys.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: decipheringkeys.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////


#ifndef BSSAPLE_IE_DECIPHERINGKEYS_H
#define BSSAPLE_IE_DECIPHERINGKEYS_H 

#include <bssaple/ie/infoelement.h>

namespace bssaple
{

namespace ie
{

static void TEST_DecipheringKeys(void);

/**
 * DecipheringKeys defines the deciphering keys which should used by the MS to
 * decode LCS broadcast assistance data.
 */
class DecipheringKeys : public InfoElement 
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
    DecipheringKeys():InfoElement(InfoElement::DECIPHERING_KEYS,
                                  sizeof(ITS_OCTET)*15)
    {}

    virtual ~DecipheringKeys()
    {}

    /**
     *  Purpose: Set key flag
     *
     *  Input Parameters:
     *      val - boolean flag ,true or false.
     *
     *  OutPut Parameters:
     *
     */
    void SetKeyFlag (ITS_BOOLEAN val)
    {
        keyFlag = val;
    }
        

    /**
     *  Purpose: Get KeyFlag
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *      
     *  Returns:
     *      boolean key flag.
     *
     */
    ITS_BOOLEAN GetKeyFlag () const
    {
        return keyFlag;
    } 

    /**
     *  Purpose: Set CurrentKey. 
     *
     *  Input Parameters:
     *      key - is a octet string of length 7.
     *
     *  OutPut Parameters:
     *
     */
    void SetCurrentKey (ITS_OCTET* key)
    {
        memcpy(currentKey,key,sizeof(ITS_OCTET) *7);
    }

    /**
     *  Purpose: Get CurrentKey into key.
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *      key - octet array if size 7.
     *  
     */
    void GetCurrentKey (ITS_OCTET *key) const
    {
        memcpy(key,currentKey,sizeof(ITS_OCTET) *7);
    }

    /**
     *  Purpose: Set NextKey.
     *
     *  Input Parameters:
     *      key - is next key of octet array of size 7.
     *
     *  OutPut Parameters:
     *
     */
    void SetNextKey (ITS_OCTET *key)
    {
        memcpy(nextKey,key,sizeof(ITS_OCTET) *7);
    }

    /**
     *  Purpose:  Get NextKey into key.
     *
     *  Input Parameters:
     *
     *  OutPut Parameters:
     *      key - is next key of octet array of size 7.
     *
     *
     */
    void GetNextKey (ITS_OCTET *key) const
    {
        memcpy(key,nextKey,sizeof(ITS_OCTET) *7);
    }

protected:

    virtual void PrintIE(std::ostream &) const;

    /**
     *  Purpose:
     *      This method Enocde the IEs in to the buf argument.
     *
     *  Input Parameters:
     *      buf - a pointer to the buffer to encode into.
     *
     *  Output Parameters:
     *      len - returns the length of encoded buffer.
     *
     *  Throws Exception:
     *      Throws EncodingException in case unsuccessful.
     */
     virtual int Encode (ITS_OCTET* buf, int& len) const;

    /**
    *   Returns a new copy
    */
    virtual InfoElement *Clone() const
    {
        return new DecipheringKeys(*this);
    }

    /**
     *  Purpose:
     *      This constructor can only be invoked by members and friends.
     *
     *  Input Parameters:
     *      buf - is encoded bufer.
     *      len - is lenght of encoded bufer.
     *
     *  Output Parameters:
     *
     */
    DecipheringKeys(const ITS_OCTET *buf,int len);

private:

    /**
    * Data Members for Class Attributes
    */
    ITS_BOOLEAN keyFlag;
    ITS_OCTET currentKey[7];
    ITS_OCTET nextKey[7];

    friend class InfoElement;
    friend void TEST_DecipheringKeys(void);
};


} // namespace ie
} // namespace bssaple


#endif

