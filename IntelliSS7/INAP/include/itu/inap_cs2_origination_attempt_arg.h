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


#if !defined(_INAP_CS2_ORIGINATION_ATTEMPT_ARG_H_)
#define _INAP_CS2_ORIGINATION_ATTEMPT_ARG_H_

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
#include <AsnEnumerated.h>

#include <inap_cs2_dp_specific_common_parameters.h>
#include <inap_cs2_calling_party_business_group_id.h>
#include <inap_cs2_calling_party_subaddress.h>
#include <inap_cs2_facility_group.h>
#include <inap_cs2_facility_group_member.h>
#include <inap_cs2_carrier.h>
#include <inap_cs2_travelling_class_mark.h>
#include <inap_cs2_extension_field.h>
#include <inap_cs2_component_type.h>
#include <inap_cs2_component_correlation_id.h>



namespace inap_cs2 {



class OriginationAttemptArg : public its::AsnSequence
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


        typedef inap_cs2::CallingPartyBusinessGroupID CallingPartyBusinessGroupID;


        typedef inap_cs2::CallingPartySubaddress CallingPartySubaddress;


        typedef inap_cs2::FacilityGroup FacilityGroup;


        typedef inap_cs2::FacilityGroupMember FacilityGroupMember;


        typedef inap_cs2::Carrier Carrier;


        typedef inap_cs2::TravellingClassMark TravellingClassMark;


        typedef inap_cs2::ComponentType ComponentType;


        typedef inap_cs2::ComponentCorrelationID ComponentCorrelationID;


////////// End Nested Class(es) //////////

    OriginationAttemptArg() : its::AsnSequence(10, false)
    {
        Initialize();
    }

    OriginationAttemptArg(its::Octets& octets) : its::AsnSequence(10, false)
    {
        Initialize();
        Decode(octets);
    }

    OriginationAttemptArg(const OriginationAttemptArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    OriginationAttemptArg(its::AsnDescObject* description) : its::AsnSequence(10, description)
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
    static its::AsnDescObject* GetCallingPartyBusinessGroupIDStaticDescription();
    static its::AsnDescObject* GetCallingPartySubaddressStaticDescription();
    static its::AsnDescObject* GetCallingFacilityGroupStaticDescription();
    static its::AsnDescObject* GetCallingFacilityGroupMemberStaticDescription();
    static its::AsnDescObject* GetCarrierStaticDescription();
    static its::AsnDescObject* GetTravellingClassMarkStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();
    static its::AsnDescObject* GetComponentTypeStaticDescription();
    static its::AsnDescObject* GetComponenttCorrelationIDStaticDescription();

public:

    virtual ~OriginationAttemptArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new OriginationAttemptArg(*this);
    }

    virtual std::string GetName() const
    { return "OriginationAttemptArg"; }

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

    void SetCallingPartyBusinessGroupID(CallingPartyBusinessGroupID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingPartyBusinessGroupIDStaticDescription());
        AddElement(1, element);
    }

    void SetCallingPartyBusinessGroupID(const CallingPartyBusinessGroupID& element)
    {
        its::AsnObject& asnObject = const_cast<CallingPartyBusinessGroupID&>(element);
        asnObject.SetDescription(GetCallingPartyBusinessGroupIDStaticDescription());
        AddElement(1, element);
    }

    bool OptionCallingPartyBusinessGroupID() const
    {
        return Contains(1);
    }

    const CallingPartyBusinessGroupID& GetCallingPartyBusinessGroupID() const
    {
        ITS_REQUIRE(OptionCallingPartyBusinessGroupID());
        return static_cast<const CallingPartyBusinessGroupID&> (ElementAt(1));
    }

    void SetCallingPartySubaddress(CallingPartySubaddress* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingPartySubaddressStaticDescription());
        AddElement(2, element);
    }

    void SetCallingPartySubaddress(const CallingPartySubaddress& element)
    {
        its::AsnObject& asnObject = const_cast<CallingPartySubaddress&>(element);
        asnObject.SetDescription(GetCallingPartySubaddressStaticDescription());
        AddElement(2, element);
    }

    bool OptionCallingPartySubaddress() const
    {
        return Contains(2);
    }

    const CallingPartySubaddress& GetCallingPartySubaddress() const
    {
        ITS_REQUIRE(OptionCallingPartySubaddress());
        return static_cast<const CallingPartySubaddress&> (ElementAt(2));
    }

    void SetCallingFacilityGroup(FacilityGroup* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingFacilityGroupStaticDescription());
        AddElement(3, element);
    }

    void SetCallingFacilityGroup(const FacilityGroup& element)
    {
        its::AsnObject& asnObject = const_cast<FacilityGroup&>(element);
        asnObject.SetDescription(GetCallingFacilityGroupStaticDescription());
        AddElement(3, element);
    }

    bool OptionCallingFacilityGroup() const
    {
        return Contains(3);
    }

    const FacilityGroup& GetCallingFacilityGroup() const
    {
        ITS_REQUIRE(OptionCallingFacilityGroup());
        return static_cast<const FacilityGroup&> (ElementAt(3));
    }

    void SetCallingFacilityGroupMember(FacilityGroupMember* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingFacilityGroupMemberStaticDescription());
        AddElement(4, element);
    }

    void SetCallingFacilityGroupMember(const FacilityGroupMember& element)
    {
        its::AsnObject& asnObject = const_cast<FacilityGroupMember&>(element);
        asnObject.SetDescription(GetCallingFacilityGroupMemberStaticDescription());
        AddElement(4, element);
    }

    bool OptionCallingFacilityGroupMember() const
    {
        return Contains(4);
    }

    const FacilityGroupMember& GetCallingFacilityGroupMember() const
    {
        ITS_REQUIRE(OptionCallingFacilityGroupMember());
        return static_cast<const FacilityGroupMember&> (ElementAt(4));
    }

    void SetCarrier(Carrier* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCarrierStaticDescription());
        AddElement(5, element);
    }

    void SetCarrier(const Carrier& element)
    {
        its::AsnObject& asnObject = const_cast<Carrier&>(element);
        asnObject.SetDescription(GetCarrierStaticDescription());
        AddElement(5, element);
    }

    bool OptionCarrier() const
    {
        return Contains(5);
    }

    const Carrier& GetCarrier() const
    {
        ITS_REQUIRE(OptionCarrier());
        return static_cast<const Carrier&> (ElementAt(5));
    }

    void SetTravellingClassMark(TravellingClassMark* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTravellingClassMarkStaticDescription());
        AddElement(6, element);
    }

    void SetTravellingClassMark(const TravellingClassMark& element)
    {
        its::AsnObject& asnObject = const_cast<TravellingClassMark&>(element);
        asnObject.SetDescription(GetTravellingClassMarkStaticDescription());
        AddElement(6, element);
    }

    bool OptionTravellingClassMark() const
    {
        return Contains(6);
    }

    const TravellingClassMark& GetTravellingClassMark() const
    {
        ITS_REQUIRE(OptionTravellingClassMark());
        return static_cast<const TravellingClassMark&> (ElementAt(6));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(7, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(7, element);
    }

    bool OptionExtensions() const
    {
        return Contains(7);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(7));
    }

    void SetComponentType(ComponentType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetComponentTypeStaticDescription());
        AddElement(8, element);
    }

    void SetComponentType(const ComponentType& element)
    {
        its::AsnObject& asnObject = const_cast<ComponentType&>(element);
        asnObject.SetDescription(GetComponentTypeStaticDescription());
        AddElement(8, element);
    }

    bool OptionComponentType() const
    {
        return Contains(8);
    }

    const ComponentType& GetComponentType() const
    {
        ITS_REQUIRE(OptionComponentType());
        return static_cast<const ComponentType&> (ElementAt(8));
    }

    void SetComponenttCorrelationID(ComponentCorrelationID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetComponenttCorrelationIDStaticDescription());
        AddElement(9, element);
    }

    void SetComponenttCorrelationID(const ComponentCorrelationID& element)
    {
        its::AsnObject& asnObject = const_cast<ComponentCorrelationID&>(element);
        asnObject.SetDescription(GetComponenttCorrelationIDStaticDescription());
        AddElement(9, element);
    }

    bool OptionComponenttCorrelationID() const
    {
        return Contains(9);
    }

    const ComponentCorrelationID& GetComponenttCorrelationID() const
    {
        ITS_REQUIRE(OptionComponenttCorrelationID());
        return static_cast<const ComponentCorrelationID&> (ElementAt(9));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_ORIGINATION_ATTEMPT_ARG_H_)
