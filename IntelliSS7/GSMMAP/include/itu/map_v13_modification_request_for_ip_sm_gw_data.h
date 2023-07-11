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


#if !defined(_MAP_V13_MODIFICATION_REQUEST_FOR_IP_SM_GW_DATA_H_)
#define _MAP_V13_MODIFICATION_REQUEST_FOR_IP_SM_GW_DATA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>

#include <map_v13_modification_instruction.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class ModificationRequestFor_IP_SM_GW_Data : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::ModificationInstruction ModificationInstruction;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    ModificationRequestFor_IP_SM_GW_Data() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    ModificationRequestFor_IP_SM_GW_Data(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    ModificationRequestFor_IP_SM_GW_Data(const ModificationRequestFor_IP_SM_GW_Data& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ModificationRequestFor_IP_SM_GW_Data(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetModifyRegistrationStatusStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~ModificationRequestFor_IP_SM_GW_Data()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ModificationRequestFor_IP_SM_GW_Data(*this);
    }

    virtual std::string GetName() const
    { return "ModificationRequestFor_IP_SM_GW_Data"; }

    void SetModifyRegistrationStatus(ModificationInstruction* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetModifyRegistrationStatusStaticDescription());
        AddElement(0, element);
    }

    void SetModifyRegistrationStatus(const ModificationInstruction& element)
    {
        its::AsnObject& asnObject = const_cast<ModificationInstruction&>(element);
        asnObject.SetDescription(GetModifyRegistrationStatusStaticDescription());
        AddElement(0, element);
    }

    bool OptionModifyRegistrationStatus() const
    {
        return Contains(0);
    }

    const ModificationInstruction& GetModifyRegistrationStatus() const
    {
        ITS_REQUIRE(OptionModifyRegistrationStatus());
        return static_cast<const ModificationInstruction&> (ElementAt(0));
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

};



} // namespace.

#endif    // !defined(_MAP_V13_MODIFICATION_REQUEST_FOR_IP_SM_GW_DATA_H_)

