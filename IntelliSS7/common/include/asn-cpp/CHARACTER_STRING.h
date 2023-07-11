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


#if !defined(_ASN_USEFUL_CHARACTER_STRING_H_)
#define _ASN_USEFUL_CHARACTER_STRING_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnChoice.h>
#include <AsnObjectIdentifier.h>
#include <AsnInteger.h>
#include <AsnNull.h>
#include <AsnOctetString.h>



namespace its {



class CHARACTER_STRING : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class Identification : public its::AsnChoice
    {
    public:


    ////////// Begin Nested Class(es) //////////



        class Syntaxes : public its::AsnSequence
        {
        public:


        ////////// Begin Nested Class(es) //////////



            class Abstract : public its::AsnObjectIdentifier
            {
            public:

                Abstract() : its::AsnObjectIdentifier(false)
                {
                    Initialize();
                }

                Abstract(const std::vector<long>& array) : its::AsnObjectIdentifier(array, false)
                {
                    Initialize();
                }

                Abstract(its::Octets& octets) : its::AsnObjectIdentifier(false)
                {
                    Initialize();
                    Decode(octets);
                }

                Abstract(const Abstract& rhs) : its::AsnObjectIdentifier(rhs)
                {
                    // Nothing to do.
                }

                Abstract(its::AsnDescObject* description) : its::AsnObjectIdentifier(description)
                {
                    // Nothing to do.
                }

                Abstract(its::AsnDescObject* description, const std::vector<long>& array) : its::AsnObjectIdentifier(description, array)
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

                virtual ~Abstract()
                {
                    // Nothing to do.
                }

                virtual its::AsnObject* Clone() const
                {
                    return new Abstract(*this);
                }

                virtual std::string GetName() const
                { return "Abstract"; }

            };



            class Transfer : public its::AsnObjectIdentifier
            {
            public:

                Transfer() : its::AsnObjectIdentifier(false)
                {
                    Initialize();
                }

                Transfer(const std::vector<long>& array) : its::AsnObjectIdentifier(array, false)
                {
                    Initialize();
                }

                Transfer(its::Octets& octets) : its::AsnObjectIdentifier(false)
                {
                    Initialize();
                    Decode(octets);
                }

                Transfer(const Transfer& rhs) : its::AsnObjectIdentifier(rhs)
                {
                    // Nothing to do.
                }

                Transfer(its::AsnDescObject* description) : its::AsnObjectIdentifier(description)
                {
                    // Nothing to do.
                }

                Transfer(its::AsnDescObject* description, const std::vector<long>& array) : its::AsnObjectIdentifier(description, array)
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

                virtual ~Transfer()
                {
                    // Nothing to do.
                }

                virtual its::AsnObject* Clone() const
                {
                    return new Transfer(*this);
                }

                virtual std::string GetName() const
                { return "Transfer"; }

            };


        ////////// End Nested Class(es) //////////

            Syntaxes() : its::AsnSequence(2, false)
            {
                Initialize();
            }

            Syntaxes(its::Octets& octets) : its::AsnSequence(2, false)
            {
                Initialize();
                Decode(octets);
            }

            Syntaxes(const Syntaxes& rhs) : its::AsnSequence(rhs)
            {
                // Nothing to do.
            }

            Syntaxes(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

            static its::AsnDescObject* GetAbstractStaticDescription();
            static its::AsnDescObject* GetTransferStaticDescription();

        public:

            virtual ~Syntaxes()
            {
                // Nothing to do.
            }

            virtual its::AsnObject* Clone() const
            {
                return new Syntaxes(*this);
            }

            virtual std::string GetName() const
            { return "Syntaxes"; }

            void SetAbstract(Abstract* element)
            {
                ITS_REQUIRE(element != NULL);
                element->AsnObject::SetDescription(GetAbstractStaticDescription());
                AddElement(0, element);
            }

            void SetAbstract(const Abstract& element)
            {
                its::AsnObject& asnObject = const_cast<Abstract&>(element);
                asnObject.SetDescription(GetAbstractStaticDescription());
                AddElement(0, element);
            }

            const Abstract& GetAbstract() const
            {
                return static_cast<const Abstract&> (ElementAt(0));
            }

            void SetTransfer(Transfer* element)
            {
                ITS_REQUIRE(element != NULL);
                element->AsnObject::SetDescription(GetTransferStaticDescription());
                AddElement(1, element);
            }

            void SetTransfer(const Transfer& element)
            {
                its::AsnObject& asnObject = const_cast<Transfer&>(element);
                asnObject.SetDescription(GetTransferStaticDescription());
                AddElement(1, element);
            }

            const Transfer& GetTransfer() const
            {
                return static_cast<const Transfer&> (ElementAt(1));
            }

        };



        class Syntax : public its::AsnObjectIdentifier
        {
        public:

            Syntax() : its::AsnObjectIdentifier(false)
            {
                Initialize();
            }

            Syntax(const std::vector<long>& array) : its::AsnObjectIdentifier(array, false)
            {
                Initialize();
            }

            Syntax(its::Octets& octets) : its::AsnObjectIdentifier(false)
            {
                Initialize();
                Decode(octets);
            }

            Syntax(const Syntax& rhs) : its::AsnObjectIdentifier(rhs)
            {
                // Nothing to do.
            }

            Syntax(its::AsnDescObject* description) : its::AsnObjectIdentifier(description)
            {
                // Nothing to do.
            }

            Syntax(its::AsnDescObject* description, const std::vector<long>& array) : its::AsnObjectIdentifier(description, array)
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

            virtual ~Syntax()
            {
                // Nothing to do.
            }

            virtual its::AsnObject* Clone() const
            {
                return new Syntax(*this);
            }

            virtual std::string GetName() const
            { return "Syntax"; }

        };



        class Presentation_context_id : public its::AsnInteger
        {
        public:

            Presentation_context_id() : its::AsnInteger(false)
            {
                Initialize();
            }

            Presentation_context_id(long value) : its::AsnInteger(value, false)
            {
                Initialize();
            }

            Presentation_context_id(its::Octets& octets) : its::AsnInteger(false)
            {
                Initialize();
                Decode(octets);
            }

            Presentation_context_id(const Presentation_context_id& rhs) : its::AsnInteger(rhs)
            {
                // Nothing to do.
            }

            Presentation_context_id(its::AsnDescObject* description) : its::AsnInteger(description)
            {
                // Nothing to do.
            }

            Presentation_context_id(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

            virtual ~Presentation_context_id()
            {
                // Nothing to do.
            }

            virtual its::AsnObject* Clone() const
            {
                return new Presentation_context_id(*this);
            }

            virtual std::string GetName() const
            { return "Presentation_context_id"; }

        };



        class Context_negotiation : public its::AsnSequence
        {
        public:


        ////////// Begin Nested Class(es) //////////



            class Presentation_context_id : public its::AsnInteger
            {
            public:

                Presentation_context_id() : its::AsnInteger(false)
                {
                    Initialize();
                }

                Presentation_context_id(long value) : its::AsnInteger(value, false)
                {
                    Initialize();
                }

                Presentation_context_id(its::Octets& octets) : its::AsnInteger(false)
                {
                    Initialize();
                    Decode(octets);
                }

                Presentation_context_id(const Presentation_context_id& rhs) : its::AsnInteger(rhs)
                {
                    // Nothing to do.
                }

                Presentation_context_id(its::AsnDescObject* description) : its::AsnInteger(description)
                {
                    // Nothing to do.
                }

                Presentation_context_id(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

                virtual ~Presentation_context_id()
                {
                    // Nothing to do.
                }

                virtual its::AsnObject* Clone() const
                {
                    return new Presentation_context_id(*this);
                }

                virtual std::string GetName() const
                { return "Presentation_context_id"; }

            };



            class Transfer_syntax : public its::AsnObjectIdentifier
            {
            public:

                Transfer_syntax() : its::AsnObjectIdentifier(false)
                {
                    Initialize();
                }

                Transfer_syntax(const std::vector<long>& array) : its::AsnObjectIdentifier(array, false)
                {
                    Initialize();
                }

                Transfer_syntax(its::Octets& octets) : its::AsnObjectIdentifier(false)
                {
                    Initialize();
                    Decode(octets);
                }

                Transfer_syntax(const Transfer_syntax& rhs) : its::AsnObjectIdentifier(rhs)
                {
                    // Nothing to do.
                }

                Transfer_syntax(its::AsnDescObject* description) : its::AsnObjectIdentifier(description)
                {
                    // Nothing to do.
                }

                Transfer_syntax(its::AsnDescObject* description, const std::vector<long>& array) : its::AsnObjectIdentifier(description, array)
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

                virtual ~Transfer_syntax()
                {
                    // Nothing to do.
                }

                virtual its::AsnObject* Clone() const
                {
                    return new Transfer_syntax(*this);
                }

                virtual std::string GetName() const
                { return "Transfer_syntax"; }

            };


        ////////// End Nested Class(es) //////////

            Context_negotiation() : its::AsnSequence(2, false)
            {
                Initialize();
            }

            Context_negotiation(its::Octets& octets) : its::AsnSequence(2, false)
            {
                Initialize();
                Decode(octets);
            }

            Context_negotiation(const Context_negotiation& rhs) : its::AsnSequence(rhs)
            {
                // Nothing to do.
            }

            Context_negotiation(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

            static its::AsnDescObject* GetPresentation_context_idStaticDescription();
            static its::AsnDescObject* GetTransfer_syntaxStaticDescription();

        public:

            virtual ~Context_negotiation()
            {
                // Nothing to do.
            }

            virtual its::AsnObject* Clone() const
            {
                return new Context_negotiation(*this);
            }

            virtual std::string GetName() const
            { return "Context_negotiation"; }

            void SetPresentation_context_id(Presentation_context_id* element)
            {
                ITS_REQUIRE(element != NULL);
                element->AsnObject::SetDescription(GetPresentation_context_idStaticDescription());
                AddElement(0, element);
            }

            void SetPresentation_context_id(const Presentation_context_id& element)
            {
                its::AsnObject& asnObject = const_cast<Presentation_context_id&>(element);
                asnObject.SetDescription(GetPresentation_context_idStaticDescription());
                AddElement(0, element);
            }

            const Presentation_context_id& GetPresentation_context_id() const
            {
                return static_cast<const Presentation_context_id&> (ElementAt(0));
            }

            void SetTransfer_syntax(Transfer_syntax* element)
            {
                ITS_REQUIRE(element != NULL);
                element->AsnObject::SetDescription(GetTransfer_syntaxStaticDescription());
                AddElement(1, element);
            }

            void SetTransfer_syntax(const Transfer_syntax& element)
            {
                its::AsnObject& asnObject = const_cast<Transfer_syntax&>(element);
                asnObject.SetDescription(GetTransfer_syntaxStaticDescription());
                AddElement(1, element);
            }

            const Transfer_syntax& GetTransfer_syntax() const
            {
                return static_cast<const Transfer_syntax&> (ElementAt(1));
            }

        };



        class Transfer_syntax : public its::AsnObjectIdentifier
        {
        public:

            Transfer_syntax() : its::AsnObjectIdentifier(false)
            {
                Initialize();
            }

            Transfer_syntax(const std::vector<long>& array) : its::AsnObjectIdentifier(array, false)
            {
                Initialize();
            }

            Transfer_syntax(its::Octets& octets) : its::AsnObjectIdentifier(false)
            {
                Initialize();
                Decode(octets);
            }

            Transfer_syntax(const Transfer_syntax& rhs) : its::AsnObjectIdentifier(rhs)
            {
                // Nothing to do.
            }

            Transfer_syntax(its::AsnDescObject* description) : its::AsnObjectIdentifier(description)
            {
                // Nothing to do.
            }

            Transfer_syntax(its::AsnDescObject* description, const std::vector<long>& array) : its::AsnObjectIdentifier(description, array)
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

            virtual ~Transfer_syntax()
            {
                // Nothing to do.
            }

            virtual its::AsnObject* Clone() const
            {
                return new Transfer_syntax(*this);
            }

            virtual std::string GetName() const
            { return "Transfer_syntax"; }

        };



        class Fixed : public its::AsnNull
        {
        public:

            Fixed() : its::AsnNull(false)
            {
                Initialize();
            }

            Fixed(its::Octets& octets) : its::AsnNull(false)
            {
                Initialize();
                Decode(octets);
            }

            Fixed(const Fixed& rhs) : its::AsnNull(rhs)
            {
                // Nothing to do.
            }

            Fixed(its::AsnDescObject* description) : its::AsnNull(description)
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

            virtual ~Fixed()
            {
                // Nothing to do.
            }

            virtual its::AsnObject* Clone() const
            {
                return new Fixed(*this);
            }

            virtual std::string GetName() const
            { return "Fixed"; }

        };


    ////////// End Nested Class(es) //////////

        Identification() : its::AsnChoice(false)
        {
            Initialize();
        }

        Identification(its::Octets& octets) : its::AsnChoice(false)
        {
            Initialize();
            Decode(octets);
        }

        Identification(const Identification& rhs) : its::AsnChoice(rhs)
        {
            // Nothing to do.
        }

        Identification(its::AsnDescObject* description) : its::AsnChoice(description)
        {
            // Nothing to do.
        }

        Identification(its::AsnDescObject* description, its::AsnObject* choice) : its::AsnChoice(description, choice)
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

        static its::AsnDescObject* GetSyntaxesStaticDescription();
        static its::AsnDescObject* GetSyntaxStaticDescription();
        static its::AsnDescObject* GetPresentation_context_idStaticDescription();
        static its::AsnDescObject* GetContext_negotiationStaticDescription();
        static its::AsnDescObject* GetTransfer_syntaxStaticDescription();
        static its::AsnDescObject* GetFixedStaticDescription();

    public:

        virtual ~Identification()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Identification(*this);
        }

        virtual std::string GetName() const
        { return "Identification"; }

        void SetChoiceSyntaxes(Syntaxes* choice)
        {
            ITS_REQUIRE(choice != NULL);
            choice->AsnObject::SetDescription(GetSyntaxesStaticDescription());
            SetChoice(choice);
        }

        void SetChoiceSyntaxes(const Syntaxes& choice)
        {
            its::AsnObject& asnObject = const_cast<Syntaxes&>(choice);
            asnObject.SetDescription(GetSyntaxesStaticDescription());
            SetChoice(choice);
        }

        bool ChoiceSyntaxes() const
        {
            return Contains(GetSyntaxesStaticDescription()->TagIdentity());
        }

        const Syntaxes& GetChoiceSyntaxes() const
        {
            ITS_REQUIRE(ChoiceSyntaxes());
            return static_cast<const Syntaxes&> (GetChoice());
        }

        void SetChoiceSyntax(Syntax* choice)
        {
            ITS_REQUIRE(choice != NULL);
            choice->AsnObject::SetDescription(GetSyntaxStaticDescription());
            SetChoice(choice);
        }

        void SetChoiceSyntax(const Syntax& choice)
        {
            its::AsnObject& asnObject = const_cast<Syntax&>(choice);
            asnObject.SetDescription(GetSyntaxStaticDescription());
            SetChoice(choice);
        }

        bool ChoiceSyntax() const
        {
            return Contains(GetSyntaxStaticDescription()->TagIdentity());
        }

        const Syntax& GetChoiceSyntax() const
        {
            ITS_REQUIRE(ChoiceSyntax());
            return static_cast<const Syntax&> (GetChoice());
        }

        void SetChoicePresentation_context_id(Presentation_context_id* choice)
        {
            ITS_REQUIRE(choice != NULL);
            choice->AsnObject::SetDescription(GetPresentation_context_idStaticDescription());
            SetChoice(choice);
        }

        void SetChoicePresentation_context_id(const Presentation_context_id& choice)
        {
            its::AsnObject& asnObject = const_cast<Presentation_context_id&>(choice);
            asnObject.SetDescription(GetPresentation_context_idStaticDescription());
            SetChoice(choice);
        }

        bool ChoicePresentation_context_id() const
        {
            return Contains(GetPresentation_context_idStaticDescription()->TagIdentity());
        }

        const Presentation_context_id& GetChoicePresentation_context_id() const
        {
            ITS_REQUIRE(ChoicePresentation_context_id());
            return static_cast<const Presentation_context_id&> (GetChoice());
        }

        void SetChoiceContext_negotiation(Context_negotiation* choice)
        {
            ITS_REQUIRE(choice != NULL);
            choice->AsnObject::SetDescription(GetContext_negotiationStaticDescription());
            SetChoice(choice);
        }

        void SetChoiceContext_negotiation(const Context_negotiation& choice)
        {
            its::AsnObject& asnObject = const_cast<Context_negotiation&>(choice);
            asnObject.SetDescription(GetContext_negotiationStaticDescription());
            SetChoice(choice);
        }

        bool ChoiceContext_negotiation() const
        {
            return Contains(GetContext_negotiationStaticDescription()->TagIdentity());
        }

        const Context_negotiation& GetChoiceContext_negotiation() const
        {
            ITS_REQUIRE(ChoiceContext_negotiation());
            return static_cast<const Context_negotiation&> (GetChoice());
        }

        void SetChoiceTransfer_syntax(Transfer_syntax* choice)
        {
            ITS_REQUIRE(choice != NULL);
            choice->AsnObject::SetDescription(GetTransfer_syntaxStaticDescription());
            SetChoice(choice);
        }

        void SetChoiceTransfer_syntax(const Transfer_syntax& choice)
        {
            its::AsnObject& asnObject = const_cast<Transfer_syntax&>(choice);
            asnObject.SetDescription(GetTransfer_syntaxStaticDescription());
            SetChoice(choice);
        }

        bool ChoiceTransfer_syntax() const
        {
            return Contains(GetTransfer_syntaxStaticDescription()->TagIdentity());
        }

        const Transfer_syntax& GetChoiceTransfer_syntax() const
        {
            ITS_REQUIRE(ChoiceTransfer_syntax());
            return static_cast<const Transfer_syntax&> (GetChoice());
        }

        void SetChoiceFixed(Fixed* choice)
        {
            ITS_REQUIRE(choice != NULL);
            choice->AsnObject::SetDescription(GetFixedStaticDescription());
            SetChoice(choice);
        }

        void SetChoiceFixed(const Fixed& choice)
        {
            its::AsnObject& asnObject = const_cast<Fixed&>(choice);
            asnObject.SetDescription(GetFixedStaticDescription());
            SetChoice(choice);
        }

        bool ChoiceFixed() const
        {
            return Contains(GetFixedStaticDescription()->TagIdentity());
        }

        const Fixed& GetChoiceFixed() const
        {
            ITS_REQUIRE(ChoiceFixed());
            return static_cast<const Fixed&> (GetChoice());
        }

    };



    class String_value : public its::AsnOctetString
    {
    public:

        String_value() : its::AsnOctetString(false)
        {
            Initialize();
        }

        String_value(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        String_value(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        String_value(const String_value& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        String_value(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        String_value(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~String_value()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new String_value(*this);
        }

        virtual std::string GetName() const
        { return "String_value"; }

    };


////////// End Nested Class(es) //////////

    CHARACTER_STRING() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    CHARACTER_STRING(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    CHARACTER_STRING(const CHARACTER_STRING& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    CHARACTER_STRING(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetIdentificationStaticDescription();
    static its::AsnDescObject* GetString_valueStaticDescription();

public:

    virtual ~CHARACTER_STRING()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CHARACTER_STRING(*this);
    }

    virtual std::string GetName() const
    { return "CHARACTER_STRING"; }

    void SetIdentification(Identification* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIdentificationStaticDescription());
        AddElement(0, element);
    }

    void SetIdentification(const Identification& element)
    {
        its::AsnObject& asnObject = const_cast<Identification&>(element);
        asnObject.SetDescription(GetIdentificationStaticDescription());
        AddElement(0, element);
    }

    const Identification& GetIdentification() const
    {
        return static_cast<const Identification&> (ElementAt(0));
    }

    void SetString_value(String_value* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetString_valueStaticDescription());
        AddElement(1, element);
    }

    void SetString_value(const String_value& element)
    {
        its::AsnObject& asnObject = const_cast<String_value&>(element);
        asnObject.SetDescription(GetString_valueStaticDescription());
        AddElement(1, element);
    }

    const String_value& GetString_value() const
    {
        return static_cast<const String_value&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_ASN_USEFUL_CHARACTER_STRING_H_)

