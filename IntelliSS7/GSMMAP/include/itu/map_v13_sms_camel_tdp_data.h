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


#if !defined(_MAP_V13_SMS_CAMEL_TDP_DATA_H_)
#define _MAP_V13_SMS_CAMEL_TDP_DATA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>
#include <AsnInteger.h>
#include <AsnOctetString.h>

#include <map_v13_sms_trigger_detection_point.h>
#include <map_v13_service_key.h>
#include <map_v13_isdn_address_string.h>
#include <map_v13_default_sms_handling.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class SMS_CAMEL_TDP_Data : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::SMS_TriggerDetectionPoint SMS_TriggerDetectionPoint;


        typedef map_v13::ServiceKey ServiceKey;


        typedef map_v13::ISDN_AddressString ISDN_AddressString;


        typedef map_v13::DefaultSMS_Handling DefaultSMS_Handling;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    SMS_CAMEL_TDP_Data() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    SMS_CAMEL_TDP_Data(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    SMS_CAMEL_TDP_Data(const SMS_CAMEL_TDP_Data& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SMS_CAMEL_TDP_Data(its::AsnDescObject* description) : its::AsnSequence(5, description)
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

    static its::AsnDescObject* GetSms_TriggerDetectionPointStaticDescription();
    static its::AsnDescObject* GetServiceKeyStaticDescription();
    static its::AsnDescObject* GetGsmSCF_AddressStaticDescription();
    static its::AsnDescObject* GetDefaultSMS_HandlingStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~SMS_CAMEL_TDP_Data()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SMS_CAMEL_TDP_Data(*this);
    }

    virtual std::string GetName() const
    { return "SMS_CAMEL_TDP_Data"; }

    void SetSms_TriggerDetectionPoint(SMS_TriggerDetectionPoint* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSms_TriggerDetectionPointStaticDescription());
        AddElement(0, element);
    }

    void SetSms_TriggerDetectionPoint(const SMS_TriggerDetectionPoint& element)
    {
        its::AsnObject& asnObject = const_cast<SMS_TriggerDetectionPoint&>(element);
        asnObject.SetDescription(GetSms_TriggerDetectionPointStaticDescription());
        AddElement(0, element);
    }

    const SMS_TriggerDetectionPoint& GetSms_TriggerDetectionPoint() const
    {
        return static_cast<const SMS_TriggerDetectionPoint&> (ElementAt(0));
    }

    void SetServiceKey(ServiceKey* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetServiceKeyStaticDescription());
        AddElement(1, element);
    }

    void SetServiceKey(const ServiceKey& element)
    {
        its::AsnObject& asnObject = const_cast<ServiceKey&>(element);
        asnObject.SetDescription(GetServiceKeyStaticDescription());
        AddElement(1, element);
    }

    const ServiceKey& GetServiceKey() const
    {
        return static_cast<const ServiceKey&> (ElementAt(1));
    }

    void SetGsmSCF_Address(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGsmSCF_AddressStaticDescription());
        AddElement(2, element);
    }

    void SetGsmSCF_Address(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetGsmSCF_AddressStaticDescription());
        AddElement(2, element);
    }

    const ISDN_AddressString& GetGsmSCF_Address() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(2));
    }

    void SetDefaultSMS_Handling(DefaultSMS_Handling* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDefaultSMS_HandlingStaticDescription());
        AddElement(3, element);
    }

    void SetDefaultSMS_Handling(const DefaultSMS_Handling& element)
    {
        its::AsnObject& asnObject = const_cast<DefaultSMS_Handling&>(element);
        asnObject.SetDescription(GetDefaultSMS_HandlingStaticDescription());
        AddElement(3, element);
    }

    const DefaultSMS_Handling& GetDefaultSMS_Handling() const
    {
        return static_cast<const DefaultSMS_Handling&> (ElementAt(3));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(4, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(4, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(4);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(4));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_SMS_CAMEL_TDP_DATA_H_)

