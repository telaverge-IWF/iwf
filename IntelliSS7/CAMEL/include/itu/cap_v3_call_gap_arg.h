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


#if !defined(_CAP_V3_CALL_GAP_ARG_H_)
#define _CAP_V3_CALL_GAP_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>
#include <AsnChoice.h>
#include <AsnEnumerated.h>

#include <cap_v3_gap_criteria.h>
#include <cap_v3_gap_indicators.h>
#include <cap_v3_control_type.h>
#include <cap_v3_gap_treatment.h>
#include <cap_v3_extension_field.h>



namespace cap_v3 {



class CallGapArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Extensions : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef cap_v3::ExtensionField ExtensionField;


    ////////// End Nested Class //////////

        Extensions() : its::AsnSequenceOf(false)
        {
            Initialize();
        }

        Extensions(its::Octets& octets) : its::AsnSequenceOf(false)
        {
            Initialize();
            Decode(octets);
        }

        Extensions(const Extensions& rhs) : its::AsnSequenceOf(rhs)
        {
            // Nothing to do.
        }

        Extensions(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

        static its::AsnDescObject* GetExtensionFieldStaticDescription();

    public:

        virtual ~Extensions()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Extensions(*this);
        }

        virtual std::string GetName() const
        { return "Extensions"; }

        void AddElement(ExtensionField* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetExtensionFieldStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        void AddElement(const ExtensionField& element)
        {
            its::AsnObject& asnObject = const_cast<ExtensionField&>(element);
            asnObject.SetDescription(GetExtensionFieldStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        const ExtensionField& ElementAt(int index) const
        {
            return static_cast<const ExtensionField&> (AsnSequenceOf::ElementAt(index));
        }

    };


        typedef cap_v3::GapCriteria GapCriteria;


        typedef cap_v3::GapIndicators GapIndicators;


        typedef cap_v3::ControlType ControlType;


        typedef cap_v3::GapTreatment GapTreatment;


////////// End Nested Class(es) //////////

    CallGapArg() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    CallGapArg(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    CallGapArg(const CallGapArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    CallGapArg(its::AsnDescObject* description) : its::AsnSequence(5, description)
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

    static its::AsnDescObject* GetGapCriteriaStaticDescription();
    static its::AsnDescObject* GetGapIndicatorsStaticDescription();
    static its::AsnDescObject* GetControlTypeStaticDescription();
    static its::AsnDescObject* GetGapTreatmentStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();

public:

    virtual ~CallGapArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CallGapArg(*this);
    }

    virtual std::string GetName() const
    { return "CallGapArg"; }

    void SetGapCriteria(GapCriteria* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGapCriteriaStaticDescription());
        AddElement(0, element);
    }

    void SetGapCriteria(const GapCriteria& element)
    {
        its::AsnObject& asnObject = const_cast<GapCriteria&>(element);
        asnObject.SetDescription(GetGapCriteriaStaticDescription());
        AddElement(0, element);
    }

    const GapCriteria& GetGapCriteria() const
    {
        return static_cast<const GapCriteria&> (ElementAt(0));
    }

    void SetGapIndicators(GapIndicators* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGapIndicatorsStaticDescription());
        AddElement(1, element);
    }

    void SetGapIndicators(const GapIndicators& element)
    {
        its::AsnObject& asnObject = const_cast<GapIndicators&>(element);
        asnObject.SetDescription(GetGapIndicatorsStaticDescription());
        AddElement(1, element);
    }

    const GapIndicators& GetGapIndicators() const
    {
        return static_cast<const GapIndicators&> (ElementAt(1));
    }

    void SetControlType(ControlType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetControlTypeStaticDescription());
        AddElement(2, element);
    }

    void SetControlType(const ControlType& element)
    {
        its::AsnObject& asnObject = const_cast<ControlType&>(element);
        asnObject.SetDescription(GetControlTypeStaticDescription());
        AddElement(2, element);
    }

    bool OptionControlType() const
    {
        return Contains(2);
    }

    const ControlType& GetControlType() const
    {
        ITS_REQUIRE(OptionControlType());
        return static_cast<const ControlType&> (ElementAt(2));
    }

    void SetGapTreatment(GapTreatment* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGapTreatmentStaticDescription());
        AddElement(3, element);
    }

    void SetGapTreatment(const GapTreatment& element)
    {
        its::AsnObject& asnObject = const_cast<GapTreatment&>(element);
        asnObject.SetDescription(GetGapTreatmentStaticDescription());
        AddElement(3, element);
    }

    bool OptionGapTreatment() const
    {
        return Contains(3);
    }

    const GapTreatment& GetGapTreatment() const
    {
        ITS_REQUIRE(OptionGapTreatment());
        return static_cast<const GapTreatment&> (ElementAt(3));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(4, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(4, element);
    }

    bool OptionExtensions() const
    {
        return Contains(4);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(4));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_CALL_GAP_ARG_H_)
