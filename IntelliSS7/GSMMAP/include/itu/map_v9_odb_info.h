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


#if !defined(_MAP_V9_ODB_INFO_H_)
#define _MAP_V9_ODB_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>

#include <map_v9_odb_data.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class ODB_Info : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class NotificationToCSE : public its::AsnNull
    {
    public:

        NotificationToCSE() : its::AsnNull(false)
        {
            Initialize();
        }

        NotificationToCSE(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        NotificationToCSE(const NotificationToCSE& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        NotificationToCSE(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~NotificationToCSE()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new NotificationToCSE(*this);
        }

        virtual std::string GetName() const
        { return "NotificationToCSE"; }

    };


        typedef map_v9::ODB_Data ODB_Data;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    ODB_Info() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    ODB_Info(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    ODB_Info(const ODB_Info& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ODB_Info(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetOdb_DataStaticDescription();
    static its::AsnDescObject* GetNotificationToCSEStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~ODB_Info()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ODB_Info(*this);
    }

    virtual std::string GetName() const
    { return "ODB_Info"; }

    void SetOdb_Data(ODB_Data* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOdb_DataStaticDescription());
        AddElement(0, element);
    }

    void SetOdb_Data(const ODB_Data& element)
    {
        its::AsnObject& asnObject = const_cast<ODB_Data&>(element);
        asnObject.SetDescription(GetOdb_DataStaticDescription());
        AddElement(0, element);
    }

    const ODB_Data& GetOdb_Data() const
    {
        return static_cast<const ODB_Data&> (ElementAt(0));
    }

    void SetNotificationToCSE(NotificationToCSE* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNotificationToCSEStaticDescription());
        AddElement(1, element);
    }

    void SetNotificationToCSE(const NotificationToCSE& element)
    {
        its::AsnObject& asnObject = const_cast<NotificationToCSE&>(element);
        asnObject.SetDescription(GetNotificationToCSEStaticDescription());
        AddElement(1, element);
    }

    bool OptionNotificationToCSE() const
    {
        return Contains(1);
    }

    const NotificationToCSE& GetNotificationToCSE() const
    {
        ITS_REQUIRE(OptionNotificationToCSE());
        return static_cast<const NotificationToCSE&> (ElementAt(1));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(2, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(2, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(2);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_ODB_INFO_H_)

