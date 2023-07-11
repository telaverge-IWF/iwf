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


#if !defined(_MAP_V3_REGISTER_SS_ARG_H_)
#define _MAP_V3_REGISTER_SS_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnChoice.h>
#include <AsnInteger.h>

#include <map_v3_ss_code.h>
#include <map_v3_basic_service_code.h>
#include <map_v3_address_string.h>
#include <map_v3_isdn_subaddress_string.h>
#include <map_v3_no_reply_condition_time.h>



namespace map_v3 {



class RegisterSS_Arg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::SS_Code SS_Code;


        typedef map_v3::BasicServiceCode BasicServiceCode;


        typedef map_v3::AddressString AddressString;


        typedef map_v3::ISDN_SubaddressString ISDN_SubaddressString;


        typedef map_v3::NoReplyConditionTime NoReplyConditionTime;


////////// End Nested Class(es) //////////

    RegisterSS_Arg() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    RegisterSS_Arg(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    RegisterSS_Arg(const RegisterSS_Arg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    RegisterSS_Arg(its::AsnDescObject* description) : its::AsnSequence(5, description)
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

    static its::AsnDescObject* GetSs_CodeStaticDescription();
    static its::AsnDescObject* GetBasicServiceStaticDescription();
    static its::AsnDescObject* GetForwardedToNumberStaticDescription();
    static its::AsnDescObject* GetForwardedToSubaddressStaticDescription();
    static its::AsnDescObject* GetNoReplyConditionTimeStaticDescription();

public:

    virtual ~RegisterSS_Arg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RegisterSS_Arg(*this);
    }

    virtual std::string GetName() const
    { return "RegisterSS_Arg"; }

    void SetSs_Code(SS_Code* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSs_CodeStaticDescription());
        AddElement(0, element);
    }

    void SetSs_Code(const SS_Code& element)
    {
        its::AsnObject& asnObject = const_cast<SS_Code&>(element);
        asnObject.SetDescription(GetSs_CodeStaticDescription());
        AddElement(0, element);
    }

    const SS_Code& GetSs_Code() const
    {
        return static_cast<const SS_Code&> (ElementAt(0));
    }

    void SetBasicService(BasicServiceCode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetBasicServiceStaticDescription());
        AddElement(1, element);
    }

    void SetBasicService(const BasicServiceCode& element)
    {
        its::AsnObject& asnObject = const_cast<BasicServiceCode&>(element);
        asnObject.SetDescription(GetBasicServiceStaticDescription());
        AddElement(1, element);
    }

    bool OptionBasicService() const
    {
        return Contains(1);
    }

    const BasicServiceCode& GetBasicService() const
    {
        ITS_REQUIRE(OptionBasicService());
        return static_cast<const BasicServiceCode&> (ElementAt(1));
    }

    void SetForwardedToNumber(AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetForwardedToNumberStaticDescription());
        AddElement(2, element);
    }

    void SetForwardedToNumber(const AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<AddressString&>(element);
        asnObject.SetDescription(GetForwardedToNumberStaticDescription());
        AddElement(2, element);
    }

    bool OptionForwardedToNumber() const
    {
        return Contains(2);
    }

    const AddressString& GetForwardedToNumber() const
    {
        ITS_REQUIRE(OptionForwardedToNumber());
        return static_cast<const AddressString&> (ElementAt(2));
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

#endif    // !defined(_MAP_V3_REGISTER_SS_ARG_H_)

