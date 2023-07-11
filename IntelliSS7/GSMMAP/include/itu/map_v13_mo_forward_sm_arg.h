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


#if !defined(_MAP_V13_MO_FORWARD_SM_ARG_H_)
#define _MAP_V13_MO_FORWARD_SM_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnChoice.h>
#include <AsnOctetString.h>

#include <map_v13_sm_rp_da.h>
#include <map_v13_sm_rp_oa.h>
#include <map_v13_signal_info.h>
#include <map_v13_extension_container.h>
#include <map_v13_imsi.h>



namespace map_v13 {



class MO_ForwardSM_Arg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::SM_RP_DA SM_RP_DA;


        typedef map_v13::SM_RP_OA SM_RP_OA;


        typedef map_v13::SignalInfo SignalInfo;


        typedef map_v13::ExtensionContainer ExtensionContainer;


        typedef map_v13::IMSI IMSI;


////////// End Nested Class(es) //////////

    MO_ForwardSM_Arg() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    MO_ForwardSM_Arg(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    MO_ForwardSM_Arg(const MO_ForwardSM_Arg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    MO_ForwardSM_Arg(its::AsnDescObject* description) : its::AsnSequence(5, description)
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

    static its::AsnDescObject* GetSm_RP_DAStaticDescription();
    static its::AsnDescObject* GetSm_RP_OAStaticDescription();
    static its::AsnDescObject* GetSm_RP_UIStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetImsiStaticDescription();

public:

    virtual ~MO_ForwardSM_Arg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MO_ForwardSM_Arg(*this);
    }

    virtual std::string GetName() const
    { return "MO_ForwardSM_Arg"; }

    void SetSm_RP_DA(SM_RP_DA* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSm_RP_DAStaticDescription());
        AddElement(0, element);
    }

    void SetSm_RP_DA(const SM_RP_DA& element)
    {
        its::AsnObject& asnObject = const_cast<SM_RP_DA&>(element);
        asnObject.SetDescription(GetSm_RP_DAStaticDescription());
        AddElement(0, element);
    }

    const SM_RP_DA& GetSm_RP_DA() const
    {
        return static_cast<const SM_RP_DA&> (ElementAt(0));
    }

    void SetSm_RP_OA(SM_RP_OA* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSm_RP_OAStaticDescription());
        AddElement(1, element);
    }

    void SetSm_RP_OA(const SM_RP_OA& element)
    {
        its::AsnObject& asnObject = const_cast<SM_RP_OA&>(element);
        asnObject.SetDescription(GetSm_RP_OAStaticDescription());
        AddElement(1, element);
    }

    const SM_RP_OA& GetSm_RP_OA() const
    {
        return static_cast<const SM_RP_OA&> (ElementAt(1));
    }

    void SetSm_RP_UI(SignalInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSm_RP_UIStaticDescription());
        AddElement(2, element);
    }

    void SetSm_RP_UI(const SignalInfo& element)
    {
        its::AsnObject& asnObject = const_cast<SignalInfo&>(element);
        asnObject.SetDescription(GetSm_RP_UIStaticDescription());
        AddElement(2, element);
    }

    const SignalInfo& GetSm_RP_UI() const
    {
        return static_cast<const SignalInfo&> (ElementAt(2));
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

    void SetImsi(IMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImsiStaticDescription());
        AddElement(4, element);
    }

    void SetImsi(const IMSI& element)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(element);
        asnObject.SetDescription(GetImsiStaticDescription());
        AddElement(4, element);
    }

    bool OptionImsi() const
    {
        return Contains(4);
    }

    const IMSI& GetImsi() const
    {
        ITS_REQUIRE(OptionImsi());
        return static_cast<const IMSI&> (ElementAt(4));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_MO_FORWARD_SM_ARG_H_)

