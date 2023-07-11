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


#if !defined(_INAP_CS2_BEARER_CAPABILITY_H_)
#define _INAP_CS2_BEARER_CAPABILITY_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnOctetString.h>



namespace inap_cs2 {



class BearerCapability : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////



    class BearerCap : public its::AsnOctetString
    {
    public:

        BearerCap() : its::AsnOctetString(false)
        {
            Initialize();
        }

        BearerCap(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        BearerCap(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        BearerCap(const BearerCap& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        BearerCap(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        BearerCap(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~BearerCap()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new BearerCap(*this);
        }

        virtual std::string GetName() const
        { return "BearerCap"; }

    };



    class Tmr : public its::AsnOctetString
    {
    public:

        Tmr() : its::AsnOctetString(false)
        {
            Initialize();
        }

        Tmr(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        Tmr(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        Tmr(const Tmr& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        Tmr(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        Tmr(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~Tmr()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Tmr(*this);
        }

        virtual std::string GetName() const
        { return "Tmr"; }

    };


////////// End Nested Class(es) //////////

    BearerCapability() : its::AsnChoice(false)
    {
        Initialize();
    }

    BearerCapability(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    BearerCapability(const BearerCapability& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    BearerCapability(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    BearerCapability(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetBearerCapStaticDescription();
    static its::AsnDescObject* GetTmrStaticDescription();

public:

    virtual ~BearerCapability()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new BearerCapability(*this);
    }

    virtual std::string GetName() const
    { return "BearerCapability"; }

    void SetChoiceBearerCap(BearerCap* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetBearerCapStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceBearerCap(const BearerCap& choice)
    {
        its::AsnObject& asnObject = const_cast<BearerCap&>(choice);
        asnObject.SetDescription(GetBearerCapStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceBearerCap() const
    {
        return Contains(GetBearerCapStaticDescription()->TagIdentity());
    }

    const BearerCap& GetChoiceBearerCap() const
    {
        ITS_REQUIRE(ChoiceBearerCap());
        return static_cast<const BearerCap&> (GetChoice());
    }

    void SetChoiceTmr(Tmr* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetTmrStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceTmr(const Tmr& choice)
    {
        its::AsnObject& asnObject = const_cast<Tmr&>(choice);
        asnObject.SetDescription(GetTmrStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceTmr() const
    {
        return Contains(GetTmrStaticDescription()->TagIdentity());
    }

    const Tmr& GetChoiceTmr() const
    {
        ITS_REQUIRE(ChoiceTmr());
        return static_cast<const Tmr&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_BEARER_CAPABILITY_H_)
