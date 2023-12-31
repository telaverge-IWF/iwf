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


#if !defined(_MAP_V9_SGSN_CAMEL_SUBSCRIPTION_INFO_H_)
#define _MAP_V9_SGSN_CAMEL_SUBSCRIPTION_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>

#include <map_v9_gprs_csi.h>
#include <map_v9_sms_csi.h>
#include <map_v9_extension_container.h>
#include <map_v9_mt_sms_cameltdp_criteria_list.h>
#include <map_v9_mg_csi.h>



namespace map_v9 {



class SGSN_CAMEL_SubscriptionInfo : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::GPRS_CSI GPRS_CSI;


        typedef map_v9::SMS_CSI SMS_CSI;


        typedef map_v9::ExtensionContainer ExtensionContainer;


        typedef map_v9::MT_smsCAMELTDP_CriteriaList MT_smsCAMELTDP_CriteriaList;


        typedef map_v9::MG_CSI MG_CSI;


////////// End Nested Class(es) //////////

    SGSN_CAMEL_SubscriptionInfo() : its::AsnSequence(6, false)
    {
        Initialize();
    }

    SGSN_CAMEL_SubscriptionInfo(its::Octets& octets) : its::AsnSequence(6, false)
    {
        Initialize();
        Decode(octets);
    }

    SGSN_CAMEL_SubscriptionInfo(const SGSN_CAMEL_SubscriptionInfo& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SGSN_CAMEL_SubscriptionInfo(its::AsnDescObject* description) : its::AsnSequence(6, description)
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

    static its::AsnDescObject* GetGprs_CSIStaticDescription();
    static its::AsnDescObject* GetMo_sms_CSIStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetMt_sms_CSIStaticDescription();
    static its::AsnDescObject* GetMt_smsCAMELTDP_CriteriaListStaticDescription();
    static its::AsnDescObject* GetMg_csiStaticDescription();

public:

    virtual ~SGSN_CAMEL_SubscriptionInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SGSN_CAMEL_SubscriptionInfo(*this);
    }

    virtual std::string GetName() const
    { return "SGSN_CAMEL_SubscriptionInfo"; }

    void SetGprs_CSI(GPRS_CSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGprs_CSIStaticDescription());
        AddElement(0, element);
    }

    void SetGprs_CSI(const GPRS_CSI& element)
    {
        its::AsnObject& asnObject = const_cast<GPRS_CSI&>(element);
        asnObject.SetDescription(GetGprs_CSIStaticDescription());
        AddElement(0, element);
    }

    bool OptionGprs_CSI() const
    {
        return Contains(0);
    }

    const GPRS_CSI& GetGprs_CSI() const
    {
        ITS_REQUIRE(OptionGprs_CSI());
        return static_cast<const GPRS_CSI&> (ElementAt(0));
    }

    void SetMo_sms_CSI(SMS_CSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMo_sms_CSIStaticDescription());
        AddElement(1, element);
    }

    void SetMo_sms_CSI(const SMS_CSI& element)
    {
        its::AsnObject& asnObject = const_cast<SMS_CSI&>(element);
        asnObject.SetDescription(GetMo_sms_CSIStaticDescription());
        AddElement(1, element);
    }

    bool OptionMo_sms_CSI() const
    {
        return Contains(1);
    }

    const SMS_CSI& GetMo_sms_CSI() const
    {
        ITS_REQUIRE(OptionMo_sms_CSI());
        return static_cast<const SMS_CSI&> (ElementAt(1));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(2, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(2, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(2);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(2));
    }

    void SetMt_sms_CSI(SMS_CSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMt_sms_CSIStaticDescription());
        AddElement(3, element);
    }

    void SetMt_sms_CSI(const SMS_CSI& element)
    {
        its::AsnObject& asnObject = const_cast<SMS_CSI&>(element);
        asnObject.SetDescription(GetMt_sms_CSIStaticDescription());
        AddElement(3, element);
    }

    bool OptionMt_sms_CSI() const
    {
        return Contains(3);
    }

    const SMS_CSI& GetMt_sms_CSI() const
    {
        ITS_REQUIRE(OptionMt_sms_CSI());
        return static_cast<const SMS_CSI&> (ElementAt(3));
    }

    void SetMt_smsCAMELTDP_CriteriaList(MT_smsCAMELTDP_CriteriaList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMt_smsCAMELTDP_CriteriaListStaticDescription());
        AddElement(4, element);
    }

    void SetMt_smsCAMELTDP_CriteriaList(const MT_smsCAMELTDP_CriteriaList& element)
    {
        its::AsnObject& asnObject = const_cast<MT_smsCAMELTDP_CriteriaList&>(element);
        asnObject.SetDescription(GetMt_smsCAMELTDP_CriteriaListStaticDescription());
        AddElement(4, element);
    }

    bool OptionMt_smsCAMELTDP_CriteriaList() const
    {
        return Contains(4);
    }

    const MT_smsCAMELTDP_CriteriaList& GetMt_smsCAMELTDP_CriteriaList() const
    {
        ITS_REQUIRE(OptionMt_smsCAMELTDP_CriteriaList());
        return static_cast<const MT_smsCAMELTDP_CriteriaList&> (ElementAt(4));
    }

    void SetMg_csi(MG_CSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMg_csiStaticDescription());
        AddElement(5, element);
    }

    void SetMg_csi(const MG_CSI& element)
    {
        its::AsnObject& asnObject = const_cast<MG_CSI&>(element);
        asnObject.SetDescription(GetMg_csiStaticDescription());
        AddElement(5, element);
    }

    bool OptionMg_csi() const
    {
        return Contains(5);
    }

    const MG_CSI& GetMg_csi() const
    {
        ITS_REQUIRE(OptionMg_csi());
        return static_cast<const MG_CSI&> (ElementAt(5));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_SGSN_CAMEL_SUBSCRIPTION_INFO_H_)

