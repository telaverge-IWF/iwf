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


#if !defined(_CAP_V3_INBAND_INFO_H_)
#define _CAP_V3_INBAND_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnInteger.h>
#include <AsnChoice.h>

#include <cap_v3_message_id.h>



namespace cap_v3 {



class InbandInfo : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class NumberOfRepetitions : public its::AsnInteger
    {
    public:

        NumberOfRepetitions() : its::AsnInteger(false)
        {
            Initialize();
        }

        NumberOfRepetitions(long value) : its::AsnInteger(value, false)
        {
            Initialize();
        }

        NumberOfRepetitions(its::Octets& octets) : its::AsnInteger(false)
        {
            Initialize();
            Decode(octets);
        }

        NumberOfRepetitions(const NumberOfRepetitions& rhs) : its::AsnInteger(rhs)
        {
            // Nothing to do.
        }

        NumberOfRepetitions(its::AsnDescObject* description) : its::AsnInteger(description)
        {
            // Nothing to do.
        }

        NumberOfRepetitions(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

        virtual ~NumberOfRepetitions()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new NumberOfRepetitions(*this);
        }

        virtual std::string GetName() const
        { return "NumberOfRepetitions"; }

    };



    class Duration : public its::AsnInteger
    {
    public:

        Duration() : its::AsnInteger(false)
        {
            Initialize();
        }

        Duration(long value) : its::AsnInteger(value, false)
        {
            Initialize();
        }

        Duration(its::Octets& octets) : its::AsnInteger(false)
        {
            Initialize();
            Decode(octets);
        }

        Duration(const Duration& rhs) : its::AsnInteger(rhs)
        {
            // Nothing to do.
        }

        Duration(its::AsnDescObject* description) : its::AsnInteger(description)
        {
            // Nothing to do.
        }

        Duration(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

        virtual ~Duration()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Duration(*this);
        }

        virtual std::string GetName() const
        { return "Duration"; }

    };



    class Interval : public its::AsnInteger
    {
    public:

        Interval() : its::AsnInteger(false)
        {
            Initialize();
        }

        Interval(long value) : its::AsnInteger(value, false)
        {
            Initialize();
        }

        Interval(its::Octets& octets) : its::AsnInteger(false)
        {
            Initialize();
            Decode(octets);
        }

        Interval(const Interval& rhs) : its::AsnInteger(rhs)
        {
            // Nothing to do.
        }

        Interval(its::AsnDescObject* description) : its::AsnInteger(description)
        {
            // Nothing to do.
        }

        Interval(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

        virtual ~Interval()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Interval(*this);
        }

        virtual std::string GetName() const
        { return "Interval"; }

    };


        typedef cap_v3::MessageID MessageID;


////////// End Nested Class(es) //////////

    InbandInfo() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    InbandInfo(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    InbandInfo(const InbandInfo& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    InbandInfo(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetMessageIDStaticDescription();
    static its::AsnDescObject* GetNumberOfRepetitionsStaticDescription();
    static its::AsnDescObject* GetDurationStaticDescription();
    static its::AsnDescObject* GetIntervalStaticDescription();

public:

    virtual ~InbandInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new InbandInfo(*this);
    }

    virtual std::string GetName() const
    { return "InbandInfo"; }

    void SetMessageID(MessageID* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMessageIDStaticDescription());
        AddElement(0, element);
    }

    void SetMessageID(const MessageID& element)
    {
        its::AsnObject& asnObject = const_cast<MessageID&>(element);
        asnObject.SetDescription(GetMessageIDStaticDescription());
        AddElement(0, element);
    }

    const MessageID& GetMessageID() const
    {
        return static_cast<const MessageID&> (ElementAt(0));
    }

    void SetNumberOfRepetitions(NumberOfRepetitions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNumberOfRepetitionsStaticDescription());
        AddElement(1, element);
    }

    void SetNumberOfRepetitions(const NumberOfRepetitions& element)
    {
        its::AsnObject& asnObject = const_cast<NumberOfRepetitions&>(element);
        asnObject.SetDescription(GetNumberOfRepetitionsStaticDescription());
        AddElement(1, element);
    }

    bool OptionNumberOfRepetitions() const
    {
        return Contains(1);
    }

    const NumberOfRepetitions& GetNumberOfRepetitions() const
    {
        ITS_REQUIRE(OptionNumberOfRepetitions());
        return static_cast<const NumberOfRepetitions&> (ElementAt(1));
    }

    void SetDuration(Duration* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDurationStaticDescription());
        AddElement(2, element);
    }

    void SetDuration(const Duration& element)
    {
        its::AsnObject& asnObject = const_cast<Duration&>(element);
        asnObject.SetDescription(GetDurationStaticDescription());
        AddElement(2, element);
    }

    bool OptionDuration() const
    {
        return Contains(2);
    }

    const Duration& GetDuration() const
    {
        ITS_REQUIRE(OptionDuration());
        return static_cast<const Duration&> (ElementAt(2));
    }

    void SetInterval(Interval* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIntervalStaticDescription());
        AddElement(3, element);
    }

    void SetInterval(const Interval& element)
    {
        its::AsnObject& asnObject = const_cast<Interval&>(element);
        asnObject.SetDescription(GetIntervalStaticDescription());
        AddElement(3, element);
    }

    bool OptionInterval() const
    {
        return Contains(3);
    }

    const Interval& GetInterval() const
    {
        ITS_REQUIRE(OptionInterval());
        return static_cast<const Interval&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_INBAND_INFO_H_)

