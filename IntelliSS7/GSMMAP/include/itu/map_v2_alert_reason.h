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


#if !defined(_MAP_V2_ALERT_REASON_H_)
#define _MAP_V2_ALERT_REASON_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v2 {



class AlertReason : public its::AsnEnumerated
{
public:

    AlertReason() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    AlertReason(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    AlertReason(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    AlertReason(const AlertReason& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    AlertReason(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    AlertReason(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~AlertReason()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AlertReason(*this);
    }

    virtual std::string GetName() const
    { return "AlertReason"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        ALERT_REASON_MS_PRESENT = 0,
        ALERT_REASON_MEMORY_AVAILABLE = 1

    };

    void SetMs_Present()
    { _value = 0; }

    bool IsMs_Present() const
    { return _value == 0; }

    void SetMemoryAvailable()
    { _value = 1; }

    bool IsMemoryAvailable() const
    { return _value == 1; }

};



} // namespace.

#endif    // !defined(_MAP_V2_ALERT_REASON_H_)

