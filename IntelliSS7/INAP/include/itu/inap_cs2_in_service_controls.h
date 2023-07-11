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


#if !defined(_INAP_CS2_IN_SERVICE_CONTROLS_H_)
#define _INAP_CS2_IN_SERVICE_CONTROLS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSet.h>
#include <AsnInteger.h>
#include <AsnBitString.h>

#include <inap_cs2_service_control_options.h>



namespace inap_cs2 {



class InServiceControls : public its::AsnSet
{
public:


////////// Begin Nested Class(es) //////////



    class Priority : public its::AsnInteger
    {
    public:

        Priority() : its::AsnInteger(false)
        {
            Initialize();
        }

        Priority(long value) : its::AsnInteger(value, false)
        {
            Initialize();
        }

        Priority(its::Octets& octets) : its::AsnInteger(false)
        {
            Initialize();
            Decode(octets);
        }

        Priority(const Priority& rhs) : its::AsnInteger(rhs)
        {
            // Nothing to do.
        }

        Priority(its::AsnDescObject* description) : its::AsnInteger(description)
        {
            // Nothing to do.
        }

        Priority(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

        virtual ~Priority()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Priority(*this);
        }

        virtual std::string GetName() const
        { return "Priority"; }

    };


        typedef inap_cs2::ServiceControlOptions ServiceControlOptions;


////////// End Nested Class(es) //////////

    InServiceControls() : its::AsnSet(2, false)
    {
        Initialize();
    }

    InServiceControls(its::Octets& octets) : its::AsnSet(2, false)
    {
        Initialize();
        Decode(octets);
    }

    InServiceControls(const InServiceControls& rhs) : its::AsnSet(rhs)
    {
        // Nothing to do.
    }

    InServiceControls(its::AsnDescObject* description) : its::AsnSet(2, description)
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

    static its::AsnDescObject* GetOptionsStaticDescription();
    static its::AsnDescObject* GetPriorityStaticDescription();

public:

    virtual ~InServiceControls()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new InServiceControls(*this);
    }

    virtual std::string GetName() const
    { return "InServiceControls"; }

    void SetOptions(ServiceControlOptions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOptionsStaticDescription());
        AddElement(0, element);
    }

    void SetOptions(const ServiceControlOptions& element)
    {
        its::AsnObject& asnObject = const_cast<ServiceControlOptions&>(element);
        asnObject.SetDescription(GetOptionsStaticDescription());
        AddElement(0, element);
}

    bool OptionOptions() const
    {
        return Contains(0);
    }

    const ServiceControlOptions& GetOptions() const
    {
        ITS_REQUIRE(OptionOptions());
        return static_cast<const ServiceControlOptions&> (ElementAt(0));
    }

    void SetPriority(Priority* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPriorityStaticDescription());
        AddElement(1, element);
    }

    void SetPriority(const Priority& element)
    {
        its::AsnObject& asnObject = const_cast<Priority&>(element);
        asnObject.SetDescription(GetPriorityStaticDescription());
        AddElement(1, element);
}

    bool OptionPriority() const
    {
        return Contains(1);
    }

    const Priority& GetPriority() const
    {
        ITS_REQUIRE(OptionPriority());
        return static_cast<const Priority&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_IN_SERVICE_CONTROLS_H_)
