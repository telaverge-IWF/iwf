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


#if !defined(_MAP_V3_READY_FOR_SM_ARG_H_)
#define _MAP_V3_READY_FOR_SM_ARG_H_

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

#include <map_v3_imsi.h>
#include <map_v3_alert_reason.h>



namespace map_v3 {



class ReadyForSM_Arg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::IMSI IMSI;


        typedef map_v3::AlertReason AlertReason;


////////// End Nested Class(es) //////////

    ReadyForSM_Arg() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    ReadyForSM_Arg(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    ReadyForSM_Arg(const ReadyForSM_Arg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ReadyForSM_Arg(its::AsnDescObject* description) : its::AsnSequence(2, description)
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
    static its::AsnDescObject* GetAlertReasonStaticDescription();

public:

    virtual ~ReadyForSM_Arg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ReadyForSM_Arg(*this);
    }

    virtual std::string GetName() const
    { return "ReadyForSM_Arg"; }

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

    void SetAlertReason(AlertReason* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAlertReasonStaticDescription());
        AddElement(1, element);
    }

    void SetAlertReason(const AlertReason& element)
    {
        its::AsnObject& asnObject = const_cast<AlertReason&>(element);
        asnObject.SetDescription(GetAlertReasonStaticDescription());
        AddElement(1, element);
    }

    const AlertReason& GetAlertReason() const
    {
        return static_cast<const AlertReason&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_READY_FOR_SM_ARG_H_)

