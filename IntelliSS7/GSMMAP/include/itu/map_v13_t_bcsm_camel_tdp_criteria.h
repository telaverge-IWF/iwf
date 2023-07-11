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


#if !defined(_MAP_V13_T_BCSM_CAMEL_TDP_CRITERIA_H_)
#define _MAP_V13_T_BCSM_CAMEL_TDP_CRITERIA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>
#include <AsnSequenceOf.h>

#include <map_v13_t_bcsm_trigger_detection_point.h>
#include <map_v13_basic_service_criteria.h>
#include <map_v13_t_cause_value_criteria.h>



namespace map_v13 {



class T_BCSM_CAMEL_TDP_Criteria : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::T_BcsmTriggerDetectionPoint T_BcsmTriggerDetectionPoint;


        typedef map_v13::BasicServiceCriteria BasicServiceCriteria;


        typedef map_v13::T_CauseValueCriteria T_CauseValueCriteria;


////////// End Nested Class(es) //////////

    T_BCSM_CAMEL_TDP_Criteria() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    T_BCSM_CAMEL_TDP_Criteria(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    T_BCSM_CAMEL_TDP_Criteria(const T_BCSM_CAMEL_TDP_Criteria& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    T_BCSM_CAMEL_TDP_Criteria(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetT_BCSM_TriggerDetectionPointStaticDescription();
    static its::AsnDescObject* GetBasicServiceCriteriaStaticDescription();
    static its::AsnDescObject* GetT_CauseValueCriteriaStaticDescription();

public:

    virtual ~T_BCSM_CAMEL_TDP_Criteria()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new T_BCSM_CAMEL_TDP_Criteria(*this);
    }

    virtual std::string GetName() const
    { return "T_BCSM_CAMEL_TDP_Criteria"; }

    void SetT_BCSM_TriggerDetectionPoint(T_BcsmTriggerDetectionPoint* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetT_BCSM_TriggerDetectionPointStaticDescription());
        AddElement(0, element);
    }

    void SetT_BCSM_TriggerDetectionPoint(const T_BcsmTriggerDetectionPoint& element)
    {
        its::AsnObject& asnObject = const_cast<T_BcsmTriggerDetectionPoint&>(element);
        asnObject.SetDescription(GetT_BCSM_TriggerDetectionPointStaticDescription());
        AddElement(0, element);
    }

    const T_BcsmTriggerDetectionPoint& GetT_BCSM_TriggerDetectionPoint() const
    {
        return static_cast<const T_BcsmTriggerDetectionPoint&> (ElementAt(0));
    }

    void SetBasicServiceCriteria(BasicServiceCriteria* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBasicServiceCriteriaStaticDescription());
        AddElement(1, element);
    }

    void SetBasicServiceCriteria(const BasicServiceCriteria& element)
    {
        its::AsnObject& asnObject = const_cast<BasicServiceCriteria&>(element);
        asnObject.SetDescription(GetBasicServiceCriteriaStaticDescription());
        AddElement(1, element);
    }

    bool OptionBasicServiceCriteria() const
    {
        return Contains(1);
    }

    const BasicServiceCriteria& GetBasicServiceCriteria() const
    {
        ITS_REQUIRE(OptionBasicServiceCriteria());
        return static_cast<const BasicServiceCriteria&> (ElementAt(1));
    }

    void SetT_CauseValueCriteria(T_CauseValueCriteria* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetT_CauseValueCriteriaStaticDescription());
        AddElement(2, element);
    }

    void SetT_CauseValueCriteria(const T_CauseValueCriteria& element)
    {
        its::AsnObject& asnObject = const_cast<T_CauseValueCriteria&>(element);
        asnObject.SetDescription(GetT_CauseValueCriteriaStaticDescription());
        AddElement(2, element);
    }

    bool OptionT_CauseValueCriteria() const
    {
        return Contains(2);
    }

    const T_CauseValueCriteria& GetT_CauseValueCriteria() const
    {
        ITS_REQUIRE(OptionT_CauseValueCriteria());
        return static_cast<const T_CauseValueCriteria&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_T_BCSM_CAMEL_TDP_CRITERIA_H_)

