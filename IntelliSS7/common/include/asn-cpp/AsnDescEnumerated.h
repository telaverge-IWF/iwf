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
// LOG: $Log: AsnDescEnumerated.h,v $
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
// LOG: Revision 5.4  2002/01/16 22:13:20  hdivoux
// LOG: Working XER decoding. Reorganization.
// LOG:
// LOG: Revision 5.3  2002/01/07 22:59:02  hdivoux
// LOG: First shot at XER encoding.
// LOG:
// LOG: Revision 5.2  2001/11/15 23:55:53  hdivoux
// LOG: Update for better performance.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

//
// ASN.1 runtime AsnDescEnumerated class definition.
//

#if !defined(_ASN_DESC_ENUMERATED_H_)
#define _ASN_DESC_ENUMERATED_H_

#ident "$Id: AsnDescEnumerated.h,v 9.2 2007/01/10 11:15:04 yranade Exp $"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnDescObject.h>

namespace its {

class AsnDescEnumerated : public AsnDescObject
{
public:

    AsnDescEnumerated() 
    :   _clauseExtensible(false),
        _defaultValue(0),
        _namedNumberList(NULL),
        _namedNumberExtList(NULL)
    {}

    AsnDescEnumerated(const AsnDescEnumerated& rhs)
    {
        bool copy_constructor_must_not_be_called = false;
        ITS_ASSERT(copy_constructor_must_not_be_called);
    }

    virtual ~AsnDescEnumerated()
    {
        // Nothing to do.
    }

    virtual AsnDescObject* 
    Clone() const
    { return new AsnDescEnumerated(*this); }

    void 
    Put(long value)
    { 
        _valueSet.insert(value); 
    }

    void
    PutExt(long value)
    {
        _valueExtSet.insert(value);
    }

    long Get(const std::string& valueName) const;

    std::string Get(long value) const;
    std::string GetExt(long value) const;

    bool 
    Contains(long value) const
    { 
        return (std::set<long, std::less<long> >::const_iterator)
                (_valueSet.find(value)) != _valueSet.end(); 
    }

    bool 
    ContainsExt(long value) const
    { 
        return (std::set<long, std::less<long> >::const_iterator)
                (_valueExtSet.find(value)) != _valueExtSet.end(); 
    }

    size_t 
    GetSize() const
    { 
        return _valueSet.size(); 
    }

    size_t 
    GetExtSize() const
    { 
        return _valueExtSet.size(); 
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

    void 
    SetDefaultValue(long defaultValue)
    { 
        _defaultValue = defaultValue; 
    }

    long 
    GetDefaultValue() const
    { 
        return _defaultValue; 
    }

    struct NamedNumber
    {
        const char* _name;
        long        _number;
    };

    void
    SetNamedNumberList(const NamedNumber* namedNumberList)
    {
        ITS_REQUIRE(namedNumberList != NULL);
        _namedNumberList = namedNumberList;
    }

    void
    SetNamedNumberExtList(const NamedNumber* namedNumberList)
    {
        ITS_REQUIRE(namedNumberList != NULL);
        _namedNumberExtList = namedNumberList;
    }

    const NamedNumber*
    GetNamedNumberList() const
    {
        return _namedNumberList;
    }

    const NamedNumber*
    GetNamedNumberExtList() const
    {
        return _namedNumberExtList;
    }

public: // Pseudo-protected.

    std::set<long, std::less<long> >    _valueSet;
    std::set<long, std::less<long> >    _valueExtSet;
    bool                                _clauseExtensible;
    long                                _defaultValue;
    const NamedNumber*                  _namedNumberList;                        
    const NamedNumber*                  _namedNumberExtList;
};

} // namespace its.

#endif // !defined(_ASN_DESC_ENUMERATED_H_)

