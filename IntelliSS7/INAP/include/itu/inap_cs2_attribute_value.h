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


#if !defined(_INAP_CS2_ATTRIBUTE_VALUE_H_)
#define _INAP_CS2_ATTRIBUTE_VALUE_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnChoice.h>
#include <AsnInteger.h>
#include <AsnOctetString.h>



namespace inap_cs2 {



class AttributeValue : public its::AsnChoice
{
public:


////////// Begin Nested Class(es) //////////



    class IntElement : public its::AsnInteger
    {
    public:

        IntElement() : its::AsnInteger(false)
        {
            Initialize();
        }

        IntElement(long value) : its::AsnInteger(value, false)
        {
            Initialize();
        }

        IntElement(its::Octets& octets) : its::AsnInteger(false)
        {
            Initialize();
            Decode(octets);
        }

        IntElement(const IntElement& rhs) : its::AsnInteger(rhs)
        {
            // Nothing to do.
        }

        IntElement(its::AsnDescObject* description) : its::AsnInteger(description)
        {
            // Nothing to do.
        }

        IntElement(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

        virtual ~IntElement()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new IntElement(*this);
        }

        virtual std::string GetName() const
        { return "IntElement"; }

    };



    class Int4Element : public its::AsnInteger
    {
    public:

        Int4Element() : its::AsnInteger(false)
        {
            Initialize();
        }

        Int4Element(long value) : its::AsnInteger(value, false)
        {
            Initialize();
        }

        Int4Element(its::Octets& octets) : its::AsnInteger(false)
        {
            Initialize();
            Decode(octets);
        }

        Int4Element(const Int4Element& rhs) : its::AsnInteger(rhs)
        {
            // Nothing to do.
        }

        Int4Element(its::AsnDescObject* description) : its::AsnInteger(description)
        {
            // Nothing to do.
        }

        Int4Element(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

        virtual ~Int4Element()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Int4Element(*this);
        }

        virtual std::string GetName() const
        { return "Int4Element"; }

    };



    class CharElement : public its::AsnOctetString
    {
    public:

        CharElement() : its::AsnOctetString(false)
        {
            Initialize();
        }

        CharElement(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        CharElement(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        CharElement(const CharElement& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        CharElement(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        CharElement(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~CharElement()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new CharElement(*this);
        }

        virtual std::string GetName() const
        { return "CharElement"; }

    };



    class StringElement : public its::AsnOctetString
    {
    public:

        StringElement() : its::AsnOctetString(false)
        {
            Initialize();
        }

        StringElement(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        StringElement(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        StringElement(const StringElement& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        StringElement(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        StringElement(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~StringElement()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new StringElement(*this);
        }

        virtual std::string GetName() const
        { return "StringElement"; }

    };


////////// End Nested Class(es) //////////

    AttributeValue() : its::AsnChoice(false)
    {
        Initialize();
    }

    AttributeValue(its::Octets& octets) : its::AsnChoice(false)
    {
        Initialize();
        Decode(octets);
    }

    AttributeValue(const AttributeValue& rhs) : its::AsnChoice(rhs)
    {
        // Nothing to do.
    }

    AttributeValue(its::AsnDescObject* description) : its::AsnChoice(description)
    {
        // Nothing to do.
    }

    AttributeValue(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

    static its::AsnDescObject* GetIntElementStaticDescription();
    static its::AsnDescObject* GetInt4ElementStaticDescription();
    static its::AsnDescObject* GetCharElementStaticDescription();
    static its::AsnDescObject* GetStringElementStaticDescription();

public:

    virtual ~AttributeValue()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AttributeValue(*this);
    }

    virtual std::string GetName() const
    { return "AttributeValue"; }

    void SetChoiceIntElement(IntElement* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetIntElementStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceIntElement(const IntElement& choice)
    {
        its::AsnObject& asnObject = const_cast<IntElement&>(choice);
        asnObject.SetDescription(GetIntElementStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceIntElement() const
    {
        return Contains(GetIntElementStaticDescription()->TagIdentity());
    }

    const IntElement& GetChoiceIntElement() const
    {
        ITS_REQUIRE(ChoiceIntElement());
        return static_cast<const IntElement&> (GetChoice());
    }

    void SetChoiceInt4Element(Int4Element* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetInt4ElementStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceInt4Element(const Int4Element& choice)
    {
        its::AsnObject& asnObject = const_cast<Int4Element&>(choice);
        asnObject.SetDescription(GetInt4ElementStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceInt4Element() const
    {
        return Contains(GetInt4ElementStaticDescription()->TagIdentity());
    }

    const Int4Element& GetChoiceInt4Element() const
    {
        ITS_REQUIRE(ChoiceInt4Element());
        return static_cast<const Int4Element&> (GetChoice());
    }

    void SetChoiceCharElement(CharElement* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetCharElementStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceCharElement(const CharElement& choice)
    {
        its::AsnObject& asnObject = const_cast<CharElement&>(choice);
        asnObject.SetDescription(GetCharElementStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceCharElement() const
    {
        return Contains(GetCharElementStaticDescription()->TagIdentity());
    }

    const CharElement& GetChoiceCharElement() const
    {
        ITS_REQUIRE(ChoiceCharElement());
        return static_cast<const CharElement&> (GetChoice());
    }

    void SetChoiceStringElement(StringElement* choice)
    {
        ITS_REQUIRE(choice != NULL);
        choice->AsnObject::SetDescription(GetStringElementStaticDescription());
        SetChoice(choice);
    }

    void SetChoiceStringElement(const StringElement& choice)
    {
        its::AsnObject& asnObject = const_cast<StringElement&>(choice);
        asnObject.SetDescription(GetStringElementStaticDescription());
        SetChoice(choice);
    }

    bool ChoiceStringElement() const
    {
        return Contains(GetStringElementStaticDescription()->TagIdentity());
    }

    const StringElement& GetChoiceStringElement() const
    {
        ITS_REQUIRE(ChoiceStringElement());
        return static_cast<const StringElement&> (GetChoice());
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_ATTRIBUTE_VALUE_H_)

