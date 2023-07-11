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


#if !defined(_CAP_V3_CAUSE_H_)
#define _CAP_V3_CAUSE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace cap_v3 {



class Cause : public its::AsnOctetString
{
public:

    Cause() : its::AsnOctetString(false)
    {
        Initialize();
    }

    Cause(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    Cause(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    Cause(const Cause& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    Cause(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    Cause(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~Cause()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Cause(*this);
    }

    virtual std::string GetName() const
    { return "Cause"; }

};



} // namespace.

#endif    // !defined(_CAP_V3_CAUSE_H_)

