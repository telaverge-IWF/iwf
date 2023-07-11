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


#if !defined(_INAP_CS2_CONNECT_ARG_H_)
#define _INAP_CS2_CONNECT_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>
#include <AsnOctetString.h>
#include <AsnInteger.h>
#include <AsnEnumerated.h>
#include <AsnBaseString.h>
#include <AsnSetOf.h>
#include <AsnChoice.h>

#include <inap_cs2_destination_routing_address.h>
#include <inap_cs2_alerting_pattern.h>
#include <inap_cs2_correlation_id.h>
#include <inap_cs2_cut_and_paste.h>
#include <inap_cs2_forwarding_condition.h>
#include <inap_cs2_isdn_access_related_information.h>
#include <inap_cs2_original_called_party_id.h>
#include <inap_cs2_route_list.h>
#include <inap_cs2_scf_id.h>
#include <inap_cs2_travelling_class_mark.h>
#include <inap_cs2_extension_field.h>
#include <inap_cs2_carrier.h>
#include <inap_cs2_service_interaction_indicators.h>
#include <inap_cs2_calling_party_number.h>
#include <inap_cs2_calling_partys_category.h>
#include <inap_cs2_redirecting_party_id.h>
#include <inap_cs2_redirection_information.h>
#include <inap_cs2_display_information.h>
#include <inap_cs2_forward_call_indicators.h>
#include <inap_cs2_generic_numbers.h>
#include <inap_cs2_service_interaction_indicators_two.h>
#include <inap_cs2_in_service_compatibility_response.h>
#include <inap_cs2_forward_gvns.h>
#include <inap_cs2_backward_gvns.h>
#include <inap_cs2_charge_number.h>
#include <inap_cs2_call_segment_id.h>
#include <inap_cs2_leg_id.h>



namespace inap_cs2 {



class ConnectArg : public its::AsnSequence
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


        typedef inap_cs2::DestinationRoutingAddress DestinationRoutingAddress;


        typedef inap_cs2::AlertingPattern AlertingPattern;


        typedef inap_cs2::CorrelationID CorrelationID;


        typedef inap_cs2::CutAndPaste CutAndPaste;


        typedef inap_cs2::ForwardingCondition ForwardingCondition;


        typedef inap_cs2::ISDNAccessRelatedInformation ISDNAccessRelatedInformation;


        typedef inap_cs2::OriginalCalledPartyID OriginalCalledPartyID;


        typedef inap_cs2::RouteList RouteList;


        typedef inap_cs2::ScfID ScfID;


        typedef inap_cs2::TravellingClassMark TravellingClassMark;


        typedef inap_cs2::Carrier Carrier;


        typedef inap_cs2::ServiceInteractionIndicators ServiceInteractionIndicators;


        typedef inap_cs2::CallingPartyNumber CallingPartyNumber;


        typedef inap_cs2::CallingPartysCategory CallingPartysCategory;


        typedef inap_cs2::RedirectingPartyID RedirectingPartyID;


        typedef inap_cs2::RedirectionInformation RedirectionInformation;


        typedef inap_cs2::DisplayInformation DisplayInformation;


        typedef inap_cs2::ForwardCallIndicators ForwardCallIndicators;


        typedef inap_cs2::GenericNumbers GenericNumbers;


        typedef inap_cs2::ServiceInteractionIndicatorsTwo ServiceInteractionIndicatorsTwo;


        typedef inap_cs2::INServiceCompatibilityResponse INServiceCompatibilityResponse;


        typedef inap_cs2::ForwardGVNS ForwardGVNS;


        typedef inap_cs2::BackwardGVNS BackwardGVNS;


        typedef inap_cs2::ChargeNumber ChargeNumber;


        typedef inap_cs2::CallSegmentID CallSegmentID;


        typedef inap_cs2::LegID LegID;


////////// End Nested Class(es) //////////

    ConnectArg() : its::AsnSequence(27, false)
    {
        Initialize();
    }

    ConnectArg(its::Octets& octets) : its::AsnSequence(27, false)
    {
        Initialize();
        Decode(octets);
    }

    ConnectArg(const ConnectArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ConnectArg(its::AsnDescObject* description) : its::AsnSequence(27, description)
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
    static its::AsnDescObject* GetCorrelationIDStaticDescription();
    static its::AsnDescObject* GetCutAndPasteStaticDescription();
    static its::AsnDescObject* GetForwardingConditionStaticDescription();
    static its::AsnDescObject* GetISDNAccessRelatedInformationStaticDescription();
    static its::AsnDescObject* GetOriginalCalledPartyIDStaticDescription();
    static its::AsnDescObject* GetRouteListStaticDescription();
    static its::AsnDescObject* GetScfIDStaticDescription();
    static its::AsnDescObject* GetTravellingClassMarkStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();
    static its::AsnDescObject* GetCarrierStaticDescription();
    static its::AsnDescObject* GetServiceInteractionIndicatorsStaticDescription();
    static its::AsnDescObject* GetCallingPartyNumberStaticDescription();
    static its::AsnDescObject* GetCallingPartysCategoryStaticDescription();
    static its::AsnDescObject* GetRedirectingPartyIDStaticDescription();
    static its::AsnDescObject* GetRedirectionInformationStaticDescription();
    static its::AsnDescObject* GetDisplayInformationStaticDescription();
    static its::AsnDescObject* GetForwardCallIndicatorsStaticDescription();
    static its::AsnDescObject* GetGenericNumbersStaticDescription();
    static its::AsnDescObject* GetServiceInteractionIndicatorsTwoStaticDescription();
    static its::AsnDescObject* GetINServiceCompatibilityResponseStaticDescription();
    static its::AsnDescObject* GetForwardGVNSStaticDescription();
    static its::AsnDescObject* GetBackwardGVNSStaticDescription();
    static its::AsnDescObject* GetChargeNumberStaticDescription();
    static its::AsnDescObject* GetCallSegmentIDStaticDescription();
    static its::AsnDescObject* GetLegToBeCreatedStaticDescription();

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

    void SetCorrelationID(CorrelationID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCorrelationIDStaticDescription());
        AddElement(2, element);
    }

    void SetCorrelationID(const CorrelationID& element)
    {
        its::AsnObject& asnObject = const_cast<CorrelationID&>(element);
        asnObject.SetDescription(GetCorrelationIDStaticDescription());
        AddElement(2, element);
    }

    bool OptionCorrelationID() const
    {
        return Contains(2);
    }

    const CorrelationID& GetCorrelationID() const
    {
        ITS_REQUIRE(OptionCorrelationID());
        return static_cast<const CorrelationID&> (ElementAt(2));
    }

    void SetCutAndPaste(CutAndPaste* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCutAndPasteStaticDescription());
        AddElement(3, element);
    }

    void SetCutAndPaste(const CutAndPaste& element)
    {
        its::AsnObject& asnObject = const_cast<CutAndPaste&>(element);
        asnObject.SetDescription(GetCutAndPasteStaticDescription());
        AddElement(3, element);
    }

    bool OptionCutAndPaste() const
    {
        return Contains(3);
    }

    const CutAndPaste& GetCutAndPaste() const
    {
        ITS_REQUIRE(OptionCutAndPaste());
        return static_cast<const CutAndPaste&> (ElementAt(3));
    }

    void SetForwardingCondition(ForwardingCondition* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardingConditionStaticDescription());
        AddElement(4, element);
    }

    void SetForwardingCondition(const ForwardingCondition& element)
    {
        its::AsnObject& asnObject = const_cast<ForwardingCondition&>(element);
        asnObject.SetDescription(GetForwardingConditionStaticDescription());
        AddElement(4, element);
    }

    bool OptionForwardingCondition() const
    {
        return Contains(4);
    }

    const ForwardingCondition& GetForwardingCondition() const
    {
        ITS_REQUIRE(OptionForwardingCondition());
        return static_cast<const ForwardingCondition&> (ElementAt(4));
    }

    void SetISDNAccessRelatedInformation(ISDNAccessRelatedInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetISDNAccessRelatedInformationStaticDescription());
        AddElement(5, element);
    }

    void SetISDNAccessRelatedInformation(const ISDNAccessRelatedInformation& element)
    {
        its::AsnObject& asnObject = const_cast<ISDNAccessRelatedInformation&>(element);
        asnObject.SetDescription(GetISDNAccessRelatedInformationStaticDescription());
        AddElement(5, element);
    }

    bool OptionISDNAccessRelatedInformation() const
    {
        return Contains(5);
    }

    const ISDNAccessRelatedInformation& GetISDNAccessRelatedInformation() const
    {
        ITS_REQUIRE(OptionISDNAccessRelatedInformation());
        return static_cast<const ISDNAccessRelatedInformation&> (ElementAt(5));
    }

    void SetOriginalCalledPartyID(OriginalCalledPartyID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOriginalCalledPartyIDStaticDescription());
        AddElement(6, element);
    }

    void SetOriginalCalledPartyID(const OriginalCalledPartyID& element)
    {
        its::AsnObject& asnObject = const_cast<OriginalCalledPartyID&>(element);
        asnObject.SetDescription(GetOriginalCalledPartyIDStaticDescription());
        AddElement(6, element);
    }

    bool OptionOriginalCalledPartyID() const
    {
        return Contains(6);
    }

    const OriginalCalledPartyID& GetOriginalCalledPartyID() const
    {
        ITS_REQUIRE(OptionOriginalCalledPartyID());
        return static_cast<const OriginalCalledPartyID&> (ElementAt(6));
    }

    void SetRouteList(RouteList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRouteListStaticDescription());
        AddElement(7, element);
    }

    void SetRouteList(const RouteList& element)
    {
        its::AsnObject& asnObject = const_cast<RouteList&>(element);
        asnObject.SetDescription(GetRouteListStaticDescription());
        AddElement(7, element);
    }

    bool OptionRouteList() const
    {
        return Contains(7);
    }

    const RouteList& GetRouteList() const
    {
        ITS_REQUIRE(OptionRouteList());
        return static_cast<const RouteList&> (ElementAt(7));
    }

    void SetScfID(ScfID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetScfIDStaticDescription());
        AddElement(8, element);
    }

    void SetScfID(const ScfID& element)
    {
        its::AsnObject& asnObject = const_cast<ScfID&>(element);
        asnObject.SetDescription(GetScfIDStaticDescription());
        AddElement(8, element);
    }

    bool OptionScfID() const
    {
        return Contains(8);
    }

    const ScfID& GetScfID() const
    {
        ITS_REQUIRE(OptionScfID());
        return static_cast<const ScfID&> (ElementAt(8));
    }

    void SetTravellingClassMark(TravellingClassMark* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTravellingClassMarkStaticDescription());
        AddElement(9, element);
    }

    void SetTravellingClassMark(const TravellingClassMark& element)
    {
        its::AsnObject& asnObject = const_cast<TravellingClassMark&>(element);
        asnObject.SetDescription(GetTravellingClassMarkStaticDescription());
        AddElement(9, element);
    }

    bool OptionTravellingClassMark() const
    {
        return Contains(9);
    }

    const TravellingClassMark& GetTravellingClassMark() const
    {
        ITS_REQUIRE(OptionTravellingClassMark());
        return static_cast<const TravellingClassMark&> (ElementAt(9));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(10, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(10, element);
    }

    bool OptionExtensions() const
    {
        return Contains(10);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(10));
    }

    void SetCarrier(Carrier* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCarrierStaticDescription());
        AddElement(11, element);
    }

    void SetCarrier(const Carrier& element)
    {
        its::AsnObject& asnObject = const_cast<Carrier&>(element);
        asnObject.SetDescription(GetCarrierStaticDescription());
        AddElement(11, element);
    }

    bool OptionCarrier() const
    {
        return Contains(11);
    }

    const Carrier& GetCarrier() const
    {
        ITS_REQUIRE(OptionCarrier());
        return static_cast<const Carrier&> (ElementAt(11));
    }

    void SetServiceInteractionIndicators(ServiceInteractionIndicators* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetServiceInteractionIndicatorsStaticDescription());
        AddElement(12, element);
    }

    void SetServiceInteractionIndicators(const ServiceInteractionIndicators& element)
    {
        its::AsnObject& asnObject = const_cast<ServiceInteractionIndicators&>(element);
        asnObject.SetDescription(GetServiceInteractionIndicatorsStaticDescription());
        AddElement(12, element);
    }

    bool OptionServiceInteractionIndicators() const
    {
        return Contains(12);
    }

    const ServiceInteractionIndicators& GetServiceInteractionIndicators() const
    {
        ITS_REQUIRE(OptionServiceInteractionIndicators());
        return static_cast<const ServiceInteractionIndicators&> (ElementAt(12));
    }

    void SetCallingPartyNumber(CallingPartyNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingPartyNumberStaticDescription());
        AddElement(13, element);
    }

    void SetCallingPartyNumber(const CallingPartyNumber& element)
    {
        its::AsnObject& asnObject = const_cast<CallingPartyNumber&>(element);
        asnObject.SetDescription(GetCallingPartyNumberStaticDescription());
        AddElement(13, element);
    }

    bool OptionCallingPartyNumber() const
    {
        return Contains(13);
    }

    const CallingPartyNumber& GetCallingPartyNumber() const
    {
        ITS_REQUIRE(OptionCallingPartyNumber());
        return static_cast<const CallingPartyNumber&> (ElementAt(13));
    }

    void SetCallingPartysCategory(CallingPartysCategory* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingPartysCategoryStaticDescription());
        AddElement(14, element);
    }

    void SetCallingPartysCategory(const CallingPartysCategory& element)
    {
        its::AsnObject& asnObject = const_cast<CallingPartysCategory&>(element);
        asnObject.SetDescription(GetCallingPartysCategoryStaticDescription());
        AddElement(14, element);
    }

    bool OptionCallingPartysCategory() const
    {
        return Contains(14);
    }

    const CallingPartysCategory& GetCallingPartysCategory() const
    {
        ITS_REQUIRE(OptionCallingPartysCategory());
        return static_cast<const CallingPartysCategory&> (ElementAt(14));
    }

    void SetRedirectingPartyID(RedirectingPartyID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRedirectingPartyIDStaticDescription());
        AddElement(15, element);
    }

    void SetRedirectingPartyID(const RedirectingPartyID& element)
    {
        its::AsnObject& asnObject = const_cast<RedirectingPartyID&>(element);
        asnObject.SetDescription(GetRedirectingPartyIDStaticDescription());
        AddElement(15, element);
    }

    bool OptionRedirectingPartyID() const
    {
        return Contains(15);
    }

    const RedirectingPartyID& GetRedirectingPartyID() const
    {
        ITS_REQUIRE(OptionRedirectingPartyID());
        return static_cast<const RedirectingPartyID&> (ElementAt(15));
    }

    void SetRedirectionInformation(RedirectionInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRedirectionInformationStaticDescription());
        AddElement(16, element);
    }

    void SetRedirectionInformation(const RedirectionInformation& element)
    {
        its::AsnObject& asnObject = const_cast<RedirectionInformation&>(element);
        asnObject.SetDescription(GetRedirectionInformationStaticDescription());
        AddElement(16, element);
    }

    bool OptionRedirectionInformation() const
    {
        return Contains(16);
    }

    const RedirectionInformation& GetRedirectionInformation() const
    {
        ITS_REQUIRE(OptionRedirectionInformation());
        return static_cast<const RedirectionInformation&> (ElementAt(16));
    }

    void SetDisplayInformation(DisplayInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDisplayInformationStaticDescription());
        AddElement(17, element);
    }

    void SetDisplayInformation(const DisplayInformation& element)
    {
        its::AsnObject& asnObject = const_cast<DisplayInformation&>(element);
        asnObject.SetDescription(GetDisplayInformationStaticDescription());
        AddElement(17, element);
    }

    bool OptionDisplayInformation() const
    {
        return Contains(17);
    }

    const DisplayInformation& GetDisplayInformation() const
    {
        ITS_REQUIRE(OptionDisplayInformation());
        return static_cast<const DisplayInformation&> (ElementAt(17));
    }

    void SetForwardCallIndicators(ForwardCallIndicators* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardCallIndicatorsStaticDescription());
        AddElement(18, element);
    }

    void SetForwardCallIndicators(const ForwardCallIndicators& element)
    {
        its::AsnObject& asnObject = const_cast<ForwardCallIndicators&>(element);
        asnObject.SetDescription(GetForwardCallIndicatorsStaticDescription());
        AddElement(18, element);
    }

    bool OptionForwardCallIndicators() const
    {
        return Contains(18);
    }

    const ForwardCallIndicators& GetForwardCallIndicators() const
    {
        ITS_REQUIRE(OptionForwardCallIndicators());
        return static_cast<const ForwardCallIndicators&> (ElementAt(18));
    }

    void SetGenericNumbers(GenericNumbers* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGenericNumbersStaticDescription());
        AddElement(19, element);
    }

    void SetGenericNumbers(const GenericNumbers& element)
    {
        its::AsnObject& asnObject = const_cast<GenericNumbers&>(element);
        asnObject.SetDescription(GetGenericNumbersStaticDescription());
        AddElement(19, element);
    }

    bool OptionGenericNumbers() const
    {
        return Contains(19);
    }

    const GenericNumbers& GetGenericNumbers() const
    {
        ITS_REQUIRE(OptionGenericNumbers());
        return static_cast<const GenericNumbers&> (ElementAt(19));
    }

    void SetServiceInteractionIndicatorsTwo(ServiceInteractionIndicatorsTwo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetServiceInteractionIndicatorsTwoStaticDescription());
        AddElement(20, element);
    }

    void SetServiceInteractionIndicatorsTwo(const ServiceInteractionIndicatorsTwo& element)
    {
        its::AsnObject& asnObject = const_cast<ServiceInteractionIndicatorsTwo&>(element);
        asnObject.SetDescription(GetServiceInteractionIndicatorsTwoStaticDescription());
        AddElement(20, element);
    }

    bool OptionServiceInteractionIndicatorsTwo() const
    {
        return Contains(20);
    }

    const ServiceInteractionIndicatorsTwo& GetServiceInteractionIndicatorsTwo() const
    {
        ITS_REQUIRE(OptionServiceInteractionIndicatorsTwo());
        return static_cast<const ServiceInteractionIndicatorsTwo&> (ElementAt(20));
    }

    void SetINServiceCompatibilityResponse(INServiceCompatibilityResponse* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetINServiceCompatibilityResponseStaticDescription());
        AddElement(21, element);
    }

    void SetINServiceCompatibilityResponse(const INServiceCompatibilityResponse& element)
    {
        its::AsnObject& asnObject = const_cast<INServiceCompatibilityResponse&>(element);
        asnObject.SetDescription(GetINServiceCompatibilityResponseStaticDescription());
        AddElement(21, element);
    }

    bool OptionINServiceCompatibilityResponse() const
    {
        return Contains(21);
    }

    const INServiceCompatibilityResponse& GetINServiceCompatibilityResponse() const
    {
        ITS_REQUIRE(OptionINServiceCompatibilityResponse());
        return static_cast<const INServiceCompatibilityResponse&> (ElementAt(21));
    }

    void SetForwardGVNS(ForwardGVNS* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardGVNSStaticDescription());
        AddElement(22, element);
    }

    void SetForwardGVNS(const ForwardGVNS& element)
    {
        its::AsnObject& asnObject = const_cast<ForwardGVNS&>(element);
        asnObject.SetDescription(GetForwardGVNSStaticDescription());
        AddElement(22, element);
    }

    bool OptionForwardGVNS() const
    {
        return Contains(22);
    }

    const ForwardGVNS& GetForwardGVNS() const
    {
        ITS_REQUIRE(OptionForwardGVNS());
        return static_cast<const ForwardGVNS&> (ElementAt(22));
    }

    void SetBackwardGVNS(BackwardGVNS* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBackwardGVNSStaticDescription());
        AddElement(23, element);
    }

    void SetBackwardGVNS(const BackwardGVNS& element)
    {
        its::AsnObject& asnObject = const_cast<BackwardGVNS&>(element);
        asnObject.SetDescription(GetBackwardGVNSStaticDescription());
        AddElement(23, element);
    }

    bool OptionBackwardGVNS() const
    {
        return Contains(23);
    }

    const BackwardGVNS& GetBackwardGVNS() const
    {
        ITS_REQUIRE(OptionBackwardGVNS());
        return static_cast<const BackwardGVNS&> (ElementAt(23));
    }

    void SetChargeNumber(ChargeNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetChargeNumberStaticDescription());
        AddElement(24, element);
    }

    void SetChargeNumber(const ChargeNumber& element)
    {
        its::AsnObject& asnObject = const_cast<ChargeNumber&>(element);
        asnObject.SetDescription(GetChargeNumberStaticDescription());
        AddElement(24, element);
    }

    bool OptionChargeNumber() const
    {
        return Contains(24);
    }

    const ChargeNumber& GetChargeNumber() const
    {
        ITS_REQUIRE(OptionChargeNumber());
        return static_cast<const ChargeNumber&> (ElementAt(24));
    }

    void SetCallSegmentID(CallSegmentID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallSegmentIDStaticDescription());
        AddElement(25, element);
    }

    void SetCallSegmentID(const CallSegmentID& element)
    {
        its::AsnObject& asnObject = const_cast<CallSegmentID&>(element);
        asnObject.SetDescription(GetCallSegmentIDStaticDescription());
        AddElement(25, element);
    }

    bool OptionCallSegmentID() const
    {
        return Contains(25);
    }

    const CallSegmentID& GetCallSegmentID() const
    {
        ITS_REQUIRE(OptionCallSegmentID());
        return static_cast<const CallSegmentID&> (ElementAt(25));
    }

    void SetLegToBeCreated(LegID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLegToBeCreatedStaticDescription());
        AddElement(26, element);
    }

    void SetLegToBeCreated(const LegID& element)
    {
        its::AsnObject& asnObject = const_cast<LegID&>(element);
        asnObject.SetDescription(GetLegToBeCreatedStaticDescription());
        AddElement(26, element);
    }

    bool OptionLegToBeCreated() const
    {
        return Contains(26);
    }

    const LegID& GetLegToBeCreated() const
    {
        ITS_REQUIRE(OptionLegToBeCreated());
        return static_cast<const LegID&> (ElementAt(26));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_CONNECT_ARG_H_)

