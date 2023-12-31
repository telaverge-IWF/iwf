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


#if !defined(_INAP_CS2_EVENT_REPORT_BCSM_ARG_H_)
#define _INAP_CS2_EVENT_REPORT_BCSM_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>
#include <AsnEnumerated.h>
#include <AsnOctetString.h>
#include <AsnChoice.h>
#include <AsnInteger.h>

#include <inap_cs2_event_type_bcsm.h>
#include <inap_cs2_correlation_id.h>
#include <inap_cs2_event_specific_information_bcsm.h>
#include <inap_cs2_leg_id.h>
#include <inap_cs2_misc_call_info.h>
#include <inap_cs2_extension_field.h>
#include <inap_cs2_component_type.h>
#include <inap_cs2_component_correlation_id.h>



namespace inap_cs2 {



class EventReportBCSMArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Extensions : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef inap_cs2::ExtensionField ExtensionField;


    ////////// End Nested Class //////////

        Extensions() : its::AsnSequenceOf(false)
        {
            Initialize();
        }

        Extensions(its::Octets& octets) : its::AsnSequenceOf(false)
        {
            Initialize();
            Decode(octets);
        }

        Extensions(const Extensions& rhs) : its::AsnSequenceOf(rhs)
        {
            // Nothing to do.
        }

        Extensions(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

        static its::AsnDescObject* GetExtensionFieldStaticDescription();

    public:

        virtual ~Extensions()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Extensions(*this);
        }

        virtual std::string GetName() const
        { return "Extensions"; }

        void AddElement(ExtensionField* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetExtensionFieldStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        void AddElement(const ExtensionField& element)
        {
            its::AsnObject& asnObject = const_cast<ExtensionField&>(element);
            asnObject.SetDescription(GetExtensionFieldStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        const ExtensionField& ElementAt(int index) const
        {
            return static_cast<const ExtensionField&> (AsnSequenceOf::ElementAt(index));
        }

    };


        typedef inap_cs2::EventTypeBCSM EventTypeBCSM;


        typedef inap_cs2::CorrelationID CorrelationID;


        typedef inap_cs2::EventSpecificInformationBCSM EventSpecificInformationBCSM;


        typedef inap_cs2::LegID LegID;


        typedef inap_cs2::MiscCallInfo MiscCallInfo;


        typedef inap_cs2::ComponentType ComponentType;


        typedef inap_cs2::ComponentCorrelationID ComponentCorrelationID;


////////// End Nested Class(es) //////////

    EventReportBCSMArg() : its::AsnSequence(8, false)
    {
        Initialize();
    }

    EventReportBCSMArg(its::Octets& octets) : its::AsnSequence(8, false)
    {
        Initialize();
        Decode(octets);
    }

    EventReportBCSMArg(const EventReportBCSMArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    EventReportBCSMArg(its::AsnDescObject* description) : its::AsnSequence(8, description)
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

    static its::AsnDescObject* GetEventTypeBCSMStaticDescription();
    static its::AsnDescObject* GetBcsmEventCorrelationIDStaticDescription();
    static its::AsnDescObject* GetEventSpecificInformationBCSMStaticDescription();
    static its::AsnDescObject* GetLegIDStaticDescription();
    static its::AsnDescObject* GetMiscCallInfoStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();
    static its::AsnDescObject* GetComponentTypeStaticDescription();
    static its::AsnDescObject* GetComponentCorrelationIDStaticDescription();

public:

    virtual ~EventReportBCSMArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new EventReportBCSMArg(*this);
    }

    virtual std::string GetName() const
    { return "EventReportBCSMArg"; }

    void SetEventTypeBCSM(EventTypeBCSM* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEventTypeBCSMStaticDescription());
        AddElement(0, element);
    }

    void SetEventTypeBCSM(const EventTypeBCSM& element)
    {
        its::AsnObject& asnObject = const_cast<EventTypeBCSM&>(element);
        asnObject.SetDescription(GetEventTypeBCSMStaticDescription());
        AddElement(0, element);
    }

    const EventTypeBCSM& GetEventTypeBCSM() const
    {
        return static_cast<const EventTypeBCSM&> (ElementAt(0));
    }

    void SetBcsmEventCorrelationID(CorrelationID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBcsmEventCorrelationIDStaticDescription());
        AddElement(1, element);
    }

    void SetBcsmEventCorrelationID(const CorrelationID& element)
    {
        its::AsnObject& asnObject = const_cast<CorrelationID&>(element);
        asnObject.SetDescription(GetBcsmEventCorrelationIDStaticDescription());
        AddElement(1, element);
    }

    bool OptionBcsmEventCorrelationID() const
    {
        return Contains(1);
    }

    const CorrelationID& GetBcsmEventCorrelationID() const
    {
        ITS_REQUIRE(OptionBcsmEventCorrelationID());
        return static_cast<const CorrelationID&> (ElementAt(1));
    }

    void SetEventSpecificInformationBCSM(EventSpecificInformationBCSM* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEventSpecificInformationBCSMStaticDescription());
        AddElement(2, element);
    }

    void SetEventSpecificInformationBCSM(const EventSpecificInformationBCSM& element)
    {
        its::AsnObject& asnObject = const_cast<EventSpecificInformationBCSM&>(element);
        asnObject.SetDescription(GetEventSpecificInformationBCSMStaticDescription());
        AddElement(2, element);
    }

    bool OptionEventSpecificInformationBCSM() const
    {
        return Contains(2);
    }

    const EventSpecificInformationBCSM& GetEventSpecificInformationBCSM() const
    {
        ITS_REQUIRE(OptionEventSpecificInformationBCSM());
        return static_cast<const EventSpecificInformationBCSM&> (ElementAt(2));
    }

    void SetLegID(LegID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLegIDStaticDescription());
        AddElement(3, element);
    }

    void SetLegID(const LegID& element)
    {
        its::AsnObject& asnObject = const_cast<LegID&>(element);
        asnObject.SetDescription(GetLegIDStaticDescription());
        AddElement(3, element);
    }

    bool OptionLegID() const
    {
        return Contains(3);
    }

    const LegID& GetLegID() const
    {
        ITS_REQUIRE(OptionLegID());
        return static_cast<const LegID&> (ElementAt(3));
    }

    void SetMiscCallInfo(MiscCallInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMiscCallInfoStaticDescription());
        AddElement(4, element);
    }

    void SetMiscCallInfo(const MiscCallInfo& element)
    {
        its::AsnObject& asnObject = const_cast<MiscCallInfo&>(element);
        asnObject.SetDescription(GetMiscCallInfoStaticDescription());
        AddElement(4, element);
    }

    const MiscCallInfo& GetMiscCallInfo() const
    {
        return static_cast<const MiscCallInfo&> (ElementAt(4));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(5, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(5, element);
    }

    bool OptionExtensions() const
    {
        return Contains(5);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(5));
    }

    void SetComponentType(ComponentType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetComponentTypeStaticDescription());
        AddElement(6, element);
    }

    void SetComponentType(const ComponentType& element)
    {
        its::AsnObject& asnObject = const_cast<ComponentType&>(element);
        asnObject.SetDescription(GetComponentTypeStaticDescription());
        AddElement(6, element);
    }

    bool OptionComponentType() const
    {
        return Contains(6);
    }

    const ComponentType& GetComponentType() const
    {
        ITS_REQUIRE(OptionComponentType());
        return static_cast<const ComponentType&> (ElementAt(6));
    }

    void SetComponentCorrelationID(ComponentCorrelationID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetComponentCorrelationIDStaticDescription());
        AddElement(7, element);
    }

    void SetComponentCorrelationID(const ComponentCorrelationID& element)
    {
        its::AsnObject& asnObject = const_cast<ComponentCorrelationID&>(element);
        asnObject.SetDescription(GetComponentCorrelationIDStaticDescription());
        AddElement(7, element);
    }

    bool OptionComponentCorrelationID() const
    {
        return Contains(7);
    }

    const ComponentCorrelationID& GetComponentCorrelationID() const
    {
        ITS_REQUIRE(OptionComponentCorrelationID());
        return static_cast<const ComponentCorrelationID&> (ElementAt(7));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_EVENT_REPORT_BCSM_ARG_H_)

