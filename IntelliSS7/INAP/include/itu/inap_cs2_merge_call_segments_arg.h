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


#if !defined(_INAP_CS2_MERGE_CALL_SEGMENTS_ARG_H_)
#define _INAP_CS2_MERGE_CALL_SEGMENTS_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>
#include <AsnInteger.h>

#include <inap_cs2_call_segment_id.h>
#include <inap_cs2_extension_field.h>



namespace inap_cs2 {



class MergeCallSegmentsArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Extensions : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef inap_cs2::ExtensionField ExtensionField;


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


        typedef inap_cs2::CallSegmentID CallSegmentID;


////////// End Nested Class(es) //////////

    MergeCallSegmentsArg() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    MergeCallSegmentsArg(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    MergeCallSegmentsArg(const MergeCallSegmentsArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    MergeCallSegmentsArg(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetSourceCallSegmentStaticDescription();
    static its::AsnDescObject* GetTargetCallSegmentStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();

public:

    virtual ~MergeCallSegmentsArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MergeCallSegmentsArg(*this);
    }

    virtual std::string GetName() const
    { return "MergeCallSegmentsArg"; }

    void SetSourceCallSegment(CallSegmentID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSourceCallSegmentStaticDescription());
        AddElement(0, element);
    }

    void SetSourceCallSegment(const CallSegmentID& element)
    {
        its::AsnObject& asnObject = const_cast<CallSegmentID&>(element);
        asnObject.SetDescription(GetSourceCallSegmentStaticDescription());
        AddElement(0, element);
    }

    const CallSegmentID& GetSourceCallSegment() const
    {
        return static_cast<const CallSegmentID&> (ElementAt(0));
    }

    void SetTargetCallSegment(CallSegmentID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTargetCallSegmentStaticDescription());
        AddElement(1, element);
    }

    void SetTargetCallSegment(const CallSegmentID& element)
    {
        its::AsnObject& asnObject = const_cast<CallSegmentID&>(element);
        asnObject.SetDescription(GetTargetCallSegmentStaticDescription());
        AddElement(1, element);
    }

    const CallSegmentID& GetTargetCallSegment() const
    {
        return static_cast<const CallSegmentID&> (ElementAt(1));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(2, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(2, element);
    }

    bool OptionExtensions() const
    {
        return Contains(2);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_MERGE_CALL_SEGMENTS_ARG_H_)

