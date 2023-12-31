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


#if !defined(_MAP_V13_SS_INVOCATION_NOTIFICATION_ARG_H_)
#define _MAP_V13_SS_INVOCATION_NOTIFICATION_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnSequenceOf.h>
#include <AsnEnumerated.h>

#include <map_v13_imsi.h>
#include <map_v13_isdn_address_string.h>
#include <map_v13_ss_code.h>
#include <map_v13_ss_event_specification.h>
#include <map_v13_extension_container.h>
#include <map_v13_ccbs_request_state.h>



namespace map_v13 {



class SS_InvocationNotificationArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::IMSI IMSI;


        typedef map_v13::ISDN_AddressString ISDN_AddressString;


        typedef map_v13::SS_Code SS_Code;


        typedef map_v13::SS_EventSpecification SS_EventSpecification;


        typedef map_v13::ExtensionContainer ExtensionContainer;


        typedef map_v13::CCBS_RequestState CCBS_RequestState;


////////// End Nested Class(es) //////////

    SS_InvocationNotificationArg() : its::AsnSequence(7, false)
    {
        Initialize();
    }

    SS_InvocationNotificationArg(its::Octets& octets) : its::AsnSequence(7, false)
    {
        Initialize();
        Decode(octets);
    }

    SS_InvocationNotificationArg(const SS_InvocationNotificationArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SS_InvocationNotificationArg(its::AsnDescObject* description) : its::AsnSequence(7, description)
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
    static its::AsnDescObject* GetMsisdnStaticDescription();
    static its::AsnDescObject* GetSs_EventStaticDescription();
    static its::AsnDescObject* GetSs_EventSpecificationStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();
    static its::AsnDescObject* GetB_subscriberNumberStaticDescription();
    static its::AsnDescObject* GetCcbs_RequestStateStaticDescription();

public:

    virtual ~SS_InvocationNotificationArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SS_InvocationNotificationArg(*this);
    }

    virtual std::string GetName() const
    { return "SS_InvocationNotificationArg"; }

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

    void SetMsisdn(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMsisdnStaticDescription());
        AddElement(1, element);
    }

    void SetMsisdn(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetMsisdnStaticDescription());
        AddElement(1, element);
    }

    const ISDN_AddressString& GetMsisdn() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(1));
    }

    void SetSs_Event(SS_Code* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_EventStaticDescription());
        AddElement(2, element);
    }

    void SetSs_Event(const SS_Code& element)
    {
        its::AsnObject& asnObject = const_cast<SS_Code&>(element);
        asnObject.SetDescription(GetSs_EventStaticDescription());
        AddElement(2, element);
    }

    const SS_Code& GetSs_Event() const
    {
        return static_cast<const SS_Code&> (ElementAt(2));
    }

    void SetSs_EventSpecification(SS_EventSpecification* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_EventSpecificationStaticDescription());
        AddElement(3, element);
    }

    void SetSs_EventSpecification(const SS_EventSpecification& element)
    {
        its::AsnObject& asnObject = const_cast<SS_EventSpecification&>(element);
        asnObject.SetDescription(GetSs_EventSpecificationStaticDescription());
        AddElement(3, element);
    }

    bool OptionSs_EventSpecification() const
    {
        return Contains(3);
    }

    const SS_EventSpecification& GetSs_EventSpecification() const
    {
        ITS_REQUIRE(OptionSs_EventSpecification());
        return static_cast<const SS_EventSpecification&> (ElementAt(3));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(4, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(4, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(4);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(4));
    }

    void SetB_subscriberNumber(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetB_subscriberNumberStaticDescription());
        AddElement(5, element);
    }

    void SetB_subscriberNumber(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetB_subscriberNumberStaticDescription());
        AddElement(5, element);
    }

    bool OptionB_subscriberNumber() const
    {
        return Contains(5);
    }

    const ISDN_AddressString& GetB_subscriberNumber() const
    {
        ITS_REQUIRE(OptionB_subscriberNumber());
        return static_cast<const ISDN_AddressString&> (ElementAt(5));
    }

    void SetCcbs_RequestState(CCBS_RequestState* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCcbs_RequestStateStaticDescription());
        AddElement(6, element);
    }

    void SetCcbs_RequestState(const CCBS_RequestState& element)
    {
        its::AsnObject& asnObject = const_cast<CCBS_RequestState&>(element);
        asnObject.SetDescription(GetCcbs_RequestStateStaticDescription());
        AddElement(6, element);
    }

    bool OptionCcbs_RequestState() const
    {
        return Contains(6);
    }

    const CCBS_RequestState& GetCcbs_RequestState() const
    {
        ITS_REQUIRE(OptionCcbs_RequestState());
        return static_cast<const CCBS_RequestState&> (ElementAt(6));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_SS_INVOCATION_NOTIFICATION_ARG_H_)

