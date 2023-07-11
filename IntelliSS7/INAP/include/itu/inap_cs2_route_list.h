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


#if !defined(_INAP_CS2_ROUTE_LIST_H_)
#define _INAP_CS2_ROUTE_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnOctetString.h>



namespace inap_cs2 {



class RouteList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////



    class OCTETSTRING : public its::AsnOctetString
    {
    public:

        OCTETSTRING() : its::AsnOctetString(false)
        {
            Initialize();
        }

        OCTETSTRING(const std::vector<byte>& array) : its::AsnOctetString(array, false)
        {
            Initialize();
        }

        OCTETSTRING(its::Octets& octets) : its::AsnOctetString(false)
        {
            Initialize();
            Decode(octets);
        }

        OCTETSTRING(const OCTETSTRING& rhs) : its::AsnOctetString(rhs)
        {
            // Nothing to do.
        }

        OCTETSTRING(its::AsnDescObject* description) : its::AsnOctetString(description)
        {
            // Nothing to do.
        }

        OCTETSTRING(its::AsnDescObject* description, const std::vector<byte>& array) : its::AsnOctetString(description, array)
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

        virtual ~OCTETSTRING()
        {
            // Nothing to do.
        }

        virtual its::AsnObject* Clone() const
        {
            return new OCTETSTRING(*this);
        }

        virtual std::string GetName() const
        { return "OCTETSTRING"; }

    };


////////// End Nested Class //////////

    RouteList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    RouteList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    RouteList(const RouteList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    RouteList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetOCTETSTRINGStaticDescription();

public:

    virtual ~RouteList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new RouteList(*this);
    }

    virtual std::string GetName() const
    { return "RouteList"; }

    void AddElement(OCTETSTRING* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOCTETSTRINGStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const OCTETSTRING& element)
    {
        its::AsnObject& asnObject = const_cast<OCTETSTRING&>(element);
        asnObject.SetDescription(GetOCTETSTRINGStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const OCTETSTRING& ElementAt(int index) const
    {
        return static_cast<const OCTETSTRING&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_INAP_CS2_ROUTE_LIST_H_)

