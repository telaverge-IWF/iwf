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


#if !defined(_MAP_V3_VOICE_GROUP_CALL_DATA_H_)
#define _MAP_V3_VOICE_GROUP_CALL_DATA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v3_group_id.h>
#include <map_v3_extension_container.h>



namespace map_v3 {



class VoiceGroupCallData : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::GroupId GroupId;


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    VoiceGroupCallData() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    VoiceGroupCallData(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    VoiceGroupCallData(const VoiceGroupCallData& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    VoiceGroupCallData(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetGroupIdStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~VoiceGroupCallData()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new VoiceGroupCallData(*this);
    }

    virtual std::string GetName() const
    { return "VoiceGroupCallData"; }

    void SetGroupId(GroupId* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGroupIdStaticDescription());
        AddElement(0, element);
    }

    void SetGroupId(const GroupId& element)
    {
        its::AsnObject& asnObject = const_cast<GroupId&>(element);
        asnObject.SetDescription(GetGroupIdStaticDescription());
        AddElement(0, element);
    }

    const GroupId& GetGroupId() const
    {
        return static_cast<const GroupId&> (ElementAt(0));
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

#endif    // !defined(_MAP_V3_VOICE_GROUP_CALL_DATA_H_)

