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


#if !defined(_MAP_V9_STATUS_REPORT_ARG_H_)
#define _MAP_V9_STATUS_REPORT_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v9_imsi.h>
#include <map_v9_event_report_data.h>
#include <map_v9_call_report_data.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class StatusReportArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::IMSI IMSI;


        typedef map_v9::EventReportData EventReportData;


        typedef map_v9::CallReportData CallReportData;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    StatusReportArg() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    StatusReportArg(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    StatusReportArg(const StatusReportArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    StatusReportArg(its::AsnDescObject* description) : its::AsnSequence(4, description)
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
    static its::AsnDescObject* GetEventReportDataStaticDescription();
    static its::AsnDescObject* GetCallReportdataStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~StatusReportArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new StatusReportArg(*this);
    }

    virtual std::string GetName() const
    { return "StatusReportArg"; }

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

    void SetEventReportData(EventReportData* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEventReportDataStaticDescription());
        AddElement(1, element);
    }

    void SetEventReportData(const EventReportData& element)
    {
        its::AsnObject& asnObject = const_cast<EventReportData&>(element);
        asnObject.SetDescription(GetEventReportDataStaticDescription());
        AddElement(1, element);
    }

    bool OptionEventReportData() const
    {
        return Contains(1);
    }

    const EventReportData& GetEventReportData() const
    {
        ITS_REQUIRE(OptionEventReportData());
        return static_cast<const EventReportData&> (ElementAt(1));
    }

    void SetCallReportdata(CallReportData* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallReportdataStaticDescription());
        AddElement(2, element);
    }

    void SetCallReportdata(const CallReportData& element)
    {
        its::AsnObject& asnObject = const_cast<CallReportData&>(element);
        asnObject.SetDescription(GetCallReportdataStaticDescription());
        AddElement(2, element);
    }

    bool OptionCallReportdata() const
    {
        return Contains(2);
    }

    const CallReportData& GetCallReportdata() const
    {
        ITS_REQUIRE(OptionCallReportdata());
        return static_cast<const CallReportData&> (ElementAt(2));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(3, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(3, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(3);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_STATUS_REPORT_ARG_H_)

