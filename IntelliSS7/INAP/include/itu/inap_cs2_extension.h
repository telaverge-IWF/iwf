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


#if !defined(_INAP_CS2_EXTENSION_H_)
#define _INAP_CS2_EXTENSION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSet.h>
#include <AsnInteger.h>
#include <AsnBoolean.h>
#include <AsnAny.h>



namespace inap_cs2 {



class Extension : public its::AsnSet
{
public:


////////// Begin Nested Class(es) //////////



    class Identifier : public its::AsnInteger
    {
    public:

        Identifier() : its::AsnInteger(false)
        {
            Initialize();
        }

        Identifier(long value) : its::AsnInteger(value, false)
        {
            Initialize();
        }

        Identifier(its::Octets& octets) : its::AsnInteger(false)
        {
            Initialize();
            Decode(octets);
        }

        Identifier(const Identifier& rhs) : its::AsnInteger(rhs)
        {
            // Nothing to do.
        }

        Identifier(its::AsnDescObject* description) : its::AsnInteger(description)
        {
            // Nothing to do.
        }

        Identifier(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

        virtual ~Identifier()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Identifier(*this);
        }

        virtual std::string GetName() const
        { return "Identifier"; }

    };



    class Critical : public its::AsnBoolean
    {
    public:

        Critical(bool value) : its::AsnBoolean(value, false)
        {
            Initialize();
        }

        Critical(its::Octets& octets) : its::AsnBoolean(false, false)
        {
            Initialize();
            Decode(octets);
        }

        Critical(const Critical& rhs) : its::AsnBoolean(rhs)
        {
            // Nothing to do.
        }

        Critical(its::AsnDescObject* description) : its::AsnBoolean(description)
        {
            // Nothing to do.
        }

        Critical(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

        virtual ~Critical()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Critical(*this);
        }

        virtual std::string GetName() const
        { return "Critical"; }

    };



    class Item : public its::AsnAny
    {
    public:

        Item() : its::AsnAny(false)
        {
            Initialize();
        }

        Item(its::AsnObject* any) : its::AsnAny(any, false)
        {
            Initialize();
        }

        Item(its::Octets& octets) : its::AsnAny(false)
        {
            Initialize();
            Decode(octets);
        }

        Item(const Item& rhs) : its::AsnAny(rhs)
        {
            // Nothing to do.
        }

        Item(its::AsnDescObject* description) : its::AsnAny(description)
        {
            // Nothing to do.
        }

    Item(its::AsnDescObject* description, its::AsnObject* any) : its::AsnAny(description, any)
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

        virtual ~Item()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Item(*this);
        }

        virtual std::string GetName() const
        { return "Item"; }

    };


////////// End Nested Class(es) //////////

    Extension() : its::AsnSet(3, false)
    {
        Initialize();
    }

    Extension(its::Octets& octets) : its::AsnSet(3, false)
    {
        Initialize();
        Decode(octets);
    }

    Extension(const Extension& rhs) : its::AsnSet(rhs)
    {
        // Nothing to do.
    }

    Extension(its::AsnDescObject* description) : its::AsnSet(3, description)
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

    static its::AsnDescObject* GetIdentifierStaticDescription();
    static its::AsnDescObject* GetCriticalStaticDescription();
    static its::AsnDescObject* GetItemStaticDescription();

public:

    virtual ~Extension()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Extension(*this);
    }

    virtual std::string GetName() const
    { return "Extension"; }

    void SetIdentifier(Identifier* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIdentifierStaticDescription());
        AddElement(0, element);
    }

    void SetIdentifier(const Identifier& element)
    {
        its::AsnObject& asnObject = const_cast<Identifier&>(element);
        asnObject.SetDescription(GetIdentifierStaticDescription());
        AddElement(0, element);
}

    const Identifier& GetIdentifier() const
    {
        return static_cast<const Identifier&> (ElementAt(0));
    }

    void SetCritical(Critical* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCriticalStaticDescription());
        AddElement(1, element);
    }

    void SetCritical(const Critical& element)
    {
        its::AsnObject& asnObject = const_cast<Critical&>(element);
        asnObject.SetDescription(GetCriticalStaticDescription());
        AddElement(1, element);
}

    bool OptionCritical() const
    {
        return Contains(1);
    }

    const Critical& GetCritical() const
    {
        ITS_REQUIRE(OptionCritical());
        return static_cast<const Critical&> (ElementAt(1));
    }

    void SetItem(Item* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetItemStaticDescription());
        AddElement(2, element);
    }

    void SetItem(const Item& element)
    {
        its::AsnObject& asnObject = const_cast<Item&>(element);
        asnObject.SetDescription(GetItemStaticDescription());
        AddElement(2, element);
}

    const Item& GetItem() const
    {
        return static_cast<const Item&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_EXTENSION_H_)

