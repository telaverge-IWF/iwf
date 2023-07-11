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


#if !defined(_MAP_V3_EXT_SS_INFO_H_)
#define _MAP_V3_EXT_SS_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnSequence.h>

#include <map_v3_ext_forw_info.h>
#include <map_v3_ext_call_bar_info.h>
#include <map_v3_cug_info.h>
#include <map_v3_ext_ss_data.h>
#include <map_v3_emlpp_info.h>



namespace map_v3 {



class Ext_SS_Info : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::Ext_ForwInfo Ext_ForwInfo;


        typedef map_v3::Ext_CallBarInfo Ext_CallBarInfo;


        typedef map_v3::CUG_Info CUG_Info;


        typedef map_v3::Ext_SS_Data Ext_SS_Data;


        typedef map_v3::EMLPP_Info EMLPP_Info;


////////// End Nested Class(es) //////////

    Ext_SS_Info() : its::AsnChoice(false)
    {
        Initialize();
    }

    Ext_SS_Info(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    Ext_SS_Info(const Ext_SS_Info& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    Ext_SS_Info(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    Ext_SS_Info(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetForwardingInfoStaticDescription();
    static its::AsnDescObject* GetCallBarringInfoStaticDescription();
    static its::AsnDescObject* GetCug_InfoStaticDescription();
    static its::AsnDescObject* GetSs_DataStaticDescription();
    static its::AsnDescObject* GetEmlpp_InfoStaticDescription();

public:

    virtual ~Ext_SS_Info()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Ext_SS_Info(*this);
    }

    virtual std::string GetName() const
    { return "Ext_SS_Info"; }

    void SetChoiceForwardingInfo(Ext_ForwInfo* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetForwardingInfoStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceForwardingInfo(const Ext_ForwInfo& choice)
    {
        its::AsnObject& asnObject = const_cast<Ext_ForwInfo&>(choice);
        asnObject.SetDescription(GetForwardingInfoStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceForwardingInfo() const
    {
        return Contains(GetForwardingInfoStaticDescription()->TagIdentity());
    }

    const Ext_ForwInfo& GetChoiceForwardingInfo() const
    {
        ITS_REQUIRE(ChoiceForwardingInfo());
        return static_cast<const Ext_ForwInfo&> (GetChoice());
    }

    void SetChoiceCallBarringInfo(Ext_CallBarInfo* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetCallBarringInfoStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceCallBarringInfo(const Ext_CallBarInfo& choice)
    {
        its::AsnObject& asnObject = const_cast<Ext_CallBarInfo&>(choice);
        asnObject.SetDescription(GetCallBarringInfoStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceCallBarringInfo() const
    {
        return Contains(GetCallBarringInfoStaticDescription()->TagIdentity());
    }

    const Ext_CallBarInfo& GetChoiceCallBarringInfo() const
    {
        ITS_REQUIRE(ChoiceCallBarringInfo());
        return static_cast<const Ext_CallBarInfo&> (GetChoice());
    }

    void SetChoiceCug_Info(CUG_Info* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetCug_InfoStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceCug_Info(const CUG_Info& choice)
    {
        its::AsnObject& asnObject = const_cast<CUG_Info&>(choice);
        asnObject.SetDescription(GetCug_InfoStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceCug_Info() const
    {
        return Contains(GetCug_InfoStaticDescription()->TagIdentity());
    }

    const CUG_Info& GetChoiceCug_Info() const
    {
        ITS_REQUIRE(ChoiceCug_Info());
        return static_cast<const CUG_Info&> (GetChoice());
    }

    void SetChoiceSs_Data(Ext_SS_Data* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetSs_DataStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceSs_Data(const Ext_SS_Data& choice)
    {
        its::AsnObject& asnObject = const_cast<Ext_SS_Data&>(choice);
        asnObject.SetDescription(GetSs_DataStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceSs_Data() const
    {
        return Contains(GetSs_DataStaticDescription()->TagIdentity());
    }

    const Ext_SS_Data& GetChoiceSs_Data() const
    {
        ITS_REQUIRE(ChoiceSs_Data());
        return static_cast<const Ext_SS_Data&> (GetChoice());
    }

    void SetChoiceEmlpp_Info(EMLPP_Info* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetEmlpp_InfoStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceEmlpp_Info(const EMLPP_Info& choice)
    {
        its::AsnObject& asnObject = const_cast<EMLPP_Info&>(choice);
        asnObject.SetDescription(GetEmlpp_InfoStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceEmlpp_Info() const
    {
        return Contains(GetEmlpp_InfoStaticDescription()->TagIdentity());
    }

    const EMLPP_Info& GetChoiceEmlpp_Info() const
    {
        ITS_REQUIRE(ChoiceEmlpp_Info());
        return static_cast<const EMLPP_Info&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_EXT_SS_INFO_H_)
