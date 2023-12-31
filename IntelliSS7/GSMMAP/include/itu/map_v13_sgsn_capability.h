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


#if !defined(_MAP_V13_SGSN_CAPABILITY_H_)
#define _MAP_V13_SGSN_CAPABILITY_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>
#include <AsnBoolean.h>
#include <AsnChoice.h>
#include <AsnBitString.h>

#include <map_v13_extension_container.h>
#include <map_v13_super_charger_info.h>
#include <map_v13_supported_camel_phases.h>
#include <map_v13_supported_lcs_capability_sets.h>
#include <map_v13_offered_camel4cs_is.h>
#include <map_v13_supported_rat_types.h>
#include <map_v13_supported_features.h>



namespace map_v13 {



class SGSN_Capability : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class SolsaSupportIndicator : public its::AsnNull
    {
    public:

        SolsaSupportIndicator() : its::AsnNull(false)
        {
            Initialize();
        }

        SolsaSupportIndicator(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        SolsaSupportIndicator(const SolsaSupportIndicator& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        SolsaSupportIndicator(its::AsnDescObject* description) : its::AsnNull(description)
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

    public:

        virtual ~SolsaSupportIndicator()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new SolsaSupportIndicator(*this);
        }

        virtual std::string GetName() const
        { return "SolsaSupportIndicator"; }

    };



    class GprsEnhancementsSupportIndicator : public its::AsnNull
    {
    public:

        GprsEnhancementsSupportIndicator() : its::AsnNull(false)
        {
            Initialize();
        }

        GprsEnhancementsSupportIndicator(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        GprsEnhancementsSupportIndicator(const GprsEnhancementsSupportIndicator& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        GprsEnhancementsSupportIndicator(its::AsnDescObject* description) : its::AsnNull(description)
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

    public:

        virtual ~GprsEnhancementsSupportIndicator()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new GprsEnhancementsSupportIndicator(*this);
        }

        virtual std::string GetName() const
        { return "GprsEnhancementsSupportIndicator"; }

    };



    class SmsCallBarringSupportIndicator : public its::AsnNull
    {
    public:

        SmsCallBarringSupportIndicator() : its::AsnNull(false)
        {
            Initialize();
        }

        SmsCallBarringSupportIndicator(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        SmsCallBarringSupportIndicator(const SmsCallBarringSupportIndicator& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        SmsCallBarringSupportIndicator(its::AsnDescObject* description) : its::AsnNull(description)
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

    public:

        virtual ~SmsCallBarringSupportIndicator()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new SmsCallBarringSupportIndicator(*this);
        }

        virtual std::string GetName() const
        { return "SmsCallBarringSupportIndicator"; }

    };



    class T_adsDataRetrieval : public its::AsnNull
    {
    public:

        T_adsDataRetrieval() : its::AsnNull(false)
        {
            Initialize();
        }

        T_adsDataRetrieval(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        T_adsDataRetrieval(const T_adsDataRetrieval& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        T_adsDataRetrieval(its::AsnDescObject* description) : its::AsnNull(description)
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

    public:

        virtual ~T_adsDataRetrieval()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new T_adsDataRetrieval(*this);
        }

        virtual std::string GetName() const
        { return "T_adsDataRetrieval"; }

    };



    class HomogeneousSupportOfIMSVoiceOverPSSessions : public its::AsnBoolean
    {
    public:

        HomogeneousSupportOfIMSVoiceOverPSSessions(bool value) : its::AsnBoolean(value, false)
        {
            Initialize();
        }

        HomogeneousSupportOfIMSVoiceOverPSSessions(its::Octets& octets) : its::AsnBoolean(false, false)
        {
            Initialize();
            Decode(octets);
        }

        HomogeneousSupportOfIMSVoiceOverPSSessions(const HomogeneousSupportOfIMSVoiceOverPSSessions& rhs) : its::AsnBoolean(rhs)
        {
            // Nothing to do.
        }

        HomogeneousSupportOfIMSVoiceOverPSSessions(its::AsnDescObject* description) : its::AsnBoolean(description)
        {
            // Nothing to do.
        }

        HomogeneousSupportOfIMSVoiceOverPSSessions(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

    public:

        virtual ~HomogeneousSupportOfIMSVoiceOverPSSessions()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new HomogeneousSupportOfIMSVoiceOverPSSessions(*this);
        }

        virtual std::string GetName() const
        { return "HomogeneousSupportOfIMSVoiceOverPSSessions"; }

    };


        typedef map_v13::ExtensionContainer ExtensionContainer;


        typedef map_v13::SuperChargerInfo SuperChargerInfo;


        typedef map_v13::SupportedCamelPhases SupportedCamelPhases;


        typedef map_v13::SupportedLCS_CapabilitySets SupportedLCS_CapabilitySets;


        typedef map_v13::OfferedCamel4CSIs OfferedCamel4CSIs;


        typedef map_v13::SupportedRAT_Types SupportedRAT_Types;


        typedef map_v13::SupportedFeatures SupportedFeatures;


////////// End Nested Class(es) //////////

    SGSN_Capability() : its::AsnSequence(12, false)
    {
        Initialize();
    }

    SGSN_Capability(its::Octets& octets) : its::AsnSequence(12, false)
    {
        Initialize();
        Decode(octets);
    }

    SGSN_Capability(const SGSN_Capability& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SGSN_Capability(its::AsnDescObject* description) : its::AsnSequence(12, description)
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

    static its::AsnDescObject* GetSolsaSupportIndicatorStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetSuperChargerSupportedInServingNetworkEntityStaticDescription();
    static its::AsnDescObject* GetGprsEnhancementsSupportIndicatorStaticDescription();
    static its::AsnDescObject* GetSupportedCamelPhasesStaticDescription();
    static its::AsnDescObject* GetSupportedLCS_CapabilitySetsStaticDescription();
    static its::AsnDescObject* GetOfferedCamel4CSIsStaticDescription();
    static its::AsnDescObject* GetSmsCallBarringSupportIndicatorStaticDescription();
    static its::AsnDescObject* GetSupportedRAT_TypesIndicatorStaticDescription();
    static its::AsnDescObject* GetSupportedFeaturesStaticDescription();
    static its::AsnDescObject* GetT_adsDataRetrievalStaticDescription();
    static its::AsnDescObject* GetHomogeneousSupportOfIMSVoiceOverPSSessionsStaticDescription();

public:

    virtual ~SGSN_Capability()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SGSN_Capability(*this);
    }

    virtual std::string GetName() const
    { return "SGSN_Capability"; }

    void SetSolsaSupportIndicator(SolsaSupportIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSolsaSupportIndicatorStaticDescription());
        AddElement(0, element);
    }

    void SetSolsaSupportIndicator(const SolsaSupportIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<SolsaSupportIndicator&>(element);
        asnObject.SetDescription(GetSolsaSupportIndicatorStaticDescription());
        AddElement(0, element);
    }

    bool OptionSolsaSupportIndicator() const
    {
        return Contains(0);
    }

    const SolsaSupportIndicator& GetSolsaSupportIndicator() const
    {
        ITS_REQUIRE(OptionSolsaSupportIndicator());
        return static_cast<const SolsaSupportIndicator&> (ElementAt(0));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(1, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(1, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(1);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(1));
    }

    void SetSuperChargerSupportedInServingNetworkEntity(SuperChargerInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSuperChargerSupportedInServingNetworkEntityStaticDescription());
        AddElement(2, element);
    }

    void SetSuperChargerSupportedInServingNetworkEntity(const SuperChargerInfo& element)
    {
        its::AsnObject& asnObject = const_cast<SuperChargerInfo&>(element);
        asnObject.SetDescription(GetSuperChargerSupportedInServingNetworkEntityStaticDescription());
        AddElement(2, element);
    }

    bool OptionSuperChargerSupportedInServingNetworkEntity() const
    {
        return Contains(2);
    }

    const SuperChargerInfo& GetSuperChargerSupportedInServingNetworkEntity() const
    {
        ITS_REQUIRE(OptionSuperChargerSupportedInServingNetworkEntity());
        return static_cast<const SuperChargerInfo&> (ElementAt(2));
    }

    void SetGprsEnhancementsSupportIndicator(GprsEnhancementsSupportIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGprsEnhancementsSupportIndicatorStaticDescription());
        AddElement(3, element);
    }

    void SetGprsEnhancementsSupportIndicator(const GprsEnhancementsSupportIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<GprsEnhancementsSupportIndicator&>(element);
        asnObject.SetDescription(GetGprsEnhancementsSupportIndicatorStaticDescription());
        AddElement(3, element);
    }

    bool OptionGprsEnhancementsSupportIndicator() const
    {
        return Contains(3);
    }

    const GprsEnhancementsSupportIndicator& GetGprsEnhancementsSupportIndicator() const
    {
        ITS_REQUIRE(OptionGprsEnhancementsSupportIndicator());
        return static_cast<const GprsEnhancementsSupportIndicator&> (ElementAt(3));
    }

    void SetSupportedCamelPhases(SupportedCamelPhases* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSupportedCamelPhasesStaticDescription());
        AddElement(4, element);
    }

    void SetSupportedCamelPhases(const SupportedCamelPhases& element)
    {
        its::AsnObject& asnObject = const_cast<SupportedCamelPhases&>(element);
        asnObject.SetDescription(GetSupportedCamelPhasesStaticDescription());
        AddElement(4, element);
    }

    bool OptionSupportedCamelPhases() const
    {
        return Contains(4);
    }

    const SupportedCamelPhases& GetSupportedCamelPhases() const
    {
        ITS_REQUIRE(OptionSupportedCamelPhases());
        return static_cast<const SupportedCamelPhases&> (ElementAt(4));
    }

    void SetSupportedLCS_CapabilitySets(SupportedLCS_CapabilitySets* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSupportedLCS_CapabilitySetsStaticDescription());
        AddElement(5, element);
    }

    void SetSupportedLCS_CapabilitySets(const SupportedLCS_CapabilitySets& element)
    {
        its::AsnObject& asnObject = const_cast<SupportedLCS_CapabilitySets&>(element);
        asnObject.SetDescription(GetSupportedLCS_CapabilitySetsStaticDescription());
        AddElement(5, element);
    }

    bool OptionSupportedLCS_CapabilitySets() const
    {
        return Contains(5);
    }

    const SupportedLCS_CapabilitySets& GetSupportedLCS_CapabilitySets() const
    {
        ITS_REQUIRE(OptionSupportedLCS_CapabilitySets());
        return static_cast<const SupportedLCS_CapabilitySets&> (ElementAt(5));
    }

    void SetOfferedCamel4CSIs(OfferedCamel4CSIs* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOfferedCamel4CSIsStaticDescription());
        AddElement(6, element);
    }

    void SetOfferedCamel4CSIs(const OfferedCamel4CSIs& element)
    {
        its::AsnObject& asnObject = const_cast<OfferedCamel4CSIs&>(element);
        asnObject.SetDescription(GetOfferedCamel4CSIsStaticDescription());
        AddElement(6, element);
    }

    bool OptionOfferedCamel4CSIs() const
    {
        return Contains(6);
    }

    const OfferedCamel4CSIs& GetOfferedCamel4CSIs() const
    {
        ITS_REQUIRE(OptionOfferedCamel4CSIs());
        return static_cast<const OfferedCamel4CSIs&> (ElementAt(6));
    }

    void SetSmsCallBarringSupportIndicator(SmsCallBarringSupportIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSmsCallBarringSupportIndicatorStaticDescription());
        AddElement(7, element);
    }

    void SetSmsCallBarringSupportIndicator(const SmsCallBarringSupportIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<SmsCallBarringSupportIndicator&>(element);
        asnObject.SetDescription(GetSmsCallBarringSupportIndicatorStaticDescription());
        AddElement(7, element);
    }

    bool OptionSmsCallBarringSupportIndicator() const
    {
        return Contains(7);
    }

    const SmsCallBarringSupportIndicator& GetSmsCallBarringSupportIndicator() const
    {
        ITS_REQUIRE(OptionSmsCallBarringSupportIndicator());
        return static_cast<const SmsCallBarringSupportIndicator&> (ElementAt(7));
    }

    void SetSupportedRAT_TypesIndicator(SupportedRAT_Types* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSupportedRAT_TypesIndicatorStaticDescription());
        AddElement(8, element);
    }

    void SetSupportedRAT_TypesIndicator(const SupportedRAT_Types& element)
    {
        its::AsnObject& asnObject = const_cast<SupportedRAT_Types&>(element);
        asnObject.SetDescription(GetSupportedRAT_TypesIndicatorStaticDescription());
        AddElement(8, element);
    }

    bool OptionSupportedRAT_TypesIndicator() const
    {
        return Contains(8);
    }

    const SupportedRAT_Types& GetSupportedRAT_TypesIndicator() const
    {
        ITS_REQUIRE(OptionSupportedRAT_TypesIndicator());
        return static_cast<const SupportedRAT_Types&> (ElementAt(8));
    }

    void SetSupportedFeatures(SupportedFeatures* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSupportedFeaturesStaticDescription());
        AddElement(9, element);
    }

    void SetSupportedFeatures(const SupportedFeatures& element)
    {
        its::AsnObject& asnObject = const_cast<SupportedFeatures&>(element);
        asnObject.SetDescription(GetSupportedFeaturesStaticDescription());
        AddElement(9, element);
    }

    bool OptionSupportedFeatures() const
    {
        return Contains(9);
    }

    const SupportedFeatures& GetSupportedFeatures() const
    {
        ITS_REQUIRE(OptionSupportedFeatures());
        return static_cast<const SupportedFeatures&> (ElementAt(9));
    }

    void SetT_adsDataRetrieval(T_adsDataRetrieval* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetT_adsDataRetrievalStaticDescription());
        AddElement(10, element);
    }

    void SetT_adsDataRetrieval(const T_adsDataRetrieval& element)
    {
        its::AsnObject& asnObject = const_cast<T_adsDataRetrieval&>(element);
        asnObject.SetDescription(GetT_adsDataRetrievalStaticDescription());
        AddElement(10, element);
    }

    bool OptionT_adsDataRetrieval() const
    {
        return Contains(10);
    }

    const T_adsDataRetrieval& GetT_adsDataRetrieval() const
    {
        ITS_REQUIRE(OptionT_adsDataRetrieval());
        return static_cast<const T_adsDataRetrieval&> (ElementAt(10));
    }

    void SetHomogeneousSupportOfIMSVoiceOverPSSessions(HomogeneousSupportOfIMSVoiceOverPSSessions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetHomogeneousSupportOfIMSVoiceOverPSSessionsStaticDescription());
        AddElement(11, element);
    }

    void SetHomogeneousSupportOfIMSVoiceOverPSSessions(const HomogeneousSupportOfIMSVoiceOverPSSessions& element)
    {
        its::AsnObject& asnObject = const_cast<HomogeneousSupportOfIMSVoiceOverPSSessions&>(element);
        asnObject.SetDescription(GetHomogeneousSupportOfIMSVoiceOverPSSessionsStaticDescription());
        AddElement(11, element);
    }

    bool OptionHomogeneousSupportOfIMSVoiceOverPSSessions() const
    {
        return Contains(11);
    }

    const HomogeneousSupportOfIMSVoiceOverPSSessions& GetHomogeneousSupportOfIMSVoiceOverPSSessions() const
    {
        ITS_REQUIRE(OptionHomogeneousSupportOfIMSVoiceOverPSSessions());
        return static_cast<const HomogeneousSupportOfIMSVoiceOverPSSessions&> (ElementAt(11));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_SGSN_CAPABILITY_H_)

