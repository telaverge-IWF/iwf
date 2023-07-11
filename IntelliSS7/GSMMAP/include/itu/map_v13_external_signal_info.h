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


#if !defined(_MAP_V13_EXTERNAL_SIGNAL_INFO_H_)
#define _MAP_V13_EXTERNAL_SIGNAL_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>
#include <AsnOctetString.h>

#include <map_v13_protocol_id.h>
#include <map_v13_signal_info.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class ExternalSignalInfo : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::ProtocolId ProtocolId;


        typedef map_v13::SignalInfo SignalInfo;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    ExternalSignalInfo() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    ExternalSignalInfo(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    ExternalSignalInfo(const ExternalSignalInfo& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ExternalSignalInfo(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetProtocolIdStaticDescription();
    static its::AsnDescObject* GetSignalInfoStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~ExternalSignalInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ExternalSignalInfo(*this);
    }

    virtual std::string GetName() const
    { return "ExternalSignalInfo"; }

    void SetProtocolId(ProtocolId* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetProtocolIdStaticDescription());
        AddElement(0, element);
    }

    void SetProtocolId(const ProtocolId& element)
    {
        its::AsnObject& asnObject = const_cast<ProtocolId&>(element);
        asnObject.SetDescription(GetProtocolIdStaticDescription());
        AddElement(0, element);
    }

    const ProtocolId& GetProtocolId() const
    {
        return static_cast<const ProtocolId&> (ElementAt(0));
    }

    void SetSignalInfo(SignalInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSignalInfoStaticDescription());
        AddElement(1, element);
    }

    void SetSignalInfo(const SignalInfo& element)
    {
        its::AsnObject& asnObject = const_cast<SignalInfo&>(element);
        asnObject.SetDescription(GetSignalInfoStaticDescription());
        AddElement(1, element);
    }

    const SignalInfo& GetSignalInfo() const
    {
        return static_cast<const SignalInfo&> (ElementAt(1));
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

#endif    // !defined(_MAP_V13_EXTERNAL_SIGNAL_INFO_H_)
