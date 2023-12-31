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


#if !defined(_CAP_V3_EVENT_TYPE_SMS_H_)
#define _CAP_V3_EVENT_TYPE_SMS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace cap_v3 {



class EventTypeSMS : public its::AsnEnumerated
{
public:

    EventTypeSMS() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    EventTypeSMS(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    EventTypeSMS(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    EventTypeSMS(const EventTypeSMS& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    EventTypeSMS(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    EventTypeSMS(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

    virtual ~EventTypeSMS()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new EventTypeSMS(*this);
    }

    virtual std::string GetName() const
    { return "EventTypeSMS"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        EVENT_TYPE_SMS_SMS_COLLECTED_INFO = 1,
        EVENT_TYPE_SMS_O_SMS_FAILURE = 2,
        EVENT_TYPE_SMS_O_SMS_SUBMITTED = 3,
        EVENT_TYPE_SMS_SMS_DELIVERY_REQUESTED = 11,
        EVENT_TYPE_SMS_T_SMS_FAILURE = 12,
        EVENT_TYPE_SMS_T_SMS_SUBMITTED = 13

    };

    void SetSms_CollectedInfo()
    { _value = 1; }

    bool IsSms_CollectedInfo() const
    { return _value == 1; }

    void SetO_smsFailure()
    { _value = 2; }

    bool IsO_smsFailure() const
    { return _value == 2; }

    void SetO_smsSubmitted()
    { _value = 3; }

    bool IsO_smsSubmitted() const
    { return _value == 3; }

    void SetSms_DeliveryRequested()
    { _value = 11; }

    bool IsSms_DeliveryRequested() const
    { return _value == 11; }

    void SetT_smsFailure()
    { _value = 12; }

    bool IsT_smsFailure() const
    { return _value == 12; }

    void SetT_smsSubmitted()
    { _value = 13; }

    bool IsT_smsSubmitted() const
    { return _value == 13; }

};



} // namespace.

#endif    // !defined(_CAP_V3_EVENT_TYPE_SMS_H_)

