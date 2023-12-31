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


#if !defined(_MAP_V9_EXT_TELESERVICE_CODE_H_)
#define _MAP_V9_EXT_TELESERVICE_CODE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v9 {



class Ext_TeleserviceCode : public its::AsnOctetString
{
public:

    Ext_TeleserviceCode() : its::AsnOctetString(false)
    {
        Initialize();
    }

    Ext_TeleserviceCode(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    Ext_TeleserviceCode(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    Ext_TeleserviceCode(const Ext_TeleserviceCode& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    Ext_TeleserviceCode(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    Ext_TeleserviceCode(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~Ext_TeleserviceCode()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Ext_TeleserviceCode(*this);
    }

    virtual std::string GetName() const
    { return "Ext_TeleserviceCode"; }

};



} // namespace.

#endif    // !defined(_MAP_V9_EXT_TELESERVICE_CODE_H_)

