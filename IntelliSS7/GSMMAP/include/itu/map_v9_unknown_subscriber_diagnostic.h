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


#if !defined(_MAP_V9_UNKNOWN_SUBSCRIBER_DIAGNOSTIC_H_)
#define _MAP_V9_UNKNOWN_SUBSCRIBER_DIAGNOSTIC_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v9 {



class UnknownSubscriberDiagnostic : public its::AsnEnumerated
{
public:

    UnknownSubscriberDiagnostic() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    UnknownSubscriberDiagnostic(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    UnknownSubscriberDiagnostic(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    UnknownSubscriberDiagnostic(const UnknownSubscriberDiagnostic& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    UnknownSubscriberDiagnostic(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    UnknownSubscriberDiagnostic(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~UnknownSubscriberDiagnostic()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new UnknownSubscriberDiagnostic(*this);
    }

    virtual std::string GetName() const
    { return "UnknownSubscriberDiagnostic"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        UNKNOWN_SUBSCRIBER_DIAGNOSTIC_IMSI_UNKNOWN = 0,
        UNKNOWN_SUBSCRIBER_DIAGNOSTIC_GPRS_SUBSCRIPTION_UNKNOWN = 1
,
        UNKNOWN_SUBSCRIBER_DIAGNOSTIC_NPDB_MISMATCH = 2
    };

    void SetImsiUnknown()
    { _value = 0; }

    bool IsImsiUnknown() const
    { return _value == 0; }

    void SetGprsSubscriptionUnknown()
    { _value = 1; }

    bool IsGprsSubscriptionUnknown() const
    { return _value == 1; }

    void SetNpdbMismatch()
    { _value = 2; SetExtension(true); }

    bool IsNpdbMismatch()
    { return (IsExtension() && (_value == 2)); }

};



} // namespace.

#endif    // !defined(_MAP_V9_UNKNOWN_SUBSCRIBER_DIAGNOSTIC_H_)

