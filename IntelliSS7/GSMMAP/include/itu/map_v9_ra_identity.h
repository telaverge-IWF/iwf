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


#if !defined(_MAP_V9_RA_IDENTITY_H_)
#define _MAP_V9_RA_IDENTITY_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v9 {



class RAIdentity : public its::AsnOctetString
{
public:

    RAIdentity() : its::AsnOctetString(false)
    {
        Initialize();
    }

    RAIdentity(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    RAIdentity(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    RAIdentity(const RAIdentity& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    RAIdentity(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    RAIdentity(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~RAIdentity()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RAIdentity(*this);
    }

    virtual std::string GetName() const
    { return "RAIdentity"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_RA_IDENTITY_H_)
