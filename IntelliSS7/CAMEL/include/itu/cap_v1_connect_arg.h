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


#if !defined(_CAP_V1_CONNECT_ARG_H_)
#define _CAP_V1_CONNECT_ARG_H_

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
#include <AsnSetOf.h>
#include <AsnNull.h>

#include <cap_v1_destination_routing_address.h>
#include <cap_v1_original_called_party_id.h>
#include <cap_v1_extension_field.h>
#include <cap_v1_generic_numbers.h>
#include <cap_v1_calling_party_number.h>
#include <cap_v1_calling_partys_category.h>
#include <cap_v1_redirecting_party_id.h>
#include <cap_v1_redirection_information.h>
#include <cap_v1_suppression_of_announcement.h>
#include <cap_v1_ocsi_applicable.h>



namespace cap_v1 {



class ConnectArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Extensions : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef cap_v1::ExtensionField ExtensionField;


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


        typedef cap_v1::DestinationRoutingAddress DestinationRoutingAddress;


        typedef cap_v1::OriginalCalledPartyID OriginalCalledPartyID;


        typedef cap_v1::GenericNumbers GenericNumbers;


        typedef cap_v1::CallingPartyNumber CallingPartyNumber;


        typedef cap_v1::CallingPartysCategory CallingPartysCategory;


        typedef cap_v1::RedirectingPartyID RedirectingPartyID;


        typedef cap_v1::RedirectionInformation RedirectionInformation;


        typedef cap_v1::SuppressionOfAnnouncement SuppressionOfAnnouncement;


        typedef cap_v1::OCSIApplicable OCSIApplicable;


////////// End Nested Class(es) //////////

    ConnectArg() : its::AsnSequence(10, false)
    {
        Initialize();
    }

    ConnectArg(its::Octets& octets) : its::AsnSequence(10, false)
    {
        Initialize();
        Decode(octets);
    }

    ConnectArg(const ConnectArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ConnectArg(its::AsnDescObject* description) : its::AsnSequence(10, description)
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

    static its::AsnDescObject* GetDestinationRoutingAddressStaticDescription();
    static its::AsnDescObject* GetOriginalCalledPartyIDStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();
    static its::AsnDescObject* GetGenericNumbersStaticDescription();
    static its::AsnDescObject* GetCallingPartyNumberStaticDescription();
    static its::AsnDescObject* GetCallingPartysCategoryStaticDescription();
    static its::AsnDescObject* GetRedirectingPartyIDStaticDescription();
    static its::AsnDescObject* GetRedirectionInformationStaticDescription();
    static its::AsnDescObject* GetSuppressionOfAnnouncementStaticDescription();
    static its::AsnDescObject* GetOCSIApplicableStaticDescription();

public:

    virtual ~ConnectArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ConnectArg(*this);
    }

    virtual std::string GetName() const
    { return "ConnectArg"; }

    void SetDestinationRoutingAddress(DestinationRoutingAddress* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDestinationRoutingAddressStaticDescription());
        AddElement(0, element);
    }

    void SetDestinationRoutingAddress(const DestinationRoutingAddress& element)
    {
        its::AsnObject& asnObject = const_cast<DestinationRoutingAddress&>(element);
        asnObject.SetDescription(GetDestinationRoutingAddressStaticDescription());
        AddElement(0, element);
    }

    const DestinationRoutingAddress& GetDestinationRoutingAddress() const
    {
        return static_cast<const DestinationRoutingAddress&> (ElementAt(0));
    }

    void SetOriginalCalledPartyID(OriginalCalledPartyID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOriginalCalledPartyIDStaticDescription());
        AddElement(1, element);
    }

    void SetOriginalCalledPartyID(const OriginalCalledPartyID& element)
    {
        its::AsnObject& asnObject = const_cast<OriginalCalledPartyID&>(element);
        asnObject.SetDescription(GetOriginalCalledPartyIDStaticDescription());
        AddElement(1, element);
    }

    bool OptionOriginalCalledPartyID() const
    {
        return Contains(1);
    }

    const OriginalCalledPartyID& GetOriginalCalledPartyID() const
    {
        ITS_REQUIRE(OptionOriginalCalledPartyID());
        return static_cast<const OriginalCalledPartyID&> (ElementAt(1));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(2, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(2, element);
    }

    bool OptionExtensions() const
    {
        return Contains(2);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(2));
    }

    void SetGenericNumbers(GenericNumbers* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGenericNumbersStaticDescription());
        AddElement(3, element);
    }

    void SetGenericNumbers(const GenericNumbers& element)
    {
        its::AsnObject& asnObject = const_cast<GenericNumbers&>(element);
        asnObject.SetDescription(GetGenericNumbersStaticDescription());
        AddElement(3, element);
    }

    bool OptionGenericNumbers() const
    {
        return Contains(3);
    }

    const GenericNumbers& GetGenericNumbers() const
    {
        ITS_REQUIRE(OptionGenericNumbers());
        return static_cast<const GenericNumbers&> (ElementAt(3));
    }

    void SetCallingPartyNumber(CallingPartyNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingPartyNumberStaticDescription());
        AddElement(4, element);
    }

    void SetCallingPartyNumber(const CallingPartyNumber& element)
    {
        its::AsnObject& asnObject = const_cast<CallingPartyNumber&>(element);
        asnObject.SetDescription(GetCallingPartyNumberStaticDescription());
        AddElement(4, element);
    }

    bool OptionCallingPartyNumber() const
    {
        return Contains(4);
    }

    const CallingPartyNumber& GetCallingPartyNumber() const
    {
        ITS_REQUIRE(OptionCallingPartyNumber());
        return static_cast<const CallingPartyNumber&> (ElementAt(4));
    }

    void SetCallingPartysCategory(CallingPartysCategory* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallingPartysCategoryStaticDescription());
        AddElement(5, element);
    }

    void SetCallingPartysCategory(const CallingPartysCategory& element)
    {
        its::AsnObject& asnObject = const_cast<CallingPartysCategory&>(element);
        asnObject.SetDescription(GetCallingPartysCategoryStaticDescription());
        AddElement(5, element);
    }

    bool OptionCallingPartysCategory() const
    {
        return Contains(5);
    }

    const CallingPartysCategory& GetCallingPartysCategory() const
    {
        ITS_REQUIRE(OptionCallingPartysCategory());
        return static_cast<const CallingPartysCategory&> (ElementAt(5));
    }

    void SetRedirectingPartyID(RedirectingPartyID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRedirectingPartyIDStaticDescription());
        AddElement(6, element);
    }

    void SetRedirectingPartyID(const RedirectingPartyID& element)
    {
        its::AsnObject& asnObject = const_cast<RedirectingPartyID&>(element);
        asnObject.SetDescription(GetRedirectingPartyIDStaticDescription());
        AddElement(6, element);
    }

    bool OptionRedirectingPartyID() const
    {
        return Contains(6);
    }

    const RedirectingPartyID& GetRedirectingPartyID() const
    {
        ITS_REQUIRE(OptionRedirectingPartyID());
        return static_cast<const RedirectingPartyID&> (ElementAt(6));
    }

    void SetRedirectionInformation(RedirectionInformation* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRedirectionInformationStaticDescription());
        AddElement(7, element);
    }

    void SetRedirectionInformation(const RedirectionInformation& element)
    {
        its::AsnObject& asnObject = const_cast<RedirectionInformation&>(element);
        asnObject.SetDescription(GetRedirectionInformationStaticDescription());
        AddElement(7, element);
    }

    bool OptionRedirectionInformation() const
    {
        return Contains(7);
    }

    const RedirectionInformation& GetRedirectionInformation() const
    {
        ITS_REQUIRE(OptionRedirectionInformation());
        return static_cast<const RedirectionInformation&> (ElementAt(7));
    }

    void SetSuppressionOfAnnouncement(SuppressionOfAnnouncement* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSuppressionOfAnnouncementStaticDescription());
        AddElement(8, element);
    }

    void SetSuppressionOfAnnouncement(const SuppressionOfAnnouncement& element)
    {
        its::AsnObject& asnObject = const_cast<SuppressionOfAnnouncement&>(element);
        asnObject.SetDescription(GetSuppressionOfAnnouncementStaticDescription());
        AddElement(8, element);
    }

    bool OptionSuppressionOfAnnouncement() const
    {
        return Contains(8);
    }

    const SuppressionOfAnnouncement& GetSuppressionOfAnnouncement() const
    {
        ITS_REQUIRE(OptionSuppressionOfAnnouncement());
        return static_cast<const SuppressionOfAnnouncement&> (ElementAt(8));
    }

    void SetOCSIApplicable(OCSIApplicable* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOCSIApplicableStaticDescription());
        AddElement(9, element);
    }

    void SetOCSIApplicable(const OCSIApplicable& element)
    {
        its::AsnObject& asnObject = const_cast<OCSIApplicable&>(element);
        asnObject.SetDescription(GetOCSIApplicableStaticDescription());
        AddElement(9, element);
    }

    bool OptionOCSIApplicable() const
    {
        return Contains(9);
    }

    const OCSIApplicable& GetOCSIApplicable() const
    {
        ITS_REQUIRE(OptionOCSIApplicable());
        return static_cast<const OCSIApplicable&> (ElementAt(9));
    }

};



} // namespace.

#endif    // !defined(_CAP_V1_CONNECT_ARG_H_)
