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


#if !defined(_MAP_V13_SM_DELIVERY_TIMER_VALUE_H_)
#define _MAP_V13_SM_DELIVERY_TIMER_VALUE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnInteger.h>



namespace map_v13 {



class SM_DeliveryTimerValue : public its::AsnInteger
{
public:

    SM_DeliveryTimerValue() : its::AsnInteger(false)
    {
        Initialize();
    }

    SM_DeliveryTimerValue(long value) : its::AsnInteger(value, false)
    {
        Initialize();
    }

    SM_DeliveryTimerValue(its::Octets& octets) : its::AsnInteger(false)
    {
        Initialize();
        Decode(octets);
    }

    SM_DeliveryTimerValue(const SM_DeliveryTimerValue& rhs) : its::AsnInteger(rhs)
    {
        // Nothing to do.
    }

    SM_DeliveryTimerValue(its::AsnDescObject* description) : its::AsnInteger(description)
    {
        // Nothing to do.
    }

    SM_DeliveryTimerValue(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

    virtual ~SM_DeliveryTimerValue()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SM_DeliveryTimerValue(*this);
    }

    virtual std::string GetName() const
    { return "SM_DeliveryTimerValue"; }

};



} // namespace.

#endif    // !defined(_MAP_V13_SM_DELIVERY_TIMER_VALUE_H_)

