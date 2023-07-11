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
// LOG: $Log: AsnDescOctetString.h,v $
// LOG: Revision 9.2  2007/01/10 11:15:04  yranade
// LOG: Merge changes from 6.5.3 and Lucent branches
// LOG:
// LOG: Revision 9.1.10.1  2005/09/06 09:15:59  mmanikandan
// LOG: Support for ASN.1 PER.
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:52  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:50:56  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:43  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
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
// ASN.1 runtime AsnDescOctetString class definition.
//

#if !defined(_ASN_DESC_OCTET_STRING_H_)
#define _ASN_DESC_OCTET_STRING_H_

#ident "$Id: AsnDescOctetString.h,v 9.2 2007/01/10 11:15:04 yranade Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnDescObject.h>

namespace its {

class AsnDescOctetString : public AsnDescObject
{
public:

    AsnDescOctetString()
    :   _clauseSize(false),
        _maxSize(0), 
        _minSize(0),
        _maxExtSize(0), 
        _minExtSize(0),
        _clauseExtensible(false)
    {}

    AsnDescOctetString(const AsnDescOctetString& rhs)
    {
        bool copy_constructor_must_not_be_called = false;
        ITS_ASSERT(copy_constructor_must_not_be_called);
    }


    virtual ~AsnDescOctetString()
    {
        // Nothing to do.
    }

    virtual AsnDescObject* 
    Clone() const
    { 
        return new AsnDescOctetString(*this); 
    }

    bool 
    IsClauseSize() const
    { 
        return _clauseSize; 
    }

    void 
    SetClauseSize()
    { 
        _clauseSize = true; 
    }

    void 
    SetMaxSize(size_t maxSize)
    { 
        _maxSize = maxSize; 
    }

    size_t 
    GetMaxSize() const
    { 
        return _maxSize; 
    }

    void 
    SetMinSize(size_t minSize)
    { 
        _minSize = minSize; 
    }

    size_t 
    GetMinSize() const
    { 
        return _minSize; 
    }

    void 
    SetMaxExtSize(size_t maxSize)
    { 
        _maxExtSize = maxSize;
    }

    size_t 
    GetMaxExtSize() const
    { 
        return _maxExtSize; 
    }

    void 
    SetMinExtSize(size_t minSize)
    { 
        _minExtSize = minSize; 
    }

    size_t 
    GetMinExtSize() const
    { 
        return _minExtSize; 
    }

    bool 
    IsClauseExtensible() const
    { 
        return _clauseExtensible; 
    }

    void 
    SetClauseExtensible(bool val = false)
    { 
        _clauseExtensible = val; 
    }

public: // Pseudo-protected.

    bool    _clauseSize;
    size_t  _maxSize;
    size_t  _minSize;
    size_t  _maxExtSize;
    size_t  _minExtSize;
    bool    _clauseExtensible;
};

} // namespace its.

#endif // !defined(_ASN_DESC_OCTET_STRING_H_)
