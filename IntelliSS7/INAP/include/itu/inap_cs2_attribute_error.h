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


#if !defined(_INAP_CS2_ATTRIBUTE_ERROR_H_)
#define _INAP_CS2_ATTRIBUTE_ERROR_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSet.h>
#include <AsnSetOf.h>
#include <AsnSequence.h>
#include <AsnChoice.h>

#include <inap_cs2_name.h>
#include <inap_cs2_attribute_error_problem.h>



namespace inap_cs2 {



class AttributeError : public its::AsnSet
{
public:


////////// Begin Nested Class(es) //////////



    class Problems : public its::AsnSetOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef inap_cs2::AttributeErrorProblem AttributeErrorProblem;


    ////////// End Nested Class //////////

        Problems() : its::AsnSetOf(false)
        {
            Initialize();
        }

        Problems(its::Octets& octets) : its::AsnSetOf(false)
        {
            Initialize();
            Decode(octets);
        }

        Problems(const Problems& rhs) : its::AsnSetOf(rhs)
        {
            // Nothing to do.
        }

        Problems(its::AsnDescObject* description) : its::AsnSetOf(description)
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

        static its::AsnDescObject* GetAttributeErrorProblemStaticDescription();

    public:

        virtual ~Problems()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Problems(*this);
        }

        virtual std::string GetName() const
        { return "Problems"; }

        void AddElement(AttributeErrorProblem* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetAttributeErrorProblemStaticDescription());
            AsnSetOf::AddElement(element);
        }

        void AddElement(const AttributeErrorProblem& element)
        {
            its::AsnObject& asnObject = const_cast<AttributeErrorProblem&>(element);
            asnObject.SetDescription(GetAttributeErrorProblemStaticDescription());
            AsnSetOf::AddElement(element);
        }

        const AttributeErrorProblem& ElementAt(int index) const
        {
            return static_cast<const AttributeErrorProblem&> (AsnSetOf::ElementAt(index));
        }

    };


        typedef inap_cs2::Name Name;


////////// End Nested Class(es) //////////

    AttributeError() : its::AsnSet(2, false)
    {
        Initialize();
    }

    AttributeError(its::Octets& octets) : its::AsnSet(2, false)
    {
        Initialize();
        Decode(octets);
    }

    AttributeError(const AttributeError& rhs) : its::AsnSet(rhs)
    {
        // Nothing to do.
    }

    AttributeError(its::AsnDescObject* description) : its::AsnSet(2, description)
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

    static its::AsnDescObject* GetObjectStaticDescription();
    static its::AsnDescObject* GetProblemsStaticDescription();

public:

    virtual ~AttributeError()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AttributeError(*this);
    }

    virtual std::string GetName() const
    { return "AttributeError"; }

    void SetObject(Name* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetObjectStaticDescription());
        AddElement(0, element);
    }

    void SetObject(const Name& element)
    {
        its::AsnObject& asnObject = const_cast<Name&>(element);
        asnObject.SetDescription(GetObjectStaticDescription());
        AddElement(0, element);
}

    const Name& GetObject() const
    {
        return static_cast<const Name&> (ElementAt(0));
    }

    void SetProblems(Problems* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetProblemsStaticDescription());
        AddElement(1, element);
    }

    void SetProblems(const Problems& element)
    {
        its::AsnObject& asnObject = const_cast<Problems&>(element);
        asnObject.SetDescription(GetProblemsStaticDescription());
        AddElement(1, element);
}

    const Problems& GetProblems() const
    {
        return static_cast<const Problems&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_ATTRIBUTE_ERROR_H_)
