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


#if !defined(_INAP_CS2_IN_ENTRY_INFORMATION_H_)
#define _INAP_CS2_IN_ENTRY_INFORMATION_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnBoolean.h>
#include <AsnChoice.h>
#include <AsnSetOf.h>

#include <inap_cs2_name.h>
#include <inap_cs2_informations.h>



namespace inap_cs2 {



class InEntryInformation : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////



    class FromEntry : public its::AsnBoolean
    {
    public:

        FromEntry(bool value) : its::AsnBoolean(value, false)
        {
            Initialize();
        }

        FromEntry(its::Octets& octets) : its::AsnBoolean(false, false)
        {
            Initialize();
            Decode(octets);
        }

        FromEntry(const FromEntry& rhs) : its::AsnBoolean(rhs)
        {
            // Nothing to do.
        }

        FromEntry(its::AsnDescObject* description) : its::AsnBoolean(description)
        {
            // Nothing to do.
        }

        FromEntry(its::AsnDescObject* description, bool value) : its::AsnBoolean(description, value)
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

        virtual ~FromEntry()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new FromEntry(*this);
        }

        virtual std::string GetName() const
        { return "FromEntry"; }

    };


        typedef inap_cs2::Name Name;


        typedef inap_cs2::Informations Informations;


////////// End Nested Class(es) //////////

    InEntryInformation() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    InEntryInformation(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    InEntryInformation(const InEntryInformation& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    InEntryInformation(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetEntryNameStaticDescription();
    static its::AsnDescObject* GetFromEntryStaticDescription();
    static its::AsnDescObject* GetInformationStaticDescription();

public:

    virtual ~InEntryInformation()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new InEntryInformation(*this);
    }

    virtual std::string GetName() const
    { return "InEntryInformation"; }

    void SetEntryName(Name* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEntryNameStaticDescription());
        AddElement(0, element);
    }

    void SetEntryName(const Name& element)
    {
        its::AsnObject& asnObject = const_cast<Name&>(element);
        asnObject.SetDescription(GetEntryNameStaticDescription());
        AddElement(0, element);
    }

    const Name& GetEntryName() const
    {
        return static_cast<const Name&> (ElementAt(0));
    }

    void SetFromEntry(FromEntry* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetFromEntryStaticDescription());
        AddElement(1, element);
    }

    void SetFromEntry(const FromEntry& element)
    {
        its::AsnObject& asnObject = const_cast<FromEntry&>(element);
        asnObject.SetDescription(GetFromEntryStaticDescription());
        AddElement(1, element);
    }

    bool OptionFromEntry() const
    {
        return Contains(1);
    }

    const FromEntry& GetFromEntry() const
    {
        ITS_REQUIRE(OptionFromEntry());
        return static_cast<const FromEntry&> (ElementAt(1));
    }

    void SetInformation(Informations* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetInformationStaticDescription());
        AddElement(2, element);
    }

    void SetInformation(const Informations& element)
    {
        its::AsnObject& asnObject = const_cast<Informations&>(element);
        asnObject.SetDescription(GetInformationStaticDescription());
        AddElement(2, element);
    }

    bool OptionInformation() const
    {
        return Contains(2);
    }

    const Informations& GetInformation() const
    {
        ITS_REQUIRE(OptionInformation());
        return static_cast<const Informations&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_IN_ENTRY_INFORMATION_H_)

