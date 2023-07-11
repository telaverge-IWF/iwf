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


#if !defined(_CAP_V2_FCI_BILLING_CHARGING_CHARACTERISTICS_H_)
#define _CAP_V2_FCI_BILLING_CHARGING_CHARACTERISTICS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnOctetString.h>



namespace cap_v2 {



class FCIBillingChargingCharacteristics : public its::AsnOctetString
{
public:

    FCIBillingChargingCharacteristics() : its::AsnOctetString(false)
    {
        Initialize();
    }

    FCIBillingChargingCharacteristics(const std::vector<byte>& array) : its::AsnOctetString(array, false)
    {
        Initialize();
    }

    FCIBillingChargingCharacteristics(its::Octets& octets) : its::AsnOctetString(false)
    {
        Initialize();
        Decode(octets);
    }

    FCIBillingChargingCharacteristics(const FCIBillingChargingCharacteristics& rhs) : its::AsnOctetString(rhs)
    {
        // Nothing to do.
    }

    FCIBillingChargingCharacteristics(its::AsnDescObject* description) : its::AsnOctetString(description)
    {
        // Nothing to do.
    }

    FCIBillingChargingCharacteristics(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

    virtual ~FCIBillingChargingCharacteristics()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new FCIBillingChargingCharacteristics(*this);
    }

    virtual std::string GetName() const
    { return "FCIBillingChargingCharacteristics"; }

};



} // namespace.

#endif    // !defined(_CAP_V2_FCI_BILLING_CHARGING_CHARACTERISTICS_H_)

