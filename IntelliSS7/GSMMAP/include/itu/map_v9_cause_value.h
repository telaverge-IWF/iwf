//
// Generated by IntelliAsnCC ASN.1 compiler (C, C++, Java).
//
// Do not edit!
//
//
//
// (C) 2000, 2001 IntelliNet Technologies Inc. All Rights Reserved.
//
//


#if !defined(_MAP_V9_CAUSE_VALUE_H_)
#define _MAP_V9_CAUSE_VALUE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v9 {



class CauseValue : public its::AsnOctetString
{
public:

    CauseValue() : its::AsnOctetString(false)
    {
        Initialize();
    }

    CauseValue(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    CauseValue(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    CauseValue(const CauseValue& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    CauseValue(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    CauseValue(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
    {
        // Nothing to do.
    }

protected:

    void Initialize()
    {
        _description = GetStaticDescription();
    }

public:

    static its::AsnDescObject* GetStaticDescription();

public:

    virtual ~CauseValue()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CauseValue(*this);
    }

    virtual std::string GetName() const
    { return "CauseValue"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_CAUSE_VALUE_H_)
