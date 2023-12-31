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


#if !defined(_MAP_V13_E_UTRAN_CGI_LIST_H_)
#define _MAP_V13_E_UTRAN_CGI_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnOctetString.h>

#include <map_v13_e_utran_cgi.h>



namespace map_v13 {



class E_UTRAN_CGI_List : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::E_UTRAN_CGI E_UTRAN_CGI;


////////// End Nested Class //////////

    E_UTRAN_CGI_List() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    E_UTRAN_CGI_List(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    E_UTRAN_CGI_List(const E_UTRAN_CGI_List& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    E_UTRAN_CGI_List(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetE_UTRAN_CGIStaticDescription();

public:

    virtual ~E_UTRAN_CGI_List()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new E_UTRAN_CGI_List(*this);
    }

    virtual std::string GetName() const
    { return "E_UTRAN_CGI_List"; }

    void AddElement(E_UTRAN_CGI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetE_UTRAN_CGIStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const E_UTRAN_CGI& element)
    {
        its::AsnObject& asnObject = const_cast<E_UTRAN_CGI&>(element);
        asnObject.SetDescription(GetE_UTRAN_CGIStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const E_UTRAN_CGI& ElementAt(int index) const
    {
        return static_cast<const E_UTRAN_CGI&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_E_UTRAN_CGI_LIST_H_)

