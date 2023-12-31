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


#if !defined(_MAP_V9_LSA_IDENTITY_LIST_H_)
#define _MAP_V9_LSA_IDENTITY_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnOctetString.h>

#include <map_v9_lsa_identity.h>



namespace map_v9 {



class LSAIdentityList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v9::LSAIdentity LSAIdentity;


////////// End Nested Class //////////

    LSAIdentityList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    LSAIdentityList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    LSAIdentityList(const LSAIdentityList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    LSAIdentityList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetLSAIdentityStaticDescription();

public:

    virtual ~LSAIdentityList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new LSAIdentityList(*this);
    }

    virtual std::string GetName() const
    { return "LSAIdentityList"; }

    void AddElement(LSAIdentity* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLSAIdentityStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const LSAIdentity& element)
    {
        its::AsnObject& asnObject = const_cast<LSAIdentity&>(element);
        asnObject.SetDescription(GetLSAIdentityStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const LSAIdentity& ElementAt(int index) const
    {
        return static_cast<const LSAIdentity&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_LSA_IDENTITY_LIST_H_)

