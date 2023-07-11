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


#if !defined(_MAP_V9_FORWARDING_FEATURE_H_)
#define _MAP_V9_FORWARDING_FEATURE_H_

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

#include <map_v9_basic_service_code.h>
#include <map_v9_ss_status.h>
#include <map_v9_isdn_address_string.h>
#include <map_v9_isdn_subaddress_string.h>
#include <map_v9_forwarding_options.h>
#include <map_v9_no_reply_condition_time.h>
#include <map_v9_ftn_address_string.h>



namespace map_v9 {



class ForwardingFeature : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::BasicServiceCode BasicServiceCode;


        typedef map_v9::SS_Status SS_Status;


        typedef map_v9::ISDN_AddressString ISDN_AddressString;


        typedef map_v9::ISDN_SubaddressString ISDN_SubaddressString;


        typedef map_v9::ForwardingOptions ForwardingOptions;


        typedef map_v9::NoReplyConditionTime NoReplyConditionTime;


        typedef map_v9::FTN_AddressString FTN_AddressString;


////////// End Nested Class(es) //////////

    ForwardingFeature() : its::AsnSequence(7, false)
    {
        Initialize();
    }

    ForwardingFeature(its::Octets& octets) : its::AsnSequence(7, false)
    {
        Initialize();
        Decode(octets);
    }

    ForwardingFeature(const ForwardingFeature& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ForwardingFeature(its::AsnDescObject* description) : its::AsnSequence(7, description)
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
    static its::AsnDescObject* GetForwardedToSubaddressStaticDescription();
    static its::AsnDescObject* GetForwardingOptionsStaticDescription();
    static its::AsnDescObject* GetNoReplyConditionTimeStaticDescription();
    static its::AsnDescObject* GetLongForwardedToNumberStaticDescription();

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

    bool OptionSs_Status() const
    {
        return Contains(1);
    }

    const SS_Status& GetSs_Status() const
    {
        ITS_REQUIRE(OptionSs_Status());
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

    void SetForwardedToSubaddress(ISDN_SubaddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardedToSubaddressStaticDescription());
        AddElement(3, element);
    }

    void SetForwardedToSubaddress(const ISDN_SubaddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_SubaddressString&>(element);
        asnObject.SetDescription(GetForwardedToSubaddressStaticDescription());
        AddElement(3, element);
    }

    bool OptionForwardedToSubaddress() const
    {
        return Contains(3);
    }

    const ISDN_SubaddressString& GetForwardedToSubaddress() const
    {
        ITS_REQUIRE(OptionForwardedToSubaddress());
        return static_cast<const ISDN_SubaddressString&> (ElementAt(3));
    }

    void SetForwardingOptions(ForwardingOptions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardingOptionsStaticDescription());
        AddElement(4, element);
    }

    void SetForwardingOptions(const ForwardingOptions& element)
    {
        its::AsnObject& asnObject = const_cast<ForwardingOptions&>(element);
        asnObject.SetDescription(GetForwardingOptionsStaticDescription());
        AddElement(4, element);
    }

    bool OptionForwardingOptions() const
    {
        return Contains(4);
    }

    const ForwardingOptions& GetForwardingOptions() const
    {
        ITS_REQUIRE(OptionForwardingOptions());
        return static_cast<const ForwardingOptions&> (ElementAt(4));
    }

    void SetNoReplyConditionTime(NoReplyConditionTime* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNoReplyConditionTimeStaticDescription());
        AddElement(5, element);
    }

    void SetNoReplyConditionTime(const NoReplyConditionTime& element)
    {
        its::AsnObject& asnObject = const_cast<NoReplyConditionTime&>(element);
        asnObject.SetDescription(GetNoReplyConditionTimeStaticDescription());
        AddElement(5, element);
    }

    bool OptionNoReplyConditionTime() const
    {
        return Contains(5);
    }

    const NoReplyConditionTime& GetNoReplyConditionTime() const
    {
        ITS_REQUIRE(OptionNoReplyConditionTime());
        return static_cast<const NoReplyConditionTime&> (ElementAt(5));
    }

    void SetLongForwardedToNumber(FTN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetLongForwardedToNumberStaticDescription());
        AddElement(6, element);
    }

    void SetLongForwardedToNumber(const FTN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<FTN_AddressString&>(element);
        asnObject.SetDescription(GetLongForwardedToNumberStaticDescription());
        AddElement(6, element);
    }

    bool OptionLongForwardedToNumber() const
    {
        return Contains(6);
    }

    const FTN_AddressString& GetLongForwardedToNumber() const
    {
        ITS_REQUIRE(OptionLongForwardedToNumber());
        return static_cast<const FTN_AddressString&> (ElementAt(6));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_FORWARDING_FEATURE_H_)

