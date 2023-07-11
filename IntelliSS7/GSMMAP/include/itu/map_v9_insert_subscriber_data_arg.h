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


#if !defined(_MAP_V9_INSERT_SUBSCRIBER_DATA_ARG_H_)
#define _MAP_V9_INSERT_SUBSCRIBER_DATA_ARG_H_

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
#include <AsnInteger.h>
#include <AsnBitString.h>

#include <map_v9_imsi.h>
#include <map_v9_isdn_address_string.h>
#include <map_v9_category.h>
#include <map_v9_subscriber_status.h>
#include <map_v9_bearer_service_list.h>
#include <map_v9_teleservice_list.h>
#include <map_v9_ext_ss_info_list.h>
#include <map_v9_odb_data.h>
#include <map_v9_zone_code_list.h>
#include <map_v9_vbs_data_list.h>
#include <map_v9_vgcs_data_list.h>
#include <map_v9_vlr_camel_subscription_info.h>
#include <map_v9_extension_container.h>
#include <map_v9_naea_preferred_ci.h>
#include <map_v9_gprs_subscription_data.h>
#include <map_v9_network_access_mode.h>
#include <map_v9_lsa_information.h>
#include <map_v9_lcs_information.h>
#include <map_v9_ist_alert_timer_value.h>
#include <map_v9_age_indicator.h>
#include <map_v9_mc_ss_info.h>
#include <map_v9_cs_allocation_retention_priority.h>
#include <map_v9_sgsn_camel_subscription_info.h>
#include <map_v9_charging_characteristics.h>
#include <map_v9_access_restriction_data.h>



namespace map_v9 {



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



    class RoamingRestrictedInSgsnDueToUnsupportedFeature : public its::AsnNull
    {
    public:

        RoamingRestrictedInSgsnDueToUnsupportedFeature() : its::AsnNull(false)
        {
            Initialize();
        }

        RoamingRestrictedInSgsnDueToUnsupportedFeature(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        RoamingRestrictedInSgsnDueToUnsupportedFeature(const RoamingRestrictedInSgsnDueToUnsupportedFeature& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        RoamingRestrictedInSgsnDueToUnsupportedFeature(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~RoamingRestrictedInSgsnDueToUnsupportedFeature()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new RoamingRestrictedInSgsnDueToUnsupportedFeature(*this);
        }

        virtual std::string GetName() const
        { return "RoamingRestrictedInSgsnDueToUnsupportedFeature"; }

    };



    class Lmu_Indicator : public its::AsnNull
    {
    public:

        Lmu_Indicator() : its::AsnNull(false)
        {
            Initialize();
        }

        Lmu_Indicator(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Lmu_Indicator(const Lmu_Indicator& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Lmu_Indicator(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Lmu_Indicator()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Lmu_Indicator(*this);
        }

        virtual std::string GetName() const
        { return "Lmu_Indicator"; }

    };


        typedef map_v9::IMSI IMSI;


        typedef map_v9::ISDN_AddressString ISDN_AddressString;


        typedef map_v9::Category Category;


        typedef map_v9::SubscriberStatus SubscriberStatus;


        typedef map_v9::BearerServiceList BearerServiceList;


        typedef map_v9::TeleserviceList TeleserviceList;


        typedef map_v9::Ext_SS_InfoList Ext_SS_InfoList;


        typedef map_v9::ODB_Data ODB_Data;


        typedef map_v9::ZoneCodeList ZoneCodeList;


        typedef map_v9::VBSDataList VBSDataList;


        typedef map_v9::VGCSDataList VGCSDataList;


        typedef map_v9::VlrCamelSubscriptionInfo VlrCamelSubscriptionInfo;


        typedef map_v9::ExtensionContainer ExtensionContainer;


        typedef map_v9::NAEA_PreferredCI NAEA_PreferredCI;


        typedef map_v9::GPRSSubscriptionData GPRSSubscriptionData;


        typedef map_v9::NetworkAccessMode NetworkAccessMode;


        typedef map_v9::LSAInformation LSAInformation;


        typedef map_v9::LCSInformation LCSInformation;


        typedef map_v9::IST_AlertTimerValue IST_AlertTimerValue;


        typedef map_v9::AgeIndicator AgeIndicator;


        typedef map_v9::MC_SS_Info MC_SS_Info;


        typedef map_v9::CS_AllocationRetentionPriority CS_AllocationRetentionPriority;


        typedef map_v9::SGSN_CAMEL_SubscriptionInfo SGSN_CAMEL_SubscriptionInfo;


        typedef map_v9::ChargingCharacteristics ChargingCharacteristics;


        typedef map_v9::AccessRestrictionData AccessRestrictionData;


////////// End Nested Class(es) //////////

    InsertSubscriberDataArg() : its::AsnSequence(28, false)
    {
        Initialize();
    }

    InsertSubscriberDataArg(its::Octets& octets) : its::AsnSequence(28, false)
    {
        Initialize();
        Decode(octets);
    }

    InsertSubscriberDataArg(const InsertSubscriberDataArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    InsertSubscriberDataArg(its::AsnDescObject* description) : its::AsnSequence(28, description)
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
    static its::AsnDescObject* GetNaea_PreferredCIStaticDescription();
    static its::AsnDescObject* GetGprsSubscriptionDataStaticDescription();
    static its::AsnDescObject* GetRoamingRestrictedInSgsnDueToUnsupportedFeatureStaticDescription();
    static its::AsnDescObject* GetNetworkAccessModeStaticDescription();
    static its::AsnDescObject* GetLsaInformationStaticDescription();
    static its::AsnDescObject* GetLmu_IndicatorStaticDescription();
    static its::AsnDescObject* GetLcsInformationStaticDescription();
    static its::AsnDescObject* GetIstAlertTimerStaticDescription();
    static its::AsnDescObject* GetSuperChargerSupportedInHLRStaticDescription();
    static its::AsnDescObject* GetMc_SS_InfoStaticDescription();
    static its::AsnDescObject* GetCs_AllocationRetentionPriorityStaticDescription();
    static its::AsnDescObject* GetSgsn_CAMEL_SubscriptionInfoStaticDescription();
    static its::AsnDescObject* GetChargingCharacteristicsStaticDescription();
    static its::AsnDescObject* GetAccessRestrictionDataStaticDescription();

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

    void SetNaea_PreferredCI(NAEA_PreferredCI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNaea_PreferredCIStaticDescription());
        AddElement(14, element);
    }

    void SetNaea_PreferredCI(const NAEA_PreferredCI& element)
    {
        its::AsnObject& asnObject = const_cast<NAEA_PreferredCI&>(element);
        asnObject.SetDescription(GetNaea_PreferredCIStaticDescription());
        AddElement(14, element);
    }

    bool OptionNaea_PreferredCI() const
    {
        return Contains(14);
    }

    const NAEA_PreferredCI& GetNaea_PreferredCI() const
    {
        ITS_REQUIRE(OptionNaea_PreferredCI());
        return static_cast<const NAEA_PreferredCI&> (ElementAt(14));
    }

    void SetGprsSubscriptionData(GPRSSubscriptionData* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGprsSubscriptionDataStaticDescription());
        AddElement(15, element);
    }

    void SetGprsSubscriptionData(const GPRSSubscriptionData& element)
    {
        its::AsnObject& asnObject = const_cast<GPRSSubscriptionData&>(element);
        asnObject.SetDescription(GetGprsSubscriptionDataStaticDescription());
        AddElement(15, element);
    }

    bool OptionGprsSubscriptionData() const
    {
        return Contains(15);
    }

    const GPRSSubscriptionData& GetGprsSubscriptionData() const
    {
        ITS_REQUIRE(OptionGprsSubscriptionData());
        return static_cast<const GPRSSubscriptionData&> (ElementAt(15));
    }

    void SetRoamingRestrictedInSgsnDueToUnsupportedFeature(RoamingRestrictedInSgsnDueToUnsupportedFeature* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRoamingRestrictedInSgsnDueToUnsupportedFeatureStaticDescription());
        AddElement(16, element);
    }

    void SetRoamingRestrictedInSgsnDueToUnsupportedFeature(const RoamingRestrictedInSgsnDueToUnsupportedFeature& element)
    {
        its::AsnObject& asnObject = const_cast<RoamingRestrictedInSgsnDueToUnsupportedFeature&>(element);
        asnObject.SetDescription(GetRoamingRestrictedInSgsnDueToUnsupportedFeatureStaticDescription());
        AddElement(16, element);
    }

    bool OptionRoamingRestrictedInSgsnDueToUnsupportedFeature() const
    {
        return Contains(16);
    }

    const RoamingRestrictedInSgsnDueToUnsupportedFeature& GetRoamingRestrictedInSgsnDueToUnsupportedFeature() const
    {
        ITS_REQUIRE(OptionRoamingRestrictedInSgsnDueToUnsupportedFeature());
        return static_cast<const RoamingRestrictedInSgsnDueToUnsupportedFeature&> (ElementAt(16));
    }

    void SetNetworkAccessMode(NetworkAccessMode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNetworkAccessModeStaticDescription());
        AddElement(17, element);
    }

    void SetNetworkAccessMode(const NetworkAccessMode& element)
    {
        its::AsnObject& asnObject = const_cast<NetworkAccessMode&>(element);
        asnObject.SetDescription(GetNetworkAccessModeStaticDescription());
        AddElement(17, element);
    }

    bool OptionNetworkAccessMode() const
    {
        return Contains(17);
    }

    const NetworkAccessMode& GetNetworkAccessMode() const
    {
        ITS_REQUIRE(OptionNetworkAccessMode());
        return static_cast<const NetworkAccessMode&> (ElementAt(17));
    }

    void SetLsaInformation(LSAInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLsaInformationStaticDescription());
        AddElement(18, element);
    }

    void SetLsaInformation(const LSAInformation& element)
    {
        its::AsnObject& asnObject = const_cast<LSAInformation&>(element);
        asnObject.SetDescription(GetLsaInformationStaticDescription());
        AddElement(18, element);
    }

    bool OptionLsaInformation() const
    {
        return Contains(18);
    }

    const LSAInformation& GetLsaInformation() const
    {
        ITS_REQUIRE(OptionLsaInformation());
        return static_cast<const LSAInformation&> (ElementAt(18));
    }

    void SetLmu_Indicator(Lmu_Indicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLmu_IndicatorStaticDescription());
        AddElement(19, element);
    }

    void SetLmu_Indicator(const Lmu_Indicator& element)
    {
        its::AsnObject& asnObject = const_cast<Lmu_Indicator&>(element);
        asnObject.SetDescription(GetLmu_IndicatorStaticDescription());
        AddElement(19, element);
    }

    bool OptionLmu_Indicator() const
    {
        return Contains(19);
    }

    const Lmu_Indicator& GetLmu_Indicator() const
    {
        ITS_REQUIRE(OptionLmu_Indicator());
        return static_cast<const Lmu_Indicator&> (ElementAt(19));
    }

    void SetLcsInformation(LCSInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLcsInformationStaticDescription());
        AddElement(20, element);
    }

    void SetLcsInformation(const LCSInformation& element)
    {
        its::AsnObject& asnObject = const_cast<LCSInformation&>(element);
        asnObject.SetDescription(GetLcsInformationStaticDescription());
        AddElement(20, element);
    }

    bool OptionLcsInformation() const
    {
        return Contains(20);
    }

    const LCSInformation& GetLcsInformation() const
    {
        ITS_REQUIRE(OptionLcsInformation());
        return static_cast<const LCSInformation&> (ElementAt(20));
    }

    void SetIstAlertTimer(IST_AlertTimerValue* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIstAlertTimerStaticDescription());
        AddElement(21, element);
    }

    void SetIstAlertTimer(const IST_AlertTimerValue& element)
    {
        its::AsnObject& asnObject = const_cast<IST_AlertTimerValue&>(element);
        asnObject.SetDescription(GetIstAlertTimerStaticDescription());
        AddElement(21, element);
    }

    bool OptionIstAlertTimer() const
    {
        return Contains(21);
    }

    const IST_AlertTimerValue& GetIstAlertTimer() const
    {
        ITS_REQUIRE(OptionIstAlertTimer());
        return static_cast<const IST_AlertTimerValue&> (ElementAt(21));
    }

    void SetSuperChargerSupportedInHLR(AgeIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSuperChargerSupportedInHLRStaticDescription());
        AddElement(22, element);
    }

    void SetSuperChargerSupportedInHLR(const AgeIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<AgeIndicator&>(element);
        asnObject.SetDescription(GetSuperChargerSupportedInHLRStaticDescription());
        AddElement(22, element);
    }

    bool OptionSuperChargerSupportedInHLR() const
    {
        return Contains(22);
    }

    const AgeIndicator& GetSuperChargerSupportedInHLR() const
    {
        ITS_REQUIRE(OptionSuperChargerSupportedInHLR());
        return static_cast<const AgeIndicator&> (ElementAt(22));
    }

    void SetMc_SS_Info(MC_SS_Info* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMc_SS_InfoStaticDescription());
        AddElement(23, element);
    }

    void SetMc_SS_Info(const MC_SS_Info& element)
    {
        its::AsnObject& asnObject = const_cast<MC_SS_Info&>(element);
        asnObject.SetDescription(GetMc_SS_InfoStaticDescription());
        AddElement(23, element);
    }

    bool OptionMc_SS_Info() const
    {
        return Contains(23);
    }

    const MC_SS_Info& GetMc_SS_Info() const
    {
        ITS_REQUIRE(OptionMc_SS_Info());
        return static_cast<const MC_SS_Info&> (ElementAt(23));
    }

    void SetCs_AllocationRetentionPriority(CS_AllocationRetentionPriority* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCs_AllocationRetentionPriorityStaticDescription());
        AddElement(24, element);
    }

    void SetCs_AllocationRetentionPriority(const CS_AllocationRetentionPriority& element)
    {
        its::AsnObject& asnObject = const_cast<CS_AllocationRetentionPriority&>(element);
        asnObject.SetDescription(GetCs_AllocationRetentionPriorityStaticDescription());
        AddElement(24, element);
    }

    bool OptionCs_AllocationRetentionPriority() const
    {
        return Contains(24);
    }

    const CS_AllocationRetentionPriority& GetCs_AllocationRetentionPriority() const
    {
        ITS_REQUIRE(OptionCs_AllocationRetentionPriority());
        return static_cast<const CS_AllocationRetentionPriority&> (ElementAt(24));
    }

    void SetSgsn_CAMEL_SubscriptionInfo(SGSN_CAMEL_SubscriptionInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSgsn_CAMEL_SubscriptionInfoStaticDescription());
        AddElement(25, element);
    }

    void SetSgsn_CAMEL_SubscriptionInfo(const SGSN_CAMEL_SubscriptionInfo& element)
    {
        its::AsnObject& asnObject = const_cast<SGSN_CAMEL_SubscriptionInfo&>(element);
        asnObject.SetDescription(GetSgsn_CAMEL_SubscriptionInfoStaticDescription());
        AddElement(25, element);
    }

    bool OptionSgsn_CAMEL_SubscriptionInfo() const
    {
        return Contains(25);
    }

    const SGSN_CAMEL_SubscriptionInfo& GetSgsn_CAMEL_SubscriptionInfo() const
    {
        ITS_REQUIRE(OptionSgsn_CAMEL_SubscriptionInfo());
        return static_cast<const SGSN_CAMEL_SubscriptionInfo&> (ElementAt(25));
    }

    void SetChargingCharacteristics(ChargingCharacteristics* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetChargingCharacteristicsStaticDescription());
        AddElement(26, element);
    }

    void SetChargingCharacteristics(const ChargingCharacteristics& element)
    {
        its::AsnObject& asnObject = const_cast<ChargingCharacteristics&>(element);
        asnObject.SetDescription(GetChargingCharacteristicsStaticDescription());
        AddElement(26, element);
    }

    bool OptionChargingCharacteristics() const
    {
        return Contains(26);
    }

    const ChargingCharacteristics& GetChargingCharacteristics() const
    {
        ITS_REQUIRE(OptionChargingCharacteristics());
        return static_cast<const ChargingCharacteristics&> (ElementAt(26));
    }

    void SetAccessRestrictionData(AccessRestrictionData* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAccessRestrictionDataStaticDescription());
        AddElement(27, element);
    }

    void SetAccessRestrictionData(const AccessRestrictionData& element)
    {
        its::AsnObject& asnObject = const_cast<AccessRestrictionData&>(element);
        asnObject.SetDescription(GetAccessRestrictionDataStaticDescription());
        AddElement(27, element);
    }

    bool OptionAccessRestrictionData() const
    {
        return Contains(27);
    }

    const AccessRestrictionData& GetAccessRestrictionData() const
    {
        ITS_REQUIRE(OptionAccessRestrictionData());
        return static_cast<const AccessRestrictionData&> (ElementAt(27));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_INSERT_SUBSCRIBER_DATA_ARG_H_)

