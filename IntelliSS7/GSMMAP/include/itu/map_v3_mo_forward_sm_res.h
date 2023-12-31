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


#if !defined(_MAP_V3_MO_FORWARD_SM_RES_H_)
#define _MAP_V3_MO_FORWARD_SM_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v3_signal_info.h>
#include <map_v3_extension_container.h>



namespace map_v3 {



class MO_ForwardSM_Res : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::SignalInfo SignalInfo;


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    MO_ForwardSM_Res() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    MO_ForwardSM_Res(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    MO_ForwardSM_Res(const MO_ForwardSM_Res& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    MO_ForwardSM_Res(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetSm_RP_UIStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~MO_ForwardSM_Res()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MO_ForwardSM_Res(*this);
    }

    virtual std::string GetName() const
    { return "MO_ForwardSM_Res"; }

    void SetSm_RP_UI(SignalInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSm_RP_UIStaticDescription());
        AddElement(0, element);
    }

    void SetSm_RP_UI(const SignalInfo& element)
    {
        its::AsnObject& asnObject = const_cast<SignalInfo&>(element);
        asnObject.SetDescription(GetSm_RP_UIStaticDescription());
        AddElement(0, element);
    }

    bool OptionSm_RP_UI() const
    {
        return Contains(0);
    }

    const SignalInfo& GetSm_RP_UI() const
    {
        ITS_REQUIRE(OptionSm_RP_UI());
        return static_cast<const SignalInfo&> (ElementAt(0));
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

#endif    // !defined(_MAP_V3_MO_FORWARD_SM_RES_H_)

