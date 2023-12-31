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


#if !defined(_MAP_V13_ANY_TIME_INTERROGATION_RES_H_)
#define _MAP_V13_ANY_TIME_INTERROGATION_RES_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <Asn.h>
#include <AsnObject.h>
#include <AsnDescObject.h>
#include <AsnError.h>

#include <AsnSequence.h>

#include <map_v13_subscriber_info.h>
#include <map_v13_extension_container.h>



namespace map_v13 {



class AnyTimeInterrogationRes : public its::AsnSequence
{
public:


////////// Begin Nested Class(es) //////////


        typedef map_v13::SubscriberInfo SubscriberInfo;


        typedef map_v13::ExtensionContainer ExtensionContainer;


////////// End Nested Class(es) //////////

    AnyTimeInterrogationRes() : its::AsnSequence(2, false)
    {
        Initialize();
    }

    AnyTimeInterrogationRes(its::Octets& octets) : its::AsnSequence(2, false)
    {
        Initialize();
        Decode(octets);
    }

    AnyTimeInterrogationRes(const AnyTimeInterrogationRes& rhs) : its::AsnSequence(rhs)
    {
        // Nothing to do.
    }

    AnyTimeInterrogationRes(its::AsnDescObject* description) : its::AsnSequence(2, description)
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

    static its::AsnDescObject* GetSubscriberInfoStaticDescription();
    static its::AsnDescObject* GetExtensionContainerStaticDescription();

public:

    virtual ~AnyTimeInterrogationRes()
    {
        // Nothing to do.
    }

    virtual its::AsnObject* Clone() const
    {
        return new AnyTimeInterrogationRes(*this);
    }

    virtual std::string GetName() const
    { return "AnyTimeInterrogationRes"; }

    void SetSubscriberInfo(SubscriberInfo* element)
    {
        ITS_REQUIRE(element != NULL);
        element->AsnObject::SetDescription(GetSubscriberInfoStaticDescription());
        AddElement(0, element);
    }

    void SetSubscriberInfo(const SubscriberInfo& element)
    {
        its::AsnObject& asnObject = const_cast<SubscriberInfo&>(element);
        asnObject.SetDescription(GetSubscriberInfoStaticDescription());
        AddElement(0, element);
    }

    const SubscriberInfo& GetSubscriberInfo() const
    {
        return static_cast<const SubscriberInfo&> (ElementAt(0));
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

#endif    // !defined(_MAP_V13_ANY_TIME_INTERROGATION_RES_H_)

