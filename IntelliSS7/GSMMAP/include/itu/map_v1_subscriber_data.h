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


#if !defined(_MAP_V1_SUBSCRIBER_DATA_H_)
#define _MAP_V1_SUBSCRIBER_DATA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnEnumerated.h>
#include <AsnSequenceOf.h>

#include <map_v1_isdn_address_string.h>
#include <map_v1_category.h>
#include <map_v1_subscriber_status.h>
#include <map_v1_bearer_service_list.h>
#include <map_v1_teleservice_list.h>
#include <map_v1_ss_info_list.h>



namespace map_v1 {



class SubscriberData : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v1::ISDN_AddressString ISDN_AddressString;


        typedef map_v1::Category Category;


        typedef map_v1::SubscriberStatus SubscriberStatus;


        typedef map_v1::BearerServiceList BearerServiceList;


        typedef map_v1::TeleserviceList TeleserviceList;


        typedef map_v1::SS_InfoList SS_InfoList;


////////// End Nested Class(es) //////////

    SubscriberData() : its::AsnSequence(6, false)
    {
        Initialize();
    }

    SubscriberData(its::Octets& octets) : its::AsnSequence(6, false)
    {
        Initialize();
        Decode(octets);
    }

    SubscriberData(const SubscriberData& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SubscriberData(its::AsnDescObject* description) : its::AsnSequence(6, description)
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

    static its::AsnDescObject* GetMsIsdnStaticDescription();
    static its::AsnDescObject* GetCategoryStaticDescription();
    static its::AsnDescObject* GetSubscriberStatusStaticDescription();
    static its::AsnDescObject* GetBearerServiceListStaticDescription();
    static its::AsnDescObject* GetTeleserviceListStaticDescription();
    static its::AsnDescObject* GetProvisionedSupplServicesStaticDescription();

public:

    virtual ~SubscriberData()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SubscriberData(*this);
    }

    virtual std::string GetName() const
    { return "SubscriberData"; }

    void SetMsIsdn(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMsIsdnStaticDescription());
        AddElement(0, element);
    }

    void SetMsIsdn(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetMsIsdnStaticDescription());
        AddElement(0, element);
    }

    bool OptionMsIsdn() const
    {
        return Contains(0);
    }

    const ISDN_AddressString& GetMsIsdn() const
    {
        ITS_REQUIRE(OptionMsIsdn());
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
    }

    void SetCategory(Category* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCategoryStaticDescription());
        AddElement(1, element);
    }

    void SetCategory(const Category& element)
    {
        its::AsnObject& asnObject = const_cast<Category&>(element);
        asnObject.SetDescription(GetCategoryStaticDescription());
        AddElement(1, element);
    }

    bool OptionCategory() const
    {
        return Contains(1);
    }

    const Category& GetCategory() const
    {
        ITS_REQUIRE(OptionCategory());
        return static_cast<const Category&> (ElementAt(1));
    }

    void SetSubscriberStatus(SubscriberStatus* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSubscriberStatusStaticDescription());
        AddElement(2, element);
    }

    void SetSubscriberStatus(const SubscriberStatus& element)
    {
        its::AsnObject& asnObject = const_cast<SubscriberStatus&>(element);
        asnObject.SetDescription(GetSubscriberStatusStaticDescription());
        AddElement(2, element);
    }

    bool OptionSubscriberStatus() const
    {
        return Contains(2);
    }

    const SubscriberStatus& GetSubscriberStatus() const
    {
        ITS_REQUIRE(OptionSubscriberStatus());
        return static_cast<const SubscriberStatus&> (ElementAt(2));
    }

    void SetBearerServiceList(BearerServiceList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBearerServiceListStaticDescription());
        AddElement(3, element);
    }

    void SetBearerServiceList(const BearerServiceList& element)
    {
        its::AsnObject& asnObject = const_cast<BearerServiceList&>(element);
        asnObject.SetDescription(GetBearerServiceListStaticDescription());
        AddElement(3, element);
    }

    bool OptionBearerServiceList() const
    {
        return Contains(3);
    }

    const BearerServiceList& GetBearerServiceList() const
    {
        ITS_REQUIRE(OptionBearerServiceList());
        return static_cast<const BearerServiceList&> (ElementAt(3));
    }

    void SetTeleserviceList(TeleserviceList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTeleserviceListStaticDescription());
        AddElement(4, element);
    }

    void SetTeleserviceList(const TeleserviceList& element)
    {
        its::AsnObject& asnObject = const_cast<TeleserviceList&>(element);
        asnObject.SetDescription(GetTeleserviceListStaticDescription());
        AddElement(4, element);
    }

    bool OptionTeleserviceList() const
    {
        return Contains(4);
    }

    const TeleserviceList& GetTeleserviceList() const
    {
        ITS_REQUIRE(OptionTeleserviceList());
        return static_cast<const TeleserviceList&> (ElementAt(4));
    }

    void SetProvisionedSupplServices(SS_InfoList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetProvisionedSupplServicesStaticDescription());
        AddElement(5, element);
    }

    void SetProvisionedSupplServices(const SS_InfoList& element)
    {
        its::AsnObject& asnObject = const_cast<SS_InfoList&>(element);
        asnObject.SetDescription(GetProvisionedSupplServicesStaticDescription());
        AddElement(5, element);
    }

    bool OptionProvisionedSupplServices() const
    {
        return Contains(5);
    }

    const SS_InfoList& GetProvisionedSupplServices() const
    {
        ITS_REQUIRE(OptionProvisionedSupplServices());
        return static_cast<const SS_InfoList&> (ElementAt(5));
    }

};



} // namespace.

#endif    // !defined(_MAP_V1_SUBSCRIBER_DATA_H_)
