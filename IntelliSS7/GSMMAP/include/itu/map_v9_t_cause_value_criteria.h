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


#if !defined(_MAP_V9_T_CAUSE_VALUE_CRITERIA_H_)
#define _MAP_V9_T_CAUSE_VALUE_CRITERIA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnOctetString.h>

#include <map_v9_cause_value.h>



namespace map_v9 {



class T_CauseValueCriteria : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v9::CauseValue CauseValue;


////////// End Nested Class //////////

    T_CauseValueCriteria() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    T_CauseValueCriteria(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    T_CauseValueCriteria(const T_CauseValueCriteria& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    T_CauseValueCriteria(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetCauseValueStaticDescription();

public:

    virtual ~T_CauseValueCriteria()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new T_CauseValueCriteria(*this);
    }

    virtual std::string GetName() const
    { return "T_CauseValueCriteria"; }

    void AddElement(CauseValue* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCauseValueStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const CauseValue& element)
    {
        its::AsnObject& asnObject = const_cast<CauseValue&>(element);
        asnObject.SetDescription(GetCauseValueStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const CauseValue& ElementAt(int index) const
    {
        return static_cast<const CauseValue&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_T_CAUSE_VALUE_CRITERIA_H_)
