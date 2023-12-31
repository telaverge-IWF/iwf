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


#if !defined(_INAP_CS2_APPLY_CHARGING_ARG_H_)
#define _INAP_CS2_APPLY_CHARGING_ARG_H_

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

#include <inap_cs2_a_ch_billing_charging_characteristics.h>
#include <inap_cs2_leg_id.h>
#include <inap_cs2_extension_field.h>



namespace inap_cs2 {



class ApplyChargingArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Extensions : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef inap_cs2::ExtensionField ExtensionField;


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


        typedef inap_cs2::AChBillingChargingCharacteristics AChBillingChargingCharacteristics;


        typedef inap_cs2::LegID LegID;


////////// End Nested Class(es) //////////

    ApplyChargingArg() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    ApplyChargingArg(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    ApplyChargingArg(const ApplyChargingArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ApplyChargingArg(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetAChBillingChargingCharacteristicsStaticDescription();
    static its::AsnDescObject* GetPartyToChargeStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();

public:

    virtual ~ApplyChargingArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ApplyChargingArg(*this);
    }

    virtual std::string GetName() const
    { return "ApplyChargingArg"; }

    void SetAChBillingChargingCharacteristics(AChBillingChargingCharacteristics* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAChBillingChargingCharacteristicsStaticDescription());
        AddElement(0, element);
    }

    void SetAChBillingChargingCharacteristics(const AChBillingChargingCharacteristics& element)
    {
        its::AsnObject& asnObject = const_cast<AChBillingChargingCharacteristics&>(element);
        asnObject.SetDescription(GetAChBillingChargingCharacteristicsStaticDescription());
        AddElement(0, element);
    }

    const AChBillingChargingCharacteristics& GetAChBillingChargingCharacteristics() const
    {
        return static_cast<const AChBillingChargingCharacteristics&> (ElementAt(0));
    }

    void SetPartyToCharge(LegID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPartyToChargeStaticDescription());
        AddElement(1, element);
    }

    void SetPartyToCharge(const LegID& element)
    {
        its::AsnObject& asnObject = const_cast<LegID&>(element);
        asnObject.SetDescription(GetPartyToChargeStaticDescription());
        AddElement(1, element);
    }

    bool OptionPartyToCharge() const
    {
        return Contains(1);
    }

    const LegID& GetPartyToCharge() const
    {
        ITS_REQUIRE(OptionPartyToCharge());
        return static_cast<const LegID&> (ElementAt(1));
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

#endif    // !defined(_INAP_CS2_APPLY_CHARGING_ARG_H_)

