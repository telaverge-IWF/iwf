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


#if !defined(_MAP_V1_MAXIMUM_CONFEREES_NUMBER_H_)
#define _MAP_V1_MAXIMUM_CONFEREES_NUMBER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v1 {



class MaximumConfereesNumber : public its::AsnInteger
{
public:

    MaximumConfereesNumber() : its::AsnInteger(false)
    {
        Initialize();
    }

    MaximumConfereesNumber(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    MaximumConfereesNumber(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    MaximumConfereesNumber(const MaximumConfereesNumber& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    MaximumConfereesNumber(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    MaximumConfereesNumber(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~MaximumConfereesNumber()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MaximumConfereesNumber(*this);
    }

    virtual std::string GetName() const
    { return "MaximumConfereesNumber"; }

};



} // namespace.

#endif    // !defined(_MAP_V1_MAXIMUM_CONFEREES_NUMBER_H_)
