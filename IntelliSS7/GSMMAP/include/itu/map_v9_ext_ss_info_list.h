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


#if !defined(_MAP_V9_EXT_SS_INFO_LIST_H_)
#define _MAP_V9_EXT_SS_INFO_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnChoice.h>

#include <map_v9_ext_ss_info.h>



namespace map_v9 {



class Ext_SS_InfoList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v9::Ext_SS_Info Ext_SS_Info;


////////// End Nested Class //////////

    Ext_SS_InfoList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    Ext_SS_InfoList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    Ext_SS_InfoList(const Ext_SS_InfoList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    Ext_SS_InfoList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetExt_SS_InfoStaticDescription();

public:

    virtual ~Ext_SS_InfoList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new Ext_SS_InfoList(*this);
    }

    virtual std::string GetName() const
    { return "Ext_SS_InfoList"; }

    void AddElement(Ext_SS_Info* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExt_SS_InfoStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const Ext_SS_Info& element)
    {
        its::AsnObject& asnObject = const_cast<Ext_SS_Info&>(element);
        asnObject.SetDescription(GetExt_SS_InfoStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const Ext_SS_Info& ElementAt(int index) const
    {
        return static_cast<const Ext_SS_Info&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_EXT_SS_INFO_LIST_H_)

