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


#if !defined(_MAP_V1_SM_RP_OA_H_)
#define _MAP_V1_SM_RP_OA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnOctetString.h>

#include <map_v1_isdn_address_string.h>
#include <map_v1_address_string.h>



namespace map_v1 {



class SM_RP_OA : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v1::ISDN_AddressString ISDN_AddressString;


        typedef map_v1::AddressString AddressString;


////////// End Nested Class(es) //////////

    SM_RP_OA() : its::AsnChoice(false)
    {
        Initialize();
    }

    SM_RP_OA(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    SM_RP_OA(const SM_RP_OA& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    SM_RP_OA(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    SM_RP_OA(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    virtual ~SM_RP_OA()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SM_RP_OA(*this);
    }

    virtual std::string GetName() const
    { return "SM_RP_OA"; }

    void SetChoiceMsIsdn(ISDN_AddressString* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetMsIsdnStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceMsIsdn(const ISDN_AddressString& choice)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(choice);
        asnObject.SetDescription(GetMsIsdnStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceMsIsdn() const
    {
        return Contains(GetMsIsdnStaticDescription()->TagIdentity());
    }

    const ISDN_AddressString& GetChoiceMsIsdn() const
    {
        ITS_REQUIRE(ChoiceMsIsdn());
        return static_cast<const ISDN_AddressString&> (GetChoice());
    }

    void SetChoiceServiceCenterAddress(AddressString* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetServiceCenterAddressStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceServiceCenterAddress(const AddressString& choice)
    {
        its::AsnObject& asnObject = const_cast<AddressString&>(choice);
        asnObject.SetDescription(GetServiceCenterAddressStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceServiceCenterAddress() const
    {
        return Contains(GetServiceCenterAddressStaticDescription()->TagIdentity());
    }

    const AddressString& GetChoiceServiceCenterAddress() const
    {
        ITS_REQUIRE(ChoiceServiceCenterAddress());
        return static_cast<const AddressString&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V1_SM_RP_OA_H_)

