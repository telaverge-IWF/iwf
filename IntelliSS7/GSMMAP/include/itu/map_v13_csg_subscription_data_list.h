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


#if !defined(_MAP_V13_CSG_SUBSCRIPTION_DATA_LIST_H_)
#define _MAP_V13_CSG_SUBSCRIPTION_DATA_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v13_csg_subscription_data.h>



namespace map_v13 {



class CSG_SubscriptionDataList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::CSG_SubscriptionData CSG_SubscriptionData;


////////// End Nested Class //////////

    CSG_SubscriptionDataList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    CSG_SubscriptionDataList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    CSG_SubscriptionDataList(const CSG_SubscriptionDataList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    CSG_SubscriptionDataList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetCSG_SubscriptionDataStaticDescription();

public:

    virtual ~CSG_SubscriptionDataList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CSG_SubscriptionDataList(*this);
    }

    virtual std::string GetName() const
    { return "CSG_SubscriptionDataList"; }

    void AddElement(CSG_SubscriptionData* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCSG_SubscriptionDataStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const CSG_SubscriptionData& element)
    {
        its::AsnObject& asnObject = const_cast<CSG_SubscriptionData&>(element);
        asnObject.SetDescription(GetCSG_SubscriptionDataStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const CSG_SubscriptionData& ElementAt(int index) const
    {
        return static_cast<const CSG_SubscriptionData&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_CSG_SUBSCRIPTION_DATA_LIST_H_)

