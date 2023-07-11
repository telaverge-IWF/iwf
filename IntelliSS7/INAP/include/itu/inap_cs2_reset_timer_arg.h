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


#if !defined(_INAP_CS2_RESET_TIMER_ARG_H_)
#define _INAP_CS2_RESET_TIMER_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>
#include <AsnEnumerated.h>
#include <AsnInteger.h>

#include <inap_cs2_timer_id.h>
#include <inap_cs2_timer_value.h>
#include <inap_cs2_extension_field.h>
#include <inap_cs2_call_segment_id.h>



namespace inap_cs2 {



class ResetTimerArg : public its::AsnSequence
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


        typedef inap_cs2::TimerID TimerID;


        typedef inap_cs2::TimerValue TimerValue;


        typedef inap_cs2::CallSegmentID CallSegmentID;


////////// End Nested Class(es) //////////

    ResetTimerArg() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    ResetTimerArg(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    ResetTimerArg(const ResetTimerArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ResetTimerArg(its::AsnDescObject* description) : its::AsnSequence(4, description)
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
    static its::AsnDescObject* GetExtensionsStaticDescription();
    static its::AsnDescObject* GetCallSegmentIDStaticDescription();

public:

    virtual ~ResetTimerArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ResetTimerArg(*this);
    }

    virtual std::string GetName() const
    { return "ResetTimerArg"; }

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

    void SetCallSegmentID(CallSegmentID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallSegmentIDStaticDescription());
        AddElement(3, element);
    }

    void SetCallSegmentID(const CallSegmentID& element)
    {
        its::AsnObject& asnObject = const_cast<CallSegmentID&>(element);
        asnObject.SetDescription(GetCallSegmentIDStaticDescription());
        AddElement(3, element);
    }

    bool OptionCallSegmentID() const
    {
        return Contains(3);
    }

    const CallSegmentID& GetCallSegmentID() const
    {
        ITS_REQUIRE(OptionCallSegmentID());
        return static_cast<const CallSegmentID&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_RESET_TIMER_ARG_H_)
