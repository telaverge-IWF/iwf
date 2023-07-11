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


#if !defined(_MAP_V13_SERVICE_TYPE_H_)
#define _MAP_V13_SERVICE_TYPE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnInteger.h>
#include <AsnEnumerated.h>

#include <map_v13_lcs_service_type_id.h>
#include <map_v13_gmlc_restriction.h>
#include <map_v13_notification_to_ms_user.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class ServiceType : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::LCSServiceTypeID LCSServiceTypeID;


        typedef map_v13::GMLC_Restriction GMLC_Restriction;


        typedef map_v13::NotificationToMSUser NotificationToMSUser;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    ServiceType() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    ServiceType(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    ServiceType(const ServiceType& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ServiceType(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetServiceTypeIdentityStaticDescription();
    static its::AsnDescObject* GetGmlc_RestrictionStaticDescription();
    static its::AsnDescObject* GetNotificationToMSUserStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~ServiceType()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ServiceType(*this);
    }

    virtual std::string GetName() const
    { return "ServiceType"; }

    void SetServiceTypeIdentity(LCSServiceTypeID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetServiceTypeIdentityStaticDescription());
        AddElement(0, element);
    }

    void SetServiceTypeIdentity(const LCSServiceTypeID& element)
    {
        its::AsnObject& asnObject = const_cast<LCSServiceTypeID&>(element);
        asnObject.SetDescription(GetServiceTypeIdentityStaticDescription());
        AddElement(0, element);
    }

    const LCSServiceTypeID& GetServiceTypeIdentity() const
    {
        return static_cast<const LCSServiceTypeID&> (ElementAt(0));
    }

    void SetGmlc_Restriction(GMLC_Restriction* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGmlc_RestrictionStaticDescription());
        AddElement(1, element);
    }

    void SetGmlc_Restriction(const GMLC_Restriction& element)
    {
        its::AsnObject& asnObject = const_cast<GMLC_Restriction&>(element);
        asnObject.SetDescription(GetGmlc_RestrictionStaticDescription());
        AddElement(1, element);
    }

    bool OptionGmlc_Restriction() const
    {
        return Contains(1);
    }

    const GMLC_Restriction& GetGmlc_Restriction() const
    {
        ITS_REQUIRE(OptionGmlc_Restriction());
        return static_cast<const GMLC_Restriction&> (ElementAt(1));
    }

    void SetNotificationToMSUser(NotificationToMSUser* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNotificationToMSUserStaticDescription());
        AddElement(2, element);
    }

    void SetNotificationToMSUser(const NotificationToMSUser& element)
    {
        its::AsnObject& asnObject = const_cast<NotificationToMSUser&>(element);
        asnObject.SetDescription(GetNotificationToMSUserStaticDescription());
        AddElement(2, element);
    }

    bool OptionNotificationToMSUser() const
    {
        return Contains(2);
    }

    const NotificationToMSUser& GetNotificationToMSUser() const
    {
        ITS_REQUIRE(OptionNotificationToMSUser());
        return static_cast<const NotificationToMSUser&> (ElementAt(2));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(3, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(3, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(3);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_SERVICE_TYPE_H_)
