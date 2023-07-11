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


#if !defined(_MAP_V9_SECURE_TRANSPORT_RES_H_)
#define _MAP_V9_SECURE_TRANSPORT_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v9_security_header.h>
#include <map_v9_protected_payload.h>



namespace map_v9 {



class SecureTransportRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::SecurityHeader SecurityHeader;


        typedef map_v9::ProtectedPayload ProtectedPayload;


////////// End Nested Class(es) //////////

    SecureTransportRes() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    SecureTransportRes(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    SecureTransportRes(const SecureTransportRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SecureTransportRes(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetSecurityHeaderStaticDescription();
    static its::AsnDescObject* GetProtectedPayloadStaticDescription();

public:

    virtual ~SecureTransportRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SecureTransportRes(*this);
    }

    virtual std::string GetName() const
    { return "SecureTransportRes"; }

    void SetSecurityHeader(SecurityHeader* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSecurityHeaderStaticDescription());
        AddElement(0, element);
    }

    void SetSecurityHeader(const SecurityHeader& element)
    {
        its::AsnObject& asnObject = const_cast<SecurityHeader&>(element);
        asnObject.SetDescription(GetSecurityHeaderStaticDescription());
        AddElement(0, element);
    }

    const SecurityHeader& GetSecurityHeader() const
    {
        return static_cast<const SecurityHeader&> (ElementAt(0));
    }

    void SetProtectedPayload(ProtectedPayload* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetProtectedPayloadStaticDescription());
        AddElement(1, element);
    }

    void SetProtectedPayload(const ProtectedPayload& element)
    {
        its::AsnObject& asnObject = const_cast<ProtectedPayload&>(element);
        asnObject.SetDescription(GetProtectedPayloadStaticDescription());
        AddElement(1, element);
    }

    bool OptionProtectedPayload() const
    {
        return Contains(1);
    }

    const ProtectedPayload& GetProtectedPayload() const
    {
        ITS_REQUIRE(OptionProtectedPayload());
        return static_cast<const ProtectedPayload&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_SECURE_TRANSPORT_RES_H_)
