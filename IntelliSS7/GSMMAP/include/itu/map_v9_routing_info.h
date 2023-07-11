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


#if !defined(_MAP_V9_ROUTING_INFO_H_)
#define _MAP_V9_ROUTING_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnOctetString.h>
#include <AsnSequence.h>

#include <map_v9_isdn_address_string.h>
#include <map_v9_forwarding_data.h>



namespace map_v9 {



class RoutingInfo : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::ISDN_AddressString ISDN_AddressString;


        typedef map_v9::ForwardingData ForwardingData;


////////// End Nested Class(es) //////////

    RoutingInfo() : its::AsnChoice(false)
    {
        Initialize();
    }

    RoutingInfo(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    RoutingInfo(const RoutingInfo& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    RoutingInfo(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    RoutingInfo(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetRoamingNumberStaticDescription();
    static its::AsnDescObject* GetForwardingDataStaticDescription();

public:

    virtual ~RoutingInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RoutingInfo(*this);
    }

    virtual std::string GetName() const
    { return "RoutingInfo"; }

    void SetChoiceRoamingNumber(ISDN_AddressString* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetRoamingNumberStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceRoamingNumber(const ISDN_AddressString& choice)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(choice);
        asnObject.SetDescription(GetRoamingNumberStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceRoamingNumber() const
    {
        return Contains(GetRoamingNumberStaticDescription()->TagIdentity());
    }

    const ISDN_AddressString& GetChoiceRoamingNumber() const
    {
        ITS_REQUIRE(ChoiceRoamingNumber());
        return static_cast<const ISDN_AddressString&> (GetChoice());
    }

    void SetChoiceForwardingData(ForwardingData* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetForwardingDataStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceForwardingData(const ForwardingData& choice)
    {
        its::AsnObject& asnObject = const_cast<ForwardingData&>(choice);
        asnObject.SetDescription(GetForwardingDataStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceForwardingData() const
    {
        return Contains(GetForwardingDataStaticDescription()->TagIdentity());
    }

    const ForwardingData& GetChoiceForwardingData() const
    {
        ITS_REQUIRE(ChoiceForwardingData());
        return static_cast<const ForwardingData&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_ROUTING_INFO_H_)

