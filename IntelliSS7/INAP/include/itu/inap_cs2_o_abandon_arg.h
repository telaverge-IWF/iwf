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


#if !defined(_INAP_CS2_O_ABANDON_ARG_H_)
#define _INAP_CS2_O_ABANDON_ARG_H_

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
#include <AsnOctetString.h>

#include <inap_cs2_dp_specific_common_parameters.h>
#include <inap_cs2_call_segment_id.h>
#include <inap_cs2_cause.h>
#include <inap_cs2_extension_field.h>



namespace inap_cs2 {



class OAbandonArg : public its::AsnSequence
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


        typedef inap_cs2::DpSpecificCommonParameters DpSpecificCommonParameters;


        typedef inap_cs2::CallSegmentID CallSegmentID;


        typedef inap_cs2::Cause Cause;


////////// End Nested Class(es) //////////

    OAbandonArg() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    OAbandonArg(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    OAbandonArg(const OAbandonArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    OAbandonArg(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetDpSpecificCommonParametersStaticDescription();
    static its::AsnDescObject* GetCallSegmentIDStaticDescription();
    static its::AsnDescObject* GetReleaseCauseStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();

public:

    virtual ~OAbandonArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new OAbandonArg(*this);
    }

    virtual std::string GetName() const
    { return "OAbandonArg"; }

    void SetDpSpecificCommonParameters(DpSpecificCommonParameters* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDpSpecificCommonParametersStaticDescription());
        AddElement(0, element);
    }

    void SetDpSpecificCommonParameters(const DpSpecificCommonParameters& element)
    {
        its::AsnObject& asnObject = const_cast<DpSpecificCommonParameters&>(element);
        asnObject.SetDescription(GetDpSpecificCommonParametersStaticDescription());
        AddElement(0, element);
    }

    const DpSpecificCommonParameters& GetDpSpecificCommonParameters() const
    {
        return static_cast<const DpSpecificCommonParameters&> (ElementAt(0));
    }

    void SetCallSegmentID(CallSegmentID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallSegmentIDStaticDescription());
        AddElement(1, element);
    }

    void SetCallSegmentID(const CallSegmentID& element)
    {
        its::AsnObject& asnObject = const_cast<CallSegmentID&>(element);
        asnObject.SetDescription(GetCallSegmentIDStaticDescription());
        AddElement(1, element);
    }

    const CallSegmentID& GetCallSegmentID() const
    {
        return static_cast<const CallSegmentID&> (ElementAt(1));
    }

    void SetReleaseCause(Cause* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetReleaseCauseStaticDescription());
        AddElement(2, element);
    }

    void SetReleaseCause(const Cause& element)
    {
        its::AsnObject& asnObject = const_cast<Cause&>(element);
        asnObject.SetDescription(GetReleaseCauseStaticDescription());
        AddElement(2, element);
    }

    bool OptionReleaseCause() const
    {
        return Contains(2);
    }

    const Cause& GetReleaseCause() const
    {
        ITS_REQUIRE(OptionReleaseCause());
        return static_cast<const Cause&> (ElementAt(2));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(3, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(3, element);
    }

    bool OptionExtensions() const
    {
        return Contains(3);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_O_ABANDON_ARG_H_)

