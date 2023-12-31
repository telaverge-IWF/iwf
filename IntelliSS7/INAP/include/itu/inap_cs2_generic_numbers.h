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


#if !defined(_INAP_CS2_GENERIC_NUMBERS_H_)
#define _INAP_CS2_GENERIC_NUMBERS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSetOf.h>
#include <AsnOctetString.h>

#include <inap_cs2_generic_number.h>



namespace inap_cs2 {



class GenericNumbers : public its::AsnSetOf
{
public:


////////// Begin Nested Class //////////


        typedef inap_cs2::GenericNumber GenericNumber;


////////// End Nested Class //////////

    GenericNumbers() : its::AsnSetOf(false)
    {
        Initialize();
    }

    GenericNumbers(its::Octets& octets) : its::AsnSetOf(false)
    {
        Initialize();
        Decode(octets);
    }

    GenericNumbers(const GenericNumbers& rhs) : its::AsnSetOf(rhs)
    {
        // Nothing to do.
    }

    GenericNumbers(its::AsnDescObject* description) : its::AsnSetOf(description)
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

    static its::AsnDescObject* GetGenericNumberStaticDescription();

public:

    virtual ~GenericNumbers()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new GenericNumbers(*this);
    }

    virtual std::string GetName() const
    { return "GenericNumbers"; }

    void AddElement(GenericNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGenericNumberStaticDescription());
        AsnSetOf::AddElement(element);
    }

    void AddElement(const GenericNumber& element)
    {
        its::AsnObject& asnObject = const_cast<GenericNumber&>(element);
        asnObject.SetDescription(GetGenericNumberStaticDescription());
        AsnSetOf::AddElement(element);
    }

    const GenericNumber& ElementAt(int index) const
    {
        return static_cast<const GenericNumber&> (AsnSetOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_GENERIC_NUMBERS_H_)

