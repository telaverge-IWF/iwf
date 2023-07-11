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


#if !defined(_MAP_V9_SECURITY_PARAMETERS_INDEX_H_)
#define _MAP_V9_SECURITY_PARAMETERS_INDEX_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v9 {



class SecurityParametersIndex : public its::AsnOctetString
{
public:

    SecurityParametersIndex() : its::AsnOctetString(false)
    {
        Initialize();
    }

    SecurityParametersIndex(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    SecurityParametersIndex(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    SecurityParametersIndex(const SecurityParametersIndex& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    SecurityParametersIndex(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    SecurityParametersIndex(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~SecurityParametersIndex()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SecurityParametersIndex(*this);
    }

    virtual std::string GetName() const
    { return "SecurityParametersIndex"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_SECURITY_PARAMETERS_INDEX_H_)

