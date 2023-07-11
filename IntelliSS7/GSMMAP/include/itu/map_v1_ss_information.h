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


#if !defined(_MAP_V1_SS_INFORMATION_H_)
#define _MAP_V1_SS_INFORMATION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnSequence.h>

#include <map_v1_forwarding_info.h>
#include <map_v1_call_barring_info.h>
#include <map_v1_cug_information.h>
#include <map_v1_ss_data.h>



namespace map_v1 {



class SS_Information : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v1::ForwardingInfo ForwardingInfo;


        typedef map_v1::CallBarringInfo CallBarringInfo;


        typedef map_v1::CUG_Information CUG_Information;


        typedef map_v1::SS_Data SS_Data;


////////// End Nested Class(es) //////////

    SS_Information() : its::AsnChoice(false)
    {
        Initialize();
    }

    SS_Information(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    SS_Information(const SS_Information& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    SS_Information(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    SS_Information(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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
    static its::AsnDescObject* GetCug_InformationStaticDescription();
    static its::AsnDescObject* GetSs_DataStaticDescription();

public:

    virtual ~SS_Information()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SS_Information(*this);
    }

    virtual std::string GetName() const
    { return "SS_Information"; }

    void SetChoiceForwardingInfo(ForwardingInfo* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetForwardingInfoStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceForwardingInfo(const ForwardingInfo& choice)
    {
        its::AsnObject& asnObject = const_cast<ForwardingInfo&>(choice);
        asnObject.SetDescription(GetForwardingInfoStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceForwardingInfo() const
    {
        return Contains(GetForwardingInfoStaticDescription()->TagIdentity());
    }

    const ForwardingInfo& GetChoiceForwardingInfo() const
    {
        ITS_REQUIRE(ChoiceForwardingInfo());
        return static_cast<const ForwardingInfo&> (GetChoice());
    }

    void SetChoiceCallBarringInfo(CallBarringInfo* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetCallBarringInfoStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceCallBarringInfo(const CallBarringInfo& choice)
    {
        its::AsnObject& asnObject = const_cast<CallBarringInfo&>(choice);
        asnObject.SetDescription(GetCallBarringInfoStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceCallBarringInfo() const
    {
        return Contains(GetCallBarringInfoStaticDescription()->TagIdentity());
    }

    const CallBarringInfo& GetChoiceCallBarringInfo() const
    {
        ITS_REQUIRE(ChoiceCallBarringInfo());
        return static_cast<const CallBarringInfo&> (GetChoice());
    }

    void SetChoiceCug_Information(CUG_Information* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetCug_InformationStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceCug_Information(const CUG_Information& choice)
    {
        its::AsnObject& asnObject = const_cast<CUG_Information&>(choice);
        asnObject.SetDescription(GetCug_InformationStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceCug_Information() const
    {
        return Contains(GetCug_InformationStaticDescription()->TagIdentity());
    }

    const CUG_Information& GetChoiceCug_Information() const
    {
        ITS_REQUIRE(ChoiceCug_Information());
        return static_cast<const CUG_Information&> (GetChoice());
    }

    void SetChoiceSs_Data(SS_Data* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetSs_DataStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceSs_Data(const SS_Data& choice)
    {
        its::AsnObject& asnObject = const_cast<SS_Data&>(choice);
        asnObject.SetDescription(GetSs_DataStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceSs_Data() const
    {
        return Contains(GetSs_DataStaticDescription()->TagIdentity());
    }

    const SS_Data& GetChoiceSs_Data() const
    {
        ITS_REQUIRE(ChoiceSs_Data());
        return static_cast<const SS_Data&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V1_SS_INFORMATION_H_)

