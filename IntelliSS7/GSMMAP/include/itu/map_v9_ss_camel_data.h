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


#if !defined(_MAP_V9_SS_CAMEL_DATA_H_)
#define _MAP_V9_SS_CAMEL_DATA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>
#include <AsnOctetString.h>

#include <map_v9_ss_event_list.h>
#include <map_v9_isdn_address_string.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class SS_CamelData : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::SS_EventList SS_EventList;


        typedef map_v9::ISDN_AddressString ISDN_AddressString;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    SS_CamelData() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    SS_CamelData(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    SS_CamelData(const SS_CamelData& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SS_CamelData(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetSs_EventListStaticDescription();
    static its::AsnDescObject* GetGsmSCF_AddressStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~SS_CamelData()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SS_CamelData(*this);
    }

    virtual std::string GetName() const
    { return "SS_CamelData"; }

    void SetSs_EventList(SS_EventList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_EventListStaticDescription());
        AddElement(0, element);
    }

    void SetSs_EventList(const SS_EventList& element)
    {
        its::AsnObject& asnObject = const_cast<SS_EventList&>(element);
        asnObject.SetDescription(GetSs_EventListStaticDescription());
        AddElement(0, element);
    }

    const SS_EventList& GetSs_EventList() const
    {
        return static_cast<const SS_EventList&> (ElementAt(0));
    }

    void SetGsmSCF_Address(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGsmSCF_AddressStaticDescription());
        AddElement(1, element);
    }

    void SetGsmSCF_Address(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetGsmSCF_AddressStaticDescription());
        AddElement(1, element);
    }

    const ISDN_AddressString& GetGsmSCF_Address() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(1));
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

#endif    // !defined(_MAP_V9_SS_CAMEL_DATA_H_)

