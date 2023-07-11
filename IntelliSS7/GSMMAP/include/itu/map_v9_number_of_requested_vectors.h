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


#if !defined(_MAP_V9_NUMBER_OF_REQUESTED_VECTORS_H_)
#define _MAP_V9_NUMBER_OF_REQUESTED_VECTORS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v9 {



class NumberOfRequestedVectors : public its::AsnInteger
{
public:

    NumberOfRequestedVectors() : its::AsnInteger(false)
    {
        Initialize();
    }

    NumberOfRequestedVectors(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    NumberOfRequestedVectors(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    NumberOfRequestedVectors(const NumberOfRequestedVectors& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    NumberOfRequestedVectors(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    NumberOfRequestedVectors(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~NumberOfRequestedVectors()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new NumberOfRequestedVectors(*this);
    }

    virtual std::string GetName() const
    { return "NumberOfRequestedVectors"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_NUMBER_OF_REQUESTED_VECTORS_H_)

