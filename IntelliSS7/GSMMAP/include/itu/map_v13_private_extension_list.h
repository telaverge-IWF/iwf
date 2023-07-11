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


#if !defined(_MAP_V13_PRIVATE_EXTENSION_LIST_H_)
#define _MAP_V13_PRIVATE_EXTENSION_LIST_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequenceOf.h>
#include <AsnSequence.h>

#include <map_v13_private_extension.h>



namespace map_v13 {



class PrivateExtensionList : public its::AsnSequenceOf
{
public:


////////// Begin Nested Class //////////


        typedef map_v13::PrivateExtension PrivateExtension;


////////// End Nested Class //////////

    PrivateExtensionList() : its::AsnSequenceOf(false)
    {
        Initialize();
    }

    PrivateExtensionList(its::Octets& octets) : its::AsnSequenceOf(false)
    {
        Initialize();
        Decode(octets);
    }

    PrivateExtensionList(const PrivateExtensionList& rhs) : its::AsnSequenceOf(rhs)
    {
        // Nothing to do.
    }

    PrivateExtensionList(its::AsnDescObject* description) : its::AsnSequenceOf(description)
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

    static its::AsnDescObject* GetPrivateExtensionStaticDescription();

public:

    virtual ~PrivateExtensionList()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new PrivateExtensionList(*this);
    }

    virtual std::string GetName() const
    { return "PrivateExtensionList"; }

    void AddElement(PrivateExtension* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetPrivateExtensionStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    void AddElement(const PrivateExtension& element)
    {
        its::AsnObject& asnObject = const_cast<PrivateExtension&>(element);
        asnObject.SetDescription(GetPrivateExtensionStaticDescription());
        AsnSequenceOf::AddElement(element);
    }

    const PrivateExtension& ElementAt(int index) const
    {
        return static_cast<const PrivateExtension&> (AsnSequenceOf::ElementAt(index));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_PRIVATE_EXTENSION_LIST_H_)

