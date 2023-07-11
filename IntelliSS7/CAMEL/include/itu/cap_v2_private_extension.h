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


#if !defined(_CAP_V2_PRIVATE_EXTENSION_H_)
#define _CAP_V2_PRIVATE_EXTENSION_H_

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



namespace cap_v2 {



class PrivateExtension : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class ExtensionId : public its::AsnObjectIdentifier
    {
    public:

        ExtensionId() : its::AsnObjectIdentifier(false)
        {
            Initialize();
        }

        ExtensionId(const std::vector<long>& array) : its::AsnObjectIdentifier(array, false)
        {
            Initialize();
        }

        ExtensionId(its::Octets& octets) : its::AsnObjectIdentifier(false)
        {
            Initialize();
            Decode(octets);
        }

        ExtensionId(const ExtensionId& rhs) : its::AsnObjectIdentifier(rhs)
        {
            // Nothing to do.
        }

        ExtensionId(its::AsnDescObject* description) : its::AsnObjectIdentifier(description)
        {
            // Nothing to do.
        }

        ExtensionId(its::AsnDescObject* description, const std::vector<long>& array) : its::AsnObjectIdentifier(description, array)
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

        virtual ~ExtensionId()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new ExtensionId(*this);
        }

        virtual std::string GetName() const
        { return "ExtensionId"; }

    };



    class ExtensionType : public its::AsnAny
    {
    public:

        ExtensionType() : its::AsnAny(false)
        {
            Initialize();
        }

        ExtensionType(its::AsnObject* any) : its::AsnAny(any, false)
        {
            Initialize();
        }

        ExtensionType(its::Octets& octets) : its::AsnAny(false)
        {
            Initialize();
            Decode(octets);
        }

        ExtensionType(const ExtensionType& rhs) : its::AsnAny(rhs)
        {
            // Nothing to do.
        }

        ExtensionType(its::AsnDescObject* description) : its::AsnAny(description)
        {
            // Nothing to do.
        }

        ExtensionType(its::AsnDescObject* description, its::AsnObject* any) : its::AsnAny(description, any)
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

        virtual ~ExtensionType()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new ExtensionType(*this);
        }

        virtual std::string GetName() const
        { return "ExtensionType"; }

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

    static its::AsnDescObject* GetExtensionIdStaticDescription();
    static its::AsnDescObject* GetExtensionTypeStaticDescription();

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

    void SetExtensionId(ExtensionId* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionIdStaticDescription());
        AddElement(0, element);
    }

    void SetExtensionId(const ExtensionId& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionId&>(element);
        asnObject.SetDescription(GetExtensionIdStaticDescription());
        AddElement(0, element);
    }

    const ExtensionId& GetExtensionId() const
    {
        return static_cast<const ExtensionId&> (ElementAt(0));
    }

    void SetExtensionType(ExtensionType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionTypeStaticDescription());
        AddElement(1, element);
    }

    void SetExtensionType(const ExtensionType& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionType&>(element);
        asnObject.SetDescription(GetExtensionTypeStaticDescription());
        AddElement(1, element);
    }

    bool OptionExtensionType() const
    {
        return Contains(1);
    }

    const ExtensionType& GetExtensionType() const
    {
        ITS_REQUIRE(OptionExtensionType());
        return static_cast<const ExtensionType&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_CAP_V2_PRIVATE_EXTENSION_H_)

