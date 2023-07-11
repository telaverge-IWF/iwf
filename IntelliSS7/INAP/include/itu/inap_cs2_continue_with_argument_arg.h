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


#if !defined(_INAP_CS2_CONTINUE_WITH_ARGUMENT_ARG_H_)
#define _INAP_CS2_CONTINUE_WITH_ARGUMENT_ARG_H_

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
#include <AsnOctetString.h>

#include <inap_cs2_leg_id.h>
#include <inap_cs2_alerting_pattern.h>
#include <inap_cs2_generic_name.h>
#include <inap_cs2_in_service_compatibility_response.h>
#include <inap_cs2_forward_gvns.h>
#include <inap_cs2_backward_gvns.h>
#include <inap_cs2_extension_field.h>
#include <inap_cs2_service_interaction_indicators_two.h>



namespace inap_cs2 {



class ContinueWithArgumentArg : public its::AsnSequence
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


        typedef inap_cs2::LegID LegID;


        typedef inap_cs2::AlertingPattern AlertingPattern;


        typedef inap_cs2::GenericName GenericName;


        typedef inap_cs2::INServiceCompatibilityResponse INServiceCompatibilityResponse;


        typedef inap_cs2::ForwardGVNS ForwardGVNS;


        typedef inap_cs2::BackwardGVNS BackwardGVNS;


        typedef inap_cs2::ServiceInteractionIndicatorsTwo ServiceInteractionIndicatorsTwo;


////////// End Nested Class(es) //////////

    ContinueWithArgumentArg() : its::AsnSequence(8, false)
    {
        Initialize();
    }

    ContinueWithArgumentArg(its::Octets& octets) : its::AsnSequence(8, false)
    {
        Initialize();
        Decode(octets);
    }

    ContinueWithArgumentArg(const ContinueWithArgumentArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ContinueWithArgumentArg(its::AsnDescObject* description) : its::AsnSequence(8, description)
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

    static its::AsnDescObject* GetLegIDStaticDescription();
    static its::AsnDescObject* GetAlertingPatternStaticDescription();
    static its::AsnDescObject* GetGenericNameStaticDescription();
    static its::AsnDescObject* GetINServiceCompatibilityResponseStaticDescription();
    static its::AsnDescObject* GetForwardGVNSStaticDescription();
    static its::AsnDescObject* GetBackwardGVNSStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();
    static its::AsnDescObject* GetServiceInteractionIndicatorsTwoStaticDescription();

public:

    virtual ~ContinueWithArgumentArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ContinueWithArgumentArg(*this);
    }

    virtual std::string GetName() const
    { return "ContinueWithArgumentArg"; }

    void SetLegID(LegID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLegIDStaticDescription());
        AddElement(0, element);
    }

    void SetLegID(const LegID& element)
    {
        its::AsnObject& asnObject = const_cast<LegID&>(element);
        asnObject.SetDescription(GetLegIDStaticDescription());
        AddElement(0, element);
    }

    const LegID& GetLegID() const
    {
        return static_cast<const LegID&> (ElementAt(0));
    }

    void SetAlertingPattern(AlertingPattern* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAlertingPatternStaticDescription());
        AddElement(1, element);
    }

    void SetAlertingPattern(const AlertingPattern& element)
    {
        its::AsnObject& asnObject = const_cast<AlertingPattern&>(element);
        asnObject.SetDescription(GetAlertingPatternStaticDescription());
        AddElement(1, element);
    }

    bool OptionAlertingPattern() const
    {
        return Contains(1);
    }

    const AlertingPattern& GetAlertingPattern() const
    {
        ITS_REQUIRE(OptionAlertingPattern());
        return static_cast<const AlertingPattern&> (ElementAt(1));
    }

    void SetGenericName(GenericName* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGenericNameStaticDescription());
        AddElement(2, element);
    }

    void SetGenericName(const GenericName& element)
    {
        its::AsnObject& asnObject = const_cast<GenericName&>(element);
        asnObject.SetDescription(GetGenericNameStaticDescription());
        AddElement(2, element);
    }

    bool OptionGenericName() const
    {
        return Contains(2);
    }

    const GenericName& GetGenericName() const
    {
        ITS_REQUIRE(OptionGenericName());
        return static_cast<const GenericName&> (ElementAt(2));
    }

    void SetINServiceCompatibilityResponse(INServiceCompatibilityResponse* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetINServiceCompatibilityResponseStaticDescription());
        AddElement(3, element);
    }

    void SetINServiceCompatibilityResponse(const INServiceCompatibilityResponse& element)
    {
        its::AsnObject& asnObject = const_cast<INServiceCompatibilityResponse&>(element);
        asnObject.SetDescription(GetINServiceCompatibilityResponseStaticDescription());
        AddElement(3, element);
    }

    bool OptionINServiceCompatibilityResponse() const
    {
        return Contains(3);
    }

    const INServiceCompatibilityResponse& GetINServiceCompatibilityResponse() const
    {
        ITS_REQUIRE(OptionINServiceCompatibilityResponse());
        return static_cast<const INServiceCompatibilityResponse&> (ElementAt(3));
    }

    void SetForwardGVNS(ForwardGVNS* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardGVNSStaticDescription());
        AddElement(4, element);
    }

    void SetForwardGVNS(const ForwardGVNS& element)
    {
        its::AsnObject& asnObject = const_cast<ForwardGVNS&>(element);
        asnObject.SetDescription(GetForwardGVNSStaticDescription());
        AddElement(4, element);
    }

    bool OptionForwardGVNS() const
    {
        return Contains(4);
    }

    const ForwardGVNS& GetForwardGVNS() const
    {
        ITS_REQUIRE(OptionForwardGVNS());
        return static_cast<const ForwardGVNS&> (ElementAt(4));
    }

    void SetBackwardGVNS(BackwardGVNS* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBackwardGVNSStaticDescription());
        AddElement(5, element);
    }

    void SetBackwardGVNS(const BackwardGVNS& element)
    {
        its::AsnObject& asnObject = const_cast<BackwardGVNS&>(element);
        asnObject.SetDescription(GetBackwardGVNSStaticDescription());
        AddElement(5, element);
    }

    bool OptionBackwardGVNS() const
    {
        return Contains(5);
    }

    const BackwardGVNS& GetBackwardGVNS() const
    {
        ITS_REQUIRE(OptionBackwardGVNS());
        return static_cast<const BackwardGVNS&> (ElementAt(5));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(6, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(6, element);
    }

    bool OptionExtensions() const
    {
        return Contains(6);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(6));
    }

    void SetServiceInteractionIndicatorsTwo(ServiceInteractionIndicatorsTwo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetServiceInteractionIndicatorsTwoStaticDescription());
        AddElement(7, element);
    }

    void SetServiceInteractionIndicatorsTwo(const ServiceInteractionIndicatorsTwo& element)
    {
        its::AsnObject& asnObject = const_cast<ServiceInteractionIndicatorsTwo&>(element);
        asnObject.SetDescription(GetServiceInteractionIndicatorsTwoStaticDescription());
        AddElement(7, element);
    }

    bool OptionServiceInteractionIndicatorsTwo() const
    {
        return Contains(7);
    }

    const ServiceInteractionIndicatorsTwo& GetServiceInteractionIndicatorsTwo() const
    {
        ITS_REQUIRE(OptionServiceInteractionIndicatorsTwo());
        return static_cast<const ServiceInteractionIndicatorsTwo&> (ElementAt(7));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_CONTINUE_WITH_ARGUMENT_ARG_H_)
