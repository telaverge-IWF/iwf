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


#if !defined(_MAP_V3_INSERT_SUBSCRIBER_DATA_ARG_H_)
#define _MAP_V3_INSERT_SUBSCRIBER_DATA_ARG_H_

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

#include <map_v3_imsi.h>
#include <map_v3_isdn_address_string.h>
#include <map_v3_category.h>
#include <map_v3_subscriber_status.h>
#include <map_v3_bearer_service_list.h>
#include <map_v3_teleservice_list.h>
#include <map_v3_ext_ss_info_list.h>
#include <map_v3_odb_data.h>
#include <map_v3_zone_code_list.h>
#include <map_v3_vbs_data_list.h>
#include <map_v3_vgcs_data_list.h>
#include <map_v3_vlr_camel_subscription_info.h>
#include <map_v3_extension_container.h>



namespace map_v3 {



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


        typedef map_v3::IMSI IMSI;


        typedef map_v3::ISDN_AddressString ISDN_AddressString;


        typedef map_v3::Category Category;


        typedef map_v3::SubscriberStatus SubscriberStatus;


        typedef map_v3::BearerServiceList BearerServiceList;


        typedef map_v3::TeleserviceList TeleserviceList;


        typedef map_v3::Ext_SS_InfoList Ext_SS_InfoList;


        typedef map_v3::ODB_Data ODB_Data;


        typedef map_v3::ZoneCodeList ZoneCodeList;


        typedef map_v3::VBSDataList VBSDataList;


        typedef map_v3::VGCSDataList VGCSDataList;


        typedef map_v3::VlrCamelSubscriptionInfo VlrCamelSubscriptionInfo;


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    InsertSubscriberDataArg() : its::AsnSequence(14, false)
    {
        Initialize();
    }

    InsertSubscriberDataArg(its::Octets& octets) : its::AsnSequence(14, false)
    {
        Initialize();
        Decode(octets);
    }

    InsertSubscriberDataArg(const InsertSubscriberDataArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    InsertSubscriberDataArg(its::AsnDescObject* description) : its::AsnSequence(14, description)
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
    static its::AsnDescObject* GetVbsSubscriptionDataStaticDescription();
    static its::AsnDescObject* GetVgcsSubscriptionDataStaticDescription();
    static its::AsnDescObject* GetVlrCamelSubscriptionInfoStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

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

    void SetProvisionedSS(Ext_SS_InfoList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetProvisionedSSStaticDescription());
        AddElement(6, element);
    }

    void SetProvisionedSS(const Ext_SS_InfoList& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_SS_InfoList&>(element);
        asnObject.SetDescription(GetProvisionedSSStaticDescription());
        AddElement(6, element);
    }

    bool OptionProvisionedSS() const
    {
        return Contains(6);
    }

    const Ext_SS_InfoList& GetProvisionedSS() const
    {
        ITS_REQUIRE(OptionProvisionedSS());
        return static_cast<const Ext_SS_InfoList&> (ElementAt(6));
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

    void SetVbsSubscriptionData(VBSDataList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetVbsSubscriptionDataStaticDescription());
        AddElement(10, element);
    }

    void SetVbsSubscriptionData(const VBSDataList& element)
    {
        its::AsnObject& asnObject = const_cast<VBSDataList&>(element);
        asnObject.SetDescription(GetVbsSubscriptionDataStaticDescription());
        AddElement(10, element);
    }

    bool OptionVbsSubscriptionData() const
    {
        return Contains(10);
    }

    const VBSDataList& GetVbsSubscriptionData() const
    {
        ITS_REQUIRE(OptionVbsSubscriptionData());
        return static_cast<const VBSDataList&> (ElementAt(10));
    }

    void SetVgcsSubscriptionData(VGCSDataList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetVgcsSubscriptionDataStaticDescription());
        AddElement(11, element);
    }

    void SetVgcsSubscriptionData(const VGCSDataList& element)
    {
        its::AsnObject& asnObject = const_cast<VGCSDataList&>(element);
        asnObject.SetDescription(GetVgcsSubscriptionDataStaticDescription());
        AddElement(11, element);
    }

    bool OptionVgcsSubscriptionData() const
    {
        return Contains(11);
    }

    const VGCSDataList& GetVgcsSubscriptionData() const
    {
        ITS_REQUIRE(OptionVgcsSubscriptionData());
        return static_cast<const VGCSDataList&> (ElementAt(11));
    }

    void SetVlrCamelSubscriptionInfo(VlrCamelSubscriptionInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetVlrCamelSubscriptionInfoStaticDescription());
        AddElement(12, element);
    }

    void SetVlrCamelSubscriptionInfo(const VlrCamelSubscriptionInfo& element)
    {
        its::AsnObject& asnObject = const_cast<VlrCamelSubscriptionInfo&>(element);
        asnObject.SetDescription(GetVlrCamelSubscriptionInfoStaticDescription());
        AddElement(12, element);
    }

    bool OptionVlrCamelSubscriptionInfo() const
    {
        return Contains(12);
    }

    const VlrCamelSubscriptionInfo& GetVlrCamelSubscriptionInfo() const
    {
        ITS_REQUIRE(OptionVlrCamelSubscriptionInfo());
        return static_cast<const VlrCamelSubscriptionInfo&> (ElementAt(12));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(13, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(13, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(13);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(13));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_INSERT_SUBSCRIBER_DATA_ARG_H_)

