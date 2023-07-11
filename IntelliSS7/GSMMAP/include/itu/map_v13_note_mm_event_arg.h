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


#if !defined(_MAP_V13_NOTE_MM_EVENT_ARG_H_)
#define _MAP_V13_NOTE_MM_EVENT_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnInteger.h>
#include <AsnOctetString.h>
#include <AsnBitString.h>

#include <map_v13_service_key.h>
#include <map_v13_mm_code.h>
#include <map_v13_imsi.h>
#include <map_v13_isdn_address_string.h>
#include <map_v13_location_information.h>
#include <map_v13_supported_camel_phases.h>
#include <map_v13_extension_container.h>
#include <map_v13_location_information_gprs.h>
#include <map_v13_offered_camel4_functionalities.h>



namespace map_v13 {



class NoteMM_EventArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::ServiceKey ServiceKey;


        typedef map_v13::MM_Code MM_Code;


        typedef map_v13::IMSI IMSI;


        typedef map_v13::ISDN_AddressString ISDN_AddressString;


        typedef map_v13::LocationInformation LocationInformation;


        typedef map_v13::SupportedCamelPhases SupportedCamelPhases;


        typedef map_v13::ExtensionContainer ExtensionContainer;


        typedef map_v13::LocationInformationGPRS LocationInformationGPRS;


        typedef map_v13::OfferedCamel4Functionalities OfferedCamel4Functionalities;


////////// End Nested Class(es) //////////

    NoteMM_EventArg() : its::AsnSequence(9, false)
    {
        Initialize();
    }

    NoteMM_EventArg(its::Octets& octets) : its::AsnSequence(9, false)
    {
        Initialize();
        Decode(octets);
    }

    NoteMM_EventArg(const NoteMM_EventArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    NoteMM_EventArg(its::AsnDescObject* description) : its::AsnSequence(9, description)
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

    static its::AsnDescObject* GetServiceKeyStaticDescription();
    static its::AsnDescObject* GetEventMetStaticDescription();
    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetMsisdnStaticDescription();
    static its::AsnDescObject* GetLocationInformationStaticDescription();
    static its::AsnDescObject* GetSupportedCAMELPhasesStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetLocationInformationGPRSStaticDescription();
    static its::AsnDescObject* GetOfferedCamel4FunctionalitiesStaticDescription();

public:

    virtual ~NoteMM_EventArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new NoteMM_EventArg(*this);
    }

    virtual std::string GetName() const
    { return "NoteMM_EventArg"; }

    void SetServiceKey(ServiceKey* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetServiceKeyStaticDescription());
        AddElement(0, element);
    }

    void SetServiceKey(const ServiceKey& element)
    {
        its::AsnObject& asnObject = const_cast<ServiceKey&>(element);
        asnObject.SetDescription(GetServiceKeyStaticDescription());
        AddElement(0, element);
    }

    const ServiceKey& GetServiceKey() const
    {
        return static_cast<const ServiceKey&> (ElementAt(0));
    }

    void SetEventMet(MM_Code* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEventMetStaticDescription());
        AddElement(1, element);
    }

    void SetEventMet(const MM_Code& element)
    {
        its::AsnObject& asnObject = const_cast<MM_Code&>(element);
        asnObject.SetDescription(GetEventMetStaticDescription());
        AddElement(1, element);
    }

    const MM_Code& GetEventMet() const
    {
        return static_cast<const MM_Code&> (ElementAt(1));
    }

    void SetImsi(IMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImsiStaticDescription());
        AddElement(2, element);
    }

    void SetImsi(const IMSI& element)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(element);
        asnObject.SetDescription(GetImsiStaticDescription());
        AddElement(2, element);
    }

    const IMSI& GetImsi() const
    {
        return static_cast<const IMSI&> (ElementAt(2));
    }

    void SetMsisdn(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMsisdnStaticDescription());
        AddElement(3, element);
    }

    void SetMsisdn(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetMsisdnStaticDescription());
        AddElement(3, element);
    }

    const ISDN_AddressString& GetMsisdn() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(3));
    }

    void SetLocationInformation(LocationInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLocationInformationStaticDescription());
        AddElement(4, element);
    }

    void SetLocationInformation(const LocationInformation& element)
    {
        its::AsnObject& asnObject = const_cast<LocationInformation&>(element);
        asnObject.SetDescription(GetLocationInformationStaticDescription());
        AddElement(4, element);
    }

    bool OptionLocationInformation() const
    {
        return Contains(4);
    }

    const LocationInformation& GetLocationInformation() const
    {
        ITS_REQUIRE(OptionLocationInformation());
        return static_cast<const LocationInformation&> (ElementAt(4));
    }

    void SetSupportedCAMELPhases(SupportedCamelPhases* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSupportedCAMELPhasesStaticDescription());
        AddElement(5, element);
    }

    void SetSupportedCAMELPhases(const SupportedCamelPhases& element)
    {
        its::AsnObject& asnObject = const_cast<SupportedCamelPhases&>(element);
        asnObject.SetDescription(GetSupportedCAMELPhasesStaticDescription());
        AddElement(5, element);
    }

    bool OptionSupportedCAMELPhases() const
    {
        return Contains(5);
    }

    const SupportedCamelPhases& GetSupportedCAMELPhases() const
    {
        ITS_REQUIRE(OptionSupportedCAMELPhases());
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

    void SetLocationInformationGPRS(LocationInformationGPRS* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLocationInformationGPRSStaticDescription());
        AddElement(7, element);
    }

    void SetLocationInformationGPRS(const LocationInformationGPRS& element)
    {
        its::AsnObject& asnObject = const_cast<LocationInformationGPRS&>(element);
        asnObject.SetDescription(GetLocationInformationGPRSStaticDescription());
        AddElement(7, element);
    }

    bool OptionLocationInformationGPRS() const
    {
        return Contains(7);
    }

    const LocationInformationGPRS& GetLocationInformationGPRS() const
    {
        ITS_REQUIRE(OptionLocationInformationGPRS());
        return static_cast<const LocationInformationGPRS&> (ElementAt(7));
    }

    void SetOfferedCamel4Functionalities(OfferedCamel4Functionalities* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOfferedCamel4FunctionalitiesStaticDescription());
        AddElement(8, element);
    }

    void SetOfferedCamel4Functionalities(const OfferedCamel4Functionalities& element)
    {
        its::AsnObject& asnObject = const_cast<OfferedCamel4Functionalities&>(element);
        asnObject.SetDescription(GetOfferedCamel4FunctionalitiesStaticDescription());
        AddElement(8, element);
    }

    bool OptionOfferedCamel4Functionalities() const
    {
        return Contains(8);
    }

    const OfferedCamel4Functionalities& GetOfferedCamel4Functionalities() const
    {
        ITS_REQUIRE(OptionOfferedCamel4Functionalities());
        return static_cast<const OfferedCamel4Functionalities&> (ElementAt(8));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_NOTE_MM_EVENT_ARG_H_)

