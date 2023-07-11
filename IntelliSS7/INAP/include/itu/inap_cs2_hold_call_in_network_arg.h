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


#if !defined(_INAP_CS2_HOLD_CALL_IN_NETWORK_ARG_H_)
#define _INAP_CS2_HOLD_CALL_IN_NETWORK_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnNull.h>
#include <AsnOctetString.h>

#include <inap_cs2_hold_cause.h>



namespace inap_cs2 {



class HoldCallInNetworkArg : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////



    class Empty : public its::AsnNull
    {
    public:

        Empty() : its::AsnNull(false)
        {
            Initialize();
        }

        Empty(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Empty(const Empty& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Empty(its::AsnDescObject* description) : its::AsnNull(description)
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

    public:

        virtual ~Empty()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Empty(*this);
        }

        virtual std::string GetName() const
        { return "Empty"; }

    };


        typedef inap_cs2::HoldCause HoldCause;


////////// End Nested Class(es) //////////

    HoldCallInNetworkArg() : its::AsnChoice(false)
    {
        Initialize();
    }

    HoldCallInNetworkArg(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    HoldCallInNetworkArg(const HoldCallInNetworkArg& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    HoldCallInNetworkArg(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    HoldCallInNetworkArg(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetHoldcauseStaticDescription();
    static its::AsnDescObject* GetEmptyStaticDescription();

public:

    virtual ~HoldCallInNetworkArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new HoldCallInNetworkArg(*this);
    }

    virtual std::string GetName() const
    { return "HoldCallInNetworkArg"; }

    void SetChoiceHoldcause(HoldCause* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetHoldcauseStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceHoldcause(const HoldCause& choice)
    {
        its::AsnObject& asnObject = const_cast<HoldCause&>(choice);
        asnObject.SetDescription(GetHoldcauseStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceHoldcause() const
    {
        return Contains(GetHoldcauseStaticDescription()->TagIdentity());
    }

    const HoldCause& GetChoiceHoldcause() const
    {
        ITS_REQUIRE(ChoiceHoldcause());
        return static_cast<const HoldCause&> (GetChoice());
    }

    void SetChoiceEmpty(Empty* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetEmptyStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceEmpty(const Empty& choice)
    {
        its::AsnObject& asnObject = const_cast<Empty&>(choice);
        asnObject.SetDescription(GetEmptyStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceEmpty() const
    {
        return Contains(GetEmptyStaticDescription()->TagIdentity());
    }

    const Empty& GetChoiceEmpty() const
    {
        ITS_REQUIRE(ChoiceEmpty());
        return static_cast<const Empty&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_HOLD_CALL_IN_NETWORK_ARG_H_)
