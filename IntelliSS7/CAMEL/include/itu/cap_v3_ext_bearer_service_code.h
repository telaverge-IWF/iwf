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


#if !defined(_CAP_V3_EXT_BEARER_SERVICE_CODE_H_)
#define _CAP_V3_EXT_BEARER_SERVICE_CODE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace cap_v3 {



class Ext_BearerServiceCode : public its::AsnOctetString
{
public:

    Ext_BearerServiceCode() : its::AsnOctetString(false)
    {
        Initialize();
    }

    Ext_BearerServiceCode(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    Ext_BearerServiceCode(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    Ext_BearerServiceCode(const Ext_BearerServiceCode& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    Ext_BearerServiceCode(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    Ext_BearerServiceCode(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~Ext_BearerServiceCode()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Ext_BearerServiceCode(*this);
    }

    virtual std::string GetName() const
    { return "Ext_BearerServiceCode"; }

};



} // namespace.

#endif    // !defined(_CAP_V3_EXT_BEARER_SERVICE_CODE_H_)

