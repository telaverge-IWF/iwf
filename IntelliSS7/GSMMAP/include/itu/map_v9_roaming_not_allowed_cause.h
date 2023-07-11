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


#if !defined(_MAP_V9_ROAMING_NOT_ALLOWED_CAUSE_H_)
#define _MAP_V9_ROAMING_NOT_ALLOWED_CAUSE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v9 {



class RoamingNotAllowedCause : public its::AsnEnumerated
{
public:

    RoamingNotAllowedCause() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    RoamingNotAllowedCause(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    RoamingNotAllowedCause(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    RoamingNotAllowedCause(const RoamingNotAllowedCause& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    RoamingNotAllowedCause(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    RoamingNotAllowedCause(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~RoamingNotAllowedCause()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RoamingNotAllowedCause(*this);
    }

    virtual std::string GetName() const
    { return "RoamingNotAllowedCause"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        ROAMING_NOT_ALLOWED_CAUSE_PLMN_ROAMING_NOT_ALLOWED = 0,
        ROAMING_NOT_ALLOWED_CAUSE_OPERATOR_DETERMINED_BARRING = 3

    };

    void SetPlmnRoamingNotAllowed()
    { _value = 0; }

    bool IsPlmnRoamingNotAllowed() const
    { return _value == 0; }

    void SetOperatorDeterminedBarring()
    { _value = 3; }

    bool IsOperatorDeterminedBarring() const
    { return _value == 3; }

};



} // namespace.

#endif    // !defined(_MAP_V9_ROAMING_NOT_ALLOWED_CAUSE_H_)

