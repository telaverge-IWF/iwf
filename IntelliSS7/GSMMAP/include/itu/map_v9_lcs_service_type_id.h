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


#if !defined(_MAP_V9_LCS_SERVICE_TYPE_ID_H_)
#define _MAP_V9_LCS_SERVICE_TYPE_ID_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v9 {



class LCSServiceTypeID : public its::AsnInteger
{
public:

    LCSServiceTypeID() : its::AsnInteger(false)
    {
        Initialize();
    }

    LCSServiceTypeID(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    LCSServiceTypeID(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    LCSServiceTypeID(const LCSServiceTypeID& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    LCSServiceTypeID(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    LCSServiceTypeID(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~LCSServiceTypeID()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new LCSServiceTypeID(*this);
    }

    virtual std::string GetName() const
    { return "LCSServiceTypeID"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_LCS_SERVICE_TYPE_ID_H_)

