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


#if !defined(_MAP_V2_DEACTIVATE_TRACE_MODE_ARG_H_)
#define _MAP_V2_DEACTIVATE_TRACE_MODE_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v2_imsi.h>
#include <map_v2_trace_reference.h>



namespace map_v2 {



class DeactivateTraceModeArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v2::IMSI IMSI;


        typedef map_v2::TraceReference TraceReference;


////////// End Nested Class(es) //////////

    DeactivateTraceModeArg() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    DeactivateTraceModeArg(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    DeactivateTraceModeArg(const DeactivateTraceModeArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    DeactivateTraceModeArg(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetImsiStaticDescription();
    static its::AsnDescObject* GetTraceReferenceStaticDescription();

public:

    virtual ~DeactivateTraceModeArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new DeactivateTraceModeArg(*this);
    }

    virtual std::string GetName() const
    { return "DeactivateTraceModeArg"; }

    void SetImsi(IMSI* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    void SetImsi(const IMSI& element)
    {
        its::AsnObject& asnObject = const_cast<IMSI&>(element);
        asnObject.SetDescription(GetImsiStaticDescription());
        AddElement(0, element);
    }

    bool OptionImsi() const
    {
        return Contains(0);
    }

    const IMSI& GetImsi() const
    {
        ITS_REQUIRE(OptionImsi());
        return static_cast<const IMSI&> (ElementAt(0));
    }

    void SetTraceReference(TraceReference* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTraceReferenceStaticDescription());
        AddElement(1, element);
    }

    void SetTraceReference(const TraceReference& element)
    {
        its::AsnObject& asnObject = const_cast<TraceReference&>(element);
        asnObject.SetDescription(GetTraceReferenceStaticDescription());
        AddElement(1, element);
    }

    const TraceReference& GetTraceReference() const
    {
        return static_cast<const TraceReference&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V2_DEACTIVATE_TRACE_MODE_ARG_H_)

