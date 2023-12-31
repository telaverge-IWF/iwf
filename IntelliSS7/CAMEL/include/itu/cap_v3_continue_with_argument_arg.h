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


#if !defined(_CAP_V3_CONTINUE_WITH_ARGUMENT_ARG_H_)
#define _CAP_V3_CONTINUE_WITH_ARGUMENT_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>
#include <AsnNull.h>
#include <AsnOctetString.h>
#include <AsnSetOf.h>

#include <cap_v3_alerting_pattern.h>
#include <cap_v3_extension_field.h>
#include <cap_v3_service_interaction_indicators_two.h>
#include <cap_v3_calling_partys_category.h>
#include <cap_v3_generic_numbers.h>
#include <cap_v3_cug_interlock.h>
#include <cap_v3_charge_number.h>
#include <cap_v3_carrier.h>
#include <cap_v3_suppression_of_announcement.h>
#include <cap_v3_na_info.h>



namespace cap_v3 {



class ContinueWithArgumentArg : public its::AsnSequence
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



    class Cug_OutgoingAccess : public its::AsnNull
    {
    public:

        Cug_OutgoingAccess() : its::AsnNull(false)
        {
            Initialize();
        }

        Cug_OutgoingAccess(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Cug_OutgoingAccess(const Cug_OutgoingAccess& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Cug_OutgoingAccess(its::AsnDescObject* description) : its::AsnNull(description)
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

    public:

        virtual ~Cug_OutgoingAccess()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Cug_OutgoingAccess(*this);
        }

        virtual std::string GetName() const
        { return "Cug_OutgoingAccess"; }

    };


        typedef cap_v3::AlertingPattern AlertingPattern;


        typedef cap_v3::ServiceInteractionIndicatorsTwo ServiceInteractionIndicatorsTwo;


        typedef cap_v3::CallingPartysCategory CallingPartysCategory;


        typedef cap_v3::GenericNumbers GenericNumbers;


        typedef cap_v3::CUG_Interlock CUG_Interlock;


        typedef cap_v3::ChargeNumber ChargeNumber;


        typedef cap_v3::Carrier Carrier;


        typedef cap_v3::SuppressionOfAnnouncement SuppressionOfAnnouncement;


        typedef cap_v3::NA_Info NA_Info;


////////// End Nested Class(es) //////////

    ContinueWithArgumentArg() : its::AsnSequence(11, false)
    {
        Initialize();
    }

    ContinueWithArgumentArg(its::Octets& octets) : its::AsnSequence(11, false)
    {
        Initialize();
        Decode(octets);
    }

    ContinueWithArgumentArg(const ContinueWithArgumentArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ContinueWithArgumentArg(its::AsnDescObject* description) : its::AsnSequence(11, description)
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

    static its::AsnDescObject* GetAlertingPatternStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();
    static its::AsnDescObject* GetServiceInteractionIndicatorsTwoStaticDescription();
    static its::AsnDescObject* GetCallingPartysCategoryStaticDescription();
    static its::AsnDescObject* GetGenericNumbersStaticDescription();
    static its::AsnDescObject* GetCug_InterlockStaticDescription();
    static its::AsnDescObject* GetCug_OutgoingAccessStaticDescription();
    static its::AsnDescObject* GetChargeNumberStaticDescription();
    static its::AsnDescObject* GetCarrierStaticDescription();
    static its::AsnDescObject* GetSuppressionOfAnnouncementStaticDescription();
    static its::AsnDescObject* GetNa_InfoStaticDescription();

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

    void SetAlertingPattern(AlertingPattern* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAlertingPatternStaticDescription());
        AddElement(0, element);
    }

    void SetAlertingPattern(const AlertingPattern& element)
    {
        its::AsnObject& asnObject = const_cast<AlertingPattern&>(element);
        asnObject.SetDescription(GetAlertingPatternStaticDescription());
        AddElement(0, element);
    }

    bool OptionAlertingPattern() const
    {
        return Contains(0);
    }

    const AlertingPattern& GetAlertingPattern() const
    {
        ITS_REQUIRE(OptionAlertingPattern());
        return static_cast<const AlertingPattern&> (ElementAt(0));
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

    void SetServiceInteractionIndicatorsTwo(ServiceInteractionIndicatorsTwo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetServiceInteractionIndicatorsTwoStaticDescription());
        AddElement(2, element);
    }

    void SetServiceInteractionIndicatorsTwo(const ServiceInteractionIndicatorsTwo& element)
    {
        its::AsnObject& asnObject = const_cast<ServiceInteractionIndicatorsTwo&>(element);
        asnObject.SetDescription(GetServiceInteractionIndicatorsTwoStaticDescription());
        AddElement(2, element);
    }

    bool OptionServiceInteractionIndicatorsTwo() const
    {
        return Contains(2);
    }

    const ServiceInteractionIndicatorsTwo& GetServiceInteractionIndicatorsTwo() const
    {
        ITS_REQUIRE(OptionServiceInteractionIndicatorsTwo());
        return static_cast<const ServiceInteractionIndicatorsTwo&> (ElementAt(2));
    }

    void SetCallingPartysCategory(CallingPartysCategory* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingPartysCategoryStaticDescription());
        AddElement(3, element);
    }

    void SetCallingPartysCategory(const CallingPartysCategory& element)
    {
        its::AsnObject& asnObject = const_cast<CallingPartysCategory&>(element);
        asnObject.SetDescription(GetCallingPartysCategoryStaticDescription());
        AddElement(3, element);
    }

    bool OptionCallingPartysCategory() const
    {
        return Contains(3);
    }

    const CallingPartysCategory& GetCallingPartysCategory() const
    {
        ITS_REQUIRE(OptionCallingPartysCategory());
        return static_cast<const CallingPartysCategory&> (ElementAt(3));
    }

    void SetGenericNumbers(GenericNumbers* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGenericNumbersStaticDescription());
        AddElement(4, element);
    }

    void SetGenericNumbers(const GenericNumbers& element)
    {
        its::AsnObject& asnObject = const_cast<GenericNumbers&>(element);
        asnObject.SetDescription(GetGenericNumbersStaticDescription());
        AddElement(4, element);
    }

    bool OptionGenericNumbers() const
    {
        return Contains(4);
    }

    const GenericNumbers& GetGenericNumbers() const
    {
        ITS_REQUIRE(OptionGenericNumbers());
        return static_cast<const GenericNumbers&> (ElementAt(4));
    }

    void SetCug_Interlock(CUG_Interlock* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCug_InterlockStaticDescription());
        AddElement(5, element);
    }

    void SetCug_Interlock(const CUG_Interlock& element)
    {
        its::AsnObject& asnObject = const_cast<CUG_Interlock&>(element);
        asnObject.SetDescription(GetCug_InterlockStaticDescription());
        AddElement(5, element);
    }

    bool OptionCug_Interlock() const
    {
        return Contains(5);
    }

    const CUG_Interlock& GetCug_Interlock() const
    {
        ITS_REQUIRE(OptionCug_Interlock());
        return static_cast<const CUG_Interlock&> (ElementAt(5));
    }

    void SetCug_OutgoingAccess(Cug_OutgoingAccess* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCug_OutgoingAccessStaticDescription());
        AddElement(6, element);
    }

    void SetCug_OutgoingAccess(const Cug_OutgoingAccess& element)
    {
        its::AsnObject& asnObject = const_cast<Cug_OutgoingAccess&>(element);
        asnObject.SetDescription(GetCug_OutgoingAccessStaticDescription());
        AddElement(6, element);
    }

    bool OptionCug_OutgoingAccess() const
    {
        return Contains(6);
    }

    const Cug_OutgoingAccess& GetCug_OutgoingAccess() const
    {
        ITS_REQUIRE(OptionCug_OutgoingAccess());
        return static_cast<const Cug_OutgoingAccess&> (ElementAt(6));
    }

    void SetChargeNumber(ChargeNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetChargeNumberStaticDescription());
        AddElement(7, element);
    }

    void SetChargeNumber(const ChargeNumber& element)
    {
        its::AsnObject& asnObject = const_cast<ChargeNumber&>(element);
        asnObject.SetDescription(GetChargeNumberStaticDescription());
        AddElement(7, element);
    }

    bool OptionChargeNumber() const
    {
        return Contains(7);
    }

    const ChargeNumber& GetChargeNumber() const
    {
        ITS_REQUIRE(OptionChargeNumber());
        return static_cast<const ChargeNumber&> (ElementAt(7));
    }

    void SetCarrier(Carrier* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCarrierStaticDescription());
        AddElement(8, element);
    }

    void SetCarrier(const Carrier& element)
    {
        its::AsnObject& asnObject = const_cast<Carrier&>(element);
        asnObject.SetDescription(GetCarrierStaticDescription());
        AddElement(8, element);
    }

    bool OptionCarrier() const
    {
        return Contains(8);
    }

    const Carrier& GetCarrier() const
    {
        ITS_REQUIRE(OptionCarrier());
        return static_cast<const Carrier&> (ElementAt(8));
    }

    void SetSuppressionOfAnnouncement(SuppressionOfAnnouncement* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSuppressionOfAnnouncementStaticDescription());
        AddElement(9, element);
    }

    void SetSuppressionOfAnnouncement(const SuppressionOfAnnouncement& element)
    {
        its::AsnObject& asnObject = const_cast<SuppressionOfAnnouncement&>(element);
        asnObject.SetDescription(GetSuppressionOfAnnouncementStaticDescription());
        AddElement(9, element);
    }

    bool OptionSuppressionOfAnnouncement() const
    {
        return Contains(9);
    }

    const SuppressionOfAnnouncement& GetSuppressionOfAnnouncement() const
    {
        ITS_REQUIRE(OptionSuppressionOfAnnouncement());
        return static_cast<const SuppressionOfAnnouncement&> (ElementAt(9));
    }

    void SetNa_Info(NA_Info* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNa_InfoStaticDescription());
        AddElement(10, element);
    }

    void SetNa_Info(const NA_Info& element)
    {
        its::AsnObject& asnObject = const_cast<NA_Info&>(element);
        asnObject.SetDescription(GetNa_InfoStaticDescription());
        AddElement(10, element);
    }

    bool OptionNa_Info() const
    {
        return Contains(10);
    }

    const NA_Info& GetNa_Info() const
    {
        ITS_REQUIRE(OptionNa_Info());
        return static_cast<const NA_Info&> (ElementAt(10));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_CONTINUE_WITH_ARGUMENT_ARG_H_)

