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


#if !defined(_INAP_CS2_NOTIFICATION_H_)
#define _INAP_CS2_NOTIFICATION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace inap_cs2 {



class Notification : public its::AsnEnumerated
{
public:

    Notification() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    Notification(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    Notification(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    Notification(const Notification& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    Notification(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    Notification(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~Notification()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Notification(*this);
    }

    virtual std::string GetName() const
    { return "Notification"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        NOTIFICATION_USER_ABANDON = 0,
        NOTIFICATION_CALL_FAILURE = 1,
        NOTIFICATION_NO_REPLY = 2,
        NOTIFICATION_CALL_RELEASE = 3,
        NOTIFICATION_SS_INVOCATION = 4,
        NOTIFICATION_CREDIT_LIMIT_REACHED = 5,
        NOTIFICATION_CALL_DURATION = 6,
        NOTIFICATION_CALLED_NUMBER = 7,
        NOTIFICATION_ANSWERED_CALL = 8

    };

    void SetUserAbandon()
    { _value = 0; }

    bool IsUserAbandon() const
    { return _value == 0; }

    void SetCallFailure()
    { _value = 1; }

    bool IsCallFailure() const
    { return _value == 1; }

    void SetNoReply()
    { _value = 2; }

    bool IsNoReply() const
    { return _value == 2; }

    void SetCallRelease()
    { _value = 3; }

    bool IsCallRelease() const
    { return _value == 3; }

    void SetSsInvocation()
    { _value = 4; }

    bool IsSsInvocation() const
    { return _value == 4; }

    void SetCreditLimitReached()
    { _value = 5; }

    bool IsCreditLimitReached() const
    { return _value == 5; }

    void SetCallDuration()
    { _value = 6; }

    bool IsCallDuration() const
    { return _value == 6; }

    void SetCalledNumber()
    { _value = 7; }

    bool IsCalledNumber() const
    { return _value == 7; }

    void SetAnsweredCall()
    { _value = 8; }

    bool IsAnsweredCall() const
    { return _value == 8; }

};



} // namespace.

#endif    // !defined(_INAP_CS2_NOTIFICATION_H_)
