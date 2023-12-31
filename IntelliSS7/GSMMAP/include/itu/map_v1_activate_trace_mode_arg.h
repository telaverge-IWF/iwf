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


#if !defined(_MAP_V1_ACTIVATE_TRACE_MODE_ARG_H_)
#define _MAP_V1_ACTIVATE_TRACE_MODE_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>
#include <AsnInteger.h>

#include <map_v1_imsi.h>
#include <map_v1_trace_reference.h>
#include <map_v1_trace_type.h>
#include <map_v1_address_string.h>



namespace map_v1 {



class ActivateTraceModeArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v1::IMSI IMSI;


        typedef map_v1::TraceReference TraceReference;


        typedef map_v1::TraceType TraceType;


        typedef map_v1::AddressString AddressString;


////////// End Nested Class(es) //////////

    ActivateTraceModeArg() : its::AsnSequence(4, false)
    {
        Initialize();
    }

    ActivateTraceModeArg(its::Octets& octets) : its::AsnSequence(4, false)
    {
        Initialize();
        Decode(octets);
    }

    ActivateTraceModeArg(const ActivateTraceModeArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ActivateTraceModeArg(its::AsnDescObject* description) : its::AsnSequence(4, description)
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
    static its::AsnDescObject* GetTraceTypeStaticDescription();
    static its::AsnDescObject* GetOmcIdStaticDescription();

public:

    virtual ~ActivateTraceModeArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ActivateTraceModeArg(*this);
    }

    virtual std::string GetName() const
    { return "ActivateTraceModeArg"; }

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

    void SetTraceType(TraceType* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetTraceTypeStaticDescription());
        AddElement(2, element);
    }

    void SetTraceType(const TraceType& element)
    {
        its::AsnObject& asnObject = const_cast<TraceType&>(element);
        asnObject.SetDescription(GetTraceTypeStaticDescription());
        AddElement(2, element);
    }

    const TraceType& GetTraceType() const
    {
        return static_cast<const TraceType&> (ElementAt(2));
    }

    void SetOmcId(AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOmcIdStaticDescription());
        AddElement(3, element);
    }

    void SetOmcId(const AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<AddressString&>(element);
        asnObject.SetDescription(GetOmcIdStaticDescription());
        AddElement(3, element);
    }

    bool OptionOmcId() const
    {
        return Contains(3);
    }

    const AddressString& GetOmcId() const
    {
        ITS_REQUIRE(OptionOmcId());
        return static_cast<const AddressString&> (ElementAt(3));
    }

};



} // namespace.

#endif    // !defined(_MAP_V1_ACTIVATE_TRACE_MODE_ARG_H_)

