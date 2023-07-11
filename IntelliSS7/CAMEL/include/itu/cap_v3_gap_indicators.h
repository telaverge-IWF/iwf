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


#if !defined(_CAP_V3_GAP_INDICATORS_H_)
#define _CAP_V3_GAP_INDICATORS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnInteger.h>

#include <cap_v3_duration.h>
#include <cap_v3_interval.h>



namespace cap_v3 {



class GapIndicators : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef cap_v3::Duration Duration;


        typedef cap_v3::Interval Interval;


////////// End Nested Class(es) //////////

    GapIndicators() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    GapIndicators(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    GapIndicators(const GapIndicators& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    GapIndicators(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetDurationStaticDescription();
    static its::AsnDescObject* GetGapIntervalStaticDescription();

public:

    virtual ~GapIndicators()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new GapIndicators(*this);
    }

    virtual std::string GetName() const
    { return "GapIndicators"; }

    void SetDuration(Duration* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDurationStaticDescription());
        AddElement(0, element);
    }

    void SetDuration(const Duration& element)
    {
        its::AsnObject& asnObject = const_cast<Duration&>(element);
        asnObject.SetDescription(GetDurationStaticDescription());
        AddElement(0, element);
    }

    const Duration& GetDuration() const
    {
        return static_cast<const Duration&> (ElementAt(0));
    }

    void SetGapInterval(Interval* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGapIntervalStaticDescription());
        AddElement(1, element);
    }

    void SetGapInterval(const Interval& element)
    {
        its::AsnObject& asnObject = const_cast<Interval&>(element);
        asnObject.SetDescription(GetGapIntervalStaticDescription());
        AddElement(1, element);
    }

    const Interval& GetGapInterval() const
    {
        return static_cast<const Interval&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_GAP_INDICATORS_H_)
