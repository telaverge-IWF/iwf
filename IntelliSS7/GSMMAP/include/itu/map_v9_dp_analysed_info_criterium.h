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


#if !defined(_MAP_V9_DP_ANALYSED_INFO_CRITERIUM_H_)
#define _MAP_V9_DP_ANALYSED_INFO_CRITERIUM_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnInteger.h>
#include <AsnEnumerated.h>

#include <map_v9_isdn_address_string.h>
#include <map_v9_service_key.h>
#include <map_v9_default_call_handling.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class DP_AnalysedInfoCriterium : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::ISDN_AddressString ISDN_AddressString;


        typedef map_v9::ServiceKey ServiceKey;


        typedef map_v9::DefaultCallHandling DefaultCallHandling;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    DP_AnalysedInfoCriterium() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    DP_AnalysedInfoCriterium(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    DP_AnalysedInfoCriterium(const DP_AnalysedInfoCriterium& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    DP_AnalysedInfoCriterium(its::AsnDescObject* description) : its::AsnSequence(5, description)
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

    static its::AsnDescObject* GetDialledNumberStaticDescription();
    static its::AsnDescObject* GetServiceKeyStaticDescription();
    static its::AsnDescObject* GetGsmSCF_AddressStaticDescription();
    static its::AsnDescObject* GetDefaultCallHandlingStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~DP_AnalysedInfoCriterium()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new DP_AnalysedInfoCriterium(*this);
    }

    virtual std::string GetName() const
    { return "DP_AnalysedInfoCriterium"; }

    void SetDialledNumber(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDialledNumberStaticDescription());
        AddElement(0, element);
    }

    void SetDialledNumber(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetDialledNumberStaticDescription());
        AddElement(0, element);
    }

    const ISDN_AddressString& GetDialledNumber() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
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

#endif    // !defined(_MAP_V9_DP_ANALYSED_INFO_CRITERIUM_H_)

