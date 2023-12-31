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


#if !defined(_MAP_V3_EXT_CALL_BAR_FEATURE_LIST_H_)
#define _MAP_V3_EXT_CALL_BAR_FEATURE_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v3_ext_call_barring_feature.h>



namespace map_v3 {



class Ext_CallBarFeatureList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v3::Ext_CallBarringFeature Ext_CallBarringFeature;


////////// End Nested Class //////////

    Ext_CallBarFeatureList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    Ext_CallBarFeatureList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    Ext_CallBarFeatureList(const Ext_CallBarFeatureList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    Ext_CallBarFeatureList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetExt_CallBarringFeatureStaticDescription();

public:

    virtual ~Ext_CallBarFeatureList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Ext_CallBarFeatureList(*this);
    }

    virtual std::string GetName() const
    { return "Ext_CallBarFeatureList"; }

    void AddElement(Ext_CallBarringFeature* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExt_CallBarringFeatureStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const Ext_CallBarringFeature& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_CallBarringFeature&>(element);
        asnObject.SetDescription(GetExt_CallBarringFeatureStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const Ext_CallBarringFeature& ElementAt(int index) const
    {
        return static_cast<const Ext_CallBarringFeature&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_EXT_CALL_BAR_FEATURE_LIST_H_)

