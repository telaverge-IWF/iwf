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


#if !defined(_CAP_V3_CONNECT_ARG_H_)
#define _CAP_V3_CONNECT_ARG_H_

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

#include <cap_v3_destination_routing_address.h>
#include <cap_v3_alerting_pattern.h>
#include <cap_v3_original_called_party_id.h>
#include <cap_v3_extension_field.h>
#include <cap_v3_carrier.h>
#include <cap_v3_calling_partys_category.h>
#include <cap_v3_redirecting_party_id.h>
#include <cap_v3_redirection_information.h>
#include <cap_v3_generic_numbers.h>
#include <cap_v3_service_interaction_indicators_two.h>
#include <cap_v3_charge_number.h>
#include <cap_v3_cug_interlock.h>
#include <cap_v3_suppression_of_announcement.h>
#include <cap_v3_ocsi_applicable.h>
#include <cap_v3_na_info.h>



namespace cap_v3 {



class ConnectArg : public its::AsnSequence
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


        typedef cap_v3::DestinationRoutingAddress DestinationRoutingAddress;


        typedef cap_v3::AlertingPattern AlertingPattern;


        typedef cap_v3::OriginalCalledPartyID OriginalCalledPartyID;


        typedef cap_v3::Carrier Carrier;


        typedef cap_v3::CallingPartysCategory CallingPartysCategory;


        typedef cap_v3::RedirectingPartyID RedirectingPartyID;


        typedef cap_v3::RedirectionInformation RedirectionInformation;


        typedef cap_v3::GenericNumbers GenericNumbers;


        typedef cap_v3::ServiceInteractionIndicatorsTwo ServiceInteractionIndicatorsTwo;


        typedef cap_v3::ChargeNumber ChargeNumber;


        typedef cap_v3::CUG_Interlock CUG_Interlock;


        typedef cap_v3::SuppressionOfAnnouncement SuppressionOfAnnouncement;


        typedef cap_v3::OCSIApplicable OCSIApplicable;


        typedef cap_v3::NA_Info NA_Info;


////////// End Nested Class(es) //////////

    ConnectArg() : its::AsnSequence(16, false)
    {
        Initialize();
    }

    ConnectArg(its::Octets& octets) : its::AsnSequence(16, false)
    {
        Initialize();
        Decode(octets);
    }

    ConnectArg(const ConnectArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ConnectArg(its::AsnDescObject* description) : its::AsnSequence(16, description)
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

    static its::AsnDescObject* GetDestinationRoutingAddressStaticDescription();
    static its::AsnDescObject* GetAlertingPatternStaticDescription();
    static its::AsnDescObject* GetOriginalCalledPartyIDStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();
    static its::AsnDescObject* GetCarrierStaticDescription();
    static its::AsnDescObject* GetCallingPartysCategoryStaticDescription();
    static its::AsnDescObject* GetRedirectingPartyIDStaticDescription();
    static its::AsnDescObject* GetRedirectionInformationStaticDescription();
    static its::AsnDescObject* GetGenericNumbersStaticDescription();
    static its::AsnDescObject* GetServiceInteractionIndicatorsTwoStaticDescription();
    static its::AsnDescObject* GetChargeNumberStaticDescription();
    static its::AsnDescObject* GetCug_InterlockStaticDescription();
    static its::AsnDescObject* GetCug_OutgoingAccessStaticDescription();
    static its::AsnDescObject* GetSuppressionOfAnnouncementStaticDescription();
    static its::AsnDescObject* GetOCSIApplicableStaticDescription();
    static its::AsnDescObject* GetNa_InfoStaticDescription();

public:

    virtual ~ConnectArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ConnectArg(*this);
    }

    virtual std::string GetName() const
    { return "ConnectArg"; }

    void SetDestinationRoutingAddress(DestinationRoutingAddress* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDestinationRoutingAddressStaticDescription());
        AddElement(0, element);
    }

    void SetDestinationRoutingAddress(const DestinationRoutingAddress& element)
    {
        its::AsnObject& asnObject = const_cast<DestinationRoutingAddress&>(element);
        asnObject.SetDescription(GetDestinationRoutingAddressStaticDescription());
        AddElement(0, element);
    }

    const DestinationRoutingAddress& GetDestinationRoutingAddress() const
    {
        return static_cast<const DestinationRoutingAddress&> (ElementAt(0));
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

    void SetOriginalCalledPartyID(OriginalCalledPartyID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOriginalCalledPartyIDStaticDescription());
        AddElement(2, element);
    }

    void SetOriginalCalledPartyID(const OriginalCalledPartyID& element)
    {
        its::AsnObject& asnObject = const_cast<OriginalCalledPartyID&>(element);
        asnObject.SetDescription(GetOriginalCalledPartyIDStaticDescription());
        AddElement(2, element);
    }

    bool OptionOriginalCalledPartyID() const
    {
        return Contains(2);
    }

    const OriginalCalledPartyID& GetOriginalCalledPartyID() const
    {
        ITS_REQUIRE(OptionOriginalCalledPartyID());
        return static_cast<const OriginalCalledPartyID&> (ElementAt(2));
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

    void SetCarrier(Carrier* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCarrierStaticDescription());
        AddElement(4, element);
    }

    void SetCarrier(const Carrier& element)
    {
        its::AsnObject& asnObject = const_cast<Carrier&>(element);
        asnObject.SetDescription(GetCarrierStaticDescription());
        AddElement(4, element);
    }

    bool OptionCarrier() const
    {
        return Contains(4);
    }

    const Carrier& GetCarrier() const
    {
        ITS_REQUIRE(OptionCarrier());
        return static_cast<const Carrier&> (ElementAt(4));
    }

    void SetCallingPartysCategory(CallingPartysCategory* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingPartysCategoryStaticDescription());
        AddElement(5, element);
    }

    void SetCallingPartysCategory(const CallingPartysCategory& element)
    {
        its::AsnObject& asnObject = const_cast<CallingPartysCategory&>(element);
        asnObject.SetDescription(GetCallingPartysCategoryStaticDescription());
        AddElement(5, element);
    }

    bool OptionCallingPartysCategory() const
    {
        return Contains(5);
    }

    const CallingPartysCategory& GetCallingPartysCategory() const
    {
        ITS_REQUIRE(OptionCallingPartysCategory());
        return static_cast<const CallingPartysCategory&> (ElementAt(5));
    }

    void SetRedirectingPartyID(RedirectingPartyID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRedirectingPartyIDStaticDescription());
        AddElement(6, element);
    }

    void SetRedirectingPartyID(const RedirectingPartyID& element)
    {
        its::AsnObject& asnObject = const_cast<RedirectingPartyID&>(element);
        asnObject.SetDescription(GetRedirectingPartyIDStaticDescription());
        AddElement(6, element);
    }

    bool OptionRedirectingPartyID() const
    {
        return Contains(6);
    }

    const RedirectingPartyID& GetRedirectingPartyID() const
    {
        ITS_REQUIRE(OptionRedirectingPartyID());
        return static_cast<const RedirectingPartyID&> (ElementAt(6));
    }

    void SetRedirectionInformation(RedirectionInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRedirectionInformationStaticDescription());
        AddElement(7, element);
    }

    void SetRedirectionInformation(const RedirectionInformation& element)
    {
        its::AsnObject& asnObject = const_cast<RedirectionInformation&>(element);
        asnObject.SetDescription(GetRedirectionInformationStaticDescription());
        AddElement(7, element);
    }

    bool OptionRedirectionInformation() const
    {
        return Contains(7);
    }

    const RedirectionInformation& GetRedirectionInformation() const
    {
        ITS_REQUIRE(OptionRedirectionInformation());
        return static_cast<const RedirectionInformation&> (ElementAt(7));
    }

    void SetGenericNumbers(GenericNumbers* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGenericNumbersStaticDescription());
        AddElement(8, element);
    }

    void SetGenericNumbers(const GenericNumbers& element)
    {
        its::AsnObject& asnObject = const_cast<GenericNumbers&>(element);
        asnObject.SetDescription(GetGenericNumbersStaticDescription());
        AddElement(8, element);
    }

    bool OptionGenericNumbers() const
    {
        return Contains(8);
    }

    const GenericNumbers& GetGenericNumbers() const
    {
        ITS_REQUIRE(OptionGenericNumbers());
        return static_cast<const GenericNumbers&> (ElementAt(8));
    }

    void SetServiceInteractionIndicatorsTwo(ServiceInteractionIndicatorsTwo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetServiceInteractionIndicatorsTwoStaticDescription());
        AddElement(9, element);
    }

    void SetServiceInteractionIndicatorsTwo(const ServiceInteractionIndicatorsTwo& element)
    {
        its::AsnObject& asnObject = const_cast<ServiceInteractionIndicatorsTwo&>(element);
        asnObject.SetDescription(GetServiceInteractionIndicatorsTwoStaticDescription());
        AddElement(9, element);
    }

    bool OptionServiceInteractionIndicatorsTwo() const
    {
        return Contains(9);
    }

    const ServiceInteractionIndicatorsTwo& GetServiceInteractionIndicatorsTwo() const
    {
        ITS_REQUIRE(OptionServiceInteractionIndicatorsTwo());
        return static_cast<const ServiceInteractionIndicatorsTwo&> (ElementAt(9));
    }

    void SetChargeNumber(ChargeNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetChargeNumberStaticDescription());
        AddElement(10, element);
    }

    void SetChargeNumber(const ChargeNumber& element)
    {
        its::AsnObject& asnObject = const_cast<ChargeNumber&>(element);
        asnObject.SetDescription(GetChargeNumberStaticDescription());
        AddElement(10, element);
    }

    bool OptionChargeNumber() const
    {
        return Contains(10);
    }

    const ChargeNumber& GetChargeNumber() const
    {
        ITS_REQUIRE(OptionChargeNumber());
        return static_cast<const ChargeNumber&> (ElementAt(10));
    }

    void SetCug_Interlock(CUG_Interlock* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCug_InterlockStaticDescription());
        AddElement(11, element);
    }

    void SetCug_Interlock(const CUG_Interlock& element)
    {
        its::AsnObject& asnObject = const_cast<CUG_Interlock&>(element);
        asnObject.SetDescription(GetCug_InterlockStaticDescription());
        AddElement(11, element);
    }

    bool OptionCug_Interlock() const
    {
        return Contains(11);
    }

    const CUG_Interlock& GetCug_Interlock() const
    {
        ITS_REQUIRE(OptionCug_Interlock());
        return static_cast<const CUG_Interlock&> (ElementAt(11));
    }

    void SetCug_OutgoingAccess(Cug_OutgoingAccess* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCug_OutgoingAccessStaticDescription());
        AddElement(12, element);
    }

    void SetCug_OutgoingAccess(const Cug_OutgoingAccess& element)
    {
        its::AsnObject& asnObject = const_cast<Cug_OutgoingAccess&>(element);
        asnObject.SetDescription(GetCug_OutgoingAccessStaticDescription());
        AddElement(12, element);
    }

    bool OptionCug_OutgoingAccess() const
    {
        return Contains(12);
    }

    const Cug_OutgoingAccess& GetCug_OutgoingAccess() const
    {
        ITS_REQUIRE(OptionCug_OutgoingAccess());
        return static_cast<const Cug_OutgoingAccess&> (ElementAt(12));
    }

    void SetSuppressionOfAnnouncement(SuppressionOfAnnouncement* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSuppressionOfAnnouncementStaticDescription());
        AddElement(13, element);
    }

    void SetSuppressionOfAnnouncement(const SuppressionOfAnnouncement& element)
    {
        its::AsnObject& asnObject = const_cast<SuppressionOfAnnouncement&>(element);
        asnObject.SetDescription(GetSuppressionOfAnnouncementStaticDescription());
        AddElement(13, element);
    }

    bool OptionSuppressionOfAnnouncement() const
    {
        return Contains(13);
    }

    const SuppressionOfAnnouncement& GetSuppressionOfAnnouncement() const
    {
        ITS_REQUIRE(OptionSuppressionOfAnnouncement());
        return static_cast<const SuppressionOfAnnouncement&> (ElementAt(13));
    }

    void SetOCSIApplicable(OCSIApplicable* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOCSIApplicableStaticDescription());
        AddElement(14, element);
    }

    void SetOCSIApplicable(const OCSIApplicable& element)
    {
        its::AsnObject& asnObject = const_cast<OCSIApplicable&>(element);
        asnObject.SetDescription(GetOCSIApplicableStaticDescription());
        AddElement(14, element);
    }

    bool OptionOCSIApplicable() const
    {
        return Contains(14);
    }

    const OCSIApplicable& GetOCSIApplicable() const
    {
        ITS_REQUIRE(OptionOCSIApplicable());
        return static_cast<const OCSIApplicable&> (ElementAt(14));
    }

    void SetNa_Info(NA_Info* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNa_InfoStaticDescription());
        AddElement(15, element);
    }

    void SetNa_Info(const NA_Info& element)
    {
        its::AsnObject& asnObject = const_cast<NA_Info&>(element);
        asnObject.SetDescription(GetNa_InfoStaticDescription());
        AddElement(15, element);
    }

    bool OptionNa_Info() const
    {
        return Contains(15);
    }

    const NA_Info& GetNa_Info() const
    {
        ITS_REQUIRE(OptionNa_Info());
        return static_cast<const NA_Info&> (ElementAt(15));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_CONNECT_ARG_H_)

