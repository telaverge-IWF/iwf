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


#if !defined(_MAP_V2_DELETE_SUBSCRIBER_DATA_ARG_H_)
#define _MAP_V2_DELETE_SUBSCRIBER_DATA_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>
#include <AsnOctetString.h>
#include <AsnSequenceOf.h>

#include <map_v2_imsi.h>
#include <map_v2_basic_service_list.h>
#include <map_v2_ss_list.h>
#include <map_v2_zone_code.h>



namespace map_v2 {



class DeleteSubscriberDataArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class RoamingRestrictionDueToUnsupportedFeature : public its::AsnNull
    {
    public:

        RoamingRestrictionDueToUnsupportedFeature() : its::AsnNull(false)
        {
            Initialize();
        }

        RoamingRestrictionDueToUnsupportedFeature(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        RoamingRestrictionDueToUnsupportedFeature(const RoamingRestrictionDueToUnsupportedFeature& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        RoamingRestrictionDueToUnsupportedFeature(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~RoamingRestrictionDueToUnsupportedFeature()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new RoamingRestrictionDueToUnsupportedFeature(*this);
        }

        virtual std::string GetName() const
        { return "RoamingRestrictionDueToUnsupportedFeature"; }

    };


        typedef map_v2::IMSI IMSI;


        typedef map_v2::BasicServiceList BasicServiceList;


        typedef map_v2::SS_List SS_List;


        typedef map_v2::ZoneCode ZoneCode;


////////// End Nested Class(es) //////////

    DeleteSubscriberDataArg() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    DeleteSubscriberDataArg(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    DeleteSubscriberDataArg(const DeleteSubscriberDataArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    DeleteSubscriberDataArg(its::AsnDescObject* description) : its::AsnSequence(5, description)
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

    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetBasicServiceListStaticDescription();
    static its::AsnDescObject* GetSs_ListStaticDescription();
    static its::AsnDescObject* GetRoamingRestrictionDueToUnsupportedFeatureStaticDescription();
    static its::AsnDescObject* GetRegionalSubscriptionIdentifierStaticDescription();

public:

    virtual ~DeleteSubscriberDataArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new DeleteSubscriberDataArg(*this);
    }

    virtual std::string GetName() const
    { return "DeleteSubscriberDataArg"; }

    void SetImsi(IMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    void SetImsi(const IMSI& element)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(element);
        asnObject.SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    const IMSI& GetImsi() const
    {
        return static_cast<const IMSI&> (ElementAt(0));
    }

    void SetBasicServiceList(BasicServiceList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBasicServiceListStaticDescription());
        AddElement(1, element);
    }

    void SetBasicServiceList(const BasicServiceList& element)
    {
        its::AsnObject& asnObject = const_cast<BasicServiceList&>(element);
        asnObject.SetDescription(GetBasicServiceListStaticDescription());
        AddElement(1, element);
    }

    bool OptionBasicServiceList() const
    {
        return Contains(1);
    }

    const BasicServiceList& GetBasicServiceList() const
    {
        ITS_REQUIRE(OptionBasicServiceList());
        return static_cast<const BasicServiceList&> (ElementAt(1));
    }

    void SetSs_List(SS_List* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_ListStaticDescription());
        AddElement(2, element);
    }

    void SetSs_List(const SS_List& element)
    {
        its::AsnObject& asnObject = const_cast<SS_List&>(element);
        asnObject.SetDescription(GetSs_ListStaticDescription());
        AddElement(2, element);
    }

    bool OptionSs_List() const
    {
        return Contains(2);
    }

    const SS_List& GetSs_List() const
    {
        ITS_REQUIRE(OptionSs_List());
        return static_cast<const SS_List&> (ElementAt(2));
    }

    void SetRoamingRestrictionDueToUnsupportedFeature(RoamingRestrictionDueToUnsupportedFeature* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRoamingRestrictionDueToUnsupportedFeatureStaticDescription());
        AddElement(3, element);
    }

    void SetRoamingRestrictionDueToUnsupportedFeature(const RoamingRestrictionDueToUnsupportedFeature& element)
    {
        its::AsnObject& asnObject = const_cast<RoamingRestrictionDueToUnsupportedFeature&>(element);
        asnObject.SetDescription(GetRoamingRestrictionDueToUnsupportedFeatureStaticDescription());
        AddElement(3, element);
    }

    bool OptionRoamingRestrictionDueToUnsupportedFeature() const
    {
        return Contains(3);
    }

    const RoamingRestrictionDueToUnsupportedFeature& GetRoamingRestrictionDueToUnsupportedFeature() const
    {
        ITS_REQUIRE(OptionRoamingRestrictionDueToUnsupportedFeature());
        return static_cast<const RoamingRestrictionDueToUnsupportedFeature&> (ElementAt(3));
    }

    void SetRegionalSubscriptionIdentifier(ZoneCode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRegionalSubscriptionIdentifierStaticDescription());
        AddElement(4, element);
    }

    void SetRegionalSubscriptionIdentifier(const ZoneCode& element)
    {
        its::AsnObject& asnObject = const_cast<ZoneCode&>(element);
        asnObject.SetDescription(GetRegionalSubscriptionIdentifierStaticDescription());
        AddElement(4, element);
    }

    bool OptionRegionalSubscriptionIdentifier() const
    {
        return Contains(4);
    }

    const ZoneCode& GetRegionalSubscriptionIdentifier() const
    {
        ITS_REQUIRE(OptionRegionalSubscriptionIdentifier());
        return static_cast<const ZoneCode&> (ElementAt(4));
    }

};



} // namespace.

#endif    // !defined(_MAP_V2_DELETE_SUBSCRIBER_DATA_ARG_H_)

