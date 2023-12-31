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


#if !defined(_MAP_V9_ANY_TIME_SUBSCRIPTION_INTERROGATION_RES_H_)
#define _MAP_V9_ANY_TIME_SUBSCRIPTION_INTERROGATION_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnBitString.h>

#include <map_v9_call_forwarding_data.h>
#include <map_v9_call_barring_data.h>
#include <map_v9_odb_info.h>
#include <map_v9_camel_subscription_info.h>
#include <map_v9_supported_camel_phases.h>
#include <map_v9_extension_container.h>
#include <map_v9_offered_camel4cs_is.h>



namespace map_v9 {



class AnyTimeSubscriptionInterrogationRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::CallForwardingData CallForwardingData;


        typedef map_v9::CallBarringData CallBarringData;


        typedef map_v9::ODB_Info ODB_Info;


        typedef map_v9::CAMEL_SubscriptionInfo CAMEL_SubscriptionInfo;


        typedef map_v9::SupportedCamelPhases SupportedCamelPhases;


        typedef map_v9::ExtensionContainer ExtensionContainer;


        typedef map_v9::OfferedCamel4CSIs OfferedCamel4CSIs;


////////// End Nested Class(es) //////////

    AnyTimeSubscriptionInterrogationRes() : its::AsnSequence(9, false)
    {
        Initialize();
    }

    AnyTimeSubscriptionInterrogationRes(its::Octets& octets) : its::AsnSequence(9, false)
    {
        Initialize();
        Decode(octets);
    }

    AnyTimeSubscriptionInterrogationRes(const AnyTimeSubscriptionInterrogationRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    AnyTimeSubscriptionInterrogationRes(its::AsnDescObject* description) : its::AsnSequence(9, description)
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

    static its::AsnDescObject* GetCallForwardingDataStaticDescription();
    static its::AsnDescObject* GetCallBarringDataStaticDescription();
    static its::AsnDescObject* GetOdb_InfoStaticDescription();
    static its::AsnDescObject* GetCamel_SubscriptionInfoStaticDescription();
    static its::AsnDescObject* GetSupportedVLR_CAMEL_PhasesStaticDescription();
    static its::AsnDescObject* GetSupportedSGSN_CAMEL_PhasesStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetOfferedCamel4CSIsInVLRStaticDescription();
    static its::AsnDescObject* GetOfferedCamel4CSIsInSGSNStaticDescription();

public:

    virtual ~AnyTimeSubscriptionInterrogationRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AnyTimeSubscriptionInterrogationRes(*this);
    }

    virtual std::string GetName() const
    { return "AnyTimeSubscriptionInterrogationRes"; }

    void SetCallForwardingData(CallForwardingData* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallForwardingDataStaticDescription());
        AddElement(0, element);
    }

    void SetCallForwardingData(const CallForwardingData& element)
    {
        its::AsnObject& asnObject = const_cast<CallForwardingData&>(element);
        asnObject.SetDescription(GetCallForwardingDataStaticDescription());
        AddElement(0, element);
    }

    bool OptionCallForwardingData() const
    {
        return Contains(0);
    }

    const CallForwardingData& GetCallForwardingData() const
    {
        ITS_REQUIRE(OptionCallForwardingData());
        return static_cast<const CallForwardingData&> (ElementAt(0));
    }

    void SetCallBarringData(CallBarringData* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallBarringDataStaticDescription());
        AddElement(1, element);
    }

    void SetCallBarringData(const CallBarringData& element)
    {
        its::AsnObject& asnObject = const_cast<CallBarringData&>(element);
        asnObject.SetDescription(GetCallBarringDataStaticDescription());
        AddElement(1, element);
    }

    bool OptionCallBarringData() const
    {
        return Contains(1);
    }

    const CallBarringData& GetCallBarringData() const
    {
        ITS_REQUIRE(OptionCallBarringData());
        return static_cast<const CallBarringData&> (ElementAt(1));
    }

    void SetOdb_Info(ODB_Info* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOdb_InfoStaticDescription());
        AddElement(2, element);
    }

    void SetOdb_Info(const ODB_Info& element)
    {
        its::AsnObject& asnObject = const_cast<ODB_Info&>(element);
        asnObject.SetDescription(GetOdb_InfoStaticDescription());
        AddElement(2, element);
    }

    bool OptionOdb_Info() const
    {
        return Contains(2);
    }

    const ODB_Info& GetOdb_Info() const
    {
        ITS_REQUIRE(OptionOdb_Info());
        return static_cast<const ODB_Info&> (ElementAt(2));
    }

    void SetCamel_SubscriptionInfo(CAMEL_SubscriptionInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCamel_SubscriptionInfoStaticDescription());
        AddElement(3, element);
    }

    void SetCamel_SubscriptionInfo(const CAMEL_SubscriptionInfo& element)
    {
        its::AsnObject& asnObject = const_cast<CAMEL_SubscriptionInfo&>(element);
        asnObject.SetDescription(GetCamel_SubscriptionInfoStaticDescription());
        AddElement(3, element);
    }

    bool OptionCamel_SubscriptionInfo() const
    {
        return Contains(3);
    }

    const CAMEL_SubscriptionInfo& GetCamel_SubscriptionInfo() const
    {
        ITS_REQUIRE(OptionCamel_SubscriptionInfo());
        return static_cast<const CAMEL_SubscriptionInfo&> (ElementAt(3));
    }

    void SetSupportedVLR_CAMEL_Phases(SupportedCamelPhases* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSupportedVLR_CAMEL_PhasesStaticDescription());
        AddElement(4, element);
    }

    void SetSupportedVLR_CAMEL_Phases(const SupportedCamelPhases& element)
    {
        its::AsnObject& asnObject = const_cast<SupportedCamelPhases&>(element);
        asnObject.SetDescription(GetSupportedVLR_CAMEL_PhasesStaticDescription());
        AddElement(4, element);
    }

    bool OptionSupportedVLR_CAMEL_Phases() const
    {
        return Contains(4);
    }

    const SupportedCamelPhases& GetSupportedVLR_CAMEL_Phases() const
    {
        ITS_REQUIRE(OptionSupportedVLR_CAMEL_Phases());
        return static_cast<const SupportedCamelPhases&> (ElementAt(4));
    }

    void SetSupportedSGSN_CAMEL_Phases(SupportedCamelPhases* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSupportedSGSN_CAMEL_PhasesStaticDescription());
        AddElement(5, element);
    }

    void SetSupportedSGSN_CAMEL_Phases(const SupportedCamelPhases& element)
    {
        its::AsnObject& asnObject = const_cast<SupportedCamelPhases&>(element);
        asnObject.SetDescription(GetSupportedSGSN_CAMEL_PhasesStaticDescription());
        AddElement(5, element);
    }

    bool OptionSupportedSGSN_CAMEL_Phases() const
    {
        return Contains(5);
    }

    const SupportedCamelPhases& GetSupportedSGSN_CAMEL_Phases() const
    {
        ITS_REQUIRE(OptionSupportedSGSN_CAMEL_Phases());
        return static_cast<const SupportedCamelPhases&> (ElementAt(5));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(6, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(6, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(6);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(6));
    }

    void SetOfferedCamel4CSIsInVLR(OfferedCamel4CSIs* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOfferedCamel4CSIsInVLRStaticDescription());
        AddElement(7, element);
    }

    void SetOfferedCamel4CSIsInVLR(const OfferedCamel4CSIs& element)
    {
        its::AsnObject& asnObject = const_cast<OfferedCamel4CSIs&>(element);
        asnObject.SetDescription(GetOfferedCamel4CSIsInVLRStaticDescription());
        AddElement(7, element);
    }

    bool OptionOfferedCamel4CSIsInVLR() const
    {
        return Contains(7);
    }

    const OfferedCamel4CSIs& GetOfferedCamel4CSIsInVLR() const
    {
        ITS_REQUIRE(OptionOfferedCamel4CSIsInVLR());
        return static_cast<const OfferedCamel4CSIs&> (ElementAt(7));
    }

    void SetOfferedCamel4CSIsInSGSN(OfferedCamel4CSIs* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOfferedCamel4CSIsInSGSNStaticDescription());
        AddElement(8, element);
    }

    void SetOfferedCamel4CSIsInSGSN(const OfferedCamel4CSIs& element)
    {
        its::AsnObject& asnObject = const_cast<OfferedCamel4CSIs&>(element);
        asnObject.SetDescription(GetOfferedCamel4CSIsInSGSNStaticDescription());
        AddElement(8, element);
    }

    bool OptionOfferedCamel4CSIsInSGSN() const
    {
        return Contains(8);
    }

    const OfferedCamel4CSIs& GetOfferedCamel4CSIsInSGSN() const
    {
        ITS_REQUIRE(OptionOfferedCamel4CSIsInSGSN());
        return static_cast<const OfferedCamel4CSIs&> (ElementAt(8));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_ANY_TIME_SUBSCRIPTION_INTERROGATION_RES_H_)

