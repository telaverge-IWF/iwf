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


#if !defined(_CAP_V3_REQUEST_REPORT_SMS_EVENT_ARG_H_)
#define _CAP_V3_REQUEST_REPORT_SMS_EVENT_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>

#include <cap_v3_sms_event.h>
#include <cap_v3_extension_field.h>



namespace cap_v3 {



class RequestReportSMSEventArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class SMSEvents : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef cap_v3::SMSEvent SMSEvent;


    ////////// End Nested Class //////////

        SMSEvents() : its::AsnSequenceOf(false)
        {
            Initialize();
        }

        SMSEvents(its::Octets& octets) : its::AsnSequenceOf(false)
        {
            Initialize();
            Decode(octets);
        }

        SMSEvents(const SMSEvents& rhs) : its::AsnSequenceOf(rhs)
        {
            // Nothing to do.
        }

        SMSEvents(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

        static its::AsnDescObject* GetSMSEventStaticDescription();

    public:

        virtual ~SMSEvents()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new SMSEvents(*this);
        }

        virtual std::string GetName() const
        { return "SMSEvents"; }

        void AddElement(SMSEvent* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetSMSEventStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        void AddElement(const SMSEvent& element)
        {
            its::AsnObject& asnObject = const_cast<SMSEvent&>(element);
            asnObject.SetDescription(GetSMSEventStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        const SMSEvent& ElementAt(int index) const
        {
            return static_cast<const SMSEvent&> (AsnSequenceOf::ElementAt(index));
        }

    };



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


////////// End Nested Class(es) //////////

    RequestReportSMSEventArg() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    RequestReportSMSEventArg(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    RequestReportSMSEventArg(const RequestReportSMSEventArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    RequestReportSMSEventArg(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetSMSEventsStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();

public:

    virtual ~RequestReportSMSEventArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RequestReportSMSEventArg(*this);
    }

    virtual std::string GetName() const
    { return "RequestReportSMSEventArg"; }

    void SetSMSEvents(SMSEvents* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSMSEventsStaticDescription());
        AddElement(0, element);
    }

    void SetSMSEvents(const SMSEvents& element)
    {
        its::AsnObject& asnObject = const_cast<SMSEvents&>(element);
        asnObject.SetDescription(GetSMSEventsStaticDescription());
        AddElement(0, element);
    }

    const SMSEvents& GetSMSEvents() const
    {
        return static_cast<const SMSEvents&> (ElementAt(0));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(1, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(1, element);
    }

    bool OptionExtensions() const
    {
        return Contains(1);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_REQUEST_REPORT_SMS_EVENT_ARG_H_)

