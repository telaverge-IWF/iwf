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


#if !defined(_MAP_V9_LOCATION_ESTIMATE_TYPE_H_)
#define _MAP_V9_LOCATION_ESTIMATE_TYPE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnEnumerated.h>



namespace map_v9 {



class LocationEstimateType : public its::AsnEnumerated
{
public:

    LocationEstimateType() : its::AsnEnumerated(false)
    {
        Initialize();
    }

    LocationEstimateType(long value) : its::AsnEnumerated(value, false)
    {
        Initialize();
    }

    LocationEstimateType(its::Octets& octets) : its::AsnEnumerated(false)
    {
        Initialize();
        Decode(octets);
    }

    LocationEstimateType(const LocationEstimateType& rhs) : its::AsnEnumerated(rhs)
    {
        // Nothing to do.
    }

    LocationEstimateType(its::AsnDescObject* description) : its::AsnEnumerated(description)
    {
        // Nothing to do.
    }

    LocationEstimateType(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

public:

    virtual ~LocationEstimateType()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new LocationEstimateType(*this);
    }

    virtual std::string GetName() const
    { return "LocationEstimateType"; }

    virtual long Get(const std::string& valueName) const;

    virtual std::string Get(long value) const;

    virtual std::string GetExt(long value) const;

    enum {
        LOCATION_ESTIMATE_TYPE_CURRENT_LOCATION = 0,
        LOCATION_ESTIMATE_TYPE_CURRENT_OR_LAST_KNOWN_LOCATION = 1,
        LOCATION_ESTIMATE_TYPE_INITIAL_LOCATION = 2
,
        LOCATION_ESTIMATE_TYPE_ACTIVATE_DEFERRED_LOCATION = 3,
        LOCATION_ESTIMATE_TYPE_CANCEL_DEFERRED_LOCATION = 4
    };

    void SetCurrentLocation()
    { _value = 0; }

    bool IsCurrentLocation() const
    { return _value == 0; }

    void SetCurrentOrLastKnownLocation()
    { _value = 1; }

    bool IsCurrentOrLastKnownLocation() const
    { return _value == 1; }

    void SetInitialLocation()
    { _value = 2; }

    bool IsInitialLocation() const
    { return _value == 2; }

    void SetActivateDeferredLocation()
    { _value = 3; SetExtension(true); }

    bool IsActivateDeferredLocation()
    { return (IsExtension() && (_value == 3)); }

    void SetCancelDeferredLocation()
    { _value = 4; SetExtension(true); }

    bool IsCancelDeferredLocation()
    { return (IsExtension() && (_value == 4)); }

};



} // namespace.

#endif    // !defined(_MAP_V9_LOCATION_ESTIMATE_TYPE_H_)

