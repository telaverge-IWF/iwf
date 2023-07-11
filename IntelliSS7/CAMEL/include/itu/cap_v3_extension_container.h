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


#if !defined(_CAP_V3_EXTENSION_CONTAINER_H_)
#define _CAP_V3_EXTENSION_CONTAINER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>

#include <cap_v3_private_extension_list.h>
#include <cap_v3_pcs_extensions.h>



namespace cap_v3 {



class ExtensionContainer : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v3::PrivateExtensionList PrivateExtensionList;


        typedef cap_v3::PCS_Extensions PCS_Extensions;


////////// End Nested Class(es) //////////

    ExtensionContainer() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    ExtensionContainer(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    ExtensionContainer(const ExtensionContainer& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ExtensionContainer(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetPrivateExtensionListStaticDescription();
    static its::AsnDescObject* GetPcs_ExtensionsStaticDescription();

public:

    virtual ~ExtensionContainer()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ExtensionContainer(*this);
    }

    virtual std::string GetName() const
    { return "ExtensionContainer"; }

    void SetPrivateExtensionList(PrivateExtensionList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPrivateExtensionListStaticDescription());
        AddElement(0, element);
    }

    void SetPrivateExtensionList(const PrivateExtensionList& element)
    {
        its::AsnObject& asnObject = const_cast<PrivateExtensionList&>(element);
        asnObject.SetDescription(GetPrivateExtensionListStaticDescription());
        AddElement(0, element);
    }

    bool OptionPrivateExtensionList() const
    {
        return Contains(0);
    }

    const PrivateExtensionList& GetPrivateExtensionList() const
    {
        ITS_REQUIRE(OptionPrivateExtensionList());
        return static_cast<const PrivateExtensionList&> (ElementAt(0));
    }

    void SetPcs_Extensions(PCS_Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPcs_ExtensionsStaticDescription());
        AddElement(1, element);
    }

    void SetPcs_Extensions(const PCS_Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<PCS_Extensions&>(element);
        asnObject.SetDescription(GetPcs_ExtensionsStaticDescription());
        AddElement(1, element);
    }

    bool OptionPcs_Extensions() const
    {
        return Contains(1);
    }

    const PCS_Extensions& GetPcs_Extensions() const
    {
        ITS_REQUIRE(OptionPcs_Extensions());
        return static_cast<const PCS_Extensions&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_EXTENSION_CONTAINER_H_)

