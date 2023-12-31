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


#if !defined(_MAP_V9_PROVIDE_ROAMING_NUMBER_ARG_H_)
#define _MAP_V9_PROVIDE_ROAMING_NUMBER_ARG_H_

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
#include <AsnBitString.h>

#include <map_v9_imsi.h>
#include <map_v9_isdn_address_string.h>
#include <map_v9_lmsi.h>
#include <map_v9_external_signal_info.h>
#include <map_v9_suppression_of_announcement.h>
#include <map_v9_call_reference_number.h>
#include <map_v9_extension_container.h>
#include <map_v9_alerting_pattern.h>
#include <map_v9_supported_camel_phases.h>
#include <map_v9_ext_external_signal_info.h>
#include <map_v9_offered_camel4cs_is.h>



namespace map_v9 {



class ProvideRoamingNumberArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Or_Interrogation : public its::AsnNull
    {
    public:

        Or_Interrogation() : its::AsnNull(false)
        {
            Initialize();
        }

        Or_Interrogation(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Or_Interrogation(const Or_Interrogation& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Or_Interrogation(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Or_Interrogation()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Or_Interrogation(*this);
        }

        virtual std::string GetName() const
        { return "Or_Interrogation"; }

    };



    class Ccbs_Call : public its::AsnNull
    {
    public:

        Ccbs_Call() : its::AsnNull(false)
        {
            Initialize();
        }

        Ccbs_Call(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Ccbs_Call(const Ccbs_Call& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Ccbs_Call(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Ccbs_Call()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Ccbs_Call(*this);
        }

        virtual std::string GetName() const
        { return "Ccbs_Call"; }

    };



    class OrNotSupportedInGMSC : public its::AsnNull
    {
    public:

        OrNotSupportedInGMSC() : its::AsnNull(false)
        {
            Initialize();
        }

        OrNotSupportedInGMSC(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        OrNotSupportedInGMSC(const OrNotSupportedInGMSC& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        OrNotSupportedInGMSC(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~OrNotSupportedInGMSC()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new OrNotSupportedInGMSC(*this);
        }

        virtual std::string GetName() const
        { return "OrNotSupportedInGMSC"; }

    };



    class Pre_pagingSupported : public its::AsnNull
    {
    public:

        Pre_pagingSupported() : its::AsnNull(false)
        {
            Initialize();
        }

        Pre_pagingSupported(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Pre_pagingSupported(const Pre_pagingSupported& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Pre_pagingSupported(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Pre_pagingSupported()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Pre_pagingSupported(*this);
        }

        virtual std::string GetName() const
        { return "Pre_pagingSupported"; }

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



    class Suppress_VT_CSI : public its::AsnNull
    {
    public:

        Suppress_VT_CSI() : its::AsnNull(false)
        {
            Initialize();
        }

        Suppress_VT_CSI(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Suppress_VT_CSI(const Suppress_VT_CSI& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Suppress_VT_CSI(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Suppress_VT_CSI()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Suppress_VT_CSI(*this);
        }

        virtual std::string GetName() const
        { return "Suppress_VT_CSI"; }

    };


        typedef map_v9::IMSI IMSI;


        typedef map_v9::ISDN_AddressString ISDN_AddressString;


        typedef map_v9::LMSI LMSI;


        typedef map_v9::ExternalSignalInfo ExternalSignalInfo;


        typedef map_v9::SuppressionOfAnnouncement SuppressionOfAnnouncement;


        typedef map_v9::CallReferenceNumber CallReferenceNumber;


        typedef map_v9::ExtensionContainer ExtensionContainer;


        typedef map_v9::AlertingPattern AlertingPattern;


        typedef map_v9::SupportedCamelPhases SupportedCamelPhases;


        typedef map_v9::Ext_ExternalSignalInfo Ext_ExternalSignalInfo;


        typedef map_v9::OfferedCamel4CSIs OfferedCamel4CSIs;


////////// End Nested Class(es) //////////

    ProvideRoamingNumberArg() : its::AsnSequence(20, false)
    {
        Initialize();
    }

    ProvideRoamingNumberArg(its::Octets& octets) : its::AsnSequence(20, false)
    {
        Initialize();
        Decode(octets);
    }

    ProvideRoamingNumberArg(const ProvideRoamingNumberArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ProvideRoamingNumberArg(its::AsnDescObject* description) : its::AsnSequence(20, description)
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

    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetMsc_NumberStaticDescription();
    static its::AsnDescObject* GetMsisdnStaticDescription();
    static its::AsnDescObject* GetLmsiStaticDescription();
    static its::AsnDescObject* GetGsm_BearerCapabilityStaticDescription();
    static its::AsnDescObject* GetNetworkSignalInfoStaticDescription();
    static its::AsnDescObject* GetSuppressionOfAnnouncementStaticDescription();
    static its::AsnDescObject* GetGmsc_AddressStaticDescription();
    static its::AsnDescObject* GetCallReferenceNumberStaticDescription();
    static its::AsnDescObject* GetOr_InterrogationStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetAlertingPatternStaticDescription();
    static its::AsnDescObject* GetCcbs_CallStaticDescription();
    static its::AsnDescObject* GetSupportedCamelPhasesInInterrogatingNodeStaticDescription();
    static its::AsnDescObject* GetAdditionalSignalInfoStaticDescription();
    static its::AsnDescObject* GetOrNotSupportedInGMSCStaticDescription();
    static its::AsnDescObject* GetPre_pagingSupportedStaticDescription();
    static its::AsnDescObject* GetLongFTN_SupportedStaticDescription();
    static its::AsnDescObject* GetSuppress_VT_CSIStaticDescription();
    static its::AsnDescObject* GetOfferedCamel4CSIsInInterrogatingNodeStaticDescription();

public:

    virtual ~ProvideRoamingNumberArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ProvideRoamingNumberArg(*this);
    }

    virtual std::string GetName() const
    { return "ProvideRoamingNumberArg"; }

    void SetImsi(IMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    void SetImsi(const IMSI& element)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(element);
        asnObject.SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    const IMSI& GetImsi() const
    {
        return static_cast<const IMSI&> (ElementAt(0));
    }

    void SetMsc_Number(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMsc_NumberStaticDescription());
        AddElement(1, element);
    }

    void SetMsc_Number(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetMsc_NumberStaticDescription());
        AddElement(1, element);
    }

    const ISDN_AddressString& GetMsc_Number() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(1));
    }

    void SetMsisdn(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMsisdnStaticDescription());
        AddElement(2, element);
    }

    void SetMsisdn(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetMsisdnStaticDescription());
        AddElement(2, element);
    }

    bool OptionMsisdn() const
    {
        return Contains(2);
    }

    const ISDN_AddressString& GetMsisdn() const
    {
        ITS_REQUIRE(OptionMsisdn());
        return static_cast<const ISDN_AddressString&> (ElementAt(2));
    }

    void SetLmsi(LMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLmsiStaticDescription());
        AddElement(3, element);
    }

    void SetLmsi(const LMSI& element)
    {
        its::AsnObject& asnObject = const_cast<LMSI&>(element);
        asnObject.SetDescription(GetLmsiStaticDescription());
        AddElement(3, element);
    }

    bool OptionLmsi() const
    {
        return Contains(3);
    }

    const LMSI& GetLmsi() const
    {
        ITS_REQUIRE(OptionLmsi());
        return static_cast<const LMSI&> (ElementAt(3));
    }

    void SetGsm_BearerCapability(ExternalSignalInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGsm_BearerCapabilityStaticDescription());
        AddElement(4, element);
    }

    void SetGsm_BearerCapability(const ExternalSignalInfo& element)
    {
        its::AsnObject& asnObject = const_cast<ExternalSignalInfo&>(element);
        asnObject.SetDescription(GetGsm_BearerCapabilityStaticDescription());
        AddElement(4, element);
    }

    bool OptionGsm_BearerCapability() const
    {
        return Contains(4);
    }

    const ExternalSignalInfo& GetGsm_BearerCapability() const
    {
        ITS_REQUIRE(OptionGsm_BearerCapability());
        return static_cast<const ExternalSignalInfo&> (ElementAt(4));
    }

    void SetNetworkSignalInfo(ExternalSignalInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNetworkSignalInfoStaticDescription());
        AddElement(5, element);
    }

    void SetNetworkSignalInfo(const ExternalSignalInfo& element)
    {
        its::AsnObject& asnObject = const_cast<ExternalSignalInfo&>(element);
        asnObject.SetDescription(GetNetworkSignalInfoStaticDescription());
        AddElement(5, element);
    }

    bool OptionNetworkSignalInfo() const
    {
        return Contains(5);
    }

    const ExternalSignalInfo& GetNetworkSignalInfo() const
    {
        ITS_REQUIRE(OptionNetworkSignalInfo());
        return static_cast<const ExternalSignalInfo&> (ElementAt(5));
    }

    void SetSuppressionOfAnnouncement(SuppressionOfAnnouncement* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSuppressionOfAnnouncementStaticDescription());
        AddElement(6, element);
    }

    void SetSuppressionOfAnnouncement(const SuppressionOfAnnouncement& element)
    {
        its::AsnObject& asnObject = const_cast<SuppressionOfAnnouncement&>(element);
        asnObject.SetDescription(GetSuppressionOfAnnouncementStaticDescription());
        AddElement(6, element);
    }

    bool OptionSuppressionOfAnnouncement() const
    {
        return Contains(6);
    }

    const SuppressionOfAnnouncement& GetSuppressionOfAnnouncement() const
    {
        ITS_REQUIRE(OptionSuppressionOfAnnouncement());
        return static_cast<const SuppressionOfAnnouncement&> (ElementAt(6));
    }

    void SetGmsc_Address(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGmsc_AddressStaticDescription());
        AddElement(7, element);
    }

    void SetGmsc_Address(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetGmsc_AddressStaticDescription());
        AddElement(7, element);
    }

    bool OptionGmsc_Address() const
    {
        return Contains(7);
    }

    const ISDN_AddressString& GetGmsc_Address() const
    {
        ITS_REQUIRE(OptionGmsc_Address());
        return static_cast<const ISDN_AddressString&> (ElementAt(7));
    }

    void SetCallReferenceNumber(CallReferenceNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallReferenceNumberStaticDescription());
        AddElement(8, element);
    }

    void SetCallReferenceNumber(const CallReferenceNumber& element)
    {
        its::AsnObject& asnObject = const_cast<CallReferenceNumber&>(element);
        asnObject.SetDescription(GetCallReferenceNumberStaticDescription());
        AddElement(8, element);
    }

    bool OptionCallReferenceNumber() const
    {
        return Contains(8);
    }

    const CallReferenceNumber& GetCallReferenceNumber() const
    {
        ITS_REQUIRE(OptionCallReferenceNumber());
        return static_cast<const CallReferenceNumber&> (ElementAt(8));
    }

    void SetOr_Interrogation(Or_Interrogation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOr_InterrogationStaticDescription());
        AddElement(9, element);
    }

    void SetOr_Interrogation(const Or_Interrogation& element)
    {
        its::AsnObject& asnObject = const_cast<Or_Interrogation&>(element);
        asnObject.SetDescription(GetOr_InterrogationStaticDescription());
        AddElement(9, element);
    }

    bool OptionOr_Interrogation() const
    {
        return Contains(9);
    }

    const Or_Interrogation& GetOr_Interrogation() const
    {
        ITS_REQUIRE(OptionOr_Interrogation());
        return static_cast<const Or_Interrogation&> (ElementAt(9));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(10, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(10, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(10);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(10));
    }

    void SetAlertingPattern(AlertingPattern* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAlertingPatternStaticDescription());
        AddElement(11, element);
    }

    void SetAlertingPattern(const AlertingPattern& element)
    {
        its::AsnObject& asnObject = const_cast<AlertingPattern&>(element);
        asnObject.SetDescription(GetAlertingPatternStaticDescription());
        AddElement(11, element);
    }

    bool OptionAlertingPattern() const
    {
        return Contains(11);
    }

    const AlertingPattern& GetAlertingPattern() const
    {
        ITS_REQUIRE(OptionAlertingPattern());
        return static_cast<const AlertingPattern&> (ElementAt(11));
    }

    void SetCcbs_Call(Ccbs_Call* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCcbs_CallStaticDescription());
        AddElement(12, element);
    }

    void SetCcbs_Call(const Ccbs_Call& element)
    {
        its::AsnObject& asnObject = const_cast<Ccbs_Call&>(element);
        asnObject.SetDescription(GetCcbs_CallStaticDescription());
        AddElement(12, element);
    }

    bool OptionCcbs_Call() const
    {
        return Contains(12);
    }

    const Ccbs_Call& GetCcbs_Call() const
    {
        ITS_REQUIRE(OptionCcbs_Call());
        return static_cast<const Ccbs_Call&> (ElementAt(12));
    }

    void SetSupportedCamelPhasesInInterrogatingNode(SupportedCamelPhases* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSupportedCamelPhasesInInterrogatingNodeStaticDescription());
        AddElement(13, element);
    }

    void SetSupportedCamelPhasesInInterrogatingNode(const SupportedCamelPhases& element)
    {
        its::AsnObject& asnObject = const_cast<SupportedCamelPhases&>(element);
        asnObject.SetDescription(GetSupportedCamelPhasesInInterrogatingNodeStaticDescription());
        AddElement(13, element);
    }

    bool OptionSupportedCamelPhasesInInterrogatingNode() const
    {
        return Contains(13);
    }

    const SupportedCamelPhases& GetSupportedCamelPhasesInInterrogatingNode() const
    {
        ITS_REQUIRE(OptionSupportedCamelPhasesInInterrogatingNode());
        return static_cast<const SupportedCamelPhases&> (ElementAt(13));
    }

    void SetAdditionalSignalInfo(Ext_ExternalSignalInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAdditionalSignalInfoStaticDescription());
        AddElement(14, element);
    }

    void SetAdditionalSignalInfo(const Ext_ExternalSignalInfo& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_ExternalSignalInfo&>(element);
        asnObject.SetDescription(GetAdditionalSignalInfoStaticDescription());
        AddElement(14, element);
    }

    bool OptionAdditionalSignalInfo() const
    {
        return Contains(14);
    }

    const Ext_ExternalSignalInfo& GetAdditionalSignalInfo() const
    {
        ITS_REQUIRE(OptionAdditionalSignalInfo());
        return static_cast<const Ext_ExternalSignalInfo&> (ElementAt(14));
    }

    void SetOrNotSupportedInGMSC(OrNotSupportedInGMSC* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOrNotSupportedInGMSCStaticDescription());
        AddElement(15, element);
    }

    void SetOrNotSupportedInGMSC(const OrNotSupportedInGMSC& element)
    {
        its::AsnObject& asnObject = const_cast<OrNotSupportedInGMSC&>(element);
        asnObject.SetDescription(GetOrNotSupportedInGMSCStaticDescription());
        AddElement(15, element);
    }

    bool OptionOrNotSupportedInGMSC() const
    {
        return Contains(15);
    }

    const OrNotSupportedInGMSC& GetOrNotSupportedInGMSC() const
    {
        ITS_REQUIRE(OptionOrNotSupportedInGMSC());
        return static_cast<const OrNotSupportedInGMSC&> (ElementAt(15));
    }

    void SetPre_pagingSupported(Pre_pagingSupported* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPre_pagingSupportedStaticDescription());
        AddElement(16, element);
    }

    void SetPre_pagingSupported(const Pre_pagingSupported& element)
    {
        its::AsnObject& asnObject = const_cast<Pre_pagingSupported&>(element);
        asnObject.SetDescription(GetPre_pagingSupportedStaticDescription());
        AddElement(16, element);
    }

    bool OptionPre_pagingSupported() const
    {
        return Contains(16);
    }

    const Pre_pagingSupported& GetPre_pagingSupported() const
    {
        ITS_REQUIRE(OptionPre_pagingSupported());
        return static_cast<const Pre_pagingSupported&> (ElementAt(16));
    }

    void SetLongFTN_Supported(LongFTN_Supported* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLongFTN_SupportedStaticDescription());
        AddElement(17, element);
    }

    void SetLongFTN_Supported(const LongFTN_Supported& element)
    {
        its::AsnObject& asnObject = const_cast<LongFTN_Supported&>(element);
        asnObject.SetDescription(GetLongFTN_SupportedStaticDescription());
        AddElement(17, element);
    }

    bool OptionLongFTN_Supported() const
    {
        return Contains(17);
    }

    const LongFTN_Supported& GetLongFTN_Supported() const
    {
        ITS_REQUIRE(OptionLongFTN_Supported());
        return static_cast<const LongFTN_Supported&> (ElementAt(17));
    }

    void SetSuppress_VT_CSI(Suppress_VT_CSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSuppress_VT_CSIStaticDescription());
        AddElement(18, element);
    }

    void SetSuppress_VT_CSI(const Suppress_VT_CSI& element)
    {
        its::AsnObject& asnObject = const_cast<Suppress_VT_CSI&>(element);
        asnObject.SetDescription(GetSuppress_VT_CSIStaticDescription());
        AddElement(18, element);
    }

    bool OptionSuppress_VT_CSI() const
    {
        return Contains(18);
    }

    const Suppress_VT_CSI& GetSuppress_VT_CSI() const
    {
        ITS_REQUIRE(OptionSuppress_VT_CSI());
        return static_cast<const Suppress_VT_CSI&> (ElementAt(18));
    }

    void SetOfferedCamel4CSIsInInterrogatingNode(OfferedCamel4CSIs* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOfferedCamel4CSIsInInterrogatingNodeStaticDescription());
        AddElement(19, element);
    }

    void SetOfferedCamel4CSIsInInterrogatingNode(const OfferedCamel4CSIs& element)
    {
        its::AsnObject& asnObject = const_cast<OfferedCamel4CSIs&>(element);
        asnObject.SetDescription(GetOfferedCamel4CSIsInInterrogatingNodeStaticDescription());
        AddElement(19, element);
    }

    bool OptionOfferedCamel4CSIsInInterrogatingNode() const
    {
        return Contains(19);
    }

    const OfferedCamel4CSIs& GetOfferedCamel4CSIsInInterrogatingNode() const
    {
        ITS_REQUIRE(OptionOfferedCamel4CSIsInInterrogatingNode());
        return static_cast<const OfferedCamel4CSIs&> (ElementAt(19));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_PROVIDE_ROAMING_NUMBER_ARG_H_)

