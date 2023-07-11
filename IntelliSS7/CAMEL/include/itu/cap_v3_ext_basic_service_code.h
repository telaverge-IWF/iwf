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


#if !defined(_CAP_V3_EXT_BASIC_SERVICE_CODE_H_)
#define _CAP_V3_EXT_BASIC_SERVICE_CODE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnOctetString.h>

#include <cap_v3_ext_bearer_service_code.h>
#include <cap_v3_ext_teleservice_code.h>



namespace cap_v3 {



class Ext_BasicServiceCode : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v3::Ext_BearerServiceCode Ext_BearerServiceCode;


        typedef cap_v3::Ext_TeleserviceCode Ext_TeleserviceCode;


////////// End Nested Class(es) //////////

    Ext_BasicServiceCode() : its::AsnChoice(false)
    {
        Initialize();
    }

    Ext_BasicServiceCode(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    Ext_BasicServiceCode(const Ext_BasicServiceCode& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    Ext_BasicServiceCode(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    Ext_BasicServiceCode(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetExt_BearerServiceStaticDescription();
    static its::AsnDescObject* GetExt_TeleserviceStaticDescription();

public:

    virtual ~Ext_BasicServiceCode()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Ext_BasicServiceCode(*this);
    }

    virtual std::string GetName() const
    { return "Ext_BasicServiceCode"; }

    void SetChoiceExt_BearerService(Ext_BearerServiceCode* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetExt_BearerServiceStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceExt_BearerService(const Ext_BearerServiceCode& choice)
    {
        its::AsnObject& asnObject = const_cast<Ext_BearerServiceCode&>(choice);
        asnObject.SetDescription(GetExt_BearerServiceStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceExt_BearerService() const
    {
        return Contains(GetExt_BearerServiceStaticDescription()->TagIdentity());
    }

    const Ext_BearerServiceCode& GetChoiceExt_BearerService() const
    {
        ITS_REQUIRE(ChoiceExt_BearerService());
        return static_cast<const Ext_BearerServiceCode&> (GetChoice());
    }

    void SetChoiceExt_Teleservice(Ext_TeleserviceCode* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetExt_TeleserviceStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceExt_Teleservice(const Ext_TeleserviceCode& choice)
    {
        its::AsnObject& asnObject = const_cast<Ext_TeleserviceCode&>(choice);
        asnObject.SetDescription(GetExt_TeleserviceStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceExt_Teleservice() const
    {
        return Contains(GetExt_TeleserviceStaticDescription()->TagIdentity());
    }

    const Ext_TeleserviceCode& GetChoiceExt_Teleservice() const
    {
        ITS_REQUIRE(ChoiceExt_Teleservice());
        return static_cast<const Ext_TeleserviceCode&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_EXT_BASIC_SERVICE_CODE_H_)

