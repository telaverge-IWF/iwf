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


#if !defined(_MAP_V13_BANDWIDTH_H_)
#define _MAP_V13_BANDWIDTH_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v13 {



class Bandwidth : public its::AsnInteger
{
public:

    Bandwidth() : its::AsnInteger(false)
    {
        Initialize();
    }

    Bandwidth(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    Bandwidth(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    Bandwidth(const Bandwidth& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    Bandwidth(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    Bandwidth(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~Bandwidth()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Bandwidth(*this);
    }

    virtual std::string GetName() const
    { return "Bandwidth"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_BANDWIDTH_H_)

