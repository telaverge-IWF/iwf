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


#if !defined(_MAP_V13_UE_SRVCC_CAPABILITY_H_)
#define _MAP_V13_UE_SRVCC_CAPABILITY_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v13 {



class UE_SRVCC_Capability : public its::AsnEnumerated
{
public:

    UE_SRVCC_Capability() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    UE_SRVCC_Capability(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    UE_SRVCC_Capability(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    UE_SRVCC_Capability(const UE_SRVCC_Capability& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    UE_SRVCC_Capability(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    UE_SRVCC_Capability(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~UE_SRVCC_Capability()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new UE_SRVCC_Capability(*this);
    }

    virtual std::string GetName() const
    { return "UE_SRVCC_Capability"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        UE_SRVCC_CAPABILITY_UE_SRVCC_NOT_SUPPORTED = 0,
        UE_SRVCC_CAPABILITY_UE_SRVCC_SUPPORTED = 1

    };

    void SetUe_srvcc_not_supported()
    { _value = 0; }

    bool IsUe_srvcc_not_supported() const
    { return _value == 0; }

    void SetUe_srvcc_supported()
    { _value = 1; }

    bool IsUe_srvcc_supported() const
    { return _value == 1; }

};



} // namespace.

#endif    // !defined(_MAP_V13_UE_SRVCC_CAPABILITY_H_)

