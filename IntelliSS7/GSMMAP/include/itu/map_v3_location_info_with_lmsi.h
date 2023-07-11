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


#if !defined(_MAP_V3_LOCATION_INFO_WITH_LMSI_H_)
#define _MAP_V3_LOCATION_INFO_WITH_LMSI_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v3_isdn_address_string.h>
#include <map_v3_lmsi.h>
#include <map_v3_extension_container.h>



namespace map_v3 {



class LocationInfoWithLMSI : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::ISDN_AddressString ISDN_AddressString;


        typedef map_v3::LMSI LMSI;


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    LocationInfoWithLMSI() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    LocationInfoWithLMSI(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    LocationInfoWithLMSI(const LocationInfoWithLMSI& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    LocationInfoWithLMSI(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetNetworkNode_NumberStaticDescription();
    static its::AsnDescObject* GetLmsiStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~LocationInfoWithLMSI()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new LocationInfoWithLMSI(*this);
    }

    virtual std::string GetName() const
    { return "LocationInfoWithLMSI"; }

    void SetNetworkNode_Number(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNetworkNode_NumberStaticDescription());
        AddElement(0, element);
    }

    void SetNetworkNode_Number(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetNetworkNode_NumberStaticDescription());
        AddElement(0, element);
    }

    const ISDN_AddressString& GetNetworkNode_Number() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
    }

    void SetLmsi(LMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLmsiStaticDescription());
        AddElement(1, element);
    }

    void SetLmsi(const LMSI& element)
    {
        its::AsnObject& asnObject = const_cast<LMSI&>(element);
        asnObject.SetDescription(GetLmsiStaticDescription());
        AddElement(1, element);
    }

    bool OptionLmsi() const
    {
        return Contains(1);
    }

    const LMSI& GetLmsi() const
    {
        ITS_REQUIRE(OptionLmsi());
        return static_cast<const LMSI&> (ElementAt(1));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(2, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(2, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(2);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_LOCATION_INFO_WITH_LMSI_H_)
