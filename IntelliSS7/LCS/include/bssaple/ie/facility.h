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
//   ID: $Id: facility.h,v 1.1.2.1 2009/12/22 10:41:42 rajeshak Exp $
//
//   LOG: $Log: facility.h,v $
//   LOG: Revision 1.1.2.1  2009/12/22 10:41:42  rajeshak
//   LOG: Adding Codec files to LCS folder
//   LOG:
//   LOG:
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BSSAPLE_IE_FACILITY_H
#define BSSAPLE_IE_FACILITY_H

#include <bssaple/ie/infoelement.h>

#define MAX_LAYER3_LEN 251


namespace bssaple
{

namespace ie
{

static void TEST_Facility(void);

class Facility : public InfoElement
{

public:

    /**
     *  Purpose:
     *      This is contructor initailizes the type and
     *      default length of base class.
     *
     *  Input Parameters:
     *      optFlag - Set this flag to true if This IEs is optional 
     *             parameter in the message.
     *
     *  Output parameters:
     *
     */
    Facility(ITS_BOOLEAN optFlag)
    :optionalFlag(optFlag),
    InfoElement(InfoElement::FACILITY,0)
    {}


    /**
     *  ~Facility
     */
    ~Facility()
    {}

    /**
     *  Purpose:
     *      This Sets the component data.
     *
     *  Input Parameters:
     *      data - is the octet string. 
     *      index - is length 
     *
     *  Out Parameters:
     *
     *  Note:
     *      The  data length should be less than MAX_LAYER3_LEN.
     *
     */
    void SetComponet(ITS_OCTET *data,int index)
    {
        if(index > MAX_LAYER3_LEN)
        {
            ITN_THROW(InvalidData,
                     "Length of data exeeded than maximum allowed");
        }
        else
        {
            memcpy(component,data,index);
            length = index;
        }
    }

    /**
     *  Purpose:
     *      This Sets the component data.
     *
     *  Input Parameters:
     *
     *  Out Parameters:
     *      data - is the octet string.
     *      index - is length
     *
     */
    void GetComponent(ITS_OCTET *data,int index) const 
    {
        memcpy(data,component,length);
        index = length;
    }

protected:
    
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

    virtual InfoElement *Clone() const
    {
        return new Facility(*this);
    }

    virtual void PrintIE(std::ostream &) const;

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
    Facility(const ITS_OCTET *buf,int len);


private:

    ITS_OCTET component[MAX_LAYER3_LEN];
    ITS_BOOLEAN optionalFlag;
    friend class InfoElement;
    friend void TEST_Facility(void);
};

}

}

#endif

