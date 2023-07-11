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


#if !defined(_MAP_V13_MDT_CONFIGURATION_H_)
#define _MAP_V13_MDT_CONFIGURATION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>
#include <AsnOctetString.h>
#include <AsnInteger.h>

#include <map_v13_job_type.h>
#include <map_v13_area_scope.h>
#include <map_v13_list_of_measurements.h>
#include <map_v13_reporting_trigger.h>
#include <map_v13_report_interval.h>
#include <map_v13_report_amount.h>
#include <map_v13_event_threshold_rsrp.h>
#include <map_v13_event_threshold_rsrq.h>
#include <map_v13_logging_interval.h>
#include <map_v13_logging_duration.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class MDT_Configuration : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::JobType JobType;


        typedef map_v13::AreaScope AreaScope;


        typedef map_v13::ListOfMeasurements ListOfMeasurements;


        typedef map_v13::ReportingTrigger ReportingTrigger;


        typedef map_v13::ReportInterval ReportInterval;


        typedef map_v13::ReportAmount ReportAmount;


        typedef map_v13::EventThresholdRSRP EventThresholdRSRP;


        typedef map_v13::EventThresholdRSRQ EventThresholdRSRQ;


        typedef map_v13::LoggingInterval LoggingInterval;


        typedef map_v13::LoggingDuration LoggingDuration;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    MDT_Configuration() : its::AsnSequence(11, false)
    {
        Initialize();
    }

    MDT_Configuration(its::Octets& octets) : its::AsnSequence(11, false)
    {
        Initialize();
        Decode(octets);
    }

    MDT_Configuration(const MDT_Configuration& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    MDT_Configuration(its::AsnDescObject* description) : its::AsnSequence(11, description)
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

    static its::AsnDescObject* GetJobTypeStaticDescription();
    static its::AsnDescObject* GetAreaScopeStaticDescription();
    static its::AsnDescObject* GetListOfMeasurementsStaticDescription();
    static its::AsnDescObject* GetReportingTriggerStaticDescription();
    static its::AsnDescObject* GetReportIntervalStaticDescription();
    static its::AsnDescObject* GetReportAmountStaticDescription();
    static its::AsnDescObject* GetEventThresholdRSRPStaticDescription();
    static its::AsnDescObject* GetEventThresholdRSRQStaticDescription();
    static its::AsnDescObject* GetLoggingIntervalStaticDescription();
    static its::AsnDescObject* GetLoggingDurationStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~MDT_Configuration()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MDT_Configuration(*this);
    }

    virtual std::string GetName() const
    { return "MDT_Configuration"; }

    void SetJobType(JobType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetJobTypeStaticDescription());
        AddElement(0, element);
    }

    void SetJobType(const JobType& element)
    {
        its::AsnObject& asnObject = const_cast<JobType&>(element);
        asnObject.SetDescription(GetJobTypeStaticDescription());
        AddElement(0, element);
    }

    const JobType& GetJobType() const
    {
        return static_cast<const JobType&> (ElementAt(0));
    }

    void SetAreaScope(AreaScope* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAreaScopeStaticDescription());
        AddElement(1, element);
    }

    void SetAreaScope(const AreaScope& element)
    {
        its::AsnObject& asnObject = const_cast<AreaScope&>(element);
        asnObject.SetDescription(GetAreaScopeStaticDescription());
        AddElement(1, element);
    }

    bool OptionAreaScope() const
    {
        return Contains(1);
    }

    const AreaScope& GetAreaScope() const
    {
        ITS_REQUIRE(OptionAreaScope());
        return static_cast<const AreaScope&> (ElementAt(1));
    }

    void SetListOfMeasurements(ListOfMeasurements* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetListOfMeasurementsStaticDescription());
        AddElement(2, element);
    }

    void SetListOfMeasurements(const ListOfMeasurements& element)
    {
        its::AsnObject& asnObject = const_cast<ListOfMeasurements&>(element);
        asnObject.SetDescription(GetListOfMeasurementsStaticDescription());
        AddElement(2, element);
    }

    bool OptionListOfMeasurements() const
    {
        return Contains(2);
    }

    const ListOfMeasurements& GetListOfMeasurements() const
    {
        ITS_REQUIRE(OptionListOfMeasurements());
        return static_cast<const ListOfMeasurements&> (ElementAt(2));
    }

    void SetReportingTrigger(ReportingTrigger* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetReportingTriggerStaticDescription());
        AddElement(3, element);
    }

    void SetReportingTrigger(const ReportingTrigger& element)
    {
        its::AsnObject& asnObject = const_cast<ReportingTrigger&>(element);
        asnObject.SetDescription(GetReportingTriggerStaticDescription());
        AddElement(3, element);
    }

    bool OptionReportingTrigger() const
    {
        return Contains(3);
    }

    const ReportingTrigger& GetReportingTrigger() const
    {
        ITS_REQUIRE(OptionReportingTrigger());
        return static_cast<const ReportingTrigger&> (ElementAt(3));
    }

    void SetReportInterval(ReportInterval* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetReportIntervalStaticDescription());
        AddElement(4, element);
    }

    void SetReportInterval(const ReportInterval& element)
    {
        its::AsnObject& asnObject = const_cast<ReportInterval&>(element);
        asnObject.SetDescription(GetReportIntervalStaticDescription());
        AddElement(4, element);
    }

    bool OptionReportInterval() const
    {
        return Contains(4);
    }

    const ReportInterval& GetReportInterval() const
    {
        ITS_REQUIRE(OptionReportInterval());
        return static_cast<const ReportInterval&> (ElementAt(4));
    }

    void SetReportAmount(ReportAmount* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetReportAmountStaticDescription());
        AddElement(5, element);
    }

    void SetReportAmount(const ReportAmount& element)
    {
        its::AsnObject& asnObject = const_cast<ReportAmount&>(element);
        asnObject.SetDescription(GetReportAmountStaticDescription());
        AddElement(5, element);
    }

    bool OptionReportAmount() const
    {
        return Contains(5);
    }

    const ReportAmount& GetReportAmount() const
    {
        ITS_REQUIRE(OptionReportAmount());
        return static_cast<const ReportAmount&> (ElementAt(5));
    }

    void SetEventThresholdRSRP(EventThresholdRSRP* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEventThresholdRSRPStaticDescription());
        AddElement(6, element);
    }

    void SetEventThresholdRSRP(const EventThresholdRSRP& element)
    {
        its::AsnObject& asnObject = const_cast<EventThresholdRSRP&>(element);
        asnObject.SetDescription(GetEventThresholdRSRPStaticDescription());
        AddElement(6, element);
    }

    bool OptionEventThresholdRSRP() const
    {
        return Contains(6);
    }

    const EventThresholdRSRP& GetEventThresholdRSRP() const
    {
        ITS_REQUIRE(OptionEventThresholdRSRP());
        return static_cast<const EventThresholdRSRP&> (ElementAt(6));
    }

    void SetEventThresholdRSRQ(EventThresholdRSRQ* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEventThresholdRSRQStaticDescription());
        AddElement(7, element);
    }

    void SetEventThresholdRSRQ(const EventThresholdRSRQ& element)
    {
        its::AsnObject& asnObject = const_cast<EventThresholdRSRQ&>(element);
        asnObject.SetDescription(GetEventThresholdRSRQStaticDescription());
        AddElement(7, element);
    }

    bool OptionEventThresholdRSRQ() const
    {
        return Contains(7);
    }

    const EventThresholdRSRQ& GetEventThresholdRSRQ() const
    {
        ITS_REQUIRE(OptionEventThresholdRSRQ());
        return static_cast<const EventThresholdRSRQ&> (ElementAt(7));
    }

    void SetLoggingInterval(LoggingInterval* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLoggingIntervalStaticDescription());
        AddElement(8, element);
    }

    void SetLoggingInterval(const LoggingInterval& element)
    {
        its::AsnObject& asnObject = const_cast<LoggingInterval&>(element);
        asnObject.SetDescription(GetLoggingIntervalStaticDescription());
        AddElement(8, element);
    }

    bool OptionLoggingInterval() const
    {
        return Contains(8);
    }

    const LoggingInterval& GetLoggingInterval() const
    {
        ITS_REQUIRE(OptionLoggingInterval());
        return static_cast<const LoggingInterval&> (ElementAt(8));
    }

    void SetLoggingDuration(LoggingDuration* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLoggingDurationStaticDescription());
        AddElement(9, element);
    }

    void SetLoggingDuration(const LoggingDuration& element)
    {
        its::AsnObject& asnObject = const_cast<LoggingDuration&>(element);
        asnObject.SetDescription(GetLoggingDurationStaticDescription());
        AddElement(9, element);
    }

    bool OptionLoggingDuration() const
    {
        return Contains(9);
    }

    const LoggingDuration& GetLoggingDuration() const
    {
        ITS_REQUIRE(OptionLoggingDuration());
        return static_cast<const LoggingDuration&> (ElementAt(9));
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

};



} // namespace.

#endif    // !defined(_MAP_V13_MDT_CONFIGURATION_H_)
