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


#if !defined(_MAP_V13_SEND_GROUP_CALL_END_SIGNAL_ARG_H_)
#define _MAP_V13_SEND_GROUP_CALL_END_SIGNAL_ARG_H_

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
#include <AsnBitString.h>

#include <map_v13_imsi.h>
#include <map_v13_extension_container.h>
#include <map_v13_talker_priority.h>
#include <map_v13_additional_info.h>



namespace map_v13 {



class SendGroupCallEndSignalArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::IMSI IMSI;


        typedef map_v13::ExtensionContainer ExtensionContainer;


        typedef map_v13::TalkerPriority TalkerPriority;


        typedef map_v13::AdditionalInfo AdditionalInfo;


////////// End Nested Class(es) //////////

    SendGroupCallEndSignalArg() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    SendGroupCallEndSignalArg(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    SendGroupCallEndSignalArg(const SendGroupCallEndSignalArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SendGroupCallEndSignalArg(its::AsnDescObject* description) : its::AsnSequence(4, description)
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
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetTalkerPriorityStaticDescription();
    static its::AsnDescObject* GetAdditionalInfoStaticDescription();

public:

    virtual ~SendGroupCallEndSignalArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SendGroupCallEndSignalArg(*this);
    }

    virtual std::string GetName() const
    { return "SendGroupCallEndSignalArg"; }

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

    bool OptionImsi() const
    {
        return Contains(0);
    }

    const IMSI& GetImsi() const
    {
        ITS_REQUIRE(OptionImsi());
        return static_cast<const IMSI&> (ElementAt(0));
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

    void SetTalkerPriority(TalkerPriority* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTalkerPriorityStaticDescription());
        AddElement(2, element);
    }

    void SetTalkerPriority(const TalkerPriority& element)
    {
        its::AsnObject& asnObject = const_cast<TalkerPriority&>(element);
        asnObject.SetDescription(GetTalkerPriorityStaticDescription());
        AddElement(2, element);
    }

    bool OptionTalkerPriority() const
    {
        return Contains(2);
    }

    const TalkerPriority& GetTalkerPriority() const
    {
        ITS_REQUIRE(OptionTalkerPriority());
        return static_cast<const TalkerPriority&> (ElementAt(2));
    }

    void SetAdditionalInfo(AdditionalInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAdditionalInfoStaticDescription());
        AddElement(3, element);
    }

    void SetAdditionalInfo(const AdditionalInfo& element)
    {
        its::AsnObject& asnObject = const_cast<AdditionalInfo&>(element);
        asnObject.SetDescription(GetAdditionalInfoStaticDescription());
        AddElement(3, element);
    }

    bool OptionAdditionalInfo() const
    {
        return Contains(3);
    }

    const AdditionalInfo& GetAdditionalInfo() const
    {
        ITS_REQUIRE(OptionAdditionalInfo());
        return static_cast<const AdditionalInfo&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_SEND_GROUP_CALL_END_SIGNAL_ARG_H_)

