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


#if !defined(_MAP_V9_PERMITTED_INTEGRITY_PROTECTION_ALGORITHMS_H_)
#define _MAP_V9_PERMITTED_INTEGRITY_PROTECTION_ALGORITHMS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v9 {



class PermittedIntegrityProtectionAlgorithms : public its::AsnOctetString
{
public:

    PermittedIntegrityProtectionAlgorithms() : its::AsnOctetString(false)
    {
        Initialize();
    }

    PermittedIntegrityProtectionAlgorithms(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    PermittedIntegrityProtectionAlgorithms(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    PermittedIntegrityProtectionAlgorithms(const PermittedIntegrityProtectionAlgorithms& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    PermittedIntegrityProtectionAlgorithms(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    PermittedIntegrityProtectionAlgorithms(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~PermittedIntegrityProtectionAlgorithms()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PermittedIntegrityProtectionAlgorithms(*this);
    }

    virtual std::string GetName() const
    { return "PermittedIntegrityProtectionAlgorithms"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_PERMITTED_INTEGRITY_PROTECTION_ALGORITHMS_H_)

