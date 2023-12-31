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


#if !defined(_INAP_CS2_CONTROL_CONDITION_BY_CALL_PARTY_H_)
#define _INAP_CS2_CONTROL_CONDITION_BY_CALL_PARTY_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>



namespace inap_cs2 {



class ControlConditionByCallParty : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class EndOfMessageSendingDigit : public its::AsnOctetString
    {
    public:

        EndOfMessageSendingDigit() : its::AsnOctetString(false)
        {
            Initialize();
        }

        EndOfMessageSendingDigit(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        EndOfMessageSendingDigit(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        EndOfMessageSendingDigit(const EndOfMessageSendingDigit& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        EndOfMessageSendingDigit(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        EndOfMessageSendingDigit(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~EndOfMessageSendingDigit()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new EndOfMessageSendingDigit(*this);
        }

        virtual std::string GetName() const
        { return "EndOfMessageSendingDigit"; }

    };



    class ReplayDigit : public its::AsnOctetString
    {
    public:

        ReplayDigit() : its::AsnOctetString(false)
        {
            Initialize();
        }

        ReplayDigit(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        ReplayDigit(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        ReplayDigit(const ReplayDigit& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        ReplayDigit(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        ReplayDigit(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~ReplayDigit()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new ReplayDigit(*this);
        }

        virtual std::string GetName() const
        { return "ReplayDigit"; }

    };


////////// End Nested Class(es) //////////

    ControlConditionByCallParty() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    ControlConditionByCallParty(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    ControlConditionByCallParty(const ControlConditionByCallParty& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ControlConditionByCallParty(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetEndOfMessageSendingDigitStaticDescription();
    static its::AsnDescObject* GetReplayDigitStaticDescription();

public:

    virtual ~ControlConditionByCallParty()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ControlConditionByCallParty(*this);
    }

    virtual std::string GetName() const
    { return "ControlConditionByCallParty"; }

    void SetEndOfMessageSendingDigit(EndOfMessageSendingDigit* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEndOfMessageSendingDigitStaticDescription());
        AddElement(0, element);
    }

    void SetEndOfMessageSendingDigit(const EndOfMessageSendingDigit& element)
    {
        its::AsnObject& asnObject = const_cast<EndOfMessageSendingDigit&>(element);
        asnObject.SetDescription(GetEndOfMessageSendingDigitStaticDescription());
        AddElement(0, element);
    }

    bool OptionEndOfMessageSendingDigit() const
    {
        return Contains(0);
    }

    const EndOfMessageSendingDigit& GetEndOfMessageSendingDigit() const
    {
        ITS_REQUIRE(OptionEndOfMessageSendingDigit());
        return static_cast<const EndOfMessageSendingDigit&> (ElementAt(0));
    }

    void SetReplayDigit(ReplayDigit* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetReplayDigitStaticDescription());
        AddElement(1, element);
    }

    void SetReplayDigit(const ReplayDigit& element)
    {
        its::AsnObject& asnObject = const_cast<ReplayDigit&>(element);
        asnObject.SetDescription(GetReplayDigitStaticDescription());
        AddElement(1, element);
    }

    bool OptionReplayDigit() const
    {
        return Contains(1);
    }

    const ReplayDigit& GetReplayDigit() const
    {
        ITS_REQUIRE(OptionReplayDigit());
        return static_cast<const ReplayDigit&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_CONTROL_CONDITION_BY_CALL_PARTY_H_)

