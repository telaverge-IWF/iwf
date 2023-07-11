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


#if !defined(_MAP_V13_FORWARD_ACCESS_SIGNALLING_ARG_H_)
#define _MAP_V13_FORWARD_ACCESS_SIGNALLING_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>
#include <AsnOctetString.h>
#include <AsnEnumerated.h>
#include <AsnSequenceOf.h>

#include <map_v13_access_network_signal_info.h>
#include <map_v13_integrity_protection_information.h>
#include <map_v13_encryption_information.h>
#include <map_v13_key_status.h>
#include <map_v13_allowed_gsm_algorithms.h>
#include <map_v13_allowed_umts_algorithms.h>
#include <map_v13_radio_resource_information.h>
#include <map_v13_extension_container.h>
#include <map_v13_radio_resource_list.h>
#include <map_v13_bssmap_service_handover.h>
#include <map_v13_ranap_service_handover.h>
#include <map_v13_bssmap_service_handover_list.h>
#include <map_v13_codec.h>
#include <map_v13_supported_codecs_list.h>
#include <map_v13_trace_propagation_list.h>
#include <map_v13_ao_ip_codecs_list.h>
#include <map_v13_ao_ip_codec.h>



namespace map_v13 {



class ForwardAccessSignalling_Arg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Rab_ConfigurationIndicator : public its::AsnNull
    {
    public:

        Rab_ConfigurationIndicator() : its::AsnNull(false)
        {
            Initialize();
        }

        Rab_ConfigurationIndicator(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Rab_ConfigurationIndicator(const Rab_ConfigurationIndicator& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Rab_ConfigurationIndicator(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Rab_ConfigurationIndicator()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Rab_ConfigurationIndicator(*this);
        }

        virtual std::string GetName() const
        { return "Rab_ConfigurationIndicator"; }

    };


        typedef map_v13::AccessNetworkSignalInfo AccessNetworkSignalInfo;


        typedef map_v13::IntegrityProtectionInformation IntegrityProtectionInformation;


        typedef map_v13::EncryptionInformation EncryptionInformation;


        typedef map_v13::KeyStatus KeyStatus;


        typedef map_v13::AllowedGSM_Algorithms AllowedGSM_Algorithms;


        typedef map_v13::AllowedUMTS_Algorithms AllowedUMTS_Algorithms;


        typedef map_v13::RadioResourceInformation RadioResourceInformation;


        typedef map_v13::ExtensionContainer ExtensionContainer;


        typedef map_v13::RadioResourceList RadioResourceList;


        typedef map_v13::BSSMAP_ServiceHandover BSSMAP_ServiceHandover;


        typedef map_v13::RANAP_ServiceHandover RANAP_ServiceHandover;


        typedef map_v13::BSSMAP_ServiceHandoverList BSSMAP_ServiceHandoverList;


        typedef map_v13::Codec Codec;


        typedef map_v13::SupportedCodecsList SupportedCodecsList;


        typedef map_v13::TracePropagationList TracePropagationList;


        typedef map_v13::AoIPCodecsList AoIPCodecsList;


        typedef map_v13::AoIPCodec AoIPCodec;


////////// End Nested Class(es) //////////

    ForwardAccessSignalling_Arg() : its::AsnSequence(20, false)
    {
        Initialize();
    }

    ForwardAccessSignalling_Arg(its::Octets& octets) : its::AsnSequence(20, false)
    {
        Initialize();
        Decode(octets);
    }

    ForwardAccessSignalling_Arg(const ForwardAccessSignalling_Arg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ForwardAccessSignalling_Arg(its::AsnDescObject* description) : its::AsnSequence(20, description)
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

    static its::AsnDescObject* GetAn_APDUStaticDescription();
    static its::AsnDescObject* GetIntegrityProtectionInfoStaticDescription();
    static its::AsnDescObject* GetEncryptionInfoStaticDescription();
    static its::AsnDescObject* GetKeyStatusStaticDescription();
    static its::AsnDescObject* GetAllowedGSM_AlgorithmsStaticDescription();
    static its::AsnDescObject* GetAllowedUMTS_AlgorithmsStaticDescription();
    static its::AsnDescObject* GetRadioResourceInformationStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetRadioResourceListStaticDescription();
    static its::AsnDescObject* GetBssmap_ServiceHandoverStaticDescription();
    static its::AsnDescObject* GetRanap_ServiceHandoverStaticDescription();
    static its::AsnDescObject* GetBssmap_ServiceHandoverListStaticDescription();
    static its::AsnDescObject* GetCurrentlyUsedCodecStaticDescription();
    static its::AsnDescObject* GetIuSupportedCodecsListStaticDescription();
    static its::AsnDescObject* GetRab_ConfigurationIndicatorStaticDescription();
    static its::AsnDescObject* GetIuSelectedCodecStaticDescription();
    static its::AsnDescObject* GetAlternativeChannelTypeStaticDescription();
    static its::AsnDescObject* GetTracePropagationListStaticDescription();
    static its::AsnDescObject* GetAoipSupportedCodecsListAnchorStaticDescription();
    static its::AsnDescObject* GetAoipSelectedCodecTargetStaticDescription();

public:

    virtual ~ForwardAccessSignalling_Arg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ForwardAccessSignalling_Arg(*this);
    }

    virtual std::string GetName() const
    { return "ForwardAccessSignalling_Arg"; }

    void SetAn_APDU(AccessNetworkSignalInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAn_APDUStaticDescription());
        AddElement(0, element);
    }

    void SetAn_APDU(const AccessNetworkSignalInfo& element)
    {
        its::AsnObject& asnObject = const_cast<AccessNetworkSignalInfo&>(element);
        asnObject.SetDescription(GetAn_APDUStaticDescription());
        AddElement(0, element);
    }

    const AccessNetworkSignalInfo& GetAn_APDU() const
    {
        return static_cast<const AccessNetworkSignalInfo&> (ElementAt(0));
    }

    void SetIntegrityProtectionInfo(IntegrityProtectionInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIntegrityProtectionInfoStaticDescription());
        AddElement(1, element);
    }

    void SetIntegrityProtectionInfo(const IntegrityProtectionInformation& element)
    {
        its::AsnObject& asnObject = const_cast<IntegrityProtectionInformation&>(element);
        asnObject.SetDescription(GetIntegrityProtectionInfoStaticDescription());
        AddElement(1, element);
    }

    bool OptionIntegrityProtectionInfo() const
    {
        return Contains(1);
    }

    const IntegrityProtectionInformation& GetIntegrityProtectionInfo() const
    {
        ITS_REQUIRE(OptionIntegrityProtectionInfo());
        return static_cast<const IntegrityProtectionInformation&> (ElementAt(1));
    }

    void SetEncryptionInfo(EncryptionInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEncryptionInfoStaticDescription());
        AddElement(2, element);
    }

    void SetEncryptionInfo(const EncryptionInformation& element)
    {
        its::AsnObject& asnObject = const_cast<EncryptionInformation&>(element);
        asnObject.SetDescription(GetEncryptionInfoStaticDescription());
        AddElement(2, element);
    }

    bool OptionEncryptionInfo() const
    {
        return Contains(2);
    }

    const EncryptionInformation& GetEncryptionInfo() const
    {
        ITS_REQUIRE(OptionEncryptionInfo());
        return static_cast<const EncryptionInformation&> (ElementAt(2));
    }

    void SetKeyStatus(KeyStatus* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetKeyStatusStaticDescription());
        AddElement(3, element);
    }

    void SetKeyStatus(const KeyStatus& element)
    {
        its::AsnObject& asnObject = const_cast<KeyStatus&>(element);
        asnObject.SetDescription(GetKeyStatusStaticDescription());
        AddElement(3, element);
    }

    bool OptionKeyStatus() const
    {
        return Contains(3);
    }

    const KeyStatus& GetKeyStatus() const
    {
        ITS_REQUIRE(OptionKeyStatus());
        return static_cast<const KeyStatus&> (ElementAt(3));
    }

    void SetAllowedGSM_Algorithms(AllowedGSM_Algorithms* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAllowedGSM_AlgorithmsStaticDescription());
        AddElement(4, element);
    }

    void SetAllowedGSM_Algorithms(const AllowedGSM_Algorithms& element)
    {
        its::AsnObject& asnObject = const_cast<AllowedGSM_Algorithms&>(element);
        asnObject.SetDescription(GetAllowedGSM_AlgorithmsStaticDescription());
        AddElement(4, element);
    }

    bool OptionAllowedGSM_Algorithms() const
    {
        return Contains(4);
    }

    const AllowedGSM_Algorithms& GetAllowedGSM_Algorithms() const
    {
        ITS_REQUIRE(OptionAllowedGSM_Algorithms());
        return static_cast<const AllowedGSM_Algorithms&> (ElementAt(4));
    }

    void SetAllowedUMTS_Algorithms(AllowedUMTS_Algorithms* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAllowedUMTS_AlgorithmsStaticDescription());
        AddElement(5, element);
    }

    void SetAllowedUMTS_Algorithms(const AllowedUMTS_Algorithms& element)
    {
        its::AsnObject& asnObject = const_cast<AllowedUMTS_Algorithms&>(element);
        asnObject.SetDescription(GetAllowedUMTS_AlgorithmsStaticDescription());
        AddElement(5, element);
    }

    bool OptionAllowedUMTS_Algorithms() const
    {
        return Contains(5);
    }

    const AllowedUMTS_Algorithms& GetAllowedUMTS_Algorithms() const
    {
        ITS_REQUIRE(OptionAllowedUMTS_Algorithms());
        return static_cast<const AllowedUMTS_Algorithms&> (ElementAt(5));
    }

    void SetRadioResourceInformation(RadioResourceInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRadioResourceInformationStaticDescription());
        AddElement(6, element);
    }

    void SetRadioResourceInformation(const RadioResourceInformation& element)
    {
        its::AsnObject& asnObject = const_cast<RadioResourceInformation&>(element);
        asnObject.SetDescription(GetRadioResourceInformationStaticDescription());
        AddElement(6, element);
    }

    bool OptionRadioResourceInformation() const
    {
        return Contains(6);
    }

    const RadioResourceInformation& GetRadioResourceInformation() const
    {
        ITS_REQUIRE(OptionRadioResourceInformation());
        return static_cast<const RadioResourceInformation&> (ElementAt(6));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(7, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(7, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(7);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(7));
    }

    void SetRadioResourceList(RadioResourceList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRadioResourceListStaticDescription());
        AddElement(8, element);
    }

    void SetRadioResourceList(const RadioResourceList& element)
    {
        its::AsnObject& asnObject = const_cast<RadioResourceList&>(element);
        asnObject.SetDescription(GetRadioResourceListStaticDescription());
        AddElement(8, element);
    }

    bool OptionRadioResourceList() const
    {
        return Contains(8);
    }

    const RadioResourceList& GetRadioResourceList() const
    {
        ITS_REQUIRE(OptionRadioResourceList());
        return static_cast<const RadioResourceList&> (ElementAt(8));
    }

    void SetBssmap_ServiceHandover(BSSMAP_ServiceHandover* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBssmap_ServiceHandoverStaticDescription());
        AddElement(9, element);
    }

    void SetBssmap_ServiceHandover(const BSSMAP_ServiceHandover& element)
    {
        its::AsnObject& asnObject = const_cast<BSSMAP_ServiceHandover&>(element);
        asnObject.SetDescription(GetBssmap_ServiceHandoverStaticDescription());
        AddElement(9, element);
    }

    bool OptionBssmap_ServiceHandover() const
    {
        return Contains(9);
    }

    const BSSMAP_ServiceHandover& GetBssmap_ServiceHandover() const
    {
        ITS_REQUIRE(OptionBssmap_ServiceHandover());
        return static_cast<const BSSMAP_ServiceHandover&> (ElementAt(9));
    }

    void SetRanap_ServiceHandover(RANAP_ServiceHandover* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRanap_ServiceHandoverStaticDescription());
        AddElement(10, element);
    }

    void SetRanap_ServiceHandover(const RANAP_ServiceHandover& element)
    {
        its::AsnObject& asnObject = const_cast<RANAP_ServiceHandover&>(element);
        asnObject.SetDescription(GetRanap_ServiceHandoverStaticDescription());
        AddElement(10, element);
    }

    bool OptionRanap_ServiceHandover() const
    {
        return Contains(10);
    }

    const RANAP_ServiceHandover& GetRanap_ServiceHandover() const
    {
        ITS_REQUIRE(OptionRanap_ServiceHandover());
        return static_cast<const RANAP_ServiceHandover&> (ElementAt(10));
    }

    void SetBssmap_ServiceHandoverList(BSSMAP_ServiceHandoverList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBssmap_ServiceHandoverListStaticDescription());
        AddElement(11, element);
    }

    void SetBssmap_ServiceHandoverList(const BSSMAP_ServiceHandoverList& element)
    {
        its::AsnObject& asnObject = const_cast<BSSMAP_ServiceHandoverList&>(element);
        asnObject.SetDescription(GetBssmap_ServiceHandoverListStaticDescription());
        AddElement(11, element);
    }

    bool OptionBssmap_ServiceHandoverList() const
    {
        return Contains(11);
    }

    const BSSMAP_ServiceHandoverList& GetBssmap_ServiceHandoverList() const
    {
        ITS_REQUIRE(OptionBssmap_ServiceHandoverList());
        return static_cast<const BSSMAP_ServiceHandoverList&> (ElementAt(11));
    }

    void SetCurrentlyUsedCodec(Codec* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCurrentlyUsedCodecStaticDescription());
        AddElement(12, element);
    }

    void SetCurrentlyUsedCodec(const Codec& element)
    {
        its::AsnObject& asnObject = const_cast<Codec&>(element);
        asnObject.SetDescription(GetCurrentlyUsedCodecStaticDescription());
        AddElement(12, element);
    }

    bool OptionCurrentlyUsedCodec() const
    {
        return Contains(12);
    }

    const Codec& GetCurrentlyUsedCodec() const
    {
        ITS_REQUIRE(OptionCurrentlyUsedCodec());
        return static_cast<const Codec&> (ElementAt(12));
    }

    void SetIuSupportedCodecsList(SupportedCodecsList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIuSupportedCodecsListStaticDescription());
        AddElement(13, element);
    }

    void SetIuSupportedCodecsList(const SupportedCodecsList& element)
    {
        its::AsnObject& asnObject = const_cast<SupportedCodecsList&>(element);
        asnObject.SetDescription(GetIuSupportedCodecsListStaticDescription());
        AddElement(13, element);
    }

    bool OptionIuSupportedCodecsList() const
    {
        return Contains(13);
    }

    const SupportedCodecsList& GetIuSupportedCodecsList() const
    {
        ITS_REQUIRE(OptionIuSupportedCodecsList());
        return static_cast<const SupportedCodecsList&> (ElementAt(13));
    }

    void SetRab_ConfigurationIndicator(Rab_ConfigurationIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRab_ConfigurationIndicatorStaticDescription());
        AddElement(14, element);
    }

    void SetRab_ConfigurationIndicator(const Rab_ConfigurationIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<Rab_ConfigurationIndicator&>(element);
        asnObject.SetDescription(GetRab_ConfigurationIndicatorStaticDescription());
        AddElement(14, element);
    }

    bool OptionRab_ConfigurationIndicator() const
    {
        return Contains(14);
    }

    const Rab_ConfigurationIndicator& GetRab_ConfigurationIndicator() const
    {
        ITS_REQUIRE(OptionRab_ConfigurationIndicator());
        return static_cast<const Rab_ConfigurationIndicator&> (ElementAt(14));
    }

    void SetIuSelectedCodec(Codec* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIuSelectedCodecStaticDescription());
        AddElement(15, element);
    }

    void SetIuSelectedCodec(const Codec& element)
    {
        its::AsnObject& asnObject = const_cast<Codec&>(element);
        asnObject.SetDescription(GetIuSelectedCodecStaticDescription());
        AddElement(15, element);
    }

    bool OptionIuSelectedCodec() const
    {
        return Contains(15);
    }

    const Codec& GetIuSelectedCodec() const
    {
        ITS_REQUIRE(OptionIuSelectedCodec());
        return static_cast<const Codec&> (ElementAt(15));
    }

    void SetAlternativeChannelType(RadioResourceInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAlternativeChannelTypeStaticDescription());
        AddElement(16, element);
    }

    void SetAlternativeChannelType(const RadioResourceInformation& element)
    {
        its::AsnObject& asnObject = const_cast<RadioResourceInformation&>(element);
        asnObject.SetDescription(GetAlternativeChannelTypeStaticDescription());
        AddElement(16, element);
    }

    bool OptionAlternativeChannelType() const
    {
        return Contains(16);
    }

    const RadioResourceInformation& GetAlternativeChannelType() const
    {
        ITS_REQUIRE(OptionAlternativeChannelType());
        return static_cast<const RadioResourceInformation&> (ElementAt(16));
    }

    void SetTracePropagationList(TracePropagationList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTracePropagationListStaticDescription());
        AddElement(17, element);
    }

    void SetTracePropagationList(const TracePropagationList& element)
    {
        its::AsnObject& asnObject = const_cast<TracePropagationList&>(element);
        asnObject.SetDescription(GetTracePropagationListStaticDescription());
        AddElement(17, element);
    }

    bool OptionTracePropagationList() const
    {
        return Contains(17);
    }

    const TracePropagationList& GetTracePropagationList() const
    {
        ITS_REQUIRE(OptionTracePropagationList());
        return static_cast<const TracePropagationList&> (ElementAt(17));
    }

    void SetAoipSupportedCodecsListAnchor(AoIPCodecsList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAoipSupportedCodecsListAnchorStaticDescription());
        AddElement(18, element);
    }

    void SetAoipSupportedCodecsListAnchor(const AoIPCodecsList& element)
    {
        its::AsnObject& asnObject = const_cast<AoIPCodecsList&>(element);
        asnObject.SetDescription(GetAoipSupportedCodecsListAnchorStaticDescription());
        AddElement(18, element);
    }

    bool OptionAoipSupportedCodecsListAnchor() const
    {
        return Contains(18);
    }

    const AoIPCodecsList& GetAoipSupportedCodecsListAnchor() const
    {
        ITS_REQUIRE(OptionAoipSupportedCodecsListAnchor());
        return static_cast<const AoIPCodecsList&> (ElementAt(18));
    }

    void SetAoipSelectedCodecTarget(AoIPCodec* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAoipSelectedCodecTargetStaticDescription());
        AddElement(19, element);
    }

    void SetAoipSelectedCodecTarget(const AoIPCodec& element)
    {
        its::AsnObject& asnObject = const_cast<AoIPCodec&>(element);
        asnObject.SetDescription(GetAoipSelectedCodecTargetStaticDescription());
        AddElement(19, element);
    }

    bool OptionAoipSelectedCodecTarget() const
    {
        return Contains(19);
    }

    const AoIPCodec& GetAoipSelectedCodecTarget() const
    {
        ITS_REQUIRE(OptionAoipSelectedCodecTarget());
        return static_cast<const AoIPCodec&> (ElementAt(19));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_FORWARD_ACCESS_SIGNALLING_ARG_H_)

