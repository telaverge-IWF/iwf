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


#if !defined(_CAP_V3_GPRS_EVENT_H_)
#define _CAP_V3_GPRS_EVENT_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>

#include <cap_v3_gprs_event_type.h>
#include <cap_v3_monitor_mode.h>



namespace cap_v3 {



class GPRSEvent : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v3::GPRSEventType GPRSEventType;


        typedef cap_v3::MonitorMode MonitorMode;


////////// End Nested Class(es) //////////

    GPRSEvent() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    GPRSEvent(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    GPRSEvent(const GPRSEvent& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    GPRSEvent(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetGPRSEventTypeStaticDescription();
    static its::AsnDescObject* GetMonitorModeStaticDescription();

public:

    virtual ~GPRSEvent()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new GPRSEvent(*this);
    }

    virtual std::string GetName() const
    { return "GPRSEvent"; }

    void SetGPRSEventType(GPRSEventType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGPRSEventTypeStaticDescription());
        AddElement(0, element);
    }

    void SetGPRSEventType(const GPRSEventType& element)
    {
        its::AsnObject& asnObject = const_cast<GPRSEventType&>(element);
        asnObject.SetDescription(GetGPRSEventTypeStaticDescription());
        AddElement(0, element);
    }

    const GPRSEventType& GetGPRSEventType() const
    {
        return static_cast<const GPRSEventType&> (ElementAt(0));
    }

    void SetMonitorMode(MonitorMode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMonitorModeStaticDescription());
        AddElement(1, element);
    }

    void SetMonitorMode(const MonitorMode& element)
    {
        its::AsnObject& asnObject = const_cast<MonitorMode&>(element);
        asnObject.SetDescription(GetMonitorModeStaticDescription());
        AddElement(1, element);
    }

    const MonitorMode& GetMonitorMode() const
    {
        return static_cast<const MonitorMode&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_GPRS_EVENT_H_)

