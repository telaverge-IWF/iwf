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


#if !defined(_MAP_V9_CURRENT_SECURITY_CONTEXT_H_)
#define _MAP_V9_CURRENT_SECURITY_CONTEXT_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnSequence.h>

#include <map_v9_gsm_security_context_data.h>
#include <map_v9_umts_security_context_data.h>



namespace map_v9 {



class CurrentSecurityContext : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::GSM_SecurityContextData GSM_SecurityContextData;


        typedef map_v9::UMTS_SecurityContextData UMTS_SecurityContextData;


////////// End Nested Class(es) //////////

    CurrentSecurityContext() : its::AsnChoice(false)
    {
        Initialize();
    }

    CurrentSecurityContext(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    CurrentSecurityContext(const CurrentSecurityContext& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    CurrentSecurityContext(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    CurrentSecurityContext(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetGsm_SecurityContextDataStaticDescription();
    static its::AsnDescObject* GetUmts_SecurityContextDataStaticDescription();

public:

    virtual ~CurrentSecurityContext()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CurrentSecurityContext(*this);
    }

    virtual std::string GetName() const
    { return "CurrentSecurityContext"; }

    void SetChoiceGsm_SecurityContextData(GSM_SecurityContextData* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetGsm_SecurityContextDataStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceGsm_SecurityContextData(const GSM_SecurityContextData& choice)
    {
        its::AsnObject& asnObject = const_cast<GSM_SecurityContextData&>(choice);
        asnObject.SetDescription(GetGsm_SecurityContextDataStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceGsm_SecurityContextData() const
    {
        return Contains(GetGsm_SecurityContextDataStaticDescription()->TagIdentity());
    }

    const GSM_SecurityContextData& GetChoiceGsm_SecurityContextData() const
    {
        ITS_REQUIRE(ChoiceGsm_SecurityContextData());
        return static_cast<const GSM_SecurityContextData&> (GetChoice());
    }

    void SetChoiceUmts_SecurityContextData(UMTS_SecurityContextData* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetUmts_SecurityContextDataStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceUmts_SecurityContextData(const UMTS_SecurityContextData& choice)
    {
        its::AsnObject& asnObject = const_cast<UMTS_SecurityContextData&>(choice);
        asnObject.SetDescription(GetUmts_SecurityContextDataStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceUmts_SecurityContextData() const
    {
        return Contains(GetUmts_SecurityContextDataStaticDescription()->TagIdentity());
    }

    const UMTS_SecurityContextData& GetChoiceUmts_SecurityContextData() const
    {
        ITS_REQUIRE(ChoiceUmts_SecurityContextData());
        return static_cast<const UMTS_SecurityContextData&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_CURRENT_SECURITY_CONTEXT_H_)
