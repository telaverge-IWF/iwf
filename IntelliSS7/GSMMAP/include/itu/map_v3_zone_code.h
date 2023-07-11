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


#if !defined(_MAP_V3_ZONE_CODE_H_)
#define _MAP_V3_ZONE_CODE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace map_v3 {



class ZoneCode : public its::AsnOctetString
{
public:

    ZoneCode() : its::AsnOctetString(false)
    {
        Initialize();
    }

    ZoneCode(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    ZoneCode(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    ZoneCode(const ZoneCode& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    ZoneCode(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    ZoneCode(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~ZoneCode()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ZoneCode(*this);
    }

    virtual std::string GetName() const
    { return "ZoneCode"; }

};



} // namespace.

#endif    // !defined(_MAP_V3_ZONE_CODE_H_)

