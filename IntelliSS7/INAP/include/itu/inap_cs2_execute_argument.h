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


#if !defined(_INAP_CS2_EXECUTE_ARGUMENT_H_)
#define _INAP_CS2_EXECUTE_ARGUMENT_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSet.h>
#include <AsnObjectIdentifier.h>
#include <AsnSequenceOf.h>
#include <AsnSequence.h>
#include <AsnChoice.h>

#include <inap_cs2_name.h>
#include <inap_cs2_attribute_type_and_value.h>
#include <inap_cs2_specific_input.h>



namespace inap_cs2 {



class ExecuteArgument : public its::AsnSet
{
public:


////////// Begin Nested Class(es) //////////



    class Method_id : public its::AsnObjectIdentifier
    {
    public:

        Method_id() : its::AsnObjectIdentifier(false)
        {
            Initialize();
        }

        Method_id(const std::vector<long>& array) : its::AsnObjectIdentifier(array, false)
        {
            Initialize();
        }

        Method_id(its::Octets& octets) : its::AsnObjectIdentifier(false)
        {
            Initialize();
            Decode(octets);
        }

        Method_id(const Method_id& rhs) : its::AsnObjectIdentifier(rhs)
        {
            // Nothing to do.
        }

        Method_id(its::AsnDescObject* description) : its::AsnObjectIdentifier(description)
        {
            // Nothing to do.
        }

        Method_id(its::AsnDescObject* description, const std::vector<long>& array) : its::AsnObjectIdentifier(description, array)
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

        virtual ~Method_id()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Method_id(*this);
        }

        virtual std::string GetName() const
        { return "Method_id"; }

    };



    class Input_assertions : public its::AsnSequenceOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef inap_cs2::AttributeTypeAndValue AttributeTypeAndValue;


    ////////// End Nested Class //////////

        Input_assertions() : its::AsnSequenceOf(false)
        {
            Initialize();
        }

        Input_assertions(its::Octets& octets) : its::AsnSequenceOf(false)
        {
            Initialize();
            Decode(octets);
        }

        Input_assertions(const Input_assertions& rhs) : its::AsnSequenceOf(rhs)
        {
            // Nothing to do.
        }

        Input_assertions(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

        static its::AsnDescObject* GetAttributeTypeAndValueStaticDescription();

    public:

        virtual ~Input_assertions()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Input_assertions(*this);
        }

        virtual std::string GetName() const
        { return "Input_assertions"; }

        void AddElement(AttributeTypeAndValue* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetAttributeTypeAndValueStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        void AddElement(const AttributeTypeAndValue& element)
        {
            its::AsnObject& asnObject = const_cast<AttributeTypeAndValue&>(element);
            asnObject.SetDescription(GetAttributeTypeAndValueStaticDescription());
            AsnSequenceOf::AddElement(element);
        }

        const AttributeTypeAndValue& ElementAt(int index) const
        {
            return static_cast<const AttributeTypeAndValue&> (AsnSequenceOf::ElementAt(index));
        }

    };


        typedef inap_cs2::Name Name;


        typedef inap_cs2::SpecificInput SpecificInput;


////////// End Nested Class(es) //////////

    ExecuteArgument() : its::AsnSet(4, false)
    {
        Initialize();
    }

    ExecuteArgument(its::Octets& octets) : its::AsnSet(4, false)
    {
        Initialize();
        Decode(octets);
    }

    ExecuteArgument(const ExecuteArgument& rhs) : its::AsnSet(rhs)
    {
        // Nothing to do.
    }

    ExecuteArgument(its::AsnDescObject* description) : its::AsnSet(4, description)
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

    static its::AsnDescObject* GetObjectStaticDescription();
    static its::AsnDescObject* GetMethod_idStaticDescription();
    static its::AsnDescObject* GetInput_assertionsStaticDescription();
    static its::AsnDescObject* GetSpecific_inputStaticDescription();

public:

    virtual ~ExecuteArgument()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ExecuteArgument(*this);
    }

    virtual std::string GetName() const
    { return "ExecuteArgument"; }

    void SetObject(Name* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetObjectStaticDescription());
        AddElement(0, element);
    }

    void SetObject(const Name& element)
    {
        its::AsnObject& asnObject = const_cast<Name&>(element);
        asnObject.SetDescription(GetObjectStaticDescription());
        AddElement(0, element);
}

    const Name& GetObject() const
    {
        return static_cast<const Name&> (ElementAt(0));
    }

    void SetMethod_id(Method_id* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMethod_idStaticDescription());
        AddElement(1, element);
    }

    void SetMethod_id(const Method_id& element)
    {
        its::AsnObject& asnObject = const_cast<Method_id&>(element);
        asnObject.SetDescription(GetMethod_idStaticDescription());
        AddElement(1, element);
}

    const Method_id& GetMethod_id() const
    {
        return static_cast<const Method_id&> (ElementAt(1));
    }

    void SetInput_assertions(Input_assertions* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetInput_assertionsStaticDescription());
        AddElement(2, element);
    }

    void SetInput_assertions(const Input_assertions& element)
    {
        its::AsnObject& asnObject = const_cast<Input_assertions&>(element);
        asnObject.SetDescription(GetInput_assertionsStaticDescription());
        AddElement(2, element);
}

    bool OptionInput_assertions() const
    {
        return Contains(2);
    }

    const Input_assertions& GetInput_assertions() const
    {
        ITS_REQUIRE(OptionInput_assertions());
        return static_cast<const Input_assertions&> (ElementAt(2));
    }

    void SetSpecific_input(SpecificInput* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSpecific_inputStaticDescription());
        AddElement(3, element);
    }

    void SetSpecific_input(const SpecificInput& element)
    {
        its::AsnObject& asnObject = const_cast<SpecificInput&>(element);
        asnObject.SetDescription(GetSpecific_inputStaticDescription());
        AddElement(3, element);
}

    bool OptionSpecific_input() const
    {
        return Contains(3);
    }

    const SpecificInput& GetSpecific_input() const
    {
        ITS_REQUIRE(OptionSpecific_input());
        return static_cast<const SpecificInput&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_EXECUTE_ARGUMENT_H_)
