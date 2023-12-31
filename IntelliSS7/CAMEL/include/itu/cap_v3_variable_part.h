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


#if !defined(_CAP_V3_VARIABLE_PART_H_)
#define _CAP_V3_VARIABLE_PART_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnOctetString.h>
#include <AsnInteger.h>

#include <cap_v3_integer4.h>
#include <cap_v3_digits.h>



namespace cap_v3 {



class VariablePart : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////



    class Time : public its::AsnOctetString
    {
    public:

        Time() : its::AsnOctetString(false)
        {
            Initialize();
        }

        Time(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        Time(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        Time(const Time& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        Time(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        Time(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~Time()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Time(*this);
        }

        virtual std::string GetName() const
        { return "Time"; }

    };



    class Date : public its::AsnOctetString
    {
    public:

        Date() : its::AsnOctetString(false)
        {
            Initialize();
        }

        Date(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        Date(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        Date(const Date& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        Date(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        Date(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~Date()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Date(*this);
        }

        virtual std::string GetName() const
        { return "Date"; }

    };



    class Price : public its::AsnOctetString
    {
    public:

        Price() : its::AsnOctetString(false)
        {
            Initialize();
        }

        Price(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        Price(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        Price(const Price& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        Price(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        Price(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~Price()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Price(*this);
        }

        virtual std::string GetName() const
        { return "Price"; }

    };


        typedef cap_v3::Integer4 Integer4;


        typedef cap_v3::Digits Digits;


////////// End Nested Class(es) //////////

    VariablePart() : its::AsnChoice(false)
    {
        Initialize();
    }

    VariablePart(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    VariablePart(const VariablePart& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    VariablePart(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    VariablePart(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetIntegerStaticDescription();
    static its::AsnDescObject* GetNumberStaticDescription();
    static its::AsnDescObject* GetTimeStaticDescription();
    static its::AsnDescObject* GetDateStaticDescription();
    static its::AsnDescObject* GetPriceStaticDescription();

public:

    virtual ~VariablePart()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new VariablePart(*this);
    }

    virtual std::string GetName() const
    { return "VariablePart"; }

    void SetChoiceInteger(Integer4* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetIntegerStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceInteger(const Integer4& choice)
    {
        its::AsnObject& asnObject = const_cast<Integer4&>(choice);
        asnObject.SetDescription(GetIntegerStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceInteger() const
    {
        return Contains(GetIntegerStaticDescription()->TagIdentity());
    }

    const Integer4& GetChoiceInteger() const
    {
        ITS_REQUIRE(ChoiceInteger());
        return static_cast<const Integer4&> (GetChoice());
    }

    void SetChoiceNumber(Digits* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetNumberStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceNumber(const Digits& choice)
    {
        its::AsnObject& asnObject = const_cast<Digits&>(choice);
        asnObject.SetDescription(GetNumberStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceNumber() const
    {
        return Contains(GetNumberStaticDescription()->TagIdentity());
    }

    const Digits& GetChoiceNumber() const
    {
        ITS_REQUIRE(ChoiceNumber());
        return static_cast<const Digits&> (GetChoice());
    }

    void SetChoiceTime(Time* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetTimeStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceTime(const Time& choice)
    {
        its::AsnObject& asnObject = const_cast<Time&>(choice);
        asnObject.SetDescription(GetTimeStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceTime() const
    {
        return Contains(GetTimeStaticDescription()->TagIdentity());
    }

    const Time& GetChoiceTime() const
    {
        ITS_REQUIRE(ChoiceTime());
        return static_cast<const Time&> (GetChoice());
    }

    void SetChoiceDate(Date* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetDateStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceDate(const Date& choice)
    {
        its::AsnObject& asnObject = const_cast<Date&>(choice);
        asnObject.SetDescription(GetDateStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceDate() const
    {
        return Contains(GetDateStaticDescription()->TagIdentity());
    }

    const Date& GetChoiceDate() const
    {
        ITS_REQUIRE(ChoiceDate());
        return static_cast<const Date&> (GetChoice());
    }

    void SetChoicePrice(Price* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetPriceStaticDescription());
        SetChoice(choice);
    }

    void SetChoicePrice(const Price& choice)
    {
        its::AsnObject& asnObject = const_cast<Price&>(choice);
        asnObject.SetDescription(GetPriceStaticDescription());
        SetChoice(choice);
    }

    bool ChoicePrice() const
    {
        return Contains(GetPriceStaticDescription()->TagIdentity());
    }

    const Price& GetChoicePrice() const
    {
        ITS_REQUIRE(ChoicePrice());
        return static_cast<const Price&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_VARIABLE_PART_H_)

