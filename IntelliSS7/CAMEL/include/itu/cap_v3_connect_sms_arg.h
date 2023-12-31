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


#if !defined(_CAP_V3_CONNECT_SMS_ARG_H_)
#define _CAP_V3_CONNECT_SMS_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnSequenceOf.h>
#include <AsnOctetString.h>

#include <cap_v3_isdn_address_string.h>
#include <cap_v3_called_party_bcd_number.h>
#include <cap_v3_extension_field.h>



namespace cap_v3 {



class ConnectSMSArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Extensions : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef cap_v3::ExtensionField ExtensionField;


    ////////// End Nested Class //////////

        Extensions() : its::AsnSequenceOf(false)
        {
            Initialize();
        }

        Extensions(its::Octets& octets) : its::AsnSequenceOf(false)
        {
            Initialize();
            Decode(octets);
        }

        Extensions(const Extensions& rhs) : its::AsnSequenceOf(rhs)
        {
            // Nothing to do.
        }

        Extensions(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

        static its::AsnDescObject* GetExtensionFieldStaticDescription();

    public:

        virtual ~Extensions()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Extensions(*this);
        }

        virtual std::string GetName() const
        { return "Extensions"; }

        void AddElement(ExtensionField* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetExtensionFieldStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        void AddElement(const ExtensionField& element)
        {
            its::AsnObject& asnObject = const_cast<ExtensionField&>(element);
            asnObject.SetDescription(GetExtensionFieldStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        const ExtensionField& ElementAt(int index) const
        {
            return static_cast<const ExtensionField&> (AsnSequenceOf::ElementAt(index));
        }

    };


        typedef cap_v3::ISDN_AddressString ISDN_AddressString;


        typedef cap_v3::CalledPartyBCDNumber CalledPartyBCDNumber;


////////// End Nested Class(es) //////////

    ConnectSMSArg() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    ConnectSMSArg(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    ConnectSMSArg(const ConnectSMSArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ConnectSMSArg(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetCallingPartysNumberStaticDescription();
    static its::AsnDescObject* GetDestinationSubscriberNumberStaticDescription();
    static its::AsnDescObject* GetSMSCAddressStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();

public:

    virtual ~ConnectSMSArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ConnectSMSArg(*this);
    }

    virtual std::string GetName() const
    { return "ConnectSMSArg"; }

    void SetCallingPartysNumber(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingPartysNumberStaticDescription());
        AddElement(0, element);
    }

    void SetCallingPartysNumber(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetCallingPartysNumberStaticDescription());
        AddElement(0, element);
    }

    bool OptionCallingPartysNumber() const
    {
        return Contains(0);
    }

    const ISDN_AddressString& GetCallingPartysNumber() const
    {
        ITS_REQUIRE(OptionCallingPartysNumber());
        return static_cast<const ISDN_AddressString&> (ElementAt(0));
    }

    void SetDestinationSubscriberNumber(CalledPartyBCDNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDestinationSubscriberNumberStaticDescription());
        AddElement(1, element);
    }

    void SetDestinationSubscriberNumber(const CalledPartyBCDNumber& element)
    {
        its::AsnObject& asnObject = const_cast<CalledPartyBCDNumber&>(element);
        asnObject.SetDescription(GetDestinationSubscriberNumberStaticDescription());
        AddElement(1, element);
    }

    bool OptionDestinationSubscriberNumber() const
    {
        return Contains(1);
    }

    const CalledPartyBCDNumber& GetDestinationSubscriberNumber() const
    {
        ITS_REQUIRE(OptionDestinationSubscriberNumber());
        return static_cast<const CalledPartyBCDNumber&> (ElementAt(1));
    }

    void SetSMSCAddress(ISDN_AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSMSCAddressStaticDescription());
        AddElement(2, element);
    }

    void SetSMSCAddress(const ISDN_AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<ISDN_AddressString&>(element);
        asnObject.SetDescription(GetSMSCAddressStaticDescription());
        AddElement(2, element);
    }

    bool OptionSMSCAddress() const
    {
        return Contains(2);
    }

    const ISDN_AddressString& GetSMSCAddress() const
    {
        ITS_REQUIRE(OptionSMSCAddress());
        return static_cast<const ISDN_AddressString&> (ElementAt(2));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(3, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(3, element);
    }

    bool OptionExtensions() const
    {
        return Contains(3);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_CONNECT_SMS_ARG_H_)

