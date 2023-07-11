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


#if !defined(_MAP_V9_DESTINATION_NUMBER_LENGTH_LIST_H_)
#define _MAP_V9_DESTINATION_NUMBER_LENGTH_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnInteger.h>



namespace map_v9 {



class DestinationNumberLengthList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////



    class INTEGER : public its::AsnInteger
    {
    public:

        INTEGER() : its::AsnInteger(false)
        {
            Initialize();
        }

        INTEGER(long value) : its::AsnInteger(value, false)
        {
            Initialize();
        }

        INTEGER(its::Octets& octets) : its::AsnInteger(false)
        {
            Initialize();
            Decode(octets);
        }

        INTEGER(const INTEGER& rhs) : its::AsnInteger(rhs)
        {
            // Nothing to do.
        }

        INTEGER(its::AsnDescObject* description) : its::AsnInteger(description)
        {
            // Nothing to do.
        }

        INTEGER(its::AsnDescObject* description, long value) : its::AsnInteger(description, value)
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

        virtual ~INTEGER()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new INTEGER(*this);
        }

        virtual std::string GetName() const
        { return "INTEGER"; }

    };


////////// End Nested Class //////////

    DestinationNumberLengthList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    DestinationNumberLengthList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    DestinationNumberLengthList(const DestinationNumberLengthList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    DestinationNumberLengthList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetINTEGERStaticDescription();

public:

    virtual ~DestinationNumberLengthList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new DestinationNumberLengthList(*this);
    }

    virtual std::string GetName() const
    { return "DestinationNumberLengthList"; }

    void AddElement(INTEGER* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetINTEGERStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const INTEGER& element)
    {
        its::AsnObject& asnObject = const_cast<INTEGER&>(element);
        asnObject.SetDescription(GetINTEGERStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const INTEGER& ElementAt(int index) const
    {
        return static_cast<const INTEGER&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_DESTINATION_NUMBER_LENGTH_LIST_H_)

