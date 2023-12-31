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


#if !defined(_INAP_CS2_MISC_CALL_INFO_H_)
#define _INAP_CS2_MISC_CALL_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnEnumerated.h>



namespace inap_cs2 {



class MiscCallInfo : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class MessageType : public its::AsnEnumerated
    {
    public:

        MessageType() : its::AsnEnumerated(false)
        {
            Initialize();
        }

        MessageType(long value) : its::AsnEnumerated(value, false)
        {
            Initialize();
        }

        MessageType(its::Octets& octets) : its::AsnEnumerated(false)
        {
            Initialize();
            Decode(octets);
        }

        MessageType(const MessageType& rhs) : its::AsnEnumerated(rhs)
        {
            // Nothing to do.
        }

        MessageType(its::AsnDescObject* description) : its::AsnEnumerated(description)
        {
            // Nothing to do.
        }

        MessageType(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

        virtual ~MessageType()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new MessageType(*this);
        }

        virtual std::string GetName() const
        { return "MessageType"; }

        virtual long Get(const std::string& valueName) const;

        virtual std::string Get(long value) const;

        virtual std::string GetExt(long value) const;

        enum {
            MESSAGE_TYPE_REQUEST = 0,
            MESSAGE_TYPE_NOTIFICATION = 1

        };

        void SetRequest()
        { _value = 0; }

        bool IsRequest() const
        { return _value == 0; }

        void SetNotification()
        { _value = 1; }

        bool IsNotification() const
        { return _value == 1; }

    };



    class DpAssignment : public its::AsnEnumerated
    {
    public:

        DpAssignment() : its::AsnEnumerated(false)
        {
            Initialize();
        }

        DpAssignment(long value) : its::AsnEnumerated(value, false)
        {
            Initialize();
        }

        DpAssignment(its::Octets& octets) : its::AsnEnumerated(false)
        {
            Initialize();
            Decode(octets);
        }

        DpAssignment(const DpAssignment& rhs) : its::AsnEnumerated(rhs)
        {
            // Nothing to do.
        }

        DpAssignment(its::AsnDescObject* description) : its::AsnEnumerated(description)
        {
            // Nothing to do.
        }

        DpAssignment(its::AsnDescObject* description, long value) : its::AsnEnumerated(description, value)
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

        virtual ~DpAssignment()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new DpAssignment(*this);
        }

        virtual std::string GetName() const
        { return "DpAssignment"; }

        virtual long Get(const std::string& valueName) const;

        virtual std::string Get(long value) const;

        virtual std::string GetExt(long value) const;

        enum {
            DP_ASSIGNMENT_INDIVIDUAL_LINE = 0,
            DP_ASSIGNMENT_GROUP_BASED = 1,
            DP_ASSIGNMENT_OFFICE_BASED = 2

        };

        void SetIndividualLine()
        { _value = 0; }

        bool IsIndividualLine() const
        { return _value == 0; }

        void SetGroupBased()
        { _value = 1; }

        bool IsGroupBased() const
        { return _value == 1; }

        void SetOfficeBased()
        { _value = 2; }

        bool IsOfficeBased() const
        { return _value == 2; }

    };


////////// End Nested Class(es) //////////

    MiscCallInfo() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    MiscCallInfo(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    MiscCallInfo(const MiscCallInfo& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    MiscCallInfo(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetMessageTypeStaticDescription();
    static its::AsnDescObject* GetDpAssignmentStaticDescription();

public:

    virtual ~MiscCallInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MiscCallInfo(*this);
    }

    virtual std::string GetName() const
    { return "MiscCallInfo"; }

    void SetMessageType(MessageType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMessageTypeStaticDescription());
        AddElement(0, element);
    }

    void SetMessageType(const MessageType& element)
    {
        its::AsnObject& asnObject = const_cast<MessageType&>(element);
        asnObject.SetDescription(GetMessageTypeStaticDescription());
        AddElement(0, element);
    }

    const MessageType& GetMessageType() const
    {
        return static_cast<const MessageType&> (ElementAt(0));
    }

    void SetDpAssignment(DpAssignment* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDpAssignmentStaticDescription());
        AddElement(1, element);
    }

    void SetDpAssignment(const DpAssignment& element)
    {
        its::AsnObject& asnObject = const_cast<DpAssignment&>(element);
        asnObject.SetDescription(GetDpAssignmentStaticDescription());
        AddElement(1, element);
    }

    bool OptionDpAssignment() const
    {
        return Contains(1);
    }

    const DpAssignment& GetDpAssignment() const
    {
        ITS_REQUIRE(OptionDpAssignment());
        return static_cast<const DpAssignment&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_MISC_CALL_INFO_H_)

