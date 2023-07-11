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


#if !defined(_CAP_V3_PRIVATE_EXTENSION_H_)
#define _CAP_V3_PRIVATE_EXTENSION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnObjectIdentifier.h>
#include <AsnAny.h>



namespace cap_v3 {



class PrivateExtension : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class ExtId : public its::AsnObjectIdentifier
    {
    public:

        ExtId() : its::AsnObjectIdentifier(false)
        {
            Initialize();
        }

        ExtId(const std::vector<long>& array) : its::AsnObjectIdentifier(array, false)
        {
            Initialize();
        }

        ExtId(its::Octets& octets) : its::AsnObjectIdentifier(false)
        {
            Initialize();
            Decode(octets);
        }

        ExtId(const ExtId& rhs) : its::AsnObjectIdentifier(rhs)
        {
            // Nothing to do.
        }

        ExtId(its::AsnDescObject* description) : its::AsnObjectIdentifier(description)
        {
            // Nothing to do.
        }

        ExtId(its::AsnDescObject* description, const std::vector<long>& array) : its::AsnObjectIdentifier(description, array)
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

        virtual ~ExtId()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new ExtId(*this);
        }

        virtual std::string GetName() const
        { return "ExtId"; }

    };



    class ExtType : public its::AsnAny
    {
    public:

        ExtType() : its::AsnAny(false)
        {
            Initialize();
        }

        ExtType(its::AsnObject* any) : its::AsnAny(any, false)
        {
            Initialize();
        }

        ExtType(its::Octets& octets) : its::AsnAny(false)
        {
            Initialize();
            Decode(octets);
        }

        ExtType(const ExtType& rhs) : its::AsnAny(rhs)
        {
            // Nothing to do.
        }

        ExtType(its::AsnDescObject* description) : its::AsnAny(description)
        {
            // Nothing to do.
        }

        ExtType(its::AsnDescObject* description, its::AsnObject* any) : its::AsnAny(description, any)
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

        virtual ~ExtType()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new ExtType(*this);
        }

        virtual std::string GetName() const
        { return "ExtType"; }

    };


////////// End Nested Class(es) //////////

    PrivateExtension() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    PrivateExtension(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    PrivateExtension(const PrivateExtension& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    PrivateExtension(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetExtIdStaticDescription();
    static its::AsnDescObject* GetExtTypeStaticDescription();

public:

    virtual ~PrivateExtension()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PrivateExtension(*this);
    }

    virtual std::string GetName() const
    { return "PrivateExtension"; }

    void SetExtId(ExtId* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtIdStaticDescription());
        AddElement(0, element);
    }

    void SetExtId(const ExtId& element)
    {
        its::AsnObject& asnObject = const_cast<ExtId&>(element);
        asnObject.SetDescription(GetExtIdStaticDescription());
        AddElement(0, element);
    }

    const ExtId& GetExtId() const
    {
        return static_cast<const ExtId&> (ElementAt(0));
    }

    void SetExtType(ExtType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtTypeStaticDescription());
        AddElement(1, element);
    }

    void SetExtType(const ExtType& element)
    {
        its::AsnObject& asnObject = const_cast<ExtType&>(element);
        asnObject.SetDescription(GetExtTypeStaticDescription());
        AddElement(1, element);
    }

    const ExtType& GetExtType() const
    {
        return static_cast<const ExtType&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_PRIVATE_EXTENSION_H_)
