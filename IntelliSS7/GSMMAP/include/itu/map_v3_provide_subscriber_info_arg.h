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


#if !defined(_MAP_V3_PROVIDE_SUBSCRIBER_INFO_ARG_H_)
#define _MAP_V3_PROVIDE_SUBSCRIBER_INFO_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v3_imsi.h>
#include <map_v3_lmsi.h>
#include <map_v3_requested_info.h>
#include <map_v3_extension_container.h>



namespace map_v3 {



class ProvideSubscriberInfoArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::IMSI IMSI;


        typedef map_v3::LMSI LMSI;


        typedef map_v3::RequestedInfo RequestedInfo;


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    ProvideSubscriberInfoArg() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    ProvideSubscriberInfoArg(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    ProvideSubscriberInfoArg(const ProvideSubscriberInfoArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ProvideSubscriberInfoArg(its::AsnDescObject* description) : its::AsnSequence(4, description)
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
    static its::AsnDescObject* GetRequestedInfoStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~ProvideSubscriberInfoArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ProvideSubscriberInfoArg(*this);
    }

    virtual std::string GetName() const
    { return "ProvideSubscriberInfoArg"; }

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

    void SetRequestedInfo(RequestedInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRequestedInfoStaticDescription());
        AddElement(2, element);
    }

    void SetRequestedInfo(const RequestedInfo& element)
    {
        its::AsnObject& asnObject = const_cast<RequestedInfo&>(element);
        asnObject.SetDescription(GetRequestedInfoStaticDescription());
        AddElement(2, element);
    }

    const RequestedInfo& GetRequestedInfo() const
    {
        return static_cast<const RequestedInfo&> (ElementAt(2));
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

};



} // namespace.

#endif    // !defined(_MAP_V3_PROVIDE_SUBSCRIBER_INFO_ARG_H_)

