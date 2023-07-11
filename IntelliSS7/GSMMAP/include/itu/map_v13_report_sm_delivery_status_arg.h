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


#if !defined(_MAP_V13_REPORT_SM_DELIVERY_STATUS_ARG_H_)
#define _MAP_V13_REPORT_SM_DELIVERY_STATUS_ARG_H_

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
#include <AsnInteger.h>

#include <map_v13_isdn_address_string.h>
#include <map_v13_address_string.h>
#include <map_v13_sm_delivery_outcome.h>
#include <map_v13_absent_subscriber_diagnostic_sm.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class ReportSM_DeliveryStatusArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class GprsSupportIndicator : public its::AsnNull
    {
    public:

        GprsSupportIndicator() : its::AsnNull(false)
        {
            Initialize();
        }

        GprsSupportIndicator(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        GprsSupportIndicator(const GprsSupportIndicator& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        GprsSupportIndicator(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~GprsSupportIndicator()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new GprsSupportIndicator(*this);
        }

        virtual std::string GetName() const
        { return "GprsSupportIndicator"; }

    };



    class DeliveryOutcomeIndicator : public its::AsnNull
    {
    public:

        DeliveryOutcomeIndicator() : its::AsnNull(false)
        {
            Initialize();
        }

        DeliveryOutcomeIndicator(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        DeliveryOutcomeIndicator(const DeliveryOutcomeIndicator& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        DeliveryOutcomeIndicator(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~DeliveryOutcomeIndicator()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new DeliveryOutcomeIndicator(*this);
        }

        virtual std::string GetName() const
        { return "DeliveryOutcomeIndicator"; }

    };



    class Ip_sm_gw_Indicator : public its::AsnNull
    {
    public:

        Ip_sm_gw_Indicator() : its::AsnNull(false)
        {
            Initialize();
        }

        Ip_sm_gw_Indicator(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Ip_sm_gw_Indicator(const Ip_sm_gw_Indicator& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Ip_sm_gw_Indicator(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Ip_sm_gw_Indicator()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Ip_sm_gw_Indicator(*this);
        }

        virtual std::string GetName() const
        { return "Ip_sm_gw_Indicator"; }

    };


        typedef map_v13::ISDN_AddressString ISDN_AddressString;


        typedef map_v13::AddressString AddressString;


        typedef map_v13::SM_DeliveryOutcome SM_DeliveryOutcome;


        typedef map_v13::AbsentSubscriberDiagnosticSM AbsentSubscriberDiagnosticSM;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    ReportSM_DeliveryStatusArg() : its::AsnSequence(12, false)
    {
        Initialize();
    }

    ReportSM_DeliveryStatusArg(its::Octets& octets) : its::AsnSequence(12, false)
    {
        Initialize();
        Decode(octets);
    }

    ReportSM_DeliveryStatusArg(const ReportSM_DeliveryStatusArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ReportSM_DeliveryStatusArg(its::AsnDescObject* description) : its::AsnSequence(12, description)
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

    static its::AsnDescObject* GetMsisdnStaticDescription();
    static its::AsnDescObject* GetServiceCentreAddressStaticDescription();
    static its::AsnDescObject* GetSm_DeliveryOutcomeStaticDescription();
    static its::AsnDescObject* GetAbsentSubscriberDiagnosticSMStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetGprsSupportIndicatorStaticDescription();
    static its::AsnDescObject* GetDeliveryOutcomeIndicatorStaticDescription();
    static its::AsnDescObject* GetAdditionalSM_DeliveryOutcomeStaticDescription();
    static its::AsnDescObject* GetAdditionalAbsentSubscriberDiagnosticSMStaticDescription();
    static its::AsnDescObject* GetIp_sm_gw_IndicatorStaticDescription();
    static its::AsnDescObject* GetIp_sm_gw_sm_deliveryOutcomeStaticDescription();
    static its::AsnDescObject* GetIp_sm_gw_absentSubscriberDiagnosticSMStaticDescription();

public:

    virtual ~ReportSM_DeliveryStatusArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ReportSM_DeliveryStatusArg(*this);
    }

    virtual std::string GetName() const
    { return "ReportSM_DeliveryStatusArg"; }

    void SetMsisdn(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMsisdnStaticDescription());
        AddElement(0, element);
    }

    void SetMsisdn(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetMsisdnStaticDescription());
        AddElement(0, element);
    }

    const ISDN_AddressString& GetMsisdn() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
    }

    void SetServiceCentreAddress(AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetServiceCentreAddressStaticDescription());
        AddElement(1, element);
    }

    void SetServiceCentreAddress(const AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<AddressString&>(element);
        asnObject.SetDescription(GetServiceCentreAddressStaticDescription());
        AddElement(1, element);
    }

    const AddressString& GetServiceCentreAddress() const
    {
        return static_cast<const AddressString&> (ElementAt(1));
    }

    void SetSm_DeliveryOutcome(SM_DeliveryOutcome* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSm_DeliveryOutcomeStaticDescription());
        AddElement(2, element);
    }

    void SetSm_DeliveryOutcome(const SM_DeliveryOutcome& element)
    {
        its::AsnObject& asnObject = const_cast<SM_DeliveryOutcome&>(element);
        asnObject.SetDescription(GetSm_DeliveryOutcomeStaticDescription());
        AddElement(2, element);
    }

    const SM_DeliveryOutcome& GetSm_DeliveryOutcome() const
    {
        return static_cast<const SM_DeliveryOutcome&> (ElementAt(2));
    }

    void SetAbsentSubscriberDiagnosticSM(AbsentSubscriberDiagnosticSM* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAbsentSubscriberDiagnosticSMStaticDescription());
        AddElement(3, element);
    }

    void SetAbsentSubscriberDiagnosticSM(const AbsentSubscriberDiagnosticSM& element)
    {
        its::AsnObject& asnObject = const_cast<AbsentSubscriberDiagnosticSM&>(element);
        asnObject.SetDescription(GetAbsentSubscriberDiagnosticSMStaticDescription());
        AddElement(3, element);
    }

    bool OptionAbsentSubscriberDiagnosticSM() const
    {
        return Contains(3);
    }

    const AbsentSubscriberDiagnosticSM& GetAbsentSubscriberDiagnosticSM() const
    {
        ITS_REQUIRE(OptionAbsentSubscriberDiagnosticSM());
        return static_cast<const AbsentSubscriberDiagnosticSM&> (ElementAt(3));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(4, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(4, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(4);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(4));
    }

    void SetGprsSupportIndicator(GprsSupportIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGprsSupportIndicatorStaticDescription());
        AddElement(5, element);
    }

    void SetGprsSupportIndicator(const GprsSupportIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<GprsSupportIndicator&>(element);
        asnObject.SetDescription(GetGprsSupportIndicatorStaticDescription());
        AddElement(5, element);
    }

    bool OptionGprsSupportIndicator() const
    {
        return Contains(5);
    }

    const GprsSupportIndicator& GetGprsSupportIndicator() const
    {
        ITS_REQUIRE(OptionGprsSupportIndicator());
        return static_cast<const GprsSupportIndicator&> (ElementAt(5));
    }

    void SetDeliveryOutcomeIndicator(DeliveryOutcomeIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDeliveryOutcomeIndicatorStaticDescription());
        AddElement(6, element);
    }

    void SetDeliveryOutcomeIndicator(const DeliveryOutcomeIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<DeliveryOutcomeIndicator&>(element);
        asnObject.SetDescription(GetDeliveryOutcomeIndicatorStaticDescription());
        AddElement(6, element);
    }

    bool OptionDeliveryOutcomeIndicator() const
    {
        return Contains(6);
    }

    const DeliveryOutcomeIndicator& GetDeliveryOutcomeIndicator() const
    {
        ITS_REQUIRE(OptionDeliveryOutcomeIndicator());
        return static_cast<const DeliveryOutcomeIndicator&> (ElementAt(6));
    }

    void SetAdditionalSM_DeliveryOutcome(SM_DeliveryOutcome* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAdditionalSM_DeliveryOutcomeStaticDescription());
        AddElement(7, element);
    }

    void SetAdditionalSM_DeliveryOutcome(const SM_DeliveryOutcome& element)
    {
        its::AsnObject& asnObject = const_cast<SM_DeliveryOutcome&>(element);
        asnObject.SetDescription(GetAdditionalSM_DeliveryOutcomeStaticDescription());
        AddElement(7, element);
    }

    bool OptionAdditionalSM_DeliveryOutcome() const
    {
        return Contains(7);
    }

    const SM_DeliveryOutcome& GetAdditionalSM_DeliveryOutcome() const
    {
        ITS_REQUIRE(OptionAdditionalSM_DeliveryOutcome());
        return static_cast<const SM_DeliveryOutcome&> (ElementAt(7));
    }

    void SetAdditionalAbsentSubscriberDiagnosticSM(AbsentSubscriberDiagnosticSM* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAdditionalAbsentSubscriberDiagnosticSMStaticDescription());
        AddElement(8, element);
    }

    void SetAdditionalAbsentSubscriberDiagnosticSM(const AbsentSubscriberDiagnosticSM& element)
    {
        its::AsnObject& asnObject = const_cast<AbsentSubscriberDiagnosticSM&>(element);
        asnObject.SetDescription(GetAdditionalAbsentSubscriberDiagnosticSMStaticDescription());
        AddElement(8, element);
    }

    bool OptionAdditionalAbsentSubscriberDiagnosticSM() const
    {
        return Contains(8);
    }

    const AbsentSubscriberDiagnosticSM& GetAdditionalAbsentSubscriberDiagnosticSM() const
    {
        ITS_REQUIRE(OptionAdditionalAbsentSubscriberDiagnosticSM());
        return static_cast<const AbsentSubscriberDiagnosticSM&> (ElementAt(8));
    }

    void SetIp_sm_gw_Indicator(Ip_sm_gw_Indicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIp_sm_gw_IndicatorStaticDescription());
        AddElement(9, element);
    }

    void SetIp_sm_gw_Indicator(const Ip_sm_gw_Indicator& element)
    {
        its::AsnObject& asnObject = const_cast<Ip_sm_gw_Indicator&>(element);
        asnObject.SetDescription(GetIp_sm_gw_IndicatorStaticDescription());
        AddElement(9, element);
    }

    bool OptionIp_sm_gw_Indicator() const
    {
        return Contains(9);
    }

    const Ip_sm_gw_Indicator& GetIp_sm_gw_Indicator() const
    {
        ITS_REQUIRE(OptionIp_sm_gw_Indicator());
        return static_cast<const Ip_sm_gw_Indicator&> (ElementAt(9));
    }

    void SetIp_sm_gw_sm_deliveryOutcome(SM_DeliveryOutcome* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIp_sm_gw_sm_deliveryOutcomeStaticDescription());
        AddElement(10, element);
    }

    void SetIp_sm_gw_sm_deliveryOutcome(const SM_DeliveryOutcome& element)
    {
        its::AsnObject& asnObject = const_cast<SM_DeliveryOutcome&>(element);
        asnObject.SetDescription(GetIp_sm_gw_sm_deliveryOutcomeStaticDescription());
        AddElement(10, element);
    }

    bool OptionIp_sm_gw_sm_deliveryOutcome() const
    {
        return Contains(10);
    }

    const SM_DeliveryOutcome& GetIp_sm_gw_sm_deliveryOutcome() const
    {
        ITS_REQUIRE(OptionIp_sm_gw_sm_deliveryOutcome());
        return static_cast<const SM_DeliveryOutcome&> (ElementAt(10));
    }

    void SetIp_sm_gw_absentSubscriberDiagnosticSM(AbsentSubscriberDiagnosticSM* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIp_sm_gw_absentSubscriberDiagnosticSMStaticDescription());
        AddElement(11, element);
    }

    void SetIp_sm_gw_absentSubscriberDiagnosticSM(const AbsentSubscriberDiagnosticSM& element)
    {
        its::AsnObject& asnObject = const_cast<AbsentSubscriberDiagnosticSM&>(element);
        asnObject.SetDescription(GetIp_sm_gw_absentSubscriberDiagnosticSMStaticDescription());
        AddElement(11, element);
    }

    bool OptionIp_sm_gw_absentSubscriberDiagnosticSM() const
    {
        return Contains(11);
    }

    const AbsentSubscriberDiagnosticSM& GetIp_sm_gw_absentSubscriberDiagnosticSM() const
    {
        ITS_REQUIRE(OptionIp_sm_gw_absentSubscriberDiagnosticSM());
        return static_cast<const AbsentSubscriberDiagnosticSM&> (ElementAt(11));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_REPORT_SM_DELIVERY_STATUS_ARG_H_)

