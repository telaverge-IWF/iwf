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


#if !defined(_CAP_V3_CONTROL_TYPE_H_)
#define _CAP_V3_CONTROL_TYPE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace cap_v3 {



class ControlType : public its::AsnEnumerated
{
public:

    ControlType() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    ControlType(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    ControlType(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    ControlType(const ControlType& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    ControlType(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    ControlType(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~ControlType()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ControlType(*this);
    }

    virtual std::string GetName() const
    { return "ControlType"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        CONTROL_TYPE_SCP_OVERLOADED = 0,
        CONTROL_TYPE_MANUALLY_INITIATED = 1

    };

    void SetSCPOverloaded()
    { _value = 0; }

    bool IsSCPOverloaded() const
    { return _value == 0; }

    void SetManuallyInitiated()
    { _value = 1; }

    bool IsManuallyInitiated() const
    { return _value == 1; }

};



} // namespace.

#endif    // !defined(_CAP_V3_CONTROL_TYPE_H_)
