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


#if !defined(_CAP_V2_CAMEL_SCI_BILLING_CHARGING_CHARACTERISTICS_H_)
#define _CAP_V2_CAMEL_SCI_BILLING_CHARGING_CHARACTERISTICS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnSequence.h>

#include <cap_v2_aoc_before_answer.h>
#include <cap_v2_aoc_subsequent.h>



namespace cap_v2 {



class CAMEL_SCIBillingChargingCharacteristics : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v2::AOCBeforeAnswer AOCBeforeAnswer;


        typedef cap_v2::AOCSubsequent AOCSubsequent;


////////// End Nested Class(es) //////////

    CAMEL_SCIBillingChargingCharacteristics() : its::AsnChoice(false)
    {
        Initialize();
    }

    CAMEL_SCIBillingChargingCharacteristics(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    CAMEL_SCIBillingChargingCharacteristics(const CAMEL_SCIBillingChargingCharacteristics& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    CAMEL_SCIBillingChargingCharacteristics(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    CAMEL_SCIBillingChargingCharacteristics(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetAOCBeforeAnswerStaticDescription();
    static its::AsnDescObject* GetAOCAfterAnswerStaticDescription();

public:

    virtual ~CAMEL_SCIBillingChargingCharacteristics()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CAMEL_SCIBillingChargingCharacteristics(*this);
    }

    virtual std::string GetName() const
    { return "CAMEL_SCIBillingChargingCharacteristics"; }

    void SetChoiceAOCBeforeAnswer(AOCBeforeAnswer* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetAOCBeforeAnswerStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceAOCBeforeAnswer(const AOCBeforeAnswer& choice)
    {
        its::AsnObject& asnObject = const_cast<AOCBeforeAnswer&>(choice);
        asnObject.SetDescription(GetAOCBeforeAnswerStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceAOCBeforeAnswer() const
    {
        return Contains(GetAOCBeforeAnswerStaticDescription()->TagIdentity());
    }

    const AOCBeforeAnswer& GetChoiceAOCBeforeAnswer() const
    {
        ITS_REQUIRE(ChoiceAOCBeforeAnswer());
        return static_cast<const AOCBeforeAnswer&> (GetChoice());
    }

    void SetChoiceAOCAfterAnswer(AOCSubsequent* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetAOCAfterAnswerStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceAOCAfterAnswer(const AOCSubsequent& choice)
    {
        its::AsnObject& asnObject = const_cast<AOCSubsequent&>(choice);
        asnObject.SetDescription(GetAOCAfterAnswerStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceAOCAfterAnswer() const
    {
        return Contains(GetAOCAfterAnswerStaticDescription()->TagIdentity());
    }

    const AOCSubsequent& GetChoiceAOCAfterAnswer() const
    {
        ITS_REQUIRE(ChoiceAOCAfterAnswer());
        return static_cast<const AOCSubsequent&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_CAP_V2_CAMEL_SCI_BILLING_CHARGING_CHARACTERISTICS_H_)

