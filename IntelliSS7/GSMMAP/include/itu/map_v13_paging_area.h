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


#if !defined(_MAP_V13_PAGING_AREA_H_)
#define _MAP_V13_PAGING_AREA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnChoice.h>

#include <map_v13_location_area.h>



namespace map_v13 {



class PagingArea : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::LocationArea LocationArea;


////////// End Nested Class //////////

    PagingArea() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    PagingArea(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    PagingArea(const PagingArea& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    PagingArea(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetLocationAreaStaticDescription();

public:

    virtual ~PagingArea()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PagingArea(*this);
    }

    virtual std::string GetName() const
    { return "PagingArea"; }

    void AddElement(LocationArea* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLocationAreaStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const LocationArea& element)
    {
        its::AsnObject& asnObject = const_cast<LocationArea&>(element);
        asnObject.SetDescription(GetLocationAreaStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const LocationArea& ElementAt(int index) const
    {
        return static_cast<const LocationArea&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_PAGING_AREA_H_)
