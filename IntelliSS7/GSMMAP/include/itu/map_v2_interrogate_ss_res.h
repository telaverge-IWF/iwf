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


#if !defined(_MAP_V2_INTERROGATE_SS_RES_H_)
#define _MAP_V2_INTERROGATE_SS_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnOctetString.h>
#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v2_ss_status.h>
#include <map_v2_isdn_address_string.h>
#include <map_v2_basic_service_group_list.h>
#include <map_v2_forwarding_feature_list.h>
#include <map_v2_cli_restriction_info.h>



namespace map_v2 {



class InterrogateSS_Res : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v2::SS_Status SS_Status;


        typedef map_v2::ISDN_AddressString ISDN_AddressString;


        typedef map_v2::BasicServiceGroupList BasicServiceGroupList;


        typedef map_v2::ForwardingFeatureList ForwardingFeatureList;


        typedef map_v2::Cli_RestrictionInfo Cli_RestrictionInfo;


////////// End Nested Class(es) //////////

    InterrogateSS_Res() : its::AsnChoice(false)
    {
        Initialize();
    }

    InterrogateSS_Res(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    InterrogateSS_Res(const InterrogateSS_Res& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    InterrogateSS_Res(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    InterrogateSS_Res(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetSs_StatusStaticDescription();
    static its::AsnDescObject* GetForwardedToNumberStaticDescription();
    static its::AsnDescObject* GetBasicServiceGroupListStaticDescription();
    static its::AsnDescObject* GetForwardingFeatureListStaticDescription();
    static its::AsnDescObject* GetCli_RestrictionInfoStaticDescription();

public:

    virtual ~InterrogateSS_Res()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new InterrogateSS_Res(*this);
    }

    virtual std::string GetName() const
    { return "InterrogateSS_Res"; }

    void SetChoiceSs_Status(SS_Status* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetSs_StatusStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceSs_Status(const SS_Status& choice)
    {
        its::AsnObject& asnObject = const_cast<SS_Status&>(choice);
        asnObject.SetDescription(GetSs_StatusStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceSs_Status() const
    {
        return Contains(GetSs_StatusStaticDescription()->TagIdentity());
    }

    const SS_Status& GetChoiceSs_Status() const
    {
        ITS_REQUIRE(ChoiceSs_Status());
        return static_cast<const SS_Status&> (GetChoice());
    }

    void SetChoiceForwardedToNumber(ISDN_AddressString* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetForwardedToNumberStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceForwardedToNumber(const ISDN_AddressString& choice)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(choice);
        asnObject.SetDescription(GetForwardedToNumberStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceForwardedToNumber() const
    {
        return Contains(GetForwardedToNumberStaticDescription()->TagIdentity());
    }

    const ISDN_AddressString& GetChoiceForwardedToNumber() const
    {
        ITS_REQUIRE(ChoiceForwardedToNumber());
        return static_cast<const ISDN_AddressString&> (GetChoice());
    }

    void SetChoiceBasicServiceGroupList(BasicServiceGroupList* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetBasicServiceGroupListStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceBasicServiceGroupList(const BasicServiceGroupList& choice)
    {
        its::AsnObject& asnObject = const_cast<BasicServiceGroupList&>(choice);
        asnObject.SetDescription(GetBasicServiceGroupListStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceBasicServiceGroupList() const
    {
        return Contains(GetBasicServiceGroupListStaticDescription()->TagIdentity());
    }

    const BasicServiceGroupList& GetChoiceBasicServiceGroupList() const
    {
        ITS_REQUIRE(ChoiceBasicServiceGroupList());
        return static_cast<const BasicServiceGroupList&> (GetChoice());
    }

    void SetChoiceForwardingFeatureList(ForwardingFeatureList* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetForwardingFeatureListStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceForwardingFeatureList(const ForwardingFeatureList& choice)
    {
        its::AsnObject& asnObject = const_cast<ForwardingFeatureList&>(choice);
        asnObject.SetDescription(GetForwardingFeatureListStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceForwardingFeatureList() const
    {
        return Contains(GetForwardingFeatureListStaticDescription()->TagIdentity());
    }

    const ForwardingFeatureList& GetChoiceForwardingFeatureList() const
    {
        ITS_REQUIRE(ChoiceForwardingFeatureList());
        return static_cast<const ForwardingFeatureList&> (GetChoice());
    }

    void SetChoiceCli_RestrictionInfo(Cli_RestrictionInfo* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetCli_RestrictionInfoStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceCli_RestrictionInfo(const Cli_RestrictionInfo& choice)
    {
        its::AsnObject& asnObject = const_cast<Cli_RestrictionInfo&>(choice);
        asnObject.SetDescription(GetCli_RestrictionInfoStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceCli_RestrictionInfo() const
    {
        return Contains(GetCli_RestrictionInfoStaticDescription()->TagIdentity());
    }

    const Cli_RestrictionInfo& GetChoiceCli_RestrictionInfo() const
    {
        ITS_REQUIRE(ChoiceCli_RestrictionInfo());
        return static_cast<const Cli_RestrictionInfo&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_MAP_V2_INTERROGATE_SS_RES_H_)

