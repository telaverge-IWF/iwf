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


#if !defined(_CAP_V2_AGE_OF_LOCATION_INFORMATION_H_)
#define _CAP_V2_AGE_OF_LOCATION_INFORMATION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace cap_v2 {



class AgeOfLocationInformation : public its::AsnInteger
{
public:

    AgeOfLocationInformation() : its::AsnInteger(false)
    {
        Initialize();
    }

    AgeOfLocationInformation(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    AgeOfLocationInformation(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    AgeOfLocationInformation(const AgeOfLocationInformation& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    AgeOfLocationInformation(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    AgeOfLocationInformation(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~AgeOfLocationInformation()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AgeOfLocationInformation(*this);
    }

    virtual std::string GetName() const
    { return "AgeOfLocationInformation"; }

};



} // namespace.

#endif    // !defined(_CAP_V2_AGE_OF_LOCATION_INFORMATION_H_)
