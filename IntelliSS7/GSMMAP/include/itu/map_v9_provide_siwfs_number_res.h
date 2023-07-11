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


#if !defined(_MAP_V9_PROVIDE_SIWFS_NUMBER_RES_H_)
#define _MAP_V9_PROVIDE_SIWFS_NUMBER_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v9_isdn_address_string.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class ProvideSIWFSNumberRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::ISDN_AddressString ISDN_AddressString;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    ProvideSIWFSNumberRes() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    ProvideSIWFSNumberRes(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    ProvideSIWFSNumberRes(const ProvideSIWFSNumberRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ProvideSIWFSNumberRes(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetSIWFSNumberStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~ProvideSIWFSNumberRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ProvideSIWFSNumberRes(*this);
    }

    virtual std::string GetName() const
    { return "ProvideSIWFSNumberRes"; }

    void SetSIWFSNumber(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSIWFSNumberStaticDescription());
        AddElement(0, element);
    }

    void SetSIWFSNumber(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetSIWFSNumberStaticDescription());
        AddElement(0, element);
    }

    const ISDN_AddressString& GetSIWFSNumber() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(1, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(1, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(1);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_PROVIDE_SIWFS_NUMBER_RES_H_)

