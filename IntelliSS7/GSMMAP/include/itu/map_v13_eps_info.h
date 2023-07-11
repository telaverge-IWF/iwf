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


#if !defined(_MAP_V13_EPS_INFO_H_)
#define _MAP_V13_EPS_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnSequence.h>
#include <AsnBitString.h>

#include <map_v13_pdn_gw_update.h>
#include <map_v13_isr_information.h>



namespace map_v13 {



class EPS_Info : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::PDN_GW_Update PDN_GW_Update;


        typedef map_v13::ISR_Information ISR_Information;


////////// End Nested Class(es) //////////

    EPS_Info() : its::AsnChoice(false)
    {
        Initialize();
    }

    EPS_Info(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    EPS_Info(const EPS_Info& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    EPS_Info(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    EPS_Info(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetPdn_gw_updateStaticDescription();
    static its::AsnDescObject* GetIsr_InformationStaticDescription();

public:

    virtual ~EPS_Info()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new EPS_Info(*this);
    }

    virtual std::string GetName() const
    { return "EPS_Info"; }

    void SetChoicePdn_gw_update(PDN_GW_Update* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetPdn_gw_updateStaticDescription());
        SetChoice(choice);
    }

    void SetChoicePdn_gw_update(const PDN_GW_Update& choice)
    {
        its::AsnObject& asnObject = const_cast<PDN_GW_Update&>(choice);
        asnObject.SetDescription(GetPdn_gw_updateStaticDescription());
        SetChoice(choice);
    }

    bool ChoicePdn_gw_update() const
    {
        return Contains(GetPdn_gw_updateStaticDescription()->TagIdentity());
    }

    const PDN_GW_Update& GetChoicePdn_gw_update() const
    {
        ITS_REQUIRE(ChoicePdn_gw_update());
        return static_cast<const PDN_GW_Update&> (GetChoice());
    }

    void SetChoiceIsr_Information(ISR_Information* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetIsr_InformationStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceIsr_Information(const ISR_Information& choice)
    {
        its::AsnObject& asnObject = const_cast<ISR_Information&>(choice);
        asnObject.SetDescription(GetIsr_InformationStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceIsr_Information() const
    {
        return Contains(GetIsr_InformationStaticDescription()->TagIdentity());
    }

    const ISR_Information& GetChoiceIsr_Information() const
    {
        ITS_REQUIRE(ChoiceIsr_Information());
        return static_cast<const ISR_Information&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_EPS_INFO_H_)

