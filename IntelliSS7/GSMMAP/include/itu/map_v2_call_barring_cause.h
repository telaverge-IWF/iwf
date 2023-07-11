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


#if !defined(_MAP_V2_CALL_BARRING_CAUSE_H_)
#define _MAP_V2_CALL_BARRING_CAUSE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v2 {



class CallBarringCause : public its::AsnEnumerated
{
public:

    CallBarringCause() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    CallBarringCause(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    CallBarringCause(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    CallBarringCause(const CallBarringCause& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    CallBarringCause(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    CallBarringCause(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~CallBarringCause()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CallBarringCause(*this);
    }

    virtual std::string GetName() const
    { return "CallBarringCause"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        CALL_BARRING_CAUSE_BARRING_SERVICE_ACTIVE = 0,
        CALL_BARRING_CAUSE_OPERATOR_BARRING = 1

    };

    void SetBarringServiceActive()
    { _value = 0; }

    bool IsBarringServiceActive() const
    { return _value == 0; }

    void SetOperatorBarring()
    { _value = 1; }

    bool IsOperatorBarring() const
    { return _value == 1; }

};



} // namespace.

#endif    // !defined(_MAP_V2_CALL_BARRING_CAUSE_H_)

