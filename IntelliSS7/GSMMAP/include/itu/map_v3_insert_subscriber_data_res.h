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


#if !defined(_MAP_V3_INSERT_SUBSCRIBER_DATA_RES_H_)
#define _MAP_V3_INSERT_SUBSCRIBER_DATA_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>
#include <AsnBitString.h>
#include <AsnEnumerated.h>

#include <map_v3_teleservice_list.h>
#include <map_v3_bearer_service_list.h>
#include <map_v3_ss_list.h>
#include <map_v3_odb_general_data.h>
#include <map_v3_regional_subscription_response.h>
#include <map_v3_supported_camel_phases.h>
#include <map_v3_extension_container.h>



namespace map_v3 {



class InsertSubscriberDataRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::TeleserviceList TeleserviceList;


        typedef map_v3::BearerServiceList BearerServiceList;


        typedef map_v3::SS_List SS_List;


        typedef map_v3::ODB_GeneralData ODB_GeneralData;


        typedef map_v3::RegionalSubscriptionResponse RegionalSubscriptionResponse;


        typedef map_v3::SupportedCamelPhases SupportedCamelPhases;


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    InsertSubscriberDataRes() : its::AsnSequence(7, false)
    {
        Initialize();
    }

    InsertSubscriberDataRes(its::Octets& octets) : its::AsnSequence(7, false)
    {
        Initialize();
        Decode(octets);
    }

    InsertSubscriberDataRes(const InsertSubscriberDataRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    InsertSubscriberDataRes(its::AsnDescObject* description) : its::AsnSequence(7, description)
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

    static its::AsnDescObject* GetTeleserviceListStaticDescription();
    static its::AsnDescObject* GetBearerServiceListStaticDescription();
    static its::AsnDescObject* GetSs_ListStaticDescription();
    static its::AsnDescObject* GetOdb_GeneralDataStaticDescription();
    static its::AsnDescObject* GetRegionalSubscriptionResponseStaticDescription();
    static its::AsnDescObject* GetSupportedCamelPhasesStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~InsertSubscriberDataRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new InsertSubscriberDataRes(*this);
    }

    virtual std::string GetName() const
    { return "InsertSubscriberDataRes"; }

    void SetTeleserviceList(TeleserviceList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTeleserviceListStaticDescription());
        AddElement(0, element);
    }

    void SetTeleserviceList(const TeleserviceList& element)
    {
        its::AsnObject& asnObject = const_cast<TeleserviceList&>(element);
        asnObject.SetDescription(GetTeleserviceListStaticDescription());
        AddElement(0, element);
    }

    bool OptionTeleserviceList() const
    {
        return Contains(0);
    }

    const TeleserviceList& GetTeleserviceList() const
    {
        ITS_REQUIRE(OptionTeleserviceList());
        return static_cast<const TeleserviceList&> (ElementAt(0));
    }

    void SetBearerServiceList(BearerServiceList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBearerServiceListStaticDescription());
        AddElement(1, element);
    }

    void SetBearerServiceList(const BearerServiceList& element)
    {
        its::AsnObject& asnObject = const_cast<BearerServiceList&>(element);
        asnObject.SetDescription(GetBearerServiceListStaticDescription());
        AddElement(1, element);
    }

    bool OptionBearerServiceList() const
    {
        return Contains(1);
    }

    const BearerServiceList& GetBearerServiceList() const
    {
        ITS_REQUIRE(OptionBearerServiceList());
        return static_cast<const BearerServiceList&> (ElementAt(1));
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

    void SetOdb_GeneralData(ODB_GeneralData* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOdb_GeneralDataStaticDescription());
        AddElement(3, element);
    }

    void SetOdb_GeneralData(const ODB_GeneralData& element)
    {
        its::AsnObject& asnObject = const_cast<ODB_GeneralData&>(element);
        asnObject.SetDescription(GetOdb_GeneralDataStaticDescription());
        AddElement(3, element);
    }

    bool OptionOdb_GeneralData() const
    {
        return Contains(3);
    }

    const ODB_GeneralData& GetOdb_GeneralData() const
    {
        ITS_REQUIRE(OptionOdb_GeneralData());
        return static_cast<const ODB_GeneralData&> (ElementAt(3));
    }

    void SetRegionalSubscriptionResponse(RegionalSubscriptionResponse* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRegionalSubscriptionResponseStaticDescription());
        AddElement(4, element);
    }

    void SetRegionalSubscriptionResponse(const RegionalSubscriptionResponse& element)
    {
        its::AsnObject& asnObject = const_cast<RegionalSubscriptionResponse&>(element);
        asnObject.SetDescription(GetRegionalSubscriptionResponseStaticDescription());
        AddElement(4, element);
    }

    bool OptionRegionalSubscriptionResponse() const
    {
        return Contains(4);
    }

    const RegionalSubscriptionResponse& GetRegionalSubscriptionResponse() const
    {
        ITS_REQUIRE(OptionRegionalSubscriptionResponse());
        return static_cast<const RegionalSubscriptionResponse&> (ElementAt(4));
    }

    void SetSupportedCamelPhases(SupportedCamelPhases* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSupportedCamelPhasesStaticDescription());
        AddElement(5, element);
    }

    void SetSupportedCamelPhases(const SupportedCamelPhases& element)
    {
        its::AsnObject& asnObject = const_cast<SupportedCamelPhases&>(element);
        asnObject.SetDescription(GetSupportedCamelPhasesStaticDescription());
        AddElement(5, element);
    }

    bool OptionSupportedCamelPhases() const
    {
        return Contains(5);
    }

    const SupportedCamelPhases& GetSupportedCamelPhases() const
    {
        ITS_REQUIRE(OptionSupportedCamelPhases());
        return static_cast<const SupportedCamelPhases&> (ElementAt(5));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(6, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(6, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(6);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(6));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_INSERT_SUBSCRIBER_DATA_RES_H_)
