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


#if !defined(_INAP_CS2_RECEIVED_INFORMATION_H_)
#define _INAP_CS2_RECEIVED_INFORMATION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnBaseString.h>

#include <IA5String.h>



namespace inap_cs2 {



class ReceivedInformation : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


    typedef its::IA5String IA5String;


////////// End Nested Class //////////

    ReceivedInformation() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    ReceivedInformation(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    ReceivedInformation(const ReceivedInformation& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    ReceivedInformation(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetIA5StringStaticDescription();

public:

    virtual ~ReceivedInformation()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ReceivedInformation(*this);
    }

    virtual std::string GetName() const
    { return "ReceivedInformation"; }

    void AddElement(IA5String* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIA5StringStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const IA5String& element)
    {
        its::AsnObject& asnObject = const_cast<IA5String&>(element);
        asnObject.SetDescription(GetIA5StringStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const IA5String& ElementAt(int index) const
    {
        return static_cast<const IA5String&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_RECEIVED_INFORMATION_H_)

