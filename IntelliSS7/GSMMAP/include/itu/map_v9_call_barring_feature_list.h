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


#if !defined(_MAP_V9_CALL_BARRING_FEATURE_LIST_H_)
#define _MAP_V9_CALL_BARRING_FEATURE_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v9_call_barring_feature.h>



namespace map_v9 {



class CallBarringFeatureList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v9::CallBarringFeature CallBarringFeature;


////////// End Nested Class //////////

    CallBarringFeatureList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    CallBarringFeatureList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    CallBarringFeatureList(const CallBarringFeatureList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    CallBarringFeatureList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetCallBarringFeatureStaticDescription();

public:

    virtual ~CallBarringFeatureList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CallBarringFeatureList(*this);
    }

    virtual std::string GetName() const
    { return "CallBarringFeatureList"; }

    void AddElement(CallBarringFeature* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallBarringFeatureStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const CallBarringFeature& element)
    {
        its::AsnObject& asnObject = const_cast<CallBarringFeature&>(element);
        asnObject.SetDescription(GetCallBarringFeatureStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const CallBarringFeature& ElementAt(int index) const
    {
        return static_cast<const CallBarringFeature&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_CALL_BARRING_FEATURE_LIST_H_)

