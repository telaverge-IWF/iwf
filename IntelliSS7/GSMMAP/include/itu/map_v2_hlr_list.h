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


#if !defined(_MAP_V2_HLR_LIST_H_)
#define _MAP_V2_HLR_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnOctetString.h>

#include <map_v2_hlr_id.h>



namespace map_v2 {



class HLR_List : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v2::HLR_Id HLR_Id;


////////// End Nested Class //////////

    HLR_List() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    HLR_List(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    HLR_List(const HLR_List& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    HLR_List(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetHLR_IdStaticDescription();

public:

    virtual ~HLR_List()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new HLR_List(*this);
    }

    virtual std::string GetName() const
    { return "HLR_List"; }

    void AddElement(HLR_Id* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetHLR_IdStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const HLR_Id& element)
    {
        its::AsnObject& asnObject = const_cast<HLR_Id&>(element);
        asnObject.SetDescription(GetHLR_IdStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const HLR_Id& ElementAt(int index) const
    {
        return static_cast<const HLR_Id&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V2_HLR_LIST_H_)
