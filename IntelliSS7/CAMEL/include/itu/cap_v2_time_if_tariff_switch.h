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


#if !defined(_CAP_V2_TIME_IF_TARIFF_SWITCH_H_)
#define _CAP_V2_TIME_IF_TARIFF_SWITCH_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnInteger.h>



namespace cap_v2 {



class TimeIfTariffSwitch : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class TimeSinceTariffSwitch : public its::AsnInteger
    {
    public:

        TimeSinceTariffSwitch() : its::AsnInteger(false)
        {
            Initialize();
        }

        TimeSinceTariffSwitch(long value) : its::AsnInteger(value, false)
        {
            Initialize();
        }

        TimeSinceTariffSwitch(its::Octets& octets) : its::AsnInteger(false)
        {
            Initialize();
            Decode(octets);
        }

        TimeSinceTariffSwitch(const TimeSinceTariffSwitch& rhs) : its::AsnInteger(rhs)
        {
            // Nothing to do.
        }

        TimeSinceTariffSwitch(its::AsnDescObject* description) : its::AsnInteger(description)
        {
            // Nothing to do.
        }

        TimeSinceTariffSwitch(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

        virtual ~TimeSinceTariffSwitch()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new TimeSinceTariffSwitch(*this);
        }

        virtual std::string GetName() const
        { return "TimeSinceTariffSwitch"; }

    };



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


////////// End Nested Class(es) //////////

    TimeIfTariffSwitch() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    TimeIfTariffSwitch(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    TimeIfTariffSwitch(const TimeIfTariffSwitch& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    TimeIfTariffSwitch(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetTimeSinceTariffSwitchStaticDescription();
    static its::AsnDescObject* GetTariffSwitchIntervalStaticDescription();

public:

    virtual ~TimeIfTariffSwitch()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new TimeIfTariffSwitch(*this);
    }

    virtual std::string GetName() const
    { return "TimeIfTariffSwitch"; }

    void SetTimeSinceTariffSwitch(TimeSinceTariffSwitch* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTimeSinceTariffSwitchStaticDescription());
        AddElement(0, element);
    }

    void SetTimeSinceTariffSwitch(const TimeSinceTariffSwitch& element)
    {
        its::AsnObject& asnObject = const_cast<TimeSinceTariffSwitch&>(element);
        asnObject.SetDescription(GetTimeSinceTariffSwitchStaticDescription());
        AddElement(0, element);
    }

    const TimeSinceTariffSwitch& GetTimeSinceTariffSwitch() const
    {
        return static_cast<const TimeSinceTariffSwitch&> (ElementAt(0));
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

#endif    // !defined(_CAP_V2_TIME_IF_TARIFF_SWITCH_H_)

