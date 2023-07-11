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


#if !defined(_MAP_V3_RESUME_CALL_HANDLING_ARG_H_)
#define _MAP_V3_RESUME_CALL_HANDLING_ARG_H_

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

#include <map_v3_call_reference_number.h>
#include <map_v3_ext_basic_service_code.h>
#include <map_v3_forwarding_data.h>
#include <map_v3_imsi.h>
#include <map_v3_cug_check_info.h>
#include <map_v3_o_csi.h>
#include <map_v3_extension_container.h>



namespace map_v3 {



class ResumeCallHandlingArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::CallReferenceNumber CallReferenceNumber;


        typedef map_v3::Ext_BasicServiceCode Ext_BasicServiceCode;


        typedef map_v3::ForwardingData ForwardingData;


        typedef map_v3::IMSI IMSI;


        typedef map_v3::CUG_CheckInfo CUG_CheckInfo;


        typedef map_v3::O_CSI O_CSI;


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    ResumeCallHandlingArg() : its::AsnSequence(7, false)
    {
        Initialize();
    }

    ResumeCallHandlingArg(its::Octets& octets) : its::AsnSequence(7, false)
    {
        Initialize();
        Decode(octets);
    }

    ResumeCallHandlingArg(const ResumeCallHandlingArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ResumeCallHandlingArg(its::AsnDescObject* description) : its::AsnSequence(7, description)
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

    static its::AsnDescObject* GetCallReferenceNumberStaticDescription();
    static its::AsnDescObject* GetBasicServiceGroupStaticDescription();
    static its::AsnDescObject* GetForwardingDataStaticDescription();
    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetCug_CheckInfoStaticDescription();
    static its::AsnDescObject* GetO_CSIStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~ResumeCallHandlingArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ResumeCallHandlingArg(*this);
    }

    virtual std::string GetName() const
    { return "ResumeCallHandlingArg"; }

    void SetCallReferenceNumber(CallReferenceNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallReferenceNumberStaticDescription());
        AddElement(0, element);
    }

    void SetCallReferenceNumber(const CallReferenceNumber& element)
    {
        its::AsnObject& asnObject = const_cast<CallReferenceNumber&>(element);
        asnObject.SetDescription(GetCallReferenceNumberStaticDescription());
        AddElement(0, element);
    }

    const CallReferenceNumber& GetCallReferenceNumber() const
    {
        return static_cast<const CallReferenceNumber&> (ElementAt(0));
    }

    void SetBasicServiceGroup(Ext_BasicServiceCode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBasicServiceGroupStaticDescription());
        AddElement(1, element);
    }

    void SetBasicServiceGroup(const Ext_BasicServiceCode& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_BasicServiceCode&>(element);
        asnObject.SetDescription(GetBasicServiceGroupStaticDescription());
        AddElement(1, element);
    }

    const Ext_BasicServiceCode& GetBasicServiceGroup() const
    {
        return static_cast<const Ext_BasicServiceCode&> (ElementAt(1));
    }

    void SetForwardingData(ForwardingData* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardingDataStaticDescription());
        AddElement(2, element);
    }

    void SetForwardingData(const ForwardingData& element)
    {
        its::AsnObject& asnObject = const_cast<ForwardingData&>(element);
        asnObject.SetDescription(GetForwardingDataStaticDescription());
        AddElement(2, element);
    }

    const ForwardingData& GetForwardingData() const
    {
        return static_cast<const ForwardingData&> (ElementAt(2));
    }

    void SetImsi(IMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImsiStaticDescription());
        AddElement(3, element);
    }

    void SetImsi(const IMSI& element)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(element);
        asnObject.SetDescription(GetImsiStaticDescription());
        AddElement(3, element);
    }

    const IMSI& GetImsi() const
    {
        return static_cast<const IMSI&> (ElementAt(3));
    }

    void SetCug_CheckInfo(CUG_CheckInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCug_CheckInfoStaticDescription());
        AddElement(4, element);
    }

    void SetCug_CheckInfo(const CUG_CheckInfo& element)
    {
        its::AsnObject& asnObject = const_cast<CUG_CheckInfo&>(element);
        asnObject.SetDescription(GetCug_CheckInfoStaticDescription());
        AddElement(4, element);
    }

    bool OptionCug_CheckInfo() const
    {
        return Contains(4);
    }

    const CUG_CheckInfo& GetCug_CheckInfo() const
    {
        ITS_REQUIRE(OptionCug_CheckInfo());
        return static_cast<const CUG_CheckInfo&> (ElementAt(4));
    }

    void SetO_CSI(O_CSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetO_CSIStaticDescription());
        AddElement(5, element);
    }

    void SetO_CSI(const O_CSI& element)
    {
        its::AsnObject& asnObject = const_cast<O_CSI&>(element);
        asnObject.SetDescription(GetO_CSIStaticDescription());
        AddElement(5, element);
    }

    bool OptionO_CSI() const
    {
        return Contains(5);
    }

    const O_CSI& GetO_CSI() const
    {
        ITS_REQUIRE(OptionO_CSI());
        return static_cast<const O_CSI&> (ElementAt(5));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(6, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(6, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(6);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(6));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_RESUME_CALL_HANDLING_ARG_H_)
