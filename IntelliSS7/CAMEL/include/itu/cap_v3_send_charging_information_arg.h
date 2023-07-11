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


#if !defined(_CAP_V3_SEND_CHARGING_INFORMATION_ARG_H_)
#define _CAP_V3_SEND_CHARGING_INFORMATION_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>
#include <AsnOctetString.h>
#include <AsnChoice.h>

#include <cap_v3_sci_billing_charging_characteristics.h>
#include <cap_v3_sending_side_id.h>
#include <cap_v3_extension_field.h>



namespace cap_v3 {



class SendChargingInformationArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Extensions : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef cap_v3::ExtensionField ExtensionField;


    ////////// End Nested Class //////////

        Extensions() : its::AsnSequenceOf(false)
        {
            Initialize();
        }

        Extensions(its::Octets& octets) : its::AsnSequenceOf(false)
        {
            Initialize();
            Decode(octets);
        }

        Extensions(const Extensions& rhs) : its::AsnSequenceOf(rhs)
        {
            // Nothing to do.
        }

        Extensions(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

        static its::AsnDescObject* GetExtensionFieldStaticDescription();

    public:

        virtual ~Extensions()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Extensions(*this);
        }

        virtual std::string GetName() const
        { return "Extensions"; }

        void AddElement(ExtensionField* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetExtensionFieldStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        void AddElement(const ExtensionField& element)
        {
            its::AsnObject& asnObject = const_cast<ExtensionField&>(element);
            asnObject.SetDescription(GetExtensionFieldStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        const ExtensionField& ElementAt(int index) const
        {
            return static_cast<const ExtensionField&> (AsnSequenceOf::ElementAt(index));
        }

    };


        typedef cap_v3::SCIBillingChargingCharacteristics SCIBillingChargingCharacteristics;


        typedef cap_v3::SendingSideID SendingSideID;


////////// End Nested Class(es) //////////

    SendChargingInformationArg() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    SendChargingInformationArg(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    SendChargingInformationArg(const SendChargingInformationArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SendChargingInformationArg(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetSCIBillingChargingCharacteristicsStaticDescription();
    static its::AsnDescObject* GetPartyToChargeStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();

public:

    virtual ~SendChargingInformationArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SendChargingInformationArg(*this);
    }

    virtual std::string GetName() const
    { return "SendChargingInformationArg"; }

    void SetSCIBillingChargingCharacteristics(SCIBillingChargingCharacteristics* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSCIBillingChargingCharacteristicsStaticDescription());
        AddElement(0, element);
    }

    void SetSCIBillingChargingCharacteristics(const SCIBillingChargingCharacteristics& element)
    {
        its::AsnObject& asnObject = const_cast<SCIBillingChargingCharacteristics&>(element);
        asnObject.SetDescription(GetSCIBillingChargingCharacteristicsStaticDescription());
        AddElement(0, element);
    }

    const SCIBillingChargingCharacteristics& GetSCIBillingChargingCharacteristics() const
    {
        return static_cast<const SCIBillingChargingCharacteristics&> (ElementAt(0));
    }

    void SetPartyToCharge(SendingSideID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPartyToChargeStaticDescription());
        AddElement(1, element);
    }

    void SetPartyToCharge(const SendingSideID& element)
    {
        its::AsnObject& asnObject = const_cast<SendingSideID&>(element);
        asnObject.SetDescription(GetPartyToChargeStaticDescription());
        AddElement(1, element);
    }

    const SendingSideID& GetPartyToCharge() const
    {
        return static_cast<const SendingSideID&> (ElementAt(1));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(2, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(2, element);
    }

    bool OptionExtensions() const
    {
        return Contains(2);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_SEND_CHARGING_INFORMATION_ARG_H_)
