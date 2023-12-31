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


#if !defined(_CAP_V2_AOC_SUBSEQUENT_H_)
#define _CAP_V2_AOC_SUBSEQUENT_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnInteger.h>

#include <cap_v2_cai_gsm0224.h>



namespace cap_v2 {



class AOCSubsequent : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class TariffSwitchInterval : public its::AsnInteger
    {
    public:

        TariffSwitchInterval() : its::AsnInteger(false)
        {
            Initialize();
        }

        TariffSwitchInterval(long value) : its::AsnInteger(value, false)
        {
            Initialize();
        }

        TariffSwitchInterval(its::Octets& octets) : its::AsnInteger(false)
        {
            Initialize();
            Decode(octets);
        }

        TariffSwitchInterval(const TariffSwitchInterval& rhs) : its::AsnInteger(rhs)
        {
            // Nothing to do.
        }

        TariffSwitchInterval(its::AsnDescObject* description) : its::AsnInteger(description)
        {
            // Nothing to do.
        }

        TariffSwitchInterval(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

        virtual ~TariffSwitchInterval()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new TariffSwitchInterval(*this);
        }

        virtual std::string GetName() const
        { return "TariffSwitchInterval"; }

    };


        typedef cap_v2::CAI_GSM0224 CAI_GSM0224;


////////// End Nested Class(es) //////////

    AOCSubsequent() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    AOCSubsequent(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    AOCSubsequent(const AOCSubsequent& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    AOCSubsequent(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetCAI_GSM0224StaticDescription();
    static its::AsnDescObject* GetTariffSwitchIntervalStaticDescription();

public:

    virtual ~AOCSubsequent()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AOCSubsequent(*this);
    }

    virtual std::string GetName() const
    { return "AOCSubsequent"; }

    void SetCAI_GSM0224(CAI_GSM0224* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCAI_GSM0224StaticDescription());
        AddElement(0, element);
    }

    void SetCAI_GSM0224(const CAI_GSM0224& element)
    {
        its::AsnObject& asnObject = const_cast<CAI_GSM0224&>(element);
        asnObject.SetDescription(GetCAI_GSM0224StaticDescription());
        AddElement(0, element);
    }

    const CAI_GSM0224& GetCAI_GSM0224() const
    {
        return static_cast<const CAI_GSM0224&> (ElementAt(0));
    }

    void SetTariffSwitchInterval(TariffSwitchInterval* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTariffSwitchIntervalStaticDescription());
        AddElement(1, element);
    }

    void SetTariffSwitchInterval(const TariffSwitchInterval& element)
    {
        its::AsnObject& asnObject = const_cast<TariffSwitchInterval&>(element);
        asnObject.SetDescription(GetTariffSwitchIntervalStaticDescription());
        AddElement(1, element);
    }

    bool OptionTariffSwitchInterval() const
    {
        return Contains(1);
    }

    const TariffSwitchInterval& GetTariffSwitchInterval() const
    {
        ITS_REQUIRE(OptionTariffSwitchInterval());
        return static_cast<const TariffSwitchInterval&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_CAP_V2_AOC_SUBSEQUENT_H_)

