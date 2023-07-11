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


#if !defined(_MAP_V13_SS_INFO_LIST_H_)
#define _MAP_V13_SS_INFO_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnChoice.h>

#include <map_v13_ss_info.h>



namespace map_v13 {



class SS_InfoList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::SS_Info SS_Info;


////////// End Nested Class //////////

    SS_InfoList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    SS_InfoList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    SS_InfoList(const SS_InfoList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    SS_InfoList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetSS_InfoStaticDescription();

public:

    virtual ~SS_InfoList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SS_InfoList(*this);
    }

    virtual std::string GetName() const
    { return "SS_InfoList"; }

    void AddElement(SS_Info* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSS_InfoStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const SS_Info& element)
    {
        its::AsnObject& asnObject = const_cast<SS_Info&>(element);
        asnObject.SetDescription(GetSS_InfoStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const SS_Info& ElementAt(int index) const
    {
        return static_cast<const SS_Info&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_SS_INFO_LIST_H_)

