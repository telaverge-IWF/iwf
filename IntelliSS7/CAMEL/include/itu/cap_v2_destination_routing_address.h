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


#if !defined(_CAP_V2_DESTINATION_ROUTING_ADDRESS_H_)
#define _CAP_V2_DESTINATION_ROUTING_ADDRESS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnOctetString.h>

#include <cap_v2_called_party_number.h>



namespace cap_v2 {



class DestinationRoutingAddress : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef cap_v2::CalledPartyNumber CalledPartyNumber;


////////// End Nested Class //////////

    DestinationRoutingAddress() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    DestinationRoutingAddress(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    DestinationRoutingAddress(const DestinationRoutingAddress& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    DestinationRoutingAddress(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetCalledPartyNumberStaticDescription();

public:

    virtual ~DestinationRoutingAddress()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new DestinationRoutingAddress(*this);
    }

    virtual std::string GetName() const
    { return "DestinationRoutingAddress"; }

    void AddElement(CalledPartyNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCalledPartyNumberStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const CalledPartyNumber& element)
    {
        its::AsnObject& asnObject = const_cast<CalledPartyNumber&>(element);
        asnObject.SetDescription(GetCalledPartyNumberStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const CalledPartyNumber& ElementAt(int index) const
    {
        return static_cast<const CalledPartyNumber&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_CAP_V2_DESTINATION_ROUTING_ADDRESS_H_)

