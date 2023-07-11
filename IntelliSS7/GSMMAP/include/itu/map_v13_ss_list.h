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


#if !defined(_MAP_V13_SS_LIST_H_)
#define _MAP_V13_SS_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnOctetString.h>

#include <map_v13_ss_code.h>



namespace map_v13 {



class SS_List : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::SS_Code SS_Code;


////////// End Nested Class //////////

    SS_List() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    SS_List(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    SS_List(const SS_List& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    SS_List(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetSS_CodeStaticDescription();

public:

    virtual ~SS_List()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SS_List(*this);
    }

    virtual std::string GetName() const
    { return "SS_List"; }

    void AddElement(SS_Code* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSS_CodeStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const SS_Code& element)
    {
        its::AsnObject& asnObject = const_cast<SS_Code&>(element);
        asnObject.SetDescription(GetSS_CodeStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const SS_Code& ElementAt(int index) const
    {
        return static_cast<const SS_Code&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_SS_LIST_H_)

