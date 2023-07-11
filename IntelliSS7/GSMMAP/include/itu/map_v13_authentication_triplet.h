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


#if !defined(_MAP_V13_AUTHENTICATION_TRIPLET_H_)
#define _MAP_V13_AUTHENTICATION_TRIPLET_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v13_rand.h>
#include <map_v13_sres.h>
#include <map_v13_kc.h>



namespace map_v13 {



class AuthenticationTriplet : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::RAND RAND;


        typedef map_v13::SRES SRES;


        typedef map_v13::Kc Kc;


////////// End Nested Class(es) //////////

    AuthenticationTriplet() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    AuthenticationTriplet(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    AuthenticationTriplet(const AuthenticationTriplet& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    AuthenticationTriplet(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetRandStaticDescription();
    static its::AsnDescObject* GetSresStaticDescription();
    static its::AsnDescObject* GetKcStaticDescription();

public:

    virtual ~AuthenticationTriplet()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AuthenticationTriplet(*this);
    }

    virtual std::string GetName() const
    { return "AuthenticationTriplet"; }

    void SetRand(RAND* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRandStaticDescription());
        AddElement(0, element);
    }

    void SetRand(const RAND& element)
    {
        its::AsnObject& asnObject = const_cast<RAND&>(element);
        asnObject.SetDescription(GetRandStaticDescription());
        AddElement(0, element);
    }

    const RAND& GetRand() const
    {
        return static_cast<const RAND&> (ElementAt(0));
    }

    void SetSres(SRES* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSresStaticDescription());
        AddElement(1, element);
    }

    void SetSres(const SRES& element)
    {
        its::AsnObject& asnObject = const_cast<SRES&>(element);
        asnObject.SetDescription(GetSresStaticDescription());
        AddElement(1, element);
    }

    const SRES& GetSres() const
    {
        return static_cast<const SRES&> (ElementAt(1));
    }

    void SetKc(Kc* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetKcStaticDescription());
        AddElement(2, element);
    }

    void SetKc(const Kc& element)
    {
        its::AsnObject& asnObject = const_cast<Kc&>(element);
        asnObject.SetDescription(GetKcStaticDescription());
        AddElement(2, element);
    }

    const Kc& GetKc() const
    {
        return static_cast<const Kc&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_AUTHENTICATION_TRIPLET_H_)

