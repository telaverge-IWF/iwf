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


#if !defined(_MAP_V9_ADDITIONAL_NUMBER_H_)
#define _MAP_V9_ADDITIONAL_NUMBER_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnOctetString.h>

#include <map_v9_isdn_address_string.h>



namespace map_v9 {



class Additional_Number : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::ISDN_AddressString ISDN_AddressString;


////////// End Nested Class(es) //////////

    Additional_Number() : its::AsnChoice(false)
    {
        Initialize();
    }

    Additional_Number(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    Additional_Number(const Additional_Number& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    Additional_Number(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    Additional_Number(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetMsc_NumberStaticDescription();
    static its::AsnDescObject* GetSgsn_NumberStaticDescription();

public:

    virtual ~Additional_Number()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Additional_Number(*this);
    }

    virtual std::string GetName() const
    { return "Additional_Number"; }

    void SetChoiceMsc_Number(ISDN_AddressString* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetMsc_NumberStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceMsc_Number(const ISDN_AddressString& choice)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(choice);
        asnObject.SetDescription(GetMsc_NumberStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceMsc_Number() const
    {
        return Contains(GetMsc_NumberStaticDescription()->TagIdentity());
    }

    const ISDN_AddressString& GetChoiceMsc_Number() const
    {
        ITS_REQUIRE(ChoiceMsc_Number());
        return static_cast<const ISDN_AddressString&> (GetChoice());
    }

    void SetChoiceSgsn_Number(ISDN_AddressString* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetSgsn_NumberStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceSgsn_Number(const ISDN_AddressString& choice)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(choice);
        asnObject.SetDescription(GetSgsn_NumberStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceSgsn_Number() const
    {
        return Contains(GetSgsn_NumberStaticDescription()->TagIdentity());
    }

    const ISDN_AddressString& GetChoiceSgsn_Number() const
    {
        ITS_REQUIRE(ChoiceSgsn_Number());
        return static_cast<const ISDN_AddressString&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_ADDITIONAL_NUMBER_H_)

