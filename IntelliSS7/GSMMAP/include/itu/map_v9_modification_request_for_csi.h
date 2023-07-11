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


#if !defined(_MAP_V9_MODIFICATION_REQUEST_FOR_CSI_H_)
#define _MAP_V9_MODIFICATION_REQUEST_FOR_CSI_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>

#include <map_v9_requested_camel_subscription_info.h>
#include <map_v9_modification_instruction.h>
#include <map_v9_extension_container.h>
#include <map_v9_additional_requested_camel_subscription_info.h>



namespace map_v9 {



class ModificationRequestFor_CSI : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::RequestedCAMEL_SubscriptionInfo RequestedCAMEL_SubscriptionInfo;


        typedef map_v9::ModificationInstruction ModificationInstruction;


        typedef map_v9::ExtensionContainer ExtensionContainer;


        typedef map_v9::AdditionalRequestedCAMEL_SubscriptionInfo AdditionalRequestedCAMEL_SubscriptionInfo;


////////// End Nested Class(es) //////////

    ModificationRequestFor_CSI() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    ModificationRequestFor_CSI(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    ModificationRequestFor_CSI(const ModificationRequestFor_CSI& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ModificationRequestFor_CSI(its::AsnDescObject* description) : its::AsnSequence(5, description)
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

    static its::AsnDescObject* GetRequestedCamel_SubscriptionInfoStaticDescription();
    static its::AsnDescObject* GetModifyNotificationToCSEStaticDescription();
    static its::AsnDescObject* GetModifyCSI_StateStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetAdditionalRequestedCAMEL_SubscriptionInfoStaticDescription();

public:

    virtual ~ModificationRequestFor_CSI()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ModificationRequestFor_CSI(*this);
    }

    virtual std::string GetName() const
    { return "ModificationRequestFor_CSI"; }

    void SetRequestedCamel_SubscriptionInfo(RequestedCAMEL_SubscriptionInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRequestedCamel_SubscriptionInfoStaticDescription());
        AddElement(0, element);
    }

    void SetRequestedCamel_SubscriptionInfo(const RequestedCAMEL_SubscriptionInfo& element)
    {
        its::AsnObject& asnObject = const_cast<RequestedCAMEL_SubscriptionInfo&>(element);
        asnObject.SetDescription(GetRequestedCamel_SubscriptionInfoStaticDescription());
        AddElement(0, element);
    }

    const RequestedCAMEL_SubscriptionInfo& GetRequestedCamel_SubscriptionInfo() const
    {
        return static_cast<const RequestedCAMEL_SubscriptionInfo&> (ElementAt(0));
    }

    void SetModifyNotificationToCSE(ModificationInstruction* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetModifyNotificationToCSEStaticDescription());
        AddElement(1, element);
    }

    void SetModifyNotificationToCSE(const ModificationInstruction& element)
    {
        its::AsnObject& asnObject = const_cast<ModificationInstruction&>(element);
        asnObject.SetDescription(GetModifyNotificationToCSEStaticDescription());
        AddElement(1, element);
    }

    bool OptionModifyNotificationToCSE() const
    {
        return Contains(1);
    }

    const ModificationInstruction& GetModifyNotificationToCSE() const
    {
        ITS_REQUIRE(OptionModifyNotificationToCSE());
        return static_cast<const ModificationInstruction&> (ElementAt(1));
    }

    void SetModifyCSI_State(ModificationInstruction* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetModifyCSI_StateStaticDescription());
        AddElement(2, element);
    }

    void SetModifyCSI_State(const ModificationInstruction& element)
    {
        its::AsnObject& asnObject = const_cast<ModificationInstruction&>(element);
        asnObject.SetDescription(GetModifyCSI_StateStaticDescription());
        AddElement(2, element);
    }

    bool OptionModifyCSI_State() const
    {
        return Contains(2);
    }

    const ModificationInstruction& GetModifyCSI_State() const
    {
        ITS_REQUIRE(OptionModifyCSI_State());
        return static_cast<const ModificationInstruction&> (ElementAt(2));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(3, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(3, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(3);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(3));
    }

    void SetAdditionalRequestedCAMEL_SubscriptionInfo(AdditionalRequestedCAMEL_SubscriptionInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAdditionalRequestedCAMEL_SubscriptionInfoStaticDescription());
        AddElement(4, element);
    }

    void SetAdditionalRequestedCAMEL_SubscriptionInfo(const AdditionalRequestedCAMEL_SubscriptionInfo& element)
    {
        its::AsnObject& asnObject = const_cast<AdditionalRequestedCAMEL_SubscriptionInfo&>(element);
        asnObject.SetDescription(GetAdditionalRequestedCAMEL_SubscriptionInfoStaticDescription());
        AddElement(4, element);
    }

    bool OptionAdditionalRequestedCAMEL_SubscriptionInfo() const
    {
        return Contains(4);
    }

    const AdditionalRequestedCAMEL_SubscriptionInfo& GetAdditionalRequestedCAMEL_SubscriptionInfo() const
    {
        ITS_REQUIRE(OptionAdditionalRequestedCAMEL_SubscriptionInfo());
        return static_cast<const AdditionalRequestedCAMEL_SubscriptionInfo&> (ElementAt(4));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_MODIFICATION_REQUEST_FOR_CSI_H_)
