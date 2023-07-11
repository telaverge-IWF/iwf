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


#if !defined(_MAP_V1_BEARER_SERVICE_LIST_H_)
#define _MAP_V1_BEARER_SERVICE_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnOctetString.h>

#include <map_v1_bearer_service_code.h>



namespace map_v1 {



class BearerServiceList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v1::BearerServiceCode BearerServiceCode;


////////// End Nested Class //////////

    BearerServiceList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    BearerServiceList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    BearerServiceList(const BearerServiceList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    BearerServiceList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetBearerServiceCodeStaticDescription();

public:

    virtual ~BearerServiceList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new BearerServiceList(*this);
    }

    virtual std::string GetName() const
    { return "BearerServiceList"; }

    void AddElement(BearerServiceCode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBearerServiceCodeStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const BearerServiceCode& element)
    {
        its::AsnObject& asnObject = const_cast<BearerServiceCode&>(element);
        asnObject.SetDescription(GetBearerServiceCodeStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const BearerServiceCode& ElementAt(int index) const
    {
        return static_cast<const BearerServiceCode&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V1_BEARER_SERVICE_LIST_H_)
