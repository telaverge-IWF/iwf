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


#if !defined(_MAP_V9_RESTORE_DATA_ARG_H_)
#define _MAP_V9_RESTORE_DATA_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v9_imsi.h>
#include <map_v9_lmsi.h>
#include <map_v9_extension_container.h>
#include <map_v9_vlr_capability.h>



namespace map_v9 {



class RestoreDataArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::IMSI IMSI;


        typedef map_v9::LMSI LMSI;


        typedef map_v9::ExtensionContainer ExtensionContainer;


        typedef map_v9::VLR_Capability VLR_Capability;


////////// End Nested Class(es) //////////

    RestoreDataArg() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    RestoreDataArg(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    RestoreDataArg(const RestoreDataArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    RestoreDataArg(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetLmsiStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetVlr_CapabilityStaticDescription();

public:

    virtual ~RestoreDataArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RestoreDataArg(*this);
    }

    virtual std::string GetName() const
    { return "RestoreDataArg"; }

    void SetImsi(IMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    void SetImsi(const IMSI& element)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(element);
        asnObject.SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    const IMSI& GetImsi() const
    {
        return static_cast<const IMSI&> (ElementAt(0));
    }

    void SetLmsi(LMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLmsiStaticDescription());
        AddElement(1, element);
    }

    void SetLmsi(const LMSI& element)
    {
        its::AsnObject& asnObject = const_cast<LMSI&>(element);
        asnObject.SetDescription(GetLmsiStaticDescription());
        AddElement(1, element);
    }

    bool OptionLmsi() const
    {
        return Contains(1);
    }

    const LMSI& GetLmsi() const
    {
        ITS_REQUIRE(OptionLmsi());
        return static_cast<const LMSI&> (ElementAt(1));
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

    void SetVlr_Capability(VLR_Capability* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetVlr_CapabilityStaticDescription());
        AddElement(3, element);
    }

    void SetVlr_Capability(const VLR_Capability& element)
    {
        its::AsnObject& asnObject = const_cast<VLR_Capability&>(element);
        asnObject.SetDescription(GetVlr_CapabilityStaticDescription());
        AddElement(3, element);
    }

    bool OptionVlr_Capability() const
    {
        return Contains(3);
    }

    const VLR_Capability& GetVlr_Capability() const
    {
        ITS_REQUIRE(OptionVlr_Capability());
        return static_cast<const VLR_Capability&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_RESTORE_DATA_ARG_H_)

