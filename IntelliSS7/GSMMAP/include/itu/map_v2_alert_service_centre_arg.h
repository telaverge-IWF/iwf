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


#if !defined(_MAP_V2_ALERT_SERVICE_CENTRE_ARG_H_)
#define _MAP_V2_ALERT_SERVICE_CENTRE_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v2_isdn_address_string.h>
#include <map_v2_address_string.h>



namespace map_v2 {



class AlertServiceCentreArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v2::ISDN_AddressString ISDN_AddressString;


        typedef map_v2::AddressString AddressString;


////////// End Nested Class(es) //////////

    AlertServiceCentreArg() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    AlertServiceCentreArg(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    AlertServiceCentreArg(const AlertServiceCentreArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    AlertServiceCentreArg(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetMsisdnStaticDescription();
    static its::AsnDescObject* GetServiceCentreAddressStaticDescription();

public:

    virtual ~AlertServiceCentreArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AlertServiceCentreArg(*this);
    }

    virtual std::string GetName() const
    { return "AlertServiceCentreArg"; }

    void SetMsisdn(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMsisdnStaticDescription());
        AddElement(0, element);
    }

    void SetMsisdn(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetMsisdnStaticDescription());
        AddElement(0, element);
    }

    const ISDN_AddressString& GetMsisdn() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
    }

    void SetServiceCentreAddress(AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetServiceCentreAddressStaticDescription());
        AddElement(1, element);
    }

    void SetServiceCentreAddress(const AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<AddressString&>(element);
        asnObject.SetDescription(GetServiceCentreAddressStaticDescription());
        AddElement(1, element);
    }

    const AddressString& GetServiceCentreAddress() const
    {
        return static_cast<const AddressString&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V2_ALERT_SERVICE_CENTRE_ARG_H_)

