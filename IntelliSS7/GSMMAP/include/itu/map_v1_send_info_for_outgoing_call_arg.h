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


#if !defined(_MAP_V1_SEND_INFO_FOR_OUTGOING_CALL_ARG_H_)
#define _MAP_V1_SEND_INFO_FOR_OUTGOING_CALL_ARG_H_

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
#include <map_v1_bearer_service_code.h>
#include <map_v1_teleservice_code.h>



namespace map_v1 {



class SendInfoForOutgoingCallArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v1::ISDN_AddressString ISDN_AddressString;


        typedef map_v1::BearerServiceCode BearerServiceCode;


        typedef map_v1::TeleserviceCode TeleserviceCode;


////////// End Nested Class(es) //////////

    SendInfoForOutgoingCallArg() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    SendInfoForOutgoingCallArg(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    SendInfoForOutgoingCallArg(const SendInfoForOutgoingCallArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SendInfoForOutgoingCallArg(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetCalledNumberStaticDescription();
    static its::AsnDescObject* GetBearerServiceStaticDescription();
    static its::AsnDescObject* GetTeleserviceStaticDescription();

public:

    virtual ~SendInfoForOutgoingCallArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SendInfoForOutgoingCallArg(*this);
    }

    virtual std::string GetName() const
    { return "SendInfoForOutgoingCallArg"; }

    void SetCalledNumber(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCalledNumberStaticDescription());
        AddElement(0, element);
    }

    void SetCalledNumber(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetCalledNumberStaticDescription());
        AddElement(0, element);
    }

    const ISDN_AddressString& GetCalledNumber() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
    }

    void SetBearerService(BearerServiceCode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBearerServiceStaticDescription());
        AddElement(1, element);
    }

    void SetBearerService(const BearerServiceCode& element)
    {
        its::AsnObject& asnObject = const_cast<BearerServiceCode&>(element);
        asnObject.SetDescription(GetBearerServiceStaticDescription());
        AddElement(1, element);
    }

    bool OptionBearerService() const
    {
        return Contains(1);
    }

    const BearerServiceCode& GetBearerService() const
    {
        ITS_REQUIRE(OptionBearerService());
        return static_cast<const BearerServiceCode&> (ElementAt(1));
    }

    void SetTeleservice(TeleserviceCode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTeleserviceStaticDescription());
        AddElement(2, element);
    }

    void SetTeleservice(const TeleserviceCode& element)
    {
        its::AsnObject& asnObject = const_cast<TeleserviceCode&>(element);
        asnObject.SetDescription(GetTeleserviceStaticDescription());
        AddElement(2, element);
    }

    bool OptionTeleservice() const
    {
        return Contains(2);
    }

    const TeleserviceCode& GetTeleservice() const
    {
        ITS_REQUIRE(OptionTeleservice());
        return static_cast<const TeleserviceCode&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V1_SEND_INFO_FOR_OUTGOING_CALL_ARG_H_)

