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


#if !defined(_MAP_V9_MODIFICATION_REQUEST_FOR_CF_INFO_H_)
#define _MAP_V9_MODIFICATION_REQUEST_FOR_CF_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnChoice.h>
#include <AsnInteger.h>
#include <AsnEnumerated.h>

#include <map_v9_ss_code.h>
#include <map_v9_ext_basic_service_code.h>
#include <map_v9_ext_ss_status.h>
#include <map_v9_address_string.h>
#include <map_v9_isdn_subaddress_string.h>
#include <map_v9_ext_no_rep_cond_time.h>
#include <map_v9_modification_instruction.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class ModificationRequestFor_CF_Info : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::SS_Code SS_Code;


        typedef map_v9::Ext_BasicServiceCode Ext_BasicServiceCode;


        typedef map_v9::Ext_SS_Status Ext_SS_Status;


        typedef map_v9::AddressString AddressString;


        typedef map_v9::ISDN_SubaddressString ISDN_SubaddressString;


        typedef map_v9::Ext_NoRepCondTime Ext_NoRepCondTime;


        typedef map_v9::ModificationInstruction ModificationInstruction;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    ModificationRequestFor_CF_Info() : its::AsnSequence(8, false)
    {
        Initialize();
    }

    ModificationRequestFor_CF_Info(its::Octets& octets) : its::AsnSequence(8, false)
    {
        Initialize();
        Decode(octets);
    }

    ModificationRequestFor_CF_Info(const ModificationRequestFor_CF_Info& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ModificationRequestFor_CF_Info(its::AsnDescObject* description) : its::AsnSequence(8, description)
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

    static its::AsnDescObject* GetSs_CodeStaticDescription();
    static its::AsnDescObject* GetBasicServiceStaticDescription();
    static its::AsnDescObject* GetSs_StatusStaticDescription();
    static its::AsnDescObject* GetForwardedToNumberStaticDescription();
    static its::AsnDescObject* GetForwardedToSubaddressStaticDescription();
    static its::AsnDescObject* GetNoReplyConditionTimeStaticDescription();
    static its::AsnDescObject* GetModifyNotificationToCSEStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~ModificationRequestFor_CF_Info()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ModificationRequestFor_CF_Info(*this);
    }

    virtual std::string GetName() const
    { return "ModificationRequestFor_CF_Info"; }

    void SetSs_Code(SS_Code* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_CodeStaticDescription());
        AddElement(0, element);
    }

    void SetSs_Code(const SS_Code& element)
    {
        its::AsnObject& asnObject = const_cast<SS_Code&>(element);
        asnObject.SetDescription(GetSs_CodeStaticDescription());
        AddElement(0, element);
    }

    const SS_Code& GetSs_Code() const
    {
        return static_cast<const SS_Code&> (ElementAt(0));
    }

    void SetBasicService(Ext_BasicServiceCode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBasicServiceStaticDescription());
        AddElement(1, element);
    }

    void SetBasicService(const Ext_BasicServiceCode& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_BasicServiceCode&>(element);
        asnObject.SetDescription(GetBasicServiceStaticDescription());
        AddElement(1, element);
    }

    bool OptionBasicService() const
    {
        return Contains(1);
    }

    const Ext_BasicServiceCode& GetBasicService() const
    {
        ITS_REQUIRE(OptionBasicService());
        return static_cast<const Ext_BasicServiceCode&> (ElementAt(1));
    }

    void SetSs_Status(Ext_SS_Status* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_StatusStaticDescription());
        AddElement(2, element);
    }

    void SetSs_Status(const Ext_SS_Status& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_SS_Status&>(element);
        asnObject.SetDescription(GetSs_StatusStaticDescription());
        AddElement(2, element);
    }

    bool OptionSs_Status() const
    {
        return Contains(2);
    }

    const Ext_SS_Status& GetSs_Status() const
    {
        ITS_REQUIRE(OptionSs_Status());
        return static_cast<const Ext_SS_Status&> (ElementAt(2));
    }

    void SetForwardedToNumber(AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardedToNumberStaticDescription());
        AddElement(3, element);
    }

    void SetForwardedToNumber(const AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<AddressString&>(element);
        asnObject.SetDescription(GetForwardedToNumberStaticDescription());
        AddElement(3, element);
    }

    bool OptionForwardedToNumber() const
    {
        return Contains(3);
    }

    const AddressString& GetForwardedToNumber() const
    {
        ITS_REQUIRE(OptionForwardedToNumber());
        return static_cast<const AddressString&> (ElementAt(3));
    }

    void SetForwardedToSubaddress(ISDN_SubaddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardedToSubaddressStaticDescription());
        AddElement(4, element);
    }

    void SetForwardedToSubaddress(const ISDN_SubaddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_SubaddressString&>(element);
        asnObject.SetDescription(GetForwardedToSubaddressStaticDescription());
        AddElement(4, element);
    }

    bool OptionForwardedToSubaddress() const
    {
        return Contains(4);
    }

    const ISDN_SubaddressString& GetForwardedToSubaddress() const
    {
        ITS_REQUIRE(OptionForwardedToSubaddress());
        return static_cast<const ISDN_SubaddressString&> (ElementAt(4));
    }

    void SetNoReplyConditionTime(Ext_NoRepCondTime* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNoReplyConditionTimeStaticDescription());
        AddElement(5, element);
    }

    void SetNoReplyConditionTime(const Ext_NoRepCondTime& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_NoRepCondTime&>(element);
        asnObject.SetDescription(GetNoReplyConditionTimeStaticDescription());
        AddElement(5, element);
    }

    bool OptionNoReplyConditionTime() const
    {
        return Contains(5);
    }

    const Ext_NoRepCondTime& GetNoReplyConditionTime() const
    {
        ITS_REQUIRE(OptionNoReplyConditionTime());
        return static_cast<const Ext_NoRepCondTime&> (ElementAt(5));
    }

    void SetModifyNotificationToCSE(ModificationInstruction* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetModifyNotificationToCSEStaticDescription());
        AddElement(6, element);
    }

    void SetModifyNotificationToCSE(const ModificationInstruction& element)
    {
        its::AsnObject& asnObject = const_cast<ModificationInstruction&>(element);
        asnObject.SetDescription(GetModifyNotificationToCSEStaticDescription());
        AddElement(6, element);
    }

    bool OptionModifyNotificationToCSE() const
    {
        return Contains(6);
    }

    const ModificationInstruction& GetModifyNotificationToCSE() const
    {
        ITS_REQUIRE(OptionModifyNotificationToCSE());
        return static_cast<const ModificationInstruction&> (ElementAt(6));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(7, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(7, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(7);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(7));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_MODIFICATION_REQUEST_FOR_CF_INFO_H_)

