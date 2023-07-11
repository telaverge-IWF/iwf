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


#if !defined(_INAP_CS2_IN_ENTRY_INFORMATION_SELECTION_H_)
#define _INAP_CS2_IN_ENTRY_INFORMATION_SELECTION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSet.h>
#include <AsnChoice.h>
#include <AsnInteger.h>

#include <inap_cs2_attribute_types.h>
#include <inap_cs2_info_types.h>



namespace inap_cs2 {



class InEntryInformationSelection : public its::AsnSet
{
public:


////////// Begin Nested Class(es) //////////


        typedef inap_cs2::AttributeTypes AttributeTypes;


        typedef inap_cs2::InfoTypes InfoTypes;


////////// End Nested Class(es) //////////

    InEntryInformationSelection() : its::AsnSet(2, false)
    {
        Initialize();
    }

    InEntryInformationSelection(its::Octets& octets) : its::AsnSet(2, false)
    {
        Initialize();
        Decode(octets);
    }

    InEntryInformationSelection(const InEntryInformationSelection& rhs) : its::AsnSet(rhs)
    {
        // Nothing to do.
    }

    InEntryInformationSelection(its::AsnDescObject* description) : its::AsnSet(2, description)
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

    static its::AsnDescObject* GetAttributeTypesStaticDescription();
    static its::AsnDescObject* GetInfoTypesStaticDescription();

public:

    virtual ~InEntryInformationSelection()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new InEntryInformationSelection(*this);
    }

    virtual std::string GetName() const
    { return "InEntryInformationSelection"; }

    void SetAttributeTypes(AttributeTypes* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAttributeTypesStaticDescription());
        AddElement(0, element);
    }

    void SetAttributeTypes(const AttributeTypes& element)
    {
        its::AsnObject& asnObject = const_cast<AttributeTypes&>(element);
        asnObject.SetDescription(GetAttributeTypesStaticDescription());
        AddElement(0, element);
}

    const AttributeTypes& GetAttributeTypes() const
    {
        return static_cast<const AttributeTypes&> (ElementAt(0));
    }

    void SetInfoTypes(InfoTypes* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetInfoTypesStaticDescription());
        AddElement(1, element);
    }

    void SetInfoTypes(const InfoTypes& element)
    {
        its::AsnObject& asnObject = const_cast<InfoTypes&>(element);
        asnObject.SetDescription(GetInfoTypesStaticDescription());
        AddElement(1, element);
}

    bool OptionInfoTypes() const
    {
        return Contains(1);
    }

    const InfoTypes& GetInfoTypes() const
    {
        ITS_REQUIRE(OptionInfoTypes());
        return static_cast<const InfoTypes&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_IN_ENTRY_INFORMATION_SELECTION_H_)

