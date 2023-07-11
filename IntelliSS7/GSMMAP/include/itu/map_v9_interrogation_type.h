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


#if !defined(_MAP_V9_INTERROGATION_TYPE_H_)
#define _MAP_V9_INTERROGATION_TYPE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v9 {



class InterrogationType : public its::AsnEnumerated
{
public:

    InterrogationType() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    InterrogationType(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    InterrogationType(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    InterrogationType(const InterrogationType& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    InterrogationType(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    InterrogationType(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~InterrogationType()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new InterrogationType(*this);
    }

    virtual std::string GetName() const
    { return "InterrogationType"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        INTERROGATION_TYPE_BASIC_CALL = 0,
        INTERROGATION_TYPE_FORWARDING = 1

    };

    void SetBasicCall()
    { _value = 0; }

    bool IsBasicCall() const
    { return _value == 0; }

    void SetForwarding()
    { _value = 1; }

    bool IsForwarding() const
    { return _value == 1; }

};



} // namespace.

#endif    // !defined(_MAP_V9_INTERROGATION_TYPE_H_)

