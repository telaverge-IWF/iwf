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


#if !defined(_CAP_V2_SENDING_SIDE_ID_H_)
#define _CAP_V2_SENDING_SIDE_ID_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnOctetString.h>

#include <cap_v2_leg_type.h>



namespace cap_v2 {



class SendingSideID : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v2::LegType LegType;


////////// End Nested Class(es) //////////

    SendingSideID() : its::AsnChoice(false)
    {
        Initialize();
    }

    SendingSideID(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    SendingSideID(const SendingSideID& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    SendingSideID(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    SendingSideID(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetSendingSideIDStaticDescription();

public:

    virtual ~SendingSideID()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SendingSideID(*this);
    }

    virtual std::string GetName() const
    { return "SendingSideID"; }

    void SetChoiceSendingSideID(LegType* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetSendingSideIDStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceSendingSideID(const LegType& choice)
    {
        its::AsnObject& asnObject = const_cast<LegType&>(choice);
        asnObject.SetDescription(GetSendingSideIDStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceSendingSideID() const
    {
        return Contains(GetSendingSideIDStaticDescription()->TagIdentity());
    }

    const LegType& GetChoiceSendingSideID() const
    {
        ITS_REQUIRE(ChoiceSendingSideID());
        return static_cast<const LegType&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_CAP_V2_SENDING_SIDE_ID_H_)

