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


#if !defined(_MAP_V9_VLR_CAPABILITY_H_)
#define _MAP_V9_VLR_CAPABILITY_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>
#include <AsnBitString.h>
#include <AsnEnumerated.h>
#include <AsnChoice.h>

#include <map_v9_supported_camel_phases.h>
#include <map_v9_extension_container.h>
#include <map_v9_ist_support_indicator.h>
#include <map_v9_super_charger_info.h>
#include <map_v9_supported_lcs_capability_sets.h>
#include <map_v9_offered_camel4cs_is.h>



namespace map_v9 {



class VLR_Capability : public its::AsnSequence
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



    class LongFTN_Supported : public its::AsnNull
    {
    public:

        LongFTN_Supported() : its::AsnNull(false)
        {
            Initialize();
        }

        LongFTN_Supported(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        LongFTN_Supported(const LongFTN_Supported& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        LongFTN_Supported(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~LongFTN_Supported()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new LongFTN_Supported(*this);
        }

        virtual std::string GetName() const
        { return "LongFTN_Supported"; }

    };


        typedef map_v9::SupportedCamelPhases SupportedCamelPhases;


        typedef map_v9::ExtensionContainer ExtensionContainer;


        typedef map_v9::IST_SupportIndicator IST_SupportIndicator;


        typedef map_v9::SuperChargerInfo SuperChargerInfo;


        typedef map_v9::SupportedLCS_CapabilitySets SupportedLCS_CapabilitySets;


        typedef map_v9::OfferedCamel4CSIs OfferedCamel4CSIs;


////////// End Nested Class(es) //////////

    VLR_Capability() : its::AsnSequence(8, false)
    {
        Initialize();
    }

    VLR_Capability(its::Octets& octets) : its::AsnSequence(8, false)
    {
        Initialize();
        Decode(octets);
    }

    VLR_Capability(const VLR_Capability& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    VLR_Capability(its::AsnDescObject* description) : its::AsnSequence(8, description)
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

    static its::AsnDescObject* GetSupportedCamelPhasesStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetSolsaSupportIndicatorStaticDescription();
    static its::AsnDescObject* GetIstSupportIndicatorStaticDescription();
    static its::AsnDescObject* GetSuperChargerSupportedInServingNetworkEntityStaticDescription();
    static its::AsnDescObject* GetLongFTN_SupportedStaticDescription();
    static its::AsnDescObject* GetSupportedLCS_CapabilitySetsStaticDescription();
    static its::AsnDescObject* GetOfferedCamel4CSIsStaticDescription();

public:

    virtual ~VLR_Capability()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new VLR_Capability(*this);
    }

    virtual std::string GetName() const
    { return "VLR_Capability"; }

    void SetSupportedCamelPhases(SupportedCamelPhases* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSupportedCamelPhasesStaticDescription());
        AddElement(0, element);
    }

    void SetSupportedCamelPhases(const SupportedCamelPhases& element)
    {
        its::AsnObject& asnObject = const_cast<SupportedCamelPhases&>(element);
        asnObject.SetDescription(GetSupportedCamelPhasesStaticDescription());
        AddElement(0, element);
    }

    bool OptionSupportedCamelPhases() const
    {
        return Contains(0);
    }

    const SupportedCamelPhases& GetSupportedCamelPhases() const
    {
        ITS_REQUIRE(OptionSupportedCamelPhases());
        return static_cast<const SupportedCamelPhases&> (ElementAt(0));
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

    void SetSolsaSupportIndicator(SolsaSupportIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSolsaSupportIndicatorStaticDescription());
        AddElement(2, element);
    }

    void SetSolsaSupportIndicator(const SolsaSupportIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<SolsaSupportIndicator&>(element);
        asnObject.SetDescription(GetSolsaSupportIndicatorStaticDescription());
        AddElement(2, element);
    }

    bool OptionSolsaSupportIndicator() const
    {
        return Contains(2);
    }

    const SolsaSupportIndicator& GetSolsaSupportIndicator() const
    {
        ITS_REQUIRE(OptionSolsaSupportIndicator());
        return static_cast<const SolsaSupportIndicator&> (ElementAt(2));
    }

    void SetIstSupportIndicator(IST_SupportIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIstSupportIndicatorStaticDescription());
        AddElement(3, element);
    }

    void SetIstSupportIndicator(const IST_SupportIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<IST_SupportIndicator&>(element);
        asnObject.SetDescription(GetIstSupportIndicatorStaticDescription());
        AddElement(3, element);
    }

    bool OptionIstSupportIndicator() const
    {
        return Contains(3);
    }

    const IST_SupportIndicator& GetIstSupportIndicator() const
    {
        ITS_REQUIRE(OptionIstSupportIndicator());
        return static_cast<const IST_SupportIndicator&> (ElementAt(3));
    }

    void SetSuperChargerSupportedInServingNetworkEntity(SuperChargerInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSuperChargerSupportedInServingNetworkEntityStaticDescription());
        AddElement(4, element);
    }

    void SetSuperChargerSupportedInServingNetworkEntity(const SuperChargerInfo& element)
    {
        its::AsnObject& asnObject = const_cast<SuperChargerInfo&>(element);
        asnObject.SetDescription(GetSuperChargerSupportedInServingNetworkEntityStaticDescription());
        AddElement(4, element);
    }

    bool OptionSuperChargerSupportedInServingNetworkEntity() const
    {
        return Contains(4);
    }

    const SuperChargerInfo& GetSuperChargerSupportedInServingNetworkEntity() const
    {
        ITS_REQUIRE(OptionSuperChargerSupportedInServingNetworkEntity());
        return static_cast<const SuperChargerInfo&> (ElementAt(4));
    }

    void SetLongFTN_Supported(LongFTN_Supported* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLongFTN_SupportedStaticDescription());
        AddElement(5, element);
    }

    void SetLongFTN_Supported(const LongFTN_Supported& element)
    {
        its::AsnObject& asnObject = const_cast<LongFTN_Supported&>(element);
        asnObject.SetDescription(GetLongFTN_SupportedStaticDescription());
        AddElement(5, element);
    }

    bool OptionLongFTN_Supported() const
    {
        return Contains(5);
    }

    const LongFTN_Supported& GetLongFTN_Supported() const
    {
        ITS_REQUIRE(OptionLongFTN_Supported());
        return static_cast<const LongFTN_Supported&> (ElementAt(5));
    }

    void SetSupportedLCS_CapabilitySets(SupportedLCS_CapabilitySets* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSupportedLCS_CapabilitySetsStaticDescription());
        AddElement(6, element);
    }

    void SetSupportedLCS_CapabilitySets(const SupportedLCS_CapabilitySets& element)
    {
        its::AsnObject& asnObject = const_cast<SupportedLCS_CapabilitySets&>(element);
        asnObject.SetDescription(GetSupportedLCS_CapabilitySetsStaticDescription());
        AddElement(6, element);
    }

    bool OptionSupportedLCS_CapabilitySets() const
    {
        return Contains(6);
    }

    const SupportedLCS_CapabilitySets& GetSupportedLCS_CapabilitySets() const
    {
        ITS_REQUIRE(OptionSupportedLCS_CapabilitySets());
        return static_cast<const SupportedLCS_CapabilitySets&> (ElementAt(6));
    }

    void SetOfferedCamel4CSIs(OfferedCamel4CSIs* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOfferedCamel4CSIsStaticDescription());
        AddElement(7, element);
    }

    void SetOfferedCamel4CSIs(const OfferedCamel4CSIs& element)
    {
        its::AsnObject& asnObject = const_cast<OfferedCamel4CSIs&>(element);
        asnObject.SetDescription(GetOfferedCamel4CSIsStaticDescription());
        AddElement(7, element);
    }

    bool OptionOfferedCamel4CSIs() const
    {
        return Contains(7);
    }

    const OfferedCamel4CSIs& GetOfferedCamel4CSIs() const
    {
        ITS_REQUIRE(OptionOfferedCamel4CSIs());
        return static_cast<const OfferedCamel4CSIs&> (ElementAt(7));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_VLR_CAPABILITY_H_)
