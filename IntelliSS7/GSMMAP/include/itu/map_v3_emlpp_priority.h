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


#if !defined(_MAP_V3_EMLPP_PRIORITY_H_)
#define _MAP_V3_EMLPP_PRIORITY_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v3 {



class EMLPP_Priority : public its::AsnInteger
{
public:

    EMLPP_Priority() : its::AsnInteger(false)
    {
        Initialize();
    }

    EMLPP_Priority(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    EMLPP_Priority(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    EMLPP_Priority(const EMLPP_Priority& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    EMLPP_Priority(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    EMLPP_Priority(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~EMLPP_Priority()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new EMLPP_Priority(*this);
    }

    virtual std::string GetName() const
    { return "EMLPP_Priority"; }

};



} // namespace.

#endif    // !defined(_MAP_V3_EMLPP_PRIORITY_H_)

