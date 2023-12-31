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


#if !defined(_MAP_V9_AUTHENTICATION_QUINTUPLET_H_)
#define _MAP_V9_AUTHENTICATION_QUINTUPLET_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v9_rand.h>
#include <map_v9_xres.h>
#include <map_v9_ck.h>
#include <map_v9_ik.h>
#include <map_v9_autn.h>



namespace map_v9 {



class AuthenticationQuintuplet : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::RAND RAND;


        typedef map_v9::XRES XRES;


        typedef map_v9::CK CK;


        typedef map_v9::IK IK;


        typedef map_v9::AUTN AUTN;


////////// End Nested Class(es) //////////

    AuthenticationQuintuplet() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    AuthenticationQuintuplet(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    AuthenticationQuintuplet(const AuthenticationQuintuplet& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    AuthenticationQuintuplet(its::AsnDescObject* description) : its::AsnSequence(5, description)
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
    static its::AsnDescObject* GetXresStaticDescription();
    static its::AsnDescObject* GetCkStaticDescription();
    static its::AsnDescObject* GetIkStaticDescription();
    static its::AsnDescObject* GetAutnStaticDescription();

public:

    virtual ~AuthenticationQuintuplet()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AuthenticationQuintuplet(*this);
    }

    virtual std::string GetName() const
    { return "AuthenticationQuintuplet"; }

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

    void SetXres(XRES* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetXresStaticDescription());
        AddElement(1, element);
    }

    void SetXres(const XRES& element)
    {
        its::AsnObject& asnObject = const_cast<XRES&>(element);
        asnObject.SetDescription(GetXresStaticDescription());
        AddElement(1, element);
    }

    const XRES& GetXres() const
    {
        return static_cast<const XRES&> (ElementAt(1));
    }

    void SetCk(CK* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCkStaticDescription());
        AddElement(2, element);
    }

    void SetCk(const CK& element)
    {
        its::AsnObject& asnObject = const_cast<CK&>(element);
        asnObject.SetDescription(GetCkStaticDescription());
        AddElement(2, element);
    }

    const CK& GetCk() const
    {
        return static_cast<const CK&> (ElementAt(2));
    }

    void SetIk(IK* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIkStaticDescription());
        AddElement(3, element);
    }

    void SetIk(const IK& element)
    {
        its::AsnObject& asnObject = const_cast<IK&>(element);
        asnObject.SetDescription(GetIkStaticDescription());
        AddElement(3, element);
    }

    const IK& GetIk() const
    {
        return static_cast<const IK&> (ElementAt(3));
    }

    void SetAutn(AUTN* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAutnStaticDescription());
        AddElement(4, element);
    }

    void SetAutn(const AUTN& element)
    {
        its::AsnObject& asnObject = const_cast<AUTN&>(element);
        asnObject.SetDescription(GetAutnStaticDescription());
        AddElement(4, element);
    }

    const AUTN& GetAutn() const
    {
        return static_cast<const AUTN&> (ElementAt(4));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_AUTHENTICATION_QUINTUPLET_H_)

