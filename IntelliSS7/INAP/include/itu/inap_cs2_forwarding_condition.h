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


#if !defined(_INAP_CS2_FORWARDING_CONDITION_H_)
#define _INAP_CS2_FORWARDING_CONDITION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace inap_cs2 {



class ForwardingCondition : public its::AsnEnumerated
{
public:

    ForwardingCondition() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    ForwardingCondition(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    ForwardingCondition(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    ForwardingCondition(const ForwardingCondition& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    ForwardingCondition(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    ForwardingCondition(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~ForwardingCondition()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ForwardingCondition(*this);
    }

    virtual std::string GetName() const
    { return "ForwardingCondition"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        FORWARDING_CONDITION_BUSY = 0,
        FORWARDING_CONDITION_NOANSWER = 1,
        FORWARDING_CONDITION_ANY = 2

    };

    void SetBusy()
    { _value = 0; }

    bool IsBusy() const
    { return _value == 0; }

    void SetNoanswer()
    { _value = 1; }

    bool IsNoanswer() const
    { return _value == 1; }

    void SetAny()
    { _value = 2; }

    bool IsAny() const
    { return _value == 2; }

};



} // namespace.

#endif    // !defined(_INAP_CS2_FORWARDING_CONDITION_H_)

