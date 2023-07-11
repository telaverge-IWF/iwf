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


#if !defined(_INAP_CS2_BCUSM_EVENT_H_)
#define _INAP_CS2_BCUSM_EVENT_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>

#include <inap_cs2_event_type_bcusm.h>
#include <inap_cs2_monitor_mode.h>



namespace inap_cs2 {



class BCUSMEvent : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef inap_cs2::EventTypeBCUSM EventTypeBCUSM;


        typedef inap_cs2::MonitorMode MonitorMode;


////////// End Nested Class(es) //////////

    BCUSMEvent() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    BCUSMEvent(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    BCUSMEvent(const BCUSMEvent& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    BCUSMEvent(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetEventTypeStaticDescription();
    static its::AsnDescObject* GetMonitorModeStaticDescription();

public:

    virtual ~BCUSMEvent()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new BCUSMEvent(*this);
    }

    virtual std::string GetName() const
    { return "BCUSMEvent"; }

    void SetEventType(EventTypeBCUSM* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEventTypeStaticDescription());
        AddElement(0, element);
    }

    void SetEventType(const EventTypeBCUSM& element)
    {
        its::AsnObject& asnObject = const_cast<EventTypeBCUSM&>(element);
        asnObject.SetDescription(GetEventTypeStaticDescription());
        AddElement(0, element);
    }

    const EventTypeBCUSM& GetEventType() const
    {
        return static_cast<const EventTypeBCUSM&> (ElementAt(0));
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

#endif    // !defined(_INAP_CS2_BCUSM_EVENT_H_)
