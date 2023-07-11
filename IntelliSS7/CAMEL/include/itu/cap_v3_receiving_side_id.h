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


#if !defined(_CAP_V3_RECEIVING_SIDE_ID_H_)
#define _CAP_V3_RECEIVING_SIDE_ID_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnOctetString.h>

#include <cap_v3_leg_type.h>



namespace cap_v3 {



class ReceivingSideID : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v3::LegType LegType;


////////// End Nested Class(es) //////////

    ReceivingSideID() : its::AsnChoice(false)
    {
        Initialize();
    }

    ReceivingSideID(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    ReceivingSideID(const ReceivingSideID& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    ReceivingSideID(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    ReceivingSideID(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetReceivingSideIDStaticDescription();

public:

    virtual ~ReceivingSideID()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ReceivingSideID(*this);
    }

    virtual std::string GetName() const
    { return "ReceivingSideID"; }

    void SetChoiceReceivingSideID(LegType* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetReceivingSideIDStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceReceivingSideID(const LegType& choice)
    {
        its::AsnObject& asnObject = const_cast<LegType&>(choice);
        asnObject.SetDescription(GetReceivingSideIDStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceReceivingSideID() const
    {
        return Contains(GetReceivingSideIDStaticDescription()->TagIdentity());
    }

    const LegType& GetChoiceReceivingSideID() const
    {
        ITS_REQUIRE(ChoiceReceivingSideID());
        return static_cast<const LegType&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_RECEIVING_SIDE_ID_H_)

