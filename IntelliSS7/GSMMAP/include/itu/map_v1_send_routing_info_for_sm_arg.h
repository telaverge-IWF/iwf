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


#if !defined(_MAP_V1_SEND_ROUTING_INFO_FOR_SM_ARG_H_)
#define _MAP_V1_SEND_ROUTING_INFO_FOR_SM_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnBoolean.h>
#include <AsnOctetString.h>

#include <map_v1_isdn_address_string.h>
#include <map_v1_address_string.h>
#include <map_v1_cug_interlock.h>
#include <map_v1_teleservice_code.h>



namespace map_v1 {



class SendRoutingInfoForSMArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Sm_RP_PRI : public its::AsnBoolean
    {
    public:

        Sm_RP_PRI(bool value) : its::AsnBoolean(value, false)
        {
            Initialize();
        }

        Sm_RP_PRI(its::Octets& octets) : its::AsnBoolean(false, false)
        {
            Initialize();
            Decode(octets);
        }

        Sm_RP_PRI(const Sm_RP_PRI& rhs) : its::AsnBoolean(rhs)
        {
            // Nothing to do.
        }

        Sm_RP_PRI(its::AsnDescObject* description) : its::AsnBoolean(description)
        {
            // Nothing to do.
        }

        Sm_RP_PRI(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

        virtual ~Sm_RP_PRI()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Sm_RP_PRI(*this);
        }

        virtual std::string GetName() const
        { return "Sm_RP_PRI"; }

    };


        typedef map_v1::ISDN_AddressString ISDN_AddressString;


        typedef map_v1::AddressString AddressString;


        typedef map_v1::CUG_Interlock CUG_Interlock;


        typedef map_v1::TeleserviceCode TeleserviceCode;


////////// End Nested Class(es) //////////

    SendRoutingInfoForSMArg() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    SendRoutingInfoForSMArg(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    SendRoutingInfoForSMArg(const SendRoutingInfoForSMArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SendRoutingInfoForSMArg(its::AsnDescObject* description) : its::AsnSequence(5, description)
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

    static its::AsnDescObject* GetMsisdnStaticDescription();
    static its::AsnDescObject* GetSm_RP_PRIStaticDescription();
    static its::AsnDescObject* GetServiceCenterAddressStaticDescription();
    static its::AsnDescObject* GetCug_InterlockStaticDescription();
    static its::AsnDescObject* GetTeleserviceCodeStaticDescription();

public:

    virtual ~SendRoutingInfoForSMArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SendRoutingInfoForSMArg(*this);
    }

    virtual std::string GetName() const
    { return "SendRoutingInfoForSMArg"; }

    void SetMsisdn(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMsisdnStaticDescription());
        AddElement(0, element);
    }

    void SetMsisdn(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetMsisdnStaticDescription());
        AddElement(0, element);
    }

    const ISDN_AddressString& GetMsisdn() const
    {
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
    }

    void SetSm_RP_PRI(Sm_RP_PRI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSm_RP_PRIStaticDescription());
        AddElement(1, element);
    }

    void SetSm_RP_PRI(const Sm_RP_PRI& element)
    {
        its::AsnObject& asnObject = const_cast<Sm_RP_PRI&>(element);
        asnObject.SetDescription(GetSm_RP_PRIStaticDescription());
        AddElement(1, element);
    }

    const Sm_RP_PRI& GetSm_RP_PRI() const
    {
        return static_cast<const Sm_RP_PRI&> (ElementAt(1));
    }

    void SetServiceCenterAddress(AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetServiceCenterAddressStaticDescription());
        AddElement(2, element);
    }

    void SetServiceCenterAddress(const AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<AddressString&>(element);
        asnObject.SetDescription(GetServiceCenterAddressStaticDescription());
        AddElement(2, element);
    }

    const AddressString& GetServiceCenterAddress() const
    {
        return static_cast<const AddressString&> (ElementAt(2));
    }

    void SetCug_Interlock(CUG_Interlock* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCug_InterlockStaticDescription());
        AddElement(3, element);
    }

    void SetCug_Interlock(const CUG_Interlock& element)
    {
        its::AsnObject& asnObject = const_cast<CUG_Interlock&>(element);
        asnObject.SetDescription(GetCug_InterlockStaticDescription());
        AddElement(3, element);
    }

    bool OptionCug_Interlock() const
    {
        return Contains(3);
    }

    const CUG_Interlock& GetCug_Interlock() const
    {
        ITS_REQUIRE(OptionCug_Interlock());
        return static_cast<const CUG_Interlock&> (ElementAt(3));
    }

    void SetTeleserviceCode(TeleserviceCode* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTeleserviceCodeStaticDescription());
        AddElement(4, element);
    }

    void SetTeleserviceCode(const TeleserviceCode& element)
    {
        its::AsnObject& asnObject = const_cast<TeleserviceCode&>(element);
        asnObject.SetDescription(GetTeleserviceCodeStaticDescription());
        AddElement(4, element);
    }

    bool OptionTeleserviceCode() const
    {
        return Contains(4);
    }

    const TeleserviceCode& GetTeleserviceCode() const
    {
        ITS_REQUIRE(OptionTeleserviceCode());
        return static_cast<const TeleserviceCode&> (ElementAt(4));
    }

};



} // namespace.

#endif    // !defined(_MAP_V1_SEND_ROUTING_INFO_FOR_SM_ARG_H_)

