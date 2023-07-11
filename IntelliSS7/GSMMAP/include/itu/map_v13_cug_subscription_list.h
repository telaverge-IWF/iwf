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


#if !defined(_MAP_V13_CUG_SUBSCRIPTION_LIST_H_)
#define _MAP_V13_CUG_SUBSCRIPTION_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v13_cug_subscription.h>



namespace map_v13 {



class CUG_SubscriptionList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::CUG_Subscription CUG_Subscription;


////////// End Nested Class //////////

    CUG_SubscriptionList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    CUG_SubscriptionList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    CUG_SubscriptionList(const CUG_SubscriptionList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    CUG_SubscriptionList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetCUG_SubscriptionStaticDescription();

public:

    virtual ~CUG_SubscriptionList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CUG_SubscriptionList(*this);
    }

    virtual std::string GetName() const
    { return "CUG_SubscriptionList"; }

    void AddElement(CUG_Subscription* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCUG_SubscriptionStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const CUG_Subscription& element)
    {
        its::AsnObject& asnObject = const_cast<CUG_Subscription&>(element);
        asnObject.SetDescription(GetCUG_SubscriptionStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const CUG_Subscription& ElementAt(int index) const
    {
        return static_cast<const CUG_Subscription&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_CUG_SUBSCRIPTION_LIST_H_)

