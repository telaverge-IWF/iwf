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


#if !defined(_INAP_CS2_SF_BILLING_CHARGING_CHARACTERISTICS_H_)
#define _INAP_CS2_SF_BILLING_CHARGING_CHARACTERISTICS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace inap_cs2 {



class SFBillingChargingCharacteristics : public its::AsnOctetString
{
public:

    SFBillingChargingCharacteristics() : its::AsnOctetString(false)
    {
        Initialize();
    }

    SFBillingChargingCharacteristics(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    SFBillingChargingCharacteristics(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    SFBillingChargingCharacteristics(const SFBillingChargingCharacteristics& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    SFBillingChargingCharacteristics(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    SFBillingChargingCharacteristics(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~SFBillingChargingCharacteristics()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SFBillingChargingCharacteristics(*this);
    }

    virtual std::string GetName() const
    { return "SFBillingChargingCharacteristics"; }

};



} // namespace.

#endif    // !defined(_INAP_CS2_SF_BILLING_CHARGING_CHARACTERISTICS_H_)

