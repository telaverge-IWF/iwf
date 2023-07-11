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


#if !defined(_INAP_CS2_PROFILE_IDENTIFIER_H_)
#define _INAP_CS2_PROFILE_IDENTIFIER_H_

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
#include <inap_cs2_facility_group.h>



namespace inap_cs2 {



class ProfileIdentifier : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef inap_cs2::CalledPartyNumber CalledPartyNumber;


        typedef inap_cs2::FacilityGroup FacilityGroup;


////////// End Nested Class(es) //////////

    ProfileIdentifier() : its::AsnChoice(false)
    {
        Initialize();
    }

    ProfileIdentifier(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    ProfileIdentifier(const ProfileIdentifier& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    ProfileIdentifier(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    ProfileIdentifier(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetAccessStaticDescription();
    static its::AsnDescObject* GetGroupStaticDescription();

public:

    virtual ~ProfileIdentifier()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ProfileIdentifier(*this);
    }

    virtual std::string GetName() const
    { return "ProfileIdentifier"; }

    void SetChoiceAccess(CalledPartyNumber* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetAccessStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceAccess(const CalledPartyNumber& choice)
    {
        its::AsnObject& asnObject = const_cast<CalledPartyNumber&>(choice);
        asnObject.SetDescription(GetAccessStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceAccess() const
    {
        return Contains(GetAccessStaticDescription()->TagIdentity());
    }

    const CalledPartyNumber& GetChoiceAccess() const
    {
        ITS_REQUIRE(ChoiceAccess());
        return static_cast<const CalledPartyNumber&> (GetChoice());
    }

    void SetChoiceGroup(FacilityGroup* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetGroupStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceGroup(const FacilityGroup& choice)
    {
        its::AsnObject& asnObject = const_cast<FacilityGroup&>(choice);
        asnObject.SetDescription(GetGroupStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceGroup() const
    {
        return Contains(GetGroupStaticDescription()->TagIdentity());
    }

    const FacilityGroup& GetChoiceGroup() const
    {
        ITS_REQUIRE(ChoiceGroup());
        return static_cast<const FacilityGroup&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_PROFILE_IDENTIFIER_H_)

