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


#if !defined(_INAP_CS2_FILTER_H_)
#define _INAP_CS2_FILTER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnSetOf.h>

#include <inap_cs2_filter_item.h>



namespace inap_cs2 {



class Filter : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////



    class And : public its::AsnSetOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef inap_cs2::FilterItem FilterItem;


    ////////// End Nested Class //////////

        And() : its::AsnSetOf(false)
        {
            Initialize();
        }

        And(its::Octets& octets) : its::AsnSetOf(false)
        {
            Initialize();
            Decode(octets);
        }

        And(const And& rhs) : its::AsnSetOf(rhs)
        {
            // Nothing to do.
        }

        And(its::AsnDescObject* description) : its::AsnSetOf(description)
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

        static its::AsnDescObject* GetFilterItemStaticDescription();

    public:

        virtual ~And()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new And(*this);
        }

        virtual std::string GetName() const
        { return "And"; }

        void AddElement(FilterItem* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetFilterItemStaticDescription());
            AsnSetOf::AddElement(element);
        }

        void AddElement(const FilterItem& element)
        {
            its::AsnObject& asnObject = const_cast<FilterItem&>(element);
            asnObject.SetDescription(GetFilterItemStaticDescription());
            AsnSetOf::AddElement(element);
        }

        const FilterItem& ElementAt(int index) const
        {
            return static_cast<const FilterItem&> (AsnSetOf::ElementAt(index));
        }

    };



    class Or : public its::AsnSetOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef inap_cs2::FilterItem FilterItem;


    ////////// End Nested Class //////////

        Or() : its::AsnSetOf(false)
        {
            Initialize();
        }

        Or(its::Octets& octets) : its::AsnSetOf(false)
        {
            Initialize();
            Decode(octets);
        }

        Or(const Or& rhs) : its::AsnSetOf(rhs)
        {
            // Nothing to do.
        }

        Or(its::AsnDescObject* description) : its::AsnSetOf(description)
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

        static its::AsnDescObject* GetFilterItemStaticDescription();

    public:

        virtual ~Or()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Or(*this);
        }

        virtual std::string GetName() const
        { return "Or"; }

        void AddElement(FilterItem* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetFilterItemStaticDescription());
            AsnSetOf::AddElement(element);
        }

        void AddElement(const FilterItem& element)
        {
            its::AsnObject& asnObject = const_cast<FilterItem&>(element);
            asnObject.SetDescription(GetFilterItemStaticDescription());
            AsnSetOf::AddElement(element);
        }

        const FilterItem& ElementAt(int index) const
        {
            return static_cast<const FilterItem&> (AsnSetOf::ElementAt(index));
        }

    };


        typedef inap_cs2::FilterItem FilterItem;


////////// End Nested Class(es) //////////

    Filter() : its::AsnChoice(false)
    {
        Initialize();
    }

    Filter(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    Filter(const Filter& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    Filter(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    Filter(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetItemStaticDescription();
    static its::AsnDescObject* GetAndStaticDescription();
    static its::AsnDescObject* GetOrStaticDescription();
    static its::AsnDescObject* GetNotStaticDescription();

public:

    virtual ~Filter()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Filter(*this);
    }

    virtual std::string GetName() const
    { return "Filter"; }

    void SetChoiceItem(FilterItem* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetItemStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceItem(const FilterItem& choice)
    {
        its::AsnObject& asnObject = const_cast<FilterItem&>(choice);
        asnObject.SetDescription(GetItemStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceItem() const
    {
        return Contains(GetItemStaticDescription()->TagIdentity());
    }

    const FilterItem& GetChoiceItem() const
    {
        ITS_REQUIRE(ChoiceItem());
        return static_cast<const FilterItem&> (GetChoice());
    }

    void SetChoiceAnd(And* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetAndStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceAnd(const And& choice)
    {
        its::AsnObject& asnObject = const_cast<And&>(choice);
        asnObject.SetDescription(GetAndStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceAnd() const
    {
        return Contains(GetAndStaticDescription()->TagIdentity());
    }

    const And& GetChoiceAnd() const
    {
        ITS_REQUIRE(ChoiceAnd());
        return static_cast<const And&> (GetChoice());
    }

    void SetChoiceOr(Or* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetOrStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceOr(const Or& choice)
    {
        its::AsnObject& asnObject = const_cast<Or&>(choice);
        asnObject.SetDescription(GetOrStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceOr() const
    {
        return Contains(GetOrStaticDescription()->TagIdentity());
    }

    const Or& GetChoiceOr() const
    {
        ITS_REQUIRE(ChoiceOr());
        return static_cast<const Or&> (GetChoice());
    }

    void SetChoiceNot(FilterItem* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetNotStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceNot(const FilterItem& choice)
    {
        its::AsnObject& asnObject = const_cast<FilterItem&>(choice);
        asnObject.SetDescription(GetNotStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceNot() const
    {
        return Contains(GetNotStaticDescription()->TagIdentity());
    }

    const FilterItem& GetChoiceNot() const
    {
        ITS_REQUIRE(ChoiceNot());
        return static_cast<const FilterItem&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_FILTER_H_)
