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


#if !defined(_CAP_V2_PLAY_ANNOUNCEMENT_ARG_H_)
#define _CAP_V2_PLAY_ANNOUNCEMENT_ARG_H_

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

#include <cap_v2_information_to_send.h>
#include <cap_v2_extension_field.h>



namespace cap_v2 {



class PlayAnnouncementArg : public its::AsnSequence
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



    class RequestAnnouncementComplete : public its::AsnBoolean
    {
    public:

        RequestAnnouncementComplete(bool value) : its::AsnBoolean(value, false)
        {
            Initialize();
        }

        RequestAnnouncementComplete(its::Octets& octets) : its::AsnBoolean(false, false)
        {
            Initialize();
            Decode(octets);
        }

        RequestAnnouncementComplete(const RequestAnnouncementComplete& rhs) : its::AsnBoolean(rhs)
        {
            // Nothing to do.
        }

        RequestAnnouncementComplete(its::AsnDescObject* description) : its::AsnBoolean(description)
        {
            // Nothing to do.
        }

        RequestAnnouncementComplete(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

        virtual ~RequestAnnouncementComplete()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new RequestAnnouncementComplete(*this);
        }

        virtual std::string GetName() const
        { return "RequestAnnouncementComplete"; }

    };



    class Extensions : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef cap_v2::ExtensionField ExtensionField;


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


        typedef cap_v2::InformationToSend InformationToSend;


////////// End Nested Class(es) //////////

    PlayAnnouncementArg() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    PlayAnnouncementArg(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    PlayAnnouncementArg(const PlayAnnouncementArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    PlayAnnouncementArg(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetInformationToSendStaticDescription();
    static its::AsnDescObject* GetDisconnectFromIPForbiddenStaticDescription();
    static its::AsnDescObject* GetRequestAnnouncementCompleteStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();

public:

    virtual ~PlayAnnouncementArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PlayAnnouncementArg(*this);
    }

    virtual std::string GetName() const
    { return "PlayAnnouncementArg"; }

    void SetInformationToSend(InformationToSend* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetInformationToSendStaticDescription());
        AddElement(0, element);
    }

    void SetInformationToSend(const InformationToSend& element)
    {
        its::AsnObject& asnObject = const_cast<InformationToSend&>(element);
        asnObject.SetDescription(GetInformationToSendStaticDescription());
        AddElement(0, element);
    }

    const InformationToSend& GetInformationToSend() const
    {
        return static_cast<const InformationToSend&> (ElementAt(0));
    }

    void SetDisconnectFromIPForbidden(DisconnectFromIPForbidden* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDisconnectFromIPForbiddenStaticDescription());
        AddElement(1, element);
    }

    void SetDisconnectFromIPForbidden(const DisconnectFromIPForbidden& element)
    {
        its::AsnObject& asnObject = const_cast<DisconnectFromIPForbidden&>(element);
        asnObject.SetDescription(GetDisconnectFromIPForbiddenStaticDescription());
        AddElement(1, element);
    }

    const DisconnectFromIPForbidden& GetDisconnectFromIPForbidden() const
    {
        return static_cast<const DisconnectFromIPForbidden&> (ElementAt(1));
    }

    void SetRequestAnnouncementComplete(RequestAnnouncementComplete* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetRequestAnnouncementCompleteStaticDescription());
        AddElement(2, element);
    }

    void SetRequestAnnouncementComplete(const RequestAnnouncementComplete& element)
    {
        its::AsnObject& asnObject = const_cast<RequestAnnouncementComplete&>(element);
        asnObject.SetDescription(GetRequestAnnouncementCompleteStaticDescription());
        AddElement(2, element);
    }

    const RequestAnnouncementComplete& GetRequestAnnouncementComplete() const
    {
        return static_cast<const RequestAnnouncementComplete&> (ElementAt(2));
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

#endif    // !defined(_CAP_V2_PLAY_ANNOUNCEMENT_ARG_H_)

