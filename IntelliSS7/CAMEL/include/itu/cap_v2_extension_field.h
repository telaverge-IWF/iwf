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


#if !defined(_CAP_V2_EXTENSION_FIELD_H_)
#define _CAP_V2_EXTENSION_FIELD_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnInteger.h>
#include <AsnAny.h>
#include <AsnEnumerated.h>

#include <cap_v2_criticality_type.h>



namespace cap_v2 {



class ExtensionField : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Type : public its::AsnInteger
    {
    public:

        Type() : its::AsnInteger(false)
        {
            Initialize();
        }

        Type(long value) : its::AsnInteger(value, false)
        {
            Initialize();
        }

        Type(its::Octets& octets) : its::AsnInteger(false)
        {
            Initialize();
            Decode(octets);
        }

        Type(const Type& rhs) : its::AsnInteger(rhs)
        {
            // Nothing to do.
        }

        Type(its::AsnDescObject* description) : its::AsnInteger(description)
        {
            // Nothing to do.
        }

        Type(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

        virtual ~Type()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Type(*this);
        }

        virtual std::string GetName() const
        { return "Type"; }

    };



    class Value : public its::AsnAny
    {
    public:

        Value() : its::AsnAny(false)
        {
            Initialize();
        }

        Value(its::AsnObject* any) : its::AsnAny(any, false)
        {
            Initialize();
        }

        Value(its::Octets& octets) : its::AsnAny(false)
        {
            Initialize();
            Decode(octets);
        }

        Value(const Value& rhs) : its::AsnAny(rhs)
        {
            // Nothing to do.
        }

        Value(its::AsnDescObject* description) : its::AsnAny(description)
        {
            // Nothing to do.
        }

        Value(its::AsnDescObject* description, its::AsnObject* any) : its::AsnAny(description, any)
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

        virtual ~Value()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Value(*this);
        }

        virtual std::string GetName() const
        { return "Value"; }

    };


        typedef cap_v2::CriticalityType CriticalityType;


////////// End Nested Class(es) //////////

    ExtensionField() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    ExtensionField(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    ExtensionField(const ExtensionField& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ExtensionField(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetTypeStaticDescription();
    static its::AsnDescObject* GetCriticalityStaticDescription();
    static its::AsnDescObject* GetValueStaticDescription();

public:

    virtual ~ExtensionField()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ExtensionField(*this);
    }

    virtual std::string GetName() const
    { return "ExtensionField"; }

    void SetType(Type* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTypeStaticDescription());
        AddElement(0, element);
    }

    void SetType(const Type& element)
    {
        its::AsnObject& asnObject = const_cast<Type&>(element);
        asnObject.SetDescription(GetTypeStaticDescription());
        AddElement(0, element);
    }

    const Type& GetType() const
    {
        return static_cast<const Type&> (ElementAt(0));
    }

    void SetCriticality(CriticalityType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCriticalityStaticDescription());
        AddElement(1, element);
    }

    void SetCriticality(const CriticalityType& element)
    {
        its::AsnObject& asnObject = const_cast<CriticalityType&>(element);
        asnObject.SetDescription(GetCriticalityStaticDescription());
        AddElement(1, element);
    }

    const CriticalityType& GetCriticality() const
    {
        return static_cast<const CriticalityType&> (ElementAt(1));
    }

    void SetValue(Value* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetValueStaticDescription());
        AddElement(2, element);
    }

    void SetValue(const Value& element)
    {
        its::AsnObject& asnObject = const_cast<Value&>(element);
        asnObject.SetDescription(GetValueStaticDescription());
        AddElement(2, element);
    }

    const Value& GetValue() const
    {
        return static_cast<const Value&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_CAP_V2_EXTENSION_FIELD_H_)

