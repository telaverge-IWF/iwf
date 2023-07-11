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


#if !defined(_MAP_V13_SUBSCRIBER_IDENTITY_H_)
#define _MAP_V13_SUBSCRIBER_IDENTITY_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnOctetString.h>

#include <map_v13_imsi.h>
#include <map_v13_isdn_address_string.h>



namespace map_v13 {



class SubscriberIdentity : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::IMSI IMSI;


        typedef map_v13::ISDN_AddressString ISDN_AddressString;


////////// End Nested Class(es) //////////

    SubscriberIdentity() : its::AsnChoice(false)
    {
        Initialize();
    }

    SubscriberIdentity(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    SubscriberIdentity(const SubscriberIdentity& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    SubscriberIdentity(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    SubscriberIdentity(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetMsisdnStaticDescription();

public:

    virtual ~SubscriberIdentity()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SubscriberIdentity(*this);
    }

    virtual std::string GetName() const
    { return "SubscriberIdentity"; }

    void SetChoiceImsi(IMSI* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetImsiStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceImsi(const IMSI& choice)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(choice);
        asnObject.SetDescription(GetImsiStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceImsi() const
    {
        return Contains(GetImsiStaticDescription()->TagIdentity());
    }

    const IMSI& GetChoiceImsi() const
    {
        ITS_REQUIRE(ChoiceImsi());
        return static_cast<const IMSI&> (GetChoice());
    }

    void SetChoiceMsisdn(ISDN_AddressString* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetMsisdnStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceMsisdn(const ISDN_AddressString& choice)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(choice);
        asnObject.SetDescription(GetMsisdnStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceMsisdn() const
    {
        return Contains(GetMsisdnStaticDescription()->TagIdentity());
    }

    const ISDN_AddressString& GetChoiceMsisdn() const
    {
        ITS_REQUIRE(ChoiceMsisdn());
        return static_cast<const ISDN_AddressString&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_SUBSCRIBER_IDENTITY_H_)

