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


#if !defined(_MAP_V13_SET_REPORTING_STATE_ARG_H_)
#define _MAP_V13_SET_REPORTING_STATE_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnEnumerated.h>

#include <map_v13_imsi.h>
#include <map_v13_lmsi.h>
#include <map_v13_reporting_state.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class SetReportingStateArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::IMSI IMSI;


        typedef map_v13::LMSI LMSI;


        typedef map_v13::ReportingState ReportingState;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    SetReportingStateArg() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    SetReportingStateArg(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    SetReportingStateArg(const SetReportingStateArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SetReportingStateArg(its::AsnDescObject* description) : its::AsnSequence(4, description)
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
    static its::AsnDescObject* GetLmsiStaticDescription();
    static its::AsnDescObject* GetCcbs_MonitoringStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~SetReportingStateArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SetReportingStateArg(*this);
    }

    virtual std::string GetName() const
    { return "SetReportingStateArg"; }

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

    bool OptionImsi() const
    {
        return Contains(0);
    }

    const IMSI& GetImsi() const
    {
        ITS_REQUIRE(OptionImsi());
        return static_cast<const IMSI&> (ElementAt(0));
    }

    void SetLmsi(LMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLmsiStaticDescription());
        AddElement(1, element);
    }

    void SetLmsi(const LMSI& element)
    {
        its::AsnObject& asnObject = const_cast<LMSI&>(element);
        asnObject.SetDescription(GetLmsiStaticDescription());
        AddElement(1, element);
    }

    bool OptionLmsi() const
    {
        return Contains(1);
    }

    const LMSI& GetLmsi() const
    {
        ITS_REQUIRE(OptionLmsi());
        return static_cast<const LMSI&> (ElementAt(1));
    }

    void SetCcbs_Monitoring(ReportingState* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCcbs_MonitoringStaticDescription());
        AddElement(2, element);
    }

    void SetCcbs_Monitoring(const ReportingState& element)
    {
        its::AsnObject& asnObject = const_cast<ReportingState&>(element);
        asnObject.SetDescription(GetCcbs_MonitoringStaticDescription());
        AddElement(2, element);
    }

    bool OptionCcbs_Monitoring() const
    {
        return Contains(2);
    }

    const ReportingState& GetCcbs_Monitoring() const
    {
        ITS_REQUIRE(OptionCcbs_Monitoring());
        return static_cast<const ReportingState&> (ElementAt(2));
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

#endif    // !defined(_MAP_V13_SET_REPORTING_STATE_ARG_H_)

