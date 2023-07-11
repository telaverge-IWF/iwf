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


#if !defined(_INAP_CS2_PARTIAL_OUTCOME_QUALIFIER_H_)
#define _INAP_CS2_PARTIAL_OUTCOME_QUALIFIER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSet.h>
#include <AsnSetOf.h>
#include <AsnBoolean.h>
#include <AsnInteger.h>

#include <inap_cs2_limit_problem.h>
#include <inap_cs2_continuation_reference.h>



namespace inap_cs2 {



class PartialOutcomeQualifier : public its::AsnSet
{
public:


////////// Begin Nested Class(es) //////////



    class Unexplored : public its::AsnSetOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef inap_cs2::ContinuationReference ContinuationReference;


    ////////// End Nested Class //////////

        Unexplored() : its::AsnSetOf(false)
        {
            Initialize();
        }

        Unexplored(its::Octets& octets) : its::AsnSetOf(false)
        {
            Initialize();
            Decode(octets);
        }

        Unexplored(const Unexplored& rhs) : its::AsnSetOf(rhs)
        {
            // Nothing to do.
        }

        Unexplored(its::AsnDescObject* description) : its::AsnSetOf(description)
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

        static its::AsnDescObject* GetContinuationReferenceStaticDescription();

    public:

        virtual ~Unexplored()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Unexplored(*this);
        }

        virtual std::string GetName() const
        { return "Unexplored"; }

        void AddElement(ContinuationReference* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetContinuationReferenceStaticDescription());
            AsnSetOf::AddElement(element);
        }

        void AddElement(const ContinuationReference& element)
        {
            its::AsnObject& asnObject = const_cast<ContinuationReference&>(element);
            asnObject.SetDescription(GetContinuationReferenceStaticDescription());
            AsnSetOf::AddElement(element);
        }

        const ContinuationReference& ElementAt(int index) const
        {
            return static_cast<const ContinuationReference&> (AsnSetOf::ElementAt(index));
        }

    };



    class UnavailableCriticalExtensions : public its::AsnBoolean
    {
    public:

        UnavailableCriticalExtensions(bool value) : its::AsnBoolean(value, false)
        {
            Initialize();
        }

        UnavailableCriticalExtensions(its::Octets& octets) : its::AsnBoolean(false, false)
        {
            Initialize();
            Decode(octets);
        }

        UnavailableCriticalExtensions(const UnavailableCriticalExtensions& rhs) : its::AsnBoolean(rhs)
        {
            // Nothing to do.
        }

        UnavailableCriticalExtensions(its::AsnDescObject* description) : its::AsnBoolean(description)
        {
            // Nothing to do.
        }

        UnavailableCriticalExtensions(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

        virtual ~UnavailableCriticalExtensions()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new UnavailableCriticalExtensions(*this);
        }

        virtual std::string GetName() const
        { return "UnavailableCriticalExtensions"; }

    };


        typedef inap_cs2::LimitProblem LimitProblem;


////////// End Nested Class(es) //////////

    PartialOutcomeQualifier() : its::AsnSet(3, false)
    {
        Initialize();
    }

    PartialOutcomeQualifier(its::Octets& octets) : its::AsnSet(3, false)
    {
        Initialize();
        Decode(octets);
    }

    PartialOutcomeQualifier(const PartialOutcomeQualifier& rhs) : its::AsnSet(rhs)
    {
        // Nothing to do.
    }

    PartialOutcomeQualifier(its::AsnDescObject* description) : its::AsnSet(3, description)
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

    static its::AsnDescObject* GetLimitProblemStaticDescription();
    static its::AsnDescObject* GetUnexploredStaticDescription();
    static its::AsnDescObject* GetUnavailableCriticalExtensionsStaticDescription();

public:

    virtual ~PartialOutcomeQualifier()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PartialOutcomeQualifier(*this);
    }

    virtual std::string GetName() const
    { return "PartialOutcomeQualifier"; }

    void SetLimitProblem(LimitProblem* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLimitProblemStaticDescription());
        AddElement(0, element);
    }

    void SetLimitProblem(const LimitProblem& element)
    {
        its::AsnObject& asnObject = const_cast<LimitProblem&>(element);
        asnObject.SetDescription(GetLimitProblemStaticDescription());
        AddElement(0, element);
}

    bool OptionLimitProblem() const
    {
        return Contains(0);
    }

    const LimitProblem& GetLimitProblem() const
    {
        ITS_REQUIRE(OptionLimitProblem());
        return static_cast<const LimitProblem&> (ElementAt(0));
    }

    void SetUnexplored(Unexplored* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetUnexploredStaticDescription());
        AddElement(1, element);
    }

    void SetUnexplored(const Unexplored& element)
    {
        its::AsnObject& asnObject = const_cast<Unexplored&>(element);
        asnObject.SetDescription(GetUnexploredStaticDescription());
        AddElement(1, element);
}

    bool OptionUnexplored() const
    {
        return Contains(1);
    }

    const Unexplored& GetUnexplored() const
    {
        ITS_REQUIRE(OptionUnexplored());
        return static_cast<const Unexplored&> (ElementAt(1));
    }

    void SetUnavailableCriticalExtensions(UnavailableCriticalExtensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetUnavailableCriticalExtensionsStaticDescription());
        AddElement(2, element);
    }

    void SetUnavailableCriticalExtensions(const UnavailableCriticalExtensions& element)
    {
        its::AsnObject& asnObject = const_cast<UnavailableCriticalExtensions&>(element);
        asnObject.SetDescription(GetUnavailableCriticalExtensionsStaticDescription());
        AddElement(2, element);
}

    bool OptionUnavailableCriticalExtensions() const
    {
        return Contains(2);
    }

    const UnavailableCriticalExtensions& GetUnavailableCriticalExtensions() const
    {
        ITS_REQUIRE(OptionUnavailableCriticalExtensions());
        return static_cast<const UnavailableCriticalExtensions&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_PARTIAL_OUTCOME_QUALIFIER_H_)

