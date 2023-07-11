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


#if !defined(_CAP_V3_SGSN_CAPABILITIES_H_)
#define _CAP_V3_SGSN_CAPABILITIES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace cap_v3 {



class SGSNCapabilities : public its::AsnOctetString
{
public:

    SGSNCapabilities() : its::AsnOctetString(false)
    {
        Initialize();
    }

    SGSNCapabilities(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    SGSNCapabilities(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    SGSNCapabilities(const SGSNCapabilities& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    SGSNCapabilities(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    SGSNCapabilities(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~SGSNCapabilities()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SGSNCapabilities(*this);
    }

    virtual std::string GetName() const
    { return "SGSNCapabilities"; }

};



} // namespace.

#endif    // !defined(_CAP_V3_SGSN_CAPABILITIES_H_)

