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


#if !defined(_MAP_V9_AREA_EVENT_INFO_H_)
#define _MAP_V9_AREA_EVENT_INFO_H_

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

#include <map_v9_area_definition.h>
#include <map_v9_occurrence_info.h>
#include <map_v9_interval_time.h>



namespace map_v9 {



class AreaEventInfo : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::AreaDefinition AreaDefinition;


        typedef map_v9::OccurrenceInfo OccurrenceInfo;


        typedef map_v9::IntervalTime IntervalTime;


////////// End Nested Class(es) //////////

    AreaEventInfo() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    AreaEventInfo(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    AreaEventInfo(const AreaEventInfo& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    AreaEventInfo(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetAreaDefinitionStaticDescription();
    static its::AsnDescObject* GetOccurrenceInfoStaticDescription();
    static its::AsnDescObject* GetIntervalTimeStaticDescription();

public:

    virtual ~AreaEventInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AreaEventInfo(*this);
    }

    virtual std::string GetName() const
    { return "AreaEventInfo"; }

    void SetAreaDefinition(AreaDefinition* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAreaDefinitionStaticDescription());
        AddElement(0, element);
    }

    void SetAreaDefinition(const AreaDefinition& element)
    {
        its::AsnObject& asnObject = const_cast<AreaDefinition&>(element);
        asnObject.SetDescription(GetAreaDefinitionStaticDescription());
        AddElement(0, element);
    }

    const AreaDefinition& GetAreaDefinition() const
    {
        return static_cast<const AreaDefinition&> (ElementAt(0));
    }

    void SetOccurrenceInfo(OccurrenceInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOccurrenceInfoStaticDescription());
        AddElement(1, element);
    }

    void SetOccurrenceInfo(const OccurrenceInfo& element)
    {
        its::AsnObject& asnObject = const_cast<OccurrenceInfo&>(element);
        asnObject.SetDescription(GetOccurrenceInfoStaticDescription());
        AddElement(1, element);
    }

    bool OptionOccurrenceInfo() const
    {
        return Contains(1);
    }

    const OccurrenceInfo& GetOccurrenceInfo() const
    {
        ITS_REQUIRE(OptionOccurrenceInfo());
        return static_cast<const OccurrenceInfo&> (ElementAt(1));
    }

    void SetIntervalTime(IntervalTime* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIntervalTimeStaticDescription());
        AddElement(2, element);
    }

    void SetIntervalTime(const IntervalTime& element)
    {
        its::AsnObject& asnObject = const_cast<IntervalTime&>(element);
        asnObject.SetDescription(GetIntervalTimeStaticDescription());
        AddElement(2, element);
    }

    bool OptionIntervalTime() const
    {
        return Contains(2);
    }

    const IntervalTime& GetIntervalTime() const
    {
        ITS_REQUIRE(OptionIntervalTime());
        return static_cast<const IntervalTime&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_AREA_EVENT_INFO_H_)

