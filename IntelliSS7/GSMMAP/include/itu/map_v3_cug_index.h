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


#if !defined(_MAP_V3_CUG_INDEX_H_)
#define _MAP_V3_CUG_INDEX_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v3 {



class CUG_Index : public its::AsnInteger
{
public:

    CUG_Index() : its::AsnInteger(false)
    {
        Initialize();
    }

    CUG_Index(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    CUG_Index(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    CUG_Index(const CUG_Index& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    CUG_Index(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    CUG_Index(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~CUG_Index()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CUG_Index(*this);
    }

    virtual std::string GetName() const
    { return "CUG_Index"; }

};



} // namespace.

#endif    // !defined(_MAP_V3_CUG_INDEX_H_)

