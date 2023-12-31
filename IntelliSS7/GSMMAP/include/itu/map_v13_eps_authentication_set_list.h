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


#if !defined(_MAP_V13_EPS_AUTHENTICATION_SET_LIST_H_)
#define _MAP_V13_EPS_AUTHENTICATION_SET_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v13_epc_av.h>



namespace map_v13 {



class EPS_AuthenticationSetList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::EPC_AV EPC_AV;


////////// End Nested Class //////////

    EPS_AuthenticationSetList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    EPS_AuthenticationSetList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    EPS_AuthenticationSetList(const EPS_AuthenticationSetList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    EPS_AuthenticationSetList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetEPC_AVStaticDescription();

public:

    virtual ~EPS_AuthenticationSetList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new EPS_AuthenticationSetList(*this);
    }

    virtual std::string GetName() const
    { return "EPS_AuthenticationSetList"; }

    void AddElement(EPC_AV* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEPC_AVStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const EPC_AV& element)
    {
        its::AsnObject& asnObject = const_cast<EPC_AV&>(element);
        asnObject.SetDescription(GetEPC_AVStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const EPC_AV& ElementAt(int index) const
    {
        return static_cast<const EPC_AV&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_EPS_AUTHENTICATION_SET_LIST_H_)

