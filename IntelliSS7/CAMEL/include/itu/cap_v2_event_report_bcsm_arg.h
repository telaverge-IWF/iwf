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


#if !defined(_CAP_V2_EVENT_REPORT_BCSM_ARG_H_)
#define _CAP_V2_EVENT_REPORT_BCSM_ARG_H_

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
#include <AsnChoice.h>

#include <cap_v2_event_type_bcsm.h>
#include <cap_v2_event_specific_information_bcsm.h>
#include <cap_v2_receiving_side_id.h>
#include <cap_v2_misc_call_info.h>
#include <cap_v2_extension_field.h>



namespace cap_v2 {



class EventReportBCSMArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Extensions : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef cap_v2::ExtensionField ExtensionField;


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


        typedef cap_v2::EventTypeBCSM EventTypeBCSM;


        typedef cap_v2::EventSpecificInformationBCSM EventSpecificInformationBCSM;


        typedef cap_v2::ReceivingSideID ReceivingSideID;


        typedef cap_v2::MiscCallInfo MiscCallInfo;


////////// End Nested Class(es) //////////

    EventReportBCSMArg() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    EventReportBCSMArg(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    EventReportBCSMArg(const EventReportBCSMArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    EventReportBCSMArg(its::AsnDescObject* description) : its::AsnSequence(5, description)
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
    static its::AsnDescObject* GetEventSpecificInformationBCSMStaticDescription();
    static its::AsnDescObject* GetLegIDStaticDescription();
    static its::AsnDescObject* GetMiscCallInfoStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();

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

    void SetEventSpecificInformationBCSM(EventSpecificInformationBCSM* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEventSpecificInformationBCSMStaticDescription());
        AddElement(1, element);
    }

    void SetEventSpecificInformationBCSM(const EventSpecificInformationBCSM& element)
    {
        its::AsnObject& asnObject = const_cast<EventSpecificInformationBCSM&>(element);
        asnObject.SetDescription(GetEventSpecificInformationBCSMStaticDescription());
        AddElement(1, element);
    }

    bool OptionEventSpecificInformationBCSM() const
    {
        return Contains(1);
    }

    const EventSpecificInformationBCSM& GetEventSpecificInformationBCSM() const
    {
        ITS_REQUIRE(OptionEventSpecificInformationBCSM());
        return static_cast<const EventSpecificInformationBCSM&> (ElementAt(1));
    }

    void SetLegID(ReceivingSideID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLegIDStaticDescription());
        AddElement(2, element);
    }

    void SetLegID(const ReceivingSideID& element)
    {
        its::AsnObject& asnObject = const_cast<ReceivingSideID&>(element);
        asnObject.SetDescription(GetLegIDStaticDescription());
        AddElement(2, element);
    }

    bool OptionLegID() const
    {
        return Contains(2);
    }

    const ReceivingSideID& GetLegID() const
    {
        ITS_REQUIRE(OptionLegID());
        return static_cast<const ReceivingSideID&> (ElementAt(2));
    }

    void SetMiscCallInfo(MiscCallInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMiscCallInfoStaticDescription());
        AddElement(3, element);
    }

    void SetMiscCallInfo(const MiscCallInfo& element)
    {
        its::AsnObject& asnObject = const_cast<MiscCallInfo&>(element);
        asnObject.SetDescription(GetMiscCallInfoStaticDescription());
        AddElement(3, element);
    }

    const MiscCallInfo& GetMiscCallInfo() const
    {
        return static_cast<const MiscCallInfo&> (ElementAt(3));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(4, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(4, element);
    }

    bool OptionExtensions() const
    {
        return Contains(4);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(4));
    }

};



} // namespace.

#endif    // !defined(_CAP_V2_EVENT_REPORT_BCSM_ARG_H_)

