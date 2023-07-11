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


#if !defined(_MAP_V13_PROCESS_ACCESS_SIGNALLING_ARG_H_)
#define _MAP_V13_PROCESS_ACCESS_SIGNALLING_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnInteger.h>

#include <map_v13_access_network_signal_info.h>
#include <map_v13_selected_umts_algorithms.h>
#include <map_v13_selected_gsm_algorithm.h>
#include <map_v13_chosen_radio_resource_information.h>
#include <map_v13_rab_id.h>
#include <map_v13_extension_container.h>
#include <map_v13_codec.h>
#include <map_v13_codec_list.h>
#include <map_v13_ao_ip_codec.h>
#include <map_v13_ao_ip_codecs_list.h>



namespace map_v13 {



class ProcessAccessSignalling_Arg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::AccessNetworkSignalInfo AccessNetworkSignalInfo;


        typedef map_v13::SelectedUMTS_Algorithms SelectedUMTS_Algorithms;


        typedef map_v13::SelectedGSM_Algorithm SelectedGSM_Algorithm;


        typedef map_v13::ChosenRadioResourceInformation ChosenRadioResourceInformation;


        typedef map_v13::RAB_Id RAB_Id;


        typedef map_v13::ExtensionContainer ExtensionContainer;


        typedef map_v13::Codec Codec;


        typedef map_v13::CodecList CodecList;


        typedef map_v13::AoIPCodec AoIPCodec;


        typedef map_v13::AoIPCodecsList AoIPCodecsList;


////////// End Nested Class(es) //////////

    ProcessAccessSignalling_Arg() : its::AsnSequence(10, false)
    {
        Initialize();
    }

    ProcessAccessSignalling_Arg(its::Octets& octets) : its::AsnSequence(10, false)
    {
        Initialize();
        Decode(octets);
    }

    ProcessAccessSignalling_Arg(const ProcessAccessSignalling_Arg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ProcessAccessSignalling_Arg(its::AsnDescObject* description) : its::AsnSequence(10, description)
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
    static its::AsnDescObject* GetSelectedUMTS_AlgorithmsStaticDescription();
    static its::AsnDescObject* GetSelectedGSM_AlgorithmStaticDescription();
    static its::AsnDescObject* GetChosenRadioResourceInformationStaticDescription();
    static its::AsnDescObject* GetSelectedRab_IdStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetIUSelectedCodecStaticDescription();
    static its::AsnDescObject* GetIuAvailableCodecsListStaticDescription();
    static its::AsnDescObject* GetAoipSelectedCodecTargetStaticDescription();
    static its::AsnDescObject* GetAoipAvailableCodecsListMapStaticDescription();

public:

    virtual ~ProcessAccessSignalling_Arg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ProcessAccessSignalling_Arg(*this);
    }

    virtual std::string GetName() const
    { return "ProcessAccessSignalling_Arg"; }

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

    void SetSelectedUMTS_Algorithms(SelectedUMTS_Algorithms* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSelectedUMTS_AlgorithmsStaticDescription());
        AddElement(1, element);
    }

    void SetSelectedUMTS_Algorithms(const SelectedUMTS_Algorithms& element)
    {
        its::AsnObject& asnObject = const_cast<SelectedUMTS_Algorithms&>(element);
        asnObject.SetDescription(GetSelectedUMTS_AlgorithmsStaticDescription());
        AddElement(1, element);
    }

    bool OptionSelectedUMTS_Algorithms() const
    {
        return Contains(1);
    }

    const SelectedUMTS_Algorithms& GetSelectedUMTS_Algorithms() const
    {
        ITS_REQUIRE(OptionSelectedUMTS_Algorithms());
        return static_cast<const SelectedUMTS_Algorithms&> (ElementAt(1));
    }

    void SetSelectedGSM_Algorithm(SelectedGSM_Algorithm* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSelectedGSM_AlgorithmStaticDescription());
        AddElement(2, element);
    }

    void SetSelectedGSM_Algorithm(const SelectedGSM_Algorithm& element)
    {
        its::AsnObject& asnObject = const_cast<SelectedGSM_Algorithm&>(element);
        asnObject.SetDescription(GetSelectedGSM_AlgorithmStaticDescription());
        AddElement(2, element);
    }

    bool OptionSelectedGSM_Algorithm() const
    {
        return Contains(2);
    }

    const SelectedGSM_Algorithm& GetSelectedGSM_Algorithm() const
    {
        ITS_REQUIRE(OptionSelectedGSM_Algorithm());
        return static_cast<const SelectedGSM_Algorithm&> (ElementAt(2));
    }

    void SetChosenRadioResourceInformation(ChosenRadioResourceInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetChosenRadioResourceInformationStaticDescription());
        AddElement(3, element);
    }

    void SetChosenRadioResourceInformation(const ChosenRadioResourceInformation& element)
    {
        its::AsnObject& asnObject = const_cast<ChosenRadioResourceInformation&>(element);
        asnObject.SetDescription(GetChosenRadioResourceInformationStaticDescription());
        AddElement(3, element);
    }

    bool OptionChosenRadioResourceInformation() const
    {
        return Contains(3);
    }

    const ChosenRadioResourceInformation& GetChosenRadioResourceInformation() const
    {
        ITS_REQUIRE(OptionChosenRadioResourceInformation());
        return static_cast<const ChosenRadioResourceInformation&> (ElementAt(3));
    }

    void SetSelectedRab_Id(RAB_Id* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSelectedRab_IdStaticDescription());
        AddElement(4, element);
    }

    void SetSelectedRab_Id(const RAB_Id& element)
    {
        its::AsnObject& asnObject = const_cast<RAB_Id&>(element);
        asnObject.SetDescription(GetSelectedRab_IdStaticDescription());
        AddElement(4, element);
    }

    bool OptionSelectedRab_Id() const
    {
        return Contains(4);
    }

    const RAB_Id& GetSelectedRab_Id() const
    {
        ITS_REQUIRE(OptionSelectedRab_Id());
        return static_cast<const RAB_Id&> (ElementAt(4));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(5, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(5, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(5);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(5));
    }

    void SetIUSelectedCodec(Codec* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIUSelectedCodecStaticDescription());
        AddElement(6, element);
    }

    void SetIUSelectedCodec(const Codec& element)
    {
        its::AsnObject& asnObject = const_cast<Codec&>(element);
        asnObject.SetDescription(GetIUSelectedCodecStaticDescription());
        AddElement(6, element);
    }

    bool OptionIUSelectedCodec() const
    {
        return Contains(6);
    }

    const Codec& GetIUSelectedCodec() const
    {
        ITS_REQUIRE(OptionIUSelectedCodec());
        return static_cast<const Codec&> (ElementAt(6));
    }

    void SetIuAvailableCodecsList(CodecList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIuAvailableCodecsListStaticDescription());
        AddElement(7, element);
    }

    void SetIuAvailableCodecsList(const CodecList& element)
    {
        its::AsnObject& asnObject = const_cast<CodecList&>(element);
        asnObject.SetDescription(GetIuAvailableCodecsListStaticDescription());
        AddElement(7, element);
    }

    bool OptionIuAvailableCodecsList() const
    {
        return Contains(7);
    }

    const CodecList& GetIuAvailableCodecsList() const
    {
        ITS_REQUIRE(OptionIuAvailableCodecsList());
        return static_cast<const CodecList&> (ElementAt(7));
    }

    void SetAoipSelectedCodecTarget(AoIPCodec* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAoipSelectedCodecTargetStaticDescription());
        AddElement(8, element);
    }

    void SetAoipSelectedCodecTarget(const AoIPCodec& element)
    {
        its::AsnObject& asnObject = const_cast<AoIPCodec&>(element);
        asnObject.SetDescription(GetAoipSelectedCodecTargetStaticDescription());
        AddElement(8, element);
    }

    bool OptionAoipSelectedCodecTarget() const
    {
        return Contains(8);
    }

    const AoIPCodec& GetAoipSelectedCodecTarget() const
    {
        ITS_REQUIRE(OptionAoipSelectedCodecTarget());
        return static_cast<const AoIPCodec&> (ElementAt(8));
    }

    void SetAoipAvailableCodecsListMap(AoIPCodecsList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAoipAvailableCodecsListMapStaticDescription());
        AddElement(9, element);
    }

    void SetAoipAvailableCodecsListMap(const AoIPCodecsList& element)
    {
        its::AsnObject& asnObject = const_cast<AoIPCodecsList&>(element);
        asnObject.SetDescription(GetAoipAvailableCodecsListMapStaticDescription());
        AddElement(9, element);
    }

    bool OptionAoipAvailableCodecsListMap() const
    {
        return Contains(9);
    }

    const AoIPCodecsList& GetAoipAvailableCodecsListMap() const
    {
        ITS_REQUIRE(OptionAoipAvailableCodecsListMap());
        return static_cast<const AoIPCodecsList&> (ElementAt(9));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_PROCESS_ACCESS_SIGNALLING_ARG_H_)
