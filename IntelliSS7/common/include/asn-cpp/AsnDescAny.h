///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//          Copyright (c) 1999 - 2002 IntelliNet Technologies, Inc.          //
//                            All Rights Reserved.                           //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
//                                                                           //
//   This product and related documentation is protected by copyright and    //
//   distributed under licenses restricting its use, copying, distribution   //
//   and decompilation.  No part of this product or related documentation    //
//   may be reproduced in any form by any means without prior written        //
//   authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                           //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//   government is subject to restrictions as set forth in subparagraph      //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Contract: Internal                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: AsnDescAny.h,v $
// LOG: Revision 9.1  2005/03/23 12:52:52  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:50:56  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:43  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.3  2002/01/16 22:13:20  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:53  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
// ASN.1 runtime AsnDescAny class definition.
//

#if !defined(_ASN_DESC_ANY_H_)
#define _ASN_DESC_ANY_H_

#ident "$Id: AsnDescAny.h,v 9.1 2005/03/23 12:52:52 cvsadmin Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnDescObject.h>

namespace its {

class AsnDescAny : public AsnDescObject
{
public:

    AsnDescAny() 
    :   _clauseAnyTag(false) 
    {}

    AsnDescAny(const AsnDescAny& rhs)
    {
        bool copy_constructor_must_not_be_called = false;
        ITS_ASSERT(copy_constructor_must_not_be_called);
    }

    virtual ~AsnDescAny()
    {
        // Nothing to do.
    }

    virtual AsnDescObject* 
    Clone() const
    { 
        return new AsnDescAny(*this); 
    }

    virtual bool 
    TagIdentify(const Tag& tag) const
    {
        ITS_REQUIRE(TagLevelNumber() >= 1);
        if (TagLevelNumber() == 1 && IsClauseAnyTag())
        {
            return true;
        }
        else
        {
            return tag == *(_tagStack.front());
        }
    }

    virtual const Tag& 
    TagIdentity() const
    {
        ITS_REQUIRE(TagLevelNumber() >= 1);
        if (TagLevelNumber() == 1 && IsClauseAnyTag())
        {
            // Should never be reached by design of the encode/decode 
            // algorithms. ANY type is always explicitly tagged by ASN.1 
            // compiler.
            bool must_not_be_reached = false;
            ITS_ASSERT(must_not_be_reached);
            static Tag notReached;
            return notReached;
        }
        else
        {
            return *(_tagStack.front());
        }
    }

    virtual size_t 
    TagLevelNumber() const  
    {
        return _tagStack.size() + 1;
    }

    bool 
    IsClauseAnyTag() const
    { 
        return _clauseAnyTag; 
    }

    void 
    SetClauseAnyTag()
    { 
        _clauseAnyTag = true; 
    }

public: // Pseudo-protected.

    bool _clauseAnyTag;

};

} // namespace its.

#endif // !defined(_ASN_DESC_ANY_H_)

