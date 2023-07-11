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


#if !defined(_MAP_V13_O_CSI_H_)
#define _MAP_V13_O_CSI_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>
#include <AsnSequenceOf.h>
#include <AsnInteger.h>

#include <map_v13_o_bcsm_camel_tdp_data_list.h>
#include <map_v13_extension_container.h>
#include <map_v13_camel_capability_handling.h>



namespace map_v13 {



class O_CSI : public its::AsnSequence
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



    class CsiActive : public its::AsnNull
    {
    public:

        CsiActive() : its::AsnNull(false)
        {
            Initialize();
        }

        CsiActive(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        CsiActive(const CsiActive& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        CsiActive(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~CsiActive()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new CsiActive(*this);
        }

        virtual std::string GetName() const
        { return "CsiActive"; }

    };


        typedef map_v13::O_BcsmCamelTDPDataList O_BcsmCamelTDPDataList;


        typedef map_v13::ExtensionContainer ExtensionContainer;


        typedef map_v13::CamelCapabilityHandling CamelCapabilityHandling;


////////// End Nested Class(es) //////////

    O_CSI() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    O_CSI(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    O_CSI(const O_CSI& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    O_CSI(its::AsnDescObject* description) : its::AsnSequence(5, description)
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

    static its::AsnDescObject* GetO_BcsmCamelTDPDataListStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetCamelCapabilityHandlingStaticDescription();
    static its::AsnDescObject* GetNotificationToCSEStaticDescription();
    static its::AsnDescObject* GetCsiActiveStaticDescription();

public:

    virtual ~O_CSI()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new O_CSI(*this);
    }

    virtual std::string GetName() const
    { return "O_CSI"; }

    void SetO_BcsmCamelTDPDataList(O_BcsmCamelTDPDataList* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetO_BcsmCamelTDPDataListStaticDescription());
        AddElement(0, element);
    }

    void SetO_BcsmCamelTDPDataList(const O_BcsmCamelTDPDataList& element)
    {
        its::AsnObject& asnObject = const_cast<O_BcsmCamelTDPDataList&>(element);
        asnObject.SetDescription(GetO_BcsmCamelTDPDataListStaticDescription());
        AddElement(0, element);
    }

    const O_BcsmCamelTDPDataList& GetO_BcsmCamelTDPDataList() const
    {
        return static_cast<const O_BcsmCamelTDPDataList&> (ElementAt(0));
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

    void SetCamelCapabilityHandling(CamelCapabilityHandling* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCamelCapabilityHandlingStaticDescription());
        AddElement(2, element);
    }

    void SetCamelCapabilityHandling(const CamelCapabilityHandling& element)
    {
        its::AsnObject& asnObject = const_cast<CamelCapabilityHandling&>(element);
        asnObject.SetDescription(GetCamelCapabilityHandlingStaticDescription());
        AddElement(2, element);
    }

    bool OptionCamelCapabilityHandling() const
    {
        return Contains(2);
    }

    const CamelCapabilityHandling& GetCamelCapabilityHandling() const
    {
        ITS_REQUIRE(OptionCamelCapabilityHandling());
        return static_cast<const CamelCapabilityHandling&> (ElementAt(2));
    }

    void SetNotificationToCSE(NotificationToCSE* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNotificationToCSEStaticDescription());
        AddElement(3, element);
    }

    void SetNotificationToCSE(const NotificationToCSE& element)
    {
        its::AsnObject& asnObject = const_cast<NotificationToCSE&>(element);
        asnObject.SetDescription(GetNotificationToCSEStaticDescription());
        AddElement(3, element);
    }

    bool OptionNotificationToCSE() const
    {
        return Contains(3);
    }

    const NotificationToCSE& GetNotificationToCSE() const
    {
        ITS_REQUIRE(OptionNotificationToCSE());
        return static_cast<const NotificationToCSE&> (ElementAt(3));
    }

    void SetCsiActive(CsiActive* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCsiActiveStaticDescription());
        AddElement(4, element);
    }

    void SetCsiActive(const CsiActive& element)
    {
        its::AsnObject& asnObject = const_cast<CsiActive&>(element);
        asnObject.SetDescription(GetCsiActiveStaticDescription());
        AddElement(4, element);
    }

    bool OptionCsiActive() const
    {
        return Contains(4);
    }

    const CsiActive& GetCsiActive() const
    {
        ITS_REQUIRE(OptionCsiActive());
        return static_cast<const CsiActive&> (ElementAt(4));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_O_CSI_H_)

