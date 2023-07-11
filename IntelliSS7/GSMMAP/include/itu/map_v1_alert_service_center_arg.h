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


#if !defined(_MAP_V1_ALERT_SERVICE_CENTER_ARG_H_)
#define _MAP_V1_ALERT_SERVICE_CENTER_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v1_isdn_address_string.h>
#include <map_v1_address_string.h>



namespace map_v1 {



class AlertServiceCenterArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v1::ISDN_AddressString ISDN_AddressString;


        typedef map_v1::AddressString AddressString;


////////// End Nested Class(es) //////////

    AlertServiceCenterArg() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    AlertServiceCenterArg(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    AlertServiceCenterArg(const AlertServiceCenterArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    AlertServiceCenterArg(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetMsIsdnStaticDescription();
    static its::AsnDescObject* GetServiceCenterAddressStaticDescription();

public:

    virtual ~AlertServiceCenterArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AlertServiceCenterArg(*this);
    }

    virtual std::string GetName() const
    { return "AlertServiceCenterArg"; }

    void SetMsIsdn(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMsIsdnStaticDescription());
        AddElement(0, element);
    }

    void SetMsIsdn(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetMsIsdnStaticDescription());
        AddElement(0, element);
    }

    const ISDN_AddressString& GetMsIsdn() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
    }

    void SetServiceCenterAddress(AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetServiceCenterAddressStaticDescription());
        AddElement(1, element);
    }

    void SetServiceCenterAddress(const AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<AddressString&>(element);
        asnObject.SetDescription(GetServiceCenterAddressStaticDescription());
        AddElement(1, element);
    }

    const AddressString& GetServiceCenterAddress() const
    {
        return static_cast<const AddressString&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V1_ALERT_SERVICE_CENTER_ARG_H_)

