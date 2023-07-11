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


#if !defined(_MAP_V13_CGI_LIST_H_)
#define _MAP_V13_CGI_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnOctetString.h>

#include <map_v13_global_cell_id.h>



namespace map_v13 {



class CGI_List : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::GlobalCellId GlobalCellId;


////////// End Nested Class //////////

    CGI_List() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    CGI_List(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    CGI_List(const CGI_List& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    CGI_List(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetGlobalCellIdStaticDescription();

public:

    virtual ~CGI_List()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new CGI_List(*this);
    }

    virtual std::string GetName() const
    { return "CGI_List"; }

    void AddElement(GlobalCellId* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetGlobalCellIdStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const GlobalCellId& element)
    {
        its::AsnObject& asnObject = const_cast<GlobalCellId&>(element);
        asnObject.SetDescription(GetGlobalCellIdStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const GlobalCellId& ElementAt(int index) const
    {
        return static_cast<const GlobalCellId&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_CGI_LIST_H_)

