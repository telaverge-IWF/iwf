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


#if !defined(_MAP_V3_O_BCSM_CAMEL_TDP_DATA_H_)
#define _MAP_V3_O_BCSM_CAMEL_TDP_DATA_H_

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

#include <map_v3_o_bcsm_trigger_detection_point.h>
#include <map_v3_service_key.h>
#include <map_v3_isdn_address_string.h>
#include <map_v3_default_call_handling.h>
#include <map_v3_extension_container.h>



namespace map_v3 {



class O_BcsmCamelTDPData : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::O_BcsmTriggerDetectionPoint O_BcsmTriggerDetectionPoint;


        typedef map_v3::ServiceKey ServiceKey;


        typedef map_v3::ISDN_AddressString ISDN_AddressString;


        typedef map_v3::DefaultCallHandling DefaultCallHandling;


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    O_BcsmCamelTDPData() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    O_BcsmCamelTDPData(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    O_BcsmCamelTDPData(const O_BcsmCamelTDPData& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    O_BcsmCamelTDPData(its::AsnDescObject* description) : its::AsnSequence(5, description)
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

    static its::AsnDescObject* GetO_BcsmTriggerDetectionPointStaticDescription();
    static its::AsnDescObject* GetServiceKeyStaticDescription();
    static its::AsnDescObject* GetGsmSCF_AddressStaticDescription();
    static its::AsnDescObject* GetDefaultCallHandlingStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~O_BcsmCamelTDPData()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new O_BcsmCamelTDPData(*this);
    }

    virtual std::string GetName() const
    { return "O_BcsmCamelTDPData"; }

    void SetO_BcsmTriggerDetectionPoint(O_BcsmTriggerDetectionPoint* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetO_BcsmTriggerDetectionPointStaticDescription());
        AddElement(0, element);
    }

    void SetO_BcsmTriggerDetectionPoint(const O_BcsmTriggerDetectionPoint& element)
    {
        its::AsnObject& asnObject = const_cast<O_BcsmTriggerDetectionPoint&>(element);
        asnObject.SetDescription(GetO_BcsmTriggerDetectionPointStaticDescription());
        AddElement(0, element);
    }

    const O_BcsmTriggerDetectionPoint& GetO_BcsmTriggerDetectionPoint() const
    {
        return static_cast<const O_BcsmTriggerDetectionPoint&> (ElementAt(0));
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

    void SetDefaultCallHandling(DefaultCallHandling* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDefaultCallHandlingStaticDescription());
        AddElement(3, element);
    }

    void SetDefaultCallHandling(const DefaultCallHandling& element)
    {
        its::AsnObject& asnObject = const_cast<DefaultCallHandling&>(element);
        asnObject.SetDescription(GetDefaultCallHandlingStaticDescription());
        AddElement(3, element);
    }

    const DefaultCallHandling& GetDefaultCallHandling() const
    {
        return static_cast<const DefaultCallHandling&> (ElementAt(3));
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

#endif    // !defined(_MAP_V3_O_BCSM_CAMEL_TDP_DATA_H_)

