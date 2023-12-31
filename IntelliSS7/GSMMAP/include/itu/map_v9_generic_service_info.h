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


#if !defined(_MAP_V9_GENERIC_SERVICE_INFO_H_)
#define _MAP_V9_GENERIC_SERVICE_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnEnumerated.h>
#include <AsnInteger.h>
#include <AsnSequenceOf.h>

#include <map_v9_ss_status.h>
#include <map_v9_cli_restriction_option.h>
#include <map_v9_emlpp_priority.h>
#include <map_v9_ccbs_feature_list.h>
#include <map_v9_max_mc_bearers.h>
#include <map_v9_mc_bearers.h>



namespace map_v9 {



class GenericServiceInfo : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::SS_Status SS_Status;


        typedef map_v9::CliRestrictionOption CliRestrictionOption;


        typedef map_v9::EMLPP_Priority EMLPP_Priority;


        typedef map_v9::CCBS_FeatureList CCBS_FeatureList;


        typedef map_v9::MaxMC_Bearers MaxMC_Bearers;


        typedef map_v9::MC_Bearers MC_Bearers;


////////// End Nested Class(es) //////////

    GenericServiceInfo() : its::AsnSequence(8, false)
    {
        Initialize();
    }

    GenericServiceInfo(its::Octets& octets) : its::AsnSequence(8, false)
    {
        Initialize();
        Decode(octets);
    }

    GenericServiceInfo(const GenericServiceInfo& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    GenericServiceInfo(its::AsnDescObject* description) : its::AsnSequence(8, description)
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
    static its::AsnDescObject* GetCliRestrictionOptionStaticDescription();
    static its::AsnDescObject* GetMaximumEntitledPriorityStaticDescription();
    static its::AsnDescObject* GetDefaultPriorityStaticDescription();
    static its::AsnDescObject* GetCcbs_FeatureListStaticDescription();
    static its::AsnDescObject* GetNbrSBStaticDescription();
    static its::AsnDescObject* GetNbrUserStaticDescription();
    static its::AsnDescObject* GetNbrSNStaticDescription();

public:

    virtual ~GenericServiceInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new GenericServiceInfo(*this);
    }

    virtual std::string GetName() const
    { return "GenericServiceInfo"; }

    void SetSs_Status(SS_Status* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_StatusStaticDescription());
        AddElement(0, element);
    }

    void SetSs_Status(const SS_Status& element)
    {
        its::AsnObject& asnObject = const_cast<SS_Status&>(element);
        asnObject.SetDescription(GetSs_StatusStaticDescription());
        AddElement(0, element);
    }

    const SS_Status& GetSs_Status() const
    {
        return static_cast<const SS_Status&> (ElementAt(0));
    }

    void SetCliRestrictionOption(CliRestrictionOption* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCliRestrictionOptionStaticDescription());
        AddElement(1, element);
    }

    void SetCliRestrictionOption(const CliRestrictionOption& element)
    {
        its::AsnObject& asnObject = const_cast<CliRestrictionOption&>(element);
        asnObject.SetDescription(GetCliRestrictionOptionStaticDescription());
        AddElement(1, element);
    }

    bool OptionCliRestrictionOption() const
    {
        return Contains(1);
    }

    const CliRestrictionOption& GetCliRestrictionOption() const
    {
        ITS_REQUIRE(OptionCliRestrictionOption());
        return static_cast<const CliRestrictionOption&> (ElementAt(1));
    }

    void SetMaximumEntitledPriority(EMLPP_Priority* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMaximumEntitledPriorityStaticDescription());
        AddElement(2, element);
    }

    void SetMaximumEntitledPriority(const EMLPP_Priority& element)
    {
        its::AsnObject& asnObject = const_cast<EMLPP_Priority&>(element);
        asnObject.SetDescription(GetMaximumEntitledPriorityStaticDescription());
        AddElement(2, element);
    }

    bool OptionMaximumEntitledPriority() const
    {
        return Contains(2);
    }

    const EMLPP_Priority& GetMaximumEntitledPriority() const
    {
        ITS_REQUIRE(OptionMaximumEntitledPriority());
        return static_cast<const EMLPP_Priority&> (ElementAt(2));
    }

    void SetDefaultPriority(EMLPP_Priority* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDefaultPriorityStaticDescription());
        AddElement(3, element);
    }

    void SetDefaultPriority(const EMLPP_Priority& element)
    {
        its::AsnObject& asnObject = const_cast<EMLPP_Priority&>(element);
        asnObject.SetDescription(GetDefaultPriorityStaticDescription());
        AddElement(3, element);
    }

    bool OptionDefaultPriority() const
    {
        return Contains(3);
    }

    const EMLPP_Priority& GetDefaultPriority() const
    {
        ITS_REQUIRE(OptionDefaultPriority());
        return static_cast<const EMLPP_Priority&> (ElementAt(3));
    }

    void SetCcbs_FeatureList(CCBS_FeatureList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCcbs_FeatureListStaticDescription());
        AddElement(4, element);
    }

    void SetCcbs_FeatureList(const CCBS_FeatureList& element)
    {
        its::AsnObject& asnObject = const_cast<CCBS_FeatureList&>(element);
        asnObject.SetDescription(GetCcbs_FeatureListStaticDescription());
        AddElement(4, element);
    }

    bool OptionCcbs_FeatureList() const
    {
        return Contains(4);
    }

    const CCBS_FeatureList& GetCcbs_FeatureList() const
    {
        ITS_REQUIRE(OptionCcbs_FeatureList());
        return static_cast<const CCBS_FeatureList&> (ElementAt(4));
    }

    void SetNbrSB(MaxMC_Bearers* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNbrSBStaticDescription());
        AddElement(5, element);
    }

    void SetNbrSB(const MaxMC_Bearers& element)
    {
        its::AsnObject& asnObject = const_cast<MaxMC_Bearers&>(element);
        asnObject.SetDescription(GetNbrSBStaticDescription());
        AddElement(5, element);
    }

    bool OptionNbrSB() const
    {
        return Contains(5);
    }

    const MaxMC_Bearers& GetNbrSB() const
    {
        ITS_REQUIRE(OptionNbrSB());
        return static_cast<const MaxMC_Bearers&> (ElementAt(5));
    }

    void SetNbrUser(MC_Bearers* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNbrUserStaticDescription());
        AddElement(6, element);
    }

    void SetNbrUser(const MC_Bearers& element)
    {
        its::AsnObject& asnObject = const_cast<MC_Bearers&>(element);
        asnObject.SetDescription(GetNbrUserStaticDescription());
        AddElement(6, element);
    }

    bool OptionNbrUser() const
    {
        return Contains(6);
    }

    const MC_Bearers& GetNbrUser() const
    {
        ITS_REQUIRE(OptionNbrUser());
        return static_cast<const MC_Bearers&> (ElementAt(6));
    }

    void SetNbrSN(MC_Bearers* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNbrSNStaticDescription());
        AddElement(7, element);
    }

    void SetNbrSN(const MC_Bearers& element)
    {
        its::AsnObject& asnObject = const_cast<MC_Bearers&>(element);
        asnObject.SetDescription(GetNbrSNStaticDescription());
        AddElement(7, element);
    }

    bool OptionNbrSN() const
    {
        return Contains(7);
    }

    const MC_Bearers& GetNbrSN() const
    {
        ITS_REQUIRE(OptionNbrSN());
        return static_cast<const MC_Bearers&> (ElementAt(7));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_GENERIC_SERVICE_INFO_H_)

