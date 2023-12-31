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


#if !defined(_MAP_V13_SUBSCRIBED_PERIODIC_RAUTA_UTIMER_H_)
#define _MAP_V13_SUBSCRIBED_PERIODIC_RAUTA_UTIMER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v13 {



class SubscribedPeriodicRAUTAUtimer : public its::AsnInteger
{
public:

    SubscribedPeriodicRAUTAUtimer() : its::AsnInteger(false)
    {
        Initialize();
    }

    SubscribedPeriodicRAUTAUtimer(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    SubscribedPeriodicRAUTAUtimer(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    SubscribedPeriodicRAUTAUtimer(const SubscribedPeriodicRAUTAUtimer& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    SubscribedPeriodicRAUTAUtimer(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    SubscribedPeriodicRAUTAUtimer(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~SubscribedPeriodicRAUTAUtimer()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SubscribedPeriodicRAUTAUtimer(*this);
    }

    virtual std::string GetName() const
    { return "SubscribedPeriodicRAUTAUtimer"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_SUBSCRIBED_PERIODIC_RAUTA_UTIMER_H_)

