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


#if !defined(_CAP_V3_CAMEL_A_CH_BILLING_CHARGING_CHARACTERISTICS_H_)
#define _CAP_V3_CAMEL_A_CH_BILLING_CHARGING_CHARACTERISTICS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnSequence.h>
#include <AsnInteger.h>
#include <AsnBoolean.h>
#include <AsnSequenceOf.h>

#include <cap_v3_extension_field.h>



namespace cap_v3 {



class CAMEL_AChBillingChargingCharacteristics : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////



    class TimeDurationCharging : public its::AsnSequence
    {
    public:


    ////////// Begin Nested Class(es) //////////



        class MaxCallPeriodDuration : public its::AsnInteger
        {
        public:

            MaxCallPeriodDuration() : its::AsnInteger(false)
            {
                Initialize();
            }

            MaxCallPeriodDuration(long value) : its::AsnInteger(value, false)
            {
                Initialize();
            }

            MaxCallPeriodDuration(its::Octets& octets) : its::AsnInteger(false)
            {
                Initialize();
                Decode(octets);
            }

            MaxCallPeriodDuration(const MaxCallPeriodDuration& rhs) : its::AsnInteger(rhs)
            {
                // Nothing to do.
            }

            MaxCallPeriodDuration(its::AsnDescObject* description) : its::AsnInteger(description)
            {
                // Nothing to do.
            }

            MaxCallPeriodDuration(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

            virtual ~MaxCallPeriodDuration()
            {
                // Nothing to do.
            }

            virtual its::AsnObject* Clone() const
            {
                return new MaxCallPeriodDuration(*this);
            }

            virtual std::string GetName() const
            { return "MaxCallPeriodDuration"; }

        };



        class ReleaseIfdurationExceeded : public its::AsnBoolean
        {
        public:

            ReleaseIfdurationExceeded(bool value) : its::AsnBoolean(value, false)
            {
                Initialize();
            }

            ReleaseIfdurationExceeded(its::Octets& octets) : its::AsnBoolean(false, false)
            {
                Initialize();
                Decode(octets);
            }

            ReleaseIfdurationExceeded(const ReleaseIfdurationExceeded& rhs) : its::AsnBoolean(rhs)
            {
                // Nothing to do.
            }

            ReleaseIfdurationExceeded(its::AsnDescObject* description) : its::AsnBoolean(description)
            {
                // Nothing to do.
            }

            ReleaseIfdurationExceeded(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

            virtual ~ReleaseIfdurationExceeded()
            {
                // Nothing to do.
            }

            virtual its::AsnObject* Clone() const
            {
                return new ReleaseIfdurationExceeded(*this);
            }

            virtual std::string GetName() const
            { return "ReleaseIfdurationExceeded"; }

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



        class Tone : public its::AsnBoolean
        {
        public:

            Tone(bool value) : its::AsnBoolean(value, false)
            {
                Initialize();
            }

            Tone(its::Octets& octets) : its::AsnBoolean(false, false)
            {
                Initialize();
                Decode(octets);
            }

            Tone(const Tone& rhs) : its::AsnBoolean(rhs)
            {
                // Nothing to do.
            }

            Tone(its::AsnDescObject* description) : its::AsnBoolean(description)
            {
                // Nothing to do.
            }

            Tone(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

            virtual ~Tone()
            {
                // Nothing to do.
            }

            virtual its::AsnObject* Clone() const
            {
                return new Tone(*this);
            }

            virtual std::string GetName() const
            { return "Tone"; }

        };



        class Extensions : public its::AsnSequenceOf
        {
        public:


        ////////// Begin Nested Class //////////


                typedef cap_v3::ExtensionField ExtensionField;


        ////////// End Nested Class //////////

            Extensions() : its::AsnSequenceOf(false)
            {
                Initialize();
            }

            Extensions(its::Octets& octets) : its::AsnSequenceOf(false)
            {
                Initialize();
                Decode(octets);
            }

            Extensions(const Extensions& rhs) : its::AsnSequenceOf(rhs)
            {
                // Nothing to do.
            }

            Extensions(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

            static its::AsnDescObject* GetExtensionFieldStaticDescription();

        public:

            virtual ~Extensions()
            {
                // Nothing to do.
            }

            virtual its::AsnObject* Clone() const
            {
                return new Extensions(*this);
            }

            virtual std::string GetName() const
            { return "Extensions"; }

            void AddElement(ExtensionField* element)
            {
                ITS_REQUIRE(element != NULL);
                element->AsnObject::SetDescription(GetExtensionFieldStaticDescription());
                AsnSequenceOf::AddElement(element);
            }

            void AddElement(const ExtensionField& element)
            {
                its::AsnObject& asnObject = const_cast<ExtensionField&>(element);
                asnObject.SetDescription(GetExtensionFieldStaticDescription());
                AsnSequenceOf::AddElement(element);
            }

            const ExtensionField& ElementAt(int index) const
            {
                return static_cast<const ExtensionField&> (AsnSequenceOf::ElementAt(index));
            }

        };


    ////////// End Nested Class(es) //////////

        TimeDurationCharging() : its::AsnSequence(5, false)
        {
            Initialize();
        }

        TimeDurationCharging(its::Octets& octets) : its::AsnSequence(5, false)
        {
            Initialize();
            Decode(octets);
        }

        TimeDurationCharging(const TimeDurationCharging& rhs) : its::AsnSequence(rhs)
        {
            // Nothing to do.
        }

        TimeDurationCharging(its::AsnDescObject* description) : its::AsnSequence(5, description)
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

        static its::AsnDescObject* GetMaxCallPeriodDurationStaticDescription();
        static its::AsnDescObject* GetReleaseIfdurationExceededStaticDescription();
        static its::AsnDescObject* GetTariffSwitchIntervalStaticDescription();
        static its::AsnDescObject* GetToneStaticDescription();
        static its::AsnDescObject* GetExtensionsStaticDescription();

    public:

        virtual ~TimeDurationCharging()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new TimeDurationCharging(*this);
        }

        virtual std::string GetName() const
        { return "TimeDurationCharging"; }

        void SetMaxCallPeriodDuration(MaxCallPeriodDuration* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetMaxCallPeriodDurationStaticDescription());
            AddElement(0, element);
        }

        void SetMaxCallPeriodDuration(const MaxCallPeriodDuration& element)
        {
            its::AsnObject& asnObject = const_cast<MaxCallPeriodDuration&>(element);
            asnObject.SetDescription(GetMaxCallPeriodDurationStaticDescription());
            AddElement(0, element);
        }

        const MaxCallPeriodDuration& GetMaxCallPeriodDuration() const
        {
            return static_cast<const MaxCallPeriodDuration&> (ElementAt(0));
        }

        void SetReleaseIfdurationExceeded(ReleaseIfdurationExceeded* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetReleaseIfdurationExceededStaticDescription());
            AddElement(1, element);
        }

        void SetReleaseIfdurationExceeded(const ReleaseIfdurationExceeded& element)
        {
            its::AsnObject& asnObject = const_cast<ReleaseIfdurationExceeded&>(element);
            asnObject.SetDescription(GetReleaseIfdurationExceededStaticDescription());
            AddElement(1, element);
        }

        const ReleaseIfdurationExceeded& GetReleaseIfdurationExceeded() const
        {
            return static_cast<const ReleaseIfdurationExceeded&> (ElementAt(1));
        }

        void SetTariffSwitchInterval(TariffSwitchInterval* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetTariffSwitchIntervalStaticDescription());
            AddElement(2, element);
        }

        void SetTariffSwitchInterval(const TariffSwitchInterval& element)
        {
            its::AsnObject& asnObject = const_cast<TariffSwitchInterval&>(element);
            asnObject.SetDescription(GetTariffSwitchIntervalStaticDescription());
            AddElement(2, element);
        }

        bool OptionTariffSwitchInterval() const
        {
            return Contains(2);
        }

        const TariffSwitchInterval& GetTariffSwitchInterval() const
        {
            ITS_REQUIRE(OptionTariffSwitchInterval());
            return static_cast<const TariffSwitchInterval&> (ElementAt(2));
        }

        void SetTone(Tone* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetToneStaticDescription());
            AddElement(3, element);
        }

        void SetTone(const Tone& element)
        {
            its::AsnObject& asnObject = const_cast<Tone&>(element);
            asnObject.SetDescription(GetToneStaticDescription());
            AddElement(3, element);
        }

        const Tone& GetTone() const
        {
            return static_cast<const Tone&> (ElementAt(3));
        }

        void SetExtensions(Extensions* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetExtensionsStaticDescription());
            AddElement(4, element);
        }

        void SetExtensions(const Extensions& element)
        {
            its::AsnObject& asnObject = const_cast<Extensions&>(element);
            asnObject.SetDescription(GetExtensionsStaticDescription());
            AddElement(4, element);
        }

        bool OptionExtensions() const
        {
            return Contains(4);
        }

        const Extensions& GetExtensions() const
        {
            ITS_REQUIRE(OptionExtensions());
            return static_cast<const Extensions&> (ElementAt(4));
        }

    };


////////// End Nested Class(es) //////////

    CAMEL_AChBillingChargingCharacteristics() : its::AsnChoice(false)
    {
        Initialize();
    }

    CAMEL_AChBillingChargingCharacteristics(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    CAMEL_AChBillingChargingCharacteristics(const CAMEL_AChBillingChargingCharacteristics& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    CAMEL_AChBillingChargingCharacteristics(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    CAMEL_AChBillingChargingCharacteristics(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetTimeDurationChargingStaticDescription();

public:

    virtual ~CAMEL_AChBillingChargingCharacteristics()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CAMEL_AChBillingChargingCharacteristics(*this);
    }

    virtual std::string GetName() const
    { return "CAMEL_AChBillingChargingCharacteristics"; }

    void SetChoiceTimeDurationCharging(TimeDurationCharging* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetTimeDurationChargingStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceTimeDurationCharging(const TimeDurationCharging& choice)
    {
        its::AsnObject& asnObject = const_cast<TimeDurationCharging&>(choice);
        asnObject.SetDescription(GetTimeDurationChargingStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceTimeDurationCharging() const
    {
        return Contains(GetTimeDurationChargingStaticDescription()->TagIdentity());
    }

    const TimeDurationCharging& GetChoiceTimeDurationCharging() const
    {
        ITS_REQUIRE(ChoiceTimeDurationCharging());
        return static_cast<const TimeDurationCharging&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_CAMEL_A_CH_BILLING_CHARGING_CHARACTERISTICS_H_)

