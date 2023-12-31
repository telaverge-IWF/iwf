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


#if !defined(_MAP_V3_OR_PHASE_H_)
#define _MAP_V3_OR_PHASE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v3 {



class OR_Phase : public its::AsnInteger
{
public:

    OR_Phase() : its::AsnInteger(false)
    {
        Initialize();
    }

    OR_Phase(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    OR_Phase(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    OR_Phase(const OR_Phase& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    OR_Phase(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    OR_Phase(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~OR_Phase()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new OR_Phase(*this);
    }

    virtual std::string GetName() const
    { return "OR_Phase"; }

};



} // namespace.

#endif    // !defined(_MAP_V3_OR_PHASE_H_)

