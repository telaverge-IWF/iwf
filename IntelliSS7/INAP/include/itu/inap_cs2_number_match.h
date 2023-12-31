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


#if !defined(_INAP_CS2_NUMBER_MATCH_H_)
#define _INAP_CS2_NUMBER_MATCH_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnOctetString.h>

#include <inap_cs2_called_party_number.h>



namespace inap_cs2 {



class NumberMatch : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef inap_cs2::CalledPartyNumber CalledPartyNumber;


////////// End Nested Class(es) //////////

    NumberMatch() : its::AsnChoice(false)
    {
        Initialize();
    }

    NumberMatch(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    NumberMatch(const NumberMatch& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    NumberMatch(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    NumberMatch(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetInitialMatchStaticDescription();
    static its::AsnDescObject* GetTotalMatchStaticDescription();

public:

    virtual ~NumberMatch()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new NumberMatch(*this);
    }

    virtual std::string GetName() const
    { return "NumberMatch"; }

    void SetChoiceInitialMatch(CalledPartyNumber* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetInitialMatchStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceInitialMatch(const CalledPartyNumber& choice)
    {
        its::AsnObject& asnObject = const_cast<CalledPartyNumber&>(choice);
        asnObject.SetDescription(GetInitialMatchStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceInitialMatch() const
    {
        return Contains(GetInitialMatchStaticDescription()->TagIdentity());
    }

    const CalledPartyNumber& GetChoiceInitialMatch() const
    {
        ITS_REQUIRE(ChoiceInitialMatch());
        return static_cast<const CalledPartyNumber&> (GetChoice());
    }

    void SetChoiceTotalMatch(CalledPartyNumber* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetTotalMatchStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceTotalMatch(const CalledPartyNumber& choice)
    {
        its::AsnObject& asnObject = const_cast<CalledPartyNumber&>(choice);
        asnObject.SetDescription(GetTotalMatchStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceTotalMatch() const
    {
        return Contains(GetTotalMatchStaticDescription()->TagIdentity());
    }

    const CalledPartyNumber& GetChoiceTotalMatch() const
    {
        ITS_REQUIRE(ChoiceTotalMatch());
        return static_cast<const CalledPartyNumber&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_NUMBER_MATCH_H_)

