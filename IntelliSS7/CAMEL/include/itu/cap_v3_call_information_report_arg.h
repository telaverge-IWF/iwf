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


#if !defined(_CAP_V3_CALL_INFORMATION_REPORT_ARG_H_)
#define _CAP_V3_CALL_INFORMATION_REPORT_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>
#include <AsnChoice.h>

#include <cap_v3_requested_information_list.h>
#include <cap_v3_extension_field.h>
#include <cap_v3_receiving_side_id.h>



namespace cap_v3 {



class CallInformationReportArg : public its::AsnSequence
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


        typedef cap_v3::RequestedInformationList RequestedInformationList;


        typedef cap_v3::ReceivingSideID ReceivingSideID;


////////// End Nested Class(es) //////////

    CallInformationReportArg() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    CallInformationReportArg(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    CallInformationReportArg(const CallInformationReportArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    CallInformationReportArg(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetRequestedInformationListStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();
    static its::AsnDescObject* GetLegIDStaticDescription();

public:

    virtual ~CallInformationReportArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CallInformationReportArg(*this);
    }

    virtual std::string GetName() const
    { return "CallInformationReportArg"; }

    void SetRequestedInformationList(RequestedInformationList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRequestedInformationListStaticDescription());
        AddElement(0, element);
    }

    void SetRequestedInformationList(const RequestedInformationList& element)
    {
        its::AsnObject& asnObject = const_cast<RequestedInformationList&>(element);
        asnObject.SetDescription(GetRequestedInformationListStaticDescription());
        AddElement(0, element);
    }

    const RequestedInformationList& GetRequestedInformationList() const
    {
        return static_cast<const RequestedInformationList&> (ElementAt(0));
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

};



} // namespace.

#endif    // !defined(_CAP_V3_CALL_INFORMATION_REPORT_ARG_H_)
