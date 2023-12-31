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


#if !defined(_INAP_CS2_SEARCH_INFO_H_)
#define _INAP_CS2_SEARCH_INFO_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSet.h>
#include <AsnSetOf.h>
#include <AsnSequence.h>
#include <AsnBoolean.h>
#include <AsnSequenceOf.h>

#include <inap_cs2_distinguished_name.h>
#include <inap_cs2_in_entry_information.h>
#include <inap_cs2_partial_outcome_qualifier.h>
#include <inap_cs2_security_parameters.h>



namespace inap_cs2 {



class SearchInfo : public its::AsnSet
{
public:


////////// Begin Nested Class(es) //////////



    class Entries : public its::AsnSetOf
    {
    public:


    ////////// Begin Nested Class //////////


            typedef inap_cs2::InEntryInformation InEntryInformation;


    ////////// End Nested Class //////////

        Entries() : its::AsnSetOf(false)
        {
            Initialize();
        }

        Entries(its::Octets& octets) : its::AsnSetOf(false)
        {
            Initialize();
            Decode(octets);
        }

        Entries(const Entries& rhs) : its::AsnSetOf(rhs)
        {
            // Nothing to do.
        }

        Entries(its::AsnDescObject* description) : its::AsnSetOf(description)
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

        static its::AsnDescObject* GetInEntryInformationStaticDescription();

    public:

        virtual ~Entries()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new Entries(*this);
        }

        virtual std::string GetName() const
        { return "Entries"; }

        void AddElement(InEntryInformation* element)
        {
            ITS_REQUIRE(element != NULL);
            element->AsnObject::SetDescription(GetInEntryInformationStaticDescription());
            AsnSetOf::AddElement(element);
        }

        void AddElement(const InEntryInformation& element)
        {
            its::AsnObject& asnObject = const_cast<InEntryInformation&>(element);
            asnObject.SetDescription(GetInEntryInformationStaticDescription());
            AsnSetOf::AddElement(element);
        }

        const InEntryInformation& ElementAt(int index) const
        {
            return static_cast<const InEntryInformation&> (AsnSetOf::ElementAt(index));
        }

    };



    class AliasDereferenced : public its::AsnBoolean
    {
    public:

        AliasDereferenced(bool value) : its::AsnBoolean(value, false)
        {
            Initialize();
        }

        AliasDereferenced(its::Octets& octets) : its::AsnBoolean(false, false)
        {
            Initialize();
            Decode(octets);
        }

        AliasDereferenced(const AliasDereferenced& rhs) : its::AsnBoolean(rhs)
        {
            // Nothing to do.
        }

        AliasDereferenced(its::AsnDescObject* description) : its::AsnBoolean(description)
        {
            // Nothing to do.
        }

        AliasDereferenced(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

        virtual ~AliasDereferenced()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new AliasDereferenced(*this);
        }

        virtual std::string GetName() const
        { return "AliasDereferenced"; }

    };


        typedef inap_cs2::DistinguishedName DistinguishedName;


        typedef inap_cs2::PartialOutcomeQualifier PartialOutcomeQualifier;


        typedef inap_cs2::SecurityParameters SecurityParameters;


////////// End Nested Class(es) //////////

    SearchInfo() : its::AsnSet(6, false)
    {
        Initialize();
    }

    SearchInfo(its::Octets& octets) : its::AsnSet(6, false)
    {
        Initialize();
        Decode(octets);
    }

    SearchInfo(const SearchInfo& rhs) : its::AsnSet(rhs)
    {
        // Nothing to do.
    }

    SearchInfo(its::AsnDescObject* description) : its::AsnSet(6, description)
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

    static its::AsnDescObject* GetDistinguishedNameStaticDescription();
    static its::AsnDescObject* GetEntriesStaticDescription();
    static its::AsnDescObject* GetPartialOutcomeQualifierStaticDescription();
    static its::AsnDescObject* GetSecurityParametersStaticDescription();
    static its::AsnDescObject* GetPerformerStaticDescription();
    static its::AsnDescObject* GetAliasDereferencedStaticDescription();

public:

    virtual ~SearchInfo()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SearchInfo(*this);
    }

    virtual std::string GetName() const
    { return "SearchInfo"; }

    void SetDistinguishedName(DistinguishedName* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetDistinguishedNameStaticDescription());
        AddElement(0, element);
    }

    void SetDistinguishedName(const DistinguishedName& element)
    {
        its::AsnObject& asnObject = const_cast<DistinguishedName&>(element);
        asnObject.SetDescription(GetDistinguishedNameStaticDescription());
        AddElement(0, element);
}

    bool OptionDistinguishedName() const
    {
        return Contains(0);
    }

    const DistinguishedName& GetDistinguishedName() const
    {
        ITS_REQUIRE(OptionDistinguishedName());
        return static_cast<const DistinguishedName&> (ElementAt(0));
    }

    void SetEntries(Entries* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEntriesStaticDescription());
        AddElement(1, element);
    }

    void SetEntries(const Entries& element)
    {
        its::AsnObject& asnObject = const_cast<Entries&>(element);
        asnObject.SetDescription(GetEntriesStaticDescription());
        AddElement(1, element);
}

    const Entries& GetEntries() const
    {
        return static_cast<const Entries&> (ElementAt(1));
    }

    void SetPartialOutcomeQualifier(PartialOutcomeQualifier* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPartialOutcomeQualifierStaticDescription());
        AddElement(2, element);
    }

    void SetPartialOutcomeQualifier(const PartialOutcomeQualifier& element)
    {
        its::AsnObject& asnObject = const_cast<PartialOutcomeQualifier&>(element);
        asnObject.SetDescription(GetPartialOutcomeQualifierStaticDescription());
        AddElement(2, element);
}

    bool OptionPartialOutcomeQualifier() const
    {
        return Contains(2);
    }

    const PartialOutcomeQualifier& GetPartialOutcomeQualifier() const
    {
        ITS_REQUIRE(OptionPartialOutcomeQualifier());
        return static_cast<const PartialOutcomeQualifier&> (ElementAt(2));
    }

    void SetSecurityParameters(SecurityParameters* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSecurityParametersStaticDescription());
        AddElement(3, element);
    }

    void SetSecurityParameters(const SecurityParameters& element)
    {
        its::AsnObject& asnObject = const_cast<SecurityParameters&>(element);
        asnObject.SetDescription(GetSecurityParametersStaticDescription());
        AddElement(3, element);
}

    bool OptionSecurityParameters() const
    {
        return Contains(3);
    }

    const SecurityParameters& GetSecurityParameters() const
    {
        ITS_REQUIRE(OptionSecurityParameters());
        return static_cast<const SecurityParameters&> (ElementAt(3));
    }

    void SetPerformer(DistinguishedName* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPerformerStaticDescription());
        AddElement(4, element);
    }

    void SetPerformer(const DistinguishedName& element)
    {
        its::AsnObject& asnObject = const_cast<DistinguishedName&>(element);
        asnObject.SetDescription(GetPerformerStaticDescription());
        AddElement(4, element);
}

    bool OptionPerformer() const
    {
        return Contains(4);
    }

    const DistinguishedName& GetPerformer() const
    {
        ITS_REQUIRE(OptionPerformer());
        return static_cast<const DistinguishedName&> (ElementAt(4));
    }

    void SetAliasDereferenced(AliasDereferenced* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetAliasDereferencedStaticDescription());
        AddElement(5, element);
    }

    void SetAliasDereferenced(const AliasDereferenced& element)
    {
        its::AsnObject& asnObject = const_cast<AliasDereferenced&>(element);
        asnObject.SetDescription(GetAliasDereferencedStaticDescription());
        AddElement(5, element);
}

    bool OptionAliasDereferenced() const
    {
        return Contains(5);
    }

    const AliasDereferenced& GetAliasDereferenced() const
    {
        ITS_REQUIRE(OptionAliasDereferenced());
        return static_cast<const AliasDereferenced&> (ElementAt(5));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_SEARCH_INFO_H_)

