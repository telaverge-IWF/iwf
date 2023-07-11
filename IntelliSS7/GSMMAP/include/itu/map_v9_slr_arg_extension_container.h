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


#if !defined(_MAP_V9_SLR_ARG_EXTENSION_CONTAINER_H_)
#define _MAP_V9_SLR_ARG_EXTENSION_CONTAINER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>

#include <map_v9_private_extension_list.h>
#include <map_v9_slr_arg_pcs_extensions.h>



namespace map_v9 {



class SLR_ArgExtensionContainer : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::PrivateExtensionList PrivateExtensionList;


        typedef map_v9::SLR_Arg_PCS_Extensions SLR_Arg_PCS_Extensions;


////////// End Nested Class(es) //////////

    SLR_ArgExtensionContainer() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    SLR_ArgExtensionContainer(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    SLR_ArgExtensionContainer(const SLR_ArgExtensionContainer& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SLR_ArgExtensionContainer(its::AsnDescObject* description) : its::AsnSequence(2, description)
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
    static its::AsnDescObject* GetSlr_Arg_PCS_ExtensionsStaticDescription();

public:

    virtual ~SLR_ArgExtensionContainer()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SLR_ArgExtensionContainer(*this);
    }

    virtual std::string GetName() const
    { return "SLR_ArgExtensionContainer"; }

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

    void SetSlr_Arg_PCS_Extensions(SLR_Arg_PCS_Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSlr_Arg_PCS_ExtensionsStaticDescription());
        AddElement(1, element);
    }

    void SetSlr_Arg_PCS_Extensions(const SLR_Arg_PCS_Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<SLR_Arg_PCS_Extensions&>(element);
        asnObject.SetDescription(GetSlr_Arg_PCS_ExtensionsStaticDescription());
        AddElement(1, element);
    }

    bool OptionSlr_Arg_PCS_Extensions() const
    {
        return Contains(1);
    }

    const SLR_Arg_PCS_Extensions& GetSlr_Arg_PCS_Extensions() const
    {
        ITS_REQUIRE(OptionSlr_Arg_PCS_Extensions());
        return static_cast<const SLR_Arg_PCS_Extensions&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_SLR_ARG_EXTENSION_CONTAINER_H_)
