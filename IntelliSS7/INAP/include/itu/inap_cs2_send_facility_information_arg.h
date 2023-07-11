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


#if !defined(_INAP_CS2_SEND_FACILITY_INFORMATION_ARG_H_)
#define _INAP_CS2_SEND_FACILITY_INFORMATION_ARG_H_

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
#include <AsnInteger.h>

#include <inap_cs2_component_type.h>
#include <inap_cs2_leg_id.h>
#include <inap_cs2_component_correlation_id.h>
#include <inap_cs2_call_processing_operation_correlation_id.h>
#include <inap_cs2_extension_field.h>



namespace inap_cs2 {



class SendFacilityInformationArg : public its::AsnSequence
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


        typedef inap_cs2::ComponentType ComponentType;


        typedef inap_cs2::LegID LegID;


        typedef inap_cs2::ComponentCorrelationID ComponentCorrelationID;


        typedef inap_cs2::CallProcessingOperationCorrelationID CallProcessingOperationCorrelationID;


////////// End Nested Class(es) //////////

    SendFacilityInformationArg() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    SendFacilityInformationArg(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    SendFacilityInformationArg(const SendFacilityInformationArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SendFacilityInformationArg(its::AsnDescObject* description) : its::AsnSequence(5, description)
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

    static its::AsnDescObject* GetComponentTypeStaticDescription();
    static its::AsnDescObject* GetLegIDStaticDescription();
    static its::AsnDescObject* GetComponentCorrelationIDStaticDescription();
    static its::AsnDescObject* GetCallProcessingOperationCorrelationIDStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();

public:

    virtual ~SendFacilityInformationArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SendFacilityInformationArg(*this);
    }

    virtual std::string GetName() const
    { return "SendFacilityInformationArg"; }

    void SetComponentType(ComponentType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetComponentTypeStaticDescription());
        AddElement(0, element);
    }

    void SetComponentType(const ComponentType& element)
    {
        its::AsnObject& asnObject = const_cast<ComponentType&>(element);
        asnObject.SetDescription(GetComponentTypeStaticDescription());
        AddElement(0, element);
    }

    const ComponentType& GetComponentType() const
    {
        return static_cast<const ComponentType&> (ElementAt(0));
    }

    void SetLegID(LegID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLegIDStaticDescription());
        AddElement(1, element);
    }

    void SetLegID(const LegID& element)
    {
        its::AsnObject& asnObject = const_cast<LegID&>(element);
        asnObject.SetDescription(GetLegIDStaticDescription());
        AddElement(1, element);
    }

    bool OptionLegID() const
    {
        return Contains(1);
    }

    const LegID& GetLegID() const
    {
        ITS_REQUIRE(OptionLegID());
        return static_cast<const LegID&> (ElementAt(1));
    }

    void SetComponentCorrelationID(ComponentCorrelationID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetComponentCorrelationIDStaticDescription());
        AddElement(2, element);
    }

    void SetComponentCorrelationID(const ComponentCorrelationID& element)
    {
        its::AsnObject& asnObject = const_cast<ComponentCorrelationID&>(element);
        asnObject.SetDescription(GetComponentCorrelationIDStaticDescription());
        AddElement(2, element);
    }

    bool OptionComponentCorrelationID() const
    {
        return Contains(2);
    }

    const ComponentCorrelationID& GetComponentCorrelationID() const
    {
        ITS_REQUIRE(OptionComponentCorrelationID());
        return static_cast<const ComponentCorrelationID&> (ElementAt(2));
    }

    void SetCallProcessingOperationCorrelationID(CallProcessingOperationCorrelationID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallProcessingOperationCorrelationIDStaticDescription());
        AddElement(3, element);
    }

    void SetCallProcessingOperationCorrelationID(const CallProcessingOperationCorrelationID& element)
    {
        its::AsnObject& asnObject = const_cast<CallProcessingOperationCorrelationID&>(element);
        asnObject.SetDescription(GetCallProcessingOperationCorrelationIDStaticDescription());
        AddElement(3, element);
    }

    const CallProcessingOperationCorrelationID& GetCallProcessingOperationCorrelationID() const
    {
        return static_cast<const CallProcessingOperationCorrelationID&> (ElementAt(3));
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

#endif    // !defined(_INAP_CS2_SEND_FACILITY_INFORMATION_ARG_H_)

