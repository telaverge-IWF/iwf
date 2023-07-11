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


#if !defined(_MAP_V13_USER_CSG_INFORMATION_H_)
#define _MAP_V13_USER_CSG_INFORMATION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnBitString.h>

#include <map_v13_csg_id.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class UserCSGInformation : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class AccessMode : public its::AsnOctetString
    {
    public:

        AccessMode() : its::AsnOctetString(false)
        {
            Initialize();
        }

        AccessMode(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        AccessMode(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        AccessMode(const AccessMode& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        AccessMode(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        AccessMode(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~AccessMode()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new AccessMode(*this);
        }

        virtual std::string GetName() const
        { return "AccessMode"; }

    };



    class Cmi : public its::AsnOctetString
    {
    public:

        Cmi() : its::AsnOctetString(false)
        {
            Initialize();
        }

        Cmi(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        Cmi(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        Cmi(const Cmi& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        Cmi(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        Cmi(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~Cmi()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Cmi(*this);
        }

        virtual std::string GetName() const
        { return "Cmi"; }

    };


        typedef map_v13::CSG_Id CSG_Id;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    UserCSGInformation() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    UserCSGInformation(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    UserCSGInformation(const UserCSGInformation& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    UserCSGInformation(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetCsg_IdStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetAccessModeStaticDescription();
    static its::AsnDescObject* GetCmiStaticDescription();

public:

    virtual ~UserCSGInformation()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new UserCSGInformation(*this);
    }

    virtual std::string GetName() const
    { return "UserCSGInformation"; }

    void SetCsg_Id(CSG_Id* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCsg_IdStaticDescription());
        AddElement(0, element);
    }

    void SetCsg_Id(const CSG_Id& element)
    {
        its::AsnObject& asnObject = const_cast<CSG_Id&>(element);
        asnObject.SetDescription(GetCsg_IdStaticDescription());
        AddElement(0, element);
    }

    const CSG_Id& GetCsg_Id() const
    {
        return static_cast<const CSG_Id&> (ElementAt(0));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(1, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(1, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(1);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(1));
    }

    void SetAccessMode(AccessMode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAccessModeStaticDescription());
        AddElement(2, element);
    }

    void SetAccessMode(const AccessMode& element)
    {
        its::AsnObject& asnObject = const_cast<AccessMode&>(element);
        asnObject.SetDescription(GetAccessModeStaticDescription());
        AddElement(2, element);
    }

    bool OptionAccessMode() const
    {
        return Contains(2);
    }

    const AccessMode& GetAccessMode() const
    {
        ITS_REQUIRE(OptionAccessMode());
        return static_cast<const AccessMode&> (ElementAt(2));
    }

    void SetCmi(Cmi* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCmiStaticDescription());
        AddElement(3, element);
    }

    void SetCmi(const Cmi& element)
    {
        its::AsnObject& asnObject = const_cast<Cmi&>(element);
        asnObject.SetDescription(GetCmiStaticDescription());
        AddElement(3, element);
    }

    bool OptionCmi() const
    {
        return Contains(3);
    }

    const Cmi& GetCmi() const
    {
        ITS_REQUIRE(OptionCmi());
        return static_cast<const Cmi&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_USER_CSG_INFORMATION_H_)

