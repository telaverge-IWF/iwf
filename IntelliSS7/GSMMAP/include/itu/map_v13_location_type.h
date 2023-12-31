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


#if !defined(_MAP_V13_LOCATION_TYPE_H_)
#define _MAP_V13_LOCATION_TYPE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>
#include <AsnBitString.h>

#include <map_v13_location_estimate_type.h>
#include <map_v13_deferred_location_event_type.h>



namespace map_v13 {



class LocationType : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::LocationEstimateType LocationEstimateType;


        typedef map_v13::DeferredLocationEventType DeferredLocationEventType;


////////// End Nested Class(es) //////////

    LocationType() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    LocationType(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    LocationType(const LocationType& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    LocationType(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetLocationEstimateTypeStaticDescription();
    static its::AsnDescObject* GetDeferredLocationEventTypeStaticDescription();

public:

    virtual ~LocationType()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new LocationType(*this);
    }

    virtual std::string GetName() const
    { return "LocationType"; }

    void SetLocationEstimateType(LocationEstimateType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLocationEstimateTypeStaticDescription());
        AddElement(0, element);
    }

    void SetLocationEstimateType(const LocationEstimateType& element)
    {
        its::AsnObject& asnObject = const_cast<LocationEstimateType&>(element);
        asnObject.SetDescription(GetLocationEstimateTypeStaticDescription());
        AddElement(0, element);
    }

    const LocationEstimateType& GetLocationEstimateType() const
    {
        return static_cast<const LocationEstimateType&> (ElementAt(0));
    }

    void SetDeferredLocationEventType(DeferredLocationEventType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDeferredLocationEventTypeStaticDescription());
        AddElement(1, element);
    }

    void SetDeferredLocationEventType(const DeferredLocationEventType& element)
    {
        its::AsnObject& asnObject = const_cast<DeferredLocationEventType&>(element);
        asnObject.SetDescription(GetDeferredLocationEventTypeStaticDescription());
        AddElement(1, element);
    }

    bool OptionDeferredLocationEventType() const
    {
        return Contains(1);
    }

    const DeferredLocationEventType& GetDeferredLocationEventType() const
    {
        ITS_REQUIRE(OptionDeferredLocationEventType());
        return static_cast<const DeferredLocationEventType&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_LOCATION_TYPE_H_)

