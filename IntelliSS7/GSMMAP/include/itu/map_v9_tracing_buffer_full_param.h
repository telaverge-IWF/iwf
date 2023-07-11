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


#if !defined(_MAP_V9_TRACING_BUFFER_FULL_PARAM_H_)
#define _MAP_V9_TRACING_BUFFER_FULL_PARAM_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>

#include <map_v9_extension_container.h>



namespace map_v9 {



class TracingBufferFullParam : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    TracingBufferFullParam() : its::AsnSequence(1, false)
    {
        Initialize();
    }

    TracingBufferFullParam(its::Octets& octets) : its::AsnSequence(1, false)
    {
        Initialize();
        Decode(octets);
    }

    TracingBufferFullParam(const TracingBufferFullParam& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    TracingBufferFullParam(its::AsnDescObject* description) : its::AsnSequence(1, description)
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

    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~TracingBufferFullParam()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new TracingBufferFullParam(*this);
    }

    virtual std::string GetName() const
    { return "TracingBufferFullParam"; }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(0, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(0, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(0);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(0));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_TRACING_BUFFER_FULL_PARAM_H_)

