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


#if !defined(_CAP_V3_EVENT_REPORT_SMS_ARG_H_)
#define _CAP_V3_EVENT_REPORT_SMS_ARG_H_

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

#include <cap_v3_event_type_sms.h>
#include <cap_v3_event_specific_information_sms.h>
#include <cap_v3_misc_call_info.h>
#include <cap_v3_extension_field.h>



namespace cap_v3 {



class EventReportSMSArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Extensions : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef cap_v3::ExtensionField ExtensionField;


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


        typedef cap_v3::EventTypeSMS EventTypeSMS;


        typedef cap_v3::EventSpecificInformationSMS EventSpecificInformationSMS;


        typedef cap_v3::MiscCallInfo MiscCallInfo;


////////// End Nested Class(es) //////////

    EventReportSMSArg() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    EventReportSMSArg(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    EventReportSMSArg(const EventReportSMSArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    EventReportSMSArg(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetEventTypeSMSStaticDescription();
    static its::AsnDescObject* GetEventSpecificInformationSMSStaticDescription();
    static its::AsnDescObject* GetMiscCallInfoStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();

public:

    virtual ~EventReportSMSArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new EventReportSMSArg(*this);
    }

    virtual std::string GetName() const
    { return "EventReportSMSArg"; }

    void SetEventTypeSMS(EventTypeSMS* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEventTypeSMSStaticDescription());
        AddElement(0, element);
    }

    void SetEventTypeSMS(const EventTypeSMS& element)
    {
        its::AsnObject& asnObject = const_cast<EventTypeSMS&>(element);
        asnObject.SetDescription(GetEventTypeSMSStaticDescription());
        AddElement(0, element);
    }

    const EventTypeSMS& GetEventTypeSMS() const
    {
        return static_cast<const EventTypeSMS&> (ElementAt(0));
    }

    void SetEventSpecificInformationSMS(EventSpecificInformationSMS* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEventSpecificInformationSMSStaticDescription());
        AddElement(1, element);
    }

    void SetEventSpecificInformationSMS(const EventSpecificInformationSMS& element)
    {
        its::AsnObject& asnObject = const_cast<EventSpecificInformationSMS&>(element);
        asnObject.SetDescription(GetEventSpecificInformationSMSStaticDescription());
        AddElement(1, element);
    }

    bool OptionEventSpecificInformationSMS() const
    {
        return Contains(1);
    }

    const EventSpecificInformationSMS& GetEventSpecificInformationSMS() const
    {
        ITS_REQUIRE(OptionEventSpecificInformationSMS());
        return static_cast<const EventSpecificInformationSMS&> (ElementAt(1));
    }

    void SetMiscCallInfo(MiscCallInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMiscCallInfoStaticDescription());
        AddElement(2, element);
    }

    void SetMiscCallInfo(const MiscCallInfo& element)
    {
        its::AsnObject& asnObject = const_cast<MiscCallInfo&>(element);
        asnObject.SetDescription(GetMiscCallInfoStaticDescription());
        AddElement(2, element);
    }

    const MiscCallInfo& GetMiscCallInfo() const
    {
        return static_cast<const MiscCallInfo&> (ElementAt(2));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(3, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(3, element);
    }

    bool OptionExtensions() const
    {
        return Contains(3);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_EVENT_REPORT_SMS_ARG_H_)
