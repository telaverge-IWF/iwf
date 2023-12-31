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


#if !defined(_MAP_V13_SEND_GROUP_CALL_INFO_ARG_H_)
#define _MAP_V13_SEND_GROUP_CALL_INFO_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnBitString.h>
#include <AsnEnumerated.h>

#include <map_v13_requested_info.h>
#include <map_v13_long_group_id.h>
#include <map_v13_ext_teleservice_code.h>
#include <map_v13_global_cell_id.h>
#include <map_v13_imsi.h>
#include <map_v13_tmsi.h>
#include <map_v13_additional_info.h>
#include <map_v13_talker_priority.h>
#include <map_v13_cksn.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class SendGroupCallInfoArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::RequestedInfo RequestedInfo;


        typedef map_v13::Long_GroupId Long_GroupId;


        typedef map_v13::Ext_TeleserviceCode Ext_TeleserviceCode;


        typedef map_v13::GlobalCellId GlobalCellId;


        typedef map_v13::IMSI IMSI;


        typedef map_v13::TMSI TMSI;


        typedef map_v13::AdditionalInfo AdditionalInfo;


        typedef map_v13::TalkerPriority TalkerPriority;


        typedef map_v13::Cksn Cksn;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    SendGroupCallInfoArg() : its::AsnSequence(10, false)
    {
        Initialize();
    }

    SendGroupCallInfoArg(its::Octets& octets) : its::AsnSequence(10, false)
    {
        Initialize();
        Decode(octets);
    }

    SendGroupCallInfoArg(const SendGroupCallInfoArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SendGroupCallInfoArg(its::AsnDescObject* description) : its::AsnSequence(10, description)
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

    static its::AsnDescObject* GetRequestedInfoStaticDescription();
    static its::AsnDescObject* GetGroupIdStaticDescription();
    static its::AsnDescObject* GetTeleserviceStaticDescription();
    static its::AsnDescObject* GetCellIdStaticDescription();
    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetTmsiStaticDescription();
    static its::AsnDescObject* GetAdditionalInfoStaticDescription();
    static its::AsnDescObject* GetTalkerPriorityStaticDescription();
    static its::AsnDescObject* GetCksnStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~SendGroupCallInfoArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SendGroupCallInfoArg(*this);
    }

    virtual std::string GetName() const
    { return "SendGroupCallInfoArg"; }

    void SetRequestedInfo(RequestedInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRequestedInfoStaticDescription());
        AddElement(0, element);
    }

    void SetRequestedInfo(const RequestedInfo& element)
    {
        its::AsnObject& asnObject = const_cast<RequestedInfo&>(element);
        asnObject.SetDescription(GetRequestedInfoStaticDescription());
        AddElement(0, element);
    }

    const RequestedInfo& GetRequestedInfo() const
    {
        return static_cast<const RequestedInfo&> (ElementAt(0));
    }

    void SetGroupId(Long_GroupId* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGroupIdStaticDescription());
        AddElement(1, element);
    }

    void SetGroupId(const Long_GroupId& element)
    {
        its::AsnObject& asnObject = const_cast<Long_GroupId&>(element);
        asnObject.SetDescription(GetGroupIdStaticDescription());
        AddElement(1, element);
    }

    const Long_GroupId& GetGroupId() const
    {
        return static_cast<const Long_GroupId&> (ElementAt(1));
    }

    void SetTeleservice(Ext_TeleserviceCode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTeleserviceStaticDescription());
        AddElement(2, element);
    }

    void SetTeleservice(const Ext_TeleserviceCode& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_TeleserviceCode&>(element);
        asnObject.SetDescription(GetTeleserviceStaticDescription());
        AddElement(2, element);
    }

    const Ext_TeleserviceCode& GetTeleservice() const
    {
        return static_cast<const Ext_TeleserviceCode&> (ElementAt(2));
    }

    void SetCellId(GlobalCellId* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCellIdStaticDescription());
        AddElement(3, element);
    }

    void SetCellId(const GlobalCellId& element)
    {
        its::AsnObject& asnObject = const_cast<GlobalCellId&>(element);
        asnObject.SetDescription(GetCellIdStaticDescription());
        AddElement(3, element);
    }

    bool OptionCellId() const
    {
        return Contains(3);
    }

    const GlobalCellId& GetCellId() const
    {
        ITS_REQUIRE(OptionCellId());
        return static_cast<const GlobalCellId&> (ElementAt(3));
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

    void SetTmsi(TMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTmsiStaticDescription());
        AddElement(5, element);
    }

    void SetTmsi(const TMSI& element)
    {
        its::AsnObject& asnObject = const_cast<TMSI&>(element);
        asnObject.SetDescription(GetTmsiStaticDescription());
        AddElement(5, element);
    }

    bool OptionTmsi() const
    {
        return Contains(5);
    }

    const TMSI& GetTmsi() const
    {
        ITS_REQUIRE(OptionTmsi());
        return static_cast<const TMSI&> (ElementAt(5));
    }

    void SetAdditionalInfo(AdditionalInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAdditionalInfoStaticDescription());
        AddElement(6, element);
    }

    void SetAdditionalInfo(const AdditionalInfo& element)
    {
        its::AsnObject& asnObject = const_cast<AdditionalInfo&>(element);
        asnObject.SetDescription(GetAdditionalInfoStaticDescription());
        AddElement(6, element);
    }

    bool OptionAdditionalInfo() const
    {
        return Contains(6);
    }

    const AdditionalInfo& GetAdditionalInfo() const
    {
        ITS_REQUIRE(OptionAdditionalInfo());
        return static_cast<const AdditionalInfo&> (ElementAt(6));
    }

    void SetTalkerPriority(TalkerPriority* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTalkerPriorityStaticDescription());
        AddElement(7, element);
    }

    void SetTalkerPriority(const TalkerPriority& element)
    {
        its::AsnObject& asnObject = const_cast<TalkerPriority&>(element);
        asnObject.SetDescription(GetTalkerPriorityStaticDescription());
        AddElement(7, element);
    }

    bool OptionTalkerPriority() const
    {
        return Contains(7);
    }

    const TalkerPriority& GetTalkerPriority() const
    {
        ITS_REQUIRE(OptionTalkerPriority());
        return static_cast<const TalkerPriority&> (ElementAt(7));
    }

    void SetCksn(Cksn* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCksnStaticDescription());
        AddElement(8, element);
    }

    void SetCksn(const Cksn& element)
    {
        its::AsnObject& asnObject = const_cast<Cksn&>(element);
        asnObject.SetDescription(GetCksnStaticDescription());
        AddElement(8, element);
    }

    bool OptionCksn() const
    {
        return Contains(8);
    }

    const Cksn& GetCksn() const
    {
        ITS_REQUIRE(OptionCksn());
        return static_cast<const Cksn&> (ElementAt(8));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(9, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(9, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(9);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(9));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_SEND_GROUP_CALL_INFO_ARG_H_)

