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


#if !defined(_MAP_V3_SUB_BUSY_FOR_MT_SMS_PARAM_H_)
#define _MAP_V3_SUB_BUSY_FOR_MT_SMS_PARAM_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>

#include <map_v3_extension_container.h>



namespace map_v3 {



class SubBusyForMT_SMS_Param : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v3::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    SubBusyForMT_SMS_Param() : its::AsnSequence(1, false)
    {
        Initialize();
    }

    SubBusyForMT_SMS_Param(its::Octets& octets) : its::AsnSequence(1, false)
    {
        Initialize();
        Decode(octets);
    }

    SubBusyForMT_SMS_Param(const SubBusyForMT_SMS_Param& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    SubBusyForMT_SMS_Param(its::AsnDescObject* description) : its::AsnSequence(1, description)
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

    virtual ~SubBusyForMT_SMS_Param()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new SubBusyForMT_SMS_Param(*this);
    }

    virtual std::string GetName() const
    { return "SubBusyForMT_SMS_Param"; }

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

#endif    // !defined(_MAP_V3_SUB_BUSY_FOR_MT_SMS_PARAM_H_)

