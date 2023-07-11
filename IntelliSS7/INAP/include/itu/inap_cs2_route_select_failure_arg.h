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


#if !defined(_INAP_CS2_ROUTE_SELECT_FAILURE_ARG_H_)
#define _INAP_CS2_ROUTE_SELECT_FAILURE_ARG_H_

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
#include <AsnChoice.h>
#include <AsnInteger.h>

#include <inap_cs2_dp_specific_common_parameters.h>
#include <inap_cs2_called_party_number.h>
#include <inap_cs2_calling_party_business_group_id.h>
#include <inap_cs2_calling_party_subaddress.h>
#include <inap_cs2_facility_group.h>
#include <inap_cs2_facility_group_member.h>
#include <inap_cs2_cause.h>
#include <inap_cs2_original_called_party_id.h>
#include <inap_cs2_digits.h>
#include <inap_cs2_redirecting_party_id.h>
#include <inap_cs2_redirection_information.h>
#include <inap_cs2_route_list.h>
#include <inap_cs2_travelling_class_mark.h>
#include <inap_cs2_extension_field.h>
#include <inap_cs2_carrier.h>



namespace inap_cs2 {



class RouteSelectFailureArg : public its::AsnSequence
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


        typedef inap_cs2::DpSpecificCommonParameters DpSpecificCommonParameters;


        typedef inap_cs2::CalledPartyNumber CalledPartyNumber;


        typedef inap_cs2::CallingPartyBusinessGroupID CallingPartyBusinessGroupID;


        typedef inap_cs2::CallingPartySubaddress CallingPartySubaddress;


        typedef inap_cs2::FacilityGroup FacilityGroup;


        typedef inap_cs2::FacilityGroupMember FacilityGroupMember;


        typedef inap_cs2::Cause Cause;


        typedef inap_cs2::OriginalCalledPartyID OriginalCalledPartyID;


        typedef inap_cs2::Digits Digits;


        typedef inap_cs2::RedirectingPartyID RedirectingPartyID;


        typedef inap_cs2::RedirectionInformation RedirectionInformation;


        typedef inap_cs2::RouteList RouteList;


        typedef inap_cs2::TravellingClassMark TravellingClassMark;


        typedef inap_cs2::Carrier Carrier;


////////// End Nested Class(es) //////////

    RouteSelectFailureArg() : its::AsnSequence(15, false)
    {
        Initialize();
    }

    RouteSelectFailureArg(its::Octets& octets) : its::AsnSequence(15, false)
    {
        Initialize();
        Decode(octets);
    }

    RouteSelectFailureArg(const RouteSelectFailureArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    RouteSelectFailureArg(its::AsnDescObject* description) : its::AsnSequence(15, description)
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

    static its::AsnDescObject* GetDpSpecificCommonParametersStaticDescription();
    static its::AsnDescObject* GetDialledDigitsStaticDescription();
    static its::AsnDescObject* GetCallingPartyBusinessGroupIDStaticDescription();
    static its::AsnDescObject* GetCallingPartySubaddressStaticDescription();
    static its::AsnDescObject* GetCallingFacilityGroupStaticDescription();
    static its::AsnDescObject* GetCallingFacilityGroupMemberStaticDescription();
    static its::AsnDescObject* GetFailureCauseStaticDescription();
    static its::AsnDescObject* GetOriginalCalledPartyIDStaticDescription();
    static its::AsnDescObject* GetPrefixStaticDescription();
    static its::AsnDescObject* GetRedirectingPartyIDStaticDescription();
    static its::AsnDescObject* GetRedirectionInformationStaticDescription();
    static its::AsnDescObject* GetRouteListStaticDescription();
    static its::AsnDescObject* GetTravellingClassMarkStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();
    static its::AsnDescObject* GetCarrierStaticDescription();

public:

    virtual ~RouteSelectFailureArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RouteSelectFailureArg(*this);
    }

    virtual std::string GetName() const
    { return "RouteSelectFailureArg"; }

    void SetDpSpecificCommonParameters(DpSpecificCommonParameters* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDpSpecificCommonParametersStaticDescription());
        AddElement(0, element);
    }

    void SetDpSpecificCommonParameters(const DpSpecificCommonParameters& element)
    {
        its::AsnObject& asnObject = const_cast<DpSpecificCommonParameters&>(element);
        asnObject.SetDescription(GetDpSpecificCommonParametersStaticDescription());
        AddElement(0, element);
    }

    const DpSpecificCommonParameters& GetDpSpecificCommonParameters() const
    {
        return static_cast<const DpSpecificCommonParameters&> (ElementAt(0));
    }

    void SetDialledDigits(CalledPartyNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDialledDigitsStaticDescription());
        AddElement(1, element);
    }

    void SetDialledDigits(const CalledPartyNumber& element)
    {
        its::AsnObject& asnObject = const_cast<CalledPartyNumber&>(element);
        asnObject.SetDescription(GetDialledDigitsStaticDescription());
        AddElement(1, element);
    }

    bool OptionDialledDigits() const
    {
        return Contains(1);
    }

    const CalledPartyNumber& GetDialledDigits() const
    {
        ITS_REQUIRE(OptionDialledDigits());
        return static_cast<const CalledPartyNumber&> (ElementAt(1));
    }

    void SetCallingPartyBusinessGroupID(CallingPartyBusinessGroupID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingPartyBusinessGroupIDStaticDescription());
        AddElement(2, element);
    }

    void SetCallingPartyBusinessGroupID(const CallingPartyBusinessGroupID& element)
    {
        its::AsnObject& asnObject = const_cast<CallingPartyBusinessGroupID&>(element);
        asnObject.SetDescription(GetCallingPartyBusinessGroupIDStaticDescription());
        AddElement(2, element);
    }

    bool OptionCallingPartyBusinessGroupID() const
    {
        return Contains(2);
    }

    const CallingPartyBusinessGroupID& GetCallingPartyBusinessGroupID() const
    {
        ITS_REQUIRE(OptionCallingPartyBusinessGroupID());
        return static_cast<const CallingPartyBusinessGroupID&> (ElementAt(2));
    }

    void SetCallingPartySubaddress(CallingPartySubaddress* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingPartySubaddressStaticDescription());
        AddElement(3, element);
    }

    void SetCallingPartySubaddress(const CallingPartySubaddress& element)
    {
        its::AsnObject& asnObject = const_cast<CallingPartySubaddress&>(element);
        asnObject.SetDescription(GetCallingPartySubaddressStaticDescription());
        AddElement(3, element);
    }

    bool OptionCallingPartySubaddress() const
    {
        return Contains(3);
    }

    const CallingPartySubaddress& GetCallingPartySubaddress() const
    {
        ITS_REQUIRE(OptionCallingPartySubaddress());
        return static_cast<const CallingPartySubaddress&> (ElementAt(3));
    }

    void SetCallingFacilityGroup(FacilityGroup* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingFacilityGroupStaticDescription());
        AddElement(4, element);
    }

    void SetCallingFacilityGroup(const FacilityGroup& element)
    {
        its::AsnObject& asnObject = const_cast<FacilityGroup&>(element);
        asnObject.SetDescription(GetCallingFacilityGroupStaticDescription());
        AddElement(4, element);
    }

    bool OptionCallingFacilityGroup() const
    {
        return Contains(4);
    }

    const FacilityGroup& GetCallingFacilityGroup() const
    {
        ITS_REQUIRE(OptionCallingFacilityGroup());
        return static_cast<const FacilityGroup&> (ElementAt(4));
    }

    void SetCallingFacilityGroupMember(FacilityGroupMember* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingFacilityGroupMemberStaticDescription());
        AddElement(5, element);
    }

    void SetCallingFacilityGroupMember(const FacilityGroupMember& element)
    {
        its::AsnObject& asnObject = const_cast<FacilityGroupMember&>(element);
        asnObject.SetDescription(GetCallingFacilityGroupMemberStaticDescription());
        AddElement(5, element);
    }

    bool OptionCallingFacilityGroupMember() const
    {
        return Contains(5);
    }

    const FacilityGroupMember& GetCallingFacilityGroupMember() const
    {
        ITS_REQUIRE(OptionCallingFacilityGroupMember());
        return static_cast<const FacilityGroupMember&> (ElementAt(5));
    }

    void SetFailureCause(Cause* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetFailureCauseStaticDescription());
        AddElement(6, element);
    }

    void SetFailureCause(const Cause& element)
    {
        its::AsnObject& asnObject = const_cast<Cause&>(element);
        asnObject.SetDescription(GetFailureCauseStaticDescription());
        AddElement(6, element);
    }

    bool OptionFailureCause() const
    {
        return Contains(6);
    }

    const Cause& GetFailureCause() const
    {
        ITS_REQUIRE(OptionFailureCause());
        return static_cast<const Cause&> (ElementAt(6));
    }

    void SetOriginalCalledPartyID(OriginalCalledPartyID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOriginalCalledPartyIDStaticDescription());
        AddElement(7, element);
    }

    void SetOriginalCalledPartyID(const OriginalCalledPartyID& element)
    {
        its::AsnObject& asnObject = const_cast<OriginalCalledPartyID&>(element);
        asnObject.SetDescription(GetOriginalCalledPartyIDStaticDescription());
        AddElement(7, element);
    }

    bool OptionOriginalCalledPartyID() const
    {
        return Contains(7);
    }

    const OriginalCalledPartyID& GetOriginalCalledPartyID() const
    {
        ITS_REQUIRE(OptionOriginalCalledPartyID());
        return static_cast<const OriginalCalledPartyID&> (ElementAt(7));
    }

    void SetPrefix(Digits* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPrefixStaticDescription());
        AddElement(8, element);
    }

    void SetPrefix(const Digits& element)
    {
        its::AsnObject& asnObject = const_cast<Digits&>(element);
        asnObject.SetDescription(GetPrefixStaticDescription());
        AddElement(8, element);
    }

    bool OptionPrefix() const
    {
        return Contains(8);
    }

    const Digits& GetPrefix() const
    {
        ITS_REQUIRE(OptionPrefix());
        return static_cast<const Digits&> (ElementAt(8));
    }

    void SetRedirectingPartyID(RedirectingPartyID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRedirectingPartyIDStaticDescription());
        AddElement(9, element);
    }

    void SetRedirectingPartyID(const RedirectingPartyID& element)
    {
        its::AsnObject& asnObject = const_cast<RedirectingPartyID&>(element);
        asnObject.SetDescription(GetRedirectingPartyIDStaticDescription());
        AddElement(9, element);
    }

    bool OptionRedirectingPartyID() const
    {
        return Contains(9);
    }

    const RedirectingPartyID& GetRedirectingPartyID() const
    {
        ITS_REQUIRE(OptionRedirectingPartyID());
        return static_cast<const RedirectingPartyID&> (ElementAt(9));
    }

    void SetRedirectionInformation(RedirectionInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRedirectionInformationStaticDescription());
        AddElement(10, element);
    }

    void SetRedirectionInformation(const RedirectionInformation& element)
    {
        its::AsnObject& asnObject = const_cast<RedirectionInformation&>(element);
        asnObject.SetDescription(GetRedirectionInformationStaticDescription());
        AddElement(10, element);
    }

    bool OptionRedirectionInformation() const
    {
        return Contains(10);
    }

    const RedirectionInformation& GetRedirectionInformation() const
    {
        ITS_REQUIRE(OptionRedirectionInformation());
        return static_cast<const RedirectionInformation&> (ElementAt(10));
    }

    void SetRouteList(RouteList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRouteListStaticDescription());
        AddElement(11, element);
    }

    void SetRouteList(const RouteList& element)
    {
        its::AsnObject& asnObject = const_cast<RouteList&>(element);
        asnObject.SetDescription(GetRouteListStaticDescription());
        AddElement(11, element);
    }

    bool OptionRouteList() const
    {
        return Contains(11);
    }

    const RouteList& GetRouteList() const
    {
        ITS_REQUIRE(OptionRouteList());
        return static_cast<const RouteList&> (ElementAt(11));
    }

    void SetTravellingClassMark(TravellingClassMark* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTravellingClassMarkStaticDescription());
        AddElement(12, element);
    }

    void SetTravellingClassMark(const TravellingClassMark& element)
    {
        its::AsnObject& asnObject = const_cast<TravellingClassMark&>(element);
        asnObject.SetDescription(GetTravellingClassMarkStaticDescription());
        AddElement(12, element);
    }

    bool OptionTravellingClassMark() const
    {
        return Contains(12);
    }

    const TravellingClassMark& GetTravellingClassMark() const
    {
        ITS_REQUIRE(OptionTravellingClassMark());
        return static_cast<const TravellingClassMark&> (ElementAt(12));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(13, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(13, element);
    }

    bool OptionExtensions() const
    {
        return Contains(13);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(13));
    }

    void SetCarrier(Carrier* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCarrierStaticDescription());
        AddElement(14, element);
    }

    void SetCarrier(const Carrier& element)
    {
        its::AsnObject& asnObject = const_cast<Carrier&>(element);
        asnObject.SetDescription(GetCarrierStaticDescription());
        AddElement(14, element);
    }

    bool OptionCarrier() const
    {
        return Contains(14);
    }

    const Carrier& GetCarrier() const
    {
        ITS_REQUIRE(OptionCarrier());
        return static_cast<const Carrier&> (ElementAt(14));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_ROUTE_SELECT_FAILURE_ARG_H_)

