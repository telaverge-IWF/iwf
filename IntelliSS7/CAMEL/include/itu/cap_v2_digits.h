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


#if !defined(_CAP_V2_DIGITS_H_)
#define _CAP_V2_DIGITS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace cap_v2 {



class Digits : public its::AsnOctetString
{
public:

    Digits() : its::AsnOctetString(false)
    {
        Initialize();
    }

    Digits(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    Digits(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    Digits(const Digits& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    Digits(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    Digits(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~Digits()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Digits(*this);
    }

    virtual std::string GetName() const
    { return "Digits"; }

};



} // namespace.

#endif    // !defined(_CAP_V2_DIGITS_H_)

