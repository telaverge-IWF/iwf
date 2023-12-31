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


#if !defined(_INAP_CS2_DURATION_H_)
#define _INAP_CS2_DURATION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace inap_cs2 {



class Duration : public its::AsnInteger
{
public:

    Duration() : its::AsnInteger(false)
    {
        Initialize();
    }

    Duration(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    Duration(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    Duration(const Duration& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    Duration(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    Duration(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~Duration()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Duration(*this);
    }

    virtual std::string GetName() const
    { return "Duration"; }

};



} // namespace.

#endif    // !defined(_INAP_CS2_DURATION_H_)

