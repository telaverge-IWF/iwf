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


#if !defined(_MAP_V2_SM_DELIVERY_FAILURE_CAUSE_H_)
#define _MAP_V2_SM_DELIVERY_FAILURE_CAUSE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnSequence.h>
#include <AsnEnumerated.h>

#include <map_v2_sm_delivery_failure_cause_with_diagnostic.h>
#include <map_v2_sm_enumerated_delivery_failure_cause.h>



namespace map_v2 {



class SM_DeliveryFailureCause : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v2::SM_DeliveryFailureCauseWithDiagnostic SM_DeliveryFailureCauseWithDiagnostic;


        typedef map_v2::SM_EnumeratedDeliveryFailureCause SM_EnumeratedDeliveryFailureCause;


////////// End Nested Class(es) //////////

    SM_DeliveryFailureCause() : its::AsnChoice(false)
    {
        Initialize();
    }

    SM_DeliveryFailureCause(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    SM_DeliveryFailureCause(const SM_DeliveryFailureCause& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    SM_DeliveryFailureCause(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    SM_DeliveryFailureCause(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetSm_DeliveryFailureCauseWithDiagnosticStaticDescription();
    static its::AsnDescObject* GetSm_EnumeratedDeliveryFailureCauseStaticDescription();

public:

    virtual ~SM_DeliveryFailureCause()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SM_DeliveryFailureCause(*this);
    }

    virtual std::string GetName() const
    { return "SM_DeliveryFailureCause"; }

    void SetChoiceSm_DeliveryFailureCauseWithDiagnostic(SM_DeliveryFailureCauseWithDiagnostic* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetSm_DeliveryFailureCauseWithDiagnosticStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceSm_DeliveryFailureCauseWithDiagnostic(const SM_DeliveryFailureCauseWithDiagnostic& choice)
    {
        its::AsnObject& asnObject = const_cast<SM_DeliveryFailureCauseWithDiagnostic&>(choice);
        asnObject.SetDescription(GetSm_DeliveryFailureCauseWithDiagnosticStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceSm_DeliveryFailureCauseWithDiagnostic() const
    {
        return Contains(GetSm_DeliveryFailureCauseWithDiagnosticStaticDescription()->TagIdentity());
    }

    const SM_DeliveryFailureCauseWithDiagnostic& GetChoiceSm_DeliveryFailureCauseWithDiagnostic() const
    {
        ITS_REQUIRE(ChoiceSm_DeliveryFailureCauseWithDiagnostic());
        return static_cast<const SM_DeliveryFailureCauseWithDiagnostic&> (GetChoice());
    }

    void SetChoiceSm_EnumeratedDeliveryFailureCause(SM_EnumeratedDeliveryFailureCause* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetSm_EnumeratedDeliveryFailureCauseStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceSm_EnumeratedDeliveryFailureCause(const SM_EnumeratedDeliveryFailureCause& choice)
    {
        its::AsnObject& asnObject = const_cast<SM_EnumeratedDeliveryFailureCause&>(choice);
        asnObject.SetDescription(GetSm_EnumeratedDeliveryFailureCauseStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceSm_EnumeratedDeliveryFailureCause() const
    {
        return Contains(GetSm_EnumeratedDeliveryFailureCauseStaticDescription()->TagIdentity());
    }

    const SM_EnumeratedDeliveryFailureCause& GetChoiceSm_EnumeratedDeliveryFailureCause() const
    {
        ITS_REQUIRE(ChoiceSm_EnumeratedDeliveryFailureCause());
        return static_cast<const SM_EnumeratedDeliveryFailureCause&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V2_SM_DELIVERY_FAILURE_CAUSE_H_)
