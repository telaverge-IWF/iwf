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


#if !defined(_MAP_V13_T_BCSM_CAMEL_TDP_CRITERIA_LIST_H_)
#define _MAP_V13_T_BCSM_CAMEL_TDP_CRITERIA_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v13_t_bcsm_camel_tdp_criteria.h>



namespace map_v13 {



class T_BCSM_CAMEL_TDP_CriteriaList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::T_BCSM_CAMEL_TDP_Criteria T_BCSM_CAMEL_TDP_Criteria;


////////// End Nested Class //////////

    T_BCSM_CAMEL_TDP_CriteriaList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    T_BCSM_CAMEL_TDP_CriteriaList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    T_BCSM_CAMEL_TDP_CriteriaList(const T_BCSM_CAMEL_TDP_CriteriaList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    T_BCSM_CAMEL_TDP_CriteriaList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetT_BCSM_CAMEL_TDP_CriteriaStaticDescription();

public:

    virtual ~T_BCSM_CAMEL_TDP_CriteriaList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new T_BCSM_CAMEL_TDP_CriteriaList(*this);
    }

    virtual std::string GetName() const
    { return "T_BCSM_CAMEL_TDP_CriteriaList"; }

    void AddElement(T_BCSM_CAMEL_TDP_Criteria* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetT_BCSM_CAMEL_TDP_CriteriaStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const T_BCSM_CAMEL_TDP_Criteria& element)
    {
        its::AsnObject& asnObject = const_cast<T_BCSM_CAMEL_TDP_Criteria&>(element);
        asnObject.SetDescription(GetT_BCSM_CAMEL_TDP_CriteriaStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const T_BCSM_CAMEL_TDP_Criteria& ElementAt(int index) const
    {
        return static_cast<const T_BCSM_CAMEL_TDP_Criteria&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_T_BCSM_CAMEL_TDP_CRITERIA_LIST_H_)
