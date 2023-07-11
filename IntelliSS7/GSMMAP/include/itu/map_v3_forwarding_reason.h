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


#if !defined(_MAP_V3_FORWARDING_REASON_H_)
#define _MAP_V3_FORWARDING_REASON_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v3 {



class ForwardingReason : public its::AsnEnumerated
{
public:

    ForwardingReason() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    ForwardingReason(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    ForwardingReason(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    ForwardingReason(const ForwardingReason& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    ForwardingReason(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    ForwardingReason(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~ForwardingReason()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ForwardingReason(*this);
    }

    virtual std::string GetName() const
    { return "ForwardingReason"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        FORWARDING_REASON_NOT_REACHABLE = 0,
        FORWARDING_REASON_BUSY = 1,
        FORWARDING_REASON_NO_REPLY = 2

    };

    void SetNotReachable()
    { _value = 0; }

    bool IsNotReachable() const
    { return _value == 0; }

    void SetBusy()
    { _value = 1; }

    bool IsBusy() const
    { return _value == 1; }

    void SetNoReply()
    { _value = 2; }

    bool IsNoReply() const
    { return _value == 2; }

};



} // namespace.

#endif    // !defined(_MAP_V3_FORWARDING_REASON_H_)

