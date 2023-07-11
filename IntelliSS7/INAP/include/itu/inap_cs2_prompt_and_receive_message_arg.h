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


#if !defined(_INAP_CS2_PROMPT_AND_RECEIVE_MESSAGE_ARG_H_)
#define _INAP_CS2_PROMPT_AND_RECEIVE_MESSAGE_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnBoolean.h>
#include <AsnSequenceOf.h>
#include <AsnChoice.h>
#include <AsnOctetString.h>
#include <AsnEnumerated.h>
#include <AsnInteger.h>

#include <inap_cs2_information_to_send.h>
#include <inap_cs2_extension_field.h>
#include <inap_cs2_generic_number.h>
#include <inap_cs2_mail_box_id.h>
#include <inap_cs2_information_to_record.h>
#include <inap_cs2_media.h>
#include <inap_cs2_call_segment_id.h>



namespace inap_cs2 {



class PromptAndReceiveMessageArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class DisconnectFromIPForbidden : public its::AsnBoolean
    {
    public:

        DisconnectFromIPForbidden(bool value) : its::AsnBoolean(value, false)
        {
            Initialize();
        }

        DisconnectFromIPForbidden(its::Octets& octets) : its::AsnBoolean(false, false)
        {
            Initialize();
            Decode(octets);
        }

        DisconnectFromIPForbidden(const DisconnectFromIPForbidden& rhs) : its::AsnBoolean(rhs)
        {
            // Nothing to do.
        }

        DisconnectFromIPForbidden(its::AsnDescObject* description) : its::AsnBoolean(description)
        {
            // Nothing to do.
        }

        DisconnectFromIPForbidden(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

        virtual ~DisconnectFromIPForbidden()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new DisconnectFromIPForbidden(*this);
        }

        virtual std::string GetName() const
        { return "DisconnectFromIPForbidden"; }

    };



    class Extensions : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef inap_cs2::ExtensionField ExtensionField;


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


        typedef inap_cs2::InformationToSend InformationToSend;


        typedef inap_cs2::GenericNumber GenericNumber;


        typedef inap_cs2::MailBoxID MailBoxID;


        typedef inap_cs2::InformationToRecord InformationToRecord;


        typedef inap_cs2::Media Media;


        typedef inap_cs2::CallSegmentID CallSegmentID;


////////// End Nested Class(es) //////////

    PromptAndReceiveMessageArg() : its::AsnSequence(8, false)
    {
        Initialize();
    }

    PromptAndReceiveMessageArg(its::Octets& octets) : its::AsnSequence(8, false)
    {
        Initialize();
        Decode(octets);
    }

    PromptAndReceiveMessageArg(const PromptAndReceiveMessageArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    PromptAndReceiveMessageArg(its::AsnDescObject* description) : its::AsnSequence(8, description)
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

    static its::AsnDescObject* GetDisconnectFromIPForbiddenStaticDescription();
    static its::AsnDescObject* GetInformationToSendStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();
    static its::AsnDescObject* GetSubscriberIDStaticDescription();
    static its::AsnDescObject* GetMailBoxIDStaticDescription();
    static its::AsnDescObject* GetInformationToRecordStaticDescription();
    static its::AsnDescObject* GetMediaStaticDescription();
    static its::AsnDescObject* GetCallSegmentIDStaticDescription();

public:

    virtual ~PromptAndReceiveMessageArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PromptAndReceiveMessageArg(*this);
    }

    virtual std::string GetName() const
    { return "PromptAndReceiveMessageArg"; }

    void SetDisconnectFromIPForbidden(DisconnectFromIPForbidden* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDisconnectFromIPForbiddenStaticDescription());
        AddElement(0, element);
    }

    void SetDisconnectFromIPForbidden(const DisconnectFromIPForbidden& element)
    {
        its::AsnObject& asnObject = const_cast<DisconnectFromIPForbidden&>(element);
        asnObject.SetDescription(GetDisconnectFromIPForbiddenStaticDescription());
        AddElement(0, element);
    }

    const DisconnectFromIPForbidden& GetDisconnectFromIPForbidden() const
    {
        return static_cast<const DisconnectFromIPForbidden&> (ElementAt(0));
    }

    void SetInformationToSend(InformationToSend* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetInformationToSendStaticDescription());
        AddElement(1, element);
    }

    void SetInformationToSend(const InformationToSend& element)
    {
        its::AsnObject& asnObject = const_cast<InformationToSend&>(element);
        asnObject.SetDescription(GetInformationToSendStaticDescription());
        AddElement(1, element);
    }

    bool OptionInformationToSend() const
    {
        return Contains(1);
    }

    const InformationToSend& GetInformationToSend() const
    {
        ITS_REQUIRE(OptionInformationToSend());
        return static_cast<const InformationToSend&> (ElementAt(1));
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

    void SetSubscriberID(GenericNumber* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSubscriberIDStaticDescription());
        AddElement(3, element);
    }

    void SetSubscriberID(const GenericNumber& element)
    {
        its::AsnObject& asnObject = const_cast<GenericNumber&>(element);
        asnObject.SetDescription(GetSubscriberIDStaticDescription());
        AddElement(3, element);
    }

    bool OptionSubscriberID() const
    {
        return Contains(3);
    }

    const GenericNumber& GetSubscriberID() const
    {
        ITS_REQUIRE(OptionSubscriberID());
        return static_cast<const GenericNumber&> (ElementAt(3));
    }

    void SetMailBoxID(MailBoxID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMailBoxIDStaticDescription());
        AddElement(4, element);
    }

    void SetMailBoxID(const MailBoxID& element)
    {
        its::AsnObject& asnObject = const_cast<MailBoxID&>(element);
        asnObject.SetDescription(GetMailBoxIDStaticDescription());
        AddElement(4, element);
    }

    bool OptionMailBoxID() const
    {
        return Contains(4);
    }

    const MailBoxID& GetMailBoxID() const
    {
        ITS_REQUIRE(OptionMailBoxID());
        return static_cast<const MailBoxID&> (ElementAt(4));
    }

    void SetInformationToRecord(InformationToRecord* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetInformationToRecordStaticDescription());
        AddElement(5, element);
    }

    void SetInformationToRecord(const InformationToRecord& element)
    {
        its::AsnObject& asnObject = const_cast<InformationToRecord&>(element);
        asnObject.SetDescription(GetInformationToRecordStaticDescription());
        AddElement(5, element);
    }

    const InformationToRecord& GetInformationToRecord() const
    {
        return static_cast<const InformationToRecord&> (ElementAt(5));
    }

    void SetMedia(Media* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMediaStaticDescription());
        AddElement(6, element);
    }

    void SetMedia(const Media& element)
    {
        its::AsnObject& asnObject = const_cast<Media&>(element);
        asnObject.SetDescription(GetMediaStaticDescription());
        AddElement(6, element);
    }

    const Media& GetMedia() const
    {
        return static_cast<const Media&> (ElementAt(6));
    }

    void SetCallSegmentID(CallSegmentID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallSegmentIDStaticDescription());
        AddElement(7, element);
    }

    void SetCallSegmentID(const CallSegmentID& element)
    {
        its::AsnObject& asnObject = const_cast<CallSegmentID&>(element);
        asnObject.SetDescription(GetCallSegmentIDStaticDescription());
        AddElement(7, element);
    }

    bool OptionCallSegmentID() const
    {
        return Contains(7);
    }

    const CallSegmentID& GetCallSegmentID() const
    {
        ITS_REQUIRE(OptionCallSegmentID());
        return static_cast<const CallSegmentID&> (ElementAt(7));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_PROMPT_AND_RECEIVE_MESSAGE_ARG_H_)
