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


#if !defined(_MAP_V2_PW_REGISTRATION_FAILURE_CAUSE_H_)
#define _MAP_V2_PW_REGISTRATION_FAILURE_CAUSE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v2 {



class PW_RegistrationFailureCause : public its::AsnEnumerated
{
public:

    PW_RegistrationFailureCause() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    PW_RegistrationFailureCause(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    PW_RegistrationFailureCause(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    PW_RegistrationFailureCause(const PW_RegistrationFailureCause& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    PW_RegistrationFailureCause(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    PW_RegistrationFailureCause(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~PW_RegistrationFailureCause()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PW_RegistrationFailureCause(*this);
    }

    virtual std::string GetName() const
    { return "PW_RegistrationFailureCause"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        PW_REGISTRATION_FAILURE_CAUSE_UNDETERMINED = 0,
        PW_REGISTRATION_FAILURE_CAUSE_INVALID_FORMAT = 1,
        PW_REGISTRATION_FAILURE_CAUSE_NEW_PASSWORDS_MISMATCH = 2

    };

    void SetUndetermined()
    { _value = 0; }

    bool IsUndetermined() const
    { return _value == 0; }

    void SetInvalidFormat()
    { _value = 1; }

    bool IsInvalidFormat() const
    { return _value == 1; }

    void SetNewPasswordsMismatch()
    { _value = 2; }

    bool IsNewPasswordsMismatch() const
    { return _value == 2; }

};



} // namespace.

#endif    // !defined(_MAP_V2_PW_REGISTRATION_FAILURE_CAUSE_H_)

