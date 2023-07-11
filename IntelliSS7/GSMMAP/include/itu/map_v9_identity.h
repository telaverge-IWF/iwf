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


#if !defined(_MAP_V9_IDENTITY_H_)
#define _MAP_V9_IDENTITY_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnOctetString.h>
#include <AsnSequence.h>

#include <map_v9_imsi.h>
#include <map_v9_imsi_with_lmsi.h>



namespace map_v9 {



class Identity : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::IMSI IMSI;


        typedef map_v9::IMSI_WithLMSI IMSI_WithLMSI;


////////// End Nested Class(es) //////////

    Identity() : its::AsnChoice(false)
    {
        Initialize();
    }

    Identity(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    Identity(const Identity& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    Identity(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    Identity(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetImsi_WithLMSIStaticDescription();

public:

    virtual ~Identity()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Identity(*this);
    }

    virtual std::string GetName() const
    { return "Identity"; }

    void SetChoiceImsi(IMSI* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetImsiStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceImsi(const IMSI& choice)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(choice);
        asnObject.SetDescription(GetImsiStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceImsi() const
    {
        return Contains(GetImsiStaticDescription()->TagIdentity());
    }

    const IMSI& GetChoiceImsi() const
    {
        ITS_REQUIRE(ChoiceImsi());
        return static_cast<const IMSI&> (GetChoice());
    }

    void SetChoiceImsi_WithLMSI(IMSI_WithLMSI* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetImsi_WithLMSIStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceImsi_WithLMSI(const IMSI_WithLMSI& choice)
    {
        its::AsnObject& asnObject = const_cast<IMSI_WithLMSI&>(choice);
        asnObject.SetDescription(GetImsi_WithLMSIStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceImsi_WithLMSI() const
    {
        return Contains(GetImsi_WithLMSIStaticDescription()->TagIdentity());
    }

    const IMSI_WithLMSI& GetChoiceImsi_WithLMSI() const
    {
        ITS_REQUIRE(ChoiceImsi_WithLMSI());
        return static_cast<const IMSI_WithLMSI&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_IDENTITY_H_)

