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


#if !defined(_CAP_V3_INITIAL_DP_ARG_EXTENSION_H_)
#define _CAP_V3_INITIAL_DP_ARG_EXTENSION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <cap_v3_isdn_address_string.h>



namespace cap_v3 {



class InitialDPArgExtension : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v3::ISDN_AddressString ISDN_AddressString;


////////// End Nested Class(es) //////////

    InitialDPArgExtension() : its::AsnSequence(1, false)
    {
        Initialize();
    }

    InitialDPArgExtension(its::Octets& octets) : its::AsnSequence(1, false)
    {
        Initialize();
        Decode(octets);
    }

    InitialDPArgExtension(const InitialDPArgExtension& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    InitialDPArgExtension(its::AsnDescObject* description) : its::AsnSequence(1, description)
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

    static its::AsnDescObject* GetGmscAddressStaticDescription();

public:

    virtual ~InitialDPArgExtension()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new InitialDPArgExtension(*this);
    }

    virtual std::string GetName() const
    { return "InitialDPArgExtension"; }

    void SetGmscAddress(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGmscAddressStaticDescription());
        AddElement(0, element);
    }

    void SetGmscAddress(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetGmscAddressStaticDescription());
        AddElement(0, element);
    }

    bool OptionGmscAddress() const
    {
        return Contains(0);
    }

    const ISDN_AddressString& GetGmscAddress() const
    {
        ITS_REQUIRE(OptionGmscAddress());
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_INITIAL_DP_ARG_EXTENSION_H_)

