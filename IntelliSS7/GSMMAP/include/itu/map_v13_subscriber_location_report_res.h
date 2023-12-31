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


#if !defined(_MAP_V13_SUBSCRIBER_LOCATION_REPORT_RES_H_)
#define _MAP_V13_SUBSCRIBER_LOCATION_REPORT_RES_H_

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

#include <map_v13_extension_container.h>
#include <map_v13_isdn_address_string.h>
#include <map_v13_gsn_address.h>
#include <map_v13_reporting_plmn_list.h>
#include <map_v13_lcs_reference_number.h>



namespace map_v13 {



class SubscriberLocationReport_Res : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Mo_lrShortCircuitIndicator : public its::AsnNull
    {
    public:

        Mo_lrShortCircuitIndicator() : its::AsnNull(false)
        {
            Initialize();
        }

        Mo_lrShortCircuitIndicator(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Mo_lrShortCircuitIndicator(const Mo_lrShortCircuitIndicator& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Mo_lrShortCircuitIndicator(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Mo_lrShortCircuitIndicator()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Mo_lrShortCircuitIndicator(*this);
        }

        virtual std::string GetName() const
        { return "Mo_lrShortCircuitIndicator"; }

    };


        typedef map_v13::ExtensionContainer ExtensionContainer;


        typedef map_v13::ISDN_AddressString ISDN_AddressString;


        typedef map_v13::GSN_Address GSN_Address;


        typedef map_v13::ReportingPLMNList ReportingPLMNList;


        typedef map_v13::LCS_ReferenceNumber LCS_ReferenceNumber;


////////// End Nested Class(es) //////////

    SubscriberLocationReport_Res() : its::AsnSequence(7, false)
    {
        Initialize();
    }

    SubscriberLocationReport_Res(its::Octets& octets) : its::AsnSequence(7, false)
    {
        Initialize();
        Decode(octets);
    }

    SubscriberLocationReport_Res(const SubscriberLocationReport_Res& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SubscriberLocationReport_Res(its::AsnDescObject* description) : its::AsnSequence(7, description)
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

    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetNa_ESRKStaticDescription();
    static its::AsnDescObject* GetNa_ESRDStaticDescription();
    static its::AsnDescObject* GetH_gmlc_AddressStaticDescription();
    static its::AsnDescObject* GetMo_lrShortCircuitIndicatorStaticDescription();
    static its::AsnDescObject* GetReportingPLMNListStaticDescription();
    static its::AsnDescObject* GetLcs_ReferenceNumberStaticDescription();

public:

    virtual ~SubscriberLocationReport_Res()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SubscriberLocationReport_Res(*this);
    }

    virtual std::string GetName() const
    { return "SubscriberLocationReport_Res"; }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(0, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(0, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(0);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(0));
    }

    void SetNa_ESRK(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNa_ESRKStaticDescription());
        AddElement(1, element);
    }

    void SetNa_ESRK(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetNa_ESRKStaticDescription());
        AddElement(1, element);
    }

    bool OptionNa_ESRK() const
    {
        return Contains(1);
    }

    const ISDN_AddressString& GetNa_ESRK() const
    {
        ITS_REQUIRE(OptionNa_ESRK());
        return static_cast<const ISDN_AddressString&> (ElementAt(1));
    }

    void SetNa_ESRD(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNa_ESRDStaticDescription());
        AddElement(2, element);
    }

    void SetNa_ESRD(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetNa_ESRDStaticDescription());
        AddElement(2, element);
    }

    bool OptionNa_ESRD() const
    {
        return Contains(2);
    }

    const ISDN_AddressString& GetNa_ESRD() const
    {
        ITS_REQUIRE(OptionNa_ESRD());
        return static_cast<const ISDN_AddressString&> (ElementAt(2));
    }

    void SetH_gmlc_Address(GSN_Address* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetH_gmlc_AddressStaticDescription());
        AddElement(3, element);
    }

    void SetH_gmlc_Address(const GSN_Address& element)
    {
        its::AsnObject& asnObject = const_cast<GSN_Address&>(element);
        asnObject.SetDescription(GetH_gmlc_AddressStaticDescription());
        AddElement(3, element);
    }

    bool OptionH_gmlc_Address() const
    {
        return Contains(3);
    }

    const GSN_Address& GetH_gmlc_Address() const
    {
        ITS_REQUIRE(OptionH_gmlc_Address());
        return static_cast<const GSN_Address&> (ElementAt(3));
    }

    void SetMo_lrShortCircuitIndicator(Mo_lrShortCircuitIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMo_lrShortCircuitIndicatorStaticDescription());
        AddElement(4, element);
    }

    void SetMo_lrShortCircuitIndicator(const Mo_lrShortCircuitIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<Mo_lrShortCircuitIndicator&>(element);
        asnObject.SetDescription(GetMo_lrShortCircuitIndicatorStaticDescription());
        AddElement(4, element);
    }

    bool OptionMo_lrShortCircuitIndicator() const
    {
        return Contains(4);
    }

    const Mo_lrShortCircuitIndicator& GetMo_lrShortCircuitIndicator() const
    {
        ITS_REQUIRE(OptionMo_lrShortCircuitIndicator());
        return static_cast<const Mo_lrShortCircuitIndicator&> (ElementAt(4));
    }

    void SetReportingPLMNList(ReportingPLMNList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetReportingPLMNListStaticDescription());
        AddElement(5, element);
    }

    void SetReportingPLMNList(const ReportingPLMNList& element)
    {
        its::AsnObject& asnObject = const_cast<ReportingPLMNList&>(element);
        asnObject.SetDescription(GetReportingPLMNListStaticDescription());
        AddElement(5, element);
    }

    bool OptionReportingPLMNList() const
    {
        return Contains(5);
    }

    const ReportingPLMNList& GetReportingPLMNList() const
    {
        ITS_REQUIRE(OptionReportingPLMNList());
        return static_cast<const ReportingPLMNList&> (ElementAt(5));
    }

    void SetLcs_ReferenceNumber(LCS_ReferenceNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLcs_ReferenceNumberStaticDescription());
        AddElement(6, element);
    }

    void SetLcs_ReferenceNumber(const LCS_ReferenceNumber& element)
    {
        its::AsnObject& asnObject = const_cast<LCS_ReferenceNumber&>(element);
        asnObject.SetDescription(GetLcs_ReferenceNumberStaticDescription());
        AddElement(6, element);
    }

    bool OptionLcs_ReferenceNumber() const
    {
        return Contains(6);
    }

    const LCS_ReferenceNumber& GetLcs_ReferenceNumber() const
    {
        ITS_REQUIRE(OptionLcs_ReferenceNumber());
        return static_cast<const LCS_ReferenceNumber&> (ElementAt(6));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_SUBSCRIBER_LOCATION_REPORT_RES_H_)

