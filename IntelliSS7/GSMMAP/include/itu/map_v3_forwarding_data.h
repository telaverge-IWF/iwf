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


#if !defined(_MAP_V3_FORWARDING_DATA_H_)
#define _MAP_V3_FORWARDING_DATA_H_

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
#include <map_v3_isdn_subaddress_string.h>
#include <map_v3_forwarding_options.h>
#include <map_v3_extension_container.h>



namespace map_v3 {



class ForwardingData : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::ISDN_AddressString ISDN_AddressString;


        typedef map_v3::ISDN_SubaddressString ISDN_SubaddressString;


        typedef map_v3::ForwardingOptions ForwardingOptions;


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    ForwardingData() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    ForwardingData(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    ForwardingData(const ForwardingData& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ForwardingData(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetForwardedToNumberStaticDescription();
    static its::AsnDescObject* GetForwardedToSubaddressStaticDescription();
    static its::AsnDescObject* GetForwardingOptionsStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~ForwardingData()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ForwardingData(*this);
    }

    virtual std::string GetName() const
    { return "ForwardingData"; }

    void SetForwardedToNumber(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardedToNumberStaticDescription());
        AddElement(0, element);
    }

    void SetForwardedToNumber(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetForwardedToNumberStaticDescription());
        AddElement(0, element);
    }

    bool OptionForwardedToNumber() const
    {
        return Contains(0);
    }

    const ISDN_AddressString& GetForwardedToNumber() const
    {
        ITS_REQUIRE(OptionForwardedToNumber());
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
    }

    void SetForwardedToSubaddress(ISDN_SubaddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardedToSubaddressStaticDescription());
        AddElement(1, element);
    }

    void SetForwardedToSubaddress(const ISDN_SubaddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_SubaddressString&>(element);
        asnObject.SetDescription(GetForwardedToSubaddressStaticDescription());
        AddElement(1, element);
    }

    bool OptionForwardedToSubaddress() const
    {
        return Contains(1);
    }

    const ISDN_SubaddressString& GetForwardedToSubaddress() const
    {
        ITS_REQUIRE(OptionForwardedToSubaddress());
        return static_cast<const ISDN_SubaddressString&> (ElementAt(1));
    }

    void SetForwardingOptions(ForwardingOptions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardingOptionsStaticDescription());
        AddElement(2, element);
    }

    void SetForwardingOptions(const ForwardingOptions& element)
    {
        its::AsnObject& asnObject = const_cast<ForwardingOptions&>(element);
        asnObject.SetDescription(GetForwardingOptionsStaticDescription());
        AddElement(2, element);
    }

    bool OptionForwardingOptions() const
    {
        return Contains(2);
    }

    const ForwardingOptions& GetForwardingOptions() const
    {
        ITS_REQUIRE(OptionForwardingOptions());
        return static_cast<const ForwardingOptions&> (ElementAt(2));
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

#endif    // !defined(_MAP_V3_FORWARDING_DATA_H_)

