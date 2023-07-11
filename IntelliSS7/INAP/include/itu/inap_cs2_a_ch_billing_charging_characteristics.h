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


#if !defined(_INAP_CS2_A_CH_BILLING_CHARGING_CHARACTERISTICS_H_)
#define _INAP_CS2_A_CH_BILLING_CHARGING_CHARACTERISTICS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace inap_cs2 {



class AChBillingChargingCharacteristics : public its::AsnOctetString
{
public:

    AChBillingChargingCharacteristics() : its::AsnOctetString(false)
    {
        Initialize();
    }

    AChBillingChargingCharacteristics(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    AChBillingChargingCharacteristics(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    AChBillingChargingCharacteristics(const AChBillingChargingCharacteristics& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    AChBillingChargingCharacteristics(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    AChBillingChargingCharacteristics(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~AChBillingChargingCharacteristics()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AChBillingChargingCharacteristics(*this);
    }

    virtual std::string GetName() const
    { return "AChBillingChargingCharacteristics"; }

};



} // namespace.

#endif    // !defined(_INAP_CS2_A_CH_BILLING_CHARGING_CHARACTERISTICS_H_)
