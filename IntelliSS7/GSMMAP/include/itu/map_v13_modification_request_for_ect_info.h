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


#if !defined(_MAP_V13_MODIFICATION_REQUEST_FOR_ECT_INFO_H_)
#define _MAP_V13_MODIFICATION_REQUEST_FOR_ECT_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnEnumerated.h>

#include <map_v13_ext_ss_status.h>
#include <map_v13_modification_instruction.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class ModificationRequestFor_ECT_Info : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::Ext_SS_Status Ext_SS_Status;


        typedef map_v13::ModificationInstruction ModificationInstruction;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    ModificationRequestFor_ECT_Info() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    ModificationRequestFor_ECT_Info(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    ModificationRequestFor_ECT_Info(const ModificationRequestFor_ECT_Info& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ModificationRequestFor_ECT_Info(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetSs_StatusStaticDescription();
    static its::AsnDescObject* GetModifyNotificationToCSEStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~ModificationRequestFor_ECT_Info()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ModificationRequestFor_ECT_Info(*this);
    }

    virtual std::string GetName() const
    { return "ModificationRequestFor_ECT_Info"; }

    void SetSs_Status(Ext_SS_Status* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_StatusStaticDescription());
        AddElement(0, element);
    }

    void SetSs_Status(const Ext_SS_Status& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_SS_Status&>(element);
        asnObject.SetDescription(GetSs_StatusStaticDescription());
        AddElement(0, element);
    }

    bool OptionSs_Status() const
    {
        return Contains(0);
    }

    const Ext_SS_Status& GetSs_Status() const
    {
        ITS_REQUIRE(OptionSs_Status());
        return static_cast<const Ext_SS_Status&> (ElementAt(0));
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

#endif    // !defined(_MAP_V13_MODIFICATION_REQUEST_FOR_ECT_INFO_H_)

