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


#if !defined(_MAP_V1_FORWARDING_FEATURE_H_)
#define _MAP_V1_FORWARDING_FEATURE_H_

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
#include <AsnInteger.h>

#include <map_v1_basic_service_code.h>
#include <map_v1_ss_status.h>
#include <map_v1_isdn_address_string.h>
#include <map_v1_forwarding_options.h>
#include <map_v1_no_reply_condition_time.h>



namespace map_v1 {



class ForwardingFeature : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v1::BasicServiceCode BasicServiceCode;


        typedef map_v1::SS_Status SS_Status;


        typedef map_v1::ISDN_AddressString ISDN_AddressString;


        typedef map_v1::ForwardingOptions ForwardingOptions;


        typedef map_v1::NoReplyConditionTime NoReplyConditionTime;


////////// End Nested Class(es) //////////

    ForwardingFeature() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    ForwardingFeature(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    ForwardingFeature(const ForwardingFeature& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ForwardingFeature(its::AsnDescObject* description) : its::AsnSequence(5, description)
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

    static its::AsnDescObject* GetBasicServiceStaticDescription();
    static its::AsnDescObject* GetSs_StatusStaticDescription();
    static its::AsnDescObject* GetForwardedToNumberStaticDescription();
    static its::AsnDescObject* GetForwardingOptionsStaticDescription();
    static its::AsnDescObject* GetNoReplyConditionTimeStaticDescription();

public:

    virtual ~ForwardingFeature()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ForwardingFeature(*this);
    }

    virtual std::string GetName() const
    { return "ForwardingFeature"; }

    void SetBasicService(BasicServiceCode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBasicServiceStaticDescription());
        AddElement(0, element);
    }

    void SetBasicService(const BasicServiceCode& element)
    {
        its::AsnObject& asnObject = const_cast<BasicServiceCode&>(element);
        asnObject.SetDescription(GetBasicServiceStaticDescription());
        AddElement(0, element);
    }

    bool OptionBasicService() const
    {
        return Contains(0);
    }

    const BasicServiceCode& GetBasicService() const
    {
        ITS_REQUIRE(OptionBasicService());
        return static_cast<const BasicServiceCode&> (ElementAt(0));
    }

    void SetSs_Status(SS_Status* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_StatusStaticDescription());
        AddElement(1, element);
    }

    void SetSs_Status(const SS_Status& element)
    {
        its::AsnObject& asnObject = const_cast<SS_Status&>(element);
        asnObject.SetDescription(GetSs_StatusStaticDescription());
        AddElement(1, element);
    }

    const SS_Status& GetSs_Status() const
    {
        return static_cast<const SS_Status&> (ElementAt(1));
    }

    void SetForwardedToNumber(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardedToNumberStaticDescription());
        AddElement(2, element);
    }

    void SetForwardedToNumber(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetForwardedToNumberStaticDescription());
        AddElement(2, element);
    }

    bool OptionForwardedToNumber() const
    {
        return Contains(2);
    }

    const ISDN_AddressString& GetForwardedToNumber() const
    {
        ITS_REQUIRE(OptionForwardedToNumber());
        return static_cast<const ISDN_AddressString&> (ElementAt(2));
    }

    void SetForwardingOptions(ForwardingOptions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardingOptionsStaticDescription());
        AddElement(3, element);
    }

    void SetForwardingOptions(const ForwardingOptions& element)
    {
        its::AsnObject& asnObject = const_cast<ForwardingOptions&>(element);
        asnObject.SetDescription(GetForwardingOptionsStaticDescription());
        AddElement(3, element);
    }

    bool OptionForwardingOptions() const
    {
        return Contains(3);
    }

    const ForwardingOptions& GetForwardingOptions() const
    {
        ITS_REQUIRE(OptionForwardingOptions());
        return static_cast<const ForwardingOptions&> (ElementAt(3));
    }

    void SetNoReplyConditionTime(NoReplyConditionTime* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNoReplyConditionTimeStaticDescription());
        AddElement(4, element);
    }

    void SetNoReplyConditionTime(const NoReplyConditionTime& element)
    {
        its::AsnObject& asnObject = const_cast<NoReplyConditionTime&>(element);
        asnObject.SetDescription(GetNoReplyConditionTimeStaticDescription());
        AddElement(4, element);
    }

    bool OptionNoReplyConditionTime() const
    {
        return Contains(4);
    }

    const NoReplyConditionTime& GetNoReplyConditionTime() const
    {
        ITS_REQUIRE(OptionNoReplyConditionTime());
        return static_cast<const NoReplyConditionTime&> (ElementAt(4));
    }

};



} // namespace.

#endif    // !defined(_MAP_V1_FORWARDING_FEATURE_H_)

