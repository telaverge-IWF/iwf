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


#if !defined(_CAP_V3_CONNECT_ARG_EXTENSION_H_)
#define _CAP_V3_CONNECT_ARG_EXTENSION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnNull.h>
#include <AsnOctetString.h>

#include <cap_v3_cug_interlock.h>



namespace cap_v3 {



class ConnectArgExtension : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Cug_OutgoingAccess : public its::AsnNull
    {
    public:

        Cug_OutgoingAccess() : its::AsnNull(false)
        {
            Initialize();
        }

        Cug_OutgoingAccess(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        Cug_OutgoingAccess(const Cug_OutgoingAccess& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        Cug_OutgoingAccess(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~Cug_OutgoingAccess()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Cug_OutgoingAccess(*this);
        }

        virtual std::string GetName() const
        { return "Cug_OutgoingAccess"; }

    };



    class NonCug_Call : public its::AsnNull
    {
    public:

        NonCug_Call() : its::AsnNull(false)
        {
            Initialize();
        }

        NonCug_Call(its::Octets& octets) : its::AsnNull(false)
        {
            Initialize();
            Decode(octets);
        }

        NonCug_Call(const NonCug_Call& rhs) : its::AsnNull(rhs)
        {
            // Nothing to do.
        }

        NonCug_Call(its::AsnDescObject* description) : its::AsnNull(description)
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

        virtual ~NonCug_Call()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new NonCug_Call(*this);
        }

        virtual std::string GetName() const
        { return "NonCug_Call"; }

    };


        typedef cap_v3::CUG_Interlock CUG_Interlock;


////////// End Nested Class(es) //////////

    ConnectArgExtension() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    ConnectArgExtension(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    ConnectArgExtension(const ConnectArgExtension& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ConnectArgExtension(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetCug_InterlockStaticDescription();
    static its::AsnDescObject* GetCug_OutgoingAccessStaticDescription();
    static its::AsnDescObject* GetNonCug_CallStaticDescription();

public:

    virtual ~ConnectArgExtension()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ConnectArgExtension(*this);
    }

    virtual std::string GetName() const
    { return "ConnectArgExtension"; }

    void SetCug_Interlock(CUG_Interlock* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCug_InterlockStaticDescription());
        AddElement(0, element);
    }

    void SetCug_Interlock(const CUG_Interlock& element)
    {
        its::AsnObject& asnObject = const_cast<CUG_Interlock&>(element);
        asnObject.SetDescription(GetCug_InterlockStaticDescription());
        AddElement(0, element);
    }

    bool OptionCug_Interlock() const
    {
        return Contains(0);
    }

    const CUG_Interlock& GetCug_Interlock() const
    {
        ITS_REQUIRE(OptionCug_Interlock());
        return static_cast<const CUG_Interlock&> (ElementAt(0));
    }

    void SetCug_OutgoingAccess(Cug_OutgoingAccess* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetCug_OutgoingAccessStaticDescription());
        AddElement(1, element);
    }

    void SetCug_OutgoingAccess(const Cug_OutgoingAccess& element)
    {
        its::AsnObject& asnObject = const_cast<Cug_OutgoingAccess&>(element);
        asnObject.SetDescription(GetCug_OutgoingAccessStaticDescription());
        AddElement(1, element);
    }

    bool OptionCug_OutgoingAccess() const
    {
        return Contains(1);
    }

    const Cug_OutgoingAccess& GetCug_OutgoingAccess() const
    {
        ITS_REQUIRE(OptionCug_OutgoingAccess());
        return static_cast<const Cug_OutgoingAccess&> (ElementAt(1));
    }

    void SetNonCug_Call(NonCug_Call* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetNonCug_CallStaticDescription());
        AddElement(2, element);
    }

    void SetNonCug_Call(const NonCug_Call& element)
    {
        its::AsnObject& asnObject = const_cast<NonCug_Call&>(element);
        asnObject.SetDescription(GetNonCug_CallStaticDescription());
        AddElement(2, element);
    }

    bool OptionNonCug_Call() const
    {
        return Contains(2);
    }

    const NonCug_Call& GetNonCug_Call() const
    {
        ITS_REQUIRE(OptionNonCug_Call());
        return static_cast<const NonCug_Call&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_CAP_V3_CONNECT_ARG_EXTENSION_H_)

