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


#if !defined(_MAP_V13_MOLR_LIST_H_)
#define _MAP_V13_MOLR_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v13_molr_class.h>



namespace map_v13 {



class MOLR_List : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::MOLR_Class MOLR_Class;


////////// End Nested Class //////////

    MOLR_List() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    MOLR_List(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    MOLR_List(const MOLR_List& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    MOLR_List(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetMOLR_ClassStaticDescription();

public:

    virtual ~MOLR_List()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new MOLR_List(*this);
    }

    virtual std::string GetName() const
    { return "MOLR_List"; }

    void AddElement(MOLR_Class* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetMOLR_ClassStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const MOLR_Class& element)
    {
        its::AsnObject& asnObject = const_cast<MOLR_Class&>(element);
        asnObject.SetDescription(GetMOLR_ClassStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const MOLR_Class& ElementAt(int index) const
    {
        return static_cast<const MOLR_Class&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_MOLR_LIST_H_)

