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


#if !defined(_INAP_CS2_RDN_SEQUENCE_H_)
#define _INAP_CS2_RDN_SEQUENCE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <inap_cs2_relative_distinguished_name.h>



namespace inap_cs2 {



class RDNSequence : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef inap_cs2::RelativeDistinguishedName RelativeDistinguishedName;


////////// End Nested Class //////////

    RDNSequence() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    RDNSequence(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    RDNSequence(const RDNSequence& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    RDNSequence(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetRelativeDistinguishedNameStaticDescription();

public:

    virtual ~RDNSequence()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RDNSequence(*this);
    }

    virtual std::string GetName() const
    { return "RDNSequence"; }

    void AddElement(RelativeDistinguishedName* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRelativeDistinguishedNameStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const RelativeDistinguishedName& element)
    {
        its::AsnObject& asnObject = const_cast<RelativeDistinguishedName&>(element);
        asnObject.SetDescription(GetRelativeDistinguishedNameStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const RelativeDistinguishedName& ElementAt(int index) const
    {
        return static_cast<const RelativeDistinguishedName&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_RDN_SEQUENCE_H_)

