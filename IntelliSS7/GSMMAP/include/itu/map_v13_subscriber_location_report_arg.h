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


#if !defined(_MAP_V13_SUBSCRIBER_LOCATION_REPORT_ARG_H_)
#define _MAP_V13_SUBSCRIBER_LOCATION_REPORT_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>
#include <AsnEnumerated.h>
#include <AsnOctetString.h>
#include <AsnInteger.h>
#include <AsnChoice.h>

#include <map_v13_lcs_event.h>
#include <map_v13_lcs_client_id.h>
#include <map_v13_lcs_location_info.h>
#include <map_v13_isdn_address_string.h>
#include <map_v13_imsi.h>
#include <map_v13_imei.h>
#include <map_v13_ext_geographical_information.h>
#include <map_v13_age_of_location_information.h>
#include <map_v13_slr_arg_extension_container.h>
#include <map_v13_add_geographical_information.h>
#include <map_v13_deferredmt_lr_data.h>
#include <map_v13_lcs_reference_number.h>
#include <map_v13_positioning_data_information.h>
#include <map_v13_utran_positioning_data_info.h>
#include <map_v13_cell_global_id_or_service_area_id_or_lai.h>
#include <map_v13_gsn_address.h>
#include <map_v13_lcs_service_type_id.h>
#include <map_v13_accuracy_fulfilment_indicator.h>
#include <map_v13_velocity_estimate.h>
#include <map_v13_sequence_number.h>
#include <map_v13_periodic_ldr_info.h>
#include <map_v13_geran_gans_spositioning_data.h>
#include <map_v13_utran_gans_spositioning_data.h>
#include <map_v13_serving_node_address.h>



namespace map_v13 {



class SubscriberLocationReport_Arg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Sai_Present : public its::AsnNull
    {
    public:

        Sai_Present() : its::AsnNull(false)
        {
            Initialize();
        }

        Sai_Present(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Sai_Present(const Sai_Present& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Sai_Present(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Sai_Present()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Sai_Present(*this);
        }

        virtual std::string GetName() const
        { return "Sai_Present"; }

    };



    class PseudonymIndicator : public its::AsnNull
    {
    public:

        PseudonymIndicator() : its::AsnNull(false)
        {
            Initialize();
        }

        PseudonymIndicator(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        PseudonymIndicator(const PseudonymIndicator& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        PseudonymIndicator(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~PseudonymIndicator()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new PseudonymIndicator(*this);
        }

        virtual std::string GetName() const
        { return "PseudonymIndicator"; }

    };



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


        typedef map_v13::LCS_Event LCS_Event;


        typedef map_v13::LCS_ClientID LCS_ClientID;


        typedef map_v13::LCSLocationInfo LCSLocationInfo;


        typedef map_v13::ISDN_AddressString ISDN_AddressString;


        typedef map_v13::IMSI IMSI;


        typedef map_v13::IMEI IMEI;


        typedef map_v13::Ext_GeographicalInformation Ext_GeographicalInformation;


        typedef map_v13::AgeOfLocationInformation AgeOfLocationInformation;


        typedef map_v13::SLR_ArgExtensionContainer SLR_ArgExtensionContainer;


        typedef map_v13::Add_GeographicalInformation Add_GeographicalInformation;


        typedef map_v13::Deferredmt_lrData Deferredmt_lrData;


        typedef map_v13::LCS_ReferenceNumber LCS_ReferenceNumber;


        typedef map_v13::PositioningDataInformation PositioningDataInformation;


        typedef map_v13::UtranPositioningDataInfo UtranPositioningDataInfo;


        typedef map_v13::CellGlobalIdOrServiceAreaIdOrLAI CellGlobalIdOrServiceAreaIdOrLAI;


        typedef map_v13::GSN_Address GSN_Address;


        typedef map_v13::LCSServiceTypeID LCSServiceTypeID;


        typedef map_v13::AccuracyFulfilmentIndicator AccuracyFulfilmentIndicator;


        typedef map_v13::VelocityEstimate VelocityEstimate;


        typedef map_v13::SequenceNumber SequenceNumber;


        typedef map_v13::PeriodicLDRInfo PeriodicLDRInfo;


        typedef map_v13::GeranGANSSpositioningData GeranGANSSpositioningData;


        typedef map_v13::UtranGANSSpositioningData UtranGANSSpositioningData;


        typedef map_v13::ServingNodeAddress ServingNodeAddress;


////////// End Nested Class(es) //////////

    SubscriberLocationReport_Arg() : its::AsnSequence(29, false)
    {
        Initialize();
    }

    SubscriberLocationReport_Arg(its::Octets& octets) : its::AsnSequence(29, false)
    {
        Initialize();
        Decode(octets);
    }

    SubscriberLocationReport_Arg(const SubscriberLocationReport_Arg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SubscriberLocationReport_Arg(its::AsnDescObject* description) : its::AsnSequence(29, description)
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

    static its::AsnDescObject* GetLcs_EventStaticDescription();
    static its::AsnDescObject* GetLcs_ClientIDStaticDescription();
    static its::AsnDescObject* GetLcsLocationInfoStaticDescription();
    static its::AsnDescObject* GetMsisdnStaticDescription();
    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetImeiStaticDescription();
    static its::AsnDescObject* GetNa_ESRDStaticDescription();
    static its::AsnDescObject* GetNa_ESRKStaticDescription();
    static its::AsnDescObject* GetLocationEstimateStaticDescription();
    static its::AsnDescObject* GetAgeOfLocationEstimateStaticDescription();
    static its::AsnDescObject* GetSlr_ArgExtensionContainerStaticDescription();
    static its::AsnDescObject* GetAdd_LocationEstimateStaticDescription();
    static its::AsnDescObject* GetDeferredmt_lrDataStaticDescription();
    static its::AsnDescObject* GetLcs_ReferenceNumberStaticDescription();
    static its::AsnDescObject* GetGeranPositioningDataStaticDescription();
    static its::AsnDescObject* GetUtranPositioningDataStaticDescription();
    static its::AsnDescObject* GetCellIdOrSaiStaticDescription();
    static its::AsnDescObject* GetH_gmlc_AddressStaticDescription();
    static its::AsnDescObject* GetLcsServiceTypeIDStaticDescription();
    static its::AsnDescObject* GetSai_PresentStaticDescription();
    static its::AsnDescObject* GetPseudonymIndicatorStaticDescription();
    static its::AsnDescObject* GetAccuracyFulfilmentIndicatorStaticDescription();
    static its::AsnDescObject* GetVelocityEstimateStaticDescription();
    static its::AsnDescObject* GetSequenceNumberStaticDescription();
    static its::AsnDescObject* GetPeriodicLDRInfoStaticDescription();
    static its::AsnDescObject* GetMo_lrShortCircuitIndicatorStaticDescription();
    static its::AsnDescObject* GetGeranGANSSpositioningDataStaticDescription();
    static its::AsnDescObject* GetUtranGANSSpositioningDataStaticDescription();
    static its::AsnDescObject* GetTargetServingNodeForHandoverStaticDescription();

public:

    virtual ~SubscriberLocationReport_Arg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SubscriberLocationReport_Arg(*this);
    }

    virtual std::string GetName() const
    { return "SubscriberLocationReport_Arg"; }

    void SetLcs_Event(LCS_Event* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLcs_EventStaticDescription());
        AddElement(0, element);
    }

    void SetLcs_Event(const LCS_Event& element)
    {
        its::AsnObject& asnObject = const_cast<LCS_Event&>(element);
        asnObject.SetDescription(GetLcs_EventStaticDescription());
        AddElement(0, element);
    }

    const LCS_Event& GetLcs_Event() const
    {
        return static_cast<const LCS_Event&> (ElementAt(0));
    }

    void SetLcs_ClientID(LCS_ClientID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLcs_ClientIDStaticDescription());
        AddElement(1, element);
    }

    void SetLcs_ClientID(const LCS_ClientID& element)
    {
        its::AsnObject& asnObject = const_cast<LCS_ClientID&>(element);
        asnObject.SetDescription(GetLcs_ClientIDStaticDescription());
        AddElement(1, element);
    }

    const LCS_ClientID& GetLcs_ClientID() const
    {
        return static_cast<const LCS_ClientID&> (ElementAt(1));
    }

    void SetLcsLocationInfo(LCSLocationInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLcsLocationInfoStaticDescription());
        AddElement(2, element);
    }

    void SetLcsLocationInfo(const LCSLocationInfo& element)
    {
        its::AsnObject& asnObject = const_cast<LCSLocationInfo&>(element);
        asnObject.SetDescription(GetLcsLocationInfoStaticDescription());
        AddElement(2, element);
    }

    const LCSLocationInfo& GetLcsLocationInfo() const
    {
        return static_cast<const LCSLocationInfo&> (ElementAt(2));
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

    bool OptionMsisdn() const
    {
        return Contains(3);
    }

    const ISDN_AddressString& GetMsisdn() const
    {
        ITS_REQUIRE(OptionMsisdn());
        return static_cast<const ISDN_AddressString&> (ElementAt(3));
    }

    void SetImsi(IMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImsiStaticDescription());
        AddElement(4, element);
    }

    void SetImsi(const IMSI& element)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(element);
        asnObject.SetDescription(GetImsiStaticDescription());
        AddElement(4, element);
    }

    bool OptionImsi() const
    {
        return Contains(4);
    }

    const IMSI& GetImsi() const
    {
        ITS_REQUIRE(OptionImsi());
        return static_cast<const IMSI&> (ElementAt(4));
    }

    void SetImei(IMEI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImeiStaticDescription());
        AddElement(5, element);
    }

    void SetImei(const IMEI& element)
    {
        its::AsnObject& asnObject = const_cast<IMEI&>(element);
        asnObject.SetDescription(GetImeiStaticDescription());
        AddElement(5, element);
    }

    bool OptionImei() const
    {
        return Contains(5);
    }

    const IMEI& GetImei() const
    {
        ITS_REQUIRE(OptionImei());
        return static_cast<const IMEI&> (ElementAt(5));
    }

    void SetNa_ESRD(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNa_ESRDStaticDescription());
        AddElement(6, element);
    }

    void SetNa_ESRD(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetNa_ESRDStaticDescription());
        AddElement(6, element);
    }

    bool OptionNa_ESRD() const
    {
        return Contains(6);
    }

    const ISDN_AddressString& GetNa_ESRD() const
    {
        ITS_REQUIRE(OptionNa_ESRD());
        return static_cast<const ISDN_AddressString&> (ElementAt(6));
    }

    void SetNa_ESRK(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNa_ESRKStaticDescription());
        AddElement(7, element);
    }

    void SetNa_ESRK(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetNa_ESRKStaticDescription());
        AddElement(7, element);
    }

    bool OptionNa_ESRK() const
    {
        return Contains(7);
    }

    const ISDN_AddressString& GetNa_ESRK() const
    {
        ITS_REQUIRE(OptionNa_ESRK());
        return static_cast<const ISDN_AddressString&> (ElementAt(7));
    }

    void SetLocationEstimate(Ext_GeographicalInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLocationEstimateStaticDescription());
        AddElement(8, element);
    }

    void SetLocationEstimate(const Ext_GeographicalInformation& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_GeographicalInformation&>(element);
        asnObject.SetDescription(GetLocationEstimateStaticDescription());
        AddElement(8, element);
    }

    bool OptionLocationEstimate() const
    {
        return Contains(8);
    }

    const Ext_GeographicalInformation& GetLocationEstimate() const
    {
        ITS_REQUIRE(OptionLocationEstimate());
        return static_cast<const Ext_GeographicalInformation&> (ElementAt(8));
    }

    void SetAgeOfLocationEstimate(AgeOfLocationInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAgeOfLocationEstimateStaticDescription());
        AddElement(9, element);
    }

    void SetAgeOfLocationEstimate(const AgeOfLocationInformation& element)
    {
        its::AsnObject& asnObject = const_cast<AgeOfLocationInformation&>(element);
        asnObject.SetDescription(GetAgeOfLocationEstimateStaticDescription());
        AddElement(9, element);
    }

    bool OptionAgeOfLocationEstimate() const
    {
        return Contains(9);
    }

    const AgeOfLocationInformation& GetAgeOfLocationEstimate() const
    {
        ITS_REQUIRE(OptionAgeOfLocationEstimate());
        return static_cast<const AgeOfLocationInformation&> (ElementAt(9));
    }

    void SetSlr_ArgExtensionContainer(SLR_ArgExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSlr_ArgExtensionContainerStaticDescription());
        AddElement(10, element);
    }

    void SetSlr_ArgExtensionContainer(const SLR_ArgExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<SLR_ArgExtensionContainer&>(element);
        asnObject.SetDescription(GetSlr_ArgExtensionContainerStaticDescription());
        AddElement(10, element);
    }

    bool OptionSlr_ArgExtensionContainer() const
    {
        return Contains(10);
    }

    const SLR_ArgExtensionContainer& GetSlr_ArgExtensionContainer() const
    {
        ITS_REQUIRE(OptionSlr_ArgExtensionContainer());
        return static_cast<const SLR_ArgExtensionContainer&> (ElementAt(10));
    }

    void SetAdd_LocationEstimate(Add_GeographicalInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAdd_LocationEstimateStaticDescription());
        AddElement(11, element);
    }

    void SetAdd_LocationEstimate(const Add_GeographicalInformation& element)
    {
        its::AsnObject& asnObject = const_cast<Add_GeographicalInformation&>(element);
        asnObject.SetDescription(GetAdd_LocationEstimateStaticDescription());
        AddElement(11, element);
    }

    bool OptionAdd_LocationEstimate() const
    {
        return Contains(11);
    }

    const Add_GeographicalInformation& GetAdd_LocationEstimate() const
    {
        ITS_REQUIRE(OptionAdd_LocationEstimate());
        return static_cast<const Add_GeographicalInformation&> (ElementAt(11));
    }

    void SetDeferredmt_lrData(Deferredmt_lrData* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDeferredmt_lrDataStaticDescription());
        AddElement(12, element);
    }

    void SetDeferredmt_lrData(const Deferredmt_lrData& element)
    {
        its::AsnObject& asnObject = const_cast<Deferredmt_lrData&>(element);
        asnObject.SetDescription(GetDeferredmt_lrDataStaticDescription());
        AddElement(12, element);
    }

    bool OptionDeferredmt_lrData() const
    {
        return Contains(12);
    }

    const Deferredmt_lrData& GetDeferredmt_lrData() const
    {
        ITS_REQUIRE(OptionDeferredmt_lrData());
        return static_cast<const Deferredmt_lrData&> (ElementAt(12));
    }

    void SetLcs_ReferenceNumber(LCS_ReferenceNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLcs_ReferenceNumberStaticDescription());
        AddElement(13, element);
    }

    void SetLcs_ReferenceNumber(const LCS_ReferenceNumber& element)
    {
        its::AsnObject& asnObject = const_cast<LCS_ReferenceNumber&>(element);
        asnObject.SetDescription(GetLcs_ReferenceNumberStaticDescription());
        AddElement(13, element);
    }

    bool OptionLcs_ReferenceNumber() const
    {
        return Contains(13);
    }

    const LCS_ReferenceNumber& GetLcs_ReferenceNumber() const
    {
        ITS_REQUIRE(OptionLcs_ReferenceNumber());
        return static_cast<const LCS_ReferenceNumber&> (ElementAt(13));
    }

    void SetGeranPositioningData(PositioningDataInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGeranPositioningDataStaticDescription());
        AddElement(14, element);
    }

    void SetGeranPositioningData(const PositioningDataInformation& element)
    {
        its::AsnObject& asnObject = const_cast<PositioningDataInformation&>(element);
        asnObject.SetDescription(GetGeranPositioningDataStaticDescription());
        AddElement(14, element);
    }

    bool OptionGeranPositioningData() const
    {
        return Contains(14);
    }

    const PositioningDataInformation& GetGeranPositioningData() const
    {
        ITS_REQUIRE(OptionGeranPositioningData());
        return static_cast<const PositioningDataInformation&> (ElementAt(14));
    }

    void SetUtranPositioningData(UtranPositioningDataInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetUtranPositioningDataStaticDescription());
        AddElement(15, element);
    }

    void SetUtranPositioningData(const UtranPositioningDataInfo& element)
    {
        its::AsnObject& asnObject = const_cast<UtranPositioningDataInfo&>(element);
        asnObject.SetDescription(GetUtranPositioningDataStaticDescription());
        AddElement(15, element);
    }

    bool OptionUtranPositioningData() const
    {
        return Contains(15);
    }

    const UtranPositioningDataInfo& GetUtranPositioningData() const
    {
        ITS_REQUIRE(OptionUtranPositioningData());
        return static_cast<const UtranPositioningDataInfo&> (ElementAt(15));
    }

    void SetCellIdOrSai(CellGlobalIdOrServiceAreaIdOrLAI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCellIdOrSaiStaticDescription());
        AddElement(16, element);
    }

    void SetCellIdOrSai(const CellGlobalIdOrServiceAreaIdOrLAI& element)
    {
        its::AsnObject& asnObject = const_cast<CellGlobalIdOrServiceAreaIdOrLAI&>(element);
        asnObject.SetDescription(GetCellIdOrSaiStaticDescription());
        AddElement(16, element);
    }

    bool OptionCellIdOrSai() const
    {
        return Contains(16);
    }

    const CellGlobalIdOrServiceAreaIdOrLAI& GetCellIdOrSai() const
    {
        ITS_REQUIRE(OptionCellIdOrSai());
        return static_cast<const CellGlobalIdOrServiceAreaIdOrLAI&> (ElementAt(16));
    }

    void SetH_gmlc_Address(GSN_Address* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetH_gmlc_AddressStaticDescription());
        AddElement(17, element);
    }

    void SetH_gmlc_Address(const GSN_Address& element)
    {
        its::AsnObject& asnObject = const_cast<GSN_Address&>(element);
        asnObject.SetDescription(GetH_gmlc_AddressStaticDescription());
        AddElement(17, element);
    }

    bool OptionH_gmlc_Address() const
    {
        return Contains(17);
    }

    const GSN_Address& GetH_gmlc_Address() const
    {
        ITS_REQUIRE(OptionH_gmlc_Address());
        return static_cast<const GSN_Address&> (ElementAt(17));
    }

    void SetLcsServiceTypeID(LCSServiceTypeID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLcsServiceTypeIDStaticDescription());
        AddElement(18, element);
    }

    void SetLcsServiceTypeID(const LCSServiceTypeID& element)
    {
        its::AsnObject& asnObject = const_cast<LCSServiceTypeID&>(element);
        asnObject.SetDescription(GetLcsServiceTypeIDStaticDescription());
        AddElement(18, element);
    }

    bool OptionLcsServiceTypeID() const
    {
        return Contains(18);
    }

    const LCSServiceTypeID& GetLcsServiceTypeID() const
    {
        ITS_REQUIRE(OptionLcsServiceTypeID());
        return static_cast<const LCSServiceTypeID&> (ElementAt(18));
    }

    void SetSai_Present(Sai_Present* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSai_PresentStaticDescription());
        AddElement(19, element);
    }

    void SetSai_Present(const Sai_Present& element)
    {
        its::AsnObject& asnObject = const_cast<Sai_Present&>(element);
        asnObject.SetDescription(GetSai_PresentStaticDescription());
        AddElement(19, element);
    }

    bool OptionSai_Present() const
    {
        return Contains(19);
    }

    const Sai_Present& GetSai_Present() const
    {
        ITS_REQUIRE(OptionSai_Present());
        return static_cast<const Sai_Present&> (ElementAt(19));
    }

    void SetPseudonymIndicator(PseudonymIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPseudonymIndicatorStaticDescription());
        AddElement(20, element);
    }

    void SetPseudonymIndicator(const PseudonymIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<PseudonymIndicator&>(element);
        asnObject.SetDescription(GetPseudonymIndicatorStaticDescription());
        AddElement(20, element);
    }

    bool OptionPseudonymIndicator() const
    {
        return Contains(20);
    }

    const PseudonymIndicator& GetPseudonymIndicator() const
    {
        ITS_REQUIRE(OptionPseudonymIndicator());
        return static_cast<const PseudonymIndicator&> (ElementAt(20));
    }

    void SetAccuracyFulfilmentIndicator(AccuracyFulfilmentIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAccuracyFulfilmentIndicatorStaticDescription());
        AddElement(21, element);
    }

    void SetAccuracyFulfilmentIndicator(const AccuracyFulfilmentIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<AccuracyFulfilmentIndicator&>(element);
        asnObject.SetDescription(GetAccuracyFulfilmentIndicatorStaticDescription());
        AddElement(21, element);
    }

    bool OptionAccuracyFulfilmentIndicator() const
    {
        return Contains(21);
    }

    const AccuracyFulfilmentIndicator& GetAccuracyFulfilmentIndicator() const
    {
        ITS_REQUIRE(OptionAccuracyFulfilmentIndicator());
        return static_cast<const AccuracyFulfilmentIndicator&> (ElementAt(21));
    }

    void SetVelocityEstimate(VelocityEstimate* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetVelocityEstimateStaticDescription());
        AddElement(22, element);
    }

    void SetVelocityEstimate(const VelocityEstimate& element)
    {
        its::AsnObject& asnObject = const_cast<VelocityEstimate&>(element);
        asnObject.SetDescription(GetVelocityEstimateStaticDescription());
        AddElement(22, element);
    }

    bool OptionVelocityEstimate() const
    {
        return Contains(22);
    }

    const VelocityEstimate& GetVelocityEstimate() const
    {
        ITS_REQUIRE(OptionVelocityEstimate());
        return static_cast<const VelocityEstimate&> (ElementAt(22));
    }

    void SetSequenceNumber(SequenceNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSequenceNumberStaticDescription());
        AddElement(23, element);
    }

    void SetSequenceNumber(const SequenceNumber& element)
    {
        its::AsnObject& asnObject = const_cast<SequenceNumber&>(element);
        asnObject.SetDescription(GetSequenceNumberStaticDescription());
        AddElement(23, element);
    }

    bool OptionSequenceNumber() const
    {
        return Contains(23);
    }

    const SequenceNumber& GetSequenceNumber() const
    {
        ITS_REQUIRE(OptionSequenceNumber());
        return static_cast<const SequenceNumber&> (ElementAt(23));
    }

    void SetPeriodicLDRInfo(PeriodicLDRInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPeriodicLDRInfoStaticDescription());
        AddElement(24, element);
    }

    void SetPeriodicLDRInfo(const PeriodicLDRInfo& element)
    {
        its::AsnObject& asnObject = const_cast<PeriodicLDRInfo&>(element);
        asnObject.SetDescription(GetPeriodicLDRInfoStaticDescription());
        AddElement(24, element);
    }

    bool OptionPeriodicLDRInfo() const
    {
        return Contains(24);
    }

    const PeriodicLDRInfo& GetPeriodicLDRInfo() const
    {
        ITS_REQUIRE(OptionPeriodicLDRInfo());
        return static_cast<const PeriodicLDRInfo&> (ElementAt(24));
    }

    void SetMo_lrShortCircuitIndicator(Mo_lrShortCircuitIndicator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMo_lrShortCircuitIndicatorStaticDescription());
        AddElement(25, element);
    }

    void SetMo_lrShortCircuitIndicator(const Mo_lrShortCircuitIndicator& element)
    {
        its::AsnObject& asnObject = const_cast<Mo_lrShortCircuitIndicator&>(element);
        asnObject.SetDescription(GetMo_lrShortCircuitIndicatorStaticDescription());
        AddElement(25, element);
    }

    bool OptionMo_lrShortCircuitIndicator() const
    {
        return Contains(25);
    }

    const Mo_lrShortCircuitIndicator& GetMo_lrShortCircuitIndicator() const
    {
        ITS_REQUIRE(OptionMo_lrShortCircuitIndicator());
        return static_cast<const Mo_lrShortCircuitIndicator&> (ElementAt(25));
    }

    void SetGeranGANSSpositioningData(GeranGANSSpositioningData* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGeranGANSSpositioningDataStaticDescription());
        AddElement(26, element);
    }

    void SetGeranGANSSpositioningData(const GeranGANSSpositioningData& element)
    {
        its::AsnObject& asnObject = const_cast<GeranGANSSpositioningData&>(element);
        asnObject.SetDescription(GetGeranGANSSpositioningDataStaticDescription());
        AddElement(26, element);
    }

    bool OptionGeranGANSSpositioningData() const
    {
        return Contains(26);
    }

    const GeranGANSSpositioningData& GetGeranGANSSpositioningData() const
    {
        ITS_REQUIRE(OptionGeranGANSSpositioningData());
        return static_cast<const GeranGANSSpositioningData&> (ElementAt(26));
    }

    void SetUtranGANSSpositioningData(UtranGANSSpositioningData* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetUtranGANSSpositioningDataStaticDescription());
        AddElement(27, element);
    }

    void SetUtranGANSSpositioningData(const UtranGANSSpositioningData& element)
    {
        its::AsnObject& asnObject = const_cast<UtranGANSSpositioningData&>(element);
        asnObject.SetDescription(GetUtranGANSSpositioningDataStaticDescription());
        AddElement(27, element);
    }

    bool OptionUtranGANSSpositioningData() const
    {
        return Contains(27);
    }

    const UtranGANSSpositioningData& GetUtranGANSSpositioningData() const
    {
        ITS_REQUIRE(OptionUtranGANSSpositioningData());
        return static_cast<const UtranGANSSpositioningData&> (ElementAt(27));
    }

    void SetTargetServingNodeForHandover(ServingNodeAddress* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTargetServingNodeForHandoverStaticDescription());
        AddElement(28, element);
    }

    void SetTargetServingNodeForHandover(const ServingNodeAddress& element)
    {
        its::AsnObject& asnObject = const_cast<ServingNodeAddress&>(element);
        asnObject.SetDescription(GetTargetServingNodeForHandoverStaticDescription());
        AddElement(28, element);
    }

    bool OptionTargetServingNodeForHandover() const
    {
        return Contains(28);
    }

    const ServingNodeAddress& GetTargetServingNodeForHandover() const
    {
        ITS_REQUIRE(OptionTargetServingNodeForHandover());
        return static_cast<const ServingNodeAddress&> (ElementAt(28));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_SUBSCRIBER_LOCATION_REPORT_ARG_H_)

