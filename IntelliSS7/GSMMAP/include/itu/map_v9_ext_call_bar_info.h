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


#if !defined(_MAP_V9_EXT_CALL_BAR_INFO_H_)
#define _MAP_V9_EXT_CALL_BAR_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnSequenceOf.h>

#include <map_v9_ss_code.h>
#include <map_v9_ext_call_bar_feature_list.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class Ext_CallBarInfo : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::SS_Code SS_Code;


        typedef map_v9::Ext_CallBarFeatureList Ext_CallBarFeatureList;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    Ext_CallBarInfo() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    Ext_CallBarInfo(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    Ext_CallBarInfo(const Ext_CallBarInfo& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    Ext_CallBarInfo(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetSs_CodeStaticDescription();
    static its::AsnDescObject* GetCallBarringFeatureListStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~Ext_CallBarInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Ext_CallBarInfo(*this);
    }

    virtual std::string GetName() const
    { return "Ext_CallBarInfo"; }

    void SetSs_Code(SS_Code* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_CodeStaticDescription());
        AddElement(0, element);
    }

    void SetSs_Code(const SS_Code& element)
    {
        its::AsnObject& asnObject = const_cast<SS_Code&>(element);
        asnObject.SetDescription(GetSs_CodeStaticDescription());
        AddElement(0, element);
    }

    const SS_Code& GetSs_Code() const
    {
        return static_cast<const SS_Code&> (ElementAt(0));
    }

    void SetCallBarringFeatureList(Ext_CallBarFeatureList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallBarringFeatureListStaticDescription());
        AddElement(1, element);
    }

    void SetCallBarringFeatureList(const Ext_CallBarFeatureList& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_CallBarFeatureList&>(element);
        asnObject.SetDescription(GetCallBarringFeatureListStaticDescription());
        AddElement(1, element);
    }

    const Ext_CallBarFeatureList& GetCallBarringFeatureList() const
    {
        return static_cast<const Ext_CallBarFeatureList&> (ElementAt(1));
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

#endif    // !defined(_MAP_V9_EXT_CALL_BAR_INFO_H_)
