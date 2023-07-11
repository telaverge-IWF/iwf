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


#if !defined(_ASN_USEFUL_UNIVERSAL_STRING_H_)
#define _ASN_USEFUL_UNIVERSAL_STRING_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnBaseString.h>



namespace its {



class UniversalString : public its::AsnBaseString
{
public:

    UniversalString() : its::AsnBaseString(false)
    {
        Initialize();
    }

    UniversalString(const std::string& str) : its::AsnBaseString(str, false)
    {
        Initialize();
    }

    UniversalString(its::Octets& octets) : its::AsnBaseString(false)
    {
        Initialize();
        Decode(octets);
    }

    UniversalString(const UniversalString& rhs) : its::AsnBaseString(rhs)
    {
        // Nothing to do.
    }

    UniversalString(its::AsnDescObject* description) : its::AsnBaseString(description)
    {
        // Nothing to do.
    }

    UniversalString(its::AsnDescObject* description, const std::string& str) : its::AsnBaseString(description, str)
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

    virtual ~UniversalString()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new UniversalString(*this);
    }

    virtual std::string GetName() const
    { return "UniversalString"; }

};



} // namespace.

#endif    // !defined(_ASN_USEFUL_UNIVERSAL_STRING_H_)

