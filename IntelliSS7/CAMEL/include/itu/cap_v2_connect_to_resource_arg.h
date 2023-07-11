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


#if !defined(_CAP_V2_CONNECT_TO_RESOURCE_ARG_H_)
#define _CAP_V2_CONNECT_TO_RESOURCE_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnChoice.h>
#include <AsnNull.h>
#include <AsnOctetString.h>
#include <AsnSequenceOf.h>

#include <cap_v2_ip_routing_address.h>
#include <cap_v2_extension_field.h>
#include <cap_v2_service_interaction_indicators_two.h>



namespace cap_v2 {



class ConnectToResourceArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class ResourceAddress : public its::AsnChoice
    {
    public:


    ////////// Begin Nested Class(es) //////////



        class None : public its::AsnNull
        {
        public:

            None() : its::AsnNull(false)
            {
                Initialize();
            }

            None(its::Octets& octets) : its::AsnNull(false)
            {
                Initialize();
                Decode(octets);
            }

            None(const None& rhs) : its::AsnNull(rhs)
            {
                // Nothing to do.
            }

            None(its::AsnDescObject* description) : its::AsnNull(description)
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

            virtual ~None()
            {
                // Nothing to do.
            }

            virtual its::AsnObject* Clone() const
            {
                return new None(*this);
            }

            virtual std::string GetName() const
            { return "None"; }

        };


            typedef cap_v2::IPRoutingAddress IPRoutingAddress;


    ////////// End Nested Class(es) //////////

        ResourceAddress() : its::AsnChoice(false)
        {
            Initialize();
        }

        ResourceAddress(its::Octets& octets) : its::AsnChoice(false)
        {
            Initialize();
            Decode(octets);
        }

        ResourceAddress(const ResourceAddress& rhs) : its::AsnChoice(rhs)
        {
            // Nothing to do.
        }

        ResourceAddress(its::AsnDescObject* description) : its::AsnChoice(description)
        {
            // Nothing to do.
        }

        ResourceAddress(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

        static its::AsnDescObject* GetIpRoutingAddressStaticDescription();
        static its::AsnDescObject* GetNoneStaticDescription();

    public:

        virtual ~ResourceAddress()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new ResourceAddress(*this);
        }

        virtual std::string GetName() const
        { return "ResourceAddress"; }

        void SetChoiceIpRoutingAddress(IPRoutingAddress* choice)
        {
            ITS_REQUIRE(choice != NULL);
            choice->AsnObject::SetDescription(GetIpRoutingAddressStaticDescription());
            SetChoice(choice);
        }

        void SetChoiceIpRoutingAddress(const IPRoutingAddress& choice)
        {
            its::AsnObject& asnObject = const_cast<IPRoutingAddress&>(choice);
            asnObject.SetDescription(GetIpRoutingAddressStaticDescription());
            SetChoice(choice);
        }

        bool ChoiceIpRoutingAddress() const
        {
            return Contains(GetIpRoutingAddressStaticDescription()->TagIdentity());
        }

        const IPRoutingAddress& GetChoiceIpRoutingAddress() const
        {
            ITS_REQUIRE(ChoiceIpRoutingAddress());
            return static_cast<const IPRoutingAddress&> (GetChoice());
        }

        void SetChoiceNone(None* choice)
        {
            ITS_REQUIRE(choice != NULL);
            choice->AsnObject::SetDescription(GetNoneStaticDescription());
            SetChoice(choice);
        }

        void SetChoiceNone(const None& choice)
        {
            its::AsnObject& asnObject = const_cast<None&>(choice);
            asnObject.SetDescription(GetNoneStaticDescription());
            SetChoice(choice);
        }

        bool ChoiceNone() const
        {
            return Contains(GetNoneStaticDescription()->TagIdentity());
        }

        const None& GetChoiceNone() const
        {
            ITS_REQUIRE(ChoiceNone());
            return static_cast<const None&> (GetChoice());
        }

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


        typedef cap_v2::ServiceInteractionIndicatorsTwo ServiceInteractionIndicatorsTwo;


////////// End Nested Class(es) //////////

    ConnectToResourceArg() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    ConnectToResourceArg(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    ConnectToResourceArg(const ConnectToResourceArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ConnectToResourceArg(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetResourceAddressStaticDescription();
    static its::AsnDescObject* GetExtensionsStaticDescription();
    static its::AsnDescObject* GetServiceInteractionIndicatorsTwoStaticDescription();

public:

    virtual ~ConnectToResourceArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ConnectToResourceArg(*this);
    }

    virtual std::string GetName() const
    { return "ConnectToResourceArg"; }

    void SetResourceAddress(ResourceAddress* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetResourceAddressStaticDescription());
        AddElement(0, element);
    }

    void SetResourceAddress(const ResourceAddress& element)
    {
        its::AsnObject& asnObject = const_cast<ResourceAddress&>(element);
        asnObject.SetDescription(GetResourceAddressStaticDescription());
        AddElement(0, element);
    }

    const ResourceAddress& GetResourceAddress() const
    {
        return static_cast<const ResourceAddress&> (ElementAt(0));
    }

    void SetExtensions(Extensions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionsStaticDescription());
        AddElement(1, element);
    }

    void SetExtensions(const Extensions& element)
    {
        its::AsnObject& asnObject = const_cast<Extensions&>(element);
        asnObject.SetDescription(GetExtensionsStaticDescription());
        AddElement(1, element);
    }

    bool OptionExtensions() const
    {
        return Contains(1);
    }

    const Extensions& GetExtensions() const
    {
        ITS_REQUIRE(OptionExtensions());
        return static_cast<const Extensions&> (ElementAt(1));
    }

    void SetServiceInteractionIndicatorsTwo(ServiceInteractionIndicatorsTwo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetServiceInteractionIndicatorsTwoStaticDescription());
        AddElement(2, element);
    }

    void SetServiceInteractionIndicatorsTwo(const ServiceInteractionIndicatorsTwo& element)
    {
        its::AsnObject& asnObject = const_cast<ServiceInteractionIndicatorsTwo&>(element);
        asnObject.SetDescription(GetServiceInteractionIndicatorsTwoStaticDescription());
        AddElement(2, element);
    }

    bool OptionServiceInteractionIndicatorsTwo() const
    {
        return Contains(2);
    }

    const ServiceInteractionIndicatorsTwo& GetServiceInteractionIndicatorsTwo() const
    {
        ITS_REQUIRE(OptionServiceInteractionIndicatorsTwo());
        return static_cast<const ServiceInteractionIndicatorsTwo&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_CAP_V2_CONNECT_TO_RESOURCE_ARG_H_)

