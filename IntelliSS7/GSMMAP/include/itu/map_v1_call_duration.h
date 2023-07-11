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


#if !defined(_MAP_V1_CALL_DURATION_H_)
#define _MAP_V1_CALL_DURATION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v1 {



class CallDuration : public its::AsnInteger
{
public:

    CallDuration() : its::AsnInteger(false)
    {
        Initialize();
    }

    CallDuration(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    CallDuration(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    CallDuration(const CallDuration& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    CallDuration(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    CallDuration(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~CallDuration()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CallDuration(*this);
    }

    virtual std::string GetName() const
    { return "CallDuration"; }

};



} // namespace.

#endif    // !defined(_MAP_V1_CALL_DURATION_H_)
