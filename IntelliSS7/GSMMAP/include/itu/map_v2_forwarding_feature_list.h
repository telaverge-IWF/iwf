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


#if !defined(_MAP_V2_FORWARDING_FEATURE_LIST_H_)
#define _MAP_V2_FORWARDING_FEATURE_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v2_forwarding_feature.h>



namespace map_v2 {



class ForwardingFeatureList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v2::ForwardingFeature ForwardingFeature;


////////// End Nested Class //////////

    ForwardingFeatureList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    ForwardingFeatureList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    ForwardingFeatureList(const ForwardingFeatureList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    ForwardingFeatureList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetForwardingFeatureStaticDescription();

public:

    virtual ~ForwardingFeatureList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ForwardingFeatureList(*this);
    }

    virtual std::string GetName() const
    { return "ForwardingFeatureList"; }

    void AddElement(ForwardingFeature* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardingFeatureStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const ForwardingFeature& element)
    {
        its::AsnObject& asnObject = const_cast<ForwardingFeature&>(element);
        asnObject.SetDescription(GetForwardingFeatureStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const ForwardingFeature& ElementAt(int index) const
    {
        return static_cast<const ForwardingFeature&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V2_FORWARDING_FEATURE_LIST_H_)

