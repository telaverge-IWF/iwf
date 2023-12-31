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


#if !defined(_MAP_V2_UPDATE_LOCATION_RES_H_)
#define _MAP_V2_UPDATE_LOCATION_RES_H_

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

#include <map_v2_isdn_address_string.h>
#include <map_v2_extensible_update_location_res.h>



namespace map_v2 {



class UpdateLocationRes : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v2::ISDN_AddressString ISDN_AddressString;


        typedef map_v2::ExtensibleUpdateLocationRes ExtensibleUpdateLocationRes;


////////// End Nested Class(es) //////////

    UpdateLocationRes() : its::AsnChoice(false)
    {
        Initialize();
    }

    UpdateLocationRes(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    UpdateLocationRes(const UpdateLocationRes& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    UpdateLocationRes(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    UpdateLocationRes(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetHlr_NumberStaticDescription();
    static its::AsnDescObject* GetExtensibleUpdateLocationResStaticDescription();

public:

    virtual ~UpdateLocationRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new UpdateLocationRes(*this);
    }

    virtual std::string GetName() const
    { return "UpdateLocationRes"; }

    void SetChoiceHlr_Number(ISDN_AddressString* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetHlr_NumberStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceHlr_Number(const ISDN_AddressString& choice)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(choice);
        asnObject.SetDescription(GetHlr_NumberStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceHlr_Number() const
    {
        return Contains(GetHlr_NumberStaticDescription()->TagIdentity());
    }

    const ISDN_AddressString& GetChoiceHlr_Number() const
    {
        ITS_REQUIRE(ChoiceHlr_Number());
        return static_cast<const ISDN_AddressString&> (GetChoice());
    }

    void SetChoiceExtensibleUpdateLocationRes(ExtensibleUpdateLocationRes* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetExtensibleUpdateLocationResStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceExtensibleUpdateLocationRes(const ExtensibleUpdateLocationRes& choice)
    {
        its::AsnObject& asnObject = const_cast<ExtensibleUpdateLocationRes&>(choice);
        asnObject.SetDescription(GetExtensibleUpdateLocationResStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceExtensibleUpdateLocationRes() const
    {
        return Contains(GetExtensibleUpdateLocationResStaticDescription()->TagIdentity());
    }

    const ExtensibleUpdateLocationRes& GetChoiceExtensibleUpdateLocationRes() const
    {
        ITS_REQUIRE(ChoiceExtensibleUpdateLocationRes());
        return static_cast<const ExtensibleUpdateLocationRes&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V2_UPDATE_LOCATION_RES_H_)

