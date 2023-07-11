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


#if !defined(_MAP_V9_SERVICE_KEY_H_)
#define _MAP_V9_SERVICE_KEY_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v9 {



class ServiceKey : public its::AsnInteger
{
public:

    ServiceKey() : its::AsnInteger(false)
    {
        Initialize();
    }

    ServiceKey(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    ServiceKey(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    ServiceKey(const ServiceKey& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    ServiceKey(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    ServiceKey(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~ServiceKey()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ServiceKey(*this);
    }

    virtual std::string GetName() const
    { return "ServiceKey"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_SERVICE_KEY_H_)

