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


#if !defined(_MAP_V3_ACTIVATE_TRACE_MODE_ARG_H_)
#define _MAP_V3_ACTIVATE_TRACE_MODE_ARG_H_

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

#include <map_v3_imsi.h>
#include <map_v3_trace_reference.h>
#include <map_v3_trace_type.h>
#include <map_v3_address_string.h>
#include <map_v3_extension_container.h>



namespace map_v3 {



class ActivateTraceModeArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::IMSI IMSI;


        typedef map_v3::TraceReference TraceReference;


        typedef map_v3::TraceType TraceType;


        typedef map_v3::AddressString AddressString;


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    ActivateTraceModeArg() : its::AsnSequence(5, false)
    {
        Initialize();
    }

    ActivateTraceModeArg(its::Octets& octets) : its::AsnSequence(5, false)
    {
        Initialize();
        Decode(octets);
    }

    ActivateTraceModeArg(const ActivateTraceModeArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ActivateTraceModeArg(its::AsnDescObject* description) : its::AsnSequence(5, description)
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
    static its::AsnDescObject* GetOmc_IdStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

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

    void SetOmc_Id(AddressString* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetOmc_IdStaticDescription());
        AddElement(3, element);
    }

    void SetOmc_Id(const AddressString& element)
    {
        its::AsnObject& asnObject = const_cast<AddressString&>(element);
        asnObject.SetDescription(GetOmc_IdStaticDescription());
        AddElement(3, element);
    }

    bool OptionOmc_Id() const
    {
        return Contains(3);
    }

    const AddressString& GetOmc_Id() const
    {
        ITS_REQUIRE(OptionOmc_Id());
        return static_cast<const AddressString&> (ElementAt(3));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(4, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(4, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(4);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(4));
    }

};



} // namespace.

#endif    // !defined(_MAP_V3_ACTIVATE_TRACE_MODE_ARG_H_)

