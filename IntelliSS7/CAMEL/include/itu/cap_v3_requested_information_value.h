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


#if !defined(_CAP_V3_REQUESTED_INFORMATION_VALUE_H_)
#define _CAP_V3_REQUESTED_INFORMATION_VALUE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnInteger.h>
#include <AsnOctetString.h>

#include <cap_v3_date_and_time.h>
#include <cap_v3_integer4.h>
#include <cap_v3_cause.h>



namespace cap_v3 {



class RequestedInformationValue : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////



    class CallAttemptElapsedTimeValue : public its::AsnInteger
    {
    public:

        CallAttemptElapsedTimeValue() : its::AsnInteger(false)
        {
            Initialize();
        }

        CallAttemptElapsedTimeValue(long value) : its::AsnInteger(value, false)
        {
            Initialize();
        }

        CallAttemptElapsedTimeValue(its::Octets& octets) : its::AsnInteger(false)
        {
            Initialize();
            Decode(octets);
        }

        CallAttemptElapsedTimeValue(const CallAttemptElapsedTimeValue& rhs) : its::AsnInteger(rhs)
        {
            // Nothing to do.
        }

        CallAttemptElapsedTimeValue(its::AsnDescObject* description) : its::AsnInteger(description)
        {
            // Nothing to do.
        }

        CallAttemptElapsedTimeValue(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

        virtual ~CallAttemptElapsedTimeValue()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new CallAttemptElapsedTimeValue(*this);
        }

        virtual std::string GetName() const
        { return "CallAttemptElapsedTimeValue"; }

    };


        typedef cap_v3::DateAndTime DateAndTime;


        typedef cap_v3::Integer4 Integer4;


        typedef cap_v3::Cause Cause;


////////// End Nested Class(es) //////////

    RequestedInformationValue() : its::AsnChoice(false)
    {
        Initialize();
    }

    RequestedInformationValue(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    RequestedInformationValue(const RequestedInformationValue& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    RequestedInformationValue(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    RequestedInformationValue(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetCallAttemptElapsedTimeValueStaticDescription();
    static its::AsnDescObject* GetCallStopTimeValueStaticDescription();
    static its::AsnDescObject* GetCallConnectedElapsedTimeValueStaticDescription();
    static its::AsnDescObject* GetReleaseCauseValueStaticDescription();

public:

    virtual ~RequestedInformationValue()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RequestedInformationValue(*this);
    }

    virtual std::string GetName() const
    { return "RequestedInformationValue"; }

    void SetChoiceCallAttemptElapsedTimeValue(CallAttemptElapsedTimeValue* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetCallAttemptElapsedTimeValueStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceCallAttemptElapsedTimeValue(const CallAttemptElapsedTimeValue& choice)
    {
        its::AsnObject& asnObject = const_cast<CallAttemptElapsedTimeValue&>(choice);
        asnObject.SetDescription(GetCallAttemptElapsedTimeValueStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceCallAttemptElapsedTimeValue() const
    {
        return Contains(GetCallAttemptElapsedTimeValueStaticDescription()->TagIdentity());
    }

    const CallAttemptElapsedTimeValue& GetChoiceCallAttemptElapsedTimeValue() const
    {
        ITS_REQUIRE(ChoiceCallAttemptElapsedTimeValue());
        return static_cast<const CallAttemptElapsedTimeValue&> (GetChoice());
    }

    void SetChoiceCallStopTimeValue(DateAndTime* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetCallStopTimeValueStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceCallStopTimeValue(const DateAndTime& choice)
    {
        its::AsnObject& asnObject = const_cast<DateAndTime&>(choice);
        asnObject.SetDescription(GetCallStopTimeValueStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceCallStopTimeValue() const
    {
        return Contains(GetCallStopTimeValueStaticDescription()->TagIdentity());
    }

    const DateAndTime& GetChoiceCallStopTimeValue() const
    {
        ITS_REQUIRE(ChoiceCallStopTimeValue());
        return static_cast<const DateAndTime&> (GetChoice());
    }

    void SetChoiceCallConnectedElapsedTimeValue(Integer4* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetCallConnectedElapsedTimeValueStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceCallConnectedElapsedTimeValue(const Integer4& choice)
    {
        its::AsnObject& asnObject = const_cast<Integer4&>(choice);
        asnObject.SetDescription(GetCallConnectedElapsedTimeValueStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceCallConnectedElapsedTimeValue() const
    {
        return Contains(GetCallConnectedElapsedTimeValueStaticDescription()->TagIdentity());
    }

    const Integer4& GetChoiceCallConnectedElapsedTimeValue() const
    {
        ITS_REQUIRE(ChoiceCallConnectedElapsedTimeValue());
        return static_cast<const Integer4&> (GetChoice());
    }

    void SetChoiceReleaseCauseValue(Cause* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetReleaseCauseValueStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceReleaseCauseValue(const Cause& choice)
    {
        its::AsnObject& asnObject = const_cast<Cause&>(choice);
        asnObject.SetDescription(GetReleaseCauseValueStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceReleaseCauseValue() const
    {
        return Contains(GetReleaseCauseValueStaticDescription()->TagIdentity());
    }

    const Cause& GetChoiceReleaseCauseValue() const
    {
        ITS_REQUIRE(ChoiceReleaseCauseValue());
        return static_cast<const Cause&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_REQUESTED_INFORMATION_VALUE_H_)

