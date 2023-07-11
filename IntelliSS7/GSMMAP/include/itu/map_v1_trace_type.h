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


#if !defined(_MAP_V1_TRACE_TYPE_H_)
#define _MAP_V1_TRACE_TYPE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v1 {



class TraceType : public its::AsnInteger
{
public:

    TraceType() : its::AsnInteger(false)
    {
        Initialize();
    }

    TraceType(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    TraceType(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    TraceType(const TraceType& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    TraceType(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    TraceType(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~TraceType()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new TraceType(*this);
    }

    virtual std::string GetName() const
    { return "TraceType"; }

};



} // namespace.

#endif    // !defined(_MAP_V1_TRACE_TYPE_H_)

