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


#if !defined(_MAP_V13_CCBS_FEATURE_LIST_H_)
#define _MAP_V13_CCBS_FEATURE_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v13_ccbs_feature.h>



namespace map_v13 {



class CCBS_FeatureList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::CCBS_Feature CCBS_Feature;


////////// End Nested Class //////////

    CCBS_FeatureList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    CCBS_FeatureList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    CCBS_FeatureList(const CCBS_FeatureList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    CCBS_FeatureList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetCCBS_FeatureStaticDescription();

public:

    virtual ~CCBS_FeatureList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CCBS_FeatureList(*this);
    }

    virtual std::string GetName() const
    { return "CCBS_FeatureList"; }

    void AddElement(CCBS_Feature* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCCBS_FeatureStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const CCBS_Feature& element)
    {
        its::AsnObject& asnObject = const_cast<CCBS_Feature&>(element);
        asnObject.SetDescription(GetCCBS_FeatureStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const CCBS_Feature& ElementAt(int index) const
    {
        return static_cast<const CCBS_Feature&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_CCBS_FEATURE_LIST_H_)

