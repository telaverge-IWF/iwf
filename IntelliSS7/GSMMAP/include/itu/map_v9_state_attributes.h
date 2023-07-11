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


#if !defined(_MAP_V9_STATE_ATTRIBUTES_H_)
#define _MAP_V9_STATE_ATTRIBUTES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>



namespace map_v9 {



class StateAttributes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class DownlinkAttached : public its::AsnNull
    {
    public:

        DownlinkAttached() : its::AsnNull(false)
        {
            Initialize();
        }

        DownlinkAttached(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        DownlinkAttached(const DownlinkAttached& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        DownlinkAttached(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~DownlinkAttached()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new DownlinkAttached(*this);
        }

        virtual std::string GetName() const
        { return "DownlinkAttached"; }

    };



    class UplinkAttached : public its::AsnNull
    {
    public:

        UplinkAttached() : its::AsnNull(false)
        {
            Initialize();
        }

        UplinkAttached(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        UplinkAttached(const UplinkAttached& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        UplinkAttached(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~UplinkAttached()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new UplinkAttached(*this);
        }

        virtual std::string GetName() const
        { return "UplinkAttached"; }

    };



    class DualCommunication : public its::AsnNull
    {
    public:

        DualCommunication() : its::AsnNull(false)
        {
            Initialize();
        }

        DualCommunication(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        DualCommunication(const DualCommunication& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        DualCommunication(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~DualCommunication()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new DualCommunication(*this);
        }

        virtual std::string GetName() const
        { return "DualCommunication"; }

    };



    class CallOriginator : public its::AsnNull
    {
    public:

        CallOriginator() : its::AsnNull(false)
        {
            Initialize();
        }

        CallOriginator(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        CallOriginator(const CallOriginator& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        CallOriginator(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~CallOriginator()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new CallOriginator(*this);
        }

        virtual std::string GetName() const
        { return "CallOriginator"; }

    };


////////// End Nested Class(es) //////////

    StateAttributes() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    StateAttributes(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    StateAttributes(const StateAttributes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    StateAttributes(its::AsnDescObject* description) : its::AsnSequence(4, description)
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

    static its::AsnDescObject* GetDownlinkAttachedStaticDescription();
    static its::AsnDescObject* GetUplinkAttachedStaticDescription();
    static its::AsnDescObject* GetDualCommunicationStaticDescription();
    static its::AsnDescObject* GetCallOriginatorStaticDescription();

public:

    virtual ~StateAttributes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new StateAttributes(*this);
    }

    virtual std::string GetName() const
    { return "StateAttributes"; }

    void SetDownlinkAttached(DownlinkAttached* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDownlinkAttachedStaticDescription());
        AddElement(0, element);
    }

    void SetDownlinkAttached(const DownlinkAttached& element)
    {
        its::AsnObject& asnObject = const_cast<DownlinkAttached&>(element);
        asnObject.SetDescription(GetDownlinkAttachedStaticDescription());
        AddElement(0, element);
    }

    bool OptionDownlinkAttached() const
    {
        return Contains(0);
    }

    const DownlinkAttached& GetDownlinkAttached() const
    {
        ITS_REQUIRE(OptionDownlinkAttached());
        return static_cast<const DownlinkAttached&> (ElementAt(0));
    }

    void SetUplinkAttached(UplinkAttached* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetUplinkAttachedStaticDescription());
        AddElement(1, element);
    }

    void SetUplinkAttached(const UplinkAttached& element)
    {
        its::AsnObject& asnObject = const_cast<UplinkAttached&>(element);
        asnObject.SetDescription(GetUplinkAttachedStaticDescription());
        AddElement(1, element);
    }

    bool OptionUplinkAttached() const
    {
        return Contains(1);
    }

    const UplinkAttached& GetUplinkAttached() const
    {
        ITS_REQUIRE(OptionUplinkAttached());
        return static_cast<const UplinkAttached&> (ElementAt(1));
    }

    void SetDualCommunication(DualCommunication* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDualCommunicationStaticDescription());
        AddElement(2, element);
    }

    void SetDualCommunication(const DualCommunication& element)
    {
        its::AsnObject& asnObject = const_cast<DualCommunication&>(element);
        asnObject.SetDescription(GetDualCommunicationStaticDescription());
        AddElement(2, element);
    }

    bool OptionDualCommunication() const
    {
        return Contains(2);
    }

    const DualCommunication& GetDualCommunication() const
    {
        ITS_REQUIRE(OptionDualCommunication());
        return static_cast<const DualCommunication&> (ElementAt(2));
    }

    void SetCallOriginator(CallOriginator* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCallOriginatorStaticDescription());
        AddElement(3, element);
    }

    void SetCallOriginator(const CallOriginator& element)
    {
        its::AsnObject& asnObject = const_cast<CallOriginator&>(element);
        asnObject.SetDescription(GetCallOriginatorStaticDescription());
        AddElement(3, element);
    }

    bool OptionCallOriginator() const
    {
        return Contains(3);
    }

    const CallOriginator& GetCallOriginator() const
    {
        ITS_REQUIRE(OptionCallOriginator());
        return static_cast<const CallOriginator&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_STATE_ATTRIBUTES_H_)

