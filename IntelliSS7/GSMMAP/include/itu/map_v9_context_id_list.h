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


#if !defined(_MAP_V9_CONTEXT_ID_LIST_H_)
#define _MAP_V9_CONTEXT_ID_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnInteger.h>

#include <map_v9_context_id.h>



namespace map_v9 {



class ContextIdList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v9::ContextId ContextId;


////////// End Nested Class //////////

    ContextIdList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    ContextIdList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    ContextIdList(const ContextIdList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    ContextIdList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetContextIdStaticDescription();

public:

    virtual ~ContextIdList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ContextIdList(*this);
    }

    virtual std::string GetName() const
    { return "ContextIdList"; }

    void AddElement(ContextId* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetContextIdStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const ContextId& element)
    {
        its::AsnObject& asnObject = const_cast<ContextId&>(element);
        asnObject.SetDescription(GetContextIdStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const ContextId& ElementAt(int index) const
    {
        return static_cast<const ContextId&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_CONTEXT_ID_LIST_H_)
