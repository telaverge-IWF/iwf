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


#if !defined(_CAP_V3_GAP_TREATMENT_H_)
#define _CAP_V3_GAP_TREATMENT_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnOctetString.h>

#include <cap_v3_information_to_send.h>
#include <cap_v3_cause.h>



namespace cap_v3 {



class GapTreatment : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v3::InformationToSend InformationToSend;


        typedef cap_v3::Cause Cause;


////////// End Nested Class(es) //////////

    GapTreatment() : its::AsnChoice(false)
    {
        Initialize();
    }

    GapTreatment(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    GapTreatment(const GapTreatment& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    GapTreatment(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    GapTreatment(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetInformationToSendStaticDescription();
    static its::AsnDescObject* GetReleaseCauseStaticDescription();

public:

    virtual ~GapTreatment()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new GapTreatment(*this);
    }

    virtual std::string GetName() const
    { return "GapTreatment"; }

    void SetChoiceInformationToSend(InformationToSend* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetInformationToSendStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceInformationToSend(const InformationToSend& choice)
    {
        its::AsnObject& asnObject = const_cast<InformationToSend&>(choice);
        asnObject.SetDescription(GetInformationToSendStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceInformationToSend() const
    {
        return Contains(GetInformationToSendStaticDescription()->TagIdentity());
    }

    const InformationToSend& GetChoiceInformationToSend() const
    {
        ITS_REQUIRE(ChoiceInformationToSend());
        return static_cast<const InformationToSend&> (GetChoice());
    }

    void SetChoiceReleaseCause(Cause* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetReleaseCauseStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceReleaseCause(const Cause& choice)
    {
        its::AsnObject& asnObject = const_cast<Cause&>(choice);
        asnObject.SetDescription(GetReleaseCauseStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceReleaseCause() const
    {
        return Contains(GetReleaseCauseStaticDescription()->TagIdentity());
    }

    const Cause& GetChoiceReleaseCause() const
    {
        ITS_REQUIRE(ChoiceReleaseCause());
        return static_cast<const Cause&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_GAP_TREATMENT_H_)

