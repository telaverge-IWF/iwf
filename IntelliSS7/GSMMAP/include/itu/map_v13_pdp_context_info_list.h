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


#if !defined(_MAP_V13_PDP_CONTEXT_INFO_LIST_H_)
#define _MAP_V13_PDP_CONTEXT_INFO_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v13_pdp_context_info.h>



namespace map_v13 {



class PDP_ContextInfoList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::PDP_ContextInfo PDP_ContextInfo;


////////// End Nested Class //////////

    PDP_ContextInfoList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    PDP_ContextInfoList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    PDP_ContextInfoList(const PDP_ContextInfoList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    PDP_ContextInfoList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetPDP_ContextInfoStaticDescription();

public:

    virtual ~PDP_ContextInfoList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PDP_ContextInfoList(*this);
    }

    virtual std::string GetName() const
    { return "PDP_ContextInfoList"; }

    void AddElement(PDP_ContextInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPDP_ContextInfoStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const PDP_ContextInfo& element)
    {
        its::AsnObject& asnObject = const_cast<PDP_ContextInfo&>(element);
        asnObject.SetDescription(GetPDP_ContextInfoStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const PDP_ContextInfo& ElementAt(int index) const
    {
        return static_cast<const PDP_ContextInfo&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_PDP_CONTEXT_INFO_LIST_H_)

