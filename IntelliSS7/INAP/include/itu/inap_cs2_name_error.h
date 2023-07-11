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


#if !defined(_INAP_CS2_NAME_ERROR_H_)
#define _INAP_CS2_NAME_ERROR_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSet.h>
#include <AsnInteger.h>
#include <AsnChoice.h>

#include <inap_cs2_name_problem.h>
#include <inap_cs2_name.h>



namespace inap_cs2 {



class NameError : public its::AsnSet
{
public:


////////// Begin Nested Class(es) //////////


        typedef inap_cs2::NameProblem NameProblem;


        typedef inap_cs2::Name Name;


////////// End Nested Class(es) //////////

    NameError() : its::AsnSet(2, false)
    {
        Initialize();
    }

    NameError(its::Octets& octets) : its::AsnSet(2, false)
    {
        Initialize();
        Decode(octets);
    }

    NameError(const NameError& rhs) : its::AsnSet(rhs)
    {
        // Nothing to do.
    }

    NameError(its::AsnDescObject* description) : its::AsnSet(2, description)
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

    static its::AsnDescObject* GetProblemStaticDescription();
    static its::AsnDescObject* GetMatchedStaticDescription();

public:

    virtual ~NameError()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new NameError(*this);
    }

    virtual std::string GetName() const
    { return "NameError"; }

    void SetProblem(NameProblem* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetProblemStaticDescription());
        AddElement(0, element);
    }

    void SetProblem(const NameProblem& element)
    {
        its::AsnObject& asnObject = const_cast<NameProblem&>(element);
        asnObject.SetDescription(GetProblemStaticDescription());
        AddElement(0, element);
}

    const NameProblem& GetProblem() const
    {
        return static_cast<const NameProblem&> (ElementAt(0));
    }

    void SetMatched(Name* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMatchedStaticDescription());
        AddElement(1, element);
    }

    void SetMatched(const Name& element)
    {
        its::AsnObject& asnObject = const_cast<Name&>(element);
        asnObject.SetDescription(GetMatchedStaticDescription());
        AddElement(1, element);
}

    const Name& GetMatched() const
    {
        return static_cast<const Name&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_NAME_ERROR_H_)

