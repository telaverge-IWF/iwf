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


#if !defined(_INAP_CS2_ACTION_PERFORMED_H_)
#define _INAP_CS2_ACTION_PERFORMED_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace inap_cs2 {



class ActionPerformed : public its::AsnEnumerated
{
public:

    ActionPerformed() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    ActionPerformed(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    ActionPerformed(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    ActionPerformed(const ActionPerformed& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    ActionPerformed(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    ActionPerformed(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~ActionPerformed()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ActionPerformed(*this);
    }

    virtual std::string GetName() const
    { return "ActionPerformed"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        ACTION_PERFORMED_ACTIVATED = 1,
        ACTION_PERFORMED_DEACTIVATED = 2,
        ACTION_PERFORMED_ALREADY_ACTIVE = 3,
        ACTION_PERFORMED_ALREADY_INACTIVE = 4,
        ACTION_PERFORMED_IS_ACTIVE = 5,
        ACTION_PERFORMED_IS_INACTIVE = 6

    };

    void SetActivated()
    { _value = 1; }

    bool IsActivated() const
    { return _value == 1; }

    void SetDeactivated()
    { _value = 2; }

    bool IsDeactivated() const
    { return _value == 2; }

    void SetAlreadyActive()
    { _value = 3; }

    bool IsAlreadyActive() const
    { return _value == 3; }

    void SetAlreadyInactive()
    { _value = 4; }

    bool IsAlreadyInactive() const
    { return _value == 4; }

    void SetIsActive()
    { _value = 5; }

    bool IsIsActive() const
    { return _value == 5; }

    void SetIsInactive()
    { _value = 6; }

    bool IsIsInactive() const
    { return _value == 6; }

};



} // namespace.

#endif    // !defined(_INAP_CS2_ACTION_PERFORMED_H_)
