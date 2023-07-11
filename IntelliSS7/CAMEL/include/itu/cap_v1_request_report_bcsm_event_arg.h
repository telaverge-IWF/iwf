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


#if !defined(_CAP_V1_REQUEST_REPORT_BCSM_EVENT_ARG_H_)
#define _CAP_V1_REQUEST_REPORT_BCSM_EVENT_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>

#include <cap_v1_bcsm_event.h>
#include <cap_v1_extension_field.h>



namespace cap_v1 {



class RequestReportBCSMEventArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class BcsmEvents : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef cap_v1::BCSMEvent BCSMEvent;


    ////////// End Nested Class //////////

        BcsmEvents() : its::AsnSequenceOf(false)
        {
            Initialize();
        }

        BcsmEvents(its::Octets& octets) : its::AsnSequenceOf(false)
        {
            Initialize();
            Decode(octets);
        }

        BcsmEvents(const BcsmEvents& rhs) : its::AsnSequenceOf(rhs)
        {
            // Nothing to do.
        }

        BcsmEvents(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

        static its::AsnDescObject* GetBCSMEventStaticDescription();

    public:

        virtual ~BcsmEvents()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new BcsmEvents(*this);
        }

        virtual std::string GetName() const
        { return "BcsmEvents"; }

        void AddElement(BCSMEvent* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetBCSMEventStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        void AddElement(const BCSMEvent& element)
        {
            its::AsnObject& asnObject = const_cast<BCSMEvent&>(element);
            asnObject.SetDescription(GetBCSMEventStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        const BCSMEvent& ElementAt(int index) const
        {
            return static_cast<const BCSMEvent&> (AsnSequenceOf::ElementAt(index));
        }

    };



    class Extensions : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef cap_v1::ExtensionField ExtensionField;


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

    RequestReportBCSMEventArg() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    RequestReportBCSMEventArg(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    RequestReportBCSMEventArg(const RequestReportBCSMEventArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    RequestReportBCSMEventArg(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetBcsmEventsStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();

public:

    virtual ~RequestReportBCSMEventArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RequestReportBCSMEventArg(*this);
    }

    virtual std::string GetName() const
    { return "RequestReportBCSMEventArg"; }

    void SetBcsmEvents(BcsmEvents* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBcsmEventsStaticDescription());
        AddElement(0, element);
    }

    void SetBcsmEvents(const BcsmEvents& element)
    {
        its::AsnObject& asnObject = const_cast<BcsmEvents&>(element);
        asnObject.SetDescription(GetBcsmEventsStaticDescription());
        AddElement(0, element);
    }

    const BcsmEvents& GetBcsmEvents() const
    {
        return static_cast<const BcsmEvents&> (ElementAt(0));
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

#endif    // !defined(_CAP_V1_REQUEST_REPORT_BCSM_EVENT_ARG_H_)

