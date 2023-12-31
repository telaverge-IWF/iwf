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


#if !defined(_CAP_V3_RESET_TIMER_GPRS_ARG_H_)
#define _CAP_V3_RESET_TIMER_GPRS_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>
#include <AsnInteger.h>
#include <AsnOctetString.h>

#include <cap_v3_timer_id.h>
#include <cap_v3_timer_value.h>
#include <cap_v3_pdpid.h>



namespace cap_v3 {



class ResetTimerGPRSArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v3::TimerID TimerID;


        typedef cap_v3::TimerValue TimerValue;


        typedef cap_v3::PDPID PDPID;


////////// End Nested Class(es) //////////

    ResetTimerGPRSArg() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    ResetTimerGPRSArg(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    ResetTimerGPRSArg(const ResetTimerGPRSArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ResetTimerGPRSArg(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetTimerIDStaticDescription();
    static its::AsnDescObject* GetTimervalueStaticDescription();
    static its::AsnDescObject* GetPDPIDStaticDescription();

public:

    virtual ~ResetTimerGPRSArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ResetTimerGPRSArg(*this);
    }

    virtual std::string GetName() const
    { return "ResetTimerGPRSArg"; }

    void SetTimerID(TimerID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTimerIDStaticDescription());
        AddElement(0, element);
    }

    void SetTimerID(const TimerID& element)
    {
        its::AsnObject& asnObject = const_cast<TimerID&>(element);
        asnObject.SetDescription(GetTimerIDStaticDescription());
        AddElement(0, element);
    }

    const TimerID& GetTimerID() const
    {
        return static_cast<const TimerID&> (ElementAt(0));
    }

    void SetTimervalue(TimerValue* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTimervalueStaticDescription());
        AddElement(1, element);
    }

    void SetTimervalue(const TimerValue& element)
    {
        its::AsnObject& asnObject = const_cast<TimerValue&>(element);
        asnObject.SetDescription(GetTimervalueStaticDescription());
        AddElement(1, element);
    }

    const TimerValue& GetTimervalue() const
    {
        return static_cast<const TimerValue&> (ElementAt(1));
    }

    void SetPDPID(PDPID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPDPIDStaticDescription());
        AddElement(2, element);
    }

    void SetPDPID(const PDPID& element)
    {
        its::AsnObject& asnObject = const_cast<PDPID&>(element);
        asnObject.SetDescription(GetPDPIDStaticDescription());
        AddElement(2, element);
    }

    bool OptionPDPID() const
    {
        return Contains(2);
    }

    const PDPID& GetPDPID() const
    {
        ITS_REQUIRE(OptionPDPID());
        return static_cast<const PDPID&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_RESET_TIMER_GPRS_ARG_H_)

