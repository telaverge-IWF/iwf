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


#if !defined(_CAP_V3_CAMEL_SCIGPRS_BILLING_CHARGING_CHARACTERISTICS_H_)
#define _CAP_V3_CAMEL_SCIGPRS_BILLING_CHARGING_CHARACTERISTICS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <cap_v3_gprs_reference_number.h>
#include <cap_v3_aocgprs.h>
#include <cap_v3_pdpid.h>



namespace cap_v3 {



class CAMEL_SCIGPRSBillingChargingCharacteristics : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v3::GPRS_ReferenceNumber GPRS_ReferenceNumber;


        typedef cap_v3::AOCGPRS AOCGPRS;


        typedef cap_v3::PDPID PDPID;


////////// End Nested Class(es) //////////

    CAMEL_SCIGPRSBillingChargingCharacteristics() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    CAMEL_SCIGPRSBillingChargingCharacteristics(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    CAMEL_SCIGPRSBillingChargingCharacteristics(const CAMEL_SCIGPRSBillingChargingCharacteristics& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    CAMEL_SCIGPRSBillingChargingCharacteristics(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetGPRS_ReferenceNumberStaticDescription();
    static its::AsnDescObject* GetAOCGPRSStaticDescription();
    static its::AsnDescObject* GetPDPIDStaticDescription();

public:

    virtual ~CAMEL_SCIGPRSBillingChargingCharacteristics()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CAMEL_SCIGPRSBillingChargingCharacteristics(*this);
    }

    virtual std::string GetName() const
    { return "CAMEL_SCIGPRSBillingChargingCharacteristics"; }

    void SetGPRS_ReferenceNumber(GPRS_ReferenceNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGPRS_ReferenceNumberStaticDescription());
        AddElement(0, element);
    }

    void SetGPRS_ReferenceNumber(const GPRS_ReferenceNumber& element)
    {
        its::AsnObject& asnObject = const_cast<GPRS_ReferenceNumber&>(element);
        asnObject.SetDescription(GetGPRS_ReferenceNumberStaticDescription());
        AddElement(0, element);
    }

    const GPRS_ReferenceNumber& GetGPRS_ReferenceNumber() const
    {
        return static_cast<const GPRS_ReferenceNumber&> (ElementAt(0));
    }

    void SetAOCGPRS(AOCGPRS* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAOCGPRSStaticDescription());
        AddElement(1, element);
    }

    void SetAOCGPRS(const AOCGPRS& element)
    {
        its::AsnObject& asnObject = const_cast<AOCGPRS&>(element);
        asnObject.SetDescription(GetAOCGPRSStaticDescription());
        AddElement(1, element);
    }

    const AOCGPRS& GetAOCGPRS() const
    {
        return static_cast<const AOCGPRS&> (ElementAt(1));
    }

    void SetPDPID(PDPID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPDPIDStaticDescription());
        AddElement(2, element);
    }

    void SetPDPID(const PDPID& element)
    {
        its::AsnObject& asnObject = const_cast<PDPID&>(element);
        asnObject.SetDescription(GetPDPIDStaticDescription());
        AddElement(2, element);
    }

    bool OptionPDPID() const
    {
        return Contains(2);
    }

    const PDPID& GetPDPID() const
    {
        ITS_REQUIRE(OptionPDPID());
        return static_cast<const PDPID&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_CAMEL_SCIGPRS_BILLING_CHARGING_CHARACTERISTICS_H_)
