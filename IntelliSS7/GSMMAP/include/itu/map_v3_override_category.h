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


#if !defined(_MAP_V3_OVERRIDE_CATEGORY_H_)
#define _MAP_V3_OVERRIDE_CATEGORY_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v3 {



class OverrideCategory : public its::AsnEnumerated
{
public:

    OverrideCategory() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    OverrideCategory(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    OverrideCategory(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    OverrideCategory(const OverrideCategory& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    OverrideCategory(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    OverrideCategory(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~OverrideCategory()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new OverrideCategory(*this);
    }

    virtual std::string GetName() const
    { return "OverrideCategory"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        OVERRIDE_CATEGORY_OVERRIDE_ENABLED = 0,
        OVERRIDE_CATEGORY_OVERRIDE_DISABLED = 1

    };

    void SetOverrideEnabled()
    { _value = 0; }

    bool IsOverrideEnabled() const
    { return _value == 0; }

    void SetOverrideDisabled()
    { _value = 1; }

    bool IsOverrideDisabled() const
    { return _value == 1; }

};



} // namespace.

#endif    // !defined(_MAP_V3_OVERRIDE_CATEGORY_H_)

