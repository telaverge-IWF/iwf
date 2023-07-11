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


#if !defined(_MAP_V13_CUG_FEATURE_H_)
#define _MAP_V13_CUG_FEATURE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnChoice.h>
#include <AsnInteger.h>
#include <AsnOctetString.h>

#include <map_v13_ext_basic_service_code.h>
#include <map_v13_cug_index.h>
#include <map_v13_inter_cug_restrictions.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class CUG_Feature : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::Ext_BasicServiceCode Ext_BasicServiceCode;


        typedef map_v13::CUG_Index CUG_Index;


        typedef map_v13::InterCUG_Restrictions InterCUG_Restrictions;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    CUG_Feature() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    CUG_Feature(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    CUG_Feature(const CUG_Feature& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    CUG_Feature(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetBasicServiceStaticDescription();
    static its::AsnDescObject* GetPreferentialCUG_IndicatorStaticDescription();
    static its::AsnDescObject* GetInterCUG_RestrictionsStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~CUG_Feature()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CUG_Feature(*this);
    }

    virtual std::string GetName() const
    { return "CUG_Feature"; }

    void SetBasicService(Ext_BasicServiceCode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBasicServiceStaticDescription());
        AddElement(0, element);
    }

    void SetBasicService(const Ext_BasicServiceCode& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_BasicServiceCode&>(element);
        asnObject.SetDescription(GetBasicServiceStaticDescription());
        AddElement(0, element);
    }

    bool OptionBasicService() const
    {
        return Contains(0);
    }

    const Ext_BasicServiceCode& GetBasicService() const
    {
        ITS_REQUIRE(OptionBasicService());
        return static_cast<const Ext_BasicServiceCode&> (ElementAt(0));
    }

    void SetPreferentialCUG_Indicator(CUG_Index* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPreferentialCUG_IndicatorStaticDescription());
        AddElement(1, element);
    }

    void SetPreferentialCUG_Indicator(const CUG_Index& element)
    {
        its::AsnObject& asnObject = const_cast<CUG_Index&>(element);
        asnObject.SetDescription(GetPreferentialCUG_IndicatorStaticDescription());
        AddElement(1, element);
    }

    bool OptionPreferentialCUG_Indicator() const
    {
        return Contains(1);
    }

    const CUG_Index& GetPreferentialCUG_Indicator() const
    {
        ITS_REQUIRE(OptionPreferentialCUG_Indicator());
        return static_cast<const CUG_Index&> (ElementAt(1));
    }

    void SetInterCUG_Restrictions(InterCUG_Restrictions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetInterCUG_RestrictionsStaticDescription());
        AddElement(2, element);
    }

    void SetInterCUG_Restrictions(const InterCUG_Restrictions& element)
    {
        its::AsnObject& asnObject = const_cast<InterCUG_Restrictions&>(element);
        asnObject.SetDescription(GetInterCUG_RestrictionsStaticDescription());
        AddElement(2, element);
    }

    const InterCUG_Restrictions& GetInterCUG_Restrictions() const
    {
        return static_cast<const InterCUG_Restrictions&> (ElementAt(2));
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

#endif    // !defined(_MAP_V13_CUG_FEATURE_H_)

