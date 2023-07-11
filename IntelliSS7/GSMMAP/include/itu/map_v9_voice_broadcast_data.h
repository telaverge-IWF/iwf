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


#if !defined(_MAP_V9_VOICE_BROADCAST_DATA_H_)
#define _MAP_V9_VOICE_BROADCAST_DATA_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>
#include <AsnOctetString.h>

#include <map_v9_group_id.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class VoiceBroadcastData : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class BroadcastInitEntitlement : public its::AsnNull
    {
    public:

        BroadcastInitEntitlement() : its::AsnNull(false)
        {
            Initialize();
        }

        BroadcastInitEntitlement(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        BroadcastInitEntitlement(const BroadcastInitEntitlement& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        BroadcastInitEntitlement(its::AsnDescObject* description) : its::AsnNull(description)
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

    public:

        virtual ~BroadcastInitEntitlement()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new BroadcastInitEntitlement(*this);
        }

        virtual std::string GetName() const
        { return "BroadcastInitEntitlement"; }

    };


        typedef map_v9::GroupId GroupId;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    VoiceBroadcastData() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    VoiceBroadcastData(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    VoiceBroadcastData(const VoiceBroadcastData& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    VoiceBroadcastData(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetGroupidStaticDescription();
    static its::AsnDescObject* GetBroadcastInitEntitlementStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~VoiceBroadcastData()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new VoiceBroadcastData(*this);
    }

    virtual std::string GetName() const
    { return "VoiceBroadcastData"; }

    void SetGroupid(GroupId* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGroupidStaticDescription());
        AddElement(0, element);
    }

    void SetGroupid(const GroupId& element)
    {
        its::AsnObject& asnObject = const_cast<GroupId&>(element);
        asnObject.SetDescription(GetGroupidStaticDescription());
        AddElement(0, element);
    }

    const GroupId& GetGroupid() const
    {
        return static_cast<const GroupId&> (ElementAt(0));
    }

    void SetBroadcastInitEntitlement(BroadcastInitEntitlement* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBroadcastInitEntitlementStaticDescription());
        AddElement(1, element);
    }

    void SetBroadcastInitEntitlement(const BroadcastInitEntitlement& element)
    {
        its::AsnObject& asnObject = const_cast<BroadcastInitEntitlement&>(element);
        asnObject.SetDescription(GetBroadcastInitEntitlementStaticDescription());
        AddElement(1, element);
    }

    bool OptionBroadcastInitEntitlement() const
    {
        return Contains(1);
    }

    const BroadcastInitEntitlement& GetBroadcastInitEntitlement() const
    {
        ITS_REQUIRE(OptionBroadcastInitEntitlement());
        return static_cast<const BroadcastInitEntitlement&> (ElementAt(1));
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

#endif    // !defined(_MAP_V9_VOICE_BROADCAST_DATA_H_)

