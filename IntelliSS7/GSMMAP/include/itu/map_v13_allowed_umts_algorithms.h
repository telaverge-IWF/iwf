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


#if !defined(_MAP_V13_ALLOWED_UMTS_ALGORITHMS_H_)
#define _MAP_V13_ALLOWED_UMTS_ALGORITHMS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v13_permitted_integrity_protection_algorithms.h>
#include <map_v13_permitted_encryption_algorithms.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class AllowedUMTS_Algorithms : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::PermittedIntegrityProtectionAlgorithms PermittedIntegrityProtectionAlgorithms;


        typedef map_v13::PermittedEncryptionAlgorithms PermittedEncryptionAlgorithms;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    AllowedUMTS_Algorithms() : its::AsnSequence(3, false)
    {
        Initialize();
    }

    AllowedUMTS_Algorithms(its::Octets& octets) : its::AsnSequence(3, false)
    {
        Initialize();
        Decode(octets);
    }

    AllowedUMTS_Algorithms(const AllowedUMTS_Algorithms& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    AllowedUMTS_Algorithms(its::AsnDescObject* description) : its::AsnSequence(3, description)
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

    static its::AsnDescObject* GetIntegrityProtectionAlgorithmsStaticDescription();
    static its::AsnDescObject* GetEncryptionAlgorithmsStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~AllowedUMTS_Algorithms()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AllowedUMTS_Algorithms(*this);
    }

    virtual std::string GetName() const
    { return "AllowedUMTS_Algorithms"; }

    void SetIntegrityProtectionAlgorithms(PermittedIntegrityProtectionAlgorithms* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetIntegrityProtectionAlgorithmsStaticDescription());
        AddElement(0, element);
    }

    void SetIntegrityProtectionAlgorithms(const PermittedIntegrityProtectionAlgorithms& element)
    {
        its::AsnObject& asnObject = const_cast<PermittedIntegrityProtectionAlgorithms&>(element);
        asnObject.SetDescription(GetIntegrityProtectionAlgorithmsStaticDescription());
        AddElement(0, element);
    }

    bool OptionIntegrityProtectionAlgorithms() const
    {
        return Contains(0);
    }

    const PermittedIntegrityProtectionAlgorithms& GetIntegrityProtectionAlgorithms() const
    {
        ITS_REQUIRE(OptionIntegrityProtectionAlgorithms());
        return static_cast<const PermittedIntegrityProtectionAlgorithms&> (ElementAt(0));
    }

    void SetEncryptionAlgorithms(PermittedEncryptionAlgorithms* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetEncryptionAlgorithmsStaticDescription());
        AddElement(1, element);
    }

    void SetEncryptionAlgorithms(const PermittedEncryptionAlgorithms& element)
    {
        its::AsnObject& asnObject = const_cast<PermittedEncryptionAlgorithms&>(element);
        asnObject.SetDescription(GetEncryptionAlgorithmsStaticDescription());
        AddElement(1, element);
    }

    bool OptionEncryptionAlgorithms() const
    {
        return Contains(1);
    }

    const PermittedEncryptionAlgorithms& GetEncryptionAlgorithms() const
    {
        ITS_REQUIRE(OptionEncryptionAlgorithms());
        return static_cast<const PermittedEncryptionAlgorithms&> (ElementAt(1));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(2, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(2, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(2);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(2));
    }

};



} // namespace.

#endif    // !defined(_MAP_V13_ALLOWED_UMTS_ALGORITHMS_H_)

