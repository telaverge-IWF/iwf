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


#if !defined(_CAP_V2_DP_SPECIFIC_CRITERIA_H_)
#define _CAP_V2_DP_SPECIFIC_CRITERIA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnInteger.h>

#include <cap_v2_application_timer.h>



namespace cap_v2 {



class DPSpecificCriteria : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v2::ApplicationTimer ApplicationTimer;


////////// End Nested Class(es) //////////

    DPSpecificCriteria() : its::AsnChoice(false)
    {
        Initialize();
    }

    DPSpecificCriteria(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    DPSpecificCriteria(const DPSpecificCriteria& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    DPSpecificCriteria(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    DPSpecificCriteria(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetApplicationTimerStaticDescription();

public:

    virtual ~DPSpecificCriteria()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new DPSpecificCriteria(*this);
    }

    virtual std::string GetName() const
    { return "DPSpecificCriteria"; }

    void SetChoiceApplicationTimer(ApplicationTimer* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetApplicationTimerStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceApplicationTimer(const ApplicationTimer& choice)
    {
        its::AsnObject& asnObject = const_cast<ApplicationTimer&>(choice);
        asnObject.SetDescription(GetApplicationTimerStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceApplicationTimer() const
    {
        return Contains(GetApplicationTimerStaticDescription()->TagIdentity());
    }

    const ApplicationTimer& GetChoiceApplicationTimer() const
    {
        ITS_REQUIRE(ChoiceApplicationTimer());
        return static_cast<const ApplicationTimer&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_CAP_V2_DP_SPECIFIC_CRITERIA_H_)

