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


#if !defined(_CAP_V3_CONTINUE_WITH_ARGUMENT_ARG_EXTENSION_H_)
#define _CAP_V3_CONTINUE_WITH_ARGUMENT_ARG_EXTENSION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>



namespace cap_v3 {



class ContinueWithArgumentArgExtension : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class NonCug_Call : public its::AsnNull
    {
    public:

        NonCug_Call() : its::AsnNull(false)
        {
            Initialize();
        }

        NonCug_Call(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        NonCug_Call(const NonCug_Call& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        NonCug_Call(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~NonCug_Call()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new NonCug_Call(*this);
        }

        virtual std::string GetName() const
        { return "NonCug_Call"; }

    };


////////// End Nested Class(es) //////////

    ContinueWithArgumentArgExtension() : its::AsnSequence(1, false)
    {
        Initialize();
    }

    ContinueWithArgumentArgExtension(its::Octets& octets) : its::AsnSequence(1, false)
    {
        Initialize();
        Decode(octets);
    }

    ContinueWithArgumentArgExtension(const ContinueWithArgumentArgExtension& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ContinueWithArgumentArgExtension(its::AsnDescObject* description) : its::AsnSequence(1, description)
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

    static its::AsnDescObject* GetNonCug_CallStaticDescription();

public:

    virtual ~ContinueWithArgumentArgExtension()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ContinueWithArgumentArgExtension(*this);
    }

    virtual std::string GetName() const
    { return "ContinueWithArgumentArgExtension"; }

    void SetNonCug_Call(NonCug_Call* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNonCug_CallStaticDescription());
        AddElement(0, element);
    }

    void SetNonCug_Call(const NonCug_Call& element)
    {
        its::AsnObject& asnObject = const_cast<NonCug_Call&>(element);
        asnObject.SetDescription(GetNonCug_CallStaticDescription());
        AddElement(0, element);
    }

    bool OptionNonCug_Call() const
    {
        return Contains(0);
    }

    const NonCug_Call& GetNonCug_Call() const
    {
        ITS_REQUIRE(OptionNonCug_Call());
        return static_cast<const NonCug_Call&> (ElementAt(0));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_CONTINUE_WITH_ARGUMENT_ARG_EXTENSION_H_)
