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


#if !defined(_MAP_V13_RELEASE_RESOURCES_RES_H_)
#define _MAP_V13_RELEASE_RESOURCES_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>

#include <map_v13_extension_container.h>



namespace map_v13 {



class ReleaseResourcesRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    ReleaseResourcesRes() : its::AsnSequence(1, false)
    {
        Initialize();
    }

    ReleaseResourcesRes(its::Octets& octets) : its::AsnSequence(1, false)
    {
        Initialize();
        Decode(octets);
    }

    ReleaseResourcesRes(const ReleaseResourcesRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    ReleaseResourcesRes(its::AsnDescObject* description) : its::AsnSequence(1, description)
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

    virtual ~ReleaseResourcesRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new ReleaseResourcesRes(*this);
    }

    virtual std::string GetName() const
    { return "ReleaseResourcesRes"; }

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

#endif    // !defined(_MAP_V13_RELEASE_RESOURCES_RES_H_)

