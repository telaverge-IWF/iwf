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


#if !defined(_CAP_V3_HIGH_LAYER_COMPATIBILITY_H_)
#define _CAP_V3_HIGH_LAYER_COMPATIBILITY_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace cap_v3 {



class HighLayerCompatibility : public its::AsnOctetString
{
public:

    HighLayerCompatibility() : its::AsnOctetString(false)
    {
        Initialize();
    }

    HighLayerCompatibility(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    HighLayerCompatibility(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    HighLayerCompatibility(const HighLayerCompatibility& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    HighLayerCompatibility(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    HighLayerCompatibility(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~HighLayerCompatibility()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new HighLayerCompatibility(*this);
    }

    virtual std::string GetName() const
    { return "HighLayerCompatibility"; }

};



} // namespace.

#endif    // !defined(_CAP_V3_HIGH_LAYER_COMPATIBILITY_H_)
