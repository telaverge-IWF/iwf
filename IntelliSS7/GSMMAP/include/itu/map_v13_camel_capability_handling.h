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


#if !defined(_MAP_V13_CAMEL_CAPABILITY_HANDLING_H_)
#define _MAP_V13_CAMEL_CAPABILITY_HANDLING_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v13 {



class CamelCapabilityHandling : public its::AsnInteger
{
public:

    CamelCapabilityHandling() : its::AsnInteger(false)
    {
        Initialize();
    }

    CamelCapabilityHandling(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    CamelCapabilityHandling(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    CamelCapabilityHandling(const CamelCapabilityHandling& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    CamelCapabilityHandling(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    CamelCapabilityHandling(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~CamelCapabilityHandling()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CamelCapabilityHandling(*this);
    }

    virtual std::string GetName() const
    { return "CamelCapabilityHandling"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_CAMEL_CAPABILITY_HANDLING_H_)

