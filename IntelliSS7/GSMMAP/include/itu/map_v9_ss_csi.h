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


#if !defined(_MAP_V9_SS_CSI_H_)
#define _MAP_V9_SS_CSI_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>

#include <map_v9_ss_camel_data.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class SS_CSI : public its::AsnSequence
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



    class Csi_Active : public its::AsnNull
    {
    public:

        Csi_Active() : its::AsnNull(false)
        {
            Initialize();
        }

        Csi_Active(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Csi_Active(const Csi_Active& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Csi_Active(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Csi_Active()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Csi_Active(*this);
        }

        virtual std::string GetName() const
        { return "Csi_Active"; }

    };


        typedef map_v9::SS_CamelData SS_CamelData;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    SS_CSI() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    SS_CSI(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    SS_CSI(const SS_CSI& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SS_CSI(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetSs_CamelDataStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetNotificationToCSEStaticDescription();
    static its::AsnDescObject* GetCsi_ActiveStaticDescription();

public:

    virtual ~SS_CSI()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SS_CSI(*this);
    }

    virtual std::string GetName() const
    { return "SS_CSI"; }

    void SetSs_CamelData(SS_CamelData* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_CamelDataStaticDescription());
        AddElement(0, element);
    }

    void SetSs_CamelData(const SS_CamelData& element)
    {
        its::AsnObject& asnObject = const_cast<SS_CamelData&>(element);
        asnObject.SetDescription(GetSs_CamelDataStaticDescription());
        AddElement(0, element);
    }

    const SS_CamelData& GetSs_CamelData() const
    {
        return static_cast<const SS_CamelData&> (ElementAt(0));
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

    void SetNotificationToCSE(NotificationToCSE* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNotificationToCSEStaticDescription());
        AddElement(2, element);
    }

    void SetNotificationToCSE(const NotificationToCSE& element)
    {
        its::AsnObject& asnObject = const_cast<NotificationToCSE&>(element);
        asnObject.SetDescription(GetNotificationToCSEStaticDescription());
        AddElement(2, element);
    }

    bool OptionNotificationToCSE() const
    {
        return Contains(2);
    }

    const NotificationToCSE& GetNotificationToCSE() const
    {
        ITS_REQUIRE(OptionNotificationToCSE());
        return static_cast<const NotificationToCSE&> (ElementAt(2));
    }

    void SetCsi_Active(Csi_Active* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCsi_ActiveStaticDescription());
        AddElement(3, element);
    }

    void SetCsi_Active(const Csi_Active& element)
    {
        its::AsnObject& asnObject = const_cast<Csi_Active&>(element);
        asnObject.SetDescription(GetCsi_ActiveStaticDescription());
        AddElement(3, element);
    }

    bool OptionCsi_Active() const
    {
        return Contains(3);
    }

    const Csi_Active& GetCsi_Active() const
    {
        ITS_REQUIRE(OptionCsi_Active());
        return static_cast<const Csi_Active&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_SS_CSI_H_)

