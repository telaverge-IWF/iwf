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
// LOG: $Log: AsnDescInteger.h,v $
// LOG: Revision 9.2  2007/01/10 11:15:04  yranade
// LOG: Merge changes from 6.5.3 and Lucent branches
// LOG:
// LOG: Revision 9.1.10.2  2005/10/06 12:13:52  mmanikandan
// LOG: Exception Handling in PER and Code Review Changes.
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
// ASN.1 runtime AsnDescInteger class definition.
//

#if !defined(_ASN_DESC_INTEGER_H_)
#define _ASN_DESC_INTEGER_H_

#ident "$Id: AsnDescInteger.h,v 9.2 2007/01/10 11:15:04 yranade Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnDescObject.h>

namespace its {

class AsnDescInteger : public AsnDescObject
{
public:

    AsnDescInteger()
    :   _clauseRange(false),
        _defaultValue(0),
        _maxValue(0), 
        _minValue(0),
        _maxExtValue(0), 
        _minExtValue(0),
       _clauseExtensible(false)
    {}

    AsnDescInteger(const AsnDescInteger& rhs)
    {
        bool copy_constructor_must_not_be_called = false;
        ITS_ASSERT(copy_constructor_must_not_be_called);
    }

    virtual ~AsnDescInteger()
    {
        // Nothing to do.
    }

    virtual AsnDescObject* 
    Clone() const
    { 
        return new AsnDescInteger(*this); 
    }

    bool 
    IsClauseRange() const
    { 
        return _clauseRange; 
    }

    void 
    SetClauseRange()
    { 
        _clauseRange = true; 
    }

    void 
    SetMaxValue(long maxValue)
    { 
        _maxValue = maxValue; 
    }

    long 
    GetMaxValue() const
    { 
        return _maxValue; 
    }

    void 
    SetMinValue(long minValue)
    { 
        _minValue = minValue; 
    }

    long 
    GetMinValue() const
    { 
        return _minValue; 
    }

    void 
    SetExtMaxValue(long maxExtValue)
    { 
        _maxExtValue = maxExtValue; 
    }

    long 
    GetExtMaxValue() const
    { 
        return _maxExtValue; 
    }

    void 
    SetExtMinValue(long minExtValue)
    { 
        _minExtValue = minExtValue; 
    }

    long 
    GetExtMinValue() const
    { 
        return _minExtValue; 
    }

    void 
    SetDefaultValue(long defaultValue)
    { 
        _defaultValue = defaultValue; 
    }

    long 
    GetDefaultValue()
    { 
        return _defaultValue; 
    }

    bool 
    IsClauseExtensible() const
    { 
        return _clauseExtensible; 
    }

    void 
    SetClauseExtensible()
    { 
        _clauseExtensible = true; 
    }

public: // Pseudo-protected.

    bool _clauseRange;
    long _defaultValue;
    long _maxValue;
    long _minValue;
    long _maxExtValue;
    long _minExtValue;
    bool _clauseExtensible;
};

} // namespace its.

#endif // !defined(_ASN_DESC_INTEGER_H_)

