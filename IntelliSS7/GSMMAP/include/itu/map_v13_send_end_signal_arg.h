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


#if !defined(_MAP_V13_SEND_END_SIGNAL_ARG_H_)
#define _MAP_V13_SEND_END_SIGNAL_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>

#include <map_v13_access_network_signal_info.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class SendEndSignal_Arg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::AccessNetworkSignalInfo AccessNetworkSignalInfo;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    SendEndSignal_Arg() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    SendEndSignal_Arg(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    SendEndSignal_Arg(const SendEndSignal_Arg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SendEndSignal_Arg(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetAn_APDUStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~SendEndSignal_Arg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SendEndSignal_Arg(*this);
    }

    virtual std::string GetName() const
    { return "SendEndSignal_Arg"; }

    void SetAn_APDU(AccessNetworkSignalInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAn_APDUStaticDescription());
        AddElement(0, element);
    }

    void SetAn_APDU(const AccessNetworkSignalInfo& element)
    {
        its::AsnObject& asnObject = const_cast<AccessNetworkSignalInfo&>(element);
        asnObject.SetDescription(GetAn_APDUStaticDescription());
        AddElement(0, element);
    }

    const AccessNetworkSignalInfo& GetAn_APDU() const
    {
        return static_cast<const AccessNetworkSignalInfo&> (ElementAt(0));
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

#endif    // !defined(_MAP_V13_SEND_END_SIGNAL_ARG_H_)

