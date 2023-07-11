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


#if !defined(_INAP_CS2_INFORMATIONS_H_)
#define _INAP_CS2_INFORMATIONS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSetOf.h>
#include <AsnChoice.h>

#include <inap_cs2_information.h>



namespace inap_cs2 {



class Informations : public its::AsnSetOf
{
public:


////////// Begin Nested Class //////////


        typedef inap_cs2::Information Information;


////////// End Nested Class //////////

    Informations() : its::AsnSetOf(false)
    {
        Initialize();
    }

    Informations(its::Octets& octets) : its::AsnSetOf(false)
    {
        Initialize();
        Decode(octets);
    }

    Informations(const Informations& rhs) : its::AsnSetOf(rhs)
    {
        // Nothing to do.
    }

    Informations(its::AsnDescObject* description) : its::AsnSetOf(description)
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

    static its::AsnDescObject* GetInformationStaticDescription();

public:

    virtual ~Informations()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Informations(*this);
    }

    virtual std::string GetName() const
    { return "Informations"; }

    void AddElement(Information* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetInformationStaticDescription());
        AsnSetOf::AddElement(element);
    }

    void AddElement(const Information& element)
    {
        its::AsnObject& asnObject = const_cast<Information&>(element);
        asnObject.SetDescription(GetInformationStaticDescription());
        AsnSetOf::AddElement(element);
    }

    const Information& ElementAt(int index) const
    {
        return static_cast<const Information&> (AsnSetOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_INFORMATIONS_H_)
