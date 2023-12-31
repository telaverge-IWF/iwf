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


#if !defined(_MAP_V13_EVENT_THRESHOLD_RSRP_H_)
#define _MAP_V13_EVENT_THRESHOLD_RSRP_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v13 {



class EventThresholdRSRP : public its::AsnInteger
{
public:

    EventThresholdRSRP() : its::AsnInteger(false)
    {
        Initialize();
    }

    EventThresholdRSRP(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    EventThresholdRSRP(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    EventThresholdRSRP(const EventThresholdRSRP& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    EventThresholdRSRP(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    EventThresholdRSRP(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~EventThresholdRSRP()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new EventThresholdRSRP(*this);
    }

    virtual std::string GetName() const
    { return "EventThresholdRSRP"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_EVENT_THRESHOLD_RSRP_H_)

