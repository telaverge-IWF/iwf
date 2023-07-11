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


#if !defined(_MAP_V2_INSERT_SUBSCRIBER_DATA_ARG_H_)
#define _MAP_V2_INSERT_SUBSCRIBER_DATA_ARG_H_

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
#include <AsnEnumerated.h>
#include <AsnSequenceOf.h>

#include <map_v2_imsi.h>
#include <map_v2_isdn_address_string.h>
#include <map_v2_category.h>
#include <map_v2_subscriber_status.h>
#include <map_v2_bearer_service_list.h>
#include <map_v2_teleservice_list.h>
#include <map_v2_ss_info_list.h>
#include <map_v2_odb_data.h>
#include <map_v2_zone_code_list.h>



namespace map_v2 {



class InsertSubscriberDataArg : public its::AsnSequence
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


        typedef map_v2::ISDN_AddressString ISDN_AddressString;


        typedef map_v2::Category Category;


        typedef map_v2::SubscriberStatus SubscriberStatus;


        typedef map_v2::BearerServiceList BearerServiceList;


        typedef map_v2::TeleserviceList TeleserviceList;


        typedef map_v2::SS_InfoList SS_InfoList;


        typedef map_v2::ODB_Data ODB_Data;


        typedef map_v2::ZoneCodeList ZoneCodeList;


////////// End Nested Class(es) //////////

    InsertSubscriberDataArg() : its::AsnSequence(10, false)
    {
        Initialize();
    }

    InsertSubscriberDataArg(its::Octets& octets) : its::AsnSequence(10, false)
    {
        Initialize();
        Decode(octets);
    }

    InsertSubscriberDataArg(const InsertSubscriberDataArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    InsertSubscriberDataArg(its::AsnDescObject* description) : its::AsnSequence(10, description)
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
    static its::AsnDescObject* GetMsisdnStaticDescription();
    static its::AsnDescObject* GetCategoryStaticDescription();
    static its::AsnDescObject* GetSubscriberStatusStaticDescription();
    static its::AsnDescObject* GetBearerServiceListStaticDescription();
    static its::AsnDescObject* GetTeleserviceListStaticDescription();
    static its::AsnDescObject* GetProvisionedSSStaticDescription();
    static its::AsnDescObject* GetOdb_DataStaticDescription();
    static its::AsnDescObject* GetRoamingRestrictionDueToUnsupportedFeatureStaticDescription();
    static its::AsnDescObject* GetRegionalSubscriptionDataStaticDescription();

public:

    virtual ~InsertSubscriberDataArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new InsertSubscriberDataArg(*this);
    }

    virtual std::string GetName() const
    { return "InsertSubscriberDataArg"; }

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

    bool OptionImsi() const
    {
        return Contains(0);
    }

    const IMSI& GetImsi() const
    {
        ITS_REQUIRE(OptionImsi());
        return static_cast<const IMSI&> (ElementAt(0));
    }

    void SetMsisdn(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMsisdnStaticDescription());
        AddElement(1, element);
    }

    void SetMsisdn(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetMsisdnStaticDescription());
        AddElement(1, element);
    }

    bool OptionMsisdn() const
    {
        return Contains(1);
    }

    const ISDN_AddressString& GetMsisdn() const
    {
        ITS_REQUIRE(OptionMsisdn());
        return static_cast<const ISDN_AddressString&> (ElementAt(1));
    }

    void SetCategory(Category* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCategoryStaticDescription());
        AddElement(2, element);
    }

    void SetCategory(const Category& element)
    {
        its::AsnObject& asnObject = const_cast<Category&>(element);
        asnObject.SetDescription(GetCategoryStaticDescription());
        AddElement(2, element);
    }

    bool OptionCategory() const
    {
        return Contains(2);
    }

    const Category& GetCategory() const
    {
        ITS_REQUIRE(OptionCategory());
        return static_cast<const Category&> (ElementAt(2));
    }

    void SetSubscriberStatus(SubscriberStatus* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSubscriberStatusStaticDescription());
        AddElement(3, element);
    }

    void SetSubscriberStatus(const SubscriberStatus& element)
    {
        its::AsnObject& asnObject = const_cast<SubscriberStatus&>(element);
        asnObject.SetDescription(GetSubscriberStatusStaticDescription());
        AddElement(3, element);
    }

    bool OptionSubscriberStatus() const
    {
        return Contains(3);
    }

    const SubscriberStatus& GetSubscriberStatus() const
    {
        ITS_REQUIRE(OptionSubscriberStatus());
        return static_cast<const SubscriberStatus&> (ElementAt(3));
    }

    void SetBearerServiceList(BearerServiceList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBearerServiceListStaticDescription());
        AddElement(4, element);
    }

    void SetBearerServiceList(const BearerServiceList& element)
    {
        its::AsnObject& asnObject = const_cast<BearerServiceList&>(element);
        asnObject.SetDescription(GetBearerServiceListStaticDescription());
        AddElement(4, element);
    }

    bool OptionBearerServiceList() const
    {
        return Contains(4);
    }

    const BearerServiceList& GetBearerServiceList() const
    {
        ITS_REQUIRE(OptionBearerServiceList());
        return static_cast<const BearerServiceList&> (ElementAt(4));
    }

    void SetTeleserviceList(TeleserviceList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTeleserviceListStaticDescription());
        AddElement(5, element);
    }

    void SetTeleserviceList(const TeleserviceList& element)
    {
        its::AsnObject& asnObject = const_cast<TeleserviceList&>(element);
        asnObject.SetDescription(GetTeleserviceListStaticDescription());
        AddElement(5, element);
    }

    bool OptionTeleserviceList() const
    {
        return Contains(5);
    }

    const TeleserviceList& GetTeleserviceList() const
    {
        ITS_REQUIRE(OptionTeleserviceList());
        return static_cast<const TeleserviceList&> (ElementAt(5));
    }

    void SetProvisionedSS(SS_InfoList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetProvisionedSSStaticDescription());
        AddElement(6, element);
    }

    void SetProvisionedSS(const SS_InfoList& element)
    {
        its::AsnObject& asnObject = const_cast<SS_InfoList&>(element);
        asnObject.SetDescription(GetProvisionedSSStaticDescription());
        AddElement(6, element);
    }

    bool OptionProvisionedSS() const
    {
        return Contains(6);
    }

    const SS_InfoList& GetProvisionedSS() const
    {
        ITS_REQUIRE(OptionProvisionedSS());
        return static_cast<const SS_InfoList&> (ElementAt(6));
    }

    void SetOdb_Data(ODB_Data* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOdb_DataStaticDescription());
        AddElement(7, element);
    }

    void SetOdb_Data(const ODB_Data& element)
    {
        its::AsnObject& asnObject = const_cast<ODB_Data&>(element);
        asnObject.SetDescription(GetOdb_DataStaticDescription());
        AddElement(7, element);
    }

    bool OptionOdb_Data() const
    {
        return Contains(7);
    }

    const ODB_Data& GetOdb_Data() const
    {
        ITS_REQUIRE(OptionOdb_Data());
        return static_cast<const ODB_Data&> (ElementAt(7));
    }

    void SetRoamingRestrictionDueToUnsupportedFeature(RoamingRestrictionDueToUnsupportedFeature* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRoamingRestrictionDueToUnsupportedFeatureStaticDescription());
        AddElement(8, element);
    }

    void SetRoamingRestrictionDueToUnsupportedFeature(const RoamingRestrictionDueToUnsupportedFeature& element)
    {
        its::AsnObject& asnObject = const_cast<RoamingRestrictionDueToUnsupportedFeature&>(element);
        asnObject.SetDescription(GetRoamingRestrictionDueToUnsupportedFeatureStaticDescription());
        AddElement(8, element);
    }

    bool OptionRoamingRestrictionDueToUnsupportedFeature() const
    {
        return Contains(8);
    }

    const RoamingRestrictionDueToUnsupportedFeature& GetRoamingRestrictionDueToUnsupportedFeature() const
    {
        ITS_REQUIRE(OptionRoamingRestrictionDueToUnsupportedFeature());
        return static_cast<const RoamingRestrictionDueToUnsupportedFeature&> (ElementAt(8));
    }

    void SetRegionalSubscriptionData(ZoneCodeList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRegionalSubscriptionDataStaticDescription());
        AddElement(9, element);
    }

    void SetRegionalSubscriptionData(const ZoneCodeList& element)
    {
        its::AsnObject& asnObject = const_cast<ZoneCodeList&>(element);
        asnObject.SetDescription(GetRegionalSubscriptionDataStaticDescription());
        AddElement(9, element);
    }

    bool OptionRegionalSubscriptionData() const
    {
        return Contains(9);
    }

    const ZoneCodeList& GetRegionalSubscriptionData() const
    {
        ITS_REQUIRE(OptionRegionalSubscriptionData());
        return static_cast<const ZoneCodeList&> (ElementAt(9));
    }

};



} // namespace.

#endif    // !defined(_MAP_V2_INSERT_SUBSCRIBER_DATA_ARG_H_)

