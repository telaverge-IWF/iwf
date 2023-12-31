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


#if !defined(_MAP_V9_IST_COMMAND_ARG_H_)
#define _MAP_V9_IST_COMMAND_ARG_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>
#include <AsnOctetString.h>

#include <map_v9_imsi.h>
#include <map_v9_extension_container.h>



namespace map_v9 {



class IST_CommandArg : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v9::IMSI IMSI;


        typedef map_v9::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    IST_CommandArg() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    IST_CommandArg(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    IST_CommandArg(const IST_CommandArg& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    IST_CommandArg(its::AsnDescObject* description) : its::AsnSequence(2, description)
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
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~IST_CommandArg()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new IST_CommandArg(*this);
    }

    virtual std::string GetName() const
    { return "IST_CommandArg"; }

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

    const IMSI& GetImsi() const
    {
        return static_cast<const IMSI&> (ElementAt(0));
    }

    void SetExtensionContainer(ExtensionContainer* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetExtensionContainerStaticDescription());
        AddElement(1, element);
    }

    void SetExtensionContainer(const ExtensionContainer& element)
    {
        its::AsnObject& asnObject = const_cast<ExtensionContainer&>(element);
        asnObject.SetDescription(GetExtensionContainerStaticDescription());
        AddElement(1, element);
    }

    bool OptionExtensionContainer() const
    {
        return Contains(1);
    }

    const ExtensionContainer& GetExtensionContainer() const
    {
        ITS_REQUIRE(OptionExtensionContainer());
        return static_cast<const ExtensionContainer&> (ElementAt(1));
    }

};



} // namespace.

#endif    // !defined(_MAP_V9_IST_COMMAND_ARG_H_)

