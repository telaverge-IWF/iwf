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


#if !defined(_MAP_V13_UNAUTHORIZED_LCS_CLIENT_DIAGNOSTIC_H_)
#define _MAP_V13_UNAUTHORIZED_LCS_CLIENT_DIAGNOSTIC_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v13 {



class UnauthorizedLCSClient_Diagnostic : public its::AsnEnumerated
{
public:

    UnauthorizedLCSClient_Diagnostic() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    UnauthorizedLCSClient_Diagnostic(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    UnauthorizedLCSClient_Diagnostic(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    UnauthorizedLCSClient_Diagnostic(const UnauthorizedLCSClient_Diagnostic& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    UnauthorizedLCSClient_Diagnostic(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    UnauthorizedLCSClient_Diagnostic(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~UnauthorizedLCSClient_Diagnostic()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new UnauthorizedLCSClient_Diagnostic(*this);
    }

    virtual std::string GetName() const
    { return "UnauthorizedLCSClient_Diagnostic"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        UNAUTHORIZED_LCS_CLIENT_DIAGNOSTIC_NO_ADDITIONAL_INFORMATION = 0,
        UNAUTHORIZED_LCS_CLIENT_DIAGNOSTIC_CLIENT_NOT_IN_MS_PRIVACY_EXCEPTION_LIST = 1,
        UNAUTHORIZED_LCS_CLIENT_DIAGNOSTIC_CALL_TO_CLIENT_NOT_SETUP = 2,
        UNAUTHORIZED_LCS_CLIENT_DIAGNOSTIC_PRIVACY_OVERRIDE_NOT_APPLICABLE = 3,
        UNAUTHORIZED_LCS_CLIENT_DIAGNOSTIC_DISALLOWED_BY_LOCAL_REGULATORY_REQUIREMENTS = 4
,
        UNAUTHORIZED_LCS_CLIENT_DIAGNOSTIC_UNAUTHORIZED_PRIVACY_CLASS = 5,
        UNAUTHORIZED_LCS_CLIENT_DIAGNOSTIC_UNAUTHORIZED_CALL_SESSION_UNRELATED_EXTERNAL_CLIENT = 6,
        UNAUTHORIZED_LCS_CLIENT_DIAGNOSTIC_UNAUTHORIZED_CALL_SESSION_RELATED_EXTERNAL_CLIENT = 7
    };

    void SetNoAdditionalInformation()
    { _value = 0; }

    bool IsNoAdditionalInformation() const
    { return _value == 0; }

    void SetClientNotInMSPrivacyExceptionList()
    { _value = 1; }

    bool IsClientNotInMSPrivacyExceptionList() const
    { return _value == 1; }

    void SetCallToClientNotSetup()
    { _value = 2; }

    bool IsCallToClientNotSetup() const
    { return _value == 2; }

    void SetPrivacyOverrideNotApplicable()
    { _value = 3; }

    bool IsPrivacyOverrideNotApplicable() const
    { return _value == 3; }

    void SetDisallowedByLocalRegulatoryRequirements()
    { _value = 4; }

    bool IsDisallowedByLocalRegulatoryRequirements() const
    { return _value == 4; }

    void SetUnauthorizedPrivacyClass()
    { _value = 5; SetExtension(true); }

    bool IsUnauthorizedPrivacyClass()
    { return (IsExtension() && (_value == 5)); }

    void SetUnauthorizedCallSessionUnrelatedExternalClient()
    { _value = 6; SetExtension(true); }

    bool IsUnauthorizedCallSessionUnrelatedExternalClient()
    { return (IsExtension() && (_value == 6)); }

    void SetUnauthorizedCallSessionRelatedExternalClient()
    { _value = 7; SetExtension(true); }

    bool IsUnauthorizedCallSessionRelatedExternalClient()
    { return (IsExtension() && (_value == 7)); }

};



} // namespace.

#endif    // !defined(_MAP_V13_UNAUTHORIZED_LCS_CLIENT_DIAGNOSTIC_H_)

