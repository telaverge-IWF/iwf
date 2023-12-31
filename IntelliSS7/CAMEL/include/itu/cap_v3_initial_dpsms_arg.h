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


#if !defined(_CAP_V3_INITIAL_DPSMS_ARG_H_)
#define _CAP_V3_INITIAL_DPSMS_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>
#include <AsnInteger.h>
#include <AsnOctetString.h>
#include <AsnEnumerated.h>

#include <cap_v3_service_key.h>
#include <cap_v3_called_party_bcd_number.h>
#include <cap_v3_isdn_address_string.h>
#include <cap_v3_event_type_sms.h>
#include <cap_v3_imsi.h>
#include <cap_v3_location_information.h>
#include <cap_v3_location_information_gprs.h>
#include <cap_v3_time_and_timezone.h>
#include <cap_v3_tp_short_message_submission_info.h>
#include <cap_v3_tp_protocol_identifier.h>
#include <cap_v3_tp_data_coding_scheme.h>
#include <cap_v3_tp_validity_period.h>
#include <cap_v3_extension_field.h>
#include <cap_v3_call_reference_number.h>
#include <cap_v3_imei.h>



namespace cap_v3 {



class InitialDPSMSArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Extensions : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef cap_v3::ExtensionField ExtensionField;


    ////////// End Nested Class //////////

        Extensions() : its::AsnSequenceOf(false)
        {
            Initialize();
        }

        Extensions(its::Octets& octets) : its::AsnSequenceOf(false)
        {
            Initialize();
            Decode(octets);
        }

        Extensions(const Extensions& rhs) : its::AsnSequenceOf(rhs)
        {
            // Nothing to do.
        }

        Extensions(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

        static its::AsnDescObject* GetExtensionFieldStaticDescription();

    public:

        virtual ~Extensions()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Extensions(*this);
        }

        virtual std::string GetName() const
        { return "Extensions"; }

        void AddElement(ExtensionField* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetExtensionFieldStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        void AddElement(const ExtensionField& element)
        {
            its::AsnObject& asnObject = const_cast<ExtensionField&>(element);
            asnObject.SetDescription(GetExtensionFieldStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        const ExtensionField& ElementAt(int index) const
        {
            return static_cast<const ExtensionField&> (AsnSequenceOf::ElementAt(index));
        }

    };


        typedef cap_v3::ServiceKey ServiceKey;


        typedef cap_v3::CalledPartyBCDNumber CalledPartyBCDNumber;


        typedef cap_v3::ISDN_AddressString ISDN_AddressString;


        typedef cap_v3::EventTypeSMS EventTypeSMS;


        typedef cap_v3::IMSI IMSI;


        typedef cap_v3::LocationInformation LocationInformation;


        typedef cap_v3::LocationInformationGPRS LocationInformationGPRS;


        typedef cap_v3::TimeAndTimezone TimeAndTimezone;


        typedef cap_v3::TPShortMessageSubmissionInfo TPShortMessageSubmissionInfo;


        typedef cap_v3::TPProtocolIdentifier TPProtocolIdentifier;


        typedef cap_v3::TPDataCodingScheme TPDataCodingScheme;


        typedef cap_v3::TPValidityPeriod TPValidityPeriod;


        typedef cap_v3::CallReferenceNumber CallReferenceNumber;


        typedef cap_v3::IMEI IMEI;


////////// End Nested Class(es) //////////

    InitialDPSMSArg() : its::AsnSequence(18, false)
    {
        Initialize();
    }

    InitialDPSMSArg(its::Octets& octets) : its::AsnSequence(18, false)
    {
        Initialize();
        Decode(octets);
    }

    InitialDPSMSArg(const InitialDPSMSArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    InitialDPSMSArg(its::AsnDescObject* description) : its::AsnSequence(18, description)
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
    static its::AsnDescObject* GetDestinationSubscriberNumberStaticDescription();
    static its::AsnDescObject* GetCallingPartyNumberStaticDescription();
    static its::AsnDescObject* GetEventTypeSMSStaticDescription();
    static its::AsnDescObject* GetIMSIStaticDescription();
    static its::AsnDescObject* GetLocationInformationMSCStaticDescription();
    static its::AsnDescObject* GetLocationInformationGPRSStaticDescription();
    static its::AsnDescObject* GetSMSCAddressStaticDescription();
    static its::AsnDescObject* GetTimeAndTimezoneStaticDescription();
    static its::AsnDescObject* GetTPShortMessageSubmissionSpecificInfoStaticDescription();
    static its::AsnDescObject* GetTPProtocolIdentifierStaticDescription();
    static its::AsnDescObject* GetTPDataCodingSchemeStaticDescription();
    static its::AsnDescObject* GetTPValidityPeriodStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();
    static its::AsnDescObject* GetSmsReferenceNumberStaticDescription();
    static its::AsnDescObject* GetMscAddressStaticDescription();
    static its::AsnDescObject* GetSgsn_NumberStaticDescription();
    static its::AsnDescObject* GetImeiStaticDescription();

public:

    virtual ~InitialDPSMSArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new InitialDPSMSArg(*this);
    }

    virtual std::string GetName() const
    { return "InitialDPSMSArg"; }

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

    void SetDestinationSubscriberNumber(CalledPartyBCDNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDestinationSubscriberNumberStaticDescription());
        AddElement(1, element);
    }

    void SetDestinationSubscriberNumber(const CalledPartyBCDNumber& element)
    {
        its::AsnObject& asnObject = const_cast<CalledPartyBCDNumber&>(element);
        asnObject.SetDescription(GetDestinationSubscriberNumberStaticDescription());
        AddElement(1, element);
    }

    bool OptionDestinationSubscriberNumber() const
    {
        return Contains(1);
    }

    const CalledPartyBCDNumber& GetDestinationSubscriberNumber() const
    {
        ITS_REQUIRE(OptionDestinationSubscriberNumber());
        return static_cast<const CalledPartyBCDNumber&> (ElementAt(1));
    }

    void SetCallingPartyNumber(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingPartyNumberStaticDescription());
        AddElement(2, element);
    }

    void SetCallingPartyNumber(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetCallingPartyNumberStaticDescription());
        AddElement(2, element);
    }

    bool OptionCallingPartyNumber() const
    {
        return Contains(2);
    }

    const ISDN_AddressString& GetCallingPartyNumber() const
    {
        ITS_REQUIRE(OptionCallingPartyNumber());
        return static_cast<const ISDN_AddressString&> (ElementAt(2));
    }

    void SetEventTypeSMS(EventTypeSMS* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEventTypeSMSStaticDescription());
        AddElement(3, element);
    }

    void SetEventTypeSMS(const EventTypeSMS& element)
    {
        its::AsnObject& asnObject = const_cast<EventTypeSMS&>(element);
        asnObject.SetDescription(GetEventTypeSMSStaticDescription());
        AddElement(3, element);
    }

    bool OptionEventTypeSMS() const
    {
        return Contains(3);
    }

    const EventTypeSMS& GetEventTypeSMS() const
    {
        ITS_REQUIRE(OptionEventTypeSMS());
        return static_cast<const EventTypeSMS&> (ElementAt(3));
    }

    void SetIMSI(IMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIMSIStaticDescription());
        AddElement(4, element);
    }

    void SetIMSI(const IMSI& element)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(element);
        asnObject.SetDescription(GetIMSIStaticDescription());
        AddElement(4, element);
    }

    bool OptionIMSI() const
    {
        return Contains(4);
    }

    const IMSI& GetIMSI() const
    {
        ITS_REQUIRE(OptionIMSI());
        return static_cast<const IMSI&> (ElementAt(4));
    }

    void SetLocationInformationMSC(LocationInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLocationInformationMSCStaticDescription());
        AddElement(5, element);
    }

    void SetLocationInformationMSC(const LocationInformation& element)
    {
        its::AsnObject& asnObject = const_cast<LocationInformation&>(element);
        asnObject.SetDescription(GetLocationInformationMSCStaticDescription());
        AddElement(5, element);
    }

    bool OptionLocationInformationMSC() const
    {
        return Contains(5);
    }

    const LocationInformation& GetLocationInformationMSC() const
    {
        ITS_REQUIRE(OptionLocationInformationMSC());
        return static_cast<const LocationInformation&> (ElementAt(5));
    }

    void SetLocationInformationGPRS(LocationInformationGPRS* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLocationInformationGPRSStaticDescription());
        AddElement(6, element);
    }

    void SetLocationInformationGPRS(const LocationInformationGPRS& element)
    {
        its::AsnObject& asnObject = const_cast<LocationInformationGPRS&>(element);
        asnObject.SetDescription(GetLocationInformationGPRSStaticDescription());
        AddElement(6, element);
    }

    bool OptionLocationInformationGPRS() const
    {
        return Contains(6);
    }

    const LocationInformationGPRS& GetLocationInformationGPRS() const
    {
        ITS_REQUIRE(OptionLocationInformationGPRS());
        return static_cast<const LocationInformationGPRS&> (ElementAt(6));
    }

    void SetSMSCAddress(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSMSCAddressStaticDescription());
        AddElement(7, element);
    }

    void SetSMSCAddress(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetSMSCAddressStaticDescription());
        AddElement(7, element);
    }

    bool OptionSMSCAddress() const
    {
        return Contains(7);
    }

    const ISDN_AddressString& GetSMSCAddress() const
    {
        ITS_REQUIRE(OptionSMSCAddress());
        return static_cast<const ISDN_AddressString&> (ElementAt(7));
    }

    void SetTimeAndTimezone(TimeAndTimezone* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTimeAndTimezoneStaticDescription());
        AddElement(8, element);
    }

    void SetTimeAndTimezone(const TimeAndTimezone& element)
    {
        its::AsnObject& asnObject = const_cast<TimeAndTimezone&>(element);
        asnObject.SetDescription(GetTimeAndTimezoneStaticDescription());
        AddElement(8, element);
    }

    bool OptionTimeAndTimezone() const
    {
        return Contains(8);
    }

    const TimeAndTimezone& GetTimeAndTimezone() const
    {
        ITS_REQUIRE(OptionTimeAndTimezone());
        return static_cast<const TimeAndTimezone&> (ElementAt(8));
    }

    void SetTPShortMessageSubmissionSpecificInfo(TPShortMessageSubmissionInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTPShortMessageSubmissionSpecificInfoStaticDescription());
        AddElement(9, element);
    }

    void SetTPShortMessageSubmissionSpecificInfo(const TPShortMessageSubmissionInfo& element)
    {
        its::AsnObject& asnObject = const_cast<TPShortMessageSubmissionInfo&>(element);
        asnObject.SetDescription(GetTPShortMessageSubmissionSpecificInfoStaticDescription());
        AddElement(9, element);
    }

    bool OptionTPShortMessageSubmissionSpecificInfo() const
    {
        return Contains(9);
    }

    const TPShortMessageSubmissionInfo& GetTPShortMessageSubmissionSpecificInfo() const
    {
        ITS_REQUIRE(OptionTPShortMessageSubmissionSpecificInfo());
        return static_cast<const TPShortMessageSubmissionInfo&> (ElementAt(9));
    }

    void SetTPProtocolIdentifier(TPProtocolIdentifier* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTPProtocolIdentifierStaticDescription());
        AddElement(10, element);
    }

    void SetTPProtocolIdentifier(const TPProtocolIdentifier& element)
    {
        its::AsnObject& asnObject = const_cast<TPProtocolIdentifier&>(element);
        asnObject.SetDescription(GetTPProtocolIdentifierStaticDescription());
        AddElement(10, element);
    }

    bool OptionTPProtocolIdentifier() const
    {
        return Contains(10);
    }

    const TPProtocolIdentifier& GetTPProtocolIdentifier() const
    {
        ITS_REQUIRE(OptionTPProtocolIdentifier());
        return static_cast<const TPProtocolIdentifier&> (ElementAt(10));
    }

    void SetTPDataCodingScheme(TPDataCodingScheme* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTPDataCodingSchemeStaticDescription());
        AddElement(11, element);
    }

    void SetTPDataCodingScheme(const TPDataCodingScheme& element)
    {
        its::AsnObject& asnObject = const_cast<TPDataCodingScheme&>(element);
        asnObject.SetDescription(GetTPDataCodingSchemeStaticDescription());
        AddElement(11, element);
    }

    bool OptionTPDataCodingScheme() const
    {
        return Contains(11);
    }

    const TPDataCodingScheme& GetTPDataCodingScheme() const
    {
        ITS_REQUIRE(OptionTPDataCodingScheme());
        return static_cast<const TPDataCodingScheme&> (ElementAt(11));
    }

    void SetTPValidityPeriod(TPValidityPeriod* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTPValidityPeriodStaticDescription());
        AddElement(12, element);
    }

    void SetTPValidityPeriod(const TPValidityPeriod& element)
    {
        its::AsnObject& asnObject = const_cast<TPValidityPeriod&>(element);
        asnObject.SetDescription(GetTPValidityPeriodStaticDescription());
        AddElement(12, element);
    }

    bool OptionTPValidityPeriod() const
    {
        return Contains(12);
    }

    const TPValidityPeriod& GetTPValidityPeriod() const
    {
        ITS_REQUIRE(OptionTPValidityPeriod());
        return static_cast<const TPValidityPeriod&> (ElementAt(12));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(13, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(13, element);
    }

    bool OptionExtensions() const
    {
        return Contains(13);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(13));
    }

    void SetSmsReferenceNumber(CallReferenceNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSmsReferenceNumberStaticDescription());
        AddElement(14, element);
    }

    void SetSmsReferenceNumber(const CallReferenceNumber& element)
    {
        its::AsnObject& asnObject = const_cast<CallReferenceNumber&>(element);
        asnObject.SetDescription(GetSmsReferenceNumberStaticDescription());
        AddElement(14, element);
    }

    bool OptionSmsReferenceNumber() const
    {
        return Contains(14);
    }

    const CallReferenceNumber& GetSmsReferenceNumber() const
    {
        ITS_REQUIRE(OptionSmsReferenceNumber());
        return static_cast<const CallReferenceNumber&> (ElementAt(14));
    }

    void SetMscAddress(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMscAddressStaticDescription());
        AddElement(15, element);
    }

    void SetMscAddress(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetMscAddressStaticDescription());
        AddElement(15, element);
    }

    bool OptionMscAddress() const
    {
        return Contains(15);
    }

    const ISDN_AddressString& GetMscAddress() const
    {
        ITS_REQUIRE(OptionMscAddress());
        return static_cast<const ISDN_AddressString&> (ElementAt(15));
    }

    void SetSgsn_Number(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSgsn_NumberStaticDescription());
        AddElement(16, element);
    }

    void SetSgsn_Number(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetSgsn_NumberStaticDescription());
        AddElement(16, element);
    }

    bool OptionSgsn_Number() const
    {
        return Contains(16);
    }

    const ISDN_AddressString& GetSgsn_Number() const
    {
        ITS_REQUIRE(OptionSgsn_Number());
        return static_cast<const ISDN_AddressString&> (ElementAt(16));
    }

    void SetImei(IMEI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImeiStaticDescription());
        AddElement(17, element);
    }

    void SetImei(const IMEI& element)
    {
        its::AsnObject& asnObject = const_cast<IMEI&>(element);
        asnObject.SetDescription(GetImeiStaticDescription());
        AddElement(17, element);
    }

    bool OptionImei() const
    {
        return Contains(17);
    }

    const IMEI& GetImei() const
    {
        ITS_REQUIRE(OptionImei());
        return static_cast<const IMEI&> (ElementAt(17));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_INITIAL_DPSMS_ARG_H_)

